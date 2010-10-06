import FWCore.ParameterSet.Config as cms

import HLTrigger.HLTfilters.hltHighLevel_cfi



AllLowestUnprescaledTriggerFilter = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone(
    #HLTPaths = ["HLT_Mu11","HLT_DoubleMu3","HLT_IsoMu9"],
    HLTPaths = ["HLT_Mu9","HLT_DoubleMu3"],
)



FinalTriggerFilter =  HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone(
    HLTPaths = ["HLT_Mu9"],
)

