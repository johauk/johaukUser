import FWCore.ParameterSet.Config as cms

import ZmumuAnalysis.Filter.DiMuonFilter_cfi



DiMuonOppositeChargeFilter = ZmumuAnalysis.Filter.DiMuonFilter_cfi.DiMuonFilter.clone(
    allowSameCharge = False,
)



DiMuonSameChargeFilter = ZmumuAnalysis.Filter.DiMuonFilter_cfi.DiMuonFilter.clone(
    allowOppositeCharge = False,
)



DiMuonMassFilter = ZmumuAnalysis.Filter.DiMuonFilter_cfi.DiMuonFilter.clone(
    massIntervals = [80.,100.],
)



DiMuonChargeFilter = ZmumuAnalysis.Filter.DiMuonFilter_cfi.DiMuonFilter.clone(
    allowSameCharge = False,
)
