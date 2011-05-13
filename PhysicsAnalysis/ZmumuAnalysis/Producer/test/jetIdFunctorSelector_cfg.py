import os

import FWCore.ParameterSet.Config as cms


process = cms.Process("JetIdFunctorSelector")



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
process.load("ZmumuAnalysis.Producer.JetIdFunctorSelector_cfi")
process.JetIdFunctorSelector1 = process.JetIdFunctorSelector.clone(
    jetSource = 'selectedPatJets',
    jetType = 'CALO',
    version = 'PURE09',
    quality = 'LOOSE',
)
process.JetIdFunctorSelector2 = process.JetIdFunctorSelector.clone(
    jetSource = 'selectedPatJetsAK5JPT',
    jetType = 'JPT',
    version = 'PURE09',
    quality = 'LOOSE',
)
process.JetIdFunctorSelector3 = process.JetIdFunctorSelector.clone(
    jetSource = 'selectedPatJetsAK5PF',
    jetType = 'PF',
    version = 'FIRSTDATA',
    quality = 'LOOSE',
)



## Path
process.p = cms.Path(
    #process.JetIdFunctorSelector1*   # At present, sth is broken with CALO jets...
    process.JetIdFunctorSelector2*
    process.JetIdFunctorSelector3
)



