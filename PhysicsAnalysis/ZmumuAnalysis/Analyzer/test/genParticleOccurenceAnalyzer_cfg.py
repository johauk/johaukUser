import os

import FWCore.ParameterSet.Config as cms


process = cms.Process("GenParticleOccurenceAnalyzer")



## Message logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000 ## really show only every 1000th



process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
)



## Input Source
process.load("ZmumuAnalysis.Configuration.samples.testSample_cff")



process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1001) )



## Analyzer under test
process.load("ZmumuAnalysis.Analyzer.GenParticleOccurenceAnalyzer_cfi")
process.GenParticleOccurenceAnalyzer1 = process.GenParticleOccurenceAnalyzer.clone(
    #particleOccurence = [5],
)



## Output File Configuration
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Analyzer/hists/test_genParticleOccurenceAnalyzer.root'),
    closeFileFast = cms.untracked.bool(True)
)



## Path
process.p = cms.Path(
    process.GenParticleOccurenceAnalyzer1
)
