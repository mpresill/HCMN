//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jul  7 16:42:45 2021 by ROOT version 6.14/09
// from TTree BOOM/BOOM
// found on file: /eos/user/v/vmariani/NTuples/HN_2016/Syst_ALL_HOPE/eejj_L13_M1000_2016.root
//////////////////////////////////////////////////////////

#ifndef tree_h
#define tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"

class tree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        EVENT_genHT;
   Double_t        EVENT_genPt;
   Int_t           EVENT_PDFv1_lhaid;
   Double_t        EVENT_PDFv1WeightUp;
   Double_t        EVENT_PDFv1WeightDown;
   Double_t        EVENT_PDFv1WeightCentral;
   Double_t        EVENT_PDFv1WeightMean;
   Double_t        EVENT_PDFv1WeightStdDev;
   Int_t           EVENT_PDFv2_lhaid;
   Double_t        EVENT_PDFv2WeightUp;
   Double_t        EVENT_PDFv2WeightDown;
   Double_t        EVENT_PDFv2WeightCentral;
   Double_t        EVENT_PDFv2WeightMean;
   Double_t        EVENT_PDFv2WeightStdDev;
   Int_t           EVENT_PDFv3_lhaid;
   Double_t        EVENT_PDFv3WeightUp;
   Double_t        EVENT_PDFv3WeightDown;
   Double_t        EVENT_PDFv3WeightCentral;
   Double_t        EVENT_PDFv3WeightMean;
   Double_t        EVENT_PDFv3WeightStdDev;
   Int_t           EVENT_PDFv4_lhaid;
   Double_t        EVENT_PDFv4WeightUp;
   Double_t        EVENT_PDFv4WeightDown;
   Double_t        EVENT_PDFv4WeightCentral;
   Double_t        EVENT_PDFv4WeightMean;
   Double_t        EVENT_PDFv4WeightStdDev;
   Int_t           EVENT_PDFv5_lhaid;
   Double_t        EVENT_PDFv5WeightUp;
   Double_t        EVENT_PDFv5WeightDown;
   Double_t        EVENT_PDFv5WeightCentral;
   Double_t        EVENT_PDFv5WeightMean;
   Double_t        EVENT_PDFv5WeightStdDev;
   Int_t           EVENT_PDFv6_lhaid;
   Double_t        EVENT_PDFv6WeightUp;
   Double_t        EVENT_PDFv6WeightDown;
   Double_t        EVENT_PDFv6WeightCentral;
   Double_t        EVENT_PDFv6WeightMean;
   Double_t        EVENT_PDFv6WeightStdDev;
   Int_t           HLT_Ele27_WPTight_Gsf;
   Int_t           HLT_Photon175;
   Int_t           HLT_Ele115_CaloIdVT_GsfTrkIdT;
   Int_t           HLT_Mu50;
   Int_t           HLT_TkMu50;
   Int_t           HLT_OldMu100;
   Int_t           HLT_TkMu100;
   vector<double>  *Gen_status;
   vector<double>  *Gen_pt;
   vector<double>  *Gen_eta;
   vector<double>  *Gen_phi;
   vector<double>  *Gen_charge;
   vector<double>  *Gen_energy;
   vector<double>  *Gen_pdg_id;
   vector<double>  *Gen_motherpdg_id;
   vector<double>  *Gen_numDaught;
   vector<double>  *Gen_numMother;
   vector<double>  *Muon_pt_tunePbt;
   vector<double>  *Muon_pt_tunePbt_corr;
   vector<double>  *Muon_pt_tunePbt_Roc;
   vector<double>  *Muon_eta;
   vector<double>  *Muon_phi;
   vector<double>  *Muon_p;
   vector<double>  *Muon_px;
   vector<double>  *Muon_py;
   vector<double>  *Muon_pz;
   vector<double>  *Muon_energy;
   vector<double>  *Muon_charge;
   vector<double>  *Muon_trackIso;
   vector<double>  *Muon_TrackerIso;
   vector<double>  *Muon_relIsoDeltaBetaR03;
   vector<double>  *Muon_relIsoDeltaBetaR04;
   vector<double>  *Muon_isHighPt;
   vector<int>     *Muon_TLayers;
   vector<int>     *Muon_loose;
   vector<int>     *Muon_medium;
   vector<int>     *Muon_tight;
   vector<double>  *patElectron_pt;
   vector<double>  *patElectron_eta;
   vector<double>  *patElectron_phi;
   vector<double>  *patElectron_energy;
   vector<double>  *patElectron_ecalTrkEnergyPostCorr;
   vector<double>  *patElectron_energyScaleUp;
   vector<double>  *patElectron_energyScaleDown;
   vector<double>  *patElectron_energySigmaUp;
   vector<double>  *patElectron_energySigmaDown;
   vector<int>     *patElectron_p;
   vector<int>     *patElectron_px;
   vector<int>     *patElectron_py;
   vector<int>     *patElectron_pz;
   vector<int>     *patElectron_charge;
   vector<int>     *patElectron_isPassVeto;
   vector<int>     *patElectron_isPassLoose;
   vector<int>     *patElectron_isPassMedium;
   vector<int>     *patElectron_isPassTight;
   vector<int>     *patElectron_isPassHEEPId;
   vector<int>     *patElectron_isPassMvatrig;
   vector<double>  *Jet_pt;
   vector<double>  *Jet_eta;
   vector<double>  *Jet_phi;
   vector<double>  *Jet_px;
   vector<double>  *Jet_py;
   vector<double>  *Jet_pz;
   vector<double>  *Jet_energy;
   vector<double>  *Jet_mass;
   vector<double>  *Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags;
   vector<double>  *Jet_pfCombinedMVAV2BJetTags;
   vector<bool>    *Jet_M;
   vector<double>  *Jet_nBoostedJets;
   vector<double>  *Jet_nBoostedJetsM;
   vector<double>  *Jet_L;
   vector<double>  *Jet_T;
   vector<double>  *Jet_TLV;
   vector<double>  *BoostedJet_pt;
   vector<double>  *BoostedJet_eta;
   vector<double>  *BoostedJet_phi;
   vector<double>  *BoostedJet_energy;
   vector<double>  *BoostedJet_mass;
   vector<double>  *BoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags;
   vector<bool>    *BoostedJet_M;
   vector<double>  *BoostedJet_nJets;
   vector<double>  *BoostedJet_nJetsM;
   vector<double>  *BoostedJet_L;
   vector<double>  *BoostedJet_T;
   vector<double>  *BoostedJet_TLV;
   vector<double>  *centralJesJer;
   vector<double>  *JesSFup;
   vector<double>  *JesSFdown;
   vector<double>  *JerSFup;
   vector<double>  *JerSFdown;
   Double_t        PileupWeight;
   Double_t        PUWeight;
   Double_t        MinBiasUpWeight;
   Double_t        MinBiasDownWeight;
   Int_t           nBestVtx;
   Double_t        trueInteractions;
   Double_t        lumi_wgt;
   Double_t        Met_type1PF_pt;
   Double_t        numOfHighptMu;
   Double_t        numOfLooseMu;
   Double_t        numOfMediumMu;
   Double_t        numOfTightMu;
   Double_t        numOfHighptEle;
   Double_t        numOfLooseEle;
   Double_t        numOfMediumEle;
   Double_t        numOfTightEle;
   Double_t        numOfVetoEle;
   Double_t        numOfJets;
   Double_t        numOfJets_L;
   Double_t        numOfJets_T;
   Double_t        numOfJets_TLV;
   Double_t        numOfBoostedJets;
   Double_t        numOfBoostedJets_L;
   Double_t        numOfBoostedJets_T;
   Double_t        numOfBoostedJets_TLV;
   Double_t        IsoTrack_L;
   Double_t        IsoTrack_T;
   Double_t        IsoTracker_L;
   Double_t        IsoTracker_T;
   Double_t        IsoPF_L;
   Double_t        IsoPF_T;
   Double_t        Ele1_pt;
   Double_t        Ele1_eta;
   Double_t        Ele1_phi;
   Double_t        Ele1_energy;
   Double_t        Ele1_p;
   Double_t        Ele1_px;
   Double_t        Ele1_py;
   Double_t        Ele1_pz;
   Double_t        Ele2_pt;
   Double_t        Ele2_eta;
   Double_t        Ele2_phi;
   Double_t        Ele2_energy;
   Double_t        Ele2_p;
   Double_t        Ele2_px;
   Double_t        Ele2_py;
   Double_t        Ele2_pz;
   Double_t        Muon1_pt;
   Double_t        Muon1_eta;
   Double_t        Muon1_phi;
   Double_t        Muon1_energy;
   Double_t        Muon1_p;
   Double_t        Muon1_px;
   Double_t        Muon1_py;
   Double_t        Muon1_pz;
   Double_t        Muon2_pt;
   Double_t        Muon2_eta;
   Double_t        Muon2_phi;
   Double_t        Muon2_energy;
   Double_t        Muon2_p;
   Double_t        Muon2_px;
   Double_t        Muon2_py;
   Double_t        Muon2_pz;
   Double_t        BoostedJet1_pt;
   Double_t        BoostedJet1_eta;
   Double_t        BoostedJet1_phi;
   Double_t        BoostedJet1_energy;
   Double_t        BoostedJet1_nJets;
   Double_t        BoostedJet2_pt;
   Double_t        BoostedJet2_eta;
   Double_t        BoostedJet2_phi;
   Double_t        BoostedJet2_energy;
   Double_t        BoostedJet2_nJets;
   Double_t        M_ele1ele2Bjet1;
   Double_t        M_ele1ele2;
   Double_t        M_elemu;
   Double_t        M_elemuBjet1;
   Double_t        M_mu1mu2;
   Double_t        M_mu1mu2Bjet1;
   Double_t        S_T_BJ;
   Double_t        S_T_jj;
   Double_t        M_leplep;
   Double_t        M_leplepBjet;
   Double_t        M_lep2Bjet;
   Double_t        M_leplepBjetBjet;
   Double_t        elesf_ele1;
   Double_t        elesf_ele2;
   Double_t        elesf_ele1_d;
   Double_t        elesf_ele2_d;
   Double_t        elesf_ele1_u;
   Double_t        elesf_ele2_u;
   Double_t        musf_trigger_mu1;
   Double_t        musf_ID_mu1;
   Double_t        musf_iso_mu1;
   Double_t        musf_reco_mu1;
   Double_t        musf_tot_mu1;
   Double_t        musf_trigger_mu2;
   Double_t        musf_ID_mu2;
   Double_t        musf_iso_mu2;
   Double_t        musf_reco_mu2;
   Double_t        musf_tot_mu2;
   Double_t        musf_trigger_mu1_u;
   Double_t        musf_ID_mu1_u;
   Double_t        musf_iso_mu1_u;
   Double_t        musf_reco_mu1_u;
   Double_t        musf_tot_mu1_u;
   Double_t        musf_trigger_mu2_u;
   Double_t        musf_ID_mu2_u;
   Double_t        musf_iso_mu2_u;
   Double_t        musf_reco_mu2_u;
   Double_t        musf_tot_mu2_u;
   Double_t        musf_trigger_mu1_d;
   Double_t        musf_ID_mu1_d;
   Double_t        musf_iso_mu1_d;
   Double_t        musf_reco_mu1_d;
   Double_t        musf_tot_mu1_d;
   Double_t        musf_trigger_mu2_d;
   Double_t        musf_ID_mu2_d;
   Double_t        musf_iso_mu2_d;
   Double_t        musf_reco_mu2_d;
   Double_t        musf_tot_mu2_d;
   Double_t        lepsf_evt;
   Double_t        lepsf_evt_u;
   Double_t        lepsf_evt_d;
   Double_t        eejj_l;
   Double_t        emujj_l;
   Double_t        mumujj_l;
   Double_t        muejj_l;
   Double_t        SRe;
   Double_t        TRe;
   Double_t        SRmu;
   Double_t        TRmu;
   Double_t        DYRe;
   Double_t        DYRmu;

   // List of branches
   TBranch        *b_EVENT_genHT;   //!
   TBranch        *b_EVENT_genPt;   //!
   TBranch        *b_EVENT_PDFv1_lhaid;   //!
   TBranch        *b_EVENT_PDFv1WeightUp;   //!
   TBranch        *b_EVENT_PDFv1WeightDown;   //!
   TBranch        *b_EVENT_PDFv1WeightCentral;   //!
   TBranch        *b_EVENT_PDFv1WeightMean;   //!
   TBranch        *b_EVENT_PDFv1WeightStdDev;   //!
   TBranch        *b_EVENT_PDFv2_lhaid;   //!
   TBranch        *b_EVENT_PDFv2WeightUp;   //!
   TBranch        *b_EVENT_PDFv2WeightDown;   //!
   TBranch        *b_EVENT_PDFv2WeightCentral;   //!
   TBranch        *b_EVENT_PDFv2WeightMean;   //!
   TBranch        *b_EVENT_PDFv2WeightStdDev;   //!
   TBranch        *b_EVENT_PDFv3_lhaid;   //!
   TBranch        *b_EVENT_PDFv3WeightUp;   //!
   TBranch        *b_EVENT_PDFv3WeightDown;   //!
   TBranch        *b_EVENT_PDFv3WeightCentral;   //!
   TBranch        *b_EVENT_PDFv3WeightMean;   //!
   TBranch        *b_EVENT_PDFv3WeightStdDev;   //!
   TBranch        *b_EVENT_PDFv4_lhaid;   //!
   TBranch        *b_EVENT_PDFv4WeightUp;   //!
   TBranch        *b_EVENT_PDFv4WeightDown;   //!
   TBranch        *b_EVENT_PDFv4WeightCentral;   //!
   TBranch        *b_EVENT_PDFv4WeightMean;   //!
   TBranch        *b_EVENT_PDFv4WeightStdDev;   //!
   TBranch        *b_EVENT_PDFv5_lhaid;   //!
   TBranch        *b_EVENT_PDFv5WeightUp;   //!
   TBranch        *b_EVENT_PDFv5WeightDown;   //!
   TBranch        *b_EVENT_PDFv5WeightCentral;   //!
   TBranch        *b_EVENT_PDFv5WeightMean;   //!
   TBranch        *b_EVENT_PDFv5WeightStdDev;   //!
   TBranch        *b_EVENT_PDFv6_lhaid;   //!
   TBranch        *b_EVENT_PDFv6WeightUp;   //!
   TBranch        *b_EVENT_PDFv6WeightDown;   //!
   TBranch        *b_EVENT_PDFv6WeightCentral;   //!
   TBranch        *b_EVENT_PDFv6WeightMean;   //!
   TBranch        *b_EVENT_PDFv6WeightStdDev;   //!
   TBranch        *b_HLT_Ele27_WPTight_Gsf;   //!
   TBranch        *b_HLT_Photon175;   //!
   TBranch        *b_HLT_Ele115_CaloIdVT_GsfTrkIdT;   //!
   TBranch        *b_HLT_Mu50;   //!
   TBranch        *b_HLT_TkMu50;   //!
   TBranch        *b_HLT_OldMu100;   //!
   TBranch        *b_HLT_TkMu100;   //!
   TBranch        *b_Gen_status;   //!
   TBranch        *b_Gen_pt;   //!
   TBranch        *b_Gen_eta;   //!
   TBranch        *b_Gen_phi;   //!
   TBranch        *b_Gen_charge;   //!
   TBranch        *b_Gen_energy;   //!
   TBranch        *b_Gen_pdg_id;   //!
   TBranch        *b_Gen_motherpdg_id;   //!
   TBranch        *b_Gen_numDaught;   //!
   TBranch        *b_Gen_numMother;   //!
   TBranch        *b_Muon_pt_tunePbt;   //!
   TBranch        *b_Muon_pt_tunePbt_corr;   //!
   TBranch        *b_Muon_pt_tunePbt_Roc;   //!
   TBranch        *b_Muon_eta;   //!
   TBranch        *b_Muon_phi;   //!
   TBranch        *b_Muon_p;   //!
   TBranch        *b_Muon_px;   //!
   TBranch        *b_Muon_py;   //!
   TBranch        *b_Muon_pz;   //!
   TBranch        *b_Muon_energy;   //!
   TBranch        *b_Muon_charge;   //!
   TBranch        *b_Muon_trackIso;   //!
   TBranch        *b_Muon_TrackerIso;   //!
   TBranch        *b_Muon_relIsoDeltaBetaR03;   //!
   TBranch        *b_Muon_relIsoDeltaBetaR04;   //!
   TBranch        *b_Muon_isHighPt;   //!
   TBranch        *b_Muon_TLayers;   //!
   TBranch        *b_Muon_loose;   //!
   TBranch        *b_Muon_medium;   //!
   TBranch        *b_Muon_tight;   //!
   TBranch        *b_patElectron_pt;   //!
   TBranch        *b_patElectron_eta;   //!
   TBranch        *b_patElectron_phi;   //!
   TBranch        *b_patElectron_energy;   //!
   TBranch        *b_patElectron_ecalTrkEnergyPostCorr;   //!
   TBranch        *b_patElectron_energyScaleUp;   //!
   TBranch        *b_patElectron_energyScaleDown;   //!
   TBranch        *b_patElectron_energySigmaUp;   //!
   TBranch        *b_patElectron_energySigmaDown;   //!
   TBranch        *b_patElectron_p;   //!
   TBranch        *b_patElectron_px;   //!
   TBranch        *b_patElectron_py;   //!
   TBranch        *b_patElectron_pz;   //!
   TBranch        *b_patElectron_charge;   //!
   TBranch        *b_patElectron_isPassVeto;   //!
   TBranch        *b_patElectron_isPassLoose;   //!
   TBranch        *b_patElectron_isPassMedium;   //!
   TBranch        *b_patElectron_isPassTight;   //!
   TBranch        *b_patElectron_isPassHEEPId;   //!
   TBranch        *b_patElectron_isPassMvatrig;   //!
   TBranch        *b_Jet_pt;   //!
   TBranch        *b_Jet_eta;   //!
   TBranch        *b_Jet_phi;   //!
   TBranch        *b_Jet_px;   //!
   TBranch        *b_Jet_py;   //!
   TBranch        *b_Jet_pz;   //!
   TBranch        *b_Jet_energy;   //!
   TBranch        *b_Jet_mass;   //!
   TBranch        *b_Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags;   //!
   TBranch        *b_Jet_pfCombinedMVAV2BJetTags;   //!
   TBranch        *b_Jet_M;   //!
   TBranch        *b_Jet_nBoostedJets;   //!
   TBranch        *b_Jet_nBoostedJetsM;   //!
   TBranch        *b_Jet_L;   //!
   TBranch        *b_Jet_T;   //!
   TBranch        *b_Jet_TLV;   //!
   TBranch        *b_BoostedJet_pt;   //!
   TBranch        *b_BoostedJet_eta;   //!
   TBranch        *b_BoostedJet_phi;   //!
   TBranch        *b_BoostedJet_energy;   //!
   TBranch        *b_BoostedJet_mass;   //!
   TBranch        *b_BoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags;   //!
   TBranch        *b_BoostedJet_M;   //!
   TBranch        *b_BoostedJet_nJets;   //!
   TBranch        *b_BoostedJet_nJetsM;   //!
   TBranch        *b_BoostedJet_L;   //!
   TBranch        *b_BoostedJet_T;   //!
   TBranch        *b_BoostedJet_TLV;   //!
   TBranch        *b_centralJesJer;   //!
   TBranch        *b_JesSFup;   //!
   TBranch        *b_JesSFdown;   //!
   TBranch        *b_JerSFup;   //!
   TBranch        *b_JerSFdown;   //!
   TBranch        *b_PileupWeight;   //!
   TBranch        *b_PUWeight;   //!
   TBranch        *b_MinBiasUpWeight;   //!
   TBranch        *b_MinBiasDownWeight;   //!
   TBranch        *b_nBestVtx;   //!
   TBranch        *b_trueInteractions;   //!
   TBranch        *b_lumi_wgt;   //!
   TBranch        *b_Met_type1PF_pt;   //!
   TBranch        *b_numOfHighptMu;   //!
   TBranch        *b_numOfLooseMu;   //!
   TBranch        *b_numOfMediumMu;   //!
   TBranch        *b_numOfTightMu;   //!
   TBranch        *b_numOfHighptEle;   //!
   TBranch        *b_numOfLooseEle;   //!
   TBranch        *b_numOfMediumEle;   //!
   TBranch        *b_numOfTightEle;   //!
   TBranch        *b_numOfVetoEle;   //!
   TBranch        *b_numOfJets;   //!
   TBranch        *b_numOfJets_L;   //!
   TBranch        *b_numOfJets_T;   //!
   TBranch        *b_numOfJets_TLV;   //!
   TBranch        *b_numOfBoostedJets;   //!
   TBranch        *b_numOfBoostedJets_L;   //!
   TBranch        *b_numOfBoostedJets_T;   //!
   TBranch        *b_numOfBoostedJets_TLV;   //!
   TBranch        *b_IsoTrack_L;   //!
   TBranch        *b_IsoTrack_T;   //!
   TBranch        *b_IsoTracker_L;   //!
   TBranch        *b_IsoTracker_T;   //!
   TBranch        *b_IsoPF_L;   //!
   TBranch        *b_IsoPF_T;   //!
   TBranch        *b_Ele1_pt;   //!
   TBranch        *b_Ele1_eta;   //!
   TBranch        *b_Ele1_phi;   //!
   TBranch        *b_Ele1_energy;   //!
   TBranch        *b_Ele1_p;   //!
   TBranch        *b_Ele1_px;   //!
   TBranch        *b_Ele1_py;   //!
   TBranch        *b_Ele1_pz;   //!
   TBranch        *b_Ele2_pt;   //!
   TBranch        *b_Ele2_eta;   //!
   TBranch        *b_Ele2_phi;   //!
   TBranch        *b_Ele2_energy;   //!
   TBranch        *b_Ele2_p;   //!
   TBranch        *b_Ele2_px;   //!
   TBranch        *b_Ele2_py;   //!
   TBranch        *b_Ele2_pz;   //!
   TBranch        *b_Muon1_pt;   //!
   TBranch        *b_Muon1_eta;   //!
   TBranch        *b_Muon1_phi;   //!
   TBranch        *b_Muon1_energy;   //!
   TBranch        *b_Muon1_p;   //!
   TBranch        *b_Muon1_px;   //!
   TBranch        *b_Muon1_py;   //!
   TBranch        *b_Muon1_pz;   //!
   TBranch        *b_Muon2_pt;   //!
   TBranch        *b_Muon2_eta;   //!
   TBranch        *b_Muon2_phi;   //!
   TBranch        *b_Muon2_energy;   //!
   TBranch        *b_Muon2_p;   //!
   TBranch        *b_Muon2_px;   //!
   TBranch        *b_Muon2_py;   //!
   TBranch        *b_Muon2_pz;   //!
   TBranch        *b_BoostedJet1_pt;   //!
   TBranch        *b_BoostedJet1_eta;   //!
   TBranch        *b_BoostedJet1_phi;   //!
   TBranch        *b_BoostedJet1_energy;   //!
   TBranch        *b_BoostedJet1_nJets;   //!
   TBranch        *b_BoostedJet2_pt;   //!
   TBranch        *b_BoostedJet2_eta;   //!
   TBranch        *b_BoostedJet2_phi;   //!
   TBranch        *b_BoostedJet2_energy;   //!
   TBranch        *b_BoostedJet2_nJets;   //!
   TBranch        *b_M_ele1ele2Bjet1;   //!
   TBranch        *b_M_ele1ele2;   //!
   TBranch        *b_M_elemu;   //!
   TBranch        *b_M_elemuBjet1;   //!
   TBranch        *b_M_mu1mu2;   //!
   TBranch        *b_M_mu1mu2Bjet1;   //!
   TBranch        *b_S_T_BJ;   //!
   TBranch        *b_S_T_jj;   //!
   TBranch        *b_M_leplep;   //!
   TBranch        *b_M_leplepBjet;   //!
   TBranch        *b_M_lep2Bjet;   //!
   TBranch        *b_M_leplepBjetBjet;   //!
   TBranch        *b_elesf_ele1;   //!
   TBranch        *b_elesf_ele2;   //!
   TBranch        *b_elesf_ele1_d;   //!
   TBranch        *b_elesf_ele2_d;   //!
   TBranch        *b_elesf_ele1_u;   //!
   TBranch        *b_elesf_ele2_u;   //!
   TBranch        *b_musf_trigger_mu1;   //!
   TBranch        *b_musf_ID_mu1;   //!
   TBranch        *b_musf_iso_mu1;   //!
   TBranch        *b_musf_reco_mu1;   //!
   TBranch        *b_musf_tot_mu1;   //!
   TBranch        *b_musf_trigger_mu2;   //!
   TBranch        *b_musf_ID_mu2;   //!
   TBranch        *b_musf_iso_mu2;   //!
   TBranch        *b_musf_reco_mu2;   //!
   TBranch        *b_musf_tot_mu2;   //!
   TBranch        *b_musf_trigger_mu1_u;   //!
   TBranch        *b_musf_ID_mu1_u;   //!
   TBranch        *b_musf_iso_mu1_u;   //!
   TBranch        *b_musf_reco_mu1_u;   //!
   TBranch        *b_musf_tot_mu1_u;   //!
   TBranch        *b_musf_trigger_mu2_u;   //!
   TBranch        *b_musf_ID_mu2_u;   //!
   TBranch        *b_musf_iso_mu2_u;   //!
   TBranch        *b_musf_reco_mu2_u;   //!
   TBranch        *b_musf_tot_mu2_u;   //!
   TBranch        *b_musf_trigger_mu1_d;   //!
   TBranch        *b_musf_ID_mu1_d;   //!
   TBranch        *b_musf_iso_mu1_d;   //!
   TBranch        *b_musf_reco_mu1_d;   //!
   TBranch        *b_musf_tot_mu1_d;   //!
   TBranch        *b_musf_trigger_mu2_d;   //!
   TBranch        *b_musf_ID_mu2_d;   //!
   TBranch        *b_musf_iso_mu2_d;   //!
   TBranch        *b_musf_reco_mu2_d;   //!
   TBranch        *b_musf_tot_mu2_d;   //!
   TBranch        *b_lepsf_evt;   //!
   TBranch        *b_lepsf_evt_u;   //!
   TBranch        *b_lepsf_evt_d;   //!
   TBranch        *b_eejj_l;   //!
   TBranch        *b_emujj_l;   //!
   TBranch        *b_mumujj_l;   //!
   TBranch        *b_muejj_l;   //!
   TBranch        *b_SRe;   //!
   TBranch        *b_TRe;   //!
   TBranch        *b_SRmu;   //!
   TBranch        *b_TRmu;   //!
   TBranch        *b_DYRe;   //!
   TBranch        *b_DYRmu;   //!

   tree(TTree *tree=0);
   virtual ~tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef tree_cxx
tree::tree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/user/v/vmariani/NTuples/HN_2016/Syst_ALL_HOPE/eejj_L13_M1000_2016.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/eos/user/v/vmariani/NTuples/HN_2016/Syst_ALL_HOPE/eejj_L13_M1000_2016.root");
      }
      f->GetObject("BOOM",tree);

   }
   Init(tree);
}

tree::~tree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void tree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   Gen_status = 0;
   Gen_pt = 0;
   Gen_eta = 0;
   Gen_phi = 0;
   Gen_charge = 0;
   Gen_energy = 0;
   Gen_pdg_id = 0;
   Gen_motherpdg_id = 0;
   Gen_numDaught = 0;
   Gen_numMother = 0;
   Muon_pt_tunePbt = 0;
   Muon_pt_tunePbt_corr = 0;
   Muon_pt_tunePbt_Roc = 0;
   Muon_eta = 0;
   Muon_phi = 0;
   Muon_p = 0;
   Muon_px = 0;
   Muon_py = 0;
   Muon_pz = 0;
   Muon_energy = 0;
   Muon_charge = 0;
   Muon_trackIso = 0;
   Muon_TrackerIso = 0;
   Muon_relIsoDeltaBetaR03 = 0;
   Muon_relIsoDeltaBetaR04 = 0;
   Muon_isHighPt = 0;
   Muon_TLayers = 0;
   Muon_loose = 0;
   Muon_medium = 0;
   Muon_tight = 0;
   patElectron_pt = 0;
   patElectron_eta = 0;
   patElectron_phi = 0;
   patElectron_energy = 0;
   patElectron_ecalTrkEnergyPostCorr = 0;
   patElectron_energyScaleUp = 0;
   patElectron_energyScaleDown = 0;
   patElectron_energySigmaUp = 0;
   patElectron_energySigmaDown = 0;
   patElectron_p = 0;
   patElectron_px = 0;
   patElectron_py = 0;
   patElectron_pz = 0;
   patElectron_charge = 0;
   patElectron_isPassVeto = 0;
   patElectron_isPassLoose = 0;
   patElectron_isPassMedium = 0;
   patElectron_isPassTight = 0;
   patElectron_isPassHEEPId = 0;
   patElectron_isPassMvatrig = 0;
   Jet_pt = 0;
   Jet_eta = 0;
   Jet_phi = 0;
   Jet_px = 0;
   Jet_py = 0;
   Jet_pz = 0;
   Jet_energy = 0;
   Jet_mass = 0;
   Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags = 0;
   Jet_pfCombinedMVAV2BJetTags = 0;
   Jet_M = 0;
   Jet_nBoostedJets = 0;
   Jet_nBoostedJetsM = 0;
   Jet_L = 0;
   Jet_T = 0;
   Jet_TLV = 0;
   BoostedJet_pt = 0;
   BoostedJet_eta = 0;
   BoostedJet_phi = 0;
   BoostedJet_energy = 0;
   BoostedJet_mass = 0;
   BoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags = 0;
   BoostedJet_M = 0;
   BoostedJet_nJets = 0;
   BoostedJet_nJetsM = 0;
   BoostedJet_L = 0;
   BoostedJet_T = 0;
   BoostedJet_TLV = 0;
   centralJesJer = 0;
   JesSFup = 0;
   JesSFdown = 0;
   JerSFup = 0;
   JerSFdown = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EVENT_genHT", &EVENT_genHT, &b_EVENT_genHT);
   fChain->SetBranchAddress("EVENT_genPt", &EVENT_genPt, &b_EVENT_genPt);
   fChain->SetBranchAddress("EVENT_PDFv1_lhaid", &EVENT_PDFv1_lhaid, &b_EVENT_PDFv1_lhaid);
   fChain->SetBranchAddress("EVENT_PDFv1WeightUp", &EVENT_PDFv1WeightUp, &b_EVENT_PDFv1WeightUp);
   fChain->SetBranchAddress("EVENT_PDFv1WeightDown", &EVENT_PDFv1WeightDown, &b_EVENT_PDFv1WeightDown);
   fChain->SetBranchAddress("EVENT_PDFv1WeightCentral", &EVENT_PDFv1WeightCentral, &b_EVENT_PDFv1WeightCentral);
   fChain->SetBranchAddress("EVENT_PDFv1WeightMean", &EVENT_PDFv1WeightMean, &b_EVENT_PDFv1WeightMean);
   fChain->SetBranchAddress("EVENT_PDFv1WeightStdDev", &EVENT_PDFv1WeightStdDev, &b_EVENT_PDFv1WeightStdDev);
   fChain->SetBranchAddress("EVENT_PDFv2_lhaid", &EVENT_PDFv2_lhaid, &b_EVENT_PDFv2_lhaid);
   fChain->SetBranchAddress("EVENT_PDFv2WeightUp", &EVENT_PDFv2WeightUp, &b_EVENT_PDFv2WeightUp);
   fChain->SetBranchAddress("EVENT_PDFv2WeightDown", &EVENT_PDFv2WeightDown, &b_EVENT_PDFv2WeightDown);
   fChain->SetBranchAddress("EVENT_PDFv2WeightCentral", &EVENT_PDFv2WeightCentral, &b_EVENT_PDFv2WeightCentral);
   fChain->SetBranchAddress("EVENT_PDFv2WeightMean", &EVENT_PDFv2WeightMean, &b_EVENT_PDFv2WeightMean);
   fChain->SetBranchAddress("EVENT_PDFv2WeightStdDev", &EVENT_PDFv2WeightStdDev, &b_EVENT_PDFv2WeightStdDev);
   fChain->SetBranchAddress("EVENT_PDFv3_lhaid", &EVENT_PDFv3_lhaid, &b_EVENT_PDFv3_lhaid);
   fChain->SetBranchAddress("EVENT_PDFv3WeightUp", &EVENT_PDFv3WeightUp, &b_EVENT_PDFv3WeightUp);
   fChain->SetBranchAddress("EVENT_PDFv3WeightDown", &EVENT_PDFv3WeightDown, &b_EVENT_PDFv3WeightDown);
   fChain->SetBranchAddress("EVENT_PDFv3WeightCentral", &EVENT_PDFv3WeightCentral, &b_EVENT_PDFv3WeightCentral);
   fChain->SetBranchAddress("EVENT_PDFv3WeightMean", &EVENT_PDFv3WeightMean, &b_EVENT_PDFv3WeightMean);
   fChain->SetBranchAddress("EVENT_PDFv3WeightStdDev", &EVENT_PDFv3WeightStdDev, &b_EVENT_PDFv3WeightStdDev);
   fChain->SetBranchAddress("EVENT_PDFv4_lhaid", &EVENT_PDFv4_lhaid, &b_EVENT_PDFv4_lhaid);
   fChain->SetBranchAddress("EVENT_PDFv4WeightUp", &EVENT_PDFv4WeightUp, &b_EVENT_PDFv4WeightUp);
   fChain->SetBranchAddress("EVENT_PDFv4WeightDown", &EVENT_PDFv4WeightDown, &b_EVENT_PDFv4WeightDown);
   fChain->SetBranchAddress("EVENT_PDFv4WeightCentral", &EVENT_PDFv4WeightCentral, &b_EVENT_PDFv4WeightCentral);
   fChain->SetBranchAddress("EVENT_PDFv4WeightMean", &EVENT_PDFv4WeightMean, &b_EVENT_PDFv4WeightMean);
   fChain->SetBranchAddress("EVENT_PDFv4WeightStdDev", &EVENT_PDFv4WeightStdDev, &b_EVENT_PDFv4WeightStdDev);
   fChain->SetBranchAddress("EVENT_PDFv5_lhaid", &EVENT_PDFv5_lhaid, &b_EVENT_PDFv5_lhaid);
   fChain->SetBranchAddress("EVENT_PDFv5WeightUp", &EVENT_PDFv5WeightUp, &b_EVENT_PDFv5WeightUp);
   fChain->SetBranchAddress("EVENT_PDFv5WeightDown", &EVENT_PDFv5WeightDown, &b_EVENT_PDFv5WeightDown);
   fChain->SetBranchAddress("EVENT_PDFv5WeightCentral", &EVENT_PDFv5WeightCentral, &b_EVENT_PDFv5WeightCentral);
   fChain->SetBranchAddress("EVENT_PDFv5WeightMean", &EVENT_PDFv5WeightMean, &b_EVENT_PDFv5WeightMean);
   fChain->SetBranchAddress("EVENT_PDFv5WeightStdDev", &EVENT_PDFv5WeightStdDev, &b_EVENT_PDFv5WeightStdDev);
   fChain->SetBranchAddress("EVENT_PDFv6_lhaid", &EVENT_PDFv6_lhaid, &b_EVENT_PDFv6_lhaid);
   fChain->SetBranchAddress("EVENT_PDFv6WeightUp", &EVENT_PDFv6WeightUp, &b_EVENT_PDFv6WeightUp);
   fChain->SetBranchAddress("EVENT_PDFv6WeightDown", &EVENT_PDFv6WeightDown, &b_EVENT_PDFv6WeightDown);
   fChain->SetBranchAddress("EVENT_PDFv6WeightCentral", &EVENT_PDFv6WeightCentral, &b_EVENT_PDFv6WeightCentral);
   fChain->SetBranchAddress("EVENT_PDFv6WeightMean", &EVENT_PDFv6WeightMean, &b_EVENT_PDFv6WeightMean);
   fChain->SetBranchAddress("EVENT_PDFv6WeightStdDev", &EVENT_PDFv6WeightStdDev, &b_EVENT_PDFv6WeightStdDev);
   fChain->SetBranchAddress("HLT_Ele27_WPTight_Gsf", &HLT_Ele27_WPTight_Gsf, &b_HLT_Ele27_WPTight_Gsf);
   fChain->SetBranchAddress("HLT_Photon175", &HLT_Photon175, &b_HLT_Photon175);
   fChain->SetBranchAddress("HLT_Ele115_CaloIdVT_GsfTrkIdT", &HLT_Ele115_CaloIdVT_GsfTrkIdT, &b_HLT_Ele115_CaloIdVT_GsfTrkIdT);
   fChain->SetBranchAddress("HLT_Mu50", &HLT_Mu50, &b_HLT_Mu50);
   fChain->SetBranchAddress("HLT_TkMu50", &HLT_TkMu50, &b_HLT_TkMu50);
   fChain->SetBranchAddress("HLT_OldMu100", &HLT_OldMu100, &b_HLT_OldMu100);
   fChain->SetBranchAddress("HLT_TkMu100", &HLT_TkMu100, &b_HLT_TkMu100);
   fChain->SetBranchAddress("Gen_status", &Gen_status, &b_Gen_status);
   fChain->SetBranchAddress("Gen_pt", &Gen_pt, &b_Gen_pt);
   fChain->SetBranchAddress("Gen_eta", &Gen_eta, &b_Gen_eta);
   fChain->SetBranchAddress("Gen_phi", &Gen_phi, &b_Gen_phi);
   fChain->SetBranchAddress("Gen_charge", &Gen_charge, &b_Gen_charge);
   fChain->SetBranchAddress("Gen_energy", &Gen_energy, &b_Gen_energy);
   fChain->SetBranchAddress("Gen_pdg_id", &Gen_pdg_id, &b_Gen_pdg_id);
   fChain->SetBranchAddress("Gen_motherpdg_id", &Gen_motherpdg_id, &b_Gen_motherpdg_id);
   fChain->SetBranchAddress("Gen_numDaught", &Gen_numDaught, &b_Gen_numDaught);
   fChain->SetBranchAddress("Gen_numMother", &Gen_numMother, &b_Gen_numMother);
   fChain->SetBranchAddress("Muon_pt_tunePbt", &Muon_pt_tunePbt, &b_Muon_pt_tunePbt);
   fChain->SetBranchAddress("Muon_pt_tunePbt_corr", &Muon_pt_tunePbt_corr, &b_Muon_pt_tunePbt_corr);
   fChain->SetBranchAddress("Muon_pt_tunePbt_Roc", &Muon_pt_tunePbt_Roc, &b_Muon_pt_tunePbt_Roc);
   fChain->SetBranchAddress("Muon_eta", &Muon_eta, &b_Muon_eta);
   fChain->SetBranchAddress("Muon_phi", &Muon_phi, &b_Muon_phi);
   fChain->SetBranchAddress("Muon_p", &Muon_p, &b_Muon_p);
   fChain->SetBranchAddress("Muon_px", &Muon_px, &b_Muon_px);
   fChain->SetBranchAddress("Muon_py", &Muon_py, &b_Muon_py);
   fChain->SetBranchAddress("Muon_pz", &Muon_pz, &b_Muon_pz);
   fChain->SetBranchAddress("Muon_energy", &Muon_energy, &b_Muon_energy);
   fChain->SetBranchAddress("Muon_charge", &Muon_charge, &b_Muon_charge);
   fChain->SetBranchAddress("Muon_trackIso", &Muon_trackIso, &b_Muon_trackIso);
   fChain->SetBranchAddress("Muon_TrackerIso", &Muon_TrackerIso, &b_Muon_TrackerIso);
   fChain->SetBranchAddress("Muon_relIsoDeltaBetaR03", &Muon_relIsoDeltaBetaR03, &b_Muon_relIsoDeltaBetaR03);
   fChain->SetBranchAddress("Muon_relIsoDeltaBetaR04", &Muon_relIsoDeltaBetaR04, &b_Muon_relIsoDeltaBetaR04);
   fChain->SetBranchAddress("Muon_isHighPt", &Muon_isHighPt, &b_Muon_isHighPt);
   fChain->SetBranchAddress("Muon_TLayers", &Muon_TLayers, &b_Muon_TLayers);
   fChain->SetBranchAddress("Muon_loose", &Muon_loose, &b_Muon_loose);
   fChain->SetBranchAddress("Muon_medium", &Muon_medium, &b_Muon_medium);
   fChain->SetBranchAddress("Muon_tight", &Muon_tight, &b_Muon_tight);
   fChain->SetBranchAddress("patElectron_pt", &patElectron_pt, &b_patElectron_pt);
   fChain->SetBranchAddress("patElectron_eta", &patElectron_eta, &b_patElectron_eta);
   fChain->SetBranchAddress("patElectron_phi", &patElectron_phi, &b_patElectron_phi);
   fChain->SetBranchAddress("patElectron_energy", &patElectron_energy, &b_patElectron_energy);
   fChain->SetBranchAddress("patElectron_ecalTrkEnergyPostCorr", &patElectron_ecalTrkEnergyPostCorr, &b_patElectron_ecalTrkEnergyPostCorr);
   fChain->SetBranchAddress("patElectron_energyScaleUp", &patElectron_energyScaleUp, &b_patElectron_energyScaleUp);
   fChain->SetBranchAddress("patElectron_energyScaleDown", &patElectron_energyScaleDown, &b_patElectron_energyScaleDown);
   fChain->SetBranchAddress("patElectron_energySigmaUp", &patElectron_energySigmaUp, &b_patElectron_energySigmaUp);
   fChain->SetBranchAddress("patElectron_energySigmaDown", &patElectron_energySigmaDown, &b_patElectron_energySigmaDown);
   fChain->SetBranchAddress("patElectron_p", &patElectron_p, &b_patElectron_p);
   fChain->SetBranchAddress("patElectron_px", &patElectron_px, &b_patElectron_px);
   fChain->SetBranchAddress("patElectron_py", &patElectron_py, &b_patElectron_py);
   fChain->SetBranchAddress("patElectron_pz", &patElectron_pz, &b_patElectron_pz);
   fChain->SetBranchAddress("patElectron_charge", &patElectron_charge, &b_patElectron_charge);
   fChain->SetBranchAddress("patElectron_isPassVeto", &patElectron_isPassVeto, &b_patElectron_isPassVeto);
   fChain->SetBranchAddress("patElectron_isPassLoose", &patElectron_isPassLoose, &b_patElectron_isPassLoose);
   fChain->SetBranchAddress("patElectron_isPassMedium", &patElectron_isPassMedium, &b_patElectron_isPassMedium);
   fChain->SetBranchAddress("patElectron_isPassTight", &patElectron_isPassTight, &b_patElectron_isPassTight);
   fChain->SetBranchAddress("patElectron_isPassHEEPId", &patElectron_isPassHEEPId, &b_patElectron_isPassHEEPId);
   fChain->SetBranchAddress("patElectron_isPassMvatrig", &patElectron_isPassMvatrig, &b_patElectron_isPassMvatrig);
   fChain->SetBranchAddress("Jet_pt", &Jet_pt, &b_Jet_pt);
   fChain->SetBranchAddress("Jet_eta", &Jet_eta, &b_Jet_eta);
   fChain->SetBranchAddress("Jet_phi", &Jet_phi, &b_Jet_phi);
   fChain->SetBranchAddress("Jet_px", &Jet_px, &b_Jet_px);
   fChain->SetBranchAddress("Jet_py", &Jet_py, &b_Jet_py);
   fChain->SetBranchAddress("Jet_pz", &Jet_pz, &b_Jet_pz);
   fChain->SetBranchAddress("Jet_energy", &Jet_energy, &b_Jet_energy);
   fChain->SetBranchAddress("Jet_mass", &Jet_mass, &b_Jet_mass);
   fChain->SetBranchAddress("Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags", &Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags, &b_Jet_pfCombinedInclusiveSecondaryVertexV2BJetTags);
   fChain->SetBranchAddress("Jet_pfCombinedMVAV2BJetTags", &Jet_pfCombinedMVAV2BJetTags, &b_Jet_pfCombinedMVAV2BJetTags);
   fChain->SetBranchAddress("Jet_M", &Jet_M, &b_Jet_M);
   fChain->SetBranchAddress("Jet_nBoostedJets", &Jet_nBoostedJets, &b_Jet_nBoostedJets);
   fChain->SetBranchAddress("Jet_nBoostedJetsM", &Jet_nBoostedJetsM, &b_Jet_nBoostedJetsM);
   fChain->SetBranchAddress("Jet_L", &Jet_L, &b_Jet_L);
   fChain->SetBranchAddress("Jet_T", &Jet_T, &b_Jet_T);
   fChain->SetBranchAddress("Jet_TLV", &Jet_TLV, &b_Jet_TLV);
   fChain->SetBranchAddress("BoostedJet_pt", &BoostedJet_pt, &b_BoostedJet_pt);
   fChain->SetBranchAddress("BoostedJet_eta", &BoostedJet_eta, &b_BoostedJet_eta);
   fChain->SetBranchAddress("BoostedJet_phi", &BoostedJet_phi, &b_BoostedJet_phi);
   fChain->SetBranchAddress("BoostedJet_energy", &BoostedJet_energy, &b_BoostedJet_energy);
   fChain->SetBranchAddress("BoostedJet_mass", &BoostedJet_mass, &b_BoostedJet_mass);
   fChain->SetBranchAddress("BoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags", &BoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags, &b_BoostedJet_pfCombinedInclusiveSecondaryVertexV2BJetTags);
   fChain->SetBranchAddress("BoostedJet_M", &BoostedJet_M, &b_BoostedJet_M);
   fChain->SetBranchAddress("BoostedJet_nJets", &BoostedJet_nJets, &b_BoostedJet_nJets);
   fChain->SetBranchAddress("BoostedJet_nJetsM", &BoostedJet_nJetsM, &b_BoostedJet_nJetsM);
   fChain->SetBranchAddress("BoostedJet_L", &BoostedJet_L, &b_BoostedJet_L);
   fChain->SetBranchAddress("BoostedJet_T", &BoostedJet_T, &b_BoostedJet_T);
   fChain->SetBranchAddress("BoostedJet_TLV", &BoostedJet_TLV, &b_BoostedJet_TLV);
   fChain->SetBranchAddress("centralJesJer", &centralJesJer, &b_centralJesJer);
   fChain->SetBranchAddress("JesSFup", &JesSFup, &b_JesSFup);
   fChain->SetBranchAddress("JesSFdown", &JesSFdown, &b_JesSFdown);
   fChain->SetBranchAddress("JerSFup", &JerSFup, &b_JerSFup);
   fChain->SetBranchAddress("JerSFdown", &JerSFdown, &b_JerSFdown);
   fChain->SetBranchAddress("PileupWeight", &PileupWeight, &b_PileupWeight);
   fChain->SetBranchAddress("PUWeight", &PUWeight, &b_PUWeight);
   fChain->SetBranchAddress("MinBiasUpWeight", &MinBiasUpWeight, &b_MinBiasUpWeight);
   fChain->SetBranchAddress("MinBiasDownWeight", &MinBiasDownWeight, &b_MinBiasDownWeight);
   fChain->SetBranchAddress("nBestVtx", &nBestVtx, &b_nBestVtx);
   fChain->SetBranchAddress("trueInteractions", &trueInteractions, &b_trueInteractions);
   fChain->SetBranchAddress("lumi_wgt", &lumi_wgt, &b_lumi_wgt);
   fChain->SetBranchAddress("Met_type1PF_pt", &Met_type1PF_pt, &b_Met_type1PF_pt);
   fChain->SetBranchAddress("numOfHighptMu", &numOfHighptMu, &b_numOfHighptMu);
   fChain->SetBranchAddress("numOfLooseMu", &numOfLooseMu, &b_numOfLooseMu);
   fChain->SetBranchAddress("numOfMediumMu", &numOfMediumMu, &b_numOfMediumMu);
   fChain->SetBranchAddress("numOfTightMu", &numOfTightMu, &b_numOfTightMu);
   fChain->SetBranchAddress("numOfHighptEle", &numOfHighptEle, &b_numOfHighptEle);
   fChain->SetBranchAddress("numOfLooseEle", &numOfLooseEle, &b_numOfLooseEle);
   fChain->SetBranchAddress("numOfMediumEle", &numOfMediumEle, &b_numOfMediumEle);
   fChain->SetBranchAddress("numOfTightEle", &numOfTightEle, &b_numOfTightEle);
   fChain->SetBranchAddress("numOfVetoEle", &numOfVetoEle, &b_numOfVetoEle);
   fChain->SetBranchAddress("numOfJets", &numOfJets, &b_numOfJets);
   fChain->SetBranchAddress("numOfJets_L", &numOfJets_L, &b_numOfJets_L);
   fChain->SetBranchAddress("numOfJets_T", &numOfJets_T, &b_numOfJets_T);
   fChain->SetBranchAddress("numOfJets_TLV", &numOfJets_TLV, &b_numOfJets_TLV);
   fChain->SetBranchAddress("numOfBoostedJets", &numOfBoostedJets, &b_numOfBoostedJets);
   fChain->SetBranchAddress("numOfBoostedJets_L", &numOfBoostedJets_L, &b_numOfBoostedJets_L);
   fChain->SetBranchAddress("numOfBoostedJets_T", &numOfBoostedJets_T, &b_numOfBoostedJets_T);
   fChain->SetBranchAddress("numOfBoostedJets_TLV", &numOfBoostedJets_TLV, &b_numOfBoostedJets_TLV);
   fChain->SetBranchAddress("IsoTrack_L", &IsoTrack_L, &b_IsoTrack_L);
   fChain->SetBranchAddress("IsoTrack_T", &IsoTrack_T, &b_IsoTrack_T);
   fChain->SetBranchAddress("IsoTracker_L", &IsoTracker_L, &b_IsoTracker_L);
   fChain->SetBranchAddress("IsoTracker_T", &IsoTracker_T, &b_IsoTracker_T);
   fChain->SetBranchAddress("IsoPF_L", &IsoPF_L, &b_IsoPF_L);
   fChain->SetBranchAddress("IsoPF_T", &IsoPF_T, &b_IsoPF_T);
   fChain->SetBranchAddress("Ele1_pt", &Ele1_pt, &b_Ele1_pt);
   fChain->SetBranchAddress("Ele1_eta", &Ele1_eta, &b_Ele1_eta);
   fChain->SetBranchAddress("Ele1_phi", &Ele1_phi, &b_Ele1_phi);
   fChain->SetBranchAddress("Ele1_energy", &Ele1_energy, &b_Ele1_energy);
   fChain->SetBranchAddress("Ele1_p", &Ele1_p, &b_Ele1_p);
   fChain->SetBranchAddress("Ele1_px", &Ele1_px, &b_Ele1_px);
   fChain->SetBranchAddress("Ele1_py", &Ele1_py, &b_Ele1_py);
   fChain->SetBranchAddress("Ele1_pz", &Ele1_pz, &b_Ele1_pz);
   fChain->SetBranchAddress("Ele2_pt", &Ele2_pt, &b_Ele2_pt);
   fChain->SetBranchAddress("Ele2_eta", &Ele2_eta, &b_Ele2_eta);
   fChain->SetBranchAddress("Ele2_phi", &Ele2_phi, &b_Ele2_phi);
   fChain->SetBranchAddress("Ele2_energy", &Ele2_energy, &b_Ele2_energy);
   fChain->SetBranchAddress("Ele2_p", &Ele2_p, &b_Ele2_p);
   fChain->SetBranchAddress("Ele2_px", &Ele2_px, &b_Ele2_px);
   fChain->SetBranchAddress("Ele2_py", &Ele2_py, &b_Ele2_py);
   fChain->SetBranchAddress("Ele2_pz", &Ele2_pz, &b_Ele2_pz);
   fChain->SetBranchAddress("Muon1_pt", &Muon1_pt, &b_Muon1_pt);
   fChain->SetBranchAddress("Muon1_eta", &Muon1_eta, &b_Muon1_eta);
   fChain->SetBranchAddress("Muon1_phi", &Muon1_phi, &b_Muon1_phi);
   fChain->SetBranchAddress("Muon1_energy", &Muon1_energy, &b_Muon1_energy);
   fChain->SetBranchAddress("Muon1_p", &Muon1_p, &b_Muon1_p);
   fChain->SetBranchAddress("Muon1_px", &Muon1_px, &b_Muon1_px);
   fChain->SetBranchAddress("Muon1_py", &Muon1_py, &b_Muon1_py);
   fChain->SetBranchAddress("Muon1_pz", &Muon1_pz, &b_Muon1_pz);
   fChain->SetBranchAddress("Muon2_pt", &Muon2_pt, &b_Muon2_pt);
   fChain->SetBranchAddress("Muon2_eta", &Muon2_eta, &b_Muon2_eta);
   fChain->SetBranchAddress("Muon2_phi", &Muon2_phi, &b_Muon2_phi);
   fChain->SetBranchAddress("Muon2_energy", &Muon2_energy, &b_Muon2_energy);
   fChain->SetBranchAddress("Muon2_p", &Muon2_p, &b_Muon2_p);
   fChain->SetBranchAddress("Muon2_px", &Muon2_px, &b_Muon2_px);
   fChain->SetBranchAddress("Muon2_py", &Muon2_py, &b_Muon2_py);
   fChain->SetBranchAddress("Muon2_pz", &Muon2_pz, &b_Muon2_pz);
   fChain->SetBranchAddress("BoostedJet1_pt", &BoostedJet1_pt, &b_BoostedJet1_pt);
   fChain->SetBranchAddress("BoostedJet1_eta", &BoostedJet1_eta, &b_BoostedJet1_eta);
   fChain->SetBranchAddress("BoostedJet1_phi", &BoostedJet1_phi, &b_BoostedJet1_phi);
   fChain->SetBranchAddress("BoostedJet1_energy", &BoostedJet1_energy, &b_BoostedJet1_energy);
   fChain->SetBranchAddress("BoostedJet1_nJets", &BoostedJet1_nJets, &b_BoostedJet1_nJets);
   fChain->SetBranchAddress("BoostedJet2_pt", &BoostedJet2_pt, &b_BoostedJet2_pt);
   fChain->SetBranchAddress("BoostedJet2_eta", &BoostedJet2_eta, &b_BoostedJet2_eta);
   fChain->SetBranchAddress("BoostedJet2_phi", &BoostedJet2_phi, &b_BoostedJet2_phi);
   fChain->SetBranchAddress("BoostedJet2_energy", &BoostedJet2_energy, &b_BoostedJet2_energy);
   fChain->SetBranchAddress("BoostedJet2_nJets", &BoostedJet2_nJets, &b_BoostedJet2_nJets);
   fChain->SetBranchAddress("M_ele1ele2Bjet1", &M_ele1ele2Bjet1, &b_M_ele1ele2Bjet1);
   fChain->SetBranchAddress("M_ele1ele2", &M_ele1ele2, &b_M_ele1ele2);
   fChain->SetBranchAddress("M_elemu", &M_elemu, &b_M_elemu);
   fChain->SetBranchAddress("M_elemuBjet1", &M_elemuBjet1, &b_M_elemuBjet1);
   fChain->SetBranchAddress("M_mu1mu2", &M_mu1mu2, &b_M_mu1mu2);
   fChain->SetBranchAddress("M_mu1mu2Bjet1", &M_mu1mu2Bjet1, &b_M_mu1mu2Bjet1);
   fChain->SetBranchAddress("S_T_BJ", &S_T_BJ, &b_S_T_BJ);
   fChain->SetBranchAddress("S_T_jj", &S_T_jj, &b_S_T_jj);
   fChain->SetBranchAddress("M_leplep", &M_leplep, &b_M_leplep);
   fChain->SetBranchAddress("M_leplepBjet", &M_leplepBjet, &b_M_leplepBjet);
   fChain->SetBranchAddress("M_lep2Bjet", &M_lep2Bjet, &b_M_lep2Bjet);
   fChain->SetBranchAddress("M_leplepBjetBjet", &M_leplepBjetBjet, &b_M_leplepBjetBjet);
   fChain->SetBranchAddress("elesf_ele1", &elesf_ele1, &b_elesf_ele1);
   fChain->SetBranchAddress("elesf_ele2", &elesf_ele2, &b_elesf_ele2);
   fChain->SetBranchAddress("elesf_ele1_d", &elesf_ele1_d, &b_elesf_ele1_d);
   fChain->SetBranchAddress("elesf_ele2_d", &elesf_ele2_d, &b_elesf_ele2_d);
   fChain->SetBranchAddress("elesf_ele1_u", &elesf_ele1_u, &b_elesf_ele1_u);
   fChain->SetBranchAddress("elesf_ele2_u", &elesf_ele2_u, &b_elesf_ele2_u);
   fChain->SetBranchAddress("musf_trigger_mu1", &musf_trigger_mu1, &b_musf_trigger_mu1);
   fChain->SetBranchAddress("musf_ID_mu1", &musf_ID_mu1, &b_musf_ID_mu1);
   fChain->SetBranchAddress("musf_iso_mu1", &musf_iso_mu1, &b_musf_iso_mu1);
   fChain->SetBranchAddress("musf_reco_mu1", &musf_reco_mu1, &b_musf_reco_mu1);
   fChain->SetBranchAddress("musf_tot_mu1", &musf_tot_mu1, &b_musf_tot_mu1);
   fChain->SetBranchAddress("musf_trigger_mu2", &musf_trigger_mu2, &b_musf_trigger_mu2);
   fChain->SetBranchAddress("musf_ID_mu2", &musf_ID_mu2, &b_musf_ID_mu2);
   fChain->SetBranchAddress("musf_iso_mu2", &musf_iso_mu2, &b_musf_iso_mu2);
   fChain->SetBranchAddress("musf_reco_mu2", &musf_reco_mu2, &b_musf_reco_mu2);
   fChain->SetBranchAddress("musf_tot_mu2", &musf_tot_mu2, &b_musf_tot_mu2);
   fChain->SetBranchAddress("musf_trigger_mu1_u", &musf_trigger_mu1_u, &b_musf_trigger_mu1_u);
   fChain->SetBranchAddress("musf_ID_mu1_u", &musf_ID_mu1_u, &b_musf_ID_mu1_u);
   fChain->SetBranchAddress("musf_iso_mu1_u", &musf_iso_mu1_u, &b_musf_iso_mu1_u);
   fChain->SetBranchAddress("musf_reco_mu1_u", &musf_reco_mu1_u, &b_musf_reco_mu1_u);
   fChain->SetBranchAddress("musf_tot_mu1_u", &musf_tot_mu1_u, &b_musf_tot_mu1_u);
   fChain->SetBranchAddress("musf_trigger_mu2_u", &musf_trigger_mu2_u, &b_musf_trigger_mu2_u);
   fChain->SetBranchAddress("musf_ID_mu2_u", &musf_ID_mu2_u, &b_musf_ID_mu2_u);
   fChain->SetBranchAddress("musf_iso_mu2_u", &musf_iso_mu2_u, &b_musf_iso_mu2_u);
   fChain->SetBranchAddress("musf_reco_mu2_u", &musf_reco_mu2_u, &b_musf_reco_mu2_u);
   fChain->SetBranchAddress("musf_tot_mu2_u", &musf_tot_mu2_u, &b_musf_tot_mu2_u);
   fChain->SetBranchAddress("musf_trigger_mu1_d", &musf_trigger_mu1_d, &b_musf_trigger_mu1_d);
   fChain->SetBranchAddress("musf_ID_mu1_d", &musf_ID_mu1_d, &b_musf_ID_mu1_d);
   fChain->SetBranchAddress("musf_iso_mu1_d", &musf_iso_mu1_d, &b_musf_iso_mu1_d);
   fChain->SetBranchAddress("musf_reco_mu1_d", &musf_reco_mu1_d, &b_musf_reco_mu1_d);
   fChain->SetBranchAddress("musf_tot_mu1_d", &musf_tot_mu1_d, &b_musf_tot_mu1_d);
   fChain->SetBranchAddress("musf_trigger_mu2_d", &musf_trigger_mu2_d, &b_musf_trigger_mu2_d);
   fChain->SetBranchAddress("musf_ID_mu2_d", &musf_ID_mu2_d, &b_musf_ID_mu2_d);
   fChain->SetBranchAddress("musf_iso_mu2_d", &musf_iso_mu2_d, &b_musf_iso_mu2_d);
   fChain->SetBranchAddress("musf_reco_mu2_d", &musf_reco_mu2_d, &b_musf_reco_mu2_d);
   fChain->SetBranchAddress("musf_tot_mu2_d", &musf_tot_mu2_d, &b_musf_tot_mu2_d);
   fChain->SetBranchAddress("lepsf_evt", &lepsf_evt, &b_lepsf_evt);
   fChain->SetBranchAddress("lepsf_evt_u", &lepsf_evt_u, &b_lepsf_evt_u);
   fChain->SetBranchAddress("lepsf_evt_d", &lepsf_evt_d, &b_lepsf_evt_d);
   fChain->SetBranchAddress("eejj_l", &eejj_l, &b_eejj_l);
   fChain->SetBranchAddress("emujj_l", &emujj_l, &b_emujj_l);
   fChain->SetBranchAddress("mumujj_l", &mumujj_l, &b_mumujj_l);
   fChain->SetBranchAddress("muejj_l", &muejj_l, &b_muejj_l);
   fChain->SetBranchAddress("SRe", &SRe, &b_SRe);
   fChain->SetBranchAddress("TRe", &TRe, &b_TRe);
   fChain->SetBranchAddress("SRmu", &SRmu, &b_SRmu);
   fChain->SetBranchAddress("TRmu", &TRmu, &b_TRmu);
   fChain->SetBranchAddress("DYRe", &DYRe, &b_DYRe);
   fChain->SetBranchAddress("DYRmu", &DYRmu, &b_DYRmu);
   Notify();
}

Bool_t tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef tree_cxx
