import os

import FWCore.ParameterSet.Config as cms


process = cms.Process("DiMuonFilter")



## Message logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000 ## really show only every 1000th


process.options = cms.untracked.PSet(
    #wantSummary = cms.untracked.bool(True),
    Rethrow = cms.untracked.vstring("ProductNotFound"), # make this exception fatal
    # fileMode  =  cms.untracked.string('FULLMERGE'), # any file order (default): caches all lumi/run products (memory!)
    # fileMode  =  cms.untracked.string('MERGE'), # needs files sorted in run and within run in lumi sections (hard to achieve)
    # fileMode  =  cms.untracked.string('FULLLUMIMERGE'), # needs files sorted in run, caches lumi
     fileMode  =  cms.untracked.string('NOMERGE'), #  no ordering needed, but calls endRun/beginRun etc. at file boundaries
)



process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1001) )



## Input Source
process.load("ZmumuAnalysis.Configuration.samples.testSample_cff")



## Analyzer under test
process.load("ZmumuAnalysis.Filter.DiMuonFilter_cfi")
process.DiMuonFilter1 = process.DiMuonFilter.clone(
    #src = 'selectedPatMuons',
    massIntervals = [0.,1.,2.],
)



## Path
process.p = cms.Path(
    process.DiMuonFilter1
)
