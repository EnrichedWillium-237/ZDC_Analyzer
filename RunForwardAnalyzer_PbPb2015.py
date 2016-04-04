import FWCore.ParameterSet.Config as cms
import sys

#if len(sys.argv) > 2:
 #   file=open(sys.argv[2])
  #  outfile=sys.argv[3]

process = cms.Process("Forward")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load('Configuration/StandardSequences/Reconstruction_cff')
process.load("RecoLocalCalo.HcalRecProducers.HcalHitReconstructor_hf_cfi")
process.load("RecoLocalCalo.HcalRecProducers.HcalHitReconstructor_zdc_cfi")
process.load("EventFilter.CastorRawToDigi.CastorRawToDigi_cfi")
process.load("RecoLocalCalo.CastorReco.CastorSimpleReconstructor_cfi")
process.load('RecoLocalTracker.SiPixelRecHits.PixelCPEESProducers_cff')

# Event selection recommendations (not final)
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('Analyzers.ForwardAnalyzer.HIClusterCompatibilityFilter_cfi') # manually changed
process.clusterCompatibilityFilter.clusterPars = cms.vdouble(0.0,0.006)


process.load("CondCore.DBCommon.CondDBSetup_cfi")


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )

process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( *(
                                                                 '/store/hidata/HIRun2015/HIMinimumBias2/AOD/PromptReco-v1/000/262/893/00000/044148AE-C1A7-E511-AA08-02163E011928.root',
                                                                 '/store/hidata/HIRun2015/HIMinimumBias2/AOD/PromptReco-v1/000/262/893/00000/127119EF-C1A7-E511-A7B3-02163E014345.root',
                                                                 '/store/hidata/HIRun2015/HIMinimumBias2/AOD/PromptReco-v1/000/262/893/00000/18BD7DAC-C1A7-E511-9419-02163E01194A.root',
                                                                 '/store/hidata/HIRun2015/HIMinimumBias2/AOD/PromptReco-v1/000/262/893/00000/2078ABC0-C1A7-E511-B68F-02163E012042.root'
                                                                 ) )
                            )

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
# pp 2015
#process.GlobalTag = GlobalTag(process.GlobalTag, '74X_dataRun2_HLT_ppAt5TeV_v0', '')
# PbPb 2015
# for prompt reco:
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_v12', '')
# for express stream
#process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_ExpressHI_v2', '')
# for Monte Carlo
#process.GlobalTag = GlobalTag(process.GlobalTag, '75X_mcRun2_HeavyIon_v11', '')

# load centralityBin producer
process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")

# the below works for HF calo towers
##process.centralityBin.Centrality = cms.InputTag("hiCentrality")
##process.centralityBin.centralityVariable = cms.string("HFtowers")



# load centrality
#process.HeavyIonGlobalParameters = cms.PSet(
#	centralityVariable = cms.string("HFhits"),
#	nonDefaultGlauberModel = cms.string(""),
#	centralitySrc = cms.InputTag("hiCentrality")
#)

# process.hltbitanalysis = cms.EDAnalyzer("HLTBitAnalyzer",
#                                         ### Trigger objects
#                                         l1GctHFBitCounts                = cms.InputTag("gctDigis"),
#                                         l1GctHFRingSums                 = cms.InputTag("gctDigis"),
#                                         l1GtObjectMapRecord             = cms.InputTag("hltL1GtObjectMap::HLT"),
#                                         l1GtReadoutRecord               = cms.InputTag("gtDigis::RECO"),
#                                         
#                                         l1extramc                       = cms.string('l1extraParticles'),
#                                         l1extramu                       = cms.string('l1extraParticles'),
#                                         hltresults                      = cms.InputTag("TriggerResults::HLT"),
#                                         HLTProcessName                  = cms.string("HLT"),
#                                         UseTFileService                 = cms.untracked.bool(True),
#                                         
#                                         ### Run parameters
#                                         RunParameters = cms.PSet(
#     HistogramFile = cms.untracked.string('hltbitanalysis.root',')
#     )
#                                         )##end of HLT

# ###L1 Stuff
# process.GtDigis = cms.EDProducer( "L1GlobalTriggerRawToDigi",
#                                   #DaqGtInputTag = cms.InputTag( "rawDataRepacker" ),
#                                   DaqGtInputTag = cms.InputTag("rawDataCollector"),
#                                   DaqGtFedId = cms.untracked.int32( 813 ),
#                                   ActiveBoardsMask = cms.uint32( 0xffff ),
#                                   UnpackBxInEvent = cms.int32( 5 ),
#                                   Verbosity = cms.untracked.int32( 0 )
#                                   )##END of L1 Stuff

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('test.root')
                                   )
                                   
import HLTrigger.HLTfilters.hltHighLevel_cfi                                                                     
process.hltMinBias = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltMinBias.HLTPaths = [
                               "HLT_HIL1MinimumBiasHF1AND_*",
                               "HLT_HIL1MinimumBiasHF2AND_*"
]

process.fwdana = cms.EDAnalyzer('ForwardAnalyzer'
                                , CentralitySrc = cms.InputTag("hiCentrality")
                                , CentralityBinSrc = cms.InputTag("centralityBin","HFtowers")
                                , trackSrc = cms.InputTag("hiGeneralTracks")
                                , vtxCollection_ = cms.InputTag("hiSelectedVertex")
)

# process.upcvertexana = cms.EDAnalyzer('UPCVertexAnalyzer',
#                                       vertexCollection=cms.string("offlinePrimaryVerticesWithBS")
#                                       )
# process.whatever = cms.Path(process.hltMinBias * process.your_analyzer)
                                      
process.p = cms.Path(process.hfCoincFilter3 *
                     process.primaryVertexFilter *
                     process.clusterCompatibilityFilter *
                     process.centralityBin *
                     process.hltMinBias *
                     process.fwdana
)
#process.p = cms.Path(process.zdcreco*process.fwdana)
#process.p = cms.Path(process.fwdana*process.upcvertexana)
