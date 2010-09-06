import FWCore.ParameterSet.Config as cms

GeneratorZmumuFilter = cms.EDFilter('GeneratorZmumuFilter',
    # generator particle collection
    src = cms.InputTag("genParticles"),
    
    ## Default: all filters inactivated, but filter for at least one Z->mumu
    
    ## Cut on Z/dimuon properties
    # filter on eta difference
    diMuDeltaEtaIntervals = cms.vdouble(),
    # filter on phi difference
    diMuDeltaPhiIntervals = cms.vdouble(),
    # filter on invariant mass (use intervals w/ even no. of elements, do not filter if empty)
    diMuMassIntervals = cms.vdouble(),
    # filter for Z pt (use intervals w/ even no. of elements, do not filter if empty)
    diMuPtIntervals = cms.vdouble(),
    
    ## Cut on muon properties
    etaIntervals = cms.vdouble(),
    ptIntervals = cms.vdouble(),
)
