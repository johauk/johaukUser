import FWCore.ParameterSet.Config as cms

from ApeEstimator.ApeEstimator.SectorBuilder_cfi import *



##
## Whole Subdetector (means only one for both endcaps)
##

Fpix = EmptySector.clone(
    name = 'Fpix',
    subdetId = [2],
)



##
## Separation of side(+,-)
##

FpixMinus = Fpix.clone(
    name = 'FpixMinus',
    side = [1],
)
FpixPlus = Fpix.clone(
    name = 'FpixPlus',
    side = [2],
)



##
## Separation of side + layers
##

FpixMinusLayer1 = FpixMinus.clone(
    name = 'FpixMinusLayer1',
    layer = [1],
)
FpixMinusLayer2 = FpixMinus.clone(
    name = 'FpixMinusLayer2',
    layer = [2],
)
FpixPlusLayer1 = FpixPlus.clone(
    name = 'FpixPlusLayer1',
    layer = [1],
)
FpixPlusLayer2 = FpixPlus.clone(
    name = 'FpixPlusLayer2',
    layer = [2],
)



##
## Separation of side + layers + orientations
##

FpixMinusLayer1Out = FpixMinusLayer1.clone(
    name = 'FpixMinusLayer1Out',
    wDirection = [-1],
)
FpixMinusLayer1In = FpixMinusLayer1.clone(
    name = 'FpixMinusLayer1In',
    wDirection = [1],
)
FpixMinusLayer2Out = FpixMinusLayer2.clone(
    name = 'FpixMinusLayer1Out',
    wDirection = [-1],
)
FpixMinusLayer2In = FpixMinusLayer2.clone(
    name = 'FpixMinusLayer1In',
    wDirection = [1],
)
FpixPlusLayer1Out = FpixPlusLayer1.clone(
    name = 'FpixPlusLayer1Out',
    wDirection = [1],
)
FpixPlusLayer1In = FpixPlusLayer1.clone(
    name = 'FpixPlusLayer1In',
    wDirection = [-1],
)
FpixPlusLayer2Out = FpixPlusLayer2.clone(
    name = 'FpixPlusLayer1Out',
    wDirection = [1],
)
FpixPlusLayer2In = FpixPlusLayer2.clone(
    name = 'FpixPlusLayer1In',
    wDirection = [-1],
)







