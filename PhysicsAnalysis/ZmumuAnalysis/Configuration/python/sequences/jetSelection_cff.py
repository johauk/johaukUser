import FWCore.ParameterSet.Config as cms

## Collection cleaner
from PhysicsTools.PatAlgos.cleaningLayer1.cleanPatCandidates_cff import *
## jet selector
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
## jet count filter
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *





###########################################################################################
#
# JET COLLECTION CLEANING
#
###########################################################################################

# Clean particleFlow-jet colleciton from electrons and muons (clean out only isolated leptons)

cleanPatJets.src = "selectedPatJetsAK5PF"

cleanPatElectrons.finalCut = cms.string(
    'et > 20.'
    '& abs(eta) < 2.5'
    '& electronID("simpleEleId80relIso")'
    '& (trackIso+caloIso)/pt < 0.15'
)
cleanPatJets.checkOverlaps.electrons.deltaR  = 0.4
cleanPatJets.checkOverlaps.electrons.requireNoOverlaps = True 

# take care to check for isolation
cleanPatJets.checkOverlaps.muons.src  = 'looseMuons'
cleanPatJets.checkOverlaps.muons.preselection = 'trackIso < 3.'
cleanPatJets.checkOverlaps.muons.deltaR  = 0.4
cleanPatJets.checkOverlaps.muons.requireNoOverlaps = True 





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

oneCleanJetSelection = countPatJets.clone(src = 'cleanPatJets', minNumber = 1)
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
    *goodJets
    *finalJets
    *bTcheJets
    *bSvheJets
)


jetSelection = cms.Sequence(
    oneCleanJetSelection
    *oneGoodJetSelection
    *oneFinalJetSelection
    *oneBTcheJetSelection   # do not use both b-taggings at same time
    #*oneBSvheJetSelection
)


