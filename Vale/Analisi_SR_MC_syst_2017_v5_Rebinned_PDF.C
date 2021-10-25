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

float extraSmearingSigma(float eta, float p) {
  if     (p <   50.) return (fabs(eta) < 0.9 ? 0.0046 : 0.0087);
  else if(p <  100.) return (fabs(eta) < 0.9 ? 0.0060 : 0.0096);
  else if(p <  200.) return (fabs(eta) < 0.9 ? 0.0078 : 0.0110);
  else if(p <  300.) return (fabs(eta) < 0.9 ? 0.0105 : 0.0124);
  else if(p <  400.) return (fabs(eta) < 0.9 ? 0.0124 : 0.0147);
  else if(p <  500.) return (fabs(eta) < 0.9 ? 0.0147 : 0.0165);
  else if(p <  700.) return (fabs(eta) < 0.9 ? 0.0174 : 0.0192);
  else if(p < 1000.) return (fabs(eta) < 0.9 ? 0.0197 : 0.0234);
  else if(p < 1500.) return (fabs(eta) < 0.9 ? 0.0229 : 0.0293);
  else if(p < 2000.) return (fabs(eta) < 0.9 ? 0.0252 : 0.0357);
  else               return (fabs(eta) < 0.9 ? 0.0266 : 0.0399);
}


//void filename_()
void Analisi_SR_MC_syst_2017_v5_Rebinned_PDF(){


TChain *a_ = new TChain("BOOM");

//a_->Add("/eos/user/v/vmariani/NTuples/HN_2017/Syst_ALL_newMuonSF/eejj_L13_M1000_2017.root");

a_->Add("/eos/user/v/vmariani/NTuples/HN_2017/25062021/eejj_L13_M1000_2017.root");
//a_->Add("/eos/user/m/mpresill/CMS/HN_Reload/rootplized_samples_2017_syst/Vale_HT_processing/eejj_L13_M1000_QCD_2017.root");  //this folder is for other with QCD

//inputFile

int HLT_Ele, HLT_Photon200, HLT_Ele115, HLT_Ele35, HLT_Mu, HLT_Mu50, HLT_OldMu100, HLT_TkMu50, HLT_TkMu100;
double muejj_l, emujj_l;
std:vector<double>* patElectron_pt; patElectron_pt=0;
vector<double>* patElectron_eta; patElectron_eta=0;
vector<double>* patElectron_phi; patElectron_phi=0;
vector<double>* patElectron_ecalTrkEnergyPostCorr; patElectron_ecalTrkEnergyPostCorr=0;
vector<double>* patElectron_energy; patElectron_energy=0;
vector<int>* patElectron_charge; patElectron_charge=0;
//vector<double>* Muon_pt_tunePbt_Roc; Muon_pt_tunePbt_Roc=0;
//vector<double>* Muon_pt_tunePbt_Roc_corr; Muon_pt_tunePbt_Roc_corr=0;
vector<double>* Muon_pt_tunePbt_Roc; Muon_pt_tunePbt_Roc=0;
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
double EVENT_prefireWeight, EVENT_prefireWeightUp, EVENT_prefireWeightDown;
int nBestVtx;
double EVENT_PDFv1WeightUp, EVENT_PDFv1WeightDown, EVENT_PDFv1WeightCentral, EVENT_PDFv1WeightMean, EVENT_PDFv1WeightStdDev;
double EVENT_PDFv2WeightUp, EVENT_PDFv2WeightDown, EVENT_PDFv2WeightCentral, EVENT_PDFv2WeightMean, EVENT_PDFv2WeightStdDev;
double EVENT_PDFv3WeightUp, EVENT_PDFv3WeightDown, EVENT_PDFv3WeightCentral, EVENT_PDFv3WeightMean, EVENT_PDFv3WeightStdDev;
double EVENT_PDFv4WeightUp, EVENT_PDFv4WeightDown, EVENT_PDFv4WeightCentral, EVENT_PDFv4WeightMean, EVENT_PDFv4WeightStdDev;
double EVENT_PDFv5WeightUp, EVENT_PDFv5WeightDown, EVENT_PDFv5WeightCentral, EVENT_PDFv5WeightMean, EVENT_PDFv5WeightStdDev;
double EVENT_PDFv6WeightUp, EVENT_PDFv6WeightDown, EVENT_PDFv6WeightCentral, EVENT_PDFv6WeightMean, EVENT_PDFv6WeightStdDev;

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


//TBranch *a_Muon_pt_tunePbt_Roc=a_->GetBranch("Muon_pt_tunePbt_Roc");
//TBranch *a_Muon_pt_tunePbt_Roc_corr=a_->GetBranch("Muon_pt_tunePbt_Roc_corr");
TBranch *a_Muon_pt_tunePbt_Roc=a_->GetBranch("Muon_pt_tunePbt_Roc");
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

TBranch *a_EVENT_prefireWeight=a_->GetBranch("EVENT_prefireWeight");
TBranch *a_EVENT_prefireWeightUp=a_->GetBranch("EVENT_prefireWeightUp");
TBranch *a_EVENT_prefireWeightDown=a_->GetBranch("EVENT_prefireWeightDown");

TBranch *a_EVENT_PDFv1WeightUp=a_->GetBranch("EVENT_PDFv1WeightUp");
TBranch *a_EVENT_PDFv1WeightDown=a_->GetBranch("EVENT_PDFv1WeightDown");
TBranch *a_EVENT_PDFv1WeightCentral=a_->GetBranch("EVENT_PDFv1WeightCentral");
TBranch *a_EVENT_PDFv1WeightMean=a_->GetBranch("EVENT_PDFv1WeightMean");
TBranch *a_EVENT_PDFv1WeightStdDev=a_->GetBranch("EVENT_PDFv1WeightStdDev");

TBranch *a_EVENT_PDFv2WeightUp=a_->GetBranch("EVENT_PDFv2WeightUp");
TBranch *a_EVENT_PDFv2WeightDown=a_->GetBranch("EVENT_PDFv2WeightDown");
TBranch *a_EVENT_PDFv2WeightCentral=a_->GetBranch("EVENT_PDFv2WeightCentral");
TBranch *a_EVENT_PDFv2WeightMean=a_->GetBranch("EVENT_PDFv2WeightMean");
TBranch *a_EVENT_PDFv2WeightStdDev=a_->GetBranch("EVENT_PDFv2WeightStdDev");

TBranch *a_EVENT_PDFv3WeightUp=a_->GetBranch("EVENT_PDFv3WeightUp");
TBranch *a_EVENT_PDFv3WeightDown=a_->GetBranch("EVENT_PDFv3WeightDown");
TBranch *a_EVENT_PDFv3WeightCentral=a_->GetBranch("EVENT_PDFv3WeightCentral");
TBranch *a_EVENT_PDFv3WeightMean=a_->GetBranch("EVENT_PDFv3WeightMean");
TBranch *a_EVENT_PDFv3WeightStdDev=a_->GetBranch("EVENT_PDFv3WeightStdDev");

TBranch *a_EVENT_PDFv4WeightUp=a_->GetBranch("EVENT_PDFv4WeightUp");
TBranch *a_EVENT_PDFv4WeightDown=a_->GetBranch("EVENT_PDFv4WeightDown");
TBranch *a_EVENT_PDFv4WeightCentral=a_->GetBranch("EVENT_PDFv4WeightCentral");
TBranch *a_EVENT_PDFv4WeightMean=a_->GetBranch("EVENT_PDFv4WeightMean");
TBranch *a_EVENT_PDFv4WeightStdDev=a_->GetBranch("EVENT_PDFv4WeightStdDev");

TBranch *a_EVENT_PDFv5WeightUp=a_->GetBranch("EVENT_PDFv5WeightUp");
TBranch *a_EVENT_PDFv5WeightDown=a_->GetBranch("EVENT_PDFv5WeightDown");
TBranch *a_EVENT_PDFv5WeightCentral=a_->GetBranch("EVENT_PDFv5WeightCentral");
TBranch *a_EVENT_PDFv5WeightMean=a_->GetBranch("EVENT_PDFv5WeightMean");
TBranch *a_EVENT_PDFv5WeightStdDev=a_->GetBranch("EVENT_PDFv5WeightStdDev");

TBranch *a_EVENT_PDFv6WeightUp=a_->GetBranch("EVENT_PDFv6WeightUp");
TBranch *a_EVENT_PDFv6WeightDown=a_->GetBranch("EVENT_PDFv6WeightDown");
TBranch *a_EVENT_PDFv6WeightCentral=a_->GetBranch("EVENT_PDFv6WeightCentral");
TBranch *a_EVENT_PDFv6WeightMean=a_->GetBranch("EVENT_PDFv6WeightMean");
TBranch *a_EVENT_PDFv6WeightStdDev=a_->GetBranch("EVENT_PDFv6WeightStdDev");

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

//a_Muon_pt_tunePbt_Roc->SetAddress(&Muon_pt_tunePbt_Roc);
//a_Muon_pt_tunePbt_Roc_corr->SetAddress(&Muon_pt_tunePbt_Roc_corr);
a_Muon_pt_tunePbt_Roc->SetAddress(&Muon_pt_tunePbt_Roc);
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

a_EVENT_prefireWeight->SetAddress(&EVENT_prefireWeight);
a_EVENT_prefireWeightUp->SetAddress(&EVENT_prefireWeightUp);
a_EVENT_prefireWeightDown->SetAddress(&EVENT_prefireWeightDown);

a_EVENT_PDFv1WeightUp->SetAddress(&EVENT_PDFv1WeightUp);
a_EVENT_PDFv1WeightDown->SetAddress(&EVENT_PDFv1WeightDown);
a_EVENT_PDFv1WeightCentral->SetAddress(&EVENT_PDFv1WeightCentral);
a_EVENT_PDFv1WeightMean->SetAddress(&EVENT_PDFv1WeightMean);
a_EVENT_PDFv1WeightStdDev->SetAddress(&EVENT_PDFv1WeightStdDev);

a_EVENT_PDFv2WeightUp->SetAddress(&EVENT_PDFv2WeightUp);
a_EVENT_PDFv2WeightDown->SetAddress(&EVENT_PDFv2WeightDown);
a_EVENT_PDFv2WeightCentral->SetAddress(&EVENT_PDFv2WeightCentral);
a_EVENT_PDFv2WeightMean->SetAddress(&EVENT_PDFv2WeightMean);
a_EVENT_PDFv2WeightStdDev->SetAddress(&EVENT_PDFv2WeightStdDev);

a_EVENT_PDFv3WeightUp->SetAddress(&EVENT_PDFv3WeightUp);
a_EVENT_PDFv3WeightDown->SetAddress(&EVENT_PDFv3WeightDown);
a_EVENT_PDFv3WeightCentral->SetAddress(&EVENT_PDFv3WeightCentral);
a_EVENT_PDFv3WeightMean->SetAddress(&EVENT_PDFv3WeightMean);
a_EVENT_PDFv3WeightStdDev->SetAddress(&EVENT_PDFv3WeightStdDev);

a_EVENT_PDFv4WeightUp->SetAddress(&EVENT_PDFv4WeightUp);
a_EVENT_PDFv4WeightDown->SetAddress(&EVENT_PDFv4WeightDown);
a_EVENT_PDFv4WeightCentral->SetAddress(&EVENT_PDFv4WeightCentral);
a_EVENT_PDFv4WeightMean->SetAddress(&EVENT_PDFv4WeightMean);
a_EVENT_PDFv4WeightStdDev->SetAddress(&EVENT_PDFv4WeightStdDev);

a_EVENT_PDFv5WeightUp->SetAddress(&EVENT_PDFv5WeightUp);
a_EVENT_PDFv5WeightDown->SetAddress(&EVENT_PDFv5WeightDown);
a_EVENT_PDFv5WeightCentral->SetAddress(&EVENT_PDFv5WeightCentral);
a_EVENT_PDFv5WeightMean->SetAddress(&EVENT_PDFv5WeightMean);
a_EVENT_PDFv5WeightStdDev->SetAddress(&EVENT_PDFv5WeightStdDev);

a_EVENT_PDFv6WeightUp->SetAddress(&EVENT_PDFv6WeightUp);
a_EVENT_PDFv6WeightDown->SetAddress(&EVENT_PDFv6WeightDown);
a_EVENT_PDFv6WeightCentral->SetAddress(&EVENT_PDFv6WeightCentral);
a_EVENT_PDFv6WeightMean->SetAddress(&EVENT_PDFv6WeightMean);
a_EVENT_PDFv6WeightStdDev->SetAddress(&EVENT_PDFv6WeightStdDev);

//new bin
//const double asymbins[9] = {0,200,400,600,800,1000,1400,2000,10000};

//old bin
const double asymbins[9] = {0,200,400,600,800,1000,1400,2000,10000};

TH1D *eejj_L13_M1000_eejj_SS = new TH1D("eejj_L13_M1000_eejj_SS", "eejj_L13_M1000_eejj_SS", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_OS = new TH1D("eejj_L13_M1000_eejj_OS", "eejj_L13_M1000_eejj_OS", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_SS = new TH1D("eejj_L13_M1000_mumujj_SS", "eejj_L13_M1000_mumujj_SS", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_OS = new TH1D("eejj_L13_M1000_mumujj_OS", "eejj_L13_M1000_mumujj_OS", 8, asymbins);
TH1D *eejj_L13_M1000_Zpeak_eejj_SS = new TH1D("eejj_L13_M1000_Zpeak_eejj_SS", "eejj_L13_M1000_Zpeak_eejj_SS", 8, asymbins);
TH1D *eejj_L13_M1000_Zpeak_eejj_OS = new TH1D("eejj_L13_M1000_Zpeak_eejj_OS", "eejj_L13_M1000_Zpeak_eejj_OS", 8, asymbins);
TH1D *eejj_L13_M1000_Zpeak_mumujj_SS = new TH1D("eejj_L13_M1000_Zpeak_mumujj_SS", "eejj_L13_M1000_Zpeak_mumujj_SS", 8, asymbins);
TH1D *eejj_L13_M1000_Zpeak_mumujj_OS = new TH1D("eejj_L13_M1000_Zpeak_mumujj_OS", "eejj_L13_M1000_Zpeak_mumujj_OS", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_SS = new TH1D("eejj_L13_M1000_DYcr_eejj_SS", "eejj_L13_M1000_DYcr_eejj_SS", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_OS = new TH1D("eejj_L13_M1000_DYcr_eejj_OS", "eejj_L13_M1000_DYcr_eejj_OS", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_SS = new TH1D("eejj_L13_M1000_DYcr_mumujj_SS", "eejj_L13_M1000_DYcr_mumujj_SS", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_OS = new TH1D("eejj_L13_M1000_DYcr_mumujj_OS", "eejj_L13_M1000_DYcr_mumujj_OS", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_SS = new TH1D("eejj_L13_M1000_TTtWcr_llJ_SS", "eejj_L13_M1000_TTtWcr_llJ_SS", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_OS = new TH1D("eejj_L13_M1000_TTtWcr_llJ_OS", "eejj_L13_M1000_TTtWcr_llJ_OS", 8, asymbins);

TH1D *eejj_L13_M1000_HTmumu = new TH1D ("eejj_L13_M1000_HTmumu", "eejj_L13_M1000_HTmumu", 100, 0, 5000);
TH1D *eejj_L13_M1000_HTmumu_BB = new TH1D ("eejj_L13_M1000_HTmumu_BB", "eejj_L13_M1000_HTmumu_BB", 100, 0, 5000);
TH1D *eejj_L13_M1000_HTmumu_BE = new TH1D ("eejj_L13_M1000_HTmumu_BE", "eejj_L13_M1000_HTmumu_BE", 100, 0, 5000);
TH1D *eejj_L13_M1000_HTmumu_EE = new TH1D ("eejj_L13_M1000_HTmumu_EE", "eejj_L13_M1000_HTmumu_EE", 100, 0, 5000);
TH1D *eejj_L13_M1000_Mmumu = new TH1D ("eejj_L13_M1000_Mmumu", "eejj_L13_M1000_Mmumu", 100, 0, 1000);
TH1D *eejj_L13_M1000_Mmumu_BB = new TH1D ("eejj_L13_M1000_Mmumu_BB", "eejj_L13_M1000_Mmumu_BB", 100, 0, 1000);
TH1D *eejj_L13_M1000_Mmumu_BE = new TH1D ("eejj_L13_M1000_Mmumu_BE", "eejj_L13_M1000_Mmumu_BE", 100, 0, 1000);
TH1D *eejj_L13_M1000_Mmumu_EE = new TH1D ("eejj_L13_M1000_Mmumu_EE", "eejj_L13_M1000_Mmumu_EE", 100, 0, 1000);
TH1D *eejj_L13_M1000_mumujj_Roc = new TH1D ("eejj_L13_M1000_mumujj_Roc", "eejj_L13_M1000_mumujj_Roc", 8, asymbins );
TH1D *eejj_L13_M1000_mumujj = new TH1D ("eejj_L13_M1000_mumujj", "eejj_L13_M1000_mumujj", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_BB = new TH1D ("eejj_L13_M1000_mumujj_BB", "eejj_L13_M1000_mumujj_BB", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_BE = new TH1D ("eejj_L13_M1000_mumujj_BE", "eejj_L13_M1000_mumujj_BE", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_EE = new TH1D ("eejj_L13_M1000_mumujj_EE", "eejj_L13_M1000_mumujj_EE", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2017_AlphaRatio = new TH1D ("eejj_L13_M1000_mumujj_2017_AlphaRatio", "eejj_L13_M1000_mumujj_2017_AlphaRatio", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2017_AlphaRatio_BB = new TH1D ("eejj_L13_M1000_mumujj_2017_AlphaRatio_BB", "eejj_L13_M1000_mumujj_2017_AlphaRatio_BB", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2017_AlphaRatio_BE = new TH1D ("eejj_L13_M1000_mumujj_2017_AlphaRatio_BE", "eejj_L13_M1000_mumujj_2017_AlphaRatio_BE", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2017_AlphaRatio_EE = new TH1D ("eejj_L13_M1000_mumujj_2017_AlphaRatio_EE", "eejj_L13_M1000_mumujj_2017_AlphaRatio_EE", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2017_AlphaRatioDown = new TH1D ("eejj_L13_M1000_mumujj_2017_AlphaRatioDown", "eejj_L13_M1000_mumujj_2017_AlphaRatioDown", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2017_AlphaRatioUp = new TH1D ("eejj_L13_M1000_mumujj_2017_AlphaRatioUp", "eejj_L13_M1000_mumujj_2017_AlphaRatioUp", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2017_SFUp = new TH1D ("eejj_L13_M1000_mumujj_2017_SFUp", "eejj_L13_M1000_mumujj_2017_SFUp", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2017_SFDown = new TH1D ("eejj_L13_M1000_mumujj_2017_SFDown", "eejj_L13_M1000_mumujj_2017_SFDown", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2017_PUUp = new TH1D ("eejj_L13_M1000_mumujj_2017_PUUp", "eejj_L13_M1000_mumujj_2017_PUUp", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2017_PUDown = new TH1D ("eejj_L13_M1000_mumujj_2017_PUDown", "eejj_L13_M1000_mumujj_2017_PUDown", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2017_centralJesJer = new TH1D ("eejj_L13_M1000_mumujj_2017_centralJesJer", "eejj_L13_M1000_mumujj_2017_centralJesJer", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2017_JesSFUp = new TH1D ("eejj_L13_M1000_mumujj_2017_JesSFUp", "eejj_L13_M1000_mumujj_2017_JesSFUp", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2017_JesSFDown = new TH1D ("eejj_L13_M1000_mumujj_2017_JesSFDown", "eejj_L13_M1000_mumujj_2017_JesSFDown", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2017_JerSFUp = new TH1D ("eejj_L13_M1000_mumujj_2017_JerSFUp", "eejj_L13_M1000_mumujj_2017_JerSFUp", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2017_JerSFDown = new TH1D ("eejj_L13_M1000_mumujj_2017_JerSFDown", "eejj_L13_M1000_mumujj_2017_JerSFDown", 8, asymbins);
//TH1D *eejj_L13_M1000_mumujj_2017_PtCorr = new TH1D ("eejj_L13_M1000_mumujj_2017_PtCorr", "eejj_L13_M1000_mumujj_2017_PtCorr", 8, asymbins);
//TH1D *eejj_L13_M1000_mumujj_2017_PtCorrDown = new TH1D ("eejj_L13_M1000_mumujj_2017_PtCorrDown", "eejj_L13_M1000_mumujj_2017_PtCorrDown", 8, asymbins);
//TH1D *eejj_L13_M1000_mumujj_2017_PtCorrUp = new TH1D ("eejj_L13_M1000_mumujj_2017_PtCorrUp", "eejj_L13_M1000_mumujj_2017_PtCorrUp", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2017_PtResoUp  = new TH1D ("eejj_L13_M1000_mumujj_2017_PtResoUp", "eejj_L13_M1000_mumujj_2017_PtResoUp", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2017_PtResoDown  = new TH1D ("eejj_L13_M1000_mumujj_2017_PtResoDown", "eejj_L13_M1000_mumujj_2017_PtResoDown", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2017_PtReso2Up  = new TH1D ("eejj_L13_M1000_mumujj_2017_PtReso2Up", "eejj_L13_M1000_mumujj_2017_PtReso2Up", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2017_PtReso2Down  = new TH1D ("eejj_L13_M1000_mumujj_2017_PtReso2Down", "eejj_L13_M1000_mumujj_2017_PtReso2Down", 8, asymbins);

TH1D *eejj_L13_M1000_Mee = new TH1D ("eejj_L13_M1000_Mee", "eejj_L13_M1000_Mee", 100, 0, 1000);
TH1D *eejj_L13_M1000_Mee_BB = new TH1D ("eejj_L13_M1000_Mee_BB", "eejj_L13_M1000_Mee_BB", 100, 0, 1000);
TH1D *eejj_L13_M1000_Mee_BE = new TH1D ("eejj_L13_M1000_Mee_BE", "eejj_L13_M1000_Mee_BE", 100, 0, 1000);
TH1D *eejj_L13_M1000_Mee_EE = new TH1D ("eejj_L13_M1000_Mee_EE", "eejj_L13_M1000_Mee_EE", 100, 0, 1000);
TH1D *eejj_L13_M1000_HTee = new TH1D ("eejj_L13_M1000_HTee", "eejj_L13_M1000_HTee", 100, 0, 5000);
TH1D *eejj_L13_M1000_HTee_BB = new TH1D ("eejj_L13_M1000_HTee_BB", "eejj_L13_M1000_HTee_BB", 100, 0, 5000);
TH1D *eejj_L13_M1000_HTee_BE = new TH1D ("eejj_L13_M1000_HTee_BE", "eejj_L13_M1000_HTee_BE", 100, 0, 5000);
TH1D *eejj_L13_M1000_HTee_EE = new TH1D ("eejj_L13_M1000_HTee_EE", "eejj_L13_M1000_HTee_EE", 100, 0, 5000);
TH1D *eejj_L13_M1000_eejj_ele1_ecalTrkEnergyPostCorr = new TH1D ("eejj_L13_M1000_eejj_ele1_ecalTrkEnergyPostCorr", "eejj_L13_M1000_eejj_ele1_ecalTrkEnergyPostCorr", 100, 0, 1000);
TH1D *eejj_L13_M1000_eejj_ele2_ecalTrkEnergyPostCorr = new TH1D ("eejj_L13_M1000_eejj_ele2_ecalTrkEnergyPostCorr", "eejj_L13_M1000_eejj_ele2_ecalTrkEnergyPostCorr", 100, 0, 1000);
TH1D *eejj_L13_M1000_eejj_ele1_energy = new TH1D ("eejj_L13_M1000_eejj_ele1_energy", "eejj_L13_M1000_eejj_ele1_energy", 100, 0, 1000);
TH1D *eejj_L13_M1000_eejj_ele2_energy = new TH1D ("eejj_L13_M1000_eejj_ele2_energy", "eejj_L13_M1000_eejj_ele2_energy", 100, 0, 1000);
TH1D *eejj_L13_M1000_eejj = new TH1D ("eejj_L13_M1000_eejj", "eejj_L13_M1000_eejj", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_BB = new TH1D ("eejj_L13_M1000_eejj_BB", "eejj_L13_M1000_eejj_BB", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_BE = new TH1D ("eejj_L13_M1000_eejj_BE", "eejj_L13_M1000_eejj_BE", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_EE = new TH1D ("eejj_L13_M1000_eejj_EE", "eejj_L13_M1000_eejj_EE", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2017_AlphaRatio = new TH1D ("eejj_L13_M1000_eejj_2017_AlphaRatio", "eejj_L13_M1000_eejj_2017_AlphaRatio", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2017_AlphaRatio_BB = new TH1D ("eejj_L13_M1000_eejj_2017_AlphaRatio_BB", "eejj_L13_M1000_eejj_2017_AlphaRatio_BB", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2017_AlphaRatio_BE = new TH1D ("eejj_L13_M1000_eejj_2017_AlphaRatio_BE", "eejj_L13_M1000_eejj_2017_AlphaRatio_BE", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2017_AlphaRatio_EE = new TH1D ("eejj_L13_M1000_eejj_2017_AlphaRatio_EE", "eejj_L13_M1000_eejj_2017_AlphaRatio_EE", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2017_AlphaRatioDown = new TH1D ("eejj_L13_M1000_eejj_2017_AlphaRatioDown", "eejj_L13_M1000_eejj_2017_AlphaRatioDown", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2017_AlphaRatioUp = new TH1D ("eejj_L13_M1000_eejj_2017_AlphaRatioUp", "eejj_L13_M1000_eejj_2017_AlphaRatioUp", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2017_SFUp = new TH1D ("eejj_L13_M1000_eejj_2017_SFUp", "eejj_L13_M1000_eejj_2017_SFUp", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2017_SFDown = new TH1D ("eejj_L13_M1000_eejj_2017_SFDown", "eejj_L13_M1000_eejj_2017_SFDown", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2017_PUUp = new TH1D ("eejj_L13_M1000_eejj_2017_PUUp", "eejj_L13_M1000_eejj_2017_PUUp", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2017_PUDown = new TH1D ("eejj_L13_M1000_eejj_2017_PUDown", "eejj_L13_M1000_eejj_2017_PUDown", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2017_centralJesJer = new TH1D ("eejj_L13_M1000_eejj_2017_centralJesJer", "eejj_L13_M1000_eejj_2017_centralJesJer", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2017_JesSFUp = new TH1D ("eejj_L13_M1000_eejj_2017_JesSFUp", "eejj_L13_M1000_eejj_2017_JesSFUp", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2017_JesSFDown = new TH1D ("eejj_L13_M1000_eejj_2017_JesSFDown", "eejj_L13_M1000_eejj_2017_JesSFDown", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2017_JerSFUp = new TH1D ("eejj_L13_M1000_eejj_2017_JerSFUp", "eejj_L13_M1000_eejj_2017_JerSFUp", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2017_JerSFDown = new TH1D ("eejj_L13_M1000_eejj_2017_JerSFDown", "eejj_L13_M1000_eejj_2017_JerSFDown", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_energyScaleUp = new TH1D ("eejj_L13_M1000_eejj_energyScaleUp", "eejj_L13_M1000_eejj_energyScaleUp", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_energyScaleDown = new TH1D ("eejj_L13_M1000_eejj_energyScaleDown", "eejj_L13_M1000_eejj_energyScaleDown", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2017_energySigmaUp = new TH1D ("eejj_L13_M1000_eejj_2017_energySigmaUp", "eejj_L13_M1000_eejj_2017_energySigmaUp", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2017_energySigmaDown = new TH1D ("eejj_L13_M1000_eejj_2017_energySigmaDown", "eejj_L13_M1000_eejj_2017_energySigmaDown", 8, asymbins);

//PDF uncertaintes for signal samples
TH1D *eejj_L13_M1000_mumujj_PDFUp = new TH1D ("eejj_L13_M1000_mumujj_PDFUp", "eejj_L13_M1000_mumujj_PDFUp", 8, asymbins);   //PDF
TH1D *eejj_L13_M1000_mumujj_PDFDown = new TH1D ("eejj_L13_M1000_mumujj_PDFDown", "eejj_L13_M1000_mumujj_PDFDown", 8, asymbins); //PDF
TH1D *eejj_L13_M1000_eejj_PDFUp = new TH1D ("eejj_L13_M1000_eejj_PDFUp", "eejj_L13_M1000_eejj_PDFUp", 8, asymbins); //PDF
TH1D *eejj_L13_M1000_eejj_PDFDown = new TH1D ("eejj_L13_M1000_eejj_PDFDown", "eejj_L13_M1000_eejj_PDFDown", 8, asymbins); //PDF

//DY CR Zpeak (mll in 60-120 GeV)
TH1D *eejj_L13_M1000_ZpeakMll_mumujj = new TH1D ("eejj_L13_M1000_ZpeakMll_mumujj", "eejj_L13_M1000_ZpeakMll_mumujj", 60,60,120);
TH1D *eejj_L13_M1000_ZpeakMll_mumujj_BB = new TH1D ("eejj_L13_M1000_ZpeakMll_mumujj_BB", "eejj_L13_M1000_ZpeakMll_mumujj_BB", 60,60,120);
TH1D *eejj_L13_M1000_ZpeakMll_mumujj_BE = new TH1D ("eejj_L13_M1000_ZpeakMll_mumujj_BE", "eejj_L13_M1000_ZpeakMll_mumujj_BE", 60,60,120);
TH1D *eejj_L13_M1000_ZpeakMll_mumujj_EE = new TH1D ("eejj_L13_M1000_ZpeakMll_mumujj_EE", "eejj_L13_M1000_ZpeakMll_mumujj_EE", 60,60,120);
TH1D *eejj_L13_M1000_Zpeak_mumujj = new TH1D ("eejj_L13_M1000_Zpeak_mumujj", "eejj_L13_M1000_Zpeak_mumujj", 8, asymbins);
TH1D *eejj_L13_M1000_Zpeak_mumujj_BB = new TH1D ("eejj_L13_M1000_Zpeak_mumujj_BB", "eejj_L13_M1000_Zpeak_mumujj_BB", 8, asymbins);
TH1D *eejj_L13_M1000_Zpeak_mumujj_BE = new TH1D ("eejj_L13_M1000_Zpeak_mumujj_BE", "eejj_L13_M1000_Zpeak_mumujj_BE", 8, asymbins);
TH1D *eejj_L13_M1000_Zpeak_mumujj_EE = new TH1D ("eejj_L13_M1000_Zpeak_mumujj_EE", "eejj_L13_M1000_Zpeak_mumujj_EE", 8, asymbins);
TH1D *eejj_L13_M1000_ZpeakMll_eejj = new TH1D ("eejj_L13_M1000_ZpeakMll_eejj", "eejj_L13_M1000_ZpeakMll_eejj", 60,60,120);
TH1D *eejj_L13_M1000_ZpeakMll_eejj_BB = new TH1D ("eejj_L13_M1000_ZpeakMll_eejj_BB", "eejj_L13_M1000_ZpeakMll_eejj_BB", 60,60,120);
TH1D *eejj_L13_M1000_ZpeakMll_eejj_BE = new TH1D ("eejj_L13_M1000_ZpeakMll_eejj_BE", "eejj_L13_M1000_ZpeakMll_eejj_BE", 60,60,120);
TH1D *eejj_L13_M1000_ZpeakMll_eejj_EE = new TH1D ("eejj_L13_M1000_ZpeakMll_eejj_EE", "eejj_L13_M1000_ZpeakMll_eejj_EE", 60,60,120);
TH1D *eejj_L13_M1000_Zpeak_eejj = new TH1D ("eejj_L13_M1000_Zpeak_eejj", "eejj_L13_M1000_Zpeak_eejj", 8, asymbins);
TH1D *eejj_L13_M1000_Zpeak_eejj_BB = new TH1D ("eejj_L13_M1000_Zpeak_eejj_BB", "eejj_L13_M1000_Zpeak_eejj_BB", 8, asymbins);
TH1D *eejj_L13_M1000_Zpeak_eejj_BE = new TH1D ("eejj_L13_M1000_Zpeak_eejj_BE", "eejj_L13_M1000_Zpeak_eejj_BE", 8, asymbins);
TH1D *eejj_L13_M1000_Zpeak_eejj_EE = new TH1D ("eejj_L13_M1000_Zpeak_eejj_EE", "eejj_L13_M1000_Zpeak_eejj_EE", 8, asymbins);
TH1D *eejj_L13_M1000_Zpeak_mumu_pt = new TH1D ("eejj_L13_M1000_Zpeak_mumu_pt", "eejj_L13_M1000_Zpeak_mumu_pt", 100, 0, 1000);
TH1D *eejj_L13_M1000_Zpeak_mumu_pt_BB = new TH1D ("eejj_L13_M1000_Zpeak_mumu_pt_BB", "eejj_L13_M1000_Zpeak_mumu_pt_BB", 100, 0, 1000);
TH1D *eejj_L13_M1000_Zpeak_mumu_pt_BE = new TH1D ("eejj_L13_M1000_Zpeak_mumu_pt_BE", "eejj_L13_M1000_Zpeak_mumu_pt_BE", 100, 0, 1000);
TH1D *eejj_L13_M1000_Zpeak_mumu_pt_EE = new TH1D ("eejj_L13_M1000_Zpeak_mumu_pt_EE", "eejj_L13_M1000_Zpeak_mumu_pt_EE", 100, 0, 1000);
TH1D *eejj_L13_M1000_Zpeak_ee_pt = new TH1D ("eejj_L13_M1000_Zpeak_ee_pt", "eejj_L13_M1000_Zpeak_ee_pt", 100, 0, 1000);
TH1D *eejj_L13_M1000_Zpeak_ee_pt_BB = new TH1D ("eejj_L13_M1000_Zpeak_ee_pt_BB", "eejj_L13_M1000_Zpeak_ee_pt_BB", 100, 0, 1000);
TH1D *eejj_L13_M1000_Zpeak_ee_pt_BE = new TH1D ("eejj_L13_M1000_Zpeak_ee_pt_BE", "eejj_L13_M1000_Zpeak_ee_pt_BE", 100, 0, 1000);
TH1D *eejj_L13_M1000_Zpeak_ee_pt_EE = new TH1D ("eejj_L13_M1000_Zpeak_ee_pt_EE", "eejj_L13_M1000_Zpeak_ee_pt_EE", 100, 0, 1000);

//DY CR (mll in 150-300 GeV)
TH1D *Mmumu_DYcr = new TH1D ("Mmumu_DYcr", "Mmumu_DYcr", 50, 150, 300);
TH1D *Mmumu_DYcr_BB = new TH1D ("Mmumu_DYcr_BB", "Mmumu_DYcr_BB", 50, 150, 300);
TH1D *Mmumu_DYcr_BE = new TH1D ("Mmumu_DYcr_BE", "Mmumu_DYcr_BE", 50, 150, 300);
TH1D *Mmumu_DYcr_EE = new TH1D ("Mmumu_DYcr_EE", "Mmumu_DYcr_EE", 50, 150, 300);
TH1D *eejj_L13_M1000_DYcr_mumujj = new TH1D ("eejj_L13_M1000_DYcr_mumujj", "eejj_L13_M1000_DYcr_mumujj", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_BB = new TH1D ("eejj_L13_M1000_DYcr_mumujj_BB", "eejj_L13_M1000_DYcr_mumujj_BB", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_BE = new TH1D ("eejj_L13_M1000_DYcr_mumujj_BE", "eejj_L13_M1000_DYcr_mumujj_BE", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_EE = new TH1D ("eejj_L13_M1000_DYcr_mumujj_EE", "eejj_L13_M1000_DYcr_mumujj_EE", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatio = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatio", "eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatio", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatio_BB = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatio_BB", "eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatio_BB", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatio_BE = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatio_BE", "eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatio_BE", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatio_EE = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatio_EE", "eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatio_EE", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatioUp = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatioUp", "eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatioUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatioDown = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatioDown", "eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatioDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2017_SFUp = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2017_SFUp", "eejj_L13_M1000_DYcr_mumujj_2017_SFUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2017_SFDown = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2017_SFDown", "eejj_L13_M1000_DYcr_mumujj_2017_SFDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2017_PUUp = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2017_PUUp", "eejj_L13_M1000_DYcr_mumujj_2017_PUUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2017_PUDown = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2017_PUDown", "eejj_L13_M1000_DYcr_mumujj_2017_PUDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_centralJesJer = new TH1D ("eejj_L13_M1000_DYcr_mumujj_centralJesJer", "eejj_L13_M1000_DYcr_mumujj_centralJesJer", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2017_JesSFUp = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2017_JesSFUp", "eejj_L13_M1000_DYcr_mumujj_2017_JesSFUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2017_JesSFDown = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2017_JesSFDown", "eejj_L13_M1000_DYcr_mumujj_2017_JesSFDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2017_JerSFUp = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2017_JerSFUp", "eejj_L13_M1000_DYcr_mumujj_2017_JerSFUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2017_JerSFDown = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2017_JerSFDown", "eejj_L13_M1000_DYcr_mumujj_2017_JerSFDown", 8, asymbins);
//TH1D *eejj_L13_M1000_DYcr_mumujj_2017_PtCorrUp = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2017_PtCorrUp", "eejj_L13_M1000_DYcr_mumujj_2017_PtCorrUp", 8, asymbins);
//TH1D *eejj_L13_M1000_DYcr_mumujj_2017_PtCorrDown = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2017_PtCorrDown", "eejj_L13_M1000_DYcr_mumujj_2017_PtCorrDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2017_PtResoUp  = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2017_PtResoUp", "eejj_L13_M1000_DYcr_mumujj_2017_PtResoUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2017_PtResoDown  = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2017_PtResoDown", "eejj_L13_M1000_DYcr_mumujj_2017_PtResoDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2017_PtReso2Up  = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2017_PtReso2Up", "eejj_L13_M1000_DYcr_mumujj_2017_PtReso2Up", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2017_PtReso2Down  = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2017_PtReso2Down", "eejj_L13_M1000_DYcr_mumujj_2017_PtReso2Down", 8, asymbins);

TH1D *eejj_L13_M1000_DYcr_eejj_ele1_ecalTrkEnergyPostCorr = new TH1D ("eejj_L13_M1000_DYcr_eejj_ele1_ecalTrkEnergyPostCorr", "eejj_L13_M1000_DYcr_eejj_ele1_ecalTrkEnergyPostCorr", 100, 0, 1000);
TH1D *eejj_L13_M1000_DYcr_eejj_ele2_ecalTrkEnergyPostCorr = new TH1D ("eejj_L13_M1000_DYcr_eejj_ele2_ecalTrkEnergyPostCorr", "eejj_L13_M1000_DYcr_eejj_ele2_ecalTrkEnergyPostCorr", 100, 0, 1000);
TH1D *eejj_L13_M1000_DYcr_eejj_ele1_energy = new TH1D ("eejj_L13_M1000_DYcr_eejj_ele1_energy", "eejj_L13_M1000_DYcr_eejj_ele1_energy", 100, 0, 1000);
TH1D *eejj_L13_M1000_DYcr_eejj_ele2_energy = new TH1D ("eejj_L13_M1000_DYcr_eejj_ele2_energy", "eejj_L13_M1000_DYcr_eejj_ele2_energy", 100, 0, 1000);

TH1D *Mee_DYcr = new TH1D ("Mee_DYcr", "Mee_DYcr", 50, 150, 300);
TH1D *Mee_DYcr_BB = new TH1D ("Mee_DYcr_BB", "Mee_DYcr_BB", 50, 150, 300);
TH1D *Mee_DYcr_BE = new TH1D ("Mee_DYcr_BE", "Mee_DYcr_BE", 50, 150, 300);
TH1D *Mee_DYcr_EE = new TH1D ("Mee_DYcr_EE", "Mee_DYcr_EE", 50, 150, 300);
TH1D *eejj_L13_M1000_DYcr_eejj = new TH1D ("eejj_L13_M1000_DYcr_eejj", "eejj_L13_M1000_DYcr_eejj", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_BB = new TH1D ("eejj_L13_M1000_DYcr_eejj_BB", "eejj_L13_M1000_DYcr_eejj_BB", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_BE = new TH1D ("eejj_L13_M1000_DYcr_eejj_BE", "eejj_L13_M1000_DYcr_eejj_BE", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_EE = new TH1D ("eejj_L13_M1000_DYcr_eejj_EE", "eejj_L13_M1000_DYcr_eejj_EE", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2017_AlphaRatio = new TH1D ("eejj_L13_M1000_DYcr_eejj_2017_AlphaRatio", "eejj_L13_M1000_DYcr_eejj_2017_AlphaRatio", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2017_AlphaRatio_BB = new TH1D ("eejj_L13_M1000_DYcr_eejj_2017_AlphaRatio_BB", "eejj_L13_M1000_DYcr_eejj_2017_AlphaRatio_BB", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2017_AlphaRatio_BE = new TH1D ("eejj_L13_M1000_DYcr_eejj_2017_AlphaRatio_BE", "eejj_L13_M1000_DYcr_eejj_2017_AlphaRatio_BE", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2017_AlphaRatio_EE = new TH1D ("eejj_L13_M1000_DYcr_eejj_2017_AlphaRatio_EE", "eejj_L13_M1000_DYcr_eejj_2017_AlphaRatio_EE", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2017_AlphaRatioUp = new TH1D ("eejj_L13_M1000_DYcr_eejj_2017_AlphaRatioUp", "eejj_L13_M1000_DYcr_eejj_2017_AlphaRatioUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2017_AlphaRatioDown = new TH1D ("eejj_L13_M1000_DYcr_eejj_2017_AlphaRatioDown", "eejj_L13_M1000_DYcr_eejj_2017_AlphaRatioDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2017_SFUp = new TH1D ("eejj_L13_M1000_DYcr_eejj_2017_SFUp", "eejj_L13_M1000_DYcr_eejj_2017_SFUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2017_SFDown = new TH1D ("eejj_L13_M1000_DYcr_eejj_2017_SFDown", "eejj_L13_M1000_DYcr_eejj_2017_SFDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2017_PUUp = new TH1D ("eejj_L13_M1000_DYcr_eejj_2017_PUUp", "eejj_L13_M1000_DYcr_eejj_2017_PUUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2017_PUDown = new TH1D ("eejj_L13_M1000_DYcr_eejj_2017_PUDown", "eejj_L13_M1000_DYcr_eejj_2017_PUDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_centralJesJer = new TH1D ("eejj_L13_M1000_DYcr_eejj_centralJesJer", "eejj_L13_M1000_DYcr_eejj_centralJesJer", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2017_JesSFUp = new TH1D ("eejj_L13_M1000_DYcr_eejj_2017_JesSFUp", "eejj_L13_M1000_DYcr_eejj_2017_JesSFUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2017_JesSFDown = new TH1D ("eejj_L13_M1000_DYcr_eejj_2017_JesSFDown", "eejj_L13_M1000_DYcr_eejj_2017_JesSFDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2017_JerSFUp = new TH1D ("eejj_L13_M1000_DYcr_eejj_2017_JerSFUp", "eejj_L13_M1000_DYcr_eejj_2017_JerSFUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2017_JerSFDown = new TH1D ("eejj_L13_M1000_DYcr_eejj_2017_JerSFDown", "eejj_L13_M1000_DYcr_eejj_2017_JerSFDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_energyScaleUp = new TH1D ("eejj_L13_M1000_DYcr_eejj_energyScaleUp", "eejj_L13_M1000_DYcr_eejj_energyScaleUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_energyScaleDown = new TH1D ("eejj_L13_M1000_DYcr_eejj_energyScaleDown", "eejj_L13_M1000_DYcr_eejj_energyScaleDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2017_energySigmaUp = new TH1D ("eejj_L13_M1000_DYcr_eejj_2017_energySigmaUp", "eejj_L13_M1000_DYcr_eejj_2017_energySigmaUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2017_energySigmaDown = new TH1D ("eejj_L13_M1000_DYcr_eejj_2017_energySigmaDown", "eejj_L13_M1000_DYcr_eejj_2017_energySigmaDown", 8, asymbins);

//TTtW cr
const double asymbins2[7] = {300,350,400,450,500,700,2000};

TH1D *eejj_L13_M1000_TTtWcr_ll = new TH1D ("eejj_L13_M1000_TTtWcr_ll", "eejj_L13_M1000_TTtWcr_ll", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_BB = new TH1D ("eejj_L13_M1000_TTtWcr_ll_BB", "eejj_L13_M1000_TTtWcr_ll_BB", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_BE = new TH1D ("eejj_L13_M1000_TTtWcr_ll_BE", "eejj_L13_M1000_TTtWcr_ll_BE", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_EE = new TH1D ("eejj_L13_M1000_TTtWcr_ll_EE", "eejj_L13_M1000_TTtWcr_ll_EE", 6, asymbins2);

/*M(emuJ)*/
TH1D *eejj_L13_M1000_TTtWcr_llJ = new TH1D ("eejj_L13_M1000_TTtWcr_llJ", "eejj_L13_M1000_TTtWcr_llJ", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_BB = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_BB", "eejj_L13_M1000_TTtWcr_llJ_BB", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_BE = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_BE", "eejj_L13_M1000_TTtWcr_llJ_BE", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_EE = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_EE", "eejj_L13_M1000_TTtWcr_llJ_EE", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2017_AlphaRatio = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2017_AlphaRatio", "eejj_L13_M1000_TTtWcr_llJ_2017_AlphaRatio", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2017_AlphaRatioUp = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2017_AlphaRatioUp", "eejj_L13_M1000_TTtWcr_llJ_2017_AlphaRatioUp", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2017_AlphaRatioDown = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2017_AlphaRatioDown", "eejj_L13_M1000_TTtWcr_llJ_2017_AlphaRatioDown", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2017_SFUp = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2017_SFUp", "eejj_L13_M1000_TTtWcr_llJ_2017_SFUp", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2017_SFDown = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2017_SFDown", "eejj_L13_M1000_TTtWcr_llJ_2017_SFDown", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2017_PUUp = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2017_PUUp", "eejj_L13_M1000_TTtWcr_llJ_2017_PUUp", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2017_PUDown = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2017_PUDown", "eejj_L13_M1000_TTtWcr_llJ_2017_PUDown", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2017_PtResoUp = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2017_PtResoUp", "eejj_L13_M1000_TTtWcr_llJ_2017_PtResoUp", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2017_PtResoDown = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2017_PtResoDown", "eejj_L13_M1000_TTtWcr_llJ_2017_PtResoDown", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2017_PtReso2Up = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2017_PtReso2Up", "eejj_L13_M1000_TTtWcr_llJ_2017_PtReso2Up", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2017_PtReso2Down = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2017_PtReso2Down", "eejj_L13_M1000_TTtWcr_llJ_2017_PtReso2Down", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_energyScaleUp = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_energyScaleUp", "eejj_L13_M1000_TTtWcr_llJ_energyScaleUp", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_energyScaleDown = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_energyScaleDown", "eejj_L13_M1000_TTtWcr_llJ_energyScaleDown", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2017_energySigmaUp = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2017_energySigmaUp", "eejj_L13_M1000_TTtWcr_llJ_2017_energySigmaUp", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2017_energySigmaDown = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2017_energySigmaDown", "eejj_L13_M1000_TTtWcr_llJ_2017_energySigmaDown", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_centralJesJer = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_centralJesJer", "eejj_L13_M1000_TTtWcr_llJ_centralJesJer", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2017_JesSFUp = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2017_JesSFUp", "eejj_L13_M1000_TTtWcr_llJ_2017_JesSFUp", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2017_JesSFDown = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2017_JesSFDown", "eejj_L13_M1000_TTtWcr_llJ_2017_JesSFDown", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2017_JerSFUp = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2017_JerSFUp", "eejj_L13_M1000_TTtWcr_llJ_2017_JerSFUp", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2017_JerSFDown = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2017_JerSFDown", "eejj_L13_M1000_TTtWcr_llJ_2017_JerSFDown", 8, asymbins);

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
TLorentzVector Muon1_Roc;
TLorentzVector Muon2_Roc;
TVector3 P1_smear;
TVector3 P2_smear;

/*this is for the patch on lepf sf systematics*/
double elesf1=0, elesf_d1=0, elesf_d2=0; 
double elesf2=0, elesf_u1=0, elesf_u2=0; 
double energy_corr0 = 0, energy_corr1 = 0;
double Muon1_px_smearing = 0, Muon1_py_smearing = 0, Muon1_pz_smearing = 0;
double Muon2_px_smearing = 0, Muon2_py_smearing = 0, Muon2_pz_smearing = 0;
double extra_smearing_1 =0, extra_smearing_2 = 0;
double muon_tot_pt = 0, ele_tot_pt = 0, jet_tot_pt = 0, HTevent=0;

for (Int_t i=0;i<a_->GetEntries();i++) {
 a_->GetEntry(i);
 HLT_Mu = 0; 
 tot = a_->GetEntries();
 if (i%100000 == 0) cout << i << " eventi analizzati su " << tot << endl;

 HLT_Mu = 0; HLT_Ele = 0;

 wg = lumi * lumi_wgt * lepsf_evt * PUWeight * EVENT_prefireWeight;
 wg_SFu = lumi * lumi_wgt * lepsf_evt_u * PUWeight * EVENT_prefireWeight;
 wg_SFd = lumi * lumi_wgt * lepsf_evt_d * PUWeight * EVENT_prefireWeight;
 wg_PUu = lumi * lumi_wgt * lepsf_evt * MinBiasUpWeight * EVENT_prefireWeight;
 wg_PUd = lumi * lumi_wgt * lepsf_evt * MinBiasDownWeight * EVENT_prefireWeight;

          
 if (HLT_Mu50==1 || HLT_TkMu100==1 || HLT_OldMu100==1 ) HLT_Mu = 1;
 if (HLT_Photon200 == 1 || HLT_Ele35==1 || HLT_Ele115 == 1) HLT_Ele = 1;

  muon_tot_pt = 0; ele_tot_pt = 0; jet_tot_pt = 0; HTevent = 0;

 for(int j=0; j<Muon_pt_tunePbt_Roc->size(); j++) {
  muon_tot_pt= Muon_pt_tunePbt_Roc->at(j)+muon_tot_pt;
 }
 for(int j=0; j<patElectron_pt->size(); j++) {
  ele_tot_pt=patElectron_pt->at(j)+ ele_tot_pt;
 }
 for(int j=0; j<BoostedJet_pt->size(); j++) {
  jet_tot_pt=BoostedJet_pt->at(j)+ jet_tot_pt;
 }
 HTevent = muon_tot_pt + ele_tot_pt + jet_tot_pt;

  if (Muon_pt_tunePbt_Roc->size() > 1 && numOfHighptMu==2 && numOfVetoEle == 0 && numOfBoostedJets>=1){

   BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
   BoostJet_JESup.SetPtEtaPhiE(BoostedJet_pt->at(1), BoostedJet_eta->at(1), BoostedJet_phi->at(1),BoostedJet_energy->at(1));
   BoostJet_JESdown.SetPtEtaPhiE(BoostedJet_pt->at(2), BoostedJet_eta->at(2), BoostedJet_phi->at(2),BoostedJet_energy->at(2));
   BoostJet_JERup.SetPtEtaPhiE(BoostedJet_pt->at(3), BoostedJet_eta->at(3), BoostedJet_phi->at(3),BoostedJet_energy->at(3));
   BoostJet_JERdown.SetPtEtaPhiE(BoostedJet_pt->at(4), BoostedJet_eta->at(4), BoostedJet_phi->at(4),BoostedJet_energy->at(4));

   Muon1.SetPtEtaPhiM(Muon_pt_tunePbt_Roc->at(0), Muon_eta->at(0), Muon_phi->at(0),0.1056583745);
   Muon2.SetPtEtaPhiM(Muon_pt_tunePbt_Roc->at(1), Muon_eta->at(1), Muon_phi->at(1),0.1056583745);

   Muon1_Roc.SetPtEtaPhiE(Muon_pt_tunePbt_Roc->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));
   Muon2_Roc.SetPtEtaPhiE(Muon_pt_tunePbt_Roc->at(1), Muon_eta->at(1), Muon_phi->at(1),Muon_energy->at(1));

   //smearing post Rochester correction
   extra_smearing_1 = extraSmearingSigma(Muon1.Eta(), Muon1.P());
   extra_smearing_2 = extraSmearingSigma(Muon2.Eta(), Muon2.P());
   
   Muon1_px_smearing=Muon1.Px()*gRandom->Gaus(1,extra_smearing_1);
   Muon1_py_smearing=Muon1.Py()*gRandom->Gaus(1,extra_smearing_1);
   Muon1_pz_smearing=Muon1.Pz()*gRandom->Gaus(1,extra_smearing_1);   

   Muon2_px_smearing=Muon2.Px()*gRandom->Gaus(1,extra_smearing_2);
   Muon2_py_smearing=Muon2.Py()*gRandom->Gaus(1,extra_smearing_2);
   Muon2_pz_smearing=Muon2.Pz()*gRandom->Gaus(1,extra_smearing_2);

   P1_smear.SetXYZ(Muon1_px_smearing, Muon1_py_smearing, Muon1_pz_smearing);
   P2_smear.SetXYZ(Muon2_px_smearing, Muon2_py_smearing, Muon2_pz_smearing);

   Muon1_PtResoUp.SetPtEtaPhiM(P1_smear.Pt(), P1_smear.Eta(), P1_smear.Phi(),0.1056583745 );
   Muon2_PtResoUp.SetPtEtaPhiM(P2_smear.Pt(), P2_smear.Eta(), P2_smear.Phi(),0.1056583745 );
   Muon1_PtResoDown.SetPtEtaPhiM(P1_smear.Pt(), P1_smear.Eta(), P1_smear.Phi(),0.1056583745 );
   Muon2_PtResoDown.SetPtEtaPhiM(P2_smear.Pt(), P2_smear.Eta(), P2_smear.Phi(),0.1056583745 );

   if (HLT_Mu == 1 && Muon1_PtResoUp.Pt() > 150 && Muon2_PtResoUp.Pt() > 100 && fabs(Muon1_PtResoUp.Eta())<2.4 && fabs(Muon2_PtResoUp.Eta())<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1_PtResoUp+Muon2_PtResoUp).M()  > 300 ){
    eejj_L13_M1000_mumujj_2017_PtReso2Up->Fill((Muon1_PtResoUp+Muon2_PtResoUp+BoostJet).M(), wg);
   }

   if (HLT_Mu == 1 && Muon1.Pt() > 150 && Muon2.Pt() > 100 && fabs(Muon1.Eta())<2.4 && fabs(Muon2.Eta())<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1+Muon2).M()  > 300 ){

   if (wg > 37.1 && wg < 37.2) continue;
    eejj_L13_M1000_mumujj_Roc->Fill((Muon1_Roc+Muon2_Roc+BoostJet).M(), wg ) ; 
   if (Muon_charge->at(0)*Muon_charge->at(1) == 1) eejj_L13_M1000_mumujj_SS->Fill((Muon1+Muon2+BoostJet).M(), wg);
   if (Muon_charge->at(0)*Muon_charge->at(1) == -1) eejj_L13_M1000_mumujj_OS->Fill((Muon1+Muon2+BoostJet).M(), wg);
   eejj_L13_M1000_mumujj_Roc->Fill((Muon1_Roc+Muon2_Roc+BoostJet).M(), wg ) ;  
  eejj_L13_M1000_mumujj->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_Mmumu->Fill((Muon1+Muon2).M(),wg );
   eejj_L13_M1000_HTmumu->Fill(HTevent,wg); 
    if (fabs(Muon1.Eta())< 0.8 && fabs(Muon2.Eta())<0.8){
    eejj_L13_M1000_Mmumu_BB->Fill((Muon1+Muon2).M(),wg );
    eejj_L13_M1000_HTmumu_BB->Fill(HTevent,wg);
    eejj_L13_M1000_mumujj_BB->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_mumujj_2017_AlphaRatio_BB->Fill((Muon1+Muon2+BoostJet).M(), wg);
   }
   if ((fabs(Muon1.Eta())< 0.8 && fabs(Muon2.Eta())>0.8) || (fabs(Muon1.Eta())> 0.8 && fabs(Muon2.Eta())<0.8)){
    eejj_L13_M1000_Mmumu_BE->Fill((Muon1+Muon2).M(),wg );
    eejj_L13_M1000_HTmumu_BE->Fill(HTevent,wg);
    eejj_L13_M1000_mumujj_BE->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_mumujj_2017_AlphaRatio_BE->Fill((Muon1+Muon2+BoostJet).M(), wg);
   }
   if (fabs(Muon1.Eta())> 0.8 && fabs(Muon2.Eta())>0.8){
    eejj_L13_M1000_Mmumu_EE->Fill((Muon1+Muon2).M(),wg );
    eejj_L13_M1000_HTmumu_EE->Fill(HTevent,wg);
    eejj_L13_M1000_mumujj_EE->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_mumujj_2017_AlphaRatio_EE->Fill((Muon1+Muon2+BoostJet).M(), wg);
   }
    eejj_L13_M1000_mumujj_2017_AlphaRatio->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_mumujj_2017_AlphaRatioUp->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_mumujj_2017_AlphaRatioDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_mumujj_2017_SFUp->Fill((Muon1+Muon2+BoostJet).M(), wg_SFu);
    eejj_L13_M1000_mumujj_2017_SFDown->Fill((Muon1+Muon2+BoostJet).M(), wg_SFd);
    eejj_L13_M1000_mumujj_2017_PUUp->Fill((Muon1+Muon2+BoostJet).M(), wg_PUu);
    eejj_L13_M1000_mumujj_2017_PUDown->Fill((Muon1+Muon2+BoostJet).M(), wg_PUd);
    if ((Muon1_PtResoUp+Muon2_PtResoUp).M() >300) eejj_L13_M1000_mumujj_2017_PtResoUp->Fill((Muon1_PtResoUp+Muon2_PtResoUp+BoostJet).M(), wg);
    eejj_L13_M1000_mumujj_2017_PtResoDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_mumujj_2017_PtReso2Down->Fill((Muon1+Muon2+BoostJet).M(), wg);  

    if(centralJesJer->at(0)==1)eejj_L13_M1000_mumujj_2017_centralJesJer->Fill((Muon1+Muon2+BoostJet).M(), wg);
    if(JesSFup->at(1)==1)eejj_L13_M1000_mumujj_2017_JesSFUp->Fill((Muon1+Muon2+BoostJet_JESup).M(), wg);
    if(JesSFdown->at(2)==1)eejj_L13_M1000_mumujj_2017_JesSFDown->Fill((Muon1+Muon2+BoostJet_JESdown).M(), wg);
    if(JerSFup->at(3)==1)eejj_L13_M1000_mumujj_2017_JerSFUp->Fill((Muon1+Muon2+BoostJet_JERup).M(), wg);
    if(JerSFdown->at(4)==1)eejj_L13_M1000_mumujj_2017_JerSFDown->Fill((Muon1+Muon2+BoostJet_JERdown).M(), wg);
  
   eejj_L13_M1000_mumujj_PDFUp->Fill((Muon1+Muon2+BoostJet).M(), wg*(1+(EVENT_PDFv4WeightUp/100)));     
   eejj_L13_M1000_mumujj_PDFDown->Fill((Muon1+Muon2+BoostJet).M(), wg*(1-(EVENT_PDFv4WeightDown/100)));
 
  }

    //Zpeak DY cr Mll in 60-120 GeV
    if (HLT_Mu == 1 && Muon1.Pt() > 150 && Muon2.Pt() > 100 && fabs(Muon1.Eta())<2.4 && fabs(Muon2.Eta())<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1+Muon2).M() > 60 && (Muon1+Muon2).M() < 120){
      BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
      eejj_L13_M1000_ZpeakMll_mumujj->Fill((Muon1+Muon2).M(), wg); 
      eejj_L13_M1000_Zpeak_mumujj->Fill((Muon1+Muon2+BoostJet).M(), wg); 
      eejj_L13_M1000_Zpeak_mumu_pt->Fill((Muon1+Muon2).Pt(), wg);
    if (Muon_charge->at(0)*Muon_charge->at(1) == 1) eejj_L13_M1000_Zpeak_mumujj_SS->Fill((Muon1+Muon2+BoostJet).M(), wg);
   if (Muon_charge->at(0)*Muon_charge->at(1) == -1) eejj_L13_M1000_Zpeak_mumujj_OS->Fill((Muon1+Muon2+BoostJet).M(), wg);
    if (fabs(Muon1.Eta())< 0.8 && fabs(Muon2.Eta())<0.8){
    eejj_L13_M1000_ZpeakMll_mumujj_BB->Fill((Muon1+Muon2).M(), wg);
    eejj_L13_M1000_Zpeak_mumujj_BB->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_Zpeak_mumu_pt_BB->Fill((Muon1+Muon2).Pt(), wg);
   }
   if((fabs(Muon1.Eta())< 0.8 && fabs(Muon2.Eta())>0.8) || (fabs(Muon1.Eta())> 0.8 && fabs(Muon2.Eta())<0.8)){
    eejj_L13_M1000_ZpeakMll_mumujj_BE->Fill((Muon1+Muon2).M(), wg);
    eejj_L13_M1000_Zpeak_mumujj_BE->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_Zpeak_mumu_pt_BE->Fill((Muon1+Muon2).Pt(), wg);
   }
   if(fabs(Muon1.Eta())> 0.8 && fabs(Muon2.Eta())>0.8){
    eejj_L13_M1000_ZpeakMll_mumujj_EE->Fill((Muon1+Muon2).M(), wg);
    eejj_L13_M1000_Zpeak_mumujj_EE->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_Zpeak_mumu_pt_EE->Fill((Muon1+Muon2).Pt(), wg);
   }
    }

    //DY cr Mll in 150-300 GeV
   if (HLT_Mu == 1 && Muon1_PtResoUp.Pt() > 150 && Muon2_PtResoUp.Pt() > 100 && fabs(Muon1_PtResoUp.Eta())<2.4 && fabs(Muon2_PtResoUp.Eta())<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1_PtResoUp+Muon2_PtResoUp).M() > 150 && (Muon1_PtResoUp+Muon2_PtResoUp).M() < 300){
    eejj_L13_M1000_DYcr_mumujj_2017_PtReso2Up->Fill((Muon1_PtResoUp+Muon2_PtResoUp+BoostJet).M(), wg);
   }
   if (HLT_Mu == 1 && Muon1.Pt() > 150 && Muon2.Pt() > 100 && fabs(Muon1.Eta())<2.4 && fabs(Muon2.Eta())<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1+Muon2).M() > 150 && (Muon1+Muon2).M() < 300){

    if (Muon_charge->at(0)*Muon_charge->at(1) == 1) eejj_L13_M1000_DYcr_mumujj_SS->Fill((Muon1+Muon2+BoostJet).M(), wg);
   if (Muon_charge->at(0)*Muon_charge->at(1) == -1) eejj_L13_M1000_DYcr_mumujj_OS->Fill((Muon1+Muon2+BoostJet).M(), wg);
    Mmumu_DYcr->Fill((Muon1+Muon2).M(), wg);
    eejj_L13_M1000_DYcr_mumujj->Fill((Muon1+Muon2+BoostJet).M(), wg); 
    if (fabs(Muon1.Eta())< 0.8 && fabs(Muon2.Eta())<0.8){
    Mmumu_DYcr_BB->Fill((Muon1+Muon2).M(), wg);
    eejj_L13_M1000_DYcr_mumujj_BB->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatio_BB->Fill((Muon1+Muon2+BoostJet).M(), wg);
   }
   if((fabs(Muon1.Eta())< 0.8 && fabs(Muon2.Eta())>0.8) || (fabs(Muon1.Eta())> 0.8 && fabs(Muon2.Eta())<0.8)){
    Mmumu_DYcr_BE->Fill((Muon1+Muon2).M(), wg);
    eejj_L13_M1000_DYcr_mumujj_BE->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatio_BE->Fill((Muon1+Muon2+BoostJet).M(), wg);
   }
   if(fabs(Muon1.Eta())> 0.8 && fabs(Muon2.Eta())>0.8){
    Mmumu_DYcr_EE->Fill((Muon1+Muon2).M(), wg);
    eejj_L13_M1000_DYcr_mumujj_EE->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatio_EE->Fill((Muon1+Muon2+BoostJet).M(), wg);
   }
    eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatio->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatioUp->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatioDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_DYcr_mumujj_2017_SFUp->Fill((Muon1+Muon2+BoostJet).M(), wg_SFu);
    eejj_L13_M1000_DYcr_mumujj_2017_SFDown->Fill((Muon1+Muon2+BoostJet).M(), wg_SFd);
    eejj_L13_M1000_DYcr_mumujj_2017_PUUp->Fill((Muon1+Muon2+BoostJet).M(), wg_PUu);
    eejj_L13_M1000_DYcr_mumujj_2017_PUDown->Fill((Muon1+Muon2+BoostJet).M(), wg_PUd);
    eejj_L13_M1000_DYcr_mumujj_2017_PtResoUp->Fill((Muon1_PtResoUp+Muon2_PtResoUp+BoostJet).M(), wg);
    eejj_L13_M1000_DYcr_mumujj_2017_PtResoDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_DYcr_mumujj_2017_PtReso2Down->Fill((Muon1+Muon2+BoostJet).M(), wg); 
  
    if(centralJesJer->at(0)==1)eejj_L13_M1000_DYcr_mumujj_centralJesJer->Fill((Muon1+Muon2+BoostJet).M(), wg);
    if(JesSFup->at(1)==1)eejj_L13_M1000_DYcr_mumujj_2017_JesSFUp->Fill((Muon1+Muon2+BoostJet_JESup).M(), wg);
    if(JesSFdown->at(2)==1)eejj_L13_M1000_DYcr_mumujj_2017_JesSFDown->Fill((Muon1+Muon2+BoostJet_JESdown).M(), wg);
    if(JerSFup->at(3)==1)eejj_L13_M1000_DYcr_mumujj_2017_JerSFUp->Fill((Muon1+Muon2+BoostJet_JERup).M(), wg);
    if(JerSFdown->at(4)==1)eejj_L13_M1000_DYcr_mumujj_2017_JerSFDown->Fill((Muon1+Muon2+BoostJet_JERdown).M(), wg);  
    }

 } // 2 muons

  if (patElectron_pt->size() > 1 && numOfHighptEle==2 && numOfLooseMu==0 && numOfBoostedJets>=1){

   Electron1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   Electron2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energy->at(1));

   // energy correction  

   energy_corr0= patElectron_ecalTrkEnergyPostCorr->at(0) / patElectron_energy->at(0) ;
   energy_corr1= patElectron_ecalTrkEnergyPostCorr->at(1) / patElectron_energy->at(1) ;
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

   if (patElectron_charge->at(0)*patElectron_charge->at(1) == 1) eejj_L13_M1000_eejj_SS->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if (patElectron_charge->at(0)*patElectron_charge->at(1) == -1) eejj_L13_M1000_eejj_OS->Fill((Electron1+Electron2+BoostJet).M(), wg);
   eejj_L13_M1000_eejj_ele1_ecalTrkEnergyPostCorr->Fill(patElectron_ecalTrkEnergyPostCorr->at(0),wg);
   eejj_L13_M1000_eejj_ele2_ecalTrkEnergyPostCorr->Fill(patElectron_ecalTrkEnergyPostCorr->at(1),wg);
   eejj_L13_M1000_eejj_ele1_energy->Fill(patElectron_energy->at(0),wg);
   eejj_L13_M1000_eejj_ele2_energy->Fill(patElectron_energy->at(1),wg);
   eejj_L13_M1000_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   eejj_L13_M1000_Mee->Fill((Electron1+Electron2).M(),wg );
   eejj_L13_M1000_HTee->Fill(HTevent,wg);

   if (fabs(patElectron_eta->at(1))< 0.8 && fabs(patElectron_eta->at(0))<0.8){
    eejj_L13_M1000_eejj_BB->Fill((Electron1+Electron2+BoostJet).M(), wg);
    eejj_L13_M1000_eejj_2017_AlphaRatio_BB->Fill((Electron1+Electron2+BoostJet).M(), wg);
    eejj_L13_M1000_Mee_BB->Fill((Electron1+Electron2).M(),wg );
    eejj_L13_M1000_HTee_BB->Fill(HTevent,wg);
   }
   if((fabs(patElectron_eta->at(1))< 0.8 && fabs(patElectron_eta->at(0))>0.8) ||(fabs(patElectron_eta->at(1))>0.8 && fabs(patElectron_eta->at(0))<0.8) ){
    eejj_L13_M1000_eejj_BE->Fill((Electron1+Electron2+BoostJet).M(), wg);
    eejj_L13_M1000_eejj_2017_AlphaRatio_BE->Fill((Electron1+Electron2+BoostJet).M(), wg);
    eejj_L13_M1000_Mee_BE->Fill((Electron1+Electron2).M(),wg );
    eejj_L13_M1000_HTee_BE->Fill(HTevent,wg); 
   }
   if (fabs(patElectron_eta->at(1))> 0.8 && fabs(patElectron_eta->at(0))>0.8){
    eejj_L13_M1000_eejj_EE->Fill((Electron1+Electron2+BoostJet).M(), wg);
    eejj_L13_M1000_eejj_2017_AlphaRatio_EE->Fill((Electron1+Electron2+BoostJet).M(), wg);
    eejj_L13_M1000_Mee_EE->Fill((Electron1+Electron2).M(),wg );
    eejj_L13_M1000_HTee_EE->Fill(HTevent,wg); 
   }

   eejj_L13_M1000_eejj_2017_AlphaRatio->Fill((Electron1+Electron2+BoostJet).M(), wg);
   eejj_L13_M1000_eejj_2017_AlphaRatioUp->Fill((Electron1+Electron2+BoostJet).M(), wg);
   eejj_L13_M1000_eejj_2017_AlphaRatioDown->Fill((Electron1+Electron2+BoostJet).M(), wg);
   eejj_L13_M1000_eejj_2017_SFUp->Fill((Electron1+Electron2+BoostJet).M(), wg_SFu);
   eejj_L13_M1000_eejj_2017_SFDown->Fill((Electron1+Electron2+BoostJet).M(), wg_SFd);
   eejj_L13_M1000_eejj_2017_PUUp->Fill((Electron1+Electron2+BoostJet).M(), wg_PUu);
   eejj_L13_M1000_eejj_2017_PUDown->Fill((Electron1+Electron2+BoostJet).M(), wg_PUd);
   eejj_L13_M1000_eejj_energyScaleUp->Fill((Ele1_ScaleUp+Ele2_ScaleUp+BoostJet).M(), wg);
   eejj_L13_M1000_eejj_energyScaleDown->Fill((Ele1_ScaleDown+Ele2_ScaleDown+BoostJet).M(), wg);
   eejj_L13_M1000_eejj_2017_energySigmaUp->Fill((Ele1_SigmaUp+Ele2_SigmaUp+BoostJet).M(), wg);
   eejj_L13_M1000_eejj_2017_energySigmaDown->Fill((Ele1_SigmaDown+Ele2_SigmaDown+BoostJet).M(), wg);
   if(centralJesJer->at(0)==1)eejj_L13_M1000_eejj_2017_centralJesJer->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)eejj_L13_M1000_eejj_2017_JesSFUp->Fill((Electron1+Electron2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)eejj_L13_M1000_eejj_2017_JesSFDown->Fill((Electron1+Electron2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)eejj_L13_M1000_eejj_2017_JerSFUp->Fill((Electron1+Electron2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)eejj_L13_M1000_eejj_2017_JerSFDown->Fill((Electron1+Electron2+BoostJet_JERdown).M(), wg);
  
  eejj_L13_M1000_eejj_PDFUp->Fill((Electron1+Electron2+BoostJet).M(), wg*(1+(EVENT_PDFv4WeightUp/100)));      //comment for bkgs                 
  eejj_L13_M1000_eejj_PDFDown->Fill((Electron1+Electron2+BoostJet).M(), wg*(1-(EVENT_PDFv4WeightDown/100)));  //comment for bkgs

  }

    //Zpeak DY cr 60-120 GeV
  if (HLT_Ele == 1 && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190 && (Electron1+Electron2).M() >60 && (Electron1+Electron2).M() < 120){

   if (patElectron_charge->at(0)*patElectron_charge->at(1) == 1) eejj_L13_M1000_Zpeak_eejj_SS->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if (patElectron_charge->at(0)*patElectron_charge->at(1) == -1) eejj_L13_M1000_Zpeak_eejj_OS->Fill((Electron1+Electron2+BoostJet).M(), wg);
   eejj_L13_M1000_ZpeakMll_eejj->Fill((Electron1+Electron2).M(), wg);
   eejj_L13_M1000_Zpeak_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   eejj_L13_M1000_Zpeak_ee_pt->Fill((Electron1+Electron2).Pt(), wg);
    if (fabs(patElectron_eta->at(1))< 0.8 && fabs(patElectron_eta->at(0))<0.8){
     eejj_L13_M1000_ZpeakMll_eejj_BB->Fill((Electron1+Electron2).M(), wg);
     eejj_L13_M1000_Zpeak_eejj_BB->Fill((Electron1+Electron2+BoostJet).M(), wg);
     eejj_L13_M1000_Zpeak_ee_pt_BB->Fill((Electron1+Electron2).Pt(), wg);
    }
    if((fabs(patElectron_eta->at(1))< 0.8 && fabs(patElectron_eta->at(0))>0.8) ||(fabs(patElectron_eta->at(1))>0.8 && fabs(patElectron_eta->at(0))<0.8) ){
     eejj_L13_M1000_ZpeakMll_eejj_BE->Fill((Electron1+Electron2).M(), wg);
     eejj_L13_M1000_Zpeak_eejj_BE->Fill((Electron1+Electron2+BoostJet).M(), wg);
     eejj_L13_M1000_Zpeak_ee_pt_BE->Fill((Electron1+Electron2).Pt(), wg);
    }
    if (fabs(patElectron_eta->at(1))> 0.8 && fabs(patElectron_eta->at(0))>0.8){
     eejj_L13_M1000_ZpeakMll_eejj_EE->Fill((Electron1+Electron2).M(), wg);
     eejj_L13_M1000_Zpeak_eejj_EE->Fill((Electron1+Electron2+BoostJet).M(), wg);
     eejj_L13_M1000_Zpeak_ee_pt_EE->Fill((Electron1+Electron2).Pt(), wg);
    }
  }

  //DY cr 150-300 GeV
   
  if (HLT_Ele == 1 && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190 && (Electron1+Electron2).M() >150 && (Electron1+Electron2).M() < 300){

   if (patElectron_charge->at(0)*patElectron_charge->at(1) == 1) eejj_L13_M1000_DYcr_eejj_SS->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if (patElectron_charge->at(0)*patElectron_charge->at(1) == -1) eejj_L13_M1000_DYcr_eejj_OS->Fill((Electron1+Electron2+BoostJet).M(), wg);
   Mee_DYcr->Fill((Electron1+Electron2).M(), wg);
   eejj_L13_M1000_DYcr_eejj_ele1_ecalTrkEnergyPostCorr->Fill(patElectron_ecalTrkEnergyPostCorr->at(0), wg);
   eejj_L13_M1000_DYcr_eejj_ele2_ecalTrkEnergyPostCorr->Fill(patElectron_ecalTrkEnergyPostCorr->at(1), wg);
   eejj_L13_M1000_DYcr_eejj_ele1_energy->Fill(patElectron_energy->at(0), wg);
   eejj_L13_M1000_DYcr_eejj_ele2_energy->Fill(patElectron_energy->at(1), wg);
   eejj_L13_M1000_DYcr_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if (fabs(patElectron_eta->at(1))< 0.8 && fabs(patElectron_eta->at(0))<0.8){
    Mee_DYcr_BB->Fill((Electron1+Electron2).M(), wg);
    eejj_L13_M1000_DYcr_eejj_BB->Fill((Electron1+Electron2+BoostJet).M(), wg);
    eejj_L13_M1000_DYcr_eejj_2017_AlphaRatio_BB->Fill((Electron1+Electron2+BoostJet).M(), wg);
   }
   if((fabs(patElectron_eta->at(1))< 0.8 && fabs(patElectron_eta->at(0))>0.8) ||(fabs(patElectron_eta->at(1))>0.8 && fabs(patElectron_eta->at(0))<0.8) ){
    Mee_DYcr_BE->Fill((Electron1+Electron2).M(), wg);
    eejj_L13_M1000_DYcr_eejj_BE->Fill((Electron1+Electron2+BoostJet).M(), wg);
    eejj_L13_M1000_DYcr_eejj_2017_AlphaRatio_BE->Fill((Electron1+Electron2+BoostJet).M(), wg);
   }
   if (fabs(patElectron_eta->at(1))> 0.8 && fabs(patElectron_eta->at(0))>0.8){
    Mee_DYcr_EE->Fill((Electron1+Electron2).M(), wg);
    eejj_L13_M1000_DYcr_eejj_EE->Fill((Electron1+Electron2+BoostJet).M(), wg);
    eejj_L13_M1000_DYcr_eejj_2017_AlphaRatio_EE->Fill((Electron1+Electron2+BoostJet).M(), wg);
   }
   eejj_L13_M1000_DYcr_eejj_2017_AlphaRatio->Fill((Electron1+Electron2+BoostJet).M(), wg);
   eejj_L13_M1000_DYcr_eejj_2017_AlphaRatioUp->Fill((Electron1+Electron2+BoostJet).M(), wg);
   eejj_L13_M1000_DYcr_eejj_2017_AlphaRatioDown->Fill((Electron1+Electron2+BoostJet).M(), wg);
   eejj_L13_M1000_DYcr_eejj_2017_SFUp->Fill((Electron1+Electron2+BoostJet).M(), wg_SFu);
   eejj_L13_M1000_DYcr_eejj_2017_SFDown->Fill((Electron1+Electron2+BoostJet).M(), wg_SFd);
   eejj_L13_M1000_DYcr_eejj_2017_PUUp->Fill((Electron1+Electron2+BoostJet).M(), wg_PUu);
   eejj_L13_M1000_DYcr_eejj_2017_PUDown->Fill((Electron1+Electron2+BoostJet).M(), wg_PUd);
   eejj_L13_M1000_DYcr_eejj_energyScaleUp->Fill((Ele1_ScaleUp+Ele2_ScaleUp+BoostJet).M(), wg);
   eejj_L13_M1000_DYcr_eejj_energyScaleDown->Fill((Ele1_ScaleDown+Ele2_ScaleDown+BoostJet).M(), wg);
   eejj_L13_M1000_DYcr_eejj_2017_energySigmaUp->Fill((Ele1_SigmaUp+Ele2_SigmaUp+BoostJet).M(), wg);
   eejj_L13_M1000_DYcr_eejj_2017_energySigmaDown->Fill((Ele1_SigmaDown+Ele2_SigmaDown+BoostJet).M(), wg);
   if(centralJesJer->at(0)==1)eejj_L13_M1000_DYcr_eejj_centralJesJer->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)eejj_L13_M1000_DYcr_eejj_2017_JesSFUp->Fill((Electron1+Electron2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)eejj_L13_M1000_DYcr_eejj_2017_JesSFDown->Fill((Electron1+Electron2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)eejj_L13_M1000_DYcr_eejj_2017_JerSFUp->Fill((Electron1+Electron2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)eejj_L13_M1000_DYcr_eejj_2017_JerSFDown->Fill((Electron1+Electron2+BoostJet_JERdown).M(), wg); 
  }

 }

 //TTtW cr
 TLorentzVector LeadLep;
TLorentzVector SubLeadLep;
TLorentzVector LeadLep2;
TLorentzVector SubLeadLep2;
TLorentzVector Ele_ScaleUp;
TLorentzVector Ele_ScaleDown;
TLorentzVector Ele_SigmaUp;
TLorentzVector Ele_SigmaDown;
TLorentzVector Muon_PtResoUp;
TLorentzVector Muon_PtResoDown;

double deltaEta = 0, deltaPhi = 0, deltaR = 0;

 if (Muon_pt_tunePbt_Roc->size() > 0 && patElectron_pt->size() > 0 && numOfHighptMu==1 && numOfHighptEle == 1 && numOfBoostedJets>=1){

  BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
   BoostJet_JESup.SetPtEtaPhiE(BoostedJet_pt->at(1), BoostedJet_eta->at(1), BoostedJet_phi->at(1),BoostedJet_energy->at(1));
   BoostJet_JESdown.SetPtEtaPhiE(BoostedJet_pt->at(2), BoostedJet_eta->at(2), BoostedJet_phi->at(2),BoostedJet_energy->at(2));
   BoostJet_JERup.SetPtEtaPhiE(BoostedJet_pt->at(3), BoostedJet_eta->at(3), BoostedJet_phi->at(3),BoostedJet_energy->at(3));
   BoostJet_JERdown.SetPtEtaPhiE(BoostedJet_pt->at(4), BoostedJet_eta->at(4), BoostedJet_phi->at(4),BoostedJet_energy->at(4));
   Ele_ScaleUp.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energyScaleUp->at(0));
   Ele_ScaleDown.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energyScaleDown->at(0));
   Ele_SigmaUp.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energySigmaUp->at(0));
   Ele_SigmaDown.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energySigmaDown->at(0));

// if smearing

   if (Muon_pt_tunePbt_Roc->at(0) >= patElectron_pt->at(0)){
   LeadLep.SetPtEtaPhiM(Muon_pt_tunePbt_Roc->at(0), Muon_eta->at(0), Muon_phi->at(0),0.1056583745 );
   SubLeadLep.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   energy_corr0= patElectron_ecalTrkEnergyPostCorr->at(0) / patElectron_energy->at(0) ;
   SubLeadLep = SubLeadLep*energy_corr0;

   extra_smearing_1 = extraSmearingSigma(LeadLep.Eta(), LeadLep.P());

   Muon1_px_smearing=LeadLep.Px()*gRandom->Gaus(1,extra_smearing_1);
   Muon1_py_smearing=LeadLep.Py()*gRandom->Gaus(1,extra_smearing_1);
   Muon1_pz_smearing=LeadLep.Pz()*gRandom->Gaus(1,extra_smearing_1);

   P1_smear.SetXYZ(Muon1_px_smearing, Muon1_py_smearing, Muon1_pz_smearing);
   Muon_PtResoUp.SetPtEtaPhiM(P1_smear.Pt(), P1_smear.Eta(), P1_smear.Phi(),0.1056583745 );
   Muon_PtResoDown.SetPtEtaPhiM(P1_smear.Pt(), P1_smear.Eta(), P1_smear.Phi(),0.1056583745 );

   LeadLep2.SetPtEtaPhiM(Muon_PtResoUp.Pt(), Muon_PtResoUp.Eta(), Muon_PtResoUp.Phi(), 0.1056583745);

   if (HLT_Mu == 1 && LeadLep2.Pt() > 150 && SubLeadLep.Pt() > 100 && fabs(LeadLep2.Eta())<2.4 && fabs(SubLeadLep.Eta())<2.4 && BoostedJet_pt->at(0) > 190 && (LeadLep2+SubLeadLep).M() > 300 ){
    veto_ele = false;
    for(int j = 0; j < Muon_pt_tunePbt_Roc->size(); j++){
     if (Muon_pt_tunePbt_Roc->at(j) > 5){
      deltaEta=fabs(Muon_eta->at(j) - patElectron_eta->at(0));
      deltaPhi = Muon_phi->at(j) - patElectron_phi->at(0);
      if(deltaPhi > M_PI) deltaPhi -= 2*M_PI;
      else if(deltaPhi <= -M_PI) deltaPhi +=2*M_PI;
      deltaR=sqrt(pow(deltaEta,2) + pow(deltaPhi,2));
      if (deltaR < 0.1) veto_ele = true;
     }
    }
    if (veto_ele == false){
     eejj_L13_M1000_TTtWcr_llJ_2017_PtReso2Up->Fill((Muon_PtResoUp+SubLeadLep+BoostJet).M(), wg);
    }
   }
  }
  else {
   LeadLep.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   SubLeadLep.SetPtEtaPhiM(Muon_pt_tunePbt_Roc->at(0), Muon_eta->at(0), Muon_phi->at(0),0.1056583745 );
   energy_corr0= patElectron_ecalTrkEnergyPostCorr->at(0) / patElectron_energy->at(0) ;
   LeadLep= LeadLep*energy_corr0;

   extra_smearing_1 = extraSmearingSigma(SubLeadLep.Eta(), SubLeadLep.P());
   Muon1_px_smearing=SubLeadLep.Px()*gRandom->Gaus(1,extra_smearing_1);
   Muon1_py_smearing=SubLeadLep.Py()*gRandom->Gaus(1,extra_smearing_1);
   Muon1_pz_smearing=SubLeadLep.Pz()*gRandom->Gaus(1,extra_smearing_1);

   P1_smear.SetXYZ(Muon1_px_smearing, Muon1_py_smearing, Muon1_pz_smearing);
   Muon_PtResoUp.SetPtEtaPhiM(P1_smear.Pt(), P1_smear.Eta(), P1_smear.Phi(),0.1056583745 );
   Muon_PtResoDown.SetPtEtaPhiM(P1_smear.Pt(), P1_smear.Eta(), P1_smear.Phi(),0.1056583745 );

   SubLeadLep2.SetPtEtaPhiM(Muon_PtResoUp.Pt(), Muon_PtResoUp.Eta(), Muon_PtResoUp.Phi(), 0.1056583745);

   if (HLT_Ele == 1 & LeadLep.Pt() > 150 && SubLeadLep2.Pt() > 100 && fabs(LeadLep.Eta())<2.4 && fabs(SubLeadLep2.Eta())<2.4 && BoostedJet_pt->at(0) > 190 && (LeadLep+SubLeadLep2).M() > 300){
    veto_ele = false;
    for(int j = 0; j < Muon_pt_tunePbt_Roc->size(); j++){
     if (Muon_pt_tunePbt_Roc->at(j) > 5){
      deltaEta=fabs(Muon_eta->at(j) - patElectron_eta->at(0));
      deltaPhi = Muon_phi->at(j) - patElectron_phi->at(0);
      if(deltaPhi > M_PI) deltaPhi -= 2*M_PI;
      else if(deltaPhi <= -M_PI) deltaPhi +=2*M_PI;
      deltaR=sqrt(pow(deltaEta,2) + pow(deltaPhi,2));
      if (deltaR < 0.1) veto_ele = true;
     }
    }
    if (veto_ele == false){
     eejj_L13_M1000_TTtWcr_llJ_2017_PtReso2Up->Fill((Muon_PtResoUp+LeadLep+BoostJet).M(),wg);
    }
   }
  }


  if (Muon_pt_tunePbt_Roc->at(0) >= patElectron_pt->at(0)){
   LeadLep.SetPtEtaPhiM(Muon_pt_tunePbt_Roc->at(0), Muon_eta->at(0), Muon_phi->at(0),0.1056583745);
   SubLeadLep.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   energy_corr0= patElectron_ecalTrkEnergyPostCorr->at(0) / patElectron_energy->at(0) ; 
   SubLeadLep = SubLeadLep*energy_corr0;

   extra_smearing_1 = extraSmearingSigma(LeadLep.Eta(), LeadLep.P());

   Muon1_px_smearing=LeadLep.Px()*gRandom->Gaus(1,extra_smearing_1);
   Muon1_py_smearing=LeadLep.Py()*gRandom->Gaus(1,extra_smearing_1);
   Muon1_pz_smearing=LeadLep.Pz()*gRandom->Gaus(1,extra_smearing_1);

   P1_smear.SetXYZ(Muon1_px_smearing, Muon1_py_smearing, Muon1_pz_smearing);
   Muon_PtResoUp.SetPtEtaPhiM(P1_smear.Pt(), P1_smear.Eta(), P1_smear.Phi(),0.1056583745 );
   Muon_PtResoDown.SetPtEtaPhiM(P1_smear.Pt(), P1_smear.Eta(), P1_smear.Phi(),0.1056583745 );

   LeadLep2.SetPtEtaPhiM(Muon_PtResoUp.Pt(), Muon_PtResoUp.Eta(), Muon_PtResoUp.Phi(), 0.1056583745);

  if (HLT_Mu == 1 && LeadLep.Pt() > 150 && SubLeadLep.Pt() > 100 && fabs(LeadLep.Eta())<2.4 && fabs(SubLeadLep.Eta())<2.4 && BoostedJet_pt->at(0) > 190 && (LeadLep+SubLeadLep).M() > 300 ){

   veto_ele = false;
   for(int j = 0; j < Muon_pt_tunePbt_Roc->size(); j++){
    if (Muon_pt_tunePbt_Roc->at(j) > 5){
     deltaEta=fabs(Muon_eta->at(j) - patElectron_eta->at(0));
     deltaPhi = Muon_phi->at(j) - patElectron_phi->at(0);
     if(deltaPhi > M_PI) deltaPhi -= 2*M_PI;
     else if(deltaPhi <= -M_PI) deltaPhi +=2*M_PI;
     deltaR=sqrt(pow(deltaEta,2) + pow(deltaPhi,2));
     if (deltaR < 0.1) veto_ele = true;
    }
   }
   if (veto_ele == false){
    eejj_L13_M1000_TTtWcr_ll->Fill((LeadLep+SubLeadLep).M(),wg);

    /*M(emuJ)*/
    if (Muon_charge->at(0)*patElectron_charge->at(0) == 1) eejj_L13_M1000_TTtWcr_llJ_SS->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if (Muon_charge->at(0)*patElectron_charge->at(0) == -1) eejj_L13_M1000_TTtWcr_llJ_OS->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    eejj_L13_M1000_TTtWcr_llJ->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    if (fabs(LeadLep.Eta()) < 0.8 && fabs(SubLeadLep.Eta())<0.8){
     eejj_L13_M1000_TTtWcr_ll_BB->Fill((LeadLep+SubLeadLep).M(),wg);
     eejj_L13_M1000_TTtWcr_llJ_BB->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    }
    if( (fabs(LeadLep.Eta()) < 0.8 && fabs(SubLeadLep.Eta())>0.8) || (fabs(LeadLep.Eta())>0.8 &&fabs(SubLeadLep.Eta())<0.8)){
     eejj_L13_M1000_TTtWcr_ll_BE->Fill((LeadLep+SubLeadLep).M(),wg);
     eejj_L13_M1000_TTtWcr_llJ_BE->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    }
    if (fabs(LeadLep.Eta()) > 0.8 && fabs(SubLeadLep.Eta()) > 0.8){
     eejj_L13_M1000_TTtWcr_ll_EE->Fill((LeadLep+SubLeadLep).M(),wg);
     eejj_L13_M1000_TTtWcr_llJ_EE->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    }
    eejj_L13_M1000_TTtWcr_llJ_2017_AlphaRatio->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2017_AlphaRatioUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2017_AlphaRatioDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2017_SFUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_SFu);
    eejj_L13_M1000_TTtWcr_llJ_2017_SFDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_SFd);
    eejj_L13_M1000_TTtWcr_llJ_2017_PUUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_PUu);
    eejj_L13_M1000_TTtWcr_llJ_2017_PUDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_PUd);
    if ((Muon_PtResoUp+SubLeadLep).M() >300) eejj_L13_M1000_TTtWcr_llJ_2017_PtResoUp->Fill((Muon_PtResoUp+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2017_PtResoDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2017_PtReso2Down->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_energyScaleUp->Fill((Ele_ScaleUp+LeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_energyScaleDown->Fill((Ele_ScaleDown+LeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2017_energySigmaUp->Fill((Ele_SigmaUp+LeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2017_energySigmaDown->Fill((Ele_SigmaDown+LeadLep+BoostJet).M(),wg);
    if(centralJesJer->at(0)==1)eejj_L13_M1000_TTtWcr_llJ_centralJesJer->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if(JesSFup->at(1)==1)eejj_L13_M1000_TTtWcr_llJ_2017_JesSFUp->Fill((LeadLep+SubLeadLep+BoostJet_JESup).M(), wg);
    if(JesSFdown->at(2)==1)eejj_L13_M1000_TTtWcr_llJ_2017_JesSFDown->Fill((LeadLep+SubLeadLep+BoostJet_JESdown).M(), wg);
    if(JerSFup->at(3)==1)eejj_L13_M1000_TTtWcr_llJ_2017_JerSFUp->Fill((LeadLep+SubLeadLep+BoostJet_JERup).M(), wg);
    if(JerSFdown->at(4)==1)eejj_L13_M1000_TTtWcr_llJ_2017_JerSFDown->Fill((LeadLep+SubLeadLep+BoostJet_JERdown).M(), wg);

   }
  }
 }

 else {

   LeadLep.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   SubLeadLep.SetPtEtaPhiM(Muon_pt_tunePbt_Roc->at(0), Muon_eta->at(0), Muon_phi->at(0), 0.1056583745);
   energy_corr0= patElectron_ecalTrkEnergyPostCorr->at(0) / patElectron_energy->at(0) ;
   LeadLep = LeadLep*energy_corr0;

   extra_smearing_1 = extraSmearingSigma(SubLeadLep.Eta(), SubLeadLep.P());

   Muon1_px_smearing=LeadLep.Px()*gRandom->Gaus(1,extra_smearing_1);
   Muon1_py_smearing=LeadLep.Py()*gRandom->Gaus(1,extra_smearing_1);
   Muon1_pz_smearing=LeadLep.Pz()*gRandom->Gaus(1,extra_smearing_1);

   P1_smear.SetXYZ(Muon1_px_smearing, Muon1_py_smearing, Muon1_pz_smearing);
   Muon_PtResoUp.SetPtEtaPhiM(P1_smear.Pt(), P1_smear.Eta(), P1_smear.Phi(),0.1056583745 );
   Muon_PtResoDown.SetPtEtaPhiM(P1_smear.Pt(), P1_smear.Eta(), P1_smear.Phi(),0.1056583745 );

   SubLeadLep2.SetPtEtaPhiM(Muon_PtResoUp.Pt(), Muon_PtResoUp.Eta(), Muon_PtResoUp.Phi(), 0.1056583745);

   if (HLT_Ele == 1 & LeadLep.Pt() > 150 && SubLeadLep.Pt() > 100 && fabs(LeadLep.Eta())<2.4 && fabs(SubLeadLep.Eta())<2.4 && BoostedJet_pt->at(0) > 190 && (LeadLep+SubLeadLep).M() > 300){

    veto_ele = false;
   for(int j = 0; j < Muon_pt_tunePbt_Roc->size(); j++){
    if (Muon_pt_tunePbt_Roc->at(j) > 5){
     deltaEta=fabs(Muon_eta->at(j) - patElectron_eta->at(0));
     deltaPhi = Muon_phi->at(j) - patElectron_phi->at(0);
     if(deltaPhi > M_PI) deltaPhi -= 2*M_PI;
     else if(deltaPhi <= -M_PI) deltaPhi +=2*M_PI;
     deltaR=sqrt(pow(deltaEta,2) + pow(deltaPhi,2));
     if (deltaR < 0.1) veto_ele = true;
    }
   }
   if (veto_ele == false){
    eejj_L13_M1000_TTtWcr_ll->Fill((LeadLep+SubLeadLep).M(),wg);


     /* M(e mu J)*/
    if (Muon_charge->at(0)*patElectron_charge->at(0) == 1) eejj_L13_M1000_TTtWcr_llJ_SS->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if (Muon_charge->at(0)*patElectron_charge->at(0) == -1) eejj_L13_M1000_TTtWcr_llJ_OS->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    eejj_L13_M1000_TTtWcr_llJ->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    if (fabs(LeadLep.Eta()) < 0.8 && fabs(SubLeadLep.Eta())<0.8){
     eejj_L13_M1000_TTtWcr_ll_BB->Fill((LeadLep+SubLeadLep).M(),wg);
     eejj_L13_M1000_TTtWcr_llJ_BB->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    }
    if( (fabs(LeadLep.Eta()) < 0.8 && fabs(SubLeadLep.Eta())>0.8) || (fabs(LeadLep.Eta())>0.8 &&fabs(SubLeadLep.Eta())<0.8)){
     eejj_L13_M1000_TTtWcr_ll_BE->Fill((LeadLep+SubLeadLep).M(),wg);
     eejj_L13_M1000_TTtWcr_llJ_BE->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    }
    if (fabs(LeadLep.Eta()) > 0.8 && fabs(SubLeadLep.Eta()) > 0.8){
     eejj_L13_M1000_TTtWcr_ll_EE->Fill((LeadLep+SubLeadLep).M(),wg);
     eejj_L13_M1000_TTtWcr_llJ_EE->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    }
    eejj_L13_M1000_TTtWcr_llJ_2017_AlphaRatio->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2017_AlphaRatioUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2017_AlphaRatioDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2017_SFUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_SFu);
    eejj_L13_M1000_TTtWcr_llJ_2017_SFDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_SFd);
    eejj_L13_M1000_TTtWcr_llJ_2017_PUUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_PUu);
    eejj_L13_M1000_TTtWcr_llJ_2017_PUDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_PUd);
    if ((Muon_PtResoUp+LeadLep).M() >300) eejj_L13_M1000_TTtWcr_llJ_2017_PtResoUp->Fill((Muon_PtResoUp+LeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2017_PtResoDown->Fill((SubLeadLep+LeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2017_PtReso2Down->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_energyScaleUp->Fill((Ele_ScaleUp+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_energyScaleDown->Fill((Ele_ScaleDown+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2017_energySigmaUp->Fill((Ele_SigmaUp+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2017_energySigmaDown->Fill((Ele_SigmaDown+SubLeadLep+BoostJet).M(),wg);
    if(centralJesJer->at(0)==1)eejj_L13_M1000_TTtWcr_llJ_centralJesJer->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if(JesSFup->at(1)==1)eejj_L13_M1000_TTtWcr_llJ_2017_JesSFUp->Fill((LeadLep+SubLeadLep+BoostJet_JESup).M(), wg);
    if(JesSFdown->at(2)==1)eejj_L13_M1000_TTtWcr_llJ_2017_JesSFDown->Fill((LeadLep+SubLeadLep+BoostJet_JESdown).M(), wg);
    if(JerSFup->at(3)==1)eejj_L13_M1000_TTtWcr_llJ_2017_JerSFUp->Fill((LeadLep+SubLeadLep+BoostJet_JERup).M(), wg);
    if(JerSFdown->at(4)==1)eejj_L13_M1000_TTtWcr_llJ_2017_JerSFDown->Fill((LeadLep+SubLeadLep+BoostJet_JERdown).M(), wg);
    }
   }
  }


 } //TTtW CR 
  
 
}

TFile *f = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/2017_ALL_HOPE/18102021/SR_syst_eejj_L13_M1000_2017.root", "RECREATE");
//TFile *f = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/2017_ALL_HOPE/SR_syst_eejj_L13_M1000_2017_test.root", "RECREATE");
//TFile *f2 = new TFile("plot/SR_syst_eejj_L13_M1000_2017.root", "RECREATE");

eejj_L13_M1000_eejj_SS->Write();
eejj_L13_M1000_eejj_OS->Write();
eejj_L13_M1000_Zpeak_eejj_SS->Write();
eejj_L13_M1000_Zpeak_eejj_OS->Write();
eejj_L13_M1000_DYcr_eejj_SS->Write();
eejj_L13_M1000_DYcr_eejj_OS->Write();
eejj_L13_M1000_mumujj_SS->Write();
eejj_L13_M1000_mumujj_OS->Write();
eejj_L13_M1000_Zpeak_mumujj_SS->Write();
eejj_L13_M1000_Zpeak_mumujj_OS->Write();
eejj_L13_M1000_DYcr_mumujj_SS->Write();
eejj_L13_M1000_DYcr_mumujj_OS->Write();
eejj_L13_M1000_TTtWcr_llJ_SS->Write();
eejj_L13_M1000_TTtWcr_llJ_OS->Write();

eejj_L13_M1000_eejj_ele1_ecalTrkEnergyPostCorr->Write();
eejj_L13_M1000_eejj_ele2_ecalTrkEnergyPostCorr->Write();
eejj_L13_M1000_eejj_ele1_energy->Write();
eejj_L13_M1000_eejj_ele2_energy->Write();

eejj_L13_M1000_HTee->Write();
eejj_L13_M1000_HTee_BB->Write();
eejj_L13_M1000_HTee_BE->Write();
eejj_L13_M1000_HTee_EE->Write();
eejj_L13_M1000_HTmumu->Write();
eejj_L13_M1000_HTmumu_BB->Write();
eejj_L13_M1000_HTmumu_BE->Write();
eejj_L13_M1000_HTmumu_EE->Write();
eejj_L13_M1000_Mmumu->Write();
eejj_L13_M1000_Mmumu_BB->Write();
eejj_L13_M1000_Mmumu_BE->Write();
eejj_L13_M1000_Mmumu_EE->Write();
eejj_L13_M1000_Mee->Write();
eejj_L13_M1000_Mee_BB->Write();
eejj_L13_M1000_Mee_BE->Write();
eejj_L13_M1000_Mee_EE->Write();
eejj_L13_M1000_eejj->Write();
eejj_L13_M1000_eejj_BB->Write();
eejj_L13_M1000_eejj_BE->Write();
eejj_L13_M1000_eejj_EE->Write();
eejj_L13_M1000_eejj_2017_AlphaRatio->Write();
eejj_L13_M1000_eejj_2017_AlphaRatio_BB->Write();
eejj_L13_M1000_eejj_2017_AlphaRatio_BE->Write();
eejj_L13_M1000_eejj_2017_AlphaRatio_EE->Write();
eejj_L13_M1000_eejj_2017_AlphaRatioUp->Write();
eejj_L13_M1000_eejj_2017_AlphaRatioDown->Write();
eejj_L13_M1000_eejj_2017_SFUp->Write();
eejj_L13_M1000_eejj_2017_SFDown->Write();
eejj_L13_M1000_eejj_2017_PUUp->Write();
eejj_L13_M1000_eejj_2017_PUDown->Write();
eejj_L13_M1000_eejj_2017_centralJesJer->Write();
eejj_L13_M1000_eejj_2017_JesSFUp->Write();
eejj_L13_M1000_eejj_2017_JesSFDown->Write();
eejj_L13_M1000_eejj_2017_JerSFUp->Write();
eejj_L13_M1000_eejj_2017_JerSFDown->Write();
eejj_L13_M1000_eejj_energyScaleUp->Write();
eejj_L13_M1000_eejj_energyScaleDown->Write();
eejj_L13_M1000_eejj_2017_energySigmaUp->Write();
eejj_L13_M1000_eejj_2017_energySigmaDown->Write();

eejj_L13_M1000_mumujj_Roc->Write();
eejj_L13_M1000_mumujj_BB->Write();
eejj_L13_M1000_mumujj_BE->Write();
eejj_L13_M1000_mumujj_EE->Write();
eejj_L13_M1000_mumujj->Write();
eejj_L13_M1000_mumujj_2017_AlphaRatio->Write();
eejj_L13_M1000_mumujj_2017_AlphaRatio_BB->Write();
eejj_L13_M1000_mumujj_2017_AlphaRatio_BE->Write();
eejj_L13_M1000_mumujj_2017_AlphaRatio_EE->Write();
eejj_L13_M1000_mumujj_2017_AlphaRatioUp->Write();
eejj_L13_M1000_mumujj_2017_AlphaRatioDown->Write();
eejj_L13_M1000_mumujj_2017_SFUp->Write();
eejj_L13_M1000_mumujj_2017_SFDown->Write();
eejj_L13_M1000_mumujj_2017_PUUp->Write();
eejj_L13_M1000_mumujj_2017_PUDown->Write();
eejj_L13_M1000_mumujj_2017_centralJesJer->Write();
eejj_L13_M1000_mumujj_2017_JesSFUp->Write();
eejj_L13_M1000_mumujj_2017_JesSFDown->Write();
eejj_L13_M1000_mumujj_2017_JerSFUp->Write();
eejj_L13_M1000_mumujj_2017_JerSFDown->Write();
eejj_L13_M1000_mumujj_2017_PtResoUp->Write();
eejj_L13_M1000_mumujj_2017_PtResoDown->Write();
eejj_L13_M1000_mumujj_2017_PtReso2Up->Write();
eejj_L13_M1000_mumujj_2017_PtReso2Down->Write();
eejj_L13_M1000_eejj_PDFUp->Write();
eejj_L13_M1000_eejj_PDFDown->Write();
eejj_L13_M1000_mumujj_PDFUp->Write();
eejj_L13_M1000_mumujj_PDFDown->Write();

//Zpeak DYcr 
eejj_L13_M1000_ZpeakMll_eejj->Write();
eejj_L13_M1000_ZpeakMll_eejj_BB->Write();
eejj_L13_M1000_ZpeakMll_eejj_BE->Write();
eejj_L13_M1000_ZpeakMll_eejj_EE->Write();
eejj_L13_M1000_ZpeakMll_mumujj->Write();
eejj_L13_M1000_ZpeakMll_mumujj_BB->Write();
eejj_L13_M1000_ZpeakMll_mumujj_BE->Write();
eejj_L13_M1000_ZpeakMll_mumujj_EE->Write();
eejj_L13_M1000_Zpeak_eejj->Write();
eejj_L13_M1000_Zpeak_eejj_BB->Write();
eejj_L13_M1000_Zpeak_eejj_BE->Write();
eejj_L13_M1000_Zpeak_eejj_EE->Write();
eejj_L13_M1000_Zpeak_mumujj->Write();
eejj_L13_M1000_Zpeak_mumujj_BE->Write();
eejj_L13_M1000_Zpeak_mumujj_BB->Write();
eejj_L13_M1000_Zpeak_mumujj_EE->Write();
eejj_L13_M1000_Zpeak_ee_pt->Write();
eejj_L13_M1000_Zpeak_ee_pt_BB->Write();
eejj_L13_M1000_Zpeak_ee_pt_BE->Write();
eejj_L13_M1000_Zpeak_ee_pt_EE->Write();
eejj_L13_M1000_Zpeak_mumu_pt->Write();
eejj_L13_M1000_Zpeak_mumu_pt_BB->Write();
eejj_L13_M1000_Zpeak_mumu_pt_BE->Write();
eejj_L13_M1000_Zpeak_mumu_pt_EE->Write();

//DYcr 
Mee_DYcr->Write();
Mee_DYcr_BB->Write();
Mee_DYcr_BE->Write();
Mee_DYcr_EE->Write();
eejj_L13_M1000_DYcr_eejj_ele1_ecalTrkEnergyPostCorr->Write();
eejj_L13_M1000_DYcr_eejj_ele2_ecalTrkEnergyPostCorr->Write();
eejj_L13_M1000_DYcr_eejj_ele1_energy->Write();
eejj_L13_M1000_DYcr_eejj_ele2_energy->Write();
eejj_L13_M1000_DYcr_eejj->Write();
eejj_L13_M1000_DYcr_eejj_BB->Write();
eejj_L13_M1000_DYcr_eejj_BE->Write();
eejj_L13_M1000_DYcr_eejj_EE->Write();
eejj_L13_M1000_DYcr_eejj_2017_AlphaRatio->Write();
eejj_L13_M1000_DYcr_eejj_2017_AlphaRatio_BB->Write();
eejj_L13_M1000_DYcr_eejj_2017_AlphaRatio_BE->Write();
eejj_L13_M1000_DYcr_eejj_2017_AlphaRatio_EE->Write();
eejj_L13_M1000_DYcr_eejj_2017_AlphaRatioUp->Write();
eejj_L13_M1000_DYcr_eejj_2017_AlphaRatioDown->Write();
eejj_L13_M1000_DYcr_eejj_2017_SFUp->Write();
eejj_L13_M1000_DYcr_eejj_2017_SFDown->Write();
eejj_L13_M1000_DYcr_eejj_2017_PUUp->Write();
eejj_L13_M1000_DYcr_eejj_2017_PUDown->Write();
eejj_L13_M1000_DYcr_eejj_centralJesJer->Write();
eejj_L13_M1000_DYcr_eejj_2017_JesSFUp->Write();
eejj_L13_M1000_DYcr_eejj_2017_JesSFDown->Write();
eejj_L13_M1000_DYcr_eejj_2017_JerSFUp->Write();
eejj_L13_M1000_DYcr_eejj_2017_JerSFDown->Write();
eejj_L13_M1000_DYcr_eejj_energyScaleUp->Write();
eejj_L13_M1000_DYcr_eejj_energyScaleDown->Write();
eejj_L13_M1000_DYcr_eejj_2017_energySigmaUp->Write();
eejj_L13_M1000_DYcr_eejj_2017_energySigmaDown->Write();

Mmumu_DYcr->Write();
Mmumu_DYcr_BB->Write();
Mmumu_DYcr_BE->Write();
Mmumu_DYcr_EE->Write();
eejj_L13_M1000_DYcr_mumujj->Write();
eejj_L13_M1000_DYcr_mumujj_BB->Write();
eejj_L13_M1000_DYcr_mumujj_BE->Write();
eejj_L13_M1000_DYcr_mumujj_EE->Write();
eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatio->Write();
eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatio_BB->Write();
eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatio_BE->Write();
eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatio_EE->Write();
eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatioUp->Write();
eejj_L13_M1000_DYcr_mumujj_2017_AlphaRatioDown->Write();
eejj_L13_M1000_DYcr_mumujj_2017_SFUp->Write();
eejj_L13_M1000_DYcr_mumujj_2017_SFDown->Write();
eejj_L13_M1000_DYcr_mumujj_2017_PUUp->Write();
eejj_L13_M1000_DYcr_mumujj_2017_PUDown->Write();
eejj_L13_M1000_DYcr_mumujj_centralJesJer->Write();
eejj_L13_M1000_DYcr_mumujj_2017_JesSFUp->Write();
eejj_L13_M1000_DYcr_mumujj_2017_JesSFDown->Write();
eejj_L13_M1000_DYcr_mumujj_2017_JerSFUp->Write();
eejj_L13_M1000_DYcr_mumujj_2017_JerSFDown->Write();
eejj_L13_M1000_DYcr_mumujj_2017_PtResoUp->Write();
eejj_L13_M1000_DYcr_mumujj_2017_PtResoDown->Write();
eejj_L13_M1000_DYcr_mumujj_2017_PtReso2Up->Write();
eejj_L13_M1000_DYcr_mumujj_2017_PtReso2Down->Write();

//TTtW cr
eejj_L13_M1000_TTtWcr_ll->Write();
eejj_L13_M1000_TTtWcr_ll_BB->Write();
eejj_L13_M1000_TTtWcr_ll_BE->Write();
eejj_L13_M1000_TTtWcr_ll_EE->Write();
eejj_L13_M1000_TTtWcr_llJ->Write();
eejj_L13_M1000_TTtWcr_llJ_BB->Write();
eejj_L13_M1000_TTtWcr_llJ_BE->Write();
eejj_L13_M1000_TTtWcr_llJ_EE->Write();
eejj_L13_M1000_TTtWcr_llJ_2017_AlphaRatio->Write();
eejj_L13_M1000_TTtWcr_llJ_2017_AlphaRatioUp->Write();
eejj_L13_M1000_TTtWcr_llJ_2017_AlphaRatioDown->Write();
eejj_L13_M1000_TTtWcr_llJ_2017_SFUp->Write();
eejj_L13_M1000_TTtWcr_llJ_2017_SFDown->Write();
eejj_L13_M1000_TTtWcr_llJ_2017_PUUp->Write();
eejj_L13_M1000_TTtWcr_llJ_2017_PUDown->Write();
eejj_L13_M1000_TTtWcr_llJ_2017_PtResoUp->Write();
eejj_L13_M1000_TTtWcr_llJ_2017_PtResoDown->Write();
eejj_L13_M1000_TTtWcr_llJ_2017_PtReso2Up->Write();
eejj_L13_M1000_TTtWcr_llJ_2017_PtReso2Down->Write();
eejj_L13_M1000_TTtWcr_llJ_energyScaleUp->Write();
eejj_L13_M1000_TTtWcr_llJ_energyScaleDown->Write();
eejj_L13_M1000_TTtWcr_llJ_2017_energySigmaUp->Write();
eejj_L13_M1000_TTtWcr_llJ_2017_energySigmaDown->Write();
eejj_L13_M1000_TTtWcr_llJ_centralJesJer->Write();
eejj_L13_M1000_TTtWcr_llJ_2017_JesSFUp->Write();
eejj_L13_M1000_TTtWcr_llJ_2017_JesSFDown->Write();
eejj_L13_M1000_TTtWcr_llJ_2017_JerSFUp->Write();
eejj_L13_M1000_TTtWcr_llJ_2017_JerSFDown->Write();

f->Write();
f->Close();

}
 
