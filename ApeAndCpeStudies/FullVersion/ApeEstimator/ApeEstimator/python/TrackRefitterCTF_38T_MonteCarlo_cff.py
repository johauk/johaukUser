import FWCore.ParameterSet.Config as cms



## GEOMETRY
from Configuration.StandardSequences.Geometry_cff import *



## CONDITIONS
#from Configuration.StandardSequences.FrontierConditions_GlobalTag_cfi import *
from Alignment.HIPAlignmentAlgorithm.FrontierConditions_GlobalTag_cff import *
GlobalTag.connect = "frontier://FrontierProd/CMS_COND_21X_GLOBALTAG"
## --- Ideal MonteCarlo ---
#GlobalTag.globaltag = 'IDEAL_V11::All'  #CMSSW210-225
#GlobalTag.globaltag = 'IDEAL_V12::All'  #CMSSW226-...
GlobalTag.globaltag = 'COSMMC_22X_TK::All'
## --- First Processing ---
#GlobalTag.globaltag = 'CRUZETALL_V6::All'
#GlobalTag.globaltag = 'CRAFT_ALL_V4::All'
## --- Third Processing, second Reprocessing ---
#GlobalTag.globaltag = 'CRAFT_ALL_V9::All'




## ALIGNMENT CONSTANTS & APE (set to zero)
#from CalibTracker.Configuration.Common.PoolDBESSource_cfi import *
import CalibTracker.Configuration.Common.PoolDBESSource_cfi

myTrackerAlignment = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(
    connect = 'frontier://FrontierProd/CMS_COND_21X_ALIGNMENT', # or your sqlite file
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
    connect = cms.string('frontier://FrontierProd/CMS_COND_21X_ALIGNMENT'),
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
from Configuration.StandardSequences.MagneticField_38T_cff import *



## BEAM SPOT
from RecoVertex.BeamSpotProducer.BeamSpot_cfi import *



## TRACK REFITTER (input for Track Selector)
from RecoTracker.TrackProducer.TrackRefitters_cff import *
TrackRefitter1 = RecoTracker.TrackProducer.TrackRefitters_cff.TrackRefitterP5.clone(
    src = 'ALCARECOTkAlCosmicsCTF0T' #'ALCARECOTkAlCosmicsCosmicTF0T' #'ALCARECOTkAlCosmicsCosmicTF'
          #'ALCARECOTkAlCosmicsCTF' #'ALCARECOTkAlCosmicsRS0T' #'ALCARECOTkAlCosmicsRS'
    ,AlgorithmName = 'ctf'  #'cosmics' #'rs' #'beamhalo'
    #,TrajectoryInEvent = False
)



## SEQUENCE
RefitterSequence = cms.Sequence(
                                offlineBeamSpot
                                *TrackRefitter1
				)




