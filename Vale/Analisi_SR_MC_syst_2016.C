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

double deltaPhi(double phi1, double phi2);

double deltaPhi(double phi1, double phi2) {
 double result = phi1 - phi2;
 while (result > M_PI) result -= 2*M_PI;
 while (result <= -M_PI) result += 2*M_PI;
 return result;
}


//void filename_()
void Analisi_SR_MC_syst_2016(){

TChain *a_ = new TChain("BOOM");

a_->Add("/eos/user/v/vmariani/NTuples/HN_2016/Syst_ALL_newMuonSF/mumujj_L13_M8000_2016.root");

int HLT_Ele, HLT_Mu, HLT_Mu50, HLT_TkMu50;
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
vector<double>* Muon_relIsoDeltaBetaR04; Muon_relIsoDeltaBetaR04=0;
vector<double>* Muon_energy; Muon_energy=0;
vector<double>* Muon_charge; Muon_charge=0;
vector<double>*BoostedJet_pt; BoostedJet_pt=0;
vector<double>*BoostedJet_eta; BoostedJet_eta=0;
vector<double>*BoostedJet_phi; BoostedJet_phi=0;
vector<double>*BoostedJet_energy; BoostedJet_energy=0;
vector<double>*Jet_pt; Jet_pt=0;
vector<double>*Jet_eta; Jet_eta=0;
vector<double>*Jet_phi; Jet_phi=0;
vector<double>*Jet_energy; Jet_energy=0;
double PUWeight, MinBiasUpWeight, MinBiasDownWeight;
double lepsf_evt, lepsf_evt_u, lepsf_evt_d; 
double numOfHighptEle, numOfVetoEle, numOfHighptMu, numOfLooseMu, numOfBoostedJets, numOfJets;
double lumi_wgt, trueInteractions;
vector<double>*centralJesJer; centralJesJer=0;
vector<double>*JesSFup; JesSFup=0;
vector<double>*JesSFdown; JesSFdown=0;
vector<double>*JerSFup; JerSFup=0;
vector<double>*JerSFdown; JerSFdown=0;
int nBestVtx;

TBranch *a_HLT_Ele115_CaloIdVT_GsfTrkIdT=a_->GetBranch("HLT_Ele115_CaloIdVT_GsfTrkIdT");
TBranch *a_HLT_Mu50=a_->GetBranch("HLT_Mu50");
TBranch *a_HLT_TkMu50=a_->GetBranch("HLT_TkMu50");

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
TBranch *a_Muon_relIsoDeltaBetaR04=a_->GetBranch("Muon_relIsoDeltaBetaR04");

TBranch *a_BoostedJet_pt=a_->GetBranch("BoostedJet_pt");
TBranch *a_BoostedJet_eta=a_->GetBranch("BoostedJet_eta");
TBranch *a_BoostedJet_phi=a_->GetBranch("BoostedJet_phi");
TBranch *a_BoostedJet_energy=a_->GetBranch("BoostedJet_energy");

TBranch *a_Jet_pt=a_->GetBranch("Jet_pt");
TBranch *a_Jet_eta=a_->GetBranch("Jet_eta");
TBranch *a_Jet_phi=a_->GetBranch("Jet_phi");
TBranch *a_Jet_energy=a_->GetBranch("Jet_energy");

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
TBranch *a_numOfJets=a_->GetBranch("numOfJets");
TBranch *a_numOfVetoEle=a_->GetBranch("numOfVetoEle");

TBranch *a_centralJesJer=a_->GetBranch("centralJesJer");
TBranch *a_JesSFup=a_->GetBranch("JesSFup");
TBranch *a_JesSFdown=a_->GetBranch("JesSFdown");
TBranch *a_JerSFup=a_->GetBranch("JerSFup");
TBranch *a_JerSFdown=a_->GetBranch("JerSFdown");

a_HLT_Ele115_CaloIdVT_GsfTrkIdT->SetAddress(&HLT_Ele);
a_HLT_Mu50->SetAddress(&HLT_Mu50);
a_HLT_TkMu50->SetAddress(&HLT_TkMu50);

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
a_Muon_relIsoDeltaBetaR04->SetAddress(&Muon_relIsoDeltaBetaR04);

a_lepsf_evt->SetAddress(&lepsf_evt);
a_lepsf_evt_u->SetAddress(&lepsf_evt_u);
a_lepsf_evt_d->SetAddress(&lepsf_evt_d);
a_lumi_wgt->SetAddress(&lumi_wgt);

a_BoostedJet_pt->SetAddress(&BoostedJet_pt);
a_BoostedJet_eta->SetAddress(&BoostedJet_eta);
a_BoostedJet_phi->SetAddress(&BoostedJet_phi);
a_BoostedJet_energy->SetAddress(&BoostedJet_energy);

a_Jet_pt->SetAddress(&Jet_pt);
a_Jet_eta->SetAddress(&Jet_eta);
a_Jet_phi->SetAddress(&Jet_phi);
a_Jet_energy->SetAddress(&Jet_energy);

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
a_numOfJets->SetAddress(&numOfJets);
a_numOfVetoEle->SetAddress(&numOfVetoEle);

a_centralJesJer->SetAddress(&centralJesJer);
a_JesSFup->SetAddress(&JesSFup);
a_JesSFdown->SetAddress(&JesSFdown);
a_JerSFup->SetAddress(&JerSFup);
a_JerSFdown->SetAddress(&JerSFdown);

//new bins
//const double asymbins[9] = {0,200,400,600,800,1000,1400,2000,10000};

//old bins
const double asymbins[10] = {0,200,400,600,800,1000,1400,2000,3500,10000};

TH1D *deltaRmu1FJ1 = new TH1D ("deltaRmu1FJ1", "deltaRmu1FJ1", 100, 0, 20);
TH1D *deltaRmu1FJ2 = new TH1D ("deltaRmu1FJ2", "deltaRmu1FJ2", 100, 0, 20);
TH1D *deltaRmu2FJ1 = new TH1D ("deltaRmu2FJ1", "deltaRmu2FJ1", 100, 0, 20);
TH1D *deltaRmu2FJ2 = new TH1D ("deltaRmu2FJ2", "deltaRmu2FJ2", 100, 0, 20);
TH1D *MllJJ = new TH1D ("MllJJ", "MllJJ", 9, asymbins);
TH1D *MllJ = new TH1D ("MllJ", "MllJ", 9, asymbins);
TH1D *MllJ_FJ1 = new TH1D ("MllJ_FJ1", "MllJ_FJ1", 9, asymbins);
TH1D *NumFatJet = new TH1D ("NumFatJet", "NumFatJet", 20, 0, 20);
TH1D *NumJet = new TH1D ("NumJet", "NumJet", 20, 0, 20);
TH1D *Mlljj = new TH1D ("Mlljj", "Mlljj", 9, asymbins);
TH1D *deltaPhijj = new TH1D ("deltaPhijj", "deltaPhijj", 60, -3, 3);
TH1D *deltaEtajj = new TH1D ("deltaEtajj", "deltaEtajj", 60, 0, 3);
TH1D *deltaRjj = new TH1D ("deltaRjj", "deltaRjj", 100, 0, 20);
TH1D *deltaRmu12 = new TH1D ("deltaRmu12", "deltaRmu12", 100, 0, 20);
TH1D *Mu1_pt = new TH1D ("Mu1_pt", "Mu1_pt", 1000, 0, 10000);
TH1D *Mu2_pt = new TH1D ("Mu2_pt", "Mu2_pt", 1000, 0, 10000); 
TH1D *Mu1_relIso = new TH1D ("Mu1_relIso", "Mu1_relIso", 100, 0, 10);
TH1D *Mu2_relIso = new TH1D ("Mu2_relIso", "Mu2_relIso", 100, 0, 10);

TH1D *mumujj_L13_M8000_mumujj = new TH1D ("mumujj_L13_M8000_mumujj", "mumujj_L13_M8000_mumujj", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2016_AlphaRatio = new TH1D ("mumujj_L13_M8000_mumujj_2016_AlphaRatio", "mumujj_L13_M8000_mumujj_2016_AlphaRatio", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2016_AlphaRatioUp = new TH1D ("mumujj_L13_M8000_mumujj_2016_AlphaRatioUp", "mumujj_L13_M8000_mumujj_2016_AlphaRatioUp", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2016_AlphaRatioDown = new TH1D ("mumujj_L13_M8000_mumujj_2016_AlphaRatioDown", "mumujj_L13_M8000_mumujj_2016_AlphaRatioDown", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2016_SFUp = new TH1D ("mumujj_L13_M8000_mumujj_2016_SFUp", "mumujj_L13_M8000_mumujj_2016_SFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2016_SFDown = new TH1D ("mumujj_L13_M8000_mumujj_2016_SFDown", "mumujj_L13_M8000_mumujj_2016_SFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2016_PUUp = new TH1D ("mumujj_L13_M8000_mumujj_2016_PUUp", "mumujj_L13_M8000_mumujj_2016_PUUp", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2016_PUDown = new TH1D ("mumujj_L13_M8000_mumujj_2016_PUDown", "mumujj_L13_M8000_mumujj_2016_PUDown", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_centralJesJer = new TH1D ("mumujj_L13_M8000_mumujj_centralJesJer", "mumujj_L13_M8000_mumujj_centralJesJer", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2016_JesSFUp = new TH1D ("mumujj_L13_M8000_mumujj_2016_JesSFUp", "mumujj_L13_M8000_mumujj_2016_JesSFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2016_JesSFDown = new TH1D ("mumujj_L13_M8000_mumujj_2016_JesSFDown", "mumujj_L13_M8000_mumujj_2016_JesSFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2016_JerSFUp = new TH1D ("mumujj_L13_M8000_mumujj_2016_JerSFUp", "mumujj_L13_M8000_mumujj_2016_JerSFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2016_JerSFDown = new TH1D ("mumujj_L13_M8000_mumujj_2016_JerSFDown", "mumujj_L13_M8000_mumujj_2016_JerSFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2016_PtCorrUp = new TH1D ("mumujj_L13_M8000_mumujj_2016_PtCorrUp", "mumujj_L13_M8000_mumujj_2016_PtCorrUp", 9, asymbins);
TH1D *mumujj_L13_M8000_mumujj_2016_PtCorrDown = new TH1D ("mumujj_L13_M8000_mumujj_2016_PtCorrDown", "mumujj_L13_M8000_mumujj_2016_PtCorrDown", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj = new TH1D ("mumujj_L13_M8000_eejj", "mumujj_L13_M8000_eejj", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2016_AlphaRatio = new TH1D ("mumujj_L13_M8000_eejj_2016_AlphaRatio", "mumujj_L13_M8000_eejj_2016_AlphaRatio", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2016_AlphaRatioUp = new TH1D ("mumujj_L13_M8000_eejj_2016_AlphaRatioUp", "mumujj_L13_M8000_eejj_2016_AlphaRatioUp", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2016_AlphaRatioDown = new TH1D ("mumujj_L13_M8000_eejj_2016_AlphaRatioDown", "mumujj_L13_M8000_eejj_2016_AlphaRatioDown", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2016_SFUp = new TH1D ("mumujj_L13_M8000_eejj_2016_SFUp", "mumujj_L13_M8000_eejj_2016_SFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2016_SFDown = new TH1D ("mumujj_L13_M8000_eejj_2016_SFDown", "mumujj_L13_M8000_eejj_2016_SFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2016_PUUp = new TH1D ("mumujj_L13_M8000_eejj_2016_PUUp", "mumujj_L13_M8000_eejj_2016_PUUp", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2016_PUDown = new TH1D ("mumujj_L13_M8000_eejj_2016_PUDown", "mumujj_L13_M8000_eejj_2016_PUDown", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_centralJesJer = new TH1D ("mumujj_L13_M8000_eejj_centralJesJer", "mumujj_L13_M8000_eejj_centralJesJer", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2016_JesSFUp = new TH1D ("mumujj_L13_M8000_eejj_2016_JesSFUp", "mumujj_L13_M8000_eejj_2016_JesSFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2016_JesSFDown = new TH1D ("mumujj_L13_M8000_eejj_2016_JesSFDown", "mumujj_L13_M8000_eejj_2016_JesSFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2016_JerSFUp = new TH1D ("mumujj_L13_M8000_eejj_2016_JerSFUp", "mumujj_L13_M8000_eejj_2016_JerSFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2016_JerSFDown = new TH1D ("mumujj_L13_M8000_eejj_2016_JerSFDown", "mumujj_L13_M8000_eejj_2016_JerSFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2016_energyScaleUp = new TH1D ("mumujj_L13_M8000_eejj_2016_energyScaleUp", "mumujj_L13_M8000_eejj_2016_energyScaleUp", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2016_energyScaleDown = new TH1D ("mumujj_L13_M8000_eejj_2016_energyScaleDown", "mumujj_L13_M8000_eejj_2016_energyScaleDown", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2016_energySigmaUp = new TH1D ("mumujj_L13_M8000_eejj_2016_energySigmaUp", "mumujj_L13_M8000_eejj_2016_energySigmaUp", 9, asymbins);
TH1D *mumujj_L13_M8000_eejj_2016_energySigmaDown = new TH1D ("mumujj_L13_M8000_eejj_2016_energySigmaDown", "mumujj_L13_M8000_eejj_2016_energySigmaDown", 9, asymbins);

//PDF uncertaintes for signal samples
TH1D *mumujj_L13_M8000_mumujj_PDFUp = new TH1D ("mumujj_L13_M8000_mumujj_PDFUp", "mumujj_L13_M8000_mumujj_PDFUp", 9, asymbins);   //PDF
TH1D *mumujj_L13_M8000_mumujj_PDFDown = new TH1D ("mumujj_L13_M8000_mumujj_PDFDown", "mumujj_L13_M8000_mumujj_PDFDown", 9, asymbins); //PDF
TH1D *mumujj_L13_M8000_eejj_PDFUp = new TH1D ("mumujj_L13_M8000_eejj_PDFUp", "mumujj_L13_M8000_eejj_PDFUp", 9, asymbins); //PDF
TH1D *mumujj_L13_M8000_eejj_PDFDown = new TH1D ("mumujj_L13_M8000_eejj_PDFDown", "mumujj_L13_M8000_eejj_PDFDown", 9, asymbins); //PDF



//DY CR (mll in 150-300 GeV)
TH1D *mumujj_L13_M8000_DYcr_mumujj = new TH1D ("mumujj_L13_M8000_DYcr_mumujj", "mumujj_L13_M8000_DYcr_mumujj", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2016_AlphaRatio = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2016_AlphaRatio", "mumujj_L13_M8000_DYcr_mumujj_2016_AlphaRatio", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2016_AlphaRatioUp = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2016_AlphaRatioUp", "mumujj_L13_M8000_DYcr_mumujj_2016_AlphaRatioUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2016_AlphaRatioDown = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2016_AlphaRatioDown", "mumujj_L13_M8000_DYcr_mumujj_2016_AlphaRatioDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2016_SFUp = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2016_SFUp", "mumujj_L13_M8000_DYcr_mumujj_2016_SFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2016_SFDown = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2016_SFDown", "mumujj_L13_M8000_DYcr_mumujj_2016_SFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2016_PUUp = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2016_PUUp", "mumujj_L13_M8000_DYcr_mumujj_2016_PUUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2016_PUDown = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2016_PUDown", "mumujj_L13_M8000_DYcr_mumujj_2016_PUDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_centralJesJer = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_centralJesJer", "mumujj_L13_M8000_DYcr_mumujj_centralJesJer", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2016_JesSFUp = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2016_JesSFUp", "mumujj_L13_M8000_DYcr_mumujj_2016_JesSFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2016_JesSFDown = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2016_JesSFDown", "mumujj_L13_M8000_DYcr_mumujj_2016_JesSFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2016_JerSFUp = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2016_JerSFUp", "mumujj_L13_M8000_DYcr_mumujj_2016_JerSFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2016_JerSFDown = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2016_JerSFDown", "mumujj_L13_M8000_DYcr_mumujj_2016_JerSFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2016_PtCorrUp = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2016_PtCorrUp", "mumujj_L13_M8000_DYcr_mumujj_2016_PtCorrUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_mumujj_2016_PtCorrDown = new TH1D ("mumujj_L13_M8000_DYcr_mumujj_2016_PtCorrDown", "mumujj_L13_M8000_DYcr_mumujj_2016_PtCorrDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj = new TH1D ("mumujj_L13_M8000_DYcr_eejj", "mumujj_L13_M8000_DYcr_eejj", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2016_AlphaRatio = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2016_AlphaRatio", "mumujj_L13_M8000_DYcr_eejj_2016_AlphaRatio", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2016_AlphaRatioUp = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2016_AlphaRatioUp", "mumujj_L13_M8000_DYcr_eejj_2016_AlphaRatioUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2016_AlphaRatioDown = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2016_AlphaRatioDown", "mumujj_L13_M8000_DYcr_eejj_2016_AlphaRatioDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2016_SFUp = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2016_SFUp", "mumujj_L13_M8000_DYcr_eejj_2016_SFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2016_SFDown = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2016_SFDown", "mumujj_L13_M8000_DYcr_eejj_2016_SFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2016_PUUp = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2016_PUUp", "mumujj_L13_M8000_DYcr_eejj_2016_PUUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2016_PUDown = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2016_PUDown", "mumujj_L13_M8000_DYcr_eejj_2016_PUDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_centralJesJer = new TH1D ("mumujj_L13_M8000_DYcr_eejj_centralJesJer", "mumujj_L13_M8000_DYcr_eejj_centralJesJer", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2016_JesSFUp = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2016_JesSFUp", "mumujj_L13_M8000_DYcr_eejj_2016_JesSFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2016_JesSFDown = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2016_JesSFDown", "mumujj_L13_M8000_DYcr_eejj_2016_JesSFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2016_JerSFUp = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2016_JerSFUp", "mumujj_L13_M8000_DYcr_eejj_2016_JerSFUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2016_JerSFDown = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2016_JerSFDown", "mumujj_L13_M8000_DYcr_eejj_2016_JerSFDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2016_energyScaleUp = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2016_energyScaleUp", "mumujj_L13_M8000_DYcr_eejj_2016_energyScaleUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2016_energyScaleDown = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2016_energyScaleDown", "mumujj_L13_M8000_DYcr_eejj_2016_energyScaleDown", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2016_energySigmaUp = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2016_energySigmaUp", "mumujj_L13_M8000_DYcr_eejj_2016_energySigmaUp", 9, asymbins);
TH1D *mumujj_L13_M8000_DYcr_eejj_2016_energySigmaDown = new TH1D ("mumujj_L13_M8000_DYcr_eejj_2016_energySigmaDown", "mumujj_L13_M8000_DYcr_eejj_2016_energySigmaDown", 9, asymbins);


cout << a_->GetEntries() << endl;
int tot=0, muejj = 0;
double wg = 0, wg_2016_SFUp = 0, wg_2016_SFDown = 0, wg_2016_PUUp = 0, wg_2016_PUDown = 0;
int lumi = 35542;//2018: 58873 //2017: 41529 //2016: 35542
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
TLorentzVector BoostJet2;
TLorentzVector Jet1;
TLorentzVector Jet2;
TLorentzVector BoostJet_JESup;
TLorentzVector BoostJet_JESdown;
TLorentzVector BoostJet_JERup;
TLorentzVector BoostJet_JERdown;

double deltaEta_jj = 0, deltaPhi_jj = 0, deltaR_jj = 0;
double deltaEta_mu1FJ1 = 0, deltaEta_mu1FJ2 = 0, deltaEta_mu2FJ1 = 0, deltaEta_mu2FJ2 = 0;
double deltaPhi_mu1FJ1 = 0, deltaPhi_mu1FJ2 = 0, deltaPhi_mu2FJ1 = 0, deltaPhi_mu2FJ2 = 0;
double deltaR_mu1FJ1 = 0, deltaR_mu1FJ2 = 0, deltaR_mu2FJ1 = 0, deltaR_mu2FJ2 = 0;
double deltaR_mu12 = 0, deltaEta_mu12 = 0, deltaPhi_mu12 = 0;

for (Int_t i=0;i<a_->GetEntries();i++) {
 a_->GetEntry(i);
 HLT_Mu = 0; 
 tot = a_->GetEntries();
 if (i%100000 == 0) cout << i << " eventi analizzati su " << tot << endl;

 wg = lumi * lumi_wgt * lepsf_evt * PUWeight;
 wg_2016_SFUp = lumi * lumi_wgt * lepsf_evt_u * PUWeight;
 wg_2016_SFDown = lumi * lumi_wgt * lepsf_evt_d * PUWeight;
 wg_2016_PUUp = lumi * lumi_wgt * lepsf_evt * MinBiasUpWeight;
 wg_2016_PUDown = lumi * lumi_wgt * lepsf_evt * MinBiasDownWeight;
          
 if (HLT_Mu50==1 || HLT_TkMu50==1 ) HLT_Mu = 1;
 
 if (Muon_pt->size() > 1 && numOfHighptMu==2 && numOfVetoEle == 0 && numOfJets >=2){
  Muon1.SetPtEtaPhiE(Muon_pt->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));
  Muon2.SetPtEtaPhiE(Muon_pt->at(1), Muon_eta->at(1), Muon_phi->at(1),Muon_energy->at(1));
  Jet1.SetPtEtaPhiE(Jet_pt->at(0), Jet_eta->at(0), Jet_phi->at(0),Jet_energy->at(0));
  Jet2.SetPtEtaPhiE(Jet_pt->at(1), Jet_eta->at(1), Jet_phi->at(1),Jet_energy->at(1));

  if (HLT_Mu == 1 && Muon_pt->at(0) > 150 && Muon_pt->at(1) > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(Muon_eta->at(1))<2.4 && Jet_pt->at(0) > 40 && Jet_pt->at(1) > 40 && (Muon1+Muon2).M() > 300 ){  
   deltaEta_jj = fabs(Jet_eta->at(0) - Jet_eta->at(1));
   deltaPhi_jj = deltaPhi(Jet_phi->at(0), Jet_phi->at(1));
   deltaR_jj = sqrt(pow(deltaEta_jj,2) + pow(deltaPhi_jj,2)); 
   deltaRjj->Fill(deltaR_jj,wg);
   deltaEtajj->Fill(deltaEta_jj,wg);
   deltaPhijj->Fill(deltaPhi_jj,wg);
   NumJet->Fill(numOfJets,wg);
   Mlljj->Fill((Muon1+Muon2+Jet1+Jet2).M(),wg);
  }
 }

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
   if (numOfBoostedJets > 1) BoostJet2.SetPtEtaPhiE(BoostedJet_pt->at(5), BoostedJet_eta->at(5), BoostedJet_phi->at(5),BoostedJet_energy->at(5));
   NumFatJet->Fill(numOfBoostedJets,wg);

   deltaEta_mu2FJ1 =fabs(Muon_eta->at(1) - BoostedJet_eta->at(0));
   deltaPhi_mu2FJ1 = deltaPhi(Muon_phi->at(1), BoostedJet_phi->at(0));
   deltaR_mu2FJ1 = sqrt(pow(deltaEta_mu2FJ1,2) + pow(deltaPhi_mu2FJ1,2));
   deltaRmu2FJ1->Fill(deltaR_mu2FJ1,wg);
   
   deltaEta_mu1FJ1 = fabs(Muon_eta->at(0) - BoostedJet_eta->at(0));
   deltaPhi_mu1FJ1 = deltaPhi(Muon_phi->at(0),BoostedJet_phi->at(0));
   deltaR_mu1FJ1 = sqrt(pow(deltaEta_mu1FJ1,1) + pow(deltaPhi_mu1FJ1,2));
   deltaRmu1FJ1->Fill(deltaR_mu1FJ1,wg);

   deltaEta_mu12 = fabs(Muon_eta->at(0) - Muon_eta->at(1));
   deltaPhi_mu12 = deltaPhi(Muon_phi->at(0),Muon_phi->at(1));
   deltaR_mu12 = sqrt(pow(deltaEta_mu12,2) + pow(deltaPhi_mu12,2));
   deltaRmu12->Fill(deltaR_mu12,wg);

   if (numOfBoostedJets > 1){
   deltaEta_mu2FJ2 =fabs(Muon_eta->at(1) - BoostedJet_eta->at(5));
   deltaPhi_mu2FJ2 = deltaPhi(Muon_phi->at(1), BoostedJet_phi->at(5));
   deltaR_mu2FJ2 = sqrt(pow(deltaEta_mu2FJ2,2) + pow(deltaPhi_mu2FJ2,2));
   deltaRmu2FJ2->Fill(deltaR_mu2FJ1,wg);

   deltaEta_mu1FJ2 = fabs(Muon_eta->at(0) - BoostedJet_eta->at(5));
   deltaPhi_mu1FJ2 = deltaPhi(Muon_phi->at(0),BoostedJet_phi->at(5));
   deltaR_mu1FJ2 = sqrt(pow(deltaEta_mu1FJ1,1) + pow(deltaPhi_mu1FJ1,2));
   deltaRmu1FJ2->Fill(deltaR_mu1FJ1,wg);
   }
   if (numOfBoostedJets ==1) MllJ_FJ1->Fill((Muon1+Muon2+BoostJet).M(),wg);
   MllJ->Fill((Muon1+Muon2+BoostJet).M(),wg);
   if (numOfBoostedJets > 1) MllJJ->Fill((Muon1+Muon2+BoostJet+BoostJet2).M(),wg);

   Mu1_pt->Fill(Muon_pt->at(0),wg); 
   Mu2_pt->Fill(Muon_pt->at(1),wg);
   Mu1_relIso->Fill(Muon_relIsoDeltaBetaR04->at(0),wg);
   Mu2_relIso->Fill(Muon_relIsoDeltaBetaR04->at(1)),wg;
  
   mumujj_L13_M8000_mumujj->Fill((Muon1+Muon2+BoostJet).M(), wg); 
   mumujj_L13_M8000_mumujj_2016_AlphaRatio->Fill((Muon1+Muon2+BoostJet).M(), wg);
   mumujj_L13_M8000_mumujj_2016_AlphaRatioUp->Fill((Muon1+Muon2+BoostJet).M(), wg);
   mumujj_L13_M8000_mumujj_2016_AlphaRatioDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
   mumujj_L13_M8000_mumujj_2016_SFUp->Fill((Muon1+Muon2+BoostJet).M(), wg_2016_SFUp);
   mumujj_L13_M8000_mumujj_2016_SFDown->Fill((Muon1+Muon2+BoostJet).M(), wg_2016_SFDown);
   mumujj_L13_M8000_mumujj_2016_PUUp->Fill((Muon1+Muon2+BoostJet).M(), wg_2016_PUUp);
   mumujj_L13_M8000_mumujj_2016_PUDown->Fill((Muon1+Muon2+BoostJet).M(), wg_2016_PUDown);
   mumujj_L13_M8000_mumujj_2016_PtCorrUp->Fill((Muon1_ptCorr+Muon2_ptCorr+BoostJet).M(), wg);
   mumujj_L13_M8000_mumujj_2016_PtCorrDown->Fill((Muon1_ptCorr+Muon2_ptCorr+BoostJet).M(), wg);
   if(centralJesJer->at(0)==1)mumujj_L13_M8000_mumujj_centralJesJer->Fill((Muon1+Muon2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)mumujj_L13_M8000_mumujj_2016_JesSFUp->Fill((Muon1+Muon2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)mumujj_L13_M8000_mumujj_2016_JesSFDown->Fill((Muon1+Muon2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)mumujj_L13_M8000_mumujj_2016_JerSFUp->Fill((Muon1+Muon2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)mumujj_L13_M8000_mumujj_2016_JerSFDown->Fill((Muon1+Muon2+BoostJet_JERdown).M(), wg);  
  
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
    mumujj_L13_M8000_DYcr_mumujj_2016_AlphaRatio->Fill((Muon1+Muon2+BoostJet).M(), wg);
    mumujj_L13_M8000_DYcr_mumujj_2016_AlphaRatioUp->Fill((Muon1+Muon2+BoostJet).M(), wg);
    mumujj_L13_M8000_DYcr_mumujj_2016_AlphaRatioDown->Fill((Muon1+Muon2+BoostJet).M(), wg);
    mumujj_L13_M8000_DYcr_mumujj_2016_SFUp->Fill((Muon1+Muon2+BoostJet).M(), wg_2016_SFUp);
    mumujj_L13_M8000_DYcr_mumujj_2016_SFDown->Fill((Muon1+Muon2+BoostJet).M(), wg_2016_SFDown);
    mumujj_L13_M8000_DYcr_mumujj_2016_PUUp->Fill((Muon1+Muon2+BoostJet).M(), wg_2016_PUUp);
    mumujj_L13_M8000_DYcr_mumujj_2016_PUDown->Fill((Muon1+Muon2+BoostJet).M(), wg_2016_PUDown);
    mumujj_L13_M8000_DYcr_mumujj_2016_PtCorrUp->Fill((Muon1_ptCorr+Muon2_ptCorr+BoostJet).M(), wg);
    mumujj_L13_M8000_DYcr_mumujj_2016_PtCorrDown->Fill((Muon1_ptCorr+Muon2_ptCorr+BoostJet).M(), wg);
    if(centralJesJer->at(0)==1)mumujj_L13_M8000_DYcr_mumujj_centralJesJer->Fill((Muon1+Muon2+BoostJet).M(), wg);
    if(JesSFup->at(1)==1)mumujj_L13_M8000_DYcr_mumujj_2016_JesSFUp->Fill((Muon1+Muon2+BoostJet_JESup).M(), wg);
    if(JesSFdown->at(2)==1)mumujj_L13_M8000_DYcr_mumujj_2016_JesSFDown->Fill((Muon1+Muon2+BoostJet_JESdown).M(), wg);
    if(JerSFup->at(3)==1)mumujj_L13_M8000_DYcr_mumujj_2016_JerSFUp->Fill((Muon1+Muon2+BoostJet_JERup).M(), wg);
    if(JerSFdown->at(4)==1)mumujj_L13_M8000_DYcr_mumujj_2016_JerSFDown->Fill((Muon1+Muon2+BoostJet_JERdown).M(), wg);  
    }



 }
 
 if (patElectron_pt->size() > 1 && numOfHighptEle==2 && numOfLooseMu==0 && numOfBoostedJets>=1){
  Electron1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
  Electron2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energy->at(1));
  if (HLT_Ele == 1 && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190 && (Electron1+Electron2).M() > 300){
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

   mumujj_L13_M8000_eejj->Fill((Electron1+Electron2+BoostJet).M(), wg);
   mumujj_L13_M8000_eejj_2016_AlphaRatio->Fill((Electron1+Electron2+BoostJet).M(), wg);
   mumujj_L13_M8000_eejj_2016_AlphaRatioUp->Fill((Electron1+Electron2+BoostJet).M(), wg);
   mumujj_L13_M8000_eejj_2016_AlphaRatioDown->Fill((Electron1+Electron2+BoostJet).M(), wg);
   mumujj_L13_M8000_eejj_2016_SFUp->Fill((Electron1+Electron2+BoostJet).M(), wg_2016_SFUp);
   mumujj_L13_M8000_eejj_2016_SFDown->Fill((Electron1+Electron2+BoostJet).M(), wg_2016_SFDown);
   mumujj_L13_M8000_eejj_2016_PUUp->Fill((Electron1+Electron2+BoostJet).M(), wg_2016_PUUp);
   mumujj_L13_M8000_eejj_2016_PUDown->Fill((Electron1+Electron2+BoostJet).M(), wg_2016_PUDown);
   mumujj_L13_M8000_eejj_2016_energyScaleUp->Fill((Ele1_ScaleUp+Ele2_ScaleUp+BoostJet).M(), wg);
   mumujj_L13_M8000_eejj_2016_energyScaleDown->Fill((Ele1_ScaleDown+Ele2_ScaleDown+BoostJet).M(), wg);
   mumujj_L13_M8000_eejj_2016_energySigmaUp->Fill((Ele1_SigmaUp+Ele2_SigmaUp+BoostJet).M(), wg);
   mumujj_L13_M8000_eejj_2016_energySigmaDown->Fill((Ele1_SigmaDown+Ele2_SigmaDown+BoostJet).M(), wg);
   if(centralJesJer->at(0)==1)mumujj_L13_M8000_eejj_centralJesJer->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)mumujj_L13_M8000_eejj_2016_JesSFUp->Fill((Electron1+Electron2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)mumujj_L13_M8000_eejj_2016_JesSFDown->Fill((Electron1+Electron2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)mumujj_L13_M8000_eejj_2016_JerSFUp->Fill((Electron1+Electron2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)mumujj_L13_M8000_eejj_2016_JerSFDown->Fill((Electron1+Electron2+BoostJet_JERdown).M(), wg); 
  
  
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
   mumujj_L13_M8000_DYcr_eejj_2016_AlphaRatio->Fill((Electron1+Electron2+BoostJet).M(), wg);
   mumujj_L13_M8000_DYcr_eejj_2016_AlphaRatioUp->Fill((Electron1+Electron2+BoostJet).M(), wg);
   mumujj_L13_M8000_DYcr_eejj_2016_AlphaRatioDown->Fill((Electron1+Electron2+BoostJet).M(), wg);
   mumujj_L13_M8000_DYcr_eejj_2016_SFUp->Fill((Electron1+Electron2+BoostJet).M(), wg_2016_SFUp);
   mumujj_L13_M8000_DYcr_eejj_2016_SFDown->Fill((Electron1+Electron2+BoostJet).M(), wg_2016_SFDown);
   mumujj_L13_M8000_DYcr_eejj_2016_PUUp->Fill((Electron1+Electron2+BoostJet).M(), wg_2016_PUUp);
   mumujj_L13_M8000_DYcr_eejj_2016_PUDown->Fill((Electron1+Electron2+BoostJet).M(), wg_2016_PUDown);
   mumujj_L13_M8000_DYcr_eejj_2016_energyScaleUp->Fill((Ele1_ScaleUp+Ele2_ScaleUp+BoostJet).M(), wg);
   mumujj_L13_M8000_DYcr_eejj_2016_energyScaleDown->Fill((Ele1_ScaleDown+Ele2_ScaleDown+BoostJet).M(), wg);
   mumujj_L13_M8000_DYcr_eejj_2016_energySigmaUp->Fill((Ele1_SigmaUp+Ele2_SigmaUp+BoostJet).M(), wg);
   mumujj_L13_M8000_DYcr_eejj_2016_energySigmaDown->Fill((Ele1_SigmaDown+Ele2_SigmaDown+BoostJet).M(), wg);
   if(centralJesJer->at(0)==1)mumujj_L13_M8000_DYcr_eejj_centralJesJer->Fill((Electron1+Electron2+BoostJet).M(), wg);
   if(JesSFup->at(1)==1)mumujj_L13_M8000_DYcr_eejj_2016_JesSFUp->Fill((Electron1+Electron2+BoostJet_JESup).M(), wg);
   if(JesSFdown->at(2)==1)mumujj_L13_M8000_DYcr_eejj_2016_JesSFDown->Fill((Electron1+Electron2+BoostJet_JESdown).M(), wg);
   if(JerSFup->at(3)==1)mumujj_L13_M8000_DYcr_eejj_2016_JerSFUp->Fill((Electron1+Electron2+BoostJet_JERup).M(), wg);
   if(JerSFdown->at(4)==1)mumujj_L13_M8000_DYcr_eejj_2016_JerSFDown->Fill((Electron1+Electron2+BoostJet_JERdown).M(), wg); 
  }
 } 
 
}
//TFile *f = new TFile("test/SR_syst_mumujj_L13_M8000_2016.root", "RECREATE");

TFile *f = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2016-OldBinning/SR_syst_mumujj_L13_M8000_2016.root", "RECREATE");
//TFile *f2 = new TFile("SR_syst_mumujj_L13_M8000_oldbin_2016.root", "RECREATE");
deltaRmu1FJ1->Write();
deltaRmu2FJ1->Write();
deltaRmu1FJ2->Write();
deltaRmu2FJ2->Write();
deltaRmu12->Write();
MllJJ->Write();
MllJ->Write();
MllJ_FJ1->Write();
NumFatJet->Write();
Mlljj->Write();
NumJet->Write();
deltaPhijj->Write();
deltaEtajj->Write();
deltaRjj->Write();

Mu1_pt->Write();
Mu2_pt->Write();
Mu1_relIso->Write();
Mu2_relIso->Write();

mumujj_L13_M8000_eejj->Write();
mumujj_L13_M8000_eejj_2016_AlphaRatio->Write();
mumujj_L13_M8000_eejj_2016_AlphaRatioUp->Write();
mumujj_L13_M8000_eejj_2016_AlphaRatioDown->Write();
mumujj_L13_M8000_eejj_2016_SFUp->Write();
mumujj_L13_M8000_eejj_2016_SFDown->Write();
mumujj_L13_M8000_eejj_2016_PUUp->Write();
mumujj_L13_M8000_eejj_2016_PUDown->Write();
mumujj_L13_M8000_eejj_centralJesJer->Write();
mumujj_L13_M8000_eejj_2016_JesSFUp->Write();
mumujj_L13_M8000_eejj_2016_JesSFDown->Write();
mumujj_L13_M8000_eejj_2016_JerSFUp->Write();
mumujj_L13_M8000_eejj_2016_JerSFDown->Write();
mumujj_L13_M8000_eejj_2016_energyScaleUp->Write();
mumujj_L13_M8000_eejj_2016_energyScaleDown->Write();
mumujj_L13_M8000_eejj_2016_energySigmaUp->Write();
mumujj_L13_M8000_eejj_2016_energySigmaDown->Write();
mumujj_L13_M8000_mumujj->Write();
mumujj_L13_M8000_mumujj_2016_AlphaRatio->Write();
mumujj_L13_M8000_mumujj_2016_AlphaRatioUp->Write();
mumujj_L13_M8000_mumujj_2016_AlphaRatioDown->Write();
mumujj_L13_M8000_mumujj_2016_SFUp->Write();
mumujj_L13_M8000_mumujj_2016_SFDown->Write();
mumujj_L13_M8000_mumujj_2016_PUUp->Write();
mumujj_L13_M8000_mumujj_2016_PUDown->Write();
mumujj_L13_M8000_mumujj_centralJesJer->Write();
mumujj_L13_M8000_mumujj_2016_JesSFUp->Write();
mumujj_L13_M8000_mumujj_2016_JesSFDown->Write();
mumujj_L13_M8000_mumujj_2016_JerSFUp->Write();
mumujj_L13_M8000_mumujj_2016_JerSFDown->Write();
mumujj_L13_M8000_mumujj_2016_PtCorrDown->Write();
mumujj_L13_M8000_mumujj_2016_PtCorrUp->Write();

mumujj_L13_M8000_eejj_PDFUp->Write();
mumujj_L13_M8000_eejj_PDFDown->Write();
mumujj_L13_M8000_mumujj_PDFUp->Write();
mumujj_L13_M8000_mumujj_PDFDown->Write();


//DYcr 
mumujj_L13_M8000_DYcr_eejj->Write();
mumujj_L13_M8000_DYcr_eejj_2016_AlphaRatio->Write();
mumujj_L13_M8000_DYcr_eejj_2016_AlphaRatioUp->Write();
mumujj_L13_M8000_DYcr_eejj_2016_AlphaRatioDown->Write();
mumujj_L13_M8000_DYcr_eejj_2016_SFUp->Write();
mumujj_L13_M8000_DYcr_eejj_2016_SFDown->Write();
mumujj_L13_M8000_DYcr_eejj_2016_PUUp->Write();
mumujj_L13_M8000_DYcr_eejj_2016_PUDown->Write();
mumujj_L13_M8000_DYcr_eejj_centralJesJer->Write();
mumujj_L13_M8000_DYcr_eejj_2016_JesSFUp->Write();
mumujj_L13_M8000_DYcr_eejj_2016_JesSFDown->Write();
mumujj_L13_M8000_DYcr_eejj_2016_JerSFUp->Write();
mumujj_L13_M8000_DYcr_eejj_2016_JerSFDown->Write();
mumujj_L13_M8000_DYcr_eejj_2016_energyScaleUp->Write();
mumujj_L13_M8000_DYcr_eejj_2016_energyScaleDown->Write();
mumujj_L13_M8000_DYcr_eejj_2016_energySigmaUp->Write();
mumujj_L13_M8000_DYcr_eejj_2016_energySigmaDown->Write();
mumujj_L13_M8000_DYcr_mumujj->Write();
mumujj_L13_M8000_DYcr_mumujj_2016_AlphaRatio->Write();
mumujj_L13_M8000_DYcr_mumujj_2016_AlphaRatioUp->Write();
mumujj_L13_M8000_DYcr_mumujj_2016_AlphaRatioDown->Write();
mumujj_L13_M8000_DYcr_mumujj_2016_SFUp->Write();
mumujj_L13_M8000_DYcr_mumujj_2016_SFDown->Write();
mumujj_L13_M8000_DYcr_mumujj_2016_PUUp->Write();
mumujj_L13_M8000_DYcr_mumujj_2016_PUDown->Write();
mumujj_L13_M8000_DYcr_mumujj_centralJesJer->Write();
mumujj_L13_M8000_DYcr_mumujj_2016_JesSFUp->Write();
mumujj_L13_M8000_DYcr_mumujj_2016_JesSFDown->Write();
mumujj_L13_M8000_DYcr_mumujj_2016_JerSFUp->Write();
mumujj_L13_M8000_DYcr_mumujj_2016_JerSFDown->Write();
mumujj_L13_M8000_DYcr_mumujj_2016_PtCorrDown->Write();
mumujj_L13_M8000_DYcr_mumujj_2016_PtCorrUp->Write(); 

f->Write();
f->Close();
//f2->Write();
//f2->Close();
}
 
