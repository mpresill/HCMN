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
void Analisi_CR_DY_MC_2018(){

TChain *a_ = new TChain("BOOM");

a_->Add("/eos/user/v/vmariani/NTuples/HN_2018/PUweight/TTtW_2018.root");
//inputFile

int HLT_Ele, HLT_Mu, HLT_Mu50, HLT_OldMu100, HLT_TkMu50, HLT_TkMu100;
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


//PU projection June
double puweight[100]={9686.56 , 13.2731 , 43.7711 , 18.688 , 12.5107 , 9.04181 , 6.57902 , 4.87346 , 3.62872 , 2.76274 , 2.22425 , 1.89967 , 1.7017 , 1.57883 , 1.50431 , 1.46451 , 1.44978 , 1.45098 , 1.4587 , 1.46369 , 1.45805 , 1.43709 , 1.40078 , 1.3533 , 1.30105 , 1.25009 , 1.20467 , 1.16697 , 1.13742 , 1.11537 , 1.0996 , 1.08877 , 1.0816 , 1.07683 , 1.07316 , 1.06908 , 1.06281 , 1.05246 , 1.03612 , 1.01213 , 0.979351 , 0.937295 , 0.886238 , 0.827196 , 0.761841 , 0.692342 , 0.6211 , 0.550495 , 0.482672 , 0.419357 , 0.361756 , 0.310542 , 0.265899 , 0.22761 , 0.195168 , 0.167896 , 0.145046 , 0.125873 , 0.109692 , 0.0959027 , 0.0840082 , 0.0736144 , 0.0644249 , 0.0562295 , 0.048887 , 0.0423067 , 0.03643 , 0.031215 , 0.0266245 , 0.0226187 , 0.0191526 , 0.0161753 , 0.0136325 , 0.0114695 , 0.00963313 , 0.00807454 , 0.00675025 , 0.00562281 , 0.00466074 , 0.00383815 , 0.00313397 , 0.00253121 , 0.0020162 , 0.00157798 , 0.00120787 , 0.000899112 , 0.000646511 , 0.000445842 , 0.000292888 , 0.000182388 , 0.000109393 , 6.25794e-05 , 3.42779e-05 , 1.80716e-05 , 9.22117e-06 , 4.57764e-06 , 2.22112e-06 , 1.05773e-06 , 4.96423e-07 , 2.30808e-07};

TBranch *a_HLT_Ele115_CaloIdVT_GsfTrkIdT=a_->GetBranch("HLT_Ele115_CaloIdVT_GsfTrkIdT");
TBranch *a_HLT_Mu50=a_->GetBranch("HLT_Mu50");
TBranch *a_HLT_OldMu100=a_->GetBranch("HLT_OldMu100");
TBranch *a_HLT_TkMu50=a_->GetBranch("HLT_TkMu50");
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
a_HLT_OldMu100->SetAddress(&HLT_OldMu100);
a_HLT_TkMu50->SetAddress(&HLT_TkMu50);
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

a_muejj_l->SetAddress(&muejj_l);
a_emujj_l->SetAddress(&emujj_l);

a_nBestVtx->SetAddress(&nBestVtx);
a_trueInteractions->SetAddress(&trueInteractions);
a_PUWeight->SetAddress(&PUWeight);

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
double wg = 0;
int lumi = 58872; //2017: 41529 //2016: 35920
bool veto_ele = false;
double mee = 0, mmumu = 0, pu_w = 0;

for (Int_t i=0;i<a_->GetEntries();i++) {//a_->GetEntries()
 a_->GetEntry(i);
 tot = a_->GetEntries();
 if (i%100000 == 0) cout << i << " eventi analizzati su " << tot << endl;

 n_best_Vtx_bef->Fill(trueInteractions);

 HLT_Mu = 0;
 if (HLT_Mu50==1 || HLT_TkMu100==1 || HLT_OldMu100==1 ) HLT_Mu = 1;
 for (int j=0; j<100; j++){
  if (trueInteractions > j && trueInteractions <= j+1){
   pu_w = puweight[j];
  break;
  }
 }
 if (Muon_pt->size() > 1 && numOfHighptMu==2 && numOfVetoEle == 0 && numOfBoostedJets>=1){
  if (HLT_Mu == 1 && Muon_pt->at(0) > 150 && Muon_pt->at(1) > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(Muon_eta->at(1))<2.4 && BoostedJet_pt->at(0) > 190 ){

   Muon1.SetPtEtaPhiE(Muon_pt->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));
   Muon2.SetPtEtaPhiE(Muon_pt->at(1), Muon_eta->at(1), Muon_phi->at(1),Muon_energy->at(1));
   BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));

   wg = lumi*lumi_wgt*lepsf_evt;
   mmumu= (Muon1+Muon2).M();
  // k = 1.067 - 0.000112*mmumu + 3.176*exp(1) - 8*pow(mmumu,2) - 4.068*exp(1) - 12*pow(mmumu,3);
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
  if (HLT_Ele==1 && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190){

   Electron1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0)); 
   Electron2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energy->at(1));

    wg = lumi*lumi_wgt*lepsf_evt;
    mee = (Electron1+Electron2).M();
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

TFile *f = new TFile("plots/CR_DY_TTtW_2018.root", "RECREATE");

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
 
