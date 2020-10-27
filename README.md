# Heavy composite Majorana neutrino reload of the EXO-16-026 analysis
Logbook: https://docs.google.com/document/d/14MxpNkXs3OW78FuB512MSL_r50s7g9FbVkhlvtPY9wk/edit?usp=sharing

Documentation in GitLab: https://gitlab.cern.ch/tdr/notes/AN-18-111 .

Samples list: https://docs.google.com/spreadsheets/d/1cjLUHCRwQxU6aovdtx6UJmBafhGXKXulmOkGTMoa9Ro/edit#gid=0

Framework available here:
- https://github.com/vmariani/BSMFramework/tree/CMSSW_10_2_16 (for 2016-2018) 
- https://github.com/mpresill/BSMFramework (2017, branch "HN17")

Rootple path: 
 - 2016: (MC)/eos/user/v/vmariani/NTuples/HN_2016/Syst_ALL_newMuonSF/
         (data ele)/eos/user/v/vmariani/NTuples/HN_2016/data_ele_2016.root
         (data mu) /eos/user/v/vmariani/NTuples/HN_2016/data_mu_2016.root
         
 - 2017: (MC) /eos/user/m/mpresill/CMS/HN_Reload/rootplized_samples_2017_syst/
         (data ele)/eos/user/m/mpresill/CMS/HN_Reload/rootplized_samples_2017/TriggerUpdate_0505/data_ele_2017.root
         (data mu)/eos/user/m/mpresill/CMS/HN_Reload/rootplized_samples_2017/TriggerUpdate_0505/data_mu_2017.root
 
 - 2018: (MC muon)/eos/user/v/vmariani/NTuples/HN_2018/Syst_ALL_newMuonSF/
         (data ele) 
         (data mu) 
         

Histograms for combine:
(2016) /eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2016-OldBinning/
(2017) /eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2017-OldBinning/
(2018) /eos/user/m/mpresill/CMS/HN_Reload/combine_histograms/SYST_2018-OldBinning/


Rootple for QCD estimation:
/eos/user/m/mpresill/CMS/HN_Reload/QCD_Rootplized_samples_2016/


Plots path:
 - Vale: http://test-valentina-mariani.web.cern.ch/test-valentina-mariani/HN/
 - Matteo: http://mpresill.web.cern.ch/mpresill/HN/ 

EXO pre-approval checklist: https://twiki.cern.ch/twiki/bin/viewauth/CMS/ExoPreapprovalChecklist

## Talks:
- First update talk by Roberto (to be added)
- Update talk (25 Nov 2019)  https://docs.google.com/presentation/d/1V6kgz4rxWQv_1hDuIGVuL24RRUsnkTPn5hZyoxKP2og/edit#slide=id.g59567419ba_0_0
(https://indico.cern.ch/event/865103/)
- Update talk (2 Mar 2020)
https://indico.cern.ch/event/892689/contributions/3769056/attachments/1996457/3330952/HN_updateJetX_2Mar20.pdf

## To-do list:
Targeting subgroup Jet+X update on nov 11th with:

- [x] make ntuple 2016
- [x] make ntuple 2017
- [x] make ntuple 2018
- [+] how to do properly PUweighting:
      instructions from https://github.com/UHH2/UHH2/wiki/Pileup-reweighting-for-MC
- [x] ntuple->rootple conversion (only for reference signals for now = Lambda 13 TeV) for 2016
- [x] ntuple->rootple conversion (only for reference signals for now = Lambda 13 TeV) for 2017
- [x] ntuple->rootple conversion (only for reference signals for now = Lambda 13 TeV) for 2018
- [x] Invariant mass plots for reference signal samples (L=13 TeV, M=0.5, 2, 5 TeV)
- [x] make script rootple->histograms inputs combine 
- [x] Limit extrapolation on cross section * BR (stat only, per year)
- [x] 2D Limits plot (stat only with unitarity constraint)
- [x] table with all corrections used in the framework 
- [ ] add SFs for FatJets https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetWtagging (low priority)
- [x] Optimization: check new SR definition with the estimator suggested by Niki (http://pdg.lbl.gov/2015/reviews/rpp2015-rev-statistics.pdf) for low background scenario
- [ ] Combine: run Combine Harvester for checking/validate the datacard (https://indico.cern.ch/event/859454/contributions/3655497/attachments/1954231/3245539/ValidationTools.pdf)
- [x] Combine: check all recent statistical committee racomandations (https://indico.cern.ch/event/859454/contributions/3653898/attachments/1954579/3246225/SCrec2019.pdf)

What is still needed from Roberto: 
   1. Macros for QCD/Other bkgs estimation (OK)
   2. Macros for signal systematics (not yet)
   3. Q: why do we have produced all these samples considering the Lambda independence on limit extraction?
      R: for now we don't really need to analyse all the samples (the request was made just to be sure on the Lambda independence on limit extraction) (=> check efficiency independence on Lambda at some point!)


- [ ] (add systematics on limit bands with Combine (MATTEO))
- [ ] (check limits independence on Lambda (MATTEO))
- [ ] (TTtW bkg estimate MC based (with cross section))
- [ ] (SF study for DY bkg) 
- [ ] (can we find other models for reinterpreting the results?)
- [ ] consider new versions of the model and present at MC&I group 

## Recipies for objects definition and weights:
 - pileup rewighting: using the scripts in https://github.com/mpresill/BSMFramework/tree/HN17/BSM3G_TNT_Maker/data/PUReweight
 - Muon efficiencies https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/tree/master/EfficienciesStudies
 - Muon reference for Run 2 https://twiki.cern.ch/twiki/bin/view/CMS/MuonReferenceEffsRun2
 - Electron scale factors for HHEPv70 ID:
 https://twiki.cern.ch/twiki/bin/view/CMS/EgammaRunIIRecommendations
 
 - Muon scale factors:
   -  trigger 2016 (https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2016_trigger/EfficienciesAndSF_RunGtoH.json, 
https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2016_trigger/EfficienciesAndSF_RunBtoF.json
, Mu50_OR_TkMu50_PtEtaBins), 2017 (http://kplee.web.cern.ch/kplee/TagProbe/94X/v20180202_MergingHighPtBins/theJSONfile_RunBtoF_Nov17Nov2017.json), 2018 (https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2018_trigger/theJSONfile_2018Data_AfterMuonHLTUpdate.json, Mu50_OR_OldMu100_OR_TkMu100_PtEtaBins)
   
   - ID 2016 (https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2016_legacy_rereco/systematic/RunBCDEF_SF_ID.json
, https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2016_legacy_rereco/systematic/RunGH_SF_ID.json
, NUM_HighPtID_DEN_genTracks), 2017 (https://twiki.cern.ch/twiki/pub/CMS/MuonReferenceEffs2017/RunBCDEF_SF_ID.json), 2018 ()
   
   - isolation 2016 (https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2016_legacy_rereco/systematic/RunBCDEF_SF_ISO.json, https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2016_legacy_rereco/systematic/RunGH_SF_ISO.json
, NUM_LooseRelIso_DEN_LooseID), 2017 (https://twiki.cern.ch/twiki/pub/CMS/MuonReferenceEffs2017/RunBCDEF_SF_ISO.json), 2018 (https://gitlab.cern.ch/cms-muonPOG/MuonReferenceEfficiencies/blob/master/EfficienciesStudies/2018/jsonfiles/RunABCD_SF_ID.json, NUM_HighPtID_DEN_TrackerMuons)
   
   - N.B. Since there are two different scale factor scenarios within 2016 data taking depending on the era (B-F) or (G-H) muon SFs for 2016 are computed by averageing the SF by the relative luminosity of each period and then apply a single weight to the MC: lumi(B-F)_Mu50=19.25 fb^-1, lumi(B-F)_TkMu50=16.64 fb^-1; lumi(G-H)_Mu50=16.29 fb^-1, lumi(G-H)_TkMu50=16.29 fb^-1 (Info from BrilCalc)   

  - PU reweighting:
MCscenario:
./makeMCPileupHist.py <scenario> 
2016 scenario: SimGeneral.MixingModule.mix_2016_25ns_Moriond17MC_PoissonOOTPU_cfi
2017 scenario:  SimGeneral.MixingModule.mix_2017_25ns_WinterMC_PUScenarioV1_PoissonOOTPU_cfi.py 
2018 scenario: SimGeneral.MixingModule.mix_2018_25ns_JuneProjectionFull18_PoissonOOTPU_cfi
Link utili:
https://twiki.cern.ch/twiki/bin/viewauth/CMS/PileupJSONFileforData
https://github.com/UHH2/UHH2/wiki/Pileup-reweighting-for-MC
https://github.com/cms-sw/cmssw/tree/CMSSW_10_4_X/SimGeneral/MixingModule/python



## Notes on bkg estimation:
- QCD: use "Rootplizer_HeavyNeutrino_QCD_2016.cc" for the estimation method used in the previous version of the analysis
- TTtW: CR on emu invariant mass
- DY: alpha-ratio method

## Utils
- How to find storage sites path: https://cmsweb.cern.ch/sitedb/prod/sites/
- To plot rootples: use "analisi_ele.cc"-> "StackPlots.cc"
- before plotting the root files can be merged with the script "hadd.sh"
- summary table of cross section of all samples https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
- For computing luminisity corresponding to some data selected with a particular JSON go on https://cms-service-lumi.web.cern.ch/cms-service-lumi/brilwsdoc.html
and install Brilcalc. Then type:
export PATH=$HOME/.local/bin:/cvmfs/cms-bril.cern.ch/brilconda/bin:$PATH
brilcalc lumi --hltpath HLT_OldMu100* -u /fb -i /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt
### How to run Rootplizer:
   1. make list of all ntuples to be converted into root files with "makelist*.sh"
   1. to export Muon SFs from JSON files use "SF_maker.py"
   1. export voms certificate: voms-proxy-init --voms cms --valid 192:00 --out ~/proxy
   1. run "submission_macro.sh" to submit jobs to condor (specify eos path etc etc) (check job status with condor_q)
   1. to resubmit failed jobs: ./submission_macro.sh resubmit
   
