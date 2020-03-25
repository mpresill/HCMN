/**
This Macro   
1. Makes the root files with all the TH1F needed for limit evaluation 

Need to specify
1. See Declare Constants
*/
/////
//   To run: root -l Limit_rootFile.cc+  
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
#include "TCanvas.h"
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
//Path - samples 
const string path         = "/eos/user/m/mpresill/CMS/HN_Reload/QCD_Rootplized_samples_2016/";
//It is important you respect the orther: bkg, data_obs, sig
//For the moment: all bkg are taken from MC; data_obs = sum of all bkg; 
//const char *samples[]   = {"DY", "DYHT100to200", "DYHT200to400", "DYHT400to600", "DYHT100to200", "DYHT600toInf", "TT", "ST", "SaT", "WJets", "WW", "WZ", "ZZ", "sig"};
//const char *ParamPoints[] = {"L5000_M500", "L5000_M1500", "L5000_M2500", "L5000_M3500", "L5000_M4500", 
                            // "L15000_M500", "L15000_M1500", "L15000_M2500", "L15000_M3500", "L15000_M4500"       
                           // };
const char *samples[] = {//"TT_2016","tW_2016", 
	                "Other_2016","DY_2016","TTtW_2016",
                         "data_ele_2016"
                         //"data_mu_2016"
                        //"mumujj_L13000_M500_2016","mumujj_L13000_M1000_2016","mumujj_L13000_M2000_2016","mumujj_L13000_M5000_2016","mumujj_L13000_M8000_2016"
			//,"eejj_L13000_M500_2016","eejj_L13000_M1000_2016","eejj_L13000_M2000_2016","eejj_L13000_M5000_2016","eejj_L13000_M8000_2016" 
			};
const string selection    = "";  
//Plots option
const string varplot    = "M_leplepBjet1";
const double fixcut     = 0; //Save only events for which varplot>fixcut
const string objsf      = "lepsf_evt";//"lepsf_evt";
const double Luminosity = 35900;
const bool noLumiNorm   = false;
const bool noPUcorr     = false;
const bool noobjsf      = true;  
const double normalize  = false;
//Binning
const int    bin             = 9; //For symmetric or asymmetric bins
const double inRange         = 0;
const double endRange        = 10000;
const bool   asymbin         = true;
const double asymbins[bin+1] = {0,200,400,600,800,1000,1400,2000,3500,10000};
//const double TTtWSF[bin]     = {1,1,0.53,0.64,0.56,0.60,0.65,0.45,1,1};
//const double SFerr[bin]      = {0,0,0.08,0.04,0.04,0.05,0.09,0.16,0,0};
//Error of bkg (pay attention to use symmetric or asymmetric errors)
//const double aTTJets_CR1[bin] = {0, 0.754, 2.912, 3.816, 4.154, 3.299, 4.82, 6.746, 3.594, 1.529, 2.735};
//const double qcd_data[bin]    = {0,11.6535,23.1558,14.9535,8.98777,8.09695,8.26044, 6.74743, 4.03808, 0};
//const double qcd_AllMC[bin]   = {0,8.65445,20.0283,13.2981,4.76533,3.48063,3.78457, 2.26429, 1.51922, 0.0914024};
/////
//   Declare functions 
/////
TH1F* Call_hist(string rootpla);
TH1F* get_treehist(string rootpla, int idx);
void setTDRStyle();
/////
//   Main function
/////
void QCD_Ele_Estimation(){
 setTDRStyle();
 //vector<string> parampoints(ParamPoints, ParamPoints + sizeof(ParamPoints)/sizeof(ParamPoints[0]));
 vector<string> rootplas(samples, samples + sizeof(samples)/sizeof(samples[0]));
 //TCanvas* c1 = new TCanvas("SRshape","SRshape",400,400,1100,800);
 //TCanvas* c1 = new TCanvas("SRshape","SRshape",400,400,1100,800);
 //Loop for any signal point
 //for(uint pp=0; pp<parampoints.size(); pp++){
  //Evaluate TH1F outside the scope of the new file 
  //Declare histos
  TH1F *DY; TH1F *TT; TH1F *tW; TH1F *TTtW; TH1F *Other; TH1F *data_read; TH1F *data_obs; TH1F *data_sub; TH1F *sig;
  if(!asymbin){
   DY    = new TH1F("","",bin,inRange,endRange);
   TT    = new TH1F("","",bin,inRange,endRange);
   tW    = new TH1F("","",bin,inRange,endRange);
   Other = new TH1F("","",bin,inRange,endRange);
   data_obs  = new TH1F("data_obs","data_obs",bin,inRange,endRange);
   data_sub = new TH1F("QCD","QCD",bin,inRange,endRange);
   data_read = new TH1F("QCD","QCD",bin,inRange,endRange);
   sig   = new TH1F("","",bin,inRange,endRange);
   //TTtW  = new TH1F("","",bin,inRange,endRange);
  }else{
   DY    = new TH1F("","",bin,asymbins);
   TT    = new TH1F("","",bin,asymbins);
   tW    = new TH1F("","",bin,asymbins);
   Other = new TH1F("","",bin,asymbins);
   data_obs  = new TH1F("data_obs","data_obs",bin,asymbins);
   data_sub = new TH1F("QCD","QCD",bin,asymbins);
   data_read = new TH1F("QCD","QCD",bin,asymbins);
   sig   = new TH1F("","",bin,asymbins);
   //TTtW  = new TH1F("","",bin,asymbins);
  }
  //data_obs->Sumw2();//For the moment, untile you get it as a sum of SM bkg
  data_read->Sumw2();
  data_sub->Sumw2();
  //Fill histos
  for(uint i=0; i<rootplas.size(); i++){
   //Take DY and TT as for the other bkg, but it will change later
   //if(rootplas[i]=="DY") DY = Call_hist(rootplas[i]);
   if(rootplas[i]=="DY") DY = get_treehist(rootplas[i],i);
   if(rootplas[i]=="TT") TT = get_treehist(rootplas[i],i);
   if(rootplas[i]=="tW") tW = get_treehist(rootplas[i],i); 
   if(rootplas[i]=="Other") Other = get_treehist(rootplas[i],i);
   if(rootplas[i]=="data_ele")   data_read = get_treehist(rootplas[i],i);
   if(rootplas[i]=="prova") data_read = get_treehist(rootplas[i],i); 
   if(rootplas[i]=="data_obs"){
   }
  /* if(rootplas[i]=="sig"){
    sig = get_treehist(parampoints[pp],pp);
    cout<<setw(30)<<parampoints[pp]<<setw(30)<<sig->Integral()<<endl;
    if(normalize){
     Double_t scale = 1./sig->Integral();
     sig->Scale(scale);
    }
   }*/
  }
  //subtracting the non(QCD backgrounds)
  
  cout<<"data before "<<data_read->Integral()<<endl;
  data_read->Add(data_read,DY,1,-1);
  data_read->Add(data_read,Other,1,-1);
  data_read->Add(data_read,TT,1,-1);
  data_read->Add(data_read,tW,1,-1);
  cout<<"data after "<<data_read->Integral()<<endl;
  //TTtW->Add(TT,tW,1,1);
  
  for(int i=1; i<=bin; i++){
    if(data_read->GetBinContent(i)>0){
     data_sub->SetBinContent(i,data_read->GetBinContent(i));
     data_sub->SetBinError(i,data_read->GetBinError(i));
    }
    else{
     data_sub->SetBinContent(i,0);
     data_sub->SetBinError(i,0);
    }
    cout<<"Bin"<<i<<"="<<data_sub->GetBinContent(i)<<"\t"<<"Err"<<i<<"="<<data_sub->GetBinError(i)<< endl;
  } 
  //Create new file
  string norm;
  if(normalize) norm = "_norm";
  string newfilename = "eejj_QCD"+norm+".root";
  TFile *newfile = new TFile(newfilename.c_str(),"recreate");
  data_sub->Write();  delete data_sub;
  //DY->Write();    delete DY;
  //TT->Write();    delete TT;
  //ST->Write();    delete ST;
  //SaT->Write();   delete SaT;
  //WJets->Write(); delete WJets;
  //WW->Write();    delete WW;
  //WZ->Write();    delete WZ;
  //ZZ->Write();    delete ZZ;
  //data_obs->Write();  delete data_obs;
  //sig->Write();   delete sig;




  newfile->Write();
  newfile->Close();
 //}
}
/////
//   Call TFile to be read
//
TH1F* Call_hist(string rootpla){
 string file_name = path+"masshape_"+rootpla+".root";
 TFile* f = new TFile(file_name.c_str(),"update");
 TH1F *hist = new TH1F("","",bin,asymbins);
 f->GetObject("masshape",hist);
 TH1F *hist_val = new TH1F(rootpla.c_str(),rootpla.c_str(),bin,asymbins);
 hist_val->SetTitle(0);
 hist_val->GetXaxis()->SetTitle("massVis (GeV/c^{2})");
 hist_val->GetYaxis()->SetTitle("Entries");
 for(int i=1; i<=bin; i++){
  if(hist->GetBinCenter(i)>=fixcut && hist->GetBinContent(i)>=0){
    hist_val->SetBinContent(i,hist->GetBinContent(i));
    hist_val->SetBinError(i,hist->GetBinError(i));
  }else{
   hist_val->SetBinContent(i,0);
   hist_val->SetBinError(i,0);
  }
 }
 return hist_val;
}
TH1F* get_treehist(string rootpla, int idx){
 //New TH1F
 TH1F *hist;
 string namehist;
 if(rootpla.substr(0,1)=="L") namehist = "sig";
 else                         namehist = "QCD";
 if(!asymbin) hist = new TH1F(namehist.c_str(),namehist.c_str(),bin,inRange,endRange);
 else         hist = new TH1F(namehist.c_str(),namehist.c_str(),bin,asymbins);
 //Call root file
 string file_name = path+rootpla+selection+".root";
 TFile* f = new TFile(file_name.c_str(),"update");
 TTree *tree; f->GetObject("BOOM",tree); 
 double curr_var;
 TBranch *b_curr_var = 0;
 tree->SetBranchAddress(varplot.c_str(),&curr_var,&b_curr_var);
 double PileupWeight;
 TBranch *b_PileupWeight = 0;
 tree->SetBranchAddress("PileupWeight",&PileupWeight,&b_PileupWeight);
 //tree->SetBranchAddress("PUWeight",&PileupWeight,&b_PileupWeight);
 double lumi_wgt;
 TBranch *b_lumi_wgt = 0;
 tree->SetBranchAddress("lumi_wgt",&lumi_wgt,&b_lumi_wgt);
 double sf_obj;
 TBranch *b_sf_obj = 0;
 tree->SetBranchAddress(objsf.c_str(),&sf_obj,&b_sf_obj);
  //double QCD_wgt_mu1;
  //TBranch *b_QCD_wgt_mu1 = 0;
  //tree->SetBranchAddress("QCD_wgt_mu1",&QCD_wgt_mu1,&b_QCD_wgt_mu1);
  //double QCD_wgt_ele1;
  //TBranch *b_QCD_wgt_ele1 = 0;
  //tree->SetBranchAddress("QCD_wgt_ele1",&QCD_wgt_ele1,&b_QCD_wgt_ele1);
 double QCD_wgt_evt;
 TBranch *b_QCD_wgt_evt = 0;
 tree->SetBranchAddress("QCD_wgt_evt",&QCD_wgt_evt,&b_QCD_wgt_evt); 

//Fill TH1F
 for(int j=0; j<tree->GetEntries(); j++)
 {
  Long64_t tentry = tree->LoadTree(j);
  b_curr_var->GetEntry(tentry);
  b_PileupWeight->GetEntry(tentry);
  b_lumi_wgt->GetEntry(tentry);
  b_sf_obj->GetEntry(tentry);
  //b_QCD_wgt_mu1->GetEntry(tentry);
  //b_QCD_wgt_ele1->GetEntry(tentry);
  b_QCD_wgt_evt->GetEntry(tentry);
  //if(QCD_wgt_mu1>0.25) QCD_wgt_mu1=0.25;
  //double QCD_wgt_evt=(QCD_wgt_ele1/(1-QCD_wgt_ele1))*(QCD_wgt_mu1/(1-QCD_wgt_mu1));


  double w = 1.;
  if(rootpla!="data_ele" && rootpla!="data_mu"){
   if(!noLumiNorm) w = w*lumi_wgt*Luminosity;
   if(!noPUcorr)   w = w*PileupWeight;
   if(!noobjsf)    w = w*sf_obj;
  }
  w = w*QCD_wgt_evt;
  if(curr_var>fixcut){
   if(curr_var<endRange) hist->Fill(curr_var,w);
   else                  hist->Fill(endRange*0.99999,w);
  }
 }
 delete tree;
 return hist;
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
  // tdrStyle->SetStatStyle(Style_t style = 1001);

  // Margins:
  tdrStyle->SetPadTopMargin(0.05);
  tdrStyle->SetPadBottomMargin(0.125);
  tdrStyle->SetPadLeftMargin(0.1);
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
  tdrStyle->SetTitleYOffset(1.05);
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
