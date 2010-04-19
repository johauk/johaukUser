import FWCore.ParameterSet.Config as cms



## GEOMETRY
from Configuration.StandardSequences.Geometry_cff import *



## CONDITIONS
from Configuration.StandardSequences.FrontierConditions_GlobalTag_cff import *
## --- Ideal MonteCarlo ---
#GlobalTag.globaltag = 'DESIGN_3X_V8B::All'    # peak mode
#GlobalTag.globaltag = 'MC_3XY_V9B::All'    # same, but bad channels are masked
## --- First ReProcessing (CRAFT '09) ---
GlobalTag.globaltag = 'CRAFT09_R_V4::All'



## ALIGNMENT CONSTANTS & APE (set to zero)
#from CalibTracker.Configuration.Common.PoolDBESSource_cfi import *
import CalibTracker.Configuration.Common.PoolDBESSource_cfi

#myTrackerAlignment = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(
#    connect = 'frontier://FrontierProd/CMS_COND_31X_FROM21X', # or your sqlite file
#    toGet = cms.VPSet(
#      cms.PSet(
#        record = cms.string('TrackerAlignmentRcd'),
#        tag = cms.string('TrackerIdealGeometry210_mc') # your tag
#        )
#      )
#    )
#es_prefer_trackerAlignment = cms.ESPrefer("PoolDBESSource","myTrackerAlignment")

## APE (set to zero)
myTrackerAlignmentErr = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(
    connect = cms.string('frontier://FrontierProd/CMS_COND_31X_FROM21X'),
    toGet = cms.VPSet(
      cms.PSet(
        record = cms.string('TrackerAlignmentErrorRcd'),
        tag = cms.string('TrackerIdealGeometryErrors210_mc')
      )
    )
)
es_prefer_trackerAlignmentErr = cms.ESPrefer("PoolDBESSource","myTrackerAlignmentErr")

### APE (as estimated with ApeEstimator)
#myTrackerAlignmentErr = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(
#    connect = cms.string('sqlite_file:/afs/cern.ch/user/h/hauk/cms/CMSSW_3_3_6_patch6/src/Alignment/CommonAlignmentAlgorithm/MyLocalApe.db'),
#    toGet = cms.VPSet(
#      cms.PSet(
#        record = cms.string('TrackerAlignmentErrorRcd'),
#        tag = cms.string('AlignmentErrors')
#      )
#    )
#)
#es_prefer_trackerAlignmentErr = cms.ESPrefer("PoolDBESSource","myTrackerAlignmentErr")





## MAGNETIC FIELD
#from Configuration.StandardSequences.MagneticField_0T_cff import *
from Configuration.StandardSequences.MagneticField_cff import *



## BEAM SPOT
from RecoVertex.BeamSpotProducer.BeamSpot_cfi import *



## CPE (combine StripCPEgeometric with standard-PixelCPE)
from RecoLocalTracker.SiStripRecHitConverter.StripCPEgeometric_cfi import *
StripCPEgeometricESProducer.APVpeakmode = True
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
# not used when < 0.
FittingSmootherRKP5.EstimateCut = -1.
# not used when < -15. (not yet implemented in used tag)
#FittingSmootherRKP5.LogPixelProbabilityCut = -16.
FittingSmootherRKP5.RejectTracks = False
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
    trackQualities = ["highPurity"]
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



