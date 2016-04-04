from WMCore.Configuration import Configuration
config = Configuration()

from CRABClient.UserUtilities import getUsernameFromSiteDB
config.section_('General')
config.General.requestName = 'PbPb2015_PromptReco_MinBias4_full'
config.General.transferOutputs = True
config.General.transferLogs = True
config.section_('JobType')
config.JobType.outputFiles = ['PbPb2015_PromptReco_MinBias4.root']
config.JobType.pyCfgParams = ['noprint']
config.JobType.pluginName = 'Analysis'

# Name of the input CMSSW configuration file
config.JobType.psetName = '/afs/cern.ch/work/w/wmcbraye/private/CMSSW_7_5_7_patch1/src/crab/RunForwardAnalyzer_PbPb2015.py'

config.JobType.maxJobRuntimeMin = 1315
config.section_('Data')
config.Data.inputDataset = '/HIMinimumBias4/HIRun2015-PromptReco-v1/AOD'

config.Data.runRange = '262548-263757'
config.Data.unitsPerJob = 20
config.Data.publication = False
config.Data.splitting = 'LumiBased'

# Construct the output dataset name
config.Data.outLFNDirBase = '/store/user/wmcbraye'
config.Data.lumiMask = 'Cert_262548-263757_PromptReco_HICollisions15_JSON.txt'
config.section_('User')
config.section_('Site')
config.Site.whitelist = ['T2_US_Vanderbilt']
config.Site.storageSite = 'T2_US_Vanderbilt'


if __name__ == '__main__':
    
    from CRABAPI.RawCommand import crabCommand
    from httplib import HTTPException
            
# We want to put all the CRAB project directories from the tasks we submit here into one common directory.
# That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = 'crab_projects'
                
    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException, hte:
            print hte.headers


submit(config)

# Modify to add additional PDs (datasets)
#
#config.General.requestName = 'PbPb2015_HIMinimumBias3_Check'
#config.Data.inputDataset = '/HIMinimumBias3/HIRun2015-PromptReco-v1/AOD'
#config.Data.outLFNDirBase = '/store/user/ssanders/PbPb2015_HIMinimumBias3_Check'
#submit(config)
#
#config.General.requestName = 'PbPb2015_HIMinimumBias4_Check'
#config.Data.inputDataset = '/HIMinimumBias4/HIRun2015-PromptReco-v1/AOD'
#config.Data.outLFNDirBase = '/store/user/ssanders/PbPb2015_HIMinimumBias4_Check'
#submit(config)
#
