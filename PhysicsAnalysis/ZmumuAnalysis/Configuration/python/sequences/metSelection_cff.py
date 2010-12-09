import FWCore.ParameterSet.Config as cms

## met selector -- not anymore in release CMSSW_3_8_4...
#from PhysicsTools.PatAlgos.selectionLayer1.metSelector_cfi import *
## met count filter -- not yet in release CMSSW_3_8_4
#from PhysicsTools.PatAlgos.selectionLayer1.metCountFilter_cfi import *




###########################################################################################
#
# MET SELECTION
#
###########################################################################################


## good MET selection
#goodMet = selectedPatMET.clone(
#    src = 'patMETsPF', 
#    cut = 'et < 40.',
#)
goodMet = cms.EDFilter("PATMETSelector",
    src = cms.InputTag("patMETsPF"),
    cut = cms.string("et<40."),
)



##
## Count Filters
##

#goodMetSelection = countPatMet.clone(src = 'goodMet', minNumber = 1)
goodMetSelection = cms.EDFilter("PATCandViewCountFilter",
    src = cms.InputTag('goodMet'),
    minNumber = cms.uint32(1),
    maxNumber = cms.uint32(9999),
)




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


