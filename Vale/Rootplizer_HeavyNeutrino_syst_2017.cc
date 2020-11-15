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
std::tuple<double, double, double> musf_reco(double eta,double pt);
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
  RoccoR  rc("RoccoR2017.txt");
  GEScaleSyst *GE = new GEScaleSyst();
  /////
  //   Variables to read
  /////
  //EVENT variables (PDF syst)
  int rEVENT_PDFv4_lhaid; rEVENT_PDFv4_lhaid = 0; TBranch* b_rEVENT_PDFv4_lhaid = 0; readingtree->SetBranchAddress("EVENT_PDFv4_lhaid",&rEVENT_PDFv4_lhaid,&b_rEVENT_PDFv4_lhaid);
  double rEVENT_PDFv4WeightUp; rEVENT_PDFv4WeightUp = 0; TBranch* b_rEVENT_PDFv4WeightUp = 0; readingtree->SetBranchAddress("EVENT_PDFv4WeightUp",&rEVENT_PDFv4WeightUp,&b_rEVENT_PDFv4WeightUp);
  double rEVENT_PDFv4WeightDown; rEVENT_PDFv4WeightDown = 0; TBranch* b_rEVENT_PDFv4WeightDown = 0; readingtree->SetBranchAddress("EVENT_PDFv4WeightDown",&rEVENT_PDFv4WeightDown,&b_rEVENT_PDFv4WeightDown);
  double rEVENT_PDFv4WeightCentral; rEVENT_PDFv4WeightCentral = 0; TBranch* b_rEVENT_PDFv4WeightCentral = 0; readingtree->SetBranchAddress("EVENT_PDFv4WeightCentral",&rEVENT_PDFv4WeightCentral,&b_rEVENT_PDFv4WeightCentral);
  double rEVENT_PDFv4WeightMean; rEVENT_PDFv4WeightMean = 0; TBranch* b_rEVENT_PDFv4WeightMean = 0; readingtree->SetBranchAddress("EVENT_PDFv4WeightMean",&rEVENT_PDFv4WeightMean,&b_rEVENT_PDFv4WeightMean);
  double rEVENT_PDFv4WeightStdDev; rEVENT_PDFv4WeightStdDev = 0; TBranch* b_rEVENT_PDFv4WeightStdDev = 0; readingtree->SetBranchAddress("EVENT_PDFv4WeightStdDev",&rEVENT_PDFv4WeightStdDev,&b_rEVENT_PDFv4WeightStdDev);


  //Trigger
  int rHLT_Photon200; rHLT_Photon200 = 0; TBranch* b_rHLT_Photon200 = 0; readingtree->SetBranchAddress("HLT_Photon200",&rHLT_Photon200,&b_rHLT_Photon200);
  int rHLT_Ele35_WPTight_Gsf; rHLT_Ele35_WPTight_Gsf = 0; TBranch* b_rHLT_Ele35_WPTight_Gsf = 0; readingtree->SetBranchAddress("HLT_Ele35_WPTight_Gsf",&rHLT_Ele35_WPTight_Gsf,&b_rHLT_Ele35_WPTight_Gsf);
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
   int HLT_Photon200; newtree->Branch("HLT_Photon200",&HLT_Photon200);
   int HLT_Ele35_WPTight_Gsf; newtree->Branch("HLT_Ele35_WPTight_Gsf",&HLT_Ele35_WPTight_Gsf);
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

   

  // EVENT (PDF syst)
  double EVENT_PDFv4_lhaid; newtree->Branch("EVENT_PDFv4_lhaid",&EVENT_PDFv4_lhaid);
  double EVENT_PDFv4WeightUp; newtree->Branch("EVENT_PDFv4WeightUp",&EVENT_PDFv4WeightUp);
  double EVENT_PDFv4WeightDown; newtree->Branch("EVENT_PDFv4WeightDown",&EVENT_PDFv4WeightDown);
  double EVENT_PDFv4WeightCentral; newtree->Branch("EVENT_PDFv4WeightCentral",&EVENT_PDFv4WeightCentral);
  double EVENT_PDFv4WeightMean; newtree->Branch("EVENT_PDFv4WeightMean",&EVENT_PDFv4WeightMean);
  double EVENT_PDFv4WeightStdDev; newtree->Branch("EVENT_PDFv4WeightStdDev",&EVENT_PDFv4WeightStdDev);

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
   double musf_reco_mu1; newtree->Branch("musf_reco_mu1",&musf_reco_mu1);
   double musf_tot_mu1; newtree->Branch("musf_tot_mu1",&musf_tot_mu1);
   double musf_trigger_mu2; newtree->Branch("musf_trigger_mu2",&musf_trigger_mu2);
   double musf_ID_mu2; newtree->Branch("musf_ID_mu2",&musf_ID_mu2);
   double musf_iso_mu2; newtree->Branch("musf_iso_mu2",&musf_iso_mu2);
   double musf_reco_mu2; newtree->Branch("musf_reco_mu2",&musf_reco_mu2);
   double musf_tot_mu2; newtree->Branch("musf_tot_mu2",&musf_tot_mu2);

   double musf_trigger_mu1_u; newtree->Branch("musf_trigger_mu1_u",&musf_trigger_mu1_u);
   double musf_ID_mu1_u; newtree->Branch("musf_ID_mu1_u",&musf_ID_mu1_u);
   double musf_iso_mu1_u; newtree->Branch("musf_iso_mu1_u",&musf_iso_mu1_u);
   double musf_reco_mu1_u; newtree->Branch("musf_reco_mu1_u",&musf_reco_mu1_u); 
   double musf_tot_mu1_u; newtree->Branch("musf_tot_mu1_u",&musf_tot_mu1_u);
   double musf_trigger_mu2_u; newtree->Branch("musf_trigger_mu2_u",&musf_trigger_mu2_u);
   double musf_ID_mu2_u; newtree->Branch("musf_ID_mu2_u",&musf_ID_mu2_u);
   double musf_iso_mu2_u; newtree->Branch("musf_iso_mu2_u",&musf_iso_mu2_u);
   double musf_reco_mu2_u; newtree->Branch("musf_reco_mu2_u",&musf_reco_mu2_u);
   double musf_tot_mu2_u; newtree->Branch("musf_tot_mu2_u",&musf_tot_mu2_u);

   double musf_trigger_mu1_d; newtree->Branch("musf_trigger_mu1_d",&musf_trigger_mu1_d);
   double musf_ID_mu1_d; newtree->Branch("musf_ID_mu1_d",&musf_ID_mu1_d);
   double musf_iso_mu1_d; newtree->Branch("musf_iso_mu1_d",&musf_iso_mu1_d);
   double musf_reco_mu1_d; newtree->Branch("musf_reco_mu1_d",&musf_reco_mu1_d);
   double musf_tot_mu1_d; newtree->Branch("musf_tot_mu1_d",&musf_tot_mu1_d);
   double musf_trigger_mu2_d; newtree->Branch("musf_trigger_mu2_d",&musf_trigger_mu2_d);
   double musf_ID_mu2_d; newtree->Branch("musf_ID_mu2_d",&musf_ID_mu2_d);
   double musf_iso_mu2_d; newtree->Branch("musf_iso_mu2_d",&musf_iso_mu2_d);
   double musf_reco_mu2_d; newtree->Branch("musf_reco_mu2_d",&musf_reco_mu2_d);
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
    
 

   int nen = nentries;
   if(nentries==-1) nen = readingtree->GetEntries();
   cout << nen << endl;
   for(int en=0; en<nen; en++){
    //Read branches
    //Trigger:
    
    b_rHLT_Photon200->GetEntry(en);
    b_rHLT_Ele35_WPTight_Gsf->GetEntry(en);
    b_rHLT_Ele115_CaloIdVT_GsfTrkIdT->GetEntry(en);
    b_rHLT_Mu50->GetEntry(en);
    b_rHLT_TkMu50->GetEntry(en);
    b_rHLT_OldMu100->GetEntry(en);
    b_rHLT_TkMu100->GetEntry(en);   
 
    //EVENT (PDF syst)
    b_rEVENT_PDFv4_lhaid->GetEntry(en);
    b_rEVENT_PDFv4WeightUp->GetEntry(en);
    b_rEVENT_PDFv4WeightCentral->GetEntry(en);
    b_rEVENT_PDFv4WeightDown->GetEntry(en);
    b_rEVENT_PDFv4WeightMean->GetEntry(en);
    b_rEVENT_PDFv4WeightStdDev->GetEntry(en);

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
      //FOR ROCHESTER
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
    HLT_Photon200 = -999;
    HLT_Ele35_WPTight_Gsf = -999;
    HLT_Ele115_CaloIdVT_GsfTrkIdT = -999;
    HLT_TkMu50 = -999;
    HLT_Mu50 = -999;
    HLT_TkMu100 = -999;
    HLT_OldMu100 = -999;

    EVENT_PDFv4WeightStdDev = -999; EVENT_PDFv4WeightCentral=-999; EVENT_PDFv4WeightMean=-999; EVENT_PDFv4WeightDown=-999; EVENT_PDFv4WeightUp=-999; EVENT_PDFv4_lhaid=-999;

    PUWeight = -999; MinBiasUpWeight = -999; MinBiasDownWeight = -999; nBestVtx = -999; trueInteractions = -999; lumi_wgt = -999; 
    Met_type1PF_pt = -999;

    numOfHighptMu=0; numOfLooseMu=0; numOfMediumMu=0; numOfTightMu=0;

    numOfHighptEle=0; numOfLooseEle=0; numOfMediumEle=0; numOfTightEle=0; numOfVetoEle=0;

    numOfJets_L=0; numOfJets_T=0; numOfJets_TLV=0;
    numOfBoostedJets_L=0; numOfBoostedJets_T=0; numOfBoostedJets_TLV=0; 

    //evt_type = -999;
    eejj_l = 0; emujj_l = 0; mumujj_l = 0; muejj_l = 0;
    SRe = 0; TRe = 0; SRmu = 0; TRmu = 0; DYRe = 0; DYRmu = 0;


    
   HLT_Photon200 = rHLT_Photon200;
   HLT_Ele35_WPTight_Gsf = rHLT_Ele35_WPTight_Gsf;
   HLT_Ele115_CaloIdVT_GsfTrkIdT = rHLT_Ele115_CaloIdVT_GsfTrkIdT;
   HLT_Mu50 = rHLT_Mu50;
   HLT_TkMu50 = rHLT_TkMu50;
   HLT_OldMu100 = rHLT_OldMu100;
   HLT_TkMu100 = rHLT_TkMu100;

  //EVENT (PDF syst)
  EVENT_PDFv4WeightStdDev = rEVENT_PDFv4WeightStdDev; EVENT_PDFv4WeightMean = rEVENT_PDFv4WeightMean; EVENT_PDFv4WeightCentral=rEVENT_PDFv4WeightCentral; EVENT_PDFv4WeightUp=rEVENT_PDFv4WeightUp; EVENT_PDFv4WeightDown=rEVENT_PDFv4WeightDown; EVENT_PDFv4_lhaid=rEVENT_PDFv4_lhaid;

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
       float pt_corr = GE->GEScaleCorrPt(170000+(int)num, (float) rMuon_pt->at(mu_en), (float) rMuon_eta->at(mu_en),(float) rMuon_phi->at(mu_en), (int) rMuon_charge->at(mu_en), false);
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
      patElectron_energyScaleDown->push_back(rpatElectron_energyScaleDown->at(ele_en));
      patElectron_energySigmaUp->push_back(rpatElectron_energySigmaUp->at(ele_en));
      patElectron_energySigmaDown->push_back(rpatElectron_energySigmaDown->at(ele_en)); 
      patElectron_isPassVeto->push_back(rpatElectron_isPassVeto->at(ele_en));
      patElectron_isPassLoose->push_back(rpatElectron_isPassLoose->at(ele_en));
      patElectron_isPassMedium->push_back(rpatElectron_isPassMedium->at(ele_en));
      patElectron_isPassTight->push_back(rpatElectron_isPassTight->at(ele_en));
      patElectron_isPassHEEPId->push_back(rpatElectron_isPassHEEPId->at(ele_en));
     }
    }
   }


   
   Met_type1PF_pt = rMet_type1PF_pt;

   if(numOfHighptEle==2 && patElectron_pt->at(0)>150 && patElectron_pt->at(1)>100 && numOfLooseMu==0) eejj_l=1;
   if(numOfHighptEle==1 && patElectron_pt->at(0)>150 && numOfHighptMu==1 &&  Muon_pt->at(0)>100) emujj_l=1;
   if(numOfHighptEle==1 && patElectron_pt->at(0)>100 && numOfHighptMu==1 &&  Muon_pt->at(0)>150) muejj_l=1;
   if(numOfHighptMu==2 && Muon_pt->at(0)>150 && Muon_pt->at(1)>100 && numOfVetoEle==0) mumujj_l=1;
   
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
      double DR_jetele = sqrt(pow(deltaPhi(patElectron_phi->at(ele_en),JetCorr.Phi()),2)+pow(patElectron_eta->at(ele_en)-JetCorr.Eta(),2) );
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
   }
   if(emujj_l==1){
    std::tie(elesf_ele1, elesf_ele1_d, elesf_ele1_u)=elesf(patElectron_eta->at(0), patElectron_pt->at(0));
    //musf_trigger_mu1=musf_trigger(Muon_eta->at(0),Muon_pt->at(0));
    //std::tie(musf_ID_mu1, musf_ID_mu1_d, musf_ID_mu1_u)=musf_ID(Muon_eta->at(0),Muon_pt->at(0));
    //std::tie(musf_iso_mu1, musf_iso_mu1_d, musf_iso_mu1_u)=musf_iso(Muon_eta->at(0),Muon_pt->at(0));
    std::tie(musf_reco_mu1, musf_reco_mu1_d, musf_reco_mu1_u)=musf_reco(Muon_eta->at(0),Muon_pt->at(0));
    //musf_tot_mu1=musf_trigger_mu1*musf_ID_mu1*musf_iso_mu1;
    musf_tot_mu1=musf_reco_mu1; //musf_ID_mu1*musf_iso_mu1;
    musf_tot_mu1_d=musf_reco_mu1_d; //musf_ID_mu1_d*musf_iso_mu1_d;
    musf_tot_mu1_u=musf_reco_mu1_u; //musf_ID_mu1_u*musf_iso_mu1_u;
    lepsf_evt=elesf_ele1*musf_tot_mu1;
    lepsf_evt_d=elesf_ele1_d*musf_tot_mu1_d;
    lepsf_evt_u=elesf_ele1_u*musf_tot_mu1_u;

   } 

   if(muejj_l==1){
    std::tie(elesf_ele1, elesf_ele1_d, elesf_ele1_u)=elesf(patElectron_eta->at(0), patElectron_pt->at(0));
    std::tie(musf_trigger_mu1, musf_trigger_mu1_d, musf_trigger_mu1_u)=musf_trigger(Muon_eta->at(0),Muon_pt->at(0));
    //std::tie(musf_ID_mu1, musf_ID_mu1_d, musf_ID_mu1_u)=musf_ID(Muon_eta->at(0),Muon_pt->at(0));
    //std::tie(musf_iso_mu1, musf_iso_mu1_d, musf_iso_mu1_u)=musf_iso(Muon_eta->at(0),Muon_pt->at(0));
    std::tie(musf_reco_mu1, musf_reco_mu1_d, musf_reco_mu1_u)=musf_reco(Muon_eta->at(0),Muon_pt->at(0));
    musf_tot_mu1=musf_trigger_mu1*musf_reco_mu1;  //*musf_ID_mu1*musf_iso_mu1;
    musf_tot_mu1_d=musf_trigger_mu1_d*musf_reco_mu1_d;  //*musf_ID_mu1_d*musf_iso_mu1_d;
    musf_tot_mu1_u=musf_trigger_mu1_u*musf_reco_mu1_u;  //*musf_ID_mu1_u*musf_iso_mu1_u;
    lepsf_evt=elesf_ele1*musf_tot_mu1;
    lepsf_evt_d=elesf_ele1_d*musf_tot_mu1_d;
    lepsf_evt_u=elesf_ele1_u*musf_tot_mu1_u;

   }
   if(mumujj_l==1){
    std::tie(musf_trigger_mu1, musf_trigger_mu1_d, musf_trigger_mu1_u)=musf_trigger(Muon_eta->at(0),Muon_pt->at(0));
    //std::tie(musf_ID_mu1, musf_ID_mu1_d, musf_ID_mu1_u)=musf_ID(Muon_eta->at(0),Muon_pt->at(0));
    //std::tie(musf_iso_mu1, musf_iso_mu1_d, musf_iso_mu1_u)=musf_iso(Muon_eta->at(0),Muon_pt->at(0));
    std::tie(musf_reco_mu1, musf_reco_mu1_d, musf_reco_mu1_u)=musf_reco(Muon_eta->at(0),Muon_pt->at(0));
    musf_tot_mu1=musf_trigger_mu1*musf_reco_mu1; //*musf_ID_mu1*musf_iso_mu1;
    musf_tot_mu1_d=musf_trigger_mu1_d*musf_reco_mu1_d; //*musf_ID_mu1_d*musf_iso_mu1_d;
    musf_tot_mu1_u=musf_trigger_mu1_u*musf_reco_mu1_u; //*musf_ID_mu1_u*musf_iso_mu1_u;

    //musf_trigger_mu2=musf_trigger(Muon_eta->at(1),Muon_pt->at(1));
    //std::tie(musf_ID_mu2, musf_ID_mu2_d, musf_ID_mu2_u)=musf_ID(Muon_eta->at(1),Muon_pt->at(1));
    //std::tie(musf_iso_mu2, musf_iso_mu2_d, musf_iso_mu2_u)=musf_iso(Muon_eta->at(1),Muon_pt->at(1));
    //musf_tot_mu2=musf_trigger_mu2*musf_ID_mu2*musf_iso_mu2;
    std::tie(musf_reco_mu2, musf_reco_mu2_d, musf_reco_mu2_u)=musf_reco(Muon_eta->at(1),Muon_pt->at(1));
    musf_tot_mu2=musf_reco_mu2; //musf_ID_mu2*musf_iso_mu2;
    musf_tot_mu2_d=musf_reco_mu2_d; //musf_ID_mu2_d*musf_iso_mu2_d;
    musf_tot_mu2_u=musf_reco_mu2_u; //musf_ID_mu2_u*musf_iso_mu2_u;

    lepsf_evt=musf_tot_mu1*musf_tot_mu2;
    lepsf_evt_d=musf_tot_mu1_d*musf_tot_mu2_d;
    lepsf_evt_u=musf_tot_mu1_u*musf_tot_mu2_u;
   
   }

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
 /*double data[] =  {5.64297e-05,0.000269623,0.000382956,0.000552844,0.000979931,0.00231634,0.0072801,0.0281133,0.0770196,0.130953,0.169536,0.182158,0.161879,0.116249,0.067104,0.0316937,0.0130125,0.00540404,0.00265731,0.00140593,0.000649204,0.000236783,6.7861e-05,1.63211e-05,3.82396e-06,1.03356e-06,3.33506e-07,1.1967e-07,4.49699e-08,1.70463e-08,6.34643e-09,2.28001e-09,7.82427e-10,2.55149e-10,7.88717e-11,2.30861e-11,6.39564e-12,1.67664e-12,4.15902e-13,9.76172e-14,2.16793e-14,4.55562e-15,9.05813e-16,1.70419e-16,3.03394e-17,5.11017e-18,8.14821e-19,1.20894e-19,2.20432e-20,0,0};
 double mc[] = {0.000108643,0.000388957,0.000332882,0.00038397,0.000549167,0.00105412,0.00459007,0.0210314,0.0573688,0.103986,0.142369,0.157729,0.147685,0.121027,0.08855,0.0582866,0.0348526,0.019457,0.0107907,0.00654313,0.00463195,0.00370927,0.0031137,0.00261141,0.00215499,0.00174491,0.00138268,0.00106731,0.000798828,0.00057785,0.00040336,0.00027161,0.000176535,0.00011092,6.75502e-05,4.00323e-05,2.32123e-05,1.32585e-05,7.51611e-06,4.25902e-06,2.42513e-06,1.39077e-06,8.02452e-07,4.64159e-07,2.67845e-07,1.5344e-07,8.68966e-08,4.84931e-08,2.6606e-08,1.433e-08};
 double puw;
 puw=data[trueInteractions]/mc[trueInteractions];*/
 double puw_[] = {0 , 0.183457 , 3.93319 , 3.47116 , 2.49243 , 1.62497 , 1.51512 , 1.28793 , 1.27826 , 0.615853 , 1.4521 , 1.4977 , 1.48749 , 1.33118 , 1.16451 , 1.07903 , 1.05438 , 1.08066 , 1.12906 , 1.16582 , 1.18934 , 1.21282 , 1.23847 , 1.25965 , 1.27096 , 1.27269 , 1.2713 , 1.27087 , 1.26652 , 1.27448 , 1.25162 , 1.22131 , 1.16954 , 1.10903 , 1.03816 , 0.969435 , 0.911885 , 0.866817 , 0.834513 , 0.788387 , 0.750805 , 0.759161 , 0.793186 , 0.858359 , 0.958807 , 1.09434 , 1.25565 , 1.41966 , 1.49595 , 1.53056 , 1.46222 , 1.33677 , 1.1544 , 0.950569 , 0.749712 , 0.569796 , 0.410753 , 0.290011 , 0.198657 , 0.137646 , 0.0966403 , 0.0692323 , 0.0508594 , 0.0384435 , 0.0299599 , 0.0240952 , 0.0171203 , 0.0124799 , 0.0107685 , 0.00959733 , 0.00881253 , 0.00830998 , 0.0080177 , 0.00788486 , 0.0078748 , 0.00633739 , 0.00533376 , 0.00544378 , 0.00558372 , 0.00574419 , 0.00591607 , 0.00609016 , 0.00625719 , 0.00640824 , 0.00509469 , 0.00422809 , 0.00425921 , 0.00426563 , 0.00424672 , 0.00420331 , 0.00413744 , 0.00405199 , 0.00395025 , 0.00294307 , 0.00229606 , 0.00220006 , 0.0021014 , 0.00200168 , 0.00190217 , 0.00180383 , 0};
 double puw=puw_[trueInteractions];
 return puw;
}

std::tuple<double, double, double> elesf(double eta, double pt){
//Electorn Sf for HEEPv7.0 taken from https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaRunIIRecommendations
  double elesf=0,  elesf_d=0, elesf_u=0;
  //Barrel (EB)
 if(fabs(eta) < 1.4442) elesf = 0.967; elesf_d = 0.966; elesf_u = 0.968; // stat 0.001
  //Endcap (EE)
 if(fabs(eta) >= 1.566 && fabs(eta) < 2.5)elesf = 0.973; elesf_d = 0.971; elesf_u = 0.975; // stat 0.002
 return std::make_tuple(elesf, elesf_d, elesf_u);

 
//syst err:
//  - barrel:
//      1% for pT < 90 GeV
//      1-3% linearly increasing for 90 GeV < pT < 1 TeV
//      3% for pT > 1 TeV
//  - endcap:
//      2% for pT < 90 GeV
//      2-5% linearly increasing for 90 GeV < pT < 300 GeV
//      5% for pT > 300 GeV 
//uncertainty: EB ET < 90 GeV: 1% else min(1+(ET-90)*0.0022)%,3%)
//uncertainty: EE ET < 90 GeV: 1% else min(1+(ET-90)*0.0143)%,4%)
     
}

std::tuple<double, double, double> musf_reco(double eta, double pt){
 double musf=0, musf_d = 0, musf_u=0;
 if (fabs(eta) <= 1.6){ 
  if (pt >= 50 && pt < 100) {musf = 0.9938; musf_d = 0.9932; musf_u = 0.9944;}
  if (pt >= 100 && pt < 150){musf = 0.9950; musf_d = 0.9943; musf_u = 0.9957;}
  if (pt >= 150 && pt < 200){musf = 0.9960; musf_d = 0.9950; musf_u = 0.9970;}
  if (pt >= 200 && pt < 300){musf = 0.9960; musf_d = 0.9950; musf_u = 0.9970;}
  if (pt >= 300 && pt < 400){musf = 0.9940; musf_d = 0.9930; musf_u = 0.9950;}
  if (pt >= 400 && pt < 600){musf = 1.0030; musf_d = 0.9970; musf_u = 1.0090;}
  if (pt >= 600 && pt <1500){musf = 0.9870; musf_d = 0.9840; musf_u = 0.9900;}
  if (pt >= 1500){musf = 0.9; musf_d = 0.8; musf_u = 1.0;}
 }
 if (fabs(eta) > 1.6 && fabs(eta) <= 2.4){
  if (pt >= 50 && pt < 100) {musf = 1; musf_d = 1; musf_u = 1;}
  if (pt >= 100 && pt < 150){musf = 0.993; musf_d = 0.992; musf_u = 0.994;} 
  if (pt >= 150 && pt < 200){musf = 0.989; musf_d = 0.988; musf_u = 0.990;}
  if (pt >= 200 && pt < 300){musf = 0.986; musf_d = 0.985; musf_u = 0.987;}
  if (pt >= 300 && pt < 400){musf = 0.989; musf_d = 0.988; musf_u = 0.990;}
  if (pt >= 400 && pt < 600){musf = 0.983; musf_d = 0.980; musf_u = 0.986;}
  if (pt >= 600 && pt <1500){musf = 0.986; musf_d = 0.980; musf_u = 0.992;}
  if (pt >= 1500) {musf = 1.01; musf_d = 1.0; musf_u = 1.02;}
 }
 return std::make_tuple(musf, musf_d, musf_u);
}

std::tuple<double, double, double> musf_trigger(double eta, double pt){
 double musf=0, musf_d = 0, musf_u=0;
 if (pt >=52 && pt < 55){
  if (fabs(eta) <= 0.9){musf = 0.968; musf_d = 0.962; musf_u = 0.974;}
  if (fabs(eta) > 0.9 && fabs(eta) <=1.2){musf = 0.929; musf_d = 0.920; musf_u = 0.938;}
  if (fabs(eta) > 1.2 && fabs(eta) <=2.1){musf = 0.980; musf_d = 0.970; musf_u = 0.990;}
  if (fabs(eta) > 2.1 && fabs(eta) <=2.4){musf = 0.869; musf_d = 0.829; musf_u = 0.909;} 
 }
 if (pt >=55 && pt < 60){
  if (fabs(eta) <= 0.9){musf = 0.968; musf_d = 0.964; musf_u = 0.972;}
  if (fabs(eta) > 0.9 && fabs(eta) <=1.2){musf = 0.953; musf_d = 0.946; musf_u = 0.960;}
  if (fabs(eta) > 1.2 && fabs(eta) <=2.1){musf = 0.981; musf_d = 0.973; musf_u = 0.989;}
  if (fabs(eta) > 2.1 && fabs(eta) <=2.4){musf = 0.864; musf_d = 0.862; musf_u = 0.866;}
 }
 if (pt >=60 && pt < 120){
  if (fabs(eta) <= 0.9){musf = 0.969; musf_d = 0.967; musf_u = 0.971;}
  if (fabs(eta) > 0.9 && fabs(eta) <=1.2){musf = 0.945; musf_d = 0.942; musf_u = 0.948;}
  if (fabs(eta) > 1.2 && fabs(eta) <=2.1){musf = 0.985; musf_d = 0.982; musf_u = 0.988;}
  if (fabs(eta) > 2.1 && fabs(eta) <=2.4){musf = 0.926; musf_d = 0.919; musf_u = 0.933;}
 }
 if (pt >=120 && pt < 200){
  if (fabs(eta) <= 0.9){musf = 0.967; musf_d = 0.965; musf_u = 0.969;}
  if (fabs(eta) > 0.9 && fabs(eta) <=1.2){musf = 0.946; musf_d = 0.941; musf_u = 0.951;}
  if (fabs(eta) > 1.2 && fabs(eta) <=2.1){musf = 0.991; musf_d = 0.987; musf_u = 0.995;}
  if (fabs(eta) > 2.1 && fabs(eta) <=2.4){musf = 0.992; musf_d = 0.982; musf_u = 1.002;}
 }
 if (pt >=200 && pt < 300){
  if (fabs(eta) <= 0.9){musf = 0.964; musf_d = 0.959; musf_u = 0.969;}
  if (fabs(eta) > 0.9 && fabs(eta) <=1.2){musf = 0.948; musf_d = 0.939; musf_u = 0.957;}
  if (fabs(eta) > 1.2 && fabs(eta) <=2.1){musf = 0.986; musf_d = 0.979; musf_u = 0.993;}
  if (fabs(eta) > 2.1 && fabs(eta) <=2.4){musf = 1.023; musf_d = 1.003; musf_u = 1.043;}
 }
 if (pt >=300 && pt < 500){
  if (fabs(eta) <= 0.9){musf = 0.963; musf_d = 0.953; musf_u = 0.973;}
  if (fabs(eta) > 0.9 && fabs(eta) <=1.2){musf = 0.939; musf_d = 0.919; musf_u = 0.959;}
  if (fabs(eta) > 1.2 && fabs(eta) <=2.1){musf = 1.002; musf_d = 0.982; musf_u = 1.022;}
  if (fabs(eta) > 2.1 && fabs(eta) <=2.4){musf = 0.905; musf_d = 0.845; musf_u = 0.965;}
 }
 if (pt >=500){
  if (fabs(eta) <= 0.9){musf = 0.951; musf_d = 0.911; musf_u = 0.991;}
  if (fabs(eta) > 0.9 && fabs(eta) <=1.2){musf = 0.896; musf_d = 0.806; musf_u = 0.986;}
  if (fabs(eta) > 1.2 && fabs(eta) <=2.1){musf = 0.922; musf_d = 0.842; musf_u = 1.002;}
  if (fabs(eta) > 2.1 && fabs(eta) <=2.4){musf = 0.424; musf_d = -0.076; musf_u = 0.924;}
 }
 return std::make_tuple(musf, musf_d, musf_u);
}

/*
std::tuple<double, double, double> musf_trigger(double eta, double pt){
 double musf=0, musf_d = 0, musf_u=0;
 // http://kplee.web.cern.ch/kplee/TagProbe/94X/v20180202_MergingHighPtBins/theJSONfile_RunBtoF_Nov17Nov2017.json
 // Mu50_PtEtaBins
 if(fabs(eta)>0.0 && fabs(eta)<=0.9){
    if(pt > 52.0 && pt <= 55.0) {musf=0.930254399776; musf_d=0.929924274861; musf_u=0.930584524692;}
    if(pt > 60.0 && pt <= 120.0) {musf=0.932169437408; musf_d=0.931820023365; musf_u=0.932518851452;}
    if(pt > 120.0 && pt <= 200.0) {musf=0.918701291084; musf_d=0.917091113696; musf_u=0.920311468472;}
    if(pt > 55.0 && pt <= 60.0) {musf=0.93343102932; musf_d=0.933070781534; musf_u=0.933791277105;}
    if(pt > 200.0 ) {musf=0.901651918888; musf_d=0.898616010706; musf_u=0.90468782707;}
}
if(fabs(eta)>1.2 && fabs(eta)<=2.1){
    if(pt > 52.0 && pt <= 55.0) {musf=0.836993277073; musf_d=0.836453855892; musf_u=0.837532698254;}
    if(pt > 60.0 && pt <= 120.0) {musf=0.889756679535; musf_d=0.889265652849; musf_u=0.89024770622;}
    if(pt > 120.0 && pt <= 200.0) {musf=0.888548195362; musf_d=0.886023400242; musf_u=0.891072990483;}
    if(pt > 55.0 && pt <= 60.0) {musf=0.873748421669; musf_d=0.873206665436; musf_u=0.874290177902;}
    if(pt > 200.0 ) {musf=0.881914794445; musf_d=0.877418413606; musf_u=0.886411175284;}
}
if(fabs(eta)>2.1 && fabs(eta)<=2.4){
    if(pt > 52.0 && pt <= 55.0) {musf=0.620357394218; musf_d=0.618793365172; musf_u=0.621921423265;}
    if(pt > 60.0 && pt <= 120.0) {musf=0.778689265251; musf_d=0.777066086598; musf_u=0.780312443904;}
    if(pt > 120.0 && pt <= 200.0) {musf=0.801188826561; musf_d=0.792672892353; musf_u=0.809704760769;}
    if(pt > 55.0 && pt <= 60.0) {musf=0.716204881668; musf_d=0.714579276965; musf_u=0.717830486371;}
    if(pt > 200.0 ) {musf=0.782012581825; musf_d=0.765359195866; musf_u=0.798665967784;}
}
if(fabs(eta)>0.9 && fabs(eta)<=1.2){
    if(pt > 52.0 && pt <= 55.0) {musf=0.902984380722; musf_d=0.902306579791; musf_u=0.903662181653;}
    if(pt > 60.0 && pt <= 120.0) {musf=0.908429205418; musf_d=0.90771059387; musf_u=0.909147816965;}
    if(pt > 120.0 && pt <= 200.0) {musf=0.888775646687; musf_d=0.885662231221; musf_u=0.891889062152;}
    if(pt > 55.0 && pt <= 60.0) {musf=0.911294996738; musf_d=0.910564175461; musf_u=0.912025818016;}
    if(pt > 200.0) {musf=0.864663362503; musf_d=0.858414627648; musf_u=0.870912097358;}
}

return std::make_tuple(musf, musf_d, musf_u);

}

std::tuple<double, double, double> musf_ID(double eta, double pt){
 double musf=0, musf_d = 0, musf_u=0;
 // https://twiki.cern.ch/twiki/pub/CMS/MuonReferenceEffs2017/RunBCDEF_SF_ID.json
 //  NUM_LooseID_DEN_genTracks
 if(fabs(eta)>1.20 && fabs(eta)<=2.10){
    if(pt > 20.00 && pt <= 25.00) {musf=0.999909632675; musf_d=0.997890220606; musf_u=1.00192904474;}
    if(pt > 50.00 && pt <= 60.00) {musf=0.9980997518; musf_d=0.997415566098; musf_u=0.998783937502;}
    if(pt > 25.00 && pt <= 30.00) {musf=0.996435081688; musf_d=0.995555149035; musf_u=0.997315014341;}
    if(pt > 60.00 ) {musf=0.999389952862; musf_d=0.998021759432; musf_u=1.00075814629;}
    if(pt > 30.00 && pt <= 40.00) {musf=1.00087087236; musf_d=1.00058473598; musf_u=1.00115700874;}
    if(pt > 40.00 && pt <= 50.00) {musf=0.999715034719; musf_d=0.999515670125; musf_u=0.999914399312;}
}
if(fabs(eta)>2.10 && fabs(eta)<=2.40){
    if(pt > 20.00 && pt <= 25.00) {musf=0.994467640194; musf_d=0.990334008718; musf_u=0.99860127167;}
    if(pt > 50.00 && pt <= 60.00) {musf=0.994452508579; musf_d=0.991732765729; musf_u=0.997172251428;}
    if(pt > 25.00 && pt <= 30.00) {musf=0.992795879929; musf_d=0.990088935767; musf_u=0.99550282409;}
    if(pt > 60.00 ) {musf=0.998280825416; musf_d=0.992878998183; musf_u=1.00368265265;}
    if(pt > 30.00 && pt <= 40.00) {musf=0.994299301303; musf_d=0.993654733806; musf_u=0.9949438688;}
    if(pt > 40.00 && pt <= 50.00) {musf=0.995255789039; musf_d=0.991721733391; musf_u=0.998789844687;}
}
if(fabs(eta)>0.90 && fabs(eta)<=1.20){
    if(pt > 20.00 && pt <= 25.00) {musf=1.0021513273; musf_d=1.00091126503; musf_u=1.00339138957;}
    if(pt > 50.00 && pt <= 60.00) {musf=0.998273907575; musf_d=0.997324814032; musf_u=0.999223001119;}
    if(pt > 25.00 && pt <= 30.00) {musf=0.999742612926; musf_d=0.997403698369; musf_u=1.00208152748;}
    if(pt > 60.00 ) {musf=0.999236708166; musf_d=0.996915999261; musf_u=1.00155741707;}
    if(pt > 30.00 && pt <= 40.00) {musf=1.00191251092; musf_d=1.00151950453; musf_u=1.00230551731;}
    if(pt > 40.00 && pt <= 50.00) {musf=0.999689283029; musf_d=0.999437590921; musf_u=0.999940975138;}
}
if(fabs(eta)>0.00 && fabs(eta)<=0.90){
    if(pt > 20.00 && pt <= 25.00) {musf=0.998018670374; musf_d=0.995317185753; musf_u=1.000720155;}
    if(pt > 50.00 && pt <= 60.00) {musf=0.998013142164; musf_d=0.997365702043; musf_u=0.998660582285;}
    if(pt > 25.00 && pt <= 30.00) {musf=0.99719721481; musf_d=0.996196419608; musf_u=0.998198010013;}
    if(pt > 60.00 ) {musf=1.00029091021; musf_d=0.999521625371; musf_u=1.00106019506;}
    if(pt > 30.00 && pt <= 40.00) {musf=1.00251468244; musf_d=1.00158408487; musf_u=1.00344528001;}
    if(pt > 40.00 && pt <= 50.00) {musf=1.00025688345; musf_d=1.00014814553; musf_u=1.00036562138;}
}

 return std::make_tuple(musf, musf_d, musf_u);

}

std::tuple<double, double, double> musf_iso(double eta, double pt){
 double musf=0, musf_d = 0, musf_u=0;
  // https://twiki.cern.ch/twiki/pub/CMS/MuonReferenceEffs2017/RunBCDEF_SF_ISO.json
  // NUM_LooseRelIso_DEN_LooseID
 if(fabs(eta)>1.20 && fabs(eta)<=2.10){
    if(pt > 20.00 && pt <= 25.00) {musf=0.996818092334; musf_d=0.99517286298; musf_u=0.998463321688;}
    if(pt > 50.00 && pt <= 60.00) {musf=0.999785897107; musf_d=0.999547566797; musf_u=1.00002422742;}
    if(pt > 25.00 && pt <= 30.00) {musf=0.999027463031; musf_d=0.998100398859; musf_u=0.999954527203;}
    if(pt > 60.00 ) {musf=1.00042884607; musf_d=0.999901224768; musf_u=1.00095646736;}
    if(pt > 30.00 && pt <= 40.00) {musf=0.998857270926; musf_d=0.998575245542; musf_u=0.99913929631;}
    if(pt > 40.00 && pt <= 50.00) {musf=0.999358772799; musf_d=0.999270468436; musf_u=0.999447077162;}
}
if(fabs(eta)>2.10 && fabs(eta)<=2.40){
    if(pt > 20.00 && pt <= 25.00) {musf=0.997637930705; musf_d=0.995461716077; musf_u=0.999814145334;}
    if(pt > 50.00 && pt <= 60.00) {musf=1.00000739502; musf_d=0.99949170477; musf_u=1.00052308527;}
    if(pt > 25.00 && pt <= 30.00) {musf=0.999041108554; musf_d=0.997830337383; musf_u=1.00025187972;}
    if(pt > 60.00 ) {musf=0.999185175032; musf_d=0.998316089714; musf_u=1.00005426035;}
    if(pt > 30.00 && pt <= 40.00) {musf=0.998931511711; musf_d=0.99854437082; musf_u=0.999318652602;}
    if(pt > 40.00 && pt <= 50.00) {musf=0.999656907198; musf_d=0.9991628247; musf_u=1.0001509897;}
}
if(fabs(eta)>0.90 && fabs(eta)<=1.20){
    if(pt > 20.00 && pt <= 25.00) {musf=0.994565683675; musf_d=0.990536307593; musf_u=0.998595059757;}
    if(pt > 50.00 && pt <= 60.00) {musf=0.999415455351; musf_d=0.998980258351; musf_u=0.99985065235;}
    if(pt > 25.00 && pt <= 30.00) {musf=0.993159025857; musf_d=0.991126914021; musf_u=0.995191137694;}
    if(pt > 60.00 ) {musf=1.00018891743; musf_d=0.999503267497; musf_u=1.00087456736;}
    if(pt > 30.00 && pt <= 40.00) {musf=0.997442209969; musf_d=0.996915940894; musf_u=0.997968479043;}
    if(pt > 40.00 && pt <= 50.00) {musf=0.998804834864; musf_d=0.998651209285; musf_u=0.998958460444;}
}
if(fabs(eta)>0.00 && fabs(eta)<=0.90){
    if(pt > 20.00 && pt <= 25.00) {musf=0.992595371452; musf_d=0.990222434525; musf_u=0.99496830838;}
    if(pt > 50.00 && pt <= 60.00) {musf=0.999640008118; musf_d=0.999416213439; musf_u=0.999863802797;}
    if(pt > 25.00 && pt <= 30.00) {musf=0.996364229898; musf_d=0.995262680877; musf_u=0.997465778918;}
    if(pt > 60.00 ) {musf=1.0000774755; musf_d=0.999724740833; musf_u=1.00043021016;}
    if(pt > 30.00 && pt <= 40.00) {musf=0.99831176374; musf_d=0.998030024077; musf_u=0.998593503404;}
    if(pt > 40.00 && pt <= 50.00) {musf=0.999363610713; musf_d=0.999270947765; musf_u=0.999456273661;}
}

 return std::make_tuple(musf, musf_d, musf_u);

}
*/
double get_wgtlumi(string FileName){
 double wgt=1;

 //xsec in pb

 // CHECKED OK!! 
 
 //wgt = xsec_in_pb / number_of_events_from_DAS
 if(FileName.find("TT") != std::string::npos) wgt=88.29/8705576; //wgt=88.29/64310000;  
 if(FileName.find("DY") != std::string::npos) wgt=6077.0/97373487; //wgt=6077/100194597;
 if(FileName.find("_ST_") != std::string::npos) wgt=32.64/7581624; //wgt=32.64/9598000; 
 if(FileName.find("_SaT_") != std::string::npos) wgt=32.70/7780870; //wgt=32.70/7623000; 
 if(FileName.find("WW") != std::string::npos) wgt=118.7/7791498; ///wgt=118.7/7850000; 
 if(FileName.find("WZ") != std::string::npos) wgt=47.13/3050057; //wgt=47.13/3885000; 
 if(FileName.find("ZZ") != std::string::npos) wgt=16.523/1949768; //wgt=16.532/1979000;
 //if(FileName.find("WJetsHT70To100") != std::string::npos) wgt=1637.13/28084244;
 if(FileName.find("WJetsHT100To200") != std::string::npos) wgt=1687.95/35862893; //wgt=1687.95/29521158;
 if(FileName.find("WJetsHT200To400") != std::string::npos) wgt=493.559/21144264; //wgt=493.559/25468933;
 if(FileName.find("WJetsHT400To600") != std::string::npos) wgt=69.55/14267690; //wgt=69.55/5932701; 
 if(FileName.find("WJetsHT600To800") != std::string::npos) wgt=15.57/21664601; //wgt=15.57/19771294; 
 if(FileName.find("WJetsHT800To1200") != std::string::npos) wgt=6.49/20348815; //wgt=6.49/8402687; 
 if(FileName.find("WJetsHT1200To2500") != std::string::npos) wgt=1.30/20258624; //wgt=1.30/7633949;
 if(FileName.find("WJetsHT2500ToInf") != std::string::npos) wgt=0.00968/21495421; //wgt=0.00968/3273980;
 if(FileName.find("WJets_") != std::string::npos) wgt=64057.4/77654763; //wgt=64057.4/71026861;
 
 //muons
 
 if((FileName.find("mumujj_17_L13_M500") != std::string::npos)) wgt=5.7090e-03/100000;
 if((FileName.find("mumujj_17_L13_M1000") != std::string::npos)) wgt=2.8140e-03/100000;
 if((FileName.find("mumujj_17_L13_M2000") != std::string::npos)) wgt=0.82140e-03/100000;
 if((FileName.find("mumujj_17_L13_M5000") != std::string::npos)) wgt=0.014250e-03/98500;
 if((FileName.find("mumujj_17_L13_M8000") != std::string::npos)) wgt=0.000091350e-03/91350;

 //electrons
 
 if((FileName.find("eejj_17_L13_M500") != std::string::npos)) wgt=5.7090e-03/100000;
 if((FileName.find("eejj_17_L13_M1000") != std::string::npos)) wgt=2.8140e-03/100000;
 if((FileName.find("eejj_17_L13_M2000") != std::string::npos)) wgt=0.82140e-03/100000;
 if((FileName.find("eejj_17_L13_M5000") != std::string::npos)) wgt=0.014250e-03/100900;
 if((FileName.find("eejj_17_L13_M8000") != std::string::npos)) wgt=0.000091350e-03/90273;
 
 return wgt;
 }

