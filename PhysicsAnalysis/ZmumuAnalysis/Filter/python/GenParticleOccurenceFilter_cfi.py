import FWCore.ParameterSet.Config as cms

GenParticleOccurenceFilter = cms.EDFilter('GenParticleOccurenceFilter',
    # generator particle collection
    src = cms.InputTag("genParticles"),
    
    
    # filter on occurence of particle in full list of all generated particles
    # default: b-quark
    particleOccurence = cms.vint32(5),
)
