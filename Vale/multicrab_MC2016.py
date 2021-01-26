if __name__ == '__main__':
 #####
 ##   Multicrab configuration
 #####
 import sys
 from CRABClient.UserUtilities import config
 config = config()
 from CRABAPI.RawCommand import crabCommand
 from CRABClient.ClientExceptions import ClientException
 from httplib import HTTPException
 config.General.workArea = 'crab_projects_16'

 def submit(config):
  try:
   crabCommand('submit', config = config)
  except HTTPException as hte:
   print "Failed submitting task: %s" % (hte.headers)
  except ClientException as cle:
   print "Failed submitting task: %s" % (cle)
 #####
 ##   Crab configuration
 #####
 datasetnames  = [
#background
#'Summer16V3_TT', 
#'Summer16V3_ST',
#'Summer16V3_SaT',
#'Summer16V3_ZZ_1',
#'Summer16V3_ZZ_2',
#'Summer16V3_WZ_1',
#'Summer16V3_WZ_2',
#'Summer16V3_WW_1',
#'Summer16V3_WW_2',
#'Summer16V3_WJetsHT70To100',
#'Summer16V3_WJetsHT100To200_1',
#'Summer16V3_WJetsHT100To200_2',
#'Summer16V3_WJetsHT100To200_3',
#'Summer16V3_WJetsHT200To400_1',
#'Summer16V3_WJetsHT200To400_2',
#'Summer16V3_WJetsHT200To400_3',
#'Summer16V3_WJetsHT400To600_1',
#'Summer16V3_WJetsHT400To600_2',
#'Summer16V3_WJetsHT600To800_1',
#'Summer16V3_WJetsHT600To800_2',
#'Summer16V3_WJetsHT800To1200_1',
#'Summer16V3_WJetsHT800To1200_2',
#'Summer16V3_WJetsHT1200To2500_1',
#'Summer16V3_WJetsHT1200To2500_2_',
#'Summer16V3_WJetsHT2500ToInf_1',
#'Summer16V3_WJetsHT2500ToInf_2_', 
#'Summer16V3_WJets_1',
#'Summer16V3_WJets_2',
#'Summer16V3_DY_1',
#'Summer16V3_DY_2',
#'Summer16V3_DY_HT70To100',
#'Summer16V3_DY_HT100To200',
#'Summer16V3_DY_HT100To200_ext',
#'Summer16V3_DY_HT200To400',
#'Summer16V3_DY_HT200To400_ext',
#'Summer16V3_DY_HT400To600',
#'Summer16V3_DY_HT400To600_ext',
#'Summer16V3_DY_HT600To800',
#'Summer16V3_DY_HT800To1200',
#'Summer16V3_DY_HT1200To2500',
#'Summer16V3_DY_HT2500ToInf',
#'Summer16V3_DY_FxFx',
'Summer16V3_QCD_HT50To100',
'Summer16V3_QCD_HT100To200',
'Summer16V3_QCD_HT200To300',
'Summer16V3_QCD_HT200To300_ext',
'Summer16V3_QCD_HT300To500',
'Summer16V3_QCD_HT300To500_ext',
'Summer16V3_QCD_HT500To700',
'Summer16V3_QCD_HT500To700_ext',
'Summer16V3_QCD_HT700To1000',
'Summer16V3_QCD_HT700To1000_ext',
'Summer16V3_QCD_HT1000To1500',
'Summer16V3_QCD_HT1000To1500_ext',
'Summer16V3_QCD_HT1500To2000',
'Summer16V3_QCD_HT1500To2000_ext',
'Summer16V3_QCD_HT2000ToInf',
'Summer16V3_QCD_HT2000ToInf_ext',
'Summer16V3_TTWJets_ext1',
'Summer16V3_TTWJets_ext2',
'Summer16V3_TTWJetsToQQ',
'Summer16V3_TTZJets',

#Signal mumujj
#'mumujj_16_L13_M500',
#'mumujj_16_L13_M1000',
#'mumujj_16_L13_M2000',
#'mumujj_16_L13_M5000',
#'mumujj_16_L13_M8000',
#'mumujj_16_L4_M1000',
#'mumujj_16_L6_M1000',
#'mumujj_16_L7_M500',
#'mumujj_16_L7_M1000',
#'mumujj_16_L7_M2000',
#'mumujj_16_L7_M3000',
#'mumujj_16_L7_M4000',
#'mumujj_16_L7_M5000',
#'mumujj_16_L7_M6000',
#'mumujj_16_L7_M7000',
#'mumujj_16_L11_M500',
#'mumujj_16_L11_M1000',
#'mumujj_16_L11_M2000',
#'mumujj_16_L11_M4000',
#'mumujj_16_L11_M7000',
#'mumujj_16_L17_M500',
#'mumujj_16_L17_M1000',
#'mumujj_16_L17_M2000',
#'mumujj_16_L17_M7000',
#'mumujj_16_L15_M1000',
#'mumujj_16_L20_M1000',


#Signal eejj
#'eejj_16_L13_M500',
#'eejj_16_L13_M1000',
#'eejj_16_L13_M2000',
#'eejj_16_L13_M5000',
#'eejj_16_L13_M8000',

#'eejj_16_L7_M500',
#'eejj_16_L7_M1000',
#'eejj_16_L7_M2000',
#'eejj_16_L7_M3000',
#'eejj_16_L7_M4000',
#'eejj_16_L7_M5000',
#'eejj_16_L7_M6000',
#'eejj_16_L7_M7000',
#'eejj_16_L11_M1000',
#'eejj_16_L11_M2000',
#'eejj_16_L11_M4000',
#'eejj_16_L11_M7000',
#'eejj_16_L17_M500',
#'eejj_16_L17_M1000',
#'eejj_16_L17_M2000',
#'eejj_16_L17_M7000',

                 ]
 datasetinputs = [
#BKG
#'/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM',
#'/ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM',
#'/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
#'/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
#'/WZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
#'/WZ_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
#'/WW_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
#'/WW_TuneCUETP8M1_13TeV-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
#'/WJetsToLNu_HT-70To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
#'/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
#'/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM',
#'/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
#'/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
#'/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
#'/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM',
#'/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
#'/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
#'/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
#'/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
#'/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
#'/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
#'/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
#'/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
#'/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
#'/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
#'/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
#'/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM',
#'/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
#'/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM',
#'/DYJetsToLL_M-50_HT-70to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
#'/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
#'/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
#'/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
#'/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
#'/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
#'/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
#'/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
#'/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1/MINIAODSIM',

'/QCD_HT50to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
'/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
'/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
'/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
'/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
'/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
'/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
'/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
'/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM',
'/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1/MINIAODSIM',
'/TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM',
'/ttZJets_13TeV_madgraphMLM-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',

#mumu jj
#'/HeavyCompositeMajoranaNeutrino_L13000_M500_mumujj_CalcHep_2019/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L13000_M1000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L13000_M2000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L13000_M5000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L13000_M8000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L4000_M1000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L6000_M1000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L7000_M500_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L7000_M1000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L7000_M2000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L7000_M3000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L7000_M4000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L7000_M5000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L7000_M6000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L7000_M7000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L11000_M500_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L11000_M1000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L11000_M2000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L11000_M4000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L11000_M7000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L17000_M500_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L17000_M1000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L17000_M2000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L17000_M7000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L11000_M1000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L15000_M1000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L20000_M1000_mumujj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',

#ee jj

#'/HeavyCompositeMajoranaNeutrino_L13000_M500_eejj_CalcHep_2019/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L13000_M1000_eejj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L13000_M2000_eejj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L13000_M5000_eejj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L13000_M8000_eejj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',

#'/HeavyCompositeMajoranaNeutrino_L7000_M500_eejj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L7000_M1000_eejj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L7000_M2000_eejj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L7000_M3000_eejj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L7000_M4000_eejj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L7000_M5000_eejj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L7000_M6000_eejj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L7000_M7000_eejj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L11000_M1000_eejj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L11000_M2000_eejj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L11000_M4000_eejj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L11000_M7000_eejj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L17000_M500_eejj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L17000_M1000_eejj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L17000_M2000_eejj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L17000_M7000_eejj_CalcHep/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM',
                ]

baseDir = "/afs/cern.ch/user/v/vmariani/CMSSW_10_2_16_UL/src/BSMFramework/"

configs = []
k = 0

for d in range(0,len(datasetnames)):
#for d in range(0,1):
    print 'multicrab.py: Running datasetname: ', datasetnames[d]

    lepFilt = 1
    nameLepFilt = 'optionlepfilt={}'.format(lepFilt)
    config.section_('General')
    config.General.requestName = datasetnames[d]
    #config.General.workArea    = datasetnames[d]
    config.General.transferLogs = True

    config.section_('JobType')
    config.JobType.pluginName  = 'Analysis'
    # List of parameters to pass to CMSSW parameter-set configuration file:
    config.JobType.psetName    = baseDir+'BSM3G_TNT_Maker/python/miniAOD_MC2016.py'
    config.JobType.inputFiles = [(baseDir+'BSM3G_TNT_Maker/data/QG/QGL_AK4chs_94X.db')]
    config.JobType.sendExternalFolder = True
    config.JobType.maxMemoryMB = 2000 # Default == 2Gb : maximum guaranteed to run on all sites
    #config.JobType.allowUndistributedCMSSW = True
    ofParam = 'ofName=' + datasetnames[d]
    config.JobType.pyCfgParams = [nameLepFilt,
                                    ofParam]
    config.section_('Data')
    config.General.instance = 'prod'
    config.Data.allowNonValidInputDataset = True
    config.Data.inputDataset   = datasetinputs[d]
    config.Data.inputDBS       = 'global'
    config.Data.splitting      = 'FileBased'
    #config.Data.splitting      = 'Automatic'
    config.Data.unitsPerJob    = 1
    config.Data.outputDatasetTag = datasetnames[d]

    #config.Data.publication = True

    config.section_('Site')
    config.Site.storageSite    = 'T2_IT_Legnaro'#'T2_CH_CERN' # Site to which output is permenantly copied by crab3
    print 'multicrab.py: Submitting Jobs'
    configs.append(config) 
    submit(configs[k])
    k+=1
