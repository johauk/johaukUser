
import FWCore.ParameterSet.Config as cms

import ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi



## Default Config
GeneratorZmumuFilter = ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi.GeneratorZmumuFilter.clone()



## Decay process
GeneratorZmumuDiMuFilter = GeneratorZmumuFilter.clone(
    zDecayMode = [13],
)

GeneratorZmumuDiTauFilter = GeneratorZmumuFilter.clone(
    zDecayMode = [15],
)



## Z properties
GeneratorZmumuZMassFilter = GeneratorZmumuFilter.clone(
    zMassIntervals = [60.,120.],
)



## Dimuon properties
GeneratorZmumuDiMuMassFilter = GeneratorZmumuFilter.clone(
    diMuMassIntervals = [60.,120.],
)



## Muon properties
GeneratorZmumuEtaHighFilter = GeneratorZmumuFilter.clone(
    muEtaHighIntervals = [-2.4,2.4],
)

GeneratorZmumuEtaLowFilter = GeneratorZmumuFilter.clone(
    muEtaLowIntervals = [-2.1,2.1],
)

GeneratorZmumuEtaHighFilter = GeneratorZmumuFilter.clone(
    muEtaHighIntervals = [-2.1,2.1],
)

GeneratorZmumuPtLowFilter = GeneratorZmumuFilter.clone(
    muPtLowIntervals = [20.,99999.],
)



## Quark origin
GeneratorZmumuUdsFilter = ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi.GeneratorZmumuFilter.clone(
    zQuarkOrigin = [1,2,3],
)

GeneratorZmumuCFilter = ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi.GeneratorZmumuFilter.clone(
    zQuarkOrigin = [4],
)

GeneratorZmumuBFilter = ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi.GeneratorZmumuFilter.clone(
    zQuarkOrigin = [5],
)









