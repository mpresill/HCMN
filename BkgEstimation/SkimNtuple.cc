/**
This Macro
1. Calls trees, fix cuts and creates ntuples with cut data  

Need to specify
0. See Declare constants
*/
/////
//   To run: root -l SkimNtuple.cc+  
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

////
//   Declare constants
/////
//Path - samples 
const string path     = "/eos/user/m/mpresill/CMS/HN_Reload/rootplized_samples_2017/TriggerUpdate_0505/"; 
//path with rootples:
//"/eos/user/v/vmariani/NTuples/HN_2016/PUweight/";
//"/eos/user/m/mpresill/CMS/HN_Reload/rootplized_samples_2017/"; 
//"/eos/user/v/vmariani/NTuples/HN_2018/PUweight/";
//QCD bkg estimation samples
//const string path = "/eos/user/m/mpresill/CMS/HN_Reload/QCD_Rootplized_samples_2016/";

const char *samples[] = {//"TT_2016","tW_2016", 
	                "DY_2017","TTtW_2017","Other_2017"
                        //,"single_ele_B_2017"
                        //"data_mu"
                         //,"data_ele_B", "data_ele_C", "data_ele_D", "data_ele_E", "data_ele_F", "data_ele_G", "data_ele_H",
                         //"data_mu_B","data_mu_C", "data_mu_D", "data_mu_E", "data_mu_F", "data_mu_G","data_mu_H"
                        //,"mumujj_L13000_M500_2016","mumujj_L13000_M1000_2016","mumujj_L13000_M2000_2016","mumujj_L13000_M5000_2016","mumujj_L13000_M8000_2016"
			//,"eejj_L13000_M500_2016","eejj_L13000_M1000_2016","eejj_L13000_M2000_2016","eejj_L13000_M5000_2016","eejj_L13000_M8000_2016" 
			};


const string specsel  = "";
//Selection
const string suffisso   = 
                          ///////muon/////////////////////
                          //"SRmu";
                          //"DYRmu";
                          //"DYRmuPlot";
                          //"DYRmuTest";
                          //"TRmu";   //CR region TTtW estimation: the second leading lepton has opposite flavor
                          //"QCDmu";   //CR region QCD estimation
			  //"NPVmu";
			  ////////ele/////////////////
                          "SRe";
                          //"DYRe";
                          //"DYRePlot";
                          //"DYReTest";
                          //"TRe"; //CR region TTtW estimation: the second leading lepton has opposite flavor
                          //"QCDe"; //CR region QCD estimation
                          //"NPVe";
const string selection  =
////////////////////////muon/////////////////////////////
//"(HLT_Mu50==1 || HLT_OldMu100 ==1 || HLT_TkMu100==1) && numOfHighptMu==2 && Muon_pt[0]>150 && Muon_pt[1]>100 && numOfVetoEle==0 && numOfBoostedJets>=1 && BoostedJet_pt[0]>190 && M_leplep>300";
//"(HLT_Mu50==1 || HLT_OldMu100 ==1 || HLT_TkMu100==1) && numOfHighptMu==2 && Muon_pt[0]>150 && Muon_pt[1]>100 && numOfVetoEle==0 && numOfBoostedJets>=1 && BoostedJet_pt[0]>190 && M_leplep>80 && M_leplep<100";
//"(HLT_Mu50==1 || HLT_OldMu100 ==1 || HLT_TkMu100==1) && numOfHighptMu==2 && Muon_pt[0]>150 && Muon_pt[1]>100 && numOfVetoEle==0 && numOfBoostedJets>=1 && BoostedJet_pt[0]>190 && M_leplep>50 && M_leplep<300";
//"(HLT_Mu50==1 || HLT_OldMu100 ==1 || HLT_TkMu100==1) && numOfHighptMu==2 && Muon_pt[0]>150 && Muon_pt[1]>100 && numOfVetoEle==0 && numOfBoostedJets>=1 && BoostedJet_pt[0]>190 && M_leplep>80 && M_leplep<300";
//"(HLT_Mu50==1 || HLT_OldMu100 ==1 || HLT_TkMu100==1) && numOfHighptMu==1 &&  Muon_pt[0]>150 && numOfHighptEle==1 && patElectron_pt[0]>100 && numOfBoostedJets>=1 && BoostedJet_pt[0]>190 && M_leplep>400";
//"(HLT_Mu50==1 || HLT_OldMu100 ==1 || HLT_TkMu100==1) && numOfVetoEle==0 && numOfFakeMu==2 && Muon_pt[0]>150 && Muon_pt[1]>100 && numOfBoostedJets>=1 && BoostedJet_pt[0]>190 && M_mu1mu2>300";
//"(HLT_Mu50==1 || HLT_OldMu100 ==1 || HLT_TkMu100==1) && numOfHighptMu==2 &&  Muon_pt[0]>50 && Muon_pt[1]>30 && numOfVetoEle==0 ";
////////////////////ele////////////////////////////////////
"(HLT_Photon200==1 || HLT_Ele35_WPTight_Gsf==1 ) && numOfHighptEle==2 && patElectron_pt[0]>150 && patElectron_pt[1]>100 && numOfLooseMu==0 && numOfBoostedJets>=1 && BoostedJet_pt[0]>190 && M_leplep>300";
//"HLT_Ele115_CaloIdVT_GsfTrkIdT==1 && numOfHighptEle==2 && patElectron_pt[0]>150 && patElectron_pt[1]>100 && numOfLooseMu==0 && numOfBoostedJets>=1 && BoostedJet_pt[0]>190 && M_leplep>80 && M_leplep<100";
//"HLT_Ele115_CaloIdVT_GsfTrkIdT==1 && numOfHighptEle==2 && patElectron_pt[0]>150 && patElectron_pt[1]>100 && numOfLooseMu==0 && numOfBoostedJets>=1 && BoostedJet_pt[0]>190 && M_leplep>50 && M_leplep<300";
//"HLT_Ele115_CaloIdVT_GsfTrkIdT==1 && numOfHighptEle==2 && patElectron_pt[0]>150 && patElectron_pt[1]>100 && numOfLooseMu==0 && numOfBoostedJets>=1 && BoostedJet_pt[0]>190 && M_leplep>80 && M_leplep<300";
//"(HLT_Photon200==1 || HLT_Ele35_WPTight_Gsf==1 ) && numOfHighptEle==1 && patElectron_pt[0]>150 && numOfHighptMu==1 &&  Muon_pt[0]>100 && numOfBoostedJets>=1 && BoostedJet_pt[0]>190 && M_leplep>300";
//"(HLT_Photon200==1 || HLT_Ele35_WPTight_Gsf==1 ) && numOfLooseMu==0 && numOfFakeEle==2 && patElectron_pt[0]>150 && patElectron_pt[1]>100 && numOfBoostedJets>=1 && BoostedJet_pt[0]>190 && M_leplep>300";
//"HLT_Ele115_CaloIdVT_GsfTrkIdT==1 && numOfLooseMu==0 &&  numOfFakeEle==2  && patElectron_pt[0]>150 && patElectron_pt[1]>100 && numOfBoostedJets>=1 && BoostedJet_pt[0]>190 && M_ele1ele2>300";
//"(HLT_Photon200==1 || HLT_Ele35_WPTight_Gsf==1 ) && numOfLooseMu==0 &&  numOfFakeEle==2  && patElectron_pt[0]>50 && patElectron_pt[1]>30";
const string dotroot  = ".root"; 
/////
//   Declare functions 
/////
TFile* Call_TFile(string rootpla);
/////
//   Main function
/////
void SkimNtuple(){
 //For all the samples
 vector<string> rootplas(samples, samples + sizeof(samples)/sizeof(samples[0]));
 double EffCum[15]={0};
 double num_EffCum[15]={0};
 double den_EffCum[15]={0};
 for(uint i=0; i<rootplas.size(); i++){
  //Call old ntupla
  TFile* f = Call_TFile(rootplas[i]); TTree* tree; f->GetObject("BOOM",tree);
  den_EffCum[i]=tree->GetEntries();
  cout<<"#tot events  "<< den_EffCum[i] <<"\n";
  //Create new ntupla
  string newfil  = specsel+rootplas[i]+"_"+suffisso+dotroot; 
  TFile *newfile = new TFile(newfil.c_str(),"recreate");
  newfile->cd();
  //Do cut
  string varCut  = selection;
  TTree* newtree = tree->CopyTree(varCut.c_str());
  //Save
  num_EffCum[i]=newtree->GetEntries();
  cout<<"#events SR "<< num_EffCum[i] <<"\n";
  EffCum[i]=num_EffCum[i]/den_EffCum[i];
  cout << "Number of selected events of sample "<< rootplas[i] <<"' =  "<<num_EffCum[i]<<"\n";
  cout << "cumulative eff of sample "<< rootplas[i] <<"' =  "<<EffCum[i]<<"\n";
  newtree->Write(); 
  newfile->Write();
  newfile->Close();
 }
 
}
/////
//   Call TFile to be read
/////
TFile* Call_TFile(string rootpla){
 string file_name = path+specsel+rootpla+dotroot;
 TFile* f = new TFile(file_name.c_str(),"read");
 return f;
}
