//#include "TDRStyle.h "

 using namespace std;
 
void MeeJ_2018(){
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
 
   TFile *f1 = new TFile("histograms/eejj_L13000_M1000_sr/eejj_L13000_M1000_sr_YearsCombination_PostFit_histograms.root");
   TString dir = "Y2018combined_signal_region_postfit/";
   TString name = "eejj_2018_M1000postfit"; //nome del file salvato
   
/////input files
   TH1F *h1_c= (TH1F*) f1->Get(dir+"TTtW");
   TH1F *h2_c= (TH1F*) f1->Get(dir+"DY");
   TH1F *h2b_c= (TH1F*) f1->Get(dir+"Other");
   TH1F *h4_c= (TH1F*) f1->Get(dir+"eejj_L13_M1000");
   TH1F *h5_c= (TH1F*) f1->Get(dir+"data_obs");

  //adjust the plot binning 
  const double asymbins[10] = {0,200,400,600,800,1000,1400,2000,3500,10000};
  TH1F *h1 = new TH1F ("", "", 9, asymbins);    
  TH1F *h2 = new TH1F ("", "", 9, asymbins);    
  TH1F *h2b= new TH1F ("", "", 9, asymbins);    
  TH1F *h4 = new TH1F ("", "", 9, asymbins);    
  TH1F *h5 = new TH1F ("", "", 9, asymbins);    
  for(int i=1;i<10;i++){
    h1->SetBinContent(i,h1_c->GetBinContent(i));    h1->SetBinError(i,h1_c->GetBinError(i));
    h2->SetBinContent(i,h2_c->GetBinContent(i));    h2->SetBinError(i,h2_c->GetBinError(i));
    h2b->SetBinContent(i,h2b_c->GetBinContent(i));  h2b->SetBinError(i,h2b_c->GetBinError(i));
    h4->SetBinContent(i,h4_c->GetBinContent(i));    h4->SetBinError(i,h4_c->GetBinError(i));
    h5->SetBinContent(i,h5_c->GetBinContent(i));    h5->SetBinError(i,h5_c->GetBinError(i));
  }


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
	TCanvas* c1 = new TCanvas("c1","c1",0,0,800,650);
	TPad *c1_1 = new TPad("c1_1", "newpad",0.01,0.01,0.99,0.99);
	c1_1->Draw();
	c1_1->cd();
	c1_1->SetTopMargin(0.1);
	c1_1->SetBottomMargin(0.15);
	c1_1->SetRightMargin(0.045);
	c1_1->SetLeftMargin(0.15);
	c1_1->SetLogy();
	c1_1->SetLogx();
///
THStack *hs = new THStack("hs","Normalizzazione all'area");
	hs->SetMinimum(1);
	hs->SetMaximum(2000);

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
for(int i=7;i<10;i++){
   NTOP =NTOP+ h1->GetBinContent(i);       NTOP_err2 = NTOP_err2 + h1->GetBinError(i)*h1->GetBinError(i); 
   Ndy =Ndy+ h2->GetBinContent(i);         Ndy_err2 = Ndy_err2 + h2->GetBinError(i)*h2->GetBinError(i);
   Nother =Nother+ h2b->GetBinContent(i);  Nother_err2 = Nother_err2 + h2b->GetBinError(i)*h2b->GetBinError(i); 
   Ndata =Ndata+ h5->GetBinContent(i);  
}
 cout << "N_ev top "<<   NTOP  <<"+-"<<  sqrt(NTOP_err2)  <<endl;
 cout << "N_ev dy "<<   Ndy  <<"+-"<<  sqrt(Ndy_err2)  <<endl;
 cout << "N_ev other "<<   Nother  <<"+-"<<  sqrt(Nother_err2)  <<endl;
 cout << "N_ev data "<<   Ndata  <<endl;
 cout << "N_ev TOTAL "<<   NTOP+ Ndy + Nother <<"+-"<< sqrt( NTOP_err2 +  Ndy_err2 +  Nother_err2   )   <<endl;
cout <<"====================="<<endl;
 cout << Ndy <<"$ pm $ "<< sqrt(Ndy_err2) <<" & "<< NTOP << "$ pm $"<<  sqrt(NTOP_err2)  <<" & "<< Nother  << "$ pm $"<< sqrt(Nother_err2) <<" & "<< NTOP+ Ndy + Nother << " $ pm $ "<< sqrt( NTOP_err2 +  Ndy_err2 +  Nother_err2   ) <<" & "<< Ndata <<endl;




 double all_bkg_Err_x[9]={h1->GetBinCenter(1),h1->GetBinCenter(2),h1->GetBinCenter(3),h1->GetBinCenter(4),h1->GetBinCenter(5),h1->GetBinCenter(6),h1->GetBinCenter(7),h1->GetBinCenter(8),h1->GetBinCenter(9)};
 double all_bkg_Err_y[9]={h1->GetBinContent(1) + h2b->GetBinContent(1) + h2->GetBinContent(1),  h1->GetBinContent(2) + h2b->GetBinContent(2) + h2->GetBinContent(2)    ,h1->GetBinContent(3) + h2b->GetBinContent(3) + h2->GetBinContent(3)   ,h1->GetBinContent(4) + h2b->GetBinContent(4) + h2->GetBinContent(4)     ,h1->GetBinContent(5) + h2b->GetBinContent(5) + h2->GetBinContent(5)     ,h1->GetBinContent(6) + h2b->GetBinContent(6) + h2->GetBinContent(6)   ,h1->GetBinContent(7) + h2b->GetBinContent(7) + h2->GetBinContent(7)    ,h1->GetBinContent(8) + h2b->GetBinContent(8) + h2->GetBinContent(8),  h1->GetBinContent(9) + h2b->GetBinContent(9) + h2->GetBinContent(9)}; 
 double all_bkg_Err_xerr[9]={h1->GetBinWidth(1)/2  ,h1->GetBinWidth(2)/2   ,h1->GetBinWidth(3)/2   ,h1->GetBinWidth(4)/2  ,h1->GetBinWidth(5)/2  ,h1->GetBinWidth(6)/2  ,h1->GetBinWidth(7)/2  ,h1->GetBinWidth(8)/2  ,h1->GetBinWidth(9)/2  };
 double all_bkg_statErr_yerr[9];  //={0,0,0,0,0,0,0,Yerr};
 double all_bkg_sistErr_yerr[9];  
 double all_bkg_totErr_yerr[9];  
  
  for(int m=1;m<10;m++){
//  	all_bkg_statErr_x[m]=h1->GetBinCenter(m) ;
  //	all_bkg_statErr_y[m]=(h1->GetBinContent(m) + h2b->GetBinContent(m) + h2->GetBinContent(m)) ;
  //	all_bkg_statErr_xerr[m]=h1->GetBinWidth(m) / 2 ;
  
  
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
   h4->Draw("histsame");
   h5->Draw("ALPEsame");    /// data unblind
   all_bkg_statErr->Draw("E2same");


// definisci gli assi dell'histo che disegni per primo, con titolo offset etc
	hs->GetXaxis()->SetTitleOffset(1.);
	hs->GetXaxis()->SetLabelSize(0.045);
	hs->GetXaxis()->SetTitleSize(0.06);
	hs->GetYaxis()->SetTitleOffset(1.2);
	hs->GetYaxis()->SetTitle("Events");
//	hs->GetYaxis()->SetTitle("Normalized Events");
	hs->GetXaxis()->SetTitle("M(e,e,J) (GeV)");
    hs->GetXaxis()->SetLabelSize(0.045);	
	hs->GetYaxis()->SetLabelSize(0.045);
	hs->GetYaxis()->SetTitleSize(0.06);
//qui inizia la leggenda, quelli commentati sono esempi di titoli "ufficiali", 
//il primo per i dati e il secondo per le simulazioni
	TLatex latexLabel;
	latexLabel.SetTextSize(0.039);
//	latexLabel2.SetTextFont(32);
	latexLabel.SetNDC();
	latexLabel.DrawLatex(0.15, 0.93, "CMS Run 2 #it{#bf{Preliminary}}");
	TLatex latexLabel2;
	latexLabel2.SetTextSize(0.039);
//	latexLabel2.SetTextFont(32);
	latexLabel2.SetNDC();
	latexLabel2.DrawLatex(0.76, 0.93, "59.74 fb^{-1} (13 TeV)");
// poi disegni la legenda  
TLegend *leg = new TLegend(0.6, 0.68, 0.90, 0.88);   //x2=0.59 per 0 PU, x2=0.65 per 200PU linear, x2=0.59 per 200PU log
 	leg->SetShadowColor(0);
 	leg->SetBorderSize(0);
 	leg->SetTextSize(0.04);
 	leg->SetFillColor(0);
	leg->AddEntry(h1, "TTtW",  "f");
	leg->AddEntry(h2, "DY", "f");
	leg->AddEntry(h2b, "Other", "f");	
//	leg->AddEntry(h6b, "All bkds", "l");
	leg->AddEntry(h4, "#scale[0.8]{#Lambda = 13, M(N_{e}) = 1 TeV}",  "l");	
	leg->AddEntry(all_bkg_statErr,"#scale[0.7]{Bkg stat. and syst.uncert.}","F");// and syst. 
   leg->AddEntry(h5, "Data", "l");

// metti la descrizione che vuoi appaia e poi con PL intendi che prende come riferimento i point e la line style dell'histo
leg->Draw();

c1->SaveAs(name+".png");
c1_1->SaveAs(name+".pdf");
   
  return;
}
