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
void Analisi_SR_MC_syst_2017(){

TChain *a_ = new TChain("BOOM");

a_->Add("/eos/user/m/mpresill/CMS/HN_Reload/rootplized_samples_2017_syst/mumujj_L13_M8000_2017.root");
//inputFile

int HLT_Ele, HLT_Photon200, HLT_Ele115, HLT_Ele35, HLT_Mu, HLT_Mu50, HLT_OldMu100, HLT_TkMu50, HLT_TkMu100;
double muejj_l, emujj_l;
std:vector<double>* patElectron_pt; patElectron_pt=0;
vector<double>* patElectron_eta; patElectron_eta=0;
vector<double>* patElectron_phi; patElectron_phi=0;
vector<double>* patElectron_energy; patElectron_energy=0;
vector<int>* patElectron_charge; patElectron_charge=0;
vector<double>* Muon_pt; Muon_pt=0;
vector<double>* Muon_pt_corr; Muon_pt_corr=0;
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
TBranch *a_patElectron_energy=a_->GetBranch("patElectron_energy");
TBranch *a_patElectron_charge=a_->GetBranch("patElectron_charge");
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
a_HLT_Ele35_WPTight_Gsf->SetAddress(&HLT_Ele35);
a_HLT_Photon200->SetAddress(&HLT_Photon200);
a_HLT_Mu50->SetAddress(&HLT_Mu50);
a_HLT_OldMu100->SetAddress(&HLT_OldMu100);
a_HLT_TkMu50->SetAddress(&HLT_TkMu50);
a_HLT_TkMu100->SetAddress(&HLT_TkMu100);

a_patElectron_pt->SetAddress(&patElectron_pt);
a_patElectron_eta->SetAddress(&patElectron_eta);
a_patElectron_phi->SetAddress(&patElectron_phi);
a_patElectron_energy->SetAddress(&patElectron_energy);
a_patElectron_charge->SetAddress(&patElectron_charge);
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

//new bin
//const double asymbins[9] = {0,200,400,600,800,1000,1400,2000,10000};

//old bin
const double asymbins[10] = {0,200,400,600,800,1000,1400,2000,3500,10000};

TH1D *mumujj_L13_M8000_mumujj = new TH1D ("mumujj_L13_M8000_mumujj", "mumujj_L13_M8000_mumujj", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2017_AlphaRatio = new TH1D ("mumujj_L13_M8000_mumujj_2017_AlphaRatio", "mumujj_L13_M8000_mumujj_2017_AlphaRatio", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2017_AlphaRatioDown = new TH1D ("mumujj_L13_M8000_mumujj_2017_AlphaRatioDown", "mumujj_L13_M8000_mumujj_2017_AlphaRatioDown", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2017_AlphaRatioUp = new TH1D ("mumujj_L13_M8000_mumujj_2017_AlphaRatioUp", "mumujj_L13_M8000_mumujj_2017_AlphaRatioUp", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2017_SFUp = new TH1D ("mumujj_L13_M8000_mumujj_2017_SFUp", "mumujj_L13_M8000_mumujj_2017_SFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2017_SFDown = new TH1D ("mumujj_L13_M8000_mumujj_2017_SFDown", "mumujj_L13_M8000_mumujj_2017_SFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2017_PUUp = new TH1D ("mumujj_L13_M8000_mumujj_2017_PUUp", "mumujj_L13_M8000_mumujj_2017_PUUp", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2017_PUDown = new TH1D ("mumujj_L13_M8000_mumujj_2017_PUDown", "mumujj_L13_M8000_mumujj_2017_PUDown", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2017_centralJesJer = new TH1D ("mumujj_L13_M8000_mumujj_2017_centralJesJer", "mumujj_L13_M8000_mumujj_2017_centralJesJer", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2017_JesSFUp = new TH1D ("mumujj_L13_M8000_mumujj_2017_JesSFUp", "mumujj_L13_M8000_mumujj_2017_JesSFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2017_JesSFDown = new TH1D ("mumujj_L13_M8000_mumujj_2017_JesSFDown", "mumujj_L13_M8000_mumujj_2017_JesSFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2017_JerSFUp = new TH1D ("mumujj_L13_M8000_mumujj_2017_JerSFUp", "mumujj_L13_M8000_mumujj_2017_JerSFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2017_JerSFDown = new TH1D ("mumujj_L13_M8000_mumujj_2017_JerSFDown", "mumujj_L13_M8000_mumujj_2017_JerSFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2017_PtCorr = new TH1D ("mumujj_L13_M8000_mumujj_2017_PtCorr", "mumujj_L13_M8000_mumujj_2017_PtCorr", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2017_PtCorrDown = new TH1D ("mumujj_L13_M8000_mumujj_2017_PtCorrDown", "mumujj_L13_M8000_mumujj_2017_PtCorrDown", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2017_PtCorrUp = new TH1D ("mumujj_L13_M8000_mumujj_2017_PtCorrUp", "mumujj_L13_M8000_mumujj_2017_PtCorrUp", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2017_PtResoUp  = new TH1D ("mumujj_L13_M8000_mumujj_2017_PtResoUp", "mumujj_L13_M8000_mumujj_2017_PtResoUp", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2017_PtResoDown  = new TH1D ("mumujj_L13_M8000_mumujj_2017_PtResoDown", "mumujj_L13_M8000_mumujj_2017_PtResoDown", 9, asymbins);

TH1D *mumujj_L13_M8000_eejj = new TH1D ("mumujj_L13_M8000_eejj", "mumujj_L13_M8000_eejj", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2017_AlphaRatio = new TH1D ("mumujj_L13_M8000_eejj_2017_AlphaRatio", "mumujj_L13_M8000_eejj_2017_AlphaRatio", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2017_AlphaRatioDown = new TH1D ("mumujj_L13_M8000_eejj_2017_AlphaRatioDown", "mumujj_L13_M8000_eejj_2017_AlphaRatioDown", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2017_AlphaRatioUp = new TH1D ("mumujj_L13_M8000_eejj_2017_AlphaRatioUp", "mumujj_L13_M8000_eejj_2017_AlphaRatioUp", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2017_SFUp = new TH1D ("mumujj_L13_M8000_eejj_2017_SFUp", "mumujj_L13_M8000_eejj_2017_SFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2017_SFDown = new TH1D ("mumujj_L13_M8000_eejj_2017_SFDown", "mumujj_L13_M8000_eejj_2017_SFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2017_PUUp = new TH1D ("mumujj_L13_M8000_eejj_2017_PUUp", "mumujj_L13_M8000_eejj_2017_PUUp", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2017_PUDown = new TH1D ("mumujj_L13_M8000_eejj_2017_PUDown", "mumujj_L13_M8000_eejj_2017_PUDown", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2017_centralJesJer = new TH1D ("mumujj_L13_M8000_eejj_2017_centralJesJer", "mumujj_L13_M8000_eejj_2017_centralJesJer", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2017_JesSFUp = new TH1D ("mumujj_L13_M8000_eejj_2017_JesSFUp", "mumujj_L13_M8000_eejj_2017_JesSFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2017_JesSFDown = new TH1D ("mumujj_L13_M8000_eejj_2017_JesSFDown", "mumujj_L13_M8000_eejj_2017_JesSFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2017_JerSFUp = new TH1D ("mumujj_L13_M8000_eejj_2017_JerSFUp", "mumujj_L13_M8000_eejj_2017_JerSFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2017_JerSFDown = new TH1D ("mumujj_L13_M8000_eejj_2017_JerSFDown", "mumujj_L13_M8000_eejj_2017_JerSFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2017_energyScaleUp = new TH1D ("mumujj_L13_M8000_eejj_2017_energyScaleUp", "mumujj_L13_M8000_eejj_2017_energyScaleUp", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2017_energyScaleDown = new TH1D ("mumujj_L13_M8000_eejj_2017_energyScaleDown", "mumujj_L13_M8000_eejj_2017_energyScaleDown", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2017_energySigmaUp = new TH1D ("mumujj_L13_M8000_eejj_2017_energySigmaUp", "mumujj_L13_M8000_eejj_2017_energySigmaUp", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2017_energySigmaDown = new TH1D ("mumujj_L13_M8000_eejj_2017_energySigmaDown", "mumujj_L13_M8000_eejj_2017_energySigmaDown", 9, asymbins);

//PDF uncertaintes for signal samples
TH1D *mumujj_L13_M8000_mumujj_PDFUp = new TH1D ("mumujj_L13_M8000_mumujj_PDFUp", "mumujj_L13_M8000_mumujj_PDFUp", 9, asymbins);   //PDF
TH1D *mumujj_L13_M8000_mumujj_PDFDown = new TH1D ("mumujj_L13_M8000_mumujj_PDFDown", "mumujj_L13_M8000_mumujj_PDFDown", 9, asymbins); //PDF
TH1D *mumujj_L13_M8000_eejj_PDFUp = new TH1D ("mumujj_L13_M8000_eejj_PDFUp", "mumujj_L13_M8000_eejj_PDFUp", 9, asymbins); //PDF
TH1D *mumujj_L13_M8000_eejj_PDFDown = new TH1D ("mumujj_L13_M8000_eejj_PDFDown", "mumujj_L13_M8000_eejj_PDFDown", 9, asymbins); //PDF


//DY CR (mll in 150-300 GeV)
TH1D *mumujj_L13_M8000_DYcr_mumujj = new TH1D ("mumujj_L13_M8000_DYcr_mumujj", "mumujj_L13_M8000_DYcr_mumujj", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2017_AlphaRatio = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2017_AlphaRatio", "mumujj_L13_M8000_DYcr_mumujj_2017_AlphaRatio", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2017_AlphaRatioUp = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2017_AlphaRatioUp", "mumujj_L13_M8000_DYcr_mumujj_2017_AlphaRatioUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2017_AlphaRatioDown = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2017_AlphaRatioDown", "mumujj_L13_M8000_DYcr_mumujj_2017_AlphaRatioDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2017_SFUp = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2017_SFUp", "mumujj_L13_M8000_DYcr_mumujj_2017_SFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2017_SFDown = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2017_SFDown", "mumujj_L13_M8000_DYcr_mumujj_2017_SFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2017_PUUp = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2017_PUUp", "mumujj_L13_M8000_DYcr_mumujj_2017_PUUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2017_PUDown = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2017_PUDown", "mumujj_L13_M8000_DYcr_mumujj_2017_PUDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_centralJesJer = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_centralJesJer", "mumujj_L13_M8000_DYcr_mumujj_centralJesJer", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2017_JesSFUp = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2017_JesSFUp", "mumujj_L13_M8000_DYcr_mumujj_2017_JesSFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2017_JesSFDown = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2017_JesSFDown", "mumujj_L13_M8000_DYcr_mumujj_2017_JesSFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2017_JerSFUp = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2017_JerSFUp", "mumujj_L13_M8000_DYcr_mumujj_2017_JerSFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2017_JerSFDown = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2017_JerSFDown", "mumujj_L13_M8000_DYcr_mumujj_2017_JerSFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2017_PtCorrUp = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2017_PtCorrUp", "mumujj_L13_M8000_DYcr_mumujj_2017_PtCorrUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2017_PtCorrDown = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2017_PtCorrDown", "mumujj_L13_M8000_DYcr_mumujj_2017_PtCorrDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2017_PtResoUp  = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2017_PtResoUp", "mumujj_L13_M8000_DYcr_mumujj_2017_PtResoUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2017_PtResoDown  = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2017_PtResoDown", "mumujj_L13_M8000_DYcr_mumujj_2017_PtResoDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj = new TH1D ("mumujj_L13_M8000_DYcr_eejj", "mumujj_L13_M8000_DYcr_eejj", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2017_AlphaRatio = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2017_AlphaRatio", "mumujj_L13_M8000_DYcr_eejj_2017_AlphaRatio", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2017_AlphaRatioUp = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2017_AlphaRatioUp", "mumujj_L13_M8000_DYcr_eejj_2017_AlphaRatioUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2017_AlphaRatioDown = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2017_AlphaRatioDown", "mumujj_L13_M8000_DYcr_eejj_2017_AlphaRatioDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2017_SFUp = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2017_SFUp", "mumujj_L13_M8000_DYcr_eejj_2017_SFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2017_SFDown = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2017_SFDown", "mumujj_L13_M8000_DYcr_eejj_2017_SFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2017_PUUp = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2017_PUUp", "mumujj_L13_M8000_DYcr_eejj_2017_PUUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2017_PUDown = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2017_PUDown", "mumujj_L13_M8000_DYcr_eejj_2017_PUDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_centralJesJer = new TH1D ("mumujj_L13_M8000_DYcr_eejj_centralJesJer", "mumujj_L13_M8000_DYcr_eejj_centralJesJer", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2017_JesSFUp = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2017_JesSFUp", "mumujj_L13_M8000_DYcr_eejj_2017_JesSFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2017_JesSFDown = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2017_JesSFDown", "mumujj_L13_M8000_DYcr_eejj_2017_JesSFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2017_JerSFUp = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2017_JerSFUp", "mumujj_L13_M8000_DYcr_eejj_2017_JerSFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2017_JerSFDown = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2017_JerSFDown", "mumujj_L13_M8000_DYcr_eejj_2017_JerSFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2017_energyScaleUp = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2017_energyScaleUp", "mumujj_L13_M8000_DYcr_eejj_2017_energyScaleUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2017_energyScaleDown = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2017_energyScaleDown", "mumujj_L13_M8000_DYcr_eejj_2017_energyScaleDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2017_energySigmaUp = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2017_energySigmaUp", "mumujj_L13_M8000_DYcr_eejj_2017_energySigmaUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2017_energySigmaDown = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2017_energySigmaDown", "mumujj_L13_M8000_DYcr_eejj_2017_energySigmaDown", 9, asymbins);


cout << a_->GetEntries() << endl;
int tot=0, muejj = 0;
double wg = 0, wg_SFu = 0, wg_SFd = 0, wg_PUu = 0, wg_PUd = 0;
int lumi = 41529;//2017: 58873 //2017: 41529 //2017: 35542
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
TLorentzVector Muon1_ptResoUp;
TLorentzVector Muon1_ptResoDown;
TLorentzVector Muon2_ptResoUp;
TLorentzVector Muon2_ptResoDown;

/*this is for the patch on lepf sf systematics*/
double elesf1=0, elesf_d1=0, elesf_d2=0; 
double elesf2=0, elesf_u1=0, elesf_u2=0; 


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

  if (Muon_pt->size() > 1 && numOfHighptMu==2 && numOfVetoEle == 0 && numOfBoostedJets>=1){

   Muon1.SetPtEtaPhiE(Muon_pt->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));
    Muon2.SetPtEtaPhiE(Muon_pt->at(1), Muon_eta->at(1), Muon_phi->at(1),Muon_energy->at(1));

   if (HLT_Mu == 1 && Muon_pt->at(0) > 150 && Muon_pt->at(1) > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(Muon_eta->at(1))<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1+Muon2).M()  > 300 ){

    BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
    BoostJet_JESup.SetPtEtaPhiE(BoostedJet_pt->at(1), BoostedJet_eta->at(1), BoostedJet_phi->at(1),BoostedJet_energy->at(1));
    BoostJet_JESdown.SetPtEtaPhiE(BoostedJet_pt->at(2), BoostedJet_eta->at(2), BoostedJet_phi->at(2),BoostedJet_energy->at(2));
    BoostJet_JERup.SetPtEtaPhiE(BoostedJet_pt->at(3), BoostedJet_eta->at(3), BoostedJet_phi->at(3),BoostedJet_energy->at(3));
    BoostJet_JERdown.SetPtEtaPhiE(BoostedJet_pt->at(4), BoostedJet_eta->at(4), BoostedJet_phi->at(4),BoostedJet_energy->at(4));
    Muon1_ptCorr.SetPtEtaPhiE(Muon_pt_corr->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));
    Muon2_ptCorr.SetPtEtaPhiE(Muon_pt_corr->at(1), Muon_eta->at(1), Muon_phi->at(1),Muon_energy->at(1));
    if (fabs(Muon1.Eta()) > 1.2) {
    Muon1_ptResoUp.SetPtEtaPhiE(Muon_pt->at(0)+0.15*Muon_pt->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));
    Muon1_ptResoDown.SetPtEtaPhiE(Muon_pt->at(0)-0.15*Muon_pt->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));
   }
   else{
    Muon1_ptResoUp = Muon1;
    Muon1_ptResoDown = Muon1;
   }
   if (fabs(Muon2.Eta()) > 1.2) {
    Muon2_ptResoUp.SetPtEtaPhiE(Muon_pt->at(1)+0.15*Muon_pt->at(1), Muon_eta->at(1), Muon_phi->at(1),Muon_energy->at(1));
    Muon2_ptResoDown.SetPtEtaPhiE(Muon_pt->at(1)-0.15*Muon_pt->at(1), Muon_eta->at(1), Muon_phi->at(1),Muon_energy->at(1));
   }
   else{
    Muon2_ptResoUp = Muon2;
    Muon2_ptResoDown= Muon2;
   }   

 
   mumujj_L13_M8000_mumujj->Fill((Muon1+Muon2+BoostJet).M(), wg);
   mumujj_L13_M8000_mumujj_2017_AlphaRatio->Fill((Muon1+Muon2+BoostJet).M(), wg);
   mumujj_L13_M8000_mumujj_2017_AlphaRatioUp->Fill((Muon1+Muon2+BoostJet).M(), wg);
   mumujj_L13_M8000_mumujj_2017_AlphaRatioDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
   mumujj_L13_M8000_mumujj_2017_SFUp->Fill((Muon1+Muon2+BoostJet).M(), wg_SFu);
   mumujj_L13_M8000_mumujj_2017_SFDown->Fill((Muon1+Muon2+BoostJet).M(), wg_SFd);
   mumujj_L13_M8000_mumujj_2017_PUUp->Fill((Muon1+Muon2+BoostJet).M(), wg_PUu);
   mumujj_L13_M8000_mumujj_2017_PUDown->Fill((Muon1+Muon2+BoostJet).M(), wg_PUd);
   mumujj_L13_M8000_mumujj_2017_PtCorr->Fill((Muon1_ptCorr+Muon2_ptCorr+BoostJet).M(), wg);
   mumujj_L13_M8000_mumujj_2017_PtCorrUp->Fill((Muon1_ptCorr+Muon2_ptCorr+BoostJet).M(), wg);
   mumujj_L13_M8000_mumujj_2017_PtCorrDown->Fill((Muon1_ptCorr+Muon2_ptCorr+BoostJet).M(), wg);
   mumujj_L13_M8000_mumujj_2017_PtResoUp->Fill((Muon1_ptResoUp+Muon2_ptResoUp+BoostJet).M(), wg);
   mumujj_L13_M8000_mumujj_2017_PtResoDown->Fill((Muon1_ptResoDown+Muon2_ptResoDown+BoostJet).M(), wg);
  
   if(centralJesJer->at(0)==1)mumujj_L13_M8000_mumujj_2017_centralJesJer->Fill((Muon1+Muon2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)mumujj_L13_M8000_mumujj_2017_JesSFUp->Fill((Muon1+Muon2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)mumujj_L13_M8000_mumujj_2017_JesSFDown->Fill((Muon1+Muon2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)mumujj_L13_M8000_mumujj_2017_JerSFUp->Fill((Muon1+Muon2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)mumujj_L13_M8000_mumujj_2017_JerSFDown->Fill((Muon1+Muon2+BoostJet_JERdown).M(), wg);
  
  mumujj_L13_M8000_mumujj_PDFUp->Fill((Muon1+Muon2+BoostJet).M(), wg*1.7);      //comment for bkgs                 
  mumujj_L13_M8000_mumujj_PDFDown->Fill((Muon1+Muon2+BoostJet).M(), wg*0.3);  //comment for bkgs

  }

    //DY cr Mll in 150-300 GeV
    if (HLT_Mu == 1 && Muon_pt->at(0) > 150 && Muon_pt->at(1) > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(Muon_eta->at(1))<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1+Muon2).M() > 150 && (Muon1+Muon2).M() < 300 ){
    BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
    BoostJet_JESup.SetPtEtaPhiE(BoostedJet_pt->at(1), BoostedJet_eta->at(1), BoostedJet_phi->at(1),BoostedJet_energy->at(1));
    BoostJet_JESdown.SetPtEtaPhiE(BoostedJet_pt->at(2), BoostedJet_eta->at(2), BoostedJet_phi->at(2),BoostedJet_energy->at(2));
    BoostJet_JERup.SetPtEtaPhiE(BoostedJet_pt->at(3), BoostedJet_eta->at(3), BoostedJet_phi->at(3),BoostedJet_energy->at(3));
    BoostJet_JERdown.SetPtEtaPhiE(BoostedJet_pt->at(4), BoostedJet_eta->at(4), BoostedJet_phi->at(4),BoostedJet_energy->at(4));
    Muon1_ptCorr.SetPtEtaPhiE(Muon_pt_corr->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));
    Muon2_ptCorr.SetPtEtaPhiE(Muon_pt_corr->at(1), Muon_eta->at(1), Muon_phi->at(1),Muon_energy->at(1));
    mumujj_L13_M8000_DYcr_mumujj->Fill((Muon1+Muon2+BoostJet).M(), wg); 
    mumujj_L13_M8000_DYcr_mumujj_2017_AlphaRatio->Fill((Muon1+Muon2+BoostJet).M(), wg);
    mumujj_L13_M8000_DYcr_mumujj_2017_AlphaRatioUp->Fill((Muon1+Muon2+BoostJet).M(), wg);
    mumujj_L13_M8000_DYcr_mumujj_2017_AlphaRatioDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
    mumujj_L13_M8000_DYcr_mumujj_2017_SFUp->Fill((Muon1+Muon2+BoostJet).M(), wg_SFu);
    mumujj_L13_M8000_DYcr_mumujj_2017_SFDown->Fill((Muon1+Muon2+BoostJet).M(), wg_SFd);
    mumujj_L13_M8000_DYcr_mumujj_2017_PUUp->Fill((Muon1+Muon2+BoostJet).M(), wg_PUu);
    mumujj_L13_M8000_DYcr_mumujj_2017_PUDown->Fill((Muon1+Muon2+BoostJet).M(), wg_PUd);
    mumujj_L13_M8000_DYcr_mumujj_2017_PtCorrUp->Fill((Muon1_ptCorr+Muon2_ptCorr+BoostJet).M(), wg);
    mumujj_L13_M8000_DYcr_mumujj_2017_PtCorrDown->Fill((Muon1_ptCorr+Muon2_ptCorr+BoostJet).M(), wg);
    mumujj_L13_M8000_DYcr_mumujj_2017_PtResoUp->Fill((Muon1_ptResoUp+Muon2_ptResoUp+BoostJet).M(), wg);
    mumujj_L13_M8000_DYcr_mumujj_2017_PtResoDown->Fill((Muon1_ptResoDown+Muon2_ptResoDown+BoostJet).M(), wg);
  
    if(centralJesJer->at(0)==1)mumujj_L13_M8000_DYcr_mumujj_centralJesJer->Fill((Muon1+Muon2+BoostJet).M(), wg);
    if(JesSFup->at(1)==1)mumujj_L13_M8000_DYcr_mumujj_2017_JesSFUp->Fill((Muon1+Muon2+BoostJet_JESup).M(), wg);
    if(JesSFdown->at(2)==1)mumujj_L13_M8000_DYcr_mumujj_2017_JesSFDown->Fill((Muon1+Muon2+BoostJet_JESdown).M(), wg);
    if(JerSFup->at(3)==1)mumujj_L13_M8000_DYcr_mumujj_2017_JerSFUp->Fill((Muon1+Muon2+BoostJet_JERup).M(), wg);
    if(JerSFdown->at(4)==1)mumujj_L13_M8000_DYcr_mumujj_2017_JerSFDown->Fill((Muon1+Muon2+BoostJet_JERdown).M(), wg);  
    }

 }

  if (patElectron_pt->size() > 1 && numOfHighptEle==2 && numOfLooseMu==0 && numOfBoostedJets>=1){
   Electron1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   Electron2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energy->at(1));


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



   mumujj_L13_M8000_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   mumujj_L13_M8000_eejj_2017_AlphaRatio->Fill((Electron1+Electron2+BoostJet).M(), wg);
   mumujj_L13_M8000_eejj_2017_AlphaRatioUp->Fill((Electron1+Electron2+BoostJet).M(), wg);
   mumujj_L13_M8000_eejj_2017_AlphaRatioDown->Fill((Electron1+Electron2+BoostJet).M(), wg);
   mumujj_L13_M8000_eejj_2017_SFUp->Fill((Electron1+Electron2+BoostJet).M(), wg_SFu);
   mumujj_L13_M8000_eejj_2017_SFDown->Fill((Electron1+Electron2+BoostJet).M(), wg_SFd);
   mumujj_L13_M8000_eejj_2017_PUUp->Fill((Electron1+Electron2+BoostJet).M(), wg_PUu);
   mumujj_L13_M8000_eejj_2017_PUDown->Fill((Electron1+Electron2+BoostJet).M(), wg_PUd);
   mumujj_L13_M8000_eejj_2017_energyScaleUp->Fill((Ele1_ScaleUp+Ele2_ScaleUp+BoostJet).M(), wg);
   mumujj_L13_M8000_eejj_2017_energyScaleDown->Fill((Ele1_ScaleDown+Ele2_ScaleDown+BoostJet).M(), wg);
   mumujj_L13_M8000_eejj_2017_energySigmaUp->Fill((Ele1_SigmaUp+Ele2_SigmaUp+BoostJet).M(), wg);
   mumujj_L13_M8000_eejj_2017_energySigmaDown->Fill((Ele1_SigmaDown+Ele2_SigmaDown+BoostJet).M(), wg);
   if(centralJesJer->at(0)==1)mumujj_L13_M8000_eejj_2017_centralJesJer->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)mumujj_L13_M8000_eejj_2017_JesSFUp->Fill((Electron1+Electron2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)mumujj_L13_M8000_eejj_2017_JesSFDown->Fill((Electron1+Electron2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)mumujj_L13_M8000_eejj_2017_JerSFUp->Fill((Electron1+Electron2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)mumujj_L13_M8000_eejj_2017_JerSFDown->Fill((Electron1+Electron2+BoostJet_JERdown).M(), wg);
  
  mumujj_L13_M8000_eejj_PDFUp->Fill((Electron1+Electron2+BoostJet).M(), wg*1.7);      //comment for bkgs                 
  mumujj_L13_M8000_eejj_PDFDown->Fill((Electron1+Electron2+BoostJet).M(), wg*0.3);  //comment for bkgs

  }
  //DY cr 150-300 GeV
  if (HLT_Ele == 1 && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190 && (Electron1+Electron2).M() >150 && (Electron1+Electron2).M() < 300){
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
   mumujj_L13_M8000_DYcr_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   mumujj_L13_M8000_DYcr_eejj_2017_AlphaRatio->Fill((Electron1+Electron2+BoostJet).M(), wg);
   mumujj_L13_M8000_DYcr_eejj_2017_AlphaRatioUp->Fill((Electron1+Electron2+BoostJet).M(), wg);
   mumujj_L13_M8000_DYcr_eejj_2017_AlphaRatioDown->Fill((Electron1+Electron2+BoostJet).M(), wg);
   mumujj_L13_M8000_DYcr_eejj_2017_SFUp->Fill((Electron1+Electron2+BoostJet).M(), wg_SFu);
   mumujj_L13_M8000_DYcr_eejj_2017_SFDown->Fill((Electron1+Electron2+BoostJet).M(), wg_SFd);
   mumujj_L13_M8000_DYcr_eejj_2017_PUUp->Fill((Electron1+Electron2+BoostJet).M(), wg_PUu);
   mumujj_L13_M8000_DYcr_eejj_2017_PUDown->Fill((Electron1+Electron2+BoostJet).M(), wg_PUd);
   mumujj_L13_M8000_DYcr_eejj_2017_energyScaleUp->Fill((Ele1_ScaleUp+Ele2_ScaleUp+BoostJet).M(), wg);
   mumujj_L13_M8000_DYcr_eejj_2017_energyScaleDown->Fill((Ele1_ScaleDown+Ele2_ScaleDown+BoostJet).M(), wg);
   mumujj_L13_M8000_DYcr_eejj_2017_energySigmaUp->Fill((Ele1_SigmaUp+Ele2_SigmaUp+BoostJet).M(), wg);
   mumujj_L13_M8000_DYcr_eejj_2017_energySigmaDown->Fill((Ele1_SigmaDown+Ele2_SigmaDown+BoostJet).M(), wg);
   if(centralJesJer->at(0)==1)mumujj_L13_M8000_DYcr_eejj_centralJesJer->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)mumujj_L13_M8000_DYcr_eejj_2017_JesSFUp->Fill((Electron1+Electron2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)mumujj_L13_M8000_DYcr_eejj_2017_JesSFDown->Fill((Electron1+Electron2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)mumujj_L13_M8000_DYcr_eejj_2017_JerSFUp->Fill((Electron1+Electron2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)mumujj_L13_M8000_DYcr_eejj_2017_JerSFDown->Fill((Electron1+Electron2+BoostJet_JERdown).M(), wg); 
  }

 }

  
 
}

TFile *f = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2017-OldBinning/SR_syst_mumujj_L13_M8000_2017.root", "RECREATE");
//TFile *f2 = new TFile("plot/SR_syst_mumujj_L13_M8000_2017.root", "RECREATE");
mumujj_L13_M8000_eejj->Write();
mumujj_L13_M8000_eejj_2017_AlphaRatio->Write();
mumujj_L13_M8000_eejj_2017_AlphaRatioUp->Write();
mumujj_L13_M8000_eejj_2017_AlphaRatioDown->Write();
mumujj_L13_M8000_eejj_2017_SFUp->Write();
mumujj_L13_M8000_eejj_2017_SFDown->Write();
mumujj_L13_M8000_eejj_2017_PUUp->Write();
mumujj_L13_M8000_eejj_2017_PUDown->Write();
mumujj_L13_M8000_eejj_2017_centralJesJer->Write();
mumujj_L13_M8000_eejj_2017_JesSFUp->Write();
mumujj_L13_M8000_eejj_2017_JesSFDown->Write();
mumujj_L13_M8000_eejj_2017_JerSFUp->Write();
mumujj_L13_M8000_eejj_2017_JerSFDown->Write();
mumujj_L13_M8000_eejj_2017_energyScaleUp->Write();
mumujj_L13_M8000_eejj_2017_energyScaleDown->Write();
mumujj_L13_M8000_eejj_2017_energySigmaUp->Write();
mumujj_L13_M8000_eejj_2017_energySigmaDown->Write();

mumujj_L13_M8000_mumujj->Write();
mumujj_L13_M8000_mumujj_2017_AlphaRatio->Write();
mumujj_L13_M8000_mumujj_2017_AlphaRatioUp->Write();
mumujj_L13_M8000_mumujj_2017_AlphaRatioDown->Write();
mumujj_L13_M8000_mumujj_2017_SFUp->Write();
mumujj_L13_M8000_mumujj_2017_SFDown->Write();
mumujj_L13_M8000_mumujj_2017_PUUp->Write();
mumujj_L13_M8000_mumujj_2017_PUDown->Write();
mumujj_L13_M8000_mumujj_2017_centralJesJer->Write();
mumujj_L13_M8000_mumujj_2017_JesSFUp->Write();
mumujj_L13_M8000_mumujj_2017_JesSFDown->Write();
mumujj_L13_M8000_mumujj_2017_JerSFUp->Write();
mumujj_L13_M8000_mumujj_2017_JerSFDown->Write();
mumujj_L13_M8000_mumujj_2017_PtCorr->Write();
mumujj_L13_M8000_mumujj_2017_PtCorrDown->Write();
mumujj_L13_M8000_mumujj_2017_PtCorrUp->Write();
mumujj_L13_M8000_mumujj_2017_PtResoUp->Write();
mumujj_L13_M8000_mumujj_2017_PtResoDown->Write();

mumujj_L13_M8000_eejj_PDFUp->Write();
mumujj_L13_M8000_eejj_PDFDown->Write();
mumujj_L13_M8000_mumujj_PDFUp->Write();
mumujj_L13_M8000_mumujj_PDFDown->Write();


//DYcr 
mumujj_L13_M8000_DYcr_eejj->Write();
mumujj_L13_M8000_DYcr_eejj_2017_AlphaRatio->Write();
mumujj_L13_M8000_DYcr_eejj_2017_AlphaRatioUp->Write();
mumujj_L13_M8000_DYcr_eejj_2017_AlphaRatioDown->Write();
mumujj_L13_M8000_DYcr_eejj_2017_SFUp->Write();
mumujj_L13_M8000_DYcr_eejj_2017_SFDown->Write();
mumujj_L13_M8000_DYcr_eejj_2017_PUUp->Write();
mumujj_L13_M8000_DYcr_eejj_2017_PUDown->Write();
mumujj_L13_M8000_DYcr_eejj_centralJesJer->Write();
mumujj_L13_M8000_DYcr_eejj_2017_JesSFUp->Write();
mumujj_L13_M8000_DYcr_eejj_2017_JesSFDown->Write();
mumujj_L13_M8000_DYcr_eejj_2017_JerSFUp->Write();
mumujj_L13_M8000_DYcr_eejj_2017_JerSFDown->Write();
mumujj_L13_M8000_DYcr_eejj_2017_energyScaleUp->Write();
mumujj_L13_M8000_DYcr_eejj_2017_energyScaleDown->Write();
mumujj_L13_M8000_DYcr_eejj_2017_energySigmaUp->Write();
mumujj_L13_M8000_DYcr_eejj_2017_energySigmaDown->Write();
mumujj_L13_M8000_DYcr_mumujj->Write();
mumujj_L13_M8000_DYcr_mumujj_2017_AlphaRatio->Write();
mumujj_L13_M8000_DYcr_mumujj_2017_AlphaRatioUp->Write();
mumujj_L13_M8000_DYcr_mumujj_2017_AlphaRatioDown->Write();
mumujj_L13_M8000_DYcr_mumujj_2017_SFUp->Write();
mumujj_L13_M8000_DYcr_mumujj_2017_SFDown->Write();
mumujj_L13_M8000_DYcr_mumujj_2017_PUUp->Write();
mumujj_L13_M8000_DYcr_mumujj_2017_PUDown->Write();
mumujj_L13_M8000_DYcr_mumujj_centralJesJer->Write();
mumujj_L13_M8000_DYcr_mumujj_2017_JesSFUp->Write();
mumujj_L13_M8000_DYcr_mumujj_2017_JesSFDown->Write();
mumujj_L13_M8000_DYcr_mumujj_2017_JerSFUp->Write();
mumujj_L13_M8000_DYcr_mumujj_2017_JerSFDown->Write();
mumujj_L13_M8000_DYcr_mumujj_2017_PtCorrDown->Write();
mumujj_L13_M8000_DYcr_mumujj_2017_PtCorrUp->Write(); 
mumujj_L13_M8000_DYcr_mumujj_2017_PtResoUp->Write();
mumujj_L13_M8000_DYcr_mumujj_2017_PtResoDown->Write();

f->Write();
f->Close();

}
 
