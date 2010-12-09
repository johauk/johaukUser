import FWCore.ParameterSet.Config as cms

MetAnalyzer = cms.EDAnalyzer('MetAnalyzer',
    # missingEt collection
    metSource = cms.InputTag("patMETs"),
)
