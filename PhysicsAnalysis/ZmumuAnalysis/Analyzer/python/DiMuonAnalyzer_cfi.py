import FWCore.ParameterSet.Config as cms

DiMuonAnalyzer = cms.EDAnalyzer('DiMuonAnalyzer',
    # muon collection
    muonSource = cms.InputTag("selectedPatMuons"),
    
    # only events with exactly 2 selected muons, or also with more than 2
    exactlyTwoMuons = cms.bool(False),
)
