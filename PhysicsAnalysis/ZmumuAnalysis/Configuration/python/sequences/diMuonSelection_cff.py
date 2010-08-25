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
tightHltGlobalDimuons = dimuons.clone(
    checkCharge = False,
    cut = 'daughter(0).isGlobalMuon = 1' +'&'+
	  'daughter(1).isGlobalMuon = 1',
    #decay = 'tightHltMuons@+ tightHltMuons@-',
    #decay = 'tightMuonsTriggerMatch@+ tightMuonsTriggerMatch@-',
    decay = 'tightHltMuonsTriggerMatch@+ tightHltMuonsTriggerMatch@-',
)



# Collection of interest, but with ambiguities
looseTightHltGlobalDimuons = tightHltGlobalDimuons.clone(
    #decay = 'tightHltMuons@+ looseMuons@-',
    #decay = 'tightMuonsTriggerMatch@+ looseMuonsTriggerMatch@-',
    decay = 'tightHltMuonsTriggerMatch@+ looseMuonsTriggerMatch@-',
)



# Build collection orthogonal to first one
overlapExcludedLooseTightHltGlobalDimuons = cms.EDFilter("ZMuMuOverlapExclusionSelector",
    src = cms.InputTag("looseTightHltGlobalDimuons"),
    overlap = cms.InputTag("tightHltGlobalDimuons"),
    filter = cms.bool(False),
)



# Merge collections without ambiguities
selectedDimuons = cms.EDProducer("CandViewMerger",
    src = cms.VInputTag("tightHltGlobalDimuons","overlapExcludedLooseTightHltGlobalDimuons")
)



# Cuts on properties of Dimuon system
goodDimuons = cms.EDFilter("CandViewRefSelector",
    src = cms.InputTag("selectedDimuons"),
    cut = cms.string(
      'abs(daughter(0).eta)<2.1 || abs(daughter(1).eta)<2.1'# +'&'+
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



# Check for HLT matching of at least one of both Muons
atLeast1HltDimuons = cms.EDFilter("ZHLTMatchFilter",
    src = cms.InputTag("isolatedDimuons"),
    condition =cms.string("atLeastOneMatched"),
    #condition =cms.string("bothMatched"),
    #condition =cms.string("firstMatched"),  # implicates that 2nd is not a global muon!!!
    #condition =cms.string("exactlyOneMatched"),
    hltPath = cms.string("HLT_Mu9"),
    filter = cms.bool(False) 
)



# Final cuts on dimuon properties
finalDimuons = cms.EDFilter("CandViewRefSelector",
    src = cms.InputTag("isolatedDimuons"),
    cut = cms.string(
      'mass > 60.' +'&'+
      'mass < 120.'# +'&'+
      #'charge = 0'# +'&'+
    ),
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


finalDimuonSelection = dimuonsFilter.clone(
    src = 'finalDimuons',
    minNumber = 1,
)




###########################################################################################
#
# SEQUENCES
#
###########################################################################################



buildDimuonCollections = cms.Sequence(
    tightHltGlobalDimuons
    *looseTightHltGlobalDimuons
    *overlapExcludedLooseTightHltGlobalDimuons
    *selectedDimuons
    *goodDimuons
    *isolatedDimuons
    *atLeast1HltDimuons
    *finalDimuons
)



dimuonSelection = cms.Sequence(
    selectedDimuonSelection
    *goodDimuonSelection
    *isolatedDimuonSelection
    *atLeast1HltDimuonSelection
    *finalDimuonSelection
)


