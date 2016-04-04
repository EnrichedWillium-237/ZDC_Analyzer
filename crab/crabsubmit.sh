#!/bin/bash

minBiasSet=HIMinimumBias2 ####change the minbias dataset you want

python ./das_client.py --query="run dataset=/$minBiasSet/HIRun2015-PromptReco-v1/AOD" --limit=0 > filelist.txt


while IFS='' read -r line || [[ -n "$line" ]]; do
  runNumber=$line
  echo "from CRABClient.UserUtilities import config" > crabsubmitcfg.py
  echo "config = config()" >> crabsubmitcfg.py
  echo "config.General.requestName = 'PbPb2015_PromptReco_MinBias2_$runNumber'" >> crabsubmitcfg.py
  echo "config.General.transferLogs = True" >> crabsubmitcfg.py
  echo "config.General.transferOutputs = True" >> crabsubmitcfg.py
  echo "config.section_('JobType')" >> crabsubmitcfg.py
  echo "config.JobType.outputFiles = ['PbPb2015_PromptReco_MinBias2_$runNumber.root']" >> crabsubmitcfg.py
  echo "config.JobType.pyCfgParams = ['noprint']" >> crabsubmitcfg.py
  echo "config.JobType.pluginName = 'Analysis'" >> crabsubmitcfg.py
  echo "config.JobType.psetName = 'RunForwardAnalyzer_PbPb2015shell.py'" >> crabsubmitcfg.py
  echo "config.Data.inputDataset = '/$minBiasSet/HIRun2015-PromptReco-v1/AOD'" >> crabsubmitcfg.py
  echo "config.Data.splitting = 'LumiBased'" >> crabsubmitcfg.py
  echo "config.Data.unitsPerJob = 20" >> crabsubmitcfg.py
  echo "config.Data.publication = False" >> crabsubmitcfg.py
  echo "lumi_mask='Cert_262548-263757_PromptReco_HICollisions15_JSON.txt'" >> crabsubmitcfg.py
  echo "config.Data.outLFNDirBase = '/store/user/wmcbraye'" >> crabsubmitcfg.py
  echo "config.Data.runRange = '$runNumber'" >> crabsubmitcfg.py
  echo "config.Site.storageSite = 'T2_US_Vanderbilt'" >> crabsubmitcfg.py
  
  echo "import FWCore.ParameterSet.Config as cms" > RunForwardAnalyzer_PbPb2015shell.py
  echo "import sys" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process = cms.Process(\"Forward\")" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.load(\"FWCore.MessageService.MessageLogger_cfi\")" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.load('Configuration.StandardSequences.GeometryRecoDB_cff')" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.load('Configuration/StandardSequences/Reconstruction_cff')" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.load(\"RecoLocalCalo.HcalRecProducers.HcalHitReconstructor_hf_cfi\")" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.load(\"RecoLocalCalo.HcalRecProducers.HcalHitReconstructor_zdc_cfi\")" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.load(\"EventFilter.CastorRawToDigi.CastorRawToDigi_cfi\")" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.load(\"RecoLocalCalo.CastorReco.CastorSimpleReconstructor_cfi\")" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.load('RecoLocalTracker.SiPixelRecHits.PixelCPEESProducers_cff')" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.load('Analyzers.ForwardAnalyzer.HIClusterCompatibilityFilter_cfi')" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.clusterCompatibilityFilter.clusterPars = cms.vdouble(0.0,0.006)" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.load(\"CondCore.DBCommon.CondDBSetup_cfi\")" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.MessageLogger.cerr.FwkReport.reportEvery = 1000" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.source = cms.Source(\"PoolSource\",fileNames = cms.untracked.vstring())" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_v12', '')" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.load(\"RecoHI.HiCentralityAlgos.CentralityBin_cfi\")" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.TFileService = cms.Service(\"TFileService\",fileName=cms.string('PbPb2015_PromptReco_MinBias2_$runNumber.root'))" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "import HLTrigger.HLTfilters.hltHighLevel_cfi" >> RunForwardAnalyzer_PbPb2015shell.py                                                                
  echo "process.hltMinBias = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.hltMinBias.HLTPaths = [\"HLT_HIL1MinimumBiasHF1AND_*\",\"HLT_HIL1MinimumBiasHF2AND_*\"]" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.fwdana = cms.EDAnalyzer('ForwardAnalyzer', CentralitySrc = cms.InputTag(\"hiCentrality\"), CentralityBinSrc = cms.InputTag(\"centralityBin\",\"HFtowers\"), trackSrc = cms.InputTag(\"hiGeneralTracks\"), vtxCollection_ = cms.InputTag(\"hiSelectedVertex\"))" >> RunForwardAnalyzer_PbPb2015shell.py
  echo "process.p = cms.Path(process.hfCoincFilter3 *process.primaryVertexFilter *process.clusterCompatibilityFilter *process.centralityBin *process.hltMinBias *process.fwdana)" >> RunForwardAnalyzer_PbPb2015shell.py
  
  
  crab submit -c crabsubmitcfg.py #uncomment to actually submit jobs. test with this commented first.
  echo "Submitted run number $runNumber from $minBiasSet dataset to crab"
  
done < "filelist.txt"


#clean up
rm crabsubmitcfg.py
rm RunForwardAnalyzer_PbPb2015shell.py
rm filelist.txt
rm crabsubmitcfg.pyc
rm RunForwardAnalyzer_PbPb2015shell.pyc