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
//PROVA MODIFICA
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
void Analisi_CR_MC(){

TChain *a_ = new TChain("BOOM");

a_->Add("ST_2017.root");
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

TH1D *Ele_pt = new TH1D ("Ele_pt", "Ele_pt", 200, 0, 5000);
TH1D *Mu_pt = new TH1D ("Mu_pt", "Mu_pt", 200, 0, 5000);
TH1D *Ele_phi = new TH1D ("Ele_phi", "Ele_phi", 200, -3, 3);
TH1D *Mu_phi = new TH1D ("Mu_phi", "Mu_phi", 200, -3, 3);
TH1D *Ele_eta = new TH1D ("Ele_eta", "Ele_eta", 200, -4, 4);
TH1D *Mu_eta = new TH1D ("Mu_eta", "Mu_eta", 200, -4, 4);
TH1D *M_ll = new TH1D ("M_ll", "M_ll", 500, 0, 8000);
TH1D *M_llBoostJ = new TH1D ("M_llBoostJ", "M_llBoostJ", 500, 0, 8000);
TH1D *Jet_pt = new TH1D ("Jet_pt", "Jet_pt", 200, 0, 5000);
TH1D *Jet_phi = new TH1D ("Jet_phi", "Jet_phi", 200, -3, 3);
TH1D *Jet_eta = new TH1D ("Jet_eta", "Jet_eta", 200, -4, 4);

TLorentzVector Muon;
TLorentzVector Electron;
TLorentzVector BoostJet;


cout << a_->GetEntries() << endl;
int tot=0, muejj = 0;
double wg = 0;
int lumi = 35542;//2018: 58873 //2017: 41529 //2016: 35542

for (Int_t i=0;i<a_->GetEntries();i++) {
 a_->GetEntry(i);
 tot = a_->GetEntries();
 if (i%100000 == 0) cout << i << " eventi analizzati su " << tot << endl;

 if (HLT_Mu50==1) HLT_Mu = 1;
 if (emujj_l == 1 || muejj_l == 1) muejj = 1; 

 if (Muon_pt->size() > 0 && patElectron_pt->size() > 0 && BoostedJet_pt->size() > 0){ 
  if (HLT_Ele==1 && patElectron_pt->at(0) > 140 && Muon_pt->at(0) > 105 && fabs(patElectron_eta->at(0))<2.4 && fabs(Muon_eta->at(0))<2.4 && numOfHighptEle==1 && numOfHighptMu==1
   && M_leplep>300 && BoostedJet_pt->at(0) > 190 && numOfBoostedJets>=1){

   Muon.SetPtEtaPhiE(Muon_pt->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0)); 
   Electron.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0), BoostedJet_energy->at(0)); 
   wg = lumi*lumi_wgt*lepsf_evt;

   Ele_pt->Fill(patElectron_pt->at(0),wg);
   Ele_eta->Fill(patElectron_eta->at(0),wg);
   Ele_phi->Fill(patElectron_phi->at(0),wg);
   Mu_pt->Fill(Muon_pt->at(0),wg);
   Mu_eta->Fill(Muon_eta->at(0),wg);
   Mu_phi->Fill(Muon_phi->at(0),wg);
   M_ll->Fill((Muon+Electron).M(),wg);
   M_llBoostJ->Fill((Muon+Electron+BoostJet).M(),wg);
   Jet_pt->Fill(BoostedJet_pt->at(0),wg);
   Jet_eta->Fill(BoostedJet_eta->at(0),wg);
   Jet_phi->Fill(BoostedJet_phi->at(0),wg);
  }
 }
}

TFile *f = new TFile("test_plots/CR_TT_2017_HLTEle.root", "RECREATE");

Ele_pt->Write();
Mu_pt->Write();
Ele_eta->Write();
Mu_eta->Write();
Ele_phi->Write();
Mu_phi->Write();
M_ll->Write();
M_llBoostJ->Write();
Jet_pt->Write();
Jet_eta->Write();
Jet_phi->Write();

f->Write();
f->Close();

}
 
