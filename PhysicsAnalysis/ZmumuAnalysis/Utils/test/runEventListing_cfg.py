import os

import FWCore.ParameterSet.Config as cms


process = cms.Process("RunEventListing")



## Message logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000 ## really show only every 1000th



process.options = cms.untracked.PSet(
    #wantSummary = cms.untracked.bool(True),
)



## Input Source
process.load("ZmumuAnalysis.Configuration.samples.testSample_cff")



process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(11) )



## Analyzer under test
process.load("ZmumuAnalysis.Utils.RunEventListing_cfi")
process.RunEventListing1 = process.RunEventListing.clone(
    printToFile = False,
    outputFile = 'test.txt',
)



## Testing the input for list of selected events
process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(
    '160955:1',
    '160955:1',
)
process.source.eventsToProcess = cms.untracked.VEventRange(
    '160955:1:2314',
    '160955:1:262062',
    '160955:1:50000-160955:1:150000',
)



## Path
process.p = cms.Path(
    process.RunEventListing1
)



