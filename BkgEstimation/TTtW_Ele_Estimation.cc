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
const string path         = "/afs/cern.ch/work/m/mpresill/HCMN/BkgEstimation/skimmed_root_files/";
//It is important you respect the orther: bkg, data_obs, sig
//For the moment: all bkg are taken from MC; data_obs = sum of all bkg; 
//const char *samples[]   = {"DY", "DYHT100to200", "DYHT200to400", "DYHT400to600", "DYHT100to200", "DYHT600toInf", "TT", "ST", "SaT", "WJets", "WW", "WZ", "ZZ", "sig"};
//const char *ParamPoints[] = {"L5000_M500", "L5000_M1500", "L5000_M2500", "L5000_M3500", "L5000_M4500", 
                            // "L15000_M500", "L15000_M1500", "L15000_M2500", "L15000_M3500", "L15000_M4500"       
                           // };
const char *samples[]     = {"DY","Other","data_ele"};
const string selection    = "_2016_TRe";  
//Plots option
const string varplot    = "M_leplepBjet";
const double fixcut     = 0; //Save only events for which varplot>fixcut
const string objsf      = "lepsf_evt";//"lepsf_evt";
const string PUw        = "PUWeight";//"PileupWeight";
const double Luminosity = 35542; //pb^-1    //2018: 58873 //2017: 41529 //2016: 35542
const bool noLumiNorm   = false;
const bool noPUcorr     = false;
const bool noobjsf      = false;  
const double normalize  = false;
//Binning
const int    bin             = 9; //For symmetric or asymmetric bins
const double inRange         = 0;
const double endRange        = 10000;
const bool   asymbin         = true;
const double asymbins[bin+1] = {0,200,400,600,800,1000,1400,2000,3500,10000};


const double TTtWSF[bin]     = {0,0,0,1.62785,0.296588,0.732169,0.547758,0.495361,0};//For e-channel with summed TT and tW
const double SFerr[bin]      = {0,0,0,2.00639,0.137307,0.202031,0.178748,0.246144,0};//For e-channel with summed TT and tW

/////
//   Declare functions 
/////
TH1F* Call_hist(string rootpla);
TH1F* get_treehist(string rootpla, int idx);
void setTDRStyle();
/////
//   Main function
/////
void TTtW_Ele_Estimation(){
 setTDRStyle();
 //vector<string> parampoints(ParamPoints, ParamPoints + sizeof(ParamPoints)/sizeof(ParamPoints[0]));
 vector<string> rootplas(samples, samples + sizeof(samples)/sizeof(samples[0]));
 //TCanvas* c1 = new TCanvas("SRshape","SRshape",400,400,1100,800);
 //Loop for any signal point
 //for(uint pp=0; pp<parampoints.size(); pp++){
  //Evaluate TH1F outside the scope of the new file 
  //Declare histos
  TH1F *DY; TH1F *TT; TH1F *tW; TH1F *TTtW; TH1F *Other; TH1F *data_read; TH1F *data_obs; TH1F *data_sub; TH1F *sig;
  if(!asymbin){
   DY    = new TH1F("","",bin,inRange,endRange);
   //TT    = new TH1F("","",bin,inRange,endRange);
   //tW    = new TH1F("","",bin,inRange,endRange);
   Other = new TH1F("","",bin,inRange,endRange);
   data_obs  = new TH1F("data_obs","data_obs",bin,inRange,endRange);
   data_sub = new TH1F("TTtW","TTtW",bin,inRange,endRange);
   data_read = new TH1F("","",bin,inRange,endRange);
   sig   = new TH1F("","",bin,inRange,endRange);
   //TTtW  = new TH1F("","",bin,inRange,endRange);
  }else{
   DY    = new TH1F("","",bin,asymbins);
   //TT    = new TH1F("","",bin,asymbins);
   //tW    = new TH1F("","",bin,asymbins);
   Other = new TH1F("","",bin,asymbins);
   data_obs  = new TH1F("data_obs","data_obs",bin,asymbins);
   data_sub = new TH1F("TTtW","TTtW",bin,asymbins);
   data_read = new TH1F("","",bin,asymbins);
   sig   = new TH1F("","",bin,asymbins);
   //TTtW  = new TH1F("","",bin,asymbins);
  }
  data_obs->Sumw2();//For the moment, untile you get it as a sum of SM bkg
  data_read->Sumw2();
  data_sub->Sumw2();
  //Fill histos
  for(uint i=0; i<rootplas.size(); i++){
   //Take DY and TT as for the other bkg, but it will change later
   //if(rootplas[i]=="DY") DY = Call_hist(rootplas[i]);
   if(rootplas[i]=="DY") DY = get_treehist(rootplas[i],i);
   //if(rootplas[i]=="TT") TT = get_treehist(rootplas[i],i);
   //if(rootplas[i]=="tW") tW = get_treehist(rootplas[i],i); 
   if(rootplas[i]=="Other") Other = get_treehist(rootplas[i],i);
   if(rootplas[i]=="data_ele")   data_read = get_treehist(rootplas[i],i); 
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
  //subtracting the non(TT and tW backgrounds)
  cout<<"data before "<<data_read->Integral()<<endl;
  data_read->Add(data_read,DY,1,-1);
  data_read->Add(data_read,Other,1,-1);
  cout<<"data after "<<data_read->Integral()<<endl;
  //Systematic calculation
  cout<<"{";
  for(int j=1; j<=bin; j++){
   double binerr=sqrt(data_read->GetBinContent(j));
   double bincont=data_read->GetBinContent(j);
   double syst;
   if(bincont>0){
    syst=100*(sqrt(pow((binerr*TTtWSF[j-1]),2)+pow((bincont*SFerr[j-1]),2)))/bincont;
   }
   else syst=0;
   cout<<syst<<",";
   //cout<<"bincont "<<bincont<<" SF "<<TTtWSF[j-1]<<" SFerr "<<SFerr[j-1]<<endl;
   //cout<<"    "<<endl;
  }
  cout<<"}"<<endl;
  //TTtW->Add(TT,tW,1,1);
  for(int i=1; i<=bin; i++){
    if(data_read->GetBinContent(i)>=0){
    data_sub->SetBinContent(i,data_read->GetBinContent(i)*TTtWSF[i-1]);
    }
    else data_sub->SetBinContent(i,0);
    if(data_sub->GetBinContent(i)!=0){
     data_sub->SetBinError(i,sqrt((pow((data_read->GetBinError(i)/data_read->GetBinContent(i)),2)+pow((SFerr[i-1]/TTtWSF[i-1]),2)))*(data_sub->GetBinContent(i)));
    }
    else{
     data_sub->SetBinError(i,0);
    /*
     if(i==8){
      data_sub->SetBinContent(i,0);
      data_sub->SetBinError(i,1.14);
     }
     if(i==9) data_sub->SetBinError(i,0.00087);
     //if(i==10) data_sub->SetBinError(i,0.0000039);
     */
    }
    cout<<"Bin"<<i<<"="<<data_sub->GetBinContent(i)<<endl;
    //cout<<data_read->GetBinContent(i)<<" "<<TTtWSF[i-1]<<endl;
    cout<<"Err"<<i<<"="<<data_sub->GetBinError(i)<<endl;
  } 
  //Create new file
  string norm;
  if(normalize) norm = "_norm";
  string newfilename = "eejj_TTtW_2016"+norm+"_data_driven.root";
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
 else                         namehist = "TTtW";//rootpla;
 if(!asymbin) hist = new TH1F(namehist.c_str(),namehist.c_str(),bin,inRange,endRange);
 else         hist = new TH1F(namehist.c_str(),namehist.c_str(),bin,asymbins);
 //Call root file
 string file_name = path+rootpla+selection+".root";
 TFile* f = new TFile(file_name.c_str(),"update");
 TTree *tree; f->GetObject("BOOM",tree); 
 double curr_var;
 TBranch *b_curr_var = 0;
 tree->SetBranchAddress(varplot.c_str(),&curr_var,&b_curr_var);
 //double PileupWeight;
 //TBranch *b_PileupWeight = 0;
 //tree->SetBranchAddress("PileupWeight",&PileupWeight,&b_PileupWeight);
 double PUWeight;
 TBranch *b_PUWeight = 0;
 tree->SetBranchAddress("PUWeight",&PUWeight,&b_PUWeight); 
 double lumi_wgt;
 TBranch *b_lumi_wgt = 0;
 tree->SetBranchAddress("lumi_wgt",&lumi_wgt,&b_lumi_wgt);
 //double sf_obj;
 //TBranch *b_sf_obj = 0;
 //tree->SetBranchAddress(objsf.c_str(),&sf_obj,&b_sf_obj);
 //Fill TH1F
 for(int j=0; j<tree->GetEntries(); j++)
 {
  Long64_t tentry = tree->LoadTree(j);
  b_curr_var->GetEntry(tentry);
  //b_PileupWeight->GetEntry(tentry);
  b_PUWeight->GetEntry(tentry);
  b_lumi_wgt->GetEntry(tentry);
  //b_sf_obj->GetEntry(tentry);
  double w = 1.;
  if(rootpla!="data_ele"){
 double sf_obj;
 TBranch *b_sf_obj = 0;
 tree->SetBranchAddress(objsf.c_str(),&sf_obj,&b_sf_obj);
 b_sf_obj->GetEntry(tentry);
   if(!noLumiNorm) w = w*lumi_wgt*Luminosity;
   //if(!noPUcorr)   w = w*PileupWeight;
   if(!noPUcorr)   w = w*PUWeight;
   if(!noobjsf)    w = w*sf_obj;
  }
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
