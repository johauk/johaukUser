import FWCore.ParameterSet.Config as cms

DimuonAnalyzer = cms.EDAnalyzer('DimuonAnalyzer',
    # Event weight source
    eventWeightSource = cms.InputTag("EventWeight"),
    
    # di-muon collection (not yet in common PAT-tuple)
    dimuonSource = cms.InputTag("selectedDimuons"),
)
