import FWCore.ParameterSet.Config as cms

## di-muon candidate producer
from ElectroWeakAnalysis.Skimming.dimuons_cfi import *
## di-muon candidate count filter
from ElectroWeakAnalysis.Skimming.dimuonsFilter_cfi import *
## isolation selection
from ElectroWeakAnalysis.ZMuMu.zSelection_cfi import *



###########################################################################################
#
# MUON SELECTION
#
###########################################################################################

##
## Build Collections
##


# Collection for ambiguity cleaning using "ZMuMuOverlapExclusionSelector"
tightHLTGlobalDimuons = dimuons.clone(
    checkCharge = False,
    cut = 'daughter(0).isGlobalMuon = 1' +'&'+
	  'daughter(1).isGlobalMuon = 1',
    decay = 'tightHltMuons@+ tightHltMuons@-',
)



# Collection of interest, but with ambiguities
looseTightHltGlobalDimuons = tightHLTGlobalDimuons.clone(
    decay = 'tightHltMuons@+ looseMuons@-',
)



# Build collection orthogonal to first one
overlapExcludedLooseTightHltGlobalDimuons = cms.EDFilter("ZMuMuOverlapExclusionSelector",
    src = cms.InputTag("looseTightHltGlobalDimuons"),
    overlap = cms.InputTag("tightHLTGlobalDimuons"),
    filter = cms.bool(False),
)



# Merge collections without ambiguities
selectedDimuons = cms.EDProducer("CandViewMerger",
    src = cms.VInputTag("tightHLTGlobalDimuons","overlapExcludedLooseTightHltGlobalDimuons")
)



# Cuts on properties of Dimuon system
goodDimuons = cms.EDFilter("CandViewRefSelector",
    src = cms.InputTag("selectedDimuons"),
    cut = cms.string(
      'mass > 20.'# +'&'+
    ),
)



# Cut on isolation of both Muons in Dimuon system
diMuonIsolation = zSelection.clone(
  cut = '',
)
isolatedDimuons = cms.EDFilter("ZToMuMuIsolatedIDSelector",
    diMuonIsolation,
    src = cms.InputTag("goodDimuons"),
    filter = cms.bool(False)
)


# Check again for HLT matching of one Muon
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

selectedDimuonSelection = dimuonsFilter.clone(
    src = 'selectedDimuons',
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
    tightHLTGlobalDimuons
    *looseTightHltGlobalDimuons
    *overlapExcludedLooseTightHltGlobalDimuons
    *selectedDimuons
    *goodDimuons
    *isolatedDimuons
#    *atLeast1HltDimuons
)


dimuonSelection = cms.Sequence(
    selectedDimuonSelection
    *goodDimuonSelection
    *isolatedDimuonSelection
#    *atLeast1HltDimuonSelection
)


