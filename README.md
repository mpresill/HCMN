# Heavy composite Majorana neutrino reload of the EXO-16-026 analysis
Documentation in GitLab: https://gitlab.cern.ch/tdr/notes/AN-18-111 .

Available samples in: https://docs.google.com/spreadsheets/d/1cjLUHCRwQxU6aovdtx6UJmBafhGXKXulmOkGTMoa9Ro/edit#gid=0

Framework available here:
- https://github.com/vmariani/BSMFramework/tree/CMSSW_10_2_16 (for 2016-2018) 
- https://github.com/mpresill/BSMFramework (2017)

## Talks:
Update talk draft https://docs.google.com/presentation/d/1V6kgz4rxWQv_1hDuIGVuL24RRUsnkTPn5hZyoxKP2og/edit#slide=id.g59567419ba_0_0

## To-do list:
Targeting subgroup Jet+X update on nov 11th with:

- [x] make ntuple 2016
- [ ] make ntuple 2017
- [x] make ntuple 2018
- [ ] ntuple->rootple conversion (only for reference signals for now = Lambda 13 TeV) for 2016
- [ ] ntuple->rootple conversion (only for reference signals for now = Lambda 13 TeV) for 2017
- [ ] ntuple->rootple conversion (only for reference signals for now = Lambda 13 TeV) for 2018
- [ ] Invariant mass plots for reference signal samples (L=13 TeV, M=0.5, 2, 5 TeV)
- [ ] Limit extrapolation on cross section * BR (stat only, per year)
- [ ] 2D Limits plot (stat only with unitarity constraint)
- [ ] table with all corrections used in the framework 
- [ ] add SFs for FatJets https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetWtagging (low priority - maybe after 11th)

What is needed from Roberto: 
   1. Macros for QCD/Other bkgs estimation
   1. Macros for signal systematics 
   1. Q: why do we have produced all these samples considering the Lambda independence on limit extraction?
      R: for now we don't really need to analyse all the samples (the request was made just to be sure on the Lambda independence on limit extraction) (=> check efficiency independence on Lambda at some point!)


- [ ] (add systematics on limit bands with Combine (MATTEO))
- [ ] (check limits independence on Lambda (MATTEO))
- [ ] (TTtW bkg estimate MC based (with cross section))
- [ ] (add fakes study) 
- [ ] (SF study for DY bkg) 
- [ ] (can we find other models for reinterpreting the results?)

## Recipies:
 - Muon efficiencies https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/tree/master/EfficienciesStudies
 - Muon reference for Run 2 https://twiki.cern.ch/twiki/bin/view/CMS/MuonReferenceEffsRun2
 - Electron efficiencies https://twiki.cern.ch/twiki/bin/viewauth/CMS/EgammaIDRecipesRun2

 - Muon scale factors:
   -  trigger 2016 (), 2017 (https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2017_trigger/theJSONfile_RunBtoF_Nov17Nov2017.json), 2018 (https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2018_trigger/theJSONfile_2018Data_AfterMuonHLTUpdate.json)
   - ID 2016 (), 2017 (), 2018 ()
   - isolation 2016 (), 2017 (), 2018 ()
   - N.B. Since there are two different scale factor scenarios within 2016 data taking depending on the era (B-F) or (G-H) muon SFs for 2016 are computed by averageing the SF by the relative luminosity of each period and then apply a single weight to the MC: lumi(B-F)_Mu50=19.25 fb^-1, lumi(B-F)_TkMu50=16.64 fb^-1; lumi(G-H)_Mu50=16.29 fb^-1, lumi(G-H)_TkMu50=16.29 fb^-1 (Info from BrilCalc)

