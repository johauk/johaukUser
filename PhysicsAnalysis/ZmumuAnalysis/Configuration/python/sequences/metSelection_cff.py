import FWCore.ParameterSet.Config as cms

## met selector
from PhysicsTools.PatAlgos.selectionLayer1.metSelector_cfi import *
## met count filter
from PhysicsTools.PatAlgos.selectionLayer1.metCountFilter_cfi import *




###########################################################################################
#
# MET SELECTION
#
###########################################################################################


## good MET selection
goodMet = selectedPatMET.clone(
    src = 'patMETsPF', 
    cut = 'pt<40.',
)
#goodMet = cms.EDFilter("PATMETSelector",
#    src = cms.InputTag("patMETsPF"),
#    cut = cms.string("pt<40."),
#)



##
## Count Filters
##

goodMetSelection = countPatMET.clone(
    src = 'goodMet',
    minNumber = 1,
)
#goodMetSelection = cms.EDFilter("PATCandViewCountFilter",
#    src = cms.InputTag('goodMet'),
#    minNumber = cms.uint32(1),
#    maxNumber = cms.uint32(9999),
#)




###########################################################################################
#
# SEQUENCES
#
###########################################################################################




buildMetCollections = cms.Sequence(
    goodMet
)


metSelection = cms.Sequence(
    goodMetSelection
)


