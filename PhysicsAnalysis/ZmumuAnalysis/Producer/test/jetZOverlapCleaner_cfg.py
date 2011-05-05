import os

import FWCore.ParameterSet.Config as cms


process = cms.Process("DiMuonAnalyzer")



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
    cut = #'daughter(0).isGlobalMuon = 1' +'&'+
	  #'daughter(1).isGlobalMuon = 1' +'&'+
	  'mass > 0',
    decay = 'selectedPatMuons@+ selectedPatMuons@-',
)



## Analyzer under test
process.load("ZmumuAnalysis.Producer.JetZOverlapCleaner_cfi")
process.JetZOverlapCleaner1 = process.JetZOverlapCleaner.clone(
    #jetSource = 'selectedPatJets',
    #dimuonSource = 'selectedDimuons',
    #deltaRMin = 0.5,
)



## Path
process.p = cms.Path(
    process.selectedDimuons*
    process.JetZOverlapCleaner1
)
