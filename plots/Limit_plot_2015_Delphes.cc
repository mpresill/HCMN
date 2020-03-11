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
const double Luminosity = 35542; //pb^-1
//Plots
const bool eejj        = true;
const bool mumujj      = false;
const bool comb        = false;
const bool thcorrected = false;
const bool   plot_r    = false; //r is the strenght; the alternative is to plot xsec times Br
const bool   save_plot = true;
const string name_plot = "limit_2016_eejj_stat_only.pdf"; //xsecBR or r
const int    val         = 5;
const double SigEvt[val] = {216.2998, 117.1731, 23.7754, 5.42671, 1.39927};
const double CumEff[val] = {0.30354, 0.47612, 0.49458, 0.50239, 0.50738}; //Num evt in SR/Num evt in dataset (Or num evt read, to be more precise) 
//Comparison 2015 vs Delphes
//double MassObs[val] = {0.5,3,6,9,9}; 
//double Obs[val]     = {0.00803057,0.00194814,0.0016556,0.00165006,0.00165006}; //Delphes
//const double Mass[val]   = {0.5,1.5,2.5,3.5,4.5};
//double Exp[val]     = {0.00765466,0.00253744,0.00187269,0.00172465,0.00164054}; //2015
//Comparison with and without sys
double MassObs[val] = {0.5,1,2,4,7}; 
double Obs[val]     = {0.001122803,0.000432545,0.00020845,1.25857E-04,0.000128563};//{0.001034882,0.000369747,0.000178038,8.91036E-05,0.000082006}; //Exp High Mass SR
double Mass[val] = {0.5,1,2,4,7}; 
double Exp[val]     = {0.001122803,0.000432545,0.00020845,1.25857E-04,0.000128563}; //Exp Low Mass SR
double Mass2[val] = {0.5,1,2,4,5}; 
double Exp2[val]     = {0.001969154,0.000828116,0.000328482,0.000193346,0.000193346}; //Exp 2015 SR    
const double xsec[val]   = {0.02605,0.008731,0.002131,0.0004793,0.0001223};
double xsecCF[val]       = {0.13,0.13,0.13,0.13,0.13}; //0.13};

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
void Limit_plot_2015_Delphes(){
 setTDRStyle();
 TLegend* leg = get_legend();
 TCanvas* c1  = new TCanvas("mass","mass",200,200,800,600); 
 c1->SetLogy();
 //Bottom part
 TPad* c1_1 = get_tpad("c1_1",0.01,0.01,0.99,0.925,0.02,0.125,0.01,0.125);
 c1_1->Draw(); c1_1->cd(); c1_1->SetLogy();
 //Limit 
 TGraph* obsLim = new TGraph(val,MassObs,Obs);
 obsLim->SetTitle(0);
 obsLim->SetLineWidth(2);
 obsLim->SetLineColor(2);
 //obsLim->SetMarkerStyle(7);
 //obsLim->SetMarkerColor(2);
 obsLim->GetXaxis()->SetTitle("m_{N_{#mu}} (TeV)");
 obsLim->GetYaxis()->SetTitle("#sigma(pp #rightarrow #mu N_{#mu}) #times BR(N #rightarrow #mu q#bar{q'}) (pb)");
 //obsLim->SetMinimum(0.0001);
 obsLim->SetMaximum(0.01);
// obsLim->SetMinimum(0.000002);
 //obsLim->SetMaximum(0.0003);
 TGraph* expLim = new TGraph(val,Mass,Exp);
 expLim->SetLineWidth(2);
 expLim->SetLineColor(2);
//expLim->SetLineStyle(2);
 //expLim->SetMarkerStyle(7);
// expLim->SetMarkerColor(4);
 TGraph* expLim2 = new TGraph(val,Mass2,Exp2);
 expLim2->SetLineWidth(2); 
 expLim2->SetLineColor(3);
// expLim2->SetLineStyle(2);
// expLim2->SetMarkerStyle(7);
 //expLim2->SetMarkerColor(5);
 obsLim->Draw("ALF2");
 expLim->Draw("L");
 expLim2->Draw("L");

 //Legend
 //leg->AddEntry(obsLim,"Expected Delphes","LP");
 //leg->AddEntry(expLim,"Expected CMS 2015 data","l");
// leg->AddEntry(obsLim,"Expected High Mass SR", "L");
 leg->AddEntry(expLim,"Expected New Selection", "L");
  leg->AddEntry(expLim2,"Expected 2015 SR", "L");
 leg->Draw();
 //Top plots
 c1->cd();
 TPad* c1_2 = get_tpad("c1_2",0.01,0.925,0.99,0.99,0.01,0.15,0.01,0.125);
 c1_2->Draw(); c1_2->cd();
 //TPaveText *pt1 = new TPaveText(.3,.1,.8,.99,"NDC");
 //pt1->AddText("#Lambda = 9 TeV, MC signal #Lambda = 5 TeV");
 //pt1->AddText("#scale[0.90]{CMS preliminary,   #sqrt{s} = 13 TeV, L = 2.32 fb^{-1}}");
 //pt1->AddText("CMS"); // #scale[0.75]{#it{Preliminary}} 2.32 fb^{-1} (13 TeV)");
 //pt1->SetShadowColor(0); pt1->SetBorderSize(0); pt1->SetFillColor(0);
 //pt1->Draw("");
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
/////
//   Draw limit parts
/////
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
 TGraph* thVSparam = new TGraph(val,Mass,xSec);
 thVSparam->SetMarkerStyle(10);
 thVSparam->SetLineWidth(1);
 if(err==1) thVSparam->SetLineStyle(7);
 thVSparam->SetLineColor(kBlue-4);
 thVSparam->SetFillColor(kBlue-10); //Needed to show proper legend
 thVSparam->Draw("L");
 return thVSparam;
}
/////
//   Get legend and histos
/////
TLegend* get_legend(){
 TLegend *leg = new TLegend(0.4, 0.65, 0.8, 0.95);
 leg->SetShadowColor(0);
 leg->SetBorderSize(0);
 leg->SetFillColor(0);
 leg->SetTextSize(0.065);
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
