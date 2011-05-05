import FWCore.ParameterSet.Config as cms


JetZOverlapCleaner = cms.EDProducer('JetZOverlapCleaner',
    # jet collection
    jetSource = cms.InputTag("selectedPatJets"),
    
    # Z collection
    dimuonSource = cms.InputTag("selectedDimuons"),
    
    # Minimum allowed deltaR between jet and both muons of Z
    deltaRMin = cms.double(0.5),
)
