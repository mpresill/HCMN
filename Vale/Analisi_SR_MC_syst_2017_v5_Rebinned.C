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
void Analisi_SR_MC_syst_2017_v5_Rebinned(){

TChain *a_ = new TChain("BOOM");

//a_->Add("/eos/user/v/vmariani/NTuples/HN_2017/Syst_ALL_newMuonSF/TTtW_2017.root");

a_->Add("/eos/user/v/vmariani/NTuples/HN_2017/Syst_ALL_HOPE/TTtW_2017.root");
//a_->Add("/eos/user/m/mpresill/CMS/HN_Reload/rootplized_samples_2017_syst/Vale_HT_processing/TTtW_QCD_2017.root");  //this folder is for other with QCD

//inputFile

int HLT_Ele, HLT_Photon200, HLT_Ele115, HLT_Ele35, HLT_Mu, HLT_Mu50, HLT_OldMu100, HLT_TkMu50, HLT_TkMu100;
double muejj_l, emujj_l;
std:vector<double>* patElectron_pt; patElectron_pt=0;
vector<double>* patElectron_eta; patElectron_eta=0;
vector<double>* patElectron_phi; patElectron_phi=0;
vector<double>* patElectron_ecalTrkEnergyPostCorr; patElectron_ecalTrkEnergyPostCorr=0;
vector<double>* patElectron_energy; patElectron_energy=0;
vector<int>* patElectron_charge; patElectron_charge=0;
vector<double>* Muon_pt_tunePbt; Muon_pt_tunePbt=0;
vector<double>* Muon_pt_tunePbt_corr; Muon_pt_tunePbt_corr=0;
vector<double>* Muon_eta; Muon_eta=0;
vector<double>* Muon_phi; Muon_phi=0;
vector<double>* Muon_energy; Muon_energy=0;
vector<double>* Muon_charge; Muon_charge=0;
vector<double>* patElectron_energyScaleUp; patElectron_energyScaleUp=0;
vector<double>* patElectron_energyScaleDown; patElectron_energyScaleDown=0;
vector<double>* patElectron_energySigmaUp; patElectron_energySigmaUp=0;
vector<double>* patElectron_energySigmaDown; patElectron_energySigmaDown=0;
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
TBranch *a_patElectron_ecalTrkEnergyPostCorr=a_->GetBranch("patElectron_ecalTrkEnergyPostCorr");
TBranch *a_patElectron_energy=a_->GetBranch("patElectron_energy");
TBranch *a_patElectron_charge=a_->GetBranch("patElectron_charge");
TBranch *a_patElectron_energyScaleUp=a_->GetBranch("patElectron_energyScaleUp");
TBranch *a_patElectron_energyScaleDown=a_->GetBranch("patElectron_energyScaleDown");
TBranch *a_patElectron_energySigmaUp=a_->GetBranch("patElectron_energySigmaUp");
TBranch *a_patElectron_energySigmaDown=a_->GetBranch("patElectron_energySigmaDown");


TBranch *a_Muon_pt_tunePbt=a_->GetBranch("Muon_pt_tunePbt");
TBranch *a_Muon_pt_tunePbt_corr=a_->GetBranch("Muon_pt_tunePbt_corr");
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
a_HLT_Ele35_WPTight_Gsf->SetAddress(&HLT_Ele35);
a_HLT_Photon200->SetAddress(&HLT_Photon200);
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
a_patElectron_energyScaleUp->SetAddress(&patElectron_energyScaleUp);
a_patElectron_energyScaleDown->SetAddress(&patElectron_energyScaleDown);
a_patElectron_energySigmaUp->SetAddress(&patElectron_energySigmaUp);
a_patElectron_energySigmaDown->SetAddress(&patElectron_energySigmaDown);

a_Muon_pt_tunePbt->SetAddress(&Muon_pt_tunePbt);
a_Muon_pt_tunePbt_corr->SetAddress(&Muon_pt_tunePbt_corr);
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

//new bin
//const double asymbins[9] = {0,200,400,600,800,1000,1400,2000,10000};

//old bin
const double asymbins[9] = {0,200,400,600,800,1000,1400,2000,10000};

TH1D *TTtW_mumujj = new TH1D ("TTtW_mumujj", "TTtW_mumujj", 8, asymbins);
TH1D *TTtW_mumujj_2017_AlphaRatio = new TH1D ("TTtW_mumujj_2017_AlphaRatio", "TTtW_mumujj_2017_AlphaRatio", 8, asymbins);
TH1D *TTtW_mumujj_2017_AlphaRatioDown = new TH1D ("TTtW_mumujj_2017_AlphaRatioDown", "TTtW_mumujj_2017_AlphaRatioDown", 8, asymbins);
TH1D *TTtW_mumujj_2017_AlphaRatioUp = new TH1D ("TTtW_mumujj_2017_AlphaRatioUp", "TTtW_mumujj_2017_AlphaRatioUp", 8, asymbins);
TH1D *TTtW_mumujj_2017_SFUp = new TH1D ("TTtW_mumujj_2017_SFUp", "TTtW_mumujj_2017_SFUp", 8, asymbins);
TH1D *TTtW_mumujj_2017_SFDown = new TH1D ("TTtW_mumujj_2017_SFDown", "TTtW_mumujj_2017_SFDown", 8, asymbins);
TH1D *TTtW_mumujj_2017_PUUp = new TH1D ("TTtW_mumujj_2017_PUUp", "TTtW_mumujj_2017_PUUp", 8, asymbins);
TH1D *TTtW_mumujj_2017_PUDown = new TH1D ("TTtW_mumujj_2017_PUDown", "TTtW_mumujj_2017_PUDown", 8, asymbins);
TH1D *TTtW_mumujj_2017_centralJesJer = new TH1D ("TTtW_mumujj_2017_centralJesJer", "TTtW_mumujj_2017_centralJesJer", 8, asymbins);
TH1D *TTtW_mumujj_2017_JesSFUp = new TH1D ("TTtW_mumujj_2017_JesSFUp", "TTtW_mumujj_2017_JesSFUp", 8, asymbins);
TH1D *TTtW_mumujj_2017_JesSFDown = new TH1D ("TTtW_mumujj_2017_JesSFDown", "TTtW_mumujj_2017_JesSFDown", 8, asymbins);
TH1D *TTtW_mumujj_2017_JerSFUp = new TH1D ("TTtW_mumujj_2017_JerSFUp", "TTtW_mumujj_2017_JerSFUp", 8, asymbins);
TH1D *TTtW_mumujj_2017_JerSFDown = new TH1D ("TTtW_mumujj_2017_JerSFDown", "TTtW_mumujj_2017_JerSFDown", 8, asymbins);
//TH1D *TTtW_mumujj_2017_PtCorr = new TH1D ("TTtW_mumujj_2017_PtCorr", "TTtW_mumujj_2017_PtCorr", 8, asymbins);
//TH1D *TTtW_mumujj_2017_PtCorrDown = new TH1D ("TTtW_mumujj_2017_PtCorrDown", "TTtW_mumujj_2017_PtCorrDown", 8, asymbins);
//TH1D *TTtW_mumujj_2017_PtCorrUp = new TH1D ("TTtW_mumujj_2017_PtCorrUp", "TTtW_mumujj_2017_PtCorrUp", 8, asymbins);
TH1D *TTtW_mumujj_2017_PtResoUp  = new TH1D ("TTtW_mumujj_2017_PtResoUp", "TTtW_mumujj_2017_PtResoUp", 8, asymbins);
TH1D *TTtW_mumujj_2017_PtResoDown  = new TH1D ("TTtW_mumujj_2017_PtResoDown", "TTtW_mumujj_2017_PtResoDown", 8, asymbins);

TH1D *TTtW_eejj_ele1_ecalTrkEnergyPostCorr = new TH1D ("TTtW_eejj_ele1_ecalTrkEnergyPostCorr", "TTtW_eejj_ele1_ecalTrkEnergyPostCorr", 100, 0, 1000);
TH1D *TTtW_eejj_ele2_ecalTrkEnergyPostCorr = new TH1D ("TTtW_eejj_ele2_ecalTrkEnergyPostCorr", "TTtW_eejj_ele2_ecalTrkEnergyPostCorr", 100, 0, 1000);
TH1D *TTtW_eejj_ele1_energy = new TH1D ("TTtW_eejj_ele1_energy", "TTtW_eejj_ele1_energy", 100, 0, 1000);
TH1D *TTtW_eejj_ele2_energy = new TH1D ("TTtW_eejj_ele2_energy", "TTtW_eejj_ele2_energy", 100, 0, 1000);
TH1D *TTtW_eejj = new TH1D ("TTtW_eejj", "TTtW_eejj", 8, asymbins);
TH1D *TTtW_eejj_2017_AlphaRatio = new TH1D ("TTtW_eejj_2017_AlphaRatio", "TTtW_eejj_2017_AlphaRatio", 8, asymbins);
TH1D *TTtW_eejj_2017_AlphaRatioDown = new TH1D ("TTtW_eejj_2017_AlphaRatioDown", "TTtW_eejj_2017_AlphaRatioDown", 8, asymbins);
TH1D *TTtW_eejj_2017_AlphaRatioUp = new TH1D ("TTtW_eejj_2017_AlphaRatioUp", "TTtW_eejj_2017_AlphaRatioUp", 8, asymbins);
TH1D *TTtW_eejj_2017_SFUp = new TH1D ("TTtW_eejj_2017_SFUp", "TTtW_eejj_2017_SFUp", 8, asymbins);
TH1D *TTtW_eejj_2017_SFDown = new TH1D ("TTtW_eejj_2017_SFDown", "TTtW_eejj_2017_SFDown", 8, asymbins);
TH1D *TTtW_eejj_2017_PUUp = new TH1D ("TTtW_eejj_2017_PUUp", "TTtW_eejj_2017_PUUp", 8, asymbins);
TH1D *TTtW_eejj_2017_PUDown = new TH1D ("TTtW_eejj_2017_PUDown", "TTtW_eejj_2017_PUDown", 8, asymbins);
TH1D *TTtW_eejj_2017_centralJesJer = new TH1D ("TTtW_eejj_2017_centralJesJer", "TTtW_eejj_2017_centralJesJer", 8, asymbins);
TH1D *TTtW_eejj_2017_JesSFUp = new TH1D ("TTtW_eejj_2017_JesSFUp", "TTtW_eejj_2017_JesSFUp", 8, asymbins);
TH1D *TTtW_eejj_2017_JesSFDown = new TH1D ("TTtW_eejj_2017_JesSFDown", "TTtW_eejj_2017_JesSFDown", 8, asymbins);
TH1D *TTtW_eejj_2017_JerSFUp = new TH1D ("TTtW_eejj_2017_JerSFUp", "TTtW_eejj_2017_JerSFUp", 8, asymbins);
TH1D *TTtW_eejj_2017_JerSFDown = new TH1D ("TTtW_eejj_2017_JerSFDown", "TTtW_eejj_2017_JerSFDown", 8, asymbins);
TH1D *TTtW_eejj_energyScaleUp = new TH1D ("TTtW_eejj_energyScaleUp", "TTtW_eejj_energyScaleUp", 8, asymbins);
TH1D *TTtW_eejj_energyScaleDown = new TH1D ("TTtW_eejj_energyScaleDown", "TTtW_eejj_energyScaleDown", 8, asymbins);
TH1D *TTtW_eejj_2017_energySigmaUp = new TH1D ("TTtW_eejj_2017_energySigmaUp", "TTtW_eejj_2017_energySigmaUp", 8, asymbins);
TH1D *TTtW_eejj_2017_energySigmaDown = new TH1D ("TTtW_eejj_2017_energySigmaDown", "TTtW_eejj_2017_energySigmaDown", 8, asymbins);

//PDF uncertaintes for signal samples
TH1D *TTtW_mumujj_PDFUp = new TH1D ("TTtW_mumujj_PDFUp", "TTtW_mumujj_PDFUp", 8, asymbins);   //PDF
TH1D *TTtW_mumujj_PDFDown = new TH1D ("TTtW_mumujj_PDFDown", "TTtW_mumujj_PDFDown", 8, asymbins); //PDF
TH1D *TTtW_eejj_PDFUp = new TH1D ("TTtW_eejj_PDFUp", "TTtW_eejj_PDFUp", 8, asymbins); //PDF
TH1D *TTtW_eejj_PDFDown = new TH1D ("TTtW_eejj_PDFDown", "TTtW_eejj_PDFDown", 8, asymbins); //PDF

//DY CR Zpeak (mll in 60-120 GeV)
TH1D *TTtW_ZpeakMll_mumujj = new TH1D ("TTtW_ZpeakMll_mumujj", "TTtW_ZpeakMll_mumujj", 60,60,120);
TH1D *TTtW_Zpeak_mumujj = new TH1D ("TTtW_Zpeak_mumujj", "TTtW_Zpeak_mumujj", 8, asymbins);
TH1D *TTtW_ZpeakMll_eejj = new TH1D ("TTtW_ZpeakMll_eejj", "TTtW_ZpeakMll_eejj", 60,60,120);
TH1D *TTtW_Zpeak_eejj = new TH1D ("TTtW_Zpeak_eejj", "TTtW_Zpeak_eejj", 8, asymbins);
TH1D *TTtW_Zpeak_eejj_ele1_ecalTrkEnergyPostCorr = new TH1D ("TTtW_Zpeak_eejj_ele1_ecalTrkEnergyPostCorr", "TTtW_Zpeak_eejj_ele1_ecalTrkEnergyPostCorr", 100, 0, 1000);
TH1D *TTtW_Zpeak_eejj_ele2_ecalTrkEnergyPostCorr = new TH1D ("TTtW_Zpeak_eejj_ele2_ecalTrkEnergyPostCorr", "TTtW_Zpeak_eejj_ele2_ecalTrkEnergyPostCorr", 100, 0, 1000);
TH1D *TTtW_Zpeak_eejj_ele1_energy = new TH1D ("TTtW_Zpeak_eejj_ele1_energy", "TTtW_Zpeak_eejj_ele1_energy", 100, 0, 1000);
TH1D *TTtW_Zpeak_eejj_ele2_energy = new TH1D ("TTtW_Zpeak_eejj_ele2_energy", "TTtW_Zpeak_eejj_ele2_energy", 100, 0, 1000);

//DY CR (mll in 150-300 GeV)
TH1D *TTtW_DYcr_mumujj = new TH1D ("TTtW_DYcr_mumujj", "TTtW_DYcr_mumujj", 8, asymbins);
TH1D *TTtW_DYcr_mumujj_2017_AlphaRatio = new TH1D ("TTtW_DYcr_mumujj_2017_AlphaRatio", "TTtW_DYcr_mumujj_2017_AlphaRatio", 8, asymbins);
TH1D *TTtW_DYcr_mumujj_2017_AlphaRatioUp = new TH1D ("TTtW_DYcr_mumujj_2017_AlphaRatioUp", "TTtW_DYcr_mumujj_2017_AlphaRatioUp", 8, asymbins);
TH1D *TTtW_DYcr_mumujj_2017_AlphaRatioDown = new TH1D ("TTtW_DYcr_mumujj_2017_AlphaRatioDown", "TTtW_DYcr_mumujj_2017_AlphaRatioDown", 8, asymbins);
TH1D *TTtW_DYcr_mumujj_2017_SFUp = new TH1D ("TTtW_DYcr_mumujj_2017_SFUp", "TTtW_DYcr_mumujj_2017_SFUp", 8, asymbins);
TH1D *TTtW_DYcr_mumujj_2017_SFDown = new TH1D ("TTtW_DYcr_mumujj_2017_SFDown", "TTtW_DYcr_mumujj_2017_SFDown", 8, asymbins);
TH1D *TTtW_DYcr_mumujj_2017_PUUp = new TH1D ("TTtW_DYcr_mumujj_2017_PUUp", "TTtW_DYcr_mumujj_2017_PUUp", 8, asymbins);
TH1D *TTtW_DYcr_mumujj_2017_PUDown = new TH1D ("TTtW_DYcr_mumujj_2017_PUDown", "TTtW_DYcr_mumujj_2017_PUDown", 8, asymbins);
TH1D *TTtW_DYcr_mumujj_centralJesJer = new TH1D ("TTtW_DYcr_mumujj_centralJesJer", "TTtW_DYcr_mumujj_centralJesJer", 8, asymbins);
TH1D *TTtW_DYcr_mumujj_2017_JesSFUp = new TH1D ("TTtW_DYcr_mumujj_2017_JesSFUp", "TTtW_DYcr_mumujj_2017_JesSFUp", 8, asymbins);
TH1D *TTtW_DYcr_mumujj_2017_JesSFDown = new TH1D ("TTtW_DYcr_mumujj_2017_JesSFDown", "TTtW_DYcr_mumujj_2017_JesSFDown", 8, asymbins);
TH1D *TTtW_DYcr_mumujj_2017_JerSFUp = new TH1D ("TTtW_DYcr_mumujj_2017_JerSFUp", "TTtW_DYcr_mumujj_2017_JerSFUp", 8, asymbins);
TH1D *TTtW_DYcr_mumujj_2017_JerSFDown = new TH1D ("TTtW_DYcr_mumujj_2017_JerSFDown", "TTtW_DYcr_mumujj_2017_JerSFDown", 8, asymbins);
//TH1D *TTtW_DYcr_mumujj_2017_PtCorrUp = new TH1D ("TTtW_DYcr_mumujj_2017_PtCorrUp", "TTtW_DYcr_mumujj_2017_PtCorrUp", 8, asymbins);
//TH1D *TTtW_DYcr_mumujj_2017_PtCorrDown = new TH1D ("TTtW_DYcr_mumujj_2017_PtCorrDown", "TTtW_DYcr_mumujj_2017_PtCorrDown", 8, asymbins);
TH1D *TTtW_DYcr_mumujj_2017_PtResoUp  = new TH1D ("TTtW_DYcr_mumujj_2017_PtResoUp", "TTtW_DYcr_mumujj_2017_PtResoUp", 8, asymbins);
TH1D *TTtW_DYcr_mumujj_2017_PtResoDown  = new TH1D ("TTtW_DYcr_mumujj_2017_PtResoDown", "TTtW_DYcr_mumujj_2017_PtResoDown", 8, asymbins);
TH1D *TTtW_DYcr_eejj_ele1_ecalTrkEnergyPostCorr = new TH1D ("TTtW_DYcr_eejj_ele1_ecalTrkEnergyPostCorr", "TTtW_DYcr_eejj_ele1_ecalTrkEnergyPostCorr", 100, 0, 1000);
TH1D *TTtW_DYcr_eejj_ele2_ecalTrkEnergyPostCorr = new TH1D ("TTtW_DYcr_eejj_ele2_ecalTrkEnergyPostCorr", "TTtW_DYcr_eejj_ele2_ecalTrkEnergyPostCorr", 100, 0, 1000);
TH1D *TTtW_DYcr_eejj_ele1_energy = new TH1D ("TTtW_DYcr_eejj_ele1_energy", "TTtW_DYcr_eejj_ele1_energy", 100, 0, 1000);
TH1D *TTtW_DYcr_eejj_ele2_energy = new TH1D ("TTtW_DYcr_eejj_ele2_energy", "TTtW_DYcr_eejj_ele2_energy", 100, 0, 1000);
TH1D *TTtW_DYcr_eejj = new TH1D ("TTtW_DYcr_eejj", "TTtW_DYcr_eejj", 8, asymbins);
TH1D *TTtW_DYcr_eejj_2017_AlphaRatio = new TH1D ("TTtW_DYcr_eejj_2017_AlphaRatio", "TTtW_DYcr_eejj_2017_AlphaRatio", 8, asymbins);
TH1D *TTtW_DYcr_eejj_2017_AlphaRatioUp = new TH1D ("TTtW_DYcr_eejj_2017_AlphaRatioUp", "TTtW_DYcr_eejj_2017_AlphaRatioUp", 8, asymbins);
TH1D *TTtW_DYcr_eejj_2017_AlphaRatioDown = new TH1D ("TTtW_DYcr_eejj_2017_AlphaRatioDown", "TTtW_DYcr_eejj_2017_AlphaRatioDown", 8, asymbins);
TH1D *TTtW_DYcr_eejj_2017_SFUp = new TH1D ("TTtW_DYcr_eejj_2017_SFUp", "TTtW_DYcr_eejj_2017_SFUp", 8, asymbins);
TH1D *TTtW_DYcr_eejj_2017_SFDown = new TH1D ("TTtW_DYcr_eejj_2017_SFDown", "TTtW_DYcr_eejj_2017_SFDown", 8, asymbins);
TH1D *TTtW_DYcr_eejj_2017_PUUp = new TH1D ("TTtW_DYcr_eejj_2017_PUUp", "TTtW_DYcr_eejj_2017_PUUp", 8, asymbins);
TH1D *TTtW_DYcr_eejj_2017_PUDown = new TH1D ("TTtW_DYcr_eejj_2017_PUDown", "TTtW_DYcr_eejj_2017_PUDown", 8, asymbins);
TH1D *TTtW_DYcr_eejj_centralJesJer = new TH1D ("TTtW_DYcr_eejj_centralJesJer", "TTtW_DYcr_eejj_centralJesJer", 8, asymbins);
TH1D *TTtW_DYcr_eejj_2017_JesSFUp = new TH1D ("TTtW_DYcr_eejj_2017_JesSFUp", "TTtW_DYcr_eejj_2017_JesSFUp", 8, asymbins);
TH1D *TTtW_DYcr_eejj_2017_JesSFDown = new TH1D ("TTtW_DYcr_eejj_2017_JesSFDown", "TTtW_DYcr_eejj_2017_JesSFDown", 8, asymbins);
TH1D *TTtW_DYcr_eejj_2017_JerSFUp = new TH1D ("TTtW_DYcr_eejj_2017_JerSFUp", "TTtW_DYcr_eejj_2017_JerSFUp", 8, asymbins);
TH1D *TTtW_DYcr_eejj_2017_JerSFDown = new TH1D ("TTtW_DYcr_eejj_2017_JerSFDown", "TTtW_DYcr_eejj_2017_JerSFDown", 8, asymbins);
TH1D *TTtW_DYcr_eejj_energyScaleUp = new TH1D ("TTtW_DYcr_eejj_energyScaleUp", "TTtW_DYcr_eejj_energyScaleUp", 8, asymbins);
TH1D *TTtW_DYcr_eejj_energyScaleDown = new TH1D ("TTtW_DYcr_eejj_energyScaleDown", "TTtW_DYcr_eejj_energyScaleDown", 8, asymbins);
TH1D *TTtW_DYcr_eejj_2017_energySigmaUp = new TH1D ("TTtW_DYcr_eejj_2017_energySigmaUp", "TTtW_DYcr_eejj_2017_energySigmaUp", 8, asymbins);
TH1D *TTtW_DYcr_eejj_2017_energySigmaDown = new TH1D ("TTtW_DYcr_eejj_2017_energySigmaDown", "TTtW_DYcr_eejj_2017_energySigmaDown", 8, asymbins);

//TTtW cr
const double asymbins2[7] = {300,350,400,450,500,700,2000};
TH1D *M_leplepJ_TTtWcr = new TH1D ("M_leplepJ_TTtWcr", "M_leplepJ_TTtWcr", 8, asymbins);

TH1D *TTtW_TTtWcr_ll = new TH1D ("TTtW_TTtWcr_ll", "TTtW_TTtWcr_ll", 6, asymbins2);
TH1D *TTtW_TTtWcr_ll_2017_AlphaRatio = new TH1D ("TTtW_TTtWcr_ll_2017_AlphaRatio", "TTtW_TTtWcr_ll_2017_AlphaRatio", 6, asymbins2);
TH1D *TTtW_TTtWcr_ll_2017_AlphaRatioUp = new TH1D ("TTtW_TTtWcr_ll_2017_AlphaRatioUp", "TTtW_TTtWcr_ll_2017_AlphaRatioUp", 6, asymbins2);
TH1D *TTtW_TTtWcr_ll_2017_AlphaRatioDown = new TH1D ("TTtW_TTtWcr_ll_2017_AlphaRatioDown", "TTtW_TTtWcr_ll_2017_AlphaRatioDown", 6, asymbins2);
TH1D *TTtW_TTtWcr_ll_2017_SFUp = new TH1D ("TTtW_TTtWcr_ll_2017_SFUp", "TTtW_TTtWcr_ll_2017_SFUp", 6, asymbins2);
TH1D *TTtW_TTtWcr_ll_2017_SFDown = new TH1D ("TTtW_TTtWcr_ll_2017_SFDown", "TTtW_TTtWcr_ll_2017_SFDown", 6, asymbins2);
TH1D *TTtW_TTtWcr_ll_2017_PUUp = new TH1D ("TTtW_TTtWcr_ll_2017_PUUp", "TTtW_TTtWcr_ll_2017_PUUp", 6, asymbins2);
TH1D *TTtW_TTtWcr_ll_2017_PUDown = new TH1D ("TTtW_TTtWcr_ll_2017_PUDown", "TTtW_TTtWcr_ll_2017_PUDown", 6, asymbins2);
TH1D *TTtW_TTtWcr_ll_energyScaleUp = new TH1D ("TTtW_TTtWcr_ll_energyScaleUp", "TTtW_TTtWcr_ll_energyScaleUp", 6, asymbins2);
TH1D *TTtW_TTtWcr_ll_energyScaleDown = new TH1D ("TTtW_TTtWcr_ll_energyScaleDown", "TTtW_TTtWcr_ll_energyScaleDown", 6, asymbins2);
TH1D *TTtW_TTtWcr_ll_2017_energySigmaUp = new TH1D ("TTtW_TTtWcr_ll_2017_energySigmaUp", "TTtW_TTtWcr_ll_2017_energySigmaUp", 6, asymbins2);
TH1D *TTtW_TTtWcr_ll_2017_energySigmaDown = new TH1D ("TTtW_TTtWcr_ll_2017_energySigmaDown", "TTtW_TTtWcr_ll_2017_energySigmaDown", 6, asymbins2);
TH1D *TTtW_TTtWcr_ll_centralJesJer = new TH1D ("TTtW_TTtWcr_ll_centralJesJer", "TTtW_TTtWcr_ll_centralJesJer", 6, asymbins2);
TH1D *TTtW_TTtWcr_ll_2017_JesSFUp = new TH1D ("TTtW_TTtWcr_ll_2017_JesSFUp", "TTtW_TTtWcr_ll_2017_JesSFUp", 6, asymbins2);
TH1D *TTtW_TTtWcr_ll_2017_JesSFDown = new TH1D ("TTtW_TTtWcr_ll_2017_JesSFDown", "TTtW_TTtWcr_ll_2017_JesSFDown", 6, asymbins2);
TH1D *TTtW_TTtWcr_ll_2017_JerSFUp = new TH1D ("TTtW_TTtWcr_ll_2017_JerSFUp", "TTtW_TTtWcr_ll_2017_JerSFUp", 6, asymbins2);
TH1D *TTtW_TTtWcr_ll_2017_JerSFDown = new TH1D ("TTtW_TTtWcr_ll_2017_JerSFDown", "TTtW_TTtWcr_ll_2017_JerSFDown", 6, asymbins2);
TH1D *TTtW_TTtWcr_ll_2017_PtResoUp = new TH1D("TTtW_TTtWcr_ll_2017_PtResoUp", "TTtW_TTtWcr_ll_2017_PtResoUp", 6, asymbins2);
TH1D *TTtW_TTtWcr_ll_2017_PtResoDown = new TH1D("TTtW_TTtWcr_ll_2017_PtResoDown", "TTtW_TTtWcr_ll_2017_PtResoDown", 6, asymbins2);

/*M(emuJ)*/
TH1D *TTtW_TTtWcr_llJ = new TH1D ("TTtW_TTtWcr_llJ", "TTtW_TTtWcr_llJ", 8, asymbins);
TH1D *TTtW_TTtWcr_llJ_2017_AlphaRatio = new TH1D ("TTtW_TTtWcr_llJ_2017_AlphaRatio", "TTtW_TTtWcr_llJ_2017_AlphaRatio", 8, asymbins);
TH1D *TTtW_TTtWcr_llJ_2017_AlphaRatioUp = new TH1D ("TTtW_TTtWcr_llJ_2017_AlphaRatioUp", "TTtW_TTtWcr_llJ_2017_AlphaRatioUp", 8, asymbins);
TH1D *TTtW_TTtWcr_llJ_2017_AlphaRatioDown = new TH1D ("TTtW_TTtWcr_llJ_2017_AlphaRatioDown", "TTtW_TTtWcr_llJ_2017_AlphaRatioDown", 8, asymbins);
TH1D *TTtW_TTtWcr_llJ_2017_SFUp = new TH1D ("TTtW_TTtWcr_llJ_2017_SFUp", "TTtW_TTtWcr_llJ_2017_SFUp", 8, asymbins);
TH1D *TTtW_TTtWcr_llJ_2017_SFDown = new TH1D ("TTtW_TTtWcr_llJ_2017_SFDown", "TTtW_TTtWcr_llJ_2017_SFDown", 8, asymbins);
TH1D *TTtW_TTtWcr_llJ_2017_PUUp = new TH1D ("TTtW_TTtWcr_llJ_2017_PUUp", "TTtW_TTtWcr_llJ_2017_PUUp", 8, asymbins);
TH1D *TTtW_TTtWcr_llJ_2017_PUDown = new TH1D ("TTtW_TTtWcr_llJ_2017_PUDown", "TTtW_TTtWcr_llJ_2017_PUDown", 8, asymbins);
TH1D *TTtW_TTtWcr_llJ_2017_PtResoUp = new TH1D ("TTtW_TTtWcr_llJ_2017_PtResoUp", "TTtW_TTtWcr_llJ_2017_PtResoUp", 8, asymbins);
TH1D *TTtW_TTtWcr_llJ_2017_PtResoDown = new TH1D ("TTtW_TTtWcr_llJ_2017_PtResoDown", "TTtW_TTtWcr_llJ_2017_PtResoDown", 8, asymbins);
TH1D *TTtW_TTtWcr_llJ_energyScaleUp = new TH1D ("TTtW_TTtWcr_llJ_energyScaleUp", "TTtW_TTtWcr_llJ_energyScaleUp", 8, asymbins);
TH1D *TTtW_TTtWcr_llJ_energyScaleDown = new TH1D ("TTtW_TTtWcr_llJ_energyScaleDown", "TTtW_TTtWcr_llJ_energyScaleDown", 8, asymbins);
TH1D *TTtW_TTtWcr_llJ_2017_energySigmaUp = new TH1D ("TTtW_TTtWcr_llJ_2017_energySigmaUp", "TTtW_TTtWcr_llJ_2017_energySigmaUp", 8, asymbins);
TH1D *TTtW_TTtWcr_llJ_2017_energySigmaDown = new TH1D ("TTtW_TTtWcr_llJ_2017_energySigmaDown", "TTtW_TTtWcr_llJ_2017_energySigmaDown", 8, asymbins);
TH1D *TTtW_TTtWcr_llJ_centralJesJer = new TH1D ("TTtW_TTtWcr_llJ_centralJesJer", "TTtW_TTtWcr_llJ_centralJesJer", 8, asymbins);
TH1D *TTtW_TTtWcr_llJ_2017_JesSFUp = new TH1D ("TTtW_TTtWcr_llJ_2017_JesSFUp", "TTtW_TTtWcr_llJ_2017_JesSFUp", 8, asymbins);
TH1D *TTtW_TTtWcr_llJ_2017_JesSFDown = new TH1D ("TTtW_TTtWcr_llJ_2017_JesSFDown", "TTtW_TTtWcr_llJ_2017_JesSFDown", 8, asymbins);
TH1D *TTtW_TTtWcr_llJ_2017_JerSFUp = new TH1D ("TTtW_TTtWcr_llJ_2017_JerSFUp", "TTtW_TTtWcr_llJ_2017_JerSFUp", 8, asymbins);
TH1D *TTtW_TTtWcr_llJ_2017_JerSFDown = new TH1D ("TTtW_TTtWcr_llJ_2017_JerSFDown", "TTtW_TTtWcr_llJ_2017_JerSFDown", 8, asymbins);

cout << a_->GetEntries() << endl;
int tot=0, muejj = 0;
double wg = 0, wg_SFu = 0, wg_SFd = 0, wg_PUu = 0, wg_PUd = 0;
int lumi = 41529;//2017: 58873 //2017: 41529 //2017: 35542
bool veto_ele = false;
double mee = 0, mmumu = 0, pu_w = 0;
double MmumuJ = 0, MmumuJ_JESup = 0, MmumuJ_JESdown = 0,  MmumuJ_JERup = 0, MmumuJ_JERdown = 0; /*this is for smearing*/


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
TLorentzVector Muon1_PtResoUp;
TLorentzVector Muon1_PtResoDown;
TLorentzVector Muon2_PtResoUp;
TLorentzVector Muon2_PtResoDown;

/*this is for the patch on lepf sf systematics*/
double elesf1=0, elesf_d1=0, elesf_d2=0; 
double elesf2=0, elesf_u1=0, elesf_u2=0; 
double energy_corr0 = 0, energy_corr1 = 0;

for (Int_t i=0;i<a_->GetEntries();i++) {
 a_->GetEntry(i);
 HLT_Mu = 0; 
 tot = a_->GetEntries();
 if (i%100000 == 0) cout << i << " eventi analizzati su " << tot << endl;

 HLT_Mu = 0; HLT_Ele = 0;

 wg = lumi * lumi_wgt * lepsf_evt * PUWeight;
 wg_SFu = lumi * lumi_wgt * lepsf_evt_u * PUWeight;
 wg_SFd = lumi * lumi_wgt * lepsf_evt_d * PUWeight;
 wg_PUu = lumi * lumi_wgt * lepsf_evt * MinBiasUpWeight;
 wg_PUd = lumi * lumi_wgt * lepsf_evt * MinBiasDownWeight;
          
 if (HLT_Mu50==1 || HLT_TkMu100==1 || HLT_OldMu100==1 ) HLT_Mu = 1;
 if (HLT_Photon200 == 1 || HLT_Ele35==1 || HLT_Ele115 == 1) HLT_Ele = 1;

  if (Muon_pt_tunePbt->size() > 1 && numOfHighptMu==2 && numOfVetoEle == 0 && numOfBoostedJets>=1){

   Muon1.SetPtEtaPhiE(Muon_pt_tunePbt->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));
   Muon2.SetPtEtaPhiE(Muon_pt_tunePbt->at(1), Muon_eta->at(1), Muon_phi->at(1),Muon_energy->at(1));
        /* BE CAREFUL ON THE WAY TO COMPUTE THE INVARIANT MASS!*/
    Muon1_PtResoUp.SetPtEtaPhiM((Muon_pt_tunePbt->at(0)+0.1*Muon_pt_tunePbt->at(0)), Muon_eta->at(0), Muon_phi->at(0),0.1056583745 );
    Muon2_PtResoUp.SetPtEtaPhiM((Muon_pt_tunePbt->at(1)+0.1*Muon_pt_tunePbt->at(1)), Muon_eta->at(1), Muon_phi->at(1),0.1056583745 );
    Muon1_PtResoDown.SetPtEtaPhiM((Muon_pt_tunePbt->at(0)-0.1*Muon_pt_tunePbt->at(0)), Muon_eta->at(0), Muon_phi->at(0),0.1056583745 );
    Muon2_PtResoDown.SetPtEtaPhiM((Muon_pt_tunePbt->at(1)-0.1*Muon_pt_tunePbt->at(1)), Muon_eta->at(1), Muon_phi->at(1),0.1056583745 );


   if (HLT_Mu == 1 && Muon_pt_tunePbt->at(0) > 150 && Muon_pt_tunePbt->at(1) > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(Muon_eta->at(1))<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1+Muon2).M()  > 300 ){

    BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
    BoostJet_JESup.SetPtEtaPhiE(BoostedJet_pt->at(1), BoostedJet_eta->at(1), BoostedJet_phi->at(1),BoostedJet_energy->at(1));
    BoostJet_JESdown.SetPtEtaPhiE(BoostedJet_pt->at(2), BoostedJet_eta->at(2), BoostedJet_phi->at(2),BoostedJet_energy->at(2));
    BoostJet_JERup.SetPtEtaPhiE(BoostedJet_pt->at(3), BoostedJet_eta->at(3), BoostedJet_phi->at(3),BoostedJet_energy->at(3));
    BoostJet_JERdown.SetPtEtaPhiE(BoostedJet_pt->at(4), BoostedJet_eta->at(4), BoostedJet_phi->at(4),BoostedJet_energy->at(4));

  /*muon resolution smearing*/
    MmumuJ= (Muon1+Muon2+BoostJet).M(); 
    MmumuJ_JESup= (Muon1+Muon2+BoostJet_JESup).M(); 
    MmumuJ_JESdown= (Muon1+Muon2+BoostJet_JESdown).M(); 
    MmumuJ_JERup= (Muon1+Muon2+BoostJet_JERup).M(); 
    MmumuJ_JERdown= (Muon1+Muon2+BoostJet_JERdown).M(); 
    if( fabs(Muon_eta->at(0)) > 1.2  || fabs(Muon_eta->at(1)) > 1.2){
    MmumuJ = gRandom->Gaus(MmumuJ,0.15);
    MmumuJ_JESup = gRandom->Gaus(MmumuJ_JESup,0.15);
    MmumuJ_JESdown = gRandom->Gaus(MmumuJ_JESdown,0.15);
    MmumuJ_JERup = gRandom->Gaus(MmumuJ_JERup,0.15);
    MmumuJ_JERdown = gRandom->Gaus(MmumuJ_JERdown,0.15);
    }
    /**/
  
   TTtW_mumujj->Fill(MmumuJ, wg);
   TTtW_mumujj_2017_AlphaRatio->Fill(MmumuJ, wg);
   TTtW_mumujj_2017_AlphaRatioUp->Fill(MmumuJ, wg);
   TTtW_mumujj_2017_AlphaRatioDown->Fill(MmumuJ, wg);
   TTtW_mumujj_2017_SFUp->Fill(MmumuJ, wg_SFu);
   TTtW_mumujj_2017_SFDown->Fill(MmumuJ, wg_SFd);
   TTtW_mumujj_2017_PUUp->Fill(MmumuJ, wg_PUu);
   TTtW_mumujj_2017_PUDown->Fill(MmumuJ, wg_PUd);
   TTtW_mumujj_2017_PtResoUp->Fill((Muon1_PtResoUp+Muon2_PtResoUp+BoostJet).M(), wg);
   TTtW_mumujj_2017_PtResoDown->Fill((Muon1_PtResoDown+Muon2_PtResoDown+BoostJet).M(), wg);
  
   if(centralJesJer->at(0)==1)TTtW_mumujj_2017_centralJesJer->Fill(MmumuJ, wg);
   if(JesSFup->at(1)==1)TTtW_mumujj_2017_JesSFUp->Fill(MmumuJ_JESup, wg);
   if(JesSFdown->at(2)==1)TTtW_mumujj_2017_JesSFDown->Fill(MmumuJ_JESdown, wg);
   if(JerSFup->at(3)==1)TTtW_mumujj_2017_JerSFUp->Fill(MmumuJ_JERup, wg);
   if(JerSFdown->at(4)==1)TTtW_mumujj_2017_JerSFDown->Fill(MmumuJ_JERdown, wg);
  
  TTtW_mumujj_PDFUp->Fill(MmumuJ, wg*1.7);      //comment for bkgs                 
  TTtW_mumujj_PDFDown->Fill(MmumuJ, wg*0.3);  //comment for bkgs

  }

    //Zpeak DY cr Mll in 60-120 GeV
    if (HLT_Mu == 1 && Muon_pt_tunePbt->at(0) > 150 && Muon_pt_tunePbt->at(1) > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(Muon_eta->at(1))<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1+Muon2).M() > 60 && (Muon1+Muon2).M() < 120 ){
      BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
      TTtW_ZpeakMll_mumujj->Fill((Muon1+Muon2).M(), wg); 
      /*muon resolution smearing*/
      MmumuJ= (Muon1+Muon2+BoostJet).M(); 
      MmumuJ_JESup= (Muon1+Muon2+BoostJet_JESup).M(); 
      MmumuJ_JESdown= (Muon1+Muon2+BoostJet_JESdown).M(); 
      MmumuJ_JERup= (Muon1+Muon2+BoostJet_JERup).M(); 
      MmumuJ_JERdown= (Muon1+Muon2+BoostJet_JERdown).M(); 
      if( fabs(Muon_eta->at(0)) > 1.2  || fabs(Muon_eta->at(1)) > 1.2){
      MmumuJ = gRandom->Gaus(MmumuJ,0.15);
      MmumuJ_JESup = gRandom->Gaus(MmumuJ_JESup,0.15);
      MmumuJ_JESdown = gRandom->Gaus(MmumuJ_JESdown,0.15);
      MmumuJ_JERup = gRandom->Gaus(MmumuJ_JERup,0.15);
      MmumuJ_JERdown = gRandom->Gaus(MmumuJ_JERdown,0.15);
      }
      /**/
      TTtW_Zpeak_mumujj->Fill(MmumuJ, wg); 
    }

    //DY cr Mll in 150-300 GeV
    if (HLT_Mu == 1 && Muon_pt_tunePbt->at(0) > 150 && Muon_pt_tunePbt->at(1) > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(Muon_eta->at(1))<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1+Muon2).M() > 150 && (Muon1+Muon2).M() < 300 ){
    BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
    BoostJet_JESup.SetPtEtaPhiE(BoostedJet_pt->at(1), BoostedJet_eta->at(1), BoostedJet_phi->at(1),BoostedJet_energy->at(1));
    BoostJet_JESdown.SetPtEtaPhiE(BoostedJet_pt->at(2), BoostedJet_eta->at(2), BoostedJet_phi->at(2),BoostedJet_energy->at(2));
    BoostJet_JERup.SetPtEtaPhiE(BoostedJet_pt->at(3), BoostedJet_eta->at(3), BoostedJet_phi->at(3),BoostedJet_energy->at(3));
    BoostJet_JERdown.SetPtEtaPhiE(BoostedJet_pt->at(4), BoostedJet_eta->at(4), BoostedJet_phi->at(4),BoostedJet_energy->at(4));
    /*muon resolution smearing*/
    MmumuJ= (Muon1+Muon2+BoostJet).M(); 
    MmumuJ_JESup= (Muon1+Muon2+BoostJet_JESup).M(); 
    MmumuJ_JESdown= (Muon1+Muon2+BoostJet_JESdown).M(); 
    MmumuJ_JERup= (Muon1+Muon2+BoostJet_JERup).M(); 
    MmumuJ_JERdown= (Muon1+Muon2+BoostJet_JERdown).M(); 
    if( fabs(Muon_eta->at(0)) > 1.2  || fabs(Muon_eta->at(1)) > 1.2){
    MmumuJ = gRandom->Gaus(MmumuJ,0.15);
    MmumuJ_JESup = gRandom->Gaus(MmumuJ_JESup,0.15);
    MmumuJ_JESdown = gRandom->Gaus(MmumuJ_JESdown,0.15);
    MmumuJ_JERup = gRandom->Gaus(MmumuJ_JERup,0.15);
    MmumuJ_JERdown = gRandom->Gaus(MmumuJ_JERdown,0.15);
    }
    /**/
    TTtW_DYcr_mumujj->Fill(MmumuJ, wg); 
    TTtW_DYcr_mumujj_2017_AlphaRatio->Fill(MmumuJ, wg);
    TTtW_DYcr_mumujj_2017_AlphaRatioUp->Fill(MmumuJ, wg);
    TTtW_DYcr_mumujj_2017_AlphaRatioDown->Fill(MmumuJ, wg);
    TTtW_DYcr_mumujj_2017_SFUp->Fill(MmumuJ, wg_SFu);
    TTtW_DYcr_mumujj_2017_SFDown->Fill(MmumuJ, wg_SFd);
    TTtW_DYcr_mumujj_2017_PUUp->Fill(MmumuJ, wg_PUu);
    TTtW_DYcr_mumujj_2017_PUDown->Fill(MmumuJ, wg_PUd);
    TTtW_DYcr_mumujj_2017_PtResoUp->Fill((Muon1_PtResoUp+Muon2_PtResoUp+BoostJet).M(), wg);
    TTtW_DYcr_mumujj_2017_PtResoDown->Fill((Muon1_PtResoDown+Muon2_PtResoDown+BoostJet).M(), wg);
  
    if(centralJesJer->at(0)==1)TTtW_DYcr_mumujj_centralJesJer->Fill((Muon1+Muon2+BoostJet).M(), wg);
    if(JesSFup->at(1)==1)TTtW_DYcr_mumujj_2017_JesSFUp->Fill(MmumuJ_JESup, wg);
    if(JesSFdown->at(2)==1)TTtW_DYcr_mumujj_2017_JesSFDown->Fill(MmumuJ_JESdown, wg);
    if(JerSFup->at(3)==1)TTtW_DYcr_mumujj_2017_JerSFUp->Fill(MmumuJ_JERup, wg);
    if(JerSFdown->at(4)==1)TTtW_DYcr_mumujj_2017_JerSFDown->Fill(MmumuJ_JERdown, wg);  
    }

 }

  if (patElectron_pt->size() > 1 && numOfHighptEle==2 && numOfLooseMu==0 && numOfBoostedJets>=1){

   Electron1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   Electron2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energy->at(1));

   // energy correction  

   energy_corr0= patElectron_ecalTrkEnergyPostCorr->at(0) / patElectron_energy->at(0) ;
   energy_corr1= patElectron_ecalTrkEnergyPostCorr->at(1) / patElectron_energy->at(1) ;
   Electron1 = Electron1*energy_corr0;
   Electron2 = Electron2*energy_corr1;


//  cout << "wg =" <<wg <<endl;
//  cout << "wg_SFu =" <<wg_SFu <<endl;
//  cout << "wg_SFd =" <<wg_SFd <<endl;
   
  /*  BUG FIXING FOR SF ELE 2017 */
  if(fabs(patElectron_eta->at(0)) < 1.4442){ 
    elesf_d1 = 0.966; elesf_u1 = 0.968; elesf1 = 0.967;
  }
  if(fabs(patElectron_eta->at(0)) >= 1.566 && fabs(patElectron_eta->at(0)) < 2.5){
    elesf_d1 = 0.971; elesf_u1 = 0.975; elesf1 = 0.973;
  }
  if(fabs(patElectron_eta->at(1)) < 1.4442){ 
    elesf_d2 = 0.966; elesf_u2 = 0.968; elesf2 = 0.967;
  }
  if(fabs(patElectron_eta->at(1)) >= 1.566 && fabs(patElectron_eta->at(1)) < 2.5){
    elesf_d2 = 0.971; elesf_u2 = 0.975; elesf2=0.973;
  }
  lepsf_evt=elesf1*elesf2;
  lepsf_evt_u=elesf_u1*elesf_u2;
  lepsf_evt_d=elesf_d1*elesf_d2;
  wg = lumi * lumi_wgt * lepsf_evt * PUWeight;  
  wg_SFu = lumi * lumi_wgt * lepsf_evt_u * PUWeight;  
  wg_SFd = lumi * lumi_wgt * lepsf_evt_d * PUWeight; 
  /*bug fixing part end*/


 //   cout << "wg =" <<wg <<endl;
 //   cout << "wg_SFu =" <<wg_SFu <<endl;
 //   cout << "wg_SFd =" <<wg_SFd <<endl;
 //   cout << "======="<<endl;

  if (HLT_Ele == 1 && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190 && (Electron1+Electron2).M() > 300){
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


   TTtW_eejj_ele1_ecalTrkEnergyPostCorr->Fill(patElectron_ecalTrkEnergyPostCorr->at(0),wg);
   TTtW_eejj_ele2_ecalTrkEnergyPostCorr->Fill(patElectron_ecalTrkEnergyPostCorr->at(1),wg);
   TTtW_eejj_ele1_energy->Fill(patElectron_energy->at(0),wg);
   TTtW_eejj_ele2_energy->Fill(patElectron_energy->at(1),wg);
   TTtW_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   TTtW_eejj_2017_AlphaRatio->Fill((Electron1+Electron2+BoostJet).M(), wg);
   TTtW_eejj_2017_AlphaRatioUp->Fill((Electron1+Electron2+BoostJet).M(), wg);
   TTtW_eejj_2017_AlphaRatioDown->Fill((Electron1+Electron2+BoostJet).M(), wg);
   TTtW_eejj_2017_SFUp->Fill((Electron1+Electron2+BoostJet).M(), wg_SFu);
   TTtW_eejj_2017_SFDown->Fill((Electron1+Electron2+BoostJet).M(), wg_SFd);
   TTtW_eejj_2017_PUUp->Fill((Electron1+Electron2+BoostJet).M(), wg_PUu);
   TTtW_eejj_2017_PUDown->Fill((Electron1+Electron2+BoostJet).M(), wg_PUd);
   TTtW_eejj_energyScaleUp->Fill((Ele1_ScaleUp+Ele2_ScaleUp+BoostJet).M(), wg);
   TTtW_eejj_energyScaleDown->Fill((Ele1_ScaleDown+Ele2_ScaleDown+BoostJet).M(), wg);
   TTtW_eejj_2017_energySigmaUp->Fill((Ele1_SigmaUp+Ele2_SigmaUp+BoostJet).M(), wg);
   TTtW_eejj_2017_energySigmaDown->Fill((Ele1_SigmaDown+Ele2_SigmaDown+BoostJet).M(), wg);
   if(centralJesJer->at(0)==1)TTtW_eejj_2017_centralJesJer->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)TTtW_eejj_2017_JesSFUp->Fill((Electron1+Electron2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)TTtW_eejj_2017_JesSFDown->Fill((Electron1+Electron2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)TTtW_eejj_2017_JerSFUp->Fill((Electron1+Electron2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)TTtW_eejj_2017_JerSFDown->Fill((Electron1+Electron2+BoostJet_JERdown).M(), wg);
  
  TTtW_eejj_PDFUp->Fill((Electron1+Electron2+BoostJet).M(), wg*1.7);      //comment for bkgs                 
  TTtW_eejj_PDFDown->Fill((Electron1+Electron2+BoostJet).M(), wg*0.3);  //comment for bkgs

  }

    //Zpeak DY cr 60-120 GeV
  if (HLT_Ele == 1 && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190 && (Electron1+Electron2).M() >60 && (Electron1+Electron2).M() < 120){
   Electron1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   Electron2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energy->at(1));  
   BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
   Electron1 = Electron1*energy_corr0;
   Electron2 = Electron2*energy_corr1;

   TTtW_ZpeakMll_eejj->Fill((Electron1+Electron2).M(), wg);
   TTtW_Zpeak_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   TTtW_Zpeak_eejj_ele1_energy->Fill(patElectron_ecalTrkEnergyPostCorr->at(0), wg);
   TTtW_Zpeak_eejj_ele2_ecalTrkEnergyPostCorr->Fill(patElectron_ecalTrkEnergyPostCorr->at(1), wg);
   TTtW_Zpeak_eejj_ele1_energy->Fill(patElectron_energy->at(0), wg);
   TTtW_Zpeak_eejj_ele2_energy->Fill(patElectron_energy->at(1), wg);
  }

  //DY cr 150-300 GeV
  if (HLT_Ele == 1 && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190 && (Electron1+Electron2).M() >150 && (Electron1+Electron2).M() < 300){
   Electron1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   Electron2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energy->at(1));  
   Electron1 = Electron1*energy_corr0;
   Electron2 = Electron2*energy_corr1;

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
   TTtW_DYcr_eejj_ele1_ecalTrkEnergyPostCorr->Fill(patElectron_ecalTrkEnergyPostCorr->at(0), wg);
   TTtW_DYcr_eejj_ele2_ecalTrkEnergyPostCorr->Fill(patElectron_ecalTrkEnergyPostCorr->at(1), wg);
   TTtW_DYcr_eejj_ele1_energy->Fill(patElectron_energy->at(0), wg);
   TTtW_DYcr_eejj_ele2_energy->Fill(patElectron_energy->at(1), wg);
   TTtW_DYcr_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   TTtW_DYcr_eejj_2017_AlphaRatio->Fill((Electron1+Electron2+BoostJet).M(), wg);
   TTtW_DYcr_eejj_2017_AlphaRatioUp->Fill((Electron1+Electron2+BoostJet).M(), wg);
   TTtW_DYcr_eejj_2017_AlphaRatioDown->Fill((Electron1+Electron2+BoostJet).M(), wg);
   TTtW_DYcr_eejj_2017_SFUp->Fill((Electron1+Electron2+BoostJet).M(), wg_SFu);
   TTtW_DYcr_eejj_2017_SFDown->Fill((Electron1+Electron2+BoostJet).M(), wg_SFd);
   TTtW_DYcr_eejj_2017_PUUp->Fill((Electron1+Electron2+BoostJet).M(), wg_PUu);
   TTtW_DYcr_eejj_2017_PUDown->Fill((Electron1+Electron2+BoostJet).M(), wg_PUd);
   TTtW_DYcr_eejj_energyScaleUp->Fill((Ele1_ScaleUp+Ele2_ScaleUp+BoostJet).M(), wg);
   TTtW_DYcr_eejj_energyScaleDown->Fill((Ele1_ScaleDown+Ele2_ScaleDown+BoostJet).M(), wg);
   TTtW_DYcr_eejj_2017_energySigmaUp->Fill((Ele1_SigmaUp+Ele2_SigmaUp+BoostJet).M(), wg);
   TTtW_DYcr_eejj_2017_energySigmaDown->Fill((Ele1_SigmaDown+Ele2_SigmaDown+BoostJet).M(), wg);
   if(centralJesJer->at(0)==1)TTtW_DYcr_eejj_centralJesJer->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)TTtW_DYcr_eejj_2017_JesSFUp->Fill((Electron1+Electron2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)TTtW_DYcr_eejj_2017_JesSFDown->Fill((Electron1+Electron2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)TTtW_DYcr_eejj_2017_JerSFUp->Fill((Electron1+Electron2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)TTtW_DYcr_eejj_2017_JerSFDown->Fill((Electron1+Electron2+BoostJet_JERdown).M(), wg); 
  }

 }

 //TTtW cr
 TLorentzVector LeadLep;
TLorentzVector SubLeadLep;
TLorentzVector Ele_ScaleUp;
TLorentzVector Ele_ScaleDown;
TLorentzVector Ele_SigmaUp;
TLorentzVector Ele_SigmaDown;
TLorentzVector Muon_PtResoUp;
TLorentzVector Muon_PtResoDown;

double deltaEta = 0, deltaPhi = 0, deltaR = 0;

 if (Muon_pt_tunePbt->size() > 0 && patElectron_pt->size() > 0 && numOfHighptMu==1 && numOfHighptEle == 1 && numOfBoostedJets>=1){

  BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
   BoostJet_JESup.SetPtEtaPhiE(BoostedJet_pt->at(1), BoostedJet_eta->at(1), BoostedJet_phi->at(1),BoostedJet_energy->at(1));
   BoostJet_JESdown.SetPtEtaPhiE(BoostedJet_pt->at(2), BoostedJet_eta->at(2), BoostedJet_phi->at(2),BoostedJet_energy->at(2));
   BoostJet_JERup.SetPtEtaPhiE(BoostedJet_pt->at(3), BoostedJet_eta->at(3), BoostedJet_phi->at(3),BoostedJet_energy->at(3));
   BoostJet_JERdown.SetPtEtaPhiE(BoostedJet_pt->at(4), BoostedJet_eta->at(4), BoostedJet_phi->at(4),BoostedJet_energy->at(4));
   Ele_ScaleUp.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energyScaleUp->at(0));
   Ele_ScaleDown.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energyScaleDown->at(0));
   Ele_SigmaUp.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energySigmaUp->at(0));
   Ele_SigmaDown.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energySigmaDown->at(0));
   Muon_PtResoUp.SetPtEtaPhiM((Muon_pt_tunePbt->at(0)+0.1*Muon_pt_tunePbt->at(0)), Muon_eta->at(0), Muon_phi->at(0),0.1056583745 );
   Muon_PtResoDown.SetPtEtaPhiM((Muon_pt_tunePbt->at(0)-0.1*Muon_pt_tunePbt->at(0)), Muon_eta->at(0), Muon_phi->at(0),0.1056583745 );
   
  if (Muon_pt_tunePbt->at(0) >= patElectron_pt->at(0)){
   LeadLep.SetPtEtaPhiE(Muon_pt_tunePbt->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));
   SubLeadLep.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));

   SubLeadLep = SubLeadLep*energy_corr0;

  if (HLT_Mu == 1 && LeadLep.Pt() > 150 && SubLeadLep.Pt() > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(patElectron_eta->at(0))<2.4
     && BoostedJet_pt->at(0) > 190 && (LeadLep+SubLeadLep).M() > 300 ){
   veto_ele = false;
   for(int j = 0; j < Muon_pt_tunePbt->size(); j++){
    if (Muon_pt_tunePbt->at(j) > 5){
     deltaEta=fabs(Muon_eta->at(j) - patElectron_eta->at(0));
     deltaPhi = Muon_phi->at(j) - patElectron_phi->at(0);
     if(deltaPhi > M_PI) deltaPhi -= 2*M_PI;
     else if(deltaPhi <= -M_PI) deltaPhi +=2*M_PI;
     deltaR=sqrt(pow(deltaEta,2) + pow(deltaPhi,2));
     if (deltaR < 0.1) veto_ele = true;
    }
   }
   if (veto_ele == false){
    TTtW_TTtWcr_ll->Fill((LeadLep+SubLeadLep).M(),wg);
    TTtW_TTtWcr_ll_2017_AlphaRatio->Fill((LeadLep+SubLeadLep).M(),wg);
    TTtW_TTtWcr_ll_2017_AlphaRatioUp->Fill((LeadLep+SubLeadLep).M(),wg);
    TTtW_TTtWcr_ll_2017_AlphaRatioDown->Fill((LeadLep+SubLeadLep).M(),wg);
    TTtW_TTtWcr_ll_2017_SFUp->Fill((LeadLep+SubLeadLep).M(),wg_SFu);
    TTtW_TTtWcr_ll_2017_SFDown->Fill((LeadLep+SubLeadLep).M(),wg_SFd);
    TTtW_TTtWcr_ll_2017_PUUp->Fill((LeadLep+SubLeadLep).M(),wg_PUu);
    TTtW_TTtWcr_ll_2017_PUDown->Fill((LeadLep+SubLeadLep).M(),wg_PUd);

   TTtW_TTtWcr_ll_energyScaleUp->Fill((Ele_ScaleUp+LeadLep).M(),wg);
    TTtW_TTtWcr_ll_energyScaleDown->Fill((Ele_ScaleDown+LeadLep).M(),wg);
    TTtW_TTtWcr_ll_2017_energySigmaUp->Fill((Ele_SigmaUp+LeadLep).M(),wg);
    TTtW_TTtWcr_ll_2017_energySigmaDown->Fill((Ele_SigmaDown+LeadLep).M(),wg);
    TTtW_TTtWcr_ll_2017_PtResoUp->Fill((Muon_PtResoUp+SubLeadLep).M(), wg);
    TTtW_TTtWcr_ll_2017_PtResoDown->Fill((Muon_PtResoDown+SubLeadLep).M(), wg);
    M_leplepJ_TTtWcr->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    if(centralJesJer->at(0)==1)TTtW_TTtWcr_ll_centralJesJer->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JesSFup->at(1)==1)TTtW_TTtWcr_ll_2017_JesSFUp->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JesSFdown->at(2)==1)TTtW_TTtWcr_ll_2017_JesSFDown->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JerSFup->at(3)==1)TTtW_TTtWcr_ll_2017_JerSFUp->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JerSFdown->at(4)==1)TTtW_TTtWcr_ll_2017_JerSFDown->Fill((LeadLep+SubLeadLep).M(), wg);

    /*M(emuJ)*/
    TTtW_TTtWcr_llJ->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    TTtW_TTtWcr_llJ_2017_AlphaRatio->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    TTtW_TTtWcr_llJ_2017_AlphaRatioUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    TTtW_TTtWcr_llJ_2017_AlphaRatioDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    TTtW_TTtWcr_llJ_2017_SFUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_SFu);
    TTtW_TTtWcr_llJ_2017_SFDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_SFd);
    TTtW_TTtWcr_llJ_2017_PUUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_PUu);
    TTtW_TTtWcr_llJ_2017_PUDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_PUd);
    TTtW_TTtWcr_llJ_2017_PtResoUp->Fill((Muon_PtResoUp+SubLeadLep).M(),wg);
    TTtW_TTtWcr_llJ_2017_PtResoDown->Fill((Muon_PtResoDown+SubLeadLep).M(),wg);
    TTtW_TTtWcr_llJ_energyScaleUp->Fill((Ele_ScaleUp+LeadLep+BoostJet).M(),wg);
    TTtW_TTtWcr_llJ_energyScaleDown->Fill((Ele_ScaleDown+LeadLep+BoostJet).M(),wg);
    TTtW_TTtWcr_llJ_2017_energySigmaUp->Fill((Ele_SigmaUp+LeadLep+BoostJet).M(),wg);
    TTtW_TTtWcr_llJ_2017_energySigmaDown->Fill((Ele_SigmaDown+LeadLep+BoostJet).M(),wg);
    if(centralJesJer->at(0)==1)TTtW_TTtWcr_llJ_centralJesJer->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if(JesSFup->at(1)==1)TTtW_TTtWcr_llJ_2017_JesSFUp->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if(JesSFdown->at(2)==1)TTtW_TTtWcr_llJ_2017_JesSFDown->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if(JerSFup->at(3)==1)TTtW_TTtWcr_llJ_2017_JerSFUp->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if(JerSFdown->at(4)==1)TTtW_TTtWcr_llJ_2017_JerSFDown->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);

   }
  }
 }

 else {

   LeadLep.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   SubLeadLep.SetPtEtaPhiE(Muon_pt_tunePbt->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));

    LeadLep = LeadLep*energy_corr0;

   if (HLT_Ele == 1 & LeadLep.Pt() > 150 && SubLeadLep.Pt() > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190 && (LeadLep+SubLeadLep).M() > 300){

    veto_ele = false;
   for(int j = 0; j < Muon_pt_tunePbt->size(); j++){
    if (Muon_pt_tunePbt->at(j) > 5){
     deltaEta=fabs(Muon_eta->at(j) - patElectron_eta->at(0));
     deltaPhi = Muon_phi->at(j) - patElectron_phi->at(0);
     if(deltaPhi > M_PI) deltaPhi -= 2*M_PI;
     else if(deltaPhi <= -M_PI) deltaPhi +=2*M_PI;
     deltaR=sqrt(pow(deltaEta,2) + pow(deltaPhi,2));
     if (deltaR < 0.1) veto_ele = true;
    }
   }
   if (veto_ele == false){
    TTtW_TTtWcr_ll->Fill((LeadLep+SubLeadLep).M(),wg);
    TTtW_TTtWcr_ll_2017_AlphaRatio->Fill((LeadLep+SubLeadLep).M(),wg);
    TTtW_TTtWcr_ll_2017_AlphaRatioUp->Fill((LeadLep+SubLeadLep).M(),wg);
    TTtW_TTtWcr_ll_2017_AlphaRatioDown->Fill((LeadLep+SubLeadLep).M(),wg);
    TTtW_TTtWcr_ll_2017_SFUp->Fill((LeadLep+SubLeadLep).M(),wg_SFu);
    TTtW_TTtWcr_ll_2017_SFDown->Fill((LeadLep+SubLeadLep).M(),wg_SFd);
    TTtW_TTtWcr_ll_2017_PUUp->Fill((LeadLep+SubLeadLep).M(),wg_PUu);
    TTtW_TTtWcr_ll_2017_PUDown->Fill((LeadLep+SubLeadLep).M(),wg_PUd);

     TTtW_TTtWcr_ll_energyScaleUp->Fill((Ele_ScaleUp+SubLeadLep).M(),wg);
    TTtW_TTtWcr_ll_energyScaleDown->Fill((Ele_ScaleDown+SubLeadLep).M(),wg);
    TTtW_TTtWcr_ll_2017_energySigmaUp->Fill((Ele_SigmaUp+SubLeadLep).M(),wg);
    TTtW_TTtWcr_ll_2017_energySigmaDown->Fill((Ele_SigmaDown+SubLeadLep).M(),wg);
    TTtW_TTtWcr_ll_2017_PtResoUp->Fill((Muon_PtResoUp+LeadLep).M(), wg);
    TTtW_TTtWcr_ll_2017_PtResoDown->Fill((Muon_PtResoDown+LeadLep).M(), wg);
    M_leplepJ_TTtWcr->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);

    if(centralJesJer->at(0)==1)TTtW_TTtWcr_ll_centralJesJer->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JesSFup->at(1)==1)TTtW_TTtWcr_ll_2017_JesSFUp->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JesSFdown->at(2)==1)TTtW_TTtWcr_ll_2017_JesSFDown->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JerSFup->at(3)==1)TTtW_TTtWcr_ll_2017_JerSFUp->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JerSFdown->at(4)==1)TTtW_TTtWcr_ll_2017_JerSFDown->Fill((LeadLep+SubLeadLep).M(), wg);

     /* M(e mu J)*/
    TTtW_TTtWcr_llJ->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    TTtW_TTtWcr_llJ_2017_AlphaRatio->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    TTtW_TTtWcr_llJ_2017_AlphaRatioUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    TTtW_TTtWcr_llJ_2017_AlphaRatioDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    TTtW_TTtWcr_llJ_2017_SFUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_SFu);
    TTtW_TTtWcr_llJ_2017_SFDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_SFd);
    TTtW_TTtWcr_llJ_2017_PUUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_PUu);
    TTtW_TTtWcr_llJ_2017_PUDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_PUd);
    TTtW_TTtWcr_llJ_2017_PtResoUp->Fill((Muon_PtResoUp+LeadLep).M(),wg);
    TTtW_TTtWcr_llJ_2017_PtResoDown->Fill((Muon_PtResoDown+LeadLep).M(),wg);
    TTtW_TTtWcr_llJ_energyScaleUp->Fill((Ele_ScaleUp+SubLeadLep+BoostJet).M(),wg);
    TTtW_TTtWcr_llJ_energyScaleDown->Fill((Ele_ScaleDown+SubLeadLep+BoostJet).M(),wg);
    TTtW_TTtWcr_llJ_2017_energySigmaUp->Fill((Ele_SigmaUp+SubLeadLep+BoostJet).M(),wg);
    TTtW_TTtWcr_llJ_2017_energySigmaDown->Fill((Ele_SigmaDown+SubLeadLep+BoostJet).M(),wg);
    if(centralJesJer->at(0)==1)TTtW_TTtWcr_llJ_centralJesJer->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if(JesSFup->at(1)==1)TTtW_TTtWcr_llJ_2017_JesSFUp->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if(JesSFdown->at(2)==1)TTtW_TTtWcr_llJ_2017_JesSFDown->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if(JerSFup->at(3)==1)TTtW_TTtWcr_llJ_2017_JerSFUp->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if(JerSFdown->at(4)==1)TTtW_TTtWcr_llJ_2017_JerSFDown->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    }
   }
  }


 } //TTtW CR 
  
 
}

//TFile *f = new TFile("SR_syst_TTtW_2017.root", "RECREATE");
TFile *f = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/2017_ALL_HOPE/SR_syst_TTtW_2017.root", "RECREATE");
//TFile *f2 = new TFile("plot/SR_syst_TTtW_2017.root", "RECREATE");
TTtW_eejj_ele1_ecalTrkEnergyPostCorr->Write();
TTtW_eejj_ele2_ecalTrkEnergyPostCorr->Write();
TTtW_eejj_ele1_energy->Write();
TTtW_eejj_ele2_energy->Write();
TTtW_eejj->Write();
TTtW_eejj_2017_AlphaRatio->Write();
TTtW_eejj_2017_AlphaRatioUp->Write();
TTtW_eejj_2017_AlphaRatioDown->Write();
TTtW_eejj_2017_SFUp->Write();
TTtW_eejj_2017_SFDown->Write();
TTtW_eejj_2017_PUUp->Write();
TTtW_eejj_2017_PUDown->Write();
TTtW_eejj_2017_centralJesJer->Write();
TTtW_eejj_2017_JesSFUp->Write();
TTtW_eejj_2017_JesSFDown->Write();
TTtW_eejj_2017_JerSFUp->Write();
TTtW_eejj_2017_JerSFDown->Write();
TTtW_eejj_energyScaleUp->Write();
TTtW_eejj_energyScaleDown->Write();
TTtW_eejj_2017_energySigmaUp->Write();
TTtW_eejj_2017_energySigmaDown->Write();

TTtW_mumujj->Write();
TTtW_mumujj_2017_AlphaRatio->Write();
TTtW_mumujj_2017_AlphaRatioUp->Write();
TTtW_mumujj_2017_AlphaRatioDown->Write();
TTtW_mumujj_2017_SFUp->Write();
TTtW_mumujj_2017_SFDown->Write();
TTtW_mumujj_2017_PUUp->Write();
TTtW_mumujj_2017_PUDown->Write();
TTtW_mumujj_2017_centralJesJer->Write();
TTtW_mumujj_2017_JesSFUp->Write();
TTtW_mumujj_2017_JesSFDown->Write();
TTtW_mumujj_2017_JerSFUp->Write();
TTtW_mumujj_2017_JerSFDown->Write();
TTtW_mumujj_2017_PtResoUp->Write();
TTtW_mumujj_2017_PtResoDown->Write();

TTtW_eejj_PDFUp->Write();
TTtW_eejj_PDFDown->Write();
TTtW_mumujj_PDFUp->Write();
TTtW_mumujj_PDFDown->Write();

//Zpeak DYcr 
TTtW_ZpeakMll_eejj->Write();
TTtW_ZpeakMll_mumujj->Write();
TTtW_Zpeak_eejj->Write();
TTtW_Zpeak_mumujj->Write();
TTtW_Zpeak_eejj_ele1_ecalTrkEnergyPostCorr->Write();
TTtW_Zpeak_eejj_ele2_ecalTrkEnergyPostCorr->Write();
TTtW_Zpeak_eejj_ele1_energy->Write();
TTtW_Zpeak_eejj_ele2_energy->Write();

//DYcr 
TTtW_DYcr_eejj_ele1_ecalTrkEnergyPostCorr->Write();
TTtW_DYcr_eejj_ele2_ecalTrkEnergyPostCorr->Write();
TTtW_DYcr_eejj_ele1_energy->Write();
TTtW_DYcr_eejj_ele2_energy->Write();
TTtW_DYcr_eejj->Write();
TTtW_DYcr_eejj_2017_AlphaRatio->Write();
TTtW_DYcr_eejj_2017_AlphaRatioUp->Write();
TTtW_DYcr_eejj_2017_AlphaRatioDown->Write();
TTtW_DYcr_eejj_2017_SFUp->Write();
TTtW_DYcr_eejj_2017_SFDown->Write();
TTtW_DYcr_eejj_2017_PUUp->Write();
TTtW_DYcr_eejj_2017_PUDown->Write();
TTtW_DYcr_eejj_centralJesJer->Write();
TTtW_DYcr_eejj_2017_JesSFUp->Write();
TTtW_DYcr_eejj_2017_JesSFDown->Write();
TTtW_DYcr_eejj_2017_JerSFUp->Write();
TTtW_DYcr_eejj_2017_JerSFDown->Write();
TTtW_DYcr_eejj_energyScaleUp->Write();
TTtW_DYcr_eejj_energyScaleDown->Write();
TTtW_DYcr_eejj_2017_energySigmaUp->Write();
TTtW_DYcr_eejj_2017_energySigmaDown->Write();
TTtW_DYcr_mumujj->Write();
TTtW_DYcr_mumujj_2017_AlphaRatio->Write();
TTtW_DYcr_mumujj_2017_AlphaRatioUp->Write();
TTtW_DYcr_mumujj_2017_AlphaRatioDown->Write();
TTtW_DYcr_mumujj_2017_SFUp->Write();
TTtW_DYcr_mumujj_2017_SFDown->Write();
TTtW_DYcr_mumujj_2017_PUUp->Write();
TTtW_DYcr_mumujj_2017_PUDown->Write();
TTtW_DYcr_mumujj_centralJesJer->Write();
TTtW_DYcr_mumujj_2017_JesSFUp->Write();
TTtW_DYcr_mumujj_2017_JesSFDown->Write();
TTtW_DYcr_mumujj_2017_JerSFUp->Write();
TTtW_DYcr_mumujj_2017_JerSFDown->Write();
TTtW_DYcr_mumujj_2017_PtResoUp->Write();
TTtW_DYcr_mumujj_2017_PtResoDown->Write();

//TTtW cr
M_leplepJ_TTtWcr->Write();
TTtW_TTtWcr_ll->Write();
TTtW_TTtWcr_ll_2017_AlphaRatio->Write();
TTtW_TTtWcr_ll_2017_AlphaRatioUp->Write();
TTtW_TTtWcr_ll_2017_AlphaRatioDown->Write();
TTtW_TTtWcr_ll_2017_SFUp->Write();
TTtW_TTtWcr_ll_2017_SFDown->Write();
TTtW_TTtWcr_ll_2017_PUUp->Write();
TTtW_TTtWcr_ll_2017_PUDown->Write();
TTtW_TTtWcr_ll_energyScaleUp->Write();
TTtW_TTtWcr_ll_energyScaleDown->Write();
TTtW_TTtWcr_ll_2017_energySigmaUp->Write();
TTtW_TTtWcr_ll_2017_energySigmaDown->Write();
TTtW_TTtWcr_ll_2017_PtResoUp->Write();
TTtW_TTtWcr_ll_2017_PtResoDown->Write();
TTtW_TTtWcr_ll_centralJesJer->Write();
TTtW_TTtWcr_ll_2017_JesSFUp->Write();
TTtW_TTtWcr_ll_2017_JesSFDown->Write();
TTtW_TTtWcr_ll_2017_JerSFUp->Write();
TTtW_TTtWcr_ll_2017_JerSFDown->Write();

TTtW_TTtWcr_llJ->Write();
TTtW_TTtWcr_llJ_2017_AlphaRatio->Write();
TTtW_TTtWcr_llJ_2017_AlphaRatioUp->Write();
TTtW_TTtWcr_llJ_2017_AlphaRatioDown->Write();
TTtW_TTtWcr_llJ_2017_SFUp->Write();
TTtW_TTtWcr_llJ_2017_SFDown->Write();
TTtW_TTtWcr_llJ_2017_PUUp->Write();
TTtW_TTtWcr_llJ_2017_PUDown->Write();
TTtW_TTtWcr_llJ_2017_PtResoUp->Write();
TTtW_TTtWcr_llJ_2017_PtResoDown->Write();
TTtW_TTtWcr_llJ_energyScaleUp->Write();
TTtW_TTtWcr_llJ_energyScaleDown->Write();
TTtW_TTtWcr_llJ_2017_energySigmaUp->Write();
TTtW_TTtWcr_llJ_2017_energySigmaDown->Write();
TTtW_TTtWcr_llJ_centralJesJer->Write();
TTtW_TTtWcr_llJ_2017_JesSFUp->Write();
TTtW_TTtWcr_llJ_2017_JesSFDown->Write();
TTtW_TTtWcr_llJ_2017_JerSFUp->Write();
TTtW_TTtWcr_llJ_2017_JerSFDown->Write();

f->Write();
f->Close();

}
 
