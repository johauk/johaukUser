import FWCore.ParameterSet.Config as cms



import Alignment.CommonAlignmentProducer.AlignmentTrackSelector_cfi



##
## FILTER for high purity tracks
##
HighPuritySelector = Alignment.CommonAlignmentProducer.AlignmentTrackSelector_cfi.AlignmentTrackSelector.clone(
    applyBasicCuts = True,
    filter = True,
    src = 'ALCARECOTkAlMinBias',
    etaMin = -999.,
    etaMax = 999.,
    trackQualities = ["highPurity"],
)




MinBiasSkimSelector = Alignment.CommonAlignmentProducer.AlignmentTrackSelector_cfi.AlignmentTrackSelector.clone(
    applyBasicCuts = True,
    filter = True,
    src = 'ALCARECOTkAlMinBias',
    ptMin = 5.,
    pMin = 9.,
    etaMin = -999.,
    etaMax = 999.,
    d0Min = -2.,
    d0Max = 2.,
    dzMin = -15.,
    dzMax = 15.,
    nHitMin = 12,
    nHitMin2D = 2,
    trackQualities = ["highPurity"],
)



MuSkimSelector = Alignment.CommonAlignmentProducer.AlignmentTrackSelector_cfi.AlignmentTrackSelector.clone(
    applyBasicCuts = True,
    filter = True,
    src = 'ALCARECOTkAlMuonIsolated',
    ptMin = 5.,
    pMin = 9.,
    etaMin = -2.5,
    etaMax = 2.5,
    d0Min = -10.,
    d0Max = 10.,
    dzMin = -50.,
    dzMax = 50.,
    nHitMin = 6,
    nHitMin2D = 0,
    trackQualities = ["highPurity"],
)





