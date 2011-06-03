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
process.source = cms.Source("EmptySource")



process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )



## Analyzer
process.load("ZmumuAnalysis.Utils.RunEventListing_cff")
process.RunEventListingFromTreeTemplate = process.RunEventListingFromTree.clone(
    inputTreeFile = os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/data/allData.root',
    #inputTreeFile = os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/fullSelection.root',
)


# The only thing to change: moduleNumber
moduleNumber = "5"
process.RunEventListingFromTree5 = process.RunEventListingFromTreeTemplate.clone(
    inputPluginName = 'RunEventListing' + moduleNumber,
    outputTextFile = os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/data/runEventList' + moduleNumber + '_cff.py',
    #outputTextFile = os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/runEventList' + moduleNumber + '_cff.py',
)
moduleNumber = "6"
process.RunEventListingFromTree6 = process.RunEventListingFromTreeTemplate.clone(
    inputPluginName = 'RunEventListing' + moduleNumber,
    outputTextFile = os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/data/runEventList' + moduleNumber + '_cff.py',
    #outputTextFile = os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/runEventList' + moduleNumber + '_cff.py',
)
moduleNumber = "7"
process.RunEventListingFromTree7 = process.RunEventListingFromTreeTemplate.clone(
    inputPluginName = 'RunEventListing' + moduleNumber,
    outputTextFile = os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/data/runEventList' + moduleNumber + '_cff.py',
    #outputTextFile = os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/runEventList' + moduleNumber + '_cff.py',
)



## Path
process.p = cms.Path(
    process.RunEventListingFromTree5*
    process.RunEventListingFromTree6*
    process.RunEventListingFromTree7
)



