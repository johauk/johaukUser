import FWCore.ParameterSet.Config as cms

EventAnalyzer = cms.EDAnalyzer('EventAnalyzer',
    # muon collection
    muonSource = cms.InputTag("selectedPatMuons"),
    # jet collection
    jetSource = cms.InputTag("selectedPatJets"),
    # missingEt collection
    metSource = cms.InputTag("patMETs"),
    
    # switch to add plots for di-muons (only possible if dimuon collection exists already)
    analyzeDiMuons = cms.bool(False),
    # di-muon collection (not used when switch analyzeDiMuons is set to False)
    diMuonSource = cms.InputTag("selectedDimuons"),
)
