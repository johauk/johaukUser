import os

import FWCore.ParameterSet.Config as cms


process = cms.Process("RunEventListingFromTree")



## Message logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories.append('RunEventListing')
process.MessageLogger.cerr.RunEventListing = cms.untracked.PSet(limit = cms.untracked.int32(-1))
process.MessageLogger.cerr.FwkReport.reportEvery = 1000 ## really show only every 1000th



process.options = cms.untracked.PSet(
    #wantSummary = cms.untracked.bool(True),
)



## Input Source
process.source = cms.Source("EmptySource")



process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )



## Analyzer under test
process.load("ZmumuAnalysis.Utils.RunEventListing_cfi")
process.RunEventListingFromTree1 = process.RunEventListingFromTree.clone(
    #getEventsFromTree = True,
    inputTreeFile = 'hists/runEventList.root',
    inputPluginName = 'RunEventListing1',
    #printToCommandLine = False,
    #printToFile = False,
    outputTextFile = os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Utils/hists/runEventListFromTree_cff.py',
    #createTree = False,
)



## Path
process.p = cms.Path(
    process.RunEventListingFromTree1
)



