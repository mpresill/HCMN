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
void Analisi_CR_DY_data_mu_2017_v5_Rebinned(){

TChain *a_ = new TChain("BOOM");


//if ELECTRON CHANNEL: restore electron and photon triggers
//a_->Add("/eos/user/m/mpresill/CMS/HN_Reload/rootplized_samples_2017/TriggerUpdate_0505/data_mu_2017.root");
a_->Add("/eos/user/v/vmariani/NTuples/HN_2017/25062021/data_mu_2017.root");
//inputFile

int HLT_Ele, HLT_Mu, HLT_Mu50, HLT_OldMu100, HLT_TkMu50, HLT_TkMu100, HLT_Photon200, HLT_Ele115, HLT_Ele35;
double muejj_l, emujj_l;
double M_leplep;
std:vector<double>* patElectron_pt; patElectron_pt=0;
vector<double>* patElectron_eta; patElectron_eta=0;
vector<double>* patElectron_phi; patElectron_phi=0;
vector<double>* patElectron_ecalTrkEnergyPostCorr; patElectron_ecalTrkEnergyPostCorr=0;
vector<double>* patElectron_energy; patElectron_energy=0;
vector<int>* patElectron_charge; patElectron_charge=0;
vector<double>* Muon_pt_tunePbt_Roc; Muon_pt_tunePbt_Roc=0;
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

/*TBranch *a_HLT_Ele115_CaloIdVT_GsfTrkIdT=a_->GetBranch("HLT_Ele115_CaloIdVT_GsfTrkIdT");
TBranch *a_HLT_Ele35_WPTight_Gsf=a_->GetBranch("HLT_Ele35_WPTight_Gsf");
TBranch *a_HLT_Photon200=a_->GetBranch("HLT_Photon200");*/
TBranch *a_HLT_Mu50=a_->GetBranch("HLT_Mu50");
TBranch *a_HLT_OldMu100=a_->GetBranch("HLT_OldMu100");
TBranch *a_HLT_TkMu50=a_->GetBranch("HLT_TkMu50");
TBranch *a_HLT_TkMu100=a_->GetBranch("HLT_TkMu100");

TBranch *a_patElectron_pt=a_->GetBranch("patElectron_pt");
TBranch *a_patElectron_eta=a_->GetBranch("patElectron_eta");
TBranch *a_patElectron_phi=a_->GetBranch("patElectron_phi");
TBranch *a_patElectron_ecalTrkEnergyPostCorr=a_->GetBranch("patElectron_ecalTrkEnergyPostCorr");
TBranch *a_patElectron_energy=a_->GetBranch("patElectron_energy");
TBranch *a_patElectron_charge=a_->GetBranch("patElectron_charge");

TBranch *a_Muon_pt_tunePbt_Roc=a_->GetBranch("Muon_pt_tunePbt_Roc");
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

/*a_HLT_Ele115_CaloIdVT_GsfTrkIdT->SetAddress(&HLT_Ele115);
a_HLT_Ele35_WPTight_Gsf->SetAddress(&HLT_Ele35);
a_HLT_Photon200->SetAddress(&HLT_Photon200); */
a_HLT_Mu50->SetAddress(&HLT_Mu50);
a_HLT_OldMu100->SetAddress(&HLT_OldMu100);
a_HLT_TkMu50->SetAddress(&HLT_TkMu50);
a_HLT_TkMu100->SetAddress(&HLT_TkMu100);

a_patElectron_pt->SetAddress(&patElectron_pt);
a_patElectron_eta->SetAddress(&patElectron_eta);
a_patElectron_phi->SetAddress(&patElectron_phi);
a_patElectron_ecalTrkEnergyPostCorr->SetAddress(&patElectron_ecalTrkEnergyPostCorr);
a_patElectron_energy->SetAddress(&patElectron_energy);
a_patElectron_charge->SetAddress(&patElectron_charge);

a_Muon_pt_tunePbt_Roc->SetAddress(&Muon_pt_tunePbt_Roc);
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

const double asymbins[9] = {0,200,400,600,800,1000,1400,2000,10000};
const double asymbinspt[5] = {250, 300, 350, 500, 10000};

TH1D *M_eeJ_SS = new TH1D ("M_eeJ_SS", "M_eeJ_SS", 8, asymbins);
TH1D *M_eeJ_OS = new TH1D ("M_eeJ_OS", "M_eeJ_OS", 8, asymbins);
TH1D *M_mumuJ_SS = new TH1D ("M_mumuJ_SS", "M_mumuJ_SS", 8, asymbins);
TH1D *M_mumuJ_OS = new TH1D ("M_mumuJ_OS", "M_mumuJ_OS", 8, asymbins);
TH1D *M_eeJ_Z_SS = new TH1D ("M_eeJ_Z_SS", "M_eeJ_Z_SS", 8, asymbins);
TH1D *M_eeJ_Z_OS = new TH1D ("M_eeJ_Z_OS", "M_eeJ_Z_OS", 8, asymbins);
TH1D *M_mumuJ_Z_SS = new TH1D ("M_mumuJ_Z_SS", "M_mumuJ_Z_SS", 8, asymbins);
TH1D *M_mumuJ_Z_OS = new TH1D ("M_mumuJ_Z_OS", "M_mumuJ_Z_OS", 8, asymbins);

TH1D *n_best_Vtx = new TH1D ("n_best_Vtx", "n_best_Vtx", 100,0, 100);
TH1D *M_mumu_100300 = new TH1D ("M_mumu_100300", "M_mumu_100300", 200, 100, 300);
TH1D *M_mumu_100300_BB = new TH1D ("M_mumu_100300_BB", "M_mumu_100300_BB", 200, 100, 300);
TH1D *M_mumu_100300_BE = new TH1D ("M_mumu_100300_BE", "M_mumu_100300_BE", 200, 100, 300);
TH1D *M_mumu_100300_EE = new TH1D ("M_mumu_100300_EE", "M_mumu_100300_EE", 200, 100, 300);
TH1D *M_ee_100300 = new TH1D ("M_ee_100300", "M_ee_100300", 200, 100, 300);
TH1D *M_ee_100300_BB = new TH1D ("M_ee_100300_BB", "M_ee_100300_BB", 200, 100, 300);
TH1D *M_ee_100300_BE = new TH1D ("M_ee_100300_BE", "M_ee_100300_BE", 200, 100, 300);
TH1D *M_ee_100300_EE = new TH1D ("M_ee_100300_EE", "M_ee_100300_EE", 200, 100, 300);
TH1D *M_mumu_Z_50130 = new TH1D ("M_mumu_Z_50130", "M_mumu_Z_50130", 80, 50, 130);
TH1D *M_mumu_Z_50130_EE = new TH1D ("M_mumu_Z_50130_EE", "M_mumu_Z_50130_EE", 80, 50, 130);
TH1D *M_mumu_Z_50130_BE = new TH1D ("M_mumu_Z_50130_BE", "M_mumu_Z_50130_BE", 80, 50, 130);
TH1D *M_mumu_Z_50130_BB = new TH1D ("M_mumu_Z_50130_BB", "M_mumu_Z_50130_BB", 80, 50, 130);
TH1D *M_ee_Z_50130 = new TH1D ("M_ee_Z_50130", "M_ee_Z_50130", 80, 50, 130);
TH1D *M_ee_Z_50130_EE = new TH1D ("M_ee_Z_50130_EE", "M_ee_Z_50130_EE", 80, 50, 130);
TH1D *M_ee_Z_50130_BE = new TH1D ("M_ee_Z_50130_BE", "M_ee_Z_50130_BE", 80, 50, 130);
TH1D *M_ee_Z_50130_BB = new TH1D ("M_ee_Z_50130_BB", "M_ee_Z_50130_BB", 80, 50, 130);

TH1D *M_mumu = new TH1D ("M_mumu", "M_mumu", 50, 150, 300);
TH1D *M_mumu_BB = new TH1D ("M_mumu_BB", "M_mumu_BB", 50, 150, 300);
TH1D *M_mumu_BE = new TH1D ("M_mumu_BE", "M_mumu_BE", 50, 150, 300);
TH1D *M_mumu_EE = new TH1D ("M_mumu_EE", "M_mumu_EE", 50, 150, 300);
TH1D *M_mumuJ = new TH1D ("M_mumuJ", "M_mumuJ", 8, asymbins);
TH1D *M_mumuJ_BB = new TH1D ("M_mumuJ_BB", "M_mumuJ_BB", 8, asymbins);
TH1D *M_mumuJ_BE = new TH1D ("M_mumuJ_BE", "M_mumuJ_BE", 8, asymbins);
TH1D *M_mumuJ_EE = new TH1D ("M_mumuJ_EE", "M_mumuJ_EE", 8, asymbins);
TH1D *pt_mumu = new TH1D ("pt_mumu", "pt_mumu", 100, 0, 1000);
TH1D *pt_mumu_BB = new TH1D ("pt_mumu_BB", "pt_mumu_BB", 100, 0, 1000);
TH1D *pt_mumu_BE = new TH1D ("pt_mumu_BE", "pt_mumu_BE", 100, 0, 1000);
TH1D *pt_mumu_EE = new TH1D ("pt_mumu_EE", "pt_mumu_EE", 100, 0, 1000);

TH1D *M_eeJ = new TH1D ("M_eeJ", "M_eeJ", 8, asymbins);
TH1D *M_eeJ_BB = new TH1D ("M_eeJ_BB", "M_eeJ_BB", 8, asymbins);
TH1D *M_eeJ_BE = new TH1D ("M_eeJ_BE", "M_eeJ_BE", 8, asymbins);
TH1D *M_eeJ_EE = new TH1D ("M_eeJ_EE", "M_eeJ_EE", 8, asymbins);
TH1D *pt_ee = new TH1D ("pt_ee", "pt_ee", 100, 0, 1000);
TH1D *pt_ee_BB = new TH1D ("pt_ee_BB", "pt_ee_BB", 100, 0, 1000);
TH1D *pt_ee_BE = new TH1D ("pt_ee_BE", "pt_ee_BE", 100, 0, 1000);
TH1D *pt_ee_EE = new TH1D ("pt_ee_EE", "pt_ee_EE", 100, 0, 1000);
TH1D *M_ee = new TH1D ("M_ee", "M_ee", 50, 150, 300);
TH1D *M_ee_BB = new TH1D ("M_ee_BB", "M_ee_BB", 50, 150, 300);
TH1D *M_ee_BE = new TH1D ("M_ee_BE", "M_ee_BE", 50, 150, 300);
TH1D *M_ee_EE = new TH1D ("M_ee_EE", "M_ee_EE", 50, 150, 300);

TH1D *Mmumu_DYcr = new TH1D ("Mmumu_DYcr", "Mmumu_DYcr", 50, 150, 300);
TH1D *M_mumuJ_Z = new TH1D ("M_mumuJ_Z", "M_mumuJ_Z", 8, asymbins);
TH1D *M_mumuJ_Z_BB = new TH1D ("M_mumuJ_Z_BB", "M_mumuJ_Z_BB", 8, asymbins);
TH1D *M_mumuJ_Z_BE = new TH1D ("M_mumuJ_Z_BE", "M_mumuJ_Z_BE", 8, asymbins);
TH1D *M_mumuJ_Z_EE = new TH1D ("M_mumuJ_Z_EE", "M_mumuJ_Z_EE", 8, asymbins);
TH1D *pt_mumu_Z = new TH1D ("pt_mumu_Z", "pt_mumu_Z", 4, asymbinspt);
TH1D *pt_mumu_Z_BB = new TH1D ("pt_mumu_Z_BB", "pt_mumu_Z_BB", 4, asymbinspt);
TH1D *pt_mumu_Z_BE = new TH1D ("pt_mumu_Z_BE", "pt_mumu_Z_BE", 4, asymbinspt);
TH1D *pt_mumu_Z_EE = new TH1D ("pt_mumu_Z_EE", "pt_mumu_Z_EE", 4, asymbinspt);
TH1D *M_eeJ_Z = new TH1D ("M_eeJ_Z", "M_eeJ_Z", 8, asymbins);
TH1D *M_eeJ_Z_BB = new TH1D ("M_eeJ_Z_BB", "M_eeJ_Z_BB", 8, asymbins);
TH1D *M_eeJ_Z_BE = new TH1D ("M_eeJ_Z_BE", "M_eeJ_Z_BE", 8, asymbins);
TH1D *M_eeJ_Z_EE = new TH1D ("M_eeJ_Z_EE", "M_eeJ_Z_EE", 8, asymbins);
TH1D *pt_ee_Z = new TH1D ("pt_ee_Z", "pt_ee_Z", 4, asymbinspt);
TH1D *pt_ee_Z_BB = new TH1D ("pt_ee_Z_BB", "pt_ee_Z_BB", 4, asymbinspt);
TH1D *pt_ee_Z_BE = new TH1D ("pt_ee_Z_BE", "pt_ee_Z_BE", 4, asymbinspt);
TH1D *pt_ee_Z_EE = new TH1D ("pt_ee_Z_EE", "pt_ee_Z_EE", 4, asymbinspt);
TH1D *M_mumu_Zpeak = new TH1D ("M_mumu_Zpeak", "M_mumu_Zpeak", 60, 60, 120);
TH1D *M_mumu_Zpeak_BB = new TH1D ("M_mumu_Zpeak_BB", "M_mumu_Zpeak_BB", 60, 60, 120);
TH1D *M_mumu_Zpeak_BE = new TH1D ("M_mumu_Zpeak_BE", "M_mumu_Zpeak_BE", 60, 60, 120);
TH1D *M_mumu_Zpeak_EE = new TH1D ("M_mumu_Zpeak_EE", "M_mumu_Zpeak_EE", 60, 60, 120);
TH1D *M_ee_Zpeak = new TH1D ("M_ee_Zpeak", "M_ee_Zpeak", 60, 60, 120);
TH1D *M_ee_Zpeak_BB = new TH1D ("M_ee_Zpeak_BB", "M_ee_Zpeak_BB", 60, 60, 120);
TH1D *M_ee_Zpeak_BE = new TH1D ("M_ee_Zpeak_BE", "M_ee_Zpeak_BE", 60, 60, 120);
TH1D *M_ee_Zpeak_EE = new TH1D ("M_ee_Zpeak_EE", "M_ee_Zpeak_EE", 60, 60, 120);


TLorentzVector Muon1;
TLorentzVector Muon2;
TLorentzVector Electron1;
TLorentzVector Electron2;
TLorentzVector BoostJet;

cout << a_->GetEntries() << endl;
int tot=0, muejj = 0;
double wg = 0;
int lumi = 41529; //2017: 41529 //2016: 35920
bool veto_ele = false;
double deltaEta = 0, deltaPhi = 0, deltaR = 0;
double mee = 0, mmumu = 0;
double energy_corr0 = 0, energy_corr1 = 0;

for (Int_t i=0;i<a_->GetEntries();i++) {
 a_->GetEntry(i);
 tot = a_->GetEntries();
 if (i%100000 == 0) cout << i << " eventi analizzati su " << tot << endl;

 HLT_Ele=0;
 HLT_Mu = 0;
 if (HLT_Mu50==1 || HLT_TkMu100==1 || HLT_OldMu100==1 ) HLT_Mu = 1;
 if (HLT_Ele115==1 || HLT_Photon200 ==1 || HLT_Ele35 ==1) HLT_Ele=1;


 if (Muon_pt_tunePbt_Roc->size() > 1 && numOfHighptMu==2 && numOfVetoEle == 0 && numOfBoostedJets>=1){
  if (HLT_Mu == 1 && Muon_pt_tunePbt_Roc->at(0) > 150 && Muon_pt_tunePbt_Roc->at(1) > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(Muon_eta->at(1))<2.4 && BoostedJet_pt->at(0) > 190 ){
   Muon1.SetPtEtaPhiM(Muon_pt_tunePbt_Roc->at(0), Muon_eta->at(0), Muon_phi->at(0),0.1056583745);
   Muon2.SetPtEtaPhiM(Muon_pt_tunePbt_Roc->at(1), Muon_eta->at(1), Muon_phi->at(1),0.1056583745);
   BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));


   mmumu= (Muon1+Muon2).M();
    if(mmumu > 100 && mmumu < 300){
        M_mumu_100300->Fill(mmumu);
     if(fabs(Muon_eta->at(1))<0.8 && fabs(Muon_eta->at(0))<0.8)M_mumu_100300_BB->Fill(mmumu);
   if((fabs(Muon_eta->at(1))<0.8 && fabs(Muon_eta->at(0))>0.8) || (fabs(Muon_eta->at(1))>0.8 && fabs(Muon_eta->at(0))<0.8))M_mumu_100300_BE->Fill(mmumu);
   if(fabs(Muon_eta->at(1))>0.8 && fabs(Muon_eta->at(0))>0.8)M_mumu_100300_EE->Fill(mmumu);
    }
    if(mmumu >50 && mmumu < 130){
     M_mumu_Z_50130->Fill(mmumu);
     if(fabs(Muon_eta->at(1))<0.8 && fabs(Muon_eta->at(0))<0.8)M_mumu_Z_50130_BB->Fill(mmumu);
   if((fabs(Muon_eta->at(1))<0.8 && fabs(Muon_eta->at(0))>0.8) || (fabs(Muon_eta->at(1))>0.8 && fabs(Muon_eta->at(0))<0.8))M_mumu_Z_50130_BE->Fill(mmumu);
   if(fabs(Muon_eta->at(1))>0.8 && fabs(Muon_eta->at(0))>0.8)M_mumu_Z_50130_EE->Fill(mmumu);
   }
   if (mmumu >=150 && mmumu <= 300){
    Mmumu_DYcr->Fill((Muon1+Muon2).M());
    M_mumuJ->Fill((Muon1+Muon2+BoostJet).M());  
    pt_mumu->Fill(Muon1.Pt() + Muon2.Pt());
    M_mumu->Fill((Muon1+Muon2).M());
    if (Muon_charge->at(0)*Muon_charge->at(1) == 1) M_mumuJ_Z_SS->Fill((Muon1+Muon2+BoostJet).M());
     if (Muon_charge->at(0)*Muon_charge->at(1) == -1) M_mumuJ_Z_OS->Fill((Muon1+Muon2+BoostJet).M());
    if(fabs(Muon_eta->at(1))<0.8 && fabs(Muon_eta->at(0))<0.8){
     M_mumu_BB->Fill((Muon1+Muon2).M());
     M_mumuJ_BB->Fill((Muon1+Muon2+BoostJet).M());
     pt_mumu_BB->Fill(Muon1.Pt() + Muon2.Pt());
    }
    if((fabs(Muon_eta->at(1))<0.8 && fabs(Muon_eta->at(0))>0.8) || (fabs(Muon_eta->at(1))>0.8 && fabs(Muon_eta->at(0))<0.8)){
     M_mumu_BE->Fill((Muon1+Muon2).M());
     M_mumuJ_BE->Fill((Muon1+Muon2+BoostJet).M());
     pt_mumu_BE->Fill(Muon1.Pt() + Muon2.Pt());
    }
    if(fabs(Muon_eta->at(1))>0.8 && fabs(Muon_eta->at(0))>0.8){
     M_mumu_EE->Fill((Muon1+Muon2).M());
     M_mumuJ_EE->Fill((Muon1+Muon2+BoostJet).M());
     pt_mumu_EE->Fill(Muon1.Pt() + Muon2.Pt());
    }
   }
    if (mmumu >= 60 && mmumu <= 120){
     M_mumuJ_Z->Fill((Muon1+Muon2+BoostJet).M());
     pt_mumu_Z->Fill(Muon1.Pt() + Muon2.Pt());
     M_mumu_Zpeak->Fill((Muon1+Muon2).M());
     if (Muon_charge->at(0)*Muon_charge->at(1) == 1) M_mumuJ_Z_SS->Fill((Muon1+Muon2+BoostJet).M());
     if (Muon_charge->at(0)*Muon_charge->at(1) == -1) M_mumuJ_Z_OS->Fill((Muon1+Muon2+BoostJet).M());
     if(fabs(Muon_eta->at(1))<0.8 && fabs(Muon_eta->at(0))<0.8){
     M_mumuJ_Z_BB->Fill((Muon1+Muon2+BoostJet).M());
     pt_mumu_Z_BB->Fill(Muon1.Pt() + Muon2.Pt());
     M_mumu_Zpeak_BB->Fill((Muon1+Muon2).M());
    }
    if((fabs(Muon_eta->at(1))<0.8 && fabs(Muon_eta->at(0))>0.8) || (fabs(Muon_eta->at(1))>0.8 && fabs(Muon_eta->at(0))<0.8)){
     M_mumuJ_Z_BE->Fill((Muon1+Muon2+BoostJet).M());
     pt_mumu_Z_BE->Fill(Muon1.Pt() + Muon2.Pt());
     M_mumu_Zpeak_BE->Fill((Muon1+Muon2).M());
    }
    if(fabs(Muon_eta->at(1))>0.8 && fabs(Muon_eta->at(0))>0.8){
     M_mumuJ_Z_EE->Fill((Muon1+Muon2+BoostJet).M());
     pt_mumu_Z_EE->Fill(Muon1.Pt() + Muon2.Pt());
     M_mumu_Zpeak_EE->Fill((Muon1+Muon2).M());
    }

    }


  }
 }
  if (patElectron_pt->size() > 1 && numOfHighptEle==2 && numOfLooseMu==0 && numOfBoostedJets>=1){
  if (HLT_Ele==1 && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190){

   Electron1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   Electron2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energy->at(1));
   BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));

  // energy correction  

   energy_corr0= patElectron_ecalTrkEnergyPostCorr->at(0) / patElectron_energy->at(0) ;
   energy_corr1= patElectron_ecalTrkEnergyPostCorr->at(1) / patElectron_energy->at(1) ;
   Electron1 = Electron1*energy_corr0;
   Electron2 = Electron2*energy_corr1;  

    mee = (Electron1+Electron2).M();
    if(mee >= 100 && mee <= 300){
     M_ee_100300->Fill(mee);
     if(fabs(patElectron_eta->at(0))<0.8 && fabs(patElectron_eta->at(1))<0.8)M_ee_100300_BB->Fill(mee);
     if((fabs(patElectron_eta->at(0))<0.8 && fabs(patElectron_eta->at(1))>0.8) || (fabs(patElectron_eta->at(0))>0.8 && fabs(patElectron_eta->at(1))<0.8))M_ee_100300_BE->Fill(mee);
     if(fabs(patElectron_eta->at(0))>0.8 && fabs(patElectron_eta->at(1))>0.8)M_ee_100300_EE->Fill(mee);
    }
    if(mee > 50 && mee < 130){
        M_ee_Z_50130->Fill(mee);
     if(fabs(patElectron_eta->at(0))<0.8 && fabs(patElectron_eta->at(1))<0.8)M_ee_Z_50130_BB->Fill(mee);
     if((fabs(patElectron_eta->at(0))<0.8 && fabs(patElectron_eta->at(1))>0.8) || (fabs(patElectron_eta->at(0))>0.8 && fabs(patElectron_eta->at(1))<0.8))M_ee_Z_50130_BE->Fill(mee);
     if(fabs(patElectron_eta->at(0))>0.8 && fabs(patElectron_eta->at(1))>0.8)M_ee_Z_50130_EE->Fill(mee);
    } 
    if (mee>=150 && mee <= 300){
     if (patElectron_charge->at(0)*patElectron_charge->at(1) == 1)M_eeJ_SS->Fill((Electron1+Electron2+BoostJet).M());
     if (patElectron_charge->at(0)*patElectron_charge->at(1) == -1)M_eeJ_OS->Fill((Electron1+Electron2+BoostJet).M());
        M_eeJ->Fill((Electron1+Electron2+BoostJet).M());
        pt_ee ->Fill(Electron1.Pt() + Electron2.Pt());
      M_ee->Fill((Electron1+Electron2).M());
      if(fabs(patElectron_eta->at(0))<0.8 && fabs(patElectron_eta->at(1))<0.8){
      M_ee_BB->Fill((Electron1+Electron2).M());
      M_eeJ_BB->Fill((Electron1+Electron2+BoostJet).M());
      pt_ee_BB->Fill(Electron1.Pt() + Electron2.Pt());
     }
     if((fabs(patElectron_eta->at(0))<0.8 && fabs(patElectron_eta->at(1))>0.8) || (fabs(patElectron_eta->at(0))>0.8 && fabs(patElectron_eta->at(1))<0.8)){
      M_ee_BE->Fill((Electron1+Electron2).M());
      M_eeJ_BE->Fill((Electron1+Electron2+BoostJet).M());
      pt_ee_BE->Fill(Electron1.Pt() + Electron2.Pt());
     }
     if(fabs(patElectron_eta->at(0))>0.8 && fabs(patElectron_eta->at(1))>0.8){
      M_ee_EE->Fill((Electron1+Electron2).M());
      M_eeJ_EE->Fill((Electron1+Electron2+BoostJet).M());
      pt_ee_EE->Fill(Electron1.Pt() + Electron2.Pt());
    }
 
    }
    if (mee >= 60 && mee <= 120){
     M_ee_Zpeak->Fill((Electron1+Electron2).M());
     M_eeJ_Z->Fill((Electron1+Electron2+BoostJet).M());
     pt_ee_Z->Fill(Electron1.Pt() + Electron2.Pt());
     if (patElectron_charge->at(0)*patElectron_charge->at(1) == 1)M_eeJ_Z_SS->Fill((Electron1+Electron2+BoostJet).M());
     if (patElectron_charge->at(0)*patElectron_charge->at(1) == -1)M_eeJ_Z_OS->Fill((Electron1+Electron2+BoostJet).M()); 
     if(fabs(patElectron_eta->at(0))<0.8 && fabs(patElectron_eta->at(1))<0.8){
      M_ee_Zpeak_BB->Fill((Electron1+Electron2).M());
      M_eeJ_Z_BB->Fill((Electron1+Electron2+BoostJet).M());
      pt_ee_Z_BB->Fill(Electron1.Pt() + Electron2.Pt());
     }
     if((fabs(patElectron_eta->at(0))<0.8 && fabs(patElectron_eta->at(1))>0.8) || (fabs(patElectron_eta->at(0))>0.8 && fabs(patElectron_eta->at(1))<0.8)){
      M_ee_Zpeak_BE->Fill((Electron1+Electron2).M());
      M_eeJ_Z_BE->Fill((Electron1+Electron2+BoostJet).M());
      pt_ee_Z_BE->Fill(Electron1.Pt() + Electron2.Pt());
     }
     if(fabs(patElectron_eta->at(0))>0.8 && fabs(patElectron_eta->at(1))>0.8){
      M_ee_Zpeak_EE->Fill((Electron1+Electron2).M());
      M_eeJ_Z_EE->Fill((Electron1+Electron2+BoostJet).M());
      pt_ee_Z_EE->Fill(Electron1.Pt() + Electron2.Pt());
     }
    }
  
  }
 }

}

TFile *f = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/2017_ALL_HOPE/25062021/CR_DY_data_mu_2017.root", "RECREATE");
//TFile *f = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/2017_ALL_HOPE/CR_DY_data_mu_2017.root", "RECREATE");
M_eeJ_Z_SS->Write();
M_eeJ_Z_OS->Write();
M_eeJ_SS->Write();
M_eeJ_OS->Write();
M_mumuJ_Z_SS->Write();
M_mumuJ_Z_OS->Write();
M_mumuJ_SS->Write();
M_mumuJ_OS->Write();
M_ee->Write();
M_ee_BB->Write();
M_ee_BE->Write();
M_ee_EE->Write();
M_mumu->Write();
M_mumu_BB->Write();
M_mumu_BE->Write();
M_mumu_EE->Write();
Mmumu_DYcr->Write();
n_best_Vtx->Write();
M_mumu_100300->Write();
M_mumu_100300_BB->Write();
M_mumu_100300_BE->Write();
M_mumu_100300_EE->Write();
M_mumu_Z_50130->Write();
M_mumu_Z_50130_BB->Write();
M_mumu_Z_50130_BE->Write();
M_mumu_Z_50130_EE->Write();
M_ee_100300->Write();
M_ee_100300_BB->Write();
M_ee_100300_BE->Write();
M_ee_100300_EE->Write();
M_ee_Z_50130->Write();
M_ee_Z_50130_BB->Write();
M_ee_Z_50130_BE->Write();
M_ee_Z_50130_EE->Write();
M_mumuJ->Write();
M_mumuJ_BB->Write();
M_mumuJ_BE->Write();
M_mumuJ_EE->Write();
pt_mumu->Write();
pt_mumu_BB->Write();
pt_mumu_BE->Write();
pt_mumu_EE->Write();
M_eeJ->Write();
M_eeJ_BB->Write();
M_eeJ_BE->Write();
M_eeJ_EE->Write();
pt_ee->Write();
pt_ee_BB->Write();
pt_ee_BE->Write();
pt_ee_EE->Write();
M_mumuJ_Z->Write();
M_mumuJ_Z_BB->Write();
M_mumuJ_Z_BE->Write();
M_mumuJ_Z_EE->Write();
pt_mumu_Z->Write();
pt_mumu_Z_BB->Write();
pt_mumu_Z_BE->Write();
pt_mumu_Z_EE->Write();
M_eeJ_Z->Write();
M_eeJ_Z_BB->Write();
M_eeJ_Z_BE->Write();
M_eeJ_Z_EE->Write();
pt_ee_Z->Write();
pt_ee_Z_BB->Write();
pt_ee_Z_BE->Write();
pt_ee_Z_EE->Write();
M_mumu_Zpeak->Write();
M_mumu_Zpeak_BB->Write();
M_mumu_Zpeak_BE->Write();
M_mumu_Zpeak_EE->Write();
M_ee_Zpeak->Write();
M_ee_Zpeak_BB->Write();
M_ee_Zpeak_BE->Write();
M_ee_Zpeak_EE->Write();

f->Write();
f->Close();

}
 
