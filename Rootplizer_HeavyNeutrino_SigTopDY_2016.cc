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
 if(fabs(eta) < 1.4442) elesf = 0.971; // stat 0.001
 if(fabs(eta) >= 1.566 && fabs(eta) < 2.5)elesf = 0.983; // stat 0.001

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

if(pt>80.0 && pt<=120.0){
    if(fabs(eta) > 0.0 && fabs(eta) <= 0.9) musf=0.979348945351; // error 0.00208323098593 
    if(fabs(eta) > 1.2 && fabs(eta) <= 2.1) musf=0.991559553185; // error 0.00344762753897 
    if(fabs(eta) > 2.1 && fabs(eta) <= 2.4) musf=0.945687243525; // error 0.00977794862985 
    if(fabs(eta) > 0.9 && fabs(eta) <= 1.2) musf=0.953858663675; // error 0.00322632096278 
}
if(pt>120.0 && pt<=200.0){
    if(fabs(eta) > 0.0 && fabs(eta) <= 0.9) musf=0.971963141223; // error 0.00358312775975 
    if(fabs(eta) > 1.2 && fabs(eta) <= 2.1) musf=0.997236642678; // error 0.00757222553809 
    if(fabs(eta) > 2.1 && fabs(eta) <= 2.4) musf=0.964864307448; // error 0.0272241772852 
    if(fabs(eta) > 0.9 && fabs(eta) <= 1.2) musf=0.940906087621; // error 0.00953153348564 
}
if(pt>400.0){
    if(fabs(eta) > 0.0 && fabs(eta) <= 0.9) musf=0.965216120987; // error 0.048615649158 
    if(fabs(eta) > 1.2 && fabs(eta) <= 2.1) musf=0.90780463359; // error 0.19017744532 
    if(fabs(eta) > 2.1 && fabs(eta) <= 2.4) musf=0.720766933187; // error 0.996638370691 
    if(fabs(eta) > 0.9 && fabs(eta) <= 1.2) musf=0.975444916201; // error 0.0780233151001 
}
if(pt>55.0 && pt<=60.0){
    if(fabs(eta) > 0.0 && fabs(eta) <= 0.9) musf=0.982172313956; // error 0.000915076135818 
    if(fabs(eta) > 1.2 && fabs(eta) <= 2.1) musf=0.993104561456; // error 0.00157310792511 
    if(fabs(eta) > 2.1 && fabs(eta) <= 2.4) musf=0.935460280411; // error 0.00407745125853 
    if(fabs(eta) > 0.9 && fabs(eta) <= 1.2) musf=0.958748861806; // error 0.00137440243945 
}
if(pt>52.0 && pt<=55.0){
    if(fabs(eta) > 0.0 && fabs(eta) <= 0.9) musf=0.97765533033; // error 0.000873373899488 
    if(fabs(eta) > 1.2 && fabs(eta) <= 2.1) musf=0.987151898728; // error 0.00147147782448 
    if(fabs(eta) > 2.1 && fabs(eta) <= 2.4) musf=0.918599081349; // error 0.00402102545385 
    if(fabs(eta) > 0.9 && fabs(eta) <= 1.2) musf=0.953752562062; // error 0.00105817396096 
}
if(pt>60.0 && pt<=80.0){
    if(fabs(eta) > 0.0 && fabs(eta) <= 0.9) musf=0.981439045142; // error 0.000853646677067 
    if(fabs(eta) > 1.2 && fabs(eta) <= 2.1) musf=0.994310399764; // error 0.00145425246559 
    if(fabs(eta) > 2.1 && fabs(eta) <= 2.4) musf=0.940574201481; // error 0.00387588865056 
    if(fabs(eta) > 0.9 && fabs(eta) <= 1.2) musf=0.958232578952; // error 0.00124132468391 
}
if(pt>200.0 && pt<=300.0){
    if(fabs(eta) > 0.0 && fabs(eta) <= 0.9) musf=0.977938102104; // error 0.00965485757377 
    if(fabs(eta) > 1.2 && fabs(eta) <= 2.1) musf=0.957358230391; // error 0.0221928341518 
    if(fabs(eta) > 2.1 && fabs(eta) <= 2.4) musf=0.825968477035; // error 0.168574059327 
    if(fabs(eta) > 0.9 && fabs(eta) <= 1.2) musf=0.944979742807; // error 0.0242208031033 
}
if(pt>300.0 && pt<=400.0){
    if(fabs(eta) > 0.0 && fabs(eta) <= 0.9) musf=1.00528291728; // error 0.0240421197081 
    if(fabs(eta) > 1.2 && fabs(eta) <= 2.1) musf=1.12126658491; // error 0.152571268391 
    if(fabs(eta) > 2.1 && fabs(eta) <= 2.4) musf=0.785026453282; // error 0.0705578748306 
    if(fabs(eta) > 0.9 && fabs(eta) <= 1.2) musf=0.944298028685; // error 0.0537756662753 
}

//https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2016_trigger/EfficienciesAndSF_RunGtoH.json
//https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2016_trigger/EfficienciesAndSF_RunBtoF.json
//Mu50_OR_TkMu50_PtEtaBins
// (pesoBF*L_BF + pesoGH*L_GH)/L_BH
 return musf;
}
double musf_ID(double eta, double pt){
 double musf=0;
 if(pt>20.00 && pt<=25.00){
    if(eta > 0.50 && eta <= 0.80) musf=1.00211123155; // stat 0.00830284954361 syst 0.00348297801398 
    if(eta > -1.60 && eta <= -1.50) musf=1.00017596119; // stat 0.0126609943153 syst 0.00204450362149 
    if(eta > 2.00 && eta <= 2.10) musf=0.983123138639; // stat 0.0114688705796 syst 0.0026291414228 
    if(eta > -0.20 && eta <= 0.00) musf=0.971543094276; // stat 0.0113411399666 syst 0.0111128156037 
    if(eta > -1.20 && eta <= -0.80) musf=0.987239460735; // stat 0.00522917995849 syst 0.00276415212077 
    if(eta > -1.70 && eta <= -1.60) musf=0.996946306362; // stat 0.00866572457671 syst 0.000938615931322 
    if(eta > 1.40 && eta <= 1.50) musf=1.00577129019; // stat 0.0106160550206 syst 0.00654039495036 
    if(eta > -2.10 && eta <= -2.00) musf=0.985070797329; // stat 0.00963624173484 syst 0.00219558134089 
    if(eta > 2.10 && eta <= 2.20) musf=0.982612531854; // stat 0.00818488702493 syst 0.00337510160654 
    if(eta > -2.40 && eta <= -2.30) musf=0.991455095023; // stat 0.0118547031637 syst 0.00639466183446 
    if(eta > 2.20 && eta <= 2.30) musf=0.996163796457; // stat 0.0138260876819 syst 0.00353036327137 
    if(eta > -1.40 && eta <= -1.20) musf=1.00558218584; // stat 0.00759290967337 syst 0.00352813548527 
    if(eta > 1.70 && eta <= 2.00) musf=0.984930856296; // stat 0.00597635827006 syst 0.00231582361227 
    if(eta > 0.80 && eta <= 1.20) musf=0.987865920447; // stat 0.00616314924911 syst 0.00300656865775 
    if(eta > 0.20 && eta <= 0.30) musf=0.961931450658; // stat 0.0176837016129 syst 0.010166495744 
    if(eta > -2.30 && eta <= -2.20) musf=0.990074021836; // stat 0.00962727873015 syst 0.00510567238519 
    if(eta > 1.60 && eta <= 1.70) musf=0.999509845929; // stat 0.00887735262956 syst 0.00532286752516 
    if(eta > -0.50 && eta <= -0.30) musf=1.01030208447; // stat 0.0105670688229 syst 0.0120938580629 
    if(eta > -2.20 && eta <= -2.10) musf=0.965039975584; // stat 0.00932478149592 syst 0.00537958604232 
    if(eta > 1.50 && eta <= 1.60) musf=1.00404959599; // stat 0.00887268219707 syst 0.00409114540157 
    if(eta > -2.00 && eta <= -1.70) musf=0.978548864125; // stat 0.00540209949607 syst 0.000943299235691 
    if(eta > -1.50 && eta <= -1.40) musf=1.00225789031; // stat 0.00855228415939 syst 0.00167462362513 
    if(eta > -0.80 && eta <= -0.50) musf=1.0021762764; // stat 0.00395472329121 syst 0.00248275133166 
    if(eta > 0.00 && eta <= 0.20) musf=0.995791165678; // stat 0.011667690184 syst 0.0113575691324 
    if(eta > 2.30 && eta <= 2.40) musf=0.999834182426; // stat 0.0132650401568 syst 0.00457248218944 
    if(eta > -0.30 && eta <= -0.20) musf=0.981066679517; // stat 0.0148713007157 syst 0.0124395670076 
    if(eta > 0.30 && eta <= 0.50) musf=1.00493346708; // stat 0.0119029114745 syst 0.0107548427105 
    if(eta > 1.20 && eta <= 1.40) musf=1.00244577072; // stat 0.0102548084783 syst 0.00652591466925 
}
if(pt>30.00 && pt<=40.00){
    if(eta > 0.50 && eta <= 0.80) musf=0.993171553226; // stat 0.00266684387344 syst 0.0011286298307 
    if(eta > -1.60 && eta <= -1.50) musf=0.995571077074; // stat 0.00227542174604 syst 0.000238352952193 
    if(eta > 2.00 && eta <= 2.10) musf=0.98716846182; // stat 0.00304091930457 syst 0.000877477563587 
    if(eta > -0.20 && eta <= 0.00) musf=0.994802753112; // stat 0.00261517452126 syst 0.00182994090936 
    if(eta > -1.20 && eta <= -0.80) musf=0.982798420661; // stat 0.0010728980739 syst 0.000774117469812 
    if(eta > -1.70 && eta <= -1.60) musf=0.993748868003; // stat 0.00160187658724 syst 0.000262651546589 
    if(eta > 1.40 && eta <= 1.50) musf=1.00046296334; // stat 0.00195907813084 syst 0.00204649354669 
    if(eta > -2.10 && eta <= -2.00) musf=0.98277405036; // stat 0.00190976611475 syst 0.000807778979007 
    if(eta > 2.10 && eta <= 2.20) musf=0.966209375263; // stat 0.00390772125997 syst 0.000883297265298 
    if(eta > -2.40 && eta <= -2.30) musf=0.989650272339; // stat 0.0061688828126 syst 0.00534075044988 
    if(eta > 2.20 && eta <= 2.30) musf=0.994147694607; // stat 0.00194149347414 syst 0.00443702653473 
    if(eta > -1.40 && eta <= -1.20) musf=0.996633483094; // stat 0.00109991275945 syst 0.00068773082376 
    if(eta > 1.70 && eta <= 2.00) musf=0.988421675521; // stat 0.00139685996796 syst 0.000485000596524 
    if(eta > 0.80 && eta <= 1.20) musf=0.98282412137; // stat 0.00109790641197 syst 0.00105669245848 
    if(eta > 0.20 && eta <= 0.30) musf=0.962215450793; // stat 0.00672756153923 syst 0.00180907024836 
    if(eta > -2.30 && eta <= -2.20) musf=0.987352265035; // stat 0.00337914648321 syst 0.00171153746004 
    if(eta > 1.60 && eta <= 1.70) musf=0.998094089468; // stat 0.00204600476472 syst 0.00163017805459 
    if(eta > -0.50 && eta <= -0.30) musf=0.993242728016; // stat 0.00217565920252 syst 0.000537924609794 
    if(eta > -2.20 && eta <= -2.10) musf=0.958949104838; // stat 0.00393373482596 syst 0.0010224158968 
    if(eta > 1.50 && eta <= 1.60) musf=1.00407209998; // stat 0.00238198727537 syst 0.0016749114201 
    if(eta > -2.00 && eta <= -1.70) musf=0.982639631735; // stat 0.00105789881122 syst 0.000569999780488 
    if(eta > -1.50 && eta <= -1.40) musf=0.996259901845; // stat 0.00175746152958 syst 0.000845050687089 
    if(eta > -0.80 && eta <= -0.50) musf=0.9926232517; // stat 0.00275132331772 syst 0.000986642668793 
    if(eta > 0.00 && eta <= 0.20) musf=0.991192011359; // stat 0.00168611403211 syst 0.00182644784469 
    if(eta > 2.30 && eta <= 2.40) musf=0.982082795263; // stat 0.00341685202333 syst 0.00353032080754 
    if(eta > -0.30 && eta <= -0.20) musf=0.970430309159; // stat 0.00551045925545 syst 0.0019951282859 
    if(eta > 0.30 && eta <= 0.50) musf=0.990286054256; // stat 0.00503893135807 syst 0.000581707742312 
    if(eta > 1.20 && eta <= 1.40) musf=0.998381592494; // stat 0.00551928091035 syst 0.00162854942844 
}
if(pt>25.00 && pt<=30.00){
    if(eta > 0.50 && eta <= 0.80) musf=0.996211530507; // stat 0.00341664447087 syst 0.00215960823807 
    if(eta > -1.60 && eta <= -1.50) musf=0.99764673899; // stat 0.00545149316744 syst 0.00142047858687 
    if(eta > 2.00 && eta <= 2.10) musf=0.982571249317; // stat 0.00442132604992 syst 0.0018904587886 
    if(eta > -0.20 && eta <= 0.00) musf=0.99102854627; // stat 0.00462519817882 syst 0.00442036074417 
    if(eta > -1.20 && eta <= -0.80) musf=0.985988791428; // stat 0.00302340006518 syst 0.00166638135626 
    if(eta > -1.70 && eta <= -1.60) musf=0.990302435021; // stat 0.00413287237829 syst 0.00125879064365 
    if(eta > 1.40 && eta <= 1.50) musf=1.00309792606; // stat 0.00491895284519 syst 0.00505568491037 
    if(eta > -2.10 && eta <= -2.00) musf=0.981363815703; // stat 0.00414452124676 syst 0.00124510627976 
    if(eta > 2.10 && eta <= 2.20) musf=0.974520357643; // stat 0.00506710632346 syst 0.00147458473975 
    if(eta > -2.40 && eta <= -2.30) musf=0.99053563837; // stat 0.00974916935678 syst 0.00376700365767 
    if(eta > 2.20 && eta <= 2.30) musf=0.99329654759; // stat 0.0051719012959 syst 0.00184243729585 
    if(eta > -1.40 && eta <= -1.20) musf=0.992715112192; // stat 0.00363403301475 syst 0.000480205504292 
    if(eta > 1.70 && eta <= 2.00) musf=0.986000657425; // stat 0.00209991574197 syst 0.000623960419802 
    if(eta > 0.80 && eta <= 1.20) musf=0.983505277391; // stat 0.00326780173258 syst 0.00114896655099 
    if(eta > 0.20 && eta <= 0.30) musf=0.970047730902; // stat 0.0106650667453 syst 0.00405549305572 
    if(eta > -2.30 && eta <= -2.20) musf=0.99273100417; // stat 0.00842490211857 syst 0.0015910016557 
    if(eta > 1.60 && eta <= 1.70) musf=0.997898823653; // stat 0.00790157108758 syst 0.00290260691682 
    if(eta > -0.50 && eta <= -0.30) musf=0.991801917122; // stat 0.00344982413127 syst 0.00324580661511 
    if(eta > -2.20 && eta <= -2.10) musf=0.964192873112; // stat 0.007238311236 syst 0.000967028796262 
    if(eta > 1.50 && eta <= 1.60) musf=0.998213836326; // stat 0.00890478320687 syst 0.00355169903384 
    if(eta > -2.00 && eta <= -1.70) musf=0.98342227361; // stat 0.00291294249905 syst 0.000967216458078 
    if(eta > -1.50 && eta <= -1.40) musf=0.994177120609; // stat 0.00500108309296 syst 0.00125269959111 
    if(eta > -0.80 && eta <= -0.50) musf=0.999070252947; // stat 0.00338589197844 syst 0.00265835982348 
    if(eta > 0.00 && eta <= 0.20) musf=0.990957471481; // stat 0.00470097412819 syst 0.00460402149086 
    if(eta > 2.30 && eta <= 2.40) musf=0.975559944702; // stat 0.00722219104929 syst 0.00322954102472 
    if(eta > -0.30 && eta <= -0.20) musf=0.974416369701; // stat 0.00893480105675 syst 0.00367733201265 
    if(eta > 0.30 && eta <= 0.50) musf=0.994643236923; // stat 0.00484943693475 syst 0.00363011238477 
    if(eta > 1.20 && eta <= 1.40) musf=0.998927102685; // stat 0.00469964584679 syst 0.00409238631196 
}
if(pt>60.00){
    if(eta > 0.50 && eta <= 0.80) musf=0.991068684788; // stat 0.00604974024823 syst 0.00984471726807 
    if(eta > -1.60 && eta <= -1.50) musf=1.00516617628; // stat 0.00744819487565 syst 0.00421115375155 
    if(eta > 2.00 && eta <= 2.10) musf=0.994790658377; // stat 0.0112765916261 syst 0.00384776169836 
    if(eta > -0.20 && eta <= 0.00) musf=0.994651136687; // stat 0.00744117254171 syst 0.00979329180534 
    if(eta > -1.20 && eta <= -0.80) musf=0.985038939081; // stat 0.00482946478136 syst 0.00399025408848 
    if(eta > -1.70 && eta <= -1.60) musf=0.987608611833; // stat 0.00812439712347 syst 0.00203148536109 
    if(eta > 1.40 && eta <= 1.50) musf=1.00064074462; // stat 0.00486501881661 syst 0.00411898520319 
    if(eta > -2.10 && eta <= -2.00) musf=0.992789681498; // stat 0.0121433213915 syst 0.00438428891199 
    if(eta > 2.10 && eta <= 2.20) musf=0.960907003749; // stat 0.0146538580497 syst 0.00618085590664 
    if(eta > -2.40 && eta <= -2.30) musf=0.979531136993; // stat 0.0248786787191 syst 0.00942693372715 
    if(eta > 2.20 && eta <= 2.30) musf=0.988549687905; // stat 0.015666169497 syst 0.00621613011452 
    if(eta > -1.40 && eta <= -1.20) musf=0.995776070011; // stat 0.00673296588747 syst 0.00358460589833 
    if(eta > 1.70 && eta <= 2.00) musf=0.983880391947; // stat 0.00551548806325 syst 0.00240235942763 
    if(eta > 0.80 && eta <= 1.20) musf=0.981085186123; // stat 0.00515491690526 syst 0.00597974289624 
    if(eta > 0.20 && eta <= 0.30) musf=0.979220742404; // stat 0.0143706182677 syst 0.0127137170866 
    if(eta > -2.30 && eta <= -2.20) musf=0.994406899012; // stat 0.0157772476327 syst 0.0082054877686 
    if(eta > 1.60 && eta <= 1.70) musf=0.985910895555; // stat 0.0131230547764 syst 0.00946395739655 
    if(eta > -0.50 && eta <= -0.30) musf=1.0075411648; // stat 0.00664348182082 syst 0.0104826186801 
    if(eta > -2.20 && eta <= -2.10) musf=0.956294223377; // stat 0.0156411029433 syst 0.00357511314798 
    if(eta > 1.50 && eta <= 1.60) musf=1.00116449917; // stat 0.0124956917286 syst 0.00688184999882 
    if(eta > -2.00 && eta <= -1.70) musf=0.983889947415; // stat 0.00872243673638 syst 0.00192154037175 
    if(eta > -1.50 && eta <= -1.40) musf=0.992977665285; // stat 0.00993373021189 syst 0.00319149233699 
    if(eta > -0.80 && eta <= -0.50) musf=0.998389793101; // stat 0.00593790699327 syst 0.00855399632027 
    if(eta > 0.00 && eta <= 0.20) musf=0.994532641055; // stat 0.00736088171145 syst 0.00807820157721 
    if(eta > 2.30 && eta <= 2.40) musf=1.00360525694; // stat 0.0147410379083 syst 0.00858739272583 
    if(eta > -0.30 && eta <= -0.20) musf=0.972506855405; // stat 0.013871214023 syst 0.0108835917767 
    if(eta > 0.30 && eta <= 0.50) musf=1.0010432274; // stat 0.00767564858187 syst 0.0110838331024 
    if(eta > 1.20 && eta <= 1.40) musf=0.995671437332; // stat 0.00992532185371 syst 0.0097084705105 
}
if(pt>40.00 && pt<=50.00){
    if(eta > 0.50 && eta <= 0.80) musf=0.994052501394; // stat 0.000845446236027 syst 0.00182256638749 
    if(eta > -1.60 && eta <= -1.50) musf=0.996668440524; // stat 0.00103070886239 syst 0.00203443995658 
    if(eta > 2.00 && eta <= 2.10) musf=0.988827732118; // stat 0.0015747590692 syst 0.00234776881844 
    if(eta > -0.20 && eta <= 0.00) musf=0.994566936222; // stat 0.00110757146232 syst 0.00155491791831 
    if(eta > -1.20 && eta <= -0.80) musf=0.98343516845; // stat 0.000828576430766 syst 0.00131618566771 
    if(eta > -1.70 && eta <= -1.60) musf=0.993012926187; // stat 0.00117529629557 syst 0.00120092232152 
    if(eta > 1.40 && eta <= 1.50) musf=1.00222026273; // stat 0.00161545411451 syst 0.00427648360746 
    if(eta > -2.10 && eta <= -2.00) musf=0.983202189391; // stat 0.00241434791767 syst 0.000977751613715 
    if(eta > 2.10 && eta <= 2.20) musf=0.971087717152; // stat 0.00295377758809 syst 0.00214569430442 
    if(eta > -2.40 && eta <= -2.30) musf=0.99080486154; // stat 0.00360368315291 syst 0.00401874399814 
    if(eta > 2.20 && eta <= 2.30) musf=0.989350035065; // stat 0.00391278881166 syst 0.00256780908525 
    if(eta > -1.40 && eta <= -1.20) musf=0.99585293099; // stat 0.000765385142332 syst 0.00172542857948 
    if(eta > 1.70 && eta <= 2.00) musf=0.989202360522; // stat 0.00109332077741 syst 0.00145561705958 
    if(eta > 0.80 && eta <= 1.20) musf=0.982754144322; // stat 0.000836991991224 syst 0.00152638823592 
    if(eta > 0.20 && eta <= 0.30) musf=0.965186543065; // stat 0.00302810532006 syst 0.00199145772932 
    if(eta > -2.30 && eta <= -2.20) musf=0.987046149703; // stat 0.00244806297139 syst 0.00277627911192 
    if(eta > 1.60 && eta <= 1.70) musf=1.00180348757; // stat 0.00148242671912 syst 0.00386947083161 
    if(eta > -0.50 && eta <= -0.30) musf=0.994814850892; // stat 0.0009307001236 syst 0.00229631412858 
    if(eta > -2.20 && eta <= -2.10) musf=0.959912235473; // stat 0.00583835731045 syst 0.00287675659175 
    if(eta > 1.50 && eta <= 1.60) musf=1.00357309057; // stat 0.00161894238983 syst 0.00464909944842 
    if(eta > -2.00 && eta <= -1.70) musf=0.983643009919; // stat 0.00208103007564 syst 0.00100766147124 
    if(eta > -1.50 && eta <= -1.40) musf=0.996327381878; // stat 0.00293018260985 syst 0.00221604906181 
    if(eta > -0.80 && eta <= -0.50) musf=0.993898054283; // stat 0.000716649141077 syst 0.00153728609062 
    if(eta > 0.00 && eta <= 0.20) musf=0.99350655446; // stat 0.00111445325998 syst 0.00199596060582 
    if(eta > 2.30 && eta <= 2.40) musf=0.990675090438; // stat 0.00335131549548 syst 0.00389278616069 
    if(eta > -0.30 && eta <= -0.20) musf=0.972499498227; // stat 0.00305094010906 syst 0.0019054985423 
    if(eta > 0.30 && eta <= 0.50) musf=0.991374746795; // stat 0.000963717958799 syst 0.00183713004591 
    if(eta > 1.20 && eta <= 1.40) musf=1.00024939714; // stat 0.00101687747329 syst 0.00307320005186 
}
if(pt>50.00 && pt<=60.00){
    if(eta > 0.50 && eta <= 0.80) musf=0.987370778403; // stat 0.00262950953653 syst 0.000439368506131 
    if(eta > -1.60 && eta <= -1.50) musf=0.993719346923; // stat 0.00400821175729 syst 0.00108337515294 
    if(eta > 2.00 && eta <= 2.10) musf=0.985959152461; // stat 0.00523369755783 syst 0.00139521644201 
    if(eta > -0.20 && eta <= 0.00) musf=0.989657897264; // stat 0.00327338390254 syst 0.000979606308056 
    if(eta > -1.20 && eta <= -0.80) musf=0.977721488229; // stat 0.00247377866891 syst 0.00106674483457 
    if(eta > -1.70 && eta <= -1.60) musf=0.993178839424; // stat 0.00365620288687 syst 0.00144305927383 
    if(eta > 1.40 && eta <= 1.50) musf=0.983802728963; // stat 0.00648610481443 syst 0.00348333890136 
    if(eta > -2.10 && eta <= -2.00) musf=0.982640111998; // stat 0.00625841335207 syst 0.0014068021952 
    if(eta > 2.10 && eta <= 2.20) musf=0.964939703756; // stat 0.00720695515806 syst 0.0015919195844 
    if(eta > -2.40 && eta <= -2.30) musf=0.978655008479; // stat 0.0132822139935 syst 0.00398190426169 
    if(eta > 2.20 && eta <= 2.30) musf=0.980775804059; // stat 0.00723238660201 syst 0.00209242292996 
    if(eta > -1.40 && eta <= -1.20) musf=0.992303149594; // stat 0.00301446247338 syst 0.00127314374548 
    if(eta > 1.70 && eta <= 2.00) musf=0.986224415426; // stat 0.00270124815857 syst 0.00100223607406 
    if(eta > 0.80 && eta <= 1.20) musf=0.978314445771; // stat 0.00255729946982 syst 0.00111458915976 
    if(eta > 0.20 && eta <= 0.30) musf=0.965063565844; // stat 0.00792026091768 syst 0.00101027852931 
    if(eta > -2.30 && eta <= -2.20) musf=0.978259303368; // stat 0.00804403224101 syst 0.00317260204026 
    if(eta > 1.60 && eta <= 1.70) musf=0.989545489316; // stat 0.00586176459615 syst 0.00221417727823 
    if(eta > -0.50 && eta <= -0.30) musf=0.991481630101; // stat 0.00307185986751 syst 0.00115752855052 
    if(eta > -2.20 && eta <= -2.10) musf=0.958070271818; // stat 0.00754802897175 syst 0.00227814666569 
    if(eta > 1.50 && eta <= 1.60) musf=0.993731313714; // stat 0.0069464952503 syst 0.00186627406646 
    if(eta > -2.00 && eta <= -1.70) musf=0.985087445306; // stat 0.00237803562302 syst 0.0004580924085 
    if(eta > -1.50 && eta <= -1.40) musf=0.99551622415; // stat 0.00416993670418 syst 0.00116742561558 
    if(eta > -0.80 && eta <= -0.50) musf=0.99057180175; // stat 0.00239351913095 syst 0.000671386199989 
    if(eta > 0.00 && eta <= 0.20) musf=0.989428312639; // stat 0.00324349097471 syst 0.00127336751368 
    if(eta > 2.30 && eta <= 2.40) musf=0.986055565116; // stat 0.0110005828986 syst 0.00395403908032 
    if(eta > -0.30 && eta <= -0.20) musf=0.971249095128; // stat 0.00811659112715 syst 0.00254373191416 
    if(eta > 0.30 && eta <= 0.50) musf=0.990328746205; // stat 0.00301067936018 syst 0.00112394763244 
    if(eta > 1.20 && eta <= 1.40) musf=0.988123770719; // stat 0.00434150751146 syst 0.0021135946514 
}
 return musf;
 // https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2016_legacy_rereco/systematic/RunBCDEF_SF_ID.json
 // https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2016_legacy_rereco/systematic/RunGH_SF_ID.json
 //NUM_HighPtID_DEN_genTracks
 // (pesoBF*L_BF + pesoGH*L_GH)/L_BH
}
double musf_iso(double eta, double pt){
 double musf=0;
if(pt>20.00 && pt<=25.00){
    if(eta > 0.50 && eta <= 0.80) musf=0.991665875336; // stat 0.00572326918454 syst 0.00115303461817 
    if(eta > -1.60 && eta <= -1.50) musf=0.995257967695; // stat 0.00641898308651 syst 0.00187475995255 
    if(eta > 2.00 && eta <= 2.10) musf=0.998802662751; // stat 0.00597392348073 syst 0.00268011369165 
    if(eta > -0.20 && eta <= 0.00) musf=0.98594635525; // stat 0.00697199095507 syst 0.00117885326216 
    if(eta > -1.20 && eta <= -0.80) musf=0.996539912083; // stat 0.00436472461156 syst 0.00055138821066 
    if(eta > -1.70 && eta <= -1.60) musf=0.991463121049; // stat 0.00625447761819 syst 0.00139224433362 
    if(eta > 1.40 && eta <= 1.50) musf=0.999571130051; // stat 0.007531011586 syst 0.00121551198449 
    if(eta > -2.10 && eta <= -2.00) musf=0.998580522123; // stat 0.00538447988493 syst 0.00330315000173 
    if(eta > 2.10 && eta <= 2.20) musf=0.993445977561; // stat 0.00598010100382 syst 0.000506368063757 
    if(eta > -2.40 && eta <= -2.30) musf=0.986741207025; // stat 0.00721949259302 syst 0.00113128623178 
    if(eta > 2.20 && eta <= 2.30) musf=0.995579254012; // stat 0.00662292339608 syst 0.000993865111664 
    if(eta > -1.40 && eta <= -1.20) musf=0.991755468766; // stat 0.00524866106869 syst 0.0018604239703 
    if(eta > 1.70 && eta <= 2.00) musf=0.996790234808; // stat 0.00355692146723 syst 0.000601028176061 
    if(eta > 0.80 && eta <= 1.20) musf=0.99767949735; // stat 0.00439921874496 syst 0.000917696853035 
    if(eta > 0.20 && eta <= 0.30) musf=0.992372321774; // stat 0.0107458297852 syst 0.00254281912075 
    if(eta > -2.30 && eta <= -2.20) musf=0.99854981963; // stat 0.00638249140678 syst 0.000860196051246 
    if(eta > 1.60 && eta <= 1.70) musf=0.995580663022; // stat 0.00651551298115 syst 0.00163857524266 
    if(eta > -0.50 && eta <= -0.30) musf=0.984500920159; // stat 0.00704649482047 syst 0.00183870723155 
    if(eta > -2.20 && eta <= -2.10) musf=0.995850544056; // stat 0.00596526783106 syst 0.00269262428798 
    if(eta > 1.50 && eta <= 1.60) musf=1.00280408329; // stat 0.00681673419527 syst 0.00195967562224 
    if(eta > -2.00 && eta <= -1.70) musf=0.998777845797; // stat 0.00350894607202 syst 0.000881064525992 
    if(eta > -1.50 && eta <= -1.40) musf=0.999870375355; // stat 0.00753069552927 syst 0.000854015098574 
    if(eta > -0.80 && eta <= -0.50) musf=0.996391080241; // stat 0.00554706187851 syst 0.00103585115253 
    if(eta > 0.00 && eta <= 0.20) musf=0.992110509615; // stat 0.00712627633116 syst 0.00200499024161 
    if(eta > 2.30 && eta <= 2.40) musf=0.996603659362; // stat 0.00744738168514 syst 0.00272546061107 
    if(eta > -0.30 && eta <= -0.20) musf=0.990195285901; // stat 0.0101885565956 syst 0.0027014454186 
    if(eta > 0.30 && eta <= 0.50) musf=0.998796754792; // stat 0.00733916861168 syst 0.00134250543698 
    if(eta > 1.20 && eta <= 1.40) musf=0.992655878172; // stat 0.0056026189674 syst 0.00143120059624 
}
if(pt>50.00 && pt<=60.00){
    if(eta > 0.50 && eta <= 0.80) musf=0.999366347869; // stat 0.00063636742466 syst 9.70061318256e-05 
    if(eta > -1.60 && eta <= -1.50) musf=1.00018102218; // stat 0.00104432502254 syst 0.000281943784697 
    if(eta > 2.00 && eta <= 2.10) musf=0.999277179667; // stat 0.00121652923668 syst 0.000717055408076 
    if(eta > -0.20 && eta <= 0.00) musf=1.00029505699; // stat 0.000815715559297 syst 0.000329832569466 
    if(eta > -1.20 && eta <= -0.80) musf=0.999792961959; // stat 0.000562063478693 syst 0.000131090719012 
    if(eta > -1.70 && eta <= -1.60) musf=1.00001357218; // stat 0.00112414648644 syst 0.000467779172698 
    if(eta > 1.40 && eta <= 1.50) musf=1.0005693559; // stat 0.00145322467133 syst 0.000592312984208 
    if(eta > -2.10 && eta <= -2.00) musf=0.998781388361; // stat 0.00110321040679 syst 0.00043624412402 
    if(eta > 2.10 && eta <= 2.20) musf=1.00072402012; // stat 0.00137340412954 syst 0.000178621456979 
    if(eta > -2.40 && eta <= -2.30) musf=1.00032562735; // stat 0.00381811200347 syst 0.00117992029051 
    if(eta > 2.20 && eta <= 2.30) musf=0.999817912233; // stat 0.00125943848618 syst 0.000606675478093 
    if(eta > -1.40 && eta <= -1.20) musf=0.999318491503; // stat 0.000774771633417 syst 0.000385938213125 
    if(eta > 1.70 && eta <= 2.00) musf=0.999343129566; // stat 0.000633478088875 syst 0.000401208514569 
    if(eta > 0.80 && eta <= 1.20) musf=0.99964379363; // stat 0.000539332942692 syst 0.000166730736934 
    if(eta > 0.20 && eta <= 0.30) musf=1.00013014575; // stat 0.00116403611516 syst 9.63740383918e-05 
    if(eta > -2.30 && eta <= -2.20) musf=0.999793510699; // stat 0.00156038999421 syst 0.00057579683856 
    if(eta > 1.60 && eta <= 1.70) musf=0.999896636814; // stat 0.000976874301178 syst 0.000246948497368 
    if(eta > -0.50 && eta <= -0.30) musf=0.999438171371; // stat 0.000790727388146 syst 0.000195471988553 
    if(eta > -2.20 && eta <= -2.10) musf=0.999775696632; // stat 0.00136153939714 syst 0.000400571969627 
    if(eta > 1.50 && eta <= 1.60) musf=1.00031393554; // stat 0.00103722216529 syst 0.000402093244504 
    if(eta > -2.00 && eta <= -1.70) musf=0.999017644387; // stat 0.000628684562474 syst 0.000203777284115 
    if(eta > -1.50 && eta <= -1.40) musf=1.00004682833; // stat 0.000993620744684 syst 0.000398756998992 
    if(eta > -0.80 && eta <= -0.50) musf=0.999730677729; // stat 0.000629078549421 syst 0.000164843852652 
    if(eta > 0.00 && eta <= 0.20) musf=0.999931313261; // stat 0.00087221608917 syst 0.000349496328839 
    if(eta > 2.30 && eta <= 2.40) musf=1.00048918506; // stat 0.00165997192222 syst 0.000766695053841 
    if(eta > -0.30 && eta <= -0.20) musf=0.999136749056; // stat 0.00101993440532 syst 0.000504460823038 
    if(eta > 0.30 && eta <= 0.50) musf=0.99962886722; // stat 0.000788240966911 syst 0.000190264769964 
    if(eta > 1.20 && eta <= 1.40) musf=0.999553164257; // stat 0.000781586061471 syst 0.000107614114962 
}
if(pt>25.00 && pt<=30.00){
    if(eta > 0.50 && eta <= 0.80) musf=1.00042869732; // stat 0.00293326266133 syst 0.00111093871739 
    if(eta > -1.60 && eta <= -1.50) musf=0.998600901958; // stat 0.00375521315405 syst 0.000772649471568 
    if(eta > 2.00 && eta <= 2.10) musf=1.00165297112; // stat 0.00352691135049 syst 0.00117896999811 
    if(eta > -0.20 && eta <= 0.00) musf=0.994870290388; // stat 0.00338312930997 syst 0.00150867115793 
    if(eta > -1.20 && eta <= -0.80) musf=0.998930908627; // stat 0.00243691043495 syst 0.000607763691465 
    if(eta > -1.70 && eta <= -1.60) musf=0.998346359565; // stat 0.00392182978198 syst 0.000450598617482 
    if(eta > 1.40 && eta <= 1.50) musf=0.996409489631; // stat 0.0042484559976 syst 0.00156376011046 
    if(eta > -2.10 && eta <= -2.00) musf=1.00057996091; // stat 0.00427701937432 syst 0.00129305055672 
    if(eta > 2.10 && eta <= 2.20) musf=1.00058148533; // stat 0.00462947809382 syst 0.00129125794408 
    if(eta > -2.40 && eta <= -2.30) musf=0.998279345445; // stat 0.00435513888716 syst 0.000420431367031 
    if(eta > 2.20 && eta <= 2.30) musf=1.00496365526; // stat 0.00371975049353 syst 0.00116627373552 
    if(eta > -1.40 && eta <= -1.20) musf=0.999072921106; // stat 0.00326487848564 syst 0.000524785602731 
    if(eta > 1.70 && eta <= 2.00) musf=1.00038307456; // stat 0.00205397289254 syst 0.00104560403513 
    if(eta > 0.80 && eta <= 1.20) musf=1.00105050708; // stat 0.00247933735478 syst 0.00117850574006 
    if(eta > 0.20 && eta <= 0.30) musf=0.99561804042; // stat 0.00479529486751 syst 0.000603155920393 
    if(eta > -2.30 && eta <= -2.20) musf=1.00409071847; // stat 0.00374087734061 syst 0.00104899045546 
    if(eta > 1.60 && eta <= 1.70) musf=0.998097292295; // stat 0.00381193321665 syst 0.000913936570191 
    if(eta > -0.50 && eta <= -0.30) musf=0.996796804192; // stat 0.00349630278293 syst 0.000824558869524 
    if(eta > -2.20 && eta <= -2.10) musf=0.996225911969; // stat 0.00351053520469 syst 0.000592348169096 
    if(eta > 1.50 && eta <= 1.60) musf=1.00064955287; // stat 0.0039206519255 syst 0.000643055183411 
    if(eta > -2.00 && eta <= -1.70) musf=0.999316635772; // stat 0.00196629272969 syst 0.000838264809059 
    if(eta > -1.50 && eta <= -1.40) musf=0.998441347882; // stat 0.00405796638346 syst 0.000537493593643 
    if(eta > -0.80 && eta <= -0.50) musf=0.999725822904; // stat 0.002838015173 syst 0.000933595766724 
    if(eta > 0.00 && eta <= 0.20) musf=1.00075914875; // stat 0.0032756248339 syst 0.000530807057721 
    if(eta > 2.30 && eta <= 2.40) musf=0.994827534928; // stat 0.00423797788148 syst 0.00122514192544 
    if(eta > -0.30 && eta <= -0.20) musf=0.998452762532; // stat 0.00472875988854 syst 0.00117672231612 
    if(eta > 0.30 && eta <= 0.50) musf=0.998321926337; // stat 0.00350960835516 syst 0.000790074689313 
    if(eta > 1.20 && eta <= 1.40) musf=1.00031922743; // stat 0.00305710868093 syst 0.000888247070644 
}
if(pt>60.00){
    if(eta > 0.50 && eta <= 0.80) musf=0.999986938605; // stat 0.000853297826851 syst 0.000193600155811 
    if(eta > -1.60 && eta <= -1.50) musf=0.998943545176; // stat 0.00173796329505 syst 0.00153319552437 
    if(eta > 2.00 && eta <= 2.10) musf=0.998048845223; // stat 0.00164708252282 syst 0.000409748653144 
    if(eta > -0.20 && eta <= 0.00) musf=1.00018681808; // stat 0.00121065489098 syst 0.00078558402182 
    if(eta > -1.20 && eta <= -0.80) musf=1.00023774097; // stat 0.000837789100354 syst 0.00112403480987 
    if(eta > -1.70 && eta <= -1.60) musf=1.00030294672; // stat 0.0018346728727 syst 0.000914054311744 
    if(eta > 1.40 && eta <= 1.50) musf=1.00031030809; // stat 0.00144557708226 syst 0.00040315554877 
    if(eta > -2.10 && eta <= -2.00) musf=0.998368799868; // stat 0.00166855677013 syst 0.000694878079314 
    if(eta > 2.10 && eta <= 2.20) musf=1.00203720943; // stat 0.00223989277088 syst 0.0003377952664 
    if(eta > -2.40 && eta <= -2.30) musf=0.9972888727; // stat 0.00254582456203 syst 0.000718666752819 
    if(eta > 2.20 && eta <= 2.30) musf=1.00104479845; // stat 0.00256289512284 syst 0.000789714187735 
    if(eta > -1.40 && eta <= -1.20) musf=0.999024737385; // stat 0.00116098744824 syst 0.000790103580629 
    if(eta > 1.70 && eta <= 2.00) musf=0.999301093145; // stat 0.000980566253979 syst 0.000250790849345 
    if(eta > 0.80 && eta <= 1.20) musf=1.00045734967; // stat 0.000790540200579 syst 0.000404991998699 
    if(eta > 0.20 && eta <= 0.30) musf=0.999419619355; // stat 0.00166092019482 syst 0.000226757477126 
    if(eta > -2.30 && eta <= -2.20) musf=0.997963351448; // stat 0.00180358926235 syst 0.00101552911879 
    if(eta > 1.60 && eta <= 1.70) musf=0.998460107423; // stat 0.00128613432676 syst 0.000399591790068 
    if(eta > -0.50 && eta <= -0.30) musf=1.0002937232; // stat 0.0011878807448 syst 0.000343321745377 
    if(eta > -2.20 && eta <= -2.10) musf=1.00207101998; // stat 0.00216857178369 syst 0.00040270093046 
    if(eta > 1.50 && eta <= 1.60) musf=0.999069462541; // stat 0.00124291906128 syst 0.000303523510282 
    if(eta > -2.00 && eta <= -1.70) musf=0.999391472024; // stat 0.00112291620412 syst 0.000352316836736 
    if(eta > -1.50 && eta <= -1.40) musf=0.99959447897; // stat 0.00133660114879 syst 0.000278428261424 
    if(eta > -0.80 && eta <= -0.50) musf=0.999289929311; // stat 0.000900391114911 syst 0.000525217402934 
    if(eta > 0.00 && eta <= 0.20) musf=0.999279132377; // stat 0.00111406557951 syst 0.000274517716606 
    if(eta > 2.30 && eta <= 2.40) musf=1.00068372541; // stat 0.00304035691132 syst 0.00154578719728 
    if(eta > -0.30 && eta <= -0.20) musf=0.999574057956; // stat 0.00167479539394 syst 0.000577703245835 
    if(eta > 0.30 && eta <= 0.50) musf=1.00057278263; // stat 0.00115864435269 syst 0.000347096718432 
    if(eta > 1.20 && eta <= 1.40) musf=1.00116008947; // stat 0.00130743801763 syst 0.000193349494425 
}
if(pt>30.00 && pt<=40.00){
    if(eta > 0.50 && eta <= 0.80) musf=1.00026685759; // stat 0.000801364314054 syst 0.000195255920476 
    if(eta > -1.60 && eta <= -1.50) musf=1.00282366237; // stat 0.00131911910748 syst 0.000864492434752 
    if(eta > 2.00 && eta <= 2.10) musf=0.999553137985; // stat 0.0013027917555 syst 0.000360301857773 
    if(eta > -0.20 && eta <= 0.00) musf=0.998020768034; // stat 0.00101253932179 syst 0.00012945717508 
    if(eta > -1.20 && eta <= -0.80) musf=0.998843579556; // stat 0.000724864646397 syst 0.000219453649933 
    if(eta > -1.70 && eta <= -1.60) musf=1.00192983554; // stat 0.00135809200639 syst 0.00299445478487 
    if(eta > 1.40 && eta <= 1.50) musf=0.999690195097; // stat 0.00137891330705 syst 0.000616140056654 
    if(eta > -2.10 && eta <= -2.00) musf=0.999757355218; // stat 0.00122782564532 syst 0.000337064140863 
    if(eta > 2.10 && eta <= 2.20) musf=1.00009890494; // stat 0.00120166400453 syst 0.000484837499545 
    if(eta > -2.40 && eta <= -2.30) musf=1.00088506045; // stat 0.00159445210354 syst 0.000494404924116 
    if(eta > 2.20 && eta <= 2.30) musf=0.998145040104; // stat 0.00131021007037 syst 0.00026136472458 
    if(eta > -1.40 && eta <= -1.20) musf=0.997999687069; // stat 0.000983492206267 syst 0.000130588485506 
    if(eta > 1.70 && eta <= 2.00) musf=1.00049159862; // stat 0.000756409691695 syst 0.000280617575804 
    if(eta > 0.80 && eta <= 1.20) musf=0.999972905153; // stat 0.000748866902298 syst 0.000216635149475 
    if(eta > 0.20 && eta <= 0.30) musf=0.99846176596; // stat 0.00143225572428 syst 0.000456948046605 
    if(eta > -2.30 && eta <= -2.20) musf=0.999975940898; // stat 0.00130710129575 syst 0.000285201460441 
    if(eta > 1.60 && eta <= 1.70) musf=0.999435598044; // stat 0.0013851746488 syst 0.000318138221974 
    if(eta > -0.50 && eta <= -0.30) musf=0.998328399003; // stat 0.00100325846177 syst 0.000352040804161 
    if(eta > -2.20 && eta <= -2.10) musf=0.999704239815; // stat 0.0012811845104 syst 0.000143827492652 
    if(eta > 1.50 && eta <= 1.60) musf=1.00032575236; // stat 0.0012865635122 syst 0.000567701643864 
    if(eta > -2.00 && eta <= -1.70) musf=1.00126299161; // stat 0.000807917784617 syst 0.000582039544737 
    if(eta > -1.50 && eta <= -1.40) musf=1.00074450843; // stat 0.00151893796108 syst 0.000395950897878 
    if(eta > -0.80 && eta <= -0.50) musf=0.99958644003; // stat 0.000831067362169 syst 0.00024288069715 
    if(eta > 0.00 && eta <= 0.20) musf=0.998422849562; // stat 0.000984502395816 syst 0.000269280535558 
    if(eta > 2.30 && eta <= 2.40) musf=1.00055383834; // stat 0.00162186993463 syst 0.000587568369442 
    if(eta > -0.30 && eta <= -0.20) musf=0.998577573844; // stat 0.00146233371206 syst 0.000177568438931 
    if(eta > 0.30 && eta <= 0.50) musf=0.999662808211; // stat 0.000991096259802 syst 0.000227539389567 
    if(eta > 1.20 && eta <= 1.40) musf=0.998497831054; // stat 0.000953815127991 syst 0.000499265290381 
}
if(pt>40.00 && pt<=50.00){
    if(eta > 0.50 && eta <= 0.80) musf=0.999382296975; // stat 0.000200572274358 syst 9.65608600305e-05 
    if(eta > -1.60 && eta <= -1.50) musf=1.00010598225; // stat 2.20142818301e-05 syst 8.70168983816e-05 
    if(eta > 2.00 && eta <= 2.10) musf=0.999105492016; // stat 0.000391529168981 syst 0.000193367065619 
    if(eta > -0.20 && eta <= 0.00) musf=0.999023744877; // stat 0.00046198762297 syst 7.19821521897e-05 
    if(eta > -1.20 && eta <= -0.80) musf=0.999071249316; // stat 0.00028100792984 syst 3.45177889127e-05 
    if(eta > -1.70 && eta <= -1.60) musf=0.999898564845; // stat 0.000555538409339 syst 0.000249774223601 
    if(eta > 1.40 && eta <= 1.50) musf=0.999383505195; // stat 0.00357867780894 syst 6.50075023433e-05 
    if(eta > -2.10 && eta <= -2.00) musf=0.999904190174; // stat 0.000632479767266 syst 0.000174113579429 
    if(eta > 2.10 && eta <= 2.20) musf=0.999785993346; // stat 0.000390160547153 syst 7.78810523662e-05 
    if(eta > -2.40 && eta <= -2.30) musf=0.999660495892; // stat 0.000933619095287 syst 0.000235742210448 
    if(eta > 2.20 && eta <= 2.30) musf=0.999774100637; // stat 0.000648939620493 syst 0.000473939853184 
    if(eta > -1.40 && eta <= -1.20) musf=0.998897327957; // stat 0.000252500110638 syst 7.62533319306e-05 
    if(eta > 1.70 && eta <= 2.00) musf=0.999560115365; // stat 0.000297449762202 syst 7.05007384378e-05 
    if(eta > 0.80 && eta <= 1.20) musf=0.999632494093; // stat 0.000310735122778 syst 5.23444356675e-05 
    if(eta > 0.20 && eta <= 0.30) musf=0.999730230781; // stat 0.000613059526766 syst 0.000118365702112 
    if(eta > -2.30 && eta <= -2.20) musf=1.00063079528; // stat 0.000783662345555 syst 0.000215053621706 
    if(eta > 1.60 && eta <= 1.70) musf=0.999474654102; // stat 0.000350466505993 syst 0.000298451684094 
    if(eta > -0.50 && eta <= -0.30) musf=0.998951006001; // stat 0.000441879454498 syst 5.61428810521e-05 
    if(eta > -2.20 && eta <= -2.10) musf=0.999517510267; // stat 0.000230927749078 syst 0.000166130581584 
    if(eta > 1.50 && eta <= 1.60) musf=0.999665735474; // stat 0.000544607941736 syst 0.000130602086721 
    if(eta > -2.00 && eta <= -1.70) musf=0.999395044471; // stat 0.000101895688792 syst 5.22232610816e-05 
    if(eta > -1.50 && eta <= -1.40) musf=0.999662830647; // stat 0.00213208877173 syst 0.000221930611921 
    if(eta > -0.80 && eta <= -0.50) musf=0.999300696472; // stat 0.00577445236875 syst 5.31658909187e-05 
    if(eta > 0.00 && eta <= 0.20) musf=0.998783821716; // stat 0.000460692681013 syst 7.2079468231e-05 
    if(eta > 2.30 && eta <= 2.40) musf=1.00048933347; // stat 0.000949125560429 syst 0.00012604243703 
    if(eta > -0.30 && eta <= -0.20) musf=0.999330851985; // stat 0.00433974259204 syst 0.000169259372258 
    if(eta > 0.30 && eta <= 0.50) musf=0.999387818578; // stat 0.000396011106921 syst 7.41814465367e-05 
    if(eta > 1.20 && eta <= 1.40) musf=0.998969905219; // stat 0.000251184282033 syst 7.276866673e-05 
}
 
//https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2016_legacy_rereco/systematic/RunBCDEF_SF_ISO.json
//https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2016_legacy_rereco/systematic/RunGH_SF_ISO.json
//NUM_LooseRelIso_DEN_LooseID
//(pesoBF*L_BF + pesoGH*L_GH)/L_BH
 return musf;
}

double get_wgtlumi(string FileName){
 double wgt=1;

 //xsec in pb

 // checked, OK!
 
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
 if((FileName.find("mumujj_L13000_M1000") != std::string::npos)) wgt=2.8140e-03/100000;
 if((FileName.find("mumujj_L13000_M2000") != std::string::npos)) wgt=0.82140e-03/100000;
 if((FileName.find("mumujj_L13000_M5000") != std::string::npos)) wgt=0.014250e-03/100000;
 if((FileName.find("mumujj_L13000_M8000") != std::string::npos)) wgt=0.000091350e-03/91350;

 //electrons
 
 if((FileName.find("eejj_L13000_M500") != std::string::npos)) wgt=5.7090e-03/100000;
 if((FileName.find("eejj_L13000_M1000") != std::string::npos)) wgt=2.8140e-03/96800;
 if((FileName.find("eejj_L13000_M2000") != std::string::npos)) wgt=0.82140e-03/100000;
 if((FileName.find("eejj_L13000_M5000") != std::string::npos)) wgt=0.014250e-03/100000;
 if((FileName.find("eejj_L13000_M8000") != std::string::npos)) wgt=0.000091350e-03/91273;
 
 return wgt;
 }

