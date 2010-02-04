import FWCore.ParameterSet.Config as cms

from ApeEstimator.ApeEstimator.SectorBuilder_cfi import *




# One Sector for each Subdetector (means only one for e.g. both endcaps)
SubdetSectors = cms.VPSet(
  cms.PSet(
    EmptySector.clone(
    subdetId = [1]
  )),
  cms.PSet(
    EmptySector.clone(
    subdetId = [2]
  )),
  cms.PSet(
    EmptySector.clone(
    subdetId = [3]
  )),
  cms.PSet(
    EmptySector.clone(
    subdetId = [4]
  )),
  cms.PSet(
    EmptySector.clone(
    subdetId = [5]
  )),
  cms.PSet(
    EmptySector.clone(
    subdetId = [6]
  )),
)





# Only TID and TEC (means only one for e.g. both endcaps)
TIDTEC = cms.VPSet(
  cms.PSet(
    EmptySector.clone(
    subdetId = [4]
  )),
  cms.PSet(
    EmptySector.clone(
    subdetId = [6]
  )),
)




# Only TIB and TOB, cosmic-like quartering (upper, lower, left, right part)
TIBTOBQuarters = cms.VPSet(
  
  # TIB
  cms.PSet(
    EmptySector.clone(
    subdetId = [3],
    posPhi = [0.7854,2.3562]   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    subdetId = [3],
    posPhi = [-2.3562,-0.7854]   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    subdetId = [3],
    posPhi = [-0.7854,0.7854]   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    subdetId = [3],
    posPhi = [-3.5,-2.3562,2.3562,3.5]   # [135,-135] degree
  )),
  
  # TOB
  cms.PSet(
    EmptySector.clone(
    subdetId = [5],
    posPhi = [0.7854,2.3562]   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    subdetId = [5],
    posPhi = [-2.3562,-0.7854]   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    subdetId = [5],
    posPhi = [-0.7854,0.7854]   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    subdetId = [5],
    posPhi = [-3.5,-2.3562,2.3562,3.5]   # [135,-135] degree
  )),
)







# Only TIB and TOB, cosmic-like quartering (upper, lower, left, right part) + Separation of 1D and 2D layers
TIBTOBQuarters2DSeparation = cms.VPSet(
  
  # TIB 2D-layers
  cms.PSet(
    EmptySector.clone(
    layer = [1,2],
    subdetId = [3],
    posPhi = [0.7854,2.3562]   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    layer = [1,2],
    subdetId = [3],
    posPhi = [-2.3562,-0.7854]   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    layer = [1,2],
    subdetId = [3],
    posPhi = [-0.7854,0.7854]   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    layer = [1,2],
    subdetId = [3],
    posPhi = [-3.5,-2.3562,2.3562,3.5]   # [135,-135] degree
  )),
  
  # TIB 1D-layers
  cms.PSet(
    EmptySector.clone(
    layer = [3,4],
    subdetId = [3],
    posPhi = [0.7854,2.3562]   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    layer = [3,4],
    subdetId = [3],
    posPhi = [-2.3562,-0.7854]   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    layer = [3,4],
    subdetId = [3],
    posPhi = [-0.7854,0.7854]   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    layer = [3,4],
    subdetId = [3],
    posPhi = [-3.5,-2.3562,2.3562,3.5]   # [135,-135] degree
  )),
  
  # TOB 2D-layers
  cms.PSet(
    EmptySector.clone(
    layer = [1,2],
    subdetId = [5],
    posPhi = [0.7854,2.3562]   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    layer = [1,2],
    subdetId = [5],
    posPhi = [-2.3562,-0.7854]   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    layer = [1,2],
    subdetId = [5],
    posPhi = [-0.7854,0.7854]   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    layer = [1,2],
    subdetId = [5],
    posPhi = [-3.5,-2.3562,2.3562,3.5]   # [135,-135] degree
  )),
  
  # TOB 1D-layers
  cms.PSet(
    EmptySector.clone(
    layer = [3,4,5,6],
    subdetId = [5],
    posPhi = [0.7854,2.3562]   # [45,135] degree
  )),
  cms.PSet(
    EmptySector.clone(
    layer = [3,4,5,6],
    subdetId = [5],
    posPhi = [-2.3562,-0.7854]   # [-135,-45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    layer = [3,4,5,6],
    subdetId = [5],
    posPhi = [-0.7854,0.7854]   # [-45,45] degree
  )),
  cms.PSet(
    EmptySector.clone(
    layer = [3,4,5,6],
    subdetId = [5],
    posPhi = [-3.5,-2.3562,2.3562,3.5]   # [135,-135] degree
  )),
)










