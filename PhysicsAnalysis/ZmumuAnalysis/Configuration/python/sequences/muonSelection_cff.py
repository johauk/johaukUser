import FWCore.ParameterSet.Config as cms

## muon selector
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
## muon count filter
from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *

## jet selector
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import *
## jet count filter
from PhysicsTools.PatAlgos.selectionLayer1.jetCountFilter_cfi import *



###########################################################################################
#
# MUON SELECTION
#
###########################################################################################

##
## Build Collections
##

##
## good muon id as given in https://twiki.cern.ch/twiki/bin/viewauth/CMS/MUO4ICHEP#Muon_Definition
##

## muons in muon system range (tracker up to 2.5)
tightMuons = selectedPatMuons.clone(
    src = 'selectedPatMuons',
    cut = 'abs(eta) < 2.4',
)
## muons reconstructed as globalMuon AND trackerMuon: isGlobalMuon() && isTrackerMuon()
globalTrackerMuons = selectedPatMuons.clone(
    src = 'tightMuons',
    cut = 'isGlobalMuon & isTrackerMuon',
)
## no. of hits in pixel: track()->hitPattern().numberOfValidPixelHits() > 0
goodPixelMuons = selectedPatMuons.clone(
    src = 'globalTrackerMuons',
    cut = 'track.hitPattern.numberOfValidPixelHits > 0',
)
## no. of hits in tracker: track()->hitPattern().numberOfValidTrackerHits() > 10
goodTrackMuons = selectedPatMuons.clone(
    src = 'goodPixelMuons',
    #cut = 'track.hitPattern.numberOfValidTrackerHits > 10',
    cut = 'track.hitPattern.numberOfValidStripHits > 9',
)
## no. of muon stations: numberOfMatches() > 1
muonMuons = selectedPatMuons.clone(
    src = 'goodTrackMuons',
    cut = 'numberOfMatches > 1',
)
## no. of muon hits in global fit: globalTrack()->hitPattern().numberOfValidMuonHits() > 0
goodMuonMuons = selectedPatMuons.clone(
    src = 'muonMuons',
    cut = 'globalTrack.hitPattern.numberOfValidMuonHits > 0',
)
## normalized chi2 of global fit: globalTrack()->normalizedChi2() < 10.
goodFitMuons = selectedPatMuons.clone(
    src = 'goodMuonMuons',
    cut = 'globalTrack.normalizedChi2 < 10.',
)
## transverse impact parameter
goodD0BeamspotMuons = selectedPatMuons.clone(
    src = 'goodFitMuons',
    cut = 'abs(dB) < 0.2',
)
goodIdMuons = goodD0BeamspotMuons.clone()


##
## additional selection for Z->mumu (only partly applied) as given in https://twiki.cern.ch/twiki/bin/view/CMS/VbtfZMuMuBaselineSelection
##

## pt cut
hardMuons = selectedPatMuons.clone(
    src = 'goodIdMuons',
    cut = 'pt > 20.',
)
## mip signature ecal
emCalMipMuons = selectedPatMuons.clone(
    src = 'hardMuons',
    cut = 'isolationR03.emVetoEt < 4.',
)
## mip signature hcal
calMipMuons = selectedPatMuons.clone(
    src = 'emCalMipMuons',
    cut = 'isolationR03.hadVetoEt < 6.',
)
## isolation cut
isolatedMuons = selectedPatMuons.clone(
    src = 'calMipMuons',
    cut = '(trackIso+caloIso)/pt < 0.3',
)
goodZmumuMuons = isolatedMuons.clone()



### Count Filters
#tightMuonSelection      = countPatMuons.clone(src = 'tightMuons',     minNumber = 2)
#globalMuonSelection     = countPatMuons.clone(src = 'globalMuons',    minNumber = 2)
#hardMuonSelection       = countPatMuons.clone(src = 'hardMuons',      minNumber = 2)
#goodTrackMuonSelection  = countPatMuons.clone(src = 'goodTrackMuons', minNumber = 2)
#goodD0MuonSelection     = countPatMuons.clone(src = 'goodD0Muons',    minNumber = 2)
#goodFitMuonSelection    = countPatMuons.clone(src = 'goodFitMuons',   minNumber = 2)
#ecalMipMuonSelection    = countPatMuons.clone(src = 'ecalMipMuons',   minNumber = 2)
#hcalMipMuonSelection    = countPatMuons.clone(src = 'hcalMipMuons',   minNumber = 2)
#isolatedMuonSelection   = countPatMuons.clone(src = 'isolatedMuons',  minNumber = 2)






###########################################################################################
#
# SEQUENCES
#
###########################################################################################


buildGoodIdMuonCollections = cms.Sequence(
    tightMuons*
    globalTrackerMuons*
    goodPixelMuons*
    goodTrackMuons*
    muonMuons*
    goodMuonMuons*
    goodFitMuons*
    goodD0BeamspotMuons*
    goodIdMuons
)			       			       


buildZmumuMuonCollections = cms.Sequence(
    hardMuons*
    emCalMipMuons*
    calMipMuons*
    isolatedMuons*
    goodZmumuMuons
)



buildCollections = cms.Sequence(
    buildGoodIdMuonCollections*
    buildZmumuMuonCollections
)





#fullLeptonicMuonMuonSelection = cms.Sequence(tightMuonSelection *
#                                             globalMuonSelection *
#				             hardMuonSelection *
#				             goodTrackMuonSelection *
#				             goodD0MuonSelection *
#				             goodFitMuonSelection *
#				             ecalMipMuonSelection *
#				             hcalMipMuonSelection *
#				             isolatedMuonSelection
#                                            )









