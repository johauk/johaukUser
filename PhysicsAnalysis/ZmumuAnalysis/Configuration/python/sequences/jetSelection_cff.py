import FWCore.ParameterSet.Config as cms

## Collection cleaner
from PhysicsTools.PatAlgos.cleaningLayer1.cleanPatCandidates_cff import *
## jet selector
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
## jet count filter
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *





###########################################################################################
#
# JET COLLECTION CLEANING - CREATE LEPTONS FOR CLEANING
#
###########################################################################################

# These collections should be only used for cleaning of jets againgst isolated leptons

# Use either preselection or final cut

cleanPatMuons.preselection = 'isGlobalMuon & isTrackerMuon & (trackIso+caloIso)/pt < 0.15'

cleanPatElectrons.preselection = 'electronID("simpleEleId85relIso")==7'




###########################################################################################
#
# JET COLLECTION CLEANING - CHECK FOR OVERLAPS, BUT DO NOT YET CLEAN CHOSEN ISOLATED LEPTONS OUT OF COLLECTION ?
#
###########################################################################################

# Clean particleFlow-jet colleciton from electrons and muons (clean out only isolated leptons)

cleanPatJets.src = "selectedPatJetsAK5PF"
cleanPatJets.preselection = 'pt>15. & abs(eta)<2.4'
# This would clean them out
cleanPatJets.finalCut = '!hasOverlaps("muons") & !hasOverlaps("electrons")'



###########################################################################################
#
# JET COLLECTION CLEANING - CHECK FOR OVERLAPS BETWEEN 2 FINAL MUONS BUILDING THE Z AND THE JETS ???
#
###########################################################################################


import ZmumuAnalysis.Producer.JetZOverlapCleaner_cfi
cleanJets = ZmumuAnalysis.Producer.JetZOverlapCleaner_cfi.JetZOverlapCleaner.clone(
    jetSource = 'cleanPatJets',
    dimuonSource = 'finalDimuons',
    deltaRMin = 0.5,
)

# take care to check for isolation

#cleanPatJets.checkOverlaps.muons.src  = 'looseMuons'
#cleanPatJets.checkOverlaps.muons.preselection = 'trackIso < 3.'
#cleanPatJets.checkOverlaps.muons.deltaR  = 0.4
#cleanPatJets.checkOverlaps.muons.requireNoOverlaps = True 





###########################################################################################
#
# JET SELECTION
#
###########################################################################################


## good jet ID selection
goodJets = selectedPatJets.clone(
    src = 'cleanPatJets', 
    cut = 'abs(eta) < 2.5'
          '& chargedHadronEnergyFraction > 0.0'
	  '& neutralHadronEnergyFraction < 1.0'
	  '& chargedEmEnergyFraction < 1.0'
	  '& neutralEmEnergyFraction < 1.0'
	  '& chargedMultiplicity > 0'
	  '& nConstituents > 1',
)

## hard jet selection
finalJets = selectedPatJets.clone(
    src = 'goodJets',
    cut = 'pt > 30.',
)


## b-tagging TrackCountingHighEfficiency with loose Working point 1.7
bTcheJets = selectedPatJets.clone(
    src = 'finalJets',
    cut = 'bDiscriminator("trackCountingHighEffBJetTags") > 1.7',
)
## OR b-tagging SecondaryVertexHighEfficiency with loose Working point 1.74
bSvheJets = selectedPatJets.clone(
    src = 'finalJets',
    cut = 'bDiscriminator("simpleSecondaryVertexHighEffBJetTags") > 1.74',
)


##
## Count Filters
##

oneCleanPatJetSelection = countPatJets.clone(src = 'cleanPatJets', minNumber = 1)
oneCleanJetSelection = countPatJets.clone(src = 'cleanJets', minNumber = 1)
oneGoodJetSelection = countPatJets.clone(src = 'goodJets', minNumber = 1)
oneFinalJetSelection = countPatJets.clone(src = 'finalJets', minNumber = 1)
oneBTcheJetSelection = countPatJets.clone(src = 'bTcheJets', minNumber = 1)
oneBSvheJetSelection = countPatJets.clone(src = 'bSvheJets', minNumber = 1)




###########################################################################################
#
# SEQUENCES
#
###########################################################################################


apllyJetCleaning = cms.Sequence(
    cleanPatCandidates
)


buildJetCollections = cms.Sequence(
    apllyJetCleaning
    *cleanJets
    *goodJets
    *finalJets
    *bTcheJets
    *bSvheJets
)


jetSelection = cms.Sequence(
    oneCleanPatJetSelection
    *oneCleanJetSelection
    *oneGoodJetSelection
    *oneFinalJetSelection
    *oneBTcheJetSelection   # do not use both b-taggings at same time
    #*oneBSvheJetSelection
)


