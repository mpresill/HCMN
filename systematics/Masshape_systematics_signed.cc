/**
This Macro   
1. Evaluates systematic effects as relative difference between
   final mass shape and the same evaluated taking into account a systematic effect

Need to specify
1. See Declare Constants
*/
/////
//   To run: root -l Masshape_systematics.cc+  
/////
/////
//   Prepare Root and Roofit
/////
#include "TFile.h"
#include "TH1F.h"
#include "TH1D.h"
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
//For sys
const string centralvalue_folder = "";//Central/";
const string syst_folder = "";//muSF/";
const string up_folder = "";//up/";
const string down_folder = "";//down/";
/////////
const string mainpath = "/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2016/";
const string systematics = "SFeejj"; 
//const string histo_central = "TTtW_eejj"; 
//const string histo_up = "TTtW_eejj_2016_SFUp";
//const string histo_down = "TTtW_eejj_2016_SFDOwn";
const char *histo_central[] = { "TTtW_eejj"            , "Other_eejj"            ,"DY_eejj"             }; 
const char *histo_up[] =      { "TTtW_eejj_2016_SFUp"  , "Other_eejj_2016_SFUp"  ,"DY_eejj_2016_SFUp"   };
const char *histo_down[] =    { "TTtW_eejj_2016_SFDown", "Other_eejj_2016_SFDown","DY_eejj_2016_SFDown" };
const char *process[] = { 
                              "SR_syst_TTtW_2016",     "SR_syst_Other_2016",     "SR_syst_DY_2016"                         
};
const int ini_proc    = 0;
const int fin_proc    = 3;   //numero di processi
//const string ininame = "masshape_";
//const string finname = ".root";
//const string finalms = "allbkg";
const string sys     = "";//muSF";
const bool updown    = true;
//For Plots
const int    bin          = 30;
const double inRange      = 0.;
//const string TitleX     = "Pileup systematics"; //Xaxis title
const double endRange     = 10000.;
const bool   doasym       = true;
const int    asymbin      = 9; ////FIX: dovrebbero essere 10
const double asymbins[10] = {0,200,400,600,800,1000,1400,2000,3500,10000};
const double upval        = 6;
const bool   saveplot     = true;
/////
//   Declare functions 
/////
void setTDRStyle();
/////
//   Main function
/////
void Masshape_systematics_signed() {
 setTDRStyle();
 vector<string> proc(process, process + sizeof(process)/sizeof(process[0]));
 vector<string> histo_c(histo_central, histo_central + sizeof(histo_central)/sizeof(histo_central[0]));
 vector<string> histo_u(histo_up, histo_up + sizeof(histo_up)/sizeof(histo_up[0]));
 vector<string> histo_d(histo_down, histo_down + sizeof(histo_down)/sizeof(histo_down[0]));
 

 for(uint p=ini_proc; p<fin_proc; p++){
 TCanvas* c1;
 if(updown){
  c1 = new TCanvas("Sys","Sys",200,200,700,600);
 }else{
  c1 = new TCanvas("Sys","Sys",200,200,1100,600);
 }
 string file = proc[p]+".root";
 string TitleX = sys+" systematics"+" for "+proc[p];
 //Legend
 TLegend *leg = new TLegend(0.8, 0.8, 1.0, 1.0);
 leg->SetHeader("");
 leg->SetBorderSize(0);
 //Bin
 int nbin = 0;
 if(doasym)  nbin = asymbin;
 if(!doasym) nbin = bin;
 //allbkg
 TH1D *h_allbkg;
 if(doasym)  h_allbkg = new TH1D("","",nbin,asymbins);
 if(!doasym) h_allbkg = new TH1D("","",nbin,inRange,endRange);
 TFile* f_allbkg = new TFile((mainpath+file).c_str(),"read");
 f_allbkg->GetObject(histo_c[p].c_str(),h_allbkg);     ///////EDITED proc[p]
 //Sys Plus
 TH1D *h_sys_p;
 if(doasym)  h_sys_p = new TH1D("","",nbin,asymbins);
 if(!doasym) h_sys_p = new TH1D("","",nbin,inRange,endRange);
 string Plus = "";
 if(updown) Plus = "Plus"; 
 //TFile* f_sys_p = new TFile((mainpath+centralvalue_folder+file).c_str(),"update");
 TFile* f_sys_p = new TFile((mainpath+file).c_str(),"read");
 f_sys_p->GetObject(histo_u[p].c_str(),h_sys_p);    ///////EDITED proc[p]
 TH1D *h_diff_p;
 if(doasym)  h_diff_p = new TH1D("","",nbin,asymbins);
 if(!doasym) h_diff_p = new TH1D("","",nbin,inRange,endRange);
 //h_diff_p->SetTitle(sys.c_str());
 //h_diff_p->SetTitle(0);
 h_diff_p->SetMarkerStyle(8);
 h_diff_p->SetMarkerColor(1);
 if(updown){ 
  h_diff_p->SetLineColor(4);
 }else{
  h_diff_p->SetLineColor(kMagenta+2);
 }
 //h_diff_p->SetMaximum(upval);
 string titleXaxis = "M(e,e,J) [GeV]";
 h_diff_p->GetXaxis()->SetTitle(titleXaxis.c_str());
 string titleYaxis = "Relative difference (in %)";
 h_diff_p->GetYaxis()->SetTitle(titleYaxis.c_str());
 //Sys Minus
 TH1D *h_sys_m;
 if(doasym)  h_sys_m = new TH1D("","",nbin,asymbins);
 if(!doasym) h_sys_m = new TH1D("","",nbin,inRange,endRange);
 string Minus = "";
 if(updown) Minus = "Minus";
 //TFile* f_sys_m = new TFile((mainpath+centralvalue_folder+file).c_str(),"update");
 TFile* f_sys_m = new TFile((mainpath+file).c_str(),"read");
 f_sys_m->GetObject(histo_d[p].c_str(),h_sys_m);    ///////EDITED proc[p]
 TH1D *h_diff_m;
 if(doasym)  h_diff_m = new TH1D("","",nbin,asymbins);
 if(!doasym) h_diff_m = new TH1D("","",nbin,inRange,endRange);
 h_diff_m->SetTitle(TitleX.c_str());
 if(updown){
  h_diff_m->SetLineColor(2);
 }else{
  h_diff_m->SetLineColor(kMagenta+2);
 }
 //Make the rel diff
 for(int i=1; i<=nbin; i++){   
  double mainval   = h_allbkg->GetBinContent(i);
  //Sys Plus
  double shiftpval = h_sys_p->GetBinContent(i);
  //double diffp     = fabs(mainval-shiftpval);
  double diffp     = mainval-shiftpval;
  double reldiffp;
  if(mainval!=0){
   reldiffp = diffp/mainval*100;
  }else{
   reldiffp = 0;
  }
  h_diff_p->SetBinContent(i,reldiffp); 
  //Sys Minus
  double shiftmval = h_sys_m->GetBinContent(i);
  //double diffm     = fabs(mainval-shiftmval);
  double diffm     = mainval-shiftmval;
  double reldiffm;
  if(mainval!=0){
   reldiffm = diffm/mainval*100;
  }else{
   reldiffm = 0;
  }
  h_diff_m->SetBinContent(i,reldiffm);
  //cout<<h_diff_m->GetBinContent(i)<<endl;
 }
 double highestbinval = 0;
 for(int h=1; h<=h_diff_p->GetNbinsX(); h++) if(h_diff_p->GetBinContent(h)>highestbinval) highestbinval=h_diff_p->GetBinContent(h);
 for(int h=1; h<=h_diff_p->GetNbinsX(); h++) if(h_diff_m->GetBinContent(h)>highestbinval) highestbinval=h_diff_m->GetBinContent(h);
 h_diff_p->SetMaximum(highestbinval+0.5);
 TGaxis::SetMaxDigits(3);
 h_diff_p->SetTitle(TitleX.c_str());
 //h_diff_p->SetTitle(0);
 h_diff_p->Draw(""); 
 h_diff_m->Draw("same");
 //Legend
 leg->AddEntry(h_diff_p,"Up","L");
 leg->AddEntry(h_diff_m,"Down","L");
 if(updown) leg->Draw();
 //Save
 string namefile = "sys_"+proc[p]+"_"+systematics+".pdf";
 if(saveplot){ c1->SaveAs(namefile.c_str());}
 //Take maximum relative difference
 if(updown){
  TH1D *h_max_sys;
  if(doasym)  h_max_sys = new TH1D("","",nbin,asymbins);
  if(!doasym) h_max_sys = new TH1D("","",nbin,inRange,endRange);
  //h_max_sys->SetTitle(0);
  h_max_sys->SetMarkerStyle(8);
  h_max_sys->SetMarkerColor(1);
  h_max_sys->SetLineColor(kMagenta+2);
  h_max_sys->SetMaximum(upval);
  h_max_sys->GetXaxis()->SetTitle(titleXaxis.c_str());
  string titleYaxis2 = "Maximum relative difference (in %)";
  h_max_sys->GetYaxis()->SetTitle(titleYaxis2.c_str());
  cout<<" "<<endl;
  cout<<"{";
  for(int m=1; m<=nbin; m++){
   if(fabs(h_diff_p->GetBinContent(m)) > fabs(h_diff_m->GetBinContent(m))){
    h_max_sys->SetBinContent(m,fabs(h_diff_p->GetBinContent(m)));
   }else{
    h_max_sys->SetBinContent(m,fabs(h_diff_m->GetBinContent(m)));
   }
   cout<<h_max_sys->GetBinContent(m)<<","; 
  }
  cout<<"}"<<"  //"<<proc[p]<<endl;
  cout<<" "<<endl;
  TCanvas* c2;
  if(updown){
   c2 = new TCanvas("Sys2","Sys2",200,200,700,600);
  }else{
   c2 = new TCanvas("Sys2","Sys2",200,200,1100,600);
  }
  h_max_sys->SetTitle(TitleX.c_str());
  //h_max_sys->SetTitle(0);
  h_max_sys->Draw(); 
  string namefile2 = "sysM_"+proc[p]+"_"+systematics+".pdf";
  if(saveplot){ c2->SaveAs(namefile2.c_str());}
 }
}
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
  tdrStyle->SetOptFit(1);
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
  tdrStyle->SetTitleH(0.045); // Set the height of the title box
  //tdrStyle->SetTitleW(0); // Set the width of the title box
  tdrStyle->SetTitleX(0.15); // Set the position of the title box
  tdrStyle->SetTitleY(1.0); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  tdrStyle->SetTitleBorderSize(0);

  // For the axis titles:
  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.2);
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
