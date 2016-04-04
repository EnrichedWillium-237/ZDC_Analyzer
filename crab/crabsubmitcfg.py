from CRABClient.UserUtilities import config
config = config()
config.General.requestName = 'PbPb2015_PromptReco_MinBias2_263099'
config.General.transferLogs = True
config.General.transferOutputs = True
config.section_('JobType')
config.JobType.outputFiles = ['PbPb2015_PromptReco_MinBias2_263099.root']
config.JobType.pyCfgParams = ['noprint']
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'RunForwardAnalyzer_PbPb2015shell.py'
config.Data.inputDataset = '/HIMinimumBias2/HIRun2015-PromptReco-v1/AOD'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 20
config.Data.publication = False
lumi_mask='Cert_262548-263757_PromptReco_HICollisions15_JSON.txt'
config.Data.outLFNDirBase = '/store/user/wmcbraye'
config.Data.runRange = '263099'
config.Site.storageSite = 'T2_US_Vanderbilt'
