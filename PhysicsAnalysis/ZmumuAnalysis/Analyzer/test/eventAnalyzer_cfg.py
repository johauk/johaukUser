import os

import FWCore.ParameterSet.Config as cms


process = cms.Process("EventAnalyzer")



## Message logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000 ## really show only every 1000th



process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
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



## Event Weight
process.load("ZmumuAnalysis.Utils.EventWeight_cff")



## Analyzer under test
process.load("ZmumuAnalysis.Analyzer.EventAnalyzer_cfi")
process.EventAnalyzer1 = process.EventAnalyzer.clone(
    jetSource = "selectedPatJetsAK5PF",
    metSource = "patMETsPF",
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
    process.makeEventWeights*
    process.EventAnalyzer1*
    process.selectedDimuons*
    process.EventAnalyzer2
)
