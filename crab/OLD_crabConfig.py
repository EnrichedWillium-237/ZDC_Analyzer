from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'PbPb2015_PromptReco_MinBias3_262988-263022'
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
# Name of the CMSSW configuration file
config.JobType.psetName = 'RunForwardAnalyzer_PbPb2015.py'

config.Data.inputDataset = '/HIMinimumBias2/HIRun2015-PromptReco-v1/AOD'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 500
config.Data.publication = False
# This string is used to construct the output dataset name
#config.Data.outputDatasetTag = 'HIExpress_HIRun2015-v1_HIL1MinimumBiasHFstarTrig'
#config.outputFiles  = 'ForwardAnalyzerRun262694_ZeroBiasPromptReco_HF.root' #not necessary
config.Data.outLFNDirBase = '/store/user/wmcbraye'

# These values only make sense for processing data
#    Select input data based on a lumi mask
#config.Data.lumiMask = 'Cert_190456-208686_8TeV_PromptReco_Collisions12_JSON.txt'
#    Select input data based on run-ranges
config.Data.runRange = '262988-263022'

# Where the output files will be transmitted to
#config.Site.storageSite = 'T2_US_MIT'
#config.Site.storageSite = 'T2_US_Purdue'
config.Site.storageSite = 'T2_US_Vanderbilt'
