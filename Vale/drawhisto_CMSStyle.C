#include "tdrstyle.C"
#include "CMS_lumi.C"
#include "TH1.h"
#include "TH1F.h"



TCanvas* c1(int iPeriod, int iPos);
void drawhisto_CMSStyle()
{
 setTDRStyle();

 writeExtraText = false;       // if extra text
 extraText  = "Simulation";
 lumi_sqrtS = "13 TeV";
 int iPeriod = 5;
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

 TString canvName = "MllJ_CMSStyle";

 TCanvas* canv = new TCanvas(canvName,canvName,50,100,W,H);
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

//  TPad *c1_2 = new TPad("c1_2", "newpad",0.01,0.07,0.99,0.99);
//h->Draw();


{ 
int color2 = kGreen+1, color3 = kRed-7, color4 = kAzure-4, color5=kOrange;
//int color2 =6, color3 =8, color4 = 7, color5 = 2, color6 = 4, color7 = 8, color8 = 28;

TH1F * gHisto ;
THStack *hs = new THStack("hs","");

TFile *f00_ = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2016-OldBinning/CR_TTtW_DY_2016_syst.root");  
TFile *f01_ = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2016-OldBinning/CR_TTtW_Other_2016_syst.root");
TFile *f02_ = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2016-OldBinning/CR_TTtW_TTtW_2016_syst.root");

TFile *f00 = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2016-OldBinning/CR_TTtW_data_ele_2016.root");
//TFile *f01 = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2016-OldBinning/SR_plots_gen_mumujj_L13_M1000_2016.root");
//TFile *f02 = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2016-OldBinning/SR_plots_gen_mumujj_L13_M2000_2016.root");
//TFile *f03 = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2016-OldBinning/SR_plots_gen_mumujj_L13_M5000_2016.root");
//TFile *f04 = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2016-OldBinning/SR_plots_gen_mumujj_L13_M8000_2016.root");

int bin = 1;

//TString name="deltaRjj";
TString name="M_leplepJ";

canvName = name;
TH1F *da_= (TH1F*) f00_->Get(name);
TH1F *da1_= (TH1F*) f01_->Get(name);
TH1F *da2_= (TH1F*) f02_->Get(name);

TH1F *da= (TH1F*) f00->Get(name);
//TH1F *da1= (TH1F*) f01->Get(name);
//TH1F *da2= (TH1F*) f02->Get(name);
//TH1F *da3= (TH1F*) f03->Get(name);
//TH1F *da4= (TH1F*) f04->Get(name);


TH1F *d_=(TH1F*) da_->Clone();
TH1F *d1_=(TH1F*) da1_->Clone();
TH1F *d2_=(TH1F*) da2_->Clone();

TH1F *d=(TH1F*) da->Clone();
//TH1F *d1=(TH1F*) da1->Clone();
//TH1F *d2=(TH1F*) da2->Clone();
//TH1F *d3=(TH1F*) da3->Clone();
//TH1F *d4=(TH1F*) da4->Clone();

int nbin = d->GetNbinsX();

//d->SetFillColor(color2);
d_->SetFillColor(color2);
d_->SetLineColor(color2);
hs->Add(d_);
//d1->SetFillColor(color3);
d1_->SetFillColor(color3);
d1_->SetLineColor(color3);
hs->Add(d1_);
//d2->SetFillColor(color4);
d2_->SetFillColor(color4);
d2_->SetLineColor(color4);
hs->Add(d2_);

d->SetLineColor(kBlack);
d->SetMarkerStyle(2);
//d->Rebin(bin);
//d->SetLineStyle(3);
d->SetLineWidth(2);
/*d1->SetLineColor(kBlue);
d1->Rebin(bin);
d1->SetLineStyle(4);
d1->SetLineWidth(2);
d2->SetLineColor(kRed);
d2->Rebin(bin);
d2->SetLineWidth(2);
d2->SetLineStyle(5);
d3->Rebin(bin);
d3->SetLineColor(kBlack);
d3->SetLineStyle(1);
d3->SetLineColor(kBlack);
d3->SetLineWidth(2);
d3->SetMarkerColor(kBlack);
d3->SetMarkerStyle(22);
d4->Rebin(bin);
d4->SetLineStyle(1);
d4->SetLineWidth(2);
d4->SetLineColor(kBlue);*/


//d->GetXaxis()->SetRangeUser(0,5);
//d1->GetXaxis()->SetRangeUser(0,5);
//d2->GetXaxis()->SetRangeUser(0,5);
//d3->GetXaxis()->SetRangeUser(0,5);
//d4->GetXaxis()->SetRangeUser(0,5);
//d_->GetXaxis()->SetRangeUser(0,5);
//d1_->GetXaxis()->SetRangeUser(0,5);
//d2_->GetXaxis()->SetRangeUser(0,5);

canv->cd();

TH1F *h3 = (TH1F*)hs->GetHistogram();

//c1_2->SetBottomMargin(0.02);//(0.1);//(0.);
c1_2->SetBottomMargin(0.1);
c1_2->SetTopMargin(0.07);
c1_2->SetRightMargin(0.1);
c1_2->Draw();
c1_2->cd();
gPad->SetLogx();
//gPad->SetLogy();
/*d3->GetXaxis()->SetTitleOffset(1.5);
d3->GetYaxis()->SetTitleOffset(1.5); 
d3->GetYaxis()->SetTitle("Events");
d3->GetYaxis()->SetTitleSize(10);
d3->GetYaxis()->SetLabelSize(25);
d3->GetXaxis()->SetLabelSize(25);
d3->GetYaxis()->SetLabelFont(43);
d3->GetYaxis()->SetTitleSize(30);
d3->GetXaxis()->SetTitleSize(30);
d3->GetYaxis()->SetTitleFont(43);*/

TLine* line1 = new TLine(80,0,80,10500);
TLine* line2 = new TLine(100,0,10,3500);
line1->SetLineColor(kBlack);
line1->SetLineWidth(2);
line2->SetLineColor(kBlack);
line2->SetLineWidth(2);

int v = 1;
v = nbin/bin;
double mc_tot[v], mc_err[v], mc_x[v], mc_ex[v];
double bincontent_d3 = 0, bincontent_d4 = 0;

for(int j=0; j<=v; j++){
 mc_tot[j] = d_->GetBinContent(j) + d1_->GetBinContent(j) + d2_->GetBinContent(j);
 mc_err[j] = sqrt(pow(d_->GetBinError(j),2) + pow(d1_->GetBinError(j),2) + pow(d2_->GetBinError(j),2));
 mc_x[j] = d_->GetBinCenter(j);
 mc_ex[j] = d_->GetBinWidth(j)/2;
}

TGraph* hs_err = new TGraphErrors(v,mc_x,mc_tot,mc_ex,mc_err);
hs_err->SetLineColor(kGray+3);
hs_err->SetFillStyle(3004);
hs_err->SetFillColor(kGray+3);

d1_->GetXaxis()->SetTitle("M_{e #mu J}");
d1_->GetXaxis()->SetLabelSize(25);
d1_->GetXaxis()->SetLabelFont(43);
d1_->GetXaxis()->SetTitleSize(30);
d1_->GetXaxis()->SetTitleFont(43);
d1_->GetXaxis()->SetTitleOffset(1.);


/*d->Sumw2();
   double w = d->Integral();//Integral();//GetEntries();
   d->Scale(1./w);
d1->Sumw2();
   double w1 = d1->Integral();//Integral();//GetEntries();
   d1->Scale(1./w1);
d2->Sumw2();
   double w2 = d2->Integral();//Integral();//GetEntries();
   d2->Scale(1./w2);*/

/*d3->Sumw2();
   double w3 = d3->Integral();//Integral();//GetEntries();
   d3->Scale(1./w3);
 d4->Sumw2();
   double w4 = d4->Integral();//Integral();//GetEntries();
   d4->Scale(1./w4);

d3->SetMaximum(0.8);

d3->Draw("histo");*/
hs->Draw("histo");
d->Draw("APsame");
//d1->Draw("histosame");
//d2->Draw("histosame");
//d3->Draw("histosame");
//d4->Draw("histosame");

hs_err->Draw("E2same");
line1->Draw("same");
line2->Draw("same");


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
 dataSUmc_x[j] = d->GetBinCenter(j);  dataSUmc_xerr[j] = 0;

 mc_tot[j] = d_->GetBinContent(j) + d1_->GetBinContent(j) + d2_->GetBinContent(j); 
 mc_err[j] = sqrt(pow(d_->GetBinError(j),2) + pow(d1_->GetBinError(j),2) + pow(d2_->GetBinError(j),2)); 
 if (d->GetBinContent(j) != 0 && mc_tot[j] != 0){   
  rd = d->GetBinContent(j);
  mc = mc_tot[j];
  rd_e = d->GetBinError(j);
  mc_e = mc_err[j];
  dataSUmc_y[j] = rd/mc;
  dataSUmc_yerr[j] = (1./mc)*sqrt(pow(rd_e,2)+(pow(rd,2)/pow(mc,2))*pow(mc_e,2));
 }
}

TGraphErrors *dataSUmc = new TGraphErrors(v, dataSUmc_x, dataSUmc_y, dataSUmc_xerr, dataSUmc_yerr);

dataSUmc->GetXaxis()->SetLimits(0,10);
dataSUmc->Draw("APZ");
dataSUmc->SetTitle(0);
dataSUmc->SetMarkerStyle(7); 
dataSUmc->GetYaxis()->SetNdivisions(5,5,1);

dataSUmc->GetXaxis()->SetTitle("M_{e #mu J}");
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


dataSUmc->SetMinimum(0.4);  //0.5
dataSUmc->SetMaximum(1.6);  //1.5
TLine* line = new TLine(0,1,10,1);
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

    float x1_l = 0.9;
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
/*
    TGraph* gr_l = new TGraphErrors(1, x_l, y_l, ex_l, ey_l );

    gStyle->SetEndErrorSize(0);
    gr_l->SetMarkerSize(0.9);
    gr_l->Draw("0P");
*/
    latex.SetTextFont(42);
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);
    latex.SetTextSize(0.13);
    latex.SetTextAlign(12);

    float xx_ = x_l[0];
    float yy_ = y_l[0];
    // latex.DrawLatex(xx_+1.*bwx_,yy_,"Data");

    float distance = .45;
/*
    TLine line_;
    line_.SetLineStyle(3);
    line_.SetLineColor(kBlack);
    line_.SetLineWidth(2);
    line_.DrawLine(xx_-bwx_/2, yy_, xx_+bwx_/2, yy_);
    latex.DrawLatex(xx_+1.*bwx_,yy_, "M500");

    yy_ = yy_-bwy_*distance;
    line_.SetLineStyle(4);
    line_.SetLineColor(kBlue);
    line_.SetLineWidth(2);
    line_.DrawLine(xx_-bwx_/2, yy_, xx_+bwx_/2, yy_);
    latex.DrawLatex(xx_+1.*bwx_,yy_, "M1000");

    yy_ = yy_-bwy_*distance;
    line_.SetLineStyle(5);
    line_.SetLineColor(kRed);
    line_.SetLineWidth(2);
    line_.DrawLine(xx_-bwx_/2, yy_, xx_+bwx_/2, yy_);
    latex.DrawLatex(xx_+1.*bwx_,yy_, "M2000");

    yy_ = yy_-bwy_*distance;
    line_.SetLineStyle(1);
    line_.SetLineColor(kBlack);
    line_.SetLineWidth(2);
    line_.DrawLine(xx_-bwx_/2, yy_, xx_+bwx_/2, yy_);
    latex.DrawLatex(xx_+1.*bwx_,yy_, "M5000");

    yy_ = yy_-bwy_*distance;
    line_.SetLineStyle(1);
    line_.SetLineColor(kBlue);
    line_.SetLineWidth(2);
    line_.DrawLine(xx_-bwx_/2, yy_, xx_+bwx_/2, yy_);
    latex.DrawLatex(xx_+1.*bwx_,yy_, "M8000");*/

    yy_ = yy_-bwy_*distance;
    TBox  box_;
    box_.SetFillColor( color2 );
    box_.DrawBox(xx_-bwx_/2, yy_-0.04, xx_+bwx_/2, yy_+0.04);
    latex.DrawLatex(xx_+1.*bwx_,yy_, "DY");

    yy_ = yy_-bwy_*distance;

    box_.SetFillColor( color3 );
    box_.DrawBox(xx_-bwx_/2, yy_-0.04, xx_+bwx_/2, yy_+0.04);
    latex.DrawLatex(xx_+1.*bwx_,yy_, "Other");

    yy_ = yy_-bwy_*distance;

    box_.SetFillColor( color4 );
    box_.DrawBox(xx_-bwx_/2, yy_-0.04, xx_+bwx_/2, yy_+0.04);
    latex.DrawLatex(xx_+1.*bwx_,yy_, "t#bar{t}+tW");

    yy_ = yy_-bwy_*distance;

    box_.SetFillStyle(3004);
    box_.SetFillColor(kGray+3);
    box_.SetLineColor(kGray+3);
   // box_.DrawBox(xx_-bwx_/2, yy_-0.04, xx_+bwx_/2, yy_+0.04);
   // latex.DrawLatex(xx_+1.*bwx_,yy_, "Bkg stat. uncert.");
   

 canv->cd();
}
  CMS_lumi( c1_2, iPeriod, iPos, 1.3 );
  c1_2->cd();
//  canv->Print("Immagini/"+canvName+".pdf");
//  canv->Print("Immagini/"+canvName+".png");
  canv->Print("//eos/user/m/mpresill/www/HN/"+canvName+".png");
  canv->Print("//eos/user/m/mpresill/www/HN/"+canvName+".pdf");
//  canv->Print("/eos/home-v/vmariani/www/HN/CR_DY_2016/"+canvName+"_2016.png");
//  canv->Print("/eos/home-v/vmariani/www/HN/CR_DY_2016/pdf/"+canvName+"_2016.pdf");

 return canv;

}
