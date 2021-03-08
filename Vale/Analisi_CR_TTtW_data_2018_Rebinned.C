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
void Analisi_CR_TTtW_data_2018_Rebinned(){

TChain *a_ = new TChain("BOOM");

a_->Add("/eos/user/v/vmariani/NTuples/HN_2018/data_ele_2018.root");
//inputFile

int HLT_Ele, HLT_Mu, HLT_Mu50, HLT_OldMu100, HLT_TkMu50, HLT_TkMu100;
double muejj_l, emujj_l;
double M_leplep;
std:vector<double>* patElectron_pt; patElectron_pt=0;
vector<double>* patElectron_eta; patElectron_eta=0;
vector<double>* patElectron_phi; patElectron_phi=0;
vector<double>* patElectron_energy; patElectron_energy=0;
vector<double>* Muon_pt; Muon_pt=0;
vector<double>* Muon_eta; Muon_eta=0;
vector<double>* Muon_phi; Muon_phi=0;
vector<double>* Muon_energy; Muon_energy=0;
vector<double>*BoostedJet_pt; BoostedJet_pt=0;
vector<double>*BoostedJet_eta; BoostedJet_eta=0;
vector<double>*BoostedJet_phi; BoostedJet_phi=0;
vector<double>*BoostedJet_energy; BoostedJet_energy=0;
double numOfHighptEle, numOfVetoEle, numOfHighptMu, numOfLooseMu, numOfBoostedJets;
double lepsf_evt, lumi_wgt, trueInteractions, PUWeight;
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

TBranch *a_Muon_pt=a_->GetBranch("Muon_pt");
TBranch *a_Muon_eta=a_->GetBranch("Muon_eta");
TBranch *a_Muon_phi=a_->GetBranch("Muon_phi");
TBranch *a_Muon_energy=a_->GetBranch("Muon_energy");

TBranch *a_BoostedJet_pt=a_->GetBranch("BoostedJet_pt");
TBranch *a_BoostedJet_eta=a_->GetBranch("BoostedJet_eta");
TBranch *a_BoostedJet_phi=a_->GetBranch("BoostedJet_phi");
TBranch *a_BoostedJet_energy=a_->GetBranch("BoostedJet_energy");

TBranch *a_M_leplep=a_->GetBranch("M_leplep");
TBranch *a_lepsf_evt=a_->GetBranch("lepsf_evt");
TBranch *a_lumi_wgt=a_->GetBranch("lumi_wgt");

TBranch *a_nBestVtx=a_->GetBranch("nBestVtx");
TBranch *a_trueInteractions=a_->GetBranch("trueInteractions");
TBranch *a_PUWeight=a_->GetBranch("PUWeight");

TBranch *a_muejj_l=a_->GetBranch("muejj_l");
TBranch *a_emujj_l=a_->GetBranch("emujj_l");

TBranch *a_numOfHighptEle=a_->GetBranch("numOfHighptEle");
TBranch *a_numOfHighptMu=a_->GetBranch("numOfHighptMu");
TBranch *a_numOfLooseMu=a_->GetBranch("numOfLooseMu");
TBranch *a_numOfBoostedJets=a_->GetBranch("numOfBoostedJets");
TBranch *a_numOfVetoEle=a_->GetBranch("numOfVetoEle");

a_HLT_Ele115_CaloIdVT_GsfTrkIdT->SetAddress(&HLT_Ele);
a_HLT_Mu50->SetAddress(&HLT_Mu50);
a_HLT_OldMu100->SetAddress(&HLT_OldMu100);
a_HLT_TkMu50->SetAddress(&HLT_TkMu50);
a_HLT_TkMu100->SetAddress(&HLT_TkMu100);

a_patElectron_pt->SetAddress(&patElectron_pt);
a_patElectron_eta->SetAddress(&patElectron_eta);
a_patElectron_phi->SetAddress(&patElectron_phi);
a_patElectron_energy->SetAddress(&patElectron_energy);

a_Muon_pt->SetAddress(&Muon_pt);
a_Muon_eta->SetAddress(&Muon_eta);
a_Muon_phi->SetAddress(&Muon_phi);
a_Muon_energy->SetAddress(&Muon_energy);

a_M_leplep->SetAddress(&M_leplep);
a_lepsf_evt->SetAddress(&lepsf_evt);
a_lumi_wgt->SetAddress(&lumi_wgt);

a_BoostedJet_pt->SetAddress(&BoostedJet_pt);
a_BoostedJet_eta->SetAddress(&BoostedJet_eta);
a_BoostedJet_phi->SetAddress(&BoostedJet_phi);
a_BoostedJet_energy->SetAddress(&BoostedJet_energy);

a_muejj_l->SetAddress(&muejj_l);
a_emujj_l->SetAddress(&emujj_l);

a_nBestVtx->SetAddress(&nBestVtx);
a_trueInteractions->SetAddress(&trueInteractions);
a_PUWeight->SetAddress(&PUWeight);

a_numOfHighptEle->SetAddress(&numOfHighptEle);
a_numOfHighptMu->SetAddress(&numOfHighptMu);
a_numOfLooseMu->SetAddress(&numOfLooseMu);
a_numOfBoostedJets->SetAddress(&numOfBoostedJets);
a_numOfVetoEle->SetAddress(&numOfVetoEle);

const double asymbins[7] = {300,350,400,450,500,700,2000};
const double asymbins2[9] = {0,200,400,600,800,1000,1400,2000,10000};

TH1D *n_best_Vtx = new TH1D ("n_best_Vtx", "n_best_Vtx", 100,0, 100);
TH1D *true_interactions = new TH1D ("true_interactions", "true_interactions", 100,0, 100 ); 
TH1D *Ele_pt = new TH1D ("Ele_pt", "Ele_pt", 200, 0, 5000);
TH1D *Mu_pt = new TH1D ("Mu_pt", "Mu_pt", 200, 0, 5000);
TH1D *Ele_phi = new TH1D ("Ele_phi", "Ele_phi", 200, -3, 3);
TH1D *Mu_phi = new TH1D ("Mu_phi", "Mu_phi", 200, -3, 3);
TH1D *Ele_eta = new TH1D ("Ele_eta", "Ele_eta", 200, -4, 4);
TH1D *Mu_eta = new TH1D ("Mu_eta", "Mu_eta", 200, -4, 4);
TH1D *data_obs = new TH1D ("data_obs", "data_obs", 6, asymbins);
TH1D *Nevents = new TH1D ("Nevents", "Nevents", 4, 0, 2);
TH1D *M_leplepJ = new TH1D ("M_leplepJ", "M_leplepJ", 8, asymbins2);

TLorentzVector Muon;
TLorentzVector Electron;
TLorentzVector BoostJet;
TLorentzVector LeadLep;
TLorentzVector SubLeadLep;

cout << a_->GetEntries() << endl;
int tot=0, muejj = 0;
double wg = 0;
int lumi = 58872; //2017: 41529 //2016: 35920
bool veto_ele = false;
double deltaEta = 0, deltaPhi = 0, deltaR = 0;

for (Int_t i=0;i<a_->GetEntries();i++) {
 a_->GetEntry(i);
 tot = a_->GetEntries();
 if (i%100000 == 0) cout << i << " eventi analizzati su " << tot << endl;

 HLT_Mu = 0;

 if (HLT_Mu50==1 || HLT_TkMu100==1 || HLT_OldMu100==1 ) HLT_Mu = 1;
 if (emujj_l == 1 || muejj_l == 1) muejj = 1; 

 if (Muon_pt->size() > 0 && patElectron_pt->size() > 0 && numOfHighptMu==1 && numOfHighptEle == 1 && numOfBoostedJets>=1){
  if (Muon_pt->at(0) >= patElectron_pt->at(0)){
   LeadLep.SetPtEtaPhiE(Muon_pt->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));
   SubLeadLep.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
  }
  else {
   LeadLep.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0),patElectron_energy->at(0));
   SubLeadLep.SetPtEtaPhiE(Muon_pt->at(0), Muon_eta->at(0), Muon_phi->at(0),Muon_energy->at(0));
  }
  if (HLT_Mu == 1 && LeadLep.Pt() > 150 && SubLeadLep.Pt() > 100 && fabs(Muon_eta->at(0))<2.4 && fabs(patElectron_eta->at(0))<2.4
     && BoostedJet_pt->at(0) > 190 && M_leplep > 300 ){
  
   BoostJet.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0), BoostedJet_energy->at(0));
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
   
    n_best_Vtx->Fill(nBestVtx);
    true_interactions->Fill(trueInteractions);
    Nevents->Fill(1);
    Ele_pt->Fill(patElectron_pt->at(0));
    Ele_eta->Fill(patElectron_eta->at(0));
    Ele_phi->Fill(patElectron_phi->at(0));
    Mu_pt->Fill(Muon_pt->at(0));
    Mu_eta->Fill(Muon_eta->at(0));
    Mu_phi->Fill(Muon_phi->at(0));
    data_obs->Fill((LeadLep+SubLeadLep).M());
    M_leplepJ->Fill((LeadLep+SubLeadLep+BoostJet).M());
   }
  }
 }
}

TFile *f = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2018/CR_TTtW_data_ele_2018.root", "RECREATE");
//TFile *f = new TFile("plots/CR_TTtW_data_ele_2018.root", "RECREATE");
n_best_Vtx->Write();
true_interactions->Write();
Nevents->Write();
Ele_pt->Write();
Mu_pt->Write();
Ele_eta->Write();
Mu_eta->Write();
Ele_phi->Write();
Mu_phi->Write();
data_obs->Write();
M_leplepJ->Write();

f->Write();
f->Close();

}
 
