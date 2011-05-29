import FWCore.ParameterSet.Config as cms



genParticleSelector = cms.EDFilter("GenParticleSelector",
    filter = cms.bool(False),
    src = cms.InputTag('genParticles'),
    cut = cms.string(''),
)
