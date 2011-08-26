import os

import FWCore.ParameterSet.Config as cms


process = cms.Process("TriggerAnalyzer")



## Message logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000 ## really show only every 1000th


process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
)



## Input Source
process.load("ZmumuAnalysis.Configuration.samples.testSample_cff")



process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1001) )



## Event Weight
process.load("ZmumuAnalysis.Utils.EventWeight_cff")



## Analyzer under test
process.load("ZmumuAnalysis.Analyzer.TriggerAnalyzer_cfi")
process.TriggerAnalyzer1 = process.TriggerAnalyzer.clone(
    #triggerResults = cms.InputTag('TriggerResults','','REDIGI311X'),
    printTriggerNames = True,
)
process.TriggerAnalyzer2 = process.TriggerAnalyzer1.clone(
    hltPaths = [
      'HLT_DoubleMu7_v*',
      'HLT_IsoMu17_v*',
      'HLT_Mu30_v*',
    ],
    printTriggerNames = False,
)



## Output File Configuration
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Analyzer/hists/test_triggerAnalyzer.root'),
    closeFileFast = cms.untracked.bool(True)
)



## Path
process.p = cms.Path(
    process.makeEventWeights*(
    process.TriggerAnalyzer1+
    process.TriggerAnalyzer2
    )
)
