import FWCore.ParameterSet.Config as cms

RunEventListing = cms.EDAnalyzer('RunEventListing',
    printToFile = cms.bool(True),
    outputFile = cms.string('testRunEventList.txt'),
)
