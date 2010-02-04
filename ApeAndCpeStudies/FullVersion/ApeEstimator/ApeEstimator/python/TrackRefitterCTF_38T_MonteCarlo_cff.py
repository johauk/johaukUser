import FWCore.ParameterSet.Config as cms



## GEOMETRY
from Configuration.StandardSequences.Geometry_cff import *



## CONDITIONS
from Configuration.StandardSequences.FrontierConditions_GlobalTag_cff import *
#GlobalTag.connect = "frontier://FrontierProd/CMS_COND_21X_GLOBALTAG"
## --- Ideal MonteCarlo ---
GlobalTag.globaltag = 'DESIGN_3X_V8B::All'    # peak mode
#GlobalTag.globaltag = 'MC_3XY_V9B::All'    # same, but bad channels are masked
## --- First ReProcessing (CRAFT '09) ---
#GlobalTag.globaltag = 'CRAFT09_R_V4::All'




## ALIGNMENT CONSTANTS & APE (set to zero)
#from CalibTracker.Configuration.Common.PoolDBESSource_cfi import *
import CalibTracker.Configuration.Common.PoolDBESSource_cfi

myTrackerAlignment = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(
    connect = 'frontier://FrontierProd/CMS_COND_31X_FROM21X', # or your sqlite file
    toGet = cms.VPSet(
      cms.PSet(
        record = cms.string('TrackerAlignmentRcd'),
        tag = cms.string('TrackerIdealGeometry210_mc') # your tag
        )
      )
    )
es_prefer_trackerAlignment = cms.ESPrefer("PoolDBESSource","myTrackerAlignment")

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



## MAGNETIC FIELD
#from Configuration.StandardSequences.MagneticField_0T_cff import *
from Configuration.StandardSequences.MagneticField_cff import *



## BEAM SPOT
from RecoVertex.BeamSpotProducer.BeamSpot_cfi import *



## CPE (combine StripCPEgeometric with standard-PixelCPE)
from RecoLocalTracker.SiStripRecHitConverter.StripCPEgeometric_cfi import *
TTRHBuilderGeometricAndTemplate = cms.ESProducer("TkTransientTrackingRecHitBuilderESProducer",
    #StripCPE = cms.string('StripCPEfromTrackAngle'), # cms.string('StripCPEgeometric'),
    StripCPE = cms.string('StripCPEgeometric'),
    ComponentName = cms.string('WithGeometricAndTemplate'),
    PixelCPE = cms.string('PixelCPEGeneric'),
    #PixelCPE = cms.string('PixelCPETemplateReco'),
    Matcher = cms.string('StandardMatcher'),
    ComputeCoarseLocalPositionFromDisk = cms.bool(False)
)



## TRACK REFITTER (input for Track Selector)
from RecoTracker.TrackProducer.TrackRefitters_cff import *
TrackRefitter1 = RecoTracker.TrackProducer.TrackRefitters_cff.TrackRefitterP5.clone(
    src = 'ALCARECOTkAlCosmicsCTF0T' #'ALCARECOTkAlCosmicsCosmicTF0T' #'ALCARECOTkAlCosmicsCosmicTF'
          #'ALCARECOTkAlCosmicsCTF' #'ALCARECOTkAlCosmicsRS0T' #'ALCARECOTkAlCosmicsRS'
    ,TTRHBuilder = 'WithGeometricAndTemplate'     # use StripCPEgeometric instead of standard
    #,AlgorithmName = 'ctf'  #'cosmics' #'rs' #'beamhalo'
    #,TrajectoryInEvent = False
    ,NavigationSchool = ''
)



## SEQUENCE
RefitterSequence = cms.Sequence(offlineBeamSpot
                                *TrackRefitter1
				)




