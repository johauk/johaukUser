import FWCore.ParameterSet.Config as cms

RunEventListing = cms.EDAnalyzer('RunEventListing',
    ## run full analyzer mode or get events from TTree
    ## (previously created with same plugin)
    getEventsFromTree = cms.bool(False),
    inputTreeFile = cms.string('inputRunEventList.root'),
    # With which plugin created (exact name)?
    inputPluginName = cms.string('RunEventListing'),
    
    ## Use std::cout
    printToCommandLine = cms.bool(True),
    
    ## Print results to a text file
    printToFile = cms.bool(True),
    outputTextFile = cms.string('runEventList_cff.py'),
    
    ## Create a TTree containing event numbers
    createTree = cms.bool(True),
)


