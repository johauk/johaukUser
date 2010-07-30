import FWCore.ParameterSet.Config as cms

## di-muon candidate producer
from ElectroWeakAnalysis.Skimming.dimuons_cfi import *
## di-muon candidate count filter
from ElectroWeakAnalysis.Skimming.dimuonsFilter_cfi import *
## isolation selection
from ElectroWeakAnalysis.ZMuMu.zSelection_cfi import *
## trigger matching of muon



###########################################################################################
#
# MUON SELECTION
#
###########################################################################################

##
## Build Collections
##


looseTightHltGlobalDimuons = dimuons.clone(
    checkCharge = False,
    cut = 'daughter(0).isGlobalMuon = 1' +'&'+
	  'daughter(1).isGlobalMuon = 1',
    decay = 'tightHltMuons@+ looseMuons@-',
)




cutValues = cms.string(
    'mass > 20.'# +'&'+
)
goodDimuons = cms.EDFilter("CandViewRefSelector",
    src = cms.InputTag("looseTightHltGlobalDimuons"),
    cut = cutValues,
)



diMuonIsolation = zSelection.clone(
  cut = '',
)
isolatedDimuons = cms.EDFilter("ZToMuMuIsolatedIDSelector",
    diMuonIsolation,
    src = cms.InputTag("goodDimuons"),
    filter = cms.bool(False)
)


# does not work, no event survives...
atLeast1HltDimuons = cms.EDFilter("ZHLTMatchFilter",
    src = cms.InputTag("isolatedDimuons"),
    condition =cms.string("atLeastOneMatched"),
    hltPath = cms.string("HLT_Mu9"),
    filter = cms.bool(False) 
)




##
## Count Filters
##

looseTightHltGlobalDimuonSelection = dimuonsFilter.clone(
    src = 'looseTightHltGlobalDimuons',
    minNumber = 1,
)

goodDimuonSelection = dimuonsFilter.clone(
    src = 'goodDimuons',
    minNumber = 1,
)


isolatedDimuonSelection = dimuonsFilter.clone(
    src = 'isolatedDimuons',
    minNumber = 1,
)

# does not work, no event survives...
atLeast1HltDimuonSelection = dimuonsFilter.clone(
    src = 'atLeast1HltDimuons',
    minNumber = 1,
)


###########################################################################################
#
# SEQUENCES
#
###########################################################################################





buildDimuonCollections = cms.Sequence(
    looseTightHltGlobalDimuons
    *goodDimuons
    *isolatedDimuons
#    *atLeast1HltDimuons
)


dimuonSelection = cms.Sequence(
    looseTightHltGlobalDimuonSelection
    *goodDimuonSelection
    *isolatedDimuonSelection
#    *atLeast1HltDimuonSelection
)


