import FWCore.ParameterSet.Config as cms


from ApeEstimator.ApeEstimator.ApeEstimator_cfi import *
from ApeEstimator.ApeEstimator.SectorBuilder_cff import *


ApeEstimator = ApeEstimatorTemplate.clone(
  maxTracksPerEvent = 0,
  #applyTrackCuts = False,
  minGoodHitsPerTrack = 1,
  residualErrorBinning = [0.0005,0.0010,0.0015,0.0020,0.0025,0.0030,0.0035,0.0040,0.0050,0.0070,0.0100], # 5-100um
  #zoomHists = False,
  vErrHists = [1],
  #Sectors = SubdetSectors,
  #Sectors = TIBTOBQuarters,
  #Sectors = TIBTOBQuarters2DSeparation,
  Sectors = TIBTOBPitchAnd2DSeparation,
  tjTkAssociationMapTag = "TrackRefitterHighPurityForApeEstimator",
)
#ApeEstimator.HitSelector.width = [1,3]
ApeEstimator.HitSelector.widthDiff = [-3.,1.]
#ApeEstimator.HitSelector.edgeStrips = [2,800]   # exclude first (and so also last) strip
ApeEstimator.HitSelector.sOverN = [15.,20000.]

#ApeEstimator.HitSelector.phiSensX = [-1.0472,1.0472]  # [-60,60] degree
#ApeEstimator.HitSelector.phiSensY = [-1.0472,1.0472]  # [-60,60] degree


#ApeEstimator.HitSelector.errXHit = cms.vdouble(0.,0.0060)  # 60um, to exclude very large clusters


