import FWCore.ParameterSet.Config as cms

import ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi



GeneratorZmumuDiMuMassFilter = ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi.GeneratorZmumuFilter.clone(
    diMuMassIntervals = [60.,120.],
)


GeneratorZmumuEtaFilter = ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi.GeneratorZmumuFilter.clone(
    etaIntervals = [-2.4,2.4],
)


GeneratorZmumuPtFilter = ZmumuAnalysis.Filter.GeneratorZmumuFilter_cfi.GeneratorZmumuFilter.clone(
    ptIntervals = [20.,99999.],
)
