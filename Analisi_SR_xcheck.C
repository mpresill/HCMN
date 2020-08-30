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
void Analisi_SR_xcheck(){

TChain *a_ = new TChain("BOOM");

a_->Add("/eos/user/m/mpresill/CMS/HN_Reload/rootplized_samples_2016_syst/mumujj_L13_M500_2016.root");
//("/eos/user/v/vmariani/NTuples/HN_2016/Syst_ALL/Other_2016.root");

int HLT_Ele, HLT_Mu, HLT_Mu50, HLT_OldMu100, HLT_TkMu50, HLT_TkMu100;
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

vector<double>*Gen_pt; Gen_pt = 0;
vector<double>*Gen_eta; Gen_eta = 0;
vector<double>*Gen_phi; Gen_phi = 0;
vector<double>*Gen_charge; Gen_charge = 0;
vector<double>*Gen_energy; Gen_energy = 0;
vector<double>*Gen_pdg_id; Gen_pdg_id = 0;
vector<double>*Gen_motherpdg_id; Gen_motherpdg_id = 0;
vector<double>*Gen_numDaught; Gen_numDaught = 0;
vector<double>*Gen_numMother; Gen_numMother = 0;

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

TBranch *a_Gen_pt=a_->GetBranch("Gen_pt");
TBranch *a_Gen_eta=a_->GetBranch("Gen_eta");
TBranch *a_Gen_phi=a_->GetBranch("Gen_phi");
TBranch *a_Gen_charge=a_->GetBranch("Gen_charge");
TBranch *a_Gen_energy=a_->GetBranch("Gen_energy");
TBranch *a_Gen_pdg_id=a_->GetBranch("Gen_pdg_id");
TBranch *a_Gen_motherpdg_id=a_->GetBranch("Gen_motherpdg_id");
TBranch *a_Gen_numDaught=a_->GetBranch("Gen_numDaught");
TBranch *a_Gen_numMother=a_->GetBranch("Gen_numMother");

a_HLT_Ele115_CaloIdVT_GsfTrkIdT->SetAddress(&HLT_Ele);
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
a_Muon_relIsoDeltaBetaR04->SetAddress(&Muon_relIsoDeltaBetaR04);

a_lepsf_evt->SetAddress(&lepsf_evt);
a_lepsf_evt_u->SetAddress(&lepsf_evt_u);
a_lepsf_evt_d->SetAddress(&lepsf_evt_d);
a_lumi_wgt->SetAddress(&lumi_wgt);

a_Gen_pt->SetAddress(&Gen_pt);
a_Gen_eta->SetAddress(&Gen_eta);
a_Gen_phi->SetAddress(&Gen_phi);
a_Gen_charge->SetAddress(&Gen_charge);
a_Gen_energy->SetAddress(&Gen_energy);
a_Gen_pdg_id->SetAddress(&Gen_pdg_id);
a_Gen_motherpdg_id->SetAddress(&Gen_motherpdg_id);
a_Gen_numDaught->SetAddress(&Gen_numDaught);
a_Gen_numMother->SetAddress(&Gen_numMother);

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

const double asymbins[10] = {0,200,400,600,800,1000,1400,2000,3500,10000};
TH1D *deltaRq2Leadj = new TH1D ("deltaRq2Leadj", "deltaRq2Leadj", 100, 0, 5);
TH1D *deltaRq2LeadJ = new TH1D ("deltaRq2LeadJ", "deltaRq2LeadJ", 100, 0, 5);
TH1D *deltaR_mu1j1 = new TH1D ("deltaR_mu1j1", "deltaR_mu1j1", 100, 0, 5);
TH1D *deltaR_mu2j1 = new TH1D ("deltaR_mu2j1", "deltaR_mu2j1", 100, 0, 5);
TH1D *deltaR_mu1j2 = new TH1D ("deltaR_mu1j2", "deltaR_mu1j2", 100, 0, 5);
TH1D *deltaR_mu2j2 = new TH1D ("deltaR_mu2j2", "deltaR_mu2j2", 100, 0, 5);
TH1D *deltaR_mu1J1 = new TH1D ("deltaR_mu1J1", "deltaR_mu1J1", 100, 0, 5);
TH1D *deltaR_mu2J1 = new TH1D ("deltaR_mu2J1", "deltaR_mu2J1", 100, 0, 5);
TH1D *deltaR_mu1J2 = new TH1D ("deltaR_mu1J2", "deltaR_mu1J2", 100, 0, 5);
TH1D *deltaR_mu2J2 = new TH1D ("deltaR_mu2J2", "deltaR_mu2J2", 100, 0, 5);
TH1D *DeltaR_q2j = new TH1D ("DeltaR_q2j", "DeltaR_q2j", 100, 0, 5);
TH1D *DeltaR_q1j = new TH1D ("DeltaR_q1j", "DeltaR_q1j", 100, 0, 5);
TH1D *DeltaR_q2J = new TH1D ("DeltaR_q2J", "DeltaR_q2J", 100, 0, 5);
TH1D *DeltaR_q1J = new TH1D ("DeltaR_q1J", "DeltaR_q1J", 100, 0, 5);
TH1D *Muon_pt_gen = new TH1D ("Muon_pt_gen", "Muon_pt_gen", 100, 0, 1000);
TH1D *Quark2_pt_gen = new TH1D ("Quark2_pt_gen", "Quark2_pt_gen", 100, 0, 1000);
TH1D *Quark1_pt_gen = new TH1D ("Quark1_pt_gen", "Quark1_pt_gen", 100, 0, 1000);
TH1D *FatJet1_pt = new TH1D ("FatJet1_pt", "FatJet1_pt", 1000, 0, 1000);
TH1D *FatJet2_pt = new TH1D ("FatJet2_pt", "FatJet2_pt", 1000, 0, 1000);
TH1D *Jet1_pt = new TH1D ("Jet1_pt", "Jet1_pt", 1000, 0, 10000);
TH1D *Jet2_pt = new TH1D ("Jet2_pt", "Jet2_pt", 1000, 0, 10000);
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
TH1D *deltaRjj = new TH1D ("deltaRjj", "deltaRjj", 100, 0, 5);
TH1D *deltaRJJ = new TH1D ("deltaRJJ", "deltaRJJ", 100, 0, 5);
TH1D *deltaRmu12 = new TH1D ("deltaRmu12", "deltaRmu12", 100, 0, 20);
TH1D *Mu1_pt = new TH1D ("Mu1_pt", "Mu1_pt", 1000, 0, 10000);
TH1D *Mu2_pt = new TH1D ("Mu2_pt", "Mu2_pt", 1000, 0, 10000); 
TH1D *Mu1_relIso = new TH1D ("Mu1_relIso", "Mu1_relIso", 100, 0, 10);
TH1D *Mu2_relIso = new TH1D ("Mu2_relIso", "Mu2_relIso", 100, 0, 10);

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
double Quark2_gen_pt = 0, Quark2_gen_eta = 0, Quark2_gen_phi = 0, Quark2_gen_energy = 0;
double Quark1_gen_pt = 0, Quark1_gen_eta = 0, Quark1_gen_phi = 0, Quark1_gen_energy = 0;
double Muon_gen_pt = 0, Muon_gen_eta = 0, Muon_gen_phi = 0, Muon_gen_energy = 0;
int quark = 0;
double Jet1_matched_pt = 0, Jet1_matched_eta = 0, Jet1_matched_phi = 0, Jet1_matched_energy=0;
double Jet2_matched_pt = 0, Jet2_matched_eta = 0, Jet2_matched_phi = 0, Jet2_matched_energy=0;
double BoostedJet1_matched_pt = 0, BoostedJet1_matched_eta = 0, BoostedJet1_matched_phi = 0, BoostedJet1_matched_energy=0;
double BoostedJet2_matched_pt = 0, BoostedJet2_matched_eta = 0, BoostedJet2_matched_phi = 0, BoostedJet2_matched_energy=0;
double deltaEta_q1j = 0, deltaPhi_q1j = 0, deltaR_q1j = 0, deltaR_q1j_tmp = 0;
double deltaEta_q2j = 0, deltaPhi_q2j = 0, deltaR_q2j = 0, deltaR_q2j_tmp = 0;
double deltaEta_q1J = 0, deltaPhi_q1J = 0, deltaR_q1J = 0, deltaR_q1J_tmp = 0;
double deltaEta_q2J = 0, deltaPhi_q2J = 0, deltaR_q2J = 0, deltaR_q2J_tmp = 0;
double deltaeta_mu1j1 = 0, deltaeta_mu2j1 = 0, deltaeta_mu1j2 = 0, deltaeta_mu2j2= 0;
double deltaphi_mu1j1 = 0, deltaphi_mu2j1 = 0, deltaphi_mu1j2 = 0, deltaphi_mu2j2= 0;
double deltaeta_mu1J1 = 0, deltaeta_mu2J1 = 0, deltaeta_mu1J2 = 0, deltaeta_mu2J2= 0;
double deltaphi_mu1J1 = 0, deltaphi_mu2J1 = 0, deltaphi_mu1J2 = 0, deltaphi_mu2J2= 0;
double deltaRmu1j1 = 0, deltaRmu2j1 = 0, deltaRmu1j2 = 0, deltaRmu2j2= 0;
double deltaRmu1J1 = 0, deltaRmu2J1 = 0, deltaRmu1J2 = 0, deltaRmu2J2= 0;
double deltaEta_JJ = 0, deltaPhi_JJ = 0, deltaR_JJ = 0;
double deltaEta_q2Leadj = 0, deltaPhi_q2Leadj = 0, deltaR_q2Leadj = 0;
double deltaEta_q2LeadJ = 0, deltaPhi_q2LeadJ = 0, deltaR_q2LeadJ = 0;

for (Int_t i=0;i<a_->GetEntries();i++) {
 a_->GetEntry(i);
 
 quark = 0;
 for (int l = 0; l<Gen_pt->size(); l++){
  if(fabs(Gen_motherpdg_id->at(l)) == 4000014){
   if (fabs(Gen_pdg_id->at(l)) == 13 ){
    Muon_gen_pt = Gen_pt->at(l);
    Muon_gen_eta = Gen_eta->at(l);
    Muon_gen_phi = Gen_phi->at(l);
    Muon_gen_energy = Gen_energy->at(l); 
   }
   if (fabs(Gen_pdg_id->at(l)) >= 1 && fabs(Gen_pdg_id->at(l)) <= 6 ){
    quark++;
    if(quark == 1){
     Quark1_gen_pt = Gen_pt->at(l);
     Quark1_gen_eta = Gen_eta->at(l);
     Quark1_gen_phi = Gen_phi->at(l);
     Quark1_gen_energy = Gen_energy->at(l);
    }
    if(quark == 2){
     Quark2_gen_pt = Gen_pt->at(l);
     Quark2_gen_eta = Gen_eta->at(l);
     Quark2_gen_phi = Gen_phi->at(l);
     Quark2_gen_energy = Gen_energy->at(l);
    }    
   }
  }
 }
 Muon_pt_gen->Fill(Muon_gen_pt);
 Quark1_pt_gen->Fill(Quark1_gen_pt);
 Quark2_pt_gen->Fill(Quark2_gen_pt);  

 HLT_Mu = 0; 
 tot = a_->GetEntries();
 if (i%100000 == 0) cout << i << " eventi analizzati su " << tot << endl;

 wg = lumi * lumi_wgt * lepsf_evt * PUWeight;
          
 if (HLT_Mu50==1 || HLT_TkMu100==1 || HLT_OldMu100==1 ) HLT_Mu = 1;

  ///         EXO-20-002 selection ////
 
 if (Muon_pt->size() > 1 && numOfHighptMu==2 && numOfVetoEle == 0 && numOfJets >=2){
  Muon1.SetPtEtaPhiE(Muon_pt->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));
  Muon2.SetPtEtaPhiE(Muon_pt->at(1), Muon_eta->at(1), Muon_phi->at(1),Muon_energy->at(1));
  Jet1.SetPtEtaPhiE(Jet_pt->at(0), Jet_eta->at(0), Jet_phi->at(0),Jet_energy->at(0));
  Jet2.SetPtEtaPhiE(Jet_pt->at(1), Jet_eta->at(1), Jet_phi->at(1),Jet_energy->at(1));

  if (HLT_Mu == 1 && Muon_pt->at(0) > 60 && Muon_pt->at(1) > 53 && fabs(Muon_eta->at(0))<2.4 && fabs(Muon_eta->at(1))<2.4 && Jet_pt->at(0) > 40 && Jet_pt->at(1) > 40 && (Muon1+Muon2).M() > 400 ){  
  /* deltaEta_jj = fabs(Jet_eta->at(0) - Jet_eta->at(1));
   deltaPhi_jj = deltaPhi(Jet_phi->at(0), Jet_phi->at(1));
   deltaR_jj = sqrt(pow(deltaEta_jj,2) + pow(deltaPhi_jj,2)); 
   deltaRjj->Fill(deltaR_jj,wg);
   deltaEtajj->Fill(deltaEta_jj,wg);
   deltaPhijj->Fill(deltaPhi_jj,wg);*/
   NumJet->Fill(numOfJets,wg);
   Mlljj->Fill((Muon1+Muon2+Jet1+Jet2).M(),wg);

   deltaR_q1j = 100, deltaR_q2j = 100;
   for (int j=0; j<numOfJets; j++){
    deltaEta_q1j=fabs(Quark1_gen_eta - Jet_eta->at(j)); 
    deltaPhi_q1j=deltaPhi(Quark1_gen_phi, Jet_phi->at(j));
    deltaR_q1j_tmp = sqrt(pow(deltaEta_q1j,2) + pow(deltaPhi_q1j,2));
    if (deltaR_q1j_tmp < deltaR_q1j){
     deltaR_q1j = deltaR_q1j_tmp;
     Jet1_matched_pt = Jet_pt->at(j);
     Jet1_matched_eta = Jet_eta->at(j);
     Jet1_matched_phi = Jet_phi->at(j);
     Jet1_matched_energy = Jet_energy->at(j); 
    }
   }
   for (int j=0; j<numOfJets; j++){
    deltaEta_q2j=fabs(Quark2_gen_eta - Jet_eta->at(j)); 
    deltaPhi_q2j=deltaPhi(Quark2_gen_phi, Jet_phi->at(j));
    deltaR_q2j_tmp = sqrt(pow(deltaEta_q2j,2) + pow(deltaPhi_q2j,2));
    if (deltaR_q2j_tmp < deltaR_q2j){
     deltaR_q2j = deltaR_q2j_tmp;
     Jet2_matched_pt = Jet_pt->at(j);
     Jet2_matched_eta = Jet_eta->at(j);
     Jet2_matched_phi = Jet_phi->at(j);
     Jet2_matched_energy = Jet_energy->at(j);
    }
   }
   DeltaR_q1j->Fill(deltaR_q1j);
   DeltaR_q2j->Fill(deltaR_q2j);
   deltaeta_mu1j1 = fabs(Muon1.Eta() - Jet1_matched_eta);
   deltaeta_mu2j1 = fabs(Muon2.Eta() - Jet1_matched_eta);
   deltaeta_mu1j2 = fabs(Muon1.Eta() - Jet2_matched_eta);
   deltaeta_mu2j2 = fabs(Muon2.Eta() - Jet2_matched_eta);
   deltaphi_mu1j1 = deltaPhi(Muon1.Phi(), Jet1_matched_phi);
   deltaphi_mu2j1 = deltaPhi(Muon2.Phi(), Jet1_matched_phi);
   deltaphi_mu1j2 = deltaPhi(Muon1.Phi(), Jet2_matched_phi);
   deltaphi_mu2j2 = deltaPhi(Muon2.Phi(), Jet2_matched_phi); 
   deltaRmu1j1 = sqrt(pow(deltaphi_mu1j1,2) + (deltaeta_mu1j1,2));
   deltaRmu2j1 = sqrt(pow(deltaphi_mu2j1,2) + (deltaeta_mu2j1,2));
   deltaRmu1j2 = sqrt(pow(deltaphi_mu1j2,2) + (deltaeta_mu1j2,2));
   deltaRmu2j2 = sqrt(pow(deltaphi_mu2j2,2) + (deltaeta_mu2j2,2));

   if (deltaR_q1j < 0.3 && deltaR_q2j < 0.3){
    deltaEta_jj = fabs(Jet1_matched_eta - Jet2_matched_eta);
    deltaPhi_jj = deltaPhi(Jet1_matched_phi, Jet2_matched_phi);
    deltaR_jj = sqrt(pow(deltaEta_jj,2) + pow(deltaPhi_jj,2));
    deltaRjj->Fill(deltaR_jj,wg);
    deltaEtajj->Fill(deltaEta_jj,wg);
    deltaPhijj->Fill(deltaPhi_jj,wg);  
    Jet1_pt->Fill(Jet1_matched_pt);
    Jet2_pt->Fill(Jet2_matched_pt); 
    deltaR_mu1j1->Fill(deltaRmu1j1);
    deltaR_mu2j1->Fill(deltaRmu2j1);
    deltaR_mu1j2->Fill(deltaRmu1j2);
    deltaR_mu2j2->Fill(deltaRmu2j2); 
   }
   deltaEta_q2Leadj = fabs(Quark2_gen_eta - Jet_eta->at(0));
   deltaPhi_q2Leadj = deltaPhi(Quark2_gen_phi, Jet_phi->at(0));
   deltaR_q2Leadj = sqrt(pow(deltaEta_q2Leadj,2) + pow(deltaPhi_q2Leadj,2)); 
   deltaRq2Leadj->Fill(deltaR_q2Leadj);
  }
 }


   // OUR SELECTION //

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

   deltaR_q1J = 100, deltaR_q2J = 100;
   for (int j=0; j<BoostedJet_pt->size(); j+=5){
    deltaEta_q1J=fabs(Quark1_gen_eta - BoostedJet_eta->at(j));
    deltaPhi_q1J=deltaPhi(Quark1_gen_phi, BoostedJet_phi->at(j));
    deltaR_q1J_tmp = sqrt(pow(deltaEta_q1J,2) + pow(deltaPhi_q1J,2));
    if (deltaR_q1J_tmp < deltaR_q1J){
     deltaR_q1J = deltaR_q1J_tmp;
     BoostedJet1_matched_pt = BoostedJet_pt->at(j);
     BoostedJet1_matched_eta = BoostedJet_eta->at(j);
     BoostedJet1_matched_phi = BoostedJet_phi->at(j);
     BoostedJet1_matched_energy = BoostedJet_energy->at(j);
    }
   }

   for (int j=0; j<BoostedJet_pt->size(); j+=5){
    deltaEta_q2J=fabs(Quark2_gen_eta - BoostedJet_eta->at(j));
    deltaPhi_q2J=deltaPhi(Quark2_gen_phi, BoostedJet_phi->at(j));
    deltaR_q2J_tmp = sqrt(pow(deltaEta_q2J,2) + pow(deltaPhi_q2J,2));
    if (deltaR_q2J_tmp < deltaR_q2J){
     deltaR_q2J = deltaR_q2J_tmp;
     BoostedJet2_matched_pt = BoostedJet_pt->at(j);
     BoostedJet2_matched_eta = BoostedJet_eta->at(j);
     BoostedJet2_matched_phi = BoostedJet_phi->at(j);
     BoostedJet2_matched_energy = BoostedJet_energy->at(j);
    }
   }
   DeltaR_q1J->Fill(deltaR_q1J);
   DeltaR_q2J->Fill(deltaR_q2J);

   deltaeta_mu1J1 = fabs(Muon1.Eta() - BoostedJet1_matched_eta);
   deltaeta_mu2J1 = fabs(Muon2.Eta() - BoostedJet1_matched_eta);
   deltaeta_mu1J2 = fabs(Muon1.Eta() - BoostedJet2_matched_eta);
   deltaeta_mu2J2 = fabs(Muon2.Eta() - BoostedJet2_matched_eta);
   deltaphi_mu1J1 = deltaPhi(Muon1.Phi(), BoostedJet1_matched_phi);
   deltaphi_mu2J1 = deltaPhi(Muon2.Phi(), BoostedJet1_matched_phi);
   deltaphi_mu1J2 = deltaPhi(Muon1.Phi(), BoostedJet2_matched_phi);
   deltaphi_mu2J2 = deltaPhi(Muon2.Phi(), BoostedJet2_matched_phi);
   deltaRmu1J1 = sqrt(pow(deltaphi_mu1J1,2) + (deltaeta_mu1J1,2));
   deltaRmu2J1 = sqrt(pow(deltaphi_mu2J1,2) + (deltaeta_mu2J1,2));
   deltaRmu1J2 = sqrt(pow(deltaphi_mu1J2,2) + (deltaeta_mu1J2,2));
   deltaRmu2J2 = sqrt(pow(deltaphi_mu2J2,2) + (deltaeta_mu2J2,2));

   if (deltaR_q1J < 0.8 && deltaR_q2J < 0.8){
    deltaEta_JJ = fabs(Jet1_matched_eta - Jet2_matched_eta);
    deltaPhi_JJ = deltaPhi(Jet1_matched_phi, Jet2_matched_phi);
    deltaR_JJ = sqrt(pow(deltaEta_JJ,2) + pow(deltaPhi_JJ,2));
    deltaRJJ->Fill(deltaR_JJ,wg);
    FatJet1_pt->Fill(BoostedJet1_matched_pt);
    FatJet2_pt->Fill(BoostedJet2_matched_pt);
    deltaR_mu1J1->Fill(deltaRmu1J1);
    deltaR_mu2J1->Fill(deltaRmu2J1);
    deltaR_mu1J2->Fill(deltaRmu1J2);
    deltaR_mu2J2->Fill(deltaRmu2J2);
   }
      
   //FatJet1_pt->Fill(BoostedJet_pt->at(0));
   deltaEta_mu2FJ1 =fabs(Muon_eta->at(1) - BoostedJet_eta->at(0));
   deltaPhi_mu2FJ1 = deltaPhi(Muon_phi->at(1), BoostedJet_phi->at(0));
   deltaR_mu2FJ1 = sqrt(pow(deltaEta_mu2FJ1,2) + pow(deltaPhi_mu2FJ1,2));
   deltaRmu2FJ1->Fill(deltaR_mu2FJ1,wg);
   
   deltaEta_mu1FJ1 = fabs(Muon_eta->at(0) - BoostedJet_eta->at(0));
   deltaPhi_mu1FJ1 = deltaPhi(Muon_phi->at(0),BoostedJet_phi->at(0));
   deltaR_mu1FJ1 = sqrt(pow(deltaEta_mu1FJ1,2) + pow(deltaPhi_mu1FJ1,2));
   deltaRmu1FJ1->Fill(deltaR_mu1FJ1,wg);

   deltaEta_mu12 = fabs(Muon_eta->at(0) - Muon_eta->at(1));
   deltaPhi_mu12 = deltaPhi(Muon_phi->at(0),Muon_phi->at(1));
   deltaR_mu12 = sqrt(pow(deltaEta_mu12,2) + pow(deltaPhi_mu12,2));
   deltaRmu12->Fill(deltaR_mu12,wg);

   deltaEta_q2LeadJ = fabs(Quark2_gen_eta - BoostedJet_eta->at(0));
   deltaPhi_q2LeadJ = deltaPhi(Quark2_gen_phi, BoostedJet_phi->at(0));
   deltaR_q2LeadJ = sqrt(pow(deltaEta_q2LeadJ,2) + pow(deltaPhi_q2LeadJ,2));
   deltaRq2LeadJ->Fill(deltaR_q2LeadJ);

   if (numOfBoostedJets > 1){
   deltaEta_mu2FJ2 =fabs(Muon_eta->at(1) - BoostedJet_eta->at(5));
   deltaPhi_mu2FJ2 = deltaPhi(Muon_phi->at(1), BoostedJet_phi->at(5));
   deltaR_mu2FJ2 = sqrt(pow(deltaEta_mu2FJ2,2) + pow(deltaPhi_mu2FJ2,2));
   deltaRmu2FJ2->Fill(deltaR_mu2FJ1,wg);

   deltaEta_mu1FJ2 = fabs(Muon_eta->at(0) - BoostedJet_eta->at(5));
   deltaPhi_mu1FJ2 = deltaPhi(Muon_phi->at(0),BoostedJet_phi->at(5));
   deltaR_mu1FJ2 = sqrt(pow(deltaEta_mu1FJ1,2) + pow(deltaPhi_mu1FJ1,2));
   deltaRmu1FJ2->Fill(deltaR_mu1FJ1,wg);
   //FatJet2_pt->Fill(BoostedJet_pt->at(5));
   }
   if (numOfBoostedJets ==1) MllJ_FJ1->Fill((Muon1+Muon2+BoostJet).M(),wg);
   MllJ->Fill((Muon1+Muon2+BoostJet).M(),wg);
   if (numOfBoostedJets > 1) MllJJ->Fill((Muon1+Muon2+BoostJet+BoostJet2).M(),wg);

   Mu1_pt->Fill(Muon_pt->at(0),wg); 
   Mu2_pt->Fill(Muon_pt->at(1),wg);
   Mu1_relIso->Fill(Muon_relIsoDeltaBetaR04->at(0),wg);
   Mu2_relIso->Fill(Muon_relIsoDeltaBetaR04->at(1)),wg;
  
  }
 }
 
 if (patElectron_pt->size() > 1 && numOfHighptEle==2 && numOfLooseMu==0 && numOfBoostedJets>=1){
  Electron1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
  Electron2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energy->at(1));
  if (HLT_Ele == 1 && patElectron_pt->at(0) > 150 && patElectron_pt->at(1) > 100 && fabs(patElectron_eta->at(1))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190 && (Electron1+Electron2).M() > 300){
   Electron1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   Electron2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1),patElectron_energy->at(1));  
   BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));

  }
 } 
 
}

TFile *f = new TFile("plot/SR_plots_gen_mumujj_L13_M500_2016.root", "RECREATE");
deltaRmu1FJ1->Write();
deltaRmu2FJ1->Write();
deltaRmu1FJ2->Write();
deltaRmu2FJ2->Write();
deltaRmu12->Write();
MllJJ->Write();
MllJ->Write();
MllJ_FJ1->Write();
NumFatJet->Write();
FatJet1_pt->Write();
FatJet2_pt->Write();
Mlljj->Write();
NumJet->Write();
Jet1_pt->Write();
Jet2_pt->Write();
deltaPhijj->Write();
deltaEtajj->Write();
deltaRjj->Write();
deltaRJJ->Write();
deltaR_mu1j1->Write();
deltaR_mu2j1->Write();
deltaR_mu1j2->Write();
deltaR_mu2j2->Write();
deltaR_mu1J1->Write();
deltaR_mu2J1->Write();
deltaR_mu1J2->Write();
deltaR_mu2J2->Write();
deltaRq2Leadj->Write();
deltaRq2LeadJ->Write();
DeltaR_q2j->Write();
DeltaR_q1j->Write();
DeltaR_q2J->Write();
DeltaR_q1J->Write();
Mu1_pt->Write();
Mu2_pt->Write();
Mu1_relIso->Write();
Mu2_relIso->Write();

Quark1_pt_gen->Write();
Quark2_pt_gen->Write();
Muon_pt_gen->Write();

f->Write();
f->Close();

}
 
