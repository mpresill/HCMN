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
const string path     = "/eos/user/m/mpresill/CMS/HN_Reload/rootplized_samples_2017/";
const char *samples[] = {"TT_2017","tW_2017","Other_2017","DY_2017","TTtW_2017",
                         //"data_ele_2017",
                         "data_mu_2017",
                         "mumujj_L13000_M500_2017","mumujj_L13000_M1000_2017","mumujj_L13000_M2000_2017","mumujj_L13000_M5000_2017","mumujj_L13000_M8000_2017"
                        };
const string specsel  = "";
//Selection
const string suffisso   = 
                          ///////muon/////////////////////
                          "SRmu";
                          //"DYRmu";
                          //"DYRmuPlot";
                          //"DYRmuTest";
                          //"TRmu";
                          ////////ele/////////////////
                          //"SRe";
                          //"DYRe";
                          //"DYRePlot";
                          //"DYReTest";
                          //"TRe";
                     
const string selection  =
////////////////////////muon/////////////////////////////
"HLT_Mu50==1 && numOfHighptMu==2 && Muon_pt[0]>250 && Muon_pt[1]>100 && numOfVetoEle==0 && numOfBoostedJets>=1 && BoostedJet_pt[0]>190 && M_leplep>500";
//"HLT_Mu50==1 && numOfHighptMu==2 && Muon_pt[0]>250 && Muon_pt[1]>150 && numOfVetoEle==0 && numOfBoostedJets>=1 && BoostedJet_pt[0]>300 && M_leplep>80 && M_leplep<100";
//"HLT_Mu50==1 && numOfHighptMu==2 && Muon_pt[0]>250 && Muon_pt[1]>150 && numOfVetoEle==0 && numOfBoostedJets>=1 && BoostedJet_pt[0]>300 && M_leplep>50 && M_leplep<130";
//"HLT_Mu50==1 && numOfHighptMu==2 && Muon_pt[0]>250 && Muon_pt[1]>150 && numOfVetoEle==0 && numOfBoostedJets>=1 && BoostedJet_pt[0]>300 && M_leplep>80 && M_leplep<300";
//"HLT_Mu50==1 && numOfHighptMu==1 &&  Muon_pt[0]>250 && numOfHighptEle==1 && patElectron_pt[0]>150 && numOfBoostedJets>=1 && BoostedJet_pt[0]>300 && M_leplep>700";
////////////////////ele////////////////////////////////////
//"HLT_Ele115_CaloIdVT_GsfTrkIdT==1 && numOfHighptEle==2 && patElectron_pt[0]>250 && patElectron_pt[1]>150 && numOfLooseMu==0 && numOfBoostedJets>=1 && BoostedJet_pt[0]>300 && M_leplep>700";
//"HLT_Ele115_CaloIdVT_GsfTrkIdT==1 && numOfHighptEle==2 && patElectron_pt[0]>250 && patElectron_pt[1]>150 && numOfLooseMu==0 && numOfBoostedJets>=1 && BoostedJet_pt[0]>300 && M_leplep>80 && M_leplep<100";
//"HLT_Ele115_CaloIdVT_GsfTrkIdT==1 && numOfHighptEle==2 && patElectron_pt[0]>250 && patElectron_pt[1]>150 && numOfLooseMu==0 && numOfBoostedJets>=1 && BoostedJet_pt[0]>300 && M_leplep>50 && M_leplep<130";
//"HLT_Ele115_CaloIdVT_GsfTrkIdT==1 && numOfHighptEle==2 && patElectron_pt[0]>250 && patElectron_pt[1]>150 && numOfLooseMu==0 && numOfBoostedJets>=1 && BoostedJet_pt[0]>300 && M_leplep>80 && M_leplep<300";
//"HLT_Ele115_CaloIdVT_GsfTrkIdT==1 && numOfHighptEle==1 && patElectron_pt[0]>250 && numOfHighptMu==1 &&  Muon_pt[0]>150 && numOfBoostedJets>=1 && BoostedJet_pt[0]>300 && M_leplep>700";
const string dotroot    = ".root"; 
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
 for(uint i=0; i<rootplas.size(); i++){
  //Call old ntupla
  TFile* f = Call_TFile(rootplas[i]); TTree* tree; f->GetObject("BOOM",tree);
  //Create new ntupla
  string newfil  = specsel+rootplas[i]+"_"+suffisso+dotroot; 
  TFile *newfile = new TFile(newfil.c_str(),"recreate");
  newfile->cd();
  //Do cut
  string varCut  = selection;
  TTree* newtree = tree->CopyTree(varCut.c_str());
  //Save
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
 TFile* f = new TFile(file_name.c_str(),"update");
 return f;
}
//const string selection  = "l1pvval!=-9999 && nmus==2 && neles==0 && cands_pt[0]>25 && cands_pt[1]>25";
// && cands_pt[0]>25 && cands_pt[1]>25 && mus_pt[1]==cands_pt[1]";// && cands_pt[0]>20 && cands_pt[1]>10";
// ((nmus==2 && mus_pt[0]>20 && mus_pt[1]>20) || (neles==2 && eles_pt[0]>20 && eles_pt[1]>20) || (nmus+neles==2 && mus_pt[0]>20 && meles_pt[0]>20))";
//2mu
//const string suffisso   = "2mu"; 
//const string selection  = "l1pvval!=-9999 && nmus==2 && neles==0";
//sig 2L
//const string suffisso   = "sr_2lep"; 
//const string selection  = "nLepGood==2 && LepGood_pt[0]>20 && LepGood_pt[1]>20 && LepGood_charge[0]*LepGood_charge[1] > 0 && nJet25>=4 && (nBJetLoose25 >= 2 || nBJetMedium25 >= 1)";
//const string suffisso   = "sr_3lep"; 
//const string selection  = "nLepGood==3 && LepGood_pt[0]>20 && LepGood_pt[1]>20 && LepGood_pt[2]>20 && nJet25>=4 && (nBJetLoose25 >= 2 || nBJetMedium25 >= 1)";

