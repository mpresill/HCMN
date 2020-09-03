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
#include "RoccoR.cc"
#include "GEScaleSyst.cc"
#include "GEScaleSyst.h"

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
std::tuple<double, double, double> elesf(double eta, double pt);
std::tuple<double, double, double> musf_trigger(double eta,double pt);
std::tuple<double, double, double> musf_ID(double eta, double pt);
std::tuple<double, double, double> musf_iso(double eta, double pt);
double get_wgtlumi(string FileName);

/////
//   Main function
/////


void  filename_(const char*  Input = "", const char*  Output =""){

  Input = "inputFile";
  Output = "outputFile"; 
  TFile *oldfile = TFile::Open(Input);
  TTree *readingtree = new TTree("readingtree","readingtree"); readingtree = (TTree*) oldfile->Get("TNT/BOOM");

  // Rochester corrections
  RoccoR  rc("RoccoR2016.txt");
  GEScaleSyst *GE = new GEScaleSyst();
  /////
  //   Variables to read
  /////
  //Trigger
  int rHLT_Ele27_WPTight_Gsf; rHLT_Ele27_WPTight_Gsf = 0; TBranch* b_rHLT_Ele27_WPTight_Gsf = 0; readingtree->SetBranchAddress("HLT_Ele27_WPTight_Gsf",&rHLT_Ele27_WPTight_Gsf,&b_rHLT_Ele27_WPTight_Gsf);
  int rHLT_Photon175; rHLT_Photon175 = 0; TBranch* b_rHLT_Photon175 = 0; readingtree->SetBranchAddress("HLT_Photon175",&rHLT_Photon175,&b_rHLT_Photon175);
  int rHLT_Ele115_CaloIdVT_GsfTrkIdT; rHLT_Ele115_CaloIdVT_GsfTrkIdT = 0; TBranch* b_rHLT_Ele115_CaloIdVT_GsfTrkIdT = 0; readingtree->SetBranchAddress("HLT_Ele115_CaloIdVT_GsfTrkIdT",&rHLT_Ele115_CaloIdVT_GsfTrkIdT,&b_rHLT_Ele115_CaloIdVT_GsfTrkIdT);
  int rHLT_Mu50; rHLT_Mu50 = 0; TBranch* b_rHLT_Mu50 = 0; readingtree->SetBranchAddress("HLT_Mu50",&rHLT_Mu50,&b_rHLT_Mu50);
  int rHLT_TkMu50; rHLT_TkMu50 = 0; TBranch* b_rHLT_TkMu50 = 0; readingtree->SetBranchAddress("HLT_TkMu50",&rHLT_TkMu50,&b_rHLT_TkMu50);
  int rHLT_OldMu100; rHLT_OldMu100 = 0; TBranch* b_rHLT_OldMu100 = 0; readingtree->SetBranchAddress("HLT_OldMu100",&rHLT_OldMu100,&b_rHLT_OldMu100);
  int rHLT_TkMu100; rHLT_TkMu100 = 0; TBranch* b_rHLT_TkMu100 = 0; readingtree->SetBranchAddress("HLT_TkMu100",&rHLT_TkMu100,&b_rHLT_TkMu100);

  //Gen variables:
  vector<double>* rGen_pt; rGen_pt = 0; TBranch* b_rGen_pt = 0; readingtree->SetBranchAddress("Gen_pt",&rGen_pt,&b_rGen_pt);
  vector<double>* rGen_eta; rGen_eta = 0; TBranch* b_rGen_eta = 0; readingtree->SetBranchAddress("Gen_eta",&rGen_eta,&b_rGen_eta);
  vector<double>* rGen_phi; rGen_phi = 0; TBranch* b_rGen_phi = 0; readingtree->SetBranchAddress("Gen_phi",&rGen_phi,&b_rGen_phi);
  vector<double>* rGen_energy; rGen_energy = 0; TBranch* b_rGen_energy = 0; readingtree->SetBranchAddress("Gen_energy",&rGen_energy,&b_rGen_energy);
  vector<double>* rGen_charge; rGen_charge = 0; TBranch* b_rGen_charge = 0; readingtree->SetBranchAddress("Gen_charge",&rGen_charge,&b_rGen_charge);
  vector<double>* rGen_pdg_id; rGen_pdg_id = 0; TBranch* b_rGen_pdg_id = 0; readingtree->SetBranchAddress("Gen_pdg_id",&rGen_pdg_id,&b_rGen_pdg_id);
  vector<double>* rGen_motherpdg_id; rGen_motherpdg_id = 0; TBranch* b_rGen_motherpdg_id = 0; readingtree->SetBranchAddress("Gen_motherpdg_id",&rGen_motherpdg_id,&b_rGen_motherpdg_id);
  vector<double>* rGen_numDaught; rGen_numDaught = 0; TBranch* b_rGen_numDaught = 0; readingtree->SetBranchAddress("Gen_numDaught",&rGen_numDaught,&b_rGen_numDaught);
  vector<double>* rGen_numMother; rGen_numMother = 0; TBranch* b_rGen_numMother = 0; readingtree->SetBranchAddress("Gen_numMother",&rGen_numMother,&b_rGen_numMother);


  //PU and systematics
  double rPUWeight; rPUWeight = 0; TBranch* b_rPUWeight = 0; readingtree->SetBranchAddress("PUWeight",&rPUWeight,&b_rPUWeight);
  double rMinBiasUpWeight; rMinBiasUpWeight = 0; TBranch* b_rMinBiasUpWeight = 0; readingtree->SetBranchAddress("MinBiasUpWeight",&rMinBiasUpWeight,&b_rMinBiasUpWeight);
  double rMinBiasDownWeight; rMinBiasDownWeight = 0; TBranch* b_rMinBiasDownWeight = 0; readingtree->SetBranchAddress("MinBiasDownWeight",&rMinBiasDownWeight,&b_rMinBiasDownWeight);
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
  vector<int>* rMuon_TLayers; rMuon_TLayers = 0; TBranch* b_rMuon_TLayers = 0; readingtree->SetBranchAddress("Muon_TLayers", &rMuon_TLayers, &b_rMuon_TLayers);
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
  vector<double>* rpatElectron_energyScaleUp; rpatElectron_energyScaleUp = 0; TBranch* b_rpatElectron_energyScaleUp = 0; readingtree->SetBranchAddress("patElectron_energyScaleUp",&rpatElectron_energyScaleUp, &b_rpatElectron_energyScaleUp);
  vector<double>* rpatElectron_energyScaleDown; rpatElectron_energyScaleDown = 0; TBranch* b_rpatElectron_energyScaleDown = 0; readingtree->SetBranchAddress("patElectron_energyScaleDown",&rpatElectron_energyScaleDown, &b_rpatElectron_energyScaleDown);
 vector<double>* rpatElectron_energySigmaUp; rpatElectron_energySigmaUp = 0; TBranch* b_rpatElectron_energySigmaUp = 0; readingtree->SetBranchAddress("patElectron_energySigmaUp",&rpatElectron_energySigmaUp, &b_rpatElectron_energySigmaUp);
  vector<double>* rpatElectron_energySigmaDown; rpatElectron_energySigmaDown = 0; TBranch* b_rpatElectron_energySigmaDown = 0; readingtree->SetBranchAddress("patElectron_energySigmaDown",&rpatElectron_energySigmaDown, &b_rpatElectron_energySigmaDown);

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
  vector<double>* rBoostedJet_JerSF; rBoostedJet_JerSF = 0; TBranch* b_rBoostedJet_JerSF = 0; readingtree->SetBranchAddress("BoostedJet_JerSF",&rBoostedJet_JerSF,&b_rBoostedJet_JerSF);
  //JES systematics
  vector<double>* rBoostedJet_JesSFup; rBoostedJet_JesSFup = 0; TBranch* b_rBoostedJet_JesSFup = 0; readingtree->SetBranchAddress("BoostedJet_JesSFup",&rBoostedJet_JesSFup,&b_rBoostedJet_JesSFup);
  vector<double>* rBoostedJet_JesSFdown; rBoostedJet_JesSFdown = 0; TBranch* b_rBoostedJet_JesSFdown = 0; readingtree->SetBranchAddress("BoostedJet_JesSFdown",&rBoostedJet_JesSFdown,&b_rBoostedJet_JesSFdown);
  //JER systematics
  vector<double>* rBoostedJet_JerSFup; rBoostedJet_JerSFup = 0; TBranch* b_rBoostedJet_JerSFup = 0; readingtree->SetBranchAddress("BoostedJet_JerSFup",&rBoostedJet_JerSFup,&b_rBoostedJet_JerSFup);
  vector<double>* rBoostedJet_JerSFdown; rBoostedJet_JerSFdown = 0; TBranch* b_rBoostedJet_JerSFdown = 0; readingtree->SetBranchAddress("BoostedJet_JerSFdown",&rBoostedJet_JerSFdown,&b_rBoostedJet_JerSFdown);
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
   int HLT_Ele27_WPTight_Gsf; newtree->Branch("HLT_Ele27_WPTight_Gsf",&HLT_Ele27_WPTight_Gsf);
   int HLT_Photon175; newtree->Branch("HLT_Photon175",&HLT_Photon175);
   int HLT_Ele115_CaloIdVT_GsfTrkIdT; newtree->Branch("HLT_Ele115_CaloIdVT_GsfTrkIdT",&HLT_Ele115_CaloIdVT_GsfTrkIdT);
   int HLT_Mu50; newtree->Branch("HLT_Mu50",&HLT_Mu50);
   int HLT_TkMu50; newtree->Branch("HLT_TkMu50",&HLT_TkMu50);
   int HLT_OldMu100; newtree->Branch("HLT_OldMu100",&HLT_OldMu100);
   int HLT_TkMu100; newtree->Branch("HLT_TkMu100",&HLT_TkMu100);

  //Gen variables
  vector<double>* Gen_pt = new std::vector<double>; newtree->Branch("Gen_pt",&Gen_pt);
  vector<double>* Gen_eta = new std::vector<double>; newtree->Branch("Gen_eta",&Gen_eta);
  vector<double>* Gen_phi = new std::vector<double>; newtree->Branch("Gen_phi",&Gen_phi);
  vector<double>* Gen_charge = new std::vector<double>; newtree->Branch("Gen_charge",&Gen_charge);
  vector<double>* Gen_energy = new std::vector<double>; newtree->Branch("Gen_energy",&Gen_energy);
  vector<double>* Gen_pdg_id = new std::vector<double>; newtree->Branch("Gen_pdg_id",&Gen_pdg_id);
  vector<double>* Gen_motherpdg_id = new std::vector<double>; newtree->Branch("Gen_motherpdg_id",&Gen_motherpdg_id);
  vector<double>* Gen_numDaught = new std::vector<double>; newtree->Branch("Gen_numDaught",&Gen_numDaught);
  vector<double>* Gen_numMother = new std::vector<double>; newtree->Branch("Gen_numMother",&Gen_numMother);


   //Muons:
   vector<double>* Muon_pt = new std::vector<double>; newtree->Branch("Muon_pt",&Muon_pt);
   vector<double>* Muon_pt_corr = new std::vector<double>; newtree->Branch("Muon_pt_corr",&Muon_pt_corr);
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
  vector<double>* patElectron_energyScaleUp = new std::vector<double>; newtree->Branch("patElectron_energyScaleUp",&patElectron_energyScaleUp);
  vector<double>* patElectron_energyScaleDown = new std::vector<double>; newtree->Branch("patElectron_energyScaleDown",&patElectron_energyScaleDown);
  vector<double>* patElectron_energySigmaUp = new std::vector<double>; newtree->Branch("patElectron_energySigmaUp",&patElectron_energySigmaUp);
  vector<double>* patElectron_energySigmaDown = new std::vector<double>; newtree->Branch("patElectron_energySigmaDown",&patElectron_energySigmaDown);
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

   //systematics sf tags: 
   vector<double>* centralJesJer = new std::vector<double>; newtree->Branch("centralJesJer",&centralJesJer);
   vector<double>* JesSFup = new std::vector<double>; newtree->Branch("JesSFup",&JesSFup);
   vector<double>* JesSFdown = new std::vector<double>; newtree->Branch("JesSFdown",&JesSFdown);
   vector<double>* JerSFup = new std::vector<double>; newtree->Branch("JerSFup",&JerSFup);
   vector<double>* JerSFdown = new std::vector<double>; newtree->Branch("JerSFdown",&JerSFdown);


   //PU:
   double PileupWeight; newtree->Branch("PileupWeight",&PileupWeight);
   double PUWeight; newtree->Branch("PUWeight",&PUWeight);
   double MinBiasUpWeight; newtree->Branch("MinBiasUpWeight",&MinBiasUpWeight);
   double MinBiasDownWeight; newtree->Branch("MinBiasDownWeight",&MinBiasDownWeight);
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
   double elesf_ele1_d; newtree->Branch("elesf_ele1_d",&elesf_ele1_d);
   double elesf_ele2_d; newtree->Branch("elesf_ele2_d",&elesf_ele2_d);
   double elesf_ele1_u; newtree->Branch("elesf_ele1_u",&elesf_ele1_u);
   double elesf_ele2_u; newtree->Branch("elesf_ele2_u",&elesf_ele2_u);

   double musf_trigger_mu1; newtree->Branch("musf_trigger_mu1",&musf_trigger_mu1);
   double musf_ID_mu1; newtree->Branch("musf_ID_mu1",&musf_ID_mu1);
   double musf_iso_mu1; newtree->Branch("musf_iso_mu1",&musf_iso_mu1);
   double musf_tot_mu1; newtree->Branch("musf_tot_mu1",&musf_tot_mu1);
   double musf_trigger_mu2; newtree->Branch("musf_trigger_mu2",&musf_trigger_mu2);
   double musf_ID_mu2; newtree->Branch("musf_ID_mu2",&musf_ID_mu2);
   double musf_iso_mu2; newtree->Branch("musf_iso_mu2",&musf_iso_mu2);
   double musf_tot_mu2; newtree->Branch("musf_tot_mu2",&musf_tot_mu2);

   double musf_trigger_mu1_u; newtree->Branch("musf_trigger_mu1_u",&musf_trigger_mu1_u);
   double musf_ID_mu1_u; newtree->Branch("musf_ID_mu1_u",&musf_ID_mu1_u);
   double musf_iso_mu1_u; newtree->Branch("musf_iso_mu1_u",&musf_iso_mu1_u);
   double musf_tot_mu1_u; newtree->Branch("musf_tot_mu1_u",&musf_tot_mu1_u);
   double musf_trigger_mu2_u; newtree->Branch("musf_trigger_mu2_u",&musf_trigger_mu2_u);
   double musf_ID_mu2_u; newtree->Branch("musf_ID_mu2_u",&musf_ID_mu2_u);
   double musf_iso_mu2_u; newtree->Branch("musf_iso_mu2_u",&musf_iso_mu2_u);
   double musf_tot_mu2_u; newtree->Branch("musf_tot_mu2_u",&musf_tot_mu2_u);

   double musf_trigger_mu1_d; newtree->Branch("musf_trigger_mu1_d",&musf_trigger_mu1_d);
   double musf_ID_mu1_d; newtree->Branch("musf_ID_mu1_d",&musf_ID_mu1_d);
   double musf_iso_mu1_d; newtree->Branch("musf_iso_mu1_d",&musf_iso_mu1_d);
   double musf_tot_mu1_d; newtree->Branch("musf_tot_mu1_d",&musf_tot_mu1_d);
   double musf_trigger_mu2_d; newtree->Branch("musf_trigger_mu2_d",&musf_trigger_mu2_d);
   double musf_ID_mu2_d; newtree->Branch("musf_ID_mu2_d",&musf_ID_mu2_d);
   double musf_iso_mu2_d; newtree->Branch("musf_iso_mu2_d",&musf_iso_mu2_d);
   double musf_tot_mu2_d; newtree->Branch("musf_tot_mu2_d",&musf_tot_mu2_d);

   double lepsf_evt; newtree->Branch("lepsf_evt",&lepsf_evt);
   double lepsf_evt_u; newtree->Branch("lepsf_evt_u",&lepsf_evt_u);
   double lepsf_evt_d; newtree->Branch("lepsf_evt_d",&lepsf_evt_d);

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
    
    b_rHLT_Ele27_WPTight_Gsf->GetEntry(en);
    b_rHLT_Photon175->GetEntry(en);
    b_rHLT_Ele115_CaloIdVT_GsfTrkIdT->GetEntry(en);
    b_rHLT_Mu50->GetEntry(en);
    b_rHLT_TkMu50->GetEntry(en);
    b_rHLT_OldMu100->GetEntry(en); 
    b_rHLT_TkMu100->GetEntry(en);
    //PU:
    b_rPUWeight->GetEntry(en);
    b_rMinBiasUpWeight->GetEntry(en);
    b_rMinBiasDownWeight->GetEntry(en);
    b_rnBestVtx->GetEntry(en);
    b_rtrueInteractions->GetEntry(en);

    //Gen variables
    b_rGen_pt->GetEntry(en);
    b_rGen_eta->GetEntry(en);
    b_rGen_phi->GetEntry(en);
    b_rGen_charge->GetEntry(en);
    b_rGen_energy->GetEntry(en);
    b_rGen_pdg_id->GetEntry(en);
    b_rGen_motherpdg_id->GetEntry(en);
    b_rGen_numDaught->GetEntry(en);
    b_rGen_numMother->GetEntry(en);


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
    b_rMuon_TLayers->GetEntry(en);
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
    b_rpatElectron_energyScaleUp->GetEntry(en);
    b_rpatElectron_energyScaleDown->GetEntry(en);
    b_rpatElectron_energySigmaUp->GetEntry(en);
    b_rpatElectron_energySigmaDown->GetEntry(en);
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
    b_rBoostedJet_JerSF->GetEntry(en);
    //systematics Jes
    b_rBoostedJet_JesSFup->GetEntry(en);
    b_rBoostedJet_JesSFdown->GetEntry(en);
    //systematics Jer
    b_rBoostedJet_JerSFup->GetEntry(en);
    b_rBoostedJet_JerSFdown->GetEntry(en);

    //b-tagging:
    b_rBoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags->GetEntry(en);    
    //MET
    b_rMet_type1PF_pt->GetEntry(en);

   //Gen variables to be written
    Gen_pt->clear();    
    Gen_eta->clear();    
    Gen_phi->clear();    
    Gen_charge->clear();    
    Gen_energy->clear();    
    Gen_pdg_id->clear();    
    Gen_motherpdg_id->clear();    
    Gen_numDaught->clear();    
    Gen_numMother->clear();    
    
    
    //New var clear (vectors):
    Muon_pt->clear();
    Muon_pt_corr->clear();
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
    patElectron_energyScaleUp->clear();
    patElectron_energyScaleDown->clear();
    patElectron_energySigmaUp->clear();
    patElectron_energySigmaDown->clear();
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
    //evt type systematics
    centralJesJer ->clear(); 
    JesSFup ->clear(); 
    JesSFdown ->clear();
    JerSFup ->clear(); 
    JerSFdown ->clear();


    //new var inizialize (scalars):
    HLT_Ele27_WPTight_Gsf = -999;
    HLT_Photon175 = -999;
    HLT_Ele115_CaloIdVT_GsfTrkIdT = -999;
    HLT_TkMu50 = -999;
    HLT_Mu50 = -999;
    HLT_TkMu100 = -999;
    HLT_OldMu100 = -999;

    PUWeight = -999; MinBiasUpWeight = -999; MinBiasDownWeight = -999; nBestVtx = -999; trueInteractions = -999; lumi_wgt = -999; 
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

    //evt_type = -999;
    eejj_l = 0; emujj_l = 0; mumujj_l = 0; muejj_l = 0;
    SRe = 0; TRe = 0; SRmu = 0; TRmu = 0; DYRe = 0; DYRmu = 0;
    

    
   HLT_Ele27_WPTight_Gsf = rHLT_Ele27_WPTight_Gsf;
   HLT_Photon175 = rHLT_Photon175;
   HLT_Ele115_CaloIdVT_GsfTrkIdT = rHLT_Ele115_CaloIdVT_GsfTrkIdT;
   HLT_Mu50 = rHLT_Mu50;
   HLT_TkMu50 = rHLT_TkMu50;
   HLT_OldMu100 = rHLT_OldMu100;
   HLT_TkMu100 = rHLT_TkMu100;

    PUWeight = rPUWeight;
    MinBiasUpWeight = rMinBiasUpWeight;
    MinBiasDownWeight = rMinBiasDownWeight;
    //trueInteractions = rtrueInteractions;
    if(rtrueInteractions > 0) trueInteractions = (double)rtrueInteractions;
    nBestVtx = rnBestVtx;
    PileupWeight = CalculatePileupWeight(trueInteractions);
    lumi_wgt = get_wgtlumi(Input);
   
   for(uint gen_en = 0; gen_en<rGen_pt->size(); gen_en++){
    //Gen variables (writing)
    Gen_pt->push_back(rGen_pt->at(gen_en));
    Gen_eta->push_back(rGen_eta->at(gen_en));
    Gen_phi->push_back(rGen_phi->at(gen_en));
    Gen_charge->push_back(rGen_charge->at(gen_en));
    Gen_energy->push_back(rGen_energy->at(gen_en));
    Gen_pdg_id->push_back(rGen_pdg_id->at(gen_en));
    Gen_motherpdg_id->push_back(rGen_motherpdg_id->at(gen_en));
    Gen_numDaught->push_back(rGen_numDaught->at(gen_en));
    Gen_numMother->push_back(rGen_numMother->at(gen_en));
   }
   
   int num = 0;
   for(uint mu_en = 0; mu_en<rMuon_pt->size(); mu_en++){
    if( rMuon_pt->at(mu_en)>20 && fabs(rMuon_eta->at(mu_en))<2.4){
     if(rMuon_loose->at(mu_en)==1 && rMuon_TrackerIso->at(mu_en)<0.1) numOfLooseMu++;
     if(rMuon_medium->at(mu_en)==1 && rMuon_TrackerIso->at(mu_en)<0.1) numOfMediumMu++;
     if(rMuon_tight->at(mu_en)==1 && rMuon_TrackerIso->at(mu_en)<0.1) numOfTightMu++;
     if(rMuon_isHighPt->at(mu_en)==1 && rMuon_TrackerIso->at(mu_en)<0.1){
      numOfHighptMu++;

      Muon_pt->push_back(rMuon_pt->at(mu_en));

      if(rMuon_pt->at(mu_en) < 200 ){
       double mcSF = rc.kSmearMC(rMuon_charge->at(mu_en), rMuon_pt->at(mu_en), rMuon_eta->at(mu_en), rMuon_phi->at(mu_en), rMuon_TLayers->at(mu_en), gRandom->Rndm(), 0, 0);
       Muon_pt_corr->push_back(rMuon_pt->at(mu_en)*mcSF);
      }
      else{
       num = 49 * gRandom->Rndm();
       float pt_corr = GE->GEScaleCorrPt(160000+(int)num, (float) rMuon_pt->at(mu_en), (float) rMuon_eta->at(mu_en),(float) rMuon_phi->at(mu_en), (int) rMuon_charge->at(mu_en), false);
       Muon_pt_corr->push_back((double) pt_corr);
      }

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
      patElectron_energyScaleUp->push_back(rpatElectron_energyScaleUp->at(ele_en));
      patElectron_energyScaleDown->push_back(rpatElectron_energyScaleUp->at(ele_en));
      patElectron_energySigmaUp->push_back(rpatElectron_energySigmaUp->at(ele_en));
      patElectron_energySigmaDown->push_back(rpatElectron_energySigmaUp->at(ele_en));
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
      double DR_jetele = sqrt(pow(deltaPhi(patElectron_phi->at(ele_en),JetCorr.Phi()),2)+pow(patElectron_eta->at(ele_en)-JetCorr.Eta(),2) );
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
      double DR_jetele = sqrt(pow(deltaPhi(patElectron_phi->at(ele_en),JetCorr.Phi()),2)+pow(patElectron_eta->at(ele_en)-JetCorr.Eta(),2) );
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
    

    count = 0;
    if(Jet_isIDT==true){
     //cout << "pt dei jet dopo la sel: " <<JetCorr.Pt() << endl;
     //Jet cleaning: 
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




  /////////////////////////////////////////////////
   ///////corrections on boosted jets with systematics up and down
   ////////////////////////////////////////////////
   bool BoostedJet_isIDL=false;
   bool BoostedJet_isIDT=false;
   bool BoostedJet_isIDTLV=false;
   //bool BoostedJet_isID=false;
   int countBoostedJets=0;
   int countBoostedJets_L=0;
   int countBoostedJets_T=0;
   int countBoostedJets_TLV=0;
   //////////////////////////////////////
   numOfBoostedJets = 0;
   bool BoostedJet_isIDT_first = false;

   for(uint jet_en = 0; jet_en<rBoostedJet_pt->size(); jet_en++){

    for (int BJETSF = 0; BJETSF < 5; BJETSF++){//this for is for running different JesSF corrections (central value=0, JesUp=1, JesDown=2, JerUp=3, JerDown=4)
  
      ///////////////////////////////////////boosted jet cleaning and definition starts here
       BoostedJet_isIDL=false;
       BoostedJet_isIDT=false;
       BoostedJet_isIDTLV=false;
      //bool BoostedJet_isID=false;
       //countBoostedJets=0;
       //countBoostedJets_L=0;
       //countBoostedJets_T=0;
       //countBoostedJets_TLV=0;
       ////jes/jer syst
       double JesSF=0, JerSF=0;
       double centr_JJ = 0, upJES = 0, downJES = 0, upJER = 0, downJER = 0;

        if(BJETSF==0){      //BJet corrections with central values of JER/JES:
            JesSF = rBoostedJet_JesSF->at(jet_en);
            JerSF = rBoostedJet_JerSF->at(jet_en);
            centr_JJ = 1;
            upJES = 0;
            downJES = 0;
            upJER = 0;
            downJER = 0;
          }
        if(BJETSF==1){      //BJet corrections with JES SF UP:
            JesSF = rBoostedJet_JesSFup->at(jet_en);
            JerSF = rBoostedJet_JerSF->at(jet_en);
            centr_JJ = 0;
            upJES = 1;
            downJES = 0;
            upJER = 0;
            downJER = 0;
        }
        if(BJETSF==2){      //BJet corrections with JES SF DOWN:
            JesSF = rBoostedJet_JesSFdown->at(jet_en);
            JerSF = rBoostedJet_JerSF->at(jet_en);
            centr_JJ = 0;
            upJES = 0;
            downJES = 1;
            upJER = 0;
            downJER = 0;
        }
        if(BJETSF==3){      //BJet corrections with JER DOWN:
            JesSF = rBoostedJet_JesSF->at(jet_en);
            JerSF = rBoostedJet_JerSFup->at(jet_en);
            centr_JJ = 0;
            upJES = 0;
            downJES = 0;
            upJER = 1;
            downJER = 0;
          }
        if(BJETSF==4){      //BJet corrections with JER UP:
            JesSF = rBoostedJet_JesSF->at(jet_en);
            JerSF = rBoostedJet_JerSFdown->at(jet_en);
            centr_JJ = 0;
            upJES = 0;
            downJES = 0;
            upJER = 0;
            downJER = 1;
          }
          
      
        //BJet SFs:
        double jet_pt = rBoostedJet_Uncorr_pt->at(jet_en)*JesSF*JerSF;
        double jet_energy=rBoostedJet_energy->at(jet_en)*rBoostedJet_Uncorr_pt->at(jet_en)/rBoostedJet_pt->at(jet_en)*JesSF*JerSF;
        TLorentzVector JetCorr(0,0,0,0); JetCorr.SetPtEtaPhiE(jet_pt, rBoostedJet_eta->at(jet_en), rBoostedJet_phi->at(jet_en), jet_energy);
        ////syst
        //definition of JetCorr from the central value for Boosted Jet ID requirement
        double jet_pt_ID = rBoostedJet_Uncorr_pt->at(jet_en)*rBoostedJet_JesSF->at(jet_en)*rBoostedJet_JerSF->at(jet_en);
        TLorentzVector JetCorr_ID(0,0,0,0); JetCorr_ID.SetPtEtaPhiE(jet_pt_ID, rBoostedJet_eta->at(jet_en), rBoostedJet_phi->at(jet_en), jet_energy);
        ///


    //BJet ID:
    BoostedJet_isIDL = BoostedJetID_Loose(JetCorr_ID.Pt(),fabs(JetCorr_ID.Eta()),rBoostedJet_neutralHadEnergyFraction->at(jet_en),
    rBoostedJet_neutralEmEmEnergyFraction->at(jet_en),rBoostedJet_numberOfConstituents->at(jet_en),rBoostedJet_muonEnergyFraction->at(jet_en),
    rBoostedJet_chargedHadronEnergyFraction->at(jet_en),rBoostedJet_chargedMultiplicity->at(jet_en),
    rBoostedJet_chargedEmEnergyFraction->at(jet_en));
    BoostedJet_isIDT = BoostedJetID_Tight(JetCorr_ID.Pt(),fabs(JetCorr_ID.Eta()),rBoostedJet_neutralHadEnergyFraction->at(jet_en),
    rBoostedJet_neutralEmEmEnergyFraction->at(jet_en),rBoostedJet_numberOfConstituents->at(jet_en),rBoostedJet_muonEnergyFraction->at(jet_en),
    rBoostedJet_chargedHadronEnergyFraction->at(jet_en),rBoostedJet_chargedMultiplicity->at(jet_en),
    rBoostedJet_chargedEmEnergyFraction->at(jet_en));
    BoostedJet_isIDTLV = BoostedJetID_TightLepVeto(JetCorr_ID.Pt(),fabs(JetCorr_ID.Eta()),rBoostedJet_neutralHadEnergyFraction->at(jet_en),
    rBoostedJet_neutralEmEmEnergyFraction->at(jet_en),rBoostedJet_numberOfConstituents->at(jet_en),rBoostedJet_muonEnergyFraction->at(jet_en),
    rBoostedJet_chargedHadronEnergyFraction->at(jet_en),rBoostedJet_chargedMultiplicity->at(jet_en),
    rBoostedJet_chargedEmEnergyFraction->at(jet_en));


    //forse anche le prossime righe che servono per il conteggio del numero di Boosted Jet nell'evento devono usare la definizion del JetCorr_ID

    count = 0;
    if(BoostedJet_isIDT_first==true){
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
      if(BJETSF == 0){
       countBoostedJets++;
       numOfBoostedJets=countBoostedJets;
      } 
      BoostedJet_pt->push_back(JetCorr.Pt());
      BoostedJet_eta->push_back(JetCorr.Eta());
      BoostedJet_phi->push_back(JetCorr.Phi());
      BoostedJet_energy->push_back(rBoostedJet_energy->at(jet_en));
      BoostedJet_mass->push_back(rBoostedJet_mass->at(jet_en));
      BoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags->push_back(rBoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags->at(jet_en));      
     ///syst event flag
      centralJesJer->push_back(centr_JJ);
      JesSFup->push_back(upJES);
      JesSFdown->push_back(downJES);
      JerSFup->push_back(upJER);
      JerSFdown->push_back(downJER);
      //BoostedJet_nJets->push_back(0);
     }
    }
   }
   //numOfBoostedJets=countBoostedJets;
   numOfBoostedJets_L=countBoostedJets_L;
   numOfBoostedJets_T=countBoostedJets_T;
   numOfBoostedJets_TLV=countBoostedJets_TLV;


    ///////
    }//end for on BJETSF for systematics
    //////////




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
   


///////////////////////////////////////
///lepton scale factor part begins here
   if(eejj_l==1){
    std::tie(elesf_ele1, elesf_ele1_d, elesf_ele1_u)=elesf(patElectron_eta->at(0), patElectron_pt->at(0));
    std::tie(elesf_ele2, elesf_ele2_d, elesf_ele2_u)=elesf(patElectron_eta->at(1), patElectron_pt->at(1));
    lepsf_evt=elesf_ele1*elesf_ele2;
    lepsf_evt_d=elesf_ele1_d*elesf_ele2_d;
    lepsf_evt_u=elesf_ele1_u*elesf_ele2_u;
    //cout << elesf_ele1 << endl;
   }
 
  if(emujj_l==1){
    std::tie(elesf_ele1, elesf_ele1_d, elesf_ele1_u)=elesf(patElectron_eta->at(0), patElectron_pt->at(0));
    //musf_trigger_mu1=musf_trigger(Muon_eta->at(0),Muon_pt->at(0));
    std::tie(musf_ID_mu1, musf_ID_mu1_d, musf_ID_mu1_u)=musf_ID(Muon_eta->at(0),Muon_pt->at(0));
    std::tie(musf_iso_mu1, musf_iso_mu1_d, musf_iso_mu1_u)=musf_iso(Muon_eta->at(0),Muon_pt->at(0));
    //musf_tot_mu1=musf_trigger_mu1*musf_ID_mu1*musf_iso_mu1;
    musf_tot_mu1=musf_ID_mu1*musf_iso_mu1;
    musf_tot_mu1_d=musf_ID_mu1_d*musf_iso_mu1_d;
    musf_tot_mu1_u=musf_ID_mu1_u*musf_iso_mu1_u;
    lepsf_evt=elesf_ele1*musf_tot_mu1;
    lepsf_evt_d=elesf_ele1_d*musf_tot_mu1_d;
    lepsf_evt_u=elesf_ele1_u*musf_tot_mu1_u;

   }

   if(muejj_l==1){
    std::tie(elesf_ele1, elesf_ele1_d, elesf_ele1_u)=elesf(patElectron_eta->at(0), patElectron_pt->at(0));
    std::tie(musf_trigger_mu1, musf_trigger_mu1_d, musf_trigger_mu1_u)=musf_trigger(Muon_eta->at(0),Muon_pt->at(0));
    std::tie(musf_ID_mu1, musf_ID_mu1_d, musf_ID_mu1_u)=musf_ID(Muon_eta->at(0),Muon_pt->at(0));
    std::tie(musf_iso_mu1, musf_iso_mu1_d, musf_iso_mu1_u)=musf_iso(Muon_eta->at(0),Muon_pt->at(0));
    musf_tot_mu1=musf_trigger_mu1*musf_ID_mu1*musf_iso_mu1;
    musf_tot_mu1_d=musf_trigger_mu1_d*musf_ID_mu1_d*musf_iso_mu1_d;
    musf_tot_mu1_u=musf_trigger_mu1_u*musf_ID_mu1_u*musf_iso_mu1_u;
    lepsf_evt=elesf_ele1*musf_tot_mu1;
    lepsf_evt_d=elesf_ele1_d*musf_tot_mu1_d;
    lepsf_evt_u=elesf_ele1_u*musf_tot_mu1_u;
   }

    if(mumujj_l==1){
    std::tie(musf_trigger_mu1, musf_trigger_mu1_d, musf_trigger_mu1_u)=musf_trigger(Muon_eta->at(0),Muon_pt->at(0));
    std::tie(musf_ID_mu1, musf_ID_mu1_d, musf_ID_mu1_u)=musf_ID(Muon_eta->at(0),Muon_pt->at(0));
    std::tie(musf_iso_mu1, musf_iso_mu1_d, musf_iso_mu1_u)=musf_iso(Muon_eta->at(0),Muon_pt->at(0));
    musf_tot_mu1=musf_trigger_mu1*musf_ID_mu1*musf_iso_mu1;
    musf_tot_mu1_d=musf_trigger_mu1_d*musf_ID_mu1_d*musf_iso_mu1_d;
    musf_tot_mu1_u=musf_trigger_mu1_u*musf_ID_mu1_u*musf_iso_mu1_u;

    //musf_trigger_mu2=musf_trigger(Muon_eta->at(1),Muon_pt->at(1));
    std::tie(musf_ID_mu2, musf_ID_mu2_d, musf_ID_mu2_u)=musf_ID(Muon_eta->at(1),Muon_pt->at(1));
    std::tie(musf_iso_mu2, musf_iso_mu2_d, musf_iso_mu2_u)=musf_iso(Muon_eta->at(1),Muon_pt->at(1));
    //musf_tot_mu2=musf_trigger_mu2*musf_ID_mu2*musf_iso_mu2;
    musf_tot_mu2=musf_ID_mu2*musf_iso_mu2;
    musf_tot_mu2_d=musf_ID_mu2_d*musf_iso_mu2_d;
    musf_tot_mu2_u=musf_ID_mu2_u*musf_iso_mu2_u;

    lepsf_evt=musf_tot_mu1*musf_tot_mu2;
    lepsf_evt_d=musf_tot_mu1_d*musf_tot_mu2_d;
    lepsf_evt_u=musf_tot_mu1_u*musf_tot_mu2_u;

  }   
///lepton scale factor ends begins here
///////////////////////////////////////    

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
/* double data[] =  {5.64297e-05,0.000269623,0.000382956,0.000552844,0.000979931,0.00231634,0.0072801,0.0281133,0.0770196,0.130953,0.169536,0.182158,0.161879,0.116249,0.067104,0.0316937,0.0130125,0.00540404,0.00265731,0.00140593,0.000649204,0.000236783,6.7861e-05,1.63211e-05,3.82396e-06,1.03356e-06,3.33506e-07,1.1967e-07,4.49699e-08,1.70463e-08,6.34643e-09,2.28001e-09,7.82427e-10,2.55149e-10,7.88717e-11,2.30861e-11,6.39564e-12,1.67664e-12,4.15902e-13,9.76172e-14,2.16793e-14,4.55562e-15,9.05813e-16,1.70419e-16,3.03394e-17,5.11017e-18,8.14821e-19,1.20894e-19,2.20432e-20,0,0};
 double mc[] = {0.000108643,0.000388957,0.000332882,0.00038397,0.000549167,0.00105412,0.00459007,0.0210314,0.0573688,0.103986,0.142369,0.157729,0.147685,0.121027,0.08855,0.0582866,0.0348526,0.019457,0.0107907,0.00654313,0.00463195,0.00370927,0.0031137,0.00261141,0.00215499,0.00174491,0.00138268,0.00106731,0.000798828,0.00057785,0.00040336,0.00027161,0.000176535,0.00011092,6.75502e-05,4.00323e-05,2.32123e-05,1.32585e-05,7.51611e-06,4.25902e-06,2.42513e-06,1.39077e-06,8.02452e-07,4.64159e-07,2.67845e-07,1.5344e-07,8.68966e-08,4.84931e-08,2.6606e-08,1.433e-08};
 double puw;
 puw=data[trueInteractions]/mc[trueInteractions];
*/
 double puw_[] = {0.366077 , 0.893925 , 1.19772 , 0.962699 , 1.12098 , 1.16486 , 0.795599 , 0.495824 , 0.742182 , 0.878856 , 0.964232 , 1.0725 , 1.12534 , 1.17603 , 1.20208 , 1.20764 , 1.20018 , 1.18268 , 1.144 , 1.09663 , 1.0656 , 1.05117 , 1.0516 , 1.05063 , 1.04986 , 1.05817 , 1.07216 , 1.08303 , 1.09569 , 1.10787 , 1.09462 , 1.08262 , 1.04125 , 0.985752 , 0.910807 , 0.820922 , 0.716787 , 0.610013 , 0.503118 , 0.404841 , 0.309195 , 0.22792 , 0.16369 , 0.11318 , 0.0773005 , 0.0509221 , 0.0318936 , 0.0200936 , 0.0122631 , 0.00742646 , 0.00438028 , 0.00260777 , 0.00156599 , 0.000971358 , 0.000729206 , 0.000672709 , 0.000730459 , 0.000948791 , 0.00135533 , 0.00189419 , 0.00308244 , 0.00409665 , 0.00487449 , 0.00525606 , 0.00578498 , 0.00551468 , 0.00500046 , 0.00440983 , 0.00401224 , 0.00354754 , 0.00310751 , 0.00270211 , 0.00233691 , 0.00202529 , 0.00172328 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0};
 double puw=puw_[trueInteractions];
 return puw;
}

std::tuple<double, double, double> elesf(double eta, double pt){
 double elesf=0, elesf_d=0, elesf_u=0;
 if(fabs(eta) < 1.4442) {elesf = 0.971; elesf_d=0.970; elesf_u=0.972;} // stat 0.001
 if(fabs(eta) >= 1.566 && fabs(eta) < 2.5){elesf = 0.983; elesf_d=0.982; elesf_u=0.984;} // stat 0.001

 return std::make_tuple(elesf, elesf_d, elesf_u);
 //return elesf;
 
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
std::tuple<double, double, double>  musf_trigger(double eta, double pt){
 double musf=0, musf_d = 0, musf_u = 0;
if(pt>80.0 && pt<=120.0){
    if(eta > 0.0 && eta <= 0.9) {musf=0.979348945351;  musf_d=0.977265714365; musf_u=0.981432176337;} 
    if(eta > 1.2 && eta <= 2.1) {musf=0.991559553185;  musf_d=0.988111925646; musf_u=0.995007180724;} 
    if(eta > 2.1 && eta <= 2.4) {musf=0.945687243525;  musf_d=0.935909294895; musf_u=0.955465192155;} 
    if(eta > 0.9 && eta <= 1.2) {musf=0.953858663675;  musf_d=0.950632342712; musf_u=0.957084984637;} 
}
if(pt>120.0 && pt<=200.0){
    if(eta > 0.0 && eta <= 0.9) {musf=0.971963141223;  musf_d=0.968380013463; musf_u=0.975546268983;} 
    if(eta > 1.2 && eta <= 2.1) {musf=0.997236642678;  musf_d=0.98966441714; musf_u=1.00480886822;} 
    if(eta > 2.1 && eta <= 2.4) {musf=0.964864307448;  musf_d=0.937640130163; musf_u=0.992088484733;} 
    if(eta > 0.9 && eta <= 1.2) {musf=0.940906087621;  musf_d=0.931374554136; musf_u=0.950437621107;} 
}
if(pt>400.0){
    if(eta > 0.0 && eta <= 0.9) {musf=0.965216120987;  musf_d=0.916600471829; musf_u=1.01383177014;} 
    if(eta > 1.2 && eta <= 2.1) {musf=0.90780463359;  musf_d=0.71762718827; musf_u=1.09798207891;} 
    if(eta > 2.1 && eta <= 2.4) {musf=0.720766933187;  musf_d=-0.275871437504; musf_u=1.71740530388;} 
    if(eta > 0.9 && eta <= 1.2) {musf=0.975444916201;  musf_d=0.897421601101; musf_u=1.0534682313;} 
}
if(pt>55.0 && pt<=60.0){
    if(eta > 0.0 && eta <= 0.9) {musf=0.982172313956;  musf_d=0.98125723782; musf_u=0.983087390092;} 
    if(eta > 1.2 && eta <= 2.1) {musf=0.993104561456;  musf_d=0.991531453531; musf_u=0.994677669381;} 
    if(eta > 2.1 && eta <= 2.4) {musf=0.935460280411;  musf_d=0.931382829152; musf_u=0.93953773167;} 
    if(eta > 0.9 && eta <= 1.2) {musf=0.958748861806;  musf_d=0.957374459366; musf_u=0.960123264245;} 
}
if(pt>52.0 && pt<=55.0){
    if(eta > 0.0 && eta <= 0.9) {musf=0.97765533033;  musf_d=0.976781956431; musf_u=0.97852870423;} 
    if(eta > 1.2 && eta <= 2.1) {musf=0.987151898728;  musf_d=0.985680420903; musf_u=0.988623376552;} 
    if(eta > 2.1 && eta <= 2.4) {musf=0.918599081349;  musf_d=0.914578055895; musf_u=0.922620106803;} 
    if(eta > 0.9 && eta <= 1.2) {musf=0.953752562062;  musf_d=0.952694388101; musf_u=0.954810736023;} 
}
if(pt>60.0 && pt<=80.0){
    if(eta > 0.0 && eta <= 0.9) {musf=0.981439045142;  musf_d=0.980585398465; musf_u=0.982292691819;} 
    if(eta > 1.2 && eta <= 2.1) {musf=0.994310399764;  musf_d=0.992856147299; musf_u=0.99576465223;} 
    if(eta > 2.1 && eta <= 2.4) {musf=0.940574201481;  musf_d=0.936698312831; musf_u=0.944450090132;} 
    if(eta > 0.9 && eta <= 1.2) {musf=0.958232578952;  musf_d=0.956991254268; musf_u=0.959473903636;} 
}
if(pt>200.0 && pt<=300.0){
    if(eta > 0.0 && eta <= 0.9) {musf=0.977938102104;  musf_d=0.96828324453; musf_u=0.987592959677;} 
    if(eta > 1.2 && eta <= 2.1) {musf=0.957358230391;  musf_d=0.935165396239; musf_u=0.979551064543;} 
    if(eta > 2.1 && eta <= 2.4) {musf=0.825968477035;  musf_d=0.657394417708; musf_u=0.994542536362;} 
    if(eta > 0.9 && eta <= 1.2) {musf=0.944979742807;  musf_d=0.920758939704; musf_u=0.96920054591;} 
}
if(pt>300.0 && pt<=400.0){
    if(eta > 0.0 && eta <= 0.9) {musf=1.00528291728;  musf_d=0.981240797575; musf_u=1.02932503699;} 
    if(eta > 1.2 && eta <= 2.1) {musf=1.12126658491;  musf_d=0.968695316519; musf_u=1.2738378533;} 
    if(eta > 2.1 && eta <= 2.4) {musf=0.785026453282;  musf_d=0.714468578451; musf_u=0.855584328113;} 
    if(eta > 0.9 && eta <= 1.2) {musf=0.944298028685;  musf_d=0.890522362409; musf_u=0.99807369496;} 
}

//https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2016_trigger/EfficienciesAndSF_RunGtoH.json
//https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2016_trigger/EfficienciesAndSF_RunBtoF.json
//Mu50_OR_TkMu50_PtEtaBins
// (pesoBF*L_BF + pesoGH*L_GH)/L_BH
 //return musf;
 return std::make_tuple(musf, musf_d, musf_u);
}
std::tuple<double, double, double> musf_ID(double eta, double pt){
 double musf=0, musf_d=0, musf_u=0;

 if(pt>20.00 && pt<=25.00){
    if(eta > 0.50 && eta <= 0.80) {musf=1.00211123155;  musf_d=0.993107429777; musf_u=1.01111503333;} 
    if(eta > -1.60 && eta <= -1.50) {musf=1.00017596119;  musf_d=0.987350955459; musf_u=1.01300096693;} 
    if(eta > 2.00 && eta <= 2.10) {musf=0.983123138639;  musf_d=0.971356772293; musf_u=0.994889504985;} 
    if(eta > -0.20 && eta <= 0.00) {musf=0.971543094276;  musf_d=0.955664929194; musf_u=0.987421259358;} 
    if(eta > -1.20 && eta <= -0.80) {musf=0.987239460735;  musf_d=0.981324660655; musf_u=0.993154260815;} 
    if(eta > -1.70 && eta <= -1.60) {musf=0.996946306362;  musf_d=0.988229897565; musf_u=1.00566271516;} 
    if(eta > 1.40 && eta <= 1.50) {musf=1.00577129019;  musf_d=0.993302232877; musf_u=1.01824034751;} 
    if(eta > -2.10 && eta <= -2.00) {musf=0.985070797329;  musf_d=0.975187592778; musf_u=0.99495400188;} 
    if(eta > 2.10 && eta <= 2.20) {musf=0.982612531854;  musf_d=0.973759075666; musf_u=0.991465988042;} 
    if(eta > -2.40 && eta <= -2.30) {musf=0.991455095023;  musf_d=0.977985659732; musf_u=1.00492453032;} 
    if(eta > 2.20 && eta <= 2.30) {musf=0.996163796457;  musf_d=0.981894102508; musf_u=1.01043349041;} 
    if(eta > -1.40 && eta <= -1.20) {musf=1.00558218584;  musf_d=0.99720961053; musf_u=1.01395476115;} 
    if(eta > 1.70 && eta <= 2.00) {musf=0.984930856296;  musf_d=0.978521496174; musf_u=0.991340216418;} 
    if(eta > 0.80 && eta <= 1.20) {musf=0.987865920447;  musf_d=0.981008525624; musf_u=0.994723315271;} 
    if(eta > 0.20 && eta <= 0.30) {musf=0.961931450658;  musf_d=0.941533633656; musf_u=0.98232926766;} 
    if(eta > -2.30 && eta <= -2.20) {musf=0.990074021836;  musf_d=0.979176664989; musf_u=1.00097137868;} 
    if(eta > 1.60 && eta <= 1.70) {musf=0.999509845929;  musf_d=0.989158985655; musf_u=1.0098607062;} 
    if(eta > -0.50 && eta <= -0.30) {musf=1.01030208447;  musf_d=0.994242061232; musf_u=1.0263621077;} 
    if(eta > -2.20 && eta <= -2.10) {musf=0.965039975584;  musf_d=0.954274684323; musf_u=0.975805266845;} 
    if(eta > 1.50 && eta <= 1.60) {musf=1.00404959599;  musf_d=0.994279132334; musf_u=1.01382005965;} 
    if(eta > -2.00 && eta <= -1.70) {musf=0.978548864125;  musf_d=0.973065024921; musf_u=0.984032703329;} 
    if(eta > -1.50 && eta <= -1.40) {musf=1.00225789031;  musf_d=0.993543194177; musf_u=1.01097258644;} 
    if(eta > -0.80 && eta <= -0.50) {musf=1.0021762764;  musf_d=0.99750681278; musf_u=1.00684574002;} 
    if(eta > 0.00 && eta <= 0.20) {musf=0.995791165678;  musf_d=0.979508371973; musf_u=1.01207395938;} 
    if(eta > 2.30 && eta <= 2.40) {musf=0.999834182426;  musf_d=0.98580318518; musf_u=1.01386517967;} 
    if(eta > -0.30 && eta <= -0.20) {musf=0.981066679517;  musf_d=0.961678579757; musf_u=1.00045477928;} 
    if(eta > 0.30 && eta <= 0.50) {musf=1.00493346708;  musf_d=0.988891461488; musf_u=1.02097547266;} 
    if(eta > 1.20 && eta <= 1.40) {musf=1.00244577072;  musf_d=0.990290580093; musf_u=1.01460096135;} 
}
if(pt>30.00 && pt<=40.00){
    if(eta > 0.50 && eta <= 0.80) {musf=0.993171553226;  musf_d=0.99027571802; musf_u=0.996067388432;} 
    if(eta > -1.60 && eta <= -1.50) {musf=0.995571077074;  musf_d=0.993283205519; musf_u=0.997858948629;} 
    if(eta > 2.00 && eta <= 2.10) {musf=0.98716846182;  musf_d=0.984003472548; musf_u=0.990333451092;} 
    if(eta > -0.20 && eta <= 0.00) {musf=0.994802753112;  musf_d=0.991610916414; musf_u=0.99799458981;} 
    if(eta > -1.20 && eta <= -0.80) {musf=0.982798420661;  musf_d=0.981475405871; musf_u=0.984121435451;} 
    if(eta > -1.70 && eta <= -1.60) {musf=0.993748868003;  musf_d=0.992125601409; musf_u=0.995372134597;} 
    if(eta > 1.40 && eta <= 1.50) {musf=1.00046296334;  musf_d=0.997629922046; musf_u=1.00329600463;} 
    if(eta > -2.10 && eta <= -2.00) {musf=0.98277405036;  musf_d=0.980700475309; musf_u=0.984847625411;} 
    if(eta > 2.10 && eta <= 2.20) {musf=0.966209375263;  musf_d=0.962203067798; musf_u=0.970215682728;} 
    if(eta > -2.40 && eta <= -2.30) {musf=0.989650272339;  musf_d=0.981490693274; musf_u=0.997809851405;} 
    if(eta > 2.20 && eta <= 2.30) {musf=0.994147694607;  musf_d=0.989304493043; musf_u=0.99899089617;} 
    if(eta > -1.40 && eta <= -1.20) {musf=0.996633483094;  musf_d=0.995336262309; musf_u=0.997930703879;} 
    if(eta > 1.70 && eta <= 2.00) {musf=0.988421675521;  musf_d=0.986943012832; musf_u=0.98990033821;} 
    if(eta > 0.80 && eta <= 1.20) {musf=0.98282412137;  musf_d=0.981300311198; musf_u=0.984347931543;} 
    if(eta > 0.20 && eta <= 0.30) {musf=0.962215450793;  musf_d=0.955248900755; musf_u=0.969182000831;} 
    if(eta > -2.30 && eta <= -2.20) {musf=0.987352265035;  musf_d=0.983564390772; musf_u=0.991140139297;} 
    if(eta > 1.60 && eta <= 1.70) {musf=0.998094089468;  musf_d=0.995478058889; musf_u=1.00071012005;} 
    if(eta > -0.50 && eta <= -0.30) {musf=0.993242728016;  musf_d=0.991001555142; musf_u=0.99548390089;} 
    if(eta > -2.20 && eta <= -2.10) {musf=0.958949104838;  musf_d=0.954884673273; musf_u=0.963013536403;} 
    if(eta > 1.50 && eta <= 1.60) {musf=1.00407209998;  musf_d=1.00116019482; musf_u=1.00698400514;} 
    if(eta > -2.00 && eta <= -1.70) {musf=0.982639631735;  musf_d=0.981437945568; musf_u=0.983841317902;} 
    if(eta > -1.50 && eta <= -1.40) {musf=0.996259901845;  musf_d=0.994309829618; musf_u=0.998209974072;} 
    if(eta > -0.80 && eta <= -0.50) {musf=0.9926232517;  musf_d=0.989700368918; musf_u=0.995546134482;} 
    if(eta > 0.00 && eta <= 0.20) {musf=0.991192011359;  musf_d=0.988706273589; musf_u=0.993677749128;} 
    if(eta > 2.30 && eta <= 2.40) {musf=0.982082795263;  musf_d=0.977169747049; musf_u=0.986995843477;} 
    if(eta > -0.30 && eta <= -0.20) {musf=0.970430309159;  musf_d=0.964569788868; musf_u=0.976290829451;} 
    if(eta > 0.30 && eta <= 0.50) {musf=0.990286054256;  musf_d=0.985213657078; musf_u=0.995358451433;} 
    if(eta > 1.20 && eta <= 1.40) {musf=0.998381592494;  musf_d=0.992627060801; musf_u=1.00413612419;} 
}
if(pt>25.00 && pt<=30.00){
    if(eta > 0.50 && eta <= 0.80) {musf=0.996211530507;  musf_d=0.992169579594; musf_u=1.00025348142;} 
    if(eta > -1.60 && eta <= -1.50) {musf=0.99764673899;  musf_d=0.992013219915; musf_u=1.00328025807;} 
    if(eta > 2.00 && eta <= 2.10) {musf=0.982571249317;  musf_d=0.977762719555; musf_u=0.987379779079;} 
    if(eta > -0.20 && eta <= 0.00) {musf=0.99102854627;  musf_d=0.984630730447; musf_u=0.997426362093;} 
    if(eta > -1.20 && eta <= -0.80) {musf=0.985988791428;  musf_d=0.982536578402; musf_u=0.989441004455;} 
    if(eta > -1.70 && eta <= -1.60) {musf=0.990302435021;  musf_d=0.985982112351; musf_u=0.994622757692;} 
    if(eta > 1.40 && eta <= 1.50) {musf=1.00309792606;  musf_d=0.996044129421; musf_u=1.0101517227;} 
    if(eta > -2.10 && eta <= -2.00) {musf=0.981363815703;  musf_d=0.977036305332; musf_u=0.985691326074;} 
    if(eta > 2.10 && eta <= 2.20) {musf=0.974520357643;  musf_d=0.969243050882; musf_u=0.979797664403;} 
    if(eta > -2.40 && eta <= -2.30) {musf=0.99053563837;  musf_d=0.980084005976; musf_u=1.00098727076;} 
    if(eta > 2.20 && eta <= 2.30) {musf=0.99329654759;  musf_d=0.987806270894; musf_u=0.998786824286;} 
    if(eta > -1.40 && eta <= -1.20) {musf=0.992715112192;  musf_d=0.989049489014; musf_u=0.996380735369;} 
    if(eta > 1.70 && eta <= 2.00) {musf=0.986000657425;  musf_d=0.983810001649; musf_u=0.988191313201;} 
    if(eta > 0.80 && eta <= 1.20) {musf=0.983505277391;  musf_d=0.980041370305; musf_u=0.986969184476;} 
    if(eta > 0.20 && eta <= 0.30) {musf=0.970047730902;  musf_d=0.958637618168; musf_u=0.981457843637;} 
    if(eta > -2.30 && eta <= -2.20) {musf=0.99273100417;  musf_d=0.984157191601; musf_u=1.00130481674;} 
    if(eta > 1.60 && eta <= 1.70) {musf=0.997898823653;  musf_d=0.989480988269; musf_u=1.00631665904;} 
    if(eta > -0.50 && eta <= -0.30) {musf=0.991801917122;  musf_d=0.987065193875; musf_u=0.996538640369;} 
    if(eta > -2.20 && eta <= -2.10) {musf=0.964192873112;  musf_d=0.956890250689; musf_u=0.971495495534;} 
    if(eta > 1.50 && eta <= 1.60) {musf=0.998213836326;  musf_d=0.988626880084; musf_u=1.00780079257;} 
    if(eta > -2.00 && eta <= -1.70) {musf=0.98342227361;  musf_d=0.980352950936; musf_u=0.986491596285;} 
    if(eta > -1.50 && eta <= -1.40) {musf=0.994177120609;  musf_d=0.989021532537; musf_u=0.999332708681;} 
    if(eta > -0.80 && eta <= -0.50) {musf=0.999070252947;  musf_d=0.994765471717; musf_u=1.00337503418;} 
    if(eta > 0.00 && eta <= 0.20) {musf=0.990957471481;  musf_d=0.984377488833; musf_u=0.997537454128;} 
    if(eta > 2.30 && eta <= 2.40) {musf=0.975559944702;  musf_d=0.967648561841; musf_u=0.983471327564;} 
    if(eta > -0.30 && eta <= -0.20) {musf=0.974416369701;  musf_d=0.964754411274; musf_u=0.984078328129;} 
    if(eta > 0.30 && eta <= 0.50) {musf=0.994643236923;  musf_d=0.988585617381; musf_u=1.00070085646;} 
    if(eta > 1.20 && eta <= 1.40) {musf=0.998927102685;  musf_d=0.992695385681; musf_u=1.00515881969;} 
}
if(pt>60.00){
    if(eta > 0.50 && eta <= 0.80) {musf=0.991068684788;  musf_d=0.979513693868; musf_u=1.00262367571;} 
    if(eta > -1.60 && eta <= -1.50) {musf=1.00516617628;  musf_d=0.996609925764; musf_u=1.01372242679;} 
    if(eta > 2.00 && eta <= 2.10) {musf=0.994790658377;  musf_d=0.982875676682; musf_u=1.00670564007;} 
    if(eta > -0.20 && eta <= 0.00) {musf=0.994651136687;  musf_d=0.982351558923; musf_u=1.00695071445;} 
    if(eta > -1.20 && eta <= -0.80) {musf=0.985038939081;  musf_d=0.978774287633; musf_u=0.991303590529;} 
    if(eta > -1.70 && eta <= -1.60) {musf=0.987608611833;  musf_d=0.979234081315; musf_u=0.995983142351;} 
    if(eta > 1.40 && eta <= 1.50) {musf=1.00064074462;  musf_d=0.994266229172; musf_u=1.00701526007;} 
    if(eta > -2.10 && eta <= -2.00) {musf=0.992789681498;  musf_d=0.979879133729; musf_u=1.00570022927;} 
    if(eta > 2.10 && eta <= 2.20) {musf=0.960907003749;  musf_d=0.945002962267; musf_u=0.976811045232;} 
    if(eta > -2.40 && eta <= -2.30) {musf=0.979531136993;  musf_d=0.952926330391; musf_u=1.00613594359;} 
    if(eta > 2.20 && eta <= 2.30) {musf=0.988549687905;  musf_d=0.971695337122; musf_u=1.00540403869;} 
    if(eta > -1.40 && eta <= -1.20) {musf=0.995776070011;  musf_d=0.988148342362; musf_u=1.00340379766;} 
    if(eta > 1.70 && eta <= 2.00) {musf=0.983880391947;  musf_d=0.97786441826; musf_u=0.989896365633;} 
    if(eta > 0.80 && eta <= 1.20) {musf=0.981085186123;  musf_d=0.973190219789; musf_u=0.988980152456;} 
    if(eta > 0.20 && eta <= 0.30) {musf=0.979220742404;  musf_d=0.96003342181; musf_u=0.998408062997;} 
    if(eta > -2.30 && eta <= -2.20) {musf=0.994406899012;  musf_d=0.976623435559; musf_u=1.01219036247;} 
    if(eta > 1.60 && eta <= 1.70) {musf=0.985910895555;  musf_d=0.969731246106; musf_u=1.002090545;} 
    if(eta > -0.50 && eta <= -0.30) {musf=1.0075411648;  musf_d=0.995130639222; musf_u=1.01995169038;} 
    if(eta > -2.20 && eta <= -2.10) {musf=0.956294223377;  musf_d=0.940249737243; musf_u=0.972338709511;} 
    if(eta > 1.50 && eta <= 1.60) {musf=1.00116449917;  musf_d=0.986899080454; musf_u=1.01542991789;} 
    if(eta > -2.00 && eta <= -1.70) {musf=0.983889947415;  musf_d=0.974958361889; musf_u=0.992821532942;} 
    if(eta > -1.50 && eta <= -1.40) {musf=0.992977665285;  musf_d=0.982543844352; musf_u=1.00341148622;} 
    if(eta > -0.80 && eta <= -0.50) {musf=0.998389793101;  musf_d=0.987976839989; musf_u=1.00880274621;} 
    if(eta > 0.00 && eta <= 0.20) {musf=0.994532641055;  musf_d=0.983603783828; musf_u=1.00546149828;} 
    if(eta > 2.30 && eta <= 2.40) {musf=1.00360525694;  musf_d=0.986545318127; musf_u=1.02066519576;} 
    if(eta > -0.30 && eta <= -0.20) {musf=0.972506855405;  musf_d=0.954875543813; musf_u=0.990138166996;} 
    if(eta > 0.30 && eta <= 0.50) {musf=1.0010432274;  musf_d=0.987561130483; musf_u=1.01452532433;} 
    if(eta > 1.20 && eta <= 1.40) {musf=0.995671437332;  musf_d=0.981787402848; musf_u=1.00955547182;} 
}
if(pt>40.00 && pt<=50.00){
    if(eta > 0.50 && eta <= 0.80) {musf=0.994052501394;  musf_d=0.992043390254; musf_u=0.996061612535;} 
    if(eta > -1.60 && eta <= -1.50) {musf=0.996668440524;  musf_d=0.99438780318; musf_u=0.998949077868;} 
    if(eta > 2.00 && eta <= 2.10) {musf=0.988827732118;  musf_d=0.986000739979; musf_u=0.991654724256;} 
    if(eta > -0.20 && eta <= 0.00) {musf=0.994566936222;  musf_d=0.992657882981; musf_u=0.996475989463;} 
    if(eta > -1.20 && eta <= -0.80) {musf=0.98343516845;  musf_d=0.981879892393; musf_u=0.984990444507;} 
    if(eta > -1.70 && eta <= -1.60) {musf=0.993012926187;  musf_d=0.991332588184; musf_u=0.99469326419;} 
    if(eta > 1.40 && eta <= 1.50) {musf=1.00222026273;  musf_d=0.997648829255; musf_u=1.00679169621;} 
    if(eta > -2.10 && eta <= -2.00) {musf=0.983202189391;  musf_d=0.980597371914; musf_u=0.985807006867;} 
    if(eta > 2.10 && eta <= 2.20) {musf=0.971087717152;  musf_d=0.967436853406; musf_u=0.974738580897;} 
    if(eta > -2.40 && eta <= -2.30) {musf=0.99080486154;  musf_d=0.985407006819; musf_u=0.996202716261;} 
    if(eta > 2.20 && eta <= 2.30) {musf=0.989350035065;  musf_d=0.984669911158; musf_u=0.994030158972;} 
    if(eta > -1.40 && eta <= -1.20) {musf=0.99585293099;  musf_d=0.993965361601; musf_u=0.99774050038;} 
    if(eta > 1.70 && eta <= 2.00) {musf=0.989202360522;  musf_d=0.987381873953; musf_u=0.99102284709;} 
    if(eta > 0.80 && eta <= 1.20) {musf=0.982754144322;  musf_d=0.981013335131; musf_u=0.984494953514;} 
    if(eta > 0.20 && eta <= 0.30) {musf=0.965186543065;  musf_d=0.961562274074; musf_u=0.968810812055;} 
    if(eta > -2.30 && eta <= -2.20) {musf=0.987046149703;  musf_d=0.983344698904; musf_u=0.990747600502;} 
    if(eta > 1.60 && eta <= 1.70) {musf=1.00180348757;  musf_d=0.99765977022; musf_u=1.00594720492;} 
    if(eta > -0.50 && eta <= -0.30) {musf=0.994814850892;  musf_d=0.992337097616; musf_u=0.997292604168;} 
    if(eta > -2.20 && eta <= -2.10) {musf=0.959912235473;  musf_d=0.953403614684; musf_u=0.966420856261;} 
    if(eta > 1.50 && eta <= 1.60) {musf=1.00357309057;  musf_d=0.998650174754; musf_u=1.00849600639;} 
    if(eta > -2.00 && eta <= -1.70) {musf=0.983643009919;  musf_d=0.98133085339; musf_u=0.985955166449;} 
    if(eta > -1.50 && eta <= -1.40) {musf=0.996327381878;  musf_d=0.992653576825; musf_u=1.00000118693;} 
    if(eta > -0.80 && eta <= -0.50) {musf=0.993898054283;  musf_d=0.992201930904; musf_u=0.995594177662;} 
    if(eta > 0.00 && eta <= 0.20) {musf=0.99350655446;  musf_d=0.99122053941; musf_u=0.99579256951;} 
    if(eta > 2.30 && eta <= 2.40) {musf=0.990675090438;  musf_d=0.9855384476; musf_u=0.995811733276;} 
    if(eta > -0.30 && eta <= -0.20) {musf=0.972499498227;  musf_d=0.968902393802; musf_u=0.976096602652;} 
    if(eta > 0.30 && eta <= 0.50) {musf=0.991374746795;  musf_d=0.989300186815; musf_u=0.993449306775;} 
    if(eta > 1.20 && eta <= 1.40) {musf=1.00024939714;  musf_d=0.997012330824; musf_u=1.00348646346;} 
}
if(pt>50.00 && pt<=60.00){
    if(eta > 0.50 && eta <= 0.80) {musf=0.987370778403;  musf_d=0.984704814208; musf_u=0.990036742597;} 
    if(eta > -1.60 && eta <= -1.50) {musf=0.993719346923;  musf_d=0.989567303665; musf_u=0.99787139018;} 
    if(eta > 2.00 && eta <= 2.10) {musf=0.985959152461;  musf_d=0.980542675835; musf_u=0.991375629088;} 
    if(eta > -0.20 && eta <= 0.00) {musf=0.989657897264;  musf_d=0.98624107554; musf_u=0.993074718987;} 
    if(eta > -1.20 && eta <= -0.80) {musf=0.977721488229;  musf_d=0.975027508748; musf_u=0.98041546771;} 
    if(eta > -1.70 && eta <= -1.60) {musf=0.993178839424;  musf_d=0.989248160142; musf_u=0.997109518706;} 
    if(eta > 1.40 && eta <= 1.50) {musf=0.983802728963;  musf_d=0.97644044633; musf_u=0.991165011596;} 
    if(eta > -2.10 && eta <= -2.00) {musf=0.982640111998;  musf_d=0.976225532502; musf_u=0.989054691493;} 
    if(eta > 2.10 && eta <= 2.20) {musf=0.964939703756;  musf_d=0.957559025561; musf_u=0.972320381951;} 
    if(eta > -2.40 && eta <= -2.30) {musf=0.978655008479;  musf_d=0.964788762768; musf_u=0.99252125419;} 
    if(eta > 2.20 && eta <= 2.30) {musf=0.980775804059;  musf_d=0.973246816764; musf_u=0.988304791353;} 
    if(eta > -1.40 && eta <= -1.20) {musf=0.992303149594;  musf_d=0.989030860029; musf_u=0.995575439159;} 
    if(eta > 1.70 && eta <= 2.00) {musf=0.986224415426;  musf_d=0.983343231856; musf_u=0.989105598995;} 
    if(eta > 0.80 && eta <= 1.20) {musf=0.978314445771;  musf_d=0.975524806085; musf_u=0.981104085456;} 
    if(eta > 0.20 && eta <= 0.30) {musf=0.965063565844;  musf_d=0.957079131255; musf_u=0.973048000433;} 
    if(eta > -2.30 && eta <= -2.20) {musf=0.978259303368;  musf_d=0.969612231123; musf_u=0.986906375612;} 
    if(eta > 1.60 && eta <= 1.70) {musf=0.989545489316;  musf_d=0.983279480602; musf_u=0.99581149803;} 
    if(eta > -0.50 && eta <= -0.30) {musf=0.991481630101;  musf_d=0.98819891851; musf_u=0.994764341692;} 
    if(eta > -2.20 && eta <= -2.10) {musf=0.958070271818;  musf_d=0.95018593966; musf_u=0.965954603977;} 
    if(eta > 1.50 && eta <= 1.60) {musf=0.993731313714;  musf_d=0.986538485678; musf_u=1.00092414175;} 
    if(eta > -2.00 && eta <= -1.70) {musf=0.985087445306;  musf_d=0.982665689315; musf_u=0.987509201297;} 
    if(eta > -1.50 && eta <= -1.40) {musf=0.99551622415;  musf_d=0.991185952255; musf_u=0.999846496045;} 
    if(eta > -0.80 && eta <= -0.50) {musf=0.99057180175;  musf_d=0.988085902867; musf_u=0.993057700634;} 
    if(eta > 0.00 && eta <= 0.20) {musf=0.989428312639;  musf_d=0.985943818626; musf_u=0.992912806653;} 
    if(eta > 2.30 && eta <= 2.40) {musf=0.986055565116;  musf_d=0.974365943687; musf_u=0.997745186545;} 
    if(eta > -0.30 && eta <= -0.20) {musf=0.971249095128;  musf_d=0.962743236936; musf_u=0.97975495332;} 
    if(eta > 0.30 && eta <= 0.50) {musf=0.990328746205;  musf_d=0.987115111426; musf_u=0.993542380984;} 
    if(eta > 1.20 && eta <= 1.40) {musf=0.988123770719;  musf_d=0.983295109432; musf_u=0.992952432006;} 
}
 return std::make_tuple(musf, musf_d, musf_u);
 //return musf;
 // https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2016_legacy_rereco/systematic/RunBCDEF_SF_ID.json
 // https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2016_legacy_rereco/systematic/RunGH_SF_ID.json
 //NUM_HighPtID_DEN_genTracks
 // (pesoBF*L_BF + pesoGH*L_GH)/L_BH
}
std::tuple<double, double, double> musf_iso(double eta, double pt){
 double musf=0, musf_d = 0, musf_u=0;

if(pt>20.00 && pt<=25.00){
    if(eta > 0.50 && eta <= 0.80) {musf=0.991665875336;  musf_d=0.985827613695; musf_u=0.997504136977;} 
    if(eta > -1.60 && eta <= -1.50) {musf=0.995257967695;  musf_d=0.988570810695; musf_u=1.00194512469;} 
    if(eta > 2.00 && eta <= 2.10) {musf=0.998802662751;  musf_d=0.992255085249; musf_u=1.00535024025;} 
    if(eta > -0.20 && eta <= 0.00) {musf=0.98594635525;  musf_d=0.978875403907; musf_u=0.993017306593;} 
    if(eta > -1.20 && eta <= -0.80) {musf=0.996539912083;  musf_d=0.992140497362; musf_u=1.00093932681;} 
    if(eta > -1.70 && eta <= -1.60) {musf=0.991463121049;  musf_d=0.985055560315; musf_u=0.997870681783;} 
    if(eta > 1.40 && eta <= 1.50) {musf=0.999571130051;  musf_d=0.991942656751; musf_u=1.00719960335;} 
    if(eta > -2.10 && eta <= -2.00) {musf=0.998580522123;  musf_d=0.992263606454; musf_u=1.00489743779;} 
    if(eta > 2.10 && eta <= 2.20) {musf=0.993445977561;  musf_d=0.987444476363; musf_u=0.99944747876;} 
    if(eta > -2.40 && eta <= -2.30) {musf=0.986741207025;  musf_d=0.979433616325; musf_u=0.994048797725;} 
    if(eta > 2.20 && eta <= 2.30) {musf=0.995579254012;  musf_d=0.988882173889; musf_u=1.00227633413;} 
    if(eta > -1.40 && eta <= -1.20) {musf=0.991755468766;  musf_d=0.986186840536; musf_u=0.997324096996;} 
    if(eta > 1.70 && eta <= 2.00) {musf=0.996790234808;  musf_d=0.993182891576; musf_u=1.00039757804;} 
    if(eta > 0.80 && eta <= 1.20) {musf=0.99767949735;  musf_d=0.993185580008; musf_u=1.00217341469;} 
    if(eta > 0.20 && eta <= 0.30) {musf=0.992372321774;  musf_d=0.981329732093; musf_u=1.00341491145;} 
    if(eta > -2.30 && eta <= -2.20) {musf=0.99854981963;  musf_d=0.992109622909; musf_u=1.00499001635;} 
    if(eta > 1.60 && eta <= 1.70) {musf=0.995580663022;  musf_d=0.988862267511; musf_u=1.00229905853;} 
    if(eta > -0.50 && eta <= -0.30) {musf=0.984500920159;  musf_d=0.977218480077; musf_u=0.99178336024;} 
    if(eta > -2.20 && eta <= -2.10) {musf=0.995850544056;  musf_d=0.989305725812; musf_u=1.0023953623;} 
    if(eta > 1.50 && eta <= 1.60) {musf=1.00280408329;  musf_d=0.995711256373; musf_u=1.0098969102;} 
    if(eta > -2.00 && eta <= -1.70) {musf=0.998777845797;  musf_d=0.99515997664; musf_u=1.00239571495;} 
    if(eta > -1.50 && eta <= -1.40) {musf=0.999870375355;  musf_d=0.992291409928; musf_u=1.00744934078;} 
    if(eta > -0.80 && eta <= -0.50) {musf=0.996391080241;  musf_d=0.990748130383; musf_u=1.0020340301;} 
    if(eta > 0.00 && eta <= 0.20) {musf=0.992110509615;  musf_d=0.984707550733; musf_u=0.999513468498;} 
    if(eta > 2.30 && eta <= 2.40) {musf=0.996603659362;  musf_d=0.988673235067; musf_u=1.00453408366;} 
    if(eta > -0.30 && eta <= -0.20) {musf=0.990195285901;  musf_d=0.979654674303; musf_u=1.0007358975;} 
    if(eta > 0.30 && eta <= 0.50) {musf=0.998796754792;  musf_d=0.991335808688; musf_u=1.0062577009;} 
    if(eta > 1.20 && eta <= 1.40) {musf=0.992655878172;  musf_d=0.986873346335; musf_u=0.998438410008;} 
}
if(pt>50.00 && pt<=60.00){
    if(eta > 0.50 && eta <= 0.80) {musf=0.999366347869;  musf_d=0.998722629228; musf_u=1.00001006651;} 
    if(eta > -1.60 && eta <= -1.50) {musf=1.00018102218;  musf_d=0.999099307319; musf_u=1.00126273705;} 
    if(eta > 2.00 && eta <= 2.10) {musf=0.999277179667;  musf_d=0.997865049418; musf_u=1.00068930992;} 
    if(eta > -0.20 && eta <= 0.00) {musf=1.00029505699;  musf_d=0.9994151812; musf_u=1.00117493277;} 
    if(eta > -1.20 && eta <= -0.80) {musf=0.999792961959;  musf_d=0.999215813684; musf_u=1.00037011023;} 
    if(eta > -1.70 && eta <= -1.60) {musf=1.00001357218;  musf_d=0.998795983306; musf_u=1.00123116106;} 
    if(eta > 1.40 && eta <= 1.50) {musf=1.0005693559;  musf_d=0.999000057771; musf_u=1.00213865403;} 
    if(eta > -2.10 && eta <= -2.00) {musf=0.998781388361;  musf_d=0.997595056984; musf_u=0.999967719739;} 
    if(eta > 2.10 && eta <= 2.20) {musf=1.00072402012;  musf_d=0.999339049172; musf_u=1.00210899107;} 
    if(eta > -2.40 && eta <= -2.30) {musf=1.00032562735;  musf_d=0.99632935519; musf_u=1.00432189951;} 
    if(eta > 2.20 && eta <= 2.30) {musf=0.999817912233;  musf_d=0.998419970734; musf_u=1.00121585373;} 
    if(eta > -1.40 && eta <= -1.20) {musf=0.999318491503;  musf_d=0.998452916903; musf_u=1.0001840661;} 
    if(eta > 1.70 && eta <= 2.00) {musf=0.999343129566;  musf_d=0.998593287742; musf_u=1.00009297139;} 
    if(eta > 0.80 && eta <= 1.20) {musf=0.99964379363;  musf_d=0.99907927688; musf_u=1.00020831038;} 
    if(eta > 0.20 && eta <= 0.30) {musf=1.00013014575;  musf_d=0.998962126904; musf_u=1.0012981646;} 
    if(eta > -2.30 && eta <= -2.20) {musf=0.999793510699;  musf_d=0.998130273214; musf_u=1.00145674818;} 
    if(eta > 1.60 && eta <= 1.70) {musf=0.999896636814;  musf_d=0.998889032249; musf_u=1.00090424138;} 
    if(eta > -0.50 && eta <= -0.30) {musf=0.999438171371;  musf_d=0.998623641384; musf_u=1.00025270136;} 
    if(eta > -2.20 && eta <= -2.10) {musf=0.999775696632;  musf_d=0.99835645478; musf_u=1.00119493848;} 
    if(eta > 1.50 && eta <= 1.60) {musf=1.00031393554;  musf_d=0.999201501816; musf_u=1.00142636927;} 
    if(eta > -2.00 && eta <= -1.70) {musf=0.999017644387;  musf_d=0.998356759025; musf_u=0.999678529748;} 
    if(eta > -1.50 && eta <= -1.40) {musf=1.00004682833;  musf_d=0.998976179313; musf_u=1.00111747736;} 
    if(eta > -0.80 && eta <= -0.50) {musf=0.999730677729;  musf_d=0.999080359871; musf_u=1.00038099559;} 
    if(eta > 0.00 && eta <= 0.20) {musf=0.999931313261;  musf_d=0.998991681104; musf_u=1.00087094542;} 
    if(eta > 2.30 && eta <= 2.40) {musf=1.00048918506;  musf_d=0.998660708078; musf_u=1.00231766205;} 
    if(eta > -0.30 && eta <= -0.20) {musf=0.999136749056;  musf_d=0.997998879594; musf_u=1.00027461852;} 
    if(eta > 0.30 && eta <= 0.50) {musf=0.99962886722;  musf_d=0.998817988373; musf_u=1.00043974607;} 
    if(eta > 1.20 && eta <= 1.40) {musf=0.999553164257;  musf_d=0.998764204455; musf_u=1.00034212406;} 
}
if(pt>25.00 && pt<=30.00){
    if(eta > 0.50 && eta <= 0.80) {musf=1.00042869732;  musf_d=0.997292104475; musf_u=1.00356529016;} 
    if(eta > -1.60 && eta <= -1.50) {musf=0.998600901958;  musf_d=0.994767024934; musf_u=1.00243477898;} 
    if(eta > 2.00 && eta <= 2.10) {musf=1.00165297112;  musf_d=0.997934224839; musf_u=1.00537171741;} 
    if(eta > -0.20 && eta <= 0.00) {musf=0.994870290388;  musf_d=0.99116601548; musf_u=0.998574565295;} 
    if(eta > -1.20 && eta <= -0.80) {musf=0.998930908627;  musf_d=0.996419353496; musf_u=1.00144246376;} 
    if(eta > -1.70 && eta <= -1.60) {musf=0.998346359565;  musf_d=0.994398728889; musf_u=1.00229399024;} 
    if(eta > 1.40 && eta <= 1.50) {musf=0.996409489631;  musf_d=0.991882379731; musf_u=1.00093659953;} 
    if(eta > -2.10 && eta <= -2.00) {musf=1.00057996091;  musf_d=0.996111753831; musf_u=1.00504816798;} 
    if(eta > 2.10 && eta <= 2.20) {musf=1.00058148533;  musf_d=0.995775300309; musf_u=1.00538767036;} 
    if(eta > -2.40 && eta <= -2.30) {musf=0.998279345445;  musf_d=0.993903960061; musf_u=1.00265473083;} 
    if(eta > 2.20 && eta <= 2.30) {musf=1.00496365526;  musf_d=1.00106535586; musf_u=1.00886195465;} 
    if(eta > -1.40 && eta <= -1.20) {musf=0.999072921106;  musf_d=0.995766135438; musf_u=1.00237970677;} 
    if(eta > 1.70 && eta <= 2.00) {musf=1.00038307456;  musf_d=0.998078276857; musf_u=1.00268787226;} 
    if(eta > 0.80 && eta <= 1.20) {musf=1.00105050708;  musf_d=0.998305331406; musf_u=1.00379568276;} 
    if(eta > 0.20 && eta <= 0.30) {musf=0.99561804042;  musf_d=0.990784961699; musf_u=1.00045111914;} 
    if(eta > -2.30 && eta <= -2.20) {musf=1.00409071847;  musf_d=1.00020554869; musf_u=1.00797588825;} 
    if(eta > 1.60 && eta <= 1.70) {musf=0.998097292295;  musf_d=0.99417732866; musf_u=1.00201725593;} 
    if(eta > -0.50 && eta <= -0.30) {musf=0.996796804192;  musf_d=0.993204586148; musf_u=1.00038902224;} 
    if(eta > -2.20 && eta <= -2.10) {musf=0.996225911969;  musf_d=0.992665752735; musf_u=0.999786071204;} 
    if(eta > 1.50 && eta <= 1.60) {musf=1.00064955287;  musf_d=0.996676514799; musf_u=1.00462259093;} 
    if(eta > -2.00 && eta <= -1.70) {musf=0.999316635772;  musf_d=0.997179115015; musf_u=1.00145415653;} 
    if(eta > -1.50 && eta <= -1.40) {musf=0.998441347882;  musf_d=0.994347939701; musf_u=1.00253475606;} 
    if(eta > -0.80 && eta <= -0.50) {musf=0.999725822904;  musf_d=0.996738193212; musf_u=1.0027134526;} 
    if(eta > 0.00 && eta <= 0.20) {musf=1.00075914875;  musf_d=0.997440794617; musf_u=1.00407750289;} 
    if(eta > 2.30 && eta <= 2.40) {musf=0.994827534928;  musf_d=0.990416023933; musf_u=0.999239045923;} 
    if(eta > -0.30 && eta <= -0.20) {musf=0.998452762532;  musf_d=0.993579791621; musf_u=1.00332573344;} 
    if(eta > 0.30 && eta <= 0.50) {musf=0.998321926337;  musf_d=0.994724487134; musf_u=1.00191936554;} 
    if(eta > 1.20 && eta <= 1.40) {musf=1.00031922743;  musf_d=0.997135692231; musf_u=1.00350276262;} 
}
if(pt>60.00 ){
    if(eta > 0.50 && eta <= 0.80) {musf=0.999986938605;  musf_d=0.999111953919; musf_u=1.00086192329;} 
    if(eta > -1.60 && eta <= -1.50) {musf=0.998943545176;  musf_d=0.996625959162; musf_u=1.00126113119;} 
    if(eta > 2.00 && eta <= 2.10) {musf=0.998048845223;  musf_d=0.996351560687; musf_u=0.999746129759;} 
    if(eta > -0.20 && eta <= 0.00) {musf=1.00018681808;  musf_d=0.998743617636; musf_u=1.00163001852;} 
    if(eta > -1.20 && eta <= -0.80) {musf=1.00023774097;  musf_d=0.998835833398; musf_u=1.00163964853;} 
    if(eta > -1.70 && eta <= -1.60) {musf=1.00030294672;  musf_d=0.998253185795; musf_u=1.00235270764;} 
    if(eta > 1.40 && eta <= 1.50) {musf=1.00031030809;  musf_d=0.998809565777; musf_u=1.00181105041;} 
    if(eta > -2.10 && eta <= -2.00) {musf=0.998368799868;  musf_d=0.996561332789; musf_u=1.00017626695;} 
    if(eta > 2.10 && eta <= 2.20) {musf=1.00203720943;  musf_d=0.999771988633; musf_u=1.00430243023;} 
    if(eta > -2.40 && eta <= -2.30) {musf=0.9972888727;  musf_d=0.994643555213; musf_u=0.999934190186;} 
    if(eta > 2.20 && eta <= 2.30) {musf=1.00104479845;  musf_d=0.998362993106; musf_u=1.0037266038;} 
    if(eta > -1.40 && eta <= -1.20) {musf=0.999024737385;  musf_d=0.997620402837; musf_u=1.00042907193;} 
    if(eta > 1.70 && eta <= 2.00) {musf=0.999301093145;  musf_d=0.998288963593; musf_u=1.0003132227;} 
    if(eta > 0.80 && eta <= 1.20) {musf=1.00045734967;  musf_d=0.999569108525; musf_u=1.00134559081;} 
    if(eta > 0.20 && eta <= 0.30) {musf=0.999419619355;  musf_d=0.997743291569; musf_u=1.00109594714;} 
    if(eta > -2.30 && eta <= -2.20) {musf=0.997963351448;  musf_d=0.995893512416; musf_u=1.00003319048;} 
    if(eta > 1.60 && eta <= 1.70) {musf=0.998460107423;  musf_d=0.997113327892; musf_u=0.999806886954;} 
    if(eta > -0.50 && eta <= -0.30) {musf=1.0002937232;  musf_d=0.999057223913; musf_u=1.00153022249;} 
    if(eta > -2.20 && eta <= -2.10) {musf=1.00207101998;  musf_d=0.999865374583; musf_u=1.00427666538;} 
    if(eta > 1.50 && eta <= 1.60) {musf=0.999069462541;  musf_d=0.997790019571; musf_u=1.00034890551;} 
    if(eta > -2.00 && eta <= -1.70) {musf=0.999391472024;  musf_d=0.998214582924; musf_u=1.00056836112;} 
    if(eta > -1.50 && eta <= -1.40) {musf=0.99959447897;  musf_d=0.998229185988; musf_u=1.00095977195;} 
    if(eta > -0.80 && eta <= -0.50) {musf=0.999289929311;  musf_d=0.998247548632; musf_u=1.00033230999;} 
    if(eta > 0.00 && eta <= 0.20) {musf=0.999279132377;  musf_d=0.998131743127; musf_u=1.00042652163;} 
    if(eta > 2.30 && eta <= 2.40) {musf=1.00068372541;  musf_d=0.997272973556; musf_u=1.00409447726;} 
    if(eta > -0.30 && eta <= -0.20) {musf=0.999574057956;  musf_d=0.997802425756; musf_u=1.00134569016;} 
    if(eta > 0.30 && eta <= 0.50) {musf=1.00057278263;  musf_d=0.999363265016; musf_u=1.00178230025;} 
    if(eta > 1.20 && eta <= 1.40) {musf=1.00116008947;  musf_d=0.999838432103; musf_u=1.00248174684;} 
}
if(pt>30.00 && pt<=40.00){
    if(eta > 0.50 && eta <= 0.80) {musf=1.00026685759;  musf_d=0.999442048742; musf_u=1.00109166644;} 
    if(eta > -1.60 && eta <= -1.50) {musf=1.00282366237;  musf_d=1.00124650595; musf_u=1.0044008188;} 
    if(eta > 2.00 && eta <= 2.10) {musf=0.999553137985;  musf_d=0.998201441353; musf_u=1.00090483462;} 
    if(eta > -0.20 && eta <= 0.00) {musf=0.998020768034;  musf_d=0.996999986452; musf_u=0.999041549616;} 
    if(eta > -1.20 && eta <= -0.80) {musf=0.998843579556;  musf_d=0.998086223194; musf_u=0.999600935919;} 
    if(eta > -1.70 && eta <= -1.60) {musf=1.00192983554;  musf_d=0.998641800661; musf_u=1.00521787042;} 
    if(eta > 1.40 && eta <= 1.50) {musf=0.999690195097;  musf_d=0.998179887023; musf_u=1.00120050317;} 
    if(eta > -2.10 && eta <= -2.00) {musf=0.999757355218;  musf_d=0.998484104241; musf_u=1.0010306062;} 
    if(eta > 2.10 && eta <= 2.20) {musf=1.00009890494;  musf_d=0.998803118004; musf_u=1.00139469187;} 
    if(eta > -2.40 && eta <= -2.30) {musf=1.00088506045;  musf_d=0.999215715143; musf_u=1.00255440575;} 
    if(eta > 2.20 && eta <= 2.30) {musf=0.998145040104;  musf_d=0.996809015423; musf_u=0.999481064784;} 
    if(eta > -1.40 && eta <= -1.20) {musf=0.997999687069;  musf_d=0.997007562948; musf_u=0.998991811191;} 
    if(eta > 1.70 && eta <= 2.00) {musf=1.00049159862;  musf_d=0.999684813741; musf_u=1.0012983835;} 
    if(eta > 0.80 && eta <= 1.20) {musf=0.999972905153;  musf_d=0.999193333203; musf_u=1.0007524771;} 
    if(eta > 0.20 && eta <= 0.30) {musf=0.99846176596;  musf_d=0.996958383781; musf_u=0.999965148139;} 
    if(eta > -2.30 && eta <= -2.20) {musf=0.999975940898;  musf_d=0.998638086769; musf_u=1.00131379503;} 
    if(eta > 1.60 && eta <= 1.70) {musf=0.999435598044;  musf_d=0.998014358889; musf_u=1.0008568372;} 
    if(eta > -0.50 && eta <= -0.30) {musf=0.998328399003;  musf_d=0.997265167951; musf_u=0.999391630054;} 
    if(eta > -2.20 && eta <= -2.10) {musf=0.999704239815;  musf_d=0.998415007448; musf_u=1.00099347218;} 
    if(eta > 1.50 && eta <= 1.60) {musf=1.00032575236;  musf_d=0.998919505284; musf_u=1.00173199943;} 
    if(eta > -2.00 && eta <= -1.70) {musf=1.00126299161;  musf_d=1.00026725009; musf_u=1.00225873313;} 
    if(eta > -1.50 && eta <= -1.40) {musf=1.00074450843;  musf_d=0.999174811123; musf_u=1.00231420574;} 
    if(eta > -0.80 && eta <= -0.50) {musf=0.99958644003;  musf_d=0.998720608641; musf_u=1.00045227142;} 
    if(eta > 0.00 && eta <= 0.20) {musf=0.998422849562;  musf_d=0.997402184596; musf_u=0.999443514529;} 
    if(eta > 2.30 && eta <= 2.40) {musf=1.00055383834;  musf_d=0.998828816984; musf_u=1.00227885969;} 
    if(eta > -0.30 && eta <= -0.20) {musf=0.998577573844;  musf_d=0.99710449868; musf_u=1.00005064901;} 
    if(eta > 0.30 && eta <= 0.50) {musf=0.999662808211;  musf_d=0.998645927702; musf_u=1.00067968872;} 
    if(eta > 1.20 && eta <= 1.40) {musf=0.998497831054;  musf_d=0.997421248902; musf_u=0.999574413205;} 
}
if(pt>40.00 && pt<=50.00){
    if(eta > 0.50 && eta <= 0.80) {musf=0.999382296975;  musf_d=0.999159691412; musf_u=0.999604902539;} 
    if(eta > -1.60 && eta <= -1.50) {musf=1.00010598225;  musf_d=1.00001622385; musf_u=1.00019574064;} 
    if(eta > 2.00 && eta <= 2.10) {musf=0.999105492016;  musf_d=0.998668816035; musf_u=0.999542167997;} 
    if(eta > -0.20 && eta <= 0.00) {musf=0.999023744877;  musf_d=0.998556183123; musf_u=0.999491306632;} 
    if(eta > -1.20 && eta <= -0.80) {musf=0.999071249316;  musf_d=0.998788129316; musf_u=0.999354369316;} 
    if(eta > -1.70 && eta <= -1.60) {musf=0.999898564845;  musf_d=0.999289458872; musf_u=1.00050767082;} 
    if(eta > 1.40 && eta <= 1.50) {musf=0.999383505195;  musf_d=0.995804236997; musf_u=1.00296277339;} 
    if(eta > -2.10 && eta <= -2.00) {musf=0.999904190174;  musf_d=0.999248182403; musf_u=1.00056019794;} 
    if(eta > 2.10 && eta <= 2.20) {musf=0.999785993346;  musf_d=0.999388135694; musf_u=1.000183851;} 
    if(eta > -2.40 && eta <= -2.30) {musf=0.999660495892;  musf_d=0.998697573775; musf_u=1.00062341801;} 
    if(eta > 2.20 && eta <= 2.30) {musf=0.999774100637;  musf_d=0.99897052014; musf_u=1.00057768113;} 
    if(eta > -1.40 && eta <= -1.20) {musf=0.998897327957;  musf_d=0.99863356504; musf_u=0.999161090875;} 
    if(eta > 1.70 && eta <= 2.00) {musf=0.999560115365;  musf_d=0.99925442481; musf_u=0.999865805919;} 
    if(eta > 0.80 && eta <= 1.20) {musf=0.999632494093;  musf_d=0.999317381008; musf_u=0.999947607179;} 
    if(eta > 0.20 && eta <= 0.30) {musf=0.999730230781;  musf_d=0.999105849148; musf_u=1.00035461241;} 
    if(eta > -2.30 && eta <= -2.20) {musf=1.00063079528;  musf_d=0.999818160837; musf_u=1.00144342972;} 
    if(eta > 1.60 && eta <= 1.70) {musf=0.999474654102;  musf_d=0.999014327936; musf_u=0.999934980269;} 
    if(eta > -0.50 && eta <= -0.30) {musf=0.998951006001;  musf_d=0.998505574216; musf_u=0.999396437786;} 
    if(eta > -2.20 && eta <= -2.10) {musf=0.999517510267;  musf_d=0.999233033562; musf_u=0.999801986971;} 
    if(eta > 1.50 && eta <= 1.60) {musf=0.999665735474;  musf_d=0.999105686623; musf_u=1.00022578432;} 
    if(eta > -2.00 && eta <= -1.70) {musf=0.999395044471;  musf_d=0.999280545561; musf_u=0.999509543381;} 
    if(eta > -1.50 && eta <= -1.40) {musf=0.999662830647;  musf_d=0.997519222538; musf_u=1.00180643876;} 
    if(eta > -0.80 && eta <= -0.50) {musf=0.999300696472;  musf_d=0.993525999357; musf_u=1.00507539359;} 
    if(eta > 0.00 && eta <= 0.20) {musf=0.998783821716;  musf_d=0.998317524391; musf_u=0.999250119042;} 
    if(eta > 2.30 && eta <= 2.40) {musf=1.00048933347;  musf_d=0.999531875364; musf_u=1.00144679158;} 
    if(eta > -0.30 && eta <= -0.20) {musf=0.999330851985;  musf_d=0.994987809906; musf_u=1.00367389406;} 
    if(eta > 0.30 && eta <= 0.50) {musf=0.999387818578;  musf_d=0.998984919479; musf_u=0.999790717677;} 
    if(eta > 1.20 && eta <= 1.40) {musf=0.998969905219;  musf_d=0.998708392653; musf_u=0.999231417785;} 
}

//https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2016_legacy_rereco/systematic/RunBCDEF_SF_ISO.json
//https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2016_legacy_rereco/systematic/RunGH_SF_ISO.json
//NUM_LooseRelIso_DEN_LooseID
//(pesoBF*L_BF + pesoGH*L_GH)/L_BH
 return std::make_tuple(musf, musf_d, musf_u);
// return musf;
}

double get_wgtlumi(string FileName){
 double wgt=1;

 //xsec in pb
 // checked, OK!
 if(FileName.find("TT") != std::string::npos) wgt=730.6/76915549;  
 if(FileName.find("DY") != std::string::npos) wgt=6077./146280395;
 if(FileName.find("_ST_") != std::string::npos)  wgt=35.61/6952830; 
 if(FileName.find("_SaT_") != std::string::npos) wgt=35.59/6933094; 
 if(FileName.find("WW") != std::string::npos) wgt=118.7/7982180; 
 if(FileName.find("WZ") != std::string::npos) wgt=47.13/3997571; 
 if(FileName.find("ZZ") != std::string::npos) wgt=16.523/1988098;
 if(FileName.find("WJetsHT70To100") != std::string::npos) wgt=1637.13/10020533;
 if(FileName.find("WJetsHT100To200") != std::string::npos) wgt=1628.66/78043017;
 if(FileName.find("WJetsHT200To400") != std::string::npos) wgt=435.721/38984322;
 if(FileName.find("WJetsHT400To600") != std::string::npos) wgt=59.048/7759701; 
 if(FileName.find("WJetsHT600To800") != std::string::npos) wgt=14.6047/18687480; 
 if(FileName.find("WJetsHT800To1200") != std::string::npos) wgt=6.65137/7830536; 
 if(FileName.find("WJetsHT1200To2500") != std::string::npos) wgt=1.60809/6806162;
 if(FileName.find("WJetsHT2500ToInf") != std::string::npos) wgt=0.0388389/1398006;
 if(FileName.find("WJets_") != std::string::npos) wgt=60814.6/86916455;
 
 //muons
 
 if((FileName.find("mumujj_16_L13_M500") != std::string::npos)) wgt=5.7090e-03/100000;
 if((FileName.find("mumujj_16_L13_M1000") != std::string::npos)) wgt=2.8140e-03/100000;
 if((FileName.find("mumujj_16_L13_M2000") != std::string::npos)) wgt=0.82140e-03/100000;
 if((FileName.find("mumujj_16_L13_M5000") != std::string::npos)) wgt=0.014250e-03/100000;
 if((FileName.find("mumujj_16_L13_M8000") != std::string::npos)) wgt=0.000091350e-03/91350;

 //electrons
 
 if((FileName.find("eejj_16_L13_M500") != std::string::npos)) wgt=5.7090e-03/100000;
 if((FileName.find("eejj_16_L13_M1000") != std::string::npos)) wgt=2.8140e-03/96800;
 if((FileName.find("eejj_16_L13_M2000") != std::string::npos)) wgt=0.82140e-03/100000;
 if((FileName.find("eejj_16_L13_M5000") != std::string::npos)) wgt=0.014250e-03/100000;
 if((FileName.find("eejj_16_L13_M8000") != std::string::npos)) wgt=0.000091350e-03/91273;
 
 return wgt;
 }

