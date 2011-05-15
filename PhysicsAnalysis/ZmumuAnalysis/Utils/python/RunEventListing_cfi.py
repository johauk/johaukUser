import FWCore.ParameterSet.Config as cms

RunEventListing = cms.EDAnalyzer('RunEventListing',
    ## Use std::cout
    printToCommandLine = cms.bool(True),
    
    ## Print results to a text file
    printToFile = cms.bool(True),
    outputTextFile = cms.string('runEventList_cff.py'),
    
    
    ## Create a TTree containing event numbers
    createTree = cms.bool(True),
    # 
    outputRootFile = cms.string('runEventList.root'),
)
