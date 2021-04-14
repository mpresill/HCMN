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
const string path           = "/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2018_fixMuon/"; 
//const string path           = "/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2018_v4/"; 
                              
const char *samples[]       = {
                              "SR_syst_TTtW","SR_syst_Other","SR_syst_DY_HTincl_Kewkqcd",
                              //"DY",
                             "CR_DY_data_ele"                  /////STEP1: change DATA channel (uncommenting the right one)
                              //"CR_DY_data_mu"
};
const string selection      = "_2018";                   ////STEP 2: change year 


                  /////STEP 3: change channel (uncommenting the right one)
TString VarName_data="M_eeJ_Z";                          

TString VarName_dy="DY_Zpeak_eejj";
TString VarName_other="Other_Zpeak_eejj";
TString VarName_top="TTtW_Zpeak_eejj";


const string channel        = "";
/////
//   Declare functions 
/////
TFile* Call_TFile(string rootpla);
void Evt_after_sel(vector<string> &rootplas, vector<double> &evt_sel, vector<double> &evt_errs, string after_sel); 
/////
//   Main function
/////
void AlphaRatioBinned(){
    double EvData=0; 
    double ErrData2=0;
    double EvOther=0;
    double ErrOther2=0;
    double EvTTtW=0;
    double ErrTTtW2=0; 
    double EvDY=0;
    double ErrDY2=0;

//Run over M ell ell J variable bins

for(int i=1; i<10; i++){


   //Run over all samples 
   vector<string> rootplas(samples, samples + sizeof(samples)/sizeof(samples[0]));
   for(uint r=0; r<rootplas.size(); r++){
      //Call files  
      TFile* f = Call_TFile(rootplas[r]); 
      TString histo_name;
      if(rootplas[r]=="CR_DY_data_ele" || rootplas[r]=="CR_DY_data_mu"){      histo_name = VarName_data;}
      if(rootplas[r]=="SR_syst_Other"){      histo_name = VarName_other;}
      if(rootplas[r]=="SR_syst_DY_HTincl_Kewkqcd"){      histo_name = VarName_dy;}
      if(rootplas[r]=="SR_syst_TTtW"){      histo_name = VarName_top;}

      //Fill histo to be read
      TH1F *hist2; hist2= (TH1F*) f->Get(histo_name); TH1F *hist=(TH1F*) hist2->Clone();
      

      /////
      // stat error for bins in the integral
      ////
      int nbin = hist->GetNbinsX();
      double Events = hist-> GetBinContent(i);  //Integral();
      //cout<<"rootpla="<<rootplas[r]<<"\n";
      //cout<<"nbins="<<nbin<<"\n";
      //cout<<"n events="<<Events<<"\n";   
      double ErrEvents=hist->GetBinError(i);      

      //////
      // save local variables to compute the alpha ratio
      //////
      if(rootplas[r]=="CR_DY_data_ele" || rootplas[r]=="CR_DY_data_mu"){EvData=Events; ErrData2=ErrEvents*ErrEvents; }
      if(rootplas[r]=="SR_syst_Other"){EvOther=Events; ErrOther2=ErrEvents*ErrEvents;}
      if(rootplas[r]=="SR_syst_TTtW"){EvTTtW=Events; ErrTTtW2=ErrEvents*ErrEvents;}
      if(rootplas[r]=="SR_syst_DY_HTincl_Kewkqcd"){EvDY=Events; ErrDY2=ErrEvents*ErrEvents;}
   }


   /////
   // compute the alpha ratio
   ////
   double D=EvData-EvOther-EvTTtW;

   double AlphaR_NoSubtractionOther=(EvData )/EvDY; //-EvOther-EvTTtW
   double AlphaR=(EvData -EvOther-EvTTtW)/EvDY; 
   
   double errD=pow((ErrData2+ErrTTtW2+ErrOther2),0.5);
   double errR=AlphaR*pow(pow((errD/D),2)+pow((pow(ErrDY2,0.5)/EvDY),2),0.5);
   
  // cout<< "========================"<<endl;   
  // cout<< selection << " BIN " << i << "\n";
  // cout<<"dy evts = "<<EvDY<<"\n";
  // cout<<"nonDYmc evts = "<<EvOther+EvTTtW<<"\n";
  // cout<<"data evts = "<<EvData<<"\n";

//   cout<<selection<<" AlphaR SENZA SOTTRRARRE OTHER E TOP = "<< AlphaR_NoSubtractionOther<<"+-"<<errR<<"\n";

//   cout<<selection<<" AlphaR = "<<AlphaR<<"+-"<<errR<<"\n";

   cout<<AlphaR << " +- "<< errR <<"\n";
   
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
