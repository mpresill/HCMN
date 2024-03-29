/**
This Macro   
1. Counts the number of events passing a given selection
Need to specify
1. See Declare Constants
*/
/////
//   To run: root -l CountingEvt.cc+  
/////
/////
//   Prepare Root and Roofit
/////
#include "TFile.h"
#include "TH1F.h"
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
//Path and root files
const string path           = ""; 
                              
const char *samples[]       = {
                              "DY","TT","ST","WW","WZ","ZZ","WJets",
                              //"data_ele"
                              "data_ele"
};
const string selection      = "_2016_QCDe";//aggiungere _selection 
const string channel        = "";
//Selections
const bool obj_sel          = true;
//Corrections
/*const double xSecs[]        = {831.76
                          // 331.7e-03,114.4e-03,22.36e-03,5.029e-03,
                           //3.197e-03,0.7725e-03,0.226e-03,0.06214e-03,0.01584e-03,
                           //0.415e-03,0.08383e-03,0.001841e-03,
                           //6099.17, 831.76, 35.6, 35.6, 61526.7, 118.70838, 47.13, 16.523
};
const double evtsRead[]     = {116591749
                           //100000,99000,100000,85000,
                           //99800,99200,99200,99800,99800,
                           //99200,100000,57000,
                           //9042031, 116591749, 995600, 988500, 72117311, 993640, 978512, 996944
};*/
const double Luminosity     = 35542; //pb^-1    //2018: 58873 //2017: 41529 //2016: 35542
const bool LumiNorm         = true; 
const bool PUcorr           = true; 
const bool GenWgtcorr       = false; 
const bool eleSFcorrection  = false;
const bool QCDcorr          = false;
//Print
const int SETPRECISION      = 10;
double evt_wgt = 1.;
/////
//   Declare functions 
/////
TFile* Call_TFile(string rootpla);
void Evt_after_sel(vector<string> &rootplas, vector<double> &evt_sel, vector<double> &evt_errs, string after_sel); 
/////
//   Main function
/////
void CountingEvt_QCD(){
 //Selections
 vector<double> evt_obj_sels;
 vector<double> evt_errs;
 vector<double> lumi_wgts; //Need to save it to calculate properly the errors
 //Run over all samples 
// vector<double> xsecs(xSecs, xSecs + sizeof(xSecs)/sizeof(xSecs[0]));
 //vector<double> evtsread(evtsRead, evtsRead + sizeof(evtsRead)/sizeof(evtsRead[0]));
 vector<string> rootplas(samples, samples + sizeof(samples)/sizeof(samples[0]));
    for(uint r=0; r<rootplas.size(); r++){
    double lumi_wgt2 = 1.;
    //Call tree  
    TFile* f = Call_TFile(rootplas[r]); TTree* tree; f->GetObject("BOOM",tree);
    /////
    //   Get variables
    /////
    double lepsf_evt;
    TBranch *b_lepsf_evt = 0;
    tree->SetBranchAddress("lepsf_evt",&lepsf_evt,&b_lepsf_evt);
    //Pileup: "PileupWeight" is the branch updated by Vale
    double PileupWeight;
    TBranch *b_PileupWeight = 0;
    tree->SetBranchAddress("PileupWeight",&PileupWeight,&b_PileupWeight);
    //Lumi 
    double lumi_wgt;
    TBranch *b_lumi_wgt = 0;
    tree->SetBranchAddress("lumi_wgt",&lumi_wgt,&b_lumi_wgt);
    //QCDcorr
    // double QCD_wgt_mu1;
    //TBranch *b_QCD_wgt_mu1 = 0;
    // tree->SetBranchAddress("QCD_wgt_mu1",&QCD_wgt_mu1,&b_QCD_wgt_mu1);
    // double QCD_wgt_mu2;
    // TBranch *b_QCD_wgt_mu2 = 0;
    // tree->SetBranchAddress("QCD_wgt_mu2",&QCD_wgt_mu2,&b_QCD_wgt_mu2);
    double QCD_wgt_evt;
    TBranch *b_QCD_wgt_evt = 0;
    tree->SetBranchAddress("QCD_wgt_evt",&QCD_wgt_evt,&b_QCD_wgt_evt);
    /////
    //   Loop over events
    /////
    //Object selection
    double evt_obj_sel = 0.;
    double evt_n = 0.;
    double evt_err=0;
    //All entries
    for(int en=0; en<tree->GetEntries(); en++){
        Long64_t tentry = tree->LoadTree(en);
        b_QCD_wgt_evt->GetEntry(tentry);
        //b_QCD_wgt_mu1->GetEntry(tentry);
        //b_QCD_wgt_mu2->GetEntry(tentry);
        //b_QCD_wgt_evt->GetEntry(tentry);
        //double QCD_wgt_evt2=(QCD_wgt_mu1/(1-QCD_wgt_mu1))*(QCD_wgt_mu2/(1-QCD_wgt_mu2));
        evt_wgt=1.;
        //cout<<"evt_wgt prima "<<evt_wgt<<endl;
        if(rootplas[r]!="data_ele" && rootplas[r]!="data_mu"){
                b_lepsf_evt->GetEntry(tentry);
                b_PileupWeight->GetEntry(tentry);
                b_lumi_wgt->GetEntry(tentry);
                if(LumiNorm){
                    //lumi_wgt2 = xsecs[r]/evtsread[r]*Luminosity;
                    if(rootplas[r]== "ST"){
                        evt_wgt = evt_wgt*Luminosity*0.000005;//lumi_wgt inseriti a mano come media pesata di ST e SaT
                        //cout << "lumi wgt ST+SaT = "<< 0.000005 << endl;
                    }
                    else{
                        evt_wgt = evt_wgt*lumi_wgt*Luminosity;
                        //cout << "lumi wgt "<<rootplas[r]<<" = "<<lumi_wgt<<endl;
                    }
                }
                if(PUcorr){
                evt_wgt = evt_wgt*PileupWeight;
                //cout << "PileupWeight "<<rootplas[r]<<" = "<<PileupWeight<<endl;
                }
                //if(GenWgtcorr){
                //double evt_genwg = 1.;
                //evt_wgt = evt_wgt*evt_genwg;
                //}
                if(eleSFcorrection){
                evt_wgt = evt_wgt*lepsf_evt;
                }
                if(QCDcorr){
                evt_wgt = evt_wgt*QCD_wgt_evt;
                cout<<"total weight (MC) "<<rootplas[r]<<" = "<<evt_wgt<<endl;
                }
        }
        else{ if(QCDcorr) evt_wgt = evt_wgt*QCD_wgt_evt; cout<<"QCD_wgt_evt DATA = "<<evt_wgt<<endl;}    
 
        /////
        //   Get values
        /////
        //cout<<"lumi_wgt="<<lumi_wgt<<endl;
        //cout<<"evt_wgt dopo "<<evt_wgt<<endl;
        evt_obj_sel += evt_wgt;
        evt_n++;
        //evt_err=sqrt(evt_n)*evt_obj_sel/evt_n; 
        //evt_obj_sel ++;
        }//End all entries
        evt_err=sqrt(evt_n)*evt_obj_sel/evt_n;
        //Save info
        //cout<<"Lumi="<<Luminosity<<endl;
        evt_obj_sels.push_back(evt_obj_sel);
        evt_errs.push_back(evt_err);
        //Print values
        //sig
        string after_sel_acceptance = "Evt_after_acceptance_selection"; 
        Evt_after_sel(rootplas,evt_obj_sels,evt_errs,after_sel_acceptance);
    }
}
/////
//   Call TFile to be read
/////
TFile* Call_TFile(string rootpla) {
    //string file_name = path+channel+selection+rootpla+".root";
    string file_name = path+rootpla+selection+".root";
    TFile* f = new TFile(file_name.c_str(),"update");
    return f;
}
/////
//   Print evt after signal selection
/////
void Evt_after_sel(vector<string> &rootplas, vector<double> &evt_sel, vector<double> &evt_errs, string after_sel){
    cout<<setiosflags(ios::fixed)<<setprecision(SETPRECISION);
    cout<<endl;
    cout<<after_sel.c_str()<<endl;
    cout<<"\\hline"<<endl;
    cout<<"Sample & Events"<<endl;
    cout<<"\\hline"<<endl;
    double evt_sel_tt = 0.;//This case is left as example for SM processes that have more samples
    double evt_sel_tt_err = 0.;
    double evt_sel_tot = 0.;
    double evt_sel_tot_err = 0.;
    int bkg_samples = 0;
    for(uint i=0; i<evt_sel.size(); i++){
        if(rootplas[i]!="data_ele" && rootplas[i]!="data_mu"){
            double evt_sig_w     = evt_sel[i];
            double evt_sig_err_w =  evt_errs[i];
            cout<<"    "<<rootplas[i]<<" & "<<evt_sig_w<<"$\\pm$"<<evt_sig_err_w<<"\\"<<endl;
            cout<<"\\hline"<<endl;
            if(rootplas[i].substr(0,1)!="L"){
                bkg_samples++;
                evt_sel_tot += evt_sig_w;
                evt_sel_tot_err += pow(evt_sig_err_w,2);
            }
        }
    }
    if(bkg_samples>0){
        cout<<" Sum bkg & "<<evt_sel_tot<<"$\\pm$"<<sqrt(evt_sel_tot_err)<<"\\"<<endl;
        cout<<"\\hline"<<endl;
    }
    for(uint i=0; i<evt_sel.size(); i++){ 
        if(rootplas[i]=="data_mu" || rootplas[i]=="data_ele"){
            cout<<" Data & "<<evt_sel[i]<<"$\\pm$"<<sqrt(evt_sel[i])<<"\\"<<endl;
            cout<<"\\hline"<<endl;
        }
    }
}
