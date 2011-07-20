import os

import FWCore.ParameterSet.Config as cms


process = cms.Process("DimuonAnalyzer")



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
process.load("ZmumuAnalysis.Analyzer.DimuonAnalyzer_cfi")
process.DimuonAnalyzer1 = process.DimuonAnalyzer.clone(
    #dimuonSource = 'selectedDimuons',
)



## Output File Configuration
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Analyzer/hists/test_dimuonAnalyzer.root'),
    closeFileFast = cms.untracked.bool(True)
)



## Path
process.p = cms.Path(
    process.selectedDimuons*
    process.DimuonAnalyzer1
)
