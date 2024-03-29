#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <vector>
#include <TString.h>
#include <TChain.h>
#include "Data.h"
#include "Algorithm.h"

class EventLoop {
 public: 
 /**
 * @brief Construct a new Event Loop object
 */
 EventLoop();

 /**
 * @brief Initialize the event loop
 */
 void initialize();

 /**
 * @brief Execute the event loop
 */
 void execute();

 /**
 * @brief list of input ROOT file names
 */
 std::vector<TString> inputFiles;

 /**
 * @brief Name of the TTree instance. Must be same in all files
 */
 TString treeName;

  /**
  * @brief List of algorithms to be executed in the event loop
  */
  std::vector<Algorithm*> algorithms;





 protected:

 /**
 * @brief Instance of the TChain class used to read the data 
 */
 TChain* m_chain = 0;

  /**
  * @brief Instance of the data-access class
  */
  Data* m_data = 0;

};

#endif