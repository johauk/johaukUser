import FWCore.ParameterSet.Config as cms

DimuonAnalyzer = cms.EDAnalyzer('DimuonAnalyzer',
    # di-muon collection (not yet in common PAT-tuple)
    dimuonSource = cms.InputTag("selectedDimuons"),
)
