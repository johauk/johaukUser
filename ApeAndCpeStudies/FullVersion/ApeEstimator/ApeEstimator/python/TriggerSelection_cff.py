import FWCore.ParameterSet.Config as cms





### Filter on primary vertex (needs vertex collection)
## As in DPGAnalysis/Skims/python/GOODCOLL_filter_cfg.py
#primaryVertexFilter1 = cms.EDFilter("GoodVertexFilter",
#    vertexCollection = cms.InputTag('offlinePrimaryVertices'),
#    minimumNDOF = cms.uint32(4) ,
#    maxAbsZ = cms.double(24), 
#    maxd0 = cms.double(2) 
#)
## As in DPGAnalysis/Skims/python/GOODCOLL_filter_cfg.py
#primaryVertexFilter2 = cms.EDFilter("VertexSelector",
#    src = cms.InputTag("offlinePrimaryVertices"),
#    cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.Rho <= 2"),
#    filter = cms.bool(True),
#)



### Beam scrap filter (input is "generalTracks", not configurable)
#beamScrapFilter = cms.EDFilter("FilterOutScraping",
#    applyfilter = cms.untracked.bool(True),
#    debugOn     = cms.untracked.bool(False),
#    numtrack    = cms.untracked.uint32(10),
#    thresh      = cms.untracked.double(0.25)
#)



### HBHE noise filter (needs HcalNoiseSummary)
#import CommonTools.RecoAlgos.HBHENoiseFilter_cfi
#HBHENoiseFilter = CommonTools.RecoAlgos.HBHENoiseFilter_cfi.HBHENoiseFilter.clone()



### Filter for L1 trigger bits (to require crossing bunches - technical trigger bits should not be used anymore...)
#from L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff import *
#import HLTrigger.HLTfilters.hltLevel1GTSeed_cfi
#L1T1 = HLTrigger.HLTfilters.hltLevel1GTSeed_cfi.hltLevel1GTSeed.clone()
#L1T1.L1TechTriggerSeeding = cms.bool(True)
#L1T1.L1SeedsLogicalExpression=cms.string('0')



## Filter for PhysicsDeclared (Stable Beams?)
#from HLTrigger.special.hltPhysicsDeclared_cfi import *
#hltPhysicsDeclared.L1GtReadoutRecordTag = 'gtDigis'



## SEQUENCE
TriggerSelectionSequence = cms.Sequence(
    #L1T1*
    #hltPhysicsDeclared
    #*primaryVertexFilter1
    #*primaryVertexFilter2
    #*beamScrapFilter
    #*HBHENoiseFilter
)


