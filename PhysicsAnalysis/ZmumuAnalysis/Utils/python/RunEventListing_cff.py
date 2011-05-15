import os

import FWCore.ParameterSet.Config as cms

from ZmumuAnalysis.Utils.RunEventListing_cfi import RunEventListing


RunEventListingCreateTreeOnly = RunEventListing.clone(
    printToCommandLine = False,
    printToFile = False,
    
)



RunEventListingFromTree = RunEventListing.clone(
    getEventsFromTree = True,
    inputTreeFile = os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/data/allData.root',
    inputPluginName = 'RunEventListing9',
    printToCommandLine = False,
    outputTextFile = os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/data/runEventList_cff.py',
    createTree = False,   # Allows empty input source (and TTree exists already!!!)
)


