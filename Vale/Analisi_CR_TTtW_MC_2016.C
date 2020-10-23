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
void Analisi_CR_TTtW_MC_2016(){

TChain *a_ = new TChain("BOOM");

a_->Add("/eos/user/v/vmariani/NTuples/HN_2016/Syst_ALL_newMuonSF/TTtW_2016.root");

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
vector<double>* Muon_energy; Muon_energy=0;
vector<double>*BoostedJet_pt; BoostedJet_pt=0;
vector<double>*BoostedJet_eta; BoostedJet_eta=0;
vector<double>*BoostedJet_phi; BoostedJet_phi=0;
vector<double>*BoostedJet_energy; BoostedJet_energy=0;
double PUWeight, MinBiasUpWeight, MinBiasDownWeight;
double lepsf_evt, lepsf_evt_u, lepsf_evt_d;
double numOfHighptEle, numOfVetoEle, numOfHighptMu, numOfLooseMu, numOfBoostedJets;
double lumi_wgt, trueInteractions;
int nBestVtx;
vector<double>*centralJesJer; centralJesJer=0;
vector<double>*JesSFup; JesSFup=0;
vector<double>*JesSFdown; JesSFdown=0;
vector<double>*JerSFup; JerSFup=0;
vector<double>*JerSFdown; JerSFdown=0;

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

const double asymbins[7] = {300,350,400,450,500,700,2000};
const double asymbins2[10] = {0,200,400,600,800,1000,1400,2000,3500,10000};
<<<<<<< HEAD
=======

>>>>>>> bf842eeda520a2834335bb4640ad3de83acd869b

TH1D *n_best_Vtx = new TH1D ("n_best_Vtx", "n_best_Vtx", 100,0, 100);
TH1D *true_interactions = new TH1D ("true_interactions", "true_interactions", 100,0, 100 );
TH1D *Ele_pt = new TH1D ("Ele_pt", "Ele_pt", 200, 0, 5000);
TH1D *Mu_pt = new TH1D ("Mu_pt", "Mu_pt", 200, 0, 5000);
TH1D *Ele_phi = new TH1D ("Ele_phi", "Ele_phi", 200, -3, 3);
TH1D *Mu_phi = new TH1D ("Mu_phi", "Mu_phi", 200, -3, 3);
TH1D *Ele_eta = new TH1D ("Ele_eta", "Ele_eta", 200, -4, 4);
TH1D *Mu_eta = new TH1D ("Mu_eta", "Mu_eta", 200, -4, 4);
TH1D *M_ll_puw = new TH1D ("M_ll_puw", "M_ll_puw", 6, asymbins);

<<<<<<< HEAD
TH1D *M_leplepJ = new TH1D ("M_leplepJ", "M_leplepJ", 9, asymbins2);

=======
>>>>>>> bf842eeda520a2834335bb4640ad3de83acd869b
TH1D *TTtW_ll = new TH1D ("TTtW_ll", "TTtW_ll", 6, asymbins);
TH1D *TTtW_ll_2016_AlphaRatio = new TH1D ("TTtW_ll_2016_AlphaRatio", "TTtW_ll_2016_AlphaRatio", 6, asymbins);
TH1D *TTtW_ll_2016_AlphaRatioUp = new TH1D ("TTtW_ll_2016_AlphaRatioUp", "TTtW_ll_2016_AlphaRatioUp", 6, asymbins);
TH1D *TTtW_ll_2016_AlphaRatioDown = new TH1D ("TTtW_ll_2016_AlphaRatioDown", "TTtW_ll_2016_AlphaRatioDown", 6, asymbins);
TH1D *TTtW_ll_2016_SFUp = new TH1D ("TTtW_ll_2016_SFUp", "TTtW_ll_2016_SFUp", 6, asymbins);
TH1D *TTtW_ll_2016_SFDown = new TH1D ("TTtW_ll_2016_SFDown", "TTtW_ll_2016_SFDown", 6, asymbins);
TH1D *TTtW_ll_2016_PUUp = new TH1D ("TTtW_ll_2016_PUUp", "TTtW_ll_2016_PUUp", 6, asymbins);
TH1D *TTtW_ll_2016_PUDown = new TH1D ("TTtW_ll_2016_PUDown", "TTtW_ll_2016_PUDown", 6, asymbins);
TH1D *TTtW_ll_2016_PtCorrUp = new TH1D ("TTtW_ll_2016_PtCorrUp", "TTtW_ll_2016_PtCorrUp", 6, asymbins);
TH1D *TTtW_ll_2016_PtCorrDown = new TH1D ("TTtW_ll_2016_PtCorrDown", "TTtW_ll_2016_PtCorrDown", 6, asymbins);
TH1D *TTtW_ll_2016_energyScaleUp = new TH1D ("TTtW_ll_2016_energyScaleUp", "TTtW_ll_2016_energyScaleUp", 6, asymbins);
TH1D *TTtW_ll_2016_energyScaleDown = new TH1D ("TTtW_ll_2016_energyScaleDown", "TTtW_ll_2016_energyScaleDown", 6, asymbins);
TH1D *TTtW_ll_2016_energySigmaUp = new TH1D ("TTtW_ll_2016_energySigmaUp", "TTtW_ll_2016_energySigmaUp", 6, asymbins);
TH1D *TTtW_ll_2016_energySigmaDown = new TH1D ("TTtW_ll_2016_energySigmaDown", "TTtW_ll_2016_energySigmaDown", 6, asymbins);
TH1D *TTtW_ll_centralJesJer = new TH1D ("TTtW_ll_centralJesJer", "TTtW_ll_centralJesJer", 6, asymbins);
TH1D *TTtW_ll_2016_JesSFUp = new TH1D ("TTtW_ll_2016_JesSFUp", "TTtW_ll_2016_JesSFUp", 6, asymbins);
TH1D *TTtW_ll_2016_JesSFDown = new TH1D ("TTtW_ll_2016_JesSFDown", "TTtW_ll_2016_JesSFDown", 6, asymbins);
TH1D *TTtW_ll_2016_JerSFUp = new TH1D ("TTtW_ll_2016_JerSFUp", "TTtW_ll_2016_JerSFUp", 6, asymbins);
TH1D *TTtW_ll_2016_JerSFDown = new TH1D ("TTtW_ll_2016_JerSFDown", "TTtW_ll_2016_JerSFDown", 6, asymbins); 
<<<<<<< HEAD
=======

TH1D *M_leplepJ = new TH1D ("M_leplepJ", "M_leplepJ", 9, asymbins2);
>>>>>>> bf842eeda520a2834335bb4640ad3de83acd869b


TLorentzVector BoostJet;
TLorentzVector LeadLep;
TLorentzVector SubLeadLep;
TLorentzVector Muon_ptCorr;
TLorentzVector Ele_ScaleUp;
TLorentzVector Ele_ScaleDown;
TLorentzVector Ele_SigmaUp;
TLorentzVector Ele_SigmaDown;
TLorentzVector BoostJet_JESup;
TLorentzVector BoostJet_JESdown;
TLorentzVector BoostJet_JERup;
TLorentzVector BoostJet_JERdown;

cout << a_->GetEntries() << endl;
int tot=0;
double wg = 0, wg_SFup = 0, wg_SFdown = 0, wg_PUup = 0, wg_PUdown = 0;
int lumi = 35542;//2018: 58873 //2017: 41529 //2016: 35542
bool veto_ele = false;
double deltaEta = 0, deltaPhi = 0, deltaR = 0, pu_w = 0;

for (Int_t i=0;i<a_->GetEntries();i++) {
 a_->GetEntry(i);
 tot = a_->GetEntries();
 if (i%100000 == 0) cout << i << " eventi analizzati su " << tot << endl;
 HLT_Mu = 0;
 if (HLT_Mu50==1 || HLT_TkMu50==1) HLT_Mu = 1;

 wg = lumi * lumi_wgt * lepsf_evt * PUWeight;
 wg_SFup = lumi * lumi_wgt * lepsf_evt_u * PUWeight;
 wg_SFdown = lumi * lumi_wgt * lepsf_evt_d * PUWeight;
 wg_PUup = lumi * lumi_wgt * lepsf_evt * MinBiasUpWeight;
 wg_PUdown = lumi * lumi_wgt * lepsf_evt * MinBiasDownWeight;
        
 if (Muon_pt->size() > 0 && patElectron_pt->size() > 0 && numOfHighptMu==1 && numOfHighptEle == 1 && numOfBoostedJets>=1){

  BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0),BoostedJet_energy->at(0));
   BoostJet_JESup.SetPtEtaPhiE(BoostedJet_pt->at(1), BoostedJet_eta->at(1), BoostedJet_phi->at(1),BoostedJet_energy->at(1));
   BoostJet_JESdown.SetPtEtaPhiE(BoostedJet_pt->at(2), BoostedJet_eta->at(2), BoostedJet_phi->at(2),BoostedJet_energy->at(2));
   BoostJet_JERup.SetPtEtaPhiE(BoostedJet_pt->at(3), BoostedJet_eta->at(3), BoostedJet_phi->at(3),BoostedJet_energy->at(3));
   BoostJet_JERdown.SetPtEtaPhiE(BoostedJet_pt->at(4), BoostedJet_eta->at(4), BoostedJet_phi->at(4),BoostedJet_energy->at(4));
   Muon_ptCorr.SetPtEtaPhiE(Muon_pt_corr->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));
   Ele_ScaleUp.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energyScaleUp->at(0));
   Ele_ScaleDown.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energyScaleDown->at(0));
   Ele_SigmaUp.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energySigmaUp->at(0));
   Ele_SigmaDown.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energySigmaDown->at(0));

  if (Muon_pt->at(0) >= patElectron_pt->at(0)){ 
   LeadLep.SetPtEtaPhiE(Muon_pt->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));
   SubLeadLep.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));


  if (HLT_Mu == 1 && LeadLep.Pt() > 150 && SubLeadLep.Pt() > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(patElectron_eta->at(0))<2.4 
     && BoostedJet_pt->at(0) > 190 && (LeadLep+SubLeadLep).M() > 300 ){
   veto_ele = false;
   for(int j = 0; j < Muon_pt->size(); j++){
    if (Muon_pt->at(j) > 5){
     deltaEta=fabs(Muon_eta->at(j) - patElectron_eta->at(0));
     deltaPhi = Muon_phi->at(j) - patElectron_phi->at(0);
     if(deltaPhi > M_PI) deltaPhi -= 2*M_PI;
     else if(deltaPhi <= -M_PI) deltaPhi +=2*M_PI;
     deltaR=sqrt(pow(deltaEta,2) + pow(deltaPhi,2));
     if (deltaR < 0.1) veto_ele = true;
    }
   }
   if (veto_ele == false){
    //cout << i << " wg " << wg  << " lumi " <<  lumi << " lumi_wgt " << lumi_wgt << " lept_evt " <<  lepsf_evt << " pu " <<  PUWeight<< endl;
    n_best_Vtx->Fill(nBestVtx, wg);
    true_interactions->Fill(trueInteractions, wg);
    Ele_pt->Fill(patElectron_pt->at(0),wg);
    Ele_eta->Fill(patElectron_eta->at(0),wg);
    Ele_phi->Fill(patElectron_phi->at(0),wg);
    Mu_pt->Fill(Muon_pt->at(0),wg);
    Mu_eta->Fill(Muon_eta->at(0),wg);
    Mu_phi->Fill(Muon_phi->at(0),wg);
    M_ll_puw->Fill((LeadLep+SubLeadLep).M(),wg);
    
    TTtW_ll->Fill((LeadLep+SubLeadLep).M(),wg);
    TTtW_ll_2016_AlphaRatio->Fill((LeadLep+SubLeadLep).M(),wg);
    TTtW_ll_2016_AlphaRatioUp->Fill((LeadLep+SubLeadLep).M(),wg);
    TTtW_ll_2016_AlphaRatioDown->Fill((LeadLep+SubLeadLep).M(),wg);     
    TTtW_ll_2016_SFUp->Fill((LeadLep+SubLeadLep).M(),wg_SFup);
    TTtW_ll_2016_SFDown->Fill((LeadLep+SubLeadLep).M(),wg_SFdown);
    TTtW_ll_2016_PUUp->Fill((LeadLep+SubLeadLep).M(),wg_PUup);
    TTtW_ll_2016_PUDown->Fill((LeadLep+SubLeadLep).M(),wg_PUdown);
    TTtW_ll_2016_PtCorrUp->Fill((Muon_ptCorr+SubLeadLep).M(),wg);
    TTtW_ll_2016_PtCorrDown->Fill((Muon_ptCorr+SubLeadLep).M(),wg);
    TTtW_ll_2016_energyScaleUp->Fill((Ele_ScaleUp+LeadLep).M(),wg);
    TTtW_ll_2016_energyScaleDown->Fill((Ele_ScaleDown+LeadLep).M(),wg);
    TTtW_ll_2016_energySigmaUp->Fill((Ele_SigmaUp+LeadLep).M(),wg);
    TTtW_ll_2016_energySigmaDown->Fill((Ele_SigmaDown+LeadLep).M(),wg);

    M_leplepJ->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);

    if(centralJesJer->at(0)==1)TTtW_ll_centralJesJer->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JesSFup->at(1)==1)TTtW_ll_2016_JesSFUp->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JesSFdown->at(2)==1)TTtW_ll_2016_JesSFDown->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JerSFup->at(3)==1)TTtW_ll_2016_JerSFUp->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JerSFdown->at(4)==1)TTtW_ll_2016_JerSFDown->Fill((LeadLep+SubLeadLep).M(), wg);

   }
  }
 }
  else {

   LeadLep.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   SubLeadLep.SetPtEtaPhiE(Muon_pt->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));

   if (HLT_Ele == 1 & LeadLep.Pt() > 150 && SubLeadLep.Pt() > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(patElectron_eta->at(0))<2.4 && BoostedJet_pt->at(0) > 190 && (LeadLep+SubLeadLep).M() > 300){

    veto_ele = false;
   for(int j = 0; j < Muon_pt->size(); j++){
    if (Muon_pt->at(j) > 5){
     deltaEta=fabs(Muon_eta->at(j) - patElectron_eta->at(0));
     deltaPhi = Muon_phi->at(j) - patElectron_phi->at(0);
     if(deltaPhi > M_PI) deltaPhi -= 2*M_PI;
     else if(deltaPhi <= -M_PI) deltaPhi +=2*M_PI;
     deltaR=sqrt(pow(deltaEta,2) + pow(deltaPhi,2));
     if (deltaR < 0.1) veto_ele = true;
    }
   }
   if (veto_ele == false){
    n_best_Vtx->Fill(nBestVtx, wg);
    true_interactions->Fill(trueInteractions, wg);
    Ele_pt->Fill(patElectron_pt->at(0),wg);
    Ele_eta->Fill(patElectron_eta->at(0),wg);
    Ele_phi->Fill(patElectron_phi->at(0),wg);
    Mu_pt->Fill(Muon_pt->at(0),wg);
    Mu_eta->Fill(Muon_eta->at(0),wg);
    Mu_phi->Fill(Muon_phi->at(0),wg);
    M_ll_puw->Fill((LeadLep+SubLeadLep).M(),wg);

    TTtW_ll->Fill((LeadLep+SubLeadLep).M(),wg);
    TTtW_ll_2016_AlphaRatio->Fill((LeadLep+SubLeadLep).M(),wg);
    TTtW_ll_2016_AlphaRatioUp->Fill((LeadLep+SubLeadLep).M(),wg);
    TTtW_ll_2016_AlphaRatioDown->Fill((LeadLep+SubLeadLep).M(),wg);
    TTtW_ll_2016_SFUp->Fill((LeadLep+SubLeadLep).M(),wg_SFup);
    TTtW_ll_2016_SFDown->Fill((LeadLep+SubLeadLep).M(),wg_SFdown);
    TTtW_ll_2016_PUUp->Fill((LeadLep+SubLeadLep).M(),wg_PUup);
<<<<<<< HEAD
    TTtW_ll_2016_PUDown->Fill((LeadLep+SubLeadLep).M(),wg_PUdown);  
=======
>>>>>>> bf842eeda520a2834335bb4640ad3de83acd869b

    TTtW_ll_2016_PtCorrUp->Fill((Muon_ptCorr+LeadLep).M(),wg);
    TTtW_ll_2016_PtCorrDown->Fill((Muon_ptCorr+LeadLep).M(),wg);
    TTtW_ll_2016_energyScaleUp->Fill((Ele_ScaleUp+SubLeadLep).M(),wg);
    TTtW_ll_2016_energyScaleDown->Fill((Ele_ScaleDown+SubLeadLep).M(),wg);
    TTtW_ll_2016_energySigmaUp->Fill((Ele_SigmaUp+SubLeadLep).M(),wg);
    TTtW_ll_2016_energySigmaDown->Fill((Ele_SigmaDown+SubLeadLep).M(),wg);

<<<<<<< HEAD
    M_leplepJ->Fill((LeadLep+SubLeadLep+BoostJet).M(),wg);

=======
>>>>>>> bf842eeda520a2834335bb4640ad3de83acd869b
    if(centralJesJer->at(0)==1)TTtW_ll_centralJesJer->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JesSFup->at(1)==1)TTtW_ll_2016_JesSFUp->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JesSFdown->at(2)==1)TTtW_ll_2016_JesSFDown->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JerSFup->at(3)==1)TTtW_ll_2016_JerSFUp->Fill((LeadLep+SubLeadLep).M(), wg);
    if(JerSFdown->at(4)==1)TTtW_ll_2016_JerSFDown->Fill((LeadLep+SubLeadLep).M(), wg);
    }
   }
  }
 }
}


TFile *f = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2016-OldBinning/CR_TTtW_TTtW_2016_syst.root", "RECREATE");

n_best_Vtx->Write();
true_interactions->Write();
Ele_pt->Write();
Mu_pt->Write();
Ele_eta->Write();
Mu_eta->Write();
Ele_phi->Write();
Mu_phi->Write();
M_ll_puw->Write();
M_leplepJ->Write();
TTtW_ll->Write();
TTtW_ll_2016_AlphaRatio->Write();
TTtW_ll_2016_AlphaRatioUp->Write();
TTtW_ll_2016_AlphaRatioDown->Write();
TTtW_ll_2016_SFUp->Write();
TTtW_ll_2016_SFDown->Write();
TTtW_ll_2016_PUUp->Write();
TTtW_ll_2016_PUDown->Write();
TTtW_ll_2016_PtCorrUp->Write();
TTtW_ll_2016_PtCorrDown->Write();
TTtW_ll_2016_energyScaleUp->Write();
TTtW_ll_2016_energyScaleDown->Write();
TTtW_ll_2016_energySigmaUp->Write();
TTtW_ll_2016_energySigmaDown->Write();
TTtW_ll_centralJesJer->Write();
TTtW_ll_2016_JesSFUp->Write();
TTtW_ll_2016_JesSFDown->Write();
TTtW_ll_2016_JerSFUp->Write();
TTtW_ll_2016_JerSFDown->Write();

f->Write();
f->Close();

}
 
