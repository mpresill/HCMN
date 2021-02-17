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
void Analisi_SR_DY_syst_2017(){

TChain *a_ = new TChain("BOOM");

a_->Add("/eos/user/m/mpresill/CMS/HN_Reload/rootplized_samples_2017_syst/DY_2017.root");
//a_->Add("/eos/user/m/mpresill/CMS/HN_Reload/rootplized_samples_2017_syst/DY_FxFx_2017.root"); //uncomment line 335 
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

/* gen particles*/
vector<double>*Gen_pt; Gen_pt = 0;
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

/*gen particles*/
TBranch *a_Gen_pt=a_->GetBranch("Gen_pt");
TBranch *a_Gen_eta=a_->GetBranch("Gen_eta");
TBranch *a_Gen_phi=a_->GetBranch("Gen_phi");
TBranch *a_Gen_charge=a_->GetBranch("Gen_charge");
TBranch *a_Gen_energy=a_->GetBranch("Gen_energy");
TBranch *a_Gen_pdg_id=a_->GetBranch("Gen_pdg_id");
TBranch *a_Gen_motherpdg_id=a_->GetBranch("Gen_motherpdg_id");
TBranch *a_Gen_numDaught=a_->GetBranch("Gen_numDaught");
TBranch *a_Gen_numMother=a_->GetBranch("Gen_numMother");
a_Gen_pt->SetAddress(&Gen_pt);
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


//old bin
const double asymbins[10] = {0,200,400,600,800,1000,1400,2000,3500,10000};


TH1D *DY_mumujj = new TH1D ("DY_mumujj", "DY_mumujj", 9,  asymbins);
TH1D *DY_mumujj_2017_AlphaRatio = new TH1D ("DY_mumujj_2017_AlphaRatio", "DY_mumujj_2017_AlphaRatio", 9,  asymbins);
TH1D *DY_mumujj_2017_AlphaRatioDown = new TH1D ("DY_mumujj_2017_AlphaRatioDown", "DY_mumujj_2017_AlphaRatioDown", 9,  asymbins);
TH1D *DY_mumujj_2017_AlphaRatioUp = new TH1D ("DY_mumujj_2017_AlphaRatioUp", "DY_mumujj_2017_AlphaRatioUp", 9,  asymbins);
TH1D *DY_mumujj_2017_SFUp = new TH1D ("DY_mumujj_2017_SFUp", "DY_mumujj_2017_SFUp", 9,  asymbins);
TH1D *DY_mumujj_2017_SFDown = new TH1D ("DY_mumujj_2017_SFDown", "DY_mumujj_2017_SFDown", 9,  asymbins);
TH1D *DY_mumujj_2017_PUUp = new TH1D ("DY_mumujj_2017_PUUp", "DY_mumujj_2017_PUUp", 9,  asymbins);
TH1D *DY_mumujj_2017_PUDown = new TH1D ("DY_mumujj_2017_PUDown", "DY_mumujj_2017_PUDown", 9,  asymbins);
TH1D *DY_mumujj_2017_centralJesJer = new TH1D ("DY_mumujj_2017_centralJesJer", "DY_mumujj_2017_centralJesJer", 9,  asymbins);
TH1D *DY_mumujj_2017_JesSFUp = new TH1D ("DY_mumujj_2017_JesSFUp", "DY_mumujj_2017_JesSFUp", 9,  asymbins);
TH1D *DY_mumujj_2017_JesSFDown = new TH1D ("DY_mumujj_2017_JesSFDown", "DY_mumujj_2017_JesSFDown", 9,  asymbins);
TH1D *DY_mumujj_2017_JerSFUp = new TH1D ("DY_mumujj_2017_JerSFUp", "DY_mumujj_2017_JerSFUp", 9,  asymbins);
TH1D *DY_mumujj_2017_JerSFDown = new TH1D ("DY_mumujj_2017_JerSFDown", "DY_mumujj_2017_JerSFDown", 9,  asymbins);
//TH1D *DY_mumujj_2017_PtCorrDown = new TH1D ("DY_mumujj_2017_PtCorrDown", "DY_mumujj_2017_PtCorrDown", 9,  asymbins);
//TH1D *DY_mumujj_2017_PtCorrUp = new TH1D ("DY_mumujj_2017_PtCorrUp", "DY_mumujj_2017_PtCorrUp", 9,  asymbins);
TH1D *DY_mumujj_2017_PtResoUp  = new TH1D ("DY_mumujj_2017_PtResoUp", "DY_mumujj_2017_PtResoUp", 9,  asymbins);
TH1D *DY_mumujj_2017_PtResoDown  = new TH1D ("DY_mumujj_2017_PtResoDown", "DY_mumujj_2017_PtResoDown", 9,  asymbins);

TH1D *DY_eejj = new TH1D ("DY_eejj", "DY_eejj", 9,  asymbins);
TH1D *DY_eejj_2017_AlphaRatio = new TH1D ("DY_eejj_2017_AlphaRatio", "DY_eejj_2017_AlphaRatio", 9,  asymbins);
TH1D *DY_eejj_2017_AlphaRatioDown = new TH1D ("DY_eejj_2017_AlphaRatioDown", "DY_eejj_2017_AlphaRatioDown", 9,  asymbins);
TH1D *DY_eejj_2017_AlphaRatioUp = new TH1D ("DY_eejj_2017_AlphaRatioUp", "DY_eejj_2017_AlphaRatioUp", 9,  asymbins);
TH1D *DY_eejj_2017_SFUp = new TH1D ("DY_eejj_2017_SFUp", "DY_eejj_2017_SFUp", 9,  asymbins);
TH1D *DY_eejj_2017_SFDown = new TH1D ("DY_eejj_2017_SFDown", "DY_eejj_2017_SFDown", 9,  asymbins);
TH1D *DY_eejj_2017_PUUp = new TH1D ("DY_eejj_2017_PUUp", "DY_eejj_2017_PUUp", 9,  asymbins);
TH1D *DY_eejj_2017_PUDown = new TH1D ("DY_eejj_2017_PUDown", "DY_eejj_2017_PUDown", 9,  asymbins);
TH1D *DY_eejj_2017_centralJesJer = new TH1D ("DY_eejj_2017_centralJesJer", "DY_eejj_2017_centralJesJer", 9,  asymbins);
TH1D *DY_eejj_2017_JesSFUp = new TH1D ("DY_eejj_2017_JesSFUp", "DY_eejj_2017_JesSFUp", 9,  asymbins);
TH1D *DY_eejj_2017_JesSFDown = new TH1D ("DY_eejj_2017_JesSFDown", "DY_eejj_2017_JesSFDown", 9,  asymbins);
TH1D *DY_eejj_2017_JerSFUp = new TH1D ("DY_eejj_2017_JerSFUp", "DY_eejj_2017_JerSFUp", 9,  asymbins);
TH1D *DY_eejj_2017_JerSFDown = new TH1D ("DY_eejj_2017_JerSFDown", "DY_eejj_2017_JerSFDown", 9,  asymbins);
TH1D *DY_eejj_2017_energyScaleUp = new TH1D ("DY_eejj_2017_energyScaleUp", "DY_eejj_2017_energyScaleUp", 9,  asymbins);
TH1D *DY_eejj_2017_energyScaleDown = new TH1D ("DY_eejj_2017_energyScaleDown", "DY_eejj_2017_energyScaleDown", 9,  asymbins);
TH1D *DY_eejj_2017_energySigmaUp = new TH1D ("DY_eejj_2017_energySigmaUp", "DY_eejj_2017_energySigmaUp", 9,  asymbins);
TH1D *DY_eejj_2017_energySigmaDown = new TH1D ("DY_eejj_2017_energySigmaDown", "DY_eejj_2017_energySigmaDown", 9,  asymbins);

//DY CR Zpeak (mll in 60-120 GeV)
TH1D *DY_ZpeakMll_mumujj = new TH1D ("DY_ZpeakMll_mumujj", "DY_ZpeakMll_mumujj", 60,60,120);
TH1D *DY_Zpeak_mumujj = new TH1D ("DY_Zpeak_mumujj", "DY_Zpeak_mumujj", 9,  asymbins);
TH1D *DY_Zpeak_mumujj_2017_AlphaRatio = new TH1D ("DY_Zpeak_mumujj_2017_AlphaRatio", "DY_Zpeak_mumujj_2017_AlphaRatio", 9,  asymbins);
TH1D *DY_Zpeak_mumujj_2017_AlphaRatioUp = new TH1D ("DY_Zpeak_mumujj_2017_AlphaRatioUp", "DY_Zpeak_mumujj_2017_AlphaRatioUp", 9,  asymbins);
TH1D *DY_Zpeak_mumujj_2017_AlphaRatioDown = new TH1D ("DY_Zpeak_mumujj_2017_AlphaRatioDown", "DY_Zpeak_mumujj_2017_AlphaRatioDown", 9,  asymbins);
TH1D *DY_Zpeak_mumujj_2017_SFUp = new TH1D ("DY_Zpeak_mumujj_2017_SFUp", "DY_Zpeak_mumujj_2017_SFUp", 9,  asymbins);
TH1D *DY_Zpeak_mumujj_2017_SFDown = new TH1D ("DY_Zpeak_mumujj_2017_SFDown", "DY_Zpeak_mumujj_2017_SFDown", 9,  asymbins);
TH1D *DY_Zpeak_mumujj_2017_PUUp = new TH1D ("DY_Zpeak_mumujj_2017_PUUp", "DY_Zpeak_mumujj_2017_PUUp", 9,  asymbins);
TH1D *DY_Zpeak_mumujj_2017_PUDown = new TH1D ("DY_Zpeak_mumujj_2017_PUDown", "DY_Zpeak_mumujj_2017_PUDown", 9,  asymbins);
TH1D *DY_Zpeak_mumujj_centralJesJer = new TH1D ("DY_Zpeak_mumujj_centralJesJer", "DY_Zpeak_mumujj_centralJesJer", 9,  asymbins);
TH1D *DY_Zpeak_mumujj_2017_JesSFUp = new TH1D ("DY_Zpeak_mumujj_2017_JesSFUp", "DY_Zpeak_mumujj_2017_JesSFUp", 9,  asymbins);
TH1D *DY_Zpeak_mumujj_2017_JesSFDown = new TH1D ("DY_Zpeak_mumujj_2017_JesSFDown", "DY_Zpeak_mumujj_2017_JesSFDown", 9,  asymbins);
TH1D *DY_Zpeak_mumujj_2017_JerSFUp = new TH1D ("DY_Zpeak_mumujj_2017_JerSFUp", "DY_Zpeak_mumujj_2017_JerSFUp", 9,  asymbins);
TH1D *DY_Zpeak_mumujj_2017_JerSFDown = new TH1D ("DY_Zpeak_mumujj_2017_JerSFDown", "DY_Zpeak_mumujj_2017_JerSFDown", 9,  asymbins);
//TH1D *DY_Zpeak_mumujj_2017_PtCorrUp = new TH1D ("DY_Zpeak_mumujj_2017_PtCorrUp", "DY_Zpeak_mumujj_2017_PtCorrUp", 9,  asymbins);
//TH1D *DY_Zpeak_mumujj_2017_PtCorrDown = new TH1D ("DY_Zpeak_mumujj_2017_PtCorrDown", "DY_Zpeak_mumujj_2017_PtCorrDown", 9,  asymbins);
TH1D *DY_Zpeak_mumujj_2017_PtResoUp  = new TH1D ("DY_Zpeak_mumujj_2017_PtResoUp", "DY_Zpeak_mumujj_2017_PtResoUp", 9,  asymbins);
TH1D *DY_Zpeak_mumujj_2017_PtResoDown  = new TH1D ("DY_Zpeak_mumujj_2017_PtResoDown", "DY_Zpeak_mumujj_2017_PtResoDown", 9,  asymbins);
TH1D *DY_ZpeakMll_eejj = new TH1D ("DY_ZpeakMll_eejj", "DY_ZpeakMll_eejj", 60,60,120);
TH1D *DY_Zpeak_eejj = new TH1D ("DY_Zpeak_eejj", "DY_Zpeak_eejj", 9,  asymbins);
TH1D *DY_Zpeak_eejj_2017_AlphaRatio = new TH1D ("DY_Zpeak_eejj_2017_AlphaRatio", "DY_Zpeak_eejj_2017_AlphaRatio", 9,  asymbins);
TH1D *DY_Zpeak_eejj_2017_AlphaRatioUp = new TH1D ("DY_Zpeak_eejj_2017_AlphaRatioUp", "DY_Zpeak_eejj_2017_AlphaRatioUp", 9,  asymbins);
TH1D *DY_Zpeak_eejj_2017_AlphaRatioDown = new TH1D ("DY_Zpeak_eejj_2017_AlphaRatioDown", "DY_Zpeak_eejj_2017_AlphaRatioDown", 9,  asymbins);
TH1D *DY_Zpeak_eejj_2017_SFUp = new TH1D ("DY_Zpeak_eejj_2017_SFUp", "DY_Zpeak_eejj_2017_SFUp", 9,  asymbins);
TH1D *DY_Zpeak_eejj_2017_SFDown = new TH1D ("DY_Zpeak_eejj_2017_SFDown", "DY_Zpeak_eejj_2017_SFDown", 9,  asymbins);
TH1D *DY_Zpeak_eejj_2017_PUUp = new TH1D ("DY_Zpeak_eejj_2017_PUUp", "DY_Zpeak_eejj_2017_PUUp", 9,  asymbins);
TH1D *DY_Zpeak_eejj_2017_PUDown = new TH1D ("DY_Zpeak_eejj_2017_PUDown", "DY_Zpeak_eejj_2017_PUDown", 9,  asymbins);
TH1D *DY_Zpeak_eejj_centralJesJer = new TH1D ("DY_Zpeak_eejj_centralJesJer", "DY_Zpeak_eejj_centralJesJer", 9,  asymbins);
TH1D *DY_Zpeak_eejj_2017_JesSFUp = new TH1D ("DY_Zpeak_eejj_2017_JesSFUp", "DY_Zpeak_eejj_2017_JesSFUp", 9,  asymbins);
TH1D *DY_Zpeak_eejj_2017_JesSFDown = new TH1D ("DY_Zpeak_eejj_2017_JesSFDown", "DY_Zpeak_eejj_2017_JesSFDown", 9,  asymbins);
TH1D *DY_Zpeak_eejj_2017_JerSFUp = new TH1D ("DY_Zpeak_eejj_2017_JerSFUp", "DY_Zpeak_eejj_2017_JerSFUp", 9,  asymbins);
TH1D *DY_Zpeak_eejj_2017_JerSFDown = new TH1D ("DY_Zpeak_eejj_2017_JerSFDown", "DY_Zpeak_eejj_2017_JerSFDown", 9,  asymbins);
TH1D *DY_Zpeak_eejj_2017_energyScaleUp = new TH1D ("DY_Zpeak_eejj_2017_energyScaleUp", "DY_Zpeak_eejj_2017_energyScaleUp", 9,  asymbins);
TH1D *DY_Zpeak_eejj_2017_energyScaleDown = new TH1D ("DY_Zpeak_eejj_2017_energyScaleDown", "DY_Zpeak_eejj_2017_energyScaleDown", 9,  asymbins);
TH1D *DY_Zpeak_eejj_2017_energySigmaUp = new TH1D ("DY_Zpeak_eejj_2017_energySigmaUp", "DY_Zpeak_eejj_2017_energySigmaUp", 9,  asymbins);
TH1D *DY_Zpeak_eejj_2017_energySigmaDown = new TH1D ("DY_Zpeak_eejj_2017_energySigmaDown", "DY_Zpeak_eejj_2017_energySigmaDown", 9,  asymbins);


//DY CR (mll in 150-300 GeV)
TH1D *DY_DYcr_mumujj = new TH1D ("DY_DYcr_mumujj", "DY_DYcr_mumujj", 9, asymbins);
TH1D *DY_DYcr_mumujj_2017_AlphaRatio = new TH1D ("DY_DYcr_mumujj_2017_AlphaRatio", "DY_DYcr_mumujj_2017_AlphaRatio", 9, asymbins);
TH1D *DY_DYcr_mumujj_2017_AlphaRatioUp = new TH1D ("DY_DYcr_mumujj_2017_AlphaRatioUp", "DY_DYcr_mumujj_2017_AlphaRatioUp", 9, asymbins);
TH1D *DY_DYcr_mumujj_2017_AlphaRatioDown = new TH1D ("DY_DYcr_mumujj_2017_AlphaRatioDown", "DY_DYcr_mumujj_2017_AlphaRatioDown", 9, asymbins);
TH1D *DY_DYcr_mumujj_2017_SFUp = new TH1D ("DY_DYcr_mumujj_2017_SFUp", "DY_DYcr_mumujj_2017_SFUp", 9, asymbins);
TH1D *DY_DYcr_mumujj_2017_SFDown = new TH1D ("DY_DYcr_mumujj_2017_SFDown", "DY_DYcr_mumujj_2017_SFDown", 9, asymbins);
TH1D *DY_DYcr_mumujj_2017_PUUp = new TH1D ("DY_DYcr_mumujj_2017_PUUp", "DY_DYcr_mumujj_2017_PUUp", 9, asymbins);
TH1D *DY_DYcr_mumujj_2017_PUDown = new TH1D ("DY_DYcr_mumujj_2017_PUDown", "DY_DYcr_mumujj_2017_PUDown", 9, asymbins);
TH1D *DY_DYcr_mumujj_centralJesJer = new TH1D ("DY_DYcr_mumujj_centralJesJer", "DY_DYcr_mumujj_centralJesJer", 9, asymbins);
TH1D *DY_DYcr_mumujj_2017_JesSFUp = new TH1D ("DY_DYcr_mumujj_2017_JesSFUp", "DY_DYcr_mumujj_2017_JesSFUp", 9, asymbins);
TH1D *DY_DYcr_mumujj_2017_JesSFDown = new TH1D ("DY_DYcr_mumujj_2017_JesSFDown", "DY_DYcr_mumujj_2017_JesSFDown", 9, asymbins);
TH1D *DY_DYcr_mumujj_2017_JerSFUp = new TH1D ("DY_DYcr_mumujj_2017_JerSFUp", "DY_DYcr_mumujj_2017_JerSFUp", 9, asymbins);
TH1D *DY_DYcr_mumujj_2017_JerSFDown = new TH1D ("DY_DYcr_mumujj_2017_JerSFDown", "DY_DYcr_mumujj_2017_JerSFDown", 9, asymbins);
//TH1D *DY_DYcr_mumujj_2017_PtCorrUp = new TH1D ("DY_DYcr_mumujj_2017_PtCorrUp", "DY_DYcr_mumujj_2017_PtCorrUp", 9, asymbins);
//TH1D *DY_DYcr_mumujj_2017_PtCorrDown = new TH1D ("DY_DYcr_mumujj_2017_PtCorrDown", "DY_DYcr_mumujj_2017_PtCorrDown", 9, asymbins);
TH1D *DY_DYcr_mumujj_2017_PtResoUp  = new TH1D ("DY_DYcr_mumujj_2017_PtResoUp", "DY_DYcr_mumujj_2017_PtResoUp", 9, asymbins);
TH1D *DY_DYcr_mumujj_2017_PtResoDown  = new TH1D ("DY_DYcr_mumujj_2017_PtResoDown", "DY_DYcr_mumujj_2017_PtResoDown", 9, asymbins);
TH1D *DY_DYcr_eejj = new TH1D ("DY_DYcr_eejj", "DY_DYcr_eejj", 9, asymbins);
TH1D *DY_DYcr_eejj_2017_AlphaRatio = new TH1D ("DY_DYcr_eejj_2017_AlphaRatio", "DY_DYcr_eejj_2017_AlphaRatio", 9, asymbins);
TH1D *DY_DYcr_eejj_2017_AlphaRatioUp = new TH1D ("DY_DYcr_eejj_2017_AlphaRatioUp", "DY_DYcr_eejj_2017_AlphaRatioUp", 9, asymbins);
TH1D *DY_DYcr_eejj_2017_AlphaRatioDown = new TH1D ("DY_DYcr_eejj_2017_AlphaRatioDown", "DY_DYcr_eejj_2017_AlphaRatioDown", 9, asymbins);
TH1D *DY_DYcr_eejj_2017_SFUp = new TH1D ("DY_DYcr_eejj_2017_SFUp", "DY_DYcr_eejj_2017_SFUp", 9, asymbins);
TH1D *DY_DYcr_eejj_2017_SFDown = new TH1D ("DY_DYcr_eejj_2017_SFDown", "DY_DYcr_eejj_2017_SFDown", 9, asymbins);
TH1D *DY_DYcr_eejj_2017_PUUp = new TH1D ("DY_DYcr_eejj_2017_PUUp", "DY_DYcr_eejj_2017_PUUp", 9, asymbins);
TH1D *DY_DYcr_eejj_2017_PUDown = new TH1D ("DY_DYcr_eejj_2017_PUDown", "DY_DYcr_eejj_2017_PUDown", 9, asymbins);
TH1D *DY_DYcr_eejj_centralJesJer = new TH1D ("DY_DYcr_eejj_centralJesJer", "DY_DYcr_eejj_centralJesJer", 9, asymbins);
TH1D *DY_DYcr_eejj_2017_JesSFUp = new TH1D ("DY_DYcr_eejj_2017_JesSFUp", "DY_DYcr_eejj_2017_JesSFUp", 9, asymbins);
TH1D *DY_DYcr_eejj_2017_JesSFDown = new TH1D ("DY_DYcr_eejj_2017_JesSFDown", "DY_DYcr_eejj_2017_JesSFDown", 9, asymbins);
TH1D *DY_DYcr_eejj_2017_JerSFUp = new TH1D ("DY_DYcr_eejj_2017_JerSFUp", "DY_DYcr_eejj_2017_JerSFUp", 9, asymbins);
TH1D *DY_DYcr_eejj_2017_JerSFDown = new TH1D ("DY_DYcr_eejj_2017_JerSFDown", "DY_DYcr_eejj_2017_JerSFDown", 9, asymbins);
TH1D *DY_DYcr_eejj_2017_energyScaleUp = new TH1D ("DY_DYcr_eejj_2017_energyScaleUp", "DY_DYcr_eejj_2017_energyScaleUp", 9, asymbins);
TH1D *DY_DYcr_eejj_2017_energyScaleDown = new TH1D ("DY_DYcr_eejj_2017_energyScaleDown", "DY_DYcr_eejj_2017_energyScaleDown", 9, asymbins);
TH1D *DY_DYcr_eejj_2017_energySigmaUp = new TH1D ("DY_DYcr_eejj_2017_energySigmaUp", "DY_DYcr_eejj_2017_energySigmaUp", 9, asymbins);
TH1D *DY_DYcr_eejj_2017_energySigmaDown = new TH1D ("DY_DYcr_eejj_2017_energySigmaDown", "DY_DYcr_eejj_2017_energySigmaDown", 9, asymbins);

cout << a_->GetEntries() << endl;
int tot=0, muejj = 0;
double wg = 0, wg_SFu = 0, wg_SFd = 0, wg_PUu = 0, wg_PUd = 0;
int lumi = 41529;//2017: 58873 //2017: 41529 //2017: 35542
bool veto_ele = false;
double mee = 0, mmumu = 0, pu_w = 0;

/*gen particles k-factors ewk nlo, qcd nlo*/
double Z_gen_pt=0;
double binCenter_ewk=0;
double binCenter_qcd=0;
double k_ewk=0, k_qcd=0;

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

for (Int_t i=0;i<a_->GetEntries();i++) {
 a_->GetEntry(i);
 tot = a_->GetEntries();
 if (i%100000 == 0) cout << i << " eventi analizzati su " << tot << endl;


/************************************************************/
  /*implementation of k-factors from monojet analysis*/
  /*here we read the histograms with the corrections */
  TFile k_qcd_file("monojetDYk/kfac_dy_filter.root");  /*this is the histo with qcd weights*/
  TH1F *k_qcd_histo = (TH1F*)k_qcd_file.Get("kfac_dy_filter");
  TFile k_ewk_file("monojetDYk/merged_kfactors_zjets.root");  /*this is the histo with ewk weights*/
  TH1F *k_ewk_histo = (TH1F*)k_ewk_file.Get("kfactor_monojet_ewk");
  /* here we read from all the gen particles the Z boson ones */
  /*if more than on Z boson...quit the for - this is not the most clean procedure, but how many Z are we expecting in each DY Region?!*/
  for (int l = 0; l<Gen_pt->size(); l++){
   if (fabs(Gen_pdg_id->at(l)) == 23  ){
    Z_gen_pt = Gen_pt->at(l);
    break;
   }
  }
  /* here we write the k_qcd */
  k_qcd=1;
  for (int ji=1; ji<= 47; ji++){
    binCenter_qcd= k_qcd_histo->GetXaxis()->GetBinCenter(ji);
    if(Z_gen_pt >(binCenter_qcd - 20) && Z_gen_pt < (binCenter_qcd + 20) ){
      k_qcd = k_qcd_histo->GetBinContent(ji);
    }
  }
  /* here we write the k_ewk */
  k_ewk =1;
    for (int jj=1; jj<= 24; jj++){
    binCenter_ewk= k_ewk_histo->GetXaxis()->GetBinCenter(jj);
    if(Z_gen_pt >(binCenter_ewk - 10) && Z_gen_pt < (binCenter_ewk +10) ){
      k_ewk = k_ewk_histo->GetBinContent(jj);
    }
  }
  /*end implementation of k-factor. The k-factors are then put in the weights for each event:   wg = lumi*lumi_wgt*lepsf_evt*k_ewk*k_qcd;*/
  /************************************************************/
 

 wg = lumi * lumi_wgt * lepsf_evt * PUWeight *k_ewk*k_qcd;
 wg_SFu = lumi * lumi_wgt * lepsf_evt_u * PUWeight*k_ewk*k_qcd;
 wg_SFd = lumi * lumi_wgt * lepsf_evt_d * PUWeight*k_ewk*k_qcd;
 wg_PUu = lumi * lumi_wgt * lepsf_evt * MinBiasUpWeight*k_ewk*k_qcd;
 wg_PUd = lumi * lumi_wgt * lepsf_evt * MinBiasDownWeight*k_ewk*k_qcd;

 HLT_Mu = 0; HLT_Ele = 0;          
 if (HLT_Mu50==1 || HLT_TkMu100==1 || HLT_OldMu100==1 ) HLT_Mu = 1;
 if (HLT_Photon200 == 1 || HLT_Ele35==1 || HLT_Ele115 == 1) HLT_Ele = 1;


  if (Muon_pt->size() > 1 && numOfHighptMu==2 && numOfVetoEle == 0 && numOfBoostedJets>=1){

   Muon1.SetPtEtaPhiE(Muon_pt->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));
   Muon2.SetPtEtaPhiE(Muon_pt->at(1), Muon_eta->at(1), Muon_phi->at(1),Muon_energy->at(1));
       /* BE CAREFUL ON THE WAY TO COMPUTE THE INVARIANT MASS!*/
    Muon1_PtResoUp.SetPtEtaPhiM((Muon_pt->at(0)+0.1*Muon_pt->at(0)), Muon_eta->at(0), Muon_phi->at(0),0.1056583745 );
    Muon2_PtResoUp.SetPtEtaPhiM((Muon_pt->at(1)+0.1*Muon_pt->at(1)), Muon_eta->at(1), Muon_phi->at(1),0.1056583745 );
    Muon1_PtResoDown.SetPtEtaPhiM((Muon_pt->at(0)-0.1*Muon_pt->at(0)), Muon_eta->at(0), Muon_phi->at(0),0.1056583745 );
    Muon2_PtResoDown.SetPtEtaPhiM((Muon_pt->at(1)-0.1*Muon_pt->at(1)), Muon_eta->at(1), Muon_phi->at(1),0.1056583745 );


   if (HLT_Mu == 1 && Muon_pt->at(0) > 150 && Muon_pt->at(1) > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(Muon_eta->at(1))<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1+Muon2).M()  > 300 ){

    BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
    BoostJet_JESup.SetPtEtaPhiE(BoostedJet_pt->at(1), BoostedJet_eta->at(1), BoostedJet_phi->at(1),BoostedJet_energy->at(1));
    BoostJet_JESdown.SetPtEtaPhiE(BoostedJet_pt->at(2), BoostedJet_eta->at(2), BoostedJet_phi->at(2),BoostedJet_energy->at(2));
    BoostJet_JERup.SetPtEtaPhiE(BoostedJet_pt->at(3), BoostedJet_eta->at(3), BoostedJet_phi->at(3),BoostedJet_energy->at(3));
    BoostJet_JERdown.SetPtEtaPhiE(BoostedJet_pt->at(4), BoostedJet_eta->at(4), BoostedJet_phi->at(4),BoostedJet_energy->at(4));


   DY_mumujj->Fill((Muon1+Muon2+BoostJet).M(), wg);
   //cout << "wg " << wg << " lumi " << lumi << " lumi_wgt " << lumi_wgt << " lepsf_evt " << lepsf_evt << " PUWeight " << PUWeight << endl;
   DY_mumujj_2017_AlphaRatio->Fill((Muon1+Muon2+BoostJet).M(), wg);
   DY_mumujj_2017_AlphaRatioUp->Fill((Muon1+Muon2+BoostJet).M(), wg);
   DY_mumujj_2017_AlphaRatioDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
   DY_mumujj_2017_SFUp->Fill((Muon1+Muon2+BoostJet).M(), wg_SFu);
   DY_mumujj_2017_SFDown->Fill((Muon1+Muon2+BoostJet).M(), wg_SFd);
   DY_mumujj_2017_PUUp->Fill((Muon1+Muon2+BoostJet).M(), wg_PUu);
   DY_mumujj_2017_PUDown->Fill((Muon1+Muon2+BoostJet).M(), wg_PUd);
   DY_mumujj_2017_PtResoUp->Fill((Muon1_PtResoUp+Muon2_PtResoUp+BoostJet).M(), wg);
   DY_mumujj_2017_PtResoDown->Fill((Muon1_PtResoDown+Muon2_PtResoDown+BoostJet).M(), wg);
  
   if(centralJesJer->at(0)==1)DY_mumujj_2017_centralJesJer->Fill((Muon1+Muon2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)DY_mumujj_2017_JesSFUp->Fill((Muon1+Muon2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)DY_mumujj_2017_JesSFDown->Fill((Muon1+Muon2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)DY_mumujj_2017_JerSFUp->Fill((Muon1+Muon2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)DY_mumujj_2017_JerSFDown->Fill((Muon1+Muon2+BoostJet_JERdown).M(), wg);
  }

//Zpeak DY cr Mll in 60-120 GeV
  if (HLT_Mu == 1 && Muon_pt->at(0) > 150 && Muon_pt->at(1) > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(Muon_eta->at(1))<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1+Muon2).M() > 60 && (Muon1+Muon2).M() < 120 ){
  BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
  BoostJet_JESup.SetPtEtaPhiE(BoostedJet_pt->at(1), BoostedJet_eta->at(1), BoostedJet_phi->at(1),BoostedJet_energy->at(1));
  BoostJet_JESdown.SetPtEtaPhiE(BoostedJet_pt->at(2), BoostedJet_eta->at(2), BoostedJet_phi->at(2),BoostedJet_energy->at(2));
  BoostJet_JERup.SetPtEtaPhiE(BoostedJet_pt->at(3), BoostedJet_eta->at(3), BoostedJet_phi->at(3),BoostedJet_energy->at(3));
  BoostJet_JERdown.SetPtEtaPhiE(BoostedJet_pt->at(4), BoostedJet_eta->at(4), BoostedJet_phi->at(4),BoostedJet_energy->at(4));
  DY_ZpeakMll_mumujj->Fill((Muon1+Muon2).M(), wg); 
  DY_Zpeak_mumujj->Fill((Muon1+Muon2+BoostJet).M(), wg); 
  DY_Zpeak_mumujj_2017_AlphaRatio->Fill((Muon1+Muon2+BoostJet).M(), wg);
  DY_Zpeak_mumujj_2017_AlphaRatioUp->Fill((Muon1+Muon2+BoostJet).M(), wg);
  DY_Zpeak_mumujj_2017_AlphaRatioDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
  DY_Zpeak_mumujj_2017_SFUp->Fill((Muon1+Muon2+BoostJet).M(), wg_SFu);
  DY_Zpeak_mumujj_2017_SFDown->Fill((Muon1+Muon2+BoostJet).M(), wg_SFd);
  DY_Zpeak_mumujj_2017_PUUp->Fill((Muon1+Muon2+BoostJet).M(), wg_PUu);
  DY_Zpeak_mumujj_2017_PUDown->Fill((Muon1+Muon2+BoostJet).M(), wg_PUd);
  DY_Zpeak_mumujj_2017_PtResoUp->Fill((Muon1_PtResoUp+Muon2_PtResoUp+BoostJet).M(), wg);
  DY_Zpeak_mumujj_2017_PtResoDown->Fill((Muon1_PtResoDown+Muon2_PtResoDown+BoostJet).M(), wg);
  if(centralJesJer->at(0)==1)DY_Zpeak_mumujj_centralJesJer->Fill((Muon1+Muon2+BoostJet).M(), wg);
  if(JesSFup->at(1)==1)DY_Zpeak_mumujj_2017_JesSFUp->Fill((Muon1+Muon2+BoostJet_JESup).M(), wg);
  if(JesSFdown->at(2)==1)DY_Zpeak_mumujj_2017_JesSFDown->Fill((Muon1+Muon2+BoostJet_JESdown).M(), wg);
  if(JerSFup->at(3)==1)DY_Zpeak_mumujj_2017_JerSFUp->Fill((Muon1+Muon2+BoostJet_JERup).M(), wg);
  if(JerSFdown->at(4)==1)DY_Zpeak_mumujj_2017_JerSFDown->Fill((Muon1+Muon2+BoostJet_JERdown).M(), wg);  
  }

    //DY cr Mll in 150-300 GeV
  if (HLT_Mu == 1 && Muon_pt->at(0) > 150 && Muon_pt->at(1) > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(Muon_eta->at(1))<2.4 && BoostedJet_pt->at(0) > 190 && (Muon1+Muon2).M() > 150 && (Muon1+Muon2).M() < 300 ){
  BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
  BoostJet_JESup.SetPtEtaPhiE(BoostedJet_pt->at(1), BoostedJet_eta->at(1), BoostedJet_phi->at(1),BoostedJet_energy->at(1));
  BoostJet_JESdown.SetPtEtaPhiE(BoostedJet_pt->at(2), BoostedJet_eta->at(2), BoostedJet_phi->at(2),BoostedJet_energy->at(2));
  BoostJet_JERup.SetPtEtaPhiE(BoostedJet_pt->at(3), BoostedJet_eta->at(3), BoostedJet_phi->at(3),BoostedJet_energy->at(3));
  BoostJet_JERdown.SetPtEtaPhiE(BoostedJet_pt->at(4), BoostedJet_eta->at(4), BoostedJet_phi->at(4),BoostedJet_energy->at(4));
  DY_DYcr_mumujj->Fill((Muon1+Muon2+BoostJet).M(), wg); 
  DY_DYcr_mumujj_2017_AlphaRatio->Fill((Muon1+Muon2+BoostJet).M(), wg);
  DY_DYcr_mumujj_2017_AlphaRatioUp->Fill((Muon1+Muon2+BoostJet).M(), wg);
  DY_DYcr_mumujj_2017_AlphaRatioDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
  DY_DYcr_mumujj_2017_SFUp->Fill((Muon1+Muon2+BoostJet).M(), wg_SFu);
  DY_DYcr_mumujj_2017_SFDown->Fill((Muon1+Muon2+BoostJet).M(), wg_SFd);
  DY_DYcr_mumujj_2017_PUUp->Fill((Muon1+Muon2+BoostJet).M(), wg_PUu);
  DY_DYcr_mumujj_2017_PUDown->Fill((Muon1+Muon2+BoostJet).M(), wg_PUd);
  DY_DYcr_mumujj_2017_PtResoUp->Fill((Muon1_PtResoUp+Muon2_PtResoUp+BoostJet).M(), wg);
  DY_DYcr_mumujj_2017_PtResoDown->Fill((Muon1_PtResoDown+Muon2_PtResoDown+BoostJet).M(), wg);
  if(centralJesJer->at(0)==1)DY_DYcr_mumujj_centralJesJer->Fill((Muon1+Muon2+BoostJet).M(), wg);
  if(JesSFup->at(1)==1)DY_DYcr_mumujj_2017_JesSFUp->Fill((Muon1+Muon2+BoostJet_JESup).M(), wg);
  if(JesSFdown->at(2)==1)DY_DYcr_mumujj_2017_JesSFDown->Fill((Muon1+Muon2+BoostJet_JESdown).M(), wg);
  if(JerSFup->at(3)==1)DY_DYcr_mumujj_2017_JerSFUp->Fill((Muon1+Muon2+BoostJet_JERup).M(), wg);
  if(JerSFdown->at(4)==1)DY_DYcr_mumujj_2017_JerSFDown->Fill((Muon1+Muon2+BoostJet_JERdown).M(), wg);  
  }

 }

  if (patElectron_pt->size() > 1 && numOfHighptEle==2 && numOfLooseMu==0 && numOfBoostedJets>=1){
   Electron1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   Electron2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energy->at(1));
  

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

   DY_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_eejj_2017_AlphaRatio->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_eejj_2017_AlphaRatioUp->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_eejj_2017_AlphaRatioDown->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_eejj_2017_SFUp->Fill((Electron1+Electron2+BoostJet).M(), wg_SFu);
   DY_eejj_2017_SFDown->Fill((Electron1+Electron2+BoostJet).M(), wg_SFd);
   DY_eejj_2017_PUUp->Fill((Electron1+Electron2+BoostJet).M(), wg_PUu);
   DY_eejj_2017_PUDown->Fill((Electron1+Electron2+BoostJet).M(), wg_PUd);
   DY_eejj_2017_energyScaleUp->Fill((Ele1_ScaleUp+Ele2_ScaleUp+BoostJet).M(), wg);
   DY_eejj_2017_energyScaleDown->Fill((Ele1_ScaleDown+Ele2_ScaleDown+BoostJet).M(), wg);
   DY_eejj_2017_energySigmaUp->Fill((Ele1_SigmaUp+Ele2_SigmaUp+BoostJet).M(), wg);
   DY_eejj_2017_energySigmaDown->Fill((Ele1_SigmaDown+Ele2_SigmaDown+BoostJet).M(), wg);
   if(centralJesJer->at(0)==1)DY_eejj_2017_centralJesJer->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)DY_eejj_2017_JesSFUp->Fill((Electron1+Electron2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)DY_eejj_2017_JesSFDown->Fill((Electron1+Electron2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)DY_eejj_2017_JerSFUp->Fill((Electron1+Electron2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)DY_eejj_2017_JerSFDown->Fill((Electron1+Electron2+BoostJet_JERdown).M(), wg);
  }

  //Zpeak DY cr 60-120 GeV
  if (HLT_Ele == 1 && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190 && (Electron1+Electron2).M() >60 && (Electron1+Electron2).M() < 120){
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
   DY_ZpeakMll_eejj->Fill((Electron1+Electron2).M(), wg);
   DY_Zpeak_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_Zpeak_eejj_2017_AlphaRatio->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_Zpeak_eejj_2017_AlphaRatioUp->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_Zpeak_eejj_2017_AlphaRatioDown->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_Zpeak_eejj_2017_SFUp->Fill((Electron1+Electron2+BoostJet).M(), wg_SFu);
   DY_Zpeak_eejj_2017_SFDown->Fill((Electron1+Electron2+BoostJet).M(), wg_SFd);
   DY_Zpeak_eejj_2017_PUUp->Fill((Electron1+Electron2+BoostJet).M(), wg_PUu);
   DY_Zpeak_eejj_2017_PUDown->Fill((Electron1+Electron2+BoostJet).M(), wg_PUd);
   DY_Zpeak_eejj_2017_energyScaleUp->Fill((Ele1_ScaleUp+Ele2_ScaleUp+BoostJet).M(), wg);
   DY_Zpeak_eejj_2017_energyScaleDown->Fill((Ele1_ScaleDown+Ele2_ScaleDown+BoostJet).M(), wg);
   DY_Zpeak_eejj_2017_energySigmaUp->Fill((Ele1_SigmaUp+Ele2_SigmaUp+BoostJet).M(), wg);
   DY_Zpeak_eejj_2017_energySigmaDown->Fill((Ele1_SigmaDown+Ele2_SigmaDown+BoostJet).M(), wg);
   if(centralJesJer->at(0)==1)DY_Zpeak_eejj_centralJesJer->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)DY_Zpeak_eejj_2017_JesSFUp->Fill((Electron1+Electron2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)DY_Zpeak_eejj_2017_JesSFDown->Fill((Electron1+Electron2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)DY_Zpeak_eejj_2017_JerSFUp->Fill((Electron1+Electron2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)DY_Zpeak_eejj_2017_JerSFDown->Fill((Electron1+Electron2+BoostJet_JERdown).M(), wg); 
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
   DY_DYcr_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_DYcr_eejj_2017_AlphaRatio->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_DYcr_eejj_2017_AlphaRatioUp->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_DYcr_eejj_2017_AlphaRatioDown->Fill((Electron1+Electron2+BoostJet).M(), wg);
   DY_DYcr_eejj_2017_SFUp->Fill((Electron1+Electron2+BoostJet).M(), wg_SFu);
   DY_DYcr_eejj_2017_SFDown->Fill((Electron1+Electron2+BoostJet).M(), wg_SFd);
   DY_DYcr_eejj_2017_PUUp->Fill((Electron1+Electron2+BoostJet).M(), wg_PUu);
   DY_DYcr_eejj_2017_PUDown->Fill((Electron1+Electron2+BoostJet).M(), wg_PUd);
   DY_DYcr_eejj_2017_energyScaleUp->Fill((Ele1_ScaleUp+Ele2_ScaleUp+BoostJet).M(), wg);
   DY_DYcr_eejj_2017_energyScaleDown->Fill((Ele1_ScaleDown+Ele2_ScaleDown+BoostJet).M(), wg);
   DY_DYcr_eejj_2017_energySigmaUp->Fill((Ele1_SigmaUp+Ele2_SigmaUp+BoostJet).M(), wg);
   DY_DYcr_eejj_2017_energySigmaDown->Fill((Ele1_SigmaDown+Ele2_SigmaDown+BoostJet).M(), wg);
   if(centralJesJer->at(0)==1)DY_DYcr_eejj_centralJesJer->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)DY_DYcr_eejj_2017_JesSFUp->Fill((Electron1+Electron2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)DY_DYcr_eejj_2017_JesSFDown->Fill((Electron1+Electron2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)DY_DYcr_eejj_2017_JerSFUp->Fill((Electron1+Electron2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)DY_DYcr_eejj_2017_JerSFDown->Fill((Electron1+Electron2+BoostJet_JERdown).M(), wg); 
  }
  
 }  
  
}


/**** adding the Alpha ratio and it's uncertainty*******/
/* alpha ratio and it's statistical error, bin per bin*/
const double Alpha_ele[9] = {1,1,0.94, 0.76, 0.77, 0.75, 0.82, 1.43, 1};
const double dAlpha_ele[9] ={0,0,0.08, 0.03, 0.03, 0.04, 0.08, 0.43, 0};
const double Alpha_mu[9] = {1,1,0.74, 0.79, 0.79, 0.76, 0.91, 1.26, 1}; //last bin is actually 0.86
const double dAlpha_mu[9] ={0,0,0.06, 0.03, 0.03, 0.03, 0.08, 0.28, 0}; //last bin error is actually 1.1
for (Int_t j=1;j<=9;j++) {
/*electron channel histograms*/
//    cout<< DY_eejj_2017_SFUp->GetBinContent(j) <<endl;
//    cout<< DY_eejj_2017_AlphaRatio->GetBinContent(j) <<endl;
 //   cout<< DY_eejj_2017_SFDown->GetBinContent(j) <<endl;
//    cout<<"================"<<endl; 
//    cout<<"================"<<endl; 

    double alpha_ele=Alpha_ele[j-1];
    double dalpha_ele=dAlpha_ele[j-1];
    DY_eejj_2017_AlphaRatio->SetBinContent(j, DY_eejj_2017_AlphaRatio->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_AlphaRatioUp->SetBinContent(j, DY_eejj_2017_AlphaRatioUp->GetBinContent(j) * (alpha_ele+dalpha_ele));
    DY_eejj_2017_AlphaRatioDown->SetBinContent(j, DY_eejj_2017_AlphaRatioDown->GetBinContent(j) * (alpha_ele-dalpha_ele));
    DY_eejj_2017_SFUp->SetBinContent(j, DY_eejj_2017_SFUp->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_SFDown->SetBinContent(j, DY_eejj_2017_SFDown->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_PUUp->SetBinContent(j, DY_eejj_2017_PUUp->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_PUDown->SetBinContent(j, DY_eejj_2017_PUDown->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_energyScaleUp->SetBinContent(j, DY_eejj_2017_energyScaleUp->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_energyScaleDown->SetBinContent(j, DY_eejj_2017_energyScaleDown->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_energySigmaUp->SetBinContent(j, DY_eejj_2017_energySigmaUp->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_energySigmaDown->SetBinContent(j, DY_eejj_2017_energySigmaDown->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_centralJesJer->SetBinContent(j, DY_eejj_2017_centralJesJer->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_JesSFUp->SetBinContent(j, DY_eejj_2017_JesSFUp->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_JesSFDown->SetBinContent(j, DY_eejj_2017_JesSFDown->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_JerSFUp->SetBinContent(j, DY_eejj_2017_JerSFUp->GetBinContent(j) * alpha_ele);
    DY_eejj_2017_JerSFDown->SetBinContent(j, DY_eejj_2017_JerSFDown->GetBinContent(j) * alpha_ele);
  /* debugging ele*/
//    cout<< DY_eejj_2017_SFUp->GetBinContent(j) <<endl;
//    cout<< DY_eejj_2017_AlphaRatio->GetBinContent(j) <<endl;
//    cout<< DY_eejj_2017_SFDown->GetBinContent(j) <<endl;
//    cout<<"================"<<endl; 

 // cout<< DY_eejj_2017_AlphaRatio->GetBinContent(j)/DY_eejj->GetBinContent(j) <<endl;
 // cout<< DY_eejj_2017_AlphaRatioDown->GetBinContent(j)/DY_eejj->GetBinContent(j) <<endl;
 // cout<<"================"<<endl; 
    //DY CR 150-300 GeV
    DY_DYcr_eejj_2017_AlphaRatio->SetBinContent(j, DY_DYcr_eejj_2017_AlphaRatio->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_AlphaRatioUp->SetBinContent(j, DY_DYcr_eejj_2017_AlphaRatioUp->GetBinContent(j) * (alpha_ele+dalpha_ele));
    DY_DYcr_eejj_2017_AlphaRatioDown->SetBinContent(j, DY_DYcr_eejj_2017_AlphaRatioDown->GetBinContent(j) * (alpha_ele-dalpha_ele));
    DY_DYcr_eejj_2017_SFUp->SetBinContent(j, DY_DYcr_eejj_2017_SFUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_SFDown->SetBinContent(j, DY_DYcr_eejj_2017_SFDown->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_PUUp->SetBinContent(j, DY_DYcr_eejj_2017_PUUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_PUDown->SetBinContent(j, DY_DYcr_eejj_2017_PUDown->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_energyScaleUp->SetBinContent(j, DY_DYcr_eejj_2017_energyScaleUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_energyScaleDown->SetBinContent(j, DY_DYcr_eejj_2017_energyScaleDown->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_energySigmaUp->SetBinContent(j, DY_DYcr_eejj_2017_energySigmaUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_energySigmaDown->SetBinContent(j, DY_DYcr_eejj_2017_energySigmaDown->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_centralJesJer->SetBinContent(j, DY_DYcr_eejj_centralJesJer->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_JesSFUp->SetBinContent(j, DY_DYcr_eejj_2017_JesSFUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_JesSFDown->SetBinContent(j, DY_DYcr_eejj_2017_JesSFDown->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_JerSFUp->SetBinContent(j, DY_DYcr_eejj_2017_JerSFUp->GetBinContent(j) * alpha_ele);
    DY_DYcr_eejj_2017_JerSFDown->SetBinContent(j, DY_DYcr_eejj_2017_JerSFDown->GetBinContent(j) * alpha_ele);

/* muon channel histograms*/
    double alpha_mu=Alpha_mu[j-1];
    double dalpha_mu=dAlpha_mu[j-1];
    DY_mumujj_2017_AlphaRatio->SetBinContent(j, DY_mumujj_2017_AlphaRatio->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_AlphaRatioUp->SetBinContent(j, DY_mumujj_2017_AlphaRatioUp->GetBinContent(j) * (alpha_mu+dalpha_mu));
    DY_mumujj_2017_AlphaRatioDown->SetBinContent(j, DY_mumujj_2017_AlphaRatioDown->GetBinContent(j) * (alpha_mu-dalpha_mu));
    DY_mumujj_2017_SFUp->SetBinContent(j, DY_mumujj_2017_SFUp->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_SFDown->SetBinContent(j, DY_mumujj_2017_SFDown->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_PUUp->SetBinContent(j, DY_mumujj_2017_PUUp->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_PUDown->SetBinContent(j, DY_mumujj_2017_PUDown->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_PtResoUp->SetBinContent(j, DY_mumujj_2017_PtResoUp->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_PtResoDown->SetBinContent(j, DY_mumujj_2017_PtResoDown->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_centralJesJer->SetBinContent(j, DY_mumujj_2017_centralJesJer->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_JesSFUp->SetBinContent(j, DY_mumujj_2017_JesSFUp->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_JesSFDown->SetBinContent(j, DY_mumujj_2017_JesSFDown->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_JerSFUp->SetBinContent(j, DY_mumujj_2017_JerSFUp->GetBinContent(j) * alpha_mu);
    DY_mumujj_2017_JerSFDown->SetBinContent(j, DY_mumujj_2017_JerSFDown->GetBinContent(j) * alpha_mu);
  /* debugging muons*/
 //cout<< DY_mumujj_2017_AlphaRatio->GetBinContent(j)/DY_mumujj->GetBinContent(j) <<endl;
 // cout<< DY_mumujj_2017_AlphaRatioUp->GetBinContent(j)/DY_mumujj->GetBinContent(j) <<endl;
 // cout<< DY_mumujj_2017_AlphaRatioDown->GetBinContent(j)/DY_mumujj->GetBinContent(j) <<endl;
 // cout<<"================"<<endl; 
 // cout<<"================"<<endl; 

     //DY CR 150-300 GeV
    DY_DYcr_mumujj_2017_AlphaRatio->SetBinContent(j, DY_DYcr_mumujj_2017_AlphaRatio->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_AlphaRatioUp->SetBinContent(j, DY_DYcr_mumujj_2017_AlphaRatioUp->GetBinContent(j) * (alpha_mu+dalpha_mu));
    DY_DYcr_mumujj_2017_AlphaRatioDown->SetBinContent(j, DY_DYcr_mumujj_2017_AlphaRatioDown->GetBinContent(j) * (alpha_mu-dalpha_mu));
    DY_DYcr_mumujj_2017_SFUp->SetBinContent(j, DY_DYcr_mumujj_2017_SFUp->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_SFDown->SetBinContent(j, DY_DYcr_mumujj_2017_SFDown->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_PUUp->SetBinContent(j, DY_DYcr_mumujj_2017_PUUp->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_PUDown->SetBinContent(j, DY_DYcr_mumujj_2017_PUDown->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_PtResoUp->SetBinContent(j, DY_DYcr_mumujj_2017_PtResoUp->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_PtResoDown->SetBinContent(j, DY_DYcr_mumujj_2017_PtResoDown->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_centralJesJer->SetBinContent(j, DY_DYcr_mumujj_centralJesJer->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_JesSFUp->SetBinContent(j, DY_DYcr_mumujj_2017_JesSFUp->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_JesSFDown->SetBinContent(j, DY_DYcr_mumujj_2017_JesSFDown->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_JerSFUp->SetBinContent(j, DY_DYcr_mumujj_2017_JerSFUp->GetBinContent(j) * alpha_mu);
    DY_DYcr_mumujj_2017_JerSFDown->SetBinContent(j, DY_DYcr_mumujj_2017_JerSFDown->GetBinContent(j) * alpha_mu);

}
/********/



TFile *f = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2017_fixMuon/SR_syst_DY_Kewkqcd_2017.root", "RECREATE");
//TFile *f = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2017-OldBinning/SR_syst_DY_FxFx_2017.root", "RECREATE");
//TFile *f2 = new TFile("SR_syst_DY_2017.root", "RECREATE");

DY_eejj->Write();
DY_eejj_2017_AlphaRatio->Write();
DY_eejj_2017_AlphaRatioUp->Write();
DY_eejj_2017_AlphaRatioDown->Write();
DY_eejj_2017_SFUp->Write();
DY_eejj_2017_SFDown->Write();
DY_eejj_2017_PUUp->Write();
DY_eejj_2017_PUDown->Write();
DY_eejj_2017_centralJesJer->Write();
DY_eejj_2017_JesSFUp->Write();
DY_eejj_2017_JesSFDown->Write();
DY_eejj_2017_JerSFUp->Write();
DY_eejj_2017_JerSFDown->Write();
DY_eejj_2017_energyScaleUp->Write();
DY_eejj_2017_energyScaleDown->Write();
DY_eejj_2017_energySigmaUp->Write();
DY_eejj_2017_energySigmaDown->Write();

DY_mumujj->Write();
DY_mumujj_2017_AlphaRatio->Write();
DY_mumujj_2017_AlphaRatioUp->Write();
DY_mumujj_2017_AlphaRatioDown->Write();
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

//Zpeak DYcr 
DY_ZpeakMll_eejj->Write();
DY_ZpeakMll_mumujj->Write();
DY_Zpeak_eejj->Write();
DY_Zpeak_eejj_2017_AlphaRatio->Write();
DY_Zpeak_eejj_2017_AlphaRatioUp->Write();
DY_Zpeak_eejj_2017_AlphaRatioDown->Write();
DY_Zpeak_eejj_2017_SFUp->Write();
DY_Zpeak_eejj_2017_SFDown->Write();
DY_Zpeak_eejj_2017_PUUp->Write();
DY_Zpeak_eejj_2017_PUDown->Write();
DY_Zpeak_eejj_centralJesJer->Write();
DY_Zpeak_eejj_2017_JesSFUp->Write();
DY_Zpeak_eejj_2017_JesSFDown->Write();
DY_Zpeak_eejj_2017_JerSFUp->Write();
DY_Zpeak_eejj_2017_JerSFDown->Write();
DY_Zpeak_eejj_2017_energyScaleUp->Write();
DY_Zpeak_eejj_2017_energyScaleDown->Write();
DY_Zpeak_eejj_2017_energySigmaUp->Write();
DY_Zpeak_eejj_2017_energySigmaDown->Write();
DY_Zpeak_mumujj->Write();
DY_Zpeak_mumujj_2017_AlphaRatio->Write();
DY_Zpeak_mumujj_2017_AlphaRatioUp->Write();
DY_Zpeak_mumujj_2017_AlphaRatioDown->Write();
DY_Zpeak_mumujj_2017_SFUp->Write();
DY_Zpeak_mumujj_2017_SFDown->Write();
DY_Zpeak_mumujj_2017_PUUp->Write();
DY_Zpeak_mumujj_2017_PUDown->Write();
DY_Zpeak_mumujj_centralJesJer->Write();
DY_Zpeak_mumujj_2017_JesSFUp->Write();
DY_Zpeak_mumujj_2017_JesSFDown->Write();
DY_Zpeak_mumujj_2017_JerSFUp->Write();
DY_Zpeak_mumujj_2017_JerSFDown->Write();
DY_Zpeak_mumujj_2017_PtResoUp->Write();
DY_Zpeak_mumujj_2017_PtResoDown->Write();

//DYcr 
DY_DYcr_eejj->Write();
DY_DYcr_eejj_2017_AlphaRatio->Write();
DY_DYcr_eejj_2017_AlphaRatioUp->Write();
DY_DYcr_eejj_2017_AlphaRatioDown->Write();
DY_DYcr_eejj_2017_SFUp->Write();
DY_DYcr_eejj_2017_SFDown->Write();
DY_DYcr_eejj_2017_PUUp->Write();
DY_DYcr_eejj_2017_PUDown->Write();
DY_DYcr_eejj_centralJesJer->Write();
DY_DYcr_eejj_2017_JesSFUp->Write();
DY_DYcr_eejj_2017_JesSFDown->Write();
DY_DYcr_eejj_2017_JerSFUp->Write();
DY_DYcr_eejj_2017_JerSFDown->Write();
DY_DYcr_eejj_2017_energyScaleUp->Write();
DY_DYcr_eejj_2017_energyScaleDown->Write();
DY_DYcr_eejj_2017_energySigmaUp->Write();
DY_DYcr_eejj_2017_energySigmaDown->Write();
DY_DYcr_mumujj->Write();
DY_DYcr_mumujj_2017_AlphaRatio->Write();
DY_DYcr_mumujj_2017_AlphaRatioUp->Write();
DY_DYcr_mumujj_2017_AlphaRatioDown->Write();
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


f->Write();
f->Close();

}
 
