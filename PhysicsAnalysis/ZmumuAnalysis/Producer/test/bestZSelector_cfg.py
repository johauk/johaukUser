import os

import FWCore.ParameterSet.Config as cms


process = cms.Process("BestZVertexCleaner")



## Message logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.debugModules = ["BestZSelector1"]
process.MessageLogger.cerr.threshold = 'DEBUG'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000 ## really show only every 1000th



process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
)



## Input Source
process.load("ZmumuAnalysis.Configuration.samples.testSample_cff")



process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(101) )



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
process.load("ZmumuAnalysis.Producer.BestZSelector_cfi")
process.BestZSelector1 = process.BestZSelector.clone(
    #dimuonSource = 'selectedDimuons',
    #criterion = 'zMass',
)



## Path
process.p = cms.Path(
    process.selectedDimuons*
    process.BestZSelector1
)





