import FWCore.ParameterSet.Config as cms



from ZmumuAnalysis.Configuration.filters.GenParticleSelector_cfi import *
from ZmumuAnalysis.Configuration.filters.GenParticleCountFilter_cfi import *


##
## Quark flavour selection
##

# Build Collections for b quarks

selectedBs = genParticleSelector.clone(
    #src = 'genParticles',
    cut = 'abs(pdgId)=5',
)

cleanBs = genParticleSelector.clone(
    src = 'selectedBs',
    cut = 'status=2 | status=3',
)

goodBs = genParticleSelector.clone(
    src = 'cleanBs',
    cut = 'pt>15.',
)

visibleGeometricBs = genParticleSelector.clone(
    src = 'goodBs',
    cut = 'abs(eta)<2.1',
)

visibleKinematicBs = genParticleSelector.clone(
    src = 'visibleGeometricBs',
    cut = 'pt>25.',
)







##
## Count filters
##

oneSelectedBSelection = genParticleCountFilter.clone(src = 'selectedBs',)
oneCleanBSelection = genParticleCountFilter.clone(src = 'cleanBs',)
oneGoodBSelection = genParticleCountFilter.clone(src = 'goodBs',)
oneVisibleGeometricBSelection = genParticleCountFilter.clone(src = 'visibleGeometricBs',)
oneVisibleKinematicBSelection = genParticleCountFilter.clone(src = 'visibleKinematicBs',)

twoSelectedBSelection = oneSelectedBSelection.clone(minNumber = 2,)
twoCleanBSelection = oneCleanBSelection.clone(minNumber = 2,)
twoGoodBSelection = oneGoodBSelection.clone(minNumber = 2,)
twoVisibleGeometricBSelection = oneVisibleGeometricBSelection.clone(minNumber = 2,)
twoVisibleKinematicBSelection = oneVisibleKinematicBSelection.clone(minNumber = 2,)



##
## Sequences
##

buildBCollections = cms.Sequence(
    selectedBs*
    cleanBs*
    goodBs*
    visibleGeometricBs*
    visibleKinematicBs
)


oneBSelection = cms.Sequence(
    oneSelectedBSelection*
    oneCleanBSelection*
    oneGoodBSelection*
    oneVisibleGeometricBSelection*
    oneVisibleKinematicBSelection
)

twoBSelection = cms.Sequence(
    twoSelectedBSelection*
    twoCleanBSelection*
    twoGoodBSelection*
    twoVisibleGeometricBSelection*
    twoVisibleKinematicBSelection
)
