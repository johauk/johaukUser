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
#cleanPatJets.finalCut = '!hasOverlaps("muons") & !hasOverlaps("electrons")'



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
    src = 'cleanJets', 
    # Definition of LOOSE PFjet id
    cut = 'neutralHadronEnergyFraction < 0.99'
	  '& neutralEmEnergyFraction < 0.99'
	  '& nConstituents > 1'
	  # For eta <2.4, additional requirements
	  '& chargedHadronEnergyFraction > 0'
	  '& chargedEmEnergyFraction < 0.99'
	  '& chargedMultiplicity > 0',
)

## hard jet selection
finalJets = selectedPatJets.clone(
    src = 'goodJets',
    cut = 'abs(eta) < 2.1 &'
          'pt > 25.',
)


## b-tagging TrackCountingHighEfficiency with Medium Working point
bTcHeMJets = selectedPatJets.clone(
    src = 'finalJets',
    cut = 'bDiscriminator("trackCountingHighEffBJetTags") > 3.3',
)
## b-tagging TrackCountingHighPurity with Tight Working point
bTcHpTJets = selectedPatJets.clone(
    src = 'finalJets',
    cut = 'bDiscriminator("trackCountingHighPurBJetTags") > 3.41',
)
## OR b-tagging SecondaryVertexHighEfficiency with Medium Working point
bSsvHeMJets = selectedPatJets.clone(
    src = 'finalJets',
    cut = 'bDiscriminator("simpleSecondaryVertexHighEffBJetTags") > 1.74',
)
## OR b-tagging SecondaryVertexHighEfficiency with Tight(?) Working point (not yet clear set defined)
bSsvHpTJets = selectedPatJets.clone(
    src = 'finalJets',
    cut = 'bDiscriminator("simpleSecondaryVertexHighPurBJetTags") > 2.0',
)




##
## Count Filters
##

oneCleanPatJetSelection = countPatJets.clone(src = 'cleanPatJets', minNumber = 1)
oneCleanJetSelection = countPatJets.clone(src = 'cleanJets', minNumber = 1)
oneGoodJetSelection = countPatJets.clone(src = 'goodJets', minNumber = 1)
oneFinalJetSelection = countPatJets.clone(src = 'finalJets', minNumber = 1)
oneBTcHeMJetSelection = countPatJets.clone(src = 'bTcHeMJets', minNumber = 1)
oneBTcHpTJetSelection = countPatJets.clone(src = 'bTcHpTJets', minNumber = 1)
oneBSsvHeMJetSelection = countPatJets.clone(src = 'bSsvHeMJets', minNumber = 1)
oneBSsvHpTJetSelection = countPatJets.clone(src = 'bSsvHpTJets', minNumber = 1)

twoFinalJetSelection = oneFinalJetSelection.clone(minNumber = 2)
twoBTcHeMJetSelection = oneBTcHeMJetSelection.clone(minNumber = 2)
twoBTcHpTJetSelection = oneBTcHpTJetSelection.clone(minNumber = 2)
twoBSsvHeMJetSelection = oneBSsvHeMJetSelection.clone(minNumber = 2)
twoBSsvHpTJetSelection = oneBSsvHpTJetSelection.clone(minNumber = 2)



###########################################################################################
#
# SEQUENCES
#
###########################################################################################


applyJetCleaning = cms.Sequence(
    cleanPatCandidates
)


buildJetCollections = cms.Sequence(
    applyJetCleaning
    *cleanJets
    *goodJets
    *finalJets
    
    *bTcHeMJets
    *bTcHpTJets
    *bSsvHeMJets
    *bSsvHpTJets
)


oneJetSelection = cms.Sequence(
    oneCleanPatJetSelection
    *oneCleanJetSelection
    *oneGoodJetSelection
    *oneFinalJetSelection
    
    #*oneBTcHeMJetSelection 
    #*oneBTcHpTJetSelection 
    *oneBSsvHeMJetSelection
    #*oneBSsvHpTJetSelection
)



twoJetSelection = cms.Sequence(
    twoFinalJetSelection
    
    *oneBSsvHpTJetSelection
    
    #*twoBTcHeMJetSelection 
    #*twoBTcHpTJetSelection 
    #*twoBSsvHeMJetSelection
    *twoBSsvHpTJetSelection
)



