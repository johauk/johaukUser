import FWCore.ParameterSet.Config as cms

## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
## muon count filter
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *
## trigger matching of muon
from PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cfi import *
from PhysicsTools.PatAlgos.triggerLayer1.triggerMatcher_cfi import *
from PhysicsTools.PatAlgos.triggerLayer1.triggerEventProducer_cfi import *
#from PhysicsTools.PatAlgos.triggerLayer1.triggerMatchEmbedder_cfi import *
from ZmumuAnalysis.Producer.TriggerMatchedMuonProducer_cfi import *



###########################################################################################
#
# MUON SELECTION
#
###########################################################################################

##
## Build Collections
##

## Common loose selection for both muons
looseMuons = selectedPatMuons.clone(
    src = 'selectedPatMuons',
    cut = 'isGlobalMuon' +'&'+
          'track.hitPattern.numberOfValidTrackerHits > 10' +'&'+
	  'abs(eta) < 2.4' +'&'+
	  'pt > 20.',
)

## Tight selection for at least one muon
tightMuons = selectedPatMuons.clone(
    src = 'looseMuons',
    cut = 'isTrackerMuon' +'&'+
          'track.hitPattern.numberOfValidPixelHits > 0' +'&'+
	  'numberOfMatches > 1' +'&'+
	  'globalTrack.hitPattern.numberOfValidMuonHits > 0' +'&'+
	  'globalTrack.normalizedChi2 < 10.' +'&'+
	  'abs(dB) < 0.2' +'&'+
	  'abs(eta) < 2.1',
)

## Tight muons matched to HLT object
patTrigger.onlyStandAlone = False
#patTrigger.triggerResults = cms.InputTag("TriggerResults::HLT")
#patTrigger.triggerEvent = cms.InputTag("hltTriggerSummaryAOD::HLT")
muonTriggerMatchHLTMuons = muonTriggerMatchHLTMu3.clone(
    src = 'tightMuons',
    filterIdsEnum  = ['TriggerMuon'], # 'TriggerMuon' is the enum from trigger::TriggerObjectType for HLT muons
    pathNames = ['HLT_Mu9'],
  #  maxDPtRel = 1.0,
  #  maxDeltaR = 0.2,
    resolveByMatchQuality = True,
)
patTriggerEvent.patTriggerMatches = ["muonTriggerMatchHLTMuons"]

# Not needed:
#selectedPatMuonsTriggerMatch = cleanPatMuonsTriggerMatch.clone(
#    src     = "tightMuons",
#    matches = ["muonTriggerMatchHLTMuons"],
#)

tightHltMuons = TriggerMatchedMuonProducer.clone(
    muonSource = "tightMuons",
)




##
## Count Filters
##

initialMuonSelection = countPatMuons.clone(
    src = 'selectedPatMuons',
    minNumber = 2,
)
looseMuonSelection = countPatMuons.clone(
    src = 'looseMuons',
    minNumber = 2,
)
tightMuonSelection = countPatMuons.clone(
    src = 'tightMuons',
    minNumber = 1,
)
tightHltMuonSelection = countPatMuons.clone(
    src = 'tightHltMuons',
    minNumber = 1,
)






###########################################################################################
#
# SEQUENCES
#
###########################################################################################



patTriggerSequence = cms.Sequence(
    patTrigger
    *muonTriggerMatchHLTMuons
    *patTriggerEvent
)

#muonTriggerMatchEmbedder = cms.Sequence(
#    selectedPatMuonsTriggerMatch
#)



buildCollections = cms.Sequence(
    looseMuons
    *tightMuons
    *patTriggerSequence
#    *muonTriggerMatchEmbedder
    *tightHltMuons
)


muonSelection = cms.Sequence(
    initialMuonSelection
    *looseMuonSelection
    *tightMuonSelection
    *tightHltMuonSelection
)


