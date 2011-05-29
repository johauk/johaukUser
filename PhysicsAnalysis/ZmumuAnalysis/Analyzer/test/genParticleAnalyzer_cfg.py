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



# Create collection of b quarks
process.selectedBs = cms.EDFilter("GenParticleSelector",
    filter = cms.bool(False),
    src = cms.InputTag('genParticles'),
    cut = cms.string('abs(pdgId)=5'),
)
process.selectedBs.filter = True



## Analyzer under test
process.load("ZmumuAnalysis.Analyzer.GenParticleAnalyzer_cfi")
process.GenParticleAnalyzer1 = process.GenParticleAnalyzer.clone(
    src = 'selectedBs',
)



## Output File Configuration
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Analyzer/hists/test_genParticleAnalyzer.root'),
    closeFileFast = cms.untracked.bool(True)
)



## Path
process.p = cms.Path(
    process.selectedBs*
    process.GenParticleAnalyzer1
)
