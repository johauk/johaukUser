import FWCore.ParameterSet.Config as cms

GenParticleAnalyzer = cms.EDAnalyzer('GenParticleAnalyzer',
    # generator particle collection
    src = cms.InputTag("genParticles"),
)
