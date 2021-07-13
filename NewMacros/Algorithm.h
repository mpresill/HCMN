#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "TString.h"
#include "TH1D.h"
#include "Data.h"

class Algorithm {
 public: 
  /**
  * @brief Construct a new Event Loop object
  */
  Algorithm();

  /**
  * @brief Initialize the algorithm
  * @param data - pointer to the data-access class instance
  */
  void initialize(Data* data);

  /**
  * @brief Execute. Here the stuff happens
  */
  void execute();

  /**
  * @brief Pointer to the histogram class instance defined as public attribute
  */
  TH1D* h_pt_e1 = 0; // must be initialized to 0

 protected:

  /**
  * @brief Instance of the data-access class
  */
  Data* m_data = 0;

};

#endif