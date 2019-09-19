void converter_dummy_observed() {
  TFile f1("ForCombine/HighMass_Selection_TTpST.root");
  f1.ls();
 // f1.cd("d_TTtW;1");
  TH1D *h1; gDirectory->GetObject("M_lljet", h1);
  cout << h1->Integral() << endl;

  TFile f2("ForCombine/HighMass_Selection_Other_noWJbin.root");
  f2.ls();
 // f2.cd("d_Other;1");
  TH1D *h2; gDirectory->GetObject("M_lljet", h2);
  cout << h2->Integral() << endl;

  TFile f3("ForCombine/HighMass_Selection_DY.root");
  f3.ls();
 // f3.cd("d_DY;1");
  TH1D *h3; gDirectory->GetObject("M_lljet", h3);
  cout << h3->Integral() << endl;  
  
  TList *list = new TList;
  list->Add(h1);
  list->Add(h2);
  list->Add(h3);
  TH1D *h = (TH1D*)h1->Clone("h");
  h->Reset();
  h->Merge(list);
  
  cout << h->Integral() << endl;
  h->SetName("data_obs");
  h->SetTitle("data_obs");
  

  TFile out_file("data_obs_HighMass_Selection.root","RECREATE");
  h->Write();
  out_file.Close();

  return;
}
