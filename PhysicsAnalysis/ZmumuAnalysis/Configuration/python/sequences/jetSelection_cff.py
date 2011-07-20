import FWCore.ParameterSet.Config as cms

## Collection cleaner
#from PhysicsTools.PatAlgos.cleaningLayer1.cleanPatCandidates_cff import *
## jet selector
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
## jet count filter
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *





###########################################################################################
#
# JET COLLECTION CLEANING - DO NOT USE, WHEN USING JetZOverlapCleaner
#
###########################################################################################

### These collections should be only used for cleaning of jets againgst isolated leptons
#
#
### Check for overlaps, but do not yet clean chosen isolated leptons out of collection
## Clean particleFlow-jet colleciton from electrons and muons (only isolated leptons)
#cleanPatJets.src = "selectedPatJetsAK5PF"
#cleanPatJets.preselection = 'pt>15. & abs(eta)<2.4'
#
### Clean via predefined lepton collections
#cleanPatMuons.preselection = 'isGlobalMuon & isTrackerMuon & (trackIso+caloIso)/pt < 0.15'
#cleanPatElectrons.preselection = 'electronID("simpleEleId85relIso")==7'
## This cleans them out
#cleanPatJets.finalCut = '!hasOverlaps("muons") & !hasOverlaps("electrons")'
#
### Alternative: clean via jet methods
## take care to check for isolation
##cleanPatJets.checkOverlaps.muons.src  = 'looseMuons'
##cleanPatJets.checkOverlaps.muons.preselection = 'trackIso < 3.'
##cleanPatJets.checkOverlaps.muons.deltaR  = 0.4
##cleanPatJets.checkOverlaps.muons.requireNoOverlaps = True 





###########################################################################################
#
# JET SELECTION
#
###########################################################################################

cleanJets = selectedPatJets.clone(
    src = 'selectedPatJetsAK5PF',
    cut = 'pt>15. & abs(eta)<2.4',
)




## good jet ID selection
# Either do it by hand (then, for the UN-COREECTED jets!!!)
#goodIdJets = selectedPatJets.clone(
#    src = 'cleanPatJets', 
#    # Definition of LOOSE PFjet id
#    # Selection needs to be done on uncorrected jets
#    cut = 'correctedJet("Uncorrected").neutralHadronEnergyFraction < 0.99'
#	  '& correctedJet("Uncorrected").neutralEmEnergyFraction < 0.99'
#	  '& correctedJet("Uncorrected").nConstituents > 1'
#	  # For eta <2.4, additional requirements
#	  '& correctedJet("Uncorrected").chargedHadronEnergyFraction > 0'
#	  '& correctedJet("Uncorrected").chargedEmEnergyFraction < 0.99'
#	  '& correctedJet("Uncorrected").chargedMultiplicity > 0',
#)

# Or use directly these simple selectors
from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector
pfJetIDSelector.version = 'FIRSTDATA'
pfJetIDSelector.quality = 'LOOSE'
goodIdJets = cms.EDFilter("PFJetIDSelectionFunctorFilter",
    filterParams = pfJetIDSelector.clone(),
    src = cms.InputTag('cleanJets'),
    #src = cms.InputTag('cleanPatJets'),  # if upper cleaning is used
    filter = cms.bool(False)
)



## Check for overlaps between (2 muons building) Z and jets
import ZmumuAnalysis.Producer.JetZOverlapCleaner_cfi
goodJets = ZmumuAnalysis.Producer.JetZOverlapCleaner_cfi.JetZOverlapCleaner.clone(
    jetSource = 'goodIdJets',
    dimuonSource = 'finalDimuons',
    deltaRMin = 0.5,
)
goodJetsZVetoLow = goodJets.clone(dimuonSource = 'finalDimuonsZVetoLow',)
goodJetsZVetoHigh = goodJets.clone(dimuonSource = 'finalDimuonsZVetoHigh',)



## hard jet selection
finalJets = selectedPatJets.clone(
    src = 'goodJets',
    cut = 'abs(eta) < 2.1 &'
          'pt > 25.',
)
finalJetsZVetoLow = finalJets.clone(src = 'goodJetsZVetoLow',)
finalJetsZVetoHigh = finalJets.clone(src = 'goodJetsZVetoHigh',)



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
bTcHeMJetsZVetoLow = bTcHeMJets.clone(src = 'finalJetsZVetoLow',)
bTcHpTJetsZVetoLow = bTcHpTJets.clone(src = 'finalJetsZVetoLow',)
bSsvHeMJetsZVetoLow = bSsvHeMJets.clone(src = 'finalJetsZVetoLow',)
bSsvHpTJetsZVetoLow = bSsvHpTJets.clone(src = 'finalJetsZVetoLow',)
bTcHeMJetsZVetoHigh = bTcHeMJets.clone(src = 'finalJetsZVetoHigh',)
bTcHpTJetsZVetoHigh = bTcHpTJets.clone(src = 'finalJetsZVetoHigh',)
bSsvHeMJetsZVetoHigh = bSsvHeMJets.clone(src = 'finalJetsZVetoHigh',)
bSsvHpTJetsZVetoHigh = bSsvHpTJets.clone(src = 'finalJetsZVetoHigh',)



##
## Count Filters
##

#oneCleanJetSelection = countPatJets.clone(src = 'cleanPatJets', minNumber = 1)
oneCleanJetSelection = countPatJets.clone(src = 'cleanJets', minNumber = 1)
oneGoodIdJetSelection = countPatJets.clone(src = 'goodIdJets', minNumber = 1)
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


oneGoodJetZVetoLowSelection = countPatJets.clone(src = 'goodJetsZVetoLow', minNumber = 1)
oneFinalJetZVetoLowSelection = countPatJets.clone(src = 'finalJetsZVetoLow', minNumber = 1)
oneBTcHeMJetZVetoLowSelection = countPatJets.clone(src = 'bTcHeMJetsZVetoLow', minNumber = 1)
oneBTcHpTJetZVetoLowSelection = countPatJets.clone(src = 'bTcHpTJetsZVetoLow', minNumber = 1)
oneBSsvHeMJetZVetoLowSelection = countPatJets.clone(src = 'bSsvHeMJetsZVetoLow', minNumber = 1)
oneBSsvHpTJetZVetoLowSelection = countPatJets.clone(src = 'bSsvHpTJetsZVetoLow', minNumber = 1)

twoFinalJetZVetoLowSelection = oneFinalJetZVetoLowSelection.clone(minNumber = 2)
twoBTcHeMJetZVetoLowSelection = oneBTcHeMJetZVetoLowSelection.clone(minNumber = 2)
twoBTcHpTJetZVetoLowSelection = oneBTcHpTJetZVetoLowSelection.clone(minNumber = 2)
twoBSsvHeMJetZVetoLowSelection = oneBSsvHeMJetZVetoLowSelection.clone(minNumber = 2)
twoBSsvHpTJetZVetoLowSelection = oneBSsvHpTJetZVetoLowSelection.clone(minNumber = 2)


oneGoodJetZVetoHighSelection = countPatJets.clone(src = 'goodJetsZVetoHigh', minNumber = 1)
oneFinalJetZVetoHighSelection = countPatJets.clone(src = 'finalJetsZVetoHigh', minNumber = 1)
oneBTcHeMJetZVetoHighSelection = countPatJets.clone(src = 'bTcHeMJetsZVetoHigh', minNumber = 1)
oneBTcHpTJetZVetoHighSelection = countPatJets.clone(src = 'bTcHpTJetsZVetoHigh', minNumber = 1)
oneBSsvHeMJetZVetoHighSelection = countPatJets.clone(src = 'bSsvHeMJetsZVetoHigh', minNumber = 1)
oneBSsvHpTJetZVetoHighSelection = countPatJets.clone(src = 'bSsvHpTJetsZVetoHigh', minNumber = 1)

twoFinalJetZVetoHighSelection = oneFinalJetZVetoHighSelection.clone(minNumber = 2)
twoBTcHeMJetZVetoHighSelection = oneBTcHeMJetZVetoHighSelection.clone(minNumber = 2)
twoBTcHpTJetZVetoHighSelection = oneBTcHpTJetZVetoHighSelection.clone(minNumber = 2)
twoBSsvHeMJetZVetoHighSelection = oneBSsvHeMJetZVetoHighSelection.clone(minNumber = 2)
twoBSsvHpTJetZVetoHighSelection = oneBSsvHpTJetZVetoHighSelection.clone(minNumber = 2)



###########################################################################################
#
# SEQUENCES
#
###########################################################################################


applyJetCleaning = cms.Sequence(
    cleanJets  # when using JetZOverlapCleaner
    #cleanPatCandidates  # when using overlap cleaning via cleanPat sequence
)


buildJetCollections = cms.Sequence(
    applyJetCleaning*
    goodIdJets*
    goodJets*
    finalJets*
    bSsvHeMJets*
    bSsvHpTJets*
    
    goodJetsZVetoLow*
    finalJetsZVetoLow*
    bSsvHeMJetsZVetoLow*
    bSsvHpTJetsZVetoLow*
    
    goodJetsZVetoHigh*
    finalJetsZVetoHigh*
    bSsvHeMJetsZVetoHigh*
    bSsvHpTJetsZVetoHigh
)


oneJetSelection = cms.Sequence(
    oneCleanJetSelection*
    oneGoodIdJetSelection*
    oneGoodJetSelection*
    oneFinalJetSelection*
    oneBSsvHeMJetSelection*
    oneBSsvHpTJetSelection
)


oneJetZVetoLowSelection = cms.Sequence(
    oneCleanJetSelection*
    oneGoodIdJetSelection*
    oneGoodJetZVetoLowSelection*
    oneFinalJetZVetoLowSelection*
    oneBSsvHeMJetZVetoLowSelection*
    oneBSsvHpTJetZVetoLowSelection
)


oneJetZVetoHighSelection = cms.Sequence(
    oneCleanJetSelection*
    oneGoodIdJetSelection*
    oneGoodJetZVetoHighSelection*
    oneFinalJetZVetoHighSelection*
    oneBSsvHeMJetZVetoHighSelection*
    oneBSsvHpTJetZVetoHighSelection
)


twoJetSelection = cms.Sequence(
    
    oneBSsvHpTJetSelection*
    twoFinalJetSelection*
    
    twoBSsvHeMJetSelection*
    twoBSsvHpTJetSelection
)



