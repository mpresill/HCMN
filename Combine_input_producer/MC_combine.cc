/**
This Macro   
1. Makes the root files with all the TH1F needed for limit evaluation 

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
const string path     = "/afs/cern.ch/work/m/mpresill/HCMN/BkgEstimation/"; 

const char *samples[] = {//"TT_2016","tW_2016", 
	                     "DY","TTtW","Other"
                        ,"data_ele"
                        //"data_mu"
                         //,"data_ele_B", "data_ele_C", "data_ele_D", "data_ele_E", "data_ele_F", "data_ele_G", "data_ele_H",
                         //"data_mu_B","data_mu_C", "data_mu_D", "data_mu_E", "data_mu_F", "data_mu_G","data_mu_H"
                        //,"mumujj_L13000_M500_2016","mumujj_L13000_M1000_2016","mumujj_L13000_M2000_2016","mumujj_L13000_M5000_2016","mumujj_L13000_M8000_2016"
			//,"eejj_L13000_M500_2016","eejj_L13000_M1000_2016","eejj_L13000_M2000_2016","eejj_L13000_M5000_2016","eejj_L13000_M8000_2016" 
};

const string selection    = "_2016_SRe";  

//Plots option
const string varplot    = "M_leplepBjet";
const double fixcut     = 0; //Save only events for which varplot>fixcut
const string objsf      = "lepsf_evt";//"lepsf_evt";
const string PUw        = "PileupWeight";
const double Luminosity = 35542; //pb^-1    //2018: 58873 //2017: 41529 //2016: 35542
const bool noLumiNorm   = false;
const bool noPUcorr     = false;
const bool noobjsf      = false;  
const double normalize  = false;
//Binning
const int    bin             = 9; //For symmetric or asymmetric bins
const double inRange         = 0;
const double endRange        = 10000;
const bool   asymbin         = true;
const double asymbins[bin+1] = {0,200,400,600,800,1000,1400,2000,3500,10000};
//Error of bkg (pay attention to use symmetric or asymmetric errors)
/////
//   Declare functions 
/////
TH1F* get_treehist(string rootpla, int idx);
/////
//   Main function
/////
void MC_combine(){
 //vector<string> parampoints(ParamPoints, ParamPoints + sizeof(ParamPoints)/sizeof(ParamPoints[0]));
  vector<string> rootplas(samples, samples + sizeof(samples)/sizeof(samples[0]));
  for(uint i=0; i<rootplas.size(); i++){
    
    TH1F* histo =  get_treehist(rootplas[i],i);
    cout<<"n. events "<<rootplas[i]<<"="<<histo->Integral()<<"\n";
    TH1F* histo2;
    for(int j=1; j<=bin; j++){
        histo2->SetBinContent(j,histo->GetBinContent(j));
        if(histo2->GetBinContent(j)!=0){
           histo2->SetBinError(j,histo->GetBinError(j));
        }
        else{histo2->SetBinError(j,0);}
        //cout<<"Bin"<<j<<"="<<histo2->GetBinContent(j)<<endl;
        //cout<<"Err"<<j<<"="<<histo2->GetBinError(j)<<endl;
    }
    //Create new file
    string norm;
    if(normalize) norm = "_norm";
    string newfilename = rootplas[i]+norm+".root";
    TFile *newfile = new TFile(newfilename.c_str(),"recreate");
    histo2->Write();  delete histo2;
 
    newfile->Write();
    newfile->Close();
  }
}
/////
//   Call TFile to be read
//
TH1F* get_treehist(string rootpla, int idx){
  //New TH1F
  TH1F *hist;
  string namehist;
  if(rootpla.substr(0,1)=="L") namehist = "sig";
  else                         namehist = rootpla;
  if(!asymbin) hist = new TH1F(namehist.c_str(),namehist.c_str(),bin,inRange,endRange);
  else         hist = new TH1F(namehist.c_str(),namehist.c_str(),bin,asymbins);
  //Call root file
  string file_name = path+rootpla+selection+".root";
  TFile* f = new TFile(file_name.c_str(),"read");
  TTree *tree; f->GetObject("BOOM",tree); 
  //branches declaration
  double curr_var; TBranch *b_curr_var = 0; tree->SetBranchAddress(varplot.c_str(),&curr_var,&b_curr_var);
  double PileupWeight; TBranch *b_PileupWeight = 0; tree->SetBranchAddress("PileupWeight",&PileupWeight,&b_PileupWeight); 
  double lumi_wgt; TBranch *b_lumi_wgt = 0; tree->SetBranchAddress("lumi_wgt",&lumi_wgt,&b_lumi_wgt);
  double sf_obj; TBranch *b_sf_obj = 0; tree->SetBranchAddress(objsf.c_str(),&sf_obj,&b_sf_obj);
  //Fill TH1F
  for(int j=0; j<tree->GetEntries(); j++)
  {
    Long64_t tentry = tree->LoadTree(j);
    b_curr_var->GetEntry(tentry);
    b_PileupWeight->GetEntry(tentry);
    b_lumi_wgt->GetEntry(tentry);
    b_sf_obj->GetEntry(tentry);
    double w = 1.;
    if(rootpla!="data_ele"||rootpla!="data_mu"){
      if(!noLumiNorm) w = w*lumi_wgt*Luminosity;
      if(!noPUcorr)   w = w*PileupWeight;
      if(!noobjsf)    w = w*sf_obj;
      //cout <<"w = " << w <<"\n";
    }
    if(curr_var>fixcut){
      if(curr_var<endRange) hist->Fill(curr_var,w);
      else                  hist->Fill(endRange*0.99999,w);
    }
  }
  delete tree;
  return hist;
}

/*
  //Systematic calculation
  for(int j=1; j<=bin; j++){
   double binerr=sqrt(DY->GetBinContent(j));
   double bincont=DY->GetBinContent(j);
   double syst;
   if(bincont>0){
    syst=sqrt(pow((binerr*DYSF),2)+pow((bincont*DYSFerr),2));
   }
   else syst=0;
   cout<<"bin "<<j<<" syst "<<syst<<endl;
  }
  for(int i=1; i<=bin; i++){
    Other2->SetBinContent(i,Other->GetBinContent(i));
    if(Other2->GetBinContent(i)!=0){
     Other2->SetBinError(i,Other->GetBinError(i));
    }
    else{Other2->SetBinError(i,0);}
    cout<<"Bin"<<i<<"="<<Other2->GetBinContent(i)<<endl;
    cout<<"Err"<<i<<"="<<Other2->GetBinError(i)<<endl;
  } 
  */