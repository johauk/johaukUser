import FWCore.ParameterSet.Config as cms

VertexAnalyzer = cms.EDAnalyzer('VertexAnalyzer',
    # vertex collection
    vertexSource = cms.InputTag("offlinePrimaryVertices"),
)
