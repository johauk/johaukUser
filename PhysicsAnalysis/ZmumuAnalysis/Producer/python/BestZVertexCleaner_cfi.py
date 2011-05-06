import FWCore.ParameterSet.Config as cms


BestZVertexCleaner = cms.EDProducer('BestZVertexCleaner',
    # What collection to produce? Dimuons or Vertices?
    product = cms.string("dimuon"), #"vertex"
    
    # Z collection
    dimuonSource = cms.InputTag("selectedDimuons"),
    
    # vertex collection
    vertexSource = cms.InputTag("offlinePrimaryVertices"),
    
    # Maximum allowed distance along z between vertex and Z
    deltaZMax = cms.double(0.1),
)
