import FWCore.ParameterSet.Config as cms

MetAnalyzer = cms.EDAnalyzer('MetAnalyzer',
    # Event weight source
    eventWeightSource = cms.InputTag("EventWeight"),
    
    # missingEt collection
    metSource = cms.InputTag("patMETs"),
)
