/**
This Macro   
1. esimate QCD background contribution
2. Makes the root files with all the TH1F needed for limit evaluation 

Need to specify
1. See Declare Constants
*/
/////
//   To run: root -l Limit_rootFile.cc+  
/////
/////
//   Prepare Root and Roofit
/////
#include "TFile.h"
#include "TH1F.h"
#include "THStack.h"
#include "TLegend.h"
#include "TTree.h"
#include "TTreePlayer.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TEfficiency.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iostream>
using namespace std;
/////
//   Declare constants
/////
//Path - samples 
const string path         = "";
const char *samples[] = {//"TT","tW", 
	                "Other","DY","TTtW",
                         "data_ele"
                         //"data_mu"
			};
const string selection    = "_2016_QCDele";  //QCDmu
//Plots option
const string varplot    = "M_ele1ele2Bjet1"; //this is the variable for MllJ (for eejj and mumujj)
const double fixcut     = 0; //Save only events for which varplot>fixcut
const string objsf      = "lepsf_evt";
const double Luminosity = 35542; //pb^-1    //2018: 58873 //2017: 41529 //2016: 35542
const bool LumiNorm   = true;
const bool PUcorr     = true;
const bool objsfCorr  = true;  
const double normalize  = false;
//Binning
const int    bin             = 9; //For symmetric or asymmetric bins
const double inRange         = 0;
const double endRange        = 10000;
const bool   asymbin         = true;
const double asymbins[bin+1] = {0,200,400,600,800,1000,1400,2000,3500,10000};

/////
//   Declare functions 
/////
TH1F* get_treehist(string rootpla);

/////
//   Main function
/////
void Matteo_QCD_Ele_Estimation(){
    vector<string> rootplas(samples, samples + sizeof(samples)/sizeof(samples[0]));
    //Declare histos
    TH1F *DY; TH1F *TT; TH1F *tW; TH1F *TTtW; TH1F *Other; TH1F *data_read; TH1F *data_obs; TH1F *data_sub; TH1F *sig;
    if(!asymbin){
    DY    = new TH1F("","",bin,inRange,endRange);
    TT    = new TH1F("","",bin,inRange,endRange);
    tW    = new TH1F("","",bin,inRange,endRange);
    Other = new TH1F("","",bin,inRange,endRange);
    data_obs  = new TH1F("data_obs","data_obs",bin,inRange,endRange);
    data_sub = new TH1F("QCD","QCD",bin,inRange,endRange);
    data_read = new TH1F("QCD","QCD",bin,inRange,endRange);
    sig   = new TH1F("","",bin,inRange,endRange);
    TTtW  = new TH1F("","",bin,inRange,endRange);
    }else{
    DY    = new TH1F("","",bin,asymbins);
    TT    = new TH1F("","",bin,asymbins);
    tW    = new TH1F("","",bin,asymbins);
    Other = new TH1F("","",bin,asymbins);
    data_obs  = new TH1F("data_obs","data_obs",bin,asymbins);
    data_sub = new TH1F("QCD","QCD",bin,asymbins);
    data_read = new TH1F("QCD","QCD",bin,asymbins);
    sig   = new TH1F("","",bin,asymbins);
    TTtW  = new TH1F("","",bin,asymbins);
    }
    //data_obs->Sumw2();//For the moment, untile you get it as a sum of SM bkg
    data_read->Sumw2();
    data_sub->Sumw2();
    
    for(uint i=0; i<rootplas.size(); i++){
        if(rootplas[i]=="DY") DY = get_treehist(rootplas[i]);
        if(rootplas[i]=="TTtW") TTtW = get_treehist(rootplas[i]);
        if(rootplas[i]=="Other") Other = get_treehist(rootplas[i]);
        if(rootplas[i]=="data_ele")   data_read = get_treehist(rootplas[i]);
    }

//subtracting the non-QCD backgrounds to the QCD bkg
    cout<<"data before "<<data_read->Integral()<<endl;
    data_read->Add(data_read,DY,1,-1);
    data_read->Add(data_read,Other,1,-1);
    data_read->Add(data_read,TTtW,1,-1);
    //data_read->Add(data_read,tW,1,-1);
    cout<<"data after "<<data_read->Integral()<<endl;
    //TTtW->Add(TT,tW,1,1);
    
    for(int i=1; i<=bin; i++){
        if(data_read->GetBinContent(i)>0){
        data_sub->SetBinContent(i,data_read->GetBinContent(i));
        data_sub->SetBinError(i,data_read->GetBinError(i));
        }
        else{
        data_sub->SetBinContent(i,0);
        data_sub->SetBinError(i,0);
        }
        cout<<"Bin"<<i<<"="<<data_sub->GetBinContent(i)<<"\t"<<"Err"<<i<<"="<<data_sub->GetBinError(i)<< endl;
    } 
    
    //Create new file with QCD bkg estimated from CR
    string norm;
    if(normalize) norm = "_norm";
    string newfilename = "eejj_QCD"+norm+".root";
    TFile *newfile = new TFile(newfilename.c_str(),"recreate");
    data_sub->Write();  delete data_sub;
    //eventually add Other_MC estimate output directly here
    
    newfile->Write();
    newfile->Close();
}



/////
//   Call TFile to be read
//
TH1F* get_treehist(string rootpla){
    //New TH1F
    TH1F *hist;
    string namehist= rootpla;
    if(!asymbin) hist = new TH1F(namehist.c_str(),namehist.c_str(),bin,inRange,endRange);
    else         hist = new TH1F(namehist.c_str(),namehist.c_str(),bin,asymbins);
    //Call root file
    string file_name = path+rootpla+selection+".root";
    TFile* f = new TFile(file_name.c_str(),"update");
    TTree *tree; f->GetObject("BOOM",tree); 
    double curr_var;
    TBranch *b_curr_var = 0;
    tree->SetBranchAddress(varplot.c_str(),&curr_var,&b_curr_var);
    double PileupWeight;
    TBranch *b_PileupWeight = 0;
    tree->SetBranchAddress("PileupWeight",&PileupWeight,&b_PileupWeight);
    double lumi_wgt;
    TBranch *b_lumi_wgt = 0;
    tree->SetBranchAddress("lumi_wgt",&lumi_wgt,&b_lumi_wgt);
    double sf_obj;
    TBranch *b_sf_obj = 0;
    tree->SetBranchAddress(objsf.c_str(),&sf_obj,&b_sf_obj);
    double QCD_wgt_evt;
    TBranch *b_QCD_wgt_evt = 0;
    tree->SetBranchAddress("QCD_wgt_evt",&QCD_wgt_evt,&b_QCD_wgt_evt); 

    //Fill TH1F
    for(int j=0; j<tree->GetEntries(); j++){
        Long64_t tentry = tree->LoadTree(j);
        b_curr_var->GetEntry(tentry);
        b_PileupWeight->GetEntry(tentry);
        b_lumi_wgt->GetEntry(tentry);
        b_sf_obj->GetEntry(tentry);
        b_QCD_wgt_evt->GetEntry(tentry);

        double w = 1.;
        if(rootpla!="data_ele"){
        if(LumiNorm) w = w*lumi_wgt*Luminosity;
        if(PUcorr)   w = w*PileupWeight;
        if(objsfCorr)    w = w*sf_obj;
        }
        w = w*QCD_wgt_evt;
        if(curr_var>fixcut){
        if(curr_var<endRange) hist->Fill(curr_var,w);
            else                  hist->Fill(endRange*0.99999,w);
        }
    }
    delete tree;
    return hist;
}