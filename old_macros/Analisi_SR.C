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

using namespace std;

//void filename_()
void Analisi_SR(){

TChain *a_ = new TChain("BOOM");

a_->Add("~/cernbox/HN_2016/Other_2016.root");
//inputFile

int HLT_Ele, HLT_Mu, HLT_Mu50, HLT_OldMu100, HLT_TkMu50, HLT_TkMu100;
double muejj_l, emujj_l;
double M_leplep;
std:vector<double>* patElectron_pt; patElectron_pt=0;
vector<double>* patElectron_eta; patElectron_eta=0;
vector<double>* patElectron_phi; patElectron_phi=0;
vector<double>* patElectron_energy; patElectron_energy=0;
vector<double>* Muon_pt; Muon_pt=0;
vector<double>* Muon_eta; Muon_eta=0;
vector<double>* Muon_phi; Muon_phi=0;
vector<double>* Muon_energy; Muon_energy=0;
vector<double>*BoostedJet_pt; BoostedJet_pt=0;
vector<double>*BoostedJet_eta; BoostedJet_eta=0;
vector<double>*BoostedJet_phi; BoostedJet_phi=0;
vector<double>*BoostedJet_energy; BoostedJet_energy=0;
double numOfHighptEle, numOfVetoEle, numOfHighptMu, numOfLooseMu, numOfBoostedJets;
double lepsf_evt, lumi_wgt;

TBranch *a_HLT_Ele115_CaloIdVT_GsfTrkIdT=a_->GetBranch("HLT_Ele115_CaloIdVT_GsfTrkIdT");
TBranch *a_HLT_Mu50=a_->GetBranch("HLT_Mu50");
TBranch *a_HLT_OldMu100=a_->GetBranch("HLT_OldMu100");
TBranch *a_HLT_TkMu50=a_->GetBranch("HLT_TkMu50");
TBranch *a_HLT_TkMu100=a_->GetBranch("HLT_TkMu100");

TBranch *a_patElectron_pt=a_->GetBranch("patElectron_pt");
TBranch *a_patElectron_eta=a_->GetBranch("patElectron_eta");
TBranch *a_patElectron_phi=a_->GetBranch("patElectron_phi");
TBranch *a_patElectron_energy=a_->GetBranch("patElectron_energy");

TBranch *a_Muon_pt=a_->GetBranch("Muon_pt");
TBranch *a_Muon_eta=a_->GetBranch("Muon_eta");
TBranch *a_Muon_phi=a_->GetBranch("Muon_phi");
TBranch *a_Muon_energy=a_->GetBranch("Muon_energy");

TBranch *a_BoostedJet_pt=a_->GetBranch("BoostedJet_pt");
TBranch *a_BoostedJet_eta=a_->GetBranch("BoostedJet_eta");
TBranch *a_BoostedJet_phi=a_->GetBranch("BoostedJet_phi");
TBranch *a_BoostedJet_energy=a_->GetBranch("BoostedJet_energy");

TBranch *a_M_leplep=a_->GetBranch("M_leplep");
TBranch *a_lepsf_evt=a_->GetBranch("lepsf_evt");
TBranch *a_lumi_wgt=a_->GetBranch("lumi_wgt");

TBranch *a_muejj_l=a_->GetBranch("muejj_l");
TBranch *a_emujj_l=a_->GetBranch("emujj_l");

TBranch *a_numOfHighptEle=a_->GetBranch("numOfHighptEle");
TBranch *a_numOfHighptMu=a_->GetBranch("numOfHighptMu");
TBranch *a_numOfLooseMu=a_->GetBranch("numOfLooseMu");
TBranch *a_numOfBoostedJets=a_->GetBranch("numOfBoostedJets");
TBranch *a_numOfVetoEle=a_->GetBranch("numOfVetoEle");

a_HLT_Ele115_CaloIdVT_GsfTrkIdT->SetAddress(&HLT_Ele);
a_HLT_Mu50->SetAddress(&HLT_Mu50);
a_HLT_OldMu100->SetAddress(&HLT_OldMu100);
a_HLT_TkMu50->SetAddress(&HLT_TkMu50);
a_HLT_TkMu100->SetAddress(&HLT_TkMu100);

a_patElectron_pt->SetAddress(&patElectron_pt);
a_patElectron_eta->SetAddress(&patElectron_eta);
a_patElectron_phi->SetAddress(&patElectron_phi);
a_patElectron_energy->SetAddress(&patElectron_energy);

a_Muon_pt->SetAddress(&Muon_pt);
a_Muon_eta->SetAddress(&Muon_eta);
a_Muon_phi->SetAddress(&Muon_phi);
a_Muon_energy->SetAddress(&Muon_energy);

a_M_leplep->SetAddress(&M_leplep);
a_lepsf_evt->SetAddress(&lepsf_evt);
a_lumi_wgt->SetAddress(&lumi_wgt);

a_BoostedJet_pt->SetAddress(&BoostedJet_pt);
a_BoostedJet_eta->SetAddress(&BoostedJet_eta);
a_BoostedJet_phi->SetAddress(&BoostedJet_phi);
a_BoostedJet_energy->SetAddress(&BoostedJet_energy);

a_muejj_l->SetAddress(&muejj_l);
a_emujj_l->SetAddress(&emujj_l);

a_numOfHighptEle->SetAddress(&numOfHighptEle);
a_numOfHighptMu->SetAddress(&numOfHighptMu);
a_numOfLooseMu->SetAddress(&numOfLooseMu);
a_numOfBoostedJets->SetAddress(&numOfBoostedJets);
a_numOfVetoEle->SetAddress(&numOfVetoEle);

TH1D *El1_pt = new TH1D ("El1_pt", "El1_pt", 200, 0, 5000);
TH1D *Mu1_pt = new TH1D ("Mu1_pt", "Mu1_pt", 200, 0, 5000);
TH1D *El1_phi = new TH1D ("El1_phi", "El1_phi", 200, -3, 3);
TH1D *Mu1_phi = new TH1D ("Mu1_phi", "Mu1_phi", 200, -3, 3);
TH1D *El1_eta = new TH1D ("El1_eta", "El1_eta", 200, -4, 4);
TH1D *Mu1_eta = new TH1D ("Mu1_eta", "Mu1_eta", 200, -4, 4);

TH1D *El2_pt = new TH1D ("El2_pt", "El2_pt", 200, 0, 5000);
TH1D *Mu2_pt = new TH1D ("Mu2_pt", "Mu2_pt", 200, 0, 5000);
TH1D *El2_phi = new TH1D ("El2_phi", "El2_phi", 200, -3, 3);
TH1D *Mu2_phi = new TH1D ("Mu2_phi", "Mu2_phi", 200, -3, 3);
TH1D *El2_eta = new TH1D ("El2_eta", "El2_eta", 200, -4, 4);
TH1D *Mu2_eta = new TH1D ("Mu2_eta", "Mu2_eta", 200, -4, 4);

TH1D *M_ll = new TH1D ("M_ll", "M_ll", 500, 0, 8000);
TH1D *M_llBoostJ = new TH1D ("M_llBoostJ", "M_llBoostJ", 500, 0, 8000);
TH1D *Jet_pt = new TH1D ("Jet_pt", "Jet_pt", 200, 0, 5000);
TH1D *Jet_phi = new TH1D ("Jet_phi", "Jet_phi", 200, -3, 3);
TH1D *Jet_eta = new TH1D ("Jet_eta", "Jet_eta", 200, -4, 4);

TLorentzVector Muon1;
TLorentzVector Muon2;

TLorentzVector Electron1;
TLorentzVector Electron2;

TLorentzVector BoostJet;


cout << a_->GetEntries() << endl;
int tot=0, muejj = 0;
double wg = 0;
int lumi = 35542;//2018: 58873 //2017: 41529 //2016: 35542


for (Int_t i=0;i<a_->GetEntries();i++) {
 a_->GetEntry(i);
 tot = a_->GetEntries();
 if (i%100000 == 0) cout << i << " eventi analizzati su " << tot << endl;
///////////////////////////////////////
//muon channel analysis: New Selection

if (Muon_pt->size() > 1 && BoostedJet_pt->size() > 0){
  if (HLT_Mu50==1 && Muon_pt->at(0) > 53 && Muon_pt->at(1) > 35 && fabs(Muon_eta->at(0))<2.4 && fabs(Muon_eta->at(1))<2.4 && numOfHighptMu==2 
   && M_leplep>300 && BoostedJet_pt->at(0) > 190 && numOfBoostedJets>=1){

   Muon1.SetPtEtaPhiE(Muon_pt->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0)); 
   Muon2.SetPtEtaPhiE(Muon_pt->at(1), Muon_eta->at(1), Muon_phi->at(1),Muon_energy->at(1)); 
   BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0), BoostedJet_energy->at(0)); 
   wg = lumi*lumi_wgt*lepsf_evt;

   Mu1_pt->Fill(Muon_pt->at(0),wg);
   Mu1_eta->Fill(Muon_eta->at(0),wg);
   Mu1_phi->Fill(Muon_phi->at(0),wg);
   Mu2_pt->Fill(Muon_pt->at(1),wg);
   Mu2_eta->Fill(Muon_eta->at(1),wg);
   Mu2_phi->Fill(Muon_phi->at(1),wg);
   M_ll->Fill((Muon1+Muon2).M(),wg);
   M_llBoostJ->Fill((Muon1+Muon2+BoostJet).M(),wg);
   Jet_pt->Fill(BoostedJet_pt->at(0),wg);
   Jet_eta->Fill(BoostedJet_eta->at(0),wg);
   Jet_phi->Fill(BoostedJet_phi->at(0),wg);
  }
 }
}

TFile *f = new TFile("test_plots/SR_Other_2016_HLTMu50-OLD-SIGNAL-REGION.root", "RECREATE");

Mu1_pt->Write();
Mu2_pt->Write();
Mu1_eta->Write();
Mu2_eta->Write();
Mu1_phi->Write();
Mu2_phi->Write();
M_ll->Write();
M_llBoostJ->Write();
Jet_pt->Write();
Jet_eta->Write();
Jet_phi->Write();

std::cout << "Total number of events is " << tot <<std::endl;
std::cout << "Number of selected events: the integral of M_llBoostJ is " << (M_llBoostJ->Integral())/wg <<std::endl;
std::cout << "(electron channel) efficiency is  " << ((M_llBoostJ->Integral())/wg)/tot  <<std::endl;


f->Write();
f->Close();


/////////////////////////
////////electron channel analysis
/*
for (Int_t i=0;i<a_->GetEntries();i++) {
 a_->GetEntry(i);
 tot = a_->GetEntries();
if (i%100000 == 0) cout << i << " eventi analizzati su " << tot << endl;
if (patElectron_pt->size() > 1 && BoostedJet_pt->size() > 0){
  if ( HLT_Ele == 1 && patElectron_pt->at(0) > 250 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(0))<2.4 && fabs(patElectron_eta->at(1))<2.4 && numOfHighptEle==2 
   && M_leplep>500 && BoostedJet_pt->at(0) > 190 && numOfBoostedJets>=1){

   Electron1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   Electron2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energy->at(1));
   BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0), BoostedJet_energy->at(0)); 
   wg = lumi*lumi_wgt*lepsf_evt;

   El1_pt->Fill(patElectron_pt->at(0),wg);
   El1_eta->Fill(patElectron_eta->at(0),wg);
   El1_phi->Fill(patElectron_phi->at(0),wg);
   El2_pt->Fill(patElectron_pt->at(1),wg);
   El2_eta->Fill(patElectron_eta->at(1),wg);
   El2_phi->Fill(patElectron_phi->at(1),wg);
   M_ll->Fill((Electron1+Electron2).M(),wg);
   M_llBoostJ->Fill((Electron1+Electron2+BoostJet).M(),wg);
   Jet_pt->Fill(BoostedJet_pt->at(0),wg);
   Jet_eta->Fill(BoostedJet_eta->at(0),wg);
   Jet_phi->Fill(BoostedJet_phi->at(0),wg);
  }
 }
}

TFile *f2 = new TFile("test_plots/SR_eejjL13M8000_2016_HLT_Ele.root", "RECREATE");

El1_pt->Write();
El2_pt->Write();
El1_eta->Write();
El2_eta->Write();
El1_phi->Write();
El2_phi->Write();
M_ll->Write();
M_llBoostJ->Write();
Jet_pt->Write();
Jet_eta->Write();
Jet_phi->Write();

std::cout << "Total number of events is " << tot <<std::endl;
std::cout << "Number of selected events: the integral of M_llBoostJ is " << (M_llBoostJ->Integral())/wg <<std::endl;
std::cout << "(muon channel) efficiency is  " << ((M_llBoostJ->Integral())/wg)/tot  <<std::endl;


f2->Write();
f2->Close();
*/

}
 
