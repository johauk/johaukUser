import FWCore.ParameterSet.Config as cms

## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
## muon count filter
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *
## trigger matching of muon
from PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cfi import *
#from PhysicsTools.PatAlgos.triggerLayer1.triggerMatcher_cfi import *
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
	  'abs(eta) < 2.1' +'&'+
	  'abs(dB) < 0.2',
)



## Muons matched to HLT object (same collection w/o reduction, only information of HLT matching added)
#patTrigger.triggerResults = cms.InputTag("TriggerResults::HLT")
#patTrigger.triggerEvent = cms.InputTag("hltTriggerSummaryAOD::HLT")
looseMuonTriggerMatchHltMuons = cms.EDProducer("PATTriggerMatcherDRDPtLessByR",
    src     = cms.InputTag("looseMuons"),
    matched = cms.InputTag("patTrigger"),
    andOr          = cms.bool( False ),
    filterIdsEnum  = cms.vstring('TriggerMuon'), # 'TriggerMuon' is the enum from trigger::TriggerObjectType for HLT muons
    filterIds      = cms.vint32(0),
    filterLabels   = cms.vstring('*'),
    pathNames      = cms.vstring('HLT_Mu9'),#,'HLT_Mu11','HLT_Mu15_v*', 'HLT_Mu15'),
    collectionTags = cms.vstring('*'),
    maxDPtRel = cms.double(1.0),
    maxDeltaR = cms.double(0.2),
    resolveAmbiguities    = cms.bool(True),
    resolveByMatchQuality = cms.bool(False)
)
tightMuonTriggerMatchHltMuons = looseMuonTriggerMatchHltMuons.clone(
    src = "tightMuons",
)
patTriggerEvent.patTriggerMatches = ["looseMuonTriggerMatchHltMuons","tightMuonTriggerMatchHltMuons"]
looseMuonsTriggerMatch = cms.EDProducer("PATTriggerMatchMuonEmbedder",
    src     = cms.InputTag("looseMuons"),
    matches = cms.VInputTag("looseMuonTriggerMatchHltMuons")
)
#tightMuonsTriggerMatch = looseMuonsTriggerMatch.clone(
#    src     = "tightMuons",
#    matches = ["tightMuonTriggerMatchHltMuons"],
#)



## Tight muons matched to HLT object (collection containing only matched muons)
#patTrigger.onlyStandAlone = False
tightHltMuons = TriggerMatchedMuonProducer.clone(
    muonSource = "tightMuons",
    matches = "tightMuonTriggerMatchHltMuons",
)



tightHltMuonTriggerMatchHltMuons = looseMuonTriggerMatchHltMuons.clone(
    src = "tightHltMuons",
)
patTriggerEvent2 = patTriggerEvent.clone(
    patTriggerMatches = ["tightHltMuonTriggerMatchHltMuons"],
)
tightHltMuonsTriggerMatch = looseMuonsTriggerMatch.clone(
    src     = "tightHltMuons",
    matches = ["tightHltMuonTriggerMatchHltMuons"],
)




##
## Count Filters
##


oneInitialMuonSelection = countPatMuons.clone(
    src = 'selectedPatMuons',
    minNumber = 1,
)
oneLooseMuonSelection = countPatMuons.clone(
    src = 'looseMuons',
    minNumber = 1,
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
    patTrigger*
    looseMuonTriggerMatchHltMuons*
    tightMuonTriggerMatchHltMuons*
    patTriggerEvent
)



muonTriggerMatchEmbedder = cms.Sequence(
    looseMuonsTriggerMatch
    #*tightMuonsTriggerMatch
)


tightHltMuonTriggerSequenceAndTriggerMatchEmbedder = cms.Sequence(
    tightHltMuons
    *tightHltMuonTriggerMatchHltMuons
    *patTriggerEvent2
    *tightHltMuonsTriggerMatch
)



buildMuonCollections = cms.Sequence(
    looseMuons
    *tightMuons
    *patTriggerSequence
    *muonTriggerMatchEmbedder
    *tightHltMuonTriggerSequenceAndTriggerMatchEmbedder
)



muonSelection = cms.Sequence(
    oneInitialMuonSelection
    *oneLooseMuonSelection
    *looseMuonSelection
    *tightMuonSelection
    *tightHltMuonSelection
)



