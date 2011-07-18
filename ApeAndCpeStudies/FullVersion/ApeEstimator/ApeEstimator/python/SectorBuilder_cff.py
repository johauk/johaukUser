import FWCore.ParameterSet.Config as cms

from ApeEstimator.ApeEstimator.SectorBuilder_Bpix_cff import *
from ApeEstimator.ApeEstimator.SectorBuilder_Fpix_cff import *
from ApeEstimator.ApeEstimator.SectorBuilder_Tib_cff import *
from ApeEstimator.ApeEstimator.SectorBuilder_Tid_cff import *
from ApeEstimator.ApeEstimator.SectorBuilder_Tob_cff import *
from ApeEstimator.ApeEstimator.SectorBuilder_Tec_cff import *



###======================================================================================================================================================================

##
## One Sector for each Subdetector (means only one for e.g. both endcaps)
##

SubdetSectors = cms.VPSet(
    Bpix,
    Fpix,
    Tib,
    Tid,
    Tob,
    Tec,
)



###======================================================================================================================================================================

##
## Only TID and TEC (means only one for e.g. both endcaps)
##

TIDTEC = cms.VPSet(
    Tid,
    Tec,
)



###======================================================================================================================================================================

##
## Only TIB and TOB
##

TIBTOB = cms.VPSet(
    Tib,
    Tob,
)



###======================================================================================================================================================================

##
## Only TIB and TOB, cosmic-like quartering (upper, lower, left, right part)
##

TIBTOBQuarters = cms.VPSet(
    TibUp,
    TibDown,
    TibLeft,
    TibRight,
    
    TobUp,
    TobDown,
    TobLeft,
    TobRight,
)



###======================================================================================================================================================================

##
## Only TIB and TOB + Separation of pitches + Separation of 1D and 2D layers
##

TIBTOBPitchAnd2DSeparation = cms.VPSet(
    TibLayer12,
    TibLayer34,
    
    TobLayer12,
    TobLayer34,
    TobLayer56,
)



###======================================================================================================================================================================

##
## Only TIB and TOB, Separation of layers + rphi/stereo + orientations
##

# In TOB: All RPhi modules within a layer point in same w direction. Same is valid for Stereo modules, but with opposite sign

TIBTOBLayerAndOrientationSeparation = cms.VPSet(
    TibLayer1RphiOut,
    TibLayer1StereoOut,
    TibLayer1RphiIn,
    TibLayer1StereoIn,
    TibLayer2RphiOut,
    TibLayer2StereoOut,
    TibLayer2RphiIn,
    TibLayer2StereoIn,
    TibLayer3Out,
    TibLayer3In,
    TibLayer4Out,
    TibLayer4In,
    
    #TobLayer1RphiOut,      # no modules contained
    TobLayer1StereoOut,
    TobLayer1RphiIn,
    #TobLayer1StereoIn,     # no modules contained
    TobLayer2RphiOut,
    #TobLayer2StereoOut,    # no modules contained
    #TobLayer2RphiIn,       # no modules contained
    TobLayer2StereoIn,
    TobLayer3Out,
    TobLayer3In,
    TobLayer4Out,
    TobLayer4In,
    TobLayer5Out,
    TobLayer5In,
    TobLayer6Out,
    TobLayer6In,
)



###======================================================================================================================================================================

##
## Only TID and TEC, Separation of side + rings + rphi/stereo + orientations
##

# In TEC: All RPhi modules within a ring point in same w direction. Same is valid for Stereo modules, but with opposite sign

TIDTECSideAndRingSeparation = cms.VPSet(
    TidMinusRing1Rphi,
    TidMinusRing1Stereo,
    TidMinusRing2Rphi,
    TidMinusRing2Stereo,
    TidMinusRing3,
    
    TidPlusRing1Rphi,
    TidPlusRing1Stereo,
    TidPlusRing2Rphi,
    TidPlusRing2Stereo,
    TidPlusRing3,
    
    TecMinusRing1Rphi,
    TecMinusRing1Stereo,
    TecMinusRing2Rphi,
    TecMinusRing2Stereo,
    TecMinusRing3,
    TecMinusRing4,
    TecMinusRing5Rphi,
    TecMinusRing5Stereo,
    TecMinusRing6,
    TecMinusRing7,
    
    TecPlusRing1Rphi,
    TecPlusRing1Stereo,
    TecPlusRing2Rphi,
    TecPlusRing2Stereo,
    TecPlusRing3,
    TecPlusRing4,
    TecPlusRing5Rphi,
    TecPlusRing5Stereo,
    TecPlusRing6,
    TecPlusRing7,
)



###======================================================================================================================================================================

##
## Only TID and TEC, Separation of side + rings + rphi/stereo + orientations
##

# In TEC: All RPhi modules within a ring point in same w direction. Same is valid for Stereo modules, but with opposite sign

TIDTECSideAndRingAndOrientationSeparation = cms.VPSet(
    TidMinusRing1RphiOut,
    TidMinusRing1StereoOut,
    TidMinusRing1RphiIn,
    TidMinusRing1StereoIn,
    TidMinusRing2RphiOut,
    TidMinusRing2StereoOut,
    TidMinusRing2RphiIn,
    TidMinusRing2StereoIn,
    TidMinusRing3Out,
    TidMinusRing3In,
    
    TidPlusRing1RphiOut,
    TidPlusRing1StereoOut,
    TidPlusRing1RphiIn,
    TidPlusRing1StereoIn,
    TidPlusRing2RphiOut,
    TidPlusRing2StereoOut,
    TidPlusRing2RphiIn,
    TidPlusRing2StereoIn,
    TidPlusRing3Out,
    TidPlusRing3In,
    
    TecMinusRing1RphiOut,
    #TecMinusRing1StereoOut,
    #TecMinusRing1RphiIn,
    TecMinusRing1StereoIn,
    #TecMinusRing2RphiOut,
    TecMinusRing2StereoOut,
    TecMinusRing2RphiIn,
    #TecMinusRing2StereoIn,
    #TecMinusRing3Out,
    TecMinusRing3In,
    TecMinusRing4Out,
    #TecMinusRing4In,
    TecMinusRing5RphiOut,
    #TecMinusRing5StereoOut,
    #TecMinusRing5RphiIn,
    TecMinusRing5StereoIn,
    TecMinusRing6Out,
    #TecMinusRing6In,
    #TecMinusRing7Out,
    TecMinusRing7In,
    
    TecPlusRing1RphiOut,
    #TecPlusRing1StereoOut,
    #TecPlusRing1RphiIn,
    TecPlusRing1StereoIn,
    #TecPlusRing2RphiOut,
    TecPlusRing2StereoOut,
    TecPlusRing2RphiIn,
    #TecPlusRing2StereoIn,
    #TecPlusRing3Out,
    TecPlusRing3In,
    TecPlusRing4Out,
    #TecPlusRing4In,
    TecPlusRing5RphiOut,
    #TecPlusRing5StereoOut,
    #TecPlusRing5RphiIn,
    TecPlusRing5StereoIn,
    TecPlusRing6Out,
    #TecPlusRing6In,
    #TecPlusRing7Out,
    TecPlusRing7In,
)



###======================================================================================================================================================================

##
## Only BPIX, Separation of layer + rphi/stereo + orientations
##

BPIXLayerAndOrientationSeparation = cms.VPSet(
    BpixLayer1Out,
    BpixLayer1In,
    BpixLayer2Out,
    BpixLayer2In,
    BpixLayer3Out,
    BpixLayer3In,
)



###======================================================================================================================================================================

##
## Only FPIX, Separation of side + rings + orientations
##

FPIXSideAndLayerAndOrientationSeparation = cms.VPSet(
    FpixMinusLayer1Out,
    FpixMinusLayer1In,
    FpixMinusLayer2Out,
    FpixMinusLayer2In,
    FpixPlusLayer1Out,
    FpixPlusLayer1In,
    FpixPlusLayer2Out,
    FpixPlusLayer2In,
)



###======================================================================================================================================================================

##
## Recent definition for whole tracker
##

RecentSectors = cms.VPSet()

RecentSectors += BPIXLayerAndOrientationSeparation
RecentSectors += FPIXSideAndLayerAndOrientationSeparation
RecentSectors += TIBTOBLayerAndOrientationSeparation
RecentSectors += TIDTECSideAndRingSeparation








