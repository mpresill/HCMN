/**
This Macro   
1. Plots variables with normalized histograms and their ratio 

Need to specify
1. See Declare Constants

Notes
1. The macro is tought to do it for 3 histograms and shows h2/h1 - h3/h1
   If you want to add more datasets you have to modify the macro
2. Currently implemented to work only with massVis and asymbin
*/
/////
//   To run: root -l Norm_plot_ratio_asym.cc+ 
/////
/////
//   Prepare Root and Roofit
/////
#include "TFile.h"
#include "TH1F.h"
#include "THStack.h"
#include "TLegend.h"
#include "TTree.h"
#include "TTreePlayer.h"
#include "TStyle.h"
#include "TGaxis.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TEfficiency.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iostream>
using namespace std;
/////
//   Declare constants
/////
//Path - channel - samples - selection
const string path       = "/afs/cern.ch/work/m/mpresill/HCMN/BkgEstimation/";
const char *samples[]   = {"TTtW_2016_TRe","TTtW_2016_SRe"}; //first sample TR, second SR
const string specsel    = "";
const string channel    = "";
const string selection  = "";
const double Luminosity = 35542; //pb^-1    //2018: 58873 //2017: 41529 //2016: 35542
const bool noLumiNorm   = false; //true means NO luminosity normalization done
const bool noPUcorr     = false; //true means NO PU corr done 
const bool noSFlepcorr  = false; //true means NO SFlep corr done
const bool normalization = false; //true means normalization to 1
const string objsf       = "lepsf_evt";
const string PUw         = "PUWeight";//"PileupWeight";
//Plots
const bool save_plots  = true;
const bool twosamples  = true; //false means 3 samples
//Variables
//const unsigned int int_var  = 2; //Till int_var, variables are int
//const char *variables[]   = {"TrkPtIsoEl", "HsuEEl"};
//const char *variables[]   = {"TrkPtIsoEl", "HsuEEl"};
//const char *titleXaxis[]  = {"TrkPtIsoEl", "H/E"};
//const int    numVar       = 2;
//const int    bin[numVar]  = {4, 5};
//const int    col_size          = 120; // = highest bin
//const double inRange[numVar]   = {0,0};
//const double endRange[numVar]  = {50, 0.2};

//Variables
const unsigned int int_var    = 0; //Till int_var, variables are int
const unsigned int ini_var    = 0;
const unsigned int double_var = 1; //From int_var to double_var, variables are double
//After double_var, variables are array  
const bool most_energetic = false; //true: plot all jet values; false: plot the most energetic jet values
const char *variables[]   = {"M_leplepBjet"};
const char *titleXaxis[]  = {"M(e, l' , J) [GeV]"}; 
//const char *titleXaxis[]  = {"M(#mu, l', J) [GeV]"};
//For Plots
const int    numVar            = 1;
const int    bin[numVar]       = {9};//330};
const int    col_size          = 500; // = highest bin
const double inRange[numVar]   = {0};
const double endRange[numVar]  = {10000};
//const double asymbins[9]      = {0,200,400,600,800,1000,1400,2000,3500};//,10000};
const double asymbins[10]      = {0,200,400,600,800,1000,1400,2000,3500,10000};
const int    logYscale[numVar] = {0};
//const int    logYscale[numVar] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
/////
//   Declare functions 
/////
TFile* Call_TFile(string rootpla);
void setTDRStyle();
/////
//   Main function
/////
void Norm_plot_ratio_asym(){
 setTDRStyle();
 //Loop over all variables
 vector<string> var(variables, variables + sizeof(variables)/sizeof(variables[0]));
 vector<string> varTitleXaxis(titleXaxis, titleXaxis + sizeof(titleXaxis)/sizeof(titleXaxis[0]));
 //for(uint v=0; v<var.size(); v++) 
 for(uint v=(uint) ini_var; v<(uint) double_var; v++){
  TCanvas* c1 = new TCanvas(var[v].c_str(),var[v].c_str(),400,400,1100,800);
  TLegend *leg = new TLegend(0.8, 0.4, 1.0, 0.93);
  leg->SetHeader("Samples");
  leg->SetBorderSize(0);
  TH1F *h1_var = new TH1F("h1_var","h1_var",bin[v],asymbins);//inRange[v],endRange[v]); h1_var->Sumw2();
  h1_var->Sumw2();
  h1_var->SetTitle(0);
  h1_var->SetMarkerStyle(20);
  h1_var->SetLineColor(1);
  h1_var->SetMarkerColor(1);
  //h1_var->GetXaxis()->SetTitle(varTitleXaxis[v].c_str());
  char bin_size_c[col_size]; float bin_size_f = ((endRange[v]-inRange[v])/bin[v]); sprintf(bin_size_c,"%.2f",bin_size_f);
  //string titleYaxis = "Events/"+(string) bin_size_c;
  string titleYaxis = "Events";
  h1_var->GetYaxis()->SetTitle(titleYaxis.c_str());
  TH1F *h2_var = new TH1F("h2_var","h2_var",bin[v],asymbins);//inRange[v],endRange[v]); h2_var->Sumw2();
  h2_var->Sumw2(); 
  h2_var->SetMarkerStyle(21);
  h2_var->SetLineColor(2);
  h2_var->SetMarkerColor(2);
  TH1F *h3_var = new TH1F("h3_var","h3_var",bin[v],asymbins);//inRange[v],endRange[v]); 
  h3_var->Sumw2();
  h3_var->SetMarkerStyle(22);
  h3_var->SetLineColor(3);
  h3_var->SetMarkerColor(3);
  //Loop over samples
  vector<string> rootplas(samples, samples + sizeof(samples)/sizeof(samples[0]));
  const uint rootplas_size = rootplas.size();
  for(uint i=0; i<rootplas_size; i++){
   //Call tree and variables 
   TFile* f = Call_TFile(rootplas[i]);
   TTree* tree; f->GetObject("BOOM",tree);
   //string objsf; 
   //if(rootplas[i]=="TT_mue" ) objsf="lepsf_evtmudown";
   //if(rootplas[i]=="TT_mumu") objsf="lepsf_evtmudown";
   double curr_var;
   TBranch *b_curr_var = 0;
   tree->SetBranchAddress(var[v].c_str(),&curr_var,&b_curr_var);
   double PU_weight;
   double PUWeight;
   //double PileupWeight;
   double sf_obj;
   double lumi_wgt;
  // TBranch *b_PU_weight = 0;
   //TBranch *b_PileupWeight = 0;
   TBranch *b_sf_obj = 0;
   TBranch *b_lumi_wgt = 0;
   TBranch *b_PUWeight = 0;
   tree->SetBranchAddress("PUWeight",&PUWeight,&b_PUWeight);  
   //tree->SetBranchAddress(PUw.c_str(),&PU_weight,&b_PU_weight);
   //tree->SetBranchAddress("PileupWeight",&PileupWeight,&b_PileupWeight);
   tree->SetBranchAddress(objsf.c_str(),&sf_obj,&b_sf_obj);
   tree->SetBranchAddress("lumi_wgt",&lumi_wgt,&b_lumi_wgt);
   double weight = 0.;
   for(int j=0; j<tree->GetEntries(); j++){
    //tree->GetEntry(j);
    Long64_t tentry = tree->LoadTree(j);
    b_curr_var->GetEntry(tentry);
    b_PUWeight->GetEntry(tentry);
    //b_PU_weight->GetEntry(tentry);
    //b_PileupWeight->GetEntry(tentry);
    b_sf_obj->GetEntry(tentry);
    b_lumi_wgt->GetEntry(tentry);
    //weight = wgt_lumi;
    //weight = weight*Luminosity/100.;
    //if(noLumiNorm) weight = 1.;
    //if(noPUcorr)   wgt_pu = 1.;
    weight = lumi_wgt*Luminosity;
    if(noLumiNorm) weight=1.;
    //if(noPUcorr) PileupWeight=1.;
    if(noPUcorr)   PUWeight=1;
    if(noSFlepcorr) sf_obj=1.;
    double gw = weight*PUWeight*sf_obj;  //cout<<"gw="<<gw<<", lumi_wgt="<<lumi_wgt<<", Luminosity="<<Luminosity<<", sf_obj="<<sf_obj<<", PUWeight="<<PUWeight<<"\n";
    if(i==0) h1_var->Fill(curr_var,gw); 
    if(i==1) h2_var->Fill(curr_var,gw);
    if(i==2) h3_var->Fill(curr_var,gw);
   }
   if(i==0){
    if(normalization){
     double scale = h1_var->Integral();
     h1_var->Scale(1/scale);
    }
    //leg->AddEntry(h1_var,rootplas[i].c_str(),"LP");
    leg->AddEntry(h1_var,"TT+tW in CR","LP");
   }
   if(i==1){
    if(normalization){
     double scale = h2_var->Integral();
     h2_var->Scale(1/scale);
    }
    //leg->AddEntry(h2_var,rootplas[i].c_str(),"LP");
    leg->AddEntry(h2_var,"TT+tW in SR","LP");
   }
   if(i==2){
    if(normalization){
     double scale = h3_var->Integral();
     h3_var->Scale(1/scale);
    }
    if(!twosamples) leg->AddEntry(h3_var,rootplas[i].c_str(),"LP");
   }
  }//Loop over rootplas
  h1_var->Draw("PE1");
  h2_var->Draw("PE1same");
  /////
  //   Draw
  /////
  //Bottom plot
  TLegend *leg1 = new TLegend(0.825, 0.35, 0.99, 0.99);
  leg1->SetHeader("Ratios");
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.075); 
  c1->cd();
  TPad* c1_1 = new TPad("pad1","pad1",0.01,0.01,0.99,0.32);
  c1_1->Draw();
  c1_1->cd();
  c1_1->SetTopMargin(0.01);
  c1_1->SetBottomMargin(0.3);
  c1_1->SetRightMargin(0.01);
  c1_1->SetLeftMargin(0.125);
  double h2_ratio_x[bin[v]]; double h2_ratio_y[bin[v]]; double h2_ratio_xerr[bin[v]]; double h2_ratio_yerr[bin[v]];
  double h3_ratio_x[bin[v]]; double h3_ratio_y[bin[v]]; double h3_ratio_xerr[bin[v]]; double h3_ratio_yerr[bin[v]];
  for(int j=0;j<bin[v];j++){
   h2_ratio_x[j] = 0; h2_ratio_y[j] = 0; h2_ratio_xerr[j] = 0; h2_ratio_yerr[j] = 0;
   h3_ratio_x[j] = 0; h3_ratio_y[j] = 0; h3_ratio_xerr[j] = 0; h3_ratio_yerr[j] = 0;
   h2_ratio_x[j] = h2_var->GetBinCenter(j+1);  h2_ratio_xerr[j] = 0;
   h3_ratio_x[j] = h3_var->GetBinCenter(j+1);  h3_ratio_xerr[j] = 0;
   double num2     = h2_var->GetBinContent(j+1); cout <<"bin Nun="<<num2;
   double num2_err = h2_var->GetBinError(j+1); cout<<", bin error Num="<<num2_err;
   double num3     = h3_var->GetBinContent(j+1);
   double num3_err = h3_var->GetBinError(j+1);
   double den      = h1_var->GetBinContent(j+1);  cout <<", bin Den="<<den;
   double den_err  = h1_var->GetBinError(j+1); cout<<", bin error Den="<<den_err<<"\n";
   if(den!=0 && num2!=0){
    h2_ratio_y[j]    = num2/den;
    h2_ratio_yerr[j] = sqrt(pow(num2_err/den,2) + pow((num2*den_err)/(den*den),2));
   }else{
    if(num2==0){	
     h2_ratio_y[j]    = 0;
     h2_ratio_yerr[j] = 0;
    }
    else{
     h2_ratio_y[j]    = -1000000;
     h2_ratio_yerr[j] = 0;
    }
   }
   if(den!=0 && num3!=0){
    h3_ratio_y[j]    = num3/den;
    h3_ratio_yerr[j] = sqrt(pow(num3_err/den,3) + pow((num3*den_err)/(den*den),3));
   }else{
    h3_ratio_y[j]    = -1000000;
    h3_ratio_yerr[j] = 0;
   }
   cout<<"center of bin (x)=  "<<h2_ratio_x[j]<<"; Numb. events (y) = "<<h2_ratio_y[j]<<"  +-  "<<h2_ratio_yerr[j]<<endl;
  }
  TGraphErrors *h2_ratio = new TGraphErrors(bin[v], h2_ratio_x, h2_ratio_y, h2_ratio_xerr, h2_ratio_yerr);
  h2_ratio->SetTitle(0);
  //h2_ratio->SetTitleSize(10);
  h2_ratio->SetMarkerStyle(7);
  h2_ratio->SetMarkerColor(2);
  h2_ratio->SetLineColor(2);
  h2_ratio->GetXaxis()->SetTitle(varTitleXaxis[v].c_str());
  h2_ratio->GetXaxis()->SetTitleSize(0.15);
  h2_ratio->GetXaxis()->SetRangeUser(inRange[v],endRange[v]);
  h2_ratio->GetYaxis()->SetRangeUser(0.5,1.5);
  h2_ratio->GetYaxis()->SetLimits(0.5,1.5);
  h2_ratio->GetYaxis()->SetTitle("Ratio");
  h2_ratio->GetYaxis()->SetLabelSize(0.075);
  h2_ratio->GetYaxis()->SetTitleSize(0.1);
  h2_ratio->GetYaxis()->SetTitleOffset(0.5);
  h2_ratio->SetMinimum(-5);
  h2_ratio->SetMaximum(1);
  h2_ratio->GetYaxis()->SetLimits(0.5,1.5);
  h2_ratio->Draw("APZ");
  h2_ratio->GetXaxis()->SetRangeUser(inRange[v],endRange[v]);
  h2_ratio->GetXaxis()->SetLimits(inRange[v],endRange[v]);
  h2_ratio->GetYaxis()->SetRangeUser(0.15,2);
  h2_ratio->GetYaxis()->SetLimits(0.15,2);
  TGraphErrors *h3_ratio = new TGraphErrors(bin[v], h3_ratio_x, h3_ratio_y, h3_ratio_xerr, h3_ratio_yerr);
  h3_ratio->SetMarkerStyle(7);
  h3_ratio->SetMarkerColor(3);
  h3_ratio->SetLineColor(3);
  if(!twosamples) h3_ratio->Draw("PZsame");
  //////////cout<<"fin qui va"<<endl;
  
  TLine* line = new TLine(inRange[v],0.69,endRange[v],0.69);
  line->SetLineColor(kRed);
  line->SetLineWidth(2);
  //line->Draw("same");
  string l2 = "#frac{"+rootplas[1]+"}"+"{"+rootplas[0]+"}";
  leg1->AddEntry(h2_ratio,l2.c_str(),"LP");
  if(!twosamples){
    string l3 = "#frac{"+rootplas[2]+"}"+"{"+rootplas[0]+"}";
    leg1->AddEntry(h3_ratio,l3.c_str(),"LP");
  }
  //leg1->Draw();
  
  ///////////////////////////////////////////////
  //Top plots
  c1->cd();
  TPad* c1_2 = new TPad("pad2","pad2",0.01,0.33,0.99,0.99);
  if(logYscale[v]==1) c1_2->SetLogy();
  c1_2->Draw();
  c1_2->cd();
  c1_2->SetTopMargin(0.01);
  c1_2->SetBottomMargin(0.1);
  c1_2->SetRightMargin(0.01);
  c1_2->SetLeftMargin(0.125);
  h1_var->SetMinimum(0);
  h1_var->SetMaximum(20); ///////////////////
  h1_var->Draw("PE1");
  h2_var->Draw("PE1same");
  if(!twosamples) h3_var->Draw("PE1same");
  leg->Draw();
  //Save plots
  c1->Update();
  string namefile = specsel+var[v]+"_"+selection+"_"+rootplas[1]+".pdf";
  if(!noPUcorr && noLumiNorm) namefile = specsel+var[v]+"_"+selection+"_PU_normratio.pdf";
  if(noLumiNorm && noPUcorr)  namefile = specsel+var[v]+"_"+selection+"_noLuminoPU_normratio.pdf";
  if(save_plots) c1->SaveAs(namefile.c_str());
 }//Loop over variables
}
/////
//   Call TFile to be read
/////
TFile* Call_TFile(string rootpla){
 //string file_name = path+specsel+"Sel_"+channel+"_"+rootpla+"_"+selection+".root";
 string file_name = path+rootpla+selection+".root";
 cout<<"file_name "<<file_name<<endl;
 TFile* f = new TFile(file_name.c_str(),"update");
 return f;
}
/////
//   Set setTDRStyle_modified (from link https://twiki.cern.ch/twiki/pub/CMS/TRK10001/setTDRStyle_modified.C)
/////
void setTDRStyle(){
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

  // For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);
  // For the Pad:
  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
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

  // For the histo:
  tdrStyle->SetHistFillColor(0);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
  // tdrStyle->SetNumberContours(Int_t number = 20);
//  tdrStyle->SetEndErrorSize(0);
  tdrStyle->SetErrorX(0.);
//  tdrStyle->SetErrorMarker(20);

  tdrStyle->SetMarkerStyle(20);

  //For the fit/function:
  tdrStyle->SetOptFit(0);
  tdrStyle->SetFitFormat("5.4g");
  //tdrStyle->SetFuncColor(1);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

  //For the date:
  tdrStyle->SetOptDate(0);
  // tdrStyle->SetDateX(Float_t x = 0.01);
  // tdrStyle->SetDateY(Float_t y = 0.01);

  // For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat(""); // To display the mean and RMS:   SetOptStat("mr");
  //tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatColor(kGray);
  tdrStyle->SetStatFont(42);

  tdrStyle->SetTextSize(11);
  tdrStyle->SetTextAlign(11);

  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(0);
  tdrStyle->SetStatX(1.); //Starting position on X axis
  tdrStyle->SetStatY(1.); //Starting position on Y axis
  tdrStyle->SetStatFontSize(0.025); //Vertical Size
  tdrStyle->SetStatW(0.25); //Horizontal size 
  // tdrStyle->SetStatStyle(Style_t style = 1001);

  // Margins:
  tdrStyle->SetPadTopMargin(0.05);
  tdrStyle->SetPadBottomMargin(0.125);
  tdrStyle->SetPadLeftMargin(0.14);
  tdrStyle->SetPadRightMargin(0.1);

  // For the Global title:

  //  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);
  // tdrStyle->SetTitleH(0); // Set the height of the title box
  // tdrStyle->SetTitleW(0); // Set the width of the title box
  // tdrStyle->SetTitleX(0); // Set the position of the title box
  // tdrStyle->SetTitleY(0.985); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  // tdrStyle->SetTitleBorderSize(2);

  // For the axis titles:
  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.0);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

  // For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.05, "XYZ");

  // For the axis:

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

  // Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);
  // Postscript options:
  // tdrStyle->SetPaperSize(15.,15.);
  // tdrStyle->SetLineScalePS(Float_t scale = 3);
  // tdrStyle->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle->SetHeaderPS(const char* header);
  // tdrStyle->SetTitlePS(const char* pstitle);
  // tdrStyle->SetBarOffset(Float_t baroff = 0.5);
  // tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
  // tdrStyle->SetPaintTextFormat(const char* format = "g");
  // tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // tdrStyle->SetTimeOffset(Double_t toffset);
  // tdrStyle->SetHistMinimumZero(kTRUE);

  tdrStyle->cd();
}
//const char *samples[]   = {"WW", "WZ", "ZZ", "DYToTauTau", "WJetToLNu", "TTJets", "data"};
//;, "massInv"};//, "jetHPT_pt","jetHPT_eta","jetHPT_phi"};
//, "massInv (GeV/c^2)"};//, "pT_{Jet} (GeV/c)","#eta_{Jet}","#phi_{Jet}"};
//Variable
/*
//Variables
const unsigned int int_var    = 0; //Till int_var, variables are int
const unsigned int double_var = 1; //From int_var to double_var, variables are double
//After double_var, variables are array  
const bool most_energetic = false; //true: plot all jet values; false: plot the most energetic jet values
const char *variables[]   = {"mu_iso"};
const char *titleXaxis[]  = {"mu_iso"};
//For Plots
const int    numVar            = 1;
const int    bin[numVar]       = {50};
const double inRange[numVar]   = {0};
const double endRange[numVar]  = {50};
*/
//Variables
//const unsigned int int_var    = 2; //Till int_var, variables are int
//const unsigned int double_var = 13; //From int_var to double_var, variables are double
//After double_var, variables are array  
//const bool most_energetic = false; //true: plot all jet values; false: plot the most energetic jet values
//const char *variables[]   = {"njet", "nbjet", "dR", "cosDphi", "pZeta", "met", "pair_cand1_pt","pair_cand1_eta","pair_cand1_phi","pair_cand2_pt","pair_cand2_eta","pair_cand2_phi", "mu_iso"};
//const char *titleXaxis[]  = {"njet", "nbjet", "dR", "cosDphi", "pZeta", "met (GeV/c)", "pT (GeV/c)_{Mu}","#eta_{Mu}","#phi_{Mu}","pT (GeV/c)_{Tau}","#eta_{Tau}","#phi_{Tau}", "mu_iso"};
//For Plots
//const int    numVar            = 13;
//const int    bin[numVar]       = {1, 5, 7, 10, 15, 17, 50, 6, 6, 50, 6, 6, 50};
//const double inRange[numVar]   = {0, 0, 0, -1, -300, 0, 0, -3, -6, 0, -3, -6, 0};
//const double endRange[numVar]  = {1, 5, 7, 1.5, 600, 510, 1000, 3, 6, 1000, 3, 6, 50};
//const int    logYscale[numVar] = {0,0,0,0,0,0};
//const int    logYscale[numVar] = {1,1,1,1,1,1,1,1,1,1,1,1,1};
//Variables
//const unsigned int int_var    = 2; //Till int_var, variables are int
//const unsigned int double_var = 13; //From int_var to double_var, variables are double
//After double_var, variables are array  
//const bool most_energetic = false; //true: plot all jet values; false: plot the most energetic jet values
//const char *variables[]   = {"njet", "nbjet", "dR", "cosDphi", "pZeta", "met", "pair_cand1_pt","pair_cand1_eta","pair_cand1_phi","pair_cand2_pt","pair_cand2_eta","pair_cand2_phi", "mu_iso"};
//const char *titleXaxis[]  = {"njet", "nbjet", "dR", "cosDphi", "pZeta", "met (GeV/c)", "pT (GeV/c)_{Mu}","#eta_{Mu}","#phi_{Mu}","pT (GeV/c)_{Tau}","#eta_{Tau}","#phi_{Tau}", "mu_iso"};
//For Plots
//const int    numVar            = 13;
//const int    bin[numVar]       = {1, 5, 7, 10, 15, 17, 50, 6, 6, 50, 6, 6, 50};
//const double inRange[numVar]   = {0, 0, 0, -1, -300, 0, 0, -3, -6, 0, -3, -6, 0};
//const double endRange[numVar]  = {1, 5, 7, 1.5, 600, 510, 1000, 3, 6, 1000, 3, 6, 50};
//const int    logYscale[numVar] = {0,0,0,0,0,0};
//const int    logYscale[numVar] = {1,1,1,1,1,1,1,1,1,1,1,1,1};
  /*
  TLine* line1;
  if(var[v]=="massT"){
   line1 = new TLine(180,0,180,70000);
   line1->SetLineColor(1);
   line1->SetLineWidth(3);
   line1->Draw("same");
  }
  if(var[v]=="met"){
   line1 = new TLine(60,0,60,100000);
   line1->SetLineColor(1);
   line1->SetLineWidth(3);
   line1->Draw("same");
  }
  */
