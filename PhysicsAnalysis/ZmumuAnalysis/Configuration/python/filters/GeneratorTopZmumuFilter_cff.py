import FWCore.ParameterSet.Config as cms

import ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi



GeneratorZmumuDiMuFilter = ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi.GeneratorZmumuFilter.clone(
    zDecayMode = [13],
)




GeneratorZmumuDiMuMassFilterFinal = GeneratorZmumuDiMuFilter.clone(
    diMuMassIntervals = [60.,120.],
)




GeneratorZmumuDiMuMassFilterVisible = GeneratorZmumuDiMuFilter.clone(
    diMuMassIntervals = [76.,106.],
)


GeneratorZmumuEtaFilterVisible = GeneratorZmumuDiMuFilter.clone(
    etaIntervals = [-2.4,2.4],
)


GeneratorZmumuPtFilterVisible = GeneratorZmumuDiMuFilter.clone(
    ptIntervals = [20.,99999.],
)
