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
void Analisi_SR_MC_syst(){

TChain *a_ = new TChain("BOOM");

a_->Add("/eos/user/m/mpresill/CMS/HN_Reload/rootplized_samples_2017_syst/WJets_2017.root");

int HLT_Ele115, HLT_Ele35, HLT_Photon200, HLT_Mu, HLT_Mu50, HLT_OldMu100, HLT_TkMu50, HLT_TkMu100;
double muejj_l, emujj_l;
std:vector<double>* patElectron_pt; patElectron_pt=0;
vector<double>* patElectron_eta; patElectron_eta=0;
vector<double>* patElectron_phi; patElectron_phi=0;
vector<double>* patElectron_energy; patElectron_energy=0;
vector<double>* patElectron_energyScaleUp; patElectron_energyScaleUp=0;
vector<double>* patElectron_energyScaleDown; patElectron_energyScaleDown=0;
vector<double>* patElectron_energySigmaUp; patElectron_energySigmaUp=0;
vector<double>* patElectron_energySigmaDown; patElectron_energySigmaDown=0;
vector<double>* Muon_pt; Muon_pt=0;
vector<double>* Muon_pt_corr; Muon_pt_corr=0;
vector<double>* Muon_eta; Muon_eta=0;
vector<double>* Muon_phi; Muon_phi=0;
vector<double>* Muon_energy; Muon_energy=0;
vector<double>* Muon_charge; Muon_charge=0;
vector<double>*BoostedJet_pt; BoostedJet_pt=0;
vector<double>*BoostedJet_eta; BoostedJet_eta=0;
vector<double>*BoostedJet_phi; BoostedJet_phi=0;
vector<double>*BoostedJet_energy; BoostedJet_energy=0;
double PUWeight, MinBiasUpWeight, MinBiasDownWeight;
double lepsf_evt, lepsf_evt_u, lepsf_evt_d; 
double numOfHighptEle, numOfVetoEle, numOfHighptMu, numOfLooseMu, numOfBoostedJets;
double lumi_wgt, trueInteractions;
vector<double>*centralJesJer; centralJesJer=0;
vector<double>*JesSFup; JesSFup=0;
vector<double>*JesSFdown; JesSFdown=0;
vector<double>*JerSFup; JerSFup=0;
vector<double>*JerSFdown; JerSFdown=0;
int nBestVtx;

TBranch *a_HLT_Ele115_CaloIdVT_GsfTrkIdT=a_->GetBranch("HLT_Ele115_CaloIdVT_GsfTrkIdT");
TBranch *a_HLT_Ele35_WPTight_Gsf=a_->GetBranch("HLT_Ele35_WPTight_Gsf");
TBranch *a_HLT_Photon200=a_->GetBranch("HLT_Photon200");
TBranch *a_HLT_Mu50=a_->GetBranch("HLT_Mu50");
TBranch *a_HLT_OldMu100=a_->GetBranch("HLT_OldMu100");
TBranch *a_HLT_TkMu50=a_->GetBranch("HLT_TkMu50");
TBranch *a_HLT_TkMu100=a_->GetBranch("HLT_TkMu100");

TBranch *a_patElectron_pt=a_->GetBranch("patElectron_pt");
TBranch *a_patElectron_eta=a_->GetBranch("patElectron_eta");
TBranch *a_patElectron_phi=a_->GetBranch("patElectron_phi");
TBranch *a_patElectron_energy=a_->GetBranch("patElectron_energy");
TBranch *a_patElectron_energyScaleUp=a_->GetBranch("patElectron_energyScaleUp");
TBranch *a_patElectron_energyScaleDown=a_->GetBranch("patElectron_energyScaleDown");
TBranch *a_patElectron_energySigmaUp=a_->GetBranch("patElectron_energySigmaUp");
TBranch *a_patElectron_energySigmaDown=a_->GetBranch("patElectron_energySigmaDown");

TBranch *a_Muon_pt=a_->GetBranch("Muon_pt");
TBranch *a_Muon_pt_corr=a_->GetBranch("Muon_pt_corr");
TBranch *a_Muon_eta=a_->GetBranch("Muon_eta");
TBranch *a_Muon_phi=a_->GetBranch("Muon_phi");
TBranch *a_Muon_energy=a_->GetBranch("Muon_energy");
TBranch *a_Muon_charge=a_->GetBranch("Muon_charge");

TBranch *a_BoostedJet_pt=a_->GetBranch("BoostedJet_pt");
TBranch *a_BoostedJet_eta=a_->GetBranch("BoostedJet_eta");
TBranch *a_BoostedJet_phi=a_->GetBranch("BoostedJet_phi");
TBranch *a_BoostedJet_energy=a_->GetBranch("BoostedJet_energy");

TBranch *a_lepsf_evt=a_->GetBranch("lepsf_evt");
TBranch *a_lepsf_evt_u=a_->GetBranch("lepsf_evt_u");
TBranch *a_lepsf_evt_d=a_->GetBranch("lepsf_evt_d");
TBranch *a_lumi_wgt=a_->GetBranch("lumi_wgt");

TBranch *a_nBestVtx=a_->GetBranch("nBestVtx");
TBranch *a_trueInteractions=a_->GetBranch("trueInteractions");
TBranch *a_PUWeight=a_->GetBranch("PUWeight");
TBranch *a_MinBiasUpWeight=a_->GetBranch("MinBiasUpWeight");
TBranch *a_MinBiasDownWeight=a_->GetBranch("MinBiasDownWeight");

TBranch *a_muejj_l=a_->GetBranch("muejj_l");
TBranch *a_emujj_l=a_->GetBranch("emujj_l");

TBranch *a_numOfHighptEle=a_->GetBranch("numOfHighptEle");
TBranch *a_numOfHighptMu=a_->GetBranch("numOfHighptMu");
TBranch *a_numOfLooseMu=a_->GetBranch("numOfLooseMu");
TBranch *a_numOfBoostedJets=a_->GetBranch("numOfBoostedJets");
TBranch *a_numOfVetoEle=a_->GetBranch("numOfVetoEle");

TBranch *a_centralJesJer=a_->GetBranch("centralJesJer");
TBranch *a_JesSFup=a_->GetBranch("JesSFup");
TBranch *a_JesSFdown=a_->GetBranch("JesSFdown");
TBranch *a_JerSFup=a_->GetBranch("JerSFup");
TBranch *a_JerSFdown=a_->GetBranch("JerSFdown");

a_HLT_Ele115_CaloIdVT_GsfTrkIdT->SetAddress(&HLT_Ele115);
a_HLT_Ele35_WPTight_Gsf ->SetAddress(&HLT_Ele35);
a_HLT_Photon200->SetAddress(&HLT_Photon200);

a_HLT_Mu50->SetAddress(&HLT_Mu50);
a_HLT_OldMu100->SetAddress(&HLT_OldMu100);
a_HLT_TkMu50->SetAddress(&HLT_TkMu50);
a_HLT_TkMu100->SetAddress(&HLT_TkMu100);

a_patElectron_pt->SetAddress(&patElectron_pt);
a_patElectron_eta->SetAddress(&patElectron_eta);
a_patElectron_phi->SetAddress(&patElectron_phi);
a_patElectron_energy->SetAddress(&patElectron_energy);
a_patElectron_energyScaleUp->SetAddress(&patElectron_energyScaleUp);
a_patElectron_energyScaleDown->SetAddress(&patElectron_energyScaleDown);
a_patElectron_energySigmaUp->SetAddress(&patElectron_energySigmaUp);
a_patElectron_energySigmaDown->SetAddress(&patElectron_energySigmaDown);

a_Muon_pt->SetAddress(&Muon_pt);
a_Muon_pt_corr->SetAddress(&Muon_pt_corr);
a_Muon_eta->SetAddress(&Muon_eta);
a_Muon_phi->SetAddress(&Muon_phi);
a_Muon_energy->SetAddress(&Muon_energy);
a_Muon_charge->SetAddress(&Muon_charge);

a_lepsf_evt->SetAddress(&lepsf_evt);
a_lepsf_evt_u->SetAddress(&lepsf_evt_u);
a_lepsf_evt_d->SetAddress(&lepsf_evt_d);
a_lumi_wgt->SetAddress(&lumi_wgt);

a_BoostedJet_pt->SetAddress(&BoostedJet_pt);
a_BoostedJet_eta->SetAddress(&BoostedJet_eta);
a_BoostedJet_phi->SetAddress(&BoostedJet_phi);
a_BoostedJet_energy->SetAddress(&BoostedJet_energy);

a_nBestVtx->SetAddress(&nBestVtx);
a_trueInteractions->SetAddress(&trueInteractions);
a_PUWeight->SetAddress(&PUWeight);
a_MinBiasUpWeight->SetAddress(&MinBiasUpWeight);
a_MinBiasDownWeight->SetAddress(&MinBiasDownWeight);

a_muejj_l->SetAddress(&muejj_l);
a_emujj_l->SetAddress(&emujj_l);

a_numOfHighptEle->SetAddress(&numOfHighptEle);
a_numOfHighptMu->SetAddress(&numOfHighptMu);
a_numOfLooseMu->SetAddress(&numOfLooseMu);
a_numOfBoostedJets->SetAddress(&numOfBoostedJets);
a_numOfVetoEle->SetAddress(&numOfVetoEle);

a_centralJesJer->SetAddress(&centralJesJer);
a_JesSFup->SetAddress(&JesSFup);
a_JesSFdown->SetAddress(&JesSFdown);
a_JerSFup->SetAddress(&JerSFup);
a_JerSFdown->SetAddress(&JerSFdown);

const double asymbins[10] = {0,200,400,600,800,1000,1400,2000,3500,10000};

TH1D *WJets_mumujj = new TH1D ("WJets_mumujj", "WJets_mumujj", 9, asymbins);
TH1D *WJets_mumujj_2017_AlphaRatio = new TH1D ("WJets_mumujj_2017_AlphaRatio", "WJets_mumujj_2017_AlphaRatio", 9, asymbins);
TH1D *WJets_mumujj_2017_AlphaRatioUp = new TH1D ("WJets_mumujj_2017_AlphaRatioUp", "WJets_mumujj_2017_AlphaRatioUp", 9, asymbins);
TH1D *WJets_mumujj_2017_AlphaRatioDown = new TH1D ("WJets_mumujj_2017_AlphaRatioDown", "WJets_mumujj_2017_AlphaRatioDown", 9, asymbins); 
TH1D *WJets_mumujj_2017_SFUp = new TH1D ("WJets_mumujj_2017_SFUp", "WJets_mumujj_2017_SFUp", 9, asymbins);
TH1D *WJets_mumujj_2017_SFDown = new TH1D ("WJets_mumujj_2017_SFDown", "WJets_mumujj_2017_SFDown", 9, asymbins);
TH1D *WJets_mumujj_2017_PUUp = new TH1D ("WJets_mumujj_2017_PUUp", "WJets_mumujj_2017_PUUp", 9, asymbins);
TH1D *WJets_mumujj_2017_PUDown = new TH1D ("WJets_mumujj_2017_PUDown", "WJets_mumujj_2017_PUDown", 9, asymbins);
TH1D *WJets_mumujj_centralJesJer = new TH1D ("WJets_mumujj_centralJesJer", "WJets_mumujj_centralJesJer", 9, asymbins);
TH1D *WJets_mumujj_2017_JesSFUp = new TH1D ("WJets_mumujj_2017_JesSFUp", "WJets_mumujj_2017_JesSFUp", 9, asymbins);
TH1D *WJets_mumujj_2017_JesSFDown = new TH1D ("WJets_mumujj_2017_JesSFDown", "WJets_mumujj_2017_JesSFDown", 9, asymbins);
TH1D *WJets_mumujj_2017_JerSFUp = new TH1D ("WJets_mumujj_2017_JerSFUp", "WJets_mumujj_2017_JerSFUp", 9, asymbins);
TH1D *WJets_mumujj_2017_JerSFDown = new TH1D ("WJets_mumujj_2017_JerSFDown", "WJets_mumujj_2017_JerSFDown", 9, asymbins);
TH1D *WJets_mumujj_2017_PtCorrUp = new TH1D ("WJets_mumujj_2017_PtCorrUp", "WJets_mumujj_2017_PtCorrUp", 9, asymbins);
TH1D *WJets_mumujj_2017_PtCorrDown = new TH1D ("WJets_mumujj_2017_PtCorrDown", "WJets_mumujj_2017_PtCorrDown", 9, asymbins);
TH1D *WJets_eejj = new TH1D ("WJets_eejj", "WJets_eejj", 9, asymbins);
TH1D *WJets_eejj_2017_AlphaRatio = new TH1D ("WJets_eejj_2017_AlphaRatio", "WJets_eejj_2017_AlphaRatio", 9, asymbins);
TH1D *WJets_eejj_2017_AlphaRatioUp = new TH1D ("WJets_eejj_2017_AlphaRatioUp", "WJets_eejj_2017_AlphaRatioUp", 9, asymbins);
TH1D *WJets_eejj_2017_AlphaRatioDown = new TH1D ("WJets_eejj_2017_AlphaRatioDown", "WJets_eejj_2017_AlphaRatioDown", 9, asymbins);
TH1D *WJets_eejj_2017_SFUp = new TH1D ("WJets_eejj_2017_SFUp", "WJets_eejj_2017_SFUp", 9, asymbins);
TH1D *WJets_eejj_2017_SFDown = new TH1D ("WJets_eejj_2017_SFDown", "WJets_eejj_2017_SFDown", 9, asymbins);
TH1D *WJets_eejj_2017_PUUp = new TH1D ("WJets_eejj_2017_PUUp", "WJets_eejj_2017_PUUp", 9, asymbins);
TH1D *WJets_eejj_2017_PUDown = new TH1D ("WJets_eejj_2017_PUDown", "WJets_eejj_2017_PUDown", 9, asymbins);
TH1D *WJets_eejj_centralJesJer = new TH1D ("WJets_eejj_centralJesJer", "WJets_eejj_centralJesJer", 9, asymbins);
TH1D *WJets_eejj_2017_JesSFUp = new TH1D ("WJets_eejj_2017_JesSFUp", "WJets_eejj_2017_JesSFUp", 9, asymbins);
TH1D *WJets_eejj_2017_JesSFDown = new TH1D ("WJets_eejj_2017_JesSFDown", "WJets_eejj_2017_JesSFDown", 9, asymbins);
TH1D *WJets_eejj_2017_JerSFUp = new TH1D ("WJets_eejj_2017_JerSFUp", "WJets_eejj_2017_JerSFUp", 9, asymbins);
TH1D *WJets_eejj_2017_JerSFDown = new TH1D ("WJets_eejj_2017_JerSFDown", "WJets_eejj_2017_JerSFDown", 9, asymbins);
TH1D *WJets_eejj_2017_energyScaleUp = new TH1D ("WJets_eejj_2017_energyScaleUp", "WJets_eejj_2017_energyScaleUp", 9, asymbins);
TH1D *WJets_eejj_2017_energyScaleDown = new TH1D ("WJets_eejj_2017_energyScaleDown", "WJets_eejj_2017_energyScaleDown", 9, asymbins);
TH1D *WJets_eejj_2017_energySigmaUp = new TH1D ("WJets_eejj_2017_energySigmaUp", "WJets_eejj_2017_energySigmaUp", 9, asymbins);
TH1D *WJets_eejj_2017_energySigmaDown = new TH1D ("WJets_eejj_2017_energySigmaDown", "WJets_eejj_2017_energySigmaDown", 9, asymbins);

cout << a_->GetEntries() << endl;
int tot=0, muejj = 0;
double wg = 0, wg_2017_SFUp = 0, wg_2017_SFDown = 0, wg_2017_PUUp = 0, wg_2017_PUDown = 0;
int lumi = 41529;//2018: 58873 //2017: 41529 //2016: 35542
bool veto_ele = false;
double mee = 0, mmumu = 0, pu_w = 0;

TLorentzVector Muon1;
TLorentzVector Muon2;
TLorentzVector Muon1_ptCorr;
TLorentzVector Muon2_ptCorr;
TLorentzVector Electron1;
TLorentzVector Electron2;
TLorentzVector Ele1_ScaleUp;
TLorentzVector Ele1_ScaleDown;
TLorentzVector Ele2_ScaleUp;
TLorentzVector Ele2_ScaleDown;
TLorentzVector Ele1_SigmaUp;
TLorentzVector Ele1_SigmaDown;
TLorentzVector Ele2_SigmaUp;
TLorentzVector Ele2_SigmaDown;
TLorentzVector BoostJet;
TLorentzVector BoostJet_JESup;
TLorentzVector BoostJet_JESdown;
TLorentzVector BoostJet_JERup;
TLorentzVector BoostJet_JERdown;

for (Int_t i=0;i<a_->GetEntries();i++) {
 a_->GetEntry(i);
 HLT_Mu = 0; 
 tot = a_->GetEntries();
 if (i%100000 == 0) cout << i << " eventi analizzati su " << tot << endl;

 wg = lumi * lumi_wgt * lepsf_evt * PUWeight;
 wg_2017_SFUp = lumi * lumi_wgt * lepsf_evt_u * PUWeight;
 wg_2017_SFDown = lumi * lumi_wgt * lepsf_evt_d * PUWeight;
 wg_2017_PUUp = lumi * lumi_wgt * lepsf_evt * MinBiasUpWeight;
 wg_2017_PUDown = lumi * lumi_wgt * lepsf_evt * MinBiasDownWeight;
          
 if (HLT_Mu50==1 || HLT_TkMu100==1 || HLT_OldMu100==1 ) HLT_Mu = 1;
 
 if (Muon_pt->size() > 1 && numOfHighptMu==2 && numOfVetoEle == 0 && numOfBoostedJets>=1){
  Muon1.SetPtEtaPhiE(Muon_pt->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));
  Muon2.SetPtEtaPhiE(Muon_pt->at(1), Muon_eta->at(1), Muon_phi->at(1),Muon_energy->at(1));

  if (HLT_Mu == 1 && Muon_pt->at(0) > 150 && Muon_pt->at(1) > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(Muon_eta->at(1))<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1+Muon2).M() > 300 ){
   BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
   BoostJet_JESup.SetPtEtaPhiE(BoostedJet_pt->at(1), BoostedJet_eta->at(1), BoostedJet_phi->at(1),BoostedJet_energy->at(1));
   BoostJet_JESdown.SetPtEtaPhiE(BoostedJet_pt->at(2), BoostedJet_eta->at(2), BoostedJet_phi->at(2),BoostedJet_energy->at(2));
   BoostJet_JERup.SetPtEtaPhiE(BoostedJet_pt->at(3), BoostedJet_eta->at(3), BoostedJet_phi->at(3),BoostedJet_energy->at(3));
   BoostJet_JERdown.SetPtEtaPhiE(BoostedJet_pt->at(4), BoostedJet_eta->at(4), BoostedJet_phi->at(4),BoostedJet_energy->at(4));
   Muon1_ptCorr.SetPtEtaPhiE(Muon_pt_corr->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));
   Muon2_ptCorr.SetPtEtaPhiE(Muon_pt_corr->at(1), Muon_eta->at(1), Muon_phi->at(1),Muon_energy->at(1));

   WJets_mumujj->Fill((Muon1+Muon2+BoostJet).M(), wg); 
   WJets_mumujj_2017_AlphaRatio->Fill((Muon1+Muon2+BoostJet).M(), wg*1.04);
   WJets_mumujj_2017_AlphaRatioUp->Fill((Muon1+Muon2+BoostJet).M(), wg*1.06);
   WJets_mumujj_2017_AlphaRatioDown->Fill((Muon1+Muon2+BoostJet).M(), wg*1.02);
   WJets_mumujj_2017_SFUp->Fill((Muon1+Muon2+BoostJet).M(), wg_2017_SFUp);
   WJets_mumujj_2017_SFDown->Fill((Muon1+Muon2+BoostJet).M(), wg_2017_SFDown);
   WJets_mumujj_2017_PUUp->Fill((Muon1+Muon2+BoostJet).M(), wg_2017_PUUp);
   WJets_mumujj_2017_PUDown->Fill((Muon1+Muon2+BoostJet).M(), wg_2017_PUDown);
   WJets_mumujj_2017_PtCorrUp->Fill((Muon1_ptCorr+Muon2_ptCorr+BoostJet).M(), wg);
   WJets_mumujj_2017_PtCorrDown->Fill((Muon1_ptCorr+Muon2_ptCorr+BoostJet).M(), wg);
   if(centralJesJer->at(0)==1)WJets_mumujj_centralJesJer->Fill((Muon1+Muon2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)WJets_mumujj_2017_JesSFUp->Fill((Muon1+Muon2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)WJets_mumujj_2017_JesSFDown->Fill((Muon1+Muon2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)WJets_mumujj_2017_JerSFUp->Fill((Muon1+Muon2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)WJets_mumujj_2017_JerSFDown->Fill((Muon1+Muon2+BoostJet_JERdown).M(), wg);  
  }
 }
 
 if (patElectron_pt->size() > 1 && numOfHighptEle==2 && numOfLooseMu==0 && numOfBoostedJets>=1){
  Electron1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
  Electron2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energy->at(1));
  if ((HLT_Ele115 == 1 || HLT_Ele35 == 1 || HLT_Photon200 == 1) && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190 && (Electron1+Electron2).M() > 300){
   Electron1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   Electron2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energy->at(1));  
   BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
   BoostJet_JESup.SetPtEtaPhiE(BoostedJet_pt->at(1), BoostedJet_eta->at(1), BoostedJet_phi->at(1),BoostedJet_energy->at(1));
   BoostJet_JESdown.SetPtEtaPhiE(BoostedJet_pt->at(2), BoostedJet_eta->at(2), BoostedJet_phi->at(2),BoostedJet_energy->at(2));
   BoostJet_JERup.SetPtEtaPhiE(BoostedJet_pt->at(3), BoostedJet_eta->at(3), BoostedJet_phi->at(3),BoostedJet_energy->at(3));
   BoostJet_JERdown.SetPtEtaPhiE(BoostedJet_pt->at(4), BoostedJet_eta->at(4), BoostedJet_phi->at(4),BoostedJet_energy->at(4));
   Ele1_ScaleUp.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energyScaleUp->at(0));
   Ele1_ScaleDown.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energyScaleDown->at(0));
   Ele2_ScaleUp.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energyScaleUp->at(1));
   Ele2_ScaleDown.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energyScaleDown->at(1));
   Ele1_SigmaUp.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energySigmaUp->at(0));
   Ele1_SigmaDown.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energySigmaDown->at(0));
   Ele2_SigmaUp.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energySigmaUp->at(1));
   Ele2_SigmaDown.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energySigmaDown->at(1));

   WJets_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   WJets_eejj_2017_AlphaRatio->Fill((Electron1+Electron2+BoostJet).M(), wg*1.07);
   WJets_eejj_2017_AlphaRatioUp->Fill((Electron1+Electron2+BoostJet).M(), wg*1.09);
   WJets_eejj_2017_AlphaRatioDown->Fill((Electron1+Electron2+BoostJet).M(), wg*1.05);
   WJets_eejj_2017_SFUp->Fill((Electron1+Electron2+BoostJet).M(), wg_2017_SFUp);
   WJets_eejj_2017_SFDown->Fill((Electron1+Electron2+BoostJet).M(), wg_2017_SFDown);
   WJets_eejj_2017_PUUp->Fill((Electron1+Electron2+BoostJet).M(), wg_2017_PUUp);
   WJets_eejj_2017_PUDown->Fill((Electron1+Electron2+BoostJet).M(), wg_2017_PUDown);
   WJets_eejj_2017_energyScaleUp->Fill((Ele1_ScaleUp+Ele2_ScaleUp+BoostJet).M(), wg);
   WJets_eejj_2017_energyScaleDown->Fill((Ele1_ScaleDown+Ele2_ScaleDown+BoostJet).M(), wg);
   WJets_eejj_2017_energySigmaUp->Fill((Ele1_SigmaUp+Ele2_SigmaUp+BoostJet).M(), wg);
   WJets_eejj_2017_energySigmaDown->Fill((Ele1_SigmaDown+Ele2_SigmaDown+BoostJet).M(), wg);
   if(centralJesJer->at(0)==1)WJets_eejj_centralJesJer->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)WJets_eejj_2017_JesSFUp->Fill((Electron1+Electron2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)WJets_eejj_2017_JesSFDown->Fill((Electron1+Electron2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)WJets_eejj_2017_JerSFUp->Fill((Electron1+Electron2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)WJets_eejj_2017_JerSFDown->Fill((Electron1+Electron2+BoostJet_JERdown).M(), wg); 
  }
 } 
 
}

TFile *f = new TFile("SR_syst_WJets_2017.root", "RECREATE");
WJets_eejj->Write();
WJets_eejj_2017_AlphaRatio->Write();
WJets_eejj_2017_AlphaRatioUp->Write();
WJets_eejj_2017_AlphaRatioDown->Write();
WJets_eejj_2017_SFUp->Write();
WJets_eejj_2017_SFDown->Write();
WJets_eejj_2017_PUUp->Write();
WJets_eejj_2017_PUDown->Write();
WJets_eejj_centralJesJer->Write();
WJets_eejj_2017_JesSFUp->Write();
WJets_eejj_2017_JesSFDown->Write();
WJets_eejj_2017_JerSFUp->Write();
WJets_eejj_2017_JerSFDown->Write();
WJets_eejj_2017_energyScaleUp->Write();
WJets_eejj_2017_energyScaleDown->Write();
WJets_eejj_2017_energySigmaUp->Write();
WJets_eejj_2017_energySigmaDown->Write();
WJets_mumujj->Write();
WJets_mumujj_2017_AlphaRatio->Write();
WJets_mumujj_2017_AlphaRatioUp->Write();
WJets_mumujj_2017_AlphaRatioDown->Write();
WJets_mumujj_2017_SFUp->Write();
WJets_mumujj_2017_SFDown->Write();
WJets_mumujj_2017_PUUp->Write();
WJets_mumujj_2017_PUDown->Write();
WJets_mumujj_centralJesJer->Write();
WJets_mumujj_2017_JesSFUp->Write();
WJets_mumujj_2017_JesSFDown->Write();
WJets_mumujj_2017_JerSFUp->Write();
WJets_mumujj_2017_JerSFDown->Write();
WJets_mumujj_2017_PtCorrDown->Write();
WJets_mumujj_2017_PtCorrUp->Write();
f->Write();
f->Close();

}
 
