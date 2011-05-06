import FWCore.ParameterSet.Config as cms

## di-muon candidate producer
from ElectroWeakAnalysis.Skimming.dimuons_cfi import *
## di-muon candidate count filter
from ElectroWeakAnalysis.Skimming.dimuonsFilter_cfi import *
## isolation selection
# Do not use anymore this IsoDeposit based parameters, use default PAT values
#from ElectroWeakAnalysis.ZMuMu.zSelection_cfi import *



###########################################################################################
#
# DI-MUON SELECTION
#
###########################################################################################

##
## Build Collections
##

# Collection for ambiguity cleaning using "ZMuMuOverlapExclusionSelector"
#tightHltGlobalDimuons = dimuons.clone(
#    checkCharge = False,
#    cut = '',#daughter(0).isGlobalMuon = 1' +'&'+
#	  #'daughter(1).isGlobalMuon = 1',
#    #decay = 'tightHltMuons@+ tightHltMuons@-',
#    #decay = 'tightMuonsTriggerMatch@+ tightMuonsTriggerMatch@-',
#    decay = 'tightHltMuonsTriggerMatch@+ tightHltMuonsTriggerMatch@-',
#)
## One could use the "CandViewCombiner" as soon as it is made lazy (not yet in CMSSW_3_8_X) instead of the default "CandViewShallowCloneCombiner"
## Then daughters know that they are of type pat::Muon and not of ShallowCloneCandidate!
## But this is not needed since it knows again, when asking for the masterClone:
##  pat::Muon = ShallowCloneCandidate.masterClone()
## So always use the ShallowClone variant to use official tools in package ElectroWeakAnalysis/
tightHltGlobalDimuons = cms.EDProducer("CandViewShallowCloneCombiner",
#tightHltGlobalDimuons = cms.EDProducer("CandViewCombiner",
    checkCharge = cms.bool(False),
    cut = cms.string(''),
    decay = cms.string('tightHltMuonsTriggerMatch@+ tightHltMuonsTriggerMatch@-'),
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
    #overlap = cms.InputTag("cleanDimuons2"),
    filter = cms.bool(False),
)



# Merge collections without ambiguities
selectedDimuons = cms.EDProducer("CandViewMerger",
    src = cms.VInputTag("tightHltGlobalDimuons","overlapExcludedLooseTightHltGlobalDimuons")
)



# Vertex association cleaning (distance of muon-muon, and dimuon)
from ZmumuAnalysis.Producer.BestZVertexCleaner_cfi import BestZVertexCleaner
cleanDimuons = BestZVertexCleaner.clone(
    product = "dimuon",
    vertexSource = 'goodPV',
    dimuonSource = 'selectedDimuons',
    #dimuonSource = 'looseTightHltGlobalDimuons',
    deltaZMax = 0.1,
)



# Cuts on properties of Dimuon system & Split opposite charge vs same charge
goodDimuons = cms.EDFilter("CandViewRefSelector",
    src = cms.InputTag("cleanDimuons"),
    cut = cms.string(
      'mass > 20. &'
      '(daughter(0).vz()-daughter(1).vz())<0.1 &'
      'charge = 0'
    ),
)


goodDimuonsSC = cms.EDFilter("CandViewRefSelector",
    src = cms.InputTag("cleanDimuons"),
    cut = cms.string(
      'mass > 20. &'
      '(daughter(0).vz()-daughter(1).vz())<0.1 &'
      'charge != 0'
    ),
)



# Cut on isolation of both Muons in Dimuon system
## Do not use this complicated module based on IsoDeposits -- easily causes mistakes
#diMuonIsolation = zSelection.clone(
#  cut = '',
#  isoCut = 3.,
#)
#isolatedDimuons = cms.EDFilter("ZToMuMuIsolatedIDSelector",
#    diMuonIsolation,
#    src = cms.InputTag("goodDimuons"),
#    filter = cms.bool(False)
#)
## Instead use this module as long as it works (no combined and no relative isolation!!! - so, tracker only or calo only...)
## But does it really work as expected??? --- no event is deselected!!!
#isolatedDimuons = cms.EDFilter("ZToMuMuIsolatedSelector",
#    src = cms.InputTag("goodDimuons"),
#    cut = cms.string(''),
#    isoCut = cms.double(3.),
#    isolationType = cms.string("track"),
#    filter = cms.bool(False)
#)
## Do the isolation cuts by hand in simple way
## Use the "CandViewSelector" and not the "CandViewRefSelector":
## First one is a lazy parser, so knows about input type
## Here: it is a ShallowCloneCandidate with corresponding methods and not only a Candidate*, as the plugin thinks as it is its input
isolatedDimuons = cms.EDFilter("CandViewSelector",
    src = cms.InputTag("goodDimuons"),
    cut = cms.string(
      '((daughter(0).masterClone.trackIso + daughter(0).masterClone.caloIso) /daughter(0).masterClone.pt < 0.15) &'
      '((daughter(1).masterClone.trackIso + daughter(1).masterClone.caloIso) /daughter(1).masterClone.pt < 0.15)'
    ),
)
## Or use directly this method (Unfortunately works only on reco::Muon and not on pat::Muon)
#isolatedDimuons = cms.EDFilter("CompositeDimuonAndSelector",
#    src = cms.InputTag("goodDimuons"),
#    daughter1cut = cms.string('(isolationR03.sumPt + isolationR03.emEt + isolationR03.hadEt) /pt < 0.15'),
#    daughter2cut = cms.string('(isolationR03.sumPt + isolationR03.emEt + isolationR03.hadEt) /pt < 0.15'),
#)
isolatedDimuonsSC = isolatedDimuons.clone(src = "goodDimuonsSC")



# Check for HLT matching of at least one of both Muons
## Works only with 
atLeast1HltDimuons = cms.EDFilter("ZHLTMatchFilter",
    src = cms.InputTag("isolatedDimuons"),
    condition =cms.string("atLeastOneMatched"),
    #condition =cms.string("bothMatched"),
    #condition =cms.string("firstMatched"),  # implicates that 2nd is not a global muon!!!
    #condition =cms.string("exactlyOneMatched"),
    hltPath = cms.string("HLT_Mu9"),
    filter = cms.bool(False) 
)
atLeast1HltDimuonsSC = atLeast1HltDimuons.clone(src = "isolatedDimuonsSC")



# Final cuts on dimuon properties
finalDimuons = cms.EDFilter("CandViewRefSelector",
    src = cms.InputTag("isolatedDimuons"),
    #src = cms.InputTag("atLeast1HltDimuons"),
    cut = cms.string(
      'mass > 60.' +'&'+
      'mass < 120.'# +'&'+
      #'charge = 0'# +'&'+
    ),
)
finalDimuonsSC = finalDimuons.clone(src = "isolatedDimuonsSC")
#finalDimuonsSC = finalDimuons.clone(src = "atLeast1HltDimuonsSC")




##
## Count Filters
##

selectedDimuonSelection = dimuonsFilter.clone(
    src = 'selectedDimuons',
    minNumber = 1,
)


cleanDimuonSelection = dimuonsFilter.clone(
    src = 'cleanDimuons',
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


atLeast1HltDimuonSelection = dimuonsFilter.clone(
    src = 'atLeast1HltDimuons',
    minNumber = 1,
)


finalDimuonSelection = dimuonsFilter.clone(
    src = 'finalDimuons',
    minNumber = 1,
)



goodDimuonSCSelection = goodDimuonSelection.clone(src = 'goodDimuonsSC')
isolatedDimuonSCSelection = isolatedDimuonSelection.clone(src = 'isolatedDimuonsSC')
atLeast1HltDimuonSCSelection = atLeast1HltDimuonSelection.clone(src = 'atLeast1HltDimuonsSC')
finalDimuonSCSelection = finalDimuonSelection.clone(src = 'finalDimuonsSC')





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
    *cleanDimuons
    *goodDimuons
    *isolatedDimuons
#    *atLeast1HltDimuons
    *finalDimuons
)



buildDimuonSCCollections = cms.Sequence(
    tightHltGlobalDimuons
    *looseTightHltGlobalDimuons
    *overlapExcludedLooseTightHltGlobalDimuons
    *selectedDimuons
    *cleanDimuons
    *goodDimuonsSC
    *isolatedDimuonsSC
#    *atLeast1HltDimuonsSC
    *finalDimuonsSC
)



dimuonSelection = cms.Sequence(
    selectedDimuonSelection
    *cleanDimuonSelection
    *goodDimuonSelection
    *isolatedDimuonSelection
#    *atLeast1HltDimuonSelection
    *finalDimuonSelection
)



dimuonSCSelection = cms.Sequence(
    selectedDimuonSelection
    *cleanDimuonSelection
    *goodDimuonSCSelection
    *isolatedDimuonSCSelection
#    *atLeast1HltDimuonSCSelection
    *finalDimuonSCSelection
)


