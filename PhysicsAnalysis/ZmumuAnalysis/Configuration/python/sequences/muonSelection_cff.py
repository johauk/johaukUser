import FWCore.ParameterSet.Config as cms

## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
## muon count filter
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *
## trigger matching of muon
from PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cfi import *



###########################################################################################
#
# MUON SELECTION
#
###########################################################################################

##
## Build Collections
##



## Muons matched to HLT object (same collection w/o reduction, only information of HLT matching added)
#process.patTrigger.processName = "HLT"
#patTrigger.triggerResults = cms.InputTag("TriggerResults::HLT")
#patTrigger.triggerEvent = cms.InputTag("hltTriggerSummaryAOD::HLT")
selectedPatMuonsTriggerMatchHltMuons = cms.EDProducer("PATTriggerMatcherDRDPtLessByR",
    src     = cms.InputTag("selectedPatMuons"),
    matched = cms.InputTag("patTrigger"),
#    matchedCuts = cms.string('type("TriggerMuon") & (path("HLT_Mu9") | path("HLT_Mu11") | path("HLT_Mu15_v*"))'),
    matchedCuts = cms.string('type("TriggerMuon") & (path("HLT_DoubleMu5_v*") || path("HLT_DoubleMu6_v*"))'),
    maxDPtRel = cms.double(0.5),
    maxDeltaR = cms.double(0.3),
    resolveAmbiguities    = cms.bool(True),
    resolveByMatchQuality = cms.bool(True),
)
selectedPatMuonsTriggerMatch = cms.EDProducer("PATTriggerMatchMuonEmbedder",
    src     = cms.InputTag("selectedPatMuons"),
    matches = cms.VInputTag("selectedPatMuonsTriggerMatchHltMuons"),
)




## Common loose selection for both muons
looseMuons = selectedPatMuons.clone(
    src = 'selectedPatMuonsTriggerMatch',
    cut = 'isGlobalMuon &'
          'isTrackerMuon &'
          'track.hitPattern.numberOfValidTrackerHits > 10 &'
	  'abs(eta) < 2.4 &'
	  'pt > 10.',
)



## Tight selection for at least one muon
tightMuons = selectedPatMuons.clone(
    src = 'looseMuons',
    cut = 'isGlobalMuon &'
          'isTrackerMuon &'
	  'track.hitPattern.numberOfValidTrackerHits > 10 &'
          'track.hitPattern.numberOfValidPixelHits > 0 &'
	  'numberOfMatches > 1 &'
	  'globalTrack.hitPattern.numberOfValidMuonHits > 0 &'
	  'globalTrack.normalizedChi2 < 10. &'
	  'abs(dB) < 0.02 &'
	  'abs(eta) < 2.1 &'
	  'pt > 20.',
)



looseHltMuons = selectedPatMuons.clone(
    src = 'looseMuons',
    cut = 'triggerObjectMatches.size > 0',
)
tightHltMuons = selectedPatMuons.clone(
    src = 'tightMuons',
    cut = 'triggerObjectMatches.size > 0',
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
oneTightMuonSelection = countPatMuons.clone(
    src = 'tightMuons',
    minNumber = 1,
)
tightMuonSelection = countPatMuons.clone(
    src = 'tightMuons',
    minNumber = 2,
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
    *selectedPatMuonsTriggerMatchHltMuons
    *selectedPatMuonsTriggerMatch
)



buildMuonCollections = cms.Sequence(
    patTriggerSequence
    *looseMuons
    *tightMuons
    #*looseHltMuons
    *tightHltMuons
)



muonSelection = cms.Sequence(
    oneInitialMuonSelection
    *oneLooseMuonSelection
    *oneTightMuonSelection
    *looseMuonSelection
    *tightMuonSelection
    *tightHltMuonSelection
)



