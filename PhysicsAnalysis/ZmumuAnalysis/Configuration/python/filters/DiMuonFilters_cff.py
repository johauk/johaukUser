import FWCore.ParameterSet.Config as cms

import ZmumuAnalysis.Filter.DiMuonFilter_cfi



DiMuonMassFilter = ZmumuAnalysis.Filter.DiMuonFilter_cfi.DiMuonFilter.clone(
    massIntervals = [80.,100.],
)



DiMuonChargeFilter = ZmumuAnalysis.Filter.DiMuonFilter_cfi.DiMuonFilter.clone(
    allowSameCharge = False,
)
