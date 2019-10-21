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
double elesf(double eta, double pt);
double musf_trigger(double eta,double pt);
double musf_ID(double eta, double pt);
double musf_iso(double eta, double pt);
double get_wgtlumi(string FileName);

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


void  filename_(const char*  Input = "", const char*  Output =""){

  Input = "inputFile";
  Output = "outputFile"; 
  TFile *oldfile = TFile::Open(Input);
  TTree *readingtree = new TTree("readingtree","readingtree"); readingtree = (TTree*) oldfile->Get("TNT/BOOM");
  /////
  //   Variables to read
  /////
  //Trigger
  //int rHLT_Ele27_eta2p1_WPLoose_Gsf; rHLT_Ele27_eta2p1_WPLoose_Gsf = 0; TBranch* b_rHLT_Ele27_eta2p1_WPLoose_Gsf = 0; readingtree->SetBranchAddress("HLT_Ele27_eta2p1_WPLoose_Gsf",&rHLT_Ele27_eta2p1_WPLoose_Gsf,&b_rHLT_Ele27_eta2p1_WPLoose_Gsf);
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
    
   TFile *newfile = new TFile(Output,"recreate");
   TTree* newtree = new TTree("BOOM","BOOM");
   newtree->SetMaxTreeSize(99000000000);
   /////
   //   New variables
   /////
   //Trigger:
  //int HLT_Ele27_eta2p1_WPLoose_Gsf; newtree->Branch("HLT_Ele27_eta2p1_WPLoose_Gsf",&HLT_Ele27_eta2p1_WPLoose_Gsf);
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
 
   double numOfHighptMu; newtree->Branch("numOfHighptMu",&numOfHighptMu);
   double numOfLooseMu; newtree->Branch("numOfLooseMu",&numOfLooseMu);
   double numOfMediumMu; newtree->Branch("numOfMediumMu",&numOfMediumMu);
   double numOfTightMu; newtree->Branch("numOfTightMu",&numOfTightMu);


   double numOfHighptEle; newtree->Branch("numOfHighptEle",&numOfHighptEle);
   double numOfLooseEle; newtree->Branch("numOfLooseEle",&numOfLooseEle);
   double numOfMediumEle; newtree->Branch("numOfMediumEle",&numOfMediumEle);
   double numOfTightEle; newtree->Branch("numOfTightEle",&numOfTightEle);
   double numOfVetoEle; newtree->Branch("numOfVetoEle",&numOfVetoEle);

   double numOfJets; newtree->Branch("numOfJets",&numOfJets); 
   double numOfJets_L; newtree->Branch("numOfJets_L",&numOfJets_L);
   double numOfJets_T; newtree->Branch("numOfJets_T",&numOfJets_T);
   double numOfJets_TLV; newtree->Branch("numOfJets_TLV",&numOfJets_TLV);
   double numOfBoostedJets; newtree->Branch("numOfBoostedJets",&numOfBoostedJets);
   double numOfBoostedJets_L; newtree->Branch("numOfBoostedJets_L",&numOfBoostedJets_L);
   double numOfBoostedJets_T; newtree->Branch("numOfBoostedJets_T",&numOfBoostedJets_T);
   double numOfBoostedJets_TLV; newtree->Branch("numOfBoostedJets_TLV",&numOfBoostedJets_TLV); 
   
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
   //Boosted Jet2 kinematics:
   double BoostedJet2_pt; newtree->Branch("BoostedJet2_pt",&BoostedJet2_pt);
   double BoostedJet2_eta; newtree->Branch("BoostedJet2_eta",&BoostedJet2_eta);
   double BoostedJet2_phi; newtree->Branch("BoostedJet2_phi",&BoostedJet2_phi);
   double BoostedJet2_energy; newtree->Branch("BoostedJet2_energy",&BoostedJet2_energy);
   double BoostedJet2_nJets; newtree->Branch("BoostedJet2_nJets",&BoostedJet2_nJets);
   //Masses:
   double M_ele1ele2Bjet1; newtree->Branch("M_ele1ele2Bjet1",&M_ele1ele2Bjet1);  
   double M_ele1ele2; newtree->Branch("M_ele1ele2",&M_ele1ele2);
   double M_elemu; newtree->Branch("M_elemu",&M_elemu);
   double M_elemuBjet1; newtree->Branch("M_elemuBjet1",&M_elemuBjet1);
   double M_mu1mu2; newtree->Branch("M_mu1mu2",&M_mu1mu2);
   double M_mu1mu2Bjet1; newtree->Branch("M_mu1mu2Bjet1",&M_mu1mu2Bjet1);   
   double S_T_BJ; newtree->Branch("S_T_BJ",&S_T_BJ);
   double S_T_jj; newtree->Branch("S_T_jj",&S_T_jj);
   double M_leplep; newtree->Branch("M_leplep",&M_leplep);
   double M_leplepBjet; newtree->Branch("M_leplepBjet",&M_leplepBjet);
   double M_lep2Bjet; newtree->Branch("M_lep2Bjet",&M_lep2Bjet);  
   double M_leplepBjetBjet; newtree->Branch("M_leplepBjetBjet",&M_leplepBjetBjet);

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
   //Event type
   //int evt_type; newtree->Branch("evt_type",&evt_type);
   double eejj_l; newtree->Branch("eejj_l",&eejj_l);
   double emujj_l; newtree->Branch("emujj_l",&emujj_l);
   double mumujj_l; newtree->Branch("mumujj_l",&mumujj_l);
   double muejj_l; newtree->Branch("muejj_l",&muejj_l);
   double SRe; newtree->Branch("SRe",&SRe);
   double TRe; newtree->Branch("TRe",&TRe);
   double SRmu; newtree->Branch("SRmu",&SRmu);
   double TRmu; newtree->Branch("TRmu",&TRmu);
   double DYRe; newtree->Branch("DYRe",&DYRe);
   double DYRmu; newtree->Branch("DYRmu",&DYRmu);
    
 
   //reco 4-vectors:
   TLorentzVector Ele1(0,0,0,0);
   TLorentzVector Ele2(0,0,0,0);
   TLorentzVector Muon1(0,0,0,0);
   TLorentzVector Muon2(0,0,0,0);
   TLorentzVector BoostedJet1(0,0,0,0);
   TLorentzVector BoostedJet2(0,0,0,0);
  
   int nen = nentries;
   if(nentries==-1) nen = readingtree->GetEntries();
   cout << nen << endl;
   for(int en=0; en<nen; en++){
    //Read branches
    //Trigger:
    
    //b_rHLT_Ele27_eta2p1_WPLoose_Gsf->GetEntry(en);
    //b_rHLT_DoubleEle33_CaloIdL_GsfTrkIdVL->GetEntry(en);
    b_rHLT_Ele115_CaloIdVT_GsfTrkIdT->GetEntry(en);
    b_rHLT_Mu50->GetEntry(en);
    
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
    //HLT_Ele27_eta2p1_WPLoose_Gsf = -999;
    //HLT_DoubleEle33_CaloIdL_GsfTrkIdVL = -999;
    HLT_Ele115_CaloIdVT_GsfTrkIdT = -999;
    HLT_TkMu50 = -999;
    HLT_Mu50 = -999;
    HLT_TkMu100 = -999;
    HLT_OldMu100 = -999;

    PUWeight = -999; nBestVtx = -999; trueInteractions = -999; lumi_wgt = -999;
    Met_type1PF_pt = -999;

    numOfHighptMu=0; numOfLooseMu=0; numOfMediumMu=0; numOfTightMu=0;

    numOfHighptEle=0; numOfLooseEle=0; numOfMediumEle=0; numOfTightEle=0; numOfVetoEle=0;


    numOfJets_L=0; numOfJets_T=0; numOfJets_TLV=0;
    numOfBoostedJets_L=0; numOfBoostedJets_T=0; numOfBoostedJets_TLV=0; 

    Ele1_pt=-999;  Ele1_eta=-999; Ele1_phi=-999; Ele1_energy=-999; Ele1_p=-999; Ele1_px=-999; Ele1_py=-999; Ele1_pz=-999;
    Ele2_pt=-999; Ele2_eta=-999; Ele2_phi=-999; Ele2_energy=-999; Ele2_p=-999; Ele2_px=-999; Ele2_py=-999; Ele2_pz=-999;
    Muon1_pt=-999;  Muon1_eta=-999; Muon1_phi=-999; Muon1_energy=-999; Muon1_p=-999; Muon1_px=-999; Muon1_py=-999; Muon1_pz=-999;
    Muon2_pt=-999;  Muon2_eta=-999; Muon2_phi=-999; Muon2_energy=-999; Muon2_p=-999; Muon2_px=-999; Muon2_py=-999; Muon2_pz=-999;
    BoostedJet1_pt=-999; BoostedJet1_eta=-999; BoostedJet1_phi=-999; BoostedJet1_energy=-999;
    BoostedJet1_nJets=-999;
    BoostedJet2_pt=-999; BoostedJet2_eta=-999; BoostedJet2_phi=-999; BoostedJet2_energy=-999;
    BoostedJet2_nJets=-999;


      
    M_ele1ele2Bjet1 = -999;  
    M_ele1ele2 = -999; M_elemu = -999; M_elemuBjet1 = -999; M_mu1mu2 = -999; M_mu1mu2Bjet1 = -999;
    S_T_BJ = -999; S_T_jj = -999;
    M_leplep = -999; M_leplepBjet = -999; M_leplepBjetBjet = -999;
    M_lep2Bjet = -999;

    musf_trigger_mu1 = -999; musf_ID_mu1 = -999; musf_iso_mu1 = -999; musf_tot_mu1 = -999;
    musf_trigger_mu2 = -999; musf_ID_mu2 = -999; musf_iso_mu2 = -999; musf_tot_mu2 = -999;
    elesf_ele1 = -999; elesf_ele2 = -999; lepsf_evt = -999; 
    //evt_type = -999;
    eejj_l = 0; emujj_l = 0; mumujj_l = 0; muejj_l = 0;
    SRe = 0; TRe = 0; SRmu = 0; TRmu = 0; DYRe = 0; DYRmu = 0;


    
   //HLT_Ele27_eta2p1_WPLoose_Gsf = rHLT_Ele27_eta2p1_WPLoose_Gsf;
   //HLT_DoubleEle33_CaloIdL_GsfTrkIdVL = rHLT_DoubleEle33_CaloIdL_GsfTrkIdVL;
   HLT_Ele115_CaloIdVT_GsfTrkIdT = rHLT_Ele115_CaloIdVT_GsfTrkIdT;
   HLT_Mu50 = rHLT_Mu50;
   HLT_TkMu50 = rHLT_TkMu50;
   HLT_OldMu100 = rHLT_OldMu100;
   HLT_TkMu100 = rHLT_TkMu100;

    PUWeight = rPUWeight;
    //trueInteractions = rtrueInteractions;
    if(rtrueInteractions > 0) trueInteractions = (double)rtrueInteractions;
    nBestVtx = rnBestVtx;
    PileupWeight = CalculatePileupWeight(trueInteractions);
    lumi_wgt = get_wgtlumi(Output);
   
   

   for(uint mu_en = 0; mu_en<rMuon_pt->size(); mu_en++){
    if( rMuon_pt->at(mu_en)>20 && fabs(rMuon_eta->at(mu_en))<2.4){
     if(rMuon_loose->at(mu_en)==1 && rMuon_TrackerIso->at(mu_en)<0.1) numOfLooseMu++;
     if(rMuon_medium->at(mu_en)==1 && rMuon_TrackerIso->at(mu_en)<0.1) numOfMediumMu++;
     if(rMuon_tight->at(mu_en)==1 && rMuon_TrackerIso->at(mu_en)<0.1) numOfTightMu++;
     if(rMuon_isHighPt->at(mu_en)==1 && rMuon_TrackerIso->at(mu_en)<0.1){
      numOfHighptMu++;
      Muon_pt->push_back(rMuon_pt->at(mu_en));
      Muon_eta->push_back(rMuon_eta->at(mu_en));
      Muon_phi->push_back(rMuon_phi->at(mu_en));
      Muon_p->push_back(rMuon_p->at(mu_en));
      Muon_px->push_back(rMuon_px->at(mu_en));
      Muon_py->push_back(rMuon_py->at(mu_en));
      Muon_pz->push_back(rMuon_pz->at(mu_en));
      Muon_energy->push_back(rMuon_energy->at(mu_en));
      Muon_charge->push_back(rMuon_charge->at(mu_en));
      Muon_trackIso->push_back(rMuon_trackIso->at(mu_en));
      Muon_TrackerIso->push_back(rMuon_TrackerIso->at(mu_en));
      Muon_relIsoDeltaBetaR03->push_back(rMuon_relIsoDeltaBetaR03->at(mu_en));
      Muon_relIsoDeltaBetaR04->push_back(rMuon_relIsoDeltaBetaR04->at(mu_en));
      Muon_isHighPt->push_back(rMuon_isHighPt->at(mu_en));
      Muon_loose->push_back(rMuon_loose->at(mu_en));
      Muon_medium->push_back(rMuon_medium->at(mu_en));
      Muon_tight->push_back(rMuon_tight->at(mu_en));
      
     }
    }
   }    


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
     }
    }
   }


   
   Met_type1PF_pt = rMet_type1PF_pt;

   if(numOfHighptEle==2 && patElectron_pt->at(0)>35 && patElectron_pt->at(1)>35 && numOfLooseMu==0) eejj_l=1;
   if(numOfHighptEle==1 && patElectron_pt->at(0)>35 && numOfHighptMu==1 &&  Muon_pt->at(0)>35) emujj_l=1;
   if(numOfHighptEle==1 && patElectron_pt->at(0)>30 && numOfHighptMu==1 &&  Muon_pt->at(0)>30) muejj_l=1;
   if(numOfHighptMu==2 && Muon_pt->at(0)>30 && Muon_pt->at(1)>30 && numOfVetoEle==0) mumujj_l=1;
   
   if(!((eejj_l==1 || emujj_l==1 || muejj_l==1 || mumujj_l==1))) continue;


   int count;
   //Jet selection: 
   bool Jet_isIDL=false;
   bool Jet_isIDT=false;
   bool Jet_isIDTLV=false;
   //bool Jet_isID=false;
   int countJets=0;
   int countJets_L=0;
   int countJets_T=0;
   int countJets_TLV=0;
   for(uint jet_en = 0; jet_en<rJet_pt->size(); jet_en++){
    //Jet corrections:
    double jet_pt = rJet_Uncorr_pt->at(jet_en)*rJet_JesSF->at(jet_en)*rJet_JerSF->at(jet_en);
    double jet_energy = rJet_energy->at(jet_en)*rJet_Uncorr_pt->at(jet_en)/rJet_pt->at(jet_en)*rJet_JesSF->at(jet_en)*rJet_JerSF->at(jet_en);
    TLorentzVector JetCorr(0,0,0,0); JetCorr.SetPtEtaPhiE(jet_pt, rJet_eta->at(jet_en), rJet_phi->at(jet_en), jet_energy);
    //cout << "pt dei jet prima della sel: " <<JetCorr.Pt() << endl;
    //Jet ID:
    Jet_isIDL = JetID_Loose(JetCorr.Pt(),fabs(JetCorr.Eta()),rJet_neutralHadEnergyFraction->at(jet_en),
               rJet_neutralEmEnergyFraction->at(jet_en),rJet_numberOfConstituents->at(jet_en),rJet_muonEnergyFraction->at(jet_en),
               rJet_chargedHadronEnergyFraction->at(jet_en),rJet_chargedMultiplicity->at(jet_en),rJet_chargedEmEnergyFraction->at(jet_en));
    Jet_isIDT = JetID_Tight(JetCorr.Pt(),fabs(JetCorr.Eta()),rJet_neutralHadEnergyFraction->at(jet_en),
               rJet_neutralEmEnergyFraction->at(jet_en),rJet_numberOfConstituents->at(jet_en),rJet_muonEnergyFraction->at(jet_en),
               rJet_chargedHadronEnergyFraction->at(jet_en),rJet_chargedMultiplicity->at(jet_en),rJet_chargedEmEnergyFraction->at(jet_en));
    Jet_isIDTLV = JetID_TightLepVeto(JetCorr.Pt(),fabs(JetCorr.Eta()),rJet_neutralHadEnergyFraction->at(jet_en),
               rJet_neutralEmEnergyFraction->at(jet_en),rJet_numberOfConstituents->at(jet_en),rJet_muonEnergyFraction->at(jet_en),
               rJet_chargedHadronEnergyFraction->at(jet_en),rJet_chargedMultiplicity->at(jet_en),rJet_chargedEmEnergyFraction->at(jet_en));

    count = 0;
    if(Jet_isIDL==true){
     Jet_L->push_back(true);
     for(uint ele_en = 0; ele_en<patElectron_pt->size(); ele_en++){
      double DR_jetele = sqrt(pow(deltaPhi(patElectron_phi->at(ele_en),JetCorr.Pt()),2)+pow(patElectron_eta->at(ele_en)-JetCorr.Eta(),2) );
      double relPt = fabs(patElectron_pt->at(ele_en) - JetCorr.Pt())/JetCorr.Pt();
      if(DR_jetele<0.5 && patElectron_isPassHEEPId->at(ele_en)==1) count++;
     }
     if(count == 0){
      countJets_L++;
     }
    }
    else Jet_L->push_back(false);
    count = 0;
    if(Jet_isIDT==true){
     Jet_T->push_back(true);
     for(uint ele_en = 0; ele_en<patElectron_pt->size(); ele_en++){
      double DR_jetele = sqrt(pow(deltaPhi(patElectron_phi->at(ele_en),JetCorr.Pt()),2)+pow(patElectron_eta->at(ele_en)-JetCorr.Eta(),2) );
      double relPt = fabs(patElectron_pt->at(ele_en) - JetCorr.Pt())/JetCorr.Pt();
      if(DR_jetele<0.5 && patElectron_isPassHEEPId->at(ele_en)==1) count++;
     }
     if(count == 0){
      countJets_T++;
     }
    }
    else Jet_T->push_back(false); 
    count = 0;
    if(Jet_isIDTLV==true){
     Jet_TLV->push_back(true);
     for(uint ele_en = 0; ele_en<patElectron_pt->size(); ele_en++){
      double DR_jetele = sqrt(pow(deltaPhi(patElectron_phi->at(ele_en),JetCorr.Pt()),2)+pow(patElectron_eta->at(ele_en)-JetCorr.Eta(),2) );
      double relPt = fabs(patElectron_pt->at(ele_en) - JetCorr.Pt())/JetCorr.Pt();
      if(DR_jetele<0.5 && patElectron_isPassHEEPId->at(ele_en)==1) count++;
     }
     if(count == 0){
      countJets_TLV++;
     }
    }
    else Jet_TLV->push_back(false);  
    
    
    
   
    

    //Jet_isID = JetID_Loose(JetCorr.Pt(),fabs(JetCorr.Eta()),rJet_neutralHadEnergyFraction->at(jet_en),
      //         rJet_neutralEmEnergyFraction->at(jet_en),rJet_numberOfConstituents->at(jet_en),rJet_muonEnergyFraction->at(jet_en),
        //       rJet_chargedHadronEnergyFraction->at(jet_en),rJet_chargedMultiplicity->at(jet_en),rJet_chargedEmEnergyFraction->at(jet_en));
    // cout << "Passa il jet: " <<Jet_isID << endl;
    count = 0;
    if(Jet_isIDT==true){
     //cout << "pt dei jet dopo la sel: " <<JetCorr.Pt() << endl;
     //Jet cleaning: 
     for(uint ele_en = 0; ele_en<patElectron_pt->size(); ele_en++){
      double DR_jetele = sqrt(pow(deltaPhi(patElectron_phi->at(ele_en),JetCorr.Pt()),2)+pow(patElectron_eta->at(ele_en)-JetCorr.Eta(),2) );
      double relPt = fabs(patElectron_pt->at(ele_en) - JetCorr.Pt())/JetCorr.Pt();
      if(DR_jetele<0.5 && patElectron_isPassHEEPId->at(ele_en)==1) count++;
    }
     for(uint mu_en = 0; mu_en<Muon_pt->size(); mu_en++){
      double DR_jetmu = sqrt(pow(deltaPhi(Muon_phi->at(mu_en),JetCorr.Pt()),2)+pow(Muon_eta->at(mu_en)-JetCorr.Eta(),2) );
      double relPt = fabs(Muon_pt->at(mu_en) - JetCorr.Pt())/JetCorr.Pt();
      if(DR_jetmu<0.5 && Muon_isHighPt->at(mu_en)==1) count++;
     }
     if(count == 0 && fabs(JetCorr.Eta())<2.4){
      countJets++;  
      Jet_pt->push_back(JetCorr.Pt());
      Jet_eta->push_back(fabs(JetCorr.Eta()));
      Jet_phi->push_back(JetCorr.Phi());
      Jet_px->push_back(rJet_px->at(jet_en));
      Jet_py->push_back(rJet_py->at(jet_en));
      Jet_pz->push_back(rJet_pz->at(jet_en));
      Jet_energy->push_back(rJet_energy->at(jet_en));
      Jet_mass->push_back(rJet_mass->at(jet_en));
      Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags->push_back(rJet_pfCombinedInclusiveSecondaryVertexV2BJetTags->at(jet_en));
      Jet_pfCombinedMVAV2BJetTags->push_back(rJet_pfCombinedMVAV2BJetTags->at(jet_en));
      //Jet_nBoostedJets->push_back(0);
     }
    }
   }
   numOfJets=countJets;
   numOfJets_L=countJets_L;
   numOfJets_T=countJets_T;
   numOfJets_TLV=countJets_TLV;

   bool BoostedJet_isIDL=false;
   bool BoostedJet_isIDT=false;
   bool BoostedJet_isIDTLV=false;
   //bool BoostedJet_isID=false;
   int countBoostedJets=0;
   int countBoostedJets_L=0;
   int countBoostedJets_T=0;
   int countBoostedJets_TLV=0;
   for(uint jet_en = 0; jet_en<rBoostedJet_pt->size(); jet_en++){
    //BJet corrections:
    double jet_pt = rBoostedJet_Uncorr_pt->at(jet_en)*rBoostedJet_JesSF->at(jet_en);
    double jet_energy=rBoostedJet_energy->at(jet_en)*rBoostedJet_Uncorr_pt->at(jet_en)/rBoostedJet_pt->at(jet_en)*rBoostedJet_JesSF->at(jet_en);
    TLorentzVector JetCorr(0,0,0,0); JetCorr.SetPtEtaPhiE(jet_pt, rBoostedJet_eta->at(jet_en), rBoostedJet_phi->at(jet_en), jet_energy);
    //BJet ID:
    BoostedJet_isIDL = BoostedJetID_Loose(JetCorr.Pt(),fabs(JetCorr.Eta()),rBoostedJet_neutralHadEnergyFraction->at(jet_en),
    rBoostedJet_neutralEmEmEnergyFraction->at(jet_en),rBoostedJet_numberOfConstituents->at(jet_en),rBoostedJet_muonEnergyFraction->at(jet_en),
    rBoostedJet_chargedHadronEnergyFraction->at(jet_en),rBoostedJet_chargedMultiplicity->at(jet_en),
    rBoostedJet_chargedEmEnergyFraction->at(jet_en));
    BoostedJet_isIDT = BoostedJetID_Tight(JetCorr.Pt(),fabs(JetCorr.Eta()),rBoostedJet_neutralHadEnergyFraction->at(jet_en),
    rBoostedJet_neutralEmEmEnergyFraction->at(jet_en),rBoostedJet_numberOfConstituents->at(jet_en),rBoostedJet_muonEnergyFraction->at(jet_en),
    rBoostedJet_chargedHadronEnergyFraction->at(jet_en),rBoostedJet_chargedMultiplicity->at(jet_en),
    rBoostedJet_chargedEmEnergyFraction->at(jet_en));
    BoostedJet_isIDTLV = BoostedJetID_TightLepVeto(JetCorr.Pt(),fabs(JetCorr.Eta()),rBoostedJet_neutralHadEnergyFraction->at(jet_en),
    rBoostedJet_neutralEmEmEnergyFraction->at(jet_en),rBoostedJet_numberOfConstituents->at(jet_en),rBoostedJet_muonEnergyFraction->at(jet_en),
    rBoostedJet_chargedHadronEnergyFraction->at(jet_en),rBoostedJet_chargedMultiplicity->at(jet_en),
    rBoostedJet_chargedEmEnergyFraction->at(jet_en));




    count = 0;
    if(BoostedJet_isIDL==true){
     BoostedJet_L->push_back(true);
     for(uint ele_en = 0; ele_en<patElectron_pt->size(); ele_en++){
      double DR_jetele = sqrt(pow(deltaPhi(patElectron_phi->at(ele_en),JetCorr.Phi()),2)+pow(patElectron_eta->at(ele_en)-JetCorr.Eta(),2) );
      double relPt = fabs(patElectron_pt->at(ele_en) - JetCorr.Pt())/JetCorr.Pt();
      if(DR_jetele<0.5 && patElectron_isPassHEEPId->at(ele_en)==1) count++;
     }
     for(uint mu_en = 0; mu_en<Muon_pt->size(); mu_en++){
      double DR_jetmu = sqrt(pow(deltaPhi(Muon_phi->at(mu_en),JetCorr.Phi()),2)+pow(Muon_eta->at(mu_en)-JetCorr.Eta(),2) );
      double relPt = fabs(Muon_pt->at(mu_en) - JetCorr.Pt())/JetCorr.Pt();
      if(DR_jetmu<0.5 && Muon_isHighPt->at(mu_en)==1) count++;
     }
     if(count==0){
      countBoostedJets_L++;
     }
    }
    else BoostedJet_L->push_back(false);
    count = 0;
    if(BoostedJet_isIDT==true){
     BoostedJet_T->push_back(true);
     for(uint ele_en = 0; ele_en<patElectron_pt->size(); ele_en++){
      double DR_jetele = sqrt(pow(deltaPhi(patElectron_phi->at(ele_en),JetCorr.Phi()),2)+pow(patElectron_eta->at(ele_en)-JetCorr.Eta(),2) );
      double relPt = fabs(patElectron_pt->at(ele_en) - JetCorr.Pt())/JetCorr.Pt();
      if(DR_jetele<0.5 && patElectron_isPassHEEPId->at(ele_en)==1) count++;
     }
     for(uint mu_en = 0; mu_en<Muon_pt->size(); mu_en++){
      double DR_jetmu = sqrt(pow(deltaPhi(Muon_phi->at(mu_en),JetCorr.Phi()),2)+pow(Muon_eta->at(mu_en)-JetCorr.Eta(),2) );
      double relPt = fabs(Muon_pt->at(mu_en) - JetCorr.Pt())/JetCorr.Pt();
      if(DR_jetmu<0.5 && Muon_isHighPt->at(mu_en)==1) count++;
     }
     if(count==0){
      countBoostedJets_T++;
     }
    }
    else BoostedJet_T->push_back(false);
    count = 0;
    if(BoostedJet_isIDTLV==true){
     BoostedJet_TLV->push_back(true);
     for(uint ele_en = 0; ele_en<patElectron_pt->size(); ele_en++){
      double DR_jetele = sqrt(pow(deltaPhi(patElectron_phi->at(ele_en),JetCorr.Phi()),2)+pow(patElectron_eta->at(ele_en)-JetCorr.Eta(),2) );
      double relPt = fabs(patElectron_pt->at(ele_en) - JetCorr.Pt())/JetCorr.Pt();
      if(DR_jetele<0.5 && patElectron_isPassHEEPId->at(ele_en)==1) count++;
     }
     for(uint mu_en = 0; mu_en<Muon_pt->size(); mu_en++){
      double DR_jetmu = sqrt(pow(deltaPhi(Muon_phi->at(mu_en),JetCorr.Phi()),2)+pow(Muon_eta->at(mu_en)-JetCorr.Eta(),2) );
      double relPt = fabs(Muon_pt->at(mu_en) - JetCorr.Pt())/JetCorr.Pt();
      if(DR_jetmu<0.5 && Muon_isHighPt->at(mu_en)==1) count++;
     }
     if(count==0){
      countBoostedJets_TLV++;
     }
    }
    else BoostedJet_TLV->push_back(false);

    
   
    // BoostedJet_isID = BoostedJetID_Loose(JetCorr.Pt(),fabs(JetCorr.Eta()),rBoostedJet_neutralHadEnergyFraction->at(jet_en),
    //rBoostedJet_neutralEmEmEnergyFraction->at(jet_en),rBoostedJet_numberOfConstituents->at(jet_en),rBoostedJet_muonEnergyFraction->at(jet_en),
    //rBoostedJet_chargedHadronEnergyFraction->at(jet_en),rBoostedJet_chargedMultiplicity->at(jet_en),
    //rBoostedJet_chargedEmEnergyFraction->at(jet_en));
    //cout << "Passa il boostedjet: " <<Jet_isID << endl;

    count = 0;
    if(BoostedJet_isIDT==true){
     //BJet cleaning:
     for(uint ele_en = 0; ele_en<patElectron_pt->size(); ele_en++){
      double DR_jetele = sqrt(pow(deltaPhi(patElectron_phi->at(ele_en),JetCorr.Phi()),2)+pow(patElectron_eta->at(ele_en)-JetCorr.Eta(),2) );
      double relPt = fabs(patElectron_pt->at(ele_en) - JetCorr.Pt())/JetCorr.Pt();
      if(DR_jetele<0.5 && patElectron_isPassHEEPId->at(ele_en)==1) count++;
     }
     for(uint mu_en = 0; mu_en<Muon_pt->size(); mu_en++){
      double DR_jetmu = sqrt(pow(deltaPhi(Muon_phi->at(mu_en),JetCorr.Phi()),2)+pow(Muon_eta->at(mu_en)-JetCorr.Eta(),2) );
      double relPt = fabs(Muon_pt->at(mu_en) - JetCorr.Pt())/JetCorr.Pt();
      if(DR_jetmu<0.5 && Muon_isHighPt->at(mu_en)==1) count++;
     }
     if(count == 0 && fabs(JetCorr.Eta())<2.4){
      countBoostedJets++;
      BoostedJet_pt->push_back(JetCorr.Pt());
      BoostedJet_eta->push_back(JetCorr.Eta());
      BoostedJet_phi->push_back(JetCorr.Phi());
      BoostedJet_energy->push_back(rBoostedJet_energy->at(jet_en));
      BoostedJet_mass->push_back(rBoostedJet_mass->at(jet_en));
      BoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags->push_back(rBoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags->at(jet_en));      
      //BoostedJet_nJets->push_back(0);
     }
    }
   }
   numOfBoostedJets=countBoostedJets;
   numOfBoostedJets_L=countBoostedJets_L;
   numOfBoostedJets_T=countBoostedJets_T;
   numOfBoostedJets_TLV=countBoostedJets_TLV;

   //if(!(numOfBoostedJets_T>=1)) continue;

   //Iso muon counting
    IsoTracker_L=0; IsoTracker_T=0; IsoTrack_L=0; IsoTrack_T=0; IsoPF_L=0; IsoPF_T=0;
    for(uint mu_en = 0; mu_en<Muon_pt->size(); mu_en++){
     if(Muon_TrackerIso->at(mu_en)<0.10) IsoTracker_L++;
     if(Muon_TrackerIso->at(mu_en)<0.05) IsoTracker_T++;
     if(Muon_trackIso->at(mu_en)<0.10) IsoTrack_L++; 
     if(Muon_trackIso->at(mu_en)<0.05) IsoTrack_T++;
     if(Muon_relIsoDeltaBetaR04->at(mu_en)<0.20) IsoPF_L++;
     if(Muon_relIsoDeltaBetaR04->at(mu_en)<0.12) IsoPF_T++;
    }
       

   for(uint i=0; i<Jet_pt->size(); i++){
    //Jet_nBoostedJets->at(i)=0;
    int JBJ_count=0;
    for(uint j=0; j<BoostedJet_pt->size(); j++){
    if(sqrt(pow(deltaPhi(Jet_phi->at(i), BoostedJet_phi->at(j)),2) + pow(Jet_eta->at(i)-BoostedJet_eta->at(j),2))<0.5)
     //Jet_nBoostedJets->at(i)++;
     JBJ_count++;
    }
    Jet_nBoostedJets->push_back(JBJ_count);
   }

   for(uint i=0; i<BoostedJet_pt->size(); i++){
    //BoostedJet_nJets->at(i)=0;
    int BJJ_count=0;
    for(uint j=0; j<Jet_pt->size(); j++){
    if(sqrt(pow(deltaPhi(BoostedJet_phi->at(i),Jet_phi->at(j)),2) + pow(BoostedJet_eta->at(i)-Jet_eta->at(j),2))<0.5)
     //BoostedJet_nJets->at(i)++;
     BJJ_count++;
    }
    BoostedJet_nJets->push_back(BJJ_count);
   }
   
    if(patElectron_pt->size()>0){
     Ele1_pt=patElectron_pt->at(0);
     Ele1_eta=patElectron_eta->at(0);
     Ele1_phi=patElectron_phi->at(0);
     Ele1_energy=patElectron_energy->at(0);
     Ele1_px=patElectron_px->at(0);
     Ele1_py=patElectron_py->at(0);
     Ele1_pz=patElectron_pz->at(0);
     Ele1_p=patElectron_p->at(0);
 
     Ele1.SetPtEtaPhiE(patElectron_pt->at(0), patElectron_eta->at(0), patElectron_phi->at(0), patElectron_energy->at(0));
   }
    if(patElectron_pt->size()>1){

     Ele2_pt=patElectron_pt->at(1);
     Ele2_eta=patElectron_eta->at(1);
     Ele2_phi=patElectron_phi->at(1);
     Ele2_energy=patElectron_energy->at(1);
     Ele2_px=patElectron_px->at(1);
     Ele2_py=patElectron_py->at(1);
     Ele2_pz=patElectron_pz->at(1);
     Ele2_p=patElectron_p->at(1);
   
     Ele2.SetPtEtaPhiE(patElectron_pt->at(1), patElectron_eta->at(1), patElectron_phi->at(1), patElectron_energy->at(1));
    }


    if(Muon_pt->size()>0){
     Muon1_pt=Muon_pt->at(0);
     Muon1_eta=Muon_eta->at(0);
     Muon1_phi=Muon_phi->at(0);
     Muon1_energy=Muon_energy->at(0);
     Muon1_px=Muon_px->at(0);
     Muon1_py=Muon_py->at(0);
     Muon1_pz=Muon_pz->at(0);
     Muon1_p=Muon_p->at(0);

     Muon1.SetPtEtaPhiE(Muon_pt->at(0), Muon_eta->at(0), Muon_phi->at(0), Muon_energy->at(0));
   }

    if(Muon_pt->size()>1){

     Muon2_pt=Muon_pt->at(1);
     Muon2_eta=Muon_eta->at(1);
     Muon2_phi=Muon_phi->at(1);
     Muon2_energy=Muon_energy->at(1);
     Muon2_px=Muon_px->at(1);
     Muon2_py=Muon_py->at(1);
     Muon2_pz=Muon_pz->at(1);
     Muon2_p=Muon_p->at(1);

     Muon2.SetPtEtaPhiE(Muon_pt->at(1), Muon_eta->at(1), Muon_phi->at(1), Muon_energy->at(1));
    }

    if(Jet_pt->size()>1){
     if(eejj_l==1){
      S_T_jj = Ele1_pt+Ele2_pt+Jet_pt->at(0)+Jet_pt->at(1);
     }
     if(mumujj_l==1){
      S_T_jj = Muon1_pt+Muon2_pt+Jet_pt->at(0)+Jet_pt->at(1);
     }
     if(emujj_l==1 || muejj_l==1){
      S_T_jj = Ele1_pt+Muon1_pt+Jet_pt->at(0)+Jet_pt->at(1);
     }
     
    }
    

    if(BoostedJet_pt->size()>0){

     BoostedJet1_pt=BoostedJet_pt->at(0);
     BoostedJet1_eta=BoostedJet_eta->at(0);
     BoostedJet1_phi=BoostedJet_phi->at(0);
     BoostedJet1_energy=BoostedJet_energy->at(0);
     BoostedJet1.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0), BoostedJet_energy->at(0));
     BoostedJet1_nJets=BoostedJet_nJets->at(0);
     BoostedJet1.SetPtEtaPhiE(BoostedJet_pt->at(0), BoostedJet_eta->at(0), BoostedJet_phi->at(0), BoostedJet_energy->at(0));

     if(eejj_l==1){
      M_ele1ele2Bjet1 = (Ele1 + Ele2 + BoostedJet1).M();
      M_leplepBjet=M_ele1ele2Bjet1;
      M_lep2Bjet = (Ele2 + BoostedJet1).M();
      S_T_BJ=Ele1_pt+Ele2_pt+BoostedJet1_pt;
     }
     if(mumujj_l==1){
      M_mu1mu2Bjet1 = (Muon1 + Muon2 + BoostedJet1).M();
      M_leplepBjet=M_mu1mu2Bjet1;
      M_lep2Bjet = (Muon2 + BoostedJet1).M();
      S_T_BJ=Muon1_pt+Muon2_pt+BoostedJet1_pt;
     }
     if(emujj_l==1 || muejj_l==1){
      M_elemuBjet1=(Ele1 + Muon1 + BoostedJet1).M();
      M_leplepBjet=M_elemuBjet1;
      if(patElectron_pt->at(0)>Muon_pt->at(0)){M_lep2Bjet = (Muon1 + BoostedJet1).M();}
      if(patElectron_pt->at(0)<Muon_pt->at(0)){M_lep2Bjet = (Ele1 + BoostedJet1).M();}
      S_T_BJ=Ele1_pt+Muon1_pt+BoostedJet1_pt;
     }
     
    }

    if(BoostedJet_pt->size()>2){

     BoostedJet2_pt=BoostedJet_pt->at(1);
     BoostedJet2_eta=BoostedJet_eta->at(1);
     BoostedJet2_phi=BoostedJet_phi->at(1);
     BoostedJet2_energy=BoostedJet_energy->at(1);
     BoostedJet2.SetPtEtaPhiE(BoostedJet_pt->at(1), BoostedJet_eta->at(1), BoostedJet_phi->at(1), BoostedJet_energy->at(1));
     BoostedJet2_nJets=BoostedJet_nJets->at(1);
     BoostedJet2.SetPtEtaPhiE(BoostedJet_pt->at(1), BoostedJet_eta->at(1), BoostedJet_phi->at(1), BoostedJet_energy->at(1));

     if(eejj_l==1){
      M_leplepBjetBjet = (Ele1 + Ele2 + BoostedJet1 + BoostedJet2).M();
     }
     if(mumujj_l==1){ 
      M_leplepBjetBjet = (Muon1 + Muon2 + BoostedJet1 + BoostedJet2).M();
     }
     if(emujj_l==1 || muejj_l==1){
      M_leplepBjetBjet=(Ele1 + Muon1 + BoostedJet1 + BoostedJet2).M();
     }




    }

    

    if(eejj_l==1){
     M_ele1ele2= (Ele1 + Ele2).M();
     M_leplep=M_ele1ele2;     
    }
    if(mumujj_l==1){
     M_mu1mu2= (Muon1 + Muon2).M();
     M_leplep=M_mu1mu2;
    }
    if(emujj_l==1 || muejj_l==1){
     //Muon1.SetPtEtaPhiE(Muon_pt->at(0), Muon_eta->at(0), Muon_phi->at(0), Muon_energy->at(0));
     M_elemu= (Ele1 + Muon1).M();
     M_leplep=M_elemu;
    }
 

   if(eejj_l==1){
    elesf_ele1=elesf(patElectron_eta->at(0), patElectron_pt->at(0));
    elesf_ele2=elesf(patElectron_eta->at(1), patElectron_pt->at(1));
    lepsf_evt=elesf_ele1*elesf_ele2;
   }
   if(emujj_l==1){
    elesf_ele1=elesf(patElectron_eta->at(0), patElectron_pt->at(0));
    //musf_trigger_mu1=musf_trigger(Muon_eta->at(0),Muon_pt->at(0));
    musf_ID_mu1=musf_ID(Muon_eta->at(0),Muon_pt->at(0));
    musf_iso_mu1=musf_iso(Muon_eta->at(0),Muon_pt->at(0));
    //musf_tot_mu1=musf_trigger_mu1*musf_ID_mu1*musf_iso_mu1;
    musf_tot_mu1=musf_ID_mu1*musf_iso_mu1;
    lepsf_evt=elesf_ele1*musf_tot_mu1;
    

   }
   if(muejj_l==1){
    elesf_ele1=elesf(patElectron_eta->at(0), patElectron_pt->at(0));
    musf_trigger_mu1=musf_trigger(Muon_eta->at(0),Muon_pt->at(0));
    musf_ID_mu1=musf_ID(Muon_eta->at(0),Muon_pt->at(0));
    musf_iso_mu1=musf_iso(Muon_eta->at(0),Muon_pt->at(0));
    musf_tot_mu1=musf_trigger_mu1*musf_ID_mu1*musf_iso_mu1;
    lepsf_evt=elesf_ele1*musf_tot_mu1;
   }
   if(mumujj_l==1){
    musf_trigger_mu1=musf_trigger(Muon_eta->at(0),Muon_pt->at(0));
    musf_ID_mu1=musf_ID(Muon_eta->at(0),Muon_pt->at(0));
    musf_iso_mu1=musf_iso(Muon_eta->at(0),Muon_pt->at(0));
    musf_tot_mu1=musf_trigger_mu1*musf_ID_mu1*musf_iso_mu1;

    //musf_trigger_mu2=musf_trigger(Muon_eta->at(1),Muon_pt->at(1));
    musf_ID_mu2=musf_ID(Muon_eta->at(1),Muon_pt->at(1));
    musf_iso_mu2=musf_iso(Muon_eta->at(1),Muon_pt->at(1));
    //musf_tot_mu2=musf_trigger_mu2*musf_ID_mu2*musf_iso_mu2;
    musf_tot_mu2=musf_ID_mu2*musf_iso_mu2;
 
    lepsf_evt=musf_tot_mu1*musf_tot_mu2;
   }

   if(HLT_Ele115_CaloIdVT_GsfTrkIdT==1 && numOfHighptEle==2 && patElectron_pt->at(0)>130 && patElectron_pt->at(1)>35 && numOfLooseMu==0 && numOfBoostedJets>=1 && M_leplep>300) SRe=1;
   if(HLT_Ele115_CaloIdVT_GsfTrkIdT==1 && numOfHighptEle==1 && patElectron_pt->at(0)>130 && numOfHighptMu==1 &&  Muon_pt->at(0)>35 && numOfBoostedJets>=1 && M_leplep>300) TRe=1;
   if(HLT_Mu50==1 && HLT_OldMu100==1 && HLT_TkMu50==1 && HLT_TkMu100==1 && numOfHighptMu==1 &&  Muon_pt->at(0)>53 && numOfHighptEle==1 && patElectron_pt->at(0)>30 && numOfBoostedJets>=1 && M_leplep>300) TRmu=1;
   if(HLT_Mu50==1 && HLT_OldMu100==1 && HLT_TkMu50==1 && HLT_TkMu100==1 && numOfHighptMu==2 && Muon_pt->at(0)>53 && Muon_pt->at(1)>30 && numOfVetoEle==0 && numOfBoostedJets>=1 && M_leplep>300) SRmu=1;
   if(HLT_Ele115_CaloIdVT_GsfTrkIdT==1 && numOfHighptEle==2 && patElectron_pt->at(0)>130 && patElectron_pt->at(1)>35 && numOfLooseMu==0 && numOfBoostedJets>=1) DYRe=1;
   if(HLT_Mu50==1 && HLT_OldMu100==1 && HLT_TkMu50==1 && HLT_TkMu100==1 && numOfHighptMu==2 && Muon_pt->at(0)>53 && Muon_pt->at(1)>30 && numOfVetoEle==0 && numOfBoostedJets>=1) DYRmu=1;


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

double elesf(double eta, double pt){
 double elesf=0;
 if (pt >= 10 && pt < 20){
  if (fabs(eta) >= 0. && fabs(eta) < 0.5) elesf=0.974953;
  if (fabs(eta) >= 0.5 && fabs(eta) < 1.) elesf=0.971215;
  if (fabs(eta) >=1 && fabs(eta) < 1.442) elesf=1.0307; 
  if (fabs(eta) >=1.442 && fabs(eta) < 1.566) elesf=1.25678;
  if (fabs(eta) >=1.566 && fabs(eta) < 2.) elesf=0.983351;
  if (fabs(eta) >=2. && fabs(eta) < 2.5) elesf=1.01998;    
 }
 if (pt >= 20 && pt < 45){
  if (fabs(eta) >= 0. && fabs(eta) < 0.5) elesf=0.98968;
  if (fabs(eta) >= 0.5 && fabs(eta) < 1.) elesf=0.99177;
  if (fabs(eta) >=1 && fabs(eta) < 1.442) elesf=0.987525;   
  if (fabs(eta) >=1.442 && fabs(eta) < 1.566) elesf=0.986095;
  if (fabs(eta) >=1.566 && fabs(eta) < 2.) elesf=0.986639;  
  if (fabs(eta) >=2. && fabs(eta) < 2.5) elesf=0.986556;
 }
 if (pt >= 45 && pt < 75){
  if (fabs(eta) >= 0. && fabs(eta) < 0.5) elesf=0.989754;
  if (fabs(eta) >= 0.5 && fabs(eta) < 1.) elesf=0.989775;
  if (fabs(eta) >=1 && fabs(eta) < 1.442) elesf=0.989691;
  if (fabs(eta) >=1.442 && fabs(eta) < 1.566) elesf=0.9867672;
  if (fabs(eta) >=1.566 && fabs(eta) < 2.) elesf=0.988764;
  if (fabs(eta) >=2. && fabs(eta) < 2.5) elesf=0.98768;
 }
 if (pt >= 75 && pt < 100){
  if (fabs(eta) >= 0. && fabs(eta) < 0.5) elesf=1.00305;
  if (fabs(eta) >= 0.5 && fabs(eta) < 1.) elesf=1.00815;
  if (fabs(eta) >=1 && fabs(eta) < 1.442) elesf=1.00818;
  if (fabs(eta) >=1.442 && fabs(eta) < 1.566) elesf=1.04381;
  if (fabs(eta) >=1.566 && fabs(eta) < 2.) elesf=1.01837;
  if (fabs(eta) >=2. && fabs(eta) < 2.5) elesf=1.00206;
 }
 if (pt >= 100){
  if (fabs(eta) >= 0. && fabs(eta) < 0.5) elesf=1.00304;
  if (fabs(eta) >= 0.5 && fabs(eta) < 1.) elesf=1.0061;
  if (fabs(eta) >=1 && fabs(eta) < 1.442) elesf=1.00718;
  if (fabs(eta) >=1.442 && fabs(eta) < 1.566) elesf=1.03668;
  if (fabs(eta) >=1.566 && fabs(eta) < 2.) elesf=0.997967;
  if (fabs(eta) >=2. && fabs(eta) < 2.5) elesf=0.983673;
 }
 return elesf;
 
//stat err 0.001 for both EB and EE
//syst err:
//  - barrel:
//      1% for pT < 90 GeV
//      1-3% linearly increasing for 90 GeV < pT < 1 TeV
//      3% for pT > 1 TeV
//  - endcap:
//      2% for pT < 90 GeV
//      2-5% linearly increasing for 90 GeV < pT < 300 GeV
//      5% for pT > 300 GeV 

}
double musf_trigger(double eta, double pt){
 double musf=0;
/* if(pt<60){
  if(fabs(eta)>=0.0 && fabs(eta)<0.9) musf=0.965465784072876;//0.9636659622192383;
  if(fabs(eta)>=0.9 && fabs(eta)<1.2) musf=0.9533324837684631;//1.0442723035812378;
  if(fabs(eta)>=1.2 && fabs(eta)<2.1) musf=0.9568167924880981;//0.9711147546768188;
  if(fabs(eta)>=2.1 && fabs(eta)<2.4) musf=0.8902276754379272;//1.0089114904403687;
 }
 if(pt>=60){
  if(fabs(eta)>=0.0 && fabs(eta)<0.9) musf=0.9708314538002014;//0.9502088427543640;
  if(fabs(eta)>=0.9 && fabs(eta)<1.2) musf=0.9528126120567322;//0.9564832448959351;
  if(fabs(eta)>=1.2 && fabs(eta)<2.1) musf=0.9712236523628235;//0.9529600739479065;
  if(fabs(eta)>=2.1 && fabs(eta)<2.4) musf=0.9417219758033752;//1.0511752367019653;
 }*/

 // Mu50_OT_OldMu100_OR_TkMu100_PtBins

 if(pt > 52. && pt <= 56.){
  if(fabs(eta)>= 0.0 && fabs(eta)<0.9) musf=0.9385219812393188; //err 0.0002566604294316861 
  if(fabs(eta)>= 0.9 && fabs(eta)<1.2) musf=0.9429171681404114; //err 0.0004323455043906205 
  if(fabs(eta)>= 1.2 && fabs(eta)<2.1) musf=0.9153958559036255; //err 0.0003371717180362242 
  if(fabs(eta)>= 2.1 && fabs(eta)<2.4) musf=0.801039457321167; //err 0.0010483845705795774
 }
 if(pt > 55. && pt <=60.){
  if(fabs(eta)>= 0.0 && fabs(eta)<0.9) musf=0.938785195350647; //err 0.0003512045613493856
  if(fabs(eta)>= 0.9 && fabs(eta)<1.2) musf=0.944566011428833; //err 0.0006453209717745792
  if(fabs(eta)>= 1.2 && fabs(eta)<2.1) musf=0.9197514057159424; //err 0.0004579121798908698 
  if(fabs(eta)>= 2.1 && fabs(eta)<2.4) musf=0.8250287771224976; //err 0.0014525323104812836
 }
 if(pt > 60. && pt <=120.){
  if(fabs(eta)>= 0.0 && fabs(eta)<0.9) musf=0.9373190402984619; //err 0.00031808216113278883
  if(fabs(eta)>= 0.9 && fabs(eta)<1.2) musf=0.9416107535362244; //err 0.0004590463319092091
  if(fabs(eta)>= 1.2 && fabs(eta)<2.1) musf=0.9216225147247314; //err 0.000365347265978311
  if(fabs(eta)>= 2.1 && fabs(eta)<2.4) musf=0.8385295867919922; //err 0.00112496967288113
 }

 if(pt > 120. && pt <=200.){
  if(fabs(eta)>= 0.0 && fabs(eta)<0.9) musf=0.9289411902427673; //err 0.0014673600305817596
  if(fabs(eta)>= 0.9 && fabs(eta)<1.2) musf=0.9340407252311707; //err 0.0019242274872617194
  if(fabs(eta)>= 1.2 && fabs(eta)<2.1) musf=0.9233274459838867; //err 0.0014746349755392736
  if(fabs(eta)>= 2.1 && fabs(eta)<2.4) musf=0.8503307104110718; //err 0.005195122102448952
 }

 if(pt > 200. && pt <=300){ 
  if(fabs(eta)>= 0.0 && fabs(eta)<0.9) musf=0.9162033796310425; //err 0.0028656970513730017
  if(fabs(eta)>= 0.9 && fabs(eta)<1.2) musf=0.9116483330726624; //err 0.004974297248567905
  if(fabs(eta)>= 1.2 && fabs(eta)<2.1) musf=0.9137247204780579; //err 0.003394166872715402
  if(fabs(eta)>= 2.1 && fabs(eta)<2.4) musf=0.8325985074043274; //err 0.023364071376511055
 }

 if(pt > 300.){ //&& pt <=1200.
  if(fabs(eta)>= 0.0 && fabs(eta)<0.9) musf=0.8930183053016663; //err 0.007617952889111469
  if(fabs(eta)>= 0.9 && fabs(eta)<1.2) musf=0.8819695115089417; //err 0.01840147234943961
  if(fabs(eta)>= 1.2 && fabs(eta)<2.1) musf=0.9049304127693176; //err 0.00863011621547623
  if(fabs(eta)>= 2.1 && fabs(eta)<2.4) musf=0.8184008598327637; //err 0.0307142641727703
 }
 //https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2018_trigger/theJSONfile_2018Data_AfterMuonHLTUpdate.json
 
 return musf;
}
double musf_ID(double eta, double pt){
 double musf=0;
/* if(pt<80){
  if(fabs(eta)>=0.0 && fabs(eta)<1.2) musf=0.985720157623291;
  if(fabs(eta)>=1.2 && fabs(eta)<2.1) musf=0.9935390949249268;
  if(fabs(eta)>=2.1 && fabs(eta)<2.4) musf=0.9843316674232483;
 }
 if(pt>=80 && pt<140){
  if(fabs(eta)>=0.0 && fabs(eta)<1.2) musf=0.990919828414917;
  if(fabs(eta)>=1.2 && fabs(eta)<2.1) musf=1.001926302909851;
  if(fabs(eta)>=2.1 && fabs(eta)<2.4) musf=0.9332278370857239;
 }
 if(pt>=140){
  if(fabs(eta)>=0.0 && fabs(eta)<1.2) musf=0.9570706486701965;
  if(fabs(eta)>=1.2 && fabs(eta)<2.1) musf=0.9942596554756165;
  if(fabs(eta)>=2.1 && fabs(eta)<2.4) musf=1.0;
 }*/
 
 if(fabs(eta)>0.0 && fabs(eta)<=0.9){
  if(pt>20 && pt<=25) musf=0.9918519901076025; //err 0.003185729427233264
  if(pt>25 && pt<=30) musf=0.9911001054125665; //err 0.0015640758217114322
  if(pt>30 && pt<=40) musf=0.9944557361148876; //err 0.0004557831724231371
  if(pt>40 && pt<=50) musf=0.996758358192331;  //err 0.0002326671202972099
  if(pt>50 && pt<=60) musf=0.9968940819376134; //err 0.0005039261211765686
  if(pt>60)musf=0.9975476925210415; //err 0.0006810584469424329
 } 
 if(fabs(eta)>0.9 && fabs(eta)<=1.2){
  if(pt>20 && pt<=25) musf=0.9984714706717206; //err 0.005411811191539856
  if(pt>25 && pt<=30) musf=0.9940757873742564; //err 0.002802383630987413
  if(pt>30 && pt<=40) musf=0.9978615016981152; //err 0.0008493542826327553
  if(pt>40 && pt<=50) musf=0.9993869832070705;  //err 0.00048459452599051176
  if(pt>50 && pt<=60) musf=0.999679044230631; //0.0009356139980307165
  if(pt>60)musf=0.9997775963828982; //0.0013212854510178426
 }
 if(fabs(eta)>1.2 && fabs(eta)<=2.1){
  if(pt>20 && pt<=25) musf=1.007141017880756; //err 0.002855951787448304
  if(pt>25 && pt<=30) musf=1.005188717373379; //err 0.0015621682103447298
  if(pt>30 && pt<=40) musf=1.003155310684889; //err 0.0005457091261743142
  if(pt>40 && pt<=50) musf=1.0025571672176914; //err 0.00032209535360209964
  if(pt>50 && pt<=60) musf=1.0010962871110791; //err 0.0006404275866293288
  if(pt>60)musf=1.0010951326162096; //err 0.000921086640081242
 }
 if(fabs(eta)>2.1 && fabs(eta)<=2.4){
  if(pt>20 && pt<=25) musf=1.0176170414890633; //err 0.0050384141397372606
  if(pt>25 && pt<=30) musf=1.0075256604703875; //err 0.0027804621904079017
  if(pt>30 && pt<=40) musf=1.0093415974693956; //err 0.0010633200403720557
  if(pt>40 && pt<=50) musf=1.0049781908139057; //err 0.0007562288075900742
  if(pt>50 && pt<=60) musf=1.0036767999639429; //err 0.0014846828629376523
  if(pt>60)musf=1.0023828518307478; //err 0.00206442239775844
 }
 return musf;
 //https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2018/jsonfiles/RunABCD_SF_ISO.json
 //NUM_TightRelTkIso_DEN_HighPtIDandIPCut
}
double musf_iso(double eta, double pt){
 double musf=0;
/* if(pt<40){
  if(fabs(eta)>=0.0 && fabs(eta)<1.2) musf=0.9995902180671692;
  if(fabs(eta)>=1.2 && fabs(eta)<2.1) musf=1.0008221864700317;
  if(fabs(eta)>=2.1 && fabs(eta)<2.4) musf=0.9995952844619751;
 }
 if(pt>=40 && pt<50){
  if(fabs(eta)>=0.0 && fabs(eta)<1.2) musf=0.9993510842323303;
  if(fabs(eta)>=1.2 && fabs(eta)<2.1) musf=0.9998430609703064;
  if(fabs(eta)>=2.1 && fabs(eta)<2.4) musf=1.0003995895385742;
 }
 if(pt>=50 && pt<60){
  if(fabs(eta)>=0.0 && fabs(eta)<1.2) musf=0.9998735785484314;
  if(fabs(eta)>=1.2 && fabs(eta)<2.1) musf=0.9997379779815674;
  if(fabs(eta)>=2.1 && fabs(eta)<2.4) musf=1.001578450202942;
 }

 if(pt>=60){
  if(fabs(eta)>=0.0 && fabs(eta)<1.2) musf=0.9995099306106567;
  if(fabs(eta)>=1.2 && fabs(eta)<2.1) musf=1.0010874271392822;
  if(fabs(eta)>=2.1 && fabs(eta)<2.4) musf=1.0011582374572754;
 }
*/
 
 if(fabs(eta)>0.0 && fabs(eta)<=0.9){
  if(pt>20 && pt<=25) musf=0.992114065208379; //err 0.0009548339162957359
  if(pt>25 && pt<=30) musf=0.9924247027728448; //err 0.0005721135461542568
  if(pt>30 && pt<=40) musf=0.9922515732194475; //err 0.00022056808100734152
  if(pt>40 && pt<=50) musf=0.9926712022753303; //err 0.00029555844081348594
  if(pt>50 && pt<=60) musf=0.9928603953286465; //err 0.0004812825431584111
  if(pt>60)musf=0.992263125763373; //err 0.0007301722545706139
 }
 if(fabs(eta)>0.9 && fabs(eta)<=1.2){
  if(pt>20 && pt<=25) musf=0.9880778949699621; //err 0.0015507830148471576
  if(pt>25 && pt<=30) musf=0.9858269794946017; //err 0.0008667578427999276
  if(pt>30 && pt<=40) musf=0.9861662092005419; //err 0.00040273205051734795 
  if(pt>40 && pt<=50) musf=0.9868886396371438;   //err 0.000358620121199017
  if(pt>50 && pt<=60) musf=0.9857803031481773;  //err 0.0008250932378258363 
  if(pt>60)musf=0.9851298296096568; //err 0.0013508015355310672
 }
 if(fabs(eta)>1.2 && fabs(eta)<=2.1){
  if(pt>20 && pt<=25) musf=0.9922334188037855; //err 0.0006058268576121627 
  if(pt>25 && pt<=30) musf=0.9923174786068355;  //err 0.00041202179870509885 
  if(pt>30 && pt<=40) musf=0.9922065831090526; //err 0.00017938520880153905 
  if(pt>40 && pt<=50) musf=0.9915977902632379; //err 0.00018633029867623288
  if(pt>50 && pt<=60) musf=0.9925127625404958; //err 0.00039796265367970246
  if(pt>60)musf=0.9910195523946569; //err 0.0006320689063062524
 }
 if(fabs(eta)>2.1 && fabs(eta)<=2.4){
  if(pt>20 && pt<=25) musf=0.9797230542389544; //err 0.002343776036433275
  if(pt>25 && pt<=30) musf=0.9781500508836776; //err 0.0011083458857072618
  if(pt>30 && pt<=40) musf=0.9777848757048854; //err 0.0005589872869792092
  if(pt>40 && pt<=50) musf=0.9777795367016231; //err 0.000807982424363258
  if(pt>50 && pt<=60) musf=0.9770080438205287; //err 0.0017636447439491989
  if(pt>60 )musf=0.9739992676455306; //err 0.0028517427863376157
 }
//https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2018/jsonfiles/RunABCD_SF_ID.json
//NUM_HighPtID_DEN_TrackerMuons
//pt>60 && pt<=120

 return musf;
}

double get_wgtlumi(string FileName){
 double wgt=1;

 //xsec in pb

 if(FileName.find("TT") != std::string::npos) wgt=730.6/76915549;  
 if(FileName.find("DY") != std::string::npos) wgt=6225.42/146280395;
 if(FileName.find("_ST_") != std::string::npos)  wgt=38.09/6952830; 
 if(FileName.find("_SaT_") != std::string::npos) wgt=38.06/6933094; 
 if(FileName.find("WW") != std::string::npos) wgt=64.4/7982180; 
 if(FileName.find("WZ") != std::string::npos) wgt=23.43/3997571; 
 if(FileName.find("ZZ") != std::string::npos) wgt=10.16/1988098;
 if(FileName.find("WJetsHT70To100") != std::string::npos) wgt=1352.0/10020533;
 if(FileName.find("WJetsHT100To200") != std::string::npos) wgt=1346.0/78043017;
 if(FileName.find("WJetsHT200To400") != std::string::npos) wgt=360.1/38984322;
 if(FileName.find("WJetsHT400To600") != std::string::npos) wgt=48.8/7759701; 
 if(FileName.find("WJetsHT600To800") != std::string::npos) wgt=12.07/18687480; 
 if(FileName.find("WJetsHT800To1200") != std::string::npos) wgt=5.497/7830536; 
 if(FileName.find("WJetsHT1200To2500") != std::string::npos) wgt=1.329/6872441;
 if(FileName.find("WJetsHT2500ToInf") != std::string::npos) wgt=0.03209/2637821;
 if(FileName.find("WJets_") != std::string::npos) wgt=50260.0/86916455;
 
 //muons
 
 if((FileName.find("mumujj_L13000_M500") != std::string::npos)) wgt=5.7090e-03/100000;
 if((FileName.find("mumujj_L13000_M1000") != std::string::npos)) wgt=2.8140e-03/10000;
 if((FileName.find("mumujj_L13000_M2000") != std::string::npos)) wgt=0.82140e-03/100000;
 if((FileName.find("mumujj_L13000_M5000") != std::string::npos)) wgt=0.014250e-03/100000;
 if((FileName.find("mumujj_L13000_M8000") != std::string::npos)) wgt=0.000091350e-03/91350;

 //electrons
 
 if((FileName.find("eejj_L13000_M500") != std::string::npos)) wgt=5.7090e-03/10000;
 if((FileName.find("eejj_L13000_M1000") != std::string::npos)) wgt=2.8140e-03/96800;
 if((FileName.find("eejj_L13000_M2000") != std::string::npos)) wgt=0.82140e-03/10000;
 if((FileName.find("eejj_L13000_M5000") != std::string::npos)) wgt=0.014250e-03/10000;
 if((FileName.find("eejj_L13000_M8000") != std::string::npos)) wgt=0.000091350e-03/91273;
 
 return wgt;
 }

