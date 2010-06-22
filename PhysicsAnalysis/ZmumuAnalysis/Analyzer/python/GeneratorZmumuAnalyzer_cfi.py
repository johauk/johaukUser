import FWCore.ParameterSet.Config as cms

GeneratorZmumuAnalyzer = cms.EDAnalyzer('GeneratorZmumuAnalyzer',
    # generator particle collection
    src = cms.InputTag("genParticles"),
    
    # lower Z mass cut
    massZMin = cms.double(-999.),
    # upper Z mass cut
    massZMax = cms.double(99999.),
    # muon eta cut
    absEtaMuMax = cms.double(99999.),
)
