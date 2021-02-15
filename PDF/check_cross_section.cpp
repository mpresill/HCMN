#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iostream>
#include "LHAPDF/LHAPDF.h"
#include <iterator>
#include <math.h>
#include <cmath>
#include <fstream>

using namespace std;
using namespace LHAPDF;

/*per compilare il file:
g++ sigma_contact_unitairty.cpp -o contact -I/usr/local/include -L/usr/local/lib -lLHAPDF
./contact
*/

int main(void)
{
	double tau, x, x1, dL, dLCKM;
	double tausup, tauinf, xsup, xinf;
	int i, k, j;
	double Q2;
	double s=169000000;             //GeV	--> s^1/2=13 TeV=13000 GeV 
	
	double lambda = 10000;		// (GeV)    
	double M;                            // (GeV)
	double stau;							// tau*s=\hat{s}
	double sigpC;						// partonic cross section
	
	double u1, u2, dbar1, dbar2, c1, c2, sbar1, sbar2, bbar1, bbar2; //parton distrib for valance quarks
	//double f1[13], f2[13];
	double xsec, Xsec;
	
	double sigma[27], massa[27];
	double N=100000;      																	  //numero di iterazioni della simulazione MC
	double pi=3.14159265358979;
	const LHAPDF::PDF* pdf = LHAPDF::mkPDF("NNPDF30_lo_as_0130", 0);
	
	std::vector<double> f1; f1.resize(11);
	std::vector<double> f2; f2.resize(11);


for(k=0;k<10;k++)		//ciclo sui diversi valori di mstar per cui calcola la sezione d'urto
{
	M=1000+1000*k;			//loop su diversi valori della massa partendo da quello definito precedentemente
	Q2=M*M;		//factorization scale setting
	massa[k]=M;

	Xsec=0;
	tauinf=M*M/s;
	tausup=1;
	srand(time(0));
	cout<<"CALCOLO PER lc ="<<lambda<<"[GeV], "<<"M ="<<M<<"[GeV]"<<"\n";                     
	for(i=0;i<N;i++)		//ciclo per integrale in x
	{	
		tau=tauinf+(rand()/(double(RAND_MAX)+1))*(tausup-tauinf);
		xinf=tau;
		xsup=1;
		x=xinf+(rand()/(double(RAND_MAX)+1))*(xsup-xinf);
		stau=s*tau;

/*definizione pdf*/
		pdf->xfxQ2(x,Q2,f1);


//		u1=f1[8]/x;
//		dbar1=f1[5]/x;
//		c1=f1[10]/x;
//		sbar1=f1[3]/x;
//		bbar1=f1[1]/x;
		u1=f1[6]/x;
		dbar1=f1[4]/x;
		c1=f1[8]/x;
		sbar1=f1[2]/x;
		bbar1=f1[0]/x;
		
		x1=tau/x;

		pdf->xfxQ2(x1,Q2,f2);


/*//at the beginning:
LHAPDF::initPDFSet(1, "ct10nnlo.LHgrid");

//then, in the event loop:
// get x1, x2, id1, id2, q from pdfInfo
LHAPDF::usePDFMember(1,0);
double xpdf1 = LHAPDF::xfx(1, x1, q, id1);
double xpdf2 = LHAPDF::xfx(1, x2, q, id2);
double w0 = xpdf1 * xpdf2;
for(int i=1; i <=50; ++i){
   LHAPDF::usePDFMember(1,i);
   double xpdf1_new = LHAPDF::xfx(1, x1, q, id1);
   double xpdf2_new = LHAPDF::xfx(1, x2, q, id2);
   double weight = xpdf1_new * xpdf2_new / w0;
   pdf_weights.push_back(weight);
}*/

//		u2=f2[8]/x1;
//		dbar2=f2[5]/x1;
//		c2=f2[10]/x1;
//		sbar2=f2[3]/x1;
//		bbar2=f2[1]/x1;
		u2=f2[6]/x1;
		dbar2=f2[4]/x1;
		c2=f2[8]/x1;
		sbar2=f2[2]/x1;
		bbar2=f2[0]/x1;

		dL=(u1*dbar2+u2*dbar1)+(u1*sbar2+u2*sbar1)+(u1*bbar2+u2*bbar1)+(c1*dbar2+c2*dbar1)+(c1*sbar2+c2*sbar1)+(c1*bbar2+c2*bbar1);

/*contact cross section for the heavy neutrino*/
	//	sigpC=(pi/(12*pow(lambda,4)))*stau*(1-M*M/stau)*(1-M*M/stau)*(1+M*M/stau)*(4*stau+2*M*M)/(3*stau+3*M*M);	//sezione d'urto di contatto, eq.2a note di Orlando	
	    sigpC=(pi/(9*pow(lambda,4)))*stau*(1-M*M/stau)*(1-M*M/stau)*(1+M*M/(2*stau));	//sezione d'urto di contatto, eq.2b note di Orlando	
	//	sigpC=1/stau;
			
/*infinitesimal MC integral with PDFs*/
		xsec=0.3894*1e+12*sigpC*dL*(1/x)*(tausup-tauinf)*(xsup-xinf);	//conversione [GeV^-2]->[fb] inclusa
		Xsec=Xsec+xsec;
	}//chiusura for i
	sigma[k]=Xsec/(N-1);

	//LHAPDF::PDF* p = LHAPDF::mkPDF("NNPDF30_lo_as_0130"); cout << p->xfxQ(21, 1e-4, 100.);
//delete p;
}	

//scrittura file cross sections
ofstream out("L10_xs_semianalitica.dat");
cout<<"Scrittura dei dati sul file"<<"\n";
for(j=0;j<k;j++)
{
//	out<<"CoM en = " << s/1000000 <<" (TeV)^2"<<"\n";
//	out<<"Lambda (GeV)= "<<lambda<<"\n";
	out<<massa[j]<<" "<<sigma[j	]<<"\n";
}
out.close();
cout<<"FINE"<<"\n";

return 0;
}
