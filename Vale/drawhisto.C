{
 //CFG CMS STYLE
 gROOT->Reset();
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(1,0);
  gStyle->SetTitleX(0.5); //title X location 
  gStyle->SetTitleY(0.96); //title Y location 
  gStyle->SetPaintTextFormat(".2f");

  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

 tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);

 tdrStyle->SetPadBorderMode(0);
 tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(1);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

 tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);

  tdrStyle->SetHistFillColor(63);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  tdrStyle->SetErrorX(0.); 
  tdrStyle->SetMarkerStyle(20);

  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);
  tdrStyle->SetOptDate(0);

  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(2);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);

  tdrStyle->SetPadTopMargin(0.05);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.23);
  tdrStyle->SetPadRightMargin(0.05);

  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);

  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.05);

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.05, "XYZ");

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

  tdrStyle->cd();


//FINE CONFIG

using namespace std;
TH1F * gHisto ;
THStack *hs = new THStack("hs","");

TFile *f00 = new TFile("/eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/2016_ALL_HOPE/SR_syst_DY_HTincl_Kewkqcd_2016.root");
/*TFile *f03 = new TFile("plot/SR_plots_lambda_mumujj_L15_M1000_2016.root");
TFile *f04 = new TFile("plot/SR_plots_lambda_mumujj_L20_M1000_2016.root");
*/
bin=1;
TString name="DY_mumujj";
TString name2="DY_mumujj_2016_PtResoUp";
TH1F *da= (TH1F*) f00->Get(name);
TH1F *da1= (TH1F*) f00->Get(name2);
/*TH1F *da3= (TH1F*) f03->Get(name);
TH1F *da4= (TH1F*) f04->Get(name);
*/
TH1F *d=(TH1F*) da->Clone();
TH1F *d1=(TH1F*) da1->Clone();
/*
TH1F *d3=(TH1F*) da3->Clone();
TH1F *d4=(TH1F*) da4->Clone();   
*/
   d->SetLineColor(kRed);
   d->SetLineWidth(2);
   d->SetFillColor(kRed);
   d->SetFillStyle(3005);
   d->Rebin(bin);
  // hs->Add(d);
   d1->SetLineColor(kBlue);
   d1->SetFillColor(kBlue);
   d1->SetFillStyle(3005);
   d1->Rebin(bin);
   //hs->Add(d1);
  // hs->Add(d2);
/*   d3->SetLineColor(kViolet);
   d3->SetLineWidth(2);
   d4->SetLineColor(kCyan);
   d4->SetLineWidth(2);
 */
   
   TCanvas *cs = new TCanvas("cs","cs",0,0,800,600);
   TPad *c1_1 = new TPad("c1_1", "newpad",0.01,0.01,0.99,0.99);
   c1_1->Draw();
   c1_1->cd();
   c1_1->SetTopMargin(0.05);
   c1_1->SetBottomMargin(0.15);
   c1_1->SetRightMargin(0.02);
   c1_1->SetLeftMargin(0.15);
   d->SetMaximum(150);
 //  d4->SetMinimum(0.000001);
   d->GetXaxis()->SetTitle("[GeV]");
   d->GetYaxis()->SetTitle("Events");
   d1->SetMaximum(150);
   d1->GetXaxis()->SetTitle("[GeV]");
   d1->GetYaxis()->SetTitle("Events");
   cout << "presmear Int " << d->Integral() << " postsmear Int " << d1->Integral() << endl;
   d->Sumw2();
   double w = d->Integral();//Integral();//GetEntries();
//   d->Scale(1./w);
   d1->Sumw2();
   double w1 = d1->Integral();//Integral();//GetEntries();
   for (int i=0; i<=d->GetNbinsX(); i++){
   cout << "bin: " << i << " content pre smear " << d->GetBinContent(i) << " content post smear " << d1->GetBinContent(i) << endl;

   }
  
//   d1->Scale(1./w1);
/*   d3->Sumw2();
   double w3 = d3->Integral();//Integral();//GetEntries();
   d3->Scale(1./w3);
   d4->Sumw2();
   double w4 = d4->Integral();//Integral();//GetEntries();
   d4->Scale(1./w4);
  // d->GetXaxis()->SetRangeUser(0,5000);
  // d1->GetXaxis()->SetRangeUser(0,5000);
  // d2->GetXaxis()->SetRangeUser(0,5000);
*/
//   d->SetMaximum(1);
   d1->Draw("histo");
//   d1->Draw("histosame");
/*   d3->Draw("histosame");
   d4->Draw("histosame");
*/
   TLegend *pl = new TLegend(0.7,0.7,0.99,0.99); //0.4,0.20,0.75,0.30
   pl->SetTextSize(0.03);
   pl->SetFillColor(0);
   pl-> SetNColumns(1);//per piu plot sovrapposti
//   pl->AddEntry(d, "pre smear", "Column 1 line 1");// "PL");
   pl->AddEntry(d1, "post smear", "Column 1 line 1"); 
/*   pl->AddEntry(d3, "mumujj L15 M1000", "Column 1 line 1");
   pl->AddEntry(d4, "mumujj L20 M1000", "Column 1 line 1");
*/   pl->Draw();

   cs->SaveAs("/eos/user/v/vmariani/www/HN/Rochester/"+name+"_postmear_2016.png");
   return cs;
}
