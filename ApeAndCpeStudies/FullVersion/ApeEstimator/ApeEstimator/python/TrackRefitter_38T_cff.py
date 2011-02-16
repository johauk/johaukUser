import FWCore.ParameterSet.Config as cms



## GEOMETRY
from Configuration.StandardSequences.Geometry_cff import *



## CONDITIONS
from Configuration.StandardSequences.FrontierConditions_GlobalTag_cff import *



## MAGNETIC FIELD
#from Configuration.StandardSequences.MagneticField_0T_cff import *
from Configuration.StandardSequences.MagneticField_cff import *



## BEAM SPOT
from RecoVertex.BeamSpotProducer.BeamSpot_cfi import *



## CPE (combine StripCPEgeometric with standard-PixelCPE)
from RecoLocalTracker.SiStripRecHitConverter.StripCPEgeometric_cfi import *
#StripCPEgeometricESProducer.APVpeakmode = True # not included anymore, coupling constants for crosstalk and outOfTime parameters taken from conditions
TTRHBuilderGeometricAndTemplate = cms.ESProducer("TkTransientTrackingRecHitBuilderESProducer",
    #StripCPE = cms.string('StripCPEfromTrackAngle'), # cms.string('StripCPEgeometric'),
    StripCPE = cms.string('StripCPEgeometric'),
    ComponentName = cms.string('WithGeometricAndTemplate'),
    #PixelCPE = cms.string('PixelCPEGeneric'),
    PixelCPE = cms.string('PixelCPETemplateReco'),
    Matcher = cms.string('StandardMatcher'),
    ComputeCoarseLocalPositionFromDisk = cms.bool(False)
)



## TRACK REFITTER (input for Track Selector)
from RecoTracker.TrackProducer.TrackRefitters_cff import *
# -- Maximal contribution of individual hit to chi2 value of track fit, e.g. = 20. means normalized residual < sqrt(20.)
# not used when < 0.
FittingSmootherRKP5.EstimateCut = -1.
# -- some cut on pixel hit probability
# not used when < -15.
FittingSmootherRKP5.LogPixelProbabilityCut = -16.
# -- do not know what exactly this track rejection does
FittingSmootherRKP5.RejectTracks = False
# -- two track segments if true or only "first" one ???
FittingSmootherRKP5.BreakTrajWith2ConsecutiveMissing = False
TrackRefitterForApeEstimator = RecoTracker.TrackProducer.TrackRefitters_cff.TrackRefitterP5.clone(
    src = 'ALCARECOTkAlCosmicsCTF0T' #'ALCARECOTkAlCosmicsCosmicTF0T' #'ALCARECOTkAlCosmicsCosmicTF'
          #'ALCARECOTkAlCosmicsCTF' #'ALCARECOTkAlCosmicsRS0T' #'ALCARECOTkAlCosmicsRS'
    ,TTRHBuilder = 'WithGeometricAndTemplate'     # use StripCPEgeometric instead of standard
    #,AlgorithmName = 'ctf'  #'cosmics' #'rs' #'beamhalo'
    #,TrajectoryInEvent = False
    ,NavigationSchool = ''
)

TrackRefitterHighPurityForApeEstimator = TrackRefitterForApeEstimator.clone(
    src = 'HighPuritySelector'
)



## FILTER for high purity tracks
import Alignment.CommonAlignmentProducer.AlignmentTrackSelector_cfi
HighPuritySelector = Alignment.CommonAlignmentProducer.AlignmentTrackSelector_cfi.AlignmentTrackSelector.clone(
    applyBasicCuts = True,
    filter = True,
    src = 'ALCARECOTkAlMinBias',
    etaMin = -999.,
    etaMax = 999.,
    trackQualities = ["highPurity"],
)



## SEQUENCE
RefitterSequence = cms.Sequence(offlineBeamSpot
                                *TrackRefitterForApeEstimator
)

RefitterHighPuritySequence = cms.Sequence(
    offlineBeamSpot
    *HighPuritySelector
    *TrackRefitterHighPurityForApeEstimator
)



