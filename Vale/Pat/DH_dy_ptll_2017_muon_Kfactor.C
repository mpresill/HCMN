#include "tdrstyle.C"
#include "CMS_lumi.C"
#include "TH1.h"
#include "TH1F.h"


TCanvas* c1(int iPeriod, int iPos);
void DH_dy_ptll_2017_muon_Kfactor()
{
 setTDRStyle();

 writeExtraText = false;       // if extra text
 extraText  = "Simulation";
 lumi_sqrtS = "13 TeV";
//========================================
//REPLACE HERE 0 to choose the period 
//========================================
 int iPeriod = 5; //periodo 4=2016, periodo 5=2017, periodo 6=2018
 c1( iPeriod, 11 );
}

TCanvas* c1(int iPeriod, int iPos){

 int W = 800;
 int H = 800;

 int H_ref = 800;
 int W_ref = 800;

 float T = 0.08*H_ref;
 float B = 0.08*H_ref;
 float L = 0.04*W_ref;
 float R = 0.04*W_ref;

 TString canvName = "Mll_CMSStyle";

 TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
 canv->SetFillColor(0);
 canv->SetBorderMode(0);
 canv->SetFrameFillStyle(0);
 canv->SetFrameBorderMode(0);
 canv->SetLeftMargin( L/W*0.8 );
 canv->SetRightMargin( R/W*1.5 );
 canv->SetTopMargin( T/H );
 canv->SetBottomMargin( B/H*2);
 canv->SetTickx(0);
 canv->SetTicky(0);

 TPad *c1_2 = new TPad("c1_2", "newpad",0.01,0.32,0.99,0.99);
 TPad *c1_1 = new TPad("c1_1", "newpad",0.01,0.01,0.99,0.32);


{ 
int color2 = kGreen+1, color3 = kRed-7, color4 = kAzure-4, color5 = kOrange;

TH1F * gHisto ;
THStack *hs = new THStack("hs","");

//REPLACE HERE 1  - to choose the path 
//===================================================
//file for 2016 
//TFile *f00_ = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2017-OldBinning/CR_DY_DY_2016.root");
//TFile *f01_ = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2017-OldBinning/CR_DY_TTtW_2016.root");
//TFile *f02_ = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2017-OldBinning/CR_DY_Other_2016.root");
 
//TFile *f00 = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2017-OldBinning/CR_DY_data_ele_2016.root");
////TFile *f00 = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2017-OldBinning/CR_DY_data_mu_2016.root");
//====================================================
//files for 2017 
//TFile *f00_ = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2017-OldBinning/CR_DY_DY_k_qcdewk_2017.root");
TFile *f00_ = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2017-OldBinning/CR_DY_DY_Kewkqcd_2017.root");
TFile *f01_ = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2017-OldBinning/CR_DY_TTtW_2017.root");
TFile *f02_ = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2017-OldBinning/CR_DY_Other_2017.root");
 
//TFile *f00 = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2017-OldBinning/CR_DY_data_ele_2017.root");
TFile *f00 = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2017-OldBinning/CR_DY_data_mu_2017.root");
//=============================
//files for 2018 
//TFile *f00_ = new TFile("DY/CR_DY_DY_2018.root");
//TFile *f00_ = new TFile("/Users/patriziaazzi/Work/CMS/HCMN/newhistos/CR_DY_DY_2018.root");
//TFile *f01_ = new TFile("/Users/patriziaazzi/Work/CMS/HCMN/newhistos/CR_DY_TTtW_2018.root");
//TFile *f02_ = new TFile("/Users/patriziaazzi/Work/CMS/HCMN/newhistos/CR_DY_Other_2018.root");
//here change mu or ele 
//TFile *f00 = new TFile("/Users/patriziaazzi/Work/CMS/HCMN/newhistos/CR_DY_data_ele_2018.root");
//TFile *f00 = new TFile("/Users/patriziaazzi/Work/CMS/HCMN/newhistos/CR_DY_data_mu_2018.root");


//==================================================
//REPLACE HERE 2 - to change the binning 
int bin=4;  //rebinning for ptee -->>> Need to fix ratio below
//TString name="pt_ee";   // this is to check the effect of the new weight on the DY MC
TString name="pt_mumu_Z";   // this is to check the effect of the new weight on the DY MC

TString nameTop="TTtW_ll";
TString nameDY="DY_ll";
TString nameOther="Other_ll";
canvName = name;
TH1F *da_= (TH1F*) f00_->Get(name);
TH1F *da1_= (TH1F*) f01_->Get(name);
TH1F *da2_= (TH1F*) f02_->Get(name);
TH1F *da= (TH1F*) f00->Get(name);

TH1F *d_=(TH1F*) da_->Clone();
TH1F *d1_=(TH1F*) da1_->Clone();
TH1F *d2_=(TH1F*) da2_->Clone();

TH1F *d=(TH1F*) da->Clone();

int nbin = d->GetNbinsX();

//d->SetFillColor(color2);
d_->SetFillColor(color2);
d_->SetLineColor(color2);
d_->Rebin(bin);
hs->Add(d_);
//d1->SetFillColor(color3);
d1_->SetFillColor(color3);
d1_->SetLineColor(color3);
d1_->Rebin(bin);
hs->Add(d1_);
//d2->SetFillColor(color4);
d2_->SetFillColor(color4);
d2_->SetLineColor(color4);
d2_->Rebin(bin);
hs->Add(d2_);

d->SetMarkerColor(kBlack);
d->SetLineColor(kBlack);
d->SetMarkerStyle(8);
d->SetMarkerSize(1);
d->Rebin(bin);

//============================================
//REPLACE HERE 4 -- to change the maximum (if needed) 
//============================================
d->SetMaximum(4000); 
//d->GetYaxis()->SetRangeUser(0,5000); //for 2018
d->GetYaxis()->SetRangeUser(0,1.8*(d->GetBinContent(d->GetMaximumBin())));
d->SetMinimum(0.5);
canv->cd();

TLine* line1 = new TLine(80,0,80,4500);
TLine* line2 = new TLine(50,80,130,4500);
line1->SetLineColor(kBlack);
line1->SetLineWidth(2);
line2->SetLineColor(kBlack);
line2->SetLineWidth(2);

d->GetXaxis()->SetTitleOffset(1.5);
d->GetYaxis()->SetTitleOffset(1.5);
d->GetYaxis()->SetTitle("Events");
d->GetYaxis()->SetTitleSize(10);
d->GetYaxis()->SetLabelSize(25);
d->GetXaxis()->SetLabelSize(25);
d->GetYaxis()->SetLabelFont(43);
d->GetYaxis()->SetTitleSize(30);
d->GetXaxis()->SetTitleSize(30);
d->GetYaxis()->SetTitleFont(43);

gPad->SetLogy();
gPad->RedrawAxis();
//gPad->SetLogx();

c1_2->SetBottomMargin(0.);//(0.1);//(0.);
c1_2->SetTopMargin(0.07);
c1_2->SetRightMargin(0.1);
c1_2->Draw();
c1_2->cd();
//gPad->SetLogy();
//gPad->RedrawAxis();
//gPad->SetLogx();

int v = 0;
v = nbin/bin;

double mc_tot[v], mc_err[v], mc_x[v], mc_ex[v];

for(int j=0; j<=v; j++){
 mc_tot[j] = d_->GetBinContent(j+1) + d1_->GetBinContent(j+1) + d2_->GetBinContent(j+1);
 mc_err[j] = sqrt(pow(d_->GetBinError(j+1),2) + pow(d1_->GetBinError(j+1),2) + pow(d2_->GetBinError(j+1),2));
 mc_x[j] = d_->GetBinCenter(j+1);
 mc_ex[j] = d_->GetBinWidth(j+1)/2;
}

TGraph* hs_err = new TGraphErrors(v,mc_x,mc_tot,mc_ex,mc_err);
hs_err->SetLineColor(kGray+3);
hs_err->SetFillStyle(3004);
hs_err->SetFillColor(kGray+3);

d->GetXaxis()->SetLabelSize(25);
d->GetXaxis()->SetLabelFont(43);
d->GetXaxis()->SetTitleSize(30);
d->GetXaxis()->SetTitleFont(43);
d->GetXaxis()->SetTitleOffset(1.);


d->Draw("PE");
hs->Draw("histosame");
hs_err->Draw("E2same");
d->Draw("PEsame");

canv->cd();
c1_1->SetTopMargin(0);
c1_1->SetBottomMargin(0.27);
c1_1->SetRightMargin(0.1);
c1_1->Draw();
c1_1->cd();


double rd = 0, mc = 0, rd_e = 0, mc_e = 0;
double dataSUmc_x[v]; double dataSUmc_y[v]; double dataSUmc_xerr[v]; double dataSUmc_yerr[v];

for(int j=0; j<v; j++){
 dataSUmc_x[j] = 0; dataSUmc_y[j] = 0; dataSUmc_xerr[j] = 0; dataSUmc_yerr[j] = 0;
 dataSUmc_x[j] = d_->GetBinCenter(j+1);  dataSUmc_xerr[j] = 0;

 mc_tot[j] = d_->GetBinContent(j+1) + d1_->GetBinContent(j+1) + d2_->GetBinContent(j+1); 
 mc_err[j] = sqrt(pow(d_->GetBinError(j+1),2) + pow(d2_->GetBinError(j+1),2) + pow(d2_->GetBinError(j+1),2)) ;
 if (d->GetBinContent(j+1) != 0 && mc_tot[j] != 0){   
  rd = d->GetBinContent(j+1);
  mc = mc_tot[j];
  rd_e = d->GetBinError(j+1);
  mc_e = mc_err[j];
  dataSUmc_y[j] = rd/mc;
  dataSUmc_yerr[j] = (1./mc)*sqrt(pow(rd_e,2)+(pow(rd,2)/pow(mc,2))*pow(mc_e,2));
 }
}

TGraphErrors *dataSUmc = new TGraphErrors(v, dataSUmc_x, dataSUmc_y, dataSUmc_xerr, dataSUmc_yerr);
//===========================================

dataSUmc->GetXaxis()->SetLimits(0,1000); //this is for the PT(ll)

dataSUmc->Draw("APZ");
dataSUmc->SetTitle(0);
dataSUmc->SetMarkerStyle(8); 
dataSUmc->GetYaxis()->SetNdivisions(5,5,1);

dataSUmc->GetXaxis()->SetTitle("Pt(#mu #mu) [GeV]");
dataSUmc->GetXaxis()->SetLabelSize(25);
dataSUmc->GetXaxis()->SetLabelFont(43);
dataSUmc->GetXaxis()->SetTitleSize(30);
dataSUmc->GetXaxis()->SetTitleFont(43);
dataSUmc->GetXaxis()->SetTitleOffset(3.4);

dataSUmc->GetYaxis()->SetTitle("Data/MC");
dataSUmc->GetYaxis()->SetLabelSize(25);
dataSUmc->GetYaxis()->SetLabelFont(43);
dataSUmc->GetYaxis()->SetTitleSize(30);
dataSUmc->GetYaxis()->SetTitleFont(43);
dataSUmc->GetYaxis()->SetTitleOffset(1.5);

//REPLACE HERE FOR THE LINE
dataSUmc->SetMinimum(0.4);  //0.5
dataSUmc->SetMaximum(1.6);  //1.5
TLine* line = new TLine(0,1,1000,1);     //per Pt(ll) larghezza linea rossa (specificare x1, x2)
line->SetLineColor(kRed);
line->SetLineWidth(2);
line->Draw("same");
  
}
{
  int color2 = kGreen+1, color3 = kRed-7, color4 = kAzure-4, color5=kOrange;

    canv->cd();
    TLatex latex;
    TLatex latex2;

    int n_ = 2;

    float x1_l = 0.95; //0.85 //0.55
    float y1_l = 0.95;

    float dx_l = 0.35;
    float dy_l = 0.35;//0.25;
    float x0_l = x1_l-dx_l;
    float y0_l = y1_l-dy_l;
    TPad* legend = new TPad("legend_0","legend_0",x0_l,y0_l,x1_l, y1_l);
    legend->SetFillStyle(4000);
    legend->Draw();
    legend->cd();

    float ar_l = dy_l/dx_l;

    float x_l[1];
    float ex_l[1];
    float y_l[1];
    float ey_l[1];
    float gap_ = 1./(n_+1)*0.5;

    float bwx_ = 0.1;
    float bwy_ = gap_/0.7;

    x_l[0] = 1.01*bwx_;
    y_l[0] = (1-gap_);
    ex_l[0] = 0.02;
    ey_l[0] = 0.03/ar_l;

    TGraph* gr_l = new TGraphErrors(1, x_l, y_l, ex_l, ey_l );

    gStyle->SetEndErrorSize(0);
    gr_l->SetMarkerSize(0.9);
    gr_l->Draw("0P");

    latex.SetTextFont(42);
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);
    latex.SetTextSize(0.13);
    latex.SetTextAlign(12);

    float xx_ = x_l[0];
    float yy_ = y_l[0];
   latex.DrawLatex(xx_+1.*bwx_,yy_,"Data");

    float distance = .45;

    yy_ = yy_-bwy_*distance;

    TBox  box_;
    box_.SetFillColor( color2 );
    box_.DrawBox(xx_-bwx_/2, yy_-0.04, xx_+bwx_/2, yy_+0.04);
    latex.DrawLatex(xx_+1.*bwx_,yy_, "DY");

    yy_ = yy_-bwy_*distance;

    box_.SetFillColor( color3 );
    box_.DrawBox(xx_-bwx_/2, yy_-0.04, xx_+bwx_/2, yy_+0.04);
    latex.DrawLatex(xx_+1.*bwx_,yy_, "t#bar{t}+tW");

    yy_ = yy_-bwy_*distance;

    box_.SetFillColor( color4 );
    box_.DrawBox(xx_-bwx_/2, yy_-0.04, xx_+bwx_/2, yy_+0.04);
    latex.DrawLatex(xx_+1.*bwx_,yy_, "Other");

    yy_ = yy_-bwy_*distance;

    box_.SetFillStyle(3004);
    box_.SetFillColor(kGray+3);
    box_.SetLineColor(kGray+3);
    box_.DrawBox(xx_-bwx_/2, yy_-0.04, xx_+bwx_/2, yy_+0.04);
    latex.DrawLatex(xx_+1.*bwx_,yy_, "Bkg stat. ");
    yy_ = yy_-bwy_*distance;
    latex.DrawLatex(xx_+1.*bwx_,yy_, " uncert.");

 canv->cd();
}
  CMS_lumi( c1_2, iPeriod, iPos, 1.3 );
  c1_2->cd();
//===========================================
//HERE REPLACE 5 
//==========================================
//2016 
 //canv->Print("Pat/"+canvName+"_2016.png");
 // canv->Print("Pat/"+canvName+"_2016.pdf");
//2017 
  canv->Print("/eos/user/m/mpresill/www/HN/DY/"+canvName+"_2017_Kewkqcd.png");
  canv->Print("/eos/user/m/mpresill/www/HN/DY/"+canvName+"_2017_Kewkqcd.pdf");
//2018 
 // canv->Print("Pat/"+canvName+"_2018.png");
  //canv->Print("Pat/"+canvName+"_2018.pdf");
 return canv;

}
