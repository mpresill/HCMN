#include "EventLoop.h"
#include <iostream>
#include <stdexcept>

EventLoop::EventLoop() {
 // nothing to do here
}

void EventLoop::initialize() {
 // create an instance of the TChain class
 m_chain = new TChain(treeName);

 // loop through the input files and add them to the chain
 for(auto inputFile : inputFiles) {
   m_chain->Add(inputFile);
   std::cout << "Added file: " << inputFile << std::endl;
 }

 // create an instance of the Data class. Here the variables
 // are linked with the tree using the SetBranchAddress method
 m_data = new Data(m_chain);

  // initialise the algorithms
 for(auto algorithm : algorithms) {
  algorithm->initialize(m_data);
 }
}

void EventLoop::execute() {
 // sanity check. m_chain must not be zero
 if(!m_chain) {
   throw std::runtime_error("Calling execute while the wvent loop was not initialized.");
 }

 // here we do the actual event loop
 for(int i=0; i<m_chain->GetEntries(); ++i) {
   // event number printout
   if(i%1000==0) {
     std::cout << "Event " << i << std::endl;
   }

   // read the data for i-th event
   m_chain->GetEntry(i);


  //  // now we can work with the variables. Let's for example print electron mass 
  // // but only for every 1000th event
  // if(i%1000==0) {
  //  std::cout << "pt electron = " << m_data->patElectron_pt->at(0) << std::endl;
  //}
  // execute all the algorithms attached to this event loop
  for(auto algorithm : algorithms) {
    algorithm->execute();
  }

 }

}

                