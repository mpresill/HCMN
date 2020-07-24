/**
This Macro   
1. Draws the plot of the limit

Need to specify
1. See Declare Constants
2. You may have need to implement specific correction factors (e.g., k-factors or error on pdf), see xSecUp, xSecDown
*/
/////
//   To run: root -l Limit_plot.cc+  
/////
/////
//   Prepare Root and Roofit
/////
#include "TPaveText.h"
#include "TLine.h"
#include "TFile.h"
#include "TH1F.h"
#include "TGraphErrors.h"
#include "THStack.h"
#include "TLegend.h"
#include "TTree.h"
#include "TTreePlayer.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TEfficiency.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iostream>
using namespace std;
/////
//   Declare constants
/////
const double Luminosity = 41529; //pb^-1
//Plots
const bool eejj        = true;
const bool mumujj      = false;
const bool comb        = false;
const bool thcorrected = false;
const bool   plot_r    = false; //r is the strenght; the alternative is to plot xsec times Br
const bool   save_plot = true;
const string name_plot = "eejj_L13000_2016-24July20_fitCR.pdf"; //xsecBR or r
const int    val       = 5;

//limits from Combine
const double Mass[val]   = {0.5,1,2,5,8};
const double SigEvt[val] = {};  //number of signal events eejj
const double SigEvtMuon[val] = {};  //number of signal events mumujj
const double xsec[val]   = {0.005716,0.002819,0.0008207,0.00001425,0.00000009135}; //cross section of the sign  samples with which limits are derived in pb
double xsecCF[val]       = {1,1,1,1,1}; //0.13};

//theoretical cross section [pb]
const int points = 10;
double Mass_L6[points]   = {0.5, 1, 2, 3, 4, 5, 6, 6,6,6 }; 
double xsec_L6[points]   = {0.1475,0.1019,0.02403,0.00501,0.001215,0.000314,0.00007404,0.00007404,0.00007404,0.00007404};
double Mass_L7[points]   = {0.5, 1, 2, 3, 4, 5, 6, 7,7,7 }; 
double xsec_L7[points]   = {0.07556,0.04767,0.01298,0.002706,0.0006548,0.0001695,0.00003995,0.000007654};
double Mass_L9[points]   = {0.5, 1, 2, 4, 6, 9, 9, 9 , 9, 9}; 
double xsec_L9[points]   = {0.02607, 0.01457,0.004754,0.0002398,0.00001462,0.00000003598,0.00000003598,0.00000003598,0.00000003598,0.00000003598};
double Mass_L11[points]  = {0.5, 1, 2, 4, 7,7,7,7,7,7}; 
double xsec_L11[points]  = {0.01134,0.005867,0.001889,0.0001076,0.000001252,0.000001252,0.000001252,0.000001252,0.000001252,0.000001252};
double Mass_L13[points]  = {0.5, 1, 2, 5, 8,8,8,8,8,8}; 
double xsec_L13[points]  = {0.005716,0.002819,0.0008207,0.00001425,0.00000009135,0.00000009135,0.00000009135,0.00000009135,0.00000009135,0.00000009135};
double Mass_L15[points]  = {0.5, 1, 2, 6}; 
double xsec_L15[points]  = {0.003199,0.001524,0.000411,0.000001893};
double Mass_L17[points]  = {0.5, 1, 2,7,7,7,7,7,7,7};
double xsec_L17[points]  = {0.001931,0.0008972,0.0002277,0.0000002195,0.0000002195,0.0000002195,0.0000002195,0.0000002195,0.0000002195,0.0000002195};
double Mass_L18[points]  = {0.5, 1, 1.5,2,2.5};
double xsec_L18[points]  = {1.54E-03,6.65E-04,3.15E-04,1.58E-04,8.22E-05};
double Mass_L20[points]  = {0.5, 1, 2, 8 , 8, 8, 8, 8, 8, 8};
double xsec_L20[points]  = {0.001007,0.0004549,0.000108,0.00000001491,0.00000001491,0.00000001491,0.00000001491,0.00000001491,0.00000001491};
const int Mass_eq_L_points = 16;
const double Mass_eq_L[Mass_eq_L_points] = {0.5,1,1.5,2,2.5,3,3.5,4,4.5,5,5.5,6,6.5,7,7.5,8};
double xsec_LM[Mass_eq_L_points]         = {6.10E+03,1.52E+02,1.28E+01,1.77E+00,3.27E-01,7.37E-02,1.93E-02,5.69E-03,1.82E-03,6.08E-04,2.07E-04,6.99E-05,2.30E-05,7.27E-06,2.18E-06,6.10E-07};  

/////
//   eejj
/////
/////
//HCMN reload  private production 2016, selezione High Mass 
const double CumEff[val] ={};// {0.186861099,0.610700894,0.692791903,0.666242661};
double Obs[val]     = {};
double Exp_m2s[val] = {1.03E-03,	3.85E-04,	1.80E-04,	7.63E-05,	1.16E-05};
double Exp_m1s[val] = {1.39E-03,	5.22E-04,	2.52E-04,	1.09E-04,	2.00E-05};
double Exp[val]     = {1.96E-03,	7.52E-04,	3.72E-04,	1.67E-04,	3.70E-05};  	//r value from Combine
double Exp_p1s[val] = {2.82E-03,	1.09E-03,	5.60E-04,	2.64E-04,	6.79E-05};
double Exp_p2s[val] = {3.87E-03,	1.52E-03,	8.08E-04,	3.99E-04,	1.12E-04};


/////
//   Declare functions 
/////
void get_limitvals(double xSec[], double xSecUp[], double xSecDown[]);
TGraph* plot_band_2s();
TGraph* plot_band_1s();
TGraph* plot_errthVSparam(double xSecUp[], double xSecDown[]);
TGraph* plot_thVSparam(double xsec[], int err);
TLegend* get_legend();
TPad* get_tpad(string name, double p1, double p2, double p3, double p4, double tm, double bm, double rm, double lm);
void setTDRStyle();
/////
//   Main function
/////
void Limit_plot_eejj(){
 setTDRStyle();
 //Get limit values
 double xSec[val]; double xSecUp[val]; double xSecDown[val];
 get_limitvals(xSec,xSecUp,xSecDown);
 //Get legend and canvas
 TLegend* leg = get_legend();
 TCanvas* c1  = new TCanvas("mass","mass",200,200,800,600); 
 c1->SetLogy();
 //Bottom part
 TPad* c1_1 = get_tpad("c1_1",0.01,0.01,0.99,0.925,0.02,0.125,0.01,0.125);
 c1_1->Draw(); c1_1->cd(); c1_1->SetLogy();
 //Limit 
 TGraph* band_2s = plot_band_2s();
 TGraph* band_1s = plot_band_1s();
 TGraph* expLim = new TGraph(val,Mass,Exp);
 expLim->SetLineWidth(2); expLim->SetLineStyle(2);
 expLim->Draw("L");
 //TGraph* obsLim = new TGraph(val,Mass,Obs);
 //obsLim->SetMarkerStyle(21);
 //obsLim->Draw("LP");
 //i=0,1 err=no,yes
 TGraph* thVSparam_L6  = plot_thVSparam(xsec_L6,6);
 TGraph* thVSparam_L7 = plot_thVSparam(xsec_L7,7);
 TGraph* thVSparam_L9  = plot_thVSparam(xsec_L9,9);
 TGraph* thVSparam_L11 = plot_thVSparam(xsec_L11,11);
 TGraph* thVSparam_L13 = plot_thVSparam(xsec_L13,13);
 TGraph* thVSparam_L15 = plot_thVSparam(xsec_L15,15); 
 TGraph* thVSparam_L17 = plot_thVSparam(xsec_L17,17);
// TGraph* thVSparam_L18 = plot_thVSparam(xsec_L18,18);
 TGraph* thVSparam_L20 = plot_thVSparam(xsec_L20,20);
 TGraph* thVSparam_LM  = plot_thVSparam(xsec_LM,0);
 TGraph* thVSparamUp; 
 TGraph* thVSparamDown; 
 if(thcorrected){
  thVSparamUp   = plot_thVSparam(xSecUp,1);
  thVSparamDown = plot_thVSparam(xSecDown,1);
 }
 //TGraph* errthVSparam = plot_errthVSparam(xSecUp,xSecDown);
 gPad->RedrawAxis();
 //Legend
 //leg->AddEntry(obsLim,"Observed","LP");
 leg->AddEntry(band_1s,"Expected #pm 1#sigma","fl");
 leg->AddEntry(band_2s,"Expected #pm 2#sigma","fl");
 if(mumujj) leg->AddEntry(thVSparam_LM,"HCMN (#scale[0.75]{#Lambda = m_{N_{#mu}}})","l");
 if(eejj)  leg->AddEntry(thVSparam_LM,"HCMN (#scale[0.75]{#Lambda = m_{N_{e}}})","l");
 leg->AddEntry(thVSparam_L6,"HCMN (#scale[0.75]{#Lambda 6 TeV})","l"); 
 leg->AddEntry(thVSparam_L7,"HCMN (#scale[0.75]{#Lambda 7 TeV})","l"); 
 leg->AddEntry(thVSparam_L9,"HCMN (#scale[0.75]{#Lambda 9 TeV})","l");
 leg->AddEntry(thVSparam_L11,"HCMN (#scale[0.75]{#Lambda 11 TeV})","l");
 leg->AddEntry(thVSparam_L13,"HCMN (#scale[0.75]{#Lambda 13 TeV})","l");
 leg->AddEntry(thVSparam_L15,"HCMN (#scale[0.75]{#Lambda 15 TeV})","l"); 
 leg->AddEntry(thVSparam_L17,"HCMN (#scale[0.75]{#Lambda 17 TeV})","l");
// leg->AddEntry(thVSparam_L18,"HCMN (#scale[0.75]{#Lambda 18 TeV})","l");
 leg->AddEntry(thVSparam_L20,"HCMN (#scale[0.75]{#Lambda 20 TeV})","l");
 if(thcorrected) leg->AddEntry(thVSparamUp,"Theory error","l");
 leg->Draw();
 //Top plots
 c1->cd();
 TPad* c1_2 = get_tpad("c1_2",0.01,0.925,0.99,0.99,0.01,0.15,0.01,0.125);
 c1_2->Draw(); c1_2->cd();
 TPaveText *pt1 = new TPaveText(.3,.1,.8,.99,"NDC");
// pt1->AddText("#Lambda = 12 TeV, MC signal #Lambda = 5 TeV");
 pt1->AddText("#scale[0.90]{CMS preliminary, #sqrt{s} = 13 TeV, L = 41.5 fb^{-1}}");
//pt1->AddText("CMS #scale[0.75]{#it{Preliminary}} 35.9 fb^{-1} (13 TeV)");
 pt1->SetShadowColor(0); pt1->SetBorderSize(0); pt1->SetFillColor(0);
 pt1->Draw("");
 //TPaveText *pt2 = new TPaveText(.225,.1,.325,.99,"NDC");
 //pt2->AddText("#it{Preliminary}"); // #scale[0.75]{#it{Preliminary}} 2.32 fb^{-1} (13 TeV)");
 //pt2->SetShadowColor(0); pt2->SetBorderSize(0); pt2->SetFillColor(0); pt2->SetTextFont(42);
 //pt2->Draw("");
 //Save plot
 if(save_plot) c1->SaveAs(name_plot.c_str()); 
}
/////
//   Get limit values
/////
void get_limitvals(double xSec[], double xSecUp[], double xSecDown[]){
 for(int i=0; i<val; i++){
  xSecUp[i]   = 0.;
  xSecDown[i] = 0.;
  if(!plot_r){
   Obs[i]      = (Obs[i]*SigEvt[i])/(Luminosity*CumEff[i]);
   Exp[i]      =   (Exp[i]);//*xsec[i]) ;    							//(Exp[i]*SigEvt[i])/(Luminosity*CumEff[i]);
   Exp_m2s[i]  =   Exp_m2s[i];//* xsec[i] ;                  //(Exp_m2s[i]*SigEvt[i])/(Luminosity*CumEff[i]);
   Exp_m1s[i]  = 	Exp_m1s[i];//*xsec[i]  ;					//(Exp_m1s[i]*SigEvt[i])/(Luminosity*CumEff[i]);
   Exp_p1s[i]  = 	Exp_p1s[i];//*xsec[i] ;					//(Exp_p1s[i]*SigEvt[i])/(Luminosity*CumEff[i]);
   Exp_p2s[i]  = 	Exp_p2s[i];//*xsec[i] ;					//(Exp_p2s[i]*SigEvt[i])/(Luminosity*CumEff[i]);
   xSec[i]     = xsec[i]; 
   xSecUp[i]   = xsec[i]*(1+xsecCF[i]);//*(1 + 0.065); //This may be model dependent
   xSecDown[i] = xsec[i]*(1-xsecCF[i]);//*(1 - 0.065);
   cout<<"The expected value for "<<i<<" is "<<Exp[i]<<endl;
  }else{
   xSecUp[i]   = 1;
   xSecDown[i] = 1;
  }
 } 
}  
/////
//   Draw limit parts
/////
TGraph* plot_band_2s(){
 TGraph* band_2s = new TGraph(2*val+1);
 for(int i=0;i<val;i++){
  band_2s->SetPoint(i,Mass[i],Exp_p2s[i]);
  band_2s->SetPoint(i+val,Mass[val-1-i],Exp_m2s[val-1-i]);
 }
 band_2s->SetPoint(2*val,Mass[0],Exp_p2s[0]);
 band_2s->SetLineStyle(2);
 band_2s->SetFillColor(kYellow);
 band_2s->Draw("ALF2");
// band_2s->SetMinimum(0.0001);
 //band_2s->SetMaximum(0.01);
 band_2s->SetMinimum(0.00001);
 band_2s->SetMaximum(1);
 band_2s->SetTitle(0);
 if(mumujj) band_2s->GetXaxis()->SetTitle("m_{N_{#mu}} (TeV)");
 if(eejj)   band_2s->GetXaxis()->SetTitle("m_{N_{e}} (TeV)");
 if(!plot_r && eejj)   band_2s->GetYaxis()->SetTitle("#sigma(pp #rightarrow eN_{e}) #times BR(N #rightarrow eq#bar{q'}) (pb)");
 if(!plot_r && mumujj) band_2s->GetYaxis()->SetTitle("#sigma(pp #rightarrow #muN_{#mu}) #times BR(N #rightarrow #muq#bar{q'}) (pb)");
 if(!plot_r && comb)   band_2s->GetYaxis()->SetTitle("#sigma(pp #rightarrow l N) #times BR(N #rightarrow l jj) (pb), l = e,#mu");
 if(plot_r)            band_2s->GetYaxis()->SetTitle("Strenght, r");
 band_2s->Draw("LF2");
 return band_2s;
}
TGraph* plot_band_1s(){
 TGraph* band_1s = new TGraph(2*val+1);
 for(int i=0;i<val;i++){
  band_1s->SetPoint(i,Mass[i],Exp_p1s[i]);
  band_1s->SetPoint(i+val,Mass[val-1-i],Exp_m1s[val-1-i]);
 }
 band_1s->SetPoint(2*val,Mass[0],Exp_p1s[0]);
 band_1s->SetLineStyle(2);
 band_1s->SetFillColor(kGreen);
 band_1s->Draw("LF2");
 return band_1s;
}
TGraph* plot_errthVSparam(double xSecUp[], double xSecDown[]){
 TGraph* errthVSparam = new TGraph(2*val+1);
 for(int i=0;i<val;i++){
  errthVSparam->SetPoint(i,Mass[i],xSecUp[i]);
  errthVSparam->SetPoint(i+val,Mass[val-1-i],xSecDown[val-1-i]);
 }
 errthVSparam->SetPoint(2*val,Mass[0],xSecUp[0]);
 errthVSparam->SetLineStyle(2);
 errthVSparam->SetFillColor(kBlue-10);
 errthVSparam->Draw("LF2");
 return errthVSparam;
}
TGraph* plot_thVSparam(double xSec[], int err){
 TGraph* thVSparam;
 if(err==6) thVSparam = new TGraph(points,Mass_L6,xSec);
  if(err==7) thVSparam = new TGraph(points,Mass_L7,xSec);
 if(err==9) thVSparam = new TGraph(points,Mass_L9,xSec);
 if(err==11) thVSparam = new TGraph(points,Mass_L11,xSec);
 if(err==13) thVSparam = new TGraph(points,Mass_L13,xSec);
 if(err==15) thVSparam = new TGraph(points,Mass_L15,xSec);
 if(err==17) thVSparam = new TGraph(points,Mass_L17,xSec);
// if(err==18) thVSparam = new TGraph(points,Mass_L18,xSec);
 if(err==20) thVSparam = new TGraph(points,Mass_L20,xSec);
 if(err==0)  thVSparam = new TGraph(Mass_eq_L_points,Mass_eq_L,xSec);
// thVSparam->SetMarkerStyle(10);
 thVSparam->SetLineWidth(2);
 if(err==0){
  thVSparam->SetLineColor(kBlue-4);
  thVSparam->SetLineWidth(2); 
 }
 if(err==6 ){
  thVSparam->SetLineColor(kRed+1);
  thVSparam->SetLineStyle(2);
 }
 if(err==9 ){
  thVSparam->SetLineColor(kRed+3);
  thVSparam->SetLineStyle(10);
 }
 if(err==11){
  thVSparam->SetLineColor(kOrange+3);
  thVSparam->SetLineStyle(3);
 }
 if(err==13){
  thVSparam->SetLineColor(kViolet-2);
  thVSparam->SetLineStyle(4);
 }
 if(err==15){
  thVSparam->SetLineColor(kGreen+3);
  thVSparam->SetLineStyle(5);
 }
 if(err==17){
  thVSparam->SetLineColor(kCyan+1);
  thVSparam->SetLineStyle(6);
 }
 if(err==7){
  thVSparam->SetLineColor(kCyan+2);
  thVSparam->SetLineStyle(7);
 }
 if(err==20){
  thVSparam->SetLineColor(kBlue+3);
  thVSparam->SetLineStyle(8);
 }
 thVSparam->Draw("L");
 return thVSparam;
}
/////
//   Get legend and histos
/////
TLegend* get_legend(){
 TLegend *leg = new TLegend(0.7, 0.55, 0.9, 0.95);
 leg->SetShadowColor(0);
 leg->SetBorderSize(0);
 leg->SetFillColor(0);
 return leg;
}
TPad* get_tpad(string name, double p1, double p2, double p3, double p4, double tm, double bm, double rm, double lm){
 TPad *pad = new TPad(name.c_str(),name.c_str(),p1,p2,p3,p4);
 pad->SetTopMargin(tm);
 pad->SetBottomMargin(bm);
 pad->SetRightMargin(rm);
 pad->SetLeftMargin(lm);
 return pad;
}
/////
//   Set setTDRStyle_modified (from link https://twiki.cern.ch/twiki/pub/CMS/TRK10001/setTDRStyle_modified.C)
/////
void setTDRStyle(){
 TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");
 //For the canvas:
 tdrStyle->SetCanvasBorderMode(0);
 tdrStyle->SetCanvasColor(kWhite);
 tdrStyle->SetCanvasDefH(600); //Height of canvas
 tdrStyle->SetCanvasDefW(600); //Width of canvas
 tdrStyle->SetCanvasDefX(0);   //POsition on screen
 tdrStyle->SetCanvasDefY(0);
 //For the Pad:
 tdrStyle->SetPadBorderMode(0);
 //tdrStyle->SetPadBorderSize(Width_t size = 1);
 tdrStyle->SetPadColor(kWhite);
 tdrStyle->SetPadGridX(false);
 tdrStyle->SetPadGridY(false);
 tdrStyle->SetGridColor(0);
 tdrStyle->SetGridStyle(3);
 tdrStyle->SetGridWidth(1);
 // For the frame:
 tdrStyle->SetFrameBorderMode(0);
 tdrStyle->SetFrameBorderSize(1);
 tdrStyle->SetFrameFillColor(0);
 tdrStyle->SetFrameFillStyle(0);
 tdrStyle->SetFrameLineColor(1);
 tdrStyle->SetFrameLineStyle(1);
 tdrStyle->SetFrameLineWidth(1);
 //For the histo:
 tdrStyle->SetHistFillColor(0);
 //tdrStyle->SetHistFillStyle(0);
 tdrStyle->SetHistLineColor(1);
 tdrStyle->SetHistLineStyle(0);
 tdrStyle->SetHistLineWidth(1);
 //tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
 //tdrStyle->SetNumberContours(Int_t number = 20);
 //tdrStyle->SetEndErrorSize(0);
 tdrStyle->SetErrorX(0.);
 //tdrStyle->SetErrorMarker(20);
 tdrStyle->SetMarkerStyle(20);
 //For the fit/function:
 tdrStyle->SetOptFit(1);
 tdrStyle->SetFitFormat("5.4g");
 //tdrStyle->SetFuncColor(1);
 tdrStyle->SetFuncStyle(1);
 tdrStyle->SetFuncWidth(1);
 //For the date:
 tdrStyle->SetOptDate(0);
 //tdrStyle->SetDateX(Float_t x = 0.01);
 //tdrStyle->SetDateY(Float_t y = 0.01);
 //For the statistics box:
 tdrStyle->SetOptFile(0);
 tdrStyle->SetOptStat("e"); // To display the mean and RMS:   SetOptStat("mr");
 //tdrStyle->SetStatColor(kWhite);
 tdrStyle->SetStatColor(kGray);
 tdrStyle->SetStatFont(42);
 tdrStyle->SetStatTextColor(1);
 tdrStyle->SetStatFormat("6.4g");
 tdrStyle->SetStatBorderSize(0);
 tdrStyle->SetStatX(1.); //Starting position on X axis
 tdrStyle->SetStatY(1.); //Starting position on Y axis
 tdrStyle->SetStatFontSize(0.025); //Vertical Size
 tdrStyle->SetStatW(0.15); //Horizontal size 
 //tdrStyle->SetStatStyle(Style_t style = 1001);
 //Margins:
 tdrStyle->SetPadTopMargin(0.05);
 tdrStyle->SetPadBottomMargin(0.125);
 tdrStyle->SetPadLeftMargin(0.105);
 tdrStyle->SetPadRightMargin(0.1);
 //For the Global title:
 //tdrStyle->SetOptTitle(0);
 tdrStyle->SetTitleFont(42);
 tdrStyle->SetTitleColor(1);
 tdrStyle->SetTitleTextColor(1);
 tdrStyle->SetTitleFillColor(10);
 tdrStyle->SetTitleFontSize(0.05);
 //tdrStyle->SetTitleH(0); // Set the height of the title box
 //tdrStyle->SetTitleW(0); // Set the width of the title box
 //tdrStyle->SetTitleX(0); // Set the position of the title box
 //tdrStyle->SetTitleY(0.985); // Set the position of the title box
 //tdrStyle->SetTitleStyle(Style_t style = 1001);
 //tdrStyle->SetTitleBorderSize(2);
 //For the axis titles:
 tdrStyle->SetTitleColor(1, "XYZ");
 tdrStyle->SetTitleFont(42, "XYZ");
 tdrStyle->SetTitleSize(0.06, "XYZ");
 //tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
 //tdrStyle->SetTitleYSize(Float_t size = 0.02);
 tdrStyle->SetTitleXOffset(0.9);
 tdrStyle->SetTitleYOffset(0.9);
 tdrStyle->SetTitleOffset(1.0, "Y"); // Another way to set the Offset
 //For the axis labels:
 tdrStyle->SetLabelColor(1, "XYZ");
 tdrStyle->SetLabelFont(42, "XYZ");
 tdrStyle->SetLabelOffset(0.007, "XYZ");
 tdrStyle->SetLabelSize(0.05, "XYZ");
 //For the axis:
 tdrStyle->SetAxisColor(1, "XYZ");
 tdrStyle->SetStripDecimals(kTRUE);
 tdrStyle->SetTickLength(0.03, "XYZ");
 tdrStyle->SetNdivisions(510, "XYZ");
 tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
 tdrStyle->SetPadTickY(1);
 //Change for log plots:
 tdrStyle->SetOptLogx(0);
 tdrStyle->SetOptLogy(0);
 tdrStyle->SetOptLogz(0);
 //Postscript options:
 //tdrStyle->SetPaperSize(15.,15.);
 //tdrStyle->SetLineScalePS(Float_t scale = 3);
 //tdrStyle->SetLineStyleString(Int_t i, const char* text);
 //tdrStyle->SetHeaderPS(const char* header);
 //tdrStyle->SetTitlePS(const char* pstitle);
 //tdrStyle->SetBarOffset(Float_t baroff = 0.5);
 //tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
 //tdrStyle->SetPaintTextFormat(const char* format = "g");
 //tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
 //tdrStyle->SetTimeOffset(double toffset);
 //tdrStyle->SetHistMinimumZero(kTRUE);
 tdrStyle->cd();
}
