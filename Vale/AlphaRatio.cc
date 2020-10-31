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
const string path           = "plots/CR_DY_"; 
                              
const char *samples[]       = {
                              "TTtW","Other","DY",
                              //"DY",
                              //"data_ele"
                              "data_mu"
};
const string selection      = "_2017";                 ////change year 
//TString VarName="M_ee_Zpeak";     
TString VarName="M_mumu_Zpeak";  
//const char *variables[]         = {"M_ee_Zpeak"};
const string channel        = "";
/////
//   Declare functions 
/////
TFile* Call_TFile(string rootpla);
void Evt_after_sel(vector<string> &rootplas, vector<double> &evt_sel, vector<double> &evt_errs, string after_sel); 
/////
//   Main function
/////
void AlphaRatio(){
    double EvData=0; 
    double ErrData2=0;
    double EvOther=0;
    double ErrOther2=0;
    double EvTTtW=0;
    double ErrTTtW2=0; 
    double EvDY=0;
    double ErrDY2=0;


 //Run over all samples 
 vector<string> rootplas(samples, samples + sizeof(samples)/sizeof(samples[0]));
 for(uint r=0; r<rootplas.size(); r++){
    //Call files  
    TFile* f = Call_TFile(rootplas[r]); 
    TString histo_name = VarName;
    //Fill histo to be read
    TH1F *hist2; hist2= (TH1F*) f->Get(histo_name); TH1F *hist=(TH1F*) hist2->Clone();
    
    /////
    // stat error for bins in the integral
    ////
    int nbin = hist->GetNbinsX();
    double Events = hist->Integral();
    //cout<<"rootpla="<<rootplas[r]<<"\n";
    //cout<<"nbins="<<nbin<<"\n";
    //cout<<"n events="<<Events<<"\n";
    double ErrEvents2=0;
    for(uint i=0; i<=nbin; i++){
       double EvtBinErr=hist->GetBinError(i);
       ErrEvents2= ErrEvents2 + EvtBinErr*EvtBinErr;
    }

    //////
    // save local variables to compute the alpha ratio
    //////
    if(rootplas[r]=="data_ele" || rootplas[r]=="data_mu"){EvData=Events; ErrData2=ErrEvents2; }
    if(rootplas[r]=="Other"){EvOther=Events; ErrOther2=ErrEvents2;}
    if(rootplas[r]=="TTtW"){EvTTtW=Events; ErrTTtW2=ErrEvents2;}
    if(rootplas[r]=="DY"){EvDY=Events; ErrDY2=ErrEvents2;}
}
/////
// compute the alpha ratio
////
double D=EvData-EvOther-EvTTtW;
double AlphaR=(EvData-EvOther-EvTTtW)/EvDY;
double errD=pow((ErrData2+ErrTTtW2+ErrOther2),0.5);
double errR=AlphaR*pow(pow((errD/D),2)+pow((pow(ErrDY2,0.5)/EvDY),2),0.5);
//cout<<"dy evts"<<EvDY<<"\n";
//cout<<"data evts"<<EvData<<"\n";
cout<<selection<<" AlphaR="<<AlphaR<<"+-"<<errR<<"\n";

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