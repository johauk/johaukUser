import FWCore.ParameterSet.Config as cms



genParticleCountFilter = cms.EDFilter("CandViewCountFilter",
    src = cms.InputTag('genParticles'),
    minNumber = cms.uint32(1),
)
