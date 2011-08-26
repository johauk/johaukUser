import os

import FWCore.ParameterSet.Config as cms


process = cms.Process("JetAnalyzer")



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
process.load("ZmumuAnalysis.Analyzer.JetAnalyzer_cfi")
process.JetAnalyzer1 = process.JetAnalyzer.clone(
    #jetSource = 'selectedPatJets',       # not in present PAT-tuple
    jetSource = 'selectedPatJetsAK5PF',
    #jetSource = 'selectedPatJetsAK5JPT', # not in present PAT-tuple
)
process.JetAnalyzer2 = process.JetAnalyzer1.clone(
    whichHists = "basic",
)



## Output File Configuration
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Analyzer/hists/test_jetAnalyzer.root'),
    closeFileFast = cms.untracked.bool(True)
)



## Path
process.p = cms.Path(
    process.makeEventWeights*(
    process.JetAnalyzer1+
    process.JetAnalyzer2
    )
)
