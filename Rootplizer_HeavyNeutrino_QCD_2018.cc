/**
This Macro
1. Prepares the rootplas to be used in the analysis, reading as input the nutplas 
Need to specify
0. See Declare constants
1. The branches you want to handle. According to the analysis needs, one may want to handle 3 types of branches for reading and/or saving the variables
  Type   Reading  Saving  Example
  varA   Yes      Yes     Jet_pt: you want to save it and need also to read it (using SetBranchStatus+CopyEntries would require more processing time) 
  varB   Yes      No      Jet_muonEnergyFraction: you want to read it to define jet ID, but may not want to save it  
  varC   No       Yes     Jet_LooseID: you can not read it from ntuplas if there is not, but you want to save in rootplas 
  Depending on the Type you may need to add different lines on this macro. Please use the script Variables_Rootplizer.sh for printing the needed lines.
3. Every variable of TypeC requires a dedicated function, if you need more than 2 lines to define it
4. Please be coherent with indentation, functions, object labels. Be clean and tidy in general!
5. Changes to do:
A. 
  Test the rootplizer as usual
B.
  Leave only 
  const int nentries    = -1;
  in "Declare constants" section
  Comment/Delete the rest
C. 
  Comment/Delete Call_TFile functions and all its implementation 
D. 
  At the beginning of the macro substitue
     void namemacro(){
      vector<string> rootplas(samples, samples + sizeof(samples)/sizeof(samples[0]));
      for(uint r=0; r<rootplas.size(); r++){
  with
     void namemacro(const char*  Input = "", const char*  Output =""){
       TFile *oldfile = TFile::Open(Input);
E. 
  Substitute
    TFile *newfile = new TFile((suffisso+".root").c_str(),"recreate");
  with
    TFile *newfile = new TFile(Output,"recreate");
F.
  At the end of the main of the macro, substitute
      newfile->Close();
     }
  with 
      newfile->Close();
  i.e.: comment/delete the curl paranthesis below newfile->Close();
*/
/////
//   To run: root -l Rootplizer_TTHLep.cc+  
/////
/////
//   Prepare Root and Roofit
/////
#include "TFile.h"
#include "TObject.h"
#include "TTree.h"
#include "TTreePlayer.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iostream>
#include <TLorentzVector.h>
#include "TVector3.h"
using namespace std;
////
//   Declare constants
///// 
const int nentries    = -1;
//const int isMC=1;
/////
//   Declare functions 
/////
double deltaPhi(double phi1, double phi2);
bool JetID_Loose(double rJet1, double rJet2, double rJet3, double rJet4,int rJet5, double rJet6, double rJet7, int rJet8, double rJet9);
bool JetID_Tight(double rJet1, double rJet2, double rJet3, double rJet4,int rJet5, double rJet6, double rJet7, int rJet8, double rJet9);
bool JetID_TightLepVeto(double rJet1, double rJet2, double rJet3, double rJet4,int rJet5, double rJet6, double rJet7, int rJet8, double rJet9);
bool BoostedJetID_Loose(double rJet1, double rJet2, double rJet3, double rJet4,int rJet5, double rJet6, double rJet7, int rJet8, double rJet9);
bool BoostedJetID_Tight(double rJet1, double rJet2, double rJet3, double rJet4,int rJet5, double rJet6, double rJet7, int rJet8, double rJet9);
bool BoostedJetID_TightLepVeto(double rJet1, double rJet2, double rJet3, double rJet4,int rJet5, double rJet6, double rJet7, int rJet8, double rJet9);
double CalculatePileupWeight(int trueInteractions);
double elesf(double eta);
double musf_trigger(double eta,double pt);
double musf_ID(double eta, double pt);
double musf_iso(double eta, double pt);
double get_wgtlumi(string FileName);
double HEEPID_check(double Et, double SCeta, double isEcalDriven, double dEtaIn, double dPhiIn, double hOverE, double full5x5_sigmaIetaIeta, double full5x5_e2x5Max, double full5x5_e5x5, double full5x5_e1x5, double ecalPFClusterIso, double hcalPFClusterIso, double isolPtTracks, double expectedMissingInnerHits, double gsfTrack_dxy_pv, double d0, double E, double rho);
double HEEPnonISO_check(double Et, double SCeta, double isEcalDriven, double dEtaIn, double dPhiIn, double hOverE, double full5x5_sigmaIetaIeta, double full5x5_e2x5Max, double full5x5_e5x5, double full5x5_e1x5, double ecalPFClusterIso, double hcalPFClusterIso, double isolPtTracks, double expectedMissingInnerHits, double gsfTrack_dxy_pv, double d0, double E, double rho);
double Mt(double px1, double py1, double pt1, double px2, double py2);
double FakeRateID(double SCeta, double full5x5_sigmaIetaIeta, double hOverE, double expectedMissingInnerHits, double gsfTrack_dxy_pv);
double Wgt_QCD(double SCeta, double Et);
double FakeRateIDmu(int Global, int Tracker, double dz, double dxy, double TLayers, double validHitsInner);
double Wgt_QCDmu(double eta, double pt);
/*double invMass2(double obj1_px, double obj1_py, double obj1_pz, double obj1_E,
                double obj2_px, double obj2_py, double obj2_pz, double obj2_E);
double invMass3(double obj1_px, double obj1_py, double obj1_pz, double obj1_E,
                double obj2_px, double obj2_py, double obj2_pz, double obj2_E,
                double obj3_px, double obj3_py, double obj3_pz, double obj3_E);
double invMass4(double obj1_px, double obj1_py, double obj1_pz, double obj1_E,
                double obj2_px, double obj2_py, double obj2_pz, double obj2_E,
                double obj3_px, double obj3_py, double obj3_pz, double obj3_E,
                double obj4_px, double obj4_py, double obj4_pz, double obj4_E);*/
/////
//   Main function
/////
void  Rootplizer_HeavyNeutrino_QCD(const char*  Input = "", const char*  Output =""){
  TFile *oldfile = TFile::Open(Input);
  TTree *readingtree = new TTree("readingtree","readingtree"); readingtree = (TTree*) oldfile->Get("TNT/BOOM");
  /////
  //   Variables to read
  /////
  //Trigger
  int rHLT_Ele27_eta2p1_WPLoose_Gsf; rHLT_Ele27_eta2p1_WPLoose_Gsf = 0; TBranch* b_rHLT_Ele27_eta2p1_WPLoose_Gsf = 0; readingtree->SetBranchAddress("HLT_Ele27_eta2p1_WPLoose_Gsf",&rHLT_Ele27_eta2p1_WPLoose_Gsf,&b_rHLT_Ele27_eta2p1_WPLoose_Gsf);
  //int rHLT_DoubleEle33_CaloIdL_GsfTrkIdVL; rHLT_DoubleEle33_CaloIdL_GsfTrkIdVL = 0; TBranch* b_rHLT_DoubleEle33_CaloIdL_GsfTrkIdVL = 0; readingtree->SetBranchAddress("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL",&rHLT_DoubleEle33_CaloIdL_GsfTrkIdVL,&b_rHLT_DoubleEle33_CaloIdL_GsfTrkIdVL);
  int rHLT_Ele115_CaloIdVT_GsfTrkIdT; rHLT_Ele115_CaloIdVT_GsfTrkIdT = 0; TBranch* b_rHLT_Ele115_CaloIdVT_GsfTrkIdT = 0; readingtree->SetBranchAddress("HLT_Ele115_CaloIdVT_GsfTrkIdT",&rHLT_Ele115_CaloIdVT_GsfTrkIdT,&b_rHLT_Ele115_CaloIdVT_GsfTrkIdT);
  int rHLT_Mu50; rHLT_Mu50 = 0; TBranch* b_rHLT_Mu50 = 0; readingtree->SetBranchAddress("HLT_Mu50",&rHLT_Mu50,&b_rHLT_Mu50);
  int rHLT_TkMu50; rHLT_TkMu50 = 0; TBranch* b_rHLT_TkMu50 = 0; readingtree->SetBranchAddress("HLT_TkMu50",&rHLT_TkMu50,&b_rHLT_TkMu50);
  int rHLT_OldMu100; rHLT_OldMu100 = 0; TBranch* b_rHLT_OldMu100 = 0; readingtree->SetBranchAddress("HLT_OldMu100",&rHLT_OldMu100,&b_rHLT_OldMu100);
  int rHLT_TkMu100; rHLT_TkMu100 = 0; TBranch* b_rHLT_TkMu100 = 0; readingtree->SetBranchAddress("HLT_TkMu100",&rHLT_TkMu100,&b_rHLT_TkMu100);

  //PU
  double rPUWeight; rPUWeight = 0; TBranch* b_rPUWeight = 0; readingtree->SetBranchAddress("PUWeight",&rPUWeight,&b_rPUWeight);
  double rtrueInteractions; rtrueInteractions = 0; TBranch* b_rtrueInteractions = 0; readingtree->SetBranchAddress("trueInteractions",&rtrueInteractions,&b_rtrueInteractions);
  int rnBestVtx; rnBestVtx = 0; TBranch* b_rnBestVtx = 0; readingtree->SetBranchAddress("nBestVtx",&rnBestVtx,&b_rnBestVtx);
  //MET
  double rMet_type1PF_pt; rMet_type1PF_pt = 0; TBranch* b_rMet_type1PF_pt = 0; 
  readingtree->SetBranchAddress("Met_type1PF_pt",&rMet_type1PF_pt,&b_rMet_type1PF_pt);
  double rMet_type1PF_phi; rMet_type1PF_phi = 0; TBranch* b_rMet_type1PF_phi = 0;
  readingtree->SetBranchAddress("Met_type1PF_phi",&rMet_type1PF_phi,&b_rMet_type1PF_phi);
  double rMet_type1PF_px; rMet_type1PF_px = 0; TBranch* b_rMet_type1PF_px = 0;
  readingtree->SetBranchAddress("Met_type1PF_px",&rMet_type1PF_px,&b_rMet_type1PF_px);
  double rMet_type1PF_py; rMet_type1PF_py = 0; TBranch* b_rMet_type1PF_py = 0;
  readingtree->SetBranchAddress("Met_type1PF_py",&rMet_type1PF_py,&b_rMet_type1PF_py);
  //Muons
  //Kinematics:
  vector<double>* rMuon_pt; rMuon_pt = 0; TBranch* b_rMuon_pt = 0; readingtree->SetBranchAddress("Muon_pt",&rMuon_pt,&b_rMuon_pt);
  vector<double>* rMuon_eta; rMuon_eta = 0; TBranch* b_rMuon_eta = 0; readingtree->SetBranchAddress("Muon_eta",&rMuon_eta,&b_rMuon_eta);
  vector<double>* rMuon_phi; rMuon_phi = 0; TBranch* b_rMuon_phi = 0; readingtree->SetBranchAddress("Muon_phi",&rMuon_phi,&b_rMuon_phi);
  vector<double>* rMuon_energy; rMuon_energy = 0; TBranch* b_rMuon_energy = 0;
  readingtree->SetBranchAddress("Muon_energy",&rMuon_energy,&b_rMuon_energy);
  vector<double>* rMuon_p; rMuon_p = 0; TBranch* b_rMuon_p = 0; readingtree->SetBranchAddress("Muon_p",&rMuon_p,&b_rMuon_p);
  vector<double>* rMuon_px; rMuon_px = 0; TBranch* b_rMuon_px = 0; readingtree->SetBranchAddress("Muon_px",&rMuon_px,&b_rMuon_px);
  vector<double>* rMuon_py; rMuon_py = 0; TBranch* b_rMuon_py = 0; readingtree->SetBranchAddress("Muon_py",&rMuon_py,&b_rMuon_py);
  vector<double>* rMuon_pz; rMuon_pz = 0; TBranch* b_rMuon_pz = 0; readingtree->SetBranchAddress("Muon_pz",&rMuon_pz,&b_rMuon_pz);
  //Isolation
  vector<double>* rMuon_trackIso; rMuon_trackIso = 0; TBranch* b_rMuon_trackIso = 0;
  readingtree->SetBranchAddress("Muon_trackIso",&rMuon_trackIso,&b_rMuon_trackIso);
  vector<double>* rMuon_TrackerIso; rMuon_TrackerIso = 0; TBranch* b_rMuon_TrackerIso = 0;
  readingtree->SetBranchAddress("Muon_TrackerIso",&rMuon_TrackerIso,&b_rMuon_TrackerIso);
  vector<double>* rMuon_relIsoDeltaBetaR03; rMuon_relIsoDeltaBetaR03 = 0; TBranch* b_rMuon_relIsoDeltaBetaR03 = 0;
  readingtree->SetBranchAddress("Muon_relIsoDeltaBetaR03",&rMuon_relIsoDeltaBetaR03,&b_rMuon_relIsoDeltaBetaR03);
  vector<double>* rMuon_relIsoDeltaBetaR04; rMuon_relIsoDeltaBetaR04 = 0; TBranch* b_rMuon_relIsoDeltaBetaR04 = 0;
  readingtree->SetBranchAddress("Muon_relIsoDeltaBetaR04",&rMuon_relIsoDeltaBetaR04,&b_rMuon_relIsoDeltaBetaR04);
  //Charge:
  vector<double>* rMuon_charge; rMuon_charge = 0; TBranch* b_rMuon_charge = 0;
  readingtree->SetBranchAddress("Muon_charge",&rMuon_charge,&b_rMuon_charge);
  //ID Selection:
  vector<int>* rMuon_soft; rMuon_soft = 0; TBranch* b_rMuon_soft = 0;
  readingtree->SetBranchAddress("Muon_soft",&rMuon_soft,&b_rMuon_soft);
  vector<int>* rMuon_loose; rMuon_loose = 0; TBranch* b_rMuon_loose = 0;
  readingtree->SetBranchAddress("Muon_loose",&rMuon_loose,&b_rMuon_loose);
  vector<int>* rMuon_medium; rMuon_medium = 0; TBranch* b_rMuon_medium = 0;
  readingtree->SetBranchAddress("Muon_medium",&rMuon_medium,&b_rMuon_medium);
  vector<int>* rMuon_tight; rMuon_tight = 0; TBranch* b_rMuon_tight = 0;
  readingtree->SetBranchAddress("Muon_tight",&rMuon_tight,&b_rMuon_tight);
  vector<int>* rMuon_isHighPt; rMuon_isHighPt = 0; TBranch* b_rMuon_isHighPt = 0;
  readingtree->SetBranchAddress("Muon_isHighPt",&rMuon_isHighPt,&b_rMuon_isHighPt);
  vector<double>* rMuon_validHitsInner; rMuon_validHitsInner = 0; TBranch* b_rMuon_validHitsInner = 0; readingtree->SetBranchAddress("Muon_validHitsInner",&rMuon_validHitsInner,&b_rMuon_validHitsInner);
  vector<double>* rMuon_TLayers; rMuon_TLayers = 0; TBranch* b_rMuon_TLayers = 0; readingtree->SetBranchAddress("Muon_TLayers",&rMuon_TLayers,&b_rMuon_TLayers);
  vector<double>* rMuon_dz_pv; rMuon_dz_pv = 0; TBranch* b_rMuon_dz_pv = 0; readingtree->SetBranchAddress("Muon_dz_pv",&rMuon_dz_pv,&b_rMuon_dz_pv);
  vector<double>* rMuon_dxy_pv; rMuon_dxy_pv = 0; TBranch* b_rMuon_dxy_pv = 0; readingtree->SetBranchAddress("Muon_dxy_pv",&rMuon_dxy_pv,&b_rMuon_dxy_pv);
  vector<int>* rMuon_isGlobal; rMuon_isGlobal = 0; TBranch* b_rMuon_isGlobal = 0;
  readingtree->SetBranchAddress("Muon_isGlobal",&rMuon_isGlobal,&b_rMuon_isGlobal);
  vector<int>* rMuon_isTrackerMuon; rMuon_isTrackerMuon = 0; TBranch* b_rMuon_isTrackerMuon = 0;
  readingtree->SetBranchAddress("Muon_isTrackerMuon",&rMuon_isTrackerMuon,&b_rMuon_isTrackerMuon);
  //Electrons
  //Kinematics:
    vector<double>* rpatElectron_pt; rpatElectron_pt = 0; TBranch* b_rpatElectron_pt = 0; readingtree->SetBranchAddress("patElectron_pt",&rpatElectron_pt,&b_rpatElectron_pt);
  vector<double>* rpatElectron_eta; rpatElectron_eta = 0; TBranch* b_rpatElectron_eta = 0; readingtree->SetBranchAddress("patElectron_eta",&rpatElectron_eta,&b_rpatElectron_eta);
  vector<double>* rpatElectron_phi; rpatElectron_phi = 0; TBranch* b_rpatElectron_phi = 0; readingtree->SetBranchAddress("patElectron_phi",&rpatElectron_phi,&b_rpatElectron_phi);
  vector<int>* rpatElectron_p; rpatElectron_p = 0; TBranch* b_rpatElectron_p = 0; readingtree->SetBranchAddress("patElectron_p",&rpatElectron_p,&b_rpatElectron_p);
  vector<int>* rpatElectron_px; rpatElectron_px = 0; TBranch* b_rpatElectron_px = 0; readingtree->SetBranchAddress("patElectron_px",&rpatElectron_px,&b_rpatElectron_px);
  vector<int>* rpatElectron_py; rpatElectron_py = 0; TBranch* b_rpatElectron_py = 0; readingtree->SetBranchAddress("patElectron_py",&rpatElectron_py,&b_rpatElectron_py);
  vector<int>* rpatElectron_pz; rpatElectron_pz = 0; TBranch* b_rpatElectron_pz = 0; readingtree->SetBranchAddress("patElectron_pz",&rpatElectron_pz,&b_rpatElectron_pz);
  vector<double>* rpatElectron_energy; rpatElectron_energy = 0; TBranch* b_rpatElectron_energy = 0; readingtree->SetBranchAddress("patElectron_energy",&rpatElectron_energy,&b_rpatElectron_energy);
  //Charge:
  vector<int>* rpatElectron_charge; rpatElectron_charge = 0; TBranch* b_rpatElectron_charge = 0; readingtree->SetBranchAddress("patElectron_charge",&rpatElectron_charge,&b_rpatElectron_charge);
  //ID selection:
  vector<int>* rpatElectron_isPassVeto; rpatElectron_isPassVeto = 0; TBranch* b_rpatElectron_isPassVeto = 0; readingtree->SetBranchAddress("patElectron_isPassVeto",&rpatElectron_isPassVeto,&b_rpatElectron_isPassVeto);
  vector<int>* rpatElectron_isPassLoose; rpatElectron_isPassLoose = 0; TBranch* b_rpatElectron_isPassLoose = 0; readingtree->SetBranchAddress("patElectron_isPassLoose",&rpatElectron_isPassLoose,&b_rpatElectron_isPassLoose);
  vector<int>* rpatElectron_isPassMedium; rpatElectron_isPassMedium = 0; TBranch* b_rpatElectron_isPassMedium = 0; readingtree->SetBranchAddress("patElectron_isPassMedium",&rpatElectron_isPassMedium,&b_rpatElectron_isPassMedium);
  vector<int>* rpatElectron_isPassTight; rpatElectron_isPassTight = 0; TBranch* b_rpatElectron_isPassTight = 0; readingtree->SetBranchAddress("patElectron_isPassTight",&rpatElectron_isPassTight,&b_rpatElectron_isPassTight);
  vector<int>* rpatElectron_isPassHEEPId; rpatElectron_isPassHEEPId = 0; TBranch* b_rpatElectron_isPassHEEPId = 0; readingtree->SetBranchAddress("patElectron_isPassHEEPId",&rpatElectron_isPassHEEPId,&b_rpatElectron_isPassHEEPId);
  vector<int>* rpatElectron_isPassMvatrig; rpatElectron_isPassMvatrig = 0; TBranch* b_rpatElectron_isPassMvatrig = 0; readingtree->SetBranchAddress("patElectron_isPassMvatrig",&rpatElectron_isPassMvatrig,&b_rpatElectron_isPassMvatrig);


  vector<double>* rpatElectron_Et; rpatElectron_Et = 0; TBranch* b_rpatElectron_Et = 0; readingtree->SetBranchAddress("patElectron_Et",&rpatElectron_Et,&b_rpatElectron_Et);
  vector<double>* rpatElectron_SCeta; rpatElectron_SCeta = 0; TBranch* b_rpatElectron_SCeta = 0; readingtree->SetBranchAddress("patElectron_SCeta",&rpatElectron_SCeta,&b_rpatElectron_SCeta);
  vector<double>* rpatElectron_isEcalDriven; rpatElectron_isEcalDriven = 0; TBranch* b_rpatElectron_isEcalDriven = 0; readingtree->SetBranchAddress("patElectron_isEcalDriven",&rpatElectron_isEcalDriven,&b_rpatElectron_isEcalDriven);
  vector<double>* rpatElectron_dEtaIn; rpatElectron_dEtaIn = 0; TBranch* b_rpatElectron_dEtaIn = 0; readingtree->SetBranchAddress("patElectron_dEtaIn",&rpatElectron_dEtaIn,&b_rpatElectron_dEtaIn);
  vector<double>* rpatElectron_dPhiIn; rpatElectron_dPhiIn = 0; TBranch* b_rpatElectron_dPhiIn = 0; readingtree->SetBranchAddress("patElectron_dPhiIn",&rpatElectron_dPhiIn,&b_rpatElectron_dPhiIn);
  vector<double>* rpatElectron_hOverE; rpatElectron_hOverE = 0; TBranch* b_rpatElectron_hOverE = 0; readingtree->SetBranchAddress("patElectron_hOverE",&rpatElectron_hOverE,&b_rpatElectron_hOverE);
  vector<double>* rpatElectron_full5x5_sigmaIetaIeta; rpatElectron_full5x5_sigmaIetaIeta = 0; TBranch* b_rpatElectron_full5x5_sigmaIetaIeta = 0; readingtree->SetBranchAddress("patElectron_full5x5_sigmaIetaIeta",&rpatElectron_full5x5_sigmaIetaIeta,&b_rpatElectron_full5x5_sigmaIetaIeta);
  vector<double>* rpatElectron_full5x5_e2x5Max; rpatElectron_full5x5_e2x5Max = 0; TBranch* b_rpatElectron_full5x5_e2x5Max = 0; readingtree->SetBranchAddress("patElectron_full5x5_e2x5Max",&rpatElectron_full5x5_e2x5Max,&b_rpatElectron_full5x5_e2x5Max);
  vector<double>* rpatElectron_full5x5_e5x5; rpatElectron_full5x5_e5x5 = 0; TBranch* b_rpatElectron_full5x5_e5x5 = 0; readingtree->SetBranchAddress("patElectron_full5x5_e5x5",&rpatElectron_full5x5_e5x5,&b_rpatElectron_full5x5_e5x5);
  vector<double>* rpatElectron_full5x5_e1x5; rpatElectron_full5x5_e1x5 = 0; TBranch* b_rpatElectron_full5x5_e1x5 = 0; readingtree->SetBranchAddress("patElectron_full5x5_e1x5",&rpatElectron_full5x5_e1x5,&b_rpatElectron_full5x5_e1x5);
  vector<double>* rpatElectron_dr03EcalRecHitSumEt; rpatElectron_dr03EcalRecHitSumEt = 0; TBranch* b_rpatElectron_dr03EcalRecHitSumEt = 0; readingtree->SetBranchAddress("patElectron_dr03EcalRecHitSumEt",&rpatElectron_dr03EcalRecHitSumEt,&b_rpatElectron_dr03EcalRecHitSumEt);
  vector<double>* rpatElectron_dr03HcalDepth1TowerSumEt; rpatElectron_dr03HcalDepth1TowerSumEt = 0; TBranch* b_rpatElectron_dr03HcalDepth1TowerSumEt = 0; readingtree->SetBranchAddress("patElectron_dr03HcalDepth1TowerSumEt",&rpatElectron_dr03HcalDepth1TowerSumEt,&b_rpatElectron_dr03HcalDepth1TowerSumEt);
  vector<double>* rpatElectron_isolPtTracks; rpatElectron_isolPtTracks = 0; TBranch* b_rpatElectron_isolPtTracks = 0; readingtree->SetBranchAddress("patElectron_isolPtTracks",&rpatElectron_isolPtTracks,&b_rpatElectron_isolPtTracks);
  vector<double>* rpatElectron_expectedMissingInnerHits; rpatElectron_expectedMissingInnerHits = 0; TBranch* b_rpatElectron_expectedMissingInnerHits = 0; readingtree->SetBranchAddress("patElectron_expectedMissingInnerHits",&rpatElectron_expectedMissingInnerHits,&b_rpatElectron_expectedMissingInnerHits);
  vector<double>* rpatElectron_gsfTrack_dxy_pv; rpatElectron_gsfTrack_dxy_pv = 0; TBranch* b_rpatElectron_gsfTrack_dxy_pv = 0; readingtree->SetBranchAddress("patElectron_gsfTrack_dxy_pv",&rpatElectron_gsfTrack_dxy_pv,&b_rpatElectron_gsfTrack_dxy_pv);
  vector<double>* rpatElectron_d0; rpatElectron_d0 = 0; TBranch* b_rpatElectron_d0 = 0; readingtree->SetBranchAddress("patElectron_d0",&rpatElectron_d0,&b_rpatElectron_d0);
  vector<double>* rpatElectron_ecalPFClusterIso; rpatElectron_ecalPFClusterIso = 0; TBranch* b_rpatElectron_ecalPFClusterIso = 0; readingtree->SetBranchAddress("patElectron_ecalPFClusterIso",&rpatElectron_ecalPFClusterIso,&b_rpatElectron_ecalPFClusterIso);
  vector<double>* rpatElectron_hcalPFClusterIso; rpatElectron_hcalPFClusterIso = 0; TBranch* b_rpatElectron_hcalPFClusterIso = 0; readingtree->SetBranchAddress("patElectron_hcalPFClusterIso",&rpatElectron_hcalPFClusterIso,&b_rpatElectron_hcalPFClusterIso);
  //Jets
  //Kinematics:
  vector<double>* rJet_pt; rJet_pt = 0; TBranch* b_rJet_pt = 0; readingtree->SetBranchAddress("Jet_pt",&rJet_pt,&b_rJet_pt);
  vector<double>* rJet_eta; rJet_eta = 0; TBranch* b_rJet_eta = 0; readingtree->SetBranchAddress("Jet_eta",&rJet_eta,&b_rJet_eta);
  vector<double>* rJet_phi; rJet_phi = 0; TBranch* b_rJet_phi = 0; readingtree->SetBranchAddress("Jet_phi",&rJet_phi,&b_rJet_phi);
  vector<double>* rJet_energy; rJet_energy = 0; TBranch* b_rJet_energy = 0;
  readingtree->SetBranchAddress("Jet_energy",&rJet_energy,&b_rJet_energy);
  vector<double>* rJet_px; rJet_px = 0; TBranch* b_rJet_px = 0; readingtree->SetBranchAddress("Jet_px",&rJet_px,&b_rJet_px);
  vector<double>* rJet_py; rJet_py = 0; TBranch* b_rJet_py = 0; readingtree->SetBranchAddress("Jet_py",&rJet_py,&b_rJet_py);
  vector<double>* rJet_pz; rJet_pz = 0; TBranch* b_rJet_pz = 0; readingtree->SetBranchAddress("Jet_pz",&rJet_pz,&b_rJet_pz);
  vector<double>* rJet_mass; rJet_mass = 0; TBranch* b_rJet_mass = 0; readingtree->SetBranchAddress("Jet_mass",&rJet_mass,&b_rJet_mass);
  //ID selection:
  vector<double>* rJet_neutralHadEnergyFraction; rJet_neutralHadEnergyFraction = 0; TBranch* b_rJet_neutralHadEnergyFraction = 0;
  readingtree->SetBranchAddress("Jet_neutralHadEnergyFraction",&rJet_neutralHadEnergyFraction,&b_rJet_neutralHadEnergyFraction);
  vector<double>* rJet_neutralEmEnergyFraction; rJet_neutralEmEnergyFraction = 0; TBranch* b_rJet_neutralEmEnergyFraction = 0;
  readingtree->SetBranchAddress("Jet_neutralEmEnergyFraction",&rJet_neutralEmEnergyFraction,&b_rJet_neutralEmEnergyFraction);
  vector<int>* rJet_chargedMultiplicity; rJet_chargedMultiplicity = 0; TBranch* b_rJet_chargedMultiplicity = 0;
  readingtree->SetBranchAddress("Jet_chargedMultiplicity",&rJet_chargedMultiplicity,&b_rJet_chargedMultiplicity);
  vector<double>* rJet_muonEnergyFraction; rJet_muonEnergyFraction = 0; TBranch* b_rJet_muonEnergyFraction = 0;
  readingtree->SetBranchAddress("Jet_muonEnergyFraction",&rJet_muonEnergyFraction,&b_rJet_muonEnergyFraction);
  vector<double>* rJet_chargedHadronEnergyFraction; rJet_chargedHadronEnergyFraction = 0; TBranch* b_rJet_chargedHadronEnergyFraction = 0;
  readingtree->SetBranchAddress("Jet_chargedHadronEnergyFraction",&rJet_chargedHadronEnergyFraction,&b_rJet_chargedHadronEnergyFraction);
  vector<double>* rJet_chargedEmEnergyFraction; rJet_chargedEmEnergyFraction = 0; TBranch* b_rJet_chargedEmEnergyFraction = 0;
  readingtree->SetBranchAddress("Jet_chargedEmEnergyFraction",&rJet_chargedEmEnergyFraction,&b_rJet_chargedEmEnergyFraction);
  vector<double>* rJet_numberOfConstituents; rJet_numberOfConstituents = 0; TBranch* b_rJet_numberOfConstituents = 0;
  readingtree->SetBranchAddress("Jet_numberOfConstituents",&rJet_numberOfConstituents,&b_rJet_numberOfConstituents);
  //Corrections: 
  vector<double>* rJet_Uncorr_pt; rJet_Uncorr_pt = 0; TBranch* b_rJet_Uncorr_pt = 0; readingtree->SetBranchAddress("Jet_Uncorr_pt",&rJet_Uncorr_pt,&b_rJet_Uncorr_pt);
  vector<double>* rJet_JesSF; rJet_JesSF = 0; TBranch* b_rJet_JesSF = 0; readingtree->SetBranchAddress("Jet_JesSF",&rJet_JesSF,&b_rJet_JesSF);
  vector<double>* rJet_JerSF; rJet_JerSF = 0; TBranch* b_rJet_JerSF = 0; readingtree->SetBranchAddress("Jet_JerSF",&rJet_JerSF,&b_rJet_JerSF);
  //b-tagging:
  vector<double>* rJet_pfCombinedInclusiveSecondaryVertexV2BJetTags; rJet_pfCombinedInclusiveSecondaryVertexV2BJetTags = 0;
  TBranch* b_rJet_pfCombinedInclusiveSecondaryVertexV2BJetTags = 0;readingtree->SetBranchAddress("Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags",&rJet_pfCombinedInclusiveSecondaryVertexV2BJetTags,&b_rJet_pfCombinedInclusiveSecondaryVertexV2BJetTags); 
  vector<double>* rJet_pfCombinedMVAV2BJetTags; rJet_pfCombinedMVAV2BJetTags = 0;
  TBranch* b_rJet_pfCombinedMVAV2BJetTags = 0;readingtree->SetBranchAddress("Jet_pfCombinedMVAV2BJetTags",&rJet_pfCombinedMVAV2BJetTags,&b_rJet_pfCombinedMVAV2BJetTags);
  //Boosted Jets
  //Kinematics:
  vector<double>* rBoostedJet_pt; rBoostedJet_pt = 0; TBranch* b_rBoostedJet_pt = 0; 
  readingtree->SetBranchAddress("BoostedJet_pt",&rBoostedJet_pt,&b_rBoostedJet_pt);
  vector<double>* rBoostedJet_eta; rBoostedJet_eta = 0; TBranch* b_rBoostedJet_eta = 0; 
  readingtree->SetBranchAddress("BoostedJet_eta",&rBoostedJet_eta,&b_rBoostedJet_eta);
  vector<double>* rBoostedJet_phi; rBoostedJet_phi = 0; TBranch* b_rBoostedJet_phi = 0; 
  readingtree->SetBranchAddress("BoostedJet_phi",&rBoostedJet_phi,&b_rBoostedJet_phi);
  vector<double>* rBoostedJet_energy; rBoostedJet_energy = 0; TBranch* b_rBoostedJet_energy = 0; 
  readingtree->SetBranchAddress("BoostedJet_energy",&rBoostedJet_energy,&b_rBoostedJet_energy);
  vector<double>* rBoostedJet_mass; rBoostedJet_mass = 0; TBranch* b_rBoostedJet_mass = 0;
  readingtree->SetBranchAddress("BoostedJet_mass",&rBoostedJet_mass,&b_rBoostedJet_mass); 
  //ID selection:
  vector<double>* rBoostedJet_neutralHadEnergyFraction; rBoostedJet_neutralHadEnergyFraction = 0; TBranch* b_rBoostedJet_neutralHadEnergyFraction = 0; readingtree->SetBranchAddress("BoostedJet_neutralHadEnergyFraction",&rBoostedJet_neutralHadEnergyFraction,&b_rBoostedJet_neutralHadEnergyFraction);
  vector<double>* rBoostedJet_neutralEmEmEnergyFraction; rBoostedJet_neutralEmEmEnergyFraction = 0; TBranch* b_rBoostedJet_neutralEmEmEnergyFraction = 0; readingtree->SetBranchAddress("BoostedJet_neutralEmEmEnergyFraction",&rBoostedJet_neutralEmEmEnergyFraction,&b_rBoostedJet_neutralEmEmEnergyFraction);
  vector<double>* rBoostedJet_chargedHadronEnergyFraction; rBoostedJet_chargedHadronEnergyFraction = 0; TBranch* b_rBoostedJet_chargedHadronEnergyFraction = 0; readingtree->SetBranchAddress("BoostedJet_chargedHadronEnergyFraction",&rBoostedJet_chargedHadronEnergyFraction,&b_rBoostedJet_chargedHadronEnergyFraction);
  vector<double>* rBoostedJet_chargedEmEnergyFraction; rBoostedJet_chargedEmEnergyFraction = 0; TBranch* b_rBoostedJet_chargedEmEnergyFraction = 0; readingtree->SetBranchAddress("BoostedJet_chargedEmEnergyFraction",&rBoostedJet_chargedEmEnergyFraction,&b_rBoostedJet_chargedEmEnergyFraction);
  vector<double>* rBoostedJet_muonEnergyFraction; rBoostedJet_muonEnergyFraction = 0; TBranch* b_rBoostedJet_muonEnergyFraction = 0; readingtree->SetBranchAddress("BoostedJet_muonEnergyFraction",&rBoostedJet_muonEnergyFraction,&b_rBoostedJet_muonEnergyFraction);
  vector<double>* rBoostedJet_electronEnergy; rBoostedJet_electronEnergy = 0; TBranch* b_rBoostedJet_electronEnergy = 0; readingtree->SetBranchAddress("BoostedJet_electronEnergy",&rBoostedJet_electronEnergy,&b_rBoostedJet_electronEnergy);
  vector<double>* rBoostedJet_photonEnergy; rBoostedJet_photonEnergy = 0; TBranch* b_rBoostedJet_photonEnergy = 0; readingtree->SetBranchAddress("BoostedJet_photonEnergy",&rBoostedJet_photonEnergy,&b_rBoostedJet_photonEnergy);
  vector<double>* rBoostedJet_numberOfConstituents; rBoostedJet_numberOfConstituents = 0; TBranch* b_rBoostedJet_numberOfConstituents = 0; readingtree->SetBranchAddress("BoostedJet_numberOfConstituents",&rBoostedJet_numberOfConstituents,&b_rBoostedJet_numberOfConstituents);
  vector<double>* rBoostedJet_chargedMultiplicity; rBoostedJet_chargedMultiplicity = 0; TBranch* b_rBoostedJet_chargedMultiplicity = 0; readingtree->SetBranchAddress("BoostedJet_chargedMultiplicity",&rBoostedJet_chargedMultiplicity,&b_rBoostedJet_chargedMultiplicity);
  //Corrections:
  vector<double>* rBoostedJet_Uncorr_pt; rBoostedJet_Uncorr_pt = 0; TBranch* b_rBoostedJet_Uncorr_pt = 0; readingtree->SetBranchAddress("BoostedJet_Uncorr_pt",&rBoostedJet_Uncorr_pt,&b_rBoostedJet_Uncorr_pt);
  vector<double>* rBoostedJet_JesSF; rBoostedJet_JesSF = 0; TBranch* b_rBoostedJet_JesSF = 0; readingtree->SetBranchAddress("BoostedJet_JesSF",&rBoostedJet_JesSF,&b_rBoostedJet_JesSF);
  //b-tagging: 
  vector<double>* rBoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags; rBoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags = 0;
  TBranch* b_rBoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags = 0;readingtree->SetBranchAddress("BoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags",&rBoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags,&b_rBoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags); 
 

//other variables
  double rEVENT_rhopog; rEVENT_rhopog = 0; TBranch* b_rEVENT_rhopog = 0; readingtree->SetBranchAddress("EVENT_rhopog",&rEVENT_rhopog,&b_rEVENT_rhopog);
  ULong64_t rEVENT_event; rEVENT_event = 0; TBranch* b_rEVENT_event = 0; readingtree->SetBranchAddress("EVENT_event",&rEVENT_event,&b_rEVENT_event);



   
   TFile *newfile = new TFile(Output,"recreate");
   TTree* newtree = new TTree("BOOM","BOOM");
   newtree->SetMaxTreeSize(99000000000);
   /////
   //   New variables
   /////
   //Trigger:
  int HLT_Ele27_eta2p1_WPLoose_Gsf; newtree->Branch("HLT_Ele27_eta2p1_WPLoose_Gsf",&HLT_Ele27_eta2p1_WPLoose_Gsf);
  //int HLT_DoubleEle33_CaloIdL_GsfTrkIdVL; newtree->Branch("HLT_DoubleEle33_CaloIdL_GsfTrkIdVL",&HLT_DoubleEle33_CaloIdL_GsfTrkIdVL);
  int HLT_Ele115_CaloIdVT_GsfTrkIdT; newtree->Branch("HLT_Ele115_CaloIdVT_GsfTrkIdT",&HLT_Ele115_CaloIdVT_GsfTrkIdT);
   int HLT_Mu50; newtree->Branch("HLT_Mu50",&HLT_Mu50);
   int HLT_TkMu50; newtree->Branch("HLT_TkMu50",&HLT_TkMu50);
   int HLT_OldMu100; newtree->Branch("HLT_OldMu100",&HLT_OldMu100);
   int HLT_TkMu100; newtree->Branch("HLT_TkMu100",&HLT_TkMu100);

   //Muons:
   vector<double>* Muon_pt = new std::vector<double>; newtree->Branch("Muon_pt",&Muon_pt);
   vector<double>* Muon_eta = new std::vector<double>; newtree->Branch("Muon_eta",&Muon_eta);
   vector<double>* Muon_phi = new std::vector<double>; newtree->Branch("Muon_phi",&Muon_phi);
   vector<double>* Muon_p = new std::vector<double>; newtree->Branch("Muon_p",&Muon_p);
   vector<double>* Muon_px = new std::vector<double>; newtree->Branch("Muon_px",&Muon_px);
   vector<double>* Muon_py = new std::vector<double>; newtree->Branch("Muon_py",&Muon_py);
   vector<double>* Muon_pz = new std::vector<double>; newtree->Branch("Muon_pz",&Muon_pz);
   vector<double>* Muon_energy = new std::vector<double>; newtree->Branch("Muon_energy",&Muon_energy);
   vector<double>* Muon_charge = new std::vector<double>; newtree->Branch("Muon_charge",&Muon_charge);
   vector<double>* Muon_trackIso = new std::vector<double>; newtree->Branch("Muon_trackIso",&Muon_trackIso);
   vector<double>* Muon_TrackerIso = new std::vector<double>; newtree->Branch("Muon_TrackerIso",&Muon_TrackerIso);
   vector<double>* Muon_relIsoDeltaBetaR03 = new std::vector<double>; newtree->Branch("Muon_relIsoDeltaBetaR03",&Muon_relIsoDeltaBetaR03);
   vector<double>* Muon_relIsoDeltaBetaR04 = new std::vector<double>; newtree->Branch("Muon_relIsoDeltaBetaR04",&Muon_relIsoDeltaBetaR04);
   vector<double>* Muon_isHighPt = new std::vector<double>; newtree->Branch("Muon_isHighPt",&Muon_isHighPt);
   vector<int>* Muon_loose = new std::vector<int>; newtree->Branch("Muon_loose",&Muon_loose);
   vector<int>* Muon_medium = new std::vector<int>; newtree->Branch("Muon_medium",&Muon_medium);
   vector<int>* Muon_tight = new std::vector<int>; newtree->Branch("Muon_tight",&Muon_tight);
  vector<double>* Muon_validHitsInner = new std::vector<double>; newtree->Branch("Muon_validHitsInner",&Muon_validHitsInner);
  vector<double>* Muon_TLayers = new std::vector<double>; newtree->Branch("Muon_TLayers",&Muon_TLayers);
  vector<double>* Muon_dz_pv = new std::vector<double>; newtree->Branch("Muon_dz_pv",&Muon_dz_pv);
  vector<double>* Muon_dxy_pv = new std::vector<double>; newtree->Branch("Muon_dxy_pv",&Muon_dxy_pv);
   
   //Electrons:
  vector<double>* patElectron_pt = new std::vector<double>; newtree->Branch("patElectron_pt",&patElectron_pt);
  vector<double>* patElectron_eta = new std::vector<double>; newtree->Branch("patElectron_eta",&patElectron_eta);
  vector<double>* patElectron_phi = new std::vector<double>; newtree->Branch("patElectron_phi",&patElectron_phi);
  vector<double>* patElectron_energy = new std::vector<double>; newtree->Branch("patElectron_energy",&patElectron_energy);
  vector<int>* patElectron_p = new std::vector<int>; newtree->Branch("patElectron_p",&patElectron_p);
  vector<int>* patElectron_px = new std::vector<int>; newtree->Branch("patElectron_px",&patElectron_px);
  vector<int>* patElectron_py = new std::vector<int>; newtree->Branch("patElectron_py",&patElectron_py);
  vector<int>* patElectron_pz = new std::vector<int>; newtree->Branch("patElectron_pz",&patElectron_pz);
  vector<int>* patElectron_charge = new std::vector<int>; newtree->Branch("patElectron_charge",&patElectron_charge);
  vector<int>* patElectron_isPassVeto = new std::vector<int>; newtree->Branch("patElectron_isPassVeto",&patElectron_isPassVeto);
  vector<int>* patElectron_isPassLoose = new std::vector<int>; newtree->Branch("patElectron_isPassLoose",&patElectron_isPassLoose);
  vector<int>* patElectron_isPassMedium = new std::vector<int>; newtree->Branch("patElectron_isPassMedium",&patElectron_isPassMedium);
  vector<int>* patElectron_isPassTight = new std::vector<int>; newtree->Branch("patElectron_isPassTight",&patElectron_isPassTight);
  vector<int>* patElectron_isPassHEEPId = new std::vector<int>; newtree->Branch("patElectron_isPassHEEPId",&patElectron_isPassHEEPId);
  vector<int>* patElectron_isPassMvatrig = new std::vector<int>; newtree->Branch("patElectron_isPassMvatrig",&patElectron_isPassMvatrig);
  vector<double>* eleIsHEEPID = new std::vector<double>; newtree->Branch("eleIsHEEPID",&eleIsHEEPID);
  vector<double>* eleIsHEEPnonISO3 = new std::vector<double>; newtree->Branch("eleIsHEEPnonISO3",&eleIsHEEPnonISO3);
  vector<double>* eleIsHEEPnonISO6 = new std::vector<double>; newtree->Branch("eleIsHEEPnonISO6",&eleIsHEEPnonISO6);

  vector<double>* patElectron_Et = new std::vector<double>; newtree->Branch("patElectron_Et",&patElectron_Et);
  vector<double>* patElectron_SCeta = new std::vector<double>; newtree->Branch("patElectron_SCeta",&patElectron_SCeta);
  vector<double>* patElectron_isEcalDriven = new std::vector<double>; newtree->Branch("patElectron_isEcalDriven",&patElectron_isEcalDriven);
  vector<double>* patElectron_dEtaIn = new std::vector<double>; newtree->Branch("patElectron_dEtaIn",&patElectron_dEtaIn);
  vector<double>* patElectron_dPhiIn = new std::vector<double>; newtree->Branch("patElectron_dPhiIn",&patElectron_dPhiIn);
  vector<double>* patElectron_hOverE = new std::vector<double>; newtree->Branch("patElectron_hOverE",&patElectron_hOverE);
  vector<double>* patElectron_full5x5_sigmaIetaIeta = new std::vector<double>; newtree->Branch("patElectron_full5x5_sigmaIetaIeta",&patElectron_full5x5_sigmaIetaIeta);
  vector<double>* patElectron_full5x5_e2x5Max = new std::vector<double>; newtree->Branch("patElectron_full5x5_e2x5Max",&patElectron_full5x5_e2x5Max);
  vector<double>* patElectron_full5x5_e5x5 = new std::vector<double>; newtree->Branch("patElectron_full5x5_e5x5",&patElectron_full5x5_e5x5);
  vector<double>* patElectron_full5x5_e1x5 = new std::vector<double>; newtree->Branch("patElectron_full5x5_e1x5",&patElectron_full5x5_e1x5);
  vector<double>* patElectron_dr03EcalRecHitSumEt = new std::vector<double>; newtree->Branch("patElectron_dr03EcalRecHitSumEt",&patElectron_dr03EcalRecHitSumEt);
  vector<double>* patElectron_dr03HcalDepth1TowerSumEt = new std::vector<double>; newtree->Branch("patElectron_dr03HcalDepth1TowerSumEt",&patElectron_dr03HcalDepth1TowerSumEt);
  vector<double>* patElectron_isolPtTracks = new std::vector<double>; newtree->Branch("patElectron_isolPtTracks",&patElectron_isolPtTracks);
  vector<double>* patElectron_expectedMissingInnerHits = new std::vector<double>; newtree->Branch("patElectron_expectedMissingInnerHits",&patElectron_expectedMissingInnerHits);
  vector<double>* patElectron_gsfTrack_dxy_pv = new std::vector<double>; newtree->Branch("patElectron_gsfTrack_dxy_pv",&patElectron_gsfTrack_dxy_pv);
  vector<double>* patElectron_d0 = new std::vector<double>; newtree->Branch("patElectron_d0",&patElectron_d0);
  vector<double>* patElectron_ecalPFClusterIso = new std::vector<double>; newtree->Branch("patElectron_ecalPFClusterIso",&patElectron_ecalPFClusterIso);
  vector<double>* patElectron_hcalPFClusterIso = new std::vector<double>; newtree->Branch("patElectron_hcalPFClusterIso",&patElectron_hcalPFClusterIso);
  vector<double>* R1_sr = new std::vector<double>; newtree->Branch("R1_sr",&R1_sr);
  vector<double>* R2_sr = new std::vector<double>; newtree->Branch("R2_sr",&R2_sr);
  vector<double>* R1_wgt = new std::vector<double>; newtree->Branch("R1_wgt",&R1_wgt);
  vector<double>* R2_wgt = new std::vector<double>; newtree->Branch("R2_wgt",&R2_wgt);  
  vector<double>* Iso1 = new std::vector<double>; newtree->Branch("Iso1",&Iso1);
  vector<double>* Iso2 = new std::vector<double>; newtree->Branch("Iso2",&Iso2);


   //Jets:
   vector<double>* Jet_pt = new std::vector<double>; newtree->Branch("Jet_pt",&Jet_pt);
   vector<double>* Jet_eta = new std::vector<double>; newtree->Branch("Jet_eta",&Jet_eta);
   vector<double>* Jet_phi = new std::vector<double>; newtree->Branch("Jet_phi",&Jet_phi);
   vector<double>* Jet_px = new std::vector<double>; newtree->Branch("Jet_px",&Jet_px);
   vector<double>* Jet_py = new std::vector<double>; newtree->Branch("Jet_py",&Jet_py);
   vector<double>* Jet_pz = new std::vector<double>; newtree->Branch("Jet_pz",&Jet_pz);
   vector<double>* Jet_energy = new std::vector<double>; newtree->Branch("Jet_energy",&Jet_energy);
   vector<double>* Jet_mass = new std::vector<double>; newtree->Branch("Jet_mass",&Jet_mass);
   vector<double>* Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags = new std::vector<double>; newtree->Branch("Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags",&Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags);
   vector<double>* Jet_pfCombinedMVAV2BJetTags = new std::vector<double>; newtree->Branch("Jet_pfCombinedMVAV2BJetTags",&Jet_pfCombinedMVAV2BJetTags);
   vector<bool>* Jet_M = new std::vector<bool>; newtree->Branch("Jet_M",&Jet_M);
   vector<double>* Jet_nBoostedJets = new std::vector<double>; newtree->Branch("Jet_nBoostedJets",&Jet_nBoostedJets);
   vector<double>* Jet_nBoostedJetsM = new std::vector<double>; newtree->Branch("Jet_nBoostedJetsM",&Jet_nBoostedJetsM);
   vector<double>* Jet_L = new std::vector<double>; newtree->Branch("Jet_L",&Jet_L);
   vector<double>* Jet_T = new std::vector<double>; newtree->Branch("Jet_T",&Jet_T);
   vector<double>* Jet_TLV = new std::vector<double>; newtree->Branch("Jet_TLV",&Jet_TLV);
   
   //Boosted Jets:
   vector<double>* BoostedJet_pt = new std::vector<double>; newtree->Branch("BoostedJet_pt",&BoostedJet_pt);
   vector<double>* BoostedJet_eta = new std::vector<double>; newtree->Branch("BoostedJet_eta",&BoostedJet_eta);
   vector<double>* BoostedJet_phi = new std::vector<double>; newtree->Branch("BoostedJet_phi",&BoostedJet_phi);
   vector<double>* BoostedJet_energy = new std::vector<double>; newtree->Branch("BoostedJet_energy",&BoostedJet_energy);
   vector<double>* BoostedJet_mass = new std::vector<double>; newtree->Branch("BoostedJet_mass",&BoostedJet_mass);
   vector<double>* BoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags = new std::vector<double>; newtree->Branch("BoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags",&BoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags);
   vector<bool>* BoostedJet_M = new std::vector<bool>; newtree->Branch("BoostedJet_M",&BoostedJet_M);
   vector<double>* BoostedJet_nJets = new std::vector<double>; newtree->Branch("BoostedJet_nJets",&BoostedJet_nJets);
   vector<double>* BoostedJet_nJetsM = new std::vector<double>; newtree->Branch("BoostedJet_nJetsM",&BoostedJet_nJetsM);

   vector<double>* BoostedJet_L = new std::vector<double>; newtree->Branch("BoostedJet_L",&BoostedJet_L);
   vector<double>* BoostedJet_T = new std::vector<double>; newtree->Branch("BoostedJet_T",&BoostedJet_T);
   vector<double>* BoostedJet_TLV = new std::vector<double>; newtree->Branch("BoostedJet_TLV",&BoostedJet_TLV);

   
   //PU:
   double PileupWeight; newtree->Branch("PileupWeight",&PileupWeight);
   double PUWeight; newtree->Branch("PUWeight",&PUWeight);
   int nBestVtx; newtree->Branch("nBestVtx",&nBestVtx);
   double trueInteractions; newtree->Branch("trueInteractions",&trueInteractions);
   //Lumi weight
   double lumi_wgt; newtree->Branch("lumi_wgt",&lumi_wgt);
   //Signal region:  
   double Met_type1PF_pt; newtree->Branch("Met_type1PF_pt",&Met_type1PF_pt);
   double Met_type1PF_phi; newtree->Branch("Met_type1PF_phi",&Met_type1PF_phi);
   double Met_type1PF_px; newtree->Branch("Met_type1PF_px",&Met_type1PF_px);
   double Met_type1PF_py; newtree->Branch("Met_type1PF_py",&Met_type1PF_py);
 
   double numOfHighptMu; newtree->Branch("numOfHighptMu",&numOfHighptMu);
   double numOfLooseMu; newtree->Branch("numOfLooseMu",&numOfLooseMu);
   double numOfMediumMu; newtree->Branch("numOfMediumMu",&numOfMediumMu);
   double numOfTightMu; newtree->Branch("numOfTightMu",&numOfTightMu);


   double numOfHighptEle; newtree->Branch("numOfHighptEle",&numOfHighptEle);
   double numOfLooseEle; newtree->Branch("numOfLooseEle",&numOfLooseEle);
   double numOfMediumEle; newtree->Branch("numOfMediumEle",&numOfMediumEle);
   double numOfTightEle; newtree->Branch("numOfTightEle",&numOfTightEle);
   double numOfVetoEle; newtree->Branch("numOfVetoEle",&numOfVetoEle);
   double numOfHEEPEle; newtree->Branch("numOfHEEPEle",&numOfHEEPEle);
   double numOfFakeMu; newtree->Branch("numOfFakeMu",&numOfFakeMu);
   double numOfFakeEle; newtree->Branch("numOfFakeEle",&numOfFakeEle);

   double numOfJets; newtree->Branch("numOfJets",&numOfJets); 
   double numOfJets_L; newtree->Branch("numOfJets_L",&numOfJets_L);
   double numOfJets_T; newtree->Branch("numOfJets_T",&numOfJets_T);
   double numOfJets_TLV; newtree->Branch("numOfJets_TLV",&numOfJets_TLV);
   double numOfBoostedJets; newtree->Branch("numOfBoostedJets",&numOfBoostedJets);
   double numOfBoostedJets_L; newtree->Branch("numOfBoostedJets_L",&numOfBoostedJets_L);
   double numOfBoostedJets_T; newtree->Branch("numOfBoostedJets_T",&numOfBoostedJets_T);
   double numOfBoostedJets_TLV; newtree->Branch("numOfBoostedJets_TLV",&numOfBoostedJets_TLV); 
   double numOfbJetsSV_WPT; newtree->Branch("numOfbJetsSV_WPT",&numOfbJetsSV_WPT);
   double numOfbJetsSV_WPM; newtree->Branch("numOfbJetsSV_WPM",&numOfbJetsSV_WPM);
   double numOfbJetsSV_WPL; newtree->Branch("numOfbJetsSV_WPL",&numOfbJetsSV_WPL);
   double numOfbJetsMVA_WPT; newtree->Branch("numOfbJetsMVA_WPT",&numOfbJetsMVA_WPT);
   double numOfbJetsMVA_WPM; newtree->Branch("numOfbJetsMVA_WPM",&numOfbJetsMVA_WPM);
   double numOfbJetsMVA_WPL; newtree->Branch("numOfbJetsMVA_WPL",&numOfbJetsMVA_WPL);
   
   double IsoTrack_L; newtree->Branch("IsoTrack_L",&IsoTrack_L); 
   double IsoTrack_T; newtree->Branch("IsoTrack_T",&IsoTrack_T);
   double IsoTracker_L; newtree->Branch("IsoTracker_L",&IsoTracker_L); 
   double IsoTracker_T; newtree->Branch("IsoTracker_T",&IsoTracker_T); 
   double IsoPF_L; newtree->Branch("IsoPF_L",&IsoPF_L); 
   double IsoPF_T; newtree->Branch("IsoPF_T",&IsoPF_T); 
   //Ele1 kinematics:
   double Ele1_pt; newtree->Branch("Ele1_pt",&Ele1_pt);
   double Ele1_eta; newtree->Branch("Ele1_eta",&Ele1_eta);
   double Ele1_phi; newtree->Branch("Ele1_phi",&Ele1_phi);
   double Ele1_energy; newtree->Branch("Ele1_energy",&Ele1_energy);
   double Ele1_p; newtree->Branch("Ele1_p",&Ele1_p);
   double Ele1_px; newtree->Branch("Ele1_px",&Ele1_px);
   double Ele1_py; newtree->Branch("Ele1_py",&Ele1_py);
   double Ele1_pz; newtree->Branch("Ele1_pz",&Ele1_pz);
   //Ele2 Kinematics:
   double Ele2_pt; newtree->Branch("Ele2_pt",&Ele2_pt);
   double Ele2_eta; newtree->Branch("Ele2_eta",&Ele2_eta);
   double Ele2_phi; newtree->Branch("Ele2_phi",&Ele2_phi);
   double Ele2_energy; newtree->Branch("Ele2_energy",&Ele2_energy);
   double Ele2_p; newtree->Branch("Ele2_p",&Ele2_p);
   double Ele2_px; newtree->Branch("Ele2_px",&Ele2_px);
   double Ele2_py; newtree->Branch("Ele2_py",&Ele2_py);
   double Ele2_pz; newtree->Branch("Ele2_pz",&Ele2_pz);
   //Muon1 Kinematics:
   double Muon1_pt; newtree->Branch("Muon1_pt",&Muon1_pt);
   double Muon1_eta; newtree->Branch("Muon1_eta",&Muon1_eta);
   double Muon1_phi; newtree->Branch("Muon1_phi",&Muon1_phi);
   double Muon1_energy; newtree->Branch("Muon1_energy",&Muon1_energy);
   double Muon1_p; newtree->Branch("Muon1_p",&Muon1_p);
   double Muon1_px; newtree->Branch("Muon1_px",&Muon1_px);
   double Muon1_py; newtree->Branch("Muon1_py",&Muon1_py);
   double Muon1_pz; newtree->Branch("Muon1_pz",&Muon1_pz);  
   //Muon2 Kinematics:
   double Muon2_pt; newtree->Branch("Muon2_pt",&Muon2_pt);
   double Muon2_eta; newtree->Branch("Muon2_eta",&Muon2_eta);
   double Muon2_phi; newtree->Branch("Muon2_phi",&Muon2_phi);
   double Muon2_energy; newtree->Branch("Muon2_energy",&Muon2_energy);
   double Muon2_p; newtree->Branch("Muon2_p",&Muon2_p);
   double Muon2_px; newtree->Branch("Muon2_px",&Muon2_px);
   double Muon2_py; newtree->Branch("Muon2_py",&Muon2_py);
   double Muon2_pz; newtree->Branch("Muon2_pz",&Muon2_pz);    
   //Boosted Jet1 kinematics:
   double BoostedJet1_pt; newtree->Branch("BoostedJet1_pt",&BoostedJet1_pt);
   double BoostedJet1_eta; newtree->Branch("BoostedJet1_eta",&BoostedJet1_eta);
   double BoostedJet1_phi; newtree->Branch("BoostedJet1_phi",&BoostedJet1_phi);
   double BoostedJet1_energy; newtree->Branch("BoostedJet1_energy",&BoostedJet1_energy);
   double BoostedJet1_nJets; newtree->Branch("BoostedJet1_nJets",&BoostedJet1_nJets);
   //Masses:
   double M_ele1ele2Bjet1; newtree->Branch("M_ele1ele2Bjet1",&M_ele1ele2Bjet1);  
   double M_ele1ele2; newtree->Branch("M_ele1ele2",&M_ele1ele2);
   double M_elemu; newtree->Branch("M_elemu",&M_elemu);
   double M_elemuBjet1; newtree->Branch("M_elemuBjet1",&M_elemuBjet1);
   double M_mu1mu2; newtree->Branch("M_mu1mu2",&M_mu1mu2);
   double M_mu1mu2Bjet1; newtree->Branch("M_mu1mu2Bjet1",&M_mu1mu2Bjet1); 
   double M_leplepBjet1; newtree->Branch("M_leplepBjet1",&M_leplepBjet1);  
   double S_T_BJ; newtree->Branch("S_T_BJ",&S_T_BJ);
   double S_T_jj; newtree->Branch("S_T_jj",&S_T_jj);
   double M_leplep; newtree->Branch("M_leplep",&M_leplep);
   double M_leplepBjet; newtree->Branch("M_leplepBjet",&M_leplepBjet);  

   //Scale Factor
   double elesf_ele1; newtree->Branch("elesf_ele1",&elesf_ele1);
   double elesf_ele2; newtree->Branch("elesf_ele2",&elesf_ele2);
   double musf_trigger_mu1; newtree->Branch("musf_trigger_mu1",&musf_trigger_mu1);
   double musf_ID_mu1; newtree->Branch("musf_ID_mu1",&musf_ID_mu1);
   double musf_iso_mu1; newtree->Branch("musf_iso_mu1",&musf_iso_mu1);
   double musf_tot_mu1; newtree->Branch("musf_tot_mu1",&musf_tot_mu1);
   double musf_trigger_mu2; newtree->Branch("musf_trigger_mu2",&musf_trigger_mu2);
   double musf_ID_mu2; newtree->Branch("musf_ID_mu2",&musf_ID_mu2);
   double musf_iso_mu2; newtree->Branch("musf_iso_mu2",&musf_iso_mu2);
   double musf_tot_mu2; newtree->Branch("musf_tot_mu2",&musf_tot_mu2);
   double lepsf_evt; newtree->Branch("lepsf_evt",&lepsf_evt);
   double QCD_wgt_mu1; newtree->Branch("QCD_wgt_mu1",&QCD_wgt_mu1);
   double QCD_wgt_mu2; newtree->Branch("QCD_wgt_mu2",&QCD_wgt_mu2);
   double QCD_wgt_ele1; newtree->Branch("QCD_wgt_ele1",&QCD_wgt_ele1);
   double QCD_wgt_ele2; newtree->Branch("QCD_wgt_ele2",&QCD_wgt_ele2);
   double QCD_wgt_evt; newtree->Branch("QCD_wgt_evt",&QCD_wgt_evt);
   //Event type
   //int evt_type; newtree->Branch("evt_type",&evt_type);
   double eejj_l; newtree->Branch("eejj_l",&eejj_l);
   double emujj_l; newtree->Branch("emujj_l",&emujj_l);
   double mumujj_l; newtree->Branch("mumujj_l",&mumujj_l);
   double muejj_l; newtree->Branch("muejj_l",&muejj_l);
   double evtype3; newtree->Branch("evtype3",&evtype3);
   double evtype6; newtree->Branch("evtype6",&evtype6);
   double et3;
   double et6;
   double QCDele; newtree->Branch("QCDele",&QCDele);
   double QCDmu; newtree->Branch("QCDmu",&QCDmu);
   double QCDemu; newtree->Branch("QCDemu",&QCDemu);
   double QCDmue; newtree->Branch("QCDmue",&QCDmue);
   //other variables
   double EVENT_rhopog; newtree->Branch("EVENT_rhopog",&EVENT_rhopog); 
   double HEEPIDele;
   double FakeMu;
   double FakeEle;
   ULong64_t EVENT_event; newtree->Branch("EVENT_event",&EVENT_event);
   double DPhi_ele1MET; newtree->Branch("DPhi_ele1MET",&DPhi_ele1MET);
   double DPhi_ele2MET; newtree->Branch("DPhi_ele2MET",&DPhi_ele2MET);
   double ele1PtOverMET; newtree->Branch("ele1PtOverMET",&ele1PtOverMET);
   double ele2PtOverMET; newtree->Branch("ele2PtOverMET",&ele2PtOverMET);
   double Mt_ele1MET; newtree->Branch("Mt_ele1MET",&Mt_ele1MET);
   double Mt_ele2MET; newtree->Branch("Mt_ele2MET",&Mt_ele2MET);
   //reco 4-vectors:
   TLorentzVector Ele1(0,0,0,0);
   TLorentzVector Ele2(0,0,0,0);
   TLorentzVector Muon1(0,0,0,0);
   TLorentzVector Muon2(0,0,0,0);
   TLorentzVector BoostedJet1(0,0,0,0);

   int countSi=0;
   int countNo=0;
   int nen = nentries;
   if(nentries==-1) nen = readingtree->GetEntries();
   cout << nen << endl;
   for(int en=0; en<nen; en++){
   //for(int en=340; en<360; en++){
    //Read branches
    //Trigger:
    
    b_rHLT_Ele27_eta2p1_WPLoose_Gsf->GetEntry(en);
    //b_rHLT_DoubleEle33_CaloIdL_GsfTrkIdVL->GetEntry(en);
    b_rHLT_Ele115_CaloIdVT_GsfTrkIdT->GetEntry(en);
    b_rHLT_Mu50->GetEntry(en);
    b_rHLT_TkMu50->GetEntry(en); 
    b_rHLT_OldMu100->GetEntry(en);
    b_rHLT_TkMu100->GetEntry(en);    
    //PU:
    b_rPUWeight->GetEntry(en);
    b_rnBestVtx->GetEntry(en);
    b_rtrueInteractions->GetEntry(en);
    //Muons
    //Kinematics:
    b_rMuon_pt->GetEntry(en);
    b_rMuon_eta->GetEntry(en);
    b_rMuon_phi->GetEntry(en);
    b_rMuon_energy->GetEntry(en);
    b_rMuon_p->GetEntry(en);
    b_rMuon_px->GetEntry(en);
    b_rMuon_py->GetEntry(en);
    b_rMuon_pz->GetEntry(en);
    b_rMuon_charge->GetEntry(en);
    //Isolation
    b_rMuon_trackIso->GetEntry(en);
    b_rMuon_TrackerIso->GetEntry(en);
    b_rMuon_relIsoDeltaBetaR03->GetEntry(en);
    b_rMuon_relIsoDeltaBetaR04->GetEntry(en);
    //ID
    b_rMuon_soft->GetEntry(en);
    b_rMuon_loose->GetEntry(en);
    b_rMuon_medium->GetEntry(en);
    b_rMuon_tight->GetEntry(en);
    b_rMuon_isHighPt->GetEntry(en);
    b_rMuon_loose->GetEntry(en);
    b_rMuon_medium->GetEntry(en);
    b_rMuon_tight->GetEntry(en);
    b_rMuon_validHitsInner->GetEntry(en);
    b_rMuon_TLayers->GetEntry(en);
    b_rMuon_dz_pv->GetEntry(en);
    b_rMuon_dxy_pv->GetEntry(en);
    b_rMuon_isGlobal->GetEntry(en);
    b_rMuon_isTrackerMuon->GetEntry(en);
    //Electrons
    //kinematics:
    b_rpatElectron_pt->GetEntry(en);
    b_rpatElectron_eta->GetEntry(en);
    b_rpatElectron_phi->GetEntry(en);
    b_rpatElectron_p->GetEntry(en);
    b_rpatElectron_px->GetEntry(en);
    b_rpatElectron_py->GetEntry(en);
    b_rpatElectron_pz->GetEntry(en);
    b_rpatElectron_energy->GetEntry(en);
    b_rpatElectron_charge->GetEntry(en);
    //ID:
    b_rpatElectron_isPassVeto->GetEntry(en);
    b_rpatElectron_isPassLoose->GetEntry(en);
    b_rpatElectron_isPassMedium->GetEntry(en);
    b_rpatElectron_isPassTight->GetEntry(en);
    b_rpatElectron_isPassHEEPId->GetEntry(en);
    b_rpatElectron_isPassMvatrig->GetEntry(en);

    b_rpatElectron_Et->GetEntry(en);
    b_rpatElectron_SCeta->GetEntry(en);
    b_rpatElectron_isEcalDriven->GetEntry(en);
    b_rpatElectron_dEtaIn->GetEntry(en);
    b_rpatElectron_dPhiIn->GetEntry(en);
    b_rpatElectron_hOverE->GetEntry(en);
    b_rpatElectron_full5x5_sigmaIetaIeta->GetEntry(en);
    b_rpatElectron_full5x5_e2x5Max->GetEntry(en);
    b_rpatElectron_full5x5_e1x5->GetEntry(en);
    b_rpatElectron_full5x5_e5x5->GetEntry(en);
    b_rpatElectron_dr03EcalRecHitSumEt->GetEntry(en);
    b_rpatElectron_dr03HcalDepth1TowerSumEt->GetEntry(en);
    b_rpatElectron_isolPtTracks->GetEntry(en);
    b_rpatElectron_expectedMissingInnerHits->GetEntry(en);
    b_rpatElectron_gsfTrack_dxy_pv->GetEntry(en);
    b_rpatElectron_d0->GetEntry(en);
   b_rpatElectron_ecalPFClusterIso->GetEntry(en);
   b_rpatElectron_hcalPFClusterIso->GetEntry(en);

    //Jets
    //kinematics:
    b_rJet_pt->GetEntry(en);
    b_rJet_eta->GetEntry(en);
    b_rJet_phi->GetEntry(en);
    b_rJet_energy->GetEntry(en);
    b_rJet_px->GetEntry(en);
    b_rJet_py->GetEntry(en);
    b_rJet_pz->GetEntry(en);
    b_rJet_mass->GetEntry(en);
    //ID variables:
    b_rJet_neutralHadEnergyFraction->GetEntry(en);
    b_rJet_neutralEmEnergyFraction->GetEntry(en);
    b_rJet_chargedHadronEnergyFraction->GetEntry(en);
    b_rJet_chargedEmEnergyFraction->GetEntry(en);
    b_rJet_muonEnergyFraction->GetEntry(en);
    b_rJet_numberOfConstituents->GetEntry(en);
    b_rJet_chargedMultiplicity->GetEntry(en);
    //corrections:
    b_rJet_Uncorr_pt->GetEntry(en);
    b_rJet_JesSF->GetEntry(en);
    b_rJet_JerSF->GetEntry(en);
    //b-tagging:
    b_rJet_pfCombinedInclusiveSecondaryVertexV2BJetTags->GetEntry(en);
    b_rJet_pfCombinedMVAV2BJetTags->GetEntry(en);
    //Boosted jets
    //kinematics:
    b_rBoostedJet_pt->GetEntry(en);
    b_rBoostedJet_eta->GetEntry(en);
    b_rBoostedJet_phi->GetEntry(en);
    b_rBoostedJet_energy->GetEntry(en);
    b_rBoostedJet_mass->GetEntry(en);
    //ID variables:
    b_rBoostedJet_neutralHadEnergyFraction->GetEntry(en);
    b_rBoostedJet_neutralEmEmEnergyFraction->GetEntry(en);
    b_rBoostedJet_chargedHadronEnergyFraction->GetEntry(en);
    b_rBoostedJet_chargedEmEnergyFraction->GetEntry(en);
    b_rBoostedJet_muonEnergyFraction->GetEntry(en);
    b_rBoostedJet_numberOfConstituents->GetEntry(en);
    b_rBoostedJet_chargedMultiplicity->GetEntry(en);
    //corrections
    b_rBoostedJet_Uncorr_pt->GetEntry(en);
    b_rBoostedJet_JesSF->GetEntry(en);
    //b-tagging:
    b_rBoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags->GetEntry(en);    
    //MET
    b_rMet_type1PF_pt->GetEntry(en);
    b_rMet_type1PF_phi->GetEntry(en);
    b_rMet_type1PF_px->GetEntry(en);
    b_rMet_type1PF_py->GetEntry(en);
    //other variables
    b_rEVENT_rhopog->GetEntry(en);
    EVENT_rhopog = -999;
    EVENT_rhopog = rEVENT_rhopog;
    b_rEVENT_event->GetEntry(en);
    EVENT_event = -999;
    EVENT_event = rEVENT_event;

    //New var clear (vectors):
    Muon_pt->clear();
    Muon_eta->clear();
    Muon_phi->clear();
    Muon_p->clear();
    Muon_px->clear();
    Muon_py->clear();
    Muon_pz->clear();
    Muon_energy->clear();
    Muon_charge->clear();
    Muon_trackIso->clear();
    Muon_TrackerIso->clear();
    Muon_relIsoDeltaBetaR03->clear();
    Muon_relIsoDeltaBetaR04->clear();
    Muon_isHighPt->clear();
    Muon_loose->clear();
    Muon_medium->clear();
    Muon_tight->clear();
    Muon_validHitsInner->clear();
    Muon_TLayers->clear();
    Muon_dz_pv->clear();
    Muon_dxy_pv->clear();

    patElectron_pt->clear();
    patElectron_eta->clear();
    patElectron_phi->clear();
    patElectron_energy->clear();
    patElectron_p->clear();
    patElectron_px->clear();
    patElectron_py->clear();
    patElectron_pz->clear();
    patElectron_charge->clear();
    patElectron_isPassVeto->clear();
    patElectron_isPassLoose->clear();
    patElectron_isPassMedium->clear();
    patElectron_isPassTight->clear();
    patElectron_isPassHEEPId->clear();
    patElectron_isPassMvatrig->clear();
    eleIsHEEPID->clear();
    eleIsHEEPnonISO3->clear();
    eleIsHEEPnonISO6->clear();

    patElectron_Et->clear();
    patElectron_SCeta->clear();
    patElectron_isEcalDriven->clear();
    patElectron_dEtaIn->clear();
    patElectron_dPhiIn->clear();
    patElectron_hOverE->clear();
    patElectron_full5x5_sigmaIetaIeta->clear();
    patElectron_full5x5_e2x5Max->clear();
    patElectron_full5x5_e5x5->clear();
    patElectron_full5x5_e1x5->clear();
    patElectron_dr03EcalRecHitSumEt->clear();
    patElectron_dr03HcalDepth1TowerSumEt->clear();
    patElectron_isolPtTracks->clear();
    patElectron_expectedMissingInnerHits->clear();
    patElectron_gsfTrack_dxy_pv->clear();
    patElectron_d0->clear();
    patElectron_ecalPFClusterIso->clear();
    patElectron_hcalPFClusterIso->clear();
    R1_sr->clear();
    R2_sr->clear();
    R1_wgt->clear();
    R2_wgt->clear();
    Iso1->clear();
    Iso2->clear();

    Jet_pt->clear();
    Jet_eta->clear();
    Jet_phi->clear();
    Jet_px->clear();
    Jet_py->clear();
    Jet_pz->clear();
    Jet_energy->clear();
    Jet_mass->clear();
    Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags->clear();
    Jet_pfCombinedMVAV2BJetTags->clear();
    Jet_M->clear();
    Jet_nBoostedJets->clear();
    Jet_nBoostedJetsM->clear();
    Jet_L->clear();
    Jet_T->clear();
    Jet_TLV->clear();

    BoostedJet_pt->clear();
    BoostedJet_eta->clear();
    BoostedJet_phi->clear();
    BoostedJet_energy->clear();
    BoostedJet_mass->clear();
    BoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags->clear();
    BoostedJet_M->clear();
    BoostedJet_nJets->clear();
    BoostedJet_nJetsM->clear();
    BoostedJet_L->clear();
    BoostedJet_T->clear();
    BoostedJet_TLV->clear();


    //new var inizialize (scalars):
    HLT_Ele27_eta2p1_WPLoose_Gsf = -999;
    //HLT_DoubleEle33_CaloIdL_GsfTrkIdVL = -999;
    HLT_Ele115_CaloIdVT_GsfTrkIdT = -999;
    HLT_Mu50 = -999;
    HLT_TkMu50 = -999;
    HLT_TkMu100 = -999;
    HLT_OldMu100 = -999;

    PUWeight = -999; nBestVtx = -999; trueInteractions = -999; lumi_wgt = -999;
    Met_type1PF_pt = -999; Met_type1PF_phi = -999; Met_type1PF_px = -999; Met_type1PF_py = -999;

    numOfHighptMu=0; numOfLooseMu=0; numOfMediumMu=0; numOfTightMu=0;

    numOfHighptEle=0; numOfLooseEle=0; numOfMediumEle=0; numOfTightEle=0; numOfVetoEle=0;
    numOfHEEPEle=0; numOfFakeMu=0; numOfFakeEle=0;


    numOfJets_L=0; numOfJets_T=0; numOfJets_TLV=0;
    numOfBoostedJets_L=0; numOfBoostedJets_T=0; numOfBoostedJets_TLV=0; 
    numOfbJetsSV_WPT=0;numOfbJetsSV_WPM=0;numOfbJetsSV_WPL=0;
    numOfbJetsMVA_WPT=0;numOfbJetsMVA_WPM=0;numOfbJetsMVA_WPL=0;

    Ele1_pt=-999;  Ele1_eta=-999; Ele1_phi=-999; Ele1_energy=-999; Ele1_p=-999; Ele1_px=-999; Ele1_py=-999; Ele1_pz=-999;
    Ele2_pt=-999; Ele2_eta=-999; Ele2_phi=-999; Ele2_energy=-999; Ele2_p=-999; Ele2_px=-999; Ele2_py=-999; Ele2_pz=-999;
    Muon1_pt=-999;  Muon1_eta=-999; Muon1_phi=-999; Muon1_energy=-999; Muon1_p=-999; Muon1_px=-999; Muon1_py=-999; Muon1_pz=-999;
    Muon2_pt=-999;  Muon2_eta=-999; Muon2_phi=-999; Muon2_energy=-999; Muon2_p=-999; Muon2_px=-999; Muon2_py=-999; Muon2_pz=-999;
    BoostedJet1_pt=-999; BoostedJet1_eta=-999; BoostedJet1_phi=-999; BoostedJet1_energy=-999;
    BoostedJet1_nJets=-999;


      
    M_ele1ele2Bjet1 = -999;  
    M_leplepBjet1 = -999;
    M_ele1ele2 = -999; M_elemu = -999; M_elemuBjet1 = -999; M_mu1mu2 = -999; M_mu1mu2Bjet1 = -999;
    S_T_BJ = -999; S_T_jj = -999;
    M_leplep = -999; M_leplepBjet = -999;

    musf_trigger_mu1 = -999; musf_ID_mu1 = -999; musf_iso_mu1 = -999; musf_tot_mu1 = -999;
    musf_trigger_mu2 = -999; musf_ID_mu2 = -999; musf_iso_mu2 = -999; musf_tot_mu2 = -999;
    elesf_ele1 = -999; elesf_ele2 = -999; lepsf_evt = -999; QCD_wgt_mu1 = -999; QCD_wgt_mu2 = -999;
    QCD_wgt_ele1 = -999; QCD_wgt_ele2 = -999;
    QCD_wgt_evt= -999;
    //evt_type = -999;
    eejj_l = 0; emujj_l = 0; mumujj_l = 0; muejj_l = 0; 
    evtype3 = 0; evtype6 = 0;
    et3 = 0; et6 = 0;
    QCDele = 0; QCDmu = 0; QCDemu = 0; QCDmue = 0;
    DPhi_ele1MET = -999; DPhi_ele2MET = -999;
    ele1PtOverMET = -999; ele2PtOverMET = -999;
    Mt_ele1MET = -999; Mt_ele2MET = -999;

    
   HLT_Ele27_eta2p1_WPLoose_Gsf = rHLT_Ele27_eta2p1_WPLoose_Gsf;
   //HLT_DoubleEle33_CaloIdL_GsfTrkIdVL = rHLT_DoubleEle33_CaloIdL_GsfTrkIdVL;
   HLT_Ele115_CaloIdVT_GsfTrkIdT = rHLT_Ele115_CaloIdVT_GsfTrkIdT;
   HLT_Mu50 = rHLT_Mu50;
   HLT_TkMu50 = rHLT_TkMu50;
   HLT_OldMu100 = rHLT_OldMu100;
   HLT_TkMu100 = rHLT_TkMu100; 

    PUWeight = rPUWeight;
    trueInteractions = rtrueInteractions;
    nBestVtx = rnBestVtx;
    PileupWeight = CalculatePileupWeight(trueInteractions);
    lumi_wgt = get_wgtlumi(Input);
   
   Met_type1PF_phi = rMet_type1PF_phi;  
   Met_type1PF_px = rMet_type1PF_px;
   Met_type1PF_py = rMet_type1PF_py; 
/*
   for(uint ele_en = 0; ele_en<rpatElectron_pt->size(); ele_en++){
    if( rpatElectron_pt->at(ele_en)>20 && fabs(rpatElectron_eta->at(ele_en))<2.4){
     if(rpatElectron_isPassLoose->at(ele_en)==1) numOfLooseEle++;
     if(rpatElectron_isPassMedium->at(ele_en)==1) numOfMediumEle++;
     if(rpatElectron_isPassTight->at(ele_en)==1) numOfTightEle++;
     if(rpatElectron_isPassVeto->at(ele_en)==1) numOfVetoEle++;
     if(rpatElectron_isPassHEEPId->at(ele_en)==1){
      numOfHighptEle++;
      patElectron_pt->push_back(rpatElectron_pt->at(ele_en));
      patElectron_eta->push_back(rpatElectron_eta->at(ele_en));
      patElectron_phi->push_back(rpatElectron_phi->at(ele_en));
      patElectron_p->push_back(rpatElectron_p->at(ele_en));
      patElectron_px->push_back(rpatElectron_px->at(ele_en));
      patElectron_py->push_back(rpatElectron_py->at(ele_en));
      patElectron_pz->push_back(rpatElectron_pz->at(ele_en));
      patElectron_charge->push_back(rpatElectron_charge->at(ele_en));
      patElectron_energy->push_back(rpatElectron_energy->at(ele_en));
      patElectron_isPassVeto->push_back(rpatElectron_isPassVeto->at(ele_en));
      patElectron_isPassLoose->push_back(rpatElectron_isPassLoose->at(ele_en));
      patElectron_isPassMedium->push_back(rpatElectron_isPassMedium->at(ele_en));
      patElectron_isPassTight->push_back(rpatElectron_isPassTight->at(ele_en));
      patElectron_isPassHEEPId->push_back(rpatElectron_isPassHEEPId->at(ele_en));
      patElectron_isPassMvatrig->push_back(rpatElectron_isPassMvatrig->at(ele_en));
     }
    }
   }      
*/
   //if(!(HLT_Mu50==1 && numOfVetoEle==0)) continue;
   //
   for(uint ele_en = 0; ele_en<rpatElectron_pt->size(); ele_en++){
    if(rpatElectron_pt->at(ele_en)>35 && fabs(rpatElectron_eta->at(ele_en))<2.4){
     if(rpatElectron_isPassVeto->at(ele_en)==1) numOfVetoEle++;
     FakeEle=FakeRateID(rpatElectron_SCeta->at(ele_en), rpatElectron_full5x5_sigmaIetaIeta->at(ele_en), rpatElectron_hOverE->at(ele_en), rpatElectron_expectedMissingInnerHits->at(ele_en), rpatElectron_gsfTrack_dxy_pv->at(ele_en));
     if(FakeEle==1 && rpatElectron_isPassHEEPId->at(ele_en)==0){
      numOfFakeEle++;
      patElectron_px->push_back(rpatElectron_px->at(ele_en));
      patElectron_py->push_back(rpatElectron_py->at(ele_en));
      patElectron_pt->push_back(rpatElectron_pt->at(ele_en));
      patElectron_eta->push_back(rpatElectron_eta->at(ele_en));
      patElectron_phi->push_back(rpatElectron_phi->at(ele_en));
      patElectron_energy->push_back(rpatElectron_energy->at(ele_en));
      patElectron_SCeta->push_back(rpatElectron_SCeta->at(ele_en));
      patElectron_Et->push_back(rpatElectron_Et->at(ele_en));

     }
    }
   }

   for(uint mu_en = 0; mu_en<rMuon_pt->size(); mu_en++){
    if( rMuon_pt->at(mu_en)>30 && fabs(rMuon_eta->at(mu_en))<2.4){
     if(rMuon_loose->at(mu_en)==1 && rMuon_TrackerIso->at(mu_en)<0.1) numOfLooseMu++;
     FakeMu = FakeRateIDmu(rMuon_isGlobal->at(mu_en), rMuon_isTrackerMuon->at(mu_en), rMuon_dz_pv->at(mu_en), rMuon_dxy_pv->at(mu_en), rMuon_TLayers->at(mu_en), rMuon_validHitsInner->at(mu_en));
     if(FakeMu==1 && rMuon_isHighPt->at(mu_en)==0){
      numOfFakeMu++;
      Muon_pt->push_back(rMuon_pt->at(mu_en));
      Muon_eta->push_back(rMuon_eta->at(mu_en));
      Muon_phi->push_back(rMuon_phi->at(mu_en));
      Muon_p->push_back(rMuon_p->at(mu_en));
      Muon_px->push_back(rMuon_px->at(mu_en));
      Muon_py->push_back(rMuon_py->at(mu_en));
      Muon_pz->push_back(rMuon_pz->at(mu_en));
      Muon_energy->push_back(rMuon_energy->at(mu_en));
      Muon_charge->push_back(rMuon_charge->at(mu_en));

     }
    }
   }


   bool BoostedJet_isIDT=false;
   int countBoostedJets=0;
   numOfBoostedJets=0;
   for(uint jet_en = 0; jet_en<rBoostedJet_pt->size(); jet_en++){
    double jet_pt = rBoostedJet_Uncorr_pt->at(jet_en)*rBoostedJet_JesSF->at(jet_en);
    double jet_energy=rBoostedJet_energy->at(jet_en)*rBoostedJet_Uncorr_pt->at(jet_en)/rBoostedJet_pt->at(jet_en)*rBoostedJet_JesSF->at(jet_en);
    TLorentzVector JetCorr(0,0,0,0); JetCorr.SetPtEtaPhiE(jet_pt, rBoostedJet_eta->at(jet_en), rBoostedJet_phi->at(jet_en), jet_energy);
    BoostedJet_isIDT = BoostedJetID_Tight(JetCorr.Pt(),fabs(JetCorr.Eta()),rBoostedJet_neutralHadEnergyFraction->at(jet_en),
    rBoostedJet_neutralEmEmEnergyFraction->at(jet_en),rBoostedJet_numberOfConstituents->at(jet_en),rBoostedJet_muonEnergyFraction->at(jet_en),
    rBoostedJet_chargedHadronEnergyFraction->at(jet_en),rBoostedJet_chargedMultiplicity->at(jet_en),
    rBoostedJet_chargedEmEnergyFraction->at(jet_en));
    int count = 0;
    if(BoostedJet_isIDT==true){

     for(uint ele_en = 0; ele_en<patElectron_pt->size(); ele_en++){
      double DR_jetele = sqrt(pow(deltaPhi(patElectron_phi->at(ele_en),JetCorr.Phi()),2)+pow(patElectron_eta->at(ele_en)-JetCorr.Eta(),2) );
      double relPt = fabs(patElectron_pt->at(ele_en) - JetCorr.Pt())/JetCorr.Pt();
      if(DR_jetele<0.5) count++;
     }
     for(uint mu_en = 0; mu_en<Muon_pt->size(); mu_en++){
      double DR_jetmu = sqrt(pow(deltaPhi(Muon_phi->at(mu_en),JetCorr.Phi()),2)+pow(Muon_eta->at(mu_en)-JetCorr.Eta(),2) );
      double relPt = fabs(Muon_pt->at(mu_en) - JetCorr.Pt())/JetCorr.Pt();
      if(DR_jetmu<0.5) count++;
     }
     if(count == 0 && fabs(JetCorr.Eta())<2.4){
      countBoostedJets++;
      BoostedJet_pt->push_back(JetCorr.Pt());
      BoostedJet_eta->push_back(JetCorr.Eta());
      BoostedJet_phi->push_back(JetCorr.Phi());
      BoostedJet_energy->push_back(rBoostedJet_energy->at(jet_en));
      BoostedJet_mass->push_back(rBoostedJet_mass->at(jet_en));
      BoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags->push_back(rBoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags->at(jet_en));
        }
       }
      }
     numOfBoostedJets=countBoostedJets;

     if(HLT_Ele115_CaloIdVT_GsfTrkIdT==1 && numOfLooseMu==0 && numOfFakeEle==2 && patElectron_pt->at(0)>130 && patElectron_pt->at(1)>35 && numOfBoostedJets>=1){
      QCDele=1;
      Ele1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0), patElectron_energy->at(0));
      Ele2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1), patElectron_energy->at(1));
      BoostedJet1.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0), BoostedJet_energy->at(0));
      M_ele1ele2= (Ele1 + Ele2).M();
      M_ele1ele2Bjet1= (Ele1 + Ele2 + BoostedJet1).M();
      M_leplepBjet1= M_ele1ele2Bjet1;
      if(!(M_ele1ele2>300)) continue;
      QCD_wgt_ele1 = Wgt_QCD(patElectron_SCeta->at(0), patElectron_Et->at(0));
      QCD_wgt_ele2 = Wgt_QCD(patElectron_SCeta->at(1), patElectron_Et->at(1));
      QCD_wgt_evt = (QCD_wgt_ele1/(1-QCD_wgt_ele1))*(QCD_wgt_ele2/(1-QCD_wgt_ele2));
     }
  
     if((HLT_Mu50==1 || HLT_OldMu100 ==1 || HLT_TkMu100==1) && numOfVetoEle==0 && numOfFakeMu==2 && Muon_pt->at(0)>53 && Muon_pt->at(1)>30 && numOfBoostedJets>=1){
      QCDmu=1;
      Muon1.SetPtEtaPhiE(Muon_pt->at(0), Muon_eta->at(0), Muon_phi->at(0), Muon_energy->at(0));
      Muon2.SetPtEtaPhiE(Muon_pt->at(1), Muon_eta->at(1), Muon_phi->at(1), Muon_energy->at(1));
      BoostedJet1.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0), BoostedJet_energy->at(0));
      M_mu1mu2= (Muon1 + Muon2).M();
      M_mu1mu2Bjet1= (Muon1 + Muon2 + BoostedJet1).M();
      M_leplepBjet1= M_mu1mu2Bjet1;
      if(!(M_mu1mu2>300)) continue;
      QCD_wgt_mu1 = Wgt_QCDmu(Muon_eta->at(0), Muon_pt->at(0));
      QCD_wgt_mu2 = Wgt_QCDmu(Muon_eta->at(1), Muon_pt->at(1));
      QCD_wgt_evt = (QCD_wgt_mu1/(1-QCD_wgt_mu1))*(QCD_wgt_mu2/(1-QCD_wgt_mu2));
     }

     if(HLT_Ele115_CaloIdVT_GsfTrkIdT==1 && numOfFakeEle==1 && patElectron_pt->at(0)>130 && numOfFakeMu==1 && Muon_pt->at(0)>35 && numOfBoostedJets>=1){
      QCDemu=1;
      Ele1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0), patElectron_energy->at(0));
      Muon1.SetPtEtaPhiE(Muon_pt->at(0), Muon_eta->at(0), Muon_phi->at(0), Muon_energy->at(0));
      BoostedJet1.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0), BoostedJet_energy->at(0));
      M_leplep= (Ele1 + Muon1).M();
      M_leplepBjet1= (Ele1 + Muon1 + BoostedJet1).M();
      if(!(M_leplep>300)) continue;
      QCD_wgt_ele1 = Wgt_QCD(patElectron_SCeta->at(0), patElectron_Et->at(0));
      QCD_wgt_mu1 = Wgt_QCDmu(Muon_eta->at(0), Muon_pt->at(0));
      QCD_wgt_evt = (QCD_wgt_ele1/(1-QCD_wgt_ele1))*(QCD_wgt_mu1/(1-QCD_wgt_mu1));
     }

     if((HLT_Mu50==1 || HLT_OldMu100 ==1 || HLT_TkMu100==1) && numOfFakeMu==1 && Muon_pt->at(0)>53 && numOfFakeEle==1 && patElectron_pt->at(0)>35 && numOfBoostedJets>=1){
      QCDmue=1;
      Ele1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0), patElectron_energy->at(0));
      Muon1.SetPtEtaPhiE(Muon_pt->at(0), Muon_eta->at(0), Muon_phi->at(0), Muon_energy->at(0));
      BoostedJet1.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0), BoostedJet_energy->at(0));
      M_leplep= (Ele1 + Muon1).M();
      M_leplepBjet1= (Ele1 + Muon1 + BoostedJet1).M();
      if(!(M_leplep>300)) continue;
      QCD_wgt_ele1 = Wgt_QCD(patElectron_SCeta->at(0), patElectron_Et->at(0));
      QCD_wgt_mu1 = Wgt_QCDmu(Muon_eta->at(0), Muon_pt->at(0));
      QCD_wgt_evt = (QCD_wgt_ele1/(1-QCD_wgt_ele1))*(QCD_wgt_mu1/(1-QCD_wgt_mu1));
     }


   if(!(QCDele==1 || QCDmu==1 || QCDemu==1 || QCDmue==1)) continue;



   newtree->Fill();    
  }
  newfile->cd();
  newfile->Write();
  newfile->Close();
 
}

bool JetID_Loose(double rJet1, double rJet2, double rJet3, double rJet4,int rJet5, double rJet6, double rJet7, int rJet8, double rJet9){
 if(rJet1>30 && fabs(rJet2)<=2.4 && rJet3<0.99 && rJet4<0.99 && rJet5>1 && rJet7>0 && rJet8>0 && rJet9<0.99) return true;
 else if(rJet1>30 && fabs(rJet2)>2.4 && fabs(rJet2)<=3.0 && rJet3<0.99 && rJet4<0.99 && rJet5>1) return true;
 else return false;
}
bool JetID_Tight(double rJet1, double rJet2, double rJet3, double rJet4,int rJet5, double rJet6, double rJet7, int rJet8, double rJet9){
 if(rJet1>30 && fabs(rJet2)<=2.4 && rJet3<0.90 && rJet4<0.90 && rJet5>1 && rJet7>0 && rJet8>0 && rJet9<0.99) return true;
 else if(rJet1>30 && fabs(rJet2)>2.4 && fabs(rJet2)<=3.0 && rJet3<0.90 && rJet4<0.90 && rJet5>1) return true;
 else return false;
}
bool JetID_TightLepVeto(double rJet1, double rJet2, double rJet3, double rJet4,int rJet5, double rJet6, double rJet7, int rJet8, double rJet9){
 if(rJet1>30 && fabs(rJet2)<=2.4 && rJet3<0.90 && rJet4<0.90 && rJet5>1 && rJet6<0.8 && rJet7>0 && rJet8>0 && rJet9<0.90) return true;
 else if(rJet1>30 && fabs(rJet2)>2.4 && fabs(rJet2)<=3.0 && rJet3<0.90 && rJet4<0.90 && rJet5>1 && rJet6<0.8) return true;
 else return false;
}
bool BoostedJetID_Loose(double rJet1, double rJet2, double rJet3, double rJet4,int rJet5, double rJet6, double rJet7, int rJet8, double rJet9){
 if(rJet1>190 && fabs(rJet2)<=2.4 && rJet3<0.99 && rJet4<0.99 && rJet5>1 && rJet7>0 && rJet8>0 && rJet9<0.99) return true;
 else if(rJet1>190 && fabs(rJet2)>2.4 && fabs(rJet2)<=3.0 && rJet3<0.99 && rJet4<0.99 && rJet5>1) return true;
 else return false;
}
bool BoostedJetID_Tight(double rJet1, double rJet2, double rJet3, double rJet4,int rJet5, double rJet6, double rJet7, int rJet8, double rJet9){
 if(rJet1>190 && fabs(rJet2)<=2.4 && rJet3<0.90 && rJet4<0.90 && rJet5>1 && rJet7>0 && rJet8>0 && rJet9<0.99) return true;
 else if(rJet1>190 && fabs(rJet2)>2.4 && fabs(rJet2)<=3.0 && rJet3<0.90 && rJet4<0.90 && rJet5>1) return true;
 else return false;
}
bool BoostedJetID_TightLepVeto(double rJet1, double rJet2, double rJet3, double rJet4,int rJet5, double rJet6, double rJet7, int rJet8, double rJet9){
 if(rJet1>190 && fabs(rJet2)<=2.4 && rJet3<0.90 && rJet4<0.90 && rJet5>1 && rJet6<0.8 && rJet7>0 && rJet8>0 && rJet9<0.90) return true;
 else if(rJet1>190 && fabs(rJet2)>2.4 && fabs(rJet2)<=3.0 && rJet3<0.90 && rJet4<0.90 && rJet5>1 && rJet6<0.8) return true;
 else return false;
}
 
double HEEPID_check(double Et, double SCeta, double isEcalDriven, double dEtaIn, double dPhiIn, double hOverE, double full5x5_sigmaIetaIeta, double full5x5_e2x5Max, double full5x5_e5x5, double full5x5_e1x5, double ecalPFClusterIso, double hcalPFClusterIso, double isolPtTracks, double expectedMissingInnerHits, double gsfTrack_dxy_pv, double d0, double E, double rho){
double eleHEEP=0;
if(
(Et>35 && fabs(SCeta)<1.4442 && isEcalDriven==1 && fabs(dEtaIn)<0.004 && fabs(dPhiIn)<0.06 && hOverE<1/E+0.05 && (full5x5_e2x5Max/full5x5_e5x5>0.94 || full5x5_e1x5/full5x5_e5x5>0.83) && ecalPFClusterIso+hcalPFClusterIso<2+0.03*Et+0.28*rho && isolPtTracks<5 && expectedMissingInnerHits<=1 && gsfTrack_dxy_pv<0.02)  
 ||
(Et>35 && fabs(SCeta)>1.566 && fabs(SCeta)<2.5 && isEcalDriven==1 && fabs(dEtaIn)<0.006 && fabs(dPhiIn)<0.06 && hOverE<5/E+0.05 && full5x5_sigmaIetaIeta<0.3 && ((Et<50 && ecalPFClusterIso+hcalPFClusterIso<2.5+0.28*rho)||(Et>50 && ecalPFClusterIso+hcalPFClusterIso<2.5+0.03*(Et-50)+0.28*rho)) && isolPtTracks<5 && expectedMissingInnerHits<=1 && gsfTrack_dxy_pv<0.05)
)eleHEEP=1;

return eleHEEP;
}

double FakeRateID(double SCeta, double full5x5_sigmaIetaIeta, double hOverE, double expectedMissingInnerHits, double gsfTrack_dxy_pv){
double eleFake=0;
if((fabs(SCeta)<1.4442 && full5x5_sigmaIetaIeta<0.013 && hOverE<0.15 && expectedMissingInnerHits<=1 && gsfTrack_dxy_pv<0.02)
||
(fabs(SCeta)>1.566 && fabs(SCeta)<2.5 && full5x5_sigmaIetaIeta<0.034 && hOverE<0.10 && expectedMissingInnerHits<=1 && gsfTrack_dxy_pv<0.05)) eleFake=1;

return eleFake;
}

double FakeRateIDmu(int Global, int Tracker, double dz, double dxy, double TLayers, double validHitsInner){
double muFake=0;
if(Global==1 && Tracker==1 && fabs(dz)<1.0 && fabs(dxy)<0.2 && TLayers>5 && validHitsInner>0) muFake=1;

return muFake;
}

double HEEPnonISO_check(double Et, double SCeta, double isEcalDriven, double dEtaIn, double dPhiIn, double hOverE, double full5x5_sigmaIetaIeta, double full5x5_e2x5Max, double full5x5_e5x5, double full5x5_e1x5, double ecalPFClusterIso, double hcalPFClusterIso, double isolPtTracks, double expectedMissingInnerHits, double gsfTrack_dxy_pv, double d0, double E, double rho){
double eleHEEP=0;
if(
(Et>35 && fabs(SCeta)<1.4442 && isEcalDriven==1 && fabs(dEtaIn)<0.004 && fabs(dPhiIn)<0.06 && hOverE<1/E+0.05 && (full5x5_e2x5Max/full5x5_e5x5>0.94 || full5x5_e1x5/full5x5_e5x5>0.83) && expectedMissingInnerHits<=1 && gsfTrack_dxy_pv<0.02)
 ||
(Et>35 && fabs(SCeta)>1.566 && fabs(SCeta)<2.5 && isEcalDriven==1 && fabs(dEtaIn)<0.006 && fabs(dPhiIn)<0.06 && hOverE<5/E+0.05 && full5x5_sigmaIetaIeta<0.3 && expectedMissingInnerHits<=1 && gsfTrack_dxy_pv<0.05)
)eleHEEP=1;

return eleHEEP;
}

double Mt(double px1, double py1, double pt1, double px2, double py2){
 double px = px1 + px2;
 double py = py1 + py2;
 double pt = pt1 + sqrt(px2*px2 + py2+py2);
 double mt2 = pt*pt - (px*px + py*py);
 if(mt2>=0) return sqrt(mt2);
 else return -1;

}

double deltaPhi(double phi1, double phi2) {
 double result = phi1 - phi2;
 while (result > M_PI) result -= 2*M_PI;
 while (result <= -M_PI) result += 2*M_PI;
 return result;
}
double CalculatePileupWeight(int trueInteractions){
 double data[] =  {5.64297e-05,0.000269623,0.000382956,0.000552844,0.000979931,0.00231634,0.0072801,0.0281133,0.0770196,0.130953,0.169536,0.182158,0.161879,0.116249,0.067104,0.0316937,0.0130125,0.00540404,0.00265731,0.00140593,0.000649204,0.000236783,6.7861e-05,1.63211e-05,3.82396e-06,1.03356e-06,3.33506e-07,1.1967e-07,4.49699e-08,1.70463e-08,6.34643e-09,2.28001e-09,7.82427e-10,2.55149e-10,7.88717e-11,2.30861e-11,6.39564e-12,1.67664e-12,4.15902e-13,9.76172e-14,2.16793e-14,4.55562e-15,9.05813e-16,1.70419e-16,3.03394e-17,5.11017e-18,8.14821e-19,1.20894e-19,2.20432e-20,0,0};
 double mc[] = {0.000108643,0.000388957,0.000332882,0.00038397,0.000549167,0.00105412,0.00459007,0.0210314,0.0573688,0.103986,0.142369,0.157729,0.147685,0.121027,0.08855,0.0582866,0.0348526,0.019457,0.0107907,0.00654313,0.00463195,0.00370927,0.0031137,0.00261141,0.00215499,0.00174491,0.00138268,0.00106731,0.000798828,0.00057785,0.00040336,0.00027161,0.000176535,0.00011092,6.75502e-05,4.00323e-05,2.32123e-05,1.32585e-05,7.51611e-06,4.25902e-06,2.42513e-06,1.39077e-06,8.02452e-07,4.64159e-07,2.67845e-07,1.5344e-07,8.68966e-08,4.84931e-08,2.6606e-08,1.433e-08};
 double puw;
 puw=data[trueInteractions]/mc[trueInteractions];
 return puw;
}

double Wgt_QCD(double SCeta, double Et){
 double wgt=0;
 if(fabs(SCeta)<1.4442){
  if(Et>=35.0 && Et<131.5) wgt = 0.106-0.00252*Et+0.0000228*Et*Et-0.0000000721*Et*Et*Et;
  if(Et>=131.5 && Et<355.0) wgt = 0.0138-0.000103*Et+0.000000362*Et*Et-0.000000000425*Et*Et*Et;
  if(Et>=355.0) wgt = 0.00279+0.00000243;
 }
 if(fabs(SCeta)>1.566 && fabs(SCeta)<2){
  if(Et>=35.0 && Et<122.0) wgt = 0.117-0.0013*Et+0.00000467*Et*Et;
  if(Et>=122.0 && Et<226.3) wgt = 0.0345-0.0000476*Et;
  if(Et>=226.3) wgt = 0.0258-0.00000909*Et;
 }
 if(fabs(SCeta)>2 && fabs(SCeta)<2.5){
  if(Et>=35.0 && Et<112.5) wgt = 0.0809-0.000343*Et;
  if(Et>=112.5) wgt = 0.0423;
 }

 return wgt;
}

double Wgt_QCDmu(double eta, double pt){
 double wgt=0;
 if(fabs(eta)<1.4442){
  if(pt>53 && pt<=200) wgt = 0.111040-0.00121997*pt+0.00000527748*pt*pt;
  if(pt>200 && pt<=800) wgt = 2.38002-5726.51/(2234.75+pt);
  if(pt>800) wgt = 0.412519;
 }
 if(fabs(eta)>1.566 && fabs(eta)<2.5){
  if(pt>53 && pt <=250) wgt = 0.137352-0.00108994*pt+0.00000564918*pt*pt;
  if(pt>250) wgt = 0.238683;
 }
 return wgt;
}


double elesf(double eta){
 double elesf=0;
  if(fabs(eta) < 1.4442) elesf = 0.989; // stat 0.001 // syst 0.014
 if(fabs(eta) >= 1.566 && fabs(eta) < 2.5)elesf = 0.982; // stat 0.001 syst 0.014
 return elesf;
}
double musf_trigger(double eta, double pt){
 double musf=0;
 if (fabs(eta) >= 0.0 && fabs(eta)<0.9){
  if(pt > 52. && pt <= 56) musf = 0.9385219812393188; //stat 0.0002566604294316861 
  if(pt > 56. && pt <= 60) musf = 0.938785195350647; // stat 0.0003512045613493856
  if(pt > 60. && pt <= 120) musf = 0.9373190402984619; // stat 0.00031808216113278883
  if(pt > 120 && pt <= 200) musf = 0.9289411902427673; // stat 0.0014673600305817596
  if(pt > 200 && pt <= 300) musf = 0.9162033796310425; // stat 0.0028656970513730017
  if(pt > 300) musf = 0.8930183053016663; // stat 0.007617952889111469
 }
 if (fabs(eta) >= 0.9 && fabs(eta)<1.2){
  if(pt > 52. && pt <= 56) musf = 0.9429171681404114; //stat 0.0004323455043906205 
  if(pt > 56. && pt <= 60) musf = 0.944566011428833; // stat 0.0006453209717745792
  if(pt > 60. && pt <= 120) musf = 0.9416107535362244; // stat 0.0004590463319092091
  if(pt > 120 && pt <= 200) musf = 0.9340407252311707; // stat 0.0019242274872617194
  if(pt > 200 && pt <= 300) musf = 0.9116483330726624; // stat 0.004974297248567905
  if(pt > 300) musf = 0.8819695115089417; // stat 0.01840147234943961
 }
 if (fabs(eta) >= 1.2 && fabs(eta)<2.1){
  if(pt > 52. && pt <= 56) musf = 0.9153958559036255; //stat 0.0003371717180362242  
  if(pt > 56. && pt <= 60) musf = 0.9197514057159424; // stat 0.0004579121798908698
  if(pt > 60. && pt <= 120) musf = 0.9216225147247314; // stat 0.000365347265978311
  if(pt > 120 && pt <= 200) musf = 0.9233274459838867; // stat 0.0014746349755392736
  if(pt > 200 && pt <= 300) musf = 0.9137247204780579; // stat 0.003394166872715402
  if(pt > 300) musf = 0.9049304127693176; // stat 0.00863011621547623
 }
 if (fabs(eta) >= 2.1 && fabs(eta)<2.4){
  if(pt > 52. && pt <= 56) musf = 0.801039457321167; //stat 0.0010483845705795774   
  if(pt > 56. && pt <= 60) musf = 0.8250287771224976; // stat 0.0014525323104812836
  if(pt > 60. && pt <= 120) musf = 0.8385295867919922; // stat 0.00112496967288113
  if(pt > 120 && pt <= 200) musf = 0.8503307104110718; // stat 0.005195122102448952
  if(pt > 200 && pt <= 300) musf = 0.8325985074043274; // stat 0.023364071376511055
  if(pt > 300) musf = 0.8184008598327637; // stat 0.0307142641727703
 }

 return musf;
}
double musf_ID(double eta, double pt){
 double musf=0;
 if(fabs(eta)>0.0 && fabs(eta)<=0.9){
  if(pt>20 && pt<=25) musf=0.992114065208379; //stat 0.0009548339162957359 syst 0.003162399267958033
  if(pt>25 && pt<=30) musf=0.9924247027728448; //stat 0.0005721135461542568 syst 0.0010782479163609626
  if(pt>30 && pt<=40) musf=0.9922515732194475; //stat 0.00022056808100734152 syst 0.0007359632248935538
  if(pt>40 && pt<=50) musf=0.9926712022753303;  //stat 0.00029555844081348594 syst 0.0003533157820171002
  if(pt>50 && pt<=60) musf=0.9928603953286465; //stat 0.0004812825431584111 syst 0.00043672529257821963 
  if(pt>60)musf=0.992263125763373; //stat 0.0007301722545706139 syst 0.002402158659265339
 }
 if(fabs(eta)>0.9 && fabs(eta)<=1.2){
  if(pt>20 && pt<=25) musf=0.9880778949699621; //stat 0.0015507830148471576 syst 0.005036496188936483
  if(pt>25 && pt<=30) musf=0.9858269794946017; //stat 0.0008667578427999276 syst 0.001745662101625533
  if(pt>30 && pt<=40) musf=0.9861662092005419; //stat 0.00040273205051734795 syst 0.0034511238183185886
  if(pt>40 && pt<=50) musf=0.9868886396371438;  //stat 0.000358620121199017 syst 0.00030898133813181395
  if(pt>50 && pt<=60) musf=0.9857803031481773; //stat 0.0008250932378258363 syst 0.0009861532718310382
  if(pt>60)musf=0.9851298296096568; //stat 0.0013508015355310672 syst 0.001925392663728019
 }
 if(fabs(eta)>1.2 && fabs(eta)<=2.1){
  if(pt>20 && pt<=25) musf=0.9922334188037855; //stat 0.0006058268576121627 syst 0.000631608941554746
  if(pt>25 && pt<=30) musf=0.9923174786068355; //stat 0.00041202179870509885 syst 0.0024034807992315737
  if(pt>30 && pt<=40) musf=0.9922065831090526; //stat 0.00017938520880153905 syst 0.001333626342856719
  if(pt>40 && pt<=50) musf=0.9915977902632379; //stat 0.00018633029867623288 syst 4.41027174736005e-05
  if(pt>50 && pt<=60) musf=0.9925127625404958; //stat 0.00039796265367970246 syst 0.0008803577974452146
  if(pt>60)musf=0.9910195523946569; //stat 0.0006320689063062524 syst 0.00036749348244443785
 }
 if(fabs(eta)>2.1 && fabs(eta)<=2.4){
  if(pt>20 && pt<=25) musf=0.9797230542389544; //stat 0.002343776036433275 syst 0.0030120193907532643 
  if(pt>25 && pt<=30) musf=0.9781500508836776; //stat 0.0011083458857072618 syst 0.0028918407397342267
  if(pt>30 && pt<=40) musf=0.9777848757048854; //stat 0.0005589872869792092 syst 0.0008953812470090439
  if(pt>40 && pt<=50) musf=0.9777795367016231; //stat 0.000807982424363258 syst 0.0018536119955217358
  if(pt>50 && pt<=60) musf=0.9770080438205287; //stat 0.0017636447439491989 syst 0.002434676080669997
  if(pt>60)musf=0.9739992676455306; //stat 0.0028517427863376157 syst 0.004570509391366933
 }

 return musf;
}
double musf_iso(double eta, double pt){
 double musf=0;
 if(fabs(eta)>0.0 && fabs(eta)<=0.9){
  if(pt>20 && pt<=25) musf=0.9919099304633023; // stat 0.001982360612184662 syst 0.0007768385116509315  
  if(pt>25 && pt<=30) musf=0.995306030345587; // stat 0.00091282105303195 syst 0.0005437735321288286 
  if(pt>30 && pt<=40) musf=0.9976936604669998; // stat 0.0002265133242871324 //syst 0.00013374847679938027 
  if(pt>40 && pt<=50) musf=0.999160897257596; // stat 0.006779894111641307 syst 0.0009722570427004104
  if(pt>50 && pt<=60) musf=0.9994395659288342; // stat 0.00018295970484288526 syst 4.147968081605816e-05 
  if(pt>60)musf=0.9997314718411786; // stat 0.00029221141460445045 syst 6.304097243921762e-05
 }
 if(fabs(eta)>0.9 && fabs(eta)<=1.2){
  if(pt>20 && pt<=25) musf=0.9953563700599016; // stat 0.0032906573832472705  syst 0.0005738209578508946 
  if(pt>25 && pt<=30) musf=0.9958066672787669; // stat 0.0016018795511927857 syst 0.0007864318418559466 
  if(pt>30 && pt<=40) musf=0.9976864595912653; // stat 0.00042385521315222807 syst 1.7519913375327746e-05  
  if(pt>40 && pt<=50) musf=0.9990643758399053; // stat 0.005770506626491954 syst 0.00010352489000910559 
  if(pt>50 && pt<=60) musf=0.9996724133222297; // stat 0.00035595587283767104 syst 8.368040978291978e-05  
  if(pt>60)musf=0.9999606370603018; // stat 0.0005612174449205558 syst 0.0001775859021951452 
 }
 if(fabs(eta)>1.2 && fabs(eta)<=2.1){
  if(pt>20 && pt<=25) musf=1.0133215397660384; //stat 0.0014374908292117512 syst 0.0010623826366502446  
  if(pt>25 && pt<=30) musf=1.0067858969024923; // stat 0.0008055497633813406 syst 0.0006414469468063717  
  if(pt>30 && pt<=40) musf=1.0020695104449462; //stat 0.0002351337627393239 syst 0.00017717041081786712 
  if(pt>40 && pt<=50) musf=1.0007060682634246; // stat 8.920118397517922e-05 syst 2.148581478604597e-05 
  if(pt>50 && pt<=60) musf=1.0004354208637907; // stat 0.00021781099981016557 syst 3.7112311166975304e-05 
  if(pt>60)musf=1.0002663898130457; // stat 0.00036988199644369217 syst 5.846133038844542e-05 
 }
 if(fabs(eta)>2.1 && fabs(eta)<=2.4){
  if(pt>20 && pt<=25) musf=1.027556905914061; // stat 0.002277534192552351 syst 0.0008986247456337133 
  if(pt>25 && pt<=30) musf=1.0143379791477725; // stat 0.0012908918832984988 && 0.0008195965444879856 
  if(pt>30 && pt<=40) musf=1.0054419865929765; // stat 0.00040019495324649626 syst 0.0007217335869673098 
  if(pt>40 && pt<=50) musf=1.0016460223436592; // stat 0.00019826487775344374 syst 4.880342247065058e-05 
  if(pt>50 && pt<=60) musf=1.0009981450462042; // stat 0.0005033796400527971 syst 0.00011776242980718527 
  if(pt>60 )musf=1.001493044021551; // stat 0.0009083825758175378 syst 0.0009244158331428465
 }

 return musf;
}

double get_wgtlumi(string FileName){
 double wgt=1;

  
   //xsec in pb

 // CHECKED for 2017 OK!! 
 
 if(FileName.find("TT") != std::string::npos) wgt=88.29/64310000;
 if(FileName.find("DY") != std::string::npos) wgt=6077./100194597;
 if(FileName.find("_ST_") != std::string::npos)  wgt=32.64/9598000;
 if(FileName.find("_SaT_") != std::string::npos) wgt=32.7/7623000;
 if(FileName.find("WW") != std::string::npos) wgt=118.7/7850000;
 if(FileName.find("WZ") != std::string::npos) wgt=47.13/3885000;
 if(FileName.find("ZZ") != std::string::npos) wgt=16.523/1979000;
 if(FileName.find("WJetsHT70To100") != std::string::npos) wgt=1563.32/28084244;
 if(FileName.find("WJetsHT100To200") != std::string::npos) wgt=1628.66/29521158;
 if(FileName.find("WJetsHT200To400") != std::string::npos) wgt=493.559/25468933;
 if(FileName.find("WJetsHT400To600") != std::string::npos) wgt=69.5508/5932701;
 if(FileName.find("WJetsHT600To800") != std::string::npos) wgt=15.5727/19771294;
 if(FileName.find("WJetsHT800To1200") != std::string::npos) wgt=6.49286/8402687;
 if(FileName.find("WJetsHT1200To2500") != std::string::npos) wgt=1.29954/7633949;
 if(FileName.find("WJetsHT2500ToInf") != std::string::npos) wgt=0.00968121/3273980;
 if(FileName.find("WJets_") != std::string::npos) wgt=63948.5/71026861;

 //muons
 
 if((FileName.find("mumujj_18_L13_M500") != std::string::npos)) wgt=5.7090e-03/100000;
 if((FileName.find("mumujj_18_L13_M1000") != std::string::npos)) wgt=2.8140e-03/100000;
 if((FileName.find("mumujj_18_L13_M2000") != std::string::npos)) wgt=0.82140e-03/100000;
 if((FileName.find("mumujj_18_L13_M5000") != std::string::npos)) wgt=0.014250e-03/98500;
 if((FileName.find("mumujj_18_L13_M8000") != std::string::npos)) wgt=0.000091350e-03/91350;

 //electrons
 
 if((FileName.find("eejj_18_L13_M500") != std::string::npos)) wgt=5.7090e-03/100000;
 if((FileName.find("eejj_18_L13_M1000") != std::string::npos)) wgt=2.8140e-03/100000;
 if((FileName.find("eejj_18_L13_M2000") != std::string::npos)) wgt=0.82140e-03/100000;
 if((FileName.find("eejj_18_L13_M5000") != std::string::npos)) wgt=0.014250e-03/100900;
 if((FileName.find("eejj_18_L13_M8000") != std::string::npos)) wgt=0.000091350e-03/90273;
 

 return wgt;
 }
