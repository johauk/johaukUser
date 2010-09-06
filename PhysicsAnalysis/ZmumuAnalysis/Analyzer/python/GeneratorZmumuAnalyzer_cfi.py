import FWCore.ParameterSet.Config as cms

GeneratorZmumuAnalyzer = cms.EDAnalyzer('GeneratorZmumuAnalyzer',
    # generator particle collection
    src = cms.InputTag("genParticles"),
)
