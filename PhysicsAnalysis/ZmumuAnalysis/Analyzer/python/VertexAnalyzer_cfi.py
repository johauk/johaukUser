import FWCore.ParameterSet.Config as cms

VertexAnalyzer = cms.EDAnalyzer('VertexAnalyzer',
    # Event weight source
    eventWeightSource = cms.InputTag("EventWeight"),
    
    # vertex collection
    vertexSource = cms.InputTag("offlinePrimaryVertices"),
)
