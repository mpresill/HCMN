#ifndef DATA_H
#define DATA_H

#include "TTree.h"
#include "TLorentzVector.h"
using namespace std;


class Data{
 public: 
  /**
  * @brief Construct a new Data object
  * 
  * @param tree - pointer to the TTree (or TChain) class
  */
  Data(TTree* tree);

  /**
  * @brief Tree variables declaration (SetBranchAddress in the cpp file)
  */
  std::vector<double>* patElectron_pt=0; //MUST SET POINTERS TO 0!
  std::vector<double>* patElectron_eta=0; //MUST SET POINTERS TO 0!
  std::vector<double>* patElectron_phi=0; //MUST SET POINTERS TO 0!
  std::vector<double>* patElectron_ecalTrkEnergyPostCorr=0;
  std::vector<double>* patElectron_energy=0;
  double M_leplep;

 protected:

  /**
  * @brief pointer to the TTree (or TChain) class
  */
  TTree* m_tree = 0;

};

#endif