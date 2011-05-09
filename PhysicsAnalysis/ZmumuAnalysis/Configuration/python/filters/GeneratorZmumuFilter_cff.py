import FWCore.ParameterSet.Config as cms

import ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi




GeneratorZmumuFilter = ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi.GeneratorZmumuFilter.clone(
    zDecayMode = [13],
)

GeneratorZtautauFilter = ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi.GeneratorZmumuFilter.clone(
    zDecayMode = [15],
)






GeneratorZmumuUdsFilter = ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi.GeneratorZmumuFilter.clone(
    zQuarkOrigin = [1,2,3],
)


GeneratorZmumuCFilter = ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi.GeneratorZmumuFilter.clone(
    zQuarkOrigin = [4],
)


GeneratorZmumuBFilter = ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi.GeneratorZmumuFilter.clone(
    zQuarkOrigin = [5],
)


GeneratorZmumuDiMuMassFilter = ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi.GeneratorZmumuFilter.clone(
    diMuMassIntervals = [60.,120.],
)


GeneratorZmumuEtaFilter = ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi.GeneratorZmumuFilter.clone(
    muEtaHighIntervals = [-2.4,2.4],
)


GeneratorZmumuPtFilter = ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi.GeneratorZmumuFilter.clone(
    muPtLowIntervals = [20.,99999.],
)
