import FWCore.ParameterSet.Config as cms

## jet selector
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
## jet count filter
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *






###########################################################################################
#
# JET SELECTION
#
###########################################################################################

selectedJets = selectedPatJets.clone(
    src = 'selectedPatJetsAK5PF',
    cut = 'pt>15. & abs(eta)<2.4',
)



## Check for overlaps between (2 muons building) Z and jets
import ZmumuAnalysis.Producer.JetZOverlapCleaner_cfi
cleanJets = ZmumuAnalysis.Producer.JetZOverlapCleaner_cfi.JetZOverlapCleaner.clone(
    jetSource = 'selectedJets',
    dimuonSource = 'bestDimuon',
    deltaRMin = 0.5,
)



## good jet ID selection
# Either do it by hand (then, for the UN-COREECTED jets!!!)
#goodIdJets = selectedPatJets.clone(
#    src = 'cleanJets', 
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
goodJets = cms.EDFilter("PFJetIDSelectionFunctorFilter",
    filterParams = pfJetIDSelector.clone(),
    src = cms.InputTag('cleanJets'),
    filter = cms.bool(False)
)



## hard jet selection
finalJets = selectedPatJets.clone(
    src = 'goodJets',
    cut = 'abs(eta) < 2.1 &'
          'pt > 25.',
)



## b-tagging SecondaryVertexHighEfficiency with Medium Working point
bSsvHeMJets = selectedPatJets.clone(
    src = 'finalJets',
    cut = 'bDiscriminator("simpleSecondaryVertexHighEffBJetTags") > 1.74',
)
## OR b-tagging SecondaryVertexHighPurity with Tight(?) Working point (not yet clear set defined)
bSsvHpTJets = selectedPatJets.clone(
    src = 'finalJets',
    cut = 'bDiscriminator("simpleSecondaryVertexHighPurBJetTags") > 2.0',
)



##
## Count Filters
##

oneSelectedJetSelection = countPatJets.clone(src = 'selectedJets', minNumber = 1)
oneCleanJetSelection = countPatJets.clone(src = 'cleanJets', minNumber = 1)
oneGoodJetSelection = countPatJets.clone(src = 'goodJets', minNumber = 1)
oneFinalJetSelection = countPatJets.clone(src = 'finalJets', minNumber = 1)
oneBSsvHeMJetSelection = countPatJets.clone(src = 'bSsvHeMJets', minNumber = 1)
oneBSsvHpTJetSelection = countPatJets.clone(src = 'bSsvHpTJets', minNumber = 1)
twoFinalJetSelection = oneFinalJetSelection.clone(minNumber = 2)
twoBSsvHeMJetSelection = oneBSsvHeMJetSelection.clone(minNumber = 2)
twoBSsvHpTJetSelection = oneBSsvHpTJetSelection.clone(minNumber = 2)





###########################################################################################
#
# SEQUENCES
#
###########################################################################################




buildJetCollections = cms.Sequence(
    selectedJets*
    cleanJets*
    goodJets*
    finalJets*
    bSsvHeMJets*
    bSsvHpTJets
)



oneJetSelection = cms.Sequence(
    oneSelectedJetSelection*
    oneCleanJetSelection*
    oneGoodJetSelection*
    oneFinalJetSelection*
    oneBSsvHeMJetSelection*
    oneBSsvHpTJetSelection
)



twoJetSelection = cms.Sequence(
    twoFinalJetSelection*
    twoBSsvHeMJetSelection*
    twoBSsvHpTJetSelection
)



