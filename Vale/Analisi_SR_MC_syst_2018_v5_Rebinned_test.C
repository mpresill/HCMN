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
void Analisi_SR_MC_syst_2018_v5_Rebinned_test(){

TChain *a_ = new TChain("BOOM");

a_->Add("/eos/user/v/vmariani/NTuples/HN_2018/Syst_ALL_HOPE/eejj_L13_M1000_2018.root");
//a_->Add("/eos/user/v/vmariani/NTuples/HN_2018/Syst_ALL_newMuonSF/eejj_L13_M1000_2018.root");

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

//new bin
//const double asymbins[9] = {0,200,400,600,800,1000,1400,2000,10000};


//old bin PRE APPROVAL ONE
const double asymbins[9] = {0,200,400,600,800,1000,1400,2000,10000};

TH1D *NumFatJet = new TH1D ("NumFatJet", "NumFatJet", 20, 0, 20);
TH1D *NumFatJet_mu = new TH1D ("NumFatJet_mu", "NumFatJet_mu", 20, 0, 20);

TH1D *eejj_L13_M1000_mumujj_Roc = new TH1D ("eejj_L13_M1000_mumujj_Roc", "eejj_L13_M1000_mumujj_Roc", 8, asymbins );
TH1D *eejj_L13_M1000_mumujj = new TH1D ("eejj_L13_M1000_mumujj", "eejj_L13_M1000_mumujj", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2018_AlphaRatio = new TH1D ("eejj_L13_M1000_mumujj_2018_AlphaRatio", "eejj_L13_M1000_2018_mumujj_AlphaRatio", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2018_AlphaRatioDown = new TH1D ("eejj_L13_M1000_mumujj_2018_AlphaRatioDown", "eejj_L13_M1000_mumujj_2018_AlphaRatioDown", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2018_AlphaRatioUp = new TH1D ("eejj_L13_M1000_mumujj_2018_AlphaRatioUp", "eejj_L13_M1000_mumujj_2018_AlphaRatioUp", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2018_SFUp = new TH1D ("eejj_L13_M1000_mumujj_2018_SFUp", "eejj_L13_M1000_mumujj_2018_SFUp", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2018_SFDown = new TH1D ("eejj_L13_M1000_mumujj_2018_SFDown", "eejj_L13_M1000_mumujj_2018_SFDown", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2018_PUUp = new TH1D ("eejj_L13_M1000_mumujj_2018_PUUp", "eejj_L13_M1000_mumujj_2018_PUUp", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2018_PUDown = new TH1D ("eejj_L13_M1000_mumujj_2018_PUDown", "eejj_L13_M1000_mumujj_2018_PUDown", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2018_centralJesJer = new TH1D ("eejj_L13_M1000_mumujj_2018_centralJesJer", "eejj_L13_M1000_mumujj_2018_centralJesJer", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2018_JesSFUp = new TH1D ("eejj_L13_M1000_mumujj_2018_JesSFUp", "eejj_L13_M1000_mumujj_2018_JesSFUp", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2018_JesSFDown = new TH1D ("eejj_L13_M1000_mumujj_2018_JesSFDown", "eejj_L13_M1000_mumujj_2018_JesSFDown", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2018_JerSFUp = new TH1D ("eejj_L13_M1000_mumujj_2018_JerSFUp", "eejj_L13_M1000_mumujj_2018_JerSFUp", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2018_JerSFDown = new TH1D ("eejj_L13_M1000_mumujj_2018_JerSFDown", "eejj_L13_M1000_mumujj_2018_JerSFDown", 8, asymbins);
/*TH1D *eejj_L13_M1000_mumujj_2018_PtCorr = new TH1D ("eejj_L13_M1000_mumujj_2018_PtCorr", "eejj_L13_M1000_mumujj_2018_PtCorr", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2018_PtCorrDown = new TH1D ("eejj_L13_M1000_mumujj_2018_PtCorrDown", "eejj_L13_M1000_mumujj_2018_PtCorrDown", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2018_PtCorrUp = new TH1D ("eejj_L13_M1000_mumujj_2018_PtCorrUp", "eejj_L13_M1000_mumujj_2018_PtCorrUp", 8, asymbins);*/
TH1D *eejj_L13_M1000_mumujj_2018_PtResoUp  = new TH1D ("eejj_L13_M1000_mumujj_2018_PtResoUp", "eejj_L13_M1000_mumujj_2018_PtResoUp", 8, asymbins);
TH1D *eejj_L13_M1000_mumujj_2018_PtResoDown  = new TH1D ("eejj_L13_M1000_mumujj_2018_PtResoDown", "eejj_L13_M1000_mumujj_2018_PtResoDown", 8, asymbins);

TH1D *eejj_L13_M1000_eejj = new TH1D ("eejj_L13_M1000_eejj", "eejj_L13_M1000_eejj", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2018_AlphaRatio = new TH1D ("eejj_L13_M1000_eejj_2018_AlphaRatio", "eejj_L13_M1000_eejj_2018_AlphaRatio", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2018_AlphaRatioDown = new TH1D ("eejj_L13_M1000_eejj_2018_AlphaRatioDown", "eejj_L13_M1000_eejj_2018_AlphaRatioDown", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2018_AlphaRatioUp = new TH1D ("eejj_L13_M1000_eejj_2018_AlphaRatioUp", "eejj_L13_M1000_eejj_2018_AlphaRatioUp", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2018_SFUp = new TH1D ("eejj_L13_M1000_eejj_2018_SFUp", "eejj_L13_M1000_eejj_2018_SFUp", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2018_SFDown = new TH1D ("eejj_L13_M1000_eejj_2018_SFDown", "eejj_L13_M1000_eejj_2018_SFDown", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2018_PUUp = new TH1D ("eejj_L13_M1000_eejj_2018_PUUp", "eejj_L13_M1000_eejj_2018_PUUp", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2018_PUDown = new TH1D ("eejj_L13_M1000_eejj_2018_PUDown", "eejj_L13_M1000_eejj_2018_PUDown", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2018_centralJesJer = new TH1D ("eejj_L13_M1000_eejj_2018_centralJesJer", "eejj_L13_M1000_eejj_2018_centralJesJer", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2018_JesSFUp = new TH1D ("eejj_L13_M1000_eejj_2018_JesSFUp", "eejj_L13_M1000_eejj_2018_JesSFUp", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2018_JesSFDown = new TH1D ("eejj_L13_M1000_eejj_2018_JesSFDown", "eejj_L13_M1000_eejj_2018_JesSFDown", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2018_JerSFUp = new TH1D ("eejj_L13_M1000_eejj_2018_JerSFUp", "eejj_L13_M1000_eejj_2018_JerSFUp", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2018_JerSFDown = new TH1D ("eejj_L13_M1000_eejj_2018_JerSFDown", "eejj_L13_M1000_eejj_2018_JerSFDown", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_energyScaleUp = new TH1D ("eejj_L13_M1000_eejj_energyScaleUp", "eejj_L13_M1000_eejj_energyScaleUp", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_energyScaleDown = new TH1D ("eejj_L13_M1000_eejj_energyScaleDown", "eejj_L13_M1000_eejj_energyScaleDown", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2018_energySigmaUp = new TH1D ("eejj_L13_M1000_eejj_2018_energySigmaUp", "eejj_L13_M1000_eejj_2018_energySigmaUp", 8, asymbins);
TH1D *eejj_L13_M1000_eejj_2018_energySigmaDown = new TH1D ("eejj_L13_M1000_eejj_2018_energySigmaDown", "eejj_L13_M1000_eejj_2018_energySigmaDown", 8, asymbins);

//PDF uncertaintes for signal samples
TH1D *eejj_L13_M1000_mumujj_PDFUp = new TH1D ("eejj_L13_M1000_mumujj_PDFUp", "eejj_L13_M1000_mumujj_PDFUp", 8, asymbins);   //PDF
TH1D *eejj_L13_M1000_mumujj_PDFDown = new TH1D ("eejj_L13_M1000_mumujj_PDFDown", "eejj_L13_M1000_mumujj_PDFDown", 8, asymbins); //PDF
TH1D *eejj_L13_M1000_eejj_PDFUp = new TH1D ("eejj_L13_M1000_eejj_PDFUp", "eejj_L13_M1000_eejj_PDFUp", 8, asymbins); //PDF
TH1D *eejj_L13_M1000_eejj_PDFDown = new TH1D ("eejj_L13_M1000_eejj_PDFDown", "eejj_L13_M1000_eejj_PDFDown", 8, asymbins); //PDF

//DY CR Zpeak (mll in 60-120 GeV)
TH1D *eejj_L13_M1000_ZpeakMll_mumujj = new TH1D ("eejj_L13_M1000_ZpeakMll_mumujj", "eejj_L13_M1000_ZpeakMll_mumujj", 60,60,120);
TH1D *eejj_L13_M1000_Zpeak_mumujj = new TH1D ("eejj_L13_M1000_Zpeak_mumujj", "eejj_L13_M1000_Zpeak_mumujj", 8, asymbins);
TH1D *eejj_L13_M1000_ZpeakMll_eejj = new TH1D ("eejj_L13_M1000_ZpeakMll_eejj", "eejj_L13_M1000_ZpeakMll_eejj", 60,60,120);
TH1D *eejj_L13_M1000_Zpeak_eejj = new TH1D ("eejj_L13_M1000_Zpeak_eejj", "eejj_L13_M1000_Zpeak_eejj", 8, asymbins);


//DY CR (mll in 150-300 GeV)
TH1D *eejj_L13_M1000_DYcr_mumujj = new TH1D ("eejj_L13_M1000_DYcr_mumujj", "eejj_L13_M1000_DYcr_mumujj", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2018_AlphaRatio = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2018_AlphaRatio", "eejj_L13_M1000_DYcr_mumujj_2018_AlphaRatio", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2018_AlphaRatioUp = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2018_AlphaRatioUp", "eejj_L13_M1000_DYcr_mumujj_2018_AlphaRatioUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2018_AlphaRatioDown = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2018_AlphaRatioDown", "eejj_L13_M1000_DYcr_mumujj_2018_AlphaRatioDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2018_SFUp = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2018_SFUp", "eejj_L13_M1000_DYcr_mumujj_2018_SFUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2018_SFDown = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2018_SFDown", "eejj_L13_M1000_DYcr_mumujj_2018_SFDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2018_PUUp = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2018_PUUp", "eejj_L13_M1000_DYcr_mumujj_2018_PUUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2018_PUDown = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2018_PUDown", "eejj_L13_M1000_DYcr_mumujj_2018_PUDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_centralJesJer = new TH1D ("eejj_L13_M1000_DYcr_mumujj_centralJesJer", "eejj_L13_M1000_DYcr_mumujj_centralJesJer", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2018_JesSFUp = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2018_JesSFUp", "eejj_L13_M1000_DYcr_mumujj_2018_JesSFUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2018_JesSFDown = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2018_JesSFDown", "eejj_L13_M1000_DYcr_mumujj_2018_JesSFDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2018_JerSFUp = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2018_JerSFUp", "eejj_L13_M1000_DYcr_mumujj_2018_JerSFUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2018_JerSFDown = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2018_JerSFDown", "eejj_L13_M1000_DYcr_mumujj_2018_JerSFDown", 8, asymbins);
/*TH1D *eejj_L13_M1000_DYcr_mumujj_2018_PtCorrUp = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2018_PtCorrUp", "eejj_L13_M1000_DYcr_mumujj_2018_PtCorrUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2018_PtCorrDown = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2018_PtCorrDown", "eejj_L13_M1000_DYcr_mumujj_2018_PtCorrDown", 8, asymbins);*/
TH1D *eejj_L13_M1000_DYcr_mumujj_2018_PtResoUp  = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2018_PtResoUp", "eejj_L13_M1000_DYcr_mumujj_2018_PtResoUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_mumujj_2018_PtResoDown  = new TH1D ("eejj_L13_M1000_DYcr_mumujj_2018_PtResoDown", "eejj_L13_M1000_DYcr_mumujj_2018_PtResoDown", 8, asymbins);
TH1D *Mmumu_DYcr = new TH1D ("Mmumu_DYcr", "Mmumu_DYcr", 50, 150, 300);
TH1D *Mee_DYcr = new TH1D ("Mee_DYcr", "Mee_DYcr", 50, 150, 300);
TH1D *eejj_L13_M1000_DYcr_eejj = new TH1D ("eejj_L13_M1000_DYcr_eejj", "eejj_L13_M1000_DYcr_eejj", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2018_AlphaRatio = new TH1D ("eejj_L13_M1000_DYcr_eejj_2018_AlphaRatio", "eejj_L13_M1000_DYcr_eejj_2018_AlphaRatio", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2018_AlphaRatioUp = new TH1D ("eejj_L13_M1000_DYcr_eejj_2018_AlphaRatioUp", "eejj_L13_M1000_DYcr_eejj_2018_AlphaRatioUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2018_AlphaRatioDown = new TH1D ("eejj_L13_M1000_DYcr_eejj_2018_AlphaRatioDown", "eejj_L13_M1000_DYcr_eejj_2018_AlphaRatioDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2018_SFUp = new TH1D ("eejj_L13_M1000_DYcr_eejj_2018_SFUp", "eejj_L13_M1000_DYcr_eejj_2018_SFUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2018_SFDown = new TH1D ("eejj_L13_M1000_DYcr_eejj_2018_SFDown", "eejj_L13_M1000_DYcr_eejj_2018_SFDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2018_PUUp = new TH1D ("eejj_L13_M1000_DYcr_eejj_2018_PUUp", "eejj_L13_M1000_DYcr_eejj_2018_PUUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2018_PUDown = new TH1D ("eejj_L13_M1000_DYcr_eejj_2018_PUDown", "eejj_L13_M1000_DYcr_eejj_2018_PUDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_centralJesJer = new TH1D ("eejj_L13_M1000_DYcr_eejj_centralJesJer", "eejj_L13_M1000_DYcr_eejj_centralJesJer", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2018_JesSFUp = new TH1D ("eejj_L13_M1000_DYcr_eejj_2018_JesSFUp", "eejj_L13_M1000_DYcr_eejj_2018_JesSFUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2018_JesSFDown = new TH1D ("eejj_L13_M1000_DYcr_eejj_2018_JesSFDown", "eejj_L13_M1000_DYcr_eejj_2018_JesSFDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2018_JerSFUp = new TH1D ("eejj_L13_M1000_DYcr_eejj_2018_JerSFUp", "eejj_L13_M1000_DYcr_eejj_2018_JerSFUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2018_JerSFDown = new TH1D ("eejj_L13_M1000_DYcr_eejj_2018_JerSFDown", "eejj_L13_M1000_DYcr_eejj_2018_JerSFDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_energyScaleUp = new TH1D ("eejj_L13_M1000_DYcr_eejj_energyScaleUp", "eejj_L13_M1000_DYcr_eejj_energyScaleUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_energyScaleDown = new TH1D ("eejj_L13_M1000_DYcr_eejj_energyScaleDown", "eejj_L13_M1000_DYcr_eejj_energyScaleDown", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2018_energySigmaUp = new TH1D ("eejj_L13_M1000_DYcr_eejj_2018_energySigmaUp", "eejj_L13_M1000_DYcr_eejj_2018_energySigmaUp", 8, asymbins);
TH1D *eejj_L13_M1000_DYcr_eejj_2018_energySigmaDown = new TH1D ("eejj_L13_M1000_DYcr_eejj_2018_energySigmaDown", "eejj_L13_M1000_DYcr_eejj_2018_energySigmaDown", 8, asymbins);

//TTtW cr
const double asymbins2[7] = {300,350,400,450,500,700,2000};
TH1D *M_leplepJ_TTtWcr = new TH1D ("M_leplepJ_TTtWcr", "M_leplepJ_TTtWcr", 8, asymbins);

TH1D *eejj_L13_M1000_TTtWcr_ll = new TH1D ("eejj_L13_M1000_TTtWcr_ll", "eejj_L13_M1000_TTtWcr_ll", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_2018_AlphaRatio = new TH1D ("eejj_L13_M1000_TTtWcr_ll_2018_AlphaRatio", "eejj_L13_M1000_TTtWcr_ll_2018_AlphaRatio", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_2018_AlphaRatioUp = new TH1D ("eejj_L13_M1000_TTtWcr_ll_2018_AlphaRatioUp", "eejj_L13_M1000_TTtWcr_ll_2018_AlphaRatioUp", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_2018_AlphaRatioDown = new TH1D ("eejj_L13_M1000_TTtWcr_ll_2018_AlphaRatioDown", "eejj_L13_M1000_TTtWcr_ll_2018_AlphaRatioDown", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_2018_SFUp = new TH1D ("eejj_L13_M1000_TTtWcr_ll_2018_SFUp", "eejj_L13_M1000_TTtWcr_ll_2018_SFUp", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_2018_SFDown = new TH1D ("eejj_L13_M1000_TTtWcr_ll_2018_SFDown", "eejj_L13_M1000_TTtWcr_ll_2018_SFDown", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_2018_PUUp = new TH1D ("eejj_L13_M1000_TTtWcr_ll_2018_PUUp", "eejj_L13_M1000_TTtWcr_ll_2018_PUUp", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_2018_PUDown = new TH1D ("eejj_L13_M1000_TTtWcr_ll_2018_PUDown", "eejj_L13_M1000_TTtWcr_ll_2018_PUDown", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_energyScaleUp = new TH1D ("eejj_L13_M1000_TTtWcr_ll_energyScaleUp", "eejj_L13_M1000_TTtWcr_ll_energyScaleUp", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_energyScaleDown = new TH1D ("eejj_L13_M1000_TTtWcr_ll_energyScaleDown", "eejj_L13_M1000_TTtWcr_ll_energyScaleDown", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_2018_energySigmaUp = new TH1D ("eejj_L13_M1000_TTtWcr_ll_2018_energySigmaUp", "eejj_L13_M1000_TTtWcr_ll_2018_energySigmaUp", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_2018_energySigmaDown = new TH1D ("eejj_L13_M1000_TTtWcr_ll_2018_energySigmaDown", "eejj_L13_M1000_TTtWcr_ll_2018_energySigmaDown", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_centralJesJer = new TH1D ("eejj_L13_M1000_TTtWcr_ll_centralJesJer", "eejj_L13_M1000_TTtWcr_ll_centralJesJer", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_2018_JesSFUp = new TH1D ("eejj_L13_M1000_TTtWcr_ll_2018_JesSFUp", "eejj_L13_M1000_TTtWcr_ll_2018_JesSFUp", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_2018_JesSFDown = new TH1D ("eejj_L13_M1000_TTtWcr_ll_2018_JesSFDown", "eejj_L13_M1000_TTtWcr_ll_2018_JesSFDown", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_2018_JerSFUp = new TH1D ("eejj_L13_M1000_TTtWcr_ll_2018_JerSFUp", "eejj_L13_M1000_TTtWcr_ll_2018_JerSFUp", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_2018_JerSFDown = new TH1D ("eejj_L13_M1000_TTtWcr_ll_2018_JerSFDown", "eejj_L13_M1000_TTtWcr_ll_2018_JerSFDown", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_2018_PtResoUp = new TH1D("eejj_L13_M1000_TTtWcr_ll_2018_PtResoUp", "eejj_L13_M1000_TTtWcr_ll_2018_PtResoUp", 6, asymbins2);
TH1D *eejj_L13_M1000_TTtWcr_ll_2018_PtResoDown = new TH1D("eejj_L13_M1000_TTtWcr_ll_2018_PtResoDown", "eejj_L13_M1000_TTtWcr_ll_2018_PtResoDown", 6, asymbins2);

/*M(emuJ)*/
TH1D *eejj_L13_M1000_TTtWcr_llJ = new TH1D ("eejj_L13_M1000_TTtWcr_llJ", "eejj_L13_M1000_TTtWcr_llJ", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2018_AlphaRatio = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2018_AlphaRatio", "eejj_L13_M1000_TTtWcr_llJ_2018_AlphaRatio", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2018_AlphaRatioUp = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2018_AlphaRatioUp", "eejj_L13_M1000_TTtWcr_llJ_2018_AlphaRatioUp", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2018_AlphaRatioDown = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2018_AlphaRatioDown", "eejj_L13_M1000_TTtWcr_llJ_2018_AlphaRatioDown", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2018_SFUp = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2018_SFUp", "eejj_L13_M1000_TTtWcr_llJ_2018_SFUp", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2018_SFDown = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2018_SFDown", "eejj_L13_M1000_TTtWcr_llJ_2018_SFDown", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2018_PUUp = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2018_PUUp", "eejj_L13_M1000_TTtWcr_llJ_2018_PUUp", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2018_PUDown = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2018_PUDown", "eejj_L13_M1000_TTtWcr_llJ_2018_PUDown", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2018_PtResoUp = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2018_PtResoUp", "eejj_L13_M1000_TTtWcr_llJ_2018_PtResoUp", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2018_PtResoDown = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2018_PtResoDown", "eejj_L13_M1000_TTtWcr_llJ_2018_PtResoDown", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_energyScaleUp = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_energyScaleUp", "eejj_L13_M1000_TTtWcr_llJ_energyScaleUp", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_energyScaleDown = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_energyScaleDown", "eejj_L13_M1000_TTtWcr_llJ_energyScaleDown", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2018_energySigmaUp = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2018_energySigmaUp", "eejj_L13_M1000_TTtWcr_llJ_2018_energySigmaUp", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2018_energySigmaDown = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2018_energySigmaDown", "eejj_L13_M1000_TTtWcr_llJ_2018_energySigmaDown", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_centralJesJer = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_centralJesJer", "eejj_L13_M1000_TTtWcr_llJ_centralJesJer", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2018_JesSFUp = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2018_JesSFUp", "eejj_L13_M1000_TTtWcr_llJ_2018_JesSFUp", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2018_JesSFDown = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2018_JesSFDown", "eejj_L13_M1000_TTtWcr_llJ_2018_JesSFDown", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2018_JerSFUp = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2018_JerSFUp", "eejj_L13_M1000_TTtWcr_llJ_2018_JerSFUp", 8, asymbins);
TH1D *eejj_L13_M1000_TTtWcr_llJ_2018_JerSFDown = new TH1D ("eejj_L13_M1000_TTtWcr_llJ_2018_JerSFDown", "eejj_L13_M1000_TTtWcr_llJ_2018_JerSFDown", 8, asymbins);



cout << a_->GetEntries() << endl;
int tot=0, muejj = 0;
double wg = 0, wg_SFu = 0, wg_SFd = 0, wg_PUu = 0, wg_PUd = 0;
int lumi = 58873;//2018: 58873 //2018: 41529 //2016: 35542
bool veto_ele = false;
double mee = 0, mmumu = 0, pu_w = 0;
double MmumuJ = 0, MmumuJ_JESup = 0, MmumuJ_JESdown = 0,  MmumuJ_JERup = 0, MmumuJ_JERdown = 0; /*this is for smearing*/
double energy_corr0 = 0, energy_corr1 = 0;

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

double Muon1_px_smearing = 0, Muon1_py_smearing = 0, Muon1_pz_smearing = 0;
double Muon2_px_smearing = 0, Muon2_py_smearing = 0, Muon2_pz_smearing = 0;
double extra_smearing_1 =0, extra_smearing_2 = 0;

for (Int_t i=0;i<a_->GetEntries();i++) {
 a_->GetEntry(i);
 HLT_Mu = 0; 
 tot = a_->GetEntries();
 if (i%100000 == 0) cout << i << " eventi analizzati su " << tot << endl;

 wg = lumi * lumi_wgt * lepsf_evt * PUWeight;
 wg_SFu = lumi * lumi_wgt * lepsf_evt_u * PUWeight;
 wg_SFd = lumi * lumi_wgt * lepsf_evt_d * PUWeight;
 wg_PUu = lumi * lumi_wgt * lepsf_evt * MinBiasUpWeight;
 wg_PUd = lumi * lumi_wgt * lepsf_evt * MinBiasDownWeight;
          
 if (HLT_Mu50==1 || HLT_TkMu100==1 || HLT_OldMu100==1 ) HLT_Mu = 1;
 
 if (Muon_pt_tunePbt_Roc->size() > 1 && numOfHighptMu==2 && numOfVetoEle == 0 && numOfBoostedJets>=1){
  Muon1.SetPtEtaPhiM(Muon_pt_tunePbt_Roc->at(0), Muon_eta->at(0), Muon_phi->at(0), 0.1056583745 );
  Muon2.SetPtEtaPhiM(Muon_pt_tunePbt_Roc->at(1), Muon_eta->at(1), Muon_phi->at(1), 0.1056583745 );
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

   if (HLT_Mu == 1 && Muon1_PtResoUp.Pt() > 150 && Muon2_PtResoUp.Pt() > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(Muon_eta->at(1))<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1_PtResoUp+Muon2_PtResoUp).M() > 300){

   BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
   BoostJet_JESup.SetPtEtaPhiE(BoostedJet_pt->at(1), BoostedJet_eta->at(1), BoostedJet_phi->at(1),BoostedJet_energy->at(1));
   BoostJet_JESdown.SetPtEtaPhiE(BoostedJet_pt->at(2), BoostedJet_eta->at(2), BoostedJet_phi->at(2),BoostedJet_energy->at(2));
   BoostJet_JERup.SetPtEtaPhiE(BoostedJet_pt->at(3), BoostedJet_eta->at(3), BoostedJet_phi->at(3),BoostedJet_energy->at(3));
   BoostJet_JERdown.SetPtEtaPhiE(BoostedJet_pt->at(4), BoostedJet_eta->at(4), BoostedJet_phi->at(4),BoostedJet_energy->at(4));
 
   NumFatJet_mu->Fill(numOfBoostedJets,wg); 

   eejj_L13_M1000_mumujj_Roc->Fill((Muon1_Roc+Muon2_Roc+BoostJet).M(), wg ) ;
   eejj_L13_M1000_mumujj->Fill((Muon1+Muon2+BoostJet).M(), wg); 
   eejj_L13_M1000_mumujj_2018_AlphaRatio->Fill((Muon1+Muon2+BoostJet).M(), wg*0.85);
   eejj_L13_M1000_mumujj_2018_AlphaRatioUp->Fill((Muon1+Muon2+BoostJet).M(), wg*0.87);
   eejj_L13_M1000_mumujj_2018_AlphaRatioDown->Fill((Muon1+Muon2+BoostJet).M(), wg*0.83);
   eejj_L13_M1000_mumujj_2018_SFUp->Fill((Muon1+Muon2+BoostJet).M(), wg_SFu);
   eejj_L13_M1000_mumujj_2018_SFDown->Fill((Muon1+Muon2+BoostJet).M(), wg_SFd);
   eejj_L13_M1000_mumujj_2018_PUUp->Fill((Muon1+Muon2+BoostJet).M(), wg_PUu);
   eejj_L13_M1000_mumujj_2018_PUDown->Fill((Muon1+Muon2+BoostJet).M(), wg_PUd);
   if ((Muon1_PtResoUp+Muon2_PtResoUp).M() >300)  eejj_L13_M1000_mumujj_2018_PtResoUp->Fill((Muon1_PtResoUp+Muon2_PtResoUp+BoostJet).M(), wg);
   eejj_L13_M1000_mumujj_2018_PtResoDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
   if(centralJesJer->at(0)==1)eejj_L13_M1000_mumujj_2018_centralJesJer->Fill((Muon1+Muon2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)eejj_L13_M1000_mumujj_2018_JesSFUp->Fill((Muon1+Muon2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)eejj_L13_M1000_mumujj_2018_JesSFDown->Fill((Muon1+Muon2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)eejj_L13_M1000_mumujj_2018_JerSFUp->Fill((Muon1+Muon2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)eejj_L13_M1000_mumujj_2018_JerSFDown->Fill((Muon1+Muon2+BoostJet_JERdown).M(), wg);  
  
  eejj_L13_M1000_mumujj_PDFUp->Fill((Muon1+Muon2+BoostJet).M(), wg*1.7);      //comment for bkgs                 
  eejj_L13_M1000_mumujj_PDFDown->Fill((Muon1+Muon2+BoostJet).M(), wg*0.3);  //comment for bkgs

  }

  //Zpeak DY cr Mll in 60-120 GeV
  if (HLT_Mu == 1 && Muon1_PtResoUp.Pt() > 150 && Muon2_PtResoUp.Pt() > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(Muon_eta->at(1))<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1_PtResoUp+Muon2_PtResoUp).M() > 60 && (Muon1_PtResoUp+Muon2_PtResoUp).M() < 120){
  BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
  eejj_L13_M1000_ZpeakMll_mumujj->Fill((Muon1+Muon2).M(), wg); 
  eejj_L13_M1000_Zpeak_mumujj->Fill((Muon1+Muon2+BoostJet).M(), wg); 
   }


  //DY cr Mll in 150-300 GeV
   if (HLT_Mu == 1 && Muon1_PtResoUp.Pt() > 150 && Muon2_PtResoUp.Pt() > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(Muon_eta->at(1))<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1_PtResoUp+Muon2_PtResoUp).M() > 150 && (Muon1_PtResoUp+Muon2_PtResoUp).M() < 300){

    BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
    BoostJet_JESup.SetPtEtaPhiE(BoostedJet_pt->at(1), BoostedJet_eta->at(1), BoostedJet_phi->at(1),BoostedJet_energy->at(1));
    BoostJet_JESdown.SetPtEtaPhiE(BoostedJet_pt->at(2), BoostedJet_eta->at(2), BoostedJet_phi->at(2),BoostedJet_energy->at(2));
    BoostJet_JERup.SetPtEtaPhiE(BoostedJet_pt->at(3), BoostedJet_eta->at(3), BoostedJet_phi->at(3),BoostedJet_energy->at(3));
    BoostJet_JERdown.SetPtEtaPhiE(BoostedJet_pt->at(4), BoostedJet_eta->at(4), BoostedJet_phi->at(4),BoostedJet_energy->at(4));
 
    Mmumu_DYcr->Fill((Muon1+Muon2).M(), wg);
    eejj_L13_M1000_DYcr_mumujj->Fill((Muon1+Muon2+BoostJet).M(), wg); 
    eejj_L13_M1000_DYcr_mumujj_2018_AlphaRatio->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_DYcr_mumujj_2018_AlphaRatioUp->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_DYcr_mumujj_2018_AlphaRatioDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
    eejj_L13_M1000_DYcr_mumujj_2018_SFUp->Fill((Muon1+Muon2+BoostJet).M(), wg_SFu);
    eejj_L13_M1000_DYcr_mumujj_2018_SFDown->Fill((Muon1+Muon2+BoostJet).M(), wg_SFd);
    eejj_L13_M1000_DYcr_mumujj_2018_PUUp->Fill((Muon1+Muon2+BoostJet).M(), wg_PUu);
    eejj_L13_M1000_DYcr_mumujj_2018_PUDown->Fill((Muon1+Muon2+BoostJet).M(), wg_PUd);
     eejj_L13_M1000_DYcr_mumujj_2018_PtResoUp->Fill((Muon1_PtResoUp+Muon2_PtResoUp+BoostJet).M(), wg);
    eejj_L13_M1000_DYcr_mumujj_2018_PtResoDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
    if(centralJesJer->at(0)==1)eejj_L13_M1000_DYcr_mumujj_centralJesJer->Fill((Muon1+Muon2+BoostJet).M(), wg);
    if(JesSFup->at(1)==1)eejj_L13_M1000_DYcr_mumujj_2018_JesSFUp->Fill((Muon1+Muon2+BoostJet_JESup).M(), wg);
    if(JesSFdown->at(2)==1)eejj_L13_M1000_DYcr_mumujj_2018_JesSFDown->Fill((Muon1+Muon2+BoostJet_JESdown).M(), wg);
    if(JerSFup->at(3)==1)eejj_L13_M1000_DYcr_mumujj_2018_JerSFUp->Fill((Muon1+Muon2+BoostJet_JERup).M(), wg);
    if(JerSFdown->at(4)==1)eejj_L13_M1000_DYcr_mumujj_2018_JerSFDown->Fill((Muon1+Muon2+BoostJet_JERdown).M(), wg);  
    }

 }
 
 if (patElectron_pt->size() > 1 && numOfHighptEle==2 && numOfLooseMu==0 && numOfBoostedJets>=1){
   Electron1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   Electron2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energy->at(1));
   energy_corr0= patElectron_ecalTrkEnergyPostCorr->at(0) / patElectron_energy->at(0) ;
   energy_corr1= patElectron_ecalTrkEnergyPostCorr->at(1) / patElectron_energy->at(1) ;
   Electron1 = Electron1*energy_corr0;
   Electron2 = Electron2*energy_corr1;

      /*  BUG FIXING FOR SF ELE 2018 */
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

   NumFatJet->Fill(numOfBoostedJets,wg); 

   eejj_L13_M1000_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   eejj_L13_M1000_eejj_2018_AlphaRatio->Fill((Electron1+Electron2+BoostJet).M(), wg*0.79);
   eejj_L13_M1000_eejj_2018_AlphaRatioUp->Fill((Electron1+Electron2+BoostJet).M(), wg*0.85);
   eejj_L13_M1000_eejj_2018_AlphaRatioDown->Fill((Electron1+Electron2+BoostJet).M(), wg*0.73); 
   eejj_L13_M1000_eejj_2018_SFUp->Fill((Electron1+Electron2+BoostJet).M(), wg_SFu);
   eejj_L13_M1000_eejj_2018_SFDown->Fill((Electron1+Electron2+BoostJet).M(), wg_SFd);
   eejj_L13_M1000_eejj_2018_PUUp->Fill((Electron1+Electron2+BoostJet).M(), wg_PUu);
   eejj_L13_M1000_eejj_2018_PUDown->Fill((Electron1+Electron2+BoostJet).M(), wg_PUd);
   eejj_L13_M1000_eejj_energyScaleUp->Fill((Ele1_ScaleUp+Ele2_ScaleUp+BoostJet).M(), wg);
   eejj_L13_M1000_eejj_energyScaleDown->Fill((Ele1_ScaleDown+Ele2_ScaleDown+BoostJet).M(), wg);
   eejj_L13_M1000_eejj_2018_energySigmaUp->Fill((Ele1_SigmaUp+Ele2_SigmaUp+BoostJet).M(), wg);
   eejj_L13_M1000_eejj_2018_energySigmaDown->Fill((Ele1_SigmaDown+Ele2_SigmaDown+BoostJet).M(), wg);
   if(centralJesJer->at(0)==1)eejj_L13_M1000_eejj_2018_centralJesJer->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)eejj_L13_M1000_eejj_2018_JesSFUp->Fill((Electron1+Electron2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)eejj_L13_M1000_eejj_2018_JesSFDown->Fill((Electron1+Electron2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)eejj_L13_M1000_eejj_2018_JerSFUp->Fill((Electron1+Electron2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)eejj_L13_M1000_eejj_2018_JerSFDown->Fill((Electron1+Electron2+BoostJet_JERdown).M(), wg); 
  
  eejj_L13_M1000_eejj_PDFUp->Fill((Electron1+Electron2+BoostJet).M(), wg*1.7);      //comment for bkgs                 
  eejj_L13_M1000_eejj_PDFDown->Fill((Electron1+Electron2+BoostJet).M(), wg*0.3);  //comment for bkgs
}


  //Zpeak DY cr 60-120 GeV
  if (HLT_Ele == 1 && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190 && (Electron1+Electron2).M() >60 && (Electron1+Electron2).M() < 120){
   Electron1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   Electron2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energy->at(1));  
   BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
   energy_corr0= patElectron_ecalTrkEnergyPostCorr->at(0) / patElectron_energy->at(0) ;
   energy_corr1= patElectron_ecalTrkEnergyPostCorr->at(1) / patElectron_energy->at(1) ;
   Electron1 = Electron1*energy_corr0;
   Electron2 = Electron2*energy_corr1;
   eejj_L13_M1000_ZpeakMll_eejj->Fill((Electron1+Electron2).M(), wg);
   eejj_L13_M1000_Zpeak_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
  }

  //DY cr 150-300 GeV
  if (HLT_Ele == 1 && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190 && (Electron1+Electron2).M() >150 && (Electron1+Electron2).M() < 300){
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

   Mee_DYcr->Fill((Electron1+Electron2).M(), wg);  
   eejj_L13_M1000_DYcr_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   eejj_L13_M1000_DYcr_eejj_2018_AlphaRatio->Fill((Electron1+Electron2+BoostJet).M(), wg);
   eejj_L13_M1000_DYcr_eejj_2018_AlphaRatioUp->Fill((Electron1+Electron2+BoostJet).M(), wg);
   eejj_L13_M1000_DYcr_eejj_2018_AlphaRatioDown->Fill((Electron1+Electron2+BoostJet).M(), wg);
   eejj_L13_M1000_DYcr_eejj_2018_SFUp->Fill((Electron1+Electron2+BoostJet).M(), wg_SFu);
   eejj_L13_M1000_DYcr_eejj_2018_SFDown->Fill((Electron1+Electron2+BoostJet).M(), wg_SFd);
   eejj_L13_M1000_DYcr_eejj_2018_PUUp->Fill((Electron1+Electron2+BoostJet).M(), wg_PUu);
   eejj_L13_M1000_DYcr_eejj_2018_PUDown->Fill((Electron1+Electron2+BoostJet).M(), wg_PUd);
   eejj_L13_M1000_DYcr_eejj_energyScaleUp->Fill((Ele1_ScaleUp+Ele2_ScaleUp+BoostJet).M(), wg);
   eejj_L13_M1000_DYcr_eejj_energyScaleDown->Fill((Ele1_ScaleDown+Ele2_ScaleDown+BoostJet).M(), wg);
   eejj_L13_M1000_DYcr_eejj_2018_energySigmaUp->Fill((Ele1_SigmaUp+Ele2_SigmaUp+BoostJet).M(), wg);
   eejj_L13_M1000_DYcr_eejj_2018_energySigmaDown->Fill((Ele1_SigmaDown+Ele2_SigmaDown+BoostJet).M(), wg);
   if(centralJesJer->at(0)==1)eejj_L13_M1000_DYcr_eejj_centralJesJer->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)eejj_L13_M1000_DYcr_eejj_2018_JesSFUp->Fill((Electron1+Electron2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)eejj_L13_M1000_DYcr_eejj_2018_JesSFDown->Fill((Electron1+Electron2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)eejj_L13_M1000_DYcr_eejj_2018_JerSFUp->Fill((Electron1+Electron2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)eejj_L13_M1000_DYcr_eejj_2018_JerSFDown->Fill((Electron1+Electron2+BoostJet_JERdown).M(), wg); 
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

   LeadLep.SetPtEtaPhiM(Muon_PtResoUp.Pt(), Muon_PtResoUp.Eta(), Muon_PtResoUp.Phi(), 0.1056583745);

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
    eejj_L13_M1000_TTtWcr_ll->Fill((LeadLep+SubLeadLep).M(),wg);
    eejj_L13_M1000_TTtWcr_ll_2018_AlphaRatio->Fill((LeadLep+SubLeadLep).M(),wg);
    eejj_L13_M1000_TTtWcr_ll_2018_AlphaRatioUp->Fill((LeadLep+SubLeadLep).M(),wg);
    eejj_L13_M1000_TTtWcr_ll_2018_AlphaRatioDown->Fill((LeadLep+SubLeadLep).M(),wg);
    eejj_L13_M1000_TTtWcr_ll_2018_SFUp->Fill((LeadLep+SubLeadLep).M(),wg_SFu);
    eejj_L13_M1000_TTtWcr_ll_2018_SFDown->Fill((LeadLep+SubLeadLep).M(),wg_SFd);
    eejj_L13_M1000_TTtWcr_ll_2018_PUUp->Fill((LeadLep+SubLeadLep).M(),wg_PUu);
    eejj_L13_M1000_TTtWcr_ll_2018_PUDown->Fill((LeadLep+SubLeadLep).M(),wg_PUd);

    eejj_L13_M1000_TTtWcr_ll_energyScaleUp->Fill((Ele_ScaleUp+LeadLep).M(),wg);
    eejj_L13_M1000_TTtWcr_ll_energyScaleDown->Fill((Ele_ScaleDown+LeadLep).M(),wg);
    eejj_L13_M1000_TTtWcr_ll_2018_energySigmaUp->Fill((Ele_SigmaUp+LeadLep).M(),wg);
    eejj_L13_M1000_TTtWcr_ll_2018_energySigmaDown->Fill((Ele_SigmaDown+LeadLep).M(),wg);
    if ((Muon_PtResoUp+SubLeadLep).M() >300) eejj_L13_M1000_TTtWcr_ll_2018_PtResoUp->Fill((Muon_PtResoUp+SubLeadLep).M(), wg);
    eejj_L13_M1000_TTtWcr_ll_2018_PtResoDown->Fill((LeadLep+SubLeadLep).M(), wg);
    M_leplepJ_TTtWcr->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    if(centralJesJer->at(0)==1)eejj_L13_M1000_TTtWcr_ll_centralJesJer->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JesSFup->at(1)==1)eejj_L13_M1000_TTtWcr_ll_2018_JesSFUp->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JesSFdown->at(2)==1)eejj_L13_M1000_TTtWcr_ll_2018_JesSFDown->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JerSFup->at(3)==1)eejj_L13_M1000_TTtWcr_ll_2018_JerSFUp->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JerSFdown->at(4)==1)eejj_L13_M1000_TTtWcr_ll_2018_JerSFDown->Fill((LeadLep+SubLeadLep).M(), wg);

    /*M(emuJ)*/
    eejj_L13_M1000_TTtWcr_llJ->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2018_AlphaRatio->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2018_AlphaRatioUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2018_AlphaRatioDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2018_SFUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_SFu);
    eejj_L13_M1000_TTtWcr_llJ_2018_SFDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_SFd);
    eejj_L13_M1000_TTtWcr_llJ_2018_PUUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_PUu);
    eejj_L13_M1000_TTtWcr_llJ_2018_PUDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_PUd);
    if ((Muon_PtResoUp+SubLeadLep).M() >300) eejj_L13_M1000_TTtWcr_llJ_2018_PtResoUp->Fill((Muon_PtResoUp+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2018_PtResoDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_energyScaleUp->Fill((Ele_ScaleUp+LeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_energyScaleDown->Fill((Ele_ScaleDown+LeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2018_energySigmaUp->Fill((Ele_SigmaUp+LeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2018_energySigmaDown->Fill((Ele_SigmaDown+LeadLep+BoostJet).M(),wg);
    if(centralJesJer->at(0)==1)eejj_L13_M1000_TTtWcr_llJ_centralJesJer->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if(JesSFup->at(1)==1)eejj_L13_M1000_TTtWcr_llJ_2018_JesSFUp->Fill((LeadLep+SubLeadLep+BoostJet_JESup).M(), wg);
    if(JesSFdown->at(2)==1)eejj_L13_M1000_TTtWcr_llJ_2018_JesSFDown->Fill((LeadLep+SubLeadLep+BoostJet_JESdown).M(), wg);
    if(JerSFup->at(3)==1)eejj_L13_M1000_TTtWcr_llJ_2018_JerSFUp->Fill((LeadLep+SubLeadLep+BoostJet_JERup).M(), wg);
    if(JerSFdown->at(4)==1)eejj_L13_M1000_TTtWcr_llJ_2018_JerSFDown->Fill((LeadLep+SubLeadLep+BoostJet_JESdown).M(), wg);

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

   SubLeadLep.SetPtEtaPhiM(Muon_PtResoUp.Pt(), Muon_PtResoUp.Eta(), Muon_PtResoUp.Phi(), 0.1056583745); 

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
    eejj_L13_M1000_TTtWcr_ll->Fill((LeadLep+SubLeadLep).M(),wg);
    eejj_L13_M1000_TTtWcr_ll_2018_AlphaRatio->Fill((LeadLep+SubLeadLep).M(),wg);
    eejj_L13_M1000_TTtWcr_ll_2018_AlphaRatioUp->Fill((LeadLep+SubLeadLep).M(),wg);
    eejj_L13_M1000_TTtWcr_ll_2018_AlphaRatioDown->Fill((LeadLep+SubLeadLep).M(),wg);
    eejj_L13_M1000_TTtWcr_ll_2018_SFUp->Fill((LeadLep+SubLeadLep).M(),wg_SFu);
    eejj_L13_M1000_TTtWcr_ll_2018_SFDown->Fill((LeadLep+SubLeadLep).M(),wg_SFd);
    eejj_L13_M1000_TTtWcr_ll_2018_PUUp->Fill((LeadLep+SubLeadLep).M(),wg_PUu);
    eejj_L13_M1000_TTtWcr_ll_2018_PUDown->Fill((LeadLep+SubLeadLep).M(),wg_PUd);

    eejj_L13_M1000_TTtWcr_ll_energyScaleUp->Fill((Ele_ScaleUp+SubLeadLep).M(),wg);
    eejj_L13_M1000_TTtWcr_ll_energyScaleDown->Fill((Ele_ScaleDown+SubLeadLep).M(),wg);
    eejj_L13_M1000_TTtWcr_ll_2018_energySigmaUp->Fill((Ele_SigmaUp+SubLeadLep).M(),wg);
    eejj_L13_M1000_TTtWcr_ll_2018_energySigmaDown->Fill((Ele_SigmaDown+SubLeadLep).M(),wg);
    if ((Muon_PtResoUp+LeadLep).M() >300) eejj_L13_M1000_TTtWcr_ll_2018_PtResoUp->Fill((Muon_PtResoUp+LeadLep).M(), wg);
    eejj_L13_M1000_TTtWcr_ll_2018_PtResoDown->Fill((SubLeadLep+LeadLep).M(), wg);
    M_leplepJ_TTtWcr->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);

    if(centralJesJer->at(0)==1)eejj_L13_M1000_TTtWcr_ll_centralJesJer->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JesSFup->at(1)==1)eejj_L13_M1000_TTtWcr_ll_2018_JesSFUp->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JesSFdown->at(2)==1)eejj_L13_M1000_TTtWcr_ll_2018_JesSFDown->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JerSFup->at(3)==1)eejj_L13_M1000_TTtWcr_ll_2018_JerSFUp->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JerSFdown->at(4)==1)eejj_L13_M1000_TTtWcr_ll_2018_JerSFDown->Fill((LeadLep+SubLeadLep).M(), wg);

     /* M(e mu J)*/
    eejj_L13_M1000_TTtWcr_llJ->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2018_AlphaRatio->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2018_AlphaRatioUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2018_AlphaRatioDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2018_SFUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_SFu);
    eejj_L13_M1000_TTtWcr_llJ_2018_SFDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_SFd);
    eejj_L13_M1000_TTtWcr_llJ_2018_PUUp->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_PUu);
    eejj_L13_M1000_TTtWcr_llJ_2018_PUDown->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg_PUd);
    if ((Muon_PtResoUp+LeadLep).M() >300) eejj_L13_M1000_TTtWcr_llJ_2018_PtResoUp->Fill((Muon_PtResoUp+LeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2018_PtResoDown->Fill((SubLeadLep+LeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_energyScaleUp->Fill((Ele_ScaleUp+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_energyScaleDown->Fill((Ele_ScaleDown+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2018_energySigmaUp->Fill((Ele_SigmaUp+SubLeadLep+BoostJet).M(),wg);
    eejj_L13_M1000_TTtWcr_llJ_2018_energySigmaDown->Fill((Ele_SigmaDown+SubLeadLep+BoostJet).M(),wg);
    if(centralJesJer->at(0)==1)eejj_L13_M1000_TTtWcr_llJ_centralJesJer->Fill((LeadLep+SubLeadLep+BoostJet).M(), wg);
    if(JesSFup->at(1)==1)eejj_L13_M1000_TTtWcr_llJ_2018_JesSFUp->Fill((LeadLep+SubLeadLep+BoostJet_JESup).M(), wg);
    if(JesSFdown->at(2)==1)eejj_L13_M1000_TTtWcr_llJ_2018_JesSFDown->Fill((LeadLep+SubLeadLep+BoostJet_JESdown).M(), wg);
    if(JerSFup->at(3)==1)eejj_L13_M1000_TTtWcr_llJ_2018_JerSFUp->Fill((LeadLep+SubLeadLep+BoostJet_JERup).M(), wg);
    if(JerSFdown->at(4)==1)eejj_L13_M1000_TTtWcr_llJ_2018_JerSFDown->Fill((LeadLep+SubLeadLep+BoostJet_JERdown).M(), wg);
    }
   }
  }


 } //TTtW CR
}

//TFile *f = new TFile("SR_syst_eejj_L13_M1000_2018.root", "RECREATE");
TFile *f = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/2018_ALL_HOPE/SR_syst_eejj_L13_M1000_2018_test.root", "RECREATE");
//TFile *f2 = new TFile("plot/SR_syst_eejj_L13_M1000_2018.root", "RECREATE");
eejj_L13_M1000_eejj->Write();
eejj_L13_M1000_eejj_2018_AlphaRatio->Write();
eejj_L13_M1000_eejj_2018_AlphaRatioUp->Write();
eejj_L13_M1000_eejj_2018_AlphaRatioDown->Write();
eejj_L13_M1000_eejj_2018_SFUp->Write();
eejj_L13_M1000_eejj_2018_SFDown->Write();
eejj_L13_M1000_eejj_2018_PUUp->Write();
eejj_L13_M1000_eejj_2018_PUDown->Write();
eejj_L13_M1000_eejj_2018_centralJesJer->Write();
eejj_L13_M1000_eejj_2018_JesSFUp->Write();
eejj_L13_M1000_eejj_2018_JesSFDown->Write();
eejj_L13_M1000_eejj_2018_JerSFUp->Write();
eejj_L13_M1000_eejj_2018_JerSFDown->Write();
eejj_L13_M1000_eejj_energyScaleUp->Write();
eejj_L13_M1000_eejj_energyScaleDown->Write();
eejj_L13_M1000_eejj_2018_energySigmaUp->Write();
eejj_L13_M1000_eejj_2018_energySigmaDown->Write();

eejj_L13_M1000_mumujj_Roc->Write();
eejj_L13_M1000_mumujj->Write();
eejj_L13_M1000_mumujj_2018_AlphaRatio->Write();
eejj_L13_M1000_mumujj_2018_AlphaRatioUp->Write();
eejj_L13_M1000_mumujj_2018_AlphaRatioDown->Write();
eejj_L13_M1000_mumujj_2018_SFUp->Write();
eejj_L13_M1000_mumujj_2018_SFDown->Write();
eejj_L13_M1000_mumujj_2018_PUUp->Write();
eejj_L13_M1000_mumujj_2018_PUDown->Write();
eejj_L13_M1000_mumujj_2018_centralJesJer->Write();
eejj_L13_M1000_mumujj_2018_JesSFUp->Write();
eejj_L13_M1000_mumujj_2018_JesSFDown->Write();
eejj_L13_M1000_mumujj_2018_JerSFUp->Write();
eejj_L13_M1000_mumujj_2018_JerSFDown->Write();
eejj_L13_M1000_mumujj_2018_PtResoUp->Write();
eejj_L13_M1000_mumujj_2018_PtResoDown->Write();
NumFatJet->Write();
NumFatJet_mu->Write();

eejj_L13_M1000_eejj_PDFUp->Write();
eejj_L13_M1000_eejj_PDFDown->Write();
eejj_L13_M1000_mumujj_PDFUp->Write();
eejj_L13_M1000_mumujj_PDFDown->Write();

//Zpeak DYcr 
eejj_L13_M1000_ZpeakMll_eejj->Write();
eejj_L13_M1000_ZpeakMll_mumujj->Write();
eejj_L13_M1000_Zpeak_eejj->Write();
eejj_L13_M1000_Zpeak_mumujj->Write();

//DYcr 
eejj_L13_M1000_DYcr_eejj->Write();
eejj_L13_M1000_DYcr_eejj_2018_AlphaRatio->Write();
eejj_L13_M1000_DYcr_eejj_2018_AlphaRatioUp->Write();
eejj_L13_M1000_DYcr_eejj_2018_AlphaRatioDown->Write();
eejj_L13_M1000_DYcr_eejj_2018_SFUp->Write();
eejj_L13_M1000_DYcr_eejj_2018_SFDown->Write();
eejj_L13_M1000_DYcr_eejj_2018_PUUp->Write();
eejj_L13_M1000_DYcr_eejj_2018_PUDown->Write();
eejj_L13_M1000_DYcr_eejj_centralJesJer->Write();
eejj_L13_M1000_DYcr_eejj_2018_JesSFUp->Write();
eejj_L13_M1000_DYcr_eejj_2018_JesSFDown->Write();
eejj_L13_M1000_DYcr_eejj_2018_JerSFUp->Write();
eejj_L13_M1000_DYcr_eejj_2018_JerSFDown->Write();
eejj_L13_M1000_DYcr_eejj_energyScaleUp->Write();
eejj_L13_M1000_DYcr_eejj_energyScaleDown->Write();
eejj_L13_M1000_DYcr_eejj_2018_energySigmaUp->Write();
eejj_L13_M1000_DYcr_eejj_2018_energySigmaDown->Write();
Mmumu_DYcr->Write();
Mee_DYcr->Write();
eejj_L13_M1000_DYcr_mumujj->Write();
eejj_L13_M1000_DYcr_mumujj_2018_AlphaRatio->Write();
eejj_L13_M1000_DYcr_mumujj_2018_AlphaRatioUp->Write();
eejj_L13_M1000_DYcr_mumujj_2018_AlphaRatioDown->Write();
eejj_L13_M1000_DYcr_mumujj_2018_SFUp->Write();
eejj_L13_M1000_DYcr_mumujj_2018_SFDown->Write();
eejj_L13_M1000_DYcr_mumujj_2018_PUUp->Write();
eejj_L13_M1000_DYcr_mumujj_2018_PUDown->Write();
eejj_L13_M1000_DYcr_mumujj_centralJesJer->Write();
eejj_L13_M1000_DYcr_mumujj_2018_JesSFUp->Write();
eejj_L13_M1000_DYcr_mumujj_2018_JesSFDown->Write();
eejj_L13_M1000_DYcr_mumujj_2018_JerSFUp->Write();
eejj_L13_M1000_DYcr_mumujj_2018_JerSFDown->Write();
eejj_L13_M1000_DYcr_mumujj_2018_PtResoUp->Write();
eejj_L13_M1000_DYcr_mumujj_2018_PtResoDown->Write();

//TTtW cr
M_leplepJ_TTtWcr->Write();
eejj_L13_M1000_TTtWcr_ll->Write();
eejj_L13_M1000_TTtWcr_ll_2018_AlphaRatio->Write();
eejj_L13_M1000_TTtWcr_ll_2018_AlphaRatioUp->Write();
eejj_L13_M1000_TTtWcr_ll_2018_AlphaRatioDown->Write();
eejj_L13_M1000_TTtWcr_ll_2018_SFUp->Write();
eejj_L13_M1000_TTtWcr_ll_2018_SFDown->Write();
eejj_L13_M1000_TTtWcr_ll_2018_PUUp->Write();
eejj_L13_M1000_TTtWcr_ll_2018_PUDown->Write();
eejj_L13_M1000_TTtWcr_ll_energyScaleUp->Write();
eejj_L13_M1000_TTtWcr_ll_energyScaleDown->Write();
eejj_L13_M1000_TTtWcr_ll_2018_energySigmaUp->Write();
eejj_L13_M1000_TTtWcr_ll_2018_energySigmaDown->Write();
eejj_L13_M1000_TTtWcr_ll_2018_PtResoUp->Write();
eejj_L13_M1000_TTtWcr_ll_2018_PtResoDown->Write();
eejj_L13_M1000_TTtWcr_ll_centralJesJer->Write();
eejj_L13_M1000_TTtWcr_ll_2018_JesSFUp->Write();
eejj_L13_M1000_TTtWcr_ll_2018_JesSFDown->Write();
eejj_L13_M1000_TTtWcr_ll_2018_JerSFUp->Write();
eejj_L13_M1000_TTtWcr_ll_2018_JerSFDown->Write();

eejj_L13_M1000_TTtWcr_llJ->Write();
eejj_L13_M1000_TTtWcr_llJ_2018_AlphaRatio->Write();
eejj_L13_M1000_TTtWcr_llJ_2018_AlphaRatioUp->Write();
eejj_L13_M1000_TTtWcr_llJ_2018_AlphaRatioDown->Write();
eejj_L13_M1000_TTtWcr_llJ_2018_SFUp->Write();
eejj_L13_M1000_TTtWcr_llJ_2018_SFDown->Write();
eejj_L13_M1000_TTtWcr_llJ_2018_PUUp->Write();
eejj_L13_M1000_TTtWcr_llJ_2018_PUDown->Write();
eejj_L13_M1000_TTtWcr_llJ_2018_PtResoUp->Write();
eejj_L13_M1000_TTtWcr_llJ_2018_PtResoDown->Write();
eejj_L13_M1000_TTtWcr_llJ_energyScaleUp->Write();
eejj_L13_M1000_TTtWcr_llJ_energyScaleDown->Write();
eejj_L13_M1000_TTtWcr_llJ_2018_energySigmaUp->Write();
eejj_L13_M1000_TTtWcr_llJ_2018_energySigmaDown->Write();
eejj_L13_M1000_TTtWcr_llJ_centralJesJer->Write();
eejj_L13_M1000_TTtWcr_llJ_2018_JesSFUp->Write();
eejj_L13_M1000_TTtWcr_llJ_2018_JesSFDown->Write();
eejj_L13_M1000_TTtWcr_llJ_2018_JerSFUp->Write();
eejj_L13_M1000_TTtWcr_llJ_2018_JerSFDown->Write();

f->Write();
f->Close();

}
 
