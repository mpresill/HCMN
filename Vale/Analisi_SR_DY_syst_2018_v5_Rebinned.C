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
void Analisi_SR_DY_syst_2018_v5_Rebinned(){

TChain *a_ = new TChain("BOOM");

a_->Add("/eos/user/m/mpresill/CMS/HN_Reload/DY_HTsplitted/25062021/DY_HTincl_LO_2018.root");
//a_->Add("/eos/user/v/vmariani/NTuples/HN_2017/Syst_ALL_newMuonSF/DY_HT100Inf_2017.root");

//a_->Add("/eos/user/m/mpresill/CMS/HN_Reload/rootplized_samples_2018_syst/DY_2018.root");
//a_->Add("/eos/user/m/mpresill/CMS/HN_Reload/rootplized_samples_2018_syst/DY_FxFx_2018.root");


int HLT_Ele, HLT_Mu, HLT_Mu50, HLT_OldMu100, HLT_TkMu50, HLT_TkMu100;
double muejj_l, emujj_l;
std:vector<double>* patElectron_pt; patElectron_pt=0;
vector<double>* patElectron_eta; patElectron_eta=0;
vector<double>* patElectron_phi; patElectron_phi=0;
vector<double>* patElectron_ecalTrkEnergyPostCorr; patElectron_ecalTrkEnergyPostCorr=0;
vector<double>* patElectron_energy; patElectron_energy=0;
vector<double>* patElectron_energyScaleUp; patElectron_energyScaleUp=0;
vector<double>* patElectron_energyScaleDown; patElectron_energyScaleDown=0;
vector<double>* patElectron_energySigmaUp; patElectron_energySigmaUp=0;
vector<double>* patElectron_energySigmaDown; patElectron_energySigmaDown=0;
vector<int>* patElectron_charge; patElectron_charge=0;
//vector<double>* Muon_pt_tunePbt_Roc; Muon_pt_tunePbt_Roc=0;
//vector<double>* Muon_pt_tunePbt_Roc_corr; Muon_pt_tunePbt_Roc_corr=0;
vector<double>* Muon_pt_tunePbt_Roc; Muon_pt_tunePbt_Roc=0;
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
TBranch *a_HLT_Mu50=a_->GetBranch("HLT_Mu50");
TBranch *a_HLT_OldMu100=a_->GetBranch("HLT_OldMu100");
TBranch *a_HLT_TkMu50=a_->GetBranch("HLT_TkMu50");
TBranch *a_HLT_TkMu100=a_->GetBranch("HLT_TkMu100");

TBranch *a_patElectron_pt=a_->GetBranch("patElectron_pt");
TBranch *a_patElectron_eta=a_->GetBranch("patElectron_eta");
TBranch *a_patElectron_phi=a_->GetBranch("patElectron_phi");
TBranch *a_patElectron_ecalTrkEnergyPostCorr=a_->GetBranch("patElectron_ecalTrkEnergyPostCorr");
TBranch *a_patElectron_energy=a_->GetBranch("patElectron_energy");
TBranch *a_patElectron_energyScaleUp=a_->GetBranch("patElectron_energyScaleUp");
TBranch *a_patElectron_energyScaleDown=a_->GetBranch("patElectron_energyScaleDown");
TBranch *a_patElectron_energySigmaUp=a_->GetBranch("patElectron_energySigmaUp");
TBranch *a_patElectron_energySigmaDown=a_->GetBranch("patElectron_energySigmaDown");
TBranch *a_patElectron_charge=a_->GetBranch("patElectron_charge");

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

a_HLT_Ele115_CaloIdVT_GsfTrkIdT->SetAddress(&HLT_Ele);
a_HLT_Mu50->SetAddress(&HLT_Mu50);
a_HLT_OldMu100->SetAddress(&HLT_OldMu100);
a_HLT_TkMu50->SetAddress(&HLT_TkMu50);
a_HLT_TkMu100->SetAddress(&HLT_TkMu100);

a_patElectron_pt->SetAddress(&patElectron_pt);
a_patElectron_eta->SetAddress(&patElectron_eta);
a_patElectron_phi->SetAddress(&patElectron_phi);
a_patElectron_ecalTrkEnergyPostCorr->SetAddress(&patElectron_ecalTrkEnergyPostCorr);
a_patElectron_energy->SetAddress(&patElectron_energy);
a_patElectron_energyScaleUp->SetAddress(&patElectron_energyScaleUp);
a_patElectron_energyScaleDown->SetAddress(&patElectron_energyScaleDown);
a_patElectron_energySigmaUp->SetAddress(&patElectron_energySigmaUp);
a_patElectron_energySigmaDown->SetAddress(&patElectron_energySigmaDown);
a_patElectron_charge->SetAddress(&patElectron_charge);

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


const double asymbins[9] = {0,200,400,600,800,1000,1400,2000,10000};

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
TH1D *NumFatJet = new TH1D ("NumFatJet", "NumFatJet", 20, 0, 20);
TH1D *NumFatJet_mu = new TH1D ("NumFatJet_mu", "NumFatJet_mu", 20, 0, 20);

TH1D *DY_mumujj_Roc = new TH1D ("DY_mumujj_Roc", "DY_mumujj_Roc", 8, asymbins);
TH1D *DY_mumujj = new TH1D ("DY_mumujj", "DY_mumujj", 8, asymbins);
TH1D *DY_mumujj_BB = new TH1D ("DY_mumujj_BB", "DY_mumujj_BB", 8, asymbins);
TH1D *DY_mumujj_BE = new TH1D ("DY_mumujj_BE", "DY_mumujj_BE", 8, asymbins);
TH1D *DY_mumujj_EE = new TH1D ("DY_mumujj_EE", "DY_mumujj_EE", 8, asymbins);
TH1D *DY_mumujj_2018_AlphaRatio = new TH1D ("DY_mumujj_2018_AlphaRatio", "DY_2018_mumujj_AlphaRatio", 8, asymbins);
TH1D *DY_mumujj_2018_AlphaRatio_BB = new TH1D ("DY_mumujj_2018_AlphaRatio_BB", "DY_mumujj_2018_AlphaRatio_BB", 8, asymbins);
TH1D *DY_mumujj_2018_AlphaRatio_BE = new TH1D ("DY_mumujj_2018_AlphaRatio_BE", "DY_mumujj_2018_AlphaRatio_BE", 8, asymbins);
TH1D *DY_mumujj_2018_AlphaRatio_EE = new TH1D ("DY_mumujj_2018_AlphaRatio_EE", "DY_mumujj_2018_AlphaRatio_EE", 8, asymbins);
TH1D *DY_mumujj_2018_AlphaRatioDown = new TH1D ("DY_mumujj_2018_AlphaRatioDown", "DY_mumujj_2018_AlphaRatioDown", 8, asymbins);
TH1D *DY_mumujj_2018_AlphaRatioUp = new TH1D ("DY_mumujj_2018_AlphaRatioUp", "DY_mumujj_2018_AlphaRatioUp", 8, asymbins);
TH1D *DY_mumujj_2018_SFUp = new TH1D ("DY_mumujj_2018_SFUp", "DY_mumujj_2018_SFUp", 8, asymbins);
TH1D *DY_mumujj_2018_SFDown = new TH1D ("DY_mumujj_2018_SFDown", "DY_mumujj_2018_SFDown", 8, asymbins);
TH1D *DY_mumujj_2018_PUUp = new TH1D ("DY_mumujj_2018_PUUp", "DY_mumujj_2018_PUUp", 8, asymbins);
TH1D *DY_mumujj_2018_PUDown = new TH1D ("DY_mumujj_2018_PUDown", "DY_mumujj_2018_PUDown", 8, asymbins);
TH1D *DY_mumujj_2018_centralJesJer = new TH1D ("DY_mumujj_2018_centralJesJer", "DY_mumujj_2018_centralJesJer", 8, asymbins);
TH1D *DY_mumujj_2018_JesSFUp = new TH1D ("DY_mumujj_2018_JesSFUp", "DY_mumujj_2018_JesSFUp", 8, asymbins);
TH1D *DY_mumujj_2018_JesSFDown = new TH1D ("DY_mumujj_2018_JesSFDown", "DY_mumujj_2018_JesSFDown", 8, asymbins);
TH1D *DY_mumujj_2018_JerSFUp = new TH1D ("DY_mumujj_2018_JerSFUp", "DY_mumujj_2018_JerSFUp", 8, asymbins);
TH1D *DY_mumujj_2018_JerSFDown = new TH1D ("DY_mumujj_2018_JerSFDown", "DY_mumujj_2018_JerSFDown", 8, asymbins);
/*TH1D *DY_mumujj_2018_PtCorr = new TH1D ("DY_mumujj_2018_PtCorr", "DY_mumujj_2018_PtCorr", 8, asymbins);
TH1D *DY_mumujj_2018_PtCorrDown = new TH1D ("DY_mumujj_2018_PtCorrDown", "DY_mumujj_2018_PtCorrDown", 8, asymbins);
TH1D *DY_mumujj_2018_PtCorrUp = new TH1D ("DY_mumujj_2018_PtCorrUp", "DY_mumujj_2018_PtCorrUp", 8, asymbins);*/
TH1D *DY_mumujj_2018_PtResoUp  = new TH1D ("DY_mumujj_2018_PtResoUp", "DY_mumujj_2018_PtResoUp", 8, asymbins);
TH1D *DY_mumujj_2018_PtResoDown  = new TH1D ("DY_mumujj_2018_PtResoDown", "DY_mumujj_2018_PtResoDown", 8, asymbins);
TH1D *DY_mumujj_2018_PtReso2Up  = new TH1D ("DY_mumujj_2018_PtReso2Up", "DY_mumujj_2018_PtReso2Up", 8, asymbins);
TH1D *DY_mumujj_2018_PtReso2Down  = new TH1D ("DY_mumujj_2018_PtReso2Down", "DY_mumujj_2018_PtReso2Down", 8, asymbins);
TH1D *DY_mumujj_2018_KqcdUp = new TH1D ("DY_mumujj_2018_KqcdUp", "DY_mumujj_2018_KqcdUp", 8, asymbins);
TH1D *DY_mumujj_2018_KqcdDown = new TH1D ("DY_mumujj_2018_KqcdDown", "DY_mumujj_2018_KqcdDown", 8, asymbins);

TH1D *DY_Mee = new TH1D ("DY_Mee", "DY_Mee", 100, 0, 1000);
TH1D *DY_Mee_BB = new TH1D ("DY_Mee_BB", "DY_Mee_BB", 100, 0, 1000);
TH1D *DY_Mee_BE = new TH1D ("DY_Mee_BE", "DY_Mee_BE", 100, 0, 1000);
TH1D *DY_Mee_EE = new TH1D ("DY_Mee_EE", "DY_Mee_EE", 100, 0, 1000);
TH1D *DY_HTee = new TH1D ("DY_HTee", "DY_HTee", 100, 0, 5000);
TH1D *DY_HTee_BB = new TH1D ("DY_HTee_BB", "DY_HTee_BB", 100, 0, 5000);
TH1D *DY_HTee_BE = new TH1D ("DY_HTee_BE", "DY_HTee_BE", 100, 0, 5000);
TH1D *DY_HTee_EE = new TH1D ("DY_HTee_EE", "DY_HTee_EE", 100, 0, 5000);
TH1D *DY_eejj = new TH1D ("DY_eejj", "DY_eejj", 8, asymbins);
TH1D *DY_eejj_BB = new TH1D ("DY_eejj_BB", "DY_eejj_BB", 8, asymbins);
TH1D *DY_eejj_BE = new TH1D ("DY_eejj_BE", "DY_eejj_BE", 8, asymbins);
TH1D *DY_eejj_EE = new TH1D ("DY_eejj_EE", "DY_eejj_EE", 8, asymbins);
TH1D *DY_eejj_2018_AlphaRatio = new TH1D ("DY_eejj_2018_AlphaRatio", "DY_eejj_2018_AlphaRatio", 8, asymbins);
TH1D *DY_eejj_2018_AlphaRatio_BB = new TH1D ("DY_eejj_2018_AlphaRatio_BB", "DY_eejj_2018_AlphaRatio_BB", 8, asymbins);
TH1D *DY_eejj_2018_AlphaRatio_BE = new TH1D ("DY_eejj_2018_AlphaRatio_BE", "DY_eejj_2018_AlphaRatio_BE", 8, asymbins);
TH1D *DY_eejj_2018_AlphaRatio_EE = new TH1D ("DY_eejj_2018_AlphaRatio_EE", "DY_eejj_2018_AlphaRatio_EE", 8, asymbins);
TH1D *DY_eejj_2018_AlphaRatioDown = new TH1D ("DY_eejj_2018_AlphaRatioDown", "DY_eejj_2018_AlphaRatioDown", 8, asymbins);
TH1D *DY_eejj_2018_AlphaRatioUp = new TH1D ("DY_eejj_2018_AlphaRatioUp", "DY_eejj_2018_AlphaRatioUp", 8, asymbins);
TH1D *DY_eejj_2018_SFUp = new TH1D ("DY_eejj_2018_SFUp", "DY_eejj_2018_SFUp", 8, asymbins);
TH1D *DY_eejj_2018_SFDown = new TH1D ("DY_eejj_2018_SFDown", "DY_eejj_2018_SFDown", 8, asymbins);
TH1D *DY_eejj_2018_PUUp = new TH1D ("DY_eejj_2018_PUUp", "DY_eejj_2018_PUUp", 8, asymbins);
TH1D *DY_eejj_2018_PUDown = new TH1D ("DY_eejj_2018_PUDown", "DY_eejj_2018_PUDown", 8, asymbins);
TH1D *DY_eejj_2018_centralJesJer = new TH1D ("DY_eejj_2018_centralJesJer", "DY_eejj_2018_centralJesJer", 8, asymbins);
TH1D *DY_eejj_2018_JesSFUp = new TH1D ("DY_eejj_2018_JesSFUp", "DY_eejj_2018_JesSFUp", 8, asymbins);
TH1D *DY_eejj_2018_JesSFDown = new TH1D ("DY_eejj_2018_JesSFDown", "DY_eejj_2018_JesSFDown", 8, asymbins);
TH1D *DY_eejj_2018_JerSFUp = new TH1D ("DY_eejj_2018_JerSFUp", "DY_eejj_2018_JerSFUp", 8, asymbins);
TH1D *DY_eejj_2018_JerSFDown = new TH1D ("DY_eejj_2018_JerSFDown", "DY_eejj_2018_JerSFDown", 8, asymbins);
TH1D *DY_eejj_energyScaleUp = new TH1D ("DY_eejj_energyScaleUp", "DY_eejj_energyScaleUp", 8, asymbins);
TH1D *DY_eejj_energyScaleDown = new TH1D ("DY_eejj_energyScaleDown", "DY_eejj_energyScaleDown", 8, asymbins);
TH1D *DY_eejj_2018_energySigmaUp = new TH1D ("DY_eejj_2018_energySigmaUp", "DY_eejj_2018_energySigmaUp", 8, asymbins);
TH1D *DY_eejj_2018_energySigmaDown = new TH1D ("DY_eejj_2018_energySigmaDown", "DY_eejj_2018_energySigmaDown", 8, asymbins);
TH1D *DY_eejj_2018_KqcdUp = new TH1D ("DY_eejj_2018_KqcdUp", "DY_eejj_2018_KqcdUp", 8, asymbins);
TH1D *DY_eejj_2018_KqcdDown = new TH1D ("DY_eejj_2018_KqcdDown", "DY_eejj_2018_KqcdDown", 8, asymbins);

//DY CR Zpeak (mll in 60-120 GeV)
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
TH1D *DY_Zpeak_mumu_pt = new TH1D ("DY_Zpeak_mumu_pt", "DY_Zpeak_mumu_pt", 100, 0, 1000);
TH1D *DY_Zpeak_mumu_pt_BB = new TH1D ("DY_Zpeak_mumu_pt_BB", "DY_Zpeak_mumu_pt_BB", 100, 0, 1000);
TH1D *DY_Zpeak_mumu_pt_BE = new TH1D ("DY_Zpeak_mumu_pt_BE", "DY_Zpeak_mumu_pt_BE", 100, 0, 1000);
TH1D *DY_Zpeak_mumu_pt_EE = new TH1D ("DY_Zpeak_mumu_pt_EE", "DY_Zpeak_mumu_pt_EE", 100, 0, 1000);
TH1D *DY_Zpeak_ee_pt = new TH1D ("DY_Zpeak_ee_pt", "DY_Zpeak_ee_pt", 100, 0, 1000);
TH1D *DY_Zpeak_ee_pt_BB = new TH1D ("DY_Zpeak_ee_pt_BB", "DY_Zpeak_ee_pt_BB", 100, 0, 1000);
TH1D *DY_Zpeak_ee_pt_BE = new TH1D ("DY_Zpeak_ee_pt_BE", "DY_Zpeak_ee_pt_BE", 100, 0, 1000);
TH1D *DY_Zpeak_ee_pt_EE = new TH1D ("DY_Zpeak_ee_pt_EE", "DY_Zpeak_ee_pt_EE", 100, 0, 1000);

//DY CR (mll in 150-300 GeV)

TH1D *DY_DYcr_mumujj = new TH1D ("DY_DYcr_mumujj", "DY_DYcr_mumujj", 8, asymbins);
TH1D *DY_DYcr_mumujj_BB = new TH1D ("DY_DYcr_mumujj_BB", "DY_DYcr_mumujj_BB", 8, asymbins);
TH1D *DY_DYcr_mumujj_BE = new TH1D ("DY_DYcr_mumujj_BE", "DY_DYcr_mumujj_BE", 8, asymbins);
TH1D *DY_DYcr_mumujj_EE = new TH1D ("DY_DYcr_mumujj_EE", "DY_DYcr_mumujj_EE", 8, asymbins);
TH1D *Mmumu_DYcr_BB = new TH1D ("Mmumu_DYcr_BB", "Mmumu_DYcr_BB", 50, 150, 300);
TH1D *Mmumu_DYcr_BE = new TH1D ("Mmumu_DYcr_BE", "Mmumu_DYcr_BE", 50, 150, 300);
TH1D *Mmumu_DYcr_EE = new TH1D ("Mmumu_DYcr_EE", "Mmumu_DYcr_EE", 50, 150, 300);
TH1D *DY_DYcr_mumujj_2018_AlphaRatio = new TH1D ("DY_DYcr_mumujj_2018_AlphaRatio", "DY_DYcr_mumujj_2018_AlphaRatio", 8, asymbins);
TH1D *DY_DYcr_mumujj_2018_AlphaRatio_BB = new TH1D ("DY_DYcr_mumujj_2018_AlphaRatio_BB", "DY_DYcr_mumujj_2018_AlphaRatio_BB", 8, asymbins);
TH1D *DY_DYcr_mumujj_2018_AlphaRatio_BE = new TH1D ("DY_DYcr_mumujj_2018_AlphaRatio_BE", "DY_DYcr_mumujj_2018_AlphaRatio_BE", 8, asymbins);
TH1D *DY_DYcr_mumujj_2018_AlphaRatio_EE = new TH1D ("DY_DYcr_mumujj_2018_AlphaRatio_EE", "DY_DYcr_mumujj_2018_AlphaRatio_EE", 8, asymbins);
TH1D *DY_DYcr_mumujj_2018_AlphaRatioUp = new TH1D ("DY_DYcr_mumujj_2018_AlphaRatioUp", "DY_DYcr_mumujj_2018_AlphaRatioUp", 8, asymbins);
TH1D *DY_DYcr_mumujj_2018_AlphaRatioDown = new TH1D ("DY_DYcr_mumujj_2018_AlphaRatioDown", "DY_DYcr_mumujj_2018_AlphaRatioDown", 8, asymbins);
TH1D *DY_DYcr_mumujj_2018_SFUp = new TH1D ("DY_DYcr_mumujj_2018_SFUp", "DY_DYcr_mumujj_2018_SFUp", 8, asymbins);
TH1D *DY_DYcr_mumujj_2018_SFDown = new TH1D ("DY_DYcr_mumujj_2018_SFDown", "DY_DYcr_mumujj_2018_SFDown", 8, asymbins);
TH1D *DY_DYcr_mumujj_2018_PUUp = new TH1D ("DY_DYcr_mumujj_2018_PUUp", "DY_DYcr_mumujj_2018_PUUp", 8, asymbins);
TH1D *DY_DYcr_mumujj_2018_PUDown = new TH1D ("DY_DYcr_mumujj_2018_PUDown", "DY_DYcr_mumujj_2018_PUDown", 8, asymbins);
TH1D *DY_DYcr_mumujj_centralJesJer = new TH1D ("DY_DYcr_mumujj_centralJesJer", "DY_DYcr_mumujj_centralJesJer", 8, asymbins);
TH1D *DY_DYcr_mumujj_2018_JesSFUp = new TH1D ("DY_DYcr_mumujj_2018_JesSFUp", "DY_DYcr_mumujj_2018_JesSFUp", 8, asymbins);
TH1D *DY_DYcr_mumujj_2018_JesSFDown = new TH1D ("DY_DYcr_mumujj_2018_JesSFDown", "DY_DYcr_mumujj_2018_JesSFDown", 8, asymbins);
TH1D *DY_DYcr_mumujj_2018_JerSFUp = new TH1D ("DY_DYcr_mumujj_2018_JerSFUp", "DY_DYcr_mumujj_2018_JerSFUp", 8, asymbins);
TH1D *DY_DYcr_mumujj_2018_JerSFDown = new TH1D ("DY_DYcr_mumujj_2018_JerSFDown", "DY_DYcr_mumujj_2018_JerSFDown", 8, asymbins);
/*TH1D *DY_DYcr_mumujj_2018_PtCorrUp = new TH1D ("DY_DYcr_mumujj_2018_PtCorrUp", "DY_DYcr_mumujj_2018_PtCorrUp", 8, asymbins);
TH1D *DY_DYcr_mumujj_2018_PtCorrDown = new TH1D ("DY_DYcr_mumujj_2018_PtCorrDown", "DY_DYcr_mumujj_2018_PtCorrDown", 8, asymbins);*/
TH1D *DY_DYcr_mumujj_2018_PtResoUp  = new TH1D ("DY_DYcr_mumujj_2018_PtResoUp", "DY_DYcr_mumujj_2018_PtResoUp", 8, asymbins);
TH1D *DY_DYcr_mumujj_2018_PtResoDown  = new TH1D ("DY_DYcr_mumujj_2018_PtResoDown", "DY_DYcr_mumujj_2018_PtResoDown", 8, asymbins);
TH1D *DY_DYcr_mumujj_2018_PtReso2Up  = new TH1D ("DY_DYcr_mumujj_2018_PtReso2Up", "DY_DYcr_mumujj_2018_PtReso2Up", 8, asymbins);
TH1D *DY_DYcr_mumujj_2018_PtReso2Down  = new TH1D ("DY_DYcr_mumujj_2018_PtReso2Down", "DY_DYcr_mumujj_2018_PtReso2Down", 8, asymbins);
TH1D *Mmumu_DYcr = new TH1D ("Mmumu_DYcr", "Mmumu_DYcr", 50, 150, 300);
TH1D *DY_DYcr_mumujj_2018_KqcdUp = new TH1D ("DY_DYcr_mumujj_2018_KqcdUp", "DY_DYcr_mumujj_2018_KqcdUp", 8, asymbins);
TH1D *DY_DYcr_mumujj_2018_KqcdDown = new TH1D ("DY_DYcr_mumujj_2018_KqcdDown", "DY_DYcr_mumujj_2018_KqcdDown", 8, asymbins);


TH1D *Mee_DYcr = new TH1D ("Mee_DYcr", "Mee_DYcr", 50, 150, 300);
TH1D *Mee_DYcr_BB = new TH1D ("Mee_DYcr_BB", "Mee_DYcr_BB", 50, 150, 300);
TH1D *Mee_DYcr_BE = new TH1D ("Mee_DYcr_BE", "Mee_DYcr_BE", 50, 150, 300);
TH1D *Mee_DYcr_EE = new TH1D ("Mee_DYcr_EE", "Mee_DYcr_EE", 50, 150, 300);
TH1D *DY_DYcr_eejj = new TH1D ("DY_DYcr_eejj", "DY_DYcr_eejj", 8, asymbins);
TH1D *DY_DYcr_eejj_BB = new TH1D ("DY_DYcr_eejj_BB", "DY_DYcr_eejj_BB", 8, asymbins);
TH1D *DY_DYcr_eejj_BE = new TH1D ("DY_DYcr_eejj_BE", "DY_DYcr_eejj_BE", 8, asymbins);
TH1D *DY_DYcr_eejj_EE = new TH1D ("DY_DYcr_eejj_EE", "DY_DYcr_eejj_EE", 8, asymbins);
TH1D *DY_DYcr_eejj_2018_AlphaRatio = new TH1D ("DY_DYcr_eejj_2018_AlphaRatio", "DY_DYcr_eejj_2018_AlphaRatio", 8, asymbins);
TH1D *DY_DYcr_eejj_2018_AlphaRatio_BB = new TH1D ("DY_DYcr_eejj_2018_AlphaRatio_BB", "DY_DYcr_eejj_2018_AlphaRatio_BB", 8, asymbins);
TH1D *DY_DYcr_eejj_2018_AlphaRatio_BE = new TH1D ("DY_DYcr_eejj_2018_AlphaRatio_BE", "DY_DYcr_eejj_2018_AlphaRatio_BE", 8, asymbins);
TH1D *DY_DYcr_eejj_2018_AlphaRatio_EE = new TH1D ("DY_DYcr_eejj_2018_AlphaRatio_EE", "DY_DYcr_eejj_2018_AlphaRatio_EE", 8, asymbins);
TH1D *DY_DYcr_eejj_2018_AlphaRatioUp = new TH1D ("DY_DYcr_eejj_2018_AlphaRatioUp", "DY_DYcr_eejj_2018_AlphaRatioUp", 8, asymbins);
TH1D *DY_DYcr_eejj_2018_AlphaRatioDown = new TH1D ("DY_DYcr_eejj_2018_AlphaRatioDown", "DY_DYcr_eejj_2018_AlphaRatioDown", 8, asymbins);
TH1D *DY_DYcr_eejj_2018_SFUp = new TH1D ("DY_DYcr_eejj_2018_SFUp", "DY_DYcr_eejj_2018_SFUp", 8, asymbins);
TH1D *DY_DYcr_eejj_2018_SFDown = new TH1D ("DY_DYcr_eejj_2018_SFDown", "DY_DYcr_eejj_2018_SFDown", 8, asymbins);
TH1D *DY_DYcr_eejj_2018_PUUp = new TH1D ("DY_DYcr_eejj_2018_PUUp", "DY_DYcr_eejj_2018_PUUp", 8, asymbins);
TH1D *DY_DYcr_eejj_2018_PUDown = new TH1D ("DY_DYcr_eejj_2018_PUDown", "DY_DYcr_eejj_2018_PUDown", 8, asymbins);
TH1D *DY_DYcr_eejj_centralJesJer = new TH1D ("DY_DYcr_eejj_centralJesJer", "DY_DYcr_eejj_centralJesJer", 8, asymbins);
TH1D *DY_DYcr_eejj_2018_JesSFUp = new TH1D ("DY_DYcr_eejj_2018_JesSFUp", "DY_DYcr_eejj_2018_JesSFUp", 8, asymbins);
TH1D *DY_DYcr_eejj_2018_JesSFDown = new TH1D ("DY_DYcr_eejj_2018_JesSFDown", "DY_DYcr_eejj_2018_JesSFDown", 8, asymbins);
TH1D *DY_DYcr_eejj_2018_JerSFUp = new TH1D ("DY_DYcr_eejj_2018_JerSFUp", "DY_DYcr_eejj_2018_JerSFUp", 8, asymbins);
TH1D *DY_DYcr_eejj_2018_JerSFDown = new TH1D ("DY_DYcr_eejj_2018_JerSFDown", "DY_DYcr_eejj_2018_JerSFDown", 8, asymbins);
TH1D *DY_DYcr_eejj_energyScaleUp = new TH1D ("DY_DYcr_eejj_energyScaleUp", "DY_DYcr_eejj_energyScaleUp", 8, asymbins);
TH1D *DY_DYcr_eejj_energyScaleDown = new TH1D ("DY_DYcr_eejj_energyScaleDown", "DY_DYcr_eejj_energyScaleDown", 8, asymbins);
TH1D *DY_DYcr_eejj_2018_energySigmaUp = new TH1D ("DY_DYcr_eejj_2018_energySigmaUp", "DY_DYcr_eejj_2018_energySigmaUp", 8, asymbins);
TH1D *DY_DYcr_eejj_2018_energySigmaDown = new TH1D ("DY_DYcr_eejj_2018_energySigmaDown", "DY_DYcr_eejj_2018_energySigmaDown", 8, asymbins);
TH1D *DY_DYcr_eejj_2018_KqcdUp = new TH1D ("DY_DYcr_eejj_2018_KqcdUp", "DY_DYcr_eejj_2018_KqcdUp", 8, asymbins);
TH1D *DY_DYcr_eejj_2018_KqcdDown = new TH1D ("DY_DYcr_eejj_2018_KqcdDown", "DY_DYcr_eejj_2018_KqcdDown", 8, asymbins);

//TTtW cr
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
TH1D *DY_TTtWcr_llJ_2018_AlphaRatio = new TH1D ("DY_TTtWcr_llJ_2018_AlphaRatio", "DY_TTtWcr_llJ_2018_AlphaRatio", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2018_AlphaRatioUp = new TH1D ("DY_TTtWcr_llJ_2018_AlphaRatioUp", "DY_TTtWcr_llJ_2018_AlphaRatioUp", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2018_AlphaRatioDown = new TH1D ("DY_TTtWcr_llJ_2018_AlphaRatioDown", "DY_TTtWcr_llJ_2018_AlphaRatioDown", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2018_SFUp = new TH1D ("DY_TTtWcr_llJ_2018_SFUp", "DY_TTtWcr_llJ_2018_SFUp", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2018_SFDown = new TH1D ("DY_TTtWcr_llJ_2018_SFDown", "DY_TTtWcr_llJ_2018_SFDown", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2018_PUUp = new TH1D ("DY_TTtWcr_llJ_2018_PUUp", "DY_TTtWcr_llJ_2018_PUUp", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2018_PUDown = new TH1D ("DY_TTtWcr_llJ_2018_PUDown", "DY_TTtWcr_llJ_2018_PUDown", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2018_PtResoUp = new TH1D ("DY_TTtWcr_llJ_2018_PtResoUp", "DY_TTtWcr_llJ_2018_PtResoUp", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2018_PtResoDown = new TH1D ("DY_TTtWcr_llJ_2018_PtResoDown", "DY_TTtWcr_llJ_2018_PtResoDown", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2018_PtReso2Up = new TH1D ("DY_TTtWcr_llJ_2018_PtReso2Up", "DY_TTtWcr_llJ_2018_PtReso2Up", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2018_PtReso2Down = new TH1D ("DY_TTtWcr_llJ_2018_PtReso2Down", "DY_TTtWcr_llJ_2018_PtReso2Down", 8, asymbins);
TH1D *DY_TTtWcr_llJ_energyScaleUp = new TH1D ("DY_TTtWcr_llJ_energyScaleUp", "DY_TTtWcr_llJ_energyScaleUp", 8, asymbins);
TH1D *DY_TTtWcr_llJ_energyScaleDown = new TH1D ("DY_TTtWcr_llJ_energyScaleDown", "DY_TTtWcr_llJ_energyScaleDown", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2018_energySigmaUp = new TH1D ("DY_TTtWcr_llJ_2018_energySigmaUp", "DY_TTtWcr_llJ_2018_energySigmaUp", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2018_energySigmaDown = new TH1D ("DY_TTtWcr_llJ_2018_energySigmaDown", "DY_TTtWcr_llJ_2018_energySigmaDown", 8, asymbins);
TH1D *DY_TTtWcr_llJ_centralJesJer = new TH1D ("DY_TTtWcr_llJ_centralJesJer", "DY_TTtWcr_llJ_centralJesJer", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2018_JesSFUp = new TH1D ("DY_TTtWcr_llJ_2018_JesSFUp", "DY_TTtWcr_llJ_2018_JesSFUp", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2018_JesSFDown = new TH1D ("DY_TTtWcr_llJ_2018_JesSFDown", "DY_TTtWcr_llJ_2018_JesSFDown", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2018_JerSFUp = new TH1D ("DY_TTtWcr_llJ_2018_JerSFUp", "DY_TTtWcr_llJ_2018_JerSFUp", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2018_JerSFDown = new TH1D ("DY_TTtWcr_llJ_2018_JerSFDown", "DY_TTtWcr_llJ_2018_JerSFDown", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2018_KqcdUp = new TH1D ("DY_TTtWcr_llJ_2018_KqcdUp", "DY_TTtWcr_llJ_2018_KqcdUp", 8, asymbins);
TH1D *DY_TTtWcr_llJ_2018_KqcdDown = new TH1D ("DY_TTtWcr_llJ_2018_KqcdDown", "DY_TTtWcr_llJ_2018_KqcdDown", 8, asymbins);

cout << a_->GetEntries() << endl;
int tot=0, muejj = 0;
double wg = 0, wg_SFu = 0, wg_SFd = 0, wg_PUu = 0, wg_PUd = 0, wg_KqcdUp = 0, wg_KqcdDown = 0;
int lumi = 58873;//2018: 58873 //2018: 41529 //2018: 35542
bool veto_ele = false;
double mee = 0, mmumu = 0, pu_w = 0;
double MmumuJ = 0, MmumuJ_JESup = 0, MmumuJ_JESdown = 0,  MmumuJ_JERup = 0, MmumuJ_JERdown = 0; /*this is for smearing*/

/*gen particles k-factors ewk nlo, qcd nlo*/
double Z_gen_pt=0;
double Gen_stat=0;
double binCenter_ewk=0;
double binCenter_qcd=0;
double k_ewk=0, k_qcd=0, k_qcd_up = 0, k_qcd_down=0;

/*this is for the patch on lepf sf systematics*/
double elesf1=0, elesf_d1=0, elesf_d2=0; 
double elesf2=0, elesf_u1=0, elesf_u2=0;
double energy_corr0 = 0, energy_corr1 = 0;

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

double Muon1_px_smearing = 0, Muon1_py_smearing = 0, Muon1_pz_smearing = 0;
double Muon2_px_smearing = 0, Muon2_py_smearing = 0, Muon2_pz_smearing = 0;
double extra_smearing_1 =0, extra_smearing_2 = 0;
double muon_tot_pt = 0, ele_tot_pt = 0, jet_tot_pt = 0, HTevent=0;
const double Alpha_ele_[9] = {1,1,1.07,0.97,1.00,0.92,0.98,1.07};
const double Alpha_mu_[9] = {1,1,1.03,1.00,1.00,0.98,0.96,1.10};

for (Int_t i=0;i<a_->GetEntries();i++) {
 a_->GetEntry(i);
 HLT_Mu = 0; 
 tot = a_->GetEntries();
 if (i%100000 == 0) cout << i << " eventi analizzati su " << tot << endl;

/************************************************************/
  /*implementation of k-factors from monojet analysis*/
  /*here we read the histograms with the corrections */
  TFile k_qcd_file("monojetDYk/Kfactor_NLO_HTincl_LO_2017.root");  /*this is the histo with qcd weights*/
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

    if( Z_gen_pt>150 && Z_gen_pt >=(binCenter_qcd - (0.5*binWidth_qcd)) && Z_gen_pt < (binCenter_qcd + (0.5*binWidth_qcd))  ){
      k_qcd = k_qcd_histo->GetBinContent(ji);
      k_qcd_up = k_qcd + 0.05*k_qcd;
      k_qcd_down = k_qcd - 0.05*k_qcd;
    }
  }*/
  /* here we write the k_ewk */
  k_ewk =1;
  int Nbins_ewk = k_ewk_histo ->GetNbinsX(); double binWidth_ewk=0;
 /* for (int jj=1; jj<= Nbins_ewk; jj++){
    binCenter_ewk= k_ewk_histo->GetXaxis()->GetBinCenter(jj);
    binWidth_ewk= k_ewk_histo->GetXaxis()->GetBinWidth(jj);

    if(Z_gen_pt >=(binCenter_ewk - (0.5*binWidth_ewk)) && Z_gen_pt < (binCenter_ewk + (0.5*binWidth_ewk)) ){
      k_ewk = k_ewk_histo->GetBinContent(jj);
    }
  }*/

  /*end implementation of k-factor. The k-factors are then put in the weights for each event:   wg = lumi*lumi_wgt*lepsf_evt*k_ewk*k_qcd;*/
  /************************************************************/

 wg = lumi * lumi_wgt * lepsf_evt * PUWeight*k_qcd*k_ewk;
 wg_SFu = lumi * lumi_wgt * lepsf_evt_u * PUWeight*k_qcd*k_ewk;  
 wg_SFd = lumi * lumi_wgt * lepsf_evt_d * PUWeight*k_qcd*k_ewk;
 wg_PUu = lumi * lumi_wgt * lepsf_evt * MinBiasUpWeight*k_qcd*k_ewk;
 wg_PUd = lumi * lumi_wgt * lepsf_evt * MinBiasDownWeight*k_qcd*k_ewk;
 wg_KqcdUp = lumi * lumi_wgt * lepsf_evt * PUWeight * k_ewk*k_qcd_up;
 wg_KqcdDown = lumi * lumi_wgt * lepsf_evt * PUWeight * k_ewk*k_qcd_down;
 

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
 HTevent = jet_tot_pt;
         
 if (HLT_Mu50==1 || HLT_TkMu100==1 || HLT_OldMu100==1 ) HLT_Mu = 1;
 
 if (Muon_pt_tunePbt_Roc->size() > 1 && numOfHighptMu==2 && numOfVetoEle == 0 && numOfBoostedJets>=1){

  Muon1.SetPtEtaPhiM(Muon_pt_tunePbt_Roc->at(0), Muon_eta->at(0), Muon_phi->at(0),0.1056583745);
  Muon2.SetPtEtaPhiM(Muon_pt_tunePbt_Roc->at(1), Muon_eta->at(1), Muon_phi->at(1),0.1056583745);
/* BE CAREFUL ON THE WAY TO COMPUTE THE INVARIANT MASS!*/
  Muon1_Roc.SetPtEtaPhiE(Muon_pt_tunePbt_Roc->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));
  Muon2_Roc.SetPtEtaPhiE(Muon_pt_tunePbt_Roc->at(1), Muon_eta->at(1), Muon_phi->at(1),Muon_energy->at(1));

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

   BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
   BoostJet_JESup.SetPtEtaPhiE(BoostedJet_pt->at(1), BoostedJet_eta->at(1), BoostedJet_phi->at(1),BoostedJet_energy->at(1));
   BoostJet_JESdown.SetPtEtaPhiE(BoostedJet_pt->at(2), BoostedJet_eta->at(2), BoostedJet_phi->at(2),BoostedJet_energy->at(2));
   BoostJet_JERup.SetPtEtaPhiE(BoostedJet_pt->at(3), BoostedJet_eta->at(3), BoostedJet_phi->at(3),BoostedJet_energy->at(3));
   BoostJet_JERdown.SetPtEtaPhiE(BoostedJet_pt->at(4), BoostedJet_eta->at(4), BoostedJet_phi->at(4),BoostedJet_energy->at(4));
  
    if (HLT_Mu == 1 && Muon1_PtResoUp.Pt() > 150 && Muon2_PtResoUp.Pt() > 100 && fabs(Muon1_PtResoUp.Eta())<2.4 && fabs(Muon2_PtResoUp.Eta())<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1_PtResoUp+Muon2_PtResoUp).M() > 300){
    DY_mumujj_2018_PtReso2Up->Fill((Muon1_PtResoUp+Muon2_PtResoUp+BoostJet).M(), wg);
   }

   if (HLT_Mu == 1 && Muon1.Pt() > 150 && Muon2.Pt() > 100 && fabs(Muon1.Eta())<2.4 && fabs(Muon2.Eta())<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1+Muon2).M() > 300){
 
    if (Muon_charge->at(0)*Muon_charge->at(1) == 1) DY_mumujj_SS->Fill((Muon1+Muon2+BoostJet).M(), wg);
   if (Muon_charge->at(0)*Muon_charge->at(1) == -1) DY_mumujj_OS->Fill((Muon1+Muon2+BoostJet).M(), wg);
    DY_Mmumu->Fill((Muon1+Muon2).M(),wg );
   DY_HTmumu->Fill(HTevent,wg);
   DY_mumujj_Roc->Fill((Muon1_Roc+Muon2_Roc+BoostJet).M(), wg);
   DY_mumujj->Fill((Muon1+Muon2+BoostJet).M(), wg); 
   if (fabs(Muon1.Eta())< 0.8 && fabs(Muon2.Eta())<0.8){
    DY_Mmumu_BB->Fill((Muon1+Muon2).M(),wg );
    DY_HTmumu_BB->Fill(HTevent,wg);
    DY_mumujj_BB->Fill((Muon1+Muon2+BoostJet).M(), wg);
    DY_mumujj_2018_AlphaRatio_BB->Fill((Muon1+Muon2+BoostJet).M(), wg);
   }
   if ((fabs(Muon1.Eta())< 0.8 && fabs(Muon2.Eta())>0.8) || (fabs(Muon1.Eta())> 0.8 && fabs(Muon2.Eta())<0.8)){
    DY_mumujj_BE->Fill((Muon1+Muon2+BoostJet).M(), wg);
    DY_mumujj_2018_AlphaRatio_BE->Fill((Muon1+Muon2+BoostJet).M(), wg);
    DY_Mmumu_BE->Fill((Muon1+Muon2).M(),wg );
    DY_HTmumu_BE->Fill(HTevent,wg);
   }
   if (fabs(Muon1.Eta())> 0.8 && fabs(Muon2.Eta())>0.8){
    DY_Mmumu_EE->Fill((Muon1+Muon2).M(),wg );
    DY_HTmumu_EE->Fill(HTevent,wg);
    DY_mumujj_EE->Fill((Muon1+Muon2+BoostJet).M(), wg);
    DY_mumujj_2018_AlphaRatio_EE->Fill((Muon1+Muon2+BoostJet).M(), wg);
   }
   NumFatJet_mu->Fill(numOfBoostedJets,wg); 
   DY_mumujj_2018_AlphaRatio->Fill((Muon1+Muon2+BoostJet).M(), wg);
   DY_mumujj_2018_AlphaRatioUp->Fill((Muon1+Muon2+BoostJet).M(), wg);
   DY_mumujj_2018_AlphaRatioDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
   DY_mumujj_2018_SFUp->Fill((Muon1+Muon2+BoostJet).M(), wg_SFu);
   DY_mumujj_2018_SFDown->Fill((Muon1+Muon2+BoostJet).M(), wg_SFd);
   DY_mumujj_2018_PUUp->Fill((Muon1+Muon2+BoostJet).M(), wg_PUu);
   DY_mumujj_2018_PUDown->Fill((Muon1+Muon2+BoostJet).M(), wg_PUd);
   if ((Muon1_PtResoUp+Muon2_PtResoUp).M() >300)  DY_mumujj_2018_PtResoUp->Fill((Muon1_PtResoUp+Muon2_PtResoUp+BoostJet).M(), wg);
   DY_mumujj_2018_PtResoDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
   DY_mumujj_2018_PtReso2Down->Fill((Muon1+Muon2+BoostJet).M(), wg);
   DY_mumujj_2018_KqcdUp->Fill((Muon1+Muon2+BoostJet).M(),wg_KqcdUp);
   DY_mumujj_2018_KqcdDown->Fill((Muon1+Muon2+BoostJet).M(),wg_KqcdDown);
   if(centralJesJer->at(0)==1)DY_mumujj_2018_centralJesJer->Fill((Muon1+Muon2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)DY_mumujj_2018_JesSFUp->Fill((Muon1+Muon2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)DY_mumujj_2018_JesSFDown->Fill((Muon1+Muon2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)DY_mumujj_2018_JerSFUp->Fill((Muon1+Muon2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)DY_mumujj_2018_JerSFDown->Fill((Muon1+Muon2+BoostJet_JERdown).M(), wg);  

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

   if (Muon_charge->at(0)*Muon_charge->at(1) == 1) DY_Zpeak_mumujj_SS->Fill((Muon1+Muon2+BoostJet).M(), wg);
   if (Muon_charge->at(0)*Muon_charge->at(1) == -1) DY_Zpeak_mumujj_OS->Fill((Muon1+Muon2+BoostJet).M(), wg);
   MmumuJ = (Muon1 + Muon2 + BoostJet).M();
   DY_ZpeakMll_mumujj->Fill((Muon1+Muon2).M(), wg); 
   DY_Zpeak_mumujj->Fill((Muon1+Muon2+BoostJet).M(), wg); 
   DY_Zpeak_mumu_pt->Fill((Muon1+Muon2).Pt(), wg);
  if (fabs(Muon1.Eta())< 0.8 && fabs(Muon2.Eta())<0.8){
    DY_ZpeakMll_mumujj_BB->Fill((Muon1+Muon2).M(), wg);
    DY_Zpeak_mumujj_BB->Fill((Muon1+Muon2+BoostJet).M(), wg);
    DY_Zpeak_mumu_pt_BB->Fill((Muon1+Muon2).Pt(), wg);
   }
   if((fabs(Muon1.Eta())< 0.8 && fabs(Muon2.Eta())>0.8) || (fabs(Muon1.Eta())> 0.8 && fabs(Muon2.Eta())<0.8)){
    DY_ZpeakMll_mumujj_BE->Fill((Muon1+Muon2).M(), wg);
    DY_Zpeak_mumujj_BE->Fill((Muon1+Muon2+BoostJet).M(), wg);
    DY_Zpeak_mumu_pt_BE->Fill((Muon1+Muon2).Pt(), wg);
   }
   if(fabs(Muon1.Eta())> 0.8 && fabs(Muon2.Eta())>0.8){
    DY_ZpeakMll_mumujj_EE->Fill((Muon1+Muon2).M(), wg);
    DY_Zpeak_mumujj_EE->Fill((Muon1+Muon2+BoostJet).M(), wg);
    DY_Zpeak_mumu_pt_EE->Fill((Muon1+Muon2).Pt(), wg);
   }
  }

    //DY cr Mll in 150-300 GeV
   if (HLT_Mu == 1 && Muon1_PtResoUp.Pt() > 150 && Muon2_PtResoUp.Pt() > 100 && fabs(Muon1_PtResoUp.Eta())<2.4 && fabs(Muon2_PtResoUp.Eta())<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1_PtResoUp+Muon2_PtResoUp).M() > 150 && (Muon1_PtResoUp+Muon2_PtResoUp).M() < 300){
   DY_DYcr_mumujj_2018_PtReso2Up->Fill((Muon1_PtResoUp+Muon2_PtResoUp+BoostJet).M(), wg);
  }

  if (HLT_Mu == 1 && Muon1.Pt() > 150 && Muon2.Pt() > 100 && fabs(Muon1.Eta())<2.4 && fabs(Muon2.Eta())<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1+Muon2).M() > 150 && (Muon1+Muon2).M() < 300){

  if (Muon_charge->at(0)*Muon_charge->at(1) == 1) DY_DYcr_mumujj_SS->Fill((Muon1+Muon2+BoostJet).M(), wg);
   if (Muon_charge->at(0)*Muon_charge->at(1) == -1) DY_DYcr_mumujj_OS->Fill((Muon1+Muon2+BoostJet).M(), wg);
  Mmumu_DYcr->Fill((Muon1+Muon2).M(), wg);
  DY_DYcr_mumujj->Fill((Muon1+Muon2+BoostJet).M(), wg); 
  if (fabs(Muon1.Eta())< 0.8 && fabs(Muon2.Eta())<0.8){
    Mmumu_DYcr_BB->Fill((Muon1+Muon2).M(), wg);
    DY_DYcr_mumujj_BB->Fill((Muon1+Muon2+BoostJet).M(), wg);
    DY_DYcr_mumujj_2018_AlphaRatio_BB->Fill((Muon1+Muon2+BoostJet).M(), wg);
   }
   if((fabs(Muon1.Eta())< 0.8 && fabs(Muon2.Eta())>0.8) || (fabs(Muon1.Eta())> 0.8 && fabs(Muon2.Eta())<0.8)){
    Mmumu_DYcr_BE->Fill((Muon1+Muon2).M(), wg);
    DY_DYcr_mumujj_BE->Fill((Muon1+Muon2+BoostJet).M(), wg);
    DY_DYcr_mumujj_2018_AlphaRatio_BE->Fill((Muon1+Muon2+BoostJet).M(), wg);
   }
   if(fabs(Muon1.Eta())> 0.8 && fabs(Muon2.Eta())>0.8){
    Mmumu_DYcr_EE->Fill((Muon1+Muon2).M(), wg);
    DY_DYcr_mumujj_EE->Fill((Muon1+Muon2+BoostJet).M(), wg);
    DY_DYcr_mumujj_2018_AlphaRatio_EE->Fill((Muon1+Muon2+BoostJet).M(), wg);
   }
  DY_DYcr_mumujj_2018_AlphaRatio->Fill((Muon1+Muon2+BoostJet).M(), wg);
  DY_DYcr_mumujj_2018_AlphaRatioUp->Fill((Muon1+Muon2+BoostJet).M(), wg);
  DY_DYcr_mumujj_2018_AlphaRatioDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
  DY_DYcr_mumujj_2018_SFUp->Fill((Muon1+Muon2+BoostJet).M(), wg_SFu);
  DY_DYcr_mumujj_2018_SFDown->Fill((Muon1+Muon2+BoostJet).M(), wg_SFd);
  DY_DYcr_mumujj_2018_PUUp->Fill((Muon1+Muon2+BoostJet).M(), wg_PUu);
  DY_DYcr_mumujj_2018_PUDown->Fill((Muon1+Muon2+BoostJet).M(), wg_PUd);
  DY_DYcr_mumujj_2018_PtResoUp->Fill((Muon1_PtResoUp+Muon2_PtResoUp+BoostJet).M(), wg);
  DY_DYcr_mumujj_2018_PtResoDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
  DY_DYcr_mumujj_2018_PtReso2Down->Fill((Muon1+Muon2+BoostJet).M(), wg);
  DY_DYcr_mumujj_2018_KqcdUp->Fill((Muon1+Muon2+BoostJet).M(),wg_KqcdUp);
  DY_DYcr_mumujj_2018_KqcdDown->Fill((Muon1+Muon2+BoostJet).M(),wg_KqcdDown);
  if(centralJesJer->at(0)==1)DY_DYcr_mumujj_centralJesJer->Fill((Muon1+Muon2+BoostJet).M(), wg);
  if(JesSFup->at(1)==1)DY_DYcr_mumujj_2018_JesSFUp->Fill((Muon1+Muon2+BoostJet_JESup).M(), wg);
  if(JesSFdown->at(2)==1)DY_DYcr_mumujj_2018_JesSFDown->Fill((Muon1+Muon2+BoostJet_JESdown).M(), wg);
  if(JerSFup->at(3)==1)DY_DYcr_mumujj_2018_JerSFUp->Fill((Muon1+Muon2+BoostJet_JERup).M(), wg);
  if(JerSFdown->at(4)==1)DY_DYcr_mumujj_2018_JerSFDown->Fill((Muon1+Muon2+BoostJet_JERdown).M(), wg);  
  }

 } // 2 muons
 
 if (patElectron_pt->size() > 1 && numOfHighptEle==2 && numOfLooseMu==0 && numOfBoostedJets>=1){
   Electron1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   Electron2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energy->at(1));
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
  wg = lumi * lumi_wgt * lepsf_evt * PUWeight*k_qcd*k_ewk;  
  wg_SFu = lumi * lumi_wgt * lepsf_evt_u * PUWeight*k_qcd*k_ewk;  
  wg_SFd = lumi * lumi_wgt * lepsf_evt_d * PUWeight*k_qcd*k_ewk; 
  /*bug fixing part end*/


  if (HLT_Ele == 1 && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190 && (Electron1+Electron2).M() > 300){
  
   if (patElectron_charge->at(0)*patElectron_charge->at(1) == 1) DY_eejj_SS->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if (patElectron_charge->at(0)*patElectron_charge->at(1) == -1) DY_eejj_OS->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_Mee->Fill((Electron1+Electron2).M(),wg );
   DY_HTee->Fill(HTevent,wg);
   NumFatJet->Fill(numOfBoostedJets,wg); 
   if (fabs(patElectron_eta->at(1))< 0.8 && fabs(patElectron_eta->at(0))<0.8){
    DY_eejj_BB->Fill((Electron1+Electron2+BoostJet).M(), wg);
    DY_eejj_2018_AlphaRatio_BB->Fill((Electron1+Electron2+BoostJet).M(), wg);
    DY_Mee_BB->Fill((Electron1+Electron2).M(),wg );
    DY_HTee_BB->Fill(HTevent,wg);
   }
   if((fabs(patElectron_eta->at(1))< 0.8 && fabs(patElectron_eta->at(0))>0.8) ||(fabs(patElectron_eta->at(1))>0.8 && fabs(patElectron_eta->at(0))<0.8) ){
    DY_eejj_BE->Fill((Electron1+Electron2+BoostJet).M(), wg);
    DY_eejj_2018_AlphaRatio_BE->Fill((Electron1+Electron2+BoostJet).M(), wg);
    DY_Mee_BE->Fill((Electron1+Electron2).M(),wg );
    DY_HTee_BE->Fill(HTevent,wg);
   }
   if (fabs(patElectron_eta->at(1))> 0.8 && fabs(patElectron_eta->at(0))>0.8){
    DY_eejj_EE->Fill((Electron1+Electron2+BoostJet).M(), wg);
    DY_eejj_2018_AlphaRatio_EE->Fill((Electron1+Electron2+BoostJet).M(), wg);
    DY_Mee_EE->Fill((Electron1+Electron2).M(),wg );
    DY_HTee_EE->Fill(HTevent,wg);
   }
   DY_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_eejj_2018_AlphaRatio->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_eejj_2018_AlphaRatioUp->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_eejj_2018_AlphaRatioDown->Fill((Electron1+Electron2+BoostJet).M(), wg); 
   DY_eejj_2018_SFUp->Fill((Electron1+Electron2+BoostJet).M(), wg_SFu);
   DY_eejj_2018_SFDown->Fill((Electron1+Electron2+BoostJet).M(), wg_SFd);
   DY_eejj_2018_PUUp->Fill((Electron1+Electron2+BoostJet).M(), wg_PUu);
   DY_eejj_2018_PUDown->Fill((Electron1+Electron2+BoostJet).M(), wg_PUd);
   DY_eejj_energyScaleUp->Fill((Ele1_ScaleUp+Ele2_ScaleUp+BoostJet).M(), wg);
   DY_eejj_energyScaleDown->Fill((Ele1_ScaleDown+Ele2_ScaleDown+BoostJet).M(), wg);
   DY_eejj_2018_energySigmaUp->Fill((Ele1_SigmaUp+Ele2_SigmaUp+BoostJet).M(), wg);
   DY_eejj_2018_energySigmaDown->Fill((Ele1_SigmaDown+Ele2_SigmaDown+BoostJet).M(), wg);
   DY_eejj_2018_KqcdUp->Fill((Electron1+Electron2+BoostJet).M(),wg_KqcdUp);
   DY_eejj_2018_KqcdDown->Fill((Electron1+Electron2+BoostJet).M(),wg_KqcdDown);
   if(centralJesJer->at(0)==1)DY_eejj_2018_centralJesJer->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)DY_eejj_2018_JesSFUp->Fill((Electron1+Electron2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)DY_eejj_2018_JesSFDown->Fill((Electron1+Electron2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)DY_eejj_2018_JerSFUp->Fill((Electron1+Electron2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)DY_eejj_2018_JerSFDown->Fill((Electron1+Electron2+BoostJet_JERdown).M(), wg); 
   //cout<< "lepsf_evt"<<lepsf_evt<<endl;
   //cout <<"lepsf_evt_u" << lepsf_evt_u <<endl;
   //cout <<"lepsf_evt_d" << lepsf_evt_d <<endl;
   //cout<< "========"<<endl;

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

   if (patElectron_charge->at(0)*patElectron_charge->at(1) == 1) DY_Zpeak_eejj_SS->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if (patElectron_charge->at(0)*patElectron_charge->at(1) == -1) DY_Zpeak_eejj_OS->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_ZpeakMll_eejj->Fill((Electron1+Electron2).M(), wg);
   DY_Zpeak_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_Zpeak_ee_pt->Fill((Electron1+Electron2).Pt(), wg);
   if (fabs(patElectron_eta->at(1))< 0.8 && fabs(patElectron_eta->at(0))<0.8){
     DY_ZpeakMll_eejj_BB->Fill((Electron1+Electron2).M(), wg);
     DY_Zpeak_eejj_BB->Fill((Electron1+Electron2+BoostJet).M(), wg);
     DY_Zpeak_ee_pt_BB->Fill((Electron1+Electron2).Pt(), wg);
    }
    if((fabs(patElectron_eta->at(1))< 0.8 && fabs(patElectron_eta->at(0))>0.8) ||(fabs(patElectron_eta->at(1))>0.8 && fabs(patElectron_eta->at(0))<0.8) ){
     DY_ZpeakMll_eejj_BE->Fill((Electron1+Electron2).M(), wg);
     DY_Zpeak_eejj_BE->Fill((Electron1+Electron2+BoostJet).M(), wg);
     DY_Zpeak_ee_pt_BE->Fill((Electron1+Electron2).Pt(), wg);
    }
    if (fabs(patElectron_eta->at(1))> 0.8 && fabs(patElectron_eta->at(0))>0.8){
     DY_ZpeakMll_eejj_EE->Fill((Electron1+Electron2).M(), wg);
     DY_Zpeak_eejj_EE->Fill((Electron1+Electron2+BoostJet).M(), wg);
     DY_Zpeak_ee_pt_EE->Fill((Electron1+Electron2).Pt(), wg);
    }
  }

     //DY cr 150-300 GeV
   if (HLT_Ele == 1 && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190 && (Electron1+Electron2).M() >150 && (Electron1+Electron2).M() < 300){
  
   if (patElectron_charge->at(0)*patElectron_charge->at(1) == 1) DY_DYcr_eejj_SS->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if (patElectron_charge->at(0)*patElectron_charge->at(1) == -1) DY_DYcr_eejj_OS->Fill((Electron1+Electron2+BoostJet).M(), wg);
   Mee_DYcr->Fill((Electron1+Electron2).M(), wg);
   DY_DYcr_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if (fabs(patElectron_eta->at(1))< 0.8 && fabs(patElectron_eta->at(0))<0.8){
    Mee_DYcr_BB->Fill((Electron1+Electron2).M(), wg);
    DY_DYcr_eejj_BB->Fill((Electron1+Electron2+BoostJet).M(), wg);
    DY_DYcr_eejj_2018_AlphaRatio_BB->Fill((Electron1+Electron2+BoostJet).M(), wg);
   }
   if((fabs(patElectron_eta->at(1))< 0.8 && fabs(patElectron_eta->at(0))>0.8) ||(fabs(patElectron_eta->at(1))>0.8 && fabs(patElectron_eta->at(0))<0.8) ){
    Mee_DYcr_BE->Fill((Electron1+Electron2).M(), wg);
    DY_DYcr_eejj_BE->Fill((Electron1+Electron2+BoostJet).M(), wg);
    DY_DYcr_eejj_2018_AlphaRatio_BE->Fill((Electron1+Electron2+BoostJet).M(), wg);
   }
   if (fabs(patElectron_eta->at(1))> 0.8 && fabs(patElectron_eta->at(0))>0.8){
    Mee_DYcr_EE->Fill((Electron1+Electron2).M(), wg);
    DY_DYcr_eejj_EE->Fill((Electron1+Electron2+BoostJet).M(), wg);
    DY_DYcr_eejj_2018_AlphaRatio_EE->Fill((Electron1+Electron2+BoostJet).M(), wg);
   }
   DY_DYcr_eejj_2018_AlphaRatio->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_DYcr_eejj_2018_AlphaRatioUp->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_DYcr_eejj_2018_AlphaRatioDown->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_DYcr_eejj_2018_SFUp->Fill((Electron1+Electron2+BoostJet).M(), wg_SFu);
   DY_DYcr_eejj_2018_SFDown->Fill((Electron1+Electron2+BoostJet).M(), wg_SFd);
   DY_DYcr_eejj_2018_PUUp->Fill((Electron1+Electron2+BoostJet).M(), wg_PUu);
   DY_DYcr_eejj_2018_PUDown->Fill((Electron1+Electron2+BoostJet).M(), wg_PUd);
   DY_DYcr_eejj_energyScaleUp->Fill((Ele1_ScaleUp+Ele2_ScaleUp+BoostJet).M(), wg);
   DY_DYcr_eejj_energyScaleDown->Fill((Ele1_ScaleDown+Ele2_ScaleDown+BoostJet).M(), wg);
   DY_DYcr_eejj_2018_energySigmaUp->Fill((Ele1_SigmaUp+Ele2_SigmaUp+BoostJet).M(), wg);
   DY_DYcr_eejj_2018_energySigmaDown->Fill((Ele1_SigmaDown+Ele2_SigmaDown+BoostJet).M(), wg);
   DY_DYcr_eejj_2018_KqcdUp->Fill((Electron1+Electron2+BoostJet).M(),wg_KqcdUp);
   DY_DYcr_eejj_2018_KqcdDown->Fill((Electron1+Electron2+BoostJet).M(),wg_KqcdDown);
   if(centralJesJer->at(0)==1)DY_DYcr_eejj_centralJesJer->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)DY_DYcr_eejj_2018_JesSFUp->Fill((Electron1+Electron2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)DY_DYcr_eejj_2018_JesSFDown->Fill((Electron1+Electron2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)DY_DYcr_eejj_2018_JerSFUp->Fill((Electron1+Electron2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)DY_DYcr_eejj_2018_JerSFDown->Fill((Electron1+Electron2+BoostJet_JERdown).M(), wg); 
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
     DY_TTtWcr_llJ_2018_PtReso2Up->Fill((Muon_PtResoUp+SubLeadLep+BoostJet).M(), wg);
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
     DY_TTtWcr_llJ_2018_PtReso2Up->Fill((Muon_PtResoUp+LeadLep+BoostJet).M(),wg);
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


   if (HLT_Mu == 1 && LeadLep.Pt() > 150 && SubLeadLep.Pt() > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(patElectron_eta->at(0))<2.4
     && BoostedJet_pt->at(0) > 190 && (LeadLep+SubLeadLep).M() > 300 ){
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
    if (Muon_charge->at(0)*patElectron_charge->at(0) == 1) DY_TTtWcr_llJ_SS->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if (Muon_charge->at(0)*patElectron_charge->at(0) == -1) DY_TTtWcr_llJ_OS->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
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
    DY_TTtWcr_llJ_2018_AlphaRatio->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2018_AlphaRatioUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2018_AlphaRatioDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2018_SFUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_SFu);
    DY_TTtWcr_llJ_2018_SFDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_SFd);
    DY_TTtWcr_llJ_2018_PUUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_PUu);
    DY_TTtWcr_llJ_2018_PUDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_PUd);
    DY_TTtWcr_HTevent->Fill(HTevent, wg);
    if ((Muon_PtResoUp+SubLeadLep).M() >300) DY_TTtWcr_llJ_2018_PtResoUp->Fill((Muon_PtResoUp+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2018_PtResoDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2018_PtReso2Down->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_energyScaleUp->Fill((Ele_ScaleUp+LeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_energyScaleDown->Fill((Ele_ScaleDown+LeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2018_energySigmaUp->Fill((Ele_SigmaUp+LeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2018_energySigmaDown->Fill((Ele_SigmaDown+LeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2018_KqcdUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_KqcdUp);
    DY_TTtWcr_llJ_2018_KqcdDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_KqcdDown);
    if(centralJesJer->at(0)==1)DY_TTtWcr_llJ_centralJesJer->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if(JesSFup->at(1)==1)DY_TTtWcr_llJ_2018_JesSFUp->Fill((LeadLep+SubLeadLep+BoostJet_JESup).M(), wg);
    if(JesSFdown->at(2)==1)DY_TTtWcr_llJ_2018_JesSFDown->Fill((LeadLep+SubLeadLep+BoostJet_JESdown).M(), wg);
    if(JerSFup->at(3)==1)DY_TTtWcr_llJ_2018_JerSFUp->Fill((LeadLep+SubLeadLep+BoostJet_JERup).M(), wg);
    if(JerSFdown->at(4)==1)DY_TTtWcr_llJ_2018_JerSFDown->Fill((LeadLep+SubLeadLep+BoostJet_JERdown).M(), wg); 

   }
  }
 }

 else {

   LeadLep.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   SubLeadLep.SetPtEtaPhiM(Muon_pt_tunePbt_Roc->at(0), Muon_eta->at(0), Muon_phi->at(0),0.1056583745);
   energy_corr0= patElectron_ecalTrkEnergyPostCorr->at(0) / patElectron_energy->at(0) ;
   LeadLep = LeadLep*energy_corr0;

   extra_smearing_1 = extraSmearingSigma(SubLeadLep.Eta(), SubLeadLep.P());
   Muon1_px_smearing=SubLeadLep.Px()*gRandom->Gaus(1,extra_smearing_1);
   Muon1_py_smearing=SubLeadLep.Py()*gRandom->Gaus(1,extra_smearing_1);
   Muon1_pz_smearing=SubLeadLep.Pz()*gRandom->Gaus(1,extra_smearing_1);

   P1_smear.SetXYZ(Muon1_px_smearing, Muon1_py_smearing, Muon1_pz_smearing);
   Muon_PtResoUp.SetPtEtaPhiM(P1_smear.Pt(), P1_smear.Eta(), P1_smear.Phi(),0.1056583745 );
   Muon_PtResoDown.SetPtEtaPhiM(P1_smear.Pt(), P1_smear.Eta(), P1_smear.Phi(),0.1056583745 );


   if (HLT_Ele == 1 & LeadLep.Pt() > 150 && SubLeadLep.Pt() > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190 && (LeadLep+SubLeadLep).M() > 300){

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
    if (Muon_charge->at(0)*patElectron_charge->at(0) == 1) DY_TTtWcr_llJ_SS->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if (Muon_charge->at(0)*patElectron_charge->at(0) == -1) DY_TTtWcr_llJ_OS->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
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
    DY_TTtWcr_llJ_2018_AlphaRatio->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2018_AlphaRatioUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2018_AlphaRatioDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2018_SFUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_SFu);
    DY_TTtWcr_llJ_2018_SFDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_SFd);
    DY_TTtWcr_llJ_2018_PUUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_PUu);
    DY_TTtWcr_llJ_2018_PUDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_PUd);
    DY_TTtWcr_HTevent->Fill(HTevent, wg); 
    if ((Muon_PtResoUp+LeadLep).M() >300) DY_TTtWcr_llJ_2018_PtResoUp->Fill((Muon_PtResoUp+LeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2018_PtResoDown->Fill((SubLeadLep+LeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2018_PtReso2Down->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_energyScaleUp->Fill((Ele_ScaleUp+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_energyScaleDown->Fill((Ele_ScaleDown+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2018_energySigmaUp->Fill((Ele_SigmaUp+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2018_energySigmaDown->Fill((Ele_SigmaDown+SubLeadLep+BoostJet).M(),wg);
    DY_TTtWcr_llJ_2018_KqcdUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_KqcdUp);
    DY_TTtWcr_llJ_2018_KqcdDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_KqcdDown);
    if(centralJesJer->at(0)==1)DY_TTtWcr_llJ_centralJesJer->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if(JesSFup->at(1)==1)DY_TTtWcr_llJ_2018_JesSFUp->Fill((LeadLep+SubLeadLep+BoostJet_JESup).M(), wg);
    if(JesSFdown->at(2)==1)DY_TTtWcr_llJ_2018_JesSFDown->Fill((LeadLep+SubLeadLep+BoostJet_JESdown).M(), wg);
    if(JerSFup->at(3)==1)DY_TTtWcr_llJ_2018_JerSFUp->Fill((LeadLep+SubLeadLep+BoostJet_JERup).M(), wg);
    if(JerSFdown->at(4)==1)DY_TTtWcr_llJ_2018_JerSFDown->Fill((LeadLep+SubLeadLep+BoostJet_JERdown).M(), wg); 

    }
   }
  }


 } //TTtW CR 

}


/**** adding the Alpha ratio and it's uncertainty*******/
/* alpha ratio and it's statistical error, bin per bin*/

// DY HT binned +inclusive  
const double Alpha_ele[9] = {1,1,1.07,0.97,1.00,0.92,0.98,1.07};
const double dAlpha_ele[9] ={0,0,0.04,0.02,0.02,0.02,0.05,0.12};

const double Alpha_mu[9] = {1,1,1.03,1.00,1.00,0.98,0.96,1.10}; 
const double dAlpha_mu[9] ={0,0,0.04,0.02,0.02,0.02,0.04,0.09};

/* old DY inclusive
const double Alpha_ele[9] = {1,1,0.83, 0.81, 0.82, 0.76, 1.02, 0.87, 0};
const double dAlpha_ele[9] ={0,0,0.07, 0.03, 0.03, 0.03, 0.01, 0.2, 0};

const double Alpha_mu[9] = {1,1,0.94, 0.80, 0.76, 0.80, 0.77, 0.89,0 }; 
const double dAlpha_mu[9] ={0,0,0.07, 0.02, 0.03, 0.03, 0.06, 0.14,0 };*/


for (Int_t j=1;j<=8;j++) {
//electron channel histograms
    double alpha_ele=Alpha_ele[j-1];
    double dalpha_ele=dAlpha_ele[j-1];

    DY_eejj_SS->SetBinContent(j, DY_eejj_SS->GetBinContent(j) * alpha_ele);
    DY_eejj_OS->SetBinContent(j, DY_eejj_OS->GetBinContent(j) * alpha_ele);    
    DY_eejj_2018_AlphaRatio->SetBinContent(j, DY_eejj_2018_AlphaRatio->GetBinContent(j) * alpha_ele);
    DY_eejj_2018_AlphaRatio_BB->SetBinContent(j, DY_eejj_2018_AlphaRatio_BB->GetBinContent(j) * alpha_ele);
    DY_eejj_2018_AlphaRatio_BE->SetBinContent(j, DY_eejj_2018_AlphaRatio_BE->GetBinContent(j) * alpha_ele);
    DY_eejj_2018_AlphaRatio_EE->SetBinContent(j, DY_eejj_2018_AlphaRatio_EE->GetBinContent(j) * alpha_ele); 
    DY_eejj_2018_AlphaRatioUp->SetBinContent(j, DY_eejj_2018_AlphaRatioUp->GetBinContent(j) * (alpha_ele+dalpha_ele));
    DY_eejj_2018_AlphaRatioDown->SetBinContent(j, DY_eejj_2018_AlphaRatioDown->GetBinContent(j) * (alpha_ele-dalpha_ele));
    DY_eejj_2018_SFUp->SetBinContent(j, DY_eejj_2018_SFUp->GetBinContent(j) * alpha_ele);
    DY_eejj_2018_SFDown->SetBinContent(j, DY_eejj_2018_SFDown->GetBinContent(j) * alpha_ele);
    DY_eejj_2018_PUUp->SetBinContent(j, DY_eejj_2018_PUUp->GetBinContent(j) * alpha_ele);
    DY_eejj_2018_PUDown->SetBinContent(j, DY_eejj_2018_PUDown->GetBinContent(j) * alpha_ele);
    DY_eejj_energyScaleUp->SetBinContent(j, DY_eejj_energyScaleUp->GetBinContent(j) * alpha_ele);
    DY_eejj_energyScaleDown->SetBinContent(j, DY_eejj_energyScaleDown->GetBinContent(j) * alpha_ele);
    DY_eejj_2018_energySigmaUp->SetBinContent(j, DY_eejj_2018_energySigmaUp->GetBinContent(j) * alpha_ele);
    DY_eejj_2018_energySigmaDown->SetBinContent(j, DY_eejj_2018_energySigmaDown->GetBinContent(j) * alpha_ele);
    DY_eejj_2018_centralJesJer->SetBinContent(j, DY_eejj_2018_centralJesJer->GetBinContent(j) * alpha_ele);
    DY_eejj_2018_JesSFUp->SetBinContent(j, DY_eejj_2018_JesSFUp->GetBinContent(j) * alpha_ele);
    DY_eejj_2018_JesSFDown->SetBinContent(j, DY_eejj_2018_JesSFDown->GetBinContent(j) * alpha_ele);
    DY_eejj_2018_JerSFUp->SetBinContent(j, DY_eejj_2018_JerSFUp->GetBinContent(j) * alpha_ele);
    DY_eejj_2018_JerSFDown->SetBinContent(j, DY_eejj_2018_JerSFDown->GetBinContent(j) * alpha_ele);
    DY_eejj_2018_KqcdUp->SetBinContent(j, DY_eejj_2018_KqcdUp->GetBinContent(j) * alpha_ele);
    DY_eejj_2018_KqcdDown->SetBinContent(j, DY_eejj_2018_KqcdDown->GetBinContent(j) * alpha_ele);
  // debugging ele
 // cout<< DY_eejj_2018_AlphaRatio->GetBinContenttent(j)/DY_eejj->GetBinContent(j) <<endl;
 // cout<< DY_eejj_2018_AlphaRatioDown->GetBinContent(j)/DY_eejj->GetBinContent(j) <<endl;
 // cout<<"================"<<endl; 
     //DY CR 150-300 GeV
    DY_DYcr_eejj_SS->SetBinContent(j, DY_DYcr_eejj_SS->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_OS->SetBinContent(j, DY_DYcr_eejj_OS->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2018_AlphaRatio->SetBinContent(j, DY_DYcr_eejj_2018_AlphaRatio->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2018_AlphaRatio_BB->SetBinContent(j, DY_DYcr_eejj_2018_AlphaRatio_BB->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2018_AlphaRatio_BE->SetBinContent(j, DY_DYcr_eejj_2018_AlphaRatio_BE->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2018_AlphaRatio_EE->SetBinContent(j, DY_DYcr_eejj_2018_AlphaRatio_EE->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2018_AlphaRatioUp->SetBinContent(j, DY_DYcr_eejj_2018_AlphaRatioUp->GetBinContent(j) * (alpha_ele+dalpha_ele));
    DY_DYcr_eejj_2018_AlphaRatioDown->SetBinContent(j, DY_DYcr_eejj_2018_AlphaRatioDown->GetBinContent(j) * (alpha_ele-dalpha_ele));
    DY_DYcr_eejj_2018_SFUp->SetBinContent(j, DY_DYcr_eejj_2018_SFUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2018_SFDown->SetBinContent(j, DY_DYcr_eejj_2018_SFDown->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2018_PUUp->SetBinContent(j, DY_DYcr_eejj_2018_PUUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2018_PUDown->SetBinContent(j, DY_DYcr_eejj_2018_PUDown->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_energyScaleUp->SetBinContent(j, DY_DYcr_eejj_energyScaleUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_energyScaleDown->SetBinContent(j, DY_DYcr_eejj_energyScaleDown->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2018_energySigmaUp->SetBinContent(j, DY_DYcr_eejj_2018_energySigmaUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2018_energySigmaDown->SetBinContent(j, DY_DYcr_eejj_2018_energySigmaDown->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_centralJesJer->SetBinContent(j, DY_DYcr_eejj_centralJesJer->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2018_JesSFUp->SetBinContent(j, DY_DYcr_eejj_2018_JesSFUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2018_JesSFDown->SetBinContent(j, DY_DYcr_eejj_2018_JesSFDown->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2018_JerSFUp->SetBinContent(j, DY_DYcr_eejj_2018_JerSFUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2018_JerSFDown->SetBinContent(j, DY_DYcr_eejj_2018_JerSFDown->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2018_KqcdUp->SetBinContent(j, DY_DYcr_eejj_2018_KqcdUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2018_KqcdDown->SetBinContent(j, DY_DYcr_eejj_2018_KqcdDown->GetBinContent(j) * alpha_ele);

// muon channel histograms
    double alpha_mu=Alpha_mu[j-1];
    double dalpha_mu=dAlpha_mu[j-1];
    DY_mumujj_SS->SetBinContent(j, DY_mumujj_SS->GetBinContent(j) * alpha_mu);
    DY_mumujj_OS->SetBinContent(j, DY_mumujj_OS->GetBinContent(j) * alpha_mu);
    DY_mumujj_2018_AlphaRatio->SetBinContent(j, DY_mumujj_2018_AlphaRatio->GetBinContent(j) * alpha_mu);
    DY_mumujj_2018_AlphaRatio_BB->SetBinContent(j, DY_mumujj_2018_AlphaRatio_BB->GetBinContent(j) * alpha_mu);
    DY_mumujj_2018_AlphaRatio_BE->SetBinContent(j, DY_mumujj_2018_AlphaRatio_BE->GetBinContent(j) * alpha_mu);
    DY_mumujj_2018_AlphaRatio_EE->SetBinContent(j, DY_mumujj_2018_AlphaRatio_EE->GetBinContent(j) * alpha_mu);
    DY_mumujj_2018_AlphaRatioUp->SetBinContent(j, DY_mumujj_2018_AlphaRatioUp->GetBinContent(j) * (alpha_mu+dalpha_mu));
    DY_mumujj_2018_AlphaRatioDown->SetBinContent(j, DY_mumujj_2018_AlphaRatioDown->GetBinContent(j) * (alpha_mu-dalpha_mu));
    DY_mumujj_2018_SFUp->SetBinContent(j, DY_mumujj_2018_SFUp->GetBinContent(j) * alpha_mu);
    DY_mumujj_2018_SFDown->SetBinContent(j, DY_mumujj_2018_SFDown->GetBinContent(j) * alpha_mu);
    DY_mumujj_2018_PUUp->SetBinContent(j, DY_mumujj_2018_PUUp->GetBinContent(j) * alpha_mu);
    DY_mumujj_2018_PUDown->SetBinContent(j, DY_mumujj_2018_PUDown->GetBinContent(j) * alpha_mu);
    DY_mumujj_2018_PtResoUp->SetBinContent(j, DY_mumujj_2018_PtResoUp->GetBinContent(j) * alpha_mu);
    DY_mumujj_2018_PtResoDown->SetBinContent(j, DY_mumujj_2018_PtResoDown->GetBinContent(j) * alpha_mu);
    DY_mumujj_2018_PtReso2Up->SetBinContent(j, DY_mumujj_2018_PtReso2Up->GetBinContent(j) * alpha_mu);
    DY_mumujj_2018_PtReso2Down->SetBinContent(j, DY_mumujj_2018_PtReso2Down->GetBinContent(j) * alpha_mu);
    DY_mumujj_2018_centralJesJer->SetBinContent(j, DY_mumujj_2018_centralJesJer->GetBinContent(j) * alpha_mu);
    DY_mumujj_2018_JesSFUp->SetBinContent(j, DY_mumujj_2018_JesSFUp->GetBinContent(j) * alpha_mu);
    DY_mumujj_2018_JesSFDown->SetBinContent(j, DY_mumujj_2018_JesSFDown->GetBinContent(j) * alpha_mu);
    DY_mumujj_2018_JerSFUp->SetBinContent(j, DY_mumujj_2018_JerSFUp->GetBinContent(j) * alpha_mu);
    DY_mumujj_2018_JerSFDown->SetBinContent(j, DY_mumujj_2018_JerSFDown->GetBinContent(j) * alpha_mu);
    DY_mumujj_2018_KqcdUp->SetBinContent(j, DY_mumujj_2018_KqcdUp->GetBinContent(j) * alpha_mu);
    DY_mumujj_2018_KqcdDown->SetBinContent(j, DY_mumujj_2018_KqcdDown->GetBinContent(j) * alpha_mu);
  // debugging muons
 //cout<< DY_mumujj_2018_AlphaRatio->GetBinContent(j)/DY_mumujj->GetBinContent(j) <<endl;
 // cout<< DY_mumujj_2018_AlphaRatioUp->GetBinContent(j)/DY_mumujj->GetBinContent(j) <<endl;
 // cout<< DY_mumujj_2018_AlphaRatioDown->GetBinContent(j)/DY_mumujj->GetBinContent(j) <<endl;
 // cout<<"================"<<endl; 
 // cout<<"================"<<endl; 
     //DY CR 150-300 GeV
    DY_DYcr_mumujj_SS->SetBinContent(j, DY_DYcr_mumujj_SS->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_OS->SetBinContent(j, DY_DYcr_mumujj_OS->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2018_AlphaRatio->SetBinContent(j, DY_DYcr_mumujj_2018_AlphaRatio->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2018_AlphaRatio_BB->SetBinContent(j, DY_DYcr_mumujj_2018_AlphaRatio_BB->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2018_AlphaRatio_BE->SetBinContent(j, DY_DYcr_mumujj_2018_AlphaRatio_BE->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2018_AlphaRatio_EE->SetBinContent(j, DY_DYcr_mumujj_2018_AlphaRatio_EE->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2018_AlphaRatioUp->SetBinContent(j, DY_DYcr_mumujj_2018_AlphaRatioUp->GetBinContent(j) * (alpha_mu+dalpha_mu));
    DY_DYcr_mumujj_2018_AlphaRatioDown->SetBinContent(j, DY_DYcr_mumujj_2018_AlphaRatioDown->GetBinContent(j) * (alpha_mu-dalpha_mu));
    DY_DYcr_mumujj_2018_SFUp->SetBinContent(j, DY_DYcr_mumujj_2018_SFUp->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2018_SFDown->SetBinContent(j, DY_DYcr_mumujj_2018_SFDown->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2018_PUUp->SetBinContent(j, DY_DYcr_mumujj_2018_PUUp->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2018_PUDown->SetBinContent(j, DY_DYcr_mumujj_2018_PUDown->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2018_PtResoUp->SetBinContent(j, DY_DYcr_mumujj_2018_PtResoUp->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2018_PtResoDown->SetBinContent(j, DY_DYcr_mumujj_2018_PtResoDown->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2018_PtReso2Up->SetBinContent(j, DY_DYcr_mumujj_2018_PtReso2Up->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2018_PtReso2Down->SetBinContent(j, DY_DYcr_mumujj_2018_PtReso2Down->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_centralJesJer->SetBinContent(j, DY_DYcr_mumujj_centralJesJer->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2018_JesSFUp->SetBinContent(j, DY_DYcr_mumujj_2018_JesSFUp->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2018_JesSFDown->SetBinContent(j, DY_DYcr_mumujj_2018_JesSFDown->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2018_JerSFUp->SetBinContent(j, DY_DYcr_mumujj_2018_JerSFUp->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2018_JerSFDown->SetBinContent(j, DY_DYcr_mumujj_2018_JerSFDown->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2018_KqcdUp->SetBinContent(j, DY_DYcr_mumujj_2018_KqcdUp->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2018_KqcdDown->SetBinContent(j, DY_DYcr_mumujj_2018_KqcdDown->GetBinContent(j) * alpha_mu);
}


TFile *f = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/2018_ALL_HOPE/18102021/SR_syst_DY_HTincl_LO_noKfactor_2018.root", "RECREATE");
//TFile *f = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/2018_ALL_HOPE/18102021/SR_syst_DY_HTincl_LO_Kfactor_new_2018.root", "RECREATE");

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
DY_eejj->Write();
DY_eejj_BB->Write();
DY_eejj_BE->Write();
DY_eejj_EE->Write();
DY_eejj_2018_AlphaRatio->Write();
DY_eejj_2018_AlphaRatio_BB->Write();
DY_eejj_2018_AlphaRatio_BE->Write();
DY_eejj_2018_AlphaRatio_EE->Write();
DY_eejj_2018_AlphaRatioUp->Write();
DY_eejj_2018_AlphaRatioDown->Write();
DY_eejj_2018_SFUp->Write();
DY_eejj_2018_SFDown->Write();
DY_eejj_2018_PUUp->Write();
DY_eejj_2018_PUDown->Write();
DY_eejj_2018_centralJesJer->Write();
DY_eejj_2018_JesSFUp->Write();
DY_eejj_2018_JesSFDown->Write();
DY_eejj_2018_JerSFUp->Write();
DY_eejj_2018_JerSFDown->Write();
DY_eejj_energyScaleUp->Write();
DY_eejj_energyScaleDown->Write();
DY_eejj_2018_energySigmaUp->Write();
DY_eejj_2018_energySigmaDown->Write();
DY_eejj_2018_KqcdUp->Write();
DY_eejj_2018_KqcdDown->Write();

DY_mumujj->Write();
DY_mumujj_BB->Write();
DY_mumujj_BE->Write();
DY_mumujj_EE->Write();
DY_mumujj_Roc->Write();
DY_mumujj_2018_AlphaRatio->Write();
DY_mumujj_2018_AlphaRatio_BB->Write();
DY_mumujj_2018_AlphaRatio_BE->Write();
DY_mumujj_2018_AlphaRatio_EE->Write();
DY_mumujj_2018_AlphaRatioUp->Write();
DY_mumujj_2018_AlphaRatioDown->Write();
DY_mumujj_2018_SFUp->Write();
DY_mumujj_2018_SFDown->Write();
DY_mumujj_2018_PUUp->Write();
DY_mumujj_2018_PUDown->Write();
DY_mumujj_2018_centralJesJer->Write();
DY_mumujj_2018_JesSFUp->Write();
DY_mumujj_2018_JesSFDown->Write();
DY_mumujj_2018_JerSFUp->Write();
DY_mumujj_2018_JerSFDown->Write();
DY_mumujj_2018_PtResoUp->Write();
DY_mumujj_2018_PtResoDown->Write();
DY_mumujj_2018_PtReso2Up->Write();
DY_mumujj_2018_PtReso2Down->Write();
DY_mumujj_2018_KqcdUp->Write();
DY_mumujj_2018_KqcdDown->Write();
NumFatJet->Write();
NumFatJet_mu->Write();

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
DY_Zpeak_ee_pt->Write();
DY_Zpeak_ee_pt_BB->Write();
DY_Zpeak_ee_pt_BE->Write();
DY_Zpeak_ee_pt_EE->Write();
DY_Zpeak_mumu_pt->Write();
DY_Zpeak_mumu_pt_BB->Write();
DY_Zpeak_mumu_pt_BE->Write();
DY_Zpeak_mumu_pt_EE->Write();
//DYcr 
DY_DYcr_eejj->Write();
DY_DYcr_eejj_BB->Write();
DY_DYcr_eejj_BE->Write();
DY_DYcr_eejj_EE->Write();
DY_DYcr_eejj_2018_AlphaRatio->Write();
DY_DYcr_eejj_2018_AlphaRatio_BB->Write();
DY_DYcr_eejj_2018_AlphaRatio_BE->Write();
DY_DYcr_eejj_2018_AlphaRatio_EE->Write();
DY_DYcr_eejj_2018_AlphaRatioUp->Write();
DY_DYcr_eejj_2018_AlphaRatioDown->Write();
DY_DYcr_eejj_2018_SFUp->Write();
DY_DYcr_eejj_2018_SFDown->Write();
DY_DYcr_eejj_2018_PUUp->Write();
DY_DYcr_eejj_2018_PUDown->Write();
DY_DYcr_eejj_centralJesJer->Write();
DY_DYcr_eejj_2018_JesSFUp->Write();
DY_DYcr_eejj_2018_JesSFDown->Write();
DY_DYcr_eejj_2018_JerSFUp->Write();
DY_DYcr_eejj_2018_JerSFDown->Write();
DY_DYcr_eejj_energyScaleUp->Write();
DY_DYcr_eejj_energyScaleDown->Write();
DY_DYcr_eejj_2018_energySigmaUp->Write();
DY_DYcr_eejj_2018_energySigmaDown->Write();
DY_DYcr_eejj_2018_KqcdUp->Write();
DY_DYcr_eejj_2018_KqcdDown->Write();
Mee_DYcr->Write();
Mee_DYcr_BB->Write();
Mee_DYcr_BE->Write();
Mee_DYcr_EE->Write();

Mmumu_DYcr->Write();
Mmumu_DYcr_BB->Write();
Mmumu_DYcr_BE->Write();
Mmumu_DYcr_EE->Write();
DY_DYcr_mumujj->Write();
DY_DYcr_mumujj_BB->Write();
DY_DYcr_mumujj_BE->Write();
DY_DYcr_mumujj_EE->Write();
DY_DYcr_mumujj_2018_AlphaRatio->Write();
DY_DYcr_mumujj_2018_AlphaRatio_BB->Write();
DY_DYcr_mumujj_2018_AlphaRatio_BE->Write();
DY_DYcr_mumujj_2018_AlphaRatio_EE->Write();
DY_DYcr_mumujj_2018_AlphaRatioUp->Write();
DY_DYcr_mumujj_2018_AlphaRatioDown->Write();
DY_DYcr_mumujj_2018_SFUp->Write();
DY_DYcr_mumujj_2018_SFDown->Write();
DY_DYcr_mumujj_2018_PUUp->Write();
DY_DYcr_mumujj_2018_PUDown->Write();
DY_DYcr_mumujj_centralJesJer->Write();
DY_DYcr_mumujj_2018_JesSFUp->Write();
DY_DYcr_mumujj_2018_JesSFDown->Write();
DY_DYcr_mumujj_2018_JerSFUp->Write();
DY_DYcr_mumujj_2018_JerSFDown->Write();
DY_DYcr_mumujj_2018_PtResoDown->Write();
DY_DYcr_mumujj_2018_PtResoUp->Write(); 
DY_DYcr_mumujj_2018_PtReso2Down->Write();
DY_DYcr_mumujj_2018_PtReso2Up->Write();
DY_DYcr_mumujj_2018_KqcdUp->Write();
DY_DYcr_mumujj_2018_KqcdDown->Write();

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
DY_TTtWcr_llJ_2018_AlphaRatio->Write();
DY_TTtWcr_llJ_2018_AlphaRatioUp->Write();
DY_TTtWcr_llJ_2018_AlphaRatioDown->Write();
DY_TTtWcr_llJ_2018_SFUp->Write();
DY_TTtWcr_llJ_2018_SFDown->Write();
DY_TTtWcr_llJ_2018_PUUp->Write();
DY_TTtWcr_llJ_2018_PUDown->Write();
DY_TTtWcr_llJ_2018_PtResoUp->Write();
DY_TTtWcr_llJ_2018_PtResoDown->Write();
DY_TTtWcr_llJ_2018_PtReso2Up->Write();
DY_TTtWcr_llJ_2018_PtReso2Down->Write();
DY_TTtWcr_llJ_energyScaleUp->Write();
DY_TTtWcr_llJ_energyScaleDown->Write();
DY_TTtWcr_llJ_2018_energySigmaUp->Write();
DY_TTtWcr_llJ_2018_energySigmaDown->Write();
DY_TTtWcr_llJ_centralJesJer->Write();
DY_TTtWcr_llJ_2018_JesSFUp->Write();
DY_TTtWcr_llJ_2018_JesSFDown->Write();
DY_TTtWcr_llJ_2018_JerSFUp->Write();
DY_TTtWcr_llJ_2018_JerSFDown->Write();
DY_TTtWcr_llJ_2018_KqcdUp->Write();
DY_TTtWcr_llJ_2018_KqcdDown->Write();

f->Write();
f->Close();

}
 
