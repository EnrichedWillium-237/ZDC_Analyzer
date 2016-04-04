import FWCore.ParameterSet.Config as cms
import sys
process = cms.Process("Forward")
process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration/StandardSequences/Reconstruction_cff')
process.load("RecoLocalCalo.HcalRecProducers.HcalHitReconstructor_hf_cfi")
process.load("RecoLocalCalo.HcalRecProducers.HcalHitReconstructor_zdc_cfi")
process.load("EventFilter.CastorRawToDigi.CastorRawToDigi_cfi")
process.load("RecoLocalCalo.CastorReco.CastorSimpleReconstructor_cfi")
process.load('RecoLocalTracker.SiPixelRecHits.PixelCPEESProducers_cff')
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('Analyzers.ForwardAnalyzer.HIClusterCompatibilityFilter_cfi')
process.clusterCompatibilityFilter.clusterPars = cms.vdouble(0.0,0.006)
process.load("CondCore.DBCommon.CondDBSetup_cfi")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.source = cms.Source("PoolSource",fileNames = cms.untracked.vstring())
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_v12', '')
process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.TFileService = cms.Service("TFileService",fileName=cms.string('PbPb2015_PromptReco_MinBias2_263099.root'))
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltMinBias = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltMinBias.HLTPaths = ["HLT_HIL1MinimumBiasHF1AND_*","HLT_HIL1MinimumBiasHF2AND_*"]
process.fwdana = cms.EDAnalyzer('ForwardAnalyzer', CentralitySrc = cms.InputTag("hiCentrality"), CentralityBinSrc = cms.InputTag("centralityBin","HFtowers"), trackSrc = cms.InputTag("hiGeneralTracks"), vtxCollection_ = cms.InputTag("hiSelectedVertex"))
process.p = cms.Path(process.hfCoincFilter3 *process.primaryVertexFilter *process.clusterCompatibilityFilter *process.centralityBin *process.hltMinBias *process.fwdana)
