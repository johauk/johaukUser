import FWCore.ParameterSet.Config as cms


TriggerMatchedMuonProducer = cms.EDProducer('TriggerMatchedMuonProducer',
    # muon collection
    muonSource = cms.InputTag("selectedPatMuons"),
    
    matches = cms.string('muonTriggerMatchHLTMuons'),
    triggerEvent = cms.InputTag("patTriggerEvent"),
)
