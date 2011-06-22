import FWCore.ParameterSet.Config as cms

from ApeEstimator.ApeEstimator.SectorBuilder_cfi import *





###======================================================================================================================================================================
###======================================================================================================================================================================




# One Sector for each Subdetector (means only one for e.g. both endcaps)
SubdetSectors = cms.VPSet(
  cms.PSet(
    EmptySector.clone(
    name = 'Bpix',
    subdetId = [1],
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'Fpix',
    subdetId = [2],
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'Tib',
    subdetId = [3],
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'Tid',
    subdetId = [4],
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'Tob',
    subdetId = [5],
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'Tec',
    subdetId = [6],
  )),
)





###======================================================================================================================================================================
###======================================================================================================================================================================




# Only TID and TEC (means only one for e.g. both endcaps)
TIDTEC = cms.VPSet(
  cms.PSet(
    EmptySector.clone(
    name = 'Tid',
    subdetId = [4],
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'Tec',
    subdetId = [6],
  )),
)





###======================================================================================================================================================================
###======================================================================================================================================================================




# Only TIB and TOB
TIBTOB = cms.VPSet(
  cms.PSet(
    EmptySector.clone(
    name = 'Tib',
    subdetId = [3],
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'Tob',
    subdetId = [5],
  )),
)





###======================================================================================================================================================================
###======================================================================================================================================================================




# Only TIB and TOB, cosmic-like quartering (upper, lower, left, right part)
TIBTOBQuarters = cms.VPSet(
  
  # TIB
  cms.PSet(
    EmptySector.clone(
    name = 'TibUp',
    subdetId = [3],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibDown',
    subdetId = [3],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibLeft',
    subdetId = [3],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibRight',
    subdetId = [3],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),
  
  # TOB
  cms.PSet(
    EmptySector.clone(
    name = 'TobUp',
    subdetId = [5],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobDown',
    subdetId = [5],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobLeft',
    subdetId = [5],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobRight',
    subdetId = [5],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),
)





###======================================================================================================================================================================
###======================================================================================================================================================================




# Only TIB and TOB + Separation of pitches + Separation of 1D and 2D layers
TIBTOBPitchAnd2DSeparation = cms.VPSet(
  
  # TIB
  cms.PSet(
    EmptySector.clone(
    name = 'TibLayer12',
    layer = [1,2],
    subdetId = [3],
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibLayer34',
    layer = [3,4],
    subdetId = [3],
  )),
  
  # TOB
  cms.PSet(
    EmptySector.clone(
    name = 'TobLayer12',
    layer = [1,2],
    subdetId = [5],
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobLayer34',
    layer = [3,4],
    subdetId = [5],
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobLayer56',
    layer = [5,6],
    subdetId = [5],
  )),
)





###======================================================================================================================================================================
###======================================================================================================================================================================




# Only TIB and TOB, cosmic-like quartering (upper, lower, left, right part) + Separation of 1D and 2D layers
TIBTOBQuarters2DSeparation = cms.VPSet(
  
  # TIB 2D-layers
  cms.PSet(
    EmptySector.clone(
    name = 'TibUpLayer12',
    layer = [1,2],
    subdetId = [3],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibDownLayer12',
    layer = [1,2],
    subdetId = [3],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibLeftLayer12',
    layer = [1,2],
    subdetId = [3],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibRightLayer12',
    layer = [1,2],
    subdetId = [3],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),
  
  # TIB 1D-layers
  cms.PSet(
    EmptySector.clone(
    name = 'TibUpLayer34',
    layer = [3,4],
    subdetId = [3],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibDownLayer34',
    layer = [3,4],
    subdetId = [3],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibLeftLayer34',
    layer = [3,4],
    subdetId = [3],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibRightLayer34',
    layer = [3,4],
    subdetId = [3],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),
  
  # TOB 2D-layers
  cms.PSet(
    EmptySector.clone(
    name = 'TobUpLayer12',
    layer = [1,2],
    subdetId = [5],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobDownLayer12',
    layer = [1,2],
    subdetId = [5],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobLeftLayer12',
    layer = [1,2],
    subdetId = [5],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobRightLayer12',
    layer = [1,2],
    subdetId = [5],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),
  
  # TOB 1D-layers
  cms.PSet(
    EmptySector.clone(
    name = 'TobUpLayer3456',
    layer = [3,4,5,6],
    subdetId = [5],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobDownLayer3456',
    layer = [3,4,5,6],
    subdetId = [5],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobLeftLayer3456',
    layer = [3,4,5,6],
    subdetId = [5],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobRightLayer3456',
    layer = [3,4,5,6],
    subdetId = [5],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),
)





###======================================================================================================================================================================
###======================================================================================================================================================================




# Only TIB and TOB, Separation of layers (also rphi and stereo layers separated) and orientations
TIBTOBLayerAndOrientationSeparation = cms.VPSet(
  
  # TIB layer 1, pointing outwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TibLayer1OutRphi',
    layer = [1],
    subdetId = [3],
    isRPhi = [1],
    wDirection = [1],
  )),
  
  # TIB layer 1, pointing outwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TibLayer1OutStereo',
    layer = [1],
    subdetId = [3],
    isRPhi = [2],
    wDirection = [1],
  )),
  
  # TIB layer 1, pointing inwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TibLayer1InRphi',
    layer = [1],
    subdetId = [3],
    isRPhi = [1],
    wDirection = [-1],
  )),
  
  # TIB layer 1, pointing inwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TibLayer1InStereo',
    layer = [1],
    subdetId = [3],
    isRPhi = [2],
    wDirection = [-1],
  )),
  
  
  # TIB layer 2, pointing outwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TibLayer2OutRphi',
    layer = [2],
    subdetId = [3],
    isRPhi = [1],
    wDirection = [1],
  )),
  
  # TIB layer 2, pointing outwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TibLayer2OutStereo',
    layer = [2],
    subdetId = [3],
    isRPhi = [2],
    wDirection = [1],
  )),
  
  # TIB layer 2, pointing inwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TibLayer2InRphi',
    layer = [2],
    subdetId = [3],
    isRPhi = [1],
    wDirection = [-1],
  )),
  
  # TIB layer 2, pointing inwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TibLayer2InStereo',
    layer = [2],
    subdetId = [3],
    isRPhi = [2],
    wDirection = [-1],
  )),
  

  # TIB layer 3, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TibLayer3Out',
    layer = [3],
    subdetId = [3],
    wDirection = [1],
  )),

  # TIB layer 3, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TibLayer3In',
    layer = [3],
    subdetId = [3],
    wDirection = [-1],
  )),


  # TIB layer 4, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TibLayer4Out',
    layer = [4],
    subdetId = [3],
    wDirection = [1],
  )),

  # TIB layer 4, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TibLayer4In',
    layer = [4],
    subdetId = [3],
    wDirection = [-1],
  )),





  
  # TOB layer 1, pointing outwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TobLayer1OutRphi',
    layer = [1],
    subdetId = [5],
    isRPhi = [1],
    wDirection = [1],
  )),
  
  # TOB layer 1, pointing outwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TobLayer1OutStereo',
    layer = [1],
    subdetId = [5],
    isRPhi = [2],
    wDirection = [1],
  )),
  
  # TOB layer 1, pointing inwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TobLayer1InRphi',
    layer = [1],
    subdetId = [5],
    isRPhi = [1],
    wDirection = [-1],
  )),

  # TOB layer 1, pointing inwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TobLayer1InStereo',
    layer = [1],
    subdetId = [5],
    isRPhi = [2],
    wDirection = [-1],
  )),


  # TOB layer 2, pointing outwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TobLayer2OutRphi',
    layer = [2],
    subdetId = [5],
    isRPhi = [1],
    wDirection = [1],
  )),
  
  # TOB layer 2, pointing outwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TobLayer2OutStereo',
    layer = [2],
    subdetId = [5],
    isRPhi = [2],
    wDirection = [1],
  )),
  
  # TOB layer 2, pointing inwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TobLayer2InRphi',
    layer = [2],
    subdetId = [5],
    isRPhi = [1],
    wDirection = [-1],
  )),
  
  # TOB layer 2, pointing inwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TobLayer2InStereo',
    layer = [2],
    subdetId = [5],
    isRPhi = [2],
    wDirection = [-1],
  )),


  # TOB layer 3, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TobLayer3Out',
    layer = [3],
    subdetId = [5],
    wDirection = [1],
  )),

  # TOB layer 3, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TobLayer3In',
    layer = [3],
    subdetId = [5],
    wDirection = [-1],
  )),


  # TOB layer 4, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TobLayer4Out',
    layer = [4],
    subdetId = [5],
    wDirection = [1],
  )),

  # TOB layer 4, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TobLayer4In',
    layer = [4],
    subdetId = [5],
    wDirection = [-1],
  )),


  # TOB layer 5, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TobLayer5Out',
    layer = [5],
    subdetId = [5],
    wDirection = [1],
  )),

  # TOB layer 5, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TobLayer5In',
    layer = [5],
    subdetId = [5],
    wDirection = [-1],
  )),


  # TOB layer 6, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TobLayer6Out',
    layer = [6],
    subdetId = [5],
    wDirection = [1],
  )),

  # TOB layer 6, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TobLayer6In',
    layer = [6],
    subdetId = [5],
    wDirection = [-1],
  )),


)





###======================================================================================================================================================================
###======================================================================================================================================================================




# Only TIB and TOB, quartering (upper, lower, left, right part) + Separation of layers and orientations
TIBTOBQuartersLayerAndOrientationSeparation = cms.VPSet(
  
  # TIB layer 1, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TibUpLayer1Out',
    layer = [1],
    subdetId = [3],
    wDirection = [1],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibDownLayer1Out',
    layer = [1],
    subdetId = [3],
    wDirection = [1],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibLeftLayer1Out',
    layer = [1],
    subdetId = [3],
    wDirection = [1],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibRightLayer1Out',
    layer = [1],
    subdetId = [3],
    wDirection = [1],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),

  # TIB layer 1, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TibUpLayer1In',
    layer = [1],
    subdetId = [3],
    wDirection = [-1],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibDownLayer1In',
    layer = [1],
    subdetId = [3],
    wDirection = [-1],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibLeftLayer1In',
    layer = [1],
    subdetId = [3],
    wDirection = [-1],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibRightLayer1In',
    layer = [1],
    subdetId = [3],
    wDirection = [-1],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),


  # TIB layer 2, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TibUpLayer2Out',
    layer = [2],
    subdetId = [3],
    wDirection = [1],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibDownLayer2Out',
    layer = [2],
    subdetId = [3],
    wDirection = [1],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibLeftLayer2Out',
    layer = [2],
    subdetId = [3],
    wDirection = [1],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibRightLayer2Out',
    layer = [2],
    subdetId = [3],
    wDirection = [1],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),

  # TIB layer 2, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TibUpLayer2In',
    layer = [2],
    subdetId = [3],
    wDirection = [-1],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibDownLayer2In',
    layer = [2],
    subdetId = [3],
    wDirection = [-1],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibLeftLayer2In',
    layer = [2],
    subdetId = [3],
    wDirection = [-1],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibRightLayer2In',
    layer = [2],
    subdetId = [3],
    wDirection = [-1],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),


  # TIB layer 3, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TibUpLayer3Out',
    layer = [3],
    subdetId = [3],
    wDirection = [1],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibDownLayer3Out',
    layer = [3],
    subdetId = [3],
    wDirection = [1],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibLeftLayer3Out',
    layer = [3],
    subdetId = [3],
    wDirection = [1],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibRightLayer3Out',
    layer = [3],
    subdetId = [3],
    wDirection = [1],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),

  # TIB layer 3, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TibUpLayer3In',
    layer = [3],
    subdetId = [3],
    wDirection = [-1],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibDownLayer3In',
    layer = [3],
    subdetId = [3],
    wDirection = [-1],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibLeftLayer3In',
    layer = [3],
    subdetId = [3],
    wDirection = [-1],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibRightLayer3In',
    layer = [3],
    subdetId = [3],
    wDirection = [-1],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),


  # TIB layer 4, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TibUpLayer4Out',
    layer = [4],
    subdetId = [3],
    wDirection = [1],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibDownLayer4Out',
    layer = [4],
    subdetId = [3],
    wDirection = [1],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibLeftLayer4Out',
    layer = [4],
    subdetId = [3],
    wDirection = [1],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibRightLayer4Out',
    layer = [4],
    subdetId = [3],
    wDirection = [1],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),

  # TIB layer 4, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TibUpLayer4In',
    layer = [4],
    subdetId = [3],
    wDirection = [-1],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibDownLayer4In',
    layer = [4],
    subdetId = [3],
    wDirection = [-1],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibLeftLayer4In',
    layer = [4],
    subdetId = [3],
    wDirection = [-1],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TibRightLayer4In',
    layer = [4],
    subdetId = [3],
    wDirection = [-1],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),





  
  # TOB layer 1, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TobUpLayer1Out',
    layer = [1],
    subdetId = [5],
    wDirection = [1],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobDownLayer1Out',
    layer = [1],
    subdetId = [5],
    wDirection = [1],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobLeftLayer1Out',
    layer = [1],
    subdetId = [5],
    wDirection = [1],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobRightLayer1Out',
    layer = [1],
    subdetId = [5],
    wDirection = [1],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),

  # TOB layer 1, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TobUpLayer1In',
    layer = [1],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobDownLayer1In',
    layer = [1],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobLeftLayer1In',
    layer = [1],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobRightLayer1In',
    layer = [1],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),


  # TOB layer 2, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TobUpLayer2Out',
    layer = [2],
    subdetId = [5],
    wDirection = [1],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobDownLayer2Out',
    layer = [2],
    subdetId = [5],
    wDirection = [1],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobLeftLayer2Out',
    layer = [2],
    subdetId = [5],
    wDirection = [1],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobRightLayer2Out',
    layer = [2],
    subdetId = [5],
    wDirection = [1],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),

  # TOB layer 2, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TobUpLayer2In',
    layer = [2],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobDownLayer2In',
    layer = [2],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobLeftLayer2In',
    layer = [2],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobRightLayer2In',
    layer = [2],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),


  # TOB layer 3, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TobUpLayer3Out',
    layer = [3],
    subdetId = [5],
    wDirection = [1],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobDownLayer3Out',
    layer = [3],
    subdetId = [5],
    wDirection = [1],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobLeftLayer3Out',
    layer = [3],
    subdetId = [5],
    wDirection = [1],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobRightLayer3Out',
    layer = [3],
    subdetId = [5],
    wDirection = [1],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),

  # TOB layer 3, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TobUpLayer3In',
    layer = [3],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobDownLayer3In',
    layer = [3],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobLeftLayer3In',
    layer = [3],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobRightLayer3In',
    layer = [3],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),


  # TOB layer 4, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TobUpLayer4Out',
    layer = [4],
    subdetId = [5],
    wDirection = [1],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobDownLayer4Out',
    layer = [4],
    subdetId = [5],
    wDirection = [1],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobLeftLayer4Out',
    layer = [4],
    subdetId = [5],
    wDirection = [1],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobRightLayer4Out',
    layer = [4],
    subdetId = [5],
    wDirection = [1],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),

  # TOB layer 4, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TobUpLayer4In',
    layer = [4],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobDownLayer4In',
    layer = [4],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobLeftLayer4In',
    layer = [4],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobRightLayer4In',
    layer = [4],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),


  # TOB layer 5, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TobUpLayer5Out',
    layer = [5],
    subdetId = [5],
    wDirection = [1],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobDownLayer5Out',
    layer = [5],
    subdetId = [5],
    wDirection = [1],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobLeftLayer5Out',
    layer = [5],
    subdetId = [5],
    wDirection = [1],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobRightLayer5Out',
    layer = [5],
    subdetId = [5],
    wDirection = [1],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),

  # TOB layer 5, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TobUpLayer5In',
    layer = [5],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobDownLayer5In',
    layer = [5],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobLeftLayer5In',
    layer = [5],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobRightLayer5In',
    layer = [5],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),


  # TOB layer 6, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TobUpLayer6Out',
    layer = [6],
    subdetId = [5],
    wDirection = [1],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobDownLayer6Out',
    layer = [6],
    subdetId = [5],
    wDirection = [1],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobLeftLayer6Out',
    layer = [6],
    subdetId = [5],
    wDirection = [1],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobRightLayer6Out',
    layer = [6],
    subdetId = [5],
    wDirection = [1],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),

  # TOB layer 6, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TobUpLayer6In',
    layer = [6],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [0.7854,2.3562],   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobDownLayer6In',
    layer = [6],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [-2.3562,-0.7854],   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobLeftLayer6In',
    layer = [6],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [-0.7854,0.7854],   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    name = 'TobRightLayer6In',
    layer = [6],
    subdetId = [5],
    wDirection = [-1],
    posPhi = [-3.5,-2.3562,2.3562,3.5],   # [135,-135] degree
  )),


)



###======================================================================================================================================================================
###======================================================================================================================================================================

## Only TID and TEC, Separation of side(+,-) and of rings (also rphi and stereo rings separated) and orientations

# In TEC: All RPhi modules within a ring point in same w direction. Same is valid for Stereo modules, but with opposite sign

TIDTECSideAndRingAndOrientationSeparation = cms.VPSet(
  
  # TID- ring 1, pointing inwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TidMinusRing1InRphi',
    side = [1],
    ring = [1],
    subdetId = [4],
    isRPhi = [1],
    wDirection = [1],
  )),
  
  # TID- ring 1, pointing inwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TidMinusRing1InStereo',
    side = [1],
    ring = [1],
    subdetId = [4],
    isRPhi = [2],
    wDirection = [1],
  )),
  
  # TID- ring 1, pointing outwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TidMinusRing1OutRphi',
    side = [1],
    ring = [1],
    subdetId = [4],
    isRPhi = [1],
    wDirection = [-1],
  )),
  
  # TID- ring 1, pointing outwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TidMinusRing1OutStereo',
    side = [1],
    ring = [1],
    subdetId = [4],
    isRPhi = [2],
    wDirection = [-1],
  )),
  
  
  # TID- ring 2, pointing inwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TidMinusRing2InRphi',
    side = [1],
    ring = [2],
    subdetId = [4],
    isRPhi = [1],
    wDirection = [1],
  )),
  
  # TID- ring 2, pointing inwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TidMinusRing2InStereo',
    side = [1],
    ring = [2],
    subdetId = [4],
    isRPhi = [2],
    wDirection = [1],
  )),
  
  # TID- ring 2, pointing outwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TidMinusRing2OutRphi',
    side = [1],
    ring = [2],
    subdetId = [4],
    isRPhi = [1],
    wDirection = [-1],
  )),
  
  # TID- ring 2, pointing outwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TidMinusRing2OutStereo',
    side = [1],
    ring = [2],
    subdetId = [4],
    isRPhi = [2],
    wDirection = [-1],
  )),
  
  
  # TID- ring 3, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TidMinusRing3In',
    side = [1],
    ring = [3],
    subdetId = [4],
    wDirection = [1],
  )),
  
  # TID- ring 3, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TidMinusRing3Out',
    side = [1],
    ring = [3],
    subdetId = [4],
    wDirection = [-1],
  )),
  
  
  
  
  
  
  
  # TEC- ring 1, pointing inwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TecMinusRing1InStereo',
    side = [1],
    ring = [1],
    subdetId = [6],
    isRPhi = [2],
    #wDirection = [1],
  )),
  
  # TEC- ring 1, pointing outwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TecMinusRing1OutRphi',
    side = [1],
    ring = [1],
    subdetId = [6],
    isRPhi = [1],
    #wDirection = [-1],
  )),
  
  
  # TEC- ring 2, pointing inwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TecMinusRing2InRPhi',
    side = [1],
    ring = [2],
    subdetId = [6],
    isRPhi = [1],
    #wDirection = [1],
  )),
  
  # TEC- ring 2, pointing outwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TecMinusRing2OutStereo',
    side = [1],
    ring = [2],
    subdetId = [6],
    isRPhi = [2],
    #wDirection = [-1],
  )),
  
  
  # TEC- ring 3, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TecMinusRing3In',
    side = [1],
    ring = [3],
    subdetId = [6],
    #wDirection = [1],
  )),
  
  
  # TEC- ring 4, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TecMinusRing4Out',
    side = [1],
    ring = [4],
    subdetId = [6],
    #wDirection = [-1],
  )),
  
  
  # TEC- ring 5, pointing inwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TecMinusRing5InStereo',
    side = [1],
    ring = [5],
    subdetId = [6],
    isRPhi = [2],
    #wDirection = [1],
  )),
  
  # TEC- ring 5, pointing outwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TecMinusRing5OutRphi',
    side = [1],
    ring = [5],
    subdetId = [6],
    isRPhi = [1],
    #wDirection = [-1],
  )),
  
  
  # TEC- ring 6, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TecMinusRing6Out',
    side = [1],
    ring = [6],
    subdetId = [6],
    #wDirection = [-1],
  )),
  
  
  # TEC- ring 7, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TecMinusRing7In',
    side = [1],
    ring = [7],
    subdetId = [6],
    #wDirection = [1],
  )),
  
  
  
  
  
  
  
  
  
  # TID+ ring 1, pointing outwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TidPlusRing1OutRphi',
    side = [2],
    ring = [1],
    subdetId = [4],
    isRPhi = [1],
    wDirection = [1],
  )),
  
  # TID+ ring 1, pointing outwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TidPlusRing1OutStereo',
    side = [2],
    ring = [1],
    subdetId = [4],
    isRPhi = [2],
    wDirection = [1],
  )),
  
  # TID+ ring 1, pointing inwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TidPlusRing1InRphi',
    side = [2],
    ring = [1],
    subdetId = [4],
    isRPhi = [1],
    wDirection = [-1],
  )),
  
  # TID+ ring 1, pointing inwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TidPlusRing1InStereo',
    side = [2],
    ring = [1],
    subdetId = [4],
    isRPhi = [2],
    wDirection = [-1],
  )),
  
  
  # TID+ ring 2, pointing outwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TidPlusRing2OutRphi',
    side = [2],
    ring = [2],
    subdetId = [4],
    isRPhi = [1],
    wDirection = [1],
  )),
  
  # TID+ ring 2, pointing outwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TidPlusRing2OutStereo',
    side = [2],
    ring = [2],
    subdetId = [4],
    isRPhi = [2],
    wDirection = [1],
  )),
  
  # TID+ ring 2, pointing inwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TidPlusRing2InRphi',
    side = [2],
    ring = [2],
    subdetId = [4],
    isRPhi = [1],
    wDirection = [-1],
  )),
  
  # TID+ ring 2, pointing inwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TidPlusRing2InStereo',
    side = [2],
    ring = [2],
    subdetId = [4],
    isRPhi = [2],
    wDirection = [-1],
  )),
  
  
  # TID+ ring 3, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TidPlusRing3Out',
    side = [2],
    ring = [3],
    subdetId = [4],
    wDirection = [1],
  )),
  
  # TID+ ring 3, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TidPlusRing3In',
    side = [2],
    ring = [3],
    subdetId = [4],
    wDirection = [-1],
  )),
  
  
  
  
  
  
  
  # TEC+ ring 1, pointing outwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TecPlusRing1OutRphi',
    side = [2],
    ring = [1],
    subdetId = [6],
    isRPhi = [1],
    #wDirection = [1],
  )),
  
  # TEC+ ring 1, pointing inwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TecPlusRing1InStereo',
    side = [2],
    ring = [1],
    subdetId = [6],
    isRPhi = [2],
    #wDirection = [-1],
  )),
  
  
  # TEC+ ring 2, pointing outwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TecPlusRing2OutStereo',
    side = [2],
    ring = [2],
    subdetId = [6],
    isRPhi = [2],
    #wDirection = [1],
  )),
  
  # TEC+ ring 2, pointing inwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TecPlusRing2InRphi',
    side = [2],
    ring = [2],
    subdetId = [6],
    isRPhi = [1],
    #wDirection = [-1],
  )),
  
  
  # TEC+ ring 3, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TecPlusRing3In',
    side = [2],
    ring = [3],
    subdetId = [6],
    #wDirection = [-1],
  )),
  
  
  # TEC+ ring 4, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TecPlusRing4Out',
    side = [2],
    ring = [4],
    subdetId = [6],
    #wDirection = [1],
  )),
  
  
  # TEC+ ring 5, pointing outwards, rphi modules
  cms.PSet(
    EmptySector.clone(
    name = 'TecPlusRing5OutRphi',
    side = [2],
    ring = [5],
    subdetId = [6],
    isRPhi = [1],
    #wDirection = [1],
  )),
  
  # TEC+ ring 5, pointing inwards, stereo modules
  cms.PSet(
    EmptySector.clone(
    name = 'TecPlusRing5InStereo',
    side = [2],
    ring = [5],
    subdetId = [6],
    isRPhi = [2],
    #wDirection = [-1],
  )),
  
  
  # TEC+ ring 6, pointing outwards
  cms.PSet(
    EmptySector.clone(
    name = 'TecPlusRing6Out',
    side = [2],
    ring = [6],
    subdetId = [6],
    #wDirection = [1],
  )),
  
  
  # TEC+ ring 7, pointing inwards
  cms.PSet(
    EmptySector.clone(
    name = 'TecPlusRing7In',
    side = [2],
    ring = [7],
    subdetId = [6],
    #wDirection = [-1],
  )),
)









