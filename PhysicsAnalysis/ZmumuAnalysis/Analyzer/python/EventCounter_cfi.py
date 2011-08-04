import FWCore.ParameterSet.Config as cms

EventCounter = cms.EDAnalyzer('EventCounter',
    # Event weight source
    eventWeightSource = cms.InputTag("EventWeight"),
)
