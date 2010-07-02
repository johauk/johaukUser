import FWCore.ParameterSet.Config as cms

EventAnalyzer = cms.EDAnalyzer('EventAnalyzer',
    # muon collection
    muonSource = cms.InputTag("selectedPatMuons"),
    # jet collection
    jetSource = cms.InputTag("selectedPatJets"),
    # missingEt collection
    metSource = cms.InputTag("patMETs"),
)
