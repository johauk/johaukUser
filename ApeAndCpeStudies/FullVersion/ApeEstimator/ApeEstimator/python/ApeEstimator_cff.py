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
  #Sectors = TIBTOBPitchAnd2DSeparation,
  #Sectors = TIBTOBLayerAndOrientationSeparation,
  #Sectors = TIDTECSideAndRingAndOrientationSeparation,
  Sectors = RecentSectors,
  tjTkAssociationMapTag = "TrackRefitterHighPurityForApeEstimator",
)
#ApeEstimator.HitSelector.width = [2,3]
ApeEstimator.HitSelector.width = [3,3]
ApeEstimator.HitSelector.maxIndex = [1,1]
#ApeEstimator.HitSelector.widthDiff = [-3.,0.1]
#ApeEstimator.HitSelector.edgeStrips = [2,800]   # exclude first (and so also last) strip
ApeEstimator.HitSelector.sOverN = [20.,50.]
#ApeEstimator.HitSelector.sOverN = [15.,20000.]



# Why is charge and maxCharge double, not int?
#ApeEstimator.HitSelector.maxCharge = [0.,250.]
ApeEstimator.HitSelector.chargeOnEdges = [0.,0.5]


#ApeEstimator.HitSelector.phiSensX = [-3.5,-0.122173,0.,3.5]  # exclude [-7,0] degree


#ApeEstimator.HitSelector.phiSensX = [-1.0472,1.0472]  # [-60,60] degree
#ApeEstimator.HitSelector.phiSensY = [-1.0472,1.0472]  # [-60,60] degree


#ApeEstimator.HitSelector.errXHit = cms.vdouble(0.,0.0060)  # 60um, to exclude very large clusters

 
