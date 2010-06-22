import FWCore.ParameterSet.Config as cms

DiMuonFilter = cms.EDFilter('DiMuonFilter',
    # muon collection
    muonSource = cms.InputTag("selectedPatMuons"),
    
    ## Default: all filters inactivated
    
    # filter on charge
    allowSameCharge = cms.bool(True),
    allowOppositeCharge = cms.bool(True),
    # filter on eta difference
    deltaEtaIntervals = cms.vdouble(),
    # filter on phi difference
    deltaPhiIntervals = cms.vdouble(),
    # filter on invariant mass (use intervals w/ even no. of elements, do not filter if empty)
    massIntervals = cms.vdouble(),
    # filter for pt (use intervals w/ even no. of elements, do not filter if empty)
    ptIntervals = cms.vdouble(),
    
)
