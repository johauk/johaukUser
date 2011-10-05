import FWCore.ParameterSet.Config as cms

## di-muon candidate producer
from ElectroWeakAnalysis.Skimming.dimuons_cfi import *
## di-muon candidate count filter
from ElectroWeakAnalysis.Skimming.dimuonsFilter_cfi import *



###########################################################################################
#
# DI-MUON SELECTION
#
###########################################################################################

##
## Build Collections
##

dimuons = cms.EDProducer("CandViewShallowCloneCombiner",
    checkCharge = cms.bool(False),
    cut = cms.string(''),
    #decay = cms.string('isolatedHltMuons@+ isolatedMuons@-'),
    decay = cms.string('isolatedMuons@+ isolatedMuons@-'),
)



# Check trigger object matching for muons
## Use the "CandViewSelector" and not the "CandViewRefSelector":
## First one is a lazy parser, so knows about input type
## Here: it is a ShallowCloneCandidate with corresponding methods and not only a Candidate*, as the plugin thinks as it is its input
selectedDimuons = cms.EDFilter("CandViewSelector",
src = cms.InputTag("dimuons"),
    cut = cms.string(
      '(daughter(0).masterClone.triggerObjectMatches.size > 0) & (daughter(1).masterClone.triggerObjectMatches.size > 0)'
    ),
)



# Vertex association cleaning (distance of muon-muon, and dimuon)
from ZmumuAnalysis.Producer.BestZVertexCleaner_cfi import BestZVertexCleaner
cleanDimuons = BestZVertexCleaner.clone(
    product = "dimuon",
    vertexSource = 'goodPVs',
    dimuonSource = 'selectedDimuons',
    deltaZMuMuMax = 0.1,
    deltaZZVertexMax = 0.1,
)



# Cuts on properties of Dimuon system & Split opposite charge vs same charge
goodDimuons = cms.EDFilter("CandViewRefSelector",
    src = cms.InputTag("cleanDimuons"),
    cut = cms.string(
      'mass > 12. &'
      #'(daughter(0).vz()-daughter(1).vz())<0.1 &'  already contained in cleanDimuons
      'charge = 0'
    ),
)
#goodDimuonsSc = goodDimuons.clone(cut = 'mass > 12. & charge != 0',)



# Primary vertices associated to goodDimuons
goodDimuonPVs = BestZVertexCleaner.clone(
    product = "vertex",
    vertexSource = 'goodPVs',
    dimuonSource = 'goodDimuons',
    deltaZMuMuMax = 0.1,
    deltaZZVertexMax = 0.1,
)



# Choose best dimuon
from ZmumuAnalysis.Producer.BestZSelector_cfi import BestZSelector
bestDimuon = BestZSelector.clone(
    dimuonSource = 'goodDimuons',
    criterion = 'zMass',
)



# Associated primary vertex for bestDimuon
bestPV = BestZVertexCleaner.clone(
    product = "vertex",
    vertexSource = 'goodDimuonPVs',
    dimuonSource = 'bestDimuon',
    deltaZMuMuMax = 0.1,
    deltaZZVertexMax = 0.1,
)



# Final cuts on dimuon properties
finalDimuons = cms.EDFilter("CandViewRefSelector",
    src = cms.InputTag("bestDimuon"),
    cut = cms.string(
      'mass > 60. &'
      'mass < 120.'
    ),
)
finalDimuonsZVetoLow = finalDimuons.clone(
    cut = 'mass <= 60.',
)
finalDimuonsZVetoHigh = finalDimuons.clone(
    cut = 'mass >= 120. & mass < 400.',
)





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
finalDimuonSelection = dimuonsFilter.clone(
    src = 'finalDimuons',
    minNumber = 1,
)

finalDimuonZVetoLowSelection = finalDimuonSelection.clone(src = 'finalDimuonsZVetoLow',)
finalDimuonZVetoHighSelection = finalDimuonSelection.clone(src = 'finalDimuonsZVetoHigh',)





###########################################################################################
#
# SEQUENCES
#
###########################################################################################



buildDimuonCollections = cms.Sequence(
    dimuons*
    selectedDimuons*
    cleanDimuons*
    goodDimuons*
    goodDimuonPVs*
    bestDimuon*
    bestPV*
    finalDimuons*
    
    finalDimuonsZVetoLow*
    finalDimuonsZVetoHigh
)



dimuonSelection = cms.Sequence(
    selectedDimuonSelection*
    cleanDimuonSelection*
    goodDimuonSelection*
    finalDimuonSelection
)


dimuonZVetoLowSelection = dimuonSelection.copy()
dimuonZVetoLowSelection.replace(finalDimuonSelection,finalDimuonZVetoLowSelection)

dimuonZVetoHighSelection = dimuonSelection.copy()
dimuonZVetoHighSelection.replace(finalDimuonSelection,finalDimuonZVetoHighSelection)













