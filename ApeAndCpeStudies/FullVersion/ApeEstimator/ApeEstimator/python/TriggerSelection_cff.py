import FWCore.ParameterSet.Config as cms






#### Event selection for Collision data (no MC)



## Filter for L1 trigger bits
from L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff import *
import HLTrigger.HLTfilters.hltLevel1GTSeed_cfi
L1T1 = HLTrigger.HLTfilters.hltLevel1GTSeed_cfi.hltLevel1GTSeed.clone()
L1T1.L1TechTriggerSeeding = cms.bool(True)
L1T1.L1SeedsLogicalExpression=cms.string('0 AND (40 OR 41) AND NOT (36 OR 37 OR 38 OR 39) AND NOT ((42 AND (NOT 43)) OR (43 AND (NOT 42)))')

L1T1forMC = HLTrigger.HLTfilters.hltLevel1GTSeed_cfi.hltLevel1GTSeed.clone()
L1T1forMC.L1TechTriggerSeeding = cms.bool(True)
L1T1forMC.L1SeedsLogicalExpression=cms.string('(40 OR 41) AND NOT (36 OR 37 OR 38 OR 39) AND NOT ((42 AND (NOT 43)) OR (43 AND (NOT 42)))')






## Filter for HLT physicsDeclared bit
hltHighLevel = cms.EDFilter("HLTHighLevel",
    TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
    HLTPaths = cms.vstring('HLT_PhysicsDeclared'),           # provide list of HLT paths (or patterns) you want
    eventSetupPathsKey = cms.string(''), # not empty => use read paths from AlCaRecoTriggerBitsRcd via this key
    andOr = cms.bool(True),             # how to deal with multiple triggers: True (OR) accept if ANY is true, False (AND) accept if ALL are true
    throw = cms.bool(True)    # throw exception on unknown path names
)




## SEQUENCE
TriggerSelectionSequence = cms.Sequence(
    L1T1
    *hltHighLevel
)

TriggerSelectionSequenceForMC = cms.Sequence(
    L1T1forMC
)

