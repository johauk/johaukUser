import os

import FWCore.ParameterSet.Config as cms


process = cms.Process("DiMuonFilter")



## Message logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories.append('DiMuonFilter')
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



## Filter under test
process.load("ZmumuAnalysis.Filter.DiMuonFilter_cfi")
process.DiMuonFilter1 = process.DiMuonFilter.clone(
    #src = 'selectedPatMuons',
    allowSameCharge = False,
    #allowOppositeCharge = False,
    deltaEtaIntervals = [-1.,2.],
    deltaPhiIntervals = [-1.,3.],
    massIntervals = [0.,30.,80.,100.],
    ptIntervals = [0.,30.,50.,60.,100.,110.],
)



## Analyzer
process.load("ZmumuAnalysis.Analyzer.DiMuonAnalyzer_cfi")
process.DiMuonAnalyzer1 = process.DiMuonAnalyzer.clone(
    #src = 'selectedPatMuons',
)



## Output File Configuration
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Filter/hists/test_diMuonFilter.root'),
    closeFileFast = cms.untracked.bool(True)
)



## Path
process.p = cms.Path(
    process.DiMuonFilter1
    *process.DiMuonAnalyzer1
)
