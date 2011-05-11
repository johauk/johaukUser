import FWCore.ParameterSet.Config as cms

## Vertex producer
#from RecoVertex.PrimaryVertexProducer.OfflinePrimaryVertices_cfi import *



###########################################################################################
#
# PRIMARY VERTEX COLLECTION
#
###########################################################################################

#goodPV = offlinePrimaryVertices.clone(
#    cut = cms.string('ndof>4 &'
#                     'abs(z)<24 &'
#	             '!isFake &'
#	             'position.Rho<2'
#    ),
#)


goodPV = cms.EDFilter("VertexSelector",
    src = cms.InputTag('offlinePrimaryVertices'),
    cut = cms.string('ndof>4 &'
                     'abs(z)<24 &'
	             '!isFake &'
	             'position.Rho<2'
    ),
)


#goodPV = cms.EDFilter("PATPrimaryVertexCleaner",
#    src = cms.InputTag('offlinePrimaryVertices'),
#    minMultiplicity = cms.uint32(4),
#    minPtSum = ...
#)





# Alternatively, filter directly
#goodPV = cms.EDFilter("GoodVertexFilter",
#    vertexCollection = cms.InputTag('offlinePrimaryVertices'),
#    minimumNDOF = cms.uint32(4) ,
#    maxAbsZ = cms.double(24),	
#    maxd0 = cms.double(2)	
#)




oneGoodPVSelection = cms.EDFilter("VertexCountFilter",
    src = cms.InputTag('goodPV'),
    minNumber = cms.uint32(1),
    maxNumber = cms.uint32(99999),
    
)




###########################################################################################
#
# SEQUENCES
#
###########################################################################################




buildVertexCollections = cms.Sequence(
    goodPV
)



vertexSelection = cms.Sequence(
    oneGoodPVSelection
)




