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
void Analisi_Ele(){

TChain *a_ = new TChain("BOOM");

a_->Add("/eos/user/v/vmariani/NTuples/DY.root");
//inputFile

int HLT_Ele;
double M_leplep;
std:vector<double>* patElectron_pt; patElectron_pt=0;
vector<double>* patElectron_eta; patElectron_eta=0;
vector<double>* patElectron_phi; patElectron_phi=0;
vector<double>*BoostedJet_pt; BoostedJet_pt=0;
vector<double>*BoostedJet_eta; BoostedJet_eta=0;
vector<double>*BoostedJet_phi; BoostedJet_phi=0;
double numOfHighptEle, numOfVetoEle, numOfHighptMu, numOfLooseMu, numOfBoostedJets;
double lepsf_evt, lumi_wgt;

TBranch *a_HLT_Ele115_CaloIdVT_GsfTrkIdT=a_->GetBranch("HLT_Ele115_CaloIdVT_GsfTrkIdT");

TBranch *a_patElectron_pt=a_->GetBranch("patElectron_pt");
TBranch *a_patElectron_eta=a_->GetBranch("patElectron_eta");
TBranch *a_patElectron_phi=a_->GetBranch("patElectron_phi");

TBranch *a_BoostedJet_pt=a_->GetBranch("BoostedJet_pt");
TBranch *a_BoostedJet_eta=a_->GetBranch("BoostedJet_eta");
TBranch *a_BoostedJet_phi=a_->GetBranch("BoostedJet_phi");

TBranch *a_M_leplep=a_->GetBranch("M_leplep");
TBranch *a_lepsf_evt=a_->GetBranch("lepsf_evt");
TBranch *a_lumi_wgt=a_->GetBranch("lumi_wgt");

TBranch *a_numOfHighptEle=a_->GetBranch("numOfHighptEle");
TBranch *a_numOfHighptMu=a_->GetBranch("numOfHighptMu");
TBranch *a_numOfLooseMu=a_->GetBranch("numOfLooseMu");
TBranch *a_numOfBoostedJets=a_->GetBranch("numOfBoostedJets");
TBranch *a_numOfVetoEle=a_->GetBranch("numOfVetoEle");

a_HLT_Ele115_CaloIdVT_GsfTrkIdT->SetAddress(&HLT_Ele);

a_patElectron_pt->SetAddress(&patElectron_pt);
a_patElectron_eta->SetAddress(&patElectron_eta);
a_patElectron_phi->SetAddress(&patElectron_phi);

a_M_leplep->SetAddress(&M_leplep);
a_lepsf_evt->SetAddress(&lepsf_evt);
a_lumi_wgt->SetAddress(&lumi_wgt);

a_BoostedJet_pt->SetAddress(&BoostedJet_pt);
a_BoostedJet_eta->SetAddress(&BoostedJet_eta);
a_BoostedJet_phi->SetAddress(&BoostedJet_phi);

a_numOfHighptEle->SetAddress(&numOfHighptEle);
a_numOfHighptMu->SetAddress(&numOfHighptMu);
a_numOfLooseMu->SetAddress(&numOfLooseMu);
a_numOfBoostedJets->SetAddress(&numOfBoostedJets);
a_numOfVetoEle->SetAddress(&numOfVetoEle);

TH1D *Ele1_pt_shape_jet190 = new TH1D ("Ele1_pt_shape_jet190", "Ele1_pt_shape_jet190", 200, 0, 5000);
TH1D *Ele2_pt_shape_jet190 = new TH1D ("Ele2_pt_shape_jet190", "Ele2_pt_shape_jet190", 200, 0, 5000);
TH1D *M_ll_shape_jet190 = new TH1D ("M_ll_shape_jet190", "M_ll_shape_jet190", 500, 0, 8000);
TH1D *Ele1_pt_jet190 = new TH1D ("Ele1_pt_jet190", "Ele1_pt_jet190", 200, 0, 5000);
TH1D *Ele2_pt_jet190 = new TH1D ("Ele2_pt_jet190", "Ele2_pt_jet190", 200, 0, 5000);
TH1D *Ele1_phi_jet190 = new TH1D ("Ele1_phi_jet190", "Ele1_phi_jet190", 200, -3, 3);
TH1D *Ele2_phi_jet190 = new TH1D ("Ele2_phi_jet190", "Ele2_phi_jet190", 200, -3, 3);
TH1D *Ele1_eta_jet190 = new TH1D ("Ele1_eta_jet190", "Ele1_eta_jet190", 200, -4, 4);
TH1D *Ele2_eta_jet190 = new TH1D ("Ele2_eta_jet190", "Ele2_eta_jet190", 200, -4, 4);
TH1D *M_ll_jet190 = new TH1D ("M_ll_jet190", "M_ll_jet190", 500, 0, 8000);
TH1D *Jet_pt_jet190 = new TH1D ("Jet_pt_jet190", "Jet_pt_jet190", 200, 0, 5000);
TH1D *Jet_phi_jet190 = new TH1D ("Jet_phi_jet190", "Jet_phi_jet190", 200, -3, 3);
TH1D *Jet_eta_jet190 = new TH1D ("Jet_eta_jet190", "Jet_eta_jet190", 200, -4, 4);

TH1D *Ele1_pt_shape_jetpt200 = new TH1D ("Ele1_pt_shape_jetpt200", "Ele1_pt_shape_jetpt200", 200, 0, 5000);
TH1D *Ele2_pt_shape_jetpt200 = new TH1D ("Ele2_pt_shape_jetpt200", "Ele2_pt_shape_jetpt200", 200, 0, 5000);
TH1D *M_ll_shape_jetpt200 = new TH1D ("M_ll_shape_jetpt200", "M_ll_shape_jetpt200", 500, 0, 8000);
TH1D *Ele1_pt_jetpt200 = new TH1D ("Ele1_pt_jetpt200", "Ele1_pt_jetpt200", 200, 0, 5000);
TH1D *Ele2_pt_jetpt200 = new TH1D ("Ele2_pt_jetpt200", "Ele2_pt_jetpt200", 200, 0, 5000);
TH1D *Ele1_phi_jetpt200 = new TH1D ("Ele1_phi_jetpt200", "Ele1_phi_jetpt200", 200, -3, 3); 
TH1D *Ele2_phi_jetpt200 = new TH1D ("Ele2_phi_jetpt200", "Ele2_phi_jetpt200", 200, -3, 3);
TH1D *Ele1_eta_jetpt200 = new TH1D ("Ele1_eta_jetpt200", "Ele1_eta_jetpt200", 200, -4, 4); 
TH1D *Ele2_eta_jetpt200 = new TH1D ("Ele2_eta_jetpt200", "Ele2_eta_jetpt200", 200, -4, 4);
TH1D *M_ll_jetpt200 = new TH1D ("M_ll_jetpt200", "M_ll_jetpt200", 500, 0, 8000);
TH1D *Jet_pt_jet200 = new TH1D ("Jet_pt_jet200", "Jet_pt_jet200", 200, 0, 5000);
TH1D *Jet_phi_jet200 = new TH1D ("Jet_phi_jet200", "Jet_phi_jet200", 200, -3, 3);
TH1D *Jet_eta_jet200 = new TH1D ("Jet_eta_jet200", "Jet_eta_jet200", 200, -4, 4);

TH1D *Ele1_pt_shape_jetpt220 = new TH1D ("Ele1_pt_shape_jetpt220", "Ele1_pt_shape_jetpt220", 200, 0, 5000);
TH1D *Ele2_pt_shape_jetpt220 = new TH1D ("Ele2_pt_shape_jetpt220", "Ele2_pt_shape_jetpt220", 200, 0, 5000);
TH1D *M_ll_shape_jetpt220 = new TH1D ("M_ll_shape_jetpt220", "M_ll_shape_jetpt220", 500, 0, 8000);
TH1D *Ele1_pt_jetpt220 = new TH1D ("Ele1_pt_jetpt220", "Ele1_pt_jetpt220", 200, 0, 5000);
TH1D *Ele2_pt_jetpt220 = new TH1D ("Ele2_pt_jetpt220", "Ele2_pt_jetpt220", 200, 0, 5000);
TH1D *Ele1_phi_jetpt220 = new TH1D ("Ele1_phi_jetpt220", "Ele1_phi_jetpt220", 200, -3, 3); 
TH1D *Ele2_phi_jetpt220 = new TH1D ("Ele2_phi_jetpt220", "Ele2_phi_jetpt220", 200, -3, 3);
TH1D *Ele1_eta_jetpt220 = new TH1D ("Ele1_eta_jetpt220", "Ele1_eta_jetpt220", 200, -4, 4); 
TH1D *Ele2_eta_jetpt220 = new TH1D ("Ele2_eta_jetpt220", "Ele2_eta_jetpt220", 200, -4, 4);
TH1D *M_ll_jetpt220 = new TH1D ("M_ll_jetpt220", "M_ll_jetpt220", 500, 0, 8000);
TH1D *Jet_pt_jet220 = new TH1D ("Jet_pt_jet220", "Jet_pt_jet220", 200, 0, 5000);
TH1D *Jet_phi_jet220 = new TH1D ("Jet_phi_jet220", "Jet_phi_jet220", 200, -3, 3);
TH1D *Jet_eta_jet220 = new TH1D ("Jet_eta_jet220", "Jet_eta_jet220", 200, -4, 4);

TH1D *Ele1_pt_shape_jetpt250 = new TH1D ("Ele1_pt_shape_jetpt250", "Ele1_pt_shape_jetpt250", 200, 0, 5000);
TH1D *Ele2_pt_shape_jetpt250 = new TH1D ("Ele2_pt_shape_jetpt250", "Ele2_pt_shape_jetpt250", 200, 0, 5000);
TH1D *M_ll_shape_jetpt250 = new TH1D ("M_ll_shape_jetpt250", "M_ll_shape_jetpt250", 500, 0, 8000);
TH1D *Ele1_pt_jetpt250 = new TH1D ("Ele1_pt_jetpt250", "Ele1_pt_jetpt250", 200, 0, 5000);
TH1D *Ele2_pt_jetpt250 = new TH1D ("Ele2_pt_jetpt250", "Ele2_pt_jetpt250", 200, 0, 5000);
TH1D *Ele1_phi_jetpt250 = new TH1D ("Ele1_phi_jetpt250", "Ele1_phi_jetpt250", 200, -3, 3); 
TH1D *Ele2_phi_jetpt250 = new TH1D ("Ele2_phi_jetpt250", "Ele2_phi_jetpt250", 200, -3, 3);
TH1D *Ele1_eta_jetpt250 = new TH1D ("Ele1_eta_jetpt250", "Ele1_eta_jetpt250", 200, -4, 4); 
TH1D *Ele2_eta_jetpt250 = new TH1D ("Ele2_eta_jetpt250", "Ele2_eta_jetpt250", 200, -4, 4);
TH1D *M_ll_jetpt250 = new TH1D ("M_ll_jetpt250", "M_ll_jetpt250", 500, 0, 8000);
TH1D *Jet_pt_jet250 = new TH1D ("Jet_pt_jet250", "Jet_pt_jet250", 200, 0, 5000);
TH1D *Jet_phi_jet250 = new TH1D ("Jet_phi_jet250", "Jet_phi_jet250", 200, -3, 3);
TH1D *Jet_eta_jet250 = new TH1D ("Jet_eta_jet250", "Jet_eta_jet250", 200, -4, 4);

TH1D *Ele1_pt_shape_jetpt270 = new TH1D ("Ele1_pt_shape_jetpt270", "Ele1_pt_shape_jetpt270", 200, 0, 5000);
TH1D *Ele2_pt_shape_jetpt270 = new TH1D ("Ele2_pt_shape_jetpt270", "Ele2_pt_shape_jetpt270", 200, 0, 5000);
TH1D *M_ll_shape_jetpt270 = new TH1D ("M_ll_shape_jetpt270", "M_ll_shape_jetpt270", 500, 0, 8000);
TH1D *Ele1_pt_jetpt270 = new TH1D ("Ele1_pt_jetpt270", "Ele1_pt_jetpt270", 200, 0, 5000);
TH1D *Ele2_pt_jetpt270 = new TH1D ("Ele2_pt_jetpt270", "Ele2_pt_jetpt270", 200, 0, 5000);
TH1D *Ele1_phi_jetpt270 = new TH1D ("Ele1_phi_jetpt270", "Ele1_phi_jetpt270", 200, -3, 3); 
TH1D *Ele2_phi_jetpt270 = new TH1D ("Ele2_phi_jetpt270", "Ele2_phi_jetpt270", 200, -3, 3);
TH1D *Ele1_eta_jetpt270 = new TH1D ("Ele1_eta_jetpt270", "Ele1_eta_jetpt270", 200, -4, 4); 
TH1D *Ele2_eta_jetpt270 = new TH1D ("Ele2_eta_jetpt270", "Ele2_eta_jetpt270", 200, -4, 4);
TH1D *M_ll_jetpt270 = new TH1D ("M_ll_jetpt270", "M_ll_jetpt270", 500, 0, 8000);
TH1D *Jet_pt_jet270 = new TH1D ("Jet_pt_jet270", "Jet_pt_jet270", 200, 0, 5000);
TH1D *Jet_phi_jet270 = new TH1D ("Jet_phi_jet270", "Jet_phi_jet270", 200, -3, 3);
TH1D *Jet_eta_jet270 = new TH1D ("Jet_eta_jet270", "Jet_eta_jet270", 200, -4, 4);

TH1D *Ele1_pt_shape_jetpt300 = new TH1D ("Ele1_pt_shape_jetpt300", "Ele1_pt_shape_jetpt300", 200, 0, 5000);
TH1D *Ele2_pt_shape_jetpt300 = new TH1D ("Ele2_pt_shape_jetpt300", "Ele2_pt_shape_jetpt300", 200, 0, 5000);
TH1D *M_ll_shape_jetpt300 = new TH1D ("M_ll_shape_jetpt300", "M_ll_shape_jetpt300", 500, 0, 8000);
TH1D *Ele1_pt_jetpt300 = new TH1D ("Ele1_pt_jetpt300", "Ele1_pt_jetpt300", 200, 0, 5000);
TH1D *Ele2_pt_jetpt300 = new TH1D ("Ele2_pt_jetpt300", "Ele2_pt_jetpt300", 200, 0, 5000);
TH1D *Ele1_phi_jetpt300 = new TH1D ("Ele1_phi_jetpt300", "Ele1_phi_jetpt300", 200, -3, 3);
TH1D *Ele2_phi_jetpt300 = new TH1D ("Ele2_phi_jetpt300", "Ele2_phi_jetpt300", 200, -3, 3);
TH1D *Ele1_eta_jetpt300 = new TH1D ("Ele1_eta_jetpt300", "Ele1_eta_jetpt300", 200, -4, 4);
TH1D *Ele2_eta_jetpt300 = new TH1D ("Ele2_eta_jetpt300", "Ele2_eta_jetpt300", 200, -4, 4);
TH1D *M_ll_jetpt300 = new TH1D ("M_ll_jetpt300", "M_ll_jetpt300", 500, 0, 8000);
TH1D *Jet_pt_jet300 = new TH1D ("Jet_pt_jet300", "Jet_pt_jet300", 200, 0, 5000);
TH1D *Jet_phi_jet300 = new TH1D ("Jet_phi_jet300", "Jet_phi_jet300", 200, -3, 3);
TH1D *Jet_eta_jet300 = new TH1D ("Jet_eta_jet300", "Jet_eta_jet300", 200, -4, 4);

TH1D *Ele1_pt_shape_jetpt500 = new TH1D ("Ele1_pt_shape_jetpt500", "Ele1_pt_shape_jetpt500", 200, 0, 5000);
TH1D *Ele2_pt_shape_jetpt500 = new TH1D ("Ele2_pt_shape_jetpt500", "Ele2_pt_shape_jetpt500", 200, 0, 5000);
TH1D *M_ll_shape_jetpt500 = new TH1D ("M_ll_shape_jetpt500", "M_ll_shape_jetpt500", 500, 0, 8000);
TH1D *Ele1_pt_jetpt500 = new TH1D ("Ele1_pt_jetpt500", "Ele1_pt_jetpt500", 200, 0, 5000);
TH1D *Ele2_pt_jetpt500 = new TH1D ("Ele2_pt_jetpt500", "Ele2_pt_jetpt500", 200, 0, 5000);
TH1D *Ele1_phi_jetpt500 = new TH1D ("Ele1_phi_jetpt500", "Ele1_phi_jetpt500", 200, -3, 3);
TH1D *Ele2_phi_jetpt500 = new TH1D ("Ele2_phi_jetpt500", "Ele2_phi_jetpt500", 200, -3, 3);
TH1D *Ele1_eta_jetpt500 = new TH1D ("Ele1_eta_jetpt500", "Ele1_eta_jetpt500", 200, -4, 4);
TH1D *Ele2_eta_jetpt500 = new TH1D ("Ele2_eta_jetpt500", "Ele2_eta_jetpt500", 200, -4, 4);
TH1D *M_ll_jetpt500 = new TH1D ("M_ll_jetpt500", "M_ll_jetpt500", 500, 0, 8000);
TH1D *Jet_pt_jet500 = new TH1D ("Jet_pt_jet500", "Jet_pt_jet500", 200, 0, 5000);
TH1D *Jet_phi_jet500 = new TH1D ("Jet_phi_jet500", "Jet_phi_jet500", 200, -3, 3);
TH1D *Jet_eta_jet500 = new TH1D ("Jet_eta_jet500", "Jet_eta_jet500", 200, -4, 4);


cout << a_->GetEntries() << endl;
int tot=0;
double wg = 0;
double lumi = 41529;
for (Int_t i=0;i<a_->GetEntries();i++) {
 a_->GetEntry(i);
 tot = a_->GetEntries();
 if (i%100000 == 0) cout << i << " eventi analizzati su " << tot << endl;

 if (patElectron_pt->size() > 1 && BoostedJet_pt->size() > 0){
  if (HLT_Ele==1 && patElectron_pt->at(0) > 250 && patElectron_pt->at(1) > 120 && fabs(patElectron_eta->at(0))<2.4 && fabs(patElectron_eta->at(1))<2.4 && numOfHighptEle==2 
   && M_leplep>500 && BoostedJet_pt->at(0) > 190 && numOfLooseMu==0 && numOfBoostedJets>=1){

   wg = lumi*lumi_wgt*lepsf_evt;

   Ele1_pt_shape_jet190->Fill(patElectron_pt->at(0));
   Ele2_pt_shape_jet190->Fill(patElectron_pt->at(1));
   M_ll_shape_jet190->Fill(M_leplep);
   Ele1_pt_jet190->Fill(patElectron_pt->at(0),wg);
   Ele1_eta_jet190->Fill(patElectron_eta->at(0),wg);
   Ele1_phi_jet190->Fill(patElectron_phi->at(0),wg);
   Ele2_pt_jet190->Fill(patElectron_pt->at(1),wg);
   Ele2_eta_jet190->Fill(patElectron_eta->at(1),wg);
   Ele2_phi_jet190->Fill(patElectron_phi->at(1),wg);
   M_ll_jet190->Fill(M_leplep,wg);
   Jet_pt_jet190->Fill(BoostedJet_pt->at(0),wg);
   Jet_eta_jet190->Fill(BoostedJet_eta->at(0),wg);
   Jet_phi_jet190->Fill(BoostedJet_phi->at(0),wg);
   
   if (BoostedJet_pt->at(0) > 200){
    Ele1_pt_shape_jetpt200->Fill(patElectron_pt->at(0));
    Ele2_pt_shape_jetpt200->Fill(patElectron_pt->at(1));
    M_ll_shape_jetpt200->Fill(M_leplep,wg);
    Ele1_pt_jetpt200->Fill(patElectron_pt->at(0),wg);
    Ele1_eta_jetpt200->Fill(patElectron_eta->at(0),wg);
    Ele1_phi_jetpt200->Fill(patElectron_phi->at(0),wg);
    Ele2_pt_jetpt200->Fill(patElectron_pt->at(1),wg);
    Ele2_eta_jetpt200->Fill(patElectron_eta->at(1),wg);
    Ele2_phi_jetpt200->Fill(patElectron_phi->at(1),wg);
    M_ll_jetpt200->Fill(M_leplep,wg);
    Jet_pt_jet200->Fill(BoostedJet_pt->at(0),wg);
    Jet_eta_jet200->Fill(BoostedJet_eta->at(0),wg);
    Jet_phi_jet200->Fill(BoostedJet_phi->at(0),wg);
   }
   if (BoostedJet_pt->at(0) > 220){
    Ele1_pt_shape_jetpt220->Fill(patElectron_pt->at(0));
    Ele2_pt_shape_jetpt220->Fill(patElectron_pt->at(1));
    M_ll_shape_jetpt220->Fill(M_leplep,wg);
    Ele1_pt_jetpt220->Fill(patElectron_pt->at(0),wg);
    Ele1_eta_jetpt220->Fill(patElectron_eta->at(0),wg);
    Ele1_phi_jetpt220->Fill(patElectron_phi->at(0),wg);
    Ele2_pt_jetpt220->Fill(patElectron_pt->at(1),wg);
    Ele2_eta_jetpt220->Fill(patElectron_eta->at(1),wg);
    Ele2_phi_jetpt220->Fill(patElectron_phi->at(1),wg);
    M_ll_jetpt220->Fill(M_leplep,wg);
    Jet_pt_jet220->Fill(BoostedJet_pt->at(0),wg);
    Jet_eta_jet220->Fill(BoostedJet_eta->at(0),wg);
    Jet_phi_jet220->Fill(BoostedJet_phi->at(0),wg);
   }
   if (BoostedJet_pt->at(0) > 250){
    Ele1_pt_shape_jetpt250->Fill(patElectron_pt->at(0));
    Ele2_pt_shape_jetpt250->Fill(patElectron_pt->at(1));
    M_ll_shape_jetpt250->Fill(M_leplep,wg);
    Ele1_pt_jetpt250->Fill(patElectron_pt->at(0),wg);
    Ele1_eta_jetpt250->Fill(patElectron_eta->at(0),wg);
    Ele1_phi_jetpt250->Fill(patElectron_phi->at(0),wg);
    Ele2_pt_jetpt250->Fill(patElectron_pt->at(1),wg);
    Ele2_eta_jetpt250->Fill(patElectron_eta->at(1),wg);
    Ele2_phi_jetpt250->Fill(patElectron_phi->at(1),wg);
    M_ll_jetpt250->Fill(M_leplep,wg);
    Jet_pt_jet250->Fill(BoostedJet_pt->at(0),wg);
    Jet_eta_jet250->Fill(BoostedJet_eta->at(0),wg);
    Jet_phi_jet250->Fill(BoostedJet_phi->at(0),wg);
   }  
   if (BoostedJet_pt->at(0) > 270){
    Ele1_pt_shape_jetpt270->Fill(patElectron_pt->at(0));
    Ele2_pt_shape_jetpt270->Fill(patElectron_pt->at(1));
    M_ll_shape_jetpt270->Fill(M_leplep,wg);
    Ele1_pt_jetpt270->Fill(patElectron_pt->at(0),wg);
    Ele1_eta_jetpt270->Fill(patElectron_eta->at(0),wg);
    Ele1_phi_jetpt270->Fill(patElectron_phi->at(0),wg);
    Ele2_pt_jetpt270->Fill(patElectron_pt->at(1),wg);
    Ele2_eta_jetpt270->Fill(patElectron_eta->at(1),wg);
    Ele2_phi_jetpt270->Fill(patElectron_phi->at(1),wg);
    M_ll_jetpt270->Fill(M_leplep,wg);
    Jet_pt_jet270->Fill(BoostedJet_pt->at(0),wg);
    Jet_eta_jet270->Fill(BoostedJet_eta->at(0),wg);
    Jet_phi_jet270->Fill(BoostedJet_phi->at(0),wg);
   }
   if (BoostedJet_pt->at(0) > 300){
    Ele1_pt_shape_jetpt300->Fill(patElectron_pt->at(0));
    Ele2_pt_shape_jetpt300->Fill(patElectron_pt->at(1));
    M_ll_shape_jetpt300->Fill(M_leplep,wg);
    Ele1_pt_jetpt300->Fill(patElectron_pt->at(0),wg);
    Ele1_eta_jetpt300->Fill(patElectron_eta->at(0),wg);
    Ele1_phi_jetpt300->Fill(patElectron_phi->at(0),wg);
    Ele2_pt_jetpt300->Fill(patElectron_pt->at(1),wg);
    Ele2_eta_jetpt300->Fill(patElectron_eta->at(1),wg);
    Ele2_phi_jetpt300->Fill(patElectron_phi->at(1),wg);
    M_ll_jetpt300->Fill(M_leplep,wg);
    Jet_pt_jet300->Fill(BoostedJet_pt->at(0),wg);
    Jet_eta_jet300->Fill(BoostedJet_eta->at(0),wg);
    Jet_phi_jet300->Fill(BoostedJet_phi->at(0),wg);
   }
   if (BoostedJet_pt->at(0) > 500){
    Ele1_pt_shape_jetpt500->Fill(patElectron_pt->at(0));
    Ele2_pt_shape_jetpt500->Fill(patElectron_pt->at(1));
    M_ll_shape_jetpt500->Fill(M_leplep,wg);
    Ele1_pt_jetpt500->Fill(patElectron_pt->at(0),wg);
    Ele1_eta_jetpt500->Fill(patElectron_eta->at(0),wg);
    Ele1_phi_jetpt500->Fill(patElectron_phi->at(0),wg);
    Ele2_pt_jetpt500->Fill(patElectron_pt->at(1),wg);
    Ele2_eta_jetpt500->Fill(patElectron_eta->at(1),wg);
    Ele2_phi_jetpt500->Fill(patElectron_phi->at(1),wg);
    M_ll_jetpt500->Fill(M_leplep,wg);
    Jet_pt_jet500->Fill(BoostedJet_pt->at(0),wg);
    Jet_eta_jet500->Fill(BoostedJet_eta->at(0),wg);
    Jet_phi_jet500->Fill(BoostedJet_phi->at(0),wg);
   }
  }
 }
}

TFile *f = new TFile("Ele_JetPt_various_cuts_DY.root", "RECREATE");

Ele1_pt_shape_jet190->Write();
Ele2_pt_shape_jet190->Write();
M_ll_shape_jet190->Write();
Ele1_pt_jet190->Write();
Ele2_pt_jet190->Write();
Ele1_eta_jet190->Write();
Ele2_eta_jet190->Write();
Ele1_phi_jet190->Write();
Ele2_phi_jet190->Write();
M_ll_jet190->Write();
Jet_pt_jet190->Write();
Jet_eta_jet190->Write();
Jet_phi_jet190->Write();

Ele1_pt_shape_jetpt200->Write();
Ele2_pt_shape_jetpt200->Write();
M_ll_shape_jetpt200->Write();
Ele1_pt_jetpt200->Write();
Ele2_pt_jetpt200->Write();
Ele1_eta_jetpt200->Write();
Ele2_eta_jetpt200->Write();
Ele1_phi_jetpt200->Write();
Ele2_phi_jetpt200->Write();
M_ll_jetpt200->Write();
Jet_pt_jet200->Write();
Jet_eta_jet200->Write();
Jet_phi_jet200->Write();

Ele1_pt_shape_jetpt220->Write();
Ele2_pt_shape_jetpt220->Write();
M_ll_shape_jetpt220->Write();
Ele1_pt_jetpt220->Write();
Ele2_pt_jetpt220->Write();
Ele1_eta_jetpt220->Write();
Ele2_eta_jetpt220->Write();
Ele1_phi_jetpt220->Write();
Ele2_phi_jetpt220->Write();
M_ll_jetpt220->Write();
Jet_pt_jet220->Write();
Jet_eta_jet220->Write();
Jet_phi_jet220->Write();

Ele1_pt_shape_jetpt250->Write();
Ele2_pt_shape_jetpt250->Write();
M_ll_shape_jetpt250->Write();
Ele1_pt_jetpt250->Write();
Ele2_pt_jetpt250->Write();
Ele1_eta_jetpt250->Write();
Ele2_eta_jetpt250->Write();
Ele1_phi_jetpt250->Write();
Ele2_phi_jetpt250->Write();
M_ll_jetpt250->Write();
Jet_pt_jet250->Write();
Jet_eta_jet250->Write();
Jet_phi_jet250->Write();

Ele1_pt_shape_jetpt270->Write();
Ele2_pt_shape_jetpt270->Write();
M_ll_shape_jetpt270->Write();
Ele1_pt_jetpt270->Write();
Ele2_pt_jetpt270->Write();
Ele1_eta_jetpt270->Write();
Ele2_eta_jetpt270->Write();
Ele1_phi_jetpt270->Write();
Ele2_phi_jetpt270->Write();
M_ll_jetpt270->Write();
Jet_pt_jet270->Write();
Jet_eta_jet270->Write();
Jet_phi_jet270->Write();

Ele1_pt_shape_jetpt300->Write();
Ele2_pt_shape_jetpt300->Write();
M_ll_shape_jetpt300->Write();
Ele1_pt_jetpt300->Write();
Ele2_pt_jetpt300->Write();
Ele1_eta_jetpt300->Write();
Ele2_eta_jetpt300->Write();
Ele1_phi_jetpt300->Write();
Ele2_phi_jetpt300->Write();
M_ll_jetpt300->Write();
Jet_pt_jet300->Write();
Jet_eta_jet300->Write();
Jet_phi_jet300->Write();

Ele1_pt_shape_jetpt500->Write();
Ele2_pt_shape_jetpt500->Write();
M_ll_shape_jetpt500->Write();
Ele1_pt_jetpt500->Write();
Ele2_pt_jetpt500->Write();
Ele1_eta_jetpt500->Write();
Ele2_eta_jetpt500->Write();
Ele1_phi_jetpt500->Write();
Ele2_phi_jetpt500->Write();
M_ll_jetpt500->Write();
Jet_pt_jet500->Write();
Jet_eta_jet500->Write();
Jet_phi_jet500->Write();

f->Write();
f->Close();

}
 
