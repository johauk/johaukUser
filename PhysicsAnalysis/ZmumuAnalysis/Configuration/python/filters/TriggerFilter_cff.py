import FWCore.ParameterSet.Config as cms

import HLTrigger.HLTfilters.hltHighLevel_cfi



TriggerFilterMu9 =  HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone(
    HLTPaths = ["HLT_Mu9"],
)



TriggerFilterMu9_11_15 =  HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone(
    #TriggerResultsTag = cms.InputTag('TriggerResults','','HLT'),   # default
    HLTPaths = ["HLT_Mu9","HLT_Mu11","HLT_Mu15","HLT_Mu15_v*"],
    throw = False,   # do not throw exception on events where not all listed triggers are in...
)



TriggerFilterMu9_11_15_Redigi = TriggerFilterMu9_11_15.clone(
    TriggerResultsTag = cms.InputTag('TriggerResults','','REDIGI38X'),
)



# different trigger versions (bla_v*) are only in data, does not select events on MC at present (use there pure version w/o suffix)
TriggerFilterMu15 =  HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone(
    HLTPaths = ["HLT_Mu15","HLT_Mu15_v*"],
    throw = False,
)



