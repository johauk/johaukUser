import FWCore.ParameterSet.Config as cms

EventWeight = cms.EDProducer("EventWeight",
    eventWeightSources = cms.VInputTag(),
)




