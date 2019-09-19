void  converter_bkgs() {
  TFile *f1=new TFile ("ForCombine/OldCuts_TTpST.root");
  f1->ls();

  TH1D *h=new TH1D;
  gDirectory->GetObject("M_lljet", h);
  cout << h->Integral() << endl;
  h->SetName("TTpST");
  h->SetTitle("TTpST");
  

  TFile out_file("OldCuts_TTpST.root","RECREATE");
  h->Write();
  out_file.Close();
/////////
  TFile *f2=new TFile ("ForCombine/OldCuts_DY.root");
  f2->ls();

  TH1D *h2=new TH1D;
  gDirectory->GetObject("M_lljet", h2);
  cout << h2->Integral() << endl;
  h2->SetName("DY");
  h2->SetTitle("DY");
  

  TFile out_file2("OldCuts_DY.root","RECREATE");
  h2->Write();
  out_file2.Close();
/////

  TFile *f3=new TFile ("ForCombine/OldCuts_Other.root");
  f3->ls();

  TH1D *h3=new TH1D;
  gDirectory->GetObject("M_lljet", h3);
  cout << h3->Integral() << endl;
  h3->SetName("Other");
  h3->SetTitle("Other");
  

  TFile out_file3("OldCuts_Other.root","RECREATE");
  h3->Write();
  out_file3.Close();
//////signal
  TFile *f4=new TFile ("ForCombine/OldCuts_Sign_mumu_L11_M500.root");
  f4->ls();

  TH1D *h4=new TH1D;
  gDirectory->GetObject("M_lljet", h4);
  cout << h4->Integral() << endl;
  h4->SetName("L11_M500");
  h4->SetTitle("L11_M500");


  TFile out_file4("OldCuts_L11_M500.root","RECREATE");
  h4->Write();
  out_file4.Close();
/////signal 2  
 TFile *f5=new TFile ("ForCombine/OldCuts_Sign_mumu_L11_M1000.root");
  f5->ls();

  TH1D *h5=new TH1D;
  gDirectory->GetObject("M_lljet", h5);
  cout << h5->Integral() << endl;
  h5->SetName("L11_M1000");
  h5->SetTitle("L11_M1000");


  TFile out_file5("OldCuts_L11_M1000.root","RECREATE");
  h5->Write();
  out_file5.Close();
//////signal 3
 TFile *f6=new TFile ("ForCombine/OldCuts_Sign_mumu_L11_M2000.root");
  f6->ls();

  TH1D *h6=new TH1D;
  gDirectory->GetObject("M_lljet", h6);
  cout << h6->Integral() << endl;
  h6->SetName("L11_M2000");
  h6->SetTitle("L11_M2000");


  TFile out_file6("OldCuts_L11_M2000.root","RECREATE");
  h6->Write();
  out_file6.Close();
////signal 4
 TFile *f7=new TFile ("ForCombine/OldCuts_Sign_mumu_L11_M4000.root");
  f7->ls();

  TH1D *h7=new TH1D;
  gDirectory->GetObject("M_lljet", h7);
  cout << h7->Integral() << endl;
  h7->SetName("L11_M4000");
  h7->SetTitle("L11_M4000");


  TFile out_file7("OldCuts_L11_M4000.root","RECREATE");
  h7->Write();
  out_file7.Close();
////signal 5
TFile *f8=new TFile ("ForCombine/OldCuts_Sign_mumu_L11_M7000.root");
  f8->ls();

  TH1D *h8=new TH1D;
  gDirectory->GetObject("M_lljet", h8);
  cout << h8->Integral() << endl;
  h8->SetName("L11_M7000");
  h8->SetTitle("L11_M7000");


  TFile out_file8("OldCuts_L11_M7000.root","RECREATE");
  h8->Write();
  out_file8.Close();




                         return;
                         }
