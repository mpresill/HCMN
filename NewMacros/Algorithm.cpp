#include "Algorithm.h"

Algorithm::Algorithm() {
}

void Algorithm::initialize(Data* data) {
 m_data = data;
}

void Algorithm::execute() {
 // here we fill the histograms. We protect the code against the empty pointers.
 if(h_pt_e1) h_pt_e1->Fill( m_data->patElectron_pt->at(0) );
}
