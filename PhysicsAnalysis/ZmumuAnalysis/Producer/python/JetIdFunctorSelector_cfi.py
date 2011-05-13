import FWCore.ParameterSet.Config as cms


JetIdFunctorSelector = cms.EDProducer('JetIdFunctorSelector',
    # jet collection
    jetSource = cms.InputTag("selectedPatJetsAK5PF"),
    
    # jet type to use
    jetType = cms.string("PF"),
    
    # 
    version = cms.string("FIRSTDATA"),
    
    # 
    quality = cms.string("LOOSE"),
)
