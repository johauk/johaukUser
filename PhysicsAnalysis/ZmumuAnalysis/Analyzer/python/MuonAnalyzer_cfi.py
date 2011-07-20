import FWCore.ParameterSet.Config as cms

MuonAnalyzer = cms.EDAnalyzer('MuonAnalyzer',
    # muon collection
    muonSource = cms.InputTag("selectedPatMuons"),
    
    # which histograms to book
    # possibilities are "major", "basic", "veryBasic"
    whichHists = cms.string("major"),
)
