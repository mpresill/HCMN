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
void Analisi_SR_DY_syst_2017_v5_Rebinned(){

TChain *a_ = new TChain("BOOM");

//a_->Add("/eos/user/m/mpresill/CMS/HN_Reload/DY_HTsplitted/25062021/DY_HTincl_LO_2017.root");
a_->Add("/eos/user/m/mpresill/CMS/HN_Reload/DY_HTsplitted/25062021/DYbins/DY_HTincl_LO_2017.root");


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
int nBestVtx;
double EVENT_prefireWeight, EVENT_prefireWeightUp, EVENT_prefireWeightDown;

/* gen particles*/
vector<double>*Gen_pt; Gen_pt = 0;
vector<double>*Gen_status; Gen_status = 0;
vector<double>*Gen_eta; Gen_eta = 0;
vector<double>*Gen_phi; Gen_phi = 0;
vector<double>*Gen_charge; Gen_charge = 0;
vector<double>*Gen_energy; Gen_energy = 0;
vector<double>*Gen_pdg_id; Gen_pdg_id = 0;
vector<double>*Gen_motherpdg_id; Gen_motherpdg_id = 0;
vector<double>*Gen_numDaught; Gen_numDaught = 0;
vector<double>*Gen_numMother; Gen_numMother = 0;

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
TBranch *a_2017_PUWeight=a_->GetBranch("PUWeight");
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

/*gen particles*/
TBranch *a_Gen_pt=a_->GetBranch("Gen_pt");
TBranch *a_Gen_status=a_->GetBranch("Gen_status");
TBranch *a_Gen_eta=a_->GetBranch("Gen_eta");
TBranch *a_Gen_phi=a_->GetBranch("Gen_phi");
TBranch *a_Gen_charge=a_->GetBranch("Gen_charge");
TBranch *a_Gen_energy=a_->GetBranch("Gen_energy");
TBranch *a_Gen_pdg_id=a_->GetBranch("Gen_pdg_id");
TBranch *a_Gen_motherpdg_id=a_->GetBranch("Gen_motherpdg_id");
TBranch *a_Gen_numDaught=a_->GetBranch("Gen_numDaught");
TBranch *a_Gen_numMother=a_->GetBranch("Gen_numMother");

TBranch *a_EVENT_prefireWeight=a_->GetBranch("EVENT_prefireWeight");
TBranch *a_EVENT_prefireWeightUp=a_->GetBranch("EVENT_prefireWeightUp");
TBranch *a_EVENT_prefireWeightDown=a_->GetBranch("EVENT_prefireWeightDown");

a_Gen_pt->SetAddress(&Gen_pt);
a_Gen_status->SetAddress(&Gen_status);
a_Gen_eta->SetAddress(&Gen_eta);
a_Gen_phi->SetAddress(&Gen_phi);
a_Gen_charge->SetAddress(&Gen_charge);
a_Gen_energy->SetAddress(&Gen_energy);
a_Gen_pdg_id->SetAddress(&Gen_pdg_id);
a_Gen_motherpdg_id->SetAddress(&Gen_motherpdg_id);
a_Gen_numDaught->SetAddress(&Gen_numDaught);
a_Gen_numMother->SetAddress(&Gen_numMother);

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
a_2017_PUWeight->SetAddress(&PUWeight);
a_MinBiasUpWeight->SetAddress(&MinBiasUpWeight);
a_MinBiasDownWeight->SetAddress(&MinBiasDownWeight);

a_muejj_l->SetAddress(&muejj_l);
a_emujj_l->SetAddress(&emujj_l);

a_numOfHighptEle->SetAddress(&numOfHighptEle);
a_numOfHighptMu->SetAddress(&numOfHighptMu);
a_numOfLooseMu->SetAddress(&numOfLooseMu);
a_numOfBoostedJets->SetAddress(&numOfBoostedJets);
a_numOfVetoEle->SetAddress(&numOfVetoEle);

a_EVENT_prefireWeight->SetAddress(&EVENT_prefireWeight);
a_EVENT_prefireWeightUp->SetAddress(&EVENT_prefireWeightUp);
a_EVENT_prefireWeightDown->SetAddress(&EVENT_prefireWeightDown);

a_centralJesJer->SetAddress(&centralJesJer);
a_JesSFup->SetAddress(&JesSFup);
a_JesSFdown->SetAddress(&JesSFdown);
a_JerSFup->SetAddress(&JerSFup);
a_JerSFdown->SetAddress(&JerSFdown);


//old bin
const double asymbins[9] = {0,200,400,600,800,1000,1400,2000,10000};
const double asymbinspt[5] = {250, 300, 350, 500, 10000};

TH1D *DY_eejj_SS = new TH1D("DY_eejj_SS", "DY_eejj_SS", 8, asymbins);
TH1D *DY_eejj_OS = new TH1D("DY_eejj_OS", "DY_eejj_OS", 8, asymbins);
TH1D *DY_mumujj_SS = new TH1D("DY_mumujj_SS", "DY_mumujj_SS", 8, asymbins);
TH1D *DY_mumujj_OS = new TH1D("DY_mumujj_OS", "DY_mumujj_OS", 8, asymbins);
TH1D *DY_Zpeak_eejj_SS = new TH1D("DY_Zpeak_eejj_SS", "DY_Zpeak_eejj_SS", 8, asymbins);
TH1D *DY_Zpeak_eejj_OS = new TH1D("DY_Zpeak_eejj_OS", "DY_Zpeak_eejj_OS", 8, asymbins);
TH1D *DY_Zpeak_mumujj_SS = new TH1D("DY_Zpeak_mumujj_SS", "DY_Zpeak_mumujj_SS", 8, asymbins);
TH1D *DY_Zpeak_mumujj_OS = new TH1D("DY_Zpeak_mumujj_OS", "DY_Zpeak_mumujj_OS", 8, asymbins);
TH1D *DY_DYcr_eejj_SS = new TH1D("DY_DYcr_eejj_SS", "DY_DYcr_eejj_SS", 8, asymbins);
TH1D *DY_DYcr_eejj_OS = new TH1D("DY_DYcr_eejj_OS", "DY_DYcr_eejj_OS", 8, asymbins);
TH1D *DY_DYcr_mumujj_SS = new TH1D("DY_DYcr_mumujj_SS", "DY_DYcr_mumujj_SS", 8, asymbins);
TH1D *DY_DYcr_mumujj_OS = new TH1D("DY_DYcr_mumujj_OS", "DY_DYcr_mumujj_OS", 8, asymbins);
TH1D *DY_TTtWcr_llJ_SS = new TH1D("DY_TTtWcr_llJ_SS", "DY_TTtWcr_llJ_SS", 8, asymbins);
TH1D *DY_TTtWcr_llJ_OS = new TH1D("DY_TTtWcr_llJ_OS", "DY_TTtWcr_llJ_OS", 8, asymbins);

TH1D *DY_HTmumu = new TH1D ("DY_HTmumu", "DY_HTmumu", 100, 0, 5000);
TH1D *DY_HTmumu_BB = new TH1D ("DY_HTmumu_BB", "DY_HTmumu_BB", 100, 0, 5000);
TH1D *DY_HTmumu_BE = new TH1D ("DY_HTmumu_BE", "DY_HTmumu_BE", 100, 0, 5000);
TH1D *DY_HTmumu_EE = new TH1D ("DY_HTmumu_EE", "DY_HTmumu_EE", 100, 0, 5000);
TH1D *DY_Mmumu = new TH1D ("DY_Mmumu", "DY_Mmumu", 100, 0, 1000);
TH1D *DY_Mmumu_BB = new TH1D ("DY_Mmumu_BB", "DY_Mmumu_BB", 100, 0, 1000);
TH1D *DY_Mmumu_BE = new TH1D ("DY_Mmumu_BE", "DY_Mmumu_BE", 100, 0, 1000);
TH1D *DY_Mmumu_EE = new TH1D ("DY_Mmumu_EE", "DY_Mmumu_EE", 100, 0, 1000);
TH1D *DY_mumujj_Roc = new TH1D ("DY_mumujj_Roc", "DY_mumujj_Roc", 8, asymbins);
TH1D *DY_mumujj = new TH1D ("DY_mumujj", "DY_mumujj", 8, asymbins);
TH1D *DY_mumujj_BB = new TH1D ("DY_mumujj_BB", "DY_mumujj_BB", 8, asymbins);
TH1D *DY_mumujj_BE = new TH1D ("DY_mumujj_BE", "DY_mumujj_BE", 8, asymbins);
TH1D *DY_mumujj_EE = new TH1D ("DY_mumujj_EE", "DY_mumujj_EE", 8, asymbins);
TH1D *DY_mumujj_2017_AlphaRatio = new TH1D ("DY_mumujj_2017_AlphaRatio", "DY_mumujj_2017_AlphaRatio", 8, asymbins);
TH1D *DY_mumujj_2017_AlphaRatio_BB = new TH1D ("DY_mumujj_2017_AlphaRatio_BB", "DY_mumujj_2017_AlphaRatio_BB", 8, asymbins);
TH1D *DY_mumujj_2017_AlphaRatio_BE = new TH1D ("DY_mumujj_2017_AlphaRatio_BE", "DY_mumujj_2017_AlphaRatio_BE", 8, asymbins);
TH1D *DY_mumujj_2017_AlphaRatio_EE = new TH1D ("DY_mumujj_2017_AlphaRatio_EE", "DY_mumujj_2017_AlphaRatio_EE", 8, asymbins);
TH1D *DY_mumujj_2017_AlphaRatioDown = new TH1D ("DY_mumujj_2017_AlphaRatioDown", "DY_mumujj_2017_AlphaRatioDown", 8, asymbins);
TH1D *DY_mumujj_2017_AlphaRatioUp = new TH1D ("DY_mumujj_2017_AlphaRatioUp", "DY_mumujj_2017_AlphaRatioUp", 8, asymbins);
TH1D *DY_mumujj_2017_SFUp = new TH1D ("DY_mumujj_2017_SFUp", "DY_mumujj_2017_SFUp", 8, asymbins);
TH1D *DY_mumujj_2017_SFDown = new TH1D ("DY_mumujj_2017_SFDown", "DY_mumujj_2017_SFDown", 8, asymbins);
TH1D *DY_mumujj_2017_PUUp = new TH1D ("DY_mumujj_2017_PUUp", "DY_mumujj_2017_PUUp", 8, asymbins);
TH1D *DY_mumujj_2017_PUDown = new TH1D ("DY_mumujj_2017_PUDown", "DY_mumujj_2017_PUDown", 8, asymbins);
TH1D *DY_mumujj_2017_centralJesJer = new TH1D ("DY_mumujj_2017_centralJesJer", "DY_mumujj_2017_centralJesJer", 8, asymbins);
TH1D *DY_mumujj_2017_JesSFUp = new TH1D ("DY_mumujj_2017_JesSFUp", "DY_mumujj_2017_JesSFUp", 8, asymbins);
TH1D *DY_mumujj_2017_JesSFDown = new TH1D ("DY_mumujj_2017_JesSFDown", "DY_mumujj_2017_JesSFDown", 8, asymbins);
TH1D *DY_mumujj_2017_JerSFUp = new TH1D ("DY_mumujj_2017_JerSFUp", "DY_mumujj_2017_JerSFUp", 8, asymbins);
TH1D *DY_mumujj_2017_JerSFDown = new TH1D ("DY_mumujj_2017_JerSFDown", "DY_mumujj_2017_JerSFDown", 8, asymbins);
//TH1D *DY_mumujj_2017_PtCorrDown = new TH1D ("DY_mumujj_2017_PtCorrDown", "DY_mumujj_2017_PtCorrDown", 8, asymbins);
//TH1D *DY_mumujj_2017_PtCorrUp = new TH1D ("DY_mumujj_2017_PtCorrUp", "DY_mumujj_2017_PtCorrUp", 8, asymbins);
TH1D *DY_mumujj_2017_PtResoUp  = new TH1D ("DY_mumujj_2017_PtResoUp", "DY_mumujj_2017_PtResoUp", 8, asymbins);
TH1D *DY_mumujj_2017_PtResoDown  = new TH1D ("DY_mumujj_2017_PtResoDown", "DY_mumujj_2017_PtResoDown", 8, asymbins);
TH1D *DY_mumujj_2017_PtReso2Up  = new TH1D ("DY_mumujj_2017_PtReso2Up", "DY_mumujj_2017_PtReso2Up", 8, asymbins);
TH1D *DY_mumujj_2017_PtReso2Down  = new TH1D ("DY_mumujj_2017_PtReso2Down", "DY_mumujj_2017_PtReso2Down", 8, asymbins);
TH1D *DY_mumujj_2017_PrefUp = new TH1D ("DY_mumujj_2017_PrefUp", "DY_mumujj_2017_PrefUp", 8, asymbins);
TH1D *DY_mumujj_2017_PrefDown = new TH1D ("DY_mumujj_2017_PrefDown", "DY_mumujj_2017_PrefDown", 8, asymbins);
TH1D *DY_mumujj_2017_KqcdUp = new TH1D ("DY_mumujj_2017_KqcdUp", "DY_mumujj_2017_KqcdUp", 8, asymbins);
TH1D *DY_mumujj_2017_KqcdDown = new TH1D ("DY_mumujj_2017_KqcdDown", "DY_mumujj_2017_KqcdDown", 8, asymbins);

TH1D *DY_Mee = new TH1D ("DY_Mee", "DY_Mee", 100, 0, 1000);
TH1D *DY_Mee_BB = new TH1D ("DY_Mee_BB", "DY_Mee_BB", 100, 0, 1000);
TH1D *DY_Mee_BE = new TH1D ("DY_Mee_BE", "DY_Mee_BE", 100, 0, 1000);
TH1D *DY_Mee_EE = new TH1D ("DY_Mee_EE", "DY_Mee_EE", 100, 0, 1000);
TH1D *DY_HTee = new TH1D ("DY_HTee", "DY_HTee", 100, 0, 5000);
TH1D *DY_HTee_BB = new TH1D ("DY_HTee_BB", "DY_HTee_BB", 100, 0, 5000);
TH1D *DY_HTee_BE = new TH1D ("DY_HTee_BE", "DY_HTee_BE", 100, 0, 5000);
TH1D *DY_HTee_EE = new TH1D ("DY_HTee_EE", "DY_HTee_EE", 100, 0, 5000);
TH1D *DY_eejj_ele1_ecalTrkEnergyPostCorr = new TH1D ("DY_eejj_ele1_ecalTrkEnergyPostCorr", "DY_eejj_ele1_ecalTrkEnergyPostCorr", 100, 0, 1000);
TH1D *DY_eejj_ele2_ecalTrkEnergyPostCorr = new TH1D ("DY_eejj_ele2_ecalTrkEnergyPostCorr", "DY_eejj_ele2_ecalTrkEnergyPostCorr", 100, 0, 1000);
TH1D *DY_eejj_ele1_energy = new TH1D ("DY_eejj_ele1_energy", "DY_eejj_ele1_energy", 100, 0, 1000);
TH1D *DY_eejj_ele2_energy = new TH1D ("DY_eejj_ele2_energy", "DY_eejj_ele2_energy", 100, 0, 1000);
TH1D *DY_eejj = new TH1D ("DY_eejj", "DY_eejj", 8, asymbins);
TH1D *DY_eejj_BB = new TH1D ("DY_eejj_BB", "DY_eejj_BB", 8, asymbins);
TH1D *DY_eejj_BE = new TH1D ("DY_eejj_BE", "DY_eejj_BE", 8, asymbins);
TH1D *DY_eejj_EE = new TH1D ("DY_eejj_EE", "DY_eejj_EE", 8, asymbins);
TH1D *DY_eejj_2017_AlphaRatio = new TH1D ("DY_eejj_2017_AlphaRatio", "DY_eejj_2017_AlphaRatio", 8, asymbins);
TH1D *DY_eejj_2017_AlphaRatio_BB = new TH1D ("DY_eejj_2017_AlphaRatio_BB", "DY_eejj_2017_AlphaRatio_BB", 8, asymbins);
TH1D *DY_eejj_2017_AlphaRatio_BE = new TH1D ("DY_eejj_2017_AlphaRatio_BE", "DY_eejj_2017_AlphaRatio_BE", 8, asymbins);
TH1D *DY_eejj_2017_AlphaRatio_EE = new TH1D ("DY_eejj_2017_AlphaRatio_EE", "DY_eejj_2017_AlphaRatio_EE", 8, asymbins);
TH1D *DY_eejj_2017_AlphaRatioDown = new TH1D ("DY_eejj_2017_AlphaRatioDown", "DY_eejj_2017_AlphaRatioDown", 8, asymbins);
TH1D *DY_eejj_2017_AlphaRatioUp = new TH1D ("DY_eejj_2017_AlphaRatioUp", "DY_eejj_2017_AlphaRatioUp", 8, asymbins);
TH1D *DY_eejj_2017_SFUp = new TH1D ("DY_eejj_2017_SFUp", "DY_eejj_2017_SFUp", 8, asymbins);
TH1D *DY_eejj_2017_SFDown = new TH1D ("DY_eejj_2017_SFDown", "DY_eejj_2017_SFDown", 8, asymbins);
TH1D *DY_eejj_2017_PUUp = new TH1D ("DY_eejj_2017_PUUp", "DY_eejj_2017_PUUp", 8, asymbins);
TH1D *DY_eejj_2017_PUDown = new TH1D ("DY_eejj_2017_PUDown", "DY_eejj_2017_PUDown", 8, asymbins);
TH1D *DY_eejj_2017_centralJesJer = new TH1D ("DY_eejj_2017_centralJesJer", "DY_eejj_2017_centralJesJer", 8, asymbins);
TH1D *DY_eejj_2017_JesSFUp = new TH1D ("DY_eejj_2017_JesSFUp", "DY_eejj_2017_JesSFUp", 8, asymbins);
TH1D *DY_eejj_2017_JesSFDown = new TH1D ("DY_eejj_2017_JesSFDown", "DY_eejj_2017_JesSFDown", 8, asymbins);
TH1D *DY_eejj_2017_JerSFUp = new TH1D ("DY_eejj_2017_JerSFUp", "DY_eejj_2017_JerSFUp", 8, asymbins);
TH1D *DY_eejj_2017_JerSFDown = new TH1D ("DY_eejj_2017_JerSFDown", "DY_eejj_2017_JerSFDown", 8, asymbins);
TH1D *DY_eejj_energyScaleUp = new TH1D ("DY_eejj_energyScaleUp", "DY_eejj_energyScaleUp", 8, asymbins);
TH1D *DY_eejj_energyScaleDown = new TH1D ("DY_eejj_energyScaleDown", "DY_eejj_energyScaleDown", 8, asymbins);
TH1D *DY_eejj_2017_energySigmaUp = new TH1D ("DY_eejj_2017_energySigmaUp", "DY_eejj_2017_energySigmaUp", 8, asymbins);
TH1D *DY_eejj_2017_energySigmaDown = new TH1D ("DY_eejj_2017_energySigmaDown", "DY_eejj_2017_energySigmaDown", 8, asymbins);
TH1D *DY_eejj_2017_PrefUp = new TH1D ("DY_eejj_2017_PrefUp", "DY_eejj_2017_PrefUp", 8, asymbins);
TH1D *DY_eejj_2017_PrefDown = new TH1D ("DY_eejj_2017_PrefDown", "DY_eejj_2017_PrefDown", 8, asymbins);
TH1D *DY_eejj_2017_KqcdUp = new TH1D ("DY_eejj_2017_KqcdUp", "DY_eejj_2017_KqcdUp", 8, asymbins);
TH1D *DY_eejj_2017_KqcdDown = new TH1D ("DY_eejj_2017_KqcdDown", "DY_eejj_2017_KqcdDown", 8, asymbins);

//DY CR Zpeak (mll in 60-120 GeV)
TH1D *n_best_Vtx = new TH1D ("n_best_Vtx", "n_best_Vtx", 100,0, 100);
TH1D *DY_ZpeakMll_mumujj = new TH1D ("DY_ZpeakMll_mumujj", "DY_ZpeakMll_mumujj", 60,60,120);
TH1D *DY_ZpeakMll_mumujj_BB = new TH1D ("DY_ZpeakMll_mumujj_BB", "DY_ZpeakMll_mumujj_BB", 60,60,120);
TH1D *DY_ZpeakMll_mumujj_BE = new TH1D ("DY_ZpeakMll_mumujj_BE", "DY_ZpeakMll_mumujj_BE", 60,60,120);
TH1D *DY_ZpeakMll_mumujj_EE = new TH1D ("DY_ZpeakMll_mumujj_EE", "DY_ZpeakMll_mumujj_EE", 60,60,120);
TH1D *DY_Zpeak_mumujj = new TH1D ("DY_Zpeak_mumujj", "DY_Zpeak_mumujj", 8, asymbins);
TH1D *DY_Zpeak_mumujj_BB = new TH1D ("DY_Zpeak_mumujj_BB", "DY_Zpeak_mumujj_BB", 8, asymbins);
TH1D *DY_Zpeak_mumujj_BE = new TH1D ("DY_Zpeak_mumujj_BE", "DY_Zpeak_mumujj_BE", 8, asymbins);
TH1D *DY_Zpeak_mumujj_EE = new TH1D ("DY_Zpeak_mumujj_EE", "DY_Zpeak_mumujj_EE", 8, asymbins);
TH1D *DY_ZpeakMll_eejj = new TH1D ("DY_ZpeakMll_eejj", "DY_ZpeakMll_eejj", 60,60,120);
TH1D *DY_ZpeakMll_eejj_BB = new TH1D ("DY_ZpeakMll_eejj_BB", "DY_ZpeakMll_eejj_BB", 60,60,120);
TH1D *DY_ZpeakMll_eejj_BE = new TH1D ("DY_ZpeakMll_eejj_BE", "DY_ZpeakMll_eejj_BE", 60,60,120);
TH1D *DY_ZpeakMll_eejj_EE = new TH1D ("DY_ZpeakMll_eejj_EE", "DY_ZpeakMll_eejj_EE", 60,60,120);
TH1D *DY_Zpeak_eejj = new TH1D ("DY_Zpeak_eejj", "DY_Zpeak_eejj", 8, asymbins);
TH1D *DY_Zpeak_eejj_BB = new TH1D ("DY_Zpeak_eejj_BB", "DY_Zpeak_eejj_BB", 8, asymbins);
TH1D *DY_Zpeak_eejj_BE = new TH1D ("DY_Zpeak_eejj_BE", "DY_Zpeak_eejj_BE", 8, asymbins);
TH1D *DY_Zpeak_eejj_EE = new TH1D ("DY_Zpeak_eejj_EE", "DY_Zpeak_eejj_EE", 8, asymbins);
TH1D *DY_Zpeak_mumu_pt_2017 = new TH1D ("DY_Zpeak_mumu_pt_2017", "DY_Zpeak_mumu_pt_2017", 100, 0, 1000);
TH1D *DY_Zpeak_mumu_pt_2017_BB = new TH1D ("DY_Zpeak_mumu_pt_2017_BB", "DY_Zpeak_mumu_pt_2017_BB", 100, 0, 1000);
TH1D *DY_Zpeak_mumu_pt_2017_BE = new TH1D ("DY_Zpeak_mumu_pt_2017_BE", "DY_Zpeak_mumu_pt_2017_BE", 100, 0, 1000);
TH1D *DY_Zpeak_mumu_pt_2017_EE = new TH1D ("DY_Zpeak_mumu_pt_2017_EE", "DY_Zpeak_mumu_pt_2017_EE", 100, 0, 1000);
TH1D *DY_Zpeak_ee_pt_2017 = new TH1D ("DY_Zpeak_ee_pt_2017", "DY_Zpeak_ee_pt_2017", 100, 0, 1000);
TH1D *DY_Zpeak_ee_pt_2017_BB = new TH1D ("DY_Zpeak_ee_pt_2017_BB", "DY_Zpeak_ee_pt_2017_BB", 100, 0, 1000);
TH1D *DY_Zpeak_ee_pt_2017_BE = new TH1D ("DY_Zpeak_ee_pt_2017_BE", "DY_Zpeak_ee_pt_2017_BE", 100, 0, 1000);
TH1D *DY_Zpeak_ee_pt_2017_EE = new TH1D ("DY_Zpeak_ee_pt_2017_EE", "DY_Zpeak_ee_pt_2017_EE", 100, 0, 1000);

TH1D *DY_Zpeak_mumu_pt_2017_SFUp = new TH1D ("DY_Zpeak_mumu_pt_2017_SFUp", "DY_Zpeak_mumu_pt_2017_SFUp", 4, asymbinspt);
TH1D *DY_Zpeak_mumu_pt_2017_SFDown = new TH1D ("DY_Zpeak_mumu_pt_2017_SFDown", "DY_Zpeak_mumu_pt_2017_SFDown", 4, asymbinspt);
TH1D *DY_Zpeak_mumu_pt_2017_PUUp = new TH1D ("DY_Zpeak_mumu_pt_2017_PUUp", "DY_Zpeak_mumu_pt_2017_PUUp", 4, asymbinspt);
TH1D *DY_Zpeak_mumu_pt_2017_PUDown = new TH1D ("DY_Zpeak_mumu_pt_2017_PUDown", "DY_Zpeak_mumu_pt_2017_PUDown", 4, asymbinspt);
TH1D *DY_Zpeak_mumu_pt_2017_PtResoUp = new TH1D ("DY_Zpeak_mumu_pt_2017_PtResoUp", "DY_Zpeak_mumu_pt_2017_PtResoUp", 4, asymbinspt);
TH1D *DY_Zpeak_mumu_pt_2017_PtResoDown = new TH1D ("DY_Zpeak_mumu_pt_2017_PtResoDown", "DY_Zpeak_mumu_pt_2017_PtResoDown", 4, asymbinspt);
TH1D *DY_Zpeak_mumu_pt_2017_PtReso2Down = new TH1D ("DY_Zpeak_mumu_pt_2017_PtReso2Down", "DY_Zpeak_mumu_pt_2017_PtReso2Down", 4, asymbinspt);
TH1D *DY_Zpeak_mumu_pt_2017_centralJesJer = new TH1D ("DY_Zpeak_mumu_pt_2017_centralJesJer", "DY_Zpeak_mumu_pt_2017_centralJesJer", 4, asymbinspt);
TH1D *DY_Zpeak_mumu_pt_2017_JesSFUp = new TH1D ("DY_Zpeak_mumu_pt_2017_JesSFUp", "DY_Zpeak_mumu_pt_2017_JesSFUp", 4, asymbinspt);
TH1D *DY_Zpeak_mumu_pt_2017_JesSFDown = new TH1D ("DY_Zpeak_mumu_pt_2017_JesSFDown", "DY_Zpeak_mumu_pt_2017_JesSFDown", 4, asymbinspt);
TH1D *DY_Zpeak_mumu_pt_2017_JerSFUp = new TH1D ("DY_Zpeak_mumu_pt_2017_JerSFUp", "DY_Zpeak_mumu_pt_2017_JerSFUp", 4, asymbinspt);
TH1D *DY_Zpeak_mumu_pt_2017_JerSFDown = new TH1D ("DY_Zpeak_mumu_pt_2017_JerSFDown", "DY_Zpeak_mumu_pt_2017_JerSFDown", 4, asymbinspt);

TH1D *DY_Zpeak_ee_pt_2017_SFUp = new TH1D ("DY_Zpeak_ee_pt_2017_SFUp", "DY_Zpeak_ee_pt_2017_SFUp", 4, asymbinspt);
TH1D *DY_Zpeak_ee_pt_2017_SFDown = new TH1D ("DY_Zpeak_ee_pt_2017_SFDown", "DY_Zpeak_ee_pt_2017_SFDown", 4, asymbinspt);
TH1D *DY_Zpeak_ee_pt_2017_PUUp = new TH1D ("DY_Zpeak_ee_pt_2017_PUUp", "DY_Zpeak_ee_pt_2017_PUUp", 4, asymbinspt);
TH1D *DY_Zpeak_ee_pt_2017_PUDown = new TH1D ("DY_Zpeak_ee_pt_2017_PUDown", "DY_Zpeak_ee_pt_2017_PUDown", 4, asymbinspt);
TH1D *DY_Zpeak_ee_pt_energyScaleUp = new TH1D ("DY_Zpeak_ee_pt_energyScaleUp", "DY_Zpeak_ee_pt_energyScaleUp", 4, asymbinspt);
TH1D *DY_Zpeak_ee_pt_energyScaleDown = new TH1D ("DY_Zpeak_ee_pt_energyScaleDown", "DY_Zpeak_ee_pt_energyScaleDown", 4, asymbinspt);
TH1D *DY_Zpeak_ee_pt_2017_energySigmaUp = new TH1D ("DY_Zpeak_ee_pt_2017_energySigmaUp", "DY_Zpeak_ee_pt_2017_energySigmaUp", 4, asymbinspt);
TH1D *DY_Zpeak_ee_pt_2017_energySigmaDown = new TH1D ("DY_Zpeak_ee_pt_2017_energySigmaDown", "DY_Zpeak_ee_pt_2017_energySigmaDown", 4, asymbinspt);
TH1D *DY_Zpeak_ee_pt_2017_centralJesJer = new TH1D ("DY_Zpeak_ee_pt_2017_centralJesJer", "DY_Zpeak_ee_pt_2017_centralJesJer", 4, asymbinspt);
TH1D *DY_Zpeak_ee_pt_2017_JesSFUp = new TH1D ("DY_Zpeak_ee_pt_2017_JesSFUp", "DY_Zpeak_ee_pt_2017_JesSFUp", 4, asymbinspt);
TH1D *DY_Zpeak_ee_pt_2017_JesSFDown = new TH1D ("DY_Zpeak_ee_pt_2017_JesSFDown", "DY_Zpeak_ee_pt_2017_JesSFDown", 4, asymbinspt);
TH1D *DY_Zpeak_ee_pt_2017_JerSFUp = new TH1D ("DY_Zpeak_ee_pt_2017_JerSFUp", "DY_Zpeak_ee_pt_2017_JerSFUp", 4, asymbinspt);
TH1D *DY_Zpeak_ee_pt_2017_JerSFDown = new TH1D ("DY_Zpeak_ee_pt_2017_JerSFDown", "DY_Zpeak_ee_pt_2017_JerSFDown", 4, asymbinspt);

//DY CR (mll in 150-300 GeV)
TH1D *Mmumu_DYcr = new TH1D ("Mmumu_DYcr", "Mmumu_DYcr", 50, 150, 300);
TH1D *Mmumu_DYcr_BB = new TH1D ("Mmumu_DYcr_BB", "Mmumu_DYcr_BB", 50, 150, 300);
TH1D *Mmumu_DYcr_BE = new TH1D ("Mmumu_DYcr_BE", "Mmumu_DYcr_BE", 50, 150, 300);
TH1D *Mmumu_DYcr_EE = new TH1D ("Mmumu_DYcr_EE", "Mmumu_DYcr_EE", 50, 150, 300);
TH1D *DY_DYcr_mumujj = new TH1D ("DY_DYcr_mumujj", "DY_DYcr_mumujj", 8, asymbins);
TH1D *DY_DYcr_mumujj_BB = new TH1D ("DY_DYcr_mumujj_BB", "DY_DYcr_mumujj_BB", 8, asymbins);
TH1D *DY_DYcr_mumujj_BE = new TH1D ("DY_DYcr_mumujj_BE", "DY_DYcr_mumujj_BE", 8, asymbins);
TH1D *DY_DYcr_mumujj_EE = new TH1D ("DY_DYcr_mumujj_EE", "DY_DYcr_mumujj_EE", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_AlphaRatio = new TH1D ("DY_DYcr_mumujj_2017_AlphaRatio", "DY_DYcr_mumujj_2017_AlphaRatio", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_AlphaRatio_BB = new TH1D ("DY_DYcr_mumujj_2017_AlphaRatio_BB", "DY_DYcr_mumujj_2017_AlphaRatio_BB", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_AlphaRatio_BE = new TH1D ("DY_DYcr_mumujj_2017_AlphaRatio_BE", "DY_DYcr_mumujj_2017_AlphaRatio_BE", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_AlphaRatio_EE = new TH1D ("DY_DYcr_mumujj_2017_AlphaRatio_EE", "DY_DYcr_mumujj_2017_AlphaRatio_EE", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_AlphaRatioUp = new TH1D ("DY_DYcr_mumujj_2017_AlphaRatioUp", "DY_DYcr_mumujj_2017_AlphaRatioUp", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_AlphaRatioDown = new TH1D ("DY_DYcr_mumujj_2017_AlphaRatioDown", "DY_DYcr_mumujj_2017_AlphaRatioDown", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_SFUp = new TH1D ("DY_DYcr_mumujj_2017_SFUp", "DY_DYcr_mumujj_2017_SFUp", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_SFDown = new TH1D ("DY_DYcr_mumujj_2017_SFDown", "DY_DYcr_mumujj_2017_SFDown", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_PUUp = new TH1D ("DY_DYcr_mumujj_2017_PUUp", "DY_DYcr_mumujj_2017_PUUp", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_PUDown = new TH1D ("DY_DYcr_mumujj_2017_PUDown", "DY_DYcr_mumujj_2017_PUDown", 8, asymbins);
TH1D *DY_DYcr_mumujj_centralJesJer = new TH1D ("DY_DYcr_mumujj_centralJesJer", "DY_DYcr_mumujj_centralJesJer", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_JesSFUp = new TH1D ("DY_DYcr_mumujj_2017_JesSFUp", "DY_DYcr_mumujj_2017_JesSFUp", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_JesSFDown = new TH1D ("DY_DYcr_mumujj_2017_JesSFDown", "DY_DYcr_mumujj_2017_JesSFDown", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_JerSFUp = new TH1D ("DY_DYcr_mumujj_2017_JerSFUp", "DY_DYcr_mumujj_2017_JerSFUp", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_JerSFDown = new TH1D ("DY_DYcr_mumujj_2017_JerSFDown", "DY_DYcr_mumujj_2017_JerSFDown", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_PrefUp = new TH1D ("DY_DYcr_mumujj_2017_PrefUp", "DY_DYcr_mumujj_2017_PrefUp", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_PrefDown = new TH1D ("DY_DYcr_mumujj_2017_PrefDown", "DY_DYcr_mumujj_2017_PrefDown", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_KqcdUp = new TH1D ("DY_DYcr_mumujj_2017_KqcdUp", "DY_DYcr_mumujj_2017_KqcdUp", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_KqcdDown = new TH1D ("DY_DYcr_mumujj_2017_KqcdDown", "DY_DYcr_mumujj_2017_KqcdDown", 8, asymbins);

TH1D *Mee_DYcr = new TH1D ("Mee_DYcr", "Mee_DYcr", 50, 150, 300);
TH1D *Mee_DYcr_BB = new TH1D ("Mee_DYcr_BB", "Mee_DYcr_BB", 50, 150, 300);
TH1D *Mee_DYcr_BE = new TH1D ("Mee_DYcr_BE", "Mee_DYcr_BE", 50, 150, 300);
TH1D *Mee_DYcr_EE = new TH1D ("Mee_DYcr_EE", "Mee_DYcr_EE", 50, 150, 300);
TH1D *DY_DYcr_eejj_ele1_ecalTrkEnergyPostCorr = new TH1D ("DY_DYcr_eejj_ele1_ecalTrkEnergyPostCorr", "DY_DYcr_eejj_ele1_ecalTrkEnergyPostCorr", 100, 0, 1000);
TH1D *DY_DYcr_eejj_ele2_ecalTrkEnergyPostCorr = new TH1D ("DY_DYcr_eejj_ele2_ecalTrkEnergyPostCorr", "DY_DYcr_eejj_ele2_ecalTrkEnergyPostCorr", 100, 0, 1000);
TH1D *DY_DYcr_eejj_ele1_energy = new TH1D ("DY_DYcr_eejj_ele1_energy", "DY_DYcr_eejj_ele1_energy", 100, 0, 1000);
TH1D *DY_DYcr_eejj_ele2_energy = new TH1D ("DY_DYcr_eejj_ele2_energy", "DY_DYcr_eejj_ele2_energy", 100, 0, 1000);

TH1D *DY_DYcr_mumujj_2017_PtResoUp  = new TH1D ("DY_DYcr_mumujj_2017_PtResoUp", "DY_DYcr_mumujj_2017_PtResoUp", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_PtResoDown  = new TH1D ("DY_DYcr_mumujj_2017_PtResoDown", "DY_DYcr_mumujj_2017_PtResoDown", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_PtReso2Up  = new TH1D ("DY_DYcr_mumujj_2017_PtReso2Up", "DY_DYcr_mumujj_2017_PtReso2Up", 8, asymbins);
TH1D *DY_DYcr_mumujj_2017_PtReso2Down  = new TH1D ("DY_DYcr_mumujj_2017_PtReso2Down", "DY_DYcr_mumujj_2017_PtReso2Down", 8, asymbins);

TH1D *DY_DYcr_eejj = new TH1D ("DY_DYcr_eejj", "DY_DYcr_eejj", 8, asymbins);
TH1D *DY_DYcr_eejj_BB = new TH1D ("DY_DYcr_eejj_BB", "DY_DYcr_eejj_BB", 8, asymbins);
TH1D *DY_DYcr_eejj_BE = new TH1D ("DY_DYcr_eejj_BE", "DY_DYcr_eejj_BE", 8, asymbins);
TH1D *DY_DYcr_eejj_EE = new TH1D ("DY_DYcr_eejj_EE", "DY_DYcr_eejj_EE", 8, asymbins);
TH1D *DY_DYcr_eejj_2017_AlphaRatio = new TH1D ("DY_DYcr_eejj_2017_AlphaRatio", "DY_DYcr_eejj_2017_AlphaRatio", 8, asymbins);
TH1D *DY_DYcr_eejj_2017_AlphaRatio_BB = new TH1D ("DY_DYcr_eejj_2017_AlphaRatio_BB", "DY_DYcr_eejj_2017_AlphaRatio_BB", 8, asymbins);
TH1D *DY_DYcr_eejj_2017_AlphaRatio_BE = new TH1D ("DY_DYcr_eejj_2017_AlphaRatio_BE", "DY_DYcr_eejj_2017_AlphaRatio_BE", 8, asymbins);
TH1D *DY_DYcr_eejj_2017_AlphaRatio_EE = new TH1D ("DY_DYcr_eejj_2017_AlphaRatio_EE", "DY_DYcr_eejj_2017_AlphaRatio_EE", 8, asymbins);
TH1D *DY_DYcr_eejj_2017_AlphaRatioUp = new TH1D ("DY_DYcr_eejj_2017_AlphaRatioUp", "DY_DYcr_eejj_2017_AlphaRatioUp", 8, asymbins);
TH1D *DY_DYcr_eejj_2017_AlphaRatioDown = new TH1D ("DY_DYcr_eejj_2017_AlphaRatioDown", "DY_DYcr_eejj_2017_AlphaRatioDown", 8, asymbins);
TH1D *DY_DYcr_eejj_2017_SFUp = new TH1D ("DY_DYcr_eejj_2017_SFUp", "DY_DYcr_eejj_2017_SFUp", 8, asymbins);
TH1D *DY_DYcr_eejj_2017_SFDown = new TH1D ("DY_DYcr_eejj_2017_SFDown", "DY_DYcr_eejj_2017_SFDown", 8, asymbins);
TH1D *DY_DYcr_eejj_2017_PUUp = new TH1D ("DY_DYcr_eejj_2017_PUUp", "DY_DYcr_eejj_2017_PUUp", 8, asymbins);
TH1D *DY_DYcr_eejj_2017_PUDown = new TH1D ("DY_DYcr_eejj_2017_PUDown", "DY_DYcr_eejj_2017_PUDown", 8, asymbins);
TH1D *DY_DYcr_eejj_centralJesJer = new TH1D ("DY_DYcr_eejj_centralJesJer", "DY_DYcr_eejj_centralJesJer", 8, asymbins);
TH1D *DY_DYcr_eejj_2017_JesSFUp = new TH1D ("DY_DYcr_eejj_2017_JesSFUp", "DY_DYcr_eejj_2017_JesSFUp", 8, asymbins);
TH1D *DY_DYcr_eejj_2017_JesSFDown = new TH1D ("DY_DYcr_eejj_2017_JesSFDown", "DY_DYcr_eejj_2017_JesSFDown", 8, asymbins);
TH1D *DY_DYcr_eejj_2017_JerSFUp = new TH1D ("DY_DYcr_eejj_2017_JerSFUp", "DY_DYcr_eejj_2017_JerSFUp", 8, asymbins);
TH1D *DY_DYcr_eejj_2017_JerSFDown = new TH1D ("DY_DYcr_eejj_2017_JerSFDown", "DY_DYcr_eejj_2017_JerSFDown", 8, asymbins);
TH1D *DY_DYcr_eejj_energyScaleUp = new TH1D ("DY_DYcr_eejj_energyScaleUp", "DY_DYcr_eejj_energyScaleUp", 8, asymbins);
TH1D *DY_DYcr_eejj_energyScaleDown = new TH1D ("DY_DYcr_eejj_energyScaleDown", "DY_DYcr_eejj_energyScaleDown", 8, asymbins);
TH1D *DY_DYcr_eejj_2017_energySigmaUp = new TH1D ("DY_DYcr_eejj_2017_energySigmaUp", "DY_DYcr_eejj_2017_energySigmaUp", 8, asymbins);
TH1D *DY_DYcr_eejj_2017_energySigmaDown = new TH1D ("DY_DYcr_eejj_2017_energySigmaDown", "DY_DYcr_eejj_2017_energySigmaDown", 8, asymbins);
TH1D *DY_DYcr_eejj_2017_PrefUp = new TH1D ("DY_DYcr_eejj_2017_PrefUp", "DY_DYcr_eejj_2017_PrefUp", 8, asymbins);
TH1D *DY_DYcr_eejj_2017_PrefDown = new TH1D ("DY_DYcr_eejj_2017_PrefDown", "DY_DYcr_eejj_2017_PrefDown", 8, asymbins);
TH1D *DY_DYcr_eejj_2017_KqcdUp = new TH1D ("DY_DYcr_eejj_2017_KqcdUp", "DY_DYcr_eejj_2017_KqcdUp", 8, asymbins);
TH1D *DY_DYcr_eejj_2017_KqcdDown = new TH1D ("DY_DYcr_eejj_2017_KqcdDown", "DY_DYcr_eejj_2017_KqcdDown", 8, asymbins);

//TTcr
const double asymbins2[7] = {300,350,400,450,500,700,2000};

TH1D *DY_TTtWcr_ll = new TH1D ("DY_TTtWcr_ll", "DY_TTtWcr_ll", 6, asymbins2);
TH1D *DY_TTtWcr_ll_BB = new TH1D ("DY_TTtWcr_ll_BB", "DY_TTtWcr_ll_BB", 6, asymbins2);
TH1D *DY_TTtWcr_ll_BE = new TH1D ("DY_TTtWcr_ll_BE", "DY_TTtWcr_ll_BE", 6, asymbins2);
TH1D *DY_TTtWcr_ll_EE = new TH1D ("DY_TTtWcr_ll_EE", "DY_TTtWcr_ll_EE", 6, asymbins2);

/*M(emuJ)*/
TH1D *DY_TTtWcr_HTevent = new TH1D ("DY_TTtWcr_HTevent", "DY_TTtWcr_HTevent", 100, 0, 5000);
TH1D *DY_TTtWcr_llJ = new TH1D ("DY_TTtWcr_llJ", "DY_TTtWcr_llJ", 8, asymbins);
TH1D *DY_TTtWcr_llJ_BB = new TH1D ("DY_TTtWcr_llJ_BB", "DY_TTtWcr_llJ_BB", 8, asymbins);
TH1D *DY_TTtWcr_llJ_BE = new TH1D ("DY_TTtWcr_llJ_BE", "DY_TTtWcr_llJ_BE", 8, asymbins);
TH1D *DY_TTtWcr_llJ_EE = new TH1D ("DY_TTtWcr_llJ_EE", "DY_TTtWcr_llJ_EE", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_AlphaRatio = new TH1D ("DY_TTtWcr_llJ_2017_AlphaRatio", "DY_TTtWcr_llJ_2017_AlphaRatio", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_AlphaRatioUp = new TH1D ("DY_TTtWcr_llJ_2017_AlphaRatioUp", "DY_TTtWcr_llJ_2017_AlphaRatioUp", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_AlphaRatioDown = new TH1D ("DY_TTtWcr_llJ_2017_AlphaRatioDown", "DY_TTtWcr_llJ_2017_AlphaRatioDown", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_SFUp = new TH1D ("DY_TTtWcr_llJ_2017_SFUp", "DY_TTtWcr_llJ_2017_SFUp", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_SFDown = new TH1D ("DY_TTtWcr_llJ_2017_SFDown", "DY_TTtWcr_llJ_2017_SFDown", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_PUUp = new TH1D ("DY_TTtWcr_llJ_2017_PUUp", "DY_TTtWcr_llJ_2017_PUUp", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_PUDown = new TH1D ("DY_TTtWcr_llJ_2017_PUDown", "DY_TTtWcr_llJ_2017_PUDown", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_PtResoUp = new TH1D ("DY_TTtWcr_llJ_2017_PtResoUp", "DY_TTtWcr_llJ_2017_PtResoUp", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_PtResoDown = new TH1D ("DY_TTtWcr_llJ_2017_PtResoDown", "DY_TTtWcr_llJ_2017_PtResoDown", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_PtReso2Up = new TH1D ("DY_TTtWcr_llJ_2017_PtReso2Up", "DY_TTtWcr_llJ_2017_PtReso2Up", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_PtReso2Down = new TH1D ("DY_TTtWcr_llJ_2017_PtReso2Down", "DY_TTtWcr_llJ_2017_PtReso2Down", 8, asymbins);
TH1D *DY_TTtWcr_llJ_energyScaleUp = new TH1D ("DY_TTtWcr_llJ_energyScaleUp", "DY_TTtWcr_llJ_energyScaleUp", 8, asymbins);
TH1D *DY_TTtWcr_llJ_energyScaleDown = new TH1D ("DY_TTtWcr_llJ_energyScaleDown", "DY_TTtWcr_llJ_energyScaleDown", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_energySigmaUp = new TH1D ("DY_TTtWcr_llJ_2017_energySigmaUp", "DY_TTtWcr_llJ_2017_energySigmaUp", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_energySigmaDown = new TH1D ("DY_TTtWcr_llJ_2017_energySigmaDown", "DY_TTtWcr_llJ_2017_energySigmaDown", 8, asymbins);
TH1D *DY_TTtWcr_llJ_centralJesJer = new TH1D ("DY_TTtWcr_llJ_centralJesJer", "DY_TTtWcr_llJ_centralJesJer", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_JesSFUp = new TH1D ("DY_TTtWcr_llJ_2017_JesSFUp", "DY_TTtWcr_llJ_2017_JesSFUp", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_JesSFDown = new TH1D ("DY_TTtWcr_llJ_2017_JesSFDown", "DY_TTtWcr_llJ_2017_JesSFDown", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_JerSFUp = new TH1D ("DY_TTtWcr_llJ_2017_JerSFUp", "DY_TTtWcr_llJ_2017_JerSFUp", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_JerSFDown = new TH1D ("DY_TTtWcr_llJ_2017_JerSFDown", "DY_TTtWcr_llJ_2017_JerSFDown", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_PrefUp = new TH1D ("DY_TTtWcr_llJ_2017_PrefUp", "DY_TTtWcr_llJ_2017_PrefUp", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_PrefDown = new TH1D ("DY_TTtWcr_llJ_2017_PrefDown", "DY_TTtWcr_llJ_2017_PrefDown", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_KqcdUp = new TH1D ("DY_TTtWcr_llJ_2017_KqcdUp", "DY_TTtWcr_llJ_2017_KqcdUp", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2017_KqcdDown = new TH1D ("DY_TTtWcr_llJ_2017_KqcdDown", "DY_TTtWcr_llJ_2017_KqcdDown", 8, asymbins);

cout << a_->GetEntries() << endl;
int tot=0, muejj = 0;
double wg = 0, wg_SFu = 0, wg_SFd = 0, wg_2017_PUu = 0, wg_2017_PUd = 0, wg_PrefUp = 0, wg_PrefDown = 0, wg_2017_KqcdUp = 0, wg_2017_KqcdDown = 0;
int lumi = 41529;//2017: 58873 //2017: 41529 //2017: 35542
bool veto_ele = false;
double mee = 0, mmumu = 0, pu_w = 0;

/*gen particles k-factors ewk nlo, qcd nlo*/
double Z_gen_pt=0;
double Gen_stat=0;
double binCenter_ewk=0;
double binCenter_qcd=0;
double k_ewk=0, k_qcd=0, k_qcd_up = 0, k_qcd_down=0;

/*this is for the patch on lepf sf systematics*/
double elesf1=0, elesf_d1=0, elesf_d2=0; 
double elesf2=0, elesf_u1=0, elesf_u2=0; 

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

double energy_corr0 = 0, energy_corr1 = 0;
double Muon1_px_smearing = 0, Muon1_py_smearing = 0, Muon1_pz_smearing = 0;
double Muon2_px_smearing = 0, Muon2_py_smearing = 0, Muon2_pz_smearing = 0;
double extra_smearing_1 =0, extra_smearing_2 = 0;
double muon_tot_pt = 0, ele_tot_pt = 0, jet_tot_pt = 0, HTevent=0;
const double Alpha_ele_[9] = {1,1,1.07,0.92,0.95,0.93,0.87,1.04};
const double Alpha_mu_[9] = {1,1,1.0,1.04,1.03,1.02,1.07,1.16};

for (Int_t i=0;i<a_->GetEntries();i++) {
 a_->GetEntry(i);
 tot = a_->GetEntries();
 if (i%100000 == 0) cout << i << " eventi analizzati su " << tot << endl;


/************************************************************/
  /*implementation of k-factors from monojet analysis*/
  /*here we read the histograms with the corrections */
  TFile k_qcd_file("monojetDYk/Kfactor_NLO_HTincl_LO_2017.root");  /*this is the histo with qcd weights*/
  //TFile k_qcd_file("monojetDYk/kfac_dy_filter.root");
  TH1F *k_qcd_histo = (TH1F*)k_qcd_file.Get("kfac_dy_filter");
  TFile k_ewk_file("monojetDYk/merged_kfactors_zjets.root");  /*this is the histo with ewk weights*/
  TH1F *k_ewk_histo = (TH1F*)k_ewk_file.Get("kfactor_monojet_ewk");
  /* here we read from all the gen particles the Z boson ones */
  /*if more than on Z boson...quit the for - this is not the most clean procedure, but how many Z are we expecting in each DY Region?!*/
  for (int l = 0; l<Gen_pt->size(); l++){
   if (fabs(Gen_pdg_id->at(l)) == 23  && Gen_status->at(l) ==62 ){
    Z_gen_pt = Gen_pt->at(l);
    Gen_stat = Gen_status->at(l);
   }
  }
  /* here we write the k_qcd */
  k_qcd=1;
  int Nbins_qcd = k_qcd_histo ->GetNbinsX(); double binWidth_qcd=0;
/*  for (int ji=1; ji<= Nbins_qcd; ji++){
    binCenter_qcd= k_qcd_histo->GetXaxis()->GetBinCenter(ji);
    binWidth_qcd= k_qcd_histo->GetXaxis()->GetBinWidth(ji);

    if(k_qcd_histo->GetBinContent(ji) ==0){continue;}

    if( Z_gen_pt>150 && Z_gen_pt >=(binCenter_qcd - (0.5*binWidth_qcd)) && Z_gen_pt < (binCenter_qcd + (0.5*binWidth_qcd))  ){
      k_qcd = k_qcd_histo->GetBinContent(ji);
      k_qcd_up = k_qcd + 0.05*k_qcd;
      k_qcd_down = k_qcd - 0.05*k_qcd;
    }
  }*/
  /* here we write the k_ewk */
  k_ewk =1;
  int Nbins_ewk = k_ewk_histo ->GetNbinsX(); double binWidth_ewk=0;
/*  for (int jj=1; jj<= Nbins_ewk; jj++){
    binCenter_ewk= k_ewk_histo->GetXaxis()->GetBinCenter(jj);
    binWidth_ewk= k_ewk_histo->GetXaxis()->GetBinWidth(jj);

    if(Z_gen_pt >=(binCenter_ewk - (0.5*binWidth_ewk)) && Z_gen_pt < (binCenter_ewk + (0.5*binWidth_ewk)) ){
      k_ewk = k_ewk_histo->GetBinContent(jj);
    }
  }*/

  /*end implementation of k-factor. The k-factors are then put in the weights for each event:   wg = lumi*lumi_wgt*lepsf_evt*k_ewk*k_qcd;*/
  /************************************************************/
 

 wg = lumi * lumi_wgt * lepsf_evt * PUWeight *k_ewk*k_qcd*EVENT_prefireWeight;
 if (wg > 10000 ) {
   cout << "WARNING "<<endl;  
   cout<< "wg = "<< wg <<"// lumi_wgt = "<<lumi_wgt<<"// lepsf_evt = "<<lepsf_evt<<"// PUWeight ="<<PUWeight<<"// k_ewk*k_qcd = "<<k_ewk*k_qcd <<endl;
   continue;
   }

 wg_SFu = lumi * lumi_wgt * lepsf_evt_u * PUWeight*k_ewk*k_qcd* EVENT_prefireWeight;
 wg_SFd = lumi * lumi_wgt * lepsf_evt_d * PUWeight*k_ewk*k_qcd* EVENT_prefireWeight;
 wg_2017_PUu = lumi * lumi_wgt * lepsf_evt * MinBiasUpWeight*k_ewk*k_qcd* EVENT_prefireWeight;
 wg_2017_PUd = lumi * lumi_wgt * lepsf_evt * MinBiasDownWeight*k_ewk*k_qcd* EVENT_prefireWeight;
 wg_PrefUp = lumi * lumi_wgt * lepsf_evt * PUWeight*k_ewk*k_qcd*EVENT_prefireWeightUp;
 wg_PrefDown = lumi * lumi_wgt * lepsf_evt * PUWeight*k_ewk*k_qcd*EVENT_prefireWeightDown;
 wg_2017_KqcdUp = lumi * lumi_wgt * lepsf_evt * PUWeight * k_ewk*k_qcd_up * EVENT_prefireWeight;
 wg_2017_KqcdDown = lumi * lumi_wgt * lepsf_evt * PUWeight * k_ewk*k_qcd_down * EVENT_prefireWeight;

 HLT_Mu = 0; HLT_Ele = 0;          
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
 HTevent= jet_tot_pt;
 bool ptmumu_bin = false, ptee_bin = false;

  if (Muon_pt_tunePbt_Roc->size() > 1 && numOfHighptMu==2 && numOfVetoEle == 0 && numOfBoostedJets>=1){

   BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
  BoostJet_JESup.SetPtEtaPhiE(BoostedJet_pt->at(1), BoostedJet_eta->at(1), BoostedJet_phi->at(1),BoostedJet_energy->at(1));
  BoostJet_JESdown.SetPtEtaPhiE(BoostedJet_pt->at(2), BoostedJet_eta->at(2), BoostedJet_phi->at(2),BoostedJet_energy->at(2));
  BoostJet_JERup.SetPtEtaPhiE(BoostedJet_pt->at(3), BoostedJet_eta->at(3), BoostedJet_phi->at(3),BoostedJet_energy->at(3));
  BoostJet_JERdown.SetPtEtaPhiE(BoostedJet_pt->at(4), BoostedJet_eta->at(4), BoostedJet_phi->at(4),BoostedJet_energy->at(4));

   Muon1.SetPtEtaPhiM(Muon_pt_tunePbt_Roc->at(0), Muon_eta->at(0), Muon_phi->at(0),0.1056583745 );
   Muon2.SetPtEtaPhiM(Muon_pt_tunePbt_Roc->at(1), Muon_eta->at(1), Muon_phi->at(1),0.1056583745 );

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

  ptmumu_bin = false;
   if ((Muon1+Muon2).Pt() > 250 && (Muon1+Muon2).Pt() < 300 ) ptmumu_bin = true;

    //if (ptmumu_bin == true){

   if (HLT_Mu == 1 && Muon1_PtResoUp.Pt() > 150 && Muon2_PtResoUp.Pt() > 100 && fabs(Muon1_PtResoUp.Eta())<2.4 && fabs(Muon2_PtResoUp.Eta())<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1_PtResoUp+Muon2_PtResoUp).M() > 300){ 
    DY_mumujj_2017_PtReso2Up->Fill((Muon1_PtResoUp+Muon2_PtResoUp+BoostJet).M(), wg);
   }

   if (HLT_Mu == 1 && Muon1.Pt() > 150 && Muon2.Pt() > 100 && fabs(Muon1.Eta())<2.4 && fabs(Muon2.Eta())<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1+Muon2).M() > 300){


   DY_mumujj_Roc->Fill((Muon1_Roc+Muon2_Roc+BoostJet).M(), wg);
   DY_mumujj->Fill((Muon1+Muon2+BoostJet).M(), wg);
   DY_Mmumu->Fill((Muon1+Muon2).M(),wg );
   DY_HTmumu->Fill(HTevent,wg);
   if (Muon_charge->at(0)*Muon_charge->at(1) == 1) DY_mumujj_SS->Fill((Muon1+Muon2+BoostJet).M(), wg);
   if (Muon_charge->at(0)*Muon_charge->at(1) == -1) DY_mumujj_OS->Fill((Muon1+Muon2+BoostJet).M(), wg);

   if (fabs(Muon1.Eta())< 0.8 && fabs(Muon2.Eta())<0.8){
    DY_Mmumu_BB->Fill((Muon1+Muon2).M(),wg );
    DY_HTmumu_BB->Fill(HTevent,wg);
    DY_mumujj_BB->Fill((Muon1+Muon2+BoostJet).M(), wg);
    DY_mumujj_2017_AlphaRatio_BB->Fill((Muon1+Muon2+BoostJet).M(), wg);
   }
   if ((fabs(Muon1.Eta())< 0.8 && fabs(Muon2.Eta())>0.8) || (fabs(Muon1.Eta())> 0.8 && fabs(Muon2.Eta())<0.8)){
    DY_Mmumu_BE->Fill((Muon1+Muon2).M(),wg );
    DY_HTmumu_BE->Fill(HTevent,wg);
    DY_mumujj_BE->Fill((Muon1+Muon2+BoostJet).M(), wg);
    DY_mumujj_2017_AlphaRatio_BE->Fill((Muon1+Muon2+BoostJet).M(), wg);
   }
   if (fabs(Muon1.Eta())> 0.8 && fabs(Muon2.Eta())>0.8){
    DY_Mmumu_EE->Fill((Muon1+Muon2).M(),wg );
    DY_HTmumu_EE->Fill(HTevent,wg);
    DY_mumujj_EE->Fill((Muon1+Muon2+BoostJet).M(), wg);
    DY_mumujj_2017_AlphaRatio_EE->Fill((Muon1+Muon2+BoostJet).M(), wg);
   }
   DY_mumujj_2017_AlphaRatio->Fill((Muon1+Muon2+BoostJet).M(), wg);
   DY_mumujj_2017_AlphaRatioUp->Fill((Muon1+Muon2+BoostJet).M(), wg);
   DY_mumujj_2017_AlphaRatioDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
   DY_mumujj_2017_SFUp->Fill((Muon1+Muon2+BoostJet).M(), wg_SFu);
   DY_mumujj_2017_SFDown->Fill((Muon1+Muon2+BoostJet).M(), wg_SFd);
   DY_mumujj_2017_PUUp->Fill((Muon1+Muon2+BoostJet).M(), wg_2017_PUu);
   DY_mumujj_2017_PUDown->Fill((Muon1+Muon2+BoostJet).M(), wg_2017_PUd);
   if ((Muon1_PtResoUp+Muon2_PtResoUp).M() >300)DY_mumujj_2017_PtResoUp->Fill((Muon1_PtResoUp+Muon2_PtResoUp+BoostJet).M(), wg);
   DY_mumujj_2017_PtResoDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
   DY_mumujj_2017_PtReso2Down->Fill((Muon1+Muon2+BoostJet).M(), wg);
   DY_mumujj_2017_PrefUp->Fill((Muon1+Muon2+BoostJet).M(), wg_PrefUp);
   DY_mumujj_2017_PrefDown->Fill((Muon1+Muon2+BoostJet).M(), wg_PrefDown);
   DY_mumujj_2017_KqcdUp->Fill((Muon1+Muon2+BoostJet).M(),wg_2017_KqcdUp);
   DY_mumujj_2017_KqcdDown->Fill((Muon1+Muon2+BoostJet).M(),wg_2017_KqcdDown);
   if(centralJesJer->at(0)==1)DY_mumujj_2017_centralJesJer->Fill((Muon1+Muon2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)DY_mumujj_2017_JesSFUp->Fill((Muon1+Muon2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)DY_mumujj_2017_JesSFDown->Fill((Muon1+Muon2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)DY_mumujj_2017_JerSFUp->Fill((Muon1+Muon2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)DY_mumujj_2017_JerSFDown->Fill((Muon1+Muon2+BoostJet_JERdown).M(), wg);

    for (int m=1; m<=8; m++){
    if ((Muon1+Muon2+BoostJet).M() > asymbins[m-1] && (Muon1+Muon2+BoostJet).M() < asymbins[m]){
     DY_Mmumu->SetBinContent(m, DY_Mmumu->GetBinContent(m)*Alpha_mu_[m-1]);
     DY_Mmumu_BB->SetBinContent(m, DY_Mmumu_BB->GetBinContent(m)*Alpha_mu_[m-1]);
     DY_Mmumu_BE->SetBinContent(m, DY_Mmumu_BE->GetBinContent(m)*Alpha_mu_[m-1]);
     DY_Mmumu_EE->SetBinContent(m, DY_Mmumu_EE->GetBinContent(m)*Alpha_mu_[m-1]);
     DY_HTmumu->SetBinContent(m, DY_HTmumu->GetBinContent(m)*Alpha_mu_[m-1]);
     DY_HTmumu_BB->SetBinContent(m, DY_HTmumu_BB->GetBinContent(m)*Alpha_mu_[m-1]);
     DY_HTmumu_BE->SetBinContent(m, DY_HTmumu_BE->GetBinContent(m)*Alpha_mu_[m-1]);
     DY_HTmumu_EE->SetBinContent(m, DY_HTmumu_EE->GetBinContent(m)*Alpha_mu_[m-1]);
    }
   }

  }

//Zpeak DY cr Mll in 60-120 GeV
 if (HLT_Mu == 1 && Muon1.Pt() > 150 && Muon2.Pt() > 100 && fabs(Muon1.Eta())<2.4 && fabs(Muon2.Eta())<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1+Muon2).M() > 60 && (Muon1+Muon2).M() < 120){

  if(nBestVtx > 5)n_best_Vtx->Fill(nBestVtx, wg);
  DY_ZpeakMll_mumujj->Fill((Muon1+Muon2).M(), wg); 
  DY_Zpeak_mumujj->Fill((Muon1+Muon2+BoostJet).M(), wg); 
  DY_Zpeak_mumu_pt_2017->Fill((Muon1+Muon2).Pt(), wg);
  DY_Zpeak_mumu_pt_2017_SFUp->Fill((Muon1+Muon2).Pt(), wg_SFu);
  DY_Zpeak_mumu_pt_2017_SFDown->Fill((Muon1+Muon2).Pt(), wg_SFd);
  DY_Zpeak_mumu_pt_2017_PUUp->Fill((Muon1+Muon2).Pt(), wg_2017_PUu);
  DY_Zpeak_mumu_pt_2017_PUDown->Fill((Muon1+Muon2).Pt(), wg_2017_PUd);
  DY_Zpeak_mumu_pt_2017_PtResoUp->Fill((Muon1_PtResoUp+Muon2_PtResoUp).Pt(), wg);
  DY_Zpeak_mumu_pt_2017_PtResoDown->Fill((Muon1+Muon2).Pt(), wg);
  DY_Zpeak_mumu_pt_2017_PtReso2Down->Fill((Muon1+Muon2).Pt(), wg);
  if(centralJesJer->at(0)==1)DY_Zpeak_mumu_pt_2017_centralJesJer->Fill((Muon1+Muon2).Pt(), wg);
  if(JesSFup->at(1)==1)DY_Zpeak_mumu_pt_2017_JesSFUp->Fill((Muon1+Muon2).Pt(), wg);
  if(JesSFdown->at(2)==1)DY_Zpeak_mumu_pt_2017_JesSFDown->Fill((Muon1+Muon2).Pt(), wg);
  if(JerSFup->at(3)==1)DY_Zpeak_mumu_pt_2017_JerSFUp->Fill((Muon1+Muon2).Pt(), wg);
  if(JerSFdown->at(4)==1)DY_Zpeak_mumu_pt_2017_JerSFDown->Fill((Muon1+Muon2).Pt(), wg);

  if (Muon_charge->at(0)*Muon_charge->at(1) == 1) DY_Zpeak_mumujj_SS->Fill((Muon1+Muon2+BoostJet).M(), wg);
   if (Muon_charge->at(0)*Muon_charge->at(1) == -1) DY_Zpeak_mumujj_OS->Fill((Muon1+Muon2+BoostJet).M(), wg);

  if (fabs(Muon1.Eta())< 0.8 && fabs(Muon2.Eta())<0.8){
    DY_ZpeakMll_mumujj_BB->Fill((Muon1+Muon2).M(), wg);
    DY_Zpeak_mumujj_BB->Fill((Muon1+Muon2+BoostJet).M(), wg);
    DY_Zpeak_mumu_pt_2017_BB->Fill((Muon1+Muon2).Pt(), wg);
   }
   if((fabs(Muon1.Eta())< 0.8 && fabs(Muon2.Eta())>0.8) || (fabs(Muon1.Eta())> 0.8 && fabs(Muon2.Eta())<0.8)){
    DY_ZpeakMll_mumujj_BE->Fill((Muon1+Muon2).M(), wg);
    DY_Zpeak_mumujj_BE->Fill((Muon1+Muon2+BoostJet).M(), wg);
    DY_Zpeak_mumu_pt_2017_BE->Fill((Muon1+Muon2).Pt(), wg);
   }
   if(fabs(Muon1.Eta())> 0.8 && fabs(Muon2.Eta())>0.8){
    DY_ZpeakMll_mumujj_EE->Fill((Muon1+Muon2).M(), wg);
    DY_Zpeak_mumujj_EE->Fill((Muon1+Muon2+BoostJet).M(), wg);
    DY_Zpeak_mumu_pt_2017_EE->Fill((Muon1+Muon2).Pt(), wg);
   }
  }

    //DY cr Mll in 150-300 GeV
  if (HLT_Mu == 1 && Muon1_PtResoUp.Pt() > 150 && Muon2_PtResoUp.Pt() > 100 && fabs(Muon1_PtResoUp.Eta())<2.4 && fabs(Muon2_PtResoUp.Eta())<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1_PtResoUp+Muon2_PtResoUp).M() > 150 && (Muon1_PtResoUp+Muon2_PtResoUp).M() < 300){
   DY_DYcr_mumujj_2017_PtReso2Up->Fill((Muon1_PtResoUp+Muon2_PtResoUp+BoostJet).M(), wg);
  }

  if (HLT_Mu == 1 && Muon1.Pt() > 150 && Muon2.Pt() > 100 && fabs(Muon1.Eta())<2.4 && fabs(Muon2.Eta())<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1+Muon2).M() > 150 && (Muon1+Muon2).M() < 300){


  Mmumu_DYcr->Fill((Muon1+Muon2).M(), wg);
  if (Muon_charge->at(0)*Muon_charge->at(1) == 1) DY_DYcr_mumujj_SS->Fill((Muon1+Muon2+BoostJet).M(), wg);
   if (Muon_charge->at(0)*Muon_charge->at(1) == -1) DY_DYcr_mumujj_OS->Fill((Muon1+Muon2+BoostJet).M(), wg);

  if (fabs(Muon1.Eta())< 0.8 && fabs(Muon2.Eta())<0.8){
    Mmumu_DYcr_BB->Fill((Muon1+Muon2).M(), wg);
    DY_DYcr_mumujj_BB->Fill((Muon1+Muon2+BoostJet).M(), wg);
    DY_DYcr_mumujj_2017_AlphaRatio_BB->Fill((Muon1+Muon2+BoostJet).M(), wg);
   }
   if((fabs(Muon1.Eta())< 0.8 && fabs(Muon2.Eta())>0.8) || (fabs(Muon1.Eta())> 0.8 && fabs(Muon2.Eta())<0.8)){
    Mmumu_DYcr_BE->Fill((Muon1+Muon2).M(), wg);
    DY_DYcr_mumujj_BE->Fill((Muon1+Muon2+BoostJet).M(), wg);
    DY_DYcr_mumujj_2017_AlphaRatio_BE->Fill((Muon1+Muon2+BoostJet).M(), wg);
   }
   if(fabs(Muon1.Eta())> 0.8 && fabs(Muon2.Eta())>0.8){
    Mmumu_DYcr_EE->Fill((Muon1+Muon2).M(), wg);
    DY_DYcr_mumujj_EE->Fill((Muon1+Muon2+BoostJet).M(), wg);
    DY_DYcr_mumujj_2017_AlphaRatio_EE->Fill((Muon1+Muon2+BoostJet).M(), wg);
   }
  DY_DYcr_mumujj->Fill((Muon1+Muon2+BoostJet).M(), wg); 
  DY_DYcr_mumujj_2017_AlphaRatio->Fill((Muon1+Muon2+BoostJet).M(), wg);
  DY_DYcr_mumujj_2017_AlphaRatioUp->Fill((Muon1+Muon2+BoostJet).M(), wg);
  DY_DYcr_mumujj_2017_AlphaRatioDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
  DY_DYcr_mumujj_2017_SFUp->Fill((Muon1+Muon2+BoostJet).M(), wg_SFu);
  DY_DYcr_mumujj_2017_SFDown->Fill((Muon1+Muon2+BoostJet).M(), wg_SFd);
  DY_DYcr_mumujj_2017_PUUp->Fill((Muon1+Muon2+BoostJet).M(), wg_2017_PUu);
  DY_DYcr_mumujj_2017_PUDown->Fill((Muon1+Muon2+BoostJet).M(), wg_2017_PUd);
  DY_DYcr_mumujj_2017_PtResoUp->Fill((Muon1_PtResoUp+Muon2_PtResoUp+BoostJet).M(), wg);
  DY_DYcr_mumujj_2017_PtResoDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
  DY_DYcr_mumujj_2017_PtReso2Down->Fill((Muon1+Muon2+BoostJet).M(), wg);
  DY_DYcr_mumujj_2017_PrefUp->Fill((Muon1+Muon2+BoostJet).M(), wg_PrefUp);
  DY_DYcr_mumujj_2017_PrefDown->Fill((Muon1+Muon2+BoostJet).M(), wg_PrefDown);
  DY_DYcr_mumujj_2017_KqcdUp->Fill((Muon1+Muon2+BoostJet).M(),wg_2017_KqcdUp);
  DY_DYcr_mumujj_2017_KqcdDown->Fill((Muon1+Muon2+BoostJet).M(),wg_2017_KqcdDown);
  if(centralJesJer->at(0)==1)DY_DYcr_mumujj_centralJesJer->Fill((Muon1+Muon2+BoostJet).M(), wg);
  if(JesSFup->at(1)==1)DY_DYcr_mumujj_2017_JesSFUp->Fill((Muon1+Muon2+BoostJet_JESup).M(), wg);
  if(JesSFdown->at(2)==1)DY_DYcr_mumujj_2017_JesSFDown->Fill((Muon1+Muon2+BoostJet_JESdown).M(), wg);
  if(JerSFup->at(3)==1)DY_DYcr_mumujj_2017_JerSFUp->Fill((Muon1+Muon2+BoostJet_JERup).M(), wg);
  if(JerSFdown->at(4)==1)DY_DYcr_mumujj_2017_JerSFDown->Fill((Muon1+Muon2+BoostJet_JERdown).M(), wg);  


  }
 //}//pt bin
 } // 2 muons

  if (patElectron_pt->size() > 1 && numOfHighptEle==2 && numOfLooseMu==0 && numOfBoostedJets>=1){
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

 // energy correction  

   energy_corr0= patElectron_ecalTrkEnergyPostCorr->at(0) / patElectron_energy->at(0) ;
   energy_corr1= patElectron_ecalTrkEnergyPostCorr->at(1) / patElectron_energy->at(1) ;
   Electron1 = Electron1*energy_corr0;
   Electron2 = Electron2*energy_corr1;

   /*  BUG FIXING FOR SF ELE 2017 */
  if(fabs(patElectron_eta->at(0)) < 1.4442){ 
     elesf1 = 0.989; elesf_d1 = 0.975; elesf_u1 = 1.003;
  }
  if(fabs(patElectron_eta->at(0)) >= 1.566 && fabs(patElectron_eta->at(0)) < 2.5){
   elesf1 = 0.982; elesf_d1 = 0.968; elesf_u1 = 0.996;
  }
  if(fabs(patElectron_eta->at(1)) < 1.4442){ 
     elesf2 = 0.989; elesf_d2 = 0.975; elesf_u2 = 1.003;
  }
  if(fabs(patElectron_eta->at(1)) >= 1.566 && fabs(patElectron_eta->at(1)) < 2.5){
    elesf2 = 0.982; elesf_d2 = 0.968; elesf_u2 = 0.996;
  }
  lepsf_evt=elesf1*elesf2;
  lepsf_evt_u=elesf_u1*elesf_u2;
  lepsf_evt_d=elesf_d1*elesf_d2;
  wg = lumi * lumi_wgt * lepsf_evt * PUWeight*k_qcd*k_ewk;  
  wg_SFu = lumi * lumi_wgt * lepsf_evt_u * PUWeight*k_qcd*k_ewk;  
  wg_SFd = lumi * lumi_wgt * lepsf_evt_d * PUWeight*k_qcd*k_ewk; 
  if( wg >1000) continue;
  /*bug fixing part end*/
  
  ptee_bin = false;
  if ((Electron1+Electron2).Pt() > 250 && (Electron1+Electron2).Pt() < 300 ) ptee_bin= true;

   //if (ptee_bin == true){

  if (HLT_Ele == 1 && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190 && (Electron1+Electron2).M() > 300){

   DY_eejj_ele1_ecalTrkEnergyPostCorr->Fill(patElectron_ecalTrkEnergyPostCorr->at(0),wg);
   DY_eejj_ele2_ecalTrkEnergyPostCorr->Fill(patElectron_ecalTrkEnergyPostCorr->at(1),wg);
   DY_eejj_ele1_energy->Fill(patElectron_energy->at(0),wg);
   DY_eejj_ele2_energy->Fill(patElectron_energy->at(1),wg);
   DY_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_Mee->Fill((Electron1+Electron2).M(),wg );
   DY_HTee->Fill(HTevent,wg);
   if (patElectron_charge->at(0)*patElectron_charge->at(1) == 1) DY_eejj_SS->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if (patElectron_charge->at(0)*patElectron_charge->at(1) == -1) DY_eejj_OS->Fill((Electron1+Electron2+BoostJet).M(), wg);

   if (fabs(patElectron_eta->at(1))< 0.8 && fabs(patElectron_eta->at(0))<0.8){
    DY_Mee_BB->Fill((Electron1+Electron2).M(),wg );
    DY_HTee_BB->Fill(HTevent,wg);
    DY_eejj_BB->Fill((Electron1+Electron2+BoostJet).M(), wg);
    DY_eejj_2017_AlphaRatio_BB->Fill((Electron1+Electron2+BoostJet).M(), wg);
   }
   if((fabs(patElectron_eta->at(1))< 0.8 && fabs(patElectron_eta->at(0))>0.8) ||(fabs(patElectron_eta->at(1))>0.8 && fabs(patElectron_eta->at(0))<0.8) ){
    DY_Mee_BE->Fill((Electron1+Electron2).M(),wg );
    DY_HTee_BE->Fill(HTevent,wg);
    DY_eejj_BE->Fill((Electron1+Electron2+BoostJet).M(), wg);
    DY_eejj_2017_AlphaRatio_BE->Fill((Electron1+Electron2+BoostJet).M(), wg);
   }
   if (fabs(patElectron_eta->at(1))> 0.8 && fabs(patElectron_eta->at(0))>0.8){
    DY_Mee_EE->Fill((Electron1+Electron2).M(),wg );
    DY_HTee_EE->Fill(HTevent,wg);
    DY_eejj_EE->Fill((Electron1+Electron2+BoostJet).M(), wg);
    DY_eejj_2017_AlphaRatio_EE->Fill((Electron1+Electron2+BoostJet).M(), wg);
   }
   DY_eejj_2017_AlphaRatio->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_eejj_2017_AlphaRatioUp->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_eejj_2017_AlphaRatioDown->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_eejj_2017_SFUp->Fill((Electron1+Electron2+BoostJet).M(), wg_SFu);
   DY_eejj_2017_SFDown->Fill((Electron1+Electron2+BoostJet).M(), wg_SFd);
   DY_eejj_2017_PUUp->Fill((Electron1+Electron2+BoostJet).M(), wg_2017_PUu);
   DY_eejj_2017_PUDown->Fill((Electron1+Electron2+BoostJet).M(), wg_2017_PUd);
   DY_eejj_energyScaleUp->Fill((Ele1_ScaleUp+Ele2_ScaleUp+BoostJet).M(), wg);
   DY_eejj_energyScaleDown->Fill((Ele1_ScaleDown+Ele2_ScaleDown+BoostJet).M(), wg);
   DY_eejj_2017_energySigmaUp->Fill((Ele1_SigmaUp+Ele2_SigmaUp+BoostJet).M(), wg);
   DY_eejj_2017_energySigmaDown->Fill((Ele1_SigmaDown+Ele2_SigmaDown+BoostJet).M(), wg);
   DY_eejj_2017_PrefUp->Fill((Electron1+Electron2+BoostJet).M(), wg_PrefUp);
   DY_eejj_2017_PrefDown->Fill((Electron1+Electron2+BoostJet).M(), wg_PrefDown);
   DY_eejj_2017_KqcdUp->Fill((Electron1+Electron2+BoostJet).M(),wg_2017_KqcdUp);
   DY_eejj_2017_KqcdDown->Fill((Electron1+Electron2+BoostJet).M(),wg_2017_KqcdDown);
   if(centralJesJer->at(0)==1)DY_eejj_2017_centralJesJer->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)DY_eejj_2017_JesSFUp->Fill((Electron1+Electron2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)DY_eejj_2017_JesSFDown->Fill((Electron1+Electron2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)DY_eejj_2017_JerSFUp->Fill((Electron1+Electron2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)DY_eejj_2017_JerSFDown->Fill((Electron1+Electron2+BoostJet_JERdown).M(), wg);
  
   for (int m=1; m<=8; m++){
    if ((Electron1+Electron2+BoostJet).M() > asymbins[m-1] && (Electron1+Electron2+BoostJet).M() < asymbins[m]){
     DY_Mee->SetBinContent(m, DY_Mee->GetBinContent(m)*Alpha_ele_[m-1]);
     DY_Mee_BB->SetBinContent(m, DY_Mee_BB->GetBinContent(m)*Alpha_ele_[m-1]);
     DY_Mee_BE->SetBinContent(m, DY_Mee_BE->GetBinContent(m)*Alpha_ele_[m-1]);
     DY_Mee_EE->SetBinContent(m, DY_Mee_EE->GetBinContent(m)*Alpha_ele_[m-1]);
     DY_HTee->SetBinContent(m, DY_HTee->GetBinContent(m)*Alpha_ele_[m-1]);
     DY_HTee_BB->SetBinContent(m, DY_HTee_BB->GetBinContent(m)*Alpha_ele_[m-1]);
     DY_HTee_BE->SetBinContent(m, DY_HTee_BE->GetBinContent(m)*Alpha_ele_[m-1]);
     DY_HTee_EE->SetBinContent(m, DY_HTee_EE->GetBinContent(m)*Alpha_ele_[m-1]);
    }
   }

  }

  //Zpeak DY cr 60-120 GeV
  if (HLT_Ele == 1 && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190 && (Electron1+Electron2).M() >60 && (Electron1+Electron2).M() < 120){
   DY_ZpeakMll_eejj->Fill((Electron1+Electron2).M(), wg);
   DY_Zpeak_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_Zpeak_ee_pt_2017->Fill((Electron1+Electron2).Pt(), wg);
   DY_Zpeak_ee_pt_2017_SFUp->Fill((Electron1+Electron2).Pt(), wg_SFu);
   DY_Zpeak_ee_pt_2017_SFDown->Fill((Electron1+Electron2).Pt(), wg_SFd);
   DY_Zpeak_ee_pt_2017_PUUp->Fill((Electron1+Electron2).Pt(), wg_2017_PUu);
   DY_Zpeak_ee_pt_2017_PUDown->Fill((Electron1+Electron2).Pt(), wg_2017_PUd);
   DY_Zpeak_ee_pt_energyScaleUp->Fill((Ele1_ScaleUp+Ele2_ScaleUp).Pt(), wg);
   DY_Zpeak_ee_pt_energyScaleDown->Fill((Ele1_ScaleDown+Ele2_ScaleDown).Pt(), wg);
   DY_Zpeak_ee_pt_2017_energySigmaUp->Fill((Ele1_SigmaUp+Ele2_SigmaUp).Pt(), wg);
   DY_Zpeak_ee_pt_2017_energySigmaDown->Fill((Ele1_SigmaDown+Ele2_SigmaDown).Pt(), wg);
   DY_Zpeak_ee_pt_2017_centralJesJer->Fill((Electron1+Electron2).Pt(), wg);
   DY_Zpeak_ee_pt_2017_JesSFUp->Fill((Electron1+Electron2).Pt(), wg);
   DY_Zpeak_ee_pt_2017_JesSFDown->Fill((Electron1+Electron2).Pt(), wg);
   DY_Zpeak_ee_pt_2017_JerSFUp->Fill((Electron1+Electron2).Pt(), wg);
   DY_Zpeak_ee_pt_2017_JerSFDown->Fill((Electron1+Electron2).Pt(), wg); 

   if (patElectron_charge->at(0)*patElectron_charge->at(1) == 1) DY_Zpeak_eejj_SS->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if (patElectron_charge->at(0)*patElectron_charge->at(1) == -1) DY_Zpeak_eejj_OS->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if (fabs(patElectron_eta->at(1))< 0.8 && fabs(patElectron_eta->at(0))<0.8){
     DY_ZpeakMll_eejj_BB->Fill((Electron1+Electron2).M(), wg);
     DY_Zpeak_eejj_BB->Fill((Electron1+Electron2+BoostJet).M(), wg);
     DY_Zpeak_ee_pt_2017_BB->Fill((Electron1+Electron2).Pt(), wg);
    }
    if((fabs(patElectron_eta->at(1))< 0.8 && fabs(patElectron_eta->at(0))>0.8) ||(fabs(patElectron_eta->at(1))>0.8 && fabs(patElectron_eta->at(0))<0.8) ){
     DY_ZpeakMll_eejj_BE->Fill((Electron1+Electron2).M(), wg);
     DY_Zpeak_eejj_BE->Fill((Electron1+Electron2+BoostJet).M(), wg);
     DY_Zpeak_ee_pt_2017_BE->Fill((Electron1+Electron2).Pt(), wg);
    }
    if (fabs(patElectron_eta->at(1))> 0.8 && fabs(patElectron_eta->at(0))>0.8){
     DY_ZpeakMll_eejj_EE->Fill((Electron1+Electron2).M(), wg);
     DY_Zpeak_eejj_EE->Fill((Electron1+Electron2+BoostJet).M(), wg);
     DY_Zpeak_ee_pt_2017_EE->Fill((Electron1+Electron2).Pt(), wg);
    }
  }

    //DY cr 150-300 GeV
  if (HLT_Ele == 1 && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190 && (Electron1+Electron2).M() >150 && (Electron1+Electron2).M() < 300){
   
   Mee_DYcr->Fill((Electron1+Electron2).M(), wg);
   if (patElectron_charge->at(0)*patElectron_charge->at(1) == 1) DY_DYcr_eejj_SS->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if (patElectron_charge->at(0)*patElectron_charge->at(1) == -1) DY_DYcr_eejj_OS->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if (fabs(patElectron_eta->at(1))< 0.8 && fabs(patElectron_eta->at(0))<0.8){
    Mee_DYcr_BB->Fill((Electron1+Electron2).M(), wg);
    DY_DYcr_eejj_BB->Fill((Electron1+Electron2+BoostJet).M(), wg);
    DY_DYcr_eejj_2017_AlphaRatio_BB->Fill((Electron1+Electron2+BoostJet).M(), wg);
   }
   if((fabs(patElectron_eta->at(1))< 0.8 && fabs(patElectron_eta->at(0))>0.8) ||(fabs(patElectron_eta->at(1))>0.8 && fabs(patElectron_eta->at(0))<0.8) ){
    Mee_DYcr_BE->Fill((Electron1+Electron2).M(), wg);
    DY_DYcr_eejj_BE->Fill((Electron1+Electron2+BoostJet).M(), wg);
    DY_DYcr_eejj_2017_AlphaRatio_BE->Fill((Electron1+Electron2+BoostJet).M(), wg);
   }
   if (fabs(patElectron_eta->at(1))> 0.8 && fabs(patElectron_eta->at(0))>0.8){
    Mee_DYcr_EE->Fill((Electron1+Electron2).M(), wg);
    DY_DYcr_eejj_EE->Fill((Electron1+Electron2+BoostJet).M(), wg);
    DY_DYcr_eejj_2017_AlphaRatio_EE->Fill((Electron1+Electron2+BoostJet).M(), wg);
   }
   DY_DYcr_eejj_ele1_ecalTrkEnergyPostCorr->Fill(patElectron_ecalTrkEnergyPostCorr->at(0), wg);
   DY_DYcr_eejj_ele2_ecalTrkEnergyPostCorr->Fill(patElectron_ecalTrkEnergyPostCorr->at(1), wg);
   DY_DYcr_eejj_ele1_energy->Fill(patElectron_energy->at(0), wg);
   DY_DYcr_eejj_ele2_energy->Fill(patElectron_energy->at(1), wg);
   DY_DYcr_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_DYcr_eejj_2017_AlphaRatio->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_DYcr_eejj_2017_AlphaRatioUp->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_DYcr_eejj_2017_AlphaRatioDown->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_DYcr_eejj_2017_SFUp->Fill((Electron1+Electron2+BoostJet).M(), wg_SFu);
   DY_DYcr_eejj_2017_SFDown->Fill((Electron1+Electron2+BoostJet).M(), wg_SFd);
   DY_DYcr_eejj_2017_PUUp->Fill((Electron1+Electron2+BoostJet).M(), wg_2017_PUu);
   DY_DYcr_eejj_2017_PUDown->Fill((Electron1+Electron2+BoostJet).M(), wg_2017_PUd);
   DY_DYcr_eejj_energyScaleUp->Fill((Ele1_ScaleUp+Ele2_ScaleUp+BoostJet).M(), wg);
   DY_DYcr_eejj_energyScaleDown->Fill((Ele1_ScaleDown+Ele2_ScaleDown+BoostJet).M(), wg);
   DY_DYcr_eejj_2017_energySigmaUp->Fill((Ele1_SigmaUp+Ele2_SigmaUp+BoostJet).M(), wg);
   DY_DYcr_eejj_2017_energySigmaDown->Fill((Ele1_SigmaDown+Ele2_SigmaDown+BoostJet).M(), wg);
   DY_DYcr_eejj_2017_PrefUp->Fill((Electron1+Electron2+BoostJet).M(), wg_PrefUp);
   DY_DYcr_eejj_2017_PrefDown->Fill((Electron1+Electron2+BoostJet).M(), wg_PrefDown);
   DY_DYcr_eejj_2017_KqcdUp->Fill((Electron1+Electron2+BoostJet).M(),wg_2017_KqcdUp);
   DY_DYcr_eejj_2017_KqcdDown->Fill((Electron1+Electron2+BoostJet).M(),wg_2017_KqcdDown);
   if(centralJesJer->at(0)==1)DY_DYcr_eejj_centralJesJer->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)DY_DYcr_eejj_2017_JesSFUp->Fill((Electron1+Electron2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)DY_DYcr_eejj_2017_JesSFDown->Fill((Electron1+Electron2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)DY_DYcr_eejj_2017_JerSFUp->Fill((Electron1+Electron2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)DY_DYcr_eejj_2017_JerSFDown->Fill((Electron1+Electron2+BoostJet_JERdown).M(), wg); 
 

  }
  //}//pt bin
 }// 2 ele  
 //TTcr
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

  //if smeared
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
     DY_TTtWcr_llJ_2017_PtReso2Up->Fill((Muon_PtResoUp+SubLeadLep+BoostJet).M(), wg);  
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
     DY_TTtWcr_llJ_2017_PtReso2Up->Fill((Muon_PtResoUp+LeadLep+BoostJet).M(),wg);
    }
   }
  } 


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
    DY_TTtWcr_ll->Fill((LeadLep+SubLeadLep).M(),wg);

    /*M(emuJ)*/
    DY_TTtWcr_llJ->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2017_AlphaRatio->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    if (fabs(LeadLep.Eta()) < 0.8 && fabs(SubLeadLep.Eta())<0.8){
     DY_TTtWcr_ll_BB->Fill((LeadLep+SubLeadLep).M(),wg);
     DY_TTtWcr_llJ_BB->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    }
    if( (fabs(LeadLep.Eta()) < 0.8 && fabs(SubLeadLep.Eta())>0.8) || (fabs(LeadLep.Eta())>0.8 &&fabs(SubLeadLep.Eta())<0.8)){
     DY_TTtWcr_ll_BE->Fill((LeadLep+SubLeadLep).M(),wg);
     DY_TTtWcr_llJ_BE->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    }
    if (fabs(LeadLep.Eta()) > 0.8 && fabs(SubLeadLep.Eta()) > 0.8){
     DY_TTtWcr_ll_EE->Fill((LeadLep+SubLeadLep).M(),wg);
     DY_TTtWcr_llJ_EE->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    }
    if (Muon_charge->at(0)*patElectron_charge->at(0) == 1) DY_TTtWcr_llJ_SS->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if (Muon_charge->at(0)*patElectron_charge->at(0) == -1) DY_TTtWcr_llJ_OS->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
   
    DY_TTtWcr_llJ_2017_AlphaRatioUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2017_AlphaRatioDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2017_SFUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_SFu);
    DY_TTtWcr_llJ_2017_SFDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_SFd);
    DY_TTtWcr_llJ_2017_PUUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_2017_PUu);
    DY_TTtWcr_llJ_2017_PUDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_2017_PUd);
    if ((Muon_PtResoUp+SubLeadLep).M() >300) DY_TTtWcr_llJ_2017_PtResoUp->Fill((Muon_PtResoUp+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_HTevent->Fill(HTevent, wg);
    DY_TTtWcr_llJ_2017_PtResoDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2017_PtReso2Down->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_energyScaleUp->Fill((Ele_ScaleUp+LeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_energyScaleDown->Fill((Ele_ScaleDown+LeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2017_energySigmaUp->Fill((Ele_SigmaUp+LeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2017_energySigmaDown->Fill((Ele_SigmaDown+LeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2017_PrefUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_PrefUp);
    DY_TTtWcr_llJ_2017_PrefDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_PrefDown);
    DY_TTtWcr_llJ_2017_KqcdUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_2017_KqcdUp);
    DY_TTtWcr_llJ_2017_KqcdDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_2017_KqcdDown);
    if(centralJesJer->at(0)==1)DY_TTtWcr_llJ_centralJesJer->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if(JesSFup->at(1)==1)DY_TTtWcr_llJ_2017_JesSFUp->Fill((LeadLep+SubLeadLep+BoostJet_JESup).M(), wg);
    if(JesSFdown->at(2)==1)DY_TTtWcr_llJ_2017_JesSFDown->Fill((LeadLep+SubLeadLep+BoostJet_JESdown).M(), wg);
    if(JerSFup->at(3)==1)DY_TTtWcr_llJ_2017_JerSFUp->Fill((LeadLep+SubLeadLep+BoostJet_JERup).M(), wg);
    if(JerSFdown->at(4)==1)DY_TTtWcr_llJ_2017_JerSFDown->Fill((LeadLep+SubLeadLep+BoostJet_JERdown).M(), wg); 

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
   DY_TTtWcr_ll->Fill((LeadLep+SubLeadLep).M(),wg);

     /* M(e mu J)*/
    DY_TTtWcr_llJ->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    if (fabs(LeadLep.Eta()) < 0.8 && fabs(SubLeadLep.Eta())<0.8){
     DY_TTtWcr_ll_BB->Fill((LeadLep+SubLeadLep).M(),wg);
     DY_TTtWcr_llJ_BB->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    }
    if( (fabs(LeadLep.Eta()) < 0.8 && fabs(SubLeadLep.Eta())>0.8) || (fabs(LeadLep.Eta())>0.8 &&fabs(SubLeadLep.Eta())<0.8)){
     DY_TTtWcr_ll_BE->Fill((LeadLep+SubLeadLep).M(),wg);
     DY_TTtWcr_llJ_BE->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    }
    if (fabs(LeadLep.Eta()) > 0.8 && fabs(SubLeadLep.Eta()) > 0.8){
     DY_TTtWcr_ll_EE->Fill((LeadLep+SubLeadLep).M(),wg);
     DY_TTtWcr_llJ_EE->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    }
    if (Muon_charge->at(0)*patElectron_charge->at(0) == 1) DY_TTtWcr_llJ_SS->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if (Muon_charge->at(0)*patElectron_charge->at(0) == -1) DY_TTtWcr_llJ_OS->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);

    DY_TTtWcr_llJ_2017_AlphaRatio->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2017_AlphaRatioUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2017_AlphaRatioDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2017_SFUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_SFu);
    DY_TTtWcr_llJ_2017_SFDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_SFd);
    DY_TTtWcr_llJ_2017_PUUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_2017_PUu);
    DY_TTtWcr_llJ_2017_PUDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_2017_PUd);
    if ((Muon_PtResoUp+LeadLep).M() >300) DY_TTtWcr_llJ_2017_PtResoUp->Fill((Muon_PtResoUp+LeadLep+BoostJet).M(),wg);
    DY_TTtWcr_HTevent->Fill(HTevent, wg);
    DY_TTtWcr_llJ_2017_PtResoDown->Fill((SubLeadLep+LeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2017_PtReso2Down->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_energyScaleUp->Fill((Ele_ScaleUp+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_energyScaleDown->Fill((Ele_ScaleDown+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2017_energySigmaUp->Fill((Ele_SigmaUp+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2017_energySigmaDown->Fill((Ele_SigmaDown+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2017_PrefUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_PrefUp);
    DY_TTtWcr_llJ_2017_PrefDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_PrefDown);
    DY_TTtWcr_llJ_2017_KqcdUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_2017_KqcdUp);
    DY_TTtWcr_llJ_2017_KqcdDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_2017_KqcdDown);
    if(centralJesJer->at(0)==1)DY_TTtWcr_llJ_centralJesJer->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if(JesSFup->at(1)==1)DY_TTtWcr_llJ_2017_JesSFUp->Fill((LeadLep+SubLeadLep+BoostJet_JESup).M(), wg);
    if(JesSFdown->at(2)==1)DY_TTtWcr_llJ_2017_JesSFDown->Fill((LeadLep+SubLeadLep+BoostJet_JESdown).M(), wg);
    if(JerSFup->at(3)==1)DY_TTtWcr_llJ_2017_JerSFUp->Fill((LeadLep+SubLeadLep+BoostJet_JERup).M(), wg);
    if(JerSFdown->at(4)==1)DY_TTtWcr_llJ_2017_JerSFDown->Fill((LeadLep+SubLeadLep+BoostJet_JERdown).M(), wg);
    }
   }
  }



 } //TTtW CR 
  
}

/**** adding the Alpha ratio and it's uncertainty*******/
/* t double Alpha_elelpha ratio and it's statistical error, bin per bin*/
const double Alpha_ele[9] = {1,1,1.07,0.92,0.95,0.93,0.87,1.04};
const double dAlpha_ele[9] ={0,0,0.05,0.02,0.02,0.03,0.05,0.14};

const double Alpha_mu[9] = {1,1,1.0,1.04,1.03,1.02,1.07,1.16}; 
const double dAlpha_mu[9] ={0,0,0.04,0.02,0.02,0.02,0.05,0.12}; 

for (Int_t j=1;j<=8;j++) {
//    cout<< DY_eejj_2017_SFUp->GetBinContent(j) <<endl;
//    cout<< DY_eejj_2017_AlphaRatio->GetBinContent(j) <<endl;
 //   cout<< DY_eejj_2017_SFDown->GetBinContent(j) <<endl;
//    cout<<"================"<<endl; 
//    cout<<"================"<<endl; 

    double alpha_ele=Alpha_ele[j-1];
    double dalpha_ele=dAlpha_ele[j-1];
    DY_eejj_SS->SetBinContent(j, DY_eejj_SS->GetBinContent(j) * alpha_ele);
    DY_eejj_OS->SetBinContent(j, DY_eejj_OS->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_AlphaRatio->SetBinContent(j, DY_eejj_2017_AlphaRatio->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_AlphaRatio_BB->SetBinContent(j, DY_eejj_2017_AlphaRatio_BB->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_AlphaRatio_BE->SetBinContent(j, DY_eejj_2017_AlphaRatio_BE->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_AlphaRatio_EE->SetBinContent(j, DY_eejj_2017_AlphaRatio_EE->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_AlphaRatioUp->SetBinContent(j, DY_eejj_2017_AlphaRatioUp->GetBinContent(j) * (alpha_ele+dalpha_ele));
    DY_eejj_2017_AlphaRatioDown->SetBinContent(j, DY_eejj_2017_AlphaRatioDown->GetBinContent(j) * (alpha_ele-dalpha_ele));
    DY_eejj_2017_SFUp->SetBinContent(j, DY_eejj_2017_SFUp->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_SFDown->SetBinContent(j, DY_eejj_2017_SFDown->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_PUUp->SetBinContent(j, DY_eejj_2017_PUUp->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_PUDown->SetBinContent(j, DY_eejj_2017_PUDown->GetBinContent(j) * alpha_ele);
    DY_eejj_energyScaleUp->SetBinContent(j, DY_eejj_energyScaleUp->GetBinContent(j) * alpha_ele);
    DY_eejj_energyScaleDown->SetBinContent(j, DY_eejj_energyScaleDown->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_energySigmaUp->SetBinContent(j, DY_eejj_2017_energySigmaUp->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_energySigmaDown->SetBinContent(j, DY_eejj_2017_energySigmaDown->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_centralJesJer->SetBinContent(j, DY_eejj_2017_centralJesJer->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_JesSFUp->SetBinContent(j, DY_eejj_2017_JesSFUp->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_JesSFDown->SetBinContent(j, DY_eejj_2017_JesSFDown->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_JerSFUp->SetBinContent(j, DY_eejj_2017_JerSFUp->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_JerSFDown->SetBinContent(j, DY_eejj_2017_JerSFDown->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_PrefUp->SetBinContent(j, DY_eejj_2017_PrefUp->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_PrefDown->SetBinContent(j, DY_eejj_2017_PrefDown->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_KqcdUp->SetBinContent(j, DY_eejj_2017_KqcdUp->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_KqcdDown->SetBinContent(j, DY_eejj_2017_KqcdDown->GetBinContent(j) * alpha_ele);
//    cout<< DY_eejj_2017_SFUp->GetBinContent(j) <<endl;
//    cout<< DY_eejj_2017_AlphaRatio->GetBinContent(j) <<endl;
//    cout<< DY_eejj_2017_SFDown->GetBinContent(j) <<endl;
//    cout<<"================"<<endl; 

 // cout<< DY_eejj_2017_AlphaRatio->GetBinContent(j)/DY_eejj->GetBinContent(j) <<endl;
 // cout<< DY_eejj_2017_AlphaRatioDown->GetBinContent(j)/DY_eejj->GetBinContent(j) <<endl;
 // cout<<"================"<<endl; 
    //DY CR 150-300 GeV
    DY_DYcr_eejj_SS->SetBinContent(j, DY_DYcr_eejj_SS->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_OS->SetBinContent(j, DY_DYcr_eejj_OS->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_AlphaRatio->SetBinContent(j, DY_DYcr_eejj_2017_AlphaRatio->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_AlphaRatio_BB->SetBinContent(j, DY_DYcr_eejj_2017_AlphaRatio_BB->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_AlphaRatio_BE->SetBinContent(j, DY_DYcr_eejj_2017_AlphaRatio_BE->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_AlphaRatio_EE->SetBinContent(j, DY_DYcr_eejj_2017_AlphaRatio_EE->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_AlphaRatioUp->SetBinContent(j, DY_DYcr_eejj_2017_AlphaRatioUp->GetBinContent(j) * (alpha_ele+dalpha_ele));
    DY_DYcr_eejj_2017_AlphaRatioDown->SetBinContent(j, DY_DYcr_eejj_2017_AlphaRatioDown->GetBinContent(j) * (alpha_ele-dalpha_ele));
    DY_DYcr_eejj_2017_SFUp->SetBinContent(j, DY_DYcr_eejj_2017_SFUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_SFDown->SetBinContent(j, DY_DYcr_eejj_2017_SFDown->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_PUUp->SetBinContent(j, DY_DYcr_eejj_2017_PUUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_PUDown->SetBinContent(j, DY_DYcr_eejj_2017_PUDown->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_energyScaleUp->SetBinContent(j, DY_DYcr_eejj_energyScaleUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_energyScaleDown->SetBinContent(j, DY_DYcr_eejj_energyScaleDown->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_energySigmaUp->SetBinContent(j, DY_DYcr_eejj_2017_energySigmaUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_energySigmaDown->SetBinContent(j, DY_DYcr_eejj_2017_energySigmaDown->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_centralJesJer->SetBinContent(j, DY_DYcr_eejj_centralJesJer->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_JesSFUp->SetBinContent(j, DY_DYcr_eejj_2017_JesSFUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_JesSFDown->SetBinContent(j, DY_DYcr_eejj_2017_JesSFDown->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_JerSFUp->SetBinContent(j, DY_DYcr_eejj_2017_JerSFUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_JerSFDown->SetBinContent(j, DY_DYcr_eejj_2017_JerSFDown->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_PrefUp->SetBinContent(j, DY_DYcr_eejj_2017_PrefUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_PrefDown->SetBinContent(j, DY_DYcr_eejj_2017_PrefDown->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_KqcdUp->SetBinContent(j, DY_DYcr_eejj_2017_KqcdUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_KqcdDown->SetBinContent(j, DY_DYcr_eejj_2017_KqcdDown->GetBinContent(j) * alpha_ele);

// muon channel histograms
    double alpha_mu=Alpha_mu[j-1];
    double dalpha_mu=dAlpha_mu[j-1];
    DY_mumujj_SS->SetBinContent(j, DY_mumujj_SS->GetBinContent(j) * alpha_mu);
    DY_mumujj_OS->SetBinContent(j, DY_mumujj_OS->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_AlphaRatio->SetBinContent(j, DY_mumujj_2017_AlphaRatio->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_AlphaRatio_BB->SetBinContent(j, DY_mumujj_2017_AlphaRatio_BB->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_AlphaRatio_BE->SetBinContent(j, DY_mumujj_2017_AlphaRatio_BE->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_AlphaRatio_EE->SetBinContent(j, DY_mumujj_2017_AlphaRatio_EE->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_AlphaRatioUp->SetBinContent(j, DY_mumujj_2017_AlphaRatioUp->GetBinContent(j) * (alpha_mu+dalpha_mu));
    DY_mumujj_2017_AlphaRatioDown->SetBinContent(j, DY_mumujj_2017_AlphaRatioDown->GetBinContent(j) * (alpha_mu-dalpha_mu));
    DY_mumujj_2017_SFUp->SetBinContent(j, DY_mumujj_2017_SFUp->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_SFDown->SetBinContent(j, DY_mumujj_2017_SFDown->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_PUUp->SetBinContent(j, DY_mumujj_2017_PUUp->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_PUDown->SetBinContent(j, DY_mumujj_2017_PUDown->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_PtResoUp->SetBinContent(j, DY_mumujj_2017_PtResoUp->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_PtResoDown->SetBinContent(j, DY_mumujj_2017_PtResoDown->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_PtReso2Up->SetBinContent(j, DY_mumujj_2017_PtReso2Up->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_PtReso2Down->SetBinContent(j, DY_mumujj_2017_PtReso2Down->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_centralJesJer->SetBinContent(j, DY_mumujj_2017_centralJesJer->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_JesSFUp->SetBinContent(j, DY_mumujj_2017_JesSFUp->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_JesSFDown->SetBinContent(j, DY_mumujj_2017_JesSFDown->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_JerSFUp->SetBinContent(j, DY_mumujj_2017_JerSFUp->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_JerSFDown->SetBinContent(j, DY_mumujj_2017_JerSFDown->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_PrefUp->SetBinContent(j, DY_mumujj_2017_PrefUp->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_PrefDown->SetBinContent(j, DY_mumujj_2017_PrefDown->GetBinContent(j) * alpha_mu); 
    DY_mumujj_2017_KqcdUp->SetBinContent(j, DY_mumujj_2017_KqcdUp->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_KqcdDown->SetBinContent(j, DY_mumujj_2017_KqcdDown->GetBinContent(j) * alpha_mu);
//cout<< DY_mumujj_2017_AlphaRatio->GetBinContent(j)/DY_mumujj->GetBinContent(j) <<endl;
 // cout<< DY_mumujj_2017_AlphaRatioUp->GetBinContent(j)/DY_mumujj->GetBinContent(j) <<endl;
 // cout<< DY_mumujj_2017_AlphaRatioDown->GetBinContent(j)/DY_mumujj->GetBinContent(j) <<endl;
 // cout<<"================"<<endl; 
 // cout<<"================"<<endl; 

     //DY CR 150-300 GeV
    DY_DYcr_mumujj_SS->SetBinContent(j, DY_DYcr_mumujj_SS->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_OS->SetBinContent(j, DY_DYcr_mumujj_OS->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_AlphaRatio->SetBinContent(j, DY_DYcr_mumujj_2017_AlphaRatio->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_AlphaRatio_BB->SetBinContent(j, DY_DYcr_mumujj_2017_AlphaRatio_BB->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_AlphaRatio_BE->SetBinContent(j, DY_DYcr_mumujj_2017_AlphaRatio_BE->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_AlphaRatio_EE->SetBinContent(j, DY_DYcr_mumujj_2017_AlphaRatio_EE->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_AlphaRatioUp->SetBinContent(j, DY_DYcr_mumujj_2017_AlphaRatioUp->GetBinContent(j) * (alpha_mu+dalpha_mu));
    DY_DYcr_mumujj_2017_AlphaRatioDown->SetBinContent(j, DY_DYcr_mumujj_2017_AlphaRatioDown->GetBinContent(j) * (alpha_mu-dalpha_mu));
    DY_DYcr_mumujj_2017_SFUp->SetBinContent(j, DY_DYcr_mumujj_2017_SFUp->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_SFDown->SetBinContent(j, DY_DYcr_mumujj_2017_SFDown->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_PUUp->SetBinContent(j, DY_DYcr_mumujj_2017_PUUp->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_PUDown->SetBinContent(j, DY_DYcr_mumujj_2017_PUDown->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_PtResoUp->SetBinContent(j, DY_DYcr_mumujj_2017_PtResoUp->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_PtResoDown->SetBinContent(j, DY_DYcr_mumujj_2017_PtResoDown->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_PtReso2Up->SetBinContent(j, DY_DYcr_mumujj_2017_PtReso2Up->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_PtReso2Down->SetBinContent(j, DY_DYcr_mumujj_2017_PtReso2Down->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_centralJesJer->SetBinContent(j, DY_DYcr_mumujj_centralJesJer->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_JesSFUp->SetBinContent(j, DY_DYcr_mumujj_2017_JesSFUp->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_JesSFDown->SetBinContent(j, DY_DYcr_mumujj_2017_JesSFDown->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_JerSFUp->SetBinContent(j, DY_DYcr_mumujj_2017_JerSFUp->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_JerSFDown->SetBinContent(j, DY_DYcr_mumujj_2017_JerSFDown->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_PrefUp->SetBinContent(j, DY_DYcr_mumujj_2017_PrefUp->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_PrefDown->SetBinContent(j, DY_DYcr_mumujj_2017_PrefDown->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_KqcdUp->SetBinContent(j, DY_DYcr_mumujj_2017_KqcdUp->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_KqcdDown->SetBinContent(j, DY_DYcr_mumujj_2017_KqcdDown->GetBinContent(j) * alpha_mu);
}

/********/

TFile *f = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/2017_ALL_HOPE/18102021/SR_syst_DY_HTincl_LO_noKfactor_2017.root", "RECREATE");
//TFile *f = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/2017_ALL_HOPE/18102021/SR_syst_DY_HTincl_LO_Kfactor_new_2017.root", "RECREATE");
n_best_Vtx->Write();
DY_eejj_SS->Write();
DY_eejj_OS->Write();
DY_Zpeak_eejj_SS->Write();
DY_Zpeak_eejj_OS->Write();
DY_DYcr_eejj_SS->Write();
DY_DYcr_eejj_OS->Write();
DY_mumujj_SS->Write();
DY_mumujj_OS->Write();
DY_Zpeak_mumujj_SS->Write();
DY_Zpeak_mumujj_OS->Write();
DY_DYcr_mumujj_SS->Write();
DY_DYcr_mumujj_OS->Write();
DY_TTtWcr_llJ_SS->Write();
DY_TTtWcr_llJ_OS->Write();

DY_HTee->Write();
DY_HTee_BB->Write();
DY_HTee_BE->Write();
DY_HTee_EE->Write();
DY_HTmumu->Write();
DY_HTmumu_BB->Write();
DY_HTmumu_BE->Write();
DY_HTmumu_EE->Write();
DY_Mmumu->Write();
DY_Mmumu_BB->Write();
DY_Mmumu_BE->Write();
DY_Mmumu_EE->Write();
DY_Mee->Write();
DY_Mee_BB->Write();
DY_Mee_BE->Write();
DY_Mee_EE->Write();
DY_eejj_ele1_ecalTrkEnergyPostCorr->Write();
DY_eejj_ele2_ecalTrkEnergyPostCorr->Write();
DY_eejj_ele1_energy->Write();
DY_eejj_ele2_energy->Write();
DY_eejj->Write();
DY_eejj_BB->Write();
DY_eejj_BE->Write();
DY_eejj_EE->Write();
DY_eejj_2017_AlphaRatio->Write();
DY_eejj_2017_AlphaRatio_BB->Write();
DY_eejj_2017_AlphaRatio_BE->Write();
DY_eejj_2017_AlphaRatio_EE->Write();
DY_eejj_2017_AlphaRatioUp->Write();
DY_eejj_2017_AlphaRatioDown->Write();
DY_eejj_2017_PrefUp->Write();
DY_eejj_2017_PrefDown->Write();
DY_eejj_2017_SFUp->Write();
DY_eejj_2017_SFDown->Write();
DY_eejj_2017_PUUp->Write();
DY_eejj_2017_PUDown->Write();
DY_eejj_2017_centralJesJer->Write();
DY_eejj_2017_JesSFUp->Write();
DY_eejj_2017_JesSFDown->Write();
DY_eejj_2017_JerSFUp->Write();
DY_eejj_2017_JerSFDown->Write();
DY_eejj_energyScaleUp->Write();
DY_eejj_energyScaleDown->Write();
DY_eejj_2017_energySigmaUp->Write();
DY_eejj_2017_energySigmaDown->Write();
DY_eejj_2017_KqcdUp->Write();
DY_eejj_2017_KqcdDown->Write();

DY_mumujj->Write();
DY_mumujj_BB->Write();
DY_mumujj_BE->Write();
DY_mumujj_EE->Write();
DY_mumujj_Roc->Write();
DY_mumujj_2017_AlphaRatio->Write();
DY_mumujj_2017_AlphaRatio_BB->Write();
DY_mumujj_2017_AlphaRatio_BE->Write();
DY_mumujj_2017_AlphaRatio_EE->Write();
DY_mumujj_2017_AlphaRatioUp->Write();
DY_mumujj_2017_AlphaRatioDown->Write();
DY_mumujj_2017_PrefUp->Write();
DY_mumujj_2017_PrefDown->Write();
DY_mumujj_2017_SFUp->Write();
DY_mumujj_2017_SFDown->Write();
DY_mumujj_2017_PUUp->Write();
DY_mumujj_2017_PUDown->Write();
DY_mumujj_2017_centralJesJer->Write();
DY_mumujj_2017_JesSFUp->Write();
DY_mumujj_2017_JesSFDown->Write();
DY_mumujj_2017_JerSFUp->Write();
DY_mumujj_2017_JerSFDown->Write();
DY_mumujj_2017_PtResoUp->Write();
DY_mumujj_2017_PtResoDown->Write();
DY_mumujj_2017_PtReso2Up->Write();
DY_mumujj_2017_PtReso2Down->Write();
DY_mumujj_2017_KqcdUp->Write();
DY_mumujj_2017_KqcdDown->Write();

//Zpeak DYcr 
DY_ZpeakMll_eejj->Write();
DY_ZpeakMll_eejj_BB->Write();
DY_ZpeakMll_eejj_BE->Write();
DY_ZpeakMll_eejj_EE->Write();
DY_ZpeakMll_mumujj->Write();
DY_ZpeakMll_mumujj_BB->Write();
DY_ZpeakMll_mumujj_BE->Write();
DY_ZpeakMll_mumujj_EE->Write();
DY_Zpeak_eejj->Write();
DY_Zpeak_eejj_BB->Write();
DY_Zpeak_eejj_BE->Write();
DY_Zpeak_eejj_EE->Write();
DY_Zpeak_mumujj->Write();
DY_Zpeak_mumujj_BE->Write();
DY_Zpeak_mumujj_BB->Write();
DY_Zpeak_mumujj_EE->Write();
DY_Zpeak_ee_pt_2017->Write();
DY_Zpeak_ee_pt_2017_BB->Write();
DY_Zpeak_ee_pt_2017_BE->Write();
DY_Zpeak_ee_pt_2017_EE->Write();
DY_Zpeak_mumu_pt_2017->Write();
DY_Zpeak_mumu_pt_2017_BB->Write();
DY_Zpeak_mumu_pt_2017_BE->Write();
DY_Zpeak_mumu_pt_2017_EE->Write();

DY_Zpeak_mumu_pt_2017_SFUp->Write();
DY_Zpeak_mumu_pt_2017_SFDown->Write();
DY_Zpeak_mumu_pt_2017_PUUp->Write();
DY_Zpeak_mumu_pt_2017_PUDown->Write();
DY_Zpeak_mumu_pt_2017_PtResoUp->Write();
DY_Zpeak_mumu_pt_2017_PtResoDown->Write();
DY_Zpeak_mumu_pt_2017_PtReso2Down->Write();
DY_Zpeak_mumu_pt_2017_centralJesJer->Write();
DY_Zpeak_mumu_pt_2017_JesSFUp->Write();
DY_Zpeak_mumu_pt_2017_JesSFDown->Write();
DY_Zpeak_mumu_pt_2017_JerSFUp->Write();
DY_Zpeak_mumu_pt_2017_JerSFDown->Write();

DY_Zpeak_ee_pt_2017_SFUp->Write();
DY_Zpeak_ee_pt_2017_SFDown->Write();
DY_Zpeak_ee_pt_2017_PUUp->Write();
DY_Zpeak_ee_pt_2017_PUDown->Write();
DY_Zpeak_ee_pt_energyScaleUp->Write();
DY_Zpeak_ee_pt_energyScaleDown->Write();
DY_Zpeak_ee_pt_2017_energySigmaUp->Write();
DY_Zpeak_ee_pt_2017_energySigmaDown->Write();
DY_Zpeak_ee_pt_2017_centralJesJer->Write();
DY_Zpeak_ee_pt_2017_JesSFUp->Write();
DY_Zpeak_ee_pt_2017_JesSFDown->Write();
DY_Zpeak_ee_pt_2017_JerSFUp->Write();
DY_Zpeak_ee_pt_2017_JerSFDown->Write();

//DYcr 
DY_DYcr_eejj_ele1_ecalTrkEnergyPostCorr->Write();
DY_DYcr_eejj_ele2_ecalTrkEnergyPostCorr->Write();
DY_DYcr_eejj_ele1_energy->Write();
DY_DYcr_eejj_ele2_energy->Write();
Mee_DYcr->Write();
Mee_DYcr_BB->Write();
Mee_DYcr_BE->Write();
Mee_DYcr_EE->Write();
DY_DYcr_eejj->Write();
DY_DYcr_eejj_BB->Write();
DY_DYcr_eejj_BE->Write();
DY_DYcr_eejj_EE->Write();
DY_DYcr_eejj_2017_AlphaRatio->Write();
DY_DYcr_eejj_2017_AlphaRatio_BB->Write();
DY_DYcr_eejj_2017_AlphaRatio_BE->Write();
DY_DYcr_eejj_2017_AlphaRatio_EE->Write();
DY_DYcr_eejj_2017_AlphaRatioUp->Write();
DY_DYcr_eejj_2017_AlphaRatioDown->Write();
DY_DYcr_eejj_2017_PrefUp->Write();
DY_DYcr_eejj_2017_PrefDown->Write();
DY_DYcr_eejj_2017_SFUp->Write();
DY_DYcr_eejj_2017_SFDown->Write();
DY_DYcr_eejj_2017_PUUp->Write();
DY_DYcr_eejj_2017_PUDown->Write();
DY_DYcr_eejj_centralJesJer->Write();
DY_DYcr_eejj_2017_JesSFUp->Write();
DY_DYcr_eejj_2017_JesSFDown->Write();
DY_DYcr_eejj_2017_JerSFUp->Write();
DY_DYcr_eejj_2017_JerSFDown->Write();
DY_DYcr_eejj_energyScaleUp->Write();
DY_DYcr_eejj_energyScaleDown->Write();
DY_DYcr_eejj_2017_energySigmaUp->Write();
DY_DYcr_eejj_2017_energySigmaDown->Write();
DY_DYcr_eejj_2017_KqcdUp->Write();
DY_DYcr_eejj_2017_KqcdDown->Write();

Mmumu_DYcr->Write();
Mmumu_DYcr_BB->Write();
Mmumu_DYcr_BE->Write();
Mmumu_DYcr_EE->Write();
DY_DYcr_mumujj->Write();
DY_DYcr_mumujj_BB->Write();
DY_DYcr_mumujj_BE->Write();
DY_DYcr_mumujj_EE->Write();
DY_DYcr_mumujj_2017_AlphaRatio->Write();
DY_DYcr_mumujj_2017_AlphaRatio_BB->Write();
DY_DYcr_mumujj_2017_AlphaRatio_BE->Write();
DY_DYcr_mumujj_2017_AlphaRatio_EE->Write();
DY_DYcr_mumujj_2017_AlphaRatioUp->Write();
DY_DYcr_mumujj_2017_AlphaRatioDown->Write();
DY_DYcr_mumujj_2017_PrefUp->Write();
DY_DYcr_mumujj_2017_PrefDown->Write();
DY_DYcr_mumujj_2017_SFUp->Write();
DY_DYcr_mumujj_2017_SFDown->Write();
DY_DYcr_mumujj_2017_PUUp->Write();
DY_DYcr_mumujj_2017_PUDown->Write();
DY_DYcr_mumujj_centralJesJer->Write();
DY_DYcr_mumujj_2017_JesSFUp->Write();
DY_DYcr_mumujj_2017_JesSFDown->Write();
DY_DYcr_mumujj_2017_JerSFUp->Write();
DY_DYcr_mumujj_2017_JerSFDown->Write();
DY_DYcr_mumujj_2017_PtResoUp->Write();
DY_DYcr_mumujj_2017_PtResoDown->Write();
DY_DYcr_mumujj_2017_PtReso2Up->Write();
DY_DYcr_mumujj_2017_PtReso2Down->Write();
DY_DYcr_mumujj_2017_KqcdUp->Write();
DY_DYcr_mumujj_2017_KqcdDown->Write();

//TTtW cr
DY_TTtWcr_HTevent->Write();
DY_TTtWcr_ll->Write();
DY_TTtWcr_ll_BB->Write();
DY_TTtWcr_ll_BE->Write();
DY_TTtWcr_ll_EE->Write();
DY_TTtWcr_llJ->Write();
DY_TTtWcr_llJ_BB->Write();
DY_TTtWcr_llJ_BE->Write();
DY_TTtWcr_llJ_EE->Write();
DY_TTtWcr_llJ_2017_AlphaRatio->Write();
DY_TTtWcr_llJ_2017_AlphaRatioUp->Write();
DY_TTtWcr_llJ_2017_AlphaRatioDown->Write();
DY_TTtWcr_llJ_2017_SFUp->Write();
DY_TTtWcr_llJ_2017_SFDown->Write();
DY_TTtWcr_llJ_2017_PUUp->Write();
DY_TTtWcr_llJ_2017_PUDown->Write();
DY_TTtWcr_llJ_2017_PtResoUp->Write();
DY_TTtWcr_llJ_2017_PtResoDown->Write();
DY_TTtWcr_llJ_2017_PtReso2Up->Write();
DY_TTtWcr_llJ_2017_PtReso2Down->Write();
DY_TTtWcr_llJ_energyScaleUp->Write();
DY_TTtWcr_llJ_energyScaleDown->Write();
DY_TTtWcr_llJ_2017_energySigmaUp->Write();
DY_TTtWcr_llJ_2017_energySigmaDown->Write();
DY_TTtWcr_llJ_centralJesJer->Write();
DY_TTtWcr_llJ_2017_JesSFUp->Write();
DY_TTtWcr_llJ_2017_JesSFDown->Write();
DY_TTtWcr_llJ_2017_JerSFUp->Write();
DY_TTtWcr_llJ_2017_JerSFDown->Write();
DY_TTtWcr_llJ_2017_PrefUp->Write();
DY_TTtWcr_llJ_2017_PrefDown->Write();
DY_TTtWcr_llJ_2017_KqcdUp->Write();
DY_TTtWcr_llJ_2017_KqcdDown->Write();

f->Write();
f->Close();

}
 
