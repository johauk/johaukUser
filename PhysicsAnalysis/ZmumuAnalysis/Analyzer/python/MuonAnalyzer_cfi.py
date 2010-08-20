import FWCore.ParameterSet.Config as cms

MuonAnalyzer = cms.EDAnalyzer('MuonAnalyzer',
    # muon collection
    muonSource = cms.InputTag("selectedPatMuons"),
)
