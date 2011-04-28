import FWCore.ParameterSet.Config as cms

import ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi


GeneratorZmumuFilter = ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi.GeneratorZmumuFilter.clone()


GeneratorZmumuDiMuFilter = GeneratorZmumuFilter.clone(
    zDecayMode = [13],
)


GeneratorZmumuZMassFilterInclusive = GeneratorZmumuFilter.clone(
    zMassIntervals = [60.,120.],
)


GeneratorZmumuZMassFilterVisible = GeneratorZmumuFilter.clone(
    zMassIntervals = [76.,106.],
)


GeneratorZmumuEtaHighFilter = GeneratorZmumuFilter.clone(
    muEtaHighIntervals = [-2.4,2.4],
)


GeneratorZmumuPtLowFilter = GeneratorZmumuFilter.clone(
    muPtLowIntervals = [20.,99999.],
)


GeneratorZmumuEtaLowFilter = GeneratorZmumuFilter.clone(
    muEtaLowIntervals = [-2.1,2.1],
)


GeneratorZmumuDiMuMassFilterInclusive = GeneratorZmumuFilter.clone(
    diMuMassIntervals = [60.,120.],
)


GeneratorZmumuDiMuMassFilterVisible = GeneratorZmumuFilter.clone(
    diMuMassIntervals = [76.,106.],
)

