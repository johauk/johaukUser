import FWCore.ParameterSet.Config as cms

DiMuonAnalyzer = cms.EDAnalyzer('DiMuonAnalyzer',
    # di-muon collection (not yet in common PAT-tuple)
    diMuonSource = cms.InputTag("selectedDimuons"),
)
