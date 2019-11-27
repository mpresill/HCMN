//#include "TDRStyle.h "

 using namespace std;
 
 void Mee(){
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
 //tdrStyle->SetStatStyle(Style_t style = 1001)
//Margins:
 tdrStyle->SetPadTopMargin(0.095);
 tdrStyle->SetPadBottomMargin(0.125);
 tdrStyle->SetPadLeftMargin(0.14);
 tdrStyle->SetPadRightMargin(0.1);
 
  
  // For the Global title:

  tdrStyle->SetOptTitle(0);
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

  // For the axis titles:

  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.05);

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

  tdrStyle->cd();
///////////////// FINE CONFIG 
 
 TString name = "Mee-nocuts"; //nome del file salvato

/////input files
///file 1
   TFile f1("eejj_TTtW_200PU.root");
   f1.ls();
   f1.cd("d_TTtW;1"); 
   TH1D *h1; gDirectory->GetObject("Mee", h1);
   h1->Sumw2(); //normalization
   double w1 = h1->Integral();//GetEntries();
   h1->Scale(1./w1);
   //file 2     
   TFile f2("eejj_DY_200PU.root");
   f2.ls();
   f2.cd("d_LL4p;1"); 
   TH1D *h2; gDirectory->GetObject("Mee", h2);
   h2->Sumw2(); //normalization
   double w2 = h2->Integral();//GetEntries();
   h2->Scale(1./w2);
//file 2     
   TFile f2b("eejj_Other_200PU.root");
   f2b.ls();
   f2b.cd("d_Other;1"); 
   TH1D *h2b; gDirectory->GetObject("Mee", h2b);
   h2b->Sumw2(); //normalization
   double w2b = h2b->Integral();//GetEntries();
   h2b->Scale(1./w2b);
  //file 3     
   TFile f3("eejj_L12000_M3000_200PU_v2.root");
   f3.ls();  
   f3.cd("d_L12M3000;1"); 
   TH1D *h3; gDirectory->GetObject("Mee", h3);
   h3->Sumw2(); //normalization
   double w3 = h3->Integral();//GetEntries();
   h3->Scale(1./w3);
 //file 4     
   TFile f4("eejj_L12000_M500_200PU_v2.root");
   f4.ls();  
   f4.cd("d_L12M500;1"); 
   TH1D *h4; gDirectory->GetObject("Mee", h4);
   h4->Sumw2(); //normalization
   double w4 = h4->Integral();//GetEntries();
   h4->Scale(1./w4);


///colors
   h1->SetLineColor(kRed-3);
   h1->SetFillStyle( 1001);
   h1->SetFillColor(kRed-3);
   h2b->SetLineColor(kOrange-3);
   h2b->SetFillStyle( 1001);
   h2b->SetFillColor( kOrange-3);
   h2->SetLineColor(kGreen-2);
   h2->SetFillStyle( 1001);
   h2->SetFillColor(kGreen-2);
   h3->SetLineColor(kBlue);
    h3->SetLineWidth(2);
   h4->SetLineColor(kViolet);
    h4->SetLineWidth(2);

//TCanvas c1;
	TCanvas* c1 = new TCanvas("c1","c1",0,0,800,650);
	TPad *c1_1 = new TPad("c1_1", "newpad",0.01,0.01,0.99,0.99);
	c1_1->Draw();
	c1_1->cd();
	c1_1->SetTopMargin(0.1);
	c1_1->SetBottomMargin(0.15);
	c1_1->SetRightMargin(0.045);
	c1_1->SetLeftMargin(0.15);
//	c1_1->SetLogy();
	//c1_1->SetLogx();
///
///
THStack *hs = new THStack("hs","Normalizzazione all'area");
	hs->Add(h2b);
	hs->Add(h1);
	hs->Add(h2);

    hs->Draw("hist");
    h4->Draw("histsame");

 //  all_bkg_statErr->Draw("E2same");


// definisci gli assi dell'histo che disegni per primo, con titolo offset etc
	hs->GetXaxis()->SetTitleOffset(1.);
	hs->GetXaxis()->SetLabelSize(0.045);
	hs->GetXaxis()->SetRangeUser(0,1200);
	hs->GetXaxis()->SetTitleSize(0.06);
	hs->GetYaxis()->SetTitleOffset(1.2);
//	h1->GetYaxis()->SetTitle("Events");
	hs->GetYaxis()->SetTitle("Normalized Events");
	hs->GetXaxis()->SetTitle("M(e,e) [GeV]");
    hs->GetXaxis()->SetLabelSize(0.035);	
	hs->GetYaxis()->SetLabelSize(0.045);
	hs->GetYaxis()->SetTitleSize(0.06);
//qui inizia la leggenda, quelli commentati sono esempi di titoli "ufficiali", 
//il primo per i dati e il secondo per le simulazioni
	TLatex latexLabel;
	latexLabel.SetTextSize(0.039);
//	latexLabel2.SetTextFont(32);
	latexLabel.SetNDC();
	latexLabel.DrawLatex(0.15, 0.93, "CMS Phase-2 simulation #it{#bf{Preliminary}}");
	TLatex latexLabel2;
	latexLabel2.SetTextSize(0.039);
//	latexLabel2.SetTextFont(32);
	latexLabel2.SetNDC();
	latexLabel2.DrawLatex(0.67, 0.93, "200 PU, 3 ab^{-1} (14 TeV)");
// poi disegni la legenda  
TLegend *leg = new TLegend(0.63, 0.45, 0.91, 0.65);   //x2=0.59 per 0 PU, x2=0.65 per 200PU linear, x2=0.59 per 200PU log
 	leg->SetShadowColor(0);
 	leg->SetBorderSize(0);
 	leg->SetTextSize(0.04);
 	leg->SetFillColor(0);
	leg->AddEntry(h1, "TTtW",  "f");
	leg->AddEntry(h2, "DY", "f");
	leg->AddEntry(h2b, "Other", "f");	
//	leg->AddEntry(h6b, "All bkds", "l");
	leg->AddEntry(h4, "#Lambda 12, M 5 TeV",  "l");	
	leg->AddEntry(h3, "#Lambda 12, M 3 TeV",  "l");	
//	leg->AddEntry(all_bkg_statErr,"#scale[0.65]{Bkg stat. and syst. uncert.}","F");


// metti la descrizione che vuoi appaia e poi con PL intendi che prende come riferimento i point e la line style dell'histo
leg->Draw();

c1->SaveAs(name+".png");
c1_1->SaveAs(name+".pdf");
   
  return;
}