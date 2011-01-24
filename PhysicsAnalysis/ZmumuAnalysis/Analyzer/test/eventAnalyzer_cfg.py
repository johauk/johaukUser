import os

import FWCore.ParameterSet.Config as cms


process = cms.Process("EventAnalyzer")



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



## Input Source
process.load("ZmumuAnalysis.Configuration.samples.testSample_cff")



process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1001) )



## di-muon candidate producer
from ElectroWeakAnalysis.Skimming.dimuons_cfi import *
process.selectedDimuons = dimuons.clone(
    checkCharge = False,
    cut = 'daughter(0).isGlobalMuon = 1' +'&'+
          'daughter(1).isGlobalMuon = 1' +'&'+
          'mass > 0',
    decay = 'selectedPatMuons@+ selectedPatMuons@-',
)



## Analyzer under test
process.load("ZmumuAnalysis.Analyzer.EventAnalyzer_cfi")
process.EventAnalyzer1 = process.EventAnalyzer.clone(
    #src = 'selectedPatMuons',
)
process.EventAnalyzer2 = process.EventAnalyzer1.clone(
    analyzeDiMuons = True,
    #diMuonSource = "selectedDimuons",
)



## Output File Configuration
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Analyzer/hists/test_eventAnalyzer.root'),
    closeFileFast = cms.untracked.bool(True)
)



## Path
process.p = cms.Path(
    process.EventAnalyzer1
    *process.selectedDimuons
    *process.EventAnalyzer2
)
