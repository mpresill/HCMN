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
#include <math.h>

using namespace std;

//void filename_()
void Analisi_CR_DY_MCDY_2016(){

TChain *a_ = new TChain("BOOM");

a_->Add("/eos/user/v/vmariani/NTuples/HN_2016/Syst_ALL_newMuonSF/DY_2016.root");
//inputFile

int HLT_Ele, HLT_Mu, HLT_Mu50, HLT_TkMu50, HLT_OldMu100, HLT_TkMu100;
double muejj_l, emujj_l;
double M_leplep;
std:vector<double>* patElectron_pt; patElectron_pt=0;
vector<double>* patElectron_eta; patElectron_eta=0;
vector<double>* patElectron_phi; patElectron_phi=0;
vector<double>* patElectron_energy; patElectron_energy=0;
vector<int>* patElectron_charge; patElectron_charge=0;
vector<double>* Muon_pt; Muon_pt=0;
vector<double>* Muon_eta; Muon_eta=0;
vector<double>* Muon_phi; Muon_phi=0;
vector<double>* Muon_energy; Muon_energy=0;
vector<double>* Muon_charge; Muon_charge=0;
vector<double>*BoostedJet_pt; BoostedJet_pt=0;
vector<double>*BoostedJet_eta; BoostedJet_eta=0;
vector<double>*BoostedJet_phi; BoostedJet_phi=0;
vector<double>*BoostedJet_energy; BoostedJet_energy=0;
double numOfHighptEle, numOfVetoEle, numOfHighptMu, numOfLooseMu, numOfBoostedJets;
double lepsf_evt, lumi_wgt, trueInteractions, PUWeight;
int nBestVtx;

double puw[100]={0.366077 , 0.893925 , 1.19772 , 0.962699 , 1.12098 , 1.16486 , 0.795599 , 0.495824 , 0.742182 , 0.878856 , 0.964232 , 1.0725 , 1.12534 , 1.17603 , 1.20208 , 1.20764 , 1.20018 , 1.18268 , 1.144 , 1.09663 , 1.0656 , 1.05117 , 1.0516 , 1.05063 , 1.04986 , 1.05817 , 1.07216 , 1.08303 , 1.09569 , 1.10787 , 1.09462 , 1.08262 , 1.04125 , 0.985752 , 0.910807 , 0.820922 , 0.716787 , 0.610013 , 0.503118 , 0.404841 , 0.309195 , 0.22792 , 0.16369 , 0.11318 , 0.0773005 , 0.0509221 , 0.0318936 , 0.0200936 , 0.0122631 , 0.00742646 , 0.00438028 , 0.00260777 , 0.00156599 , 0.000971358 , 0.000729206 , 0.000672709 , 0.000730459 , 0.000948791 , 0.00135533 , 0.00189419 , 0.00308244 , 0.00409665 , 0.00487449 , 0.00525606 , 0.00578498 , 0.00551468 , 0.00500046 , 0.00440983 , 0.00401224 , 0.00354754 , 0.00310751 , 0.00270211 , 0.00233691 , 0.00202529 , 0.00172328 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0};


TBranch *a_HLT_Ele115_CaloIdVT_GsfTrkIdT=a_->GetBranch("HLT_Ele115_CaloIdVT_GsfTrkIdT");
TBranch *a_HLT_Mu50=a_->GetBranch("HLT_Mu50");
TBranch *a_HLT_TkMu50=a_->GetBranch("HLT_TkMu50");
TBranch *a_HLT_OldMu100=a_->GetBranch("HLT_OldMu100");
TBranch *a_HLT_TkMu100=a_->GetBranch("HLT_TkMu100");

TBranch *a_patElectron_pt=a_->GetBranch("patElectron_pt");
TBranch *a_patElectron_eta=a_->GetBranch("patElectron_eta");
TBranch *a_patElectron_phi=a_->GetBranch("patElectron_phi");
TBranch *a_patElectron_energy=a_->GetBranch("patElectron_energy");
TBranch *a_patElectron_charge=a_->GetBranch("patElectron_charge");

TBranch *a_Muon_pt=a_->GetBranch("Muon_pt");
TBranch *a_Muon_eta=a_->GetBranch("Muon_eta");
TBranch *a_Muon_phi=a_->GetBranch("Muon_phi");
TBranch *a_Muon_energy=a_->GetBranch("Muon_energy");
TBranch *a_Muon_charge=a_->GetBranch("Muon_charge");

TBranch *a_BoostedJet_pt=a_->GetBranch("BoostedJet_pt");
TBranch *a_BoostedJet_eta=a_->GetBranch("BoostedJet_eta");
TBranch *a_BoostedJet_phi=a_->GetBranch("BoostedJet_phi");
TBranch *a_BoostedJet_energy=a_->GetBranch("BoostedJet_energy");

TBranch *a_M_leplep=a_->GetBranch("M_leplep");
TBranch *a_lepsf_evt=a_->GetBranch("lepsf_evt");
TBranch *a_lumi_wgt=a_->GetBranch("lumi_wgt");

TBranch *a_nBestVtx=a_->GetBranch("nBestVtx");
TBranch *a_trueInteractions=a_->GetBranch("trueInteractions");
TBranch *a_PUWeight=a_->GetBranch("PUWeight");

TBranch *a_muejj_l=a_->GetBranch("muejj_l");
TBranch *a_emujj_l=a_->GetBranch("emujj_l");

TBranch *a_numOfHighptEle=a_->GetBranch("numOfHighptEle");
TBranch *a_numOfHighptMu=a_->GetBranch("numOfHighptMu");
TBranch *a_numOfLooseMu=a_->GetBranch("numOfLooseMu");
TBranch *a_numOfBoostedJets=a_->GetBranch("numOfBoostedJets");
TBranch *a_numOfVetoEle=a_->GetBranch("numOfVetoEle");

a_HLT_Ele115_CaloIdVT_GsfTrkIdT->SetAddress(&HLT_Ele);
a_HLT_Mu50->SetAddress(&HLT_Mu50);
a_HLT_TkMu50->SetAddress(&HLT_TkMu50);
a_HLT_OldMu100->SetAddress(&HLT_OldMu100);
a_HLT_TkMu100->SetAddress(&HLT_TkMu100);

a_patElectron_pt->SetAddress(&patElectron_pt);
a_patElectron_eta->SetAddress(&patElectron_eta);
a_patElectron_phi->SetAddress(&patElectron_phi);
a_patElectron_energy->SetAddress(&patElectron_energy);
a_patElectron_charge->SetAddress(&patElectron_charge);

a_Muon_pt->SetAddress(&Muon_pt);
a_Muon_eta->SetAddress(&Muon_eta);
a_Muon_phi->SetAddress(&Muon_phi);
a_Muon_energy->SetAddress(&Muon_energy);
a_Muon_charge->SetAddress(&Muon_charge);

a_M_leplep->SetAddress(&M_leplep);
a_lepsf_evt->SetAddress(&lepsf_evt);
a_lumi_wgt->SetAddress(&lumi_wgt);

a_BoostedJet_pt->SetAddress(&BoostedJet_pt);
a_BoostedJet_eta->SetAddress(&BoostedJet_eta);
a_BoostedJet_phi->SetAddress(&BoostedJet_phi);
a_BoostedJet_energy->SetAddress(&BoostedJet_energy);

a_nBestVtx->SetAddress(&nBestVtx);
a_trueInteractions->SetAddress(&trueInteractions);
a_PUWeight->SetAddress(&PUWeight);

a_muejj_l->SetAddress(&muejj_l);
a_emujj_l->SetAddress(&emujj_l);

a_numOfHighptEle->SetAddress(&numOfHighptEle);
a_numOfHighptMu->SetAddress(&numOfHighptMu);
a_numOfLooseMu->SetAddress(&numOfLooseMu);
a_numOfBoostedJets->SetAddress(&numOfBoostedJets);
a_numOfVetoEle->SetAddress(&numOfVetoEle);

const double asymbins[10] = {0, 100, 200, 300, 500, 700, 1000, 1500, 3000, 5000};

TH1D *n_best_Vtx_bef = new TH1D ("n_best_Vtx_bef", "n_best_Vtx_bef", 100,0, 100);
TH1D *n_best_Vtx = new TH1D ("n_best_Vtx", "n_best_Vtx", 100,0, 100);
TH1D *n_best_Vtx_w = new TH1D ("n_best_Vtx_w", "n_best_Vtx_w", 100,0, 100);
TH1D *M_mumu_100300 = new TH1D ("M_mumu_100300", "M_mumu_100300", 200, 100, 300);
TH1D *M_ee_100300 = new TH1D ("M_ee_100300", "M_ee_100300", 200, 100, 300);
TH1D *M_mumu_Z_50130 = new TH1D ("M_mumu_Z_50130", "M_mumu_Z_50130", 80, 50, 130);
TH1D *M_ee_Z_50130 = new TH1D ("M_ee_Z_50130", "M_ee_Z_50130", 80, 50, 130);
TH1D *M_mumuJ = new TH1D ("M_mumuJ", "M_mumuJ", 9, asymbins);
TH1D *pt_mumu = new TH1D ("pt_mumu", "pt_mumu", 100, 0, 1000);
TH1D *M_eeJ = new TH1D ("M_eeJ", "M_eeJ", 9, asymbins);
TH1D *pt_ee = new TH1D ("pt_ee", "pt_ee", 100, 0, 1000);
TH1D *M_mumuJ_Z = new TH1D ("M_mumuJ_Z", "M_mumuJ_Z", 9, asymbins);
TH1D *pt_mumu_Z = new TH1D ("pt_mumu_Z", "pt_mumu_Z", 100, 0, 1000);
TH1D *M_eeJ_Z = new TH1D ("M_eeJ_Z", "M_eeJ_Z", 9, asymbins);
TH1D *pt_ee_Z = new TH1D ("pt_ee_Z", "pt_ee_Z", 100, 0, 1000);
TH1D *M_mumu_Zpeak = new TH1D ("M_mumu_Zpeak", "M_mumu_Zpeak", 10, 80, 100);
TH1D *M_ee_Zpeak = new TH1D ("M_ee_Zpeak", "M_ee_Zpeak", 10, 80, 100);

TLorentzVector Muon1;
TLorentzVector Muon2;
TLorentzVector Electron1;
TLorentzVector Electron2;
TLorentzVector BoostJet;


cout << a_->GetEntries() << endl;
int tot=0, muejj = 0;
double k = 0, wg = 0;
int lumi = 35542;//2018: 58873 //2017: 41529 //2016: 35542
bool veto_ele = false;
double mee = 0, mmumu = 0, pu_w = 0;

for (Int_t i=0;i<a_->GetEntries();i++) {//a_->GetEntries()
 a_->GetEntry(i);
 tot = a_->GetEntries();
 if (i%100000 == 0) cout << i << " eventi analizzati su " << tot << endl;

 HLT_Mu = 0;

 n_best_Vtx_bef->Fill(trueInteractions);

 if (HLT_Mu50==1 || HLT_TkMu50) HLT_Mu = 1;

 for (int j=0; j<100; j++){
  if (trueInteractions > j && trueInteractions <= j+1){
   pu_w = puw[j];
  break;
  }
 }

 if (Muon_pt->size() > 1 && numOfHighptMu==2 && numOfVetoEle == 0 && numOfBoostedJets>=1){
  if (HLT_Mu == 1 && Muon_pt->at(0) > 150 && Muon_pt->at(1) > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(Muon_eta->at(1))<2.4 && BoostedJet_pt->at(0) > 190 ){
   Muon1.SetPtEtaPhiE(Muon_pt->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));
   Muon2.SetPtEtaPhiE(Muon_pt->at(1), Muon_eta->at(1), Muon_phi->at(1),Muon_energy->at(1));
   BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));

   mmumu= (Muon1+Muon2).M();
  // k = 1.067 - 0.000112*mmumu + 3.176*exp(1) - 8*pow(mmumu,2) - 4.068*exp(1) - 12*pow(mmumu,3);
   k = 1.067 - 0.000112*mmumu + 3.176e-8*pow(mmumu,2) - 4.068e-12*pow(mmumu,3);
   wg = lumi*lumi_wgt*lepsf_evt*k; 
   if(mmumu > 100 && mmumu < 300){
    M_mumu_100300->Fill(mmumu,wg*pu_w);
   }
   if(mmumu >50 && mmumu < 130){
    n_best_Vtx->Fill(nBestVtx, wg);
    n_best_Vtx_w->Fill(nBestVtx, wg*pu_w);
    M_mumu_Z_50130->Fill(mmumu,wg*pu_w);
   }

   if(mmumu >= 80 && mmumu <= 100) M_mumu_Zpeak->Fill((Muon1+Muon2).M(), wg*pu_w);
 
   if (mmumu < 300){
    M_mumuJ->Fill((Muon1+Muon2+BoostJet).M(),wg*pu_w);  
    pt_mumu->Fill(Muon1.Pt() + Muon2.Pt(), wg*pu_w);
    if (mmumu > 80 && mmumu < 100){
     M_mumuJ_Z->Fill((Muon1+Muon2+BoostJet).M(),wg*pu_w);
     pt_mumu_Z->Fill(Muon1.Pt() + Muon2.Pt(), wg*pu_w);
    }
   }
  }
 }
 if (patElectron_pt->size() > 1 && numOfHighptEle==2 && numOfLooseMu==0 && numOfBoostedJets>=1){
   if (HLT_Ele == 1 && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190){

   Electron1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   Electron2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energy->at(1));
   BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));

    mee = (Electron1+Electron2).M();
    //k = 1.067 - 0.000112*mee + 3.176*exp(1) - 8*pow(mee,2) - 4.068*exp(1) - 12*pow(mee,3);
    k = 1.067 - 0.000112*mee + 3.176e-8*pow(mee,2) - 4.068e-12*pow(mee,3);
    wg = lumi*lumi_wgt*lepsf_evt*k;
    if(mee > 100 && mee < 300){
     M_ee_100300->Fill(mee,wg*pu_w);
    }
    if(mee > 50 && mee < 130){
    M_ee_Z_50130->Fill(mee,wg*pu_w);
   } 
 
   if(mee >= 80 && mee <= 100) M_ee_Zpeak->Fill((Electron1+Electron2).M(), wg*pu_w);
   
   if (mee < 300){
    M_eeJ->Fill((Electron1+Electron2+BoostJet).M(),wg*pu_w);
    pt_ee ->Fill(Electron1.Pt() + Electron2.Pt(), wg*pu_w);
    if (mee > 80 && mee < 100){
     M_eeJ_Z->Fill((Electron1+Electron2+BoostJet).M(),wg*pu_w);
     pt_ee_Z->Fill(Electron1.Pt() + Electron2.Pt(), wg*pu_w);
    }
   }
   
  }
 } 
 
}

TFile *f = new TFile("plot/CR_DY_DY_2016.root", "RECREATE");
n_best_Vtx->Write();
n_best_Vtx_w->Write();
n_best_Vtx_bef->Write();
M_mumu_100300->Write();
M_ee_100300->Write();
M_mumu_Z_50130->Write();
M_ee_Z_50130->Write();
M_eeJ->Write();
pt_ee->Write();
M_eeJ_Z->Write();
pt_ee_Z->Write();
M_mumuJ->Write();
pt_mumu->Write();
M_mumuJ_Z->Write();
pt_mumu_Z->Write();
M_mumu_Zpeak->Write();
M_ee_Zpeak->Write();

f->Write();
f->Close();

}
 
