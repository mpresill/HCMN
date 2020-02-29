/**
This Macro   
1. Draws the plot of the limit

Need to specify
1. See Declare Constants
2. You may have need to implement specific correction factors (e.g., k-factors or error on pdf), see xSecUp, xSecDown
*/
/////
//   To run: root -l Limit_plot_2D.cc+  
/////
/////
//   Prepare Root and Roofit
/////
#include "TText.h"
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
//#include "CMS_lumi.C"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iostream>
using namespace std;
/////
//   Declare constants
/////
const double Luminosity = 35900	; //pb^-1
//Plots
const bool eejj        = true;
const bool mumujj      = false;
const bool   save_plot = true;
const string name_plot = "eejj_2D_limit_stat_2016.pdf"; //xsecBR or r
const bool   plot_err  = false;
const bool comb        = false;
const bool thcorrected = false;
const bool   plot_r    = false; //r is the strenght; the alternative is to plot xsec times Br

//mumujj     UNCOMMENT THIS FOR mumuJJ CHANNEL HighMass SR with 2016 samples, compared with old SR
/*const int val = 9;
double LambdaObs[val] = {7, 7,  7, 9, 11, 13, 15, 17, 18 }; //2015 SR 
double Obs[val]       = {4.6, 4.6, 4.6, 4, 3.5, 3, 2.5, 2, 0.7}; //2015 SR
double LambdaExp[val] = {5.4,6,7.5,10,12,14,16,18,20};  //HIgh Mass SR
double Exp[val]       = {5.4,5.2,4.75,4,3.5,2.9,2.4,1.8,0.5}; //HIgh Mass SR
double LambdaErrm2s[val] = {4.76, 6,    7,    8,    9,    10,   11,   12};//4.60,5.12 
double Exp_m2s[val]      = {5.06, 4.66, 4.21, 3.81, 3.40, 3.11, 2.85, 2.05};//2.58};
double LambdaErrm1s[val] = {4.73, 6,    7,    8,    9,    10,   11,   12};//4.60,4.86 
double Exp_m1s[val]      = {4.73, 4.26, 3.81, 3.39, 3.02, 2.72, 2.44, 2.05};
double LambdaErrp1s[val] = {4.60, 6,    7,    8,    9,    10,   11,   11}; 
double Exp_p1s[val]      = {4.27, 3.33, 2.89, 2.49, 2.09, 1.73, 0.35, 0.35};
double LambdaErrp2s[val] = {4.60, 6,    7,    8,    9,    10,   11,   11}; 
double Exp_p2s[val]      = {4.08, 2.99, 2.50, 2.01, 1.67, 0.25, 0.35, 0.35};
*/

//eejj
    //UNCOMMENT THIS FOR eeJJ CHANNEL

const int val = 9;
double LambdaObs[val] = {7, 7,  7, 9, 11, 13, 15, 17, 17 }; //2015 SR 
double Obs[val]       = {4.6, 4.6, 4.6, 3.8, 3.2, 2.5, 2, 0.7, 0.7}; //2015 SR
double LambdaExp[val] = {5.4,6,7,9,11,13,15,17,20};  //HIgh Mass SR
double Exp[val]       = {5.4,5.2,4.75,4,3.4,2.8,2.4,1.7,0.5}; //HIgh Mass SR
double LambdaErrp2s[val] = {4.70, 6,    7,    8,    9,    9,   10}; 
double Exp_p2s[val]   = {4.21, 3.06, 2.51, 1.79, 0.34, 0.34, 0.40};//L'ultimo punto sarebbe 9,0.34 ma per fare tornare il plot si usa 10,0.40
double LambdaErrp1s[val] = {4.70, 6,    7,    8,    9,    10,   10}; 
double Exp_p1s[val]   = {4.41, 3.46, 2.94, 2.48, 1.94, 0.40, 0.40};
double LambdaErrm1s[val] = {4.9, 6,    7,    8,    9,    10,   11}; //Il primo punto di m2s sarebbe 4.7,5.31 ma per fare tornare 
double Exp_m1s[val]   = {4.95, 4.53, 4.04, 3.61, 3.13, 2.75, 2.39};  //il plot si usa 5.17,5.31
double LambdaErrm2s[val] = {5.17, 6,    7,    8,    9,    10,   11}; 
double Exp_m2s[val]   = {5.31, 4.95, 4.50, 4.08, 3.61, 3.29, 2.39};//L'ultimo punto sarebbe 2.93 ma per far tornare il plot si usa 2.39 come in m1s


/////
//   Declare functions 
/////
void plot_line();
TGraph* plot_band_2s();
TGraph* plot_band_1s();
TLegend* get_legend();
TPad* get_tpad(string name, double p1, double p2, double p3, double p4, double tm, double bm, double rm, double lm);
void setTDRStyle();
/////
//   Main function
/////
void Limit_plot_2D(){
 setTDRStyle();
 //Get legend and canvas
 TLegend* leg = get_legend();
 TCanvas* c1  = new TCanvas("mass","mass",200,200,800,600); 
 //c1->SetLogy();
 //Bottom part
 //TPad* c1_1 = get_tpad("c1_1",0.01,0.01,0.99,0.925,0.02,0.125,0.01,0.125);
 //c1_1->Draw(); c1_1->cd(); //c1_1->SetLogy();
 //Limit 
 if(plot_err){
  TGraph* band_2s = plot_band_2s();
  TGraph* band_1s = plot_band_1s();
  leg->AddEntry(band_1s,"68% expected","fl");
  leg->AddEntry(band_2s,"95% expected","fl");
 }
 TGraph* expLim = new TGraph(val,Exp,LambdaExp);
 expLim->SetTitle(0);
 expLim->SetLineWidth(2); expLim->SetLineStyle(2); expLim->SetLineColor(kBlack);//expLim->SetLineColor(9);
 expLim->SetMinimum(0);
 expLim->SetMaximum(20);//LambdaExp[val-1]+0.25*LambdaExp[val-1]); 
 if(plot_err) expLim->Draw("L"); 
 else     expLim->Draw("AL2");
 if(eejj)   expLim->GetXaxis()->SetTitle("#scale[1.2]{#font[12]{m}_{N_{e}}} (TeV)");
 if(mumujj) expLim->GetXaxis()->SetTitle("#scale[1.2]{#font[12]{m}_{N_{#mu}}} (TeV)");
 expLim->GetYaxis()->SetTitle("#Lambda (TeV)"); 
 expLim->GetYaxis()->SetRangeUser(0,22);
 expLim->GetXaxis()->SetRangeUser(0,6);
 ///obs limits
 TGraph* obsLim = new TGraph(val,Obs,LambdaObs);
 obsLim->SetLineWidth(2); obsLim->SetLineStyle(2); obsLim->SetLineColor(kBlue);  //obsLim->SetLineColor(9);
 obsLim->SetMarkerStyle(21);
 obsLim->Draw("L");
 obsLim->GetYaxis()->SetRangeUser(0,40);
 obsLim->GetXaxis()->SetRangeUser(0,8);
 
 
 gPad->RedrawAxis();
  ////
    TLatex latexLabel;
	latexLabel.SetTextSize(0.039);
	latexLabel.SetNDC();
	latexLabel.DrawLatex(0.13, 0.95,"CMS Run 2 #it{#bf{Preliminary}}");
	TLatex latexLabel2;
	latexLabel2.SetTextSize(0.039);
	latexLabel2.SetNDC();
	latexLabel2.DrawLatex(0.75, 0.95, "35.9 fb^{-1} (13 TeV)"); 
 //TGraph* sres = new TGraph(sval,xs,ys);
  //sres->SetLineWidth(2); sres->SetLineColor(2);
 //Legend
// leg->AddEntry(obsLim,"Expected 2015 SR","L");
 
 if(!plot_err) leg->AddEntry(expLim,"Expected","L");
// if(eejj) leg->AddEntry(sres,"e^{*} Observed->2015 SR","L");
 //if(mumujj) leg->AddEntry(sres,"#mu^{*} Observed-> 2015 SR","L");
 leg->Draw();
 plot_line();
 TPaveText *pt3 = new TPaveText(.1,.31,.3,.41,"NDC");
 TPaveText *pt3b = new TPaveText(.1,.17,.3,.27,"NDC");
 TPaveText *pt3c = new TPaveText(.1,.12,.3,.22,"NDC");

 TPaveText *pt2 = new TPaveText(.7,.16,.9,.24,"NDC");
 pt3->AddText("#scale[0.30]{100%}");
 pt3b->AddText("#scale[0.30]{95%}");
 pt3c->AddText("#scale[0.30]{50%}"); 
 if(eejj)   pt2->AddText("#scale[0.90]{#Lambda < #font[12]{m}_{N_{e}}}");
 if(mumujj) pt2->AddText("#scale[0.90]{#Lambda < #font[12]{m}_{N_{#mu}}}");
 pt2->SetShadowColor(0); pt2->SetBorderSize(0); pt2->SetFillColor(16); pt2->SetFillStyle(3001);
 pt3->SetShadowColor(0); pt3->SetBorderSize(0); pt3->SetFillColor(0); pt3->SetFillStyle(0);
 pt3b->SetShadowColor(0); pt3b->SetBorderSize(0); pt3b->SetFillColor(0); pt3b->SetFillStyle(0);
 pt3c->SetShadowColor(0); pt3c->SetBorderSize(0); pt3c->SetFillColor(0); pt3c->SetFillStyle(0);
 pt2->Draw("");
 pt3->Draw("");
 pt3b->Draw("");
 pt3c->Draw("");
 gPad->RedrawAxis();
 //CMS_lumi( c1, 0, 11 );
 //Top plots
 //c1->cd();
 //TPad* c1_2 = get_tpad("c1_2",0.01,0.925,0.99,0.99,0.01,0.15,0.01,0.125);
 //c1_2->Draw(); c1_2->cd();
 //TPaveText *pt1 = new TPaveText(.3,.1,.8,.99,"NDC");
 //pt1->AddText("#scale[0.90]{CMS preliminary,   #sqrt{s} = 13 TeV, L = 2.32 fb^{-1}}");
 //pt1->SetShadowColor(0); pt1->SetBorderSize(0); pt1->SetFillColor(0);
 //pt1->Draw("");
 //Save plot
 if(save_plot) c1->SaveAs(name_plot.c_str()); 
}
void plot_line(){
 const int xyp = 16;
 double xyval[xyp] = {0.5,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
//unitarity 
const int unit_points = 13;
double Unitary_mass[unit_points] = {0.1,0.5,1,2,3,4,5,6,7,8,9,10,11}; // {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,2,3,4,5,6,7,8,9,10,11,11,0.1,0.1};
double Unitary_violation_50[unit_points] = {0.53256,0.83457,1.13612,1.60476,2.07038,2.49458,2.73050,2.81477,2.81775,2.76824,2.67826,2.51949,2.23561}; //{0.12595,0.31758,0.53659,0.78264,1.04515,1.32282,1.61596,1.92098,2.23488,2.55606,6.21932,10.43748,14.99286,19.89706,25.14043,30.61665,36.30667,42.18770,48.23688,54.46248,11,0.1,0.12595};
double Unitary_violation_95[unit_points] = {1.83558,2.07402,2.43453,3.17282,3.73856,4.03673,4.16016,4.19540,4.15588,4.05151,3.88583,3.61739,3.14583};
double Unitary_violation_100[unit_points] = {5.85902,5.93254,6.03131,6.26083,6.38297,6.44087,6.30823,6.18094,5.99812,5.66145,5.31500,4.78422,4.08481};
TGraph* line1 = new TGraph(13, Unitary_mass, Unitary_violation_50);  //unitarity violation
TGraph* line2 = new TGraph(13, Unitary_mass, Unitary_violation_95);  //unitarity violation
TGraph* line3 = new TGraph(13, Unitary_mass, Unitary_violation_100);  //unitarity violation
TGraph* line = new TGraph(2*xyp+1); //L<M bound
line1 ->SetLineColor(kMagenta+2);
line1 ->Draw("l");
line2 ->SetLineColor(kMagenta+2);
line2 ->Draw("l");
line3 ->SetLineColor(kMagenta+2);
line3 ->Draw("l");
for(int i=0;i<xyp;i++){
  line->SetPoint(i,xyval[i],xyval[i]);
  line->SetPoint(i+val,xyval[i],0);
 }
 line->SetFillStyle(3001);
 line->SetFillColor(16);
 line->Draw("f");
}

/////
//   Draw limit parts
/////
TGraph* plot_band_2s(){
 TGraph* band_2s = new TGraph(2*val+1);
 for(int i=0;i<val;i++){
  band_2s->SetPoint(i,Exp_p2s[i],LambdaErrp2s[i]);
  band_2s->SetPoint(i+val,Exp_m2s[val-1-i],LambdaErrm2s[val-1-i]);
 }
 band_2s->SetPoint(2*val,Exp_p2s[0],LambdaErrp2s[0]);
 band_2s->SetLineStyle(2);
 band_2s->SetFillColor(kOrange);
 band_2s->Draw("ALF2");
 band_2s->SetMinimum(0);
 band_2s->SetMaximum(20);
 band_2s->SetTitle(0);
 if(eejj)   band_2s->GetXaxis()->SetTitle("#scale[1.2]{#font[12]{m}_{N_{e}}} (TeV)");
 if(mumujj) band_2s->GetXaxis()->SetTitle("#scale[1.2]{#font[12]{m}_{N_{#mu}}} (TeV)");
            band_2s->GetYaxis()->SetTitle("#Lambda (TeV)");
 band_2s->Draw("LF2");
 return band_2s;
}
TGraph* plot_band_1s(){
 TGraph* band_1s = new TGraph(2*val+1);
 for(int i=0;i<val;i++){
  band_1s->SetPoint(i,Exp_p1s[i],LambdaErrp1s[i]);
  band_1s->SetPoint(i+val,Exp_m1s[val-1-i],LambdaErrm1s[val-1-i]);
 }
 band_1s->SetPoint(2*val,Exp_p1s[0],LambdaErrp1s[0]);
 band_1s->SetLineStyle(2);
 band_1s->SetFillColor(kGreen+1);
 band_1s->Draw("LF2");
 return band_1s;
}
/////
//   Get legend and histos
/////
TLegend* get_legend(){
 TLegend *leg = new TLegend(0.55, 0.7, 0.65, 0.95);
 leg->SetShadowColor(0);
 leg->SetBorderSize(0);
 leg->SetTextSize(0.04);
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
 tdrStyle->SetPadTopMargin(0.065);
 tdrStyle->SetPadBottomMargin(0.125);
 tdrStyle->SetPadLeftMargin(0.125);
 tdrStyle->SetPadRightMargin(0.05);
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
 tdrStyle->SetTitleOffset(0.7, "Y"); // Another way to set the Offset
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
