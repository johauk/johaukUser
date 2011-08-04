import os

import FWCore.ParameterSet.Config as cms


process = cms.Process("MuonAnalyzer")



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
process.load("ZmumuAnalysis.Utils.EventWeight_cfi")



## Analyzer under test
process.load("ZmumuAnalysis.Analyzer.MuonAnalyzer_cfi")
process.MuonAnalyzer1 = process.MuonAnalyzer.clone(
    #src = 'selectedPatMuons',
)
process.MuonAnalyzer2 = process.MuonAnalyzer1.clone(
    whichHists = "basic",
)
process.MuonAnalyzer3 = process.MuonAnalyzer2.clone(
    whichHists = "veryBasic",
)




## Output File Configuration
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Analyzer/hists/test_muonAnalyzer.root'),
    closeFileFast = cms.untracked.bool(True)
)



## Path
process.p = cms.Path(
    process.EventWeight*(
    process.MuonAnalyzer1+
    process.MuonAnalyzer2+
    process.MuonAnalyzer3
    )
)
