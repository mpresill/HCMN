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
//void filename_(const char*  Input = "", const char*  Output =""){
void Analisi_data(){

TChain *a_ = new TChain("BOOM");


const char* Input = "/eos/user/v/vmariani/NTuples/HN_2016/Syst_ALL_HOPE/data_ele_2016.root"; //then this can be insterted in the function input

/*
here we check if the data are electron or muon ones, and which year they are referring to 
*/


//const char* Output = "outputFile"; 
a_->Add(Input);
//inputFile

int HLT_Ele, HLT_Mu, HLT_Mu50, HLT_TkMu50;
double muejj_l, emujj_l;
double M_leplep;
std:vector<double>* patElectron_pt; patElectron_pt=0;
vector<double>* patElectron_eta; patElectron_eta=0;
vector<double>* patElectron_phi; patElectron_phi=0;
vector<double>* patElectron_ecalTrkEnergyPostCorr; patElectron_ecalTrkEnergyPostCorr=0;
vector<double>* patElectron_energy; patElectron_energy=0;
vector<int>* patElectron_charge; patElectron_charge=0;
vector<double>* Muon_pt_tunePbt; Muon_pt_tunePbt=0;
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

TBranch *a_HLT_Ele115_CaloIdVT_GsfTrkIdT=a_->GetBranch("HLT_Ele115_CaloIdVT_GsfTrkIdT");
TBranch *a_HLT_Mu50=a_->GetBranch("HLT_Mu50");
TBranch *a_HLT_TkMu50=a_->GetBranch("HLT_TkMu50");

TBranch *a_patElectron_pt=a_->GetBranch("patElectron_pt");
TBranch *a_patElectron_eta=a_->GetBranch("patElectron_eta");
TBranch *a_patElectron_phi=a_->GetBranch("patElectron_phi");
TBranch *a_patElectron_ecalTrkEnergyPostCorr=a_->GetBranch("patElectron_ecalTrkEnergyPostCorr");
TBranch *a_patElectron_energy=a_->GetBranch("patElectron_energy");
TBranch *a_patElectron_charge=a_->GetBranch("patElectron_charge");

TBranch *a_Muon_pt_tunePbt=a_->GetBranch("Muon_pt_tunePbt");
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

a_patElectron_pt->SetAddress(&patElectron_pt);
a_patElectron_eta->SetAddress(&patElectron_eta);
a_patElectron_phi->SetAddress(&patElectron_phi);
a_patElectron_ecalTrkEnergyPostCorr->SetAddress(&patElectron_ecalTrkEnergyPostCorr);
a_patElectron_energy->SetAddress(&patElectron_energy);
a_patElectron_charge->SetAddress(&patElectron_charge);

a_Muon_pt_tunePbt->SetAddress(&Muon_pt_tunePbt);
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

TH1D *n_best_Vtx = new TH1D ("n_best_Vtx", "n_best_Vtx", 100,0, 100);
TH1D *data_obs_mumu = new TH1D ("data_obs_mumu", "data_obs_mumu", 220, 80, 300);
TH1D *data_obs_ee = new TH1D ("data_obs_ee", "data_obs_ee", 220, 80, 300);
TH1D *data_obs_mumu_Z = new TH1D ("data_obs_mumu_Z", "data_obs_mumu_Z", 80, 50, 130);
TH1D *data_obs_ee_Z = new TH1D ("data_obs_ee_Z", "data_obs_ee_Z", 80, 50, 130);

const double asymbins[9] = {0,200,400,600,800,1000,1400,2000,10000};

TH1D *data_obs = new TH1D ("data_obs", "data_obs", 8, asymbins);


TLorentzVector Muon1;
TLorentzVector Muon2;
TLorentzVector Electron1;
TLorentzVector Electron2;
TLorentzVector BoostJet;



cout << a_->GetEntries() << endl;
int tot=0, muejj = 0;
double wg = 0;
int lumi = 35542;//2018: 58873 //2017: 41529 //2016: 35542
bool veto_ele = false;
double mee = 0, mmumu = 0;
double energy_corr0 =0, energy_corr1=0;




for (Int_t i=0;i<a_->GetEntries();i++) {
 a_->GetEntry(i);
 tot = a_->GetEntries();
 if (i%100000 == 0) cout << i << " eventi analizzati su " << tot << endl;
 HLT_Mu = 0;

 if (HLT_Mu50==1 || HLT_TkMu50==1) HLT_Mu = 1;

 if (Muon_pt_tunePbt->size() > 1 && numOfHighptMu==2 && numOfVetoEle == 0 && numOfBoostedJets>=1){
  if (HLT_Mu == 1 && Muon_pt_tunePbt->at(0) > 150 && Muon_pt_tunePbt->at(1) > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(Muon_eta->at(1))<2.4 && BoostedJet_pt->at(0) > 190 ){
   BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
   Muon1.SetPtEtaPhiM(Muon_pt_tunePbt->at(0), Muon_eta->at(0), Muon_phi->at(0),0.1056583745 );
   Muon2.SetPtEtaPhiM(Muon_pt_tunePbt->at(1), Muon_eta->at(1), Muon_phi->at(1),0.1056583745 );
   mmumu= (Muon1+Muon2).M();
   if(mmumu > 300){
    data_obs->Fill((Muon1+Muon2+BoostJet).M());
   }
  }
 }

 if (patElectron_pt->size() > 1 && numOfHighptEle==2 && numOfLooseMu==0 && numOfBoostedJets>=1){
   if (HLT_Ele == 1 && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190){
    BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));	
    Electron1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
    Electron2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energy->at(1));
    energy_corr0= patElectron_ecalTrkEnergyPostCorr->at(0) / patElectron_energy->at(0) ;
    energy_corr1= patElectron_ecalTrkEnergyPostCorr->at(1) / patElectron_energy->at(1) ;
    Electron1 = Electron1*energy_corr0;
    Electron2 = Electron2*energy_corr1;
    mee = (Electron1+Electron2).M();
    if(mee > 300){
     data_obs->Fill((Electron1+Electron2+BoostJet).M());
    }
  }
 }
 
}





TFile *f = new TFile("test_data.root", "RECREATE");




data_obs->Write();
f->Write();
f->Close();


}
 
