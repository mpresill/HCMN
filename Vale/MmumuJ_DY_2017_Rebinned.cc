#include "tdrstyle.C"
#include "CMS_lumi.C"
#include "TH1.h"
#include "TH1F.h"


TCanvas* c1(int iPeriod, int iPos); 
void MmumuJ_DY_2017_Rebinned()
{
 setTDRStyle();
 
 writeExtraText = true;       // if extra text
 extraText  = "Preliminary";
 //lumi_sqrtS = "13 TeV";
 int iPeriod = 17;
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

 TString canvName = "Mmumuj_CMSStyle";
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
 
   TFile *f1 = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/PostFit/histograms/mumujj_L13000_M1000_sr_Rebinned/mumujj_L13000_M1000_sr_YearsCombination_Rebinned_PostFit_histograms.root");
   TString name = "mumujj_2017_M1000postfit_DYcr_Rebinned"; //nome del file salvato

   TString dir2017 = "DYcr_Y2017_DYcr_postfit/";
   //TString dir     = "postfit/";


/////input files
   //2017
   TH1F *h1_c= (TH1F*) f1->Get(dir2017+"TTtW");
   TH1F *h2_c= (TH1F*) f1->Get(dir2017+"DY");
   TH1F *h2b_c= (TH1F*) f1->Get(dir2017+"Other");
  TH1F *h4_c= (TH1F*) f1->Get(dir2017+"mumujj_L13_M1000");
   TH1F *h5_c= (TH1F*) f1->Get(dir2017+"data_obs");


  //Full Run2 histos from combine --total-shape option 
//   TH1F *h4_c= (TH1F*) f1->Get(dir+"TotalSig");
//   TH1F *h5_c= (TH1F*) f1->Get(dir+"data_obs");
//   TH1F *h6_c= (TH1F*) f1->Get(dir+"TotalBkg");

  //set the correct asymmetric binning
  const double asymbins[9] = {0,200,400,600,800,1000,1400,2000,10000};
 
  TH1F *h1 = new TH1F ("", "", 8, asymbins);    
  TH1F *h2 = new TH1F ("", "", 8, asymbins);    
  TH1F *h2b= new TH1F ("", "", 8, asymbins);    
  TH1F *h4 = new TH1F ("", "", 8, asymbins);    
  TH1F *h5 = new TH1F ("", "", 8, asymbins);    
  for(int i=1;i<10;i++){
    h1->SetBinContent(i,h1_c->GetBinContent(i));    h1->SetBinError(i,h1_c->GetBinError(i));
    h2->SetBinContent(i,h2_c->GetBinContent(i));    h2->SetBinError(i,h2_c->GetBinError(i));
    h2b->SetBinContent(i,h2b_c->GetBinContent(i));  h2b->SetBinError(i,h2b_c->GetBinError(i));
    h4->SetBinContent(i,h4_c->GetBinContent(i));    h4->SetBinError(i,h4_c->GetBinError(i));
    h5->SetBinContent(i,h5_c->GetBinContent(i));    h5->SetBinError(i,h5_c->GetBinError(i));
  }


//Drawing
///colors // color2 = kGreen+1, color3 = kRed-7, color4 = kAzure-4,
   h1->SetLineColor(kRed-7);
   h1->SetFillStyle( 1001);
   h1->SetFillColor(kRed-7);
   h2b->SetLineColor(kAzure-4);
   h2b->SetFillStyle( 1001);
   h2b->SetFillColor(kAzure-4);
   h2->SetLineColor(kGreen+1);
   h2->SetFillStyle( 1001);
   h2->SetFillColor(kGreen+1);
   h4->SetLineColor(kBlue+2);
   h4->SetLineWidth(3);
   h4->SetLineStyle(10);

   h5->SetLineColor(kBlack);
   h5->SetMarkerStyle(8); 

//TCanvas c1;
    canv->cd(); 
    c1_1->Draw();
    c1_1->cd();
    c1_1->SetTopMargin(0.07);
    c1_1->SetBottomMargin(0.);
    c1_1->SetRightMargin(0.045);
    c1_1->SetLeftMargin(0.15);
    c1_1->SetLogy();
    c1_1->SetLogx();
///
THStack *hs = new THStack("hs","Normalizzazione all'area");
    hs->SetMinimum(1);
    hs->SetMaximum(3000);

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
for(int i=1;i<10;i++){
   NTOP =NTOP+ h1->GetBinContent(i);       NTOP_err2 = NTOP_err2 + h1->GetBinError(i)*h1->GetBinError(i); 
   Ndy =Ndy+ h2->GetBinContent(i);         Ndy_err2 = Ndy_err2 + h2->GetBinError(i)*h2->GetBinError(i);
   Nother =Nother+ h2b->GetBinContent(i);  Nother_err2 = Nother_err2 + h2b->GetBinError(i)*h2b->GetBinError(i); 
   Ndata =Ndata+ h5->GetBinContent(i);  
   // Ntot_combine = Ntot_combine + h6_c->GetBinContent(i); Ntot_combine_err = Ntot_combine_err + h6_c->GetBinError(i)*h6_c->GetBinError(i);
  //cout <<h5->GetBinContent(i)<<endl;
}

 Ntot_combine=NTOP+Ndy+Nother;
 Ntot_combine_err=sqrt(NTOP_err2+Ndy_err2+Nother_err2);


 double all_bkg_Err_x[9]={h1->GetBinCenter(1),h1->GetBinCenter(2),h1->GetBinCenter(3),h1->GetBinCenter(4),h1->GetBinCenter(5),h1->GetBinCenter(6),h1->GetBinCenter(7),h1->GetBinCenter(8),h1->GetBinCenter(9)};
 double all_bkg_Err_y[9]={h1->GetBinContent(1) + h2b->GetBinContent(1) + h2->GetBinContent(1),  h1->GetBinContent(2) + h2b->GetBinContent(2) + h2->GetBinContent(2)    ,h1->GetBinContent(3) + h2b->GetBinContent(3) + h2->GetBinContent(3)   ,h1->GetBinContent(4) + h2b->GetBinContent(4) + h2->GetBinContent(4)     ,h1->GetBinContent(5) + h2b->GetBinContent(5) + h2->GetBinContent(5)     ,h1->GetBinContent(6) + h2b->GetBinContent(6) + h2->GetBinContent(6)   ,h1->GetBinContent(7) + h2b->GetBinContent(7) + h2->GetBinContent(7)    ,h1->GetBinContent(8) + h2b->GetBinContent(8) + h2->GetBinContent(8),  h1->GetBinContent(9) + h2b->GetBinContent(9) + h2->GetBinContent(9)}; 
 double all_bkg_Err_xerr[9]={h1->GetBinWidth(1)/2  ,h1->GetBinWidth(2)/2   ,h1->GetBinWidth(3)/2   ,h1->GetBinWidth(4)/2  ,h1->GetBinWidth(5)/2  ,h1->GetBinWidth(6)/2  ,h1->GetBinWidth(7)/2  ,h1->GetBinWidth(8)/2  ,h1->GetBinWidth(9)/2  };
 double all_bkg_statErr_yerr[9];  //={0,0,0,0,0,0,0,Yerr};
 double all_bkg_sistErr_yerr[9];  
 double all_bkg_totErr_yerr[9];  
  
  for(int m=1;m<10;m++){
    ///statistic e systematic error are togheter in the postfit histos
    all_bkg_statErr_yerr[m-1]=sqrt( (h1->GetBinError(m))*(h1->GetBinError(m)) + (h2->GetBinError(m))*(h2->GetBinError(m)) + (h2b->GetBinError(m))*(h2b->GetBinError(m)) );
    ///systematics
      all_bkg_sistErr_yerr[m-1]=0;   
    /////total error
    all_bkg_totErr_yerr[m-1]= (all_bkg_statErr_yerr[m-1] ) ;        
   }
  
 TGraphErrors *all_bkg_statErr = new TGraphErrors(9, all_bkg_Err_x, all_bkg_Err_y, all_bkg_Err_xerr, all_bkg_totErr_yerr);
 all_bkg_statErr->SetLineColor(kGray+3);
 all_bkg_statErr->SetFillStyle(3004);
 all_bkg_statErr->SetFillColor(kGray+3);
 
   hs->Draw("hist");
   //h4->Draw("histsame");
   h5->Draw("ALPEsame");    /// data unblind
   all_bkg_statErr->Draw("E2same");


// definisci gli assi dell'histo che disegni per primo, con titolo offset etc
    hs->GetXaxis()->SetLimits(10,10000);   
    hs->GetXaxis()->SetTitleOffset(1.);
    hs->GetXaxis()->SetLabelSize(0.045);
    hs->GetXaxis()->SetTitleSize(0.06);
    hs->GetYaxis()->SetTitleOffset(1.);
    hs->GetYaxis()->SetTitle("Events");
//  hs->GetYaxis()->SetTitle("Normalized Events");
    hs->GetXaxis()->SetTitle("M(#mu,#mu,J) (GeV)");
    hs->GetXaxis()->SetLabelSize(0.045);    
    hs->GetYaxis()->SetLabelSize(0.045);
    hs->GetYaxis()->SetTitleSize(0.06);

 canv->cd();
c1_2->SetTopMargin(0);
c1_2->SetBottomMargin(0.27);
c1_2->SetRightMargin(0.045);
c1_2->SetLeftMargin(0.15);
c1_2->SetLogx();
c1_2->Draw();
c1_2->cd();

int v = 10;
double rd = 0, mc = 0, rd_e = 0, mc_e = 0;
double dataSUmc_x[v]; double dataSUmc_y[v]; double dataSUmc_xerr[v]; double dataSUmc_yerr[v];
double mc_tot[v], mc_err[v], mc_x[v], mc_ex[v];

for(int j=1; j<v; j++){

 dataSUmc_x[j] = 0; dataSUmc_y[j] = 0; dataSUmc_xerr[j] = 0; dataSUmc_yerr[j] = 0;

 dataSUmc_x[j] = h1->GetBinCenter(j);  dataSUmc_xerr[j] = 0;

 mc_tot[j] = h2b->GetBinContent(j) + h1->GetBinContent(j) + h2->GetBinContent(j);

 if (h5_c->GetBinContent(j) != 0 && mc_tot[j] != 0){
  rd = h5_c->GetBinContent(j);
  mc = mc_tot[j];
  rd_e = h5_c->GetBinError(j);
  mc_e = mc_err[j];
  dataSUmc_y[j] = rd/mc;
  dataSUmc_yerr[j] = (1./mc)*sqrt(pow(rd_e,2)+(pow(rd,2)/pow(mc,2))*pow(mc_e,2));
 }
 cout << "x " << dataSUmc_x[j] << " ratio " << dataSUmc_y[j] << endl;
}

TGraphErrors *dataSUmc = new TGraphErrors(v, dataSUmc_x, dataSUmc_y, dataSUmc_xerr, dataSUmc_yerr);

  dataSUmc->GetXaxis()->SetLimits(200,10000);
dataSUmc->Draw("APZ");
dataSUmc->SetTitle(0);
dataSUmc->SetMarkerStyle(8);
dataSUmc->GetYaxis()->SetNdivisions(5,5,1);

dataSUmc->GetXaxis()->SetTitle("M(#mu,#mu,J) (GeV)");
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
TLine* line = new TLine(0,1,10000,1);
line->SetLineColor(kRed);
line->SetLineWidth(2);
line->Draw("same");

gPad->RedrawAxis();
//gPad->SetLogx();


c1_1->cd();


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
    leg->AddEntry(all_bkg_statErr,"#scale[0.7]{Bkg stat. and syst.uncert.}","F");// and syst. 
  leg->AddEntry(h5, "Data", "l");

// metti la descrizione che vuoi appaia e poi con PL intendi che prende come riferimento i point e la line style dell'histo
leg->Draw();

canv->cd();
  CMS_lumi( c1_1, iPeriod, iPos, 1.3 );

canv->Print(name+".png");
canv->Print(name+".pdf");
canv->Print("/eos/user/v/vmariani/www/HN/postfit/"+name+".png");
canv->Print("/eos/user/v/vmariani/www/HN/postfit/"+name+".pdf");
  return canv;

}
