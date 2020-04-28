/**
This Macro   
1. Plots variables in stack mode with the option to compare them with data
   It also allows the option to normalise them to 1

Need to specify
1. See Declare Constants
2. In double_h_var you have to specify if you want to access 1d or vector variables 
3. datatype in the main
   Make also sure that the data sample is the last one in the list const char *samples[] 
   Usually the signal comes soon before the data sample
4. You will have to custimazie color, aesthetics, and style according to the specific plot needs
5. Remember that if doasym is true
   . v = n-1: where v is in bin[v] and n is inasymbin[n]
   . the range must be the same between [inRange-endRange] e asymbin
*/
/////
//   To run: root -l StackPlots.cc+  
/////
/////
//   Prepare Root and Roofit
/////
#include "TFile.h"
#include "TH1F.h"
#include "TH1.h"
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
#include "TBranch.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <iostream>
#include "TPaveText.h"
#include "CMS_lumi.C"
using namespace std;
/////
//   Declare constants
/////
//Path - samples - selection
const string path       = "/eos/user/v/vmariani/NTuples/HN_2018/";
//"/eos/user/m/mpresill/CMS/HN_Reload/rootplized_samples_2017/";
const char *samples[]   = {"TTtW","DY","Other", "data_ele"};
const string selection  = "_2018"; //_SingleEle, _SingleMu
const bool nodata       = false;  //You must always comment data in "samples" if you don't want it
const bool show_ratio   = true;
//Weights
const double Luminosity = 35542; //pb^-1    //2018: 58873 //2017: 41529 //2016: 35542
const bool   LumiNorm   = true; //default true  
const bool   PUcorr     = true; //default true
const bool   SF         = true; //default true
const double scale      = 0;    //0 means no scaling; any other values means scale histo by the value of scale
//Normalisation of plots (it requires to run one time for get bkg normalisation)
const bool normalised   = false;
const double normbkg    = 1; //normbkg and normdata values have to be taken after 1 iteration of the macro with normalised = false
const double normdata   = 1;
const double normsig1    = 1;
const double normsig2   = 1;
//Plots
const bool save_plots   = true;
const bool show_title   = true;
const bool doasym       = false; 
const double asymbin[10] = {0,200,400,600,800,1000,1400,2000,3500,10000};
const double asymbin2[7] = {400,600,800,1000,1400,2000,3500};
const int    numVar     = 1;
//const int logYscale[numVar] = {};
const int logYscale[numVar] = {0};
const int logXscale[numVar] = {1};
const int    col_size   = 500; //>= highest bin
//Variables
const unsigned int ini_var = 0;
const unsigned int fin_var = 1; 
const int posvtcr          = 0;

const char *variables[]         = {
/*"BJetness_num_vetonoipnoiso_leps", "BJetness_num_soft_leps", "BJetness_num_pdgid_leps", "BJetness_num_loosenoipnoiso_leps", "BJetness_pvTrkOVcollTrk", "BJetness_numjettrksnopv", "BJetness_avsip3d_sig", "BJetness_avip3d_val", "BJetness_avip3d_sig", "BJetness_avip1d_sig", */"nBestVtx"
};
const char *titleXaxis[]        = {
/*"BJetness_num_vetonoipnoiso_leps", "BJetness_num_soft_leps", "BJetness_num_pdgid_leps", "Number of leptons", "pvTrkOVcollTrk", "Number of not PV tracks", "Average Signed IP 3D Sig", "Average IP 3D Val", "Average IP 3D Sig", "Average IP 1D Sig", */ "NPV"
};
/*const int    bin[numVar]        = {
5, 10, 8, 8, 15, 15, 90, 70, 80, 80, 30
};
const double inRange[numVar]    = {
0, 0, 0, 0, 0, 0, -10, 0, 0, 0, 0
};
const double endRange[numVar]   = {
20, 10, 8, 8, 1.5, 15, 80, 1, 80, 100, 30
};
*/
/*const char *variables[]         = {
"M_leplepBjet"
};
const char *titleXaxis[]        = {
"#scale[1]{#font[12]{M}_{#mu #mu J}} #scale[0.8]{(GeV)}"
//"#scale[1]{#font[12]{M}_{eeJ}} #scale[0.8]{(GeV)}"
};
*/
const int    bin[numVar]        = {
100
};
const int    bin2[numVar]       = {
100
};
const double inRange[numVar]    = {
0
};
const double endRange[numVar]   = {
100
};
/////
//   Declare functions 
/////
TFile* Call_TFile(string rootpla);
TH1F* double_h_var(unsigned int v, string var, string vaT, uint i, string rootplas, double err_AllBkg[][col_size], double ent_AllBkg[][col_size], int datatype);
TH1F* double_h_var2(unsigned int v, string var, string vaT, uint i, string rootplas, double err_AllBkg[][col_size], double ent_AllBkg[][col_size], int datatype);
void draw_plots(TCanvas* c1, TH1F* h_sum_var, THStack* hstack, TH1F* h_data_var, TH1F* h_data_var2, TH1F* h_sig, TH1F* h_sig2, TH1F* h_TTtW, TH1F* h_DY, TH1F* h_Other, TLegend* leg, double err_AllBkg[][col_size], double ent_AllBkg[][col_size], uint rootplas_size, int v, string var, string vartitle, double highestbinval);
void draw_lines(double x1, double y1, double x2, double y2);
int      get_col(string name);
double   get_highestbinval(TH1F* h_data_var, TH1F* h_sig, TH1F* h_sig2, THStack* hstack, int v);
void save_canvas(TCanvas* c1, string var);
TLegend* get_legend();
TH1F*    get_th1f(string var, int v);
TH1F*    get_datath1f(string var, string title, int v);
void setTDRStyle();
/////
//   Main function
/////
void StackPlots_var(){
 setTDRStyle();
 //Loop over all variables
 vector<string> var(variables, variables + sizeof(variables)/sizeof(variables[0]));
 vector<string> varTitleXaxis(titleXaxis, titleXaxis + sizeof(titleXaxis)/sizeof(titleXaxis[0]));
 for(uint v=ini_var; v<fin_var; v++){
  cout<<var[v]<<endl;
  //Declare legend and histograms 
  TLegend *leg = get_legend();
  //MC
  double bkgstackintegral = 0.;
  THStack* hstack = new THStack("hstack","hstack");
  TH1F* h_sum_var = get_th1f(var[v], v); h_sum_var->Sumw2();
  TH1F* h_sig     = get_th1f(var[v], v);
  TH1F* h_sig2    = get_th1f(var[v], v); 
  TH1F* h_TTtW    = get_th1f(var[v], v);
  TH1F* h_DY      = get_th1f(var[v], v);
  TH1F* h_Other   = get_th1f(var[v], v);
  //Data
  TH1F* h_data_var = get_datath1f(var[v], varTitleXaxis[v], v); h_data_var->Sumw2();
  TH1F* h_data_var2 = get_datath1f(var[v], varTitleXaxis[v], v); h_data_var2->Sumw2();
  //Loop over samples
  vector<string> rootplas(samples, samples + sizeof(samples)/sizeof(samples[0]));
  const uint rootplas_size = rootplas.size();
  double err_AllBkg[rootplas_size][col_size];
  double ent_AllBkg[rootplas_size][col_size];
  for(uint i=0; i<rootplas_size; i++) for(int j=0; j<bin[v]; j++) err_AllBkg[i][j] = 0.;
  for(uint i=0; i<rootplas_size; i++) for(int j=0; j<bin[v]; j++) ent_AllBkg[i][j] = 0.;
  for(uint i=0; i<rootplas_size; i++){
   int datatype = 0; //for data
   if(rootplas[i]=="eejj_L13000_M2000" || rootplas[i]=="eejj_L13000_M1000"){                                                 datatype = 1; //for signal
   }else if(rootplas[i]!="data_ele" && rootplas[i]!="data_mu" && rootplas[i]!="SLep"){ datatype = 2; //for other mc samples
   }
   //Declare histograms for variables
   TH1F *h_var = get_th1f(var[v], v);
   //Choose type of variables
   if(datatype==2){       h_var  = double_h_var(v,var[v],varTitleXaxis[v],i,rootplas[i],err_AllBkg,ent_AllBkg,datatype);
   }else if(datatype==1){
     if(rootplas[i]=="eejj_L13000_M2000"){h_sig  = double_h_var(v,var[v],varTitleXaxis[v],i,rootplas[i],err_AllBkg,ent_AllBkg,datatype);}
     if(rootplas[i]=="eejj_L13000_M1000"){h_sig2  = double_h_var(v,var[v],varTitleXaxis[v],i,rootplas[i],err_AllBkg,ent_AllBkg,datatype);}
   }else{   h_data_var = double_h_var(v,var[v],varTitleXaxis[v],i,rootplas[i],err_AllBkg,ent_AllBkg,datatype);
            h_data_var2 = double_h_var2(v,var[v],varTitleXaxis[v],i,rootplas[i],err_AllBkg,ent_AllBkg,datatype);
}
   if(datatype==2){ 
    //Put histos in the hstack 
    int col = get_col(rootplas[i]);
    if(rootplas[i].substr(0,2)=="TT" || rootplas[i].substr(0,2)=="tW"){
     h_var->SetFillColor(kOrange+1);
     h_var->SetLineColor(kOrange+1);
     h_TTtW->SetFillColor(kOrange+1);
     h_TTtW->SetLineColor(kOrange+1);
    }else if (rootplas[i].substr(0,2)=="DY"){
     h_var->SetFillColor(kRed-3);
     h_var->SetLineColor(kRed-3);
     h_DY->SetFillColor(kRed-3);
     h_DY->SetLineColor(kRed-3);
    }else{
     h_var->SetFillColor(kBlue-1);
     h_var->SetLineColor(kBlue-1);
     h_Other->SetFillColor(kBlue-1);
     h_Other->SetLineColor(kBlue-1);
    }
    hstack->Add(h_var);
    float sig_entries_f = h_sig->Integral();
    float sig2_entries_f = h_sig2->Integral();
    char numBkg_entries_c[1000]; float numBkg_entries_f = h_var->Integral();
    sprintf(numBkg_entries_c,"%.1f",numBkg_entries_f);
    //string bkg_leg = "#scale[0.75]{"+rootplas[i]+" ("+(string)numBkg_entries_c+")}";
    string bkg_leg = "#scale[0.75]{"+rootplas[i]+"}";
    if(rootplas[i]=="TTtW") bkg_leg = "#scale[0.75]{t#bar{t}+tW}";
    //leg->AddEntry(h_var,rootplas[i].c_str(),"F");
    ////////////////leg->AddEntry(h_var,bkg_leg.c_str(),"F");
    //Sum them for the error
    h_sum_var->Add(h_sum_var,h_var); 
    cout<<setw(5)<<"Evt"<<setw(15)<<rootplas[i]<<setw(15)<<h_var->Integral()<<endl;
    bkgstackintegral += h_var->Integral();
   }else if(datatype==0){
    cout<<setw(5)<<"Evt"<<setw(15)<<rootplas[i]<<setw(15)<<h_data_var->Integral()<<endl;
   }
  }
  cout<<setw(5)<<"Evt"<<setw(15)<<"Bkg"<<setw(15)<<bkgstackintegral<<endl;  
  cout<<setw(5)<<"Evt"<<setw(15)<<"Sig"<<setw(15)<<h_sig->Integral()<<endl;
  cout<<setw(5)<<"Evt"<<setw(15)<<"Sig2"<<setw(15)<<h_sig2->Integral()<<endl;  
  //Draw
  double highestbinval = get_highestbinval(h_data_var,h_sig,h_sig2,hstack,v);
  TCanvas* c1 = new TCanvas(var[v].c_str(),var[v].c_str(),200,200,700,600);
  draw_plots(c1,h_sum_var,hstack,h_data_var,h_data_var2,h_sig,h_sig2,h_TTtW,h_DY,h_Other,leg,err_AllBkg,ent_AllBkg,rootplas_size,v,var[v],varTitleXaxis[v],highestbinval);
  //draw_lines(2,0,2,highestbinval+0.25*highestbinval);
  save_canvas(c1,var[v]);
 }
}
/////
//   Call TFile to be read
/////
TFile* Call_TFile(string rootpla){
 string file_name = path+rootpla+selection+".root";
 TFile* f = new TFile(file_name.c_str(),"read");
 return f;
}
/////
//   Fill histo with double type
/////
TH1F* double_h_var(unsigned int v, string var, string varT, uint i, string rootplas, double err_AllBkg[][col_size], double ent_AllBkg[][col_size], int datatype){
 //Call tree and variables 
 TFile* f = Call_TFile(rootplas); TTree *tree; f->GetObject("BOOM",tree);
 //vector <double> * curr_var;
 //curr_var = 0;
 //TBranch *b_curr_var = 0;
 //tree->SetBranchAddress(var.c_str(),&curr_var,&b_curr_var);
 //double curr_var;
 int curr_var;
 TBranch *b_curr_var = 0;
 tree->SetBranchAddress(var.c_str(),&curr_var,&b_curr_var);
 double PileupWeight;
 TBranch *b_PileupWeight = 0;
 tree->SetBranchAddress("PileupWeight",&PileupWeight,&b_PileupWeight);
 double PUWeight; //added by Matteo
 TBranch *b_PUWeight = 0;
 tree->SetBranchAddress("PUWeight",&PUWeight,&b_PUWeight);
 double lumi_wgt;
 TBranch *b_lumi_wgt = 0;
 tree->SetBranchAddress("lumi_wgt",&lumi_wgt,&b_lumi_wgt);
 double lepsf_evt;
 TBranch *b_lepsf_evt = 0;
 tree->SetBranchAddress("lepsf_evt",&lepsf_evt,&b_lepsf_evt);
 //Fill histo
 TH1F *hist = get_th1f(var, v);
 hist->SetTitle(0); hist->SetMarkerStyle(8); hist->SetMarkerColor(1); hist->SetLineColor(1);
 TH1F *hist_err;
 if(var=="M_leplepBjet" && doasym) hist_err = new TH1F("hist_err","hist_err",bin[v],asymbin);
 else                         hist_err = new TH1F("hist_err","hist_err",bin[v],inRange[v],endRange[v]);
 hist_err->Sumw2();
 for(int j=0; j<tree->GetEntries(); j++)
 //for(int j=0; j<10; j++)
 {
  double w = 1.;
  Long64_t tentry = tree->LoadTree(j);
  b_curr_var->GetEntry(tentry); 
  b_PileupWeight->GetEntry(tentry);
  b_PUWeight->GetEntry(tentry);
  b_lepsf_evt->GetEntry(tentry);
  b_lumi_wgt->GetEntry(tentry);
  if(datatype!=0){
   if(LumiNorm) w = w*lumi_wgt*Luminosity;
   if(PUcorr)   w = w*PileupWeight;//PileupWeight;
   if(SF)       w = w*lepsf_evt;
   if(scale!=0) w = w*scale;
   if(inRange[v]<curr_var && curr_var<endRange[v]){hist->Fill(curr_var,w);         hist_err->Fill(curr_var,w*w);}
   if(curr_var>=endRange[v])                      {hist->Fill(0.99*endRange[v],w); hist_err->Fill(0.99*endRange[v],w*w);}
   if(curr_var<=inRange[v])                       {hist->Fill(1.01*inRange[v],w);  hist_err->Fill(1.01*inRange[v],w*w);}
   //if(inRange[v]<curr_var->at(posvtcr) && curr_var->at(posvtcr)<endRange[v]){hist->Fill(curr_var->at(posvtcr),w);hist_err->Fill(curr_var->at(posvtcr),w*w);}
   //if(curr_var->at(posvtcr)>=endRange[v])                                   {hist->Fill(0.99*endRange[v],w); hist_err->Fill(0.99*endRange[v],w*w);}
   //if(curr_var->at(posvtcr)<=inRange[v])                                    {hist->Fill(1.01*inRange[v],w);  hist_err->Fill(1.01*inRange[v],w*w);}
  }else{
   if(inRange[v]<curr_var && curr_var<endRange[v]) hist->Fill(curr_var);
   if(curr_var>=endRange[v])                       hist->Fill(0.99*endRange[v]);
   if(curr_var<=inRange[v])                        hist->Fill(1.01*inRange[v]);
   //if(inRange[v]<curr_var->at(posvtcr) && curr_var->at(posvtcr)<endRange[v]) hist->Fill(curr_var->at(posvtcr));
   //if(curr_var->at(posvtcr)>=endRange[v])                                    hist->Fill(0.99*endRange[v]);
   //if(curr_var->at(posvtcr)<=inRange[v])                                     hist->Fill(1.01*inRange[v]);
  }
 }
 //Get errors, normalise
 if(normalised){
  if(datatype==0) hist->Scale(1/normdata);
  if(datatype==1 && rootplas=="eejj_L13000_M2000" ) hist->Scale(1/normsig1);
  if(datatype==1 && rootplas=="eejj_L13000_M1000") hist->Scale(1/normsig2);
  if(datatype==2) hist->Scale(1/normbkg);
 }
 if(datatype==2){
  for(int j=0; j<bin[v]; j++){
   ent_AllBkg[i][j] = hist->GetBinContent(j+1);
   err_AllBkg[i][j] = sqrt(hist_err->GetBinContent(j+1));
   if(normalised)   err_AllBkg[i][j] = err_AllBkg[i][j]/normbkg;
  }
 }
 delete tree;
 return hist;
}

TH1F* double_h_var2(unsigned int v, string var, string varT, uint i, string rootplas, double err_AllBkg[][col_size], double ent_AllBkg[][col_size], int datatype){
 TFile* f = Call_TFile(rootplas); TTree *tree; f->GetObject("BOOM",tree);
 double curr_var;
 TBranch *b_curr_var = 0;
 tree->SetBranchAddress(var.c_str(),&curr_var,&b_curr_var);
 double PileupWeight;
 TBranch *b_PileupWeight = 0;
 tree->SetBranchAddress("PileupWeight",&PileupWeight,&b_PileupWeight);
 double PUWeight; //added by Matteo
 TBranch *b_PUWeight = 0;
 tree->SetBranchAddress("PUWeight",&PUWeight,&b_PUWeight);
 double lumi_wgt;
 TBranch *b_lumi_wgt = 0;
 tree->SetBranchAddress("lumi_wgt",&lumi_wgt,&b_lumi_wgt);
 double lepsf_evt;
 TBranch *b_lepsf_evt = 0;
 tree->SetBranchAddress("lepsf_evt",&lepsf_evt,&b_lepsf_evt);
 TH1F *hist = new TH1F("hist_err","hist_err",bin2[v],asymbin2);
 hist->SetTitle(0); hist->SetMarkerStyle(1); hist->SetMarkerColor(1); hist->SetLineColor(1);
 TH1F *hist_err;
 if(var=="M_leplepBjet" && doasym) hist_err = new TH1F("hist_err","hist_err",bin2[v],asymbin2);
 else                         hist_err = new TH1F("hist_err","hist_err",bin2[v],inRange[v],endRange[v]);
 hist_err->Sumw2();
 for(int j=0; j<tree->GetEntries(); j++)
 {
  double w = 1.;
  Long64_t tentry = tree->LoadTree(j);
  b_curr_var->GetEntry(tentry);
  b_PileupWeight->GetEntry(tentry);
  b_PUWeight->GetEntry(tentry);
  b_lepsf_evt->GetEntry(tentry);
  b_lumi_wgt->GetEntry(tentry);
  if(datatype!=0){
   if(LumiNorm) w = w*lumi_wgt*Luminosity;
   if(PUcorr)   w = w*PileupWeight; //default was "w*PileupWeight"
   if(SF)       w = w*lepsf_evt;
   if(scale!=0) w = w*scale;
   if(inRange[v]<curr_var && curr_var<endRange[v]){hist->Fill(curr_var,w);         hist_err->Fill(curr_var,w*w);}
   if(curr_var>=endRange[v])                      {hist->Fill(0.99*endRange[v],w); hist_err->Fill(0.99*endRange[v],w*w);}
   if(curr_var<=inRange[v])                       {hist->Fill(1.01*inRange[v],w);  hist_err->Fill(1.01*inRange[v],w*w);}
  }else{
   if(200<curr_var && curr_var<3500) hist->Fill(curr_var);
  }
 }
 if(normalised){
  if(datatype==0) hist->Scale(1/normdata);
  if(datatype==1 && rootplas=="eejj_L13000_M2000" ) hist->Scale(1/normsig1);
  if(datatype==1 && rootplas=="eejj_L13000_M1000") hist->Scale(1/normsig2);
  if(datatype==2) hist->Scale(1/normbkg);
 }
 if(datatype==2){
  for(int j=0; j<bin[v]; j++){
   ent_AllBkg[i][j] = hist->GetBinContent(j+1);
   err_AllBkg[i][j] = sqrt(hist_err->GetBinContent(j+1));
   if(normalised)   err_AllBkg[i][j] = err_AllBkg[i][j]/normbkg;
  }
 }
 delete tree;
 return hist;
}




void draw_plots(TCanvas* c1, TH1F* h_sum_var, THStack* hstack, TH1F* h_data_var, TH1F* h_data_var2, TH1F* h_sig, TH1F* h_sig2, TH1F* h_TTtW, TH1F* h_DY, TH1F* h_Other, TLegend* leg, double err_AllBkg[][col_size], double ent_AllBkg[][col_size], uint rootplas_size, int v, string var, string vartitle, double highestbinval){
 //Canvas
 if(logYscale[v]==1) c1->SetLogy();
 if(logXscale[v]==1) c1->SetLogx();
 if(show_ratio){  
  //Bottom plot
  TPad *c1_1 = new TPad("c1_1", "newpad",0.01,0.01,0.99,0.32);
  c1_1->Draw();
  c1_1->cd();
  c1_1->SetTopMargin(0.01);
  c1_1->SetBottomMargin(0.4);
  c1_1->SetRightMargin(0.01);
  c1_1->SetLeftMargin(0.125);
  //c1_1->SetFillStyle(0);
  //Get values 
  double dataSUmc_x[bin[v]]; double dataSUmc_y[bin[v]]; double dataSUmc_xerr[bin[v]]; double dataSUmc_yerr[bin[v]];
  for(int j=0; j<bin[v]; j++){
   dataSUmc_x[j] = 0; dataSUmc_y[j] = 0; dataSUmc_xerr[j] = 0; dataSUmc_yerr[j] = 0;
   dataSUmc_x[j] = h_sum_var->GetBinCenter(j+1);  dataSUmc_xerr[j] = 0; 
   double mc_err = 0;
   for(uint i=0; i<rootplas_size; i++) mc_err += err_AllBkg[i][j]*err_AllBkg[i][j];
   if(h_sum_var->GetBinContent(j+1)!=0){
    double rd = h_data_var->GetBinContent(j+1);
    double mc = h_sum_var->GetBinContent(j+1); 
    if(normalised){
     rd = rd*normdata;
     mc = mc*normbkg;
    }
    dataSUmc_y[j]    = rd/mc; 
    dataSUmc_yerr[j] = sqrt(pow(sqrt(rd)/mc,2) + pow((rd*sqrt(mc_err))/(mc*mc),2));
   }else{
    dataSUmc_y[j]    = -1000000; 
    dataSUmc_yerr[j] = 0;
   }
  }
  if(var=="massVis"){
   cout<<"const double sf[bin] = {";
   for(int ar=0; ar<bin[v]; ar++) cout<<dataSUmc_y[ar]<<",";
   cout<<"};"<<endl;
   cout<<"const double sferr[bin] = {";
   for(int ar=0; ar<bin[v]; ar++) cout<<dataSUmc_yerr[ar]<<",";
   cout<<"};"<<endl;
  }
  //Plot values
  TGraphErrors *dataSUmc = new TGraphErrors(bin[v], dataSUmc_x, dataSUmc_y, dataSUmc_xerr, dataSUmc_yerr);
  dataSUmc->SetTitle(0);
  //dataSUmc->SetTitleSize(10);
  dataSUmc->SetMarkerStyle(7);
  //dataSUmc->SetMarkerColor(1);
  //dataSUmc->SetLineColor(1);
  dataSUmc->GetXaxis()->SetRangeUser(inRange[v],endRange[v]);
  dataSUmc->GetXaxis()->SetTitle(vartitle.c_str()); 
  dataSUmc->GetXaxis()->SetTitleSize(0.2);
  dataSUmc->GetYaxis()->SetTitle("Data/MC");
  dataSUmc->GetYaxis()->SetLabelSize(0.075);
  dataSUmc->GetYaxis()->SetTitleSize(0.15);
  dataSUmc->GetYaxis()->SetTitleOffset(0.35);
  dataSUmc->SetMinimum(5);  //0.5
  dataSUmc->SetMaximum(2);  //1.5
  dataSUmc->GetXaxis()->SetRangeUser(inRange[v],endRange[v]);
  dataSUmc->GetXaxis()->SetLimits(inRange[v],endRange[v]);
  dataSUmc->Draw("APZ");
  dataSUmc->GetXaxis()->SetRangeUser(inRange[v],endRange[v]);
  dataSUmc->GetXaxis()->SetLimits(inRange[v],endRange[v]);
  TLine* line = new TLine(inRange[v],1,endRange[v],1);
  line->SetLineColor(kRed);
  line->SetLineWidth(2);
  line->Draw("same");
  //Top plots
  c1->cd();
  TPad *c1_2 = new TPad("c1_2", "newpad",0.01,0.33,0.99,0.99);
  if(logYscale[v]==1) c1_2->SetLogy();
  c1_2->Draw();
  c1_2->cd();
  c1_2->SetTopMargin(0.065);
  c1_2->SetBottomMargin(0.1);
  c1_2->SetRightMargin(0.01);
  c1_2->SetLeftMargin(0.125);
  //c1_2->SetFillStyle(0);
 }
 //Set maximum Y value
 if(logYscale[v]==0){
  h_data_var->SetMaximum(highestbinval+0.25*highestbinval);
  //h_data_var->SetMaximum(40);//(28);
  if(normalised) h_data_var->SetMinimum(0.0001);
 }else{
  h_data_var->SetMaximum((highestbinval+0.25*highestbinval)*10);
  if(normalised) h_data_var->SetMinimum(0.0001);
 }
 //Data and bkg
 TGaxis::SetMaxDigits(4);
 if(!show_ratio){
  h_data_var->SetTitleOffset(1.02,"x");
  h_data_var->GetXaxis()->SetTitle(vartitle.c_str());
 }
 h_data_var->GetYaxis()->SetTitle("#scale[0.8]{Events/bin}");
 //if(show_title)  h_data_var->SetTitle("#scale[0.90]{CMS preliminary,   #sqrt{s} = 13 TeV, L =  XXX fb^{-1}}");
 if(h_data_var->GetEntries()==0) gStyle->SetOptStat(0);
 h_data_var->SetBinErrorOption(TH1::kPoisson);
 h_data_var2->SetBinErrorOption(TH1::kPoisson);


 //for(int ibin=1; ibin<=bin[v]; ibin++){ 
 // double err_low = h_data_var->GetBinErrorLow(ibin);
 // double err_up = h1->GetBinErrorUp(ibin);
// }
 h_data_var->Draw("P");
 //hstack->Draw("textsame");
 hstack->Draw("histsame");
 h_data_var2->SetMarkerStyle(1);
 if(!normalised) h_data_var2->Draw("E0same");
 else            h_data_var2->Draw("Esame");
 h_data_var->Draw("Psame");
 //h_data_var->Draw("text45same");
 gPad->RedrawAxis();
 h_sig->SetLineWidth(2);
 h_sig->SetLineColor(kBlack);
 if(h_sig->Integral()!=0) h_sig->Draw("histsame");
 h_sig2->SetLineWidth(2);
 h_sig2->SetLineStyle(2); //Dashed
 h_sig2->SetLineColor(kBlack);
 if(h_sig2->Integral()!=0) h_sig2->Draw("histsame");
 char sig_entries_c[1000]; float sig_entries_f = h_sig->Integral();
 sprintf(sig_entries_c,"%.1f",sig_entries_f);
 //string sig_leg = "#scale[0.75]{#Lambda 5, M 2.5 [TeV] ("+(string)sig_entries_c+")}";
 string sig_leg = "#scale[0.75]{#Lambda 13, M 2 [TeV]}";
 char sig2_entries_c[1000]; float sig2_entries_f = h_sig2->Integral();
 sprintf(sig2_entries_c,"%.1f",sig2_entries_f);
// string sig2_leg = "#scale[0.75]{#Lambda 5, M 3.5 [TeV] ("+(string)sig2_entries_c+")}";
 string sig2_leg = "#scale[0.75]{#Lambda 13, M 1 [TeV]}";
 char data_entries_c[1000]; int data_entries_f = h_data_var->Integral();
 sprintf(data_entries_c,"%.1i",data_entries_f);
 //string data_leg = "#scale[0.75]{data ("+(string)data_entries_c+")}";
 string data_leg = "#scale[0.75]{Data}";
 //if(!(h_data_var->GetEntries()==0)) leg->AddEntry(h_data_var,data_leg.c_str(),"P");
 //if(!(h_sig->GetEntries()==0))      leg->AddEntry(h_sig,sig_leg.c_str(),"L");
 //if(!(h_sig2->GetEntries()==0))     leg->AddEntry(h_sig2,sig2_leg.c_str(),"L");
 //leg->Draw();
 //Bkg err
 double all_bkg_statErr_x[bin[v]]; double all_bkg_statErr_y[bin[v]]; double all_bkg_statErr_xerr[bin[v]]; double all_bkg_statErr_yerr[bin[v]];
 for(int j=0; j<bin[v]; j++){
  all_bkg_statErr_x[j] = 0; all_bkg_statErr_y[j] = 0; all_bkg_statErr_xerr[j] = 0; all_bkg_statErr_yerr[j] = 0;
  all_bkg_statErr_x[j] = h_sum_var->GetBinCenter(j+1);
  if(var=="M_leplepBjet" && doasym){
   all_bkg_statErr_xerr[j] = (asymbin[j+1]-asymbin[j])*0.5;
  }else{
   all_bkg_statErr_xerr[j] = ((endRange[v]-inRange[v])/bin[v])*0.5;
  }
  for(uint i=0; i<rootplas_size; i++) all_bkg_statErr_yerr[j] += err_AllBkg[i][j]*err_AllBkg[i][j];
  all_bkg_statErr_y[j] = h_sum_var->GetBinContent(j+1); all_bkg_statErr_yerr[j] = sqrt(all_bkg_statErr_yerr[j]);
 }
 TGraphErrors *all_bkg_statErr = new TGraphErrors(bin[v], all_bkg_statErr_x, all_bkg_statErr_y, all_bkg_statErr_xerr, all_bkg_statErr_yerr);
 all_bkg_statErr->SetLineColor(kGray+1);
 all_bkg_statErr->SetFillStyle(3002);
 all_bkg_statErr->SetFillColor(kGray+1);
 all_bkg_statErr->Draw("E2same");

 if(!(h_data_var->GetEntries()==0)) leg->AddEntry(h_data_var,data_leg.c_str(),"EP");
 if(!(h_sig->GetEntries()==0))      leg->AddEntry(h_sig,sig_leg.c_str(),"L");
 if(!(h_sig2->GetEntries()==0))     leg->AddEntry(h_sig2,sig2_leg.c_str(),"L");
 leg->AddEntry(h_TTtW,"#scale[0.75]{t#bar{t}+tW}","F");
 leg->AddEntry(h_DY,"#scale[0.75]{DY}","F");
 leg->AddEntry(h_Other,"#scale[0.75]{Other}","F");
 leg->AddEntry(all_bkg_statErr,"#scale[0.75]{Bkg stat. uncert.}","F");
 leg->Draw();

 //CMS_lumi( c1, 0, 11 ); uncomment for writing "CMS" on top left of inner box

}
void draw_lines(double x1, double y1, double x2, double y2){
 TLine* line1 = new TLine(x1,y1,x2,y2);
 line1->SetLineColor(kRed);
 line1->SetLineWidth(3);
 line1->Draw("same");
}
int get_col(string name){
 int col;
 if(name=="Other")    col = -10;  //Non main bkg need a different color type
 //if(name=="WW")   col = -10;
 //if(name=="WZ") col = -9;   //Possibly with soft intensity
 //if(name=="WJets")    col = -8;
 //if(name=="ZZ")    col = -7;
 //if(name=="QCD")   col = -6;
 if(name=="DY") col = -5; //For main bkg uses same color type with different numbers
 if(name=="TTtW") col = -8;  //darker for lower bkg (that should come first) 
 if(name=="tW")  col = -6;  //softer for higher bkg (that should come after)
 return col;
}
double get_highestbinval(TH1F* h_data_var, TH1F* h_sig, TH1F* h_sig2, THStack* hstack, int v){
 double highestbinval = 0;
 for(int h=1; h<=h_data_var->GetNbinsX(); h++) if(h_data_var->GetBinContent(h)>highestbinval) highestbinval=h_data_var->GetBinContent(h);
 for(int h=1; h<=h_sig->GetNbinsX(); h++) if(h_sig->GetBinContent(h)>highestbinval) highestbinval=h_sig->GetBinContent(h);
 for(int h=1; h<=h_sig2->GetNbinsX(); h++) if(h_sig2->GetBinContent(h)>highestbinval) highestbinval=h_sig2->GetBinContent(h);
 if(hstack->GetMaximum()>highestbinval) highestbinval=hstack->GetMaximum();
 return highestbinval;
}
void save_canvas(TCanvas* c1, string var){
 string namefile = var+selection+".pdf";
 if(save_plots)  c1->SaveAs(namefile.c_str());
}
/////
//   Get legends and histos
/////
TLegend* get_legend(){
 TLegend *leg = new TLegend(0.19, 0.52, 0.40, 0.9);
 leg->SetHeader("");
 leg->SetBorderSize(0);
 leg->SetTextSize(0.05);
 return leg;
}
TH1F* get_th1f(string var, int v){
 TH1F *th1f;
 if(var=="M_leplepBjet" && doasym) th1f = new TH1F("","",bin[v],asymbin);
 else                         th1f = new TH1F("","",bin[v],inRange[v],endRange[v]);
 return th1f;
}
TH1F* get_datath1f(string var, string title, int v){
 TH1F *datath1f = get_th1f(var, v);
 datath1f->SetTitle(0); datath1f->SetMarkerStyle(8); datath1f->SetMarkerColor(1); datath1f->SetLineColor(1);
 datath1f->GetXaxis()->SetRangeUser(inRange[v],endRange[v]);
 datath1f->GetXaxis()->SetLimits(inRange[v],endRange[v]);
 //if(!show_ratio) datath1f->GetXaxis()->SetTitle(title.c_str());
 //char bin_size_c[col_size]; float bin_size_f = ((endRange[v]-inRange[v])/bin[v]); sprintf(bin_size_c,"%.2f",bin_size_f); 
 //string titleYaxis;
 //if(name=="massVis" && doasym) titleYaxis = "Events";
 //else                          titleYaxis = "Events/"+(string) bin_size_c;
 //datath1f->GetYaxis()->SetTitle(titleYaxis.c_str());
 //TGaxis::SetMaxDigits(4);
 if(show_title) datath1f->SetTitle("#scale[0.90]{CMS preliminary,   #sqrt{s} = 13 TeV, L = 35.5 fb^{-1}}");
 return datath1f;
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
 //For the frame:
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
 //tdrStyle->SetStatStyle(Style_t style = 1001);
 //Margins:
 tdrStyle->SetPadTopMargin(0.095);
 tdrStyle->SetPadBottomMargin(0.125);
 tdrStyle->SetPadLeftMargin(0.14);
 tdrStyle->SetPadRightMargin(0.1);
 //For the Global title:
 //tdrStyle->SetOptTitle(0);
 tdrStyle->SetTitleFont(42);
 tdrStyle->SetTitleColor(1);
 tdrStyle->SetTitleTextColor(1);
 tdrStyle->SetTitleFillColor(10);
 tdrStyle->SetTitleFontSize(0.05);
 tdrStyle->SetTitleH(0.045); // Set the height of the title box
 //tdrStyle->SetTitleW(0); // Set the width of the title box
 tdrStyle->SetTitleX(0.20); // Set the position of the title box
 tdrStyle->SetTitleY(1.0); // Set the position of the title box
 //tdrStyle->SetTitleStyle(Style_t style = 1001);
 tdrStyle->SetTitleBorderSize(0);
 //For the axis titles:
 tdrStyle->SetTitleColor(1, "XYZ");
 tdrStyle->SetTitleFont(42, "XYZ");
 tdrStyle->SetTitleSize(0.06, "XYZ");
 //tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
 //tdrStyle->SetTitleYSize(Float_t size = 0.02);
 tdrStyle->SetTitleXOffset(0.9);
 tdrStyle->SetTitleYOffset(1.0);
 //tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset
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
 //tdrStyle->SetTimeOffset(Double_t toffset);
 //tdrStyle->SetHistMinimumZero(kTRUE);
 tdrStyle->cd();
}
 //if(logYscale[v]==1 && !normalised){h_data_var->SetMaximum((highestbinval+0.25*highestbinval)*10);}else if(logYscale[v]==1 && normalised)
 //{h_data_var->SetMaximum(2);}
 //if(logYscale[v]==1 && normalised){h_data_var->SetMinimum(0.0001);}else if(logYscale[v]==1 && !normalised){h_data_var->SetMinimum(0.01);}else{h_data_var->SetMinimum(0);}
 //if(logYscale[v]==1){hstack->SetMaximum((highestbinval+0.25*highestbinval)*10);}else{hstack->SetMaximum(highestbinval+0.25*highestbinval);}
 //if(logYscale[v]==1){hstack->SetMinimum(0.1);}else{hstack->SetMinimum(0);}
