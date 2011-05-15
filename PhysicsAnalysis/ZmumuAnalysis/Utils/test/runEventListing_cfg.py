import os

import FWCore.ParameterSet.Config as cms


process = cms.Process("RunEventListing")



## Message logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories.append('RunEventListing')
process.MessageLogger.cerr.RunEventListing = cms.untracked.PSet(limit = cms.untracked.int32(-1))
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
    #printToCommandLine = False,
    #printToFile = False,
    outputTextFile = os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Utils/hists/runEventList_cff.py',
    #createTree = False,
)



## Testing the input for list of selected events
#process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange(
#    '160955:1',
#    '160955:1',
#)
#process.source.eventsToProcess = cms.untracked.VEventRange(
#    '160955:1:2314',
#    '160955:1:262062',
#    '160955:1:50000-160955:1:150000',
#)



## Output File Configuration
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Utils/hists/runEventListing.root'),
    closeFileFast = cms.untracked.bool(True)
)



## Path
process.p = cms.Path(
    process.RunEventListing1
)



