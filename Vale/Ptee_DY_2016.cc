#include "tdrstyle.C"
#include "CMS_lumi.C"
#include "TH1.h"
#include "TH1F.h"


TCanvas* c1(int iPeriod, int iPos); 
void Ptee_DY_2016()
{
setTDRStyle();
 
 writeExtraText = true;       // if extra text
 extraText  = "Preliminary";
 //lumi_sqrtS = "13 TeV";
 int iPeriod = 16;
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

 TString canvName = "Meej_CMSStyle";

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

 TPad *c1_1 = new TPad("c1_1", "newpad",0.01,0.32,0.99,0.99);
 TPad *c1_2 = new TPad("c1_2", "newpad",0.01,0.01,0.99,0.32);

int color2 = kGreen+1, color3 = kRed-7, color4 = kAzure-4, color5 = kOrange;

TH1F * gHisto ;
 

   TFile *f1 = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/2016_ALL_HOPE/25062021/SR_syst_TTtW_2016.root");
   //TFile *f2 = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/2016_ALL_HOPE/25062021/SR_syst_DY_HTincl_LO_2016.root");
   TFile *f2 = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/2016_ALL_HOPE/25062021/SR_syst_DY_HTincl_LO_Kqcdnew_2016.root"); 
 // TFile *f2 = new TFile("/afs/cern.ch/user/v/vmariani/CMSSW_10_2_16_UL/src/BSMFramework/BSM3G_TNT_Maker/python/2016/SR_syst_DY_HTincl_Kewkqcd_2016.root");
   TFile *f3 = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/2016_ALL_HOPE/25062021/SR_syst_Other_2016.root");
   TFile *f4 = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/2016_ALL_HOPE/25062021/SR_syst_eejj_L13_M1000_2016.root");
   TFile *f5 = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/2016_ALL_HOPE/25062021/CR_DY_data_ele_2016.root");


/////input files
  //2016
   TH1F *h1_c= (TH1F*) f1->Get("TTtW_Zpeak_ee_pt");
   TH1F *h2_c= (TH1F*) f2->Get("DY_Zpeak_ee_pt");
   TH1F *h2b_c= (TH1F*) f3->Get("Other_Zpeak_ee_pt");
   TH1F *h4_c= (TH1F*) f4->Get("eejj_L13_M1000_Zpeak_ee_pt");
   TH1F *h5_c= (TH1F*) f5->Get("pt_ee_Z");

   TH1F *h1=(TH1F*) h1_c->Clone();
   TH1F *h2=(TH1F*) h2_c->Clone();
   TH1F *h2b=(TH1F*) h2b_c->Clone();
   TH1F *h4=(TH1F*) h4_c->Clone();
   TH1F *h5=(TH1F*) h5_c->Clone();

  //Full Run2 histos from combine --total-shape option 
//   TH1F *h4_c= (TH1F*) f1->Get(dir+"TotalSig");
//   TH1F *h5_c= (TH1F*) f1->Get(dir+"data_obs");
//   TH1F *h6_c= (TH1F*) f1->Get(dir+"TotalBkg");

  //set the correct asymmetric binning
//  const double asymbins[10] = {0,200,400,600,800,1000,1400,2000,3500,10000};
  
//Drawing
///colors // color2 = kGreen+1, color3 = kRed-7, color4 = kAzure-4,
   int bin = 1;
   int Nbins = h1->GetNbinsX();
   int w = Nbins / bin;
   h1->SetLineColor(kRed-7);
   h1->SetFillStyle( 1001);
   h1->SetFillColor(kRed-7);
   h1->Rebin(bin);
   h2b->SetLineColor(kAzure-4);
   h2b->SetFillStyle( 1001);
   h2b->SetFillColor(kAzure-4);
   h2b->Rebin(bin);
   h2->SetLineColor(kGreen+1);
   h2->SetFillStyle( 1001);
   h2->Rebin(bin);
   h2->SetFillColor(kGreen+1);
   h4->SetLineColor(kBlue+2);
   h4->SetLineWidth(3);
   h4->SetLineStyle(10);
   h4->Rebin(bin);

   h5->SetLineColor(kBlack);
   h5->SetMarkerStyle(8); 
   h5->Rebin(bin);
//TCanvas c1;
    canv->cd();
    c1_1->Draw();
    c1_1->cd();
    c1_1->SetTopMargin(0.07);
    c1_1->SetBottomMargin(0.);
    c1_1->SetRightMargin(0.045);
    c1_1->SetLeftMargin(0.15);
    //c1_1->SetLogy();
    //c1_1->SetLogx();
///
THStack *hs = new THStack("hs","Normalizzazione all'area");
    hs->SetMinimum(1);
    hs->SetMaximum(700);

    hs->Add(h2b);
    hs->Add(h1);
    hs->Add(h2);

///////
 /////All Bkgs statistical & systematic error
 //////
double NTOP=0, NTOP_err2=0;
double Ndy=0, Ndy_err2=0;
double Nother=0, Nother_err2=0;
double Ntot=0, Ntot_err2=0;
double Ndata=0;
double Ntot_combine=0, Ntot_combine_err=0;
double all_bkg_Err_x[w], all_bkg_Err_y[w], all_bkg_Err_xerr[w], all_bkg_statErr_yerr[w], all_bkg_sistErr_yerr[w], all_bkg_totErr_yerr[w];
for(int i=1;i<=w;i++){
   NTOP =NTOP+ h1->GetBinContent(i);       NTOP_err2 = NTOP_err2 + h1->GetBinError(i)*h1->GetBinError(i); 
   Ndy =Ndy+ h2->GetBinContent(i);         Ndy_err2 = Ndy_err2 + h2->GetBinError(i)*h2->GetBinError(i);
   Nother =Nother+ h2b->GetBinContent(i);  Nother_err2 = Nother_err2 + h2b->GetBinError(i)*h2b->GetBinError(i); 
   Ndata =Ndata+ h5->GetBinContent(i);  
   all_bkg_Err_x[i-1] = h1->GetBinCenter(i);
   all_bkg_Err_y[i-1] = h1->GetBinContent(i)+h2b->GetBinContent(i)+h2->GetBinContent(i);
   all_bkg_Err_xerr[i-1] = h1->GetBinWidth(i)/2;
   // Ntot_combine = Ntot_combine + h6_c->GetBinContent(i); Ntot_combine_err = Ntot_combine_err + h6_c->GetBinError(i)*h6_c->GetBinError(i);
  //cout <<h5->GetBinContent(i)<<endl;
}

 Ntot_combine=NTOP+Ndy+Nother;
 Ntot_combine_err=sqrt(NTOP_err2+Ndy_err2+Nother_err2);

  for(int m=1;m<=w;m++){
    ///statistic e systematic error are togheter in the prefit histos
   all_bkg_statErr_yerr[m-1]=sqrt(pow(sqrt(h1->GetBinContent(m)),2) + pow(sqrt(h2->GetBinContent(m)),2) + pow(sqrt(h2b->GetBinContent(m)),2));
    ///systematics
      all_bkg_sistErr_yerr[m-1]=0;   
    /////total error
    all_bkg_totErr_yerr[m-1]= (all_bkg_statErr_yerr[m-1] ) ;        
   }
  
 TGraphErrors *all_bkg_statErr = new TGraphErrors(w, all_bkg_Err_x, all_bkg_Err_y, all_bkg_Err_xerr, all_bkg_totErr_yerr);
 all_bkg_statErr->SetLineColor(kGray+3);
 all_bkg_statErr->SetFillStyle(3004);
 all_bkg_statErr->SetFillColor(kGray+3);
 
   hs->Draw("hist");
   //h4->Draw("histsame");
   h5->Draw("ALPEsame");    /// data unblind
   all_bkg_statErr->Draw("E2same");


// definisci gli assi dell'histo che disegni per primo, con titolo offset etc
    hs->GetXaxis()->SetLimits(0,1000);
    hs->GetXaxis()->SetTitleOffset(1.);
    hs->GetXaxis()->SetLabelSize(0.045);
    hs->GetXaxis()->SetTitleSize(0.06);
    hs->GetYaxis()->SetTitleOffset(1.);
    hs->GetYaxis()->SetTitle("Events");
//  hs->GetYaxis()->SetTitle("Normalized Events");
    hs->GetXaxis()->SetTitle("M(e,e) (GeV)");
    hs->GetXaxis()->SetLabelSize(0.045);    
    hs->GetYaxis()->SetLabelSize(0.045);
    hs->GetYaxis()->SetTitleSize(0.06);

   canv->cd();
c1_2->SetTopMargin(0);
c1_2->SetBottomMargin(0.27);
c1_2->SetRightMargin(0.045);
c1_2->SetLeftMargin(0.15);
//c1_2->SetLogx();
c1_2->Draw();
c1_2->cd();

double rd = 0, mc = 0, rd_e = 0, mc_e = 0;
double dataSUmc_x[w], dataSUmc_y[w], dataSUmc_xerr[w], dataSUmc_yerr[w];
double mc_tot[w], mc_err[w], mc_x[w], mc_ex[w];

for(int j=1; j<w; j++){

 dataSUmc_x[j] = 0; dataSUmc_y[j] = 0; dataSUmc_xerr[j] = 0; dataSUmc_yerr[j] = 0;

 dataSUmc_x[j] = h1->GetBinCenter(j);  dataSUmc_xerr[j] = 0;

 mc_tot[j] = h2b->GetBinContent(j) + h1->GetBinContent(j) + h2->GetBinContent(j);

 if (h5->GetBinContent(j) != 0 && mc_tot[j] != 0){
  rd = h5->GetBinContent(j);
  mc = mc_tot[j];
  rd_e = h5->GetBinError(j);
  mc_e = all_bkg_totErr_yerr[j];
  dataSUmc_y[j] = rd/mc;
  dataSUmc_yerr[j] = (1./mc)*sqrt(pow(rd_e,2)+(pow(rd,2)/pow(mc,2))*pow(mc_e,2));
 }
}

TGraphErrors *dataSUmc = new TGraphErrors(w, dataSUmc_x, dataSUmc_y, dataSUmc_xerr, dataSUmc_yerr);

 dataSUmc->GetXaxis()->SetLimits(0,1000);
dataSUmc->Draw("APZ");
dataSUmc->SetTitle(0);
dataSUmc->SetMarkerStyle(8);
dataSUmc->GetYaxis()->SetNdivisions(5,5,1);

dataSUmc->GetXaxis()->SetTitle("p_{t} (e,e) (GeV)");
dataSUmc->GetXaxis()->SetLabelSize(25);
dataSUmc->GetXaxis()->SetLabelFont(43);
dataSUmc->GetXaxis()->SetTitleSize(30);
dataSUmc->GetXaxis()->SetTitleFont(43);
dataSUmc->GetXaxis()->SetTitleOffset(3);

dataSUmc->GetYaxis()->SetTitle("Data/MC");
dataSUmc->GetYaxis()->SetLabelSize(25);
dataSUmc->GetYaxis()->SetLabelFont(43);
dataSUmc->GetYaxis()->SetTitleSize(30);
dataSUmc->GetYaxis()->SetTitleFont(43);
dataSUmc->GetYaxis()->SetTitleOffset(1.5);


dataSUmc->SetMinimum(0.4);  //0.5
dataSUmc->SetMaximum(1.6);  //1.5
TLine* line = new TLine(0,1,1000,1);
line->SetLineColor(kRed);
line->SetLineWidth(2);
line->Draw("same");

gPad->RedrawAxis();
//gPad->SetLogx();


c1_1->cd();

// poi disegni la legenda  
TLegend *leg = new TLegend(0.6, 0.68, 0.90, 0.88);   //x2=0.59 per 0 PU, x2=0.65 per 200PU linear, x2=0.59 per 200PU log
    leg->SetShadowColor(0);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.04);
    leg->SetFillColor(0);
    leg->AddEntry(h1, "TTtW",  "f");
    leg->AddEntry(h2, "DY", "f");
    leg->AddEntry(h2b, "Other", "f");   
//  leg->AddEntry(h6b, "All bkds", "l");
//  leg->AddEntry(h4, "#scale[0.8]{#Lambda = 13, M(N_{e}) = 1 TeV}",  "l"); 
    leg->AddEntry(all_bkg_statErr,"#scale[0.7]{Bkg stat. and syst. uncert.}","F");// and syst. 
  leg->AddEntry(h5, "Data", "l");

// metti la descrizione che vuoi appaia e poi con PL intendi che prende come riferimento i point e la line style dell'histo
leg->Draw();

canv->cd();
  CMS_lumi( c1_1, iPeriod, iPos, 1.3 );

canv->Print("/eos/user/v/vmariani/www/HN/25062021/DYbins/Pt_ee_Zpeak_Kewkqcd_new_LO_2016.png");
canv->Print("/eos/user/v/vmariani/www/HN/25062021/DYbins/Pt_ee_Zpeak_Kewkqcd_new_LO_2016.pdf");
  return canv;
}
