import FWCore.ParameterSet.Config as cms


BestZSelector = cms.EDProducer('BestZSelector',
    # Z collection
    dimuonSource = cms.InputTag("selectedDimuons"),
    
    # Which criterion to use
    criterion = cms.string('zMass'),
)
