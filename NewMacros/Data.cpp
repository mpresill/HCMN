#include "Data.h"

 Data::Data(TTree* tree) : m_tree(tree) {
     m_tree->SetBranchAddress("patElectron_pt", &patElectron_pt);
     m_tree->SetBranchAddress("patElectron_eta", &patElectron_eta);
     m_tree->SetBranchAddress("patElectron_phi", &patElectron_phi);
     m_tree->SetBranchAddress("patElectron_ecalTrkEnergyPostCorr", &patElectron_ecalTrkEnergyPostCorr);
     m_tree->SetBranchAddress("patElectron_energy", &patElectron_energy);
     m_tree->SetBranchAddress("M_leplep", &M_leplep);
}