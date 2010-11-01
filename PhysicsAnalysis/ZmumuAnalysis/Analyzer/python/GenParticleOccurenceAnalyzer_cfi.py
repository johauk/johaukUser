import FWCore.ParameterSet.Config as cms

GenParticleOccurenceAnalyzer = cms.EDAnalyzer('GenParticleOccurenceAnalyzer',
    # generator particle collection
    src = cms.InputTag("genParticles"),
    
    # filter via PDG-ID on occurence of particle in full list of all generated particles
    # careful result interpretation: e.g. in Pythia every Z appears twice, once with status 3 and as its own daughter with status 2
    # but for quarks it seems to be correct
    # default: b-quark
    particleOccurence = cms.vint32(5),
)
