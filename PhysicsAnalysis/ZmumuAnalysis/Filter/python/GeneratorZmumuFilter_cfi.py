import FWCore.ParameterSet.Config as cms

GeneratorZmumuFilter = cms.EDFilter('GeneratorZmumuFilter',
    # generator particle collection
    src = cms.InputTag("genParticles"),
    
    
    ## Default: all filters inactivated, but filter for at least one Z->xx
    # filter on Z decay mode via PDG-id: default is muon(13)
    zDecayMode = cms.vint32(13),
    
    # all variable names are like in Z->mumu case, but act universally on Z->xx
    
    
    # filter on quark origin of qqbar->Z (down=1, up=2, strange=3, charm=4, bottom=5)
    zQuarkOrigin = cms.vint32(),
    
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
