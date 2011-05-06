import FWCore.ParameterSet.Config as cms

## Vertex producer
from RecoVertex.PrimaryVertexProducer.OfflinePrimaryVertices_cfi import *



###########################################################################################
#
# PRIMARY VERTEX COLLECTION
#
###########################################################################################

goodPV = offlinePrimaryVertices.clone(
    cut = cms.string('ndof>4 &'
                     'abs(z)<24 &'
	             '!isFake &'
	             'position.Rho<2'
    ),
)

# Alternatively
#goodPV = cms.EDFilter("GoodVertexFilter",
#    vertexCollection = cms.InputTag('offlinePrimaryVertices'),
#    minimumNDOF = cms.uint32(4) ,
#    maxAbsZ = cms.double(24),	
#    maxd0 = cms.double(2)	
#)




oneGoodPVSelection = cms.EDFilter("VertexCountFilter",
    src = cms.string('goodPV'),
    minNumber = cms.int32(1),
)
