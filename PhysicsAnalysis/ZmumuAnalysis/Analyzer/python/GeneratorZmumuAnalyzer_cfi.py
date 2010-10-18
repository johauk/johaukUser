import FWCore.ParameterSet.Config as cms

GeneratorZmumuAnalyzer = cms.EDAnalyzer('GeneratorZmumuAnalyzer',
    # generator particle collection
    src = cms.InputTag("genParticles"),
    
    # analyze only given Z->xx decay mode via PDG-id: default is muon(13)
    zDecayMode = cms.vint32(13),
)
