import FWCore.ParameterSet.Config as cms


from ApeEstimator.ApeEstimator.apeestimator_cfi import *
from ApeEstimator.ApeEstimator.SectorBuilder_cff import *


ApeEstimatorCosmics = ApeEstimator.clone(
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
  sigmaFactorFit = 2.5,
  apeScaling = 0.5,
  tjTkAssociationMapTag = "TrackRefitterHighPurityForApeEstimator",
)
#ApeEstimatorCosmics.HitSelector.width = [1,3]
ApeEstimatorCosmics.HitSelector.widthDiff = [-3.,1.]
#ApeEstimatorCosmics.HitSelector.edgeStrips = [2,800]   # exclude first (and so also last) strip
ApeEstimatorCosmics.HitSelector.sOverN = [15.,20000.]

#ApeEstimatorCosmics.HitSelector.phiSensX = [-1.0472,1.0472]  # [-60,60] degree
#ApeEstimatorCosmics.HitSelector.phiSensY = [-1.0472,1.0472]  # [-60,60] degree


#ApeEstimatorCosmics.HitSelector.errXHit = cms.vdouble(0.,0.0060)  # 60um, to exclude very large clusters


