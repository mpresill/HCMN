if __name__ == '__main__':
 #####
 ##   Multicrab configuration
 #####
 import sys
 from CRABClient.UserUtilities import config, getUsernameFromSiteDB
 config = config()
 from CRABAPI.RawCommand import crabCommand
 from CRABClient.ClientExceptions import ClientException
 from httplib import HTTPException
 config.General.workArea = 'crab_projects_18'

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

#'Autumn18_TT', 
#'Autumn18_ST',
#'Autumn18_SaT',
#'Autumn18_ZZ',
#'Autumn18_WZ',
#'Autumn18_WW',
#'Autumn18_WJetsHT70To100',
#'Autumn18_WJetsHT100To200',
#'Autumn18_WJetsHT200To400',
#'Autumn18_WJetsHT400To600',
#'Autumn18_WJetsHT600To800',
#'Autumn18_WJetsHT800To1200',
#'Autumn18_WJetsHT1200To2500',
#'Autumn18_WJetsHT2500ToInf',
#'Autumn18_WJets_',
#'Autumn18_DY',

#Signal mumu
'mumujj_18_L13_M500',
'mumujj_18_L13_M1000',
'mumujj_18_L13_M2000',
#'mumujj_18_L13_M5000',
#'mumujj_18_L13_M8000',

#Signal ee
#'eejj_18_L13_M500',
#'eejj_18_L13_M1000',
#'eejj_18_L13_M2000',
#'eejj_18_L13_M5000',
#'eejj_18_L13_M8000',
                 ]
 datasetinputs = [
#BKG
#'/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM',
#'/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v1/MINIAODSIM',
#'/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15_ext1-v1/MINIAODSIM',
#'/ZZ_TuneCP5_13TeV-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM',
#'/WZ_TuneCP5_13TeV-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v3/MINIAODSIM',
#'/WW_TuneCP5_13TeV-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM',
#'/WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM',
#'/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM',
#'/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM',
#'/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM',
#'/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM',
#'/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM',
#'/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM',
#'/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM',
#'/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v2/MINIAODSIM',
#'/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM',

#signal mumu
'/HeavyCompositeMajoranaNeutrino_L13000_M500_mumujj_CalcHep/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM',
'/HeavyCompositeMajoranaNeutrino_L13000_M1000_mumujj_CalcHep/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM',
'/HeavyCompositeMajoranaNeutrino_L13000_M2000_mumujj_CalcHep/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L13000_M5000_mumujj_CalcHep/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L13000_M8000_mumujj_CalcHep/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM',

#Signal ee
#'/HeavyCompositeMajoranaNeutrino_L13000_M500_eejj_CalcHep/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L13000_M1000_eejj_CalcHep/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L13000_M2000_eejj_CalcHep/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L13000_M5000_eejj_CalcHep/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM',
#'/HeavyCompositeMajoranaNeutrino_L13000_M8000_eejj_CalcHep/RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1/MINIAODSIM',
                ]


#for d in range(len(datasetnames)):
for d in range(0,len(datasetnames)):
    print 'multicrab.py: Running datasetname: ', datasetnames[d]

    
    lepFilt = 1
    nameLepFilt = 'optionlepfilt={}'.format(lepFilt) 
    
    config.section_('General')
    config.General.requestName = datasetnames[d]
    #config.General.workArea    = datasetnames[d]
    config.General.transferLogs = True

    config.General.instance = 'prod'
    config.section_('JobType')
    config.JobType.pluginName  = 'Analysis'
    # List of parameters to pass to CMSSW parameter-set configuration file:
    config.JobType.psetName    = '/afs/cern.ch/user/v/vmariani/CMSSW_10_2_16_UL/src/BSMFramework/BSM3G_TNT_Maker/python/miniAOD_MC2018.py'
    config.JobType.inputFiles = ['/afs/cern.ch/user/v/vmariani/CMSSW_10_2_16_UL/src/BSMFramework/BSM3G_TNT_Maker/data/QG/QGL_AK4chs_94X.db']
    config.JobType.sendExternalFolder = True
    config.JobType.maxMemoryMB = 2000 # Default == 2Gb : maximum guaranteed to run on all sites
    #config.JobType.allowUndistributedCMSSW = True
    ofParam = 'ofName=' + datasetnames[d]
    config.JobType.pyCfgParams = [nameLepFilt,
                                    ofParam]
    config.section_('Data')
    config.Data.allowNonValidInputDataset = True
    config.Data.inputDataset   = datasetinputs[d]
    config.Data.inputDBS       = 'global'
    #config.Data.splitting      = 'FileBased'
    #config.Data.totalUnits     = 40000 #With 'FileBased' splitting tells how many files to analyse
    config.Data.splitting      = 'Automatic'
    config.Data.unitsPerJob    = 180
    config.Data.outputDatasetTag = datasetnames[d]

    #config.Data.publication = True

    config.section_('Site')
    config.Site.storageSite    = 'T2_IT_Bari'#'T2_CH_CERN' # Site to which output is permenantly copied by crab3
    print 'multicrab.py: Submitting Jobs'
    submit(config)
