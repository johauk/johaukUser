import os

import FWCore.ParameterSet.Config as cms



process = cms.Process("MyAlcareco")



##
## Message Logger
##
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories.append('AlignmentTrackSelector')
#process.MessageLogger.categories.append('')
process.MessageLogger.cerr.INFO.limit = 0
process.MessageLogger.cerr.default.limit = -1
process.MessageLogger.cerr.AlignmentTrackSelector = cms.untracked.PSet(limit = cms.untracked.int32(-1))

process.MessageLogger.cerr.FwkReport.reportEvery = 1000 ## really show only every 1000th



##
## Process options
##
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
)



##
## Input Files
##
## --- Particle Gun ---
process.load("ApeEstimator.ApeEstimator.samples.Mc_QcdMuEnriched_desy_cff")



##
## Number of Events (should be after input file)
##
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1001) )



##
## ALCARECOTkAlMuonIsolated selection
##

## First select goodId + isolated muons
#process.load("Alignment.CommonAlignmentProducer.python.TkAlMuonSelectors_cfi")
#process.load("Alignment.CommonAlignmentProducer.ALCARECOTkAlMuonIsolated_cff")
TkAlGoodIdMuonSelector = cms.EDFilter("MuonSelector",
    src = cms.InputTag('muons'),
    cut = cms.string('isGlobalMuon &'
                     'isTrackerMuon &'
                     'numberOfMatches > 1 &'
                     'globalTrack.hitPattern.numberOfValidMuonHits > 0 &'
                     'abs(eta) < 2.5 &'
                     'globalTrack.normalizedChi2 < 20.'),
    filter = cms.bool(True)
)
TkAlRelCombIsoMuonSelector = cms.EDFilter("MuonSelector",
    src = cms.InputTag(''),
    cut = cms.string('(isolationR03().sumPt + isolationR03().emEt + isolationR03().hadEt)/pt  < 0.15'),
    filter = cms.bool(True)
)
process.ALCARECOTkAlMuonIsolatedGoodMuons = TkAlGoodIdMuonSelector.clone()
process.ALCARECOTkAlMuonIsolatedRelCombIsoMuons = TkAlRelCombIsoMuonSelector.clone(src = 'ALCARECOTkAlMuonIsolatedGoodMuons')

## Then select their tracks with additional cuts
import Alignment.CommonAlignmentProducer.AlignmentTrackSelector_cfi
process.ALCARECOTkAlMuonIsolated = Alignment.CommonAlignmentProducer.AlignmentTrackSelector_cfi.AlignmentTrackSelector.clone(
    filter = True, ##do not store empty events
    applyBasicCuts = True,
    ptMin = 2.0, ##GeV 
    etaMin = -3.5,
    etaMax = 3.5,
    nHitMin = 0
)
process.ALCARECOTkAlMuonIsolated.GlobalSelector.muonSource = 'ALCARECOTkAlMuonIsolatedRelCombIsoMuons'
# Isolation is shifted to the muon preselection, and then applied intrinsically if applyGlobalMuonFilter = True
process.ALCARECOTkAlMuonIsolated.GlobalSelector.applyIsolationtest = False
process.ALCARECOTkAlMuonIsolated.GlobalSelector.applyGlobalMuonFilter = True
process.ALCARECOTkAlMuonIsolated.TwoBodyDecaySelector.applyMassrangeFilter = False
process.ALCARECOTkAlMuonIsolated.TwoBodyDecaySelector.applyChargeFilter = False
process.ALCARECOTkAlMuonIsolated.TwoBodyDecaySelector.applyAcoplanarityFilter = False

## Define ALCARECO sequence
process.mySeqALCARECOTkAlMuonIsolated = cms.Sequence(process.ALCARECOTkAlMuonIsolatedGoodMuons*process.ALCARECOTkAlMuonIsolatedRelCombIsoMuons*process.ALCARECOTkAlMuonIsolated)



##
## Good Primary Vertex Selection
##
process.goodPVs = cms.EDFilter("VertexSelector",
    src = cms.InputTag('offlinePrimaryVertices'),
    cut = cms.string('ndof>4 &'
                     'abs(z)<24 &'
                     '!isFake &'
                     'position.Rho<2'
    ),
)
process.oneGoodPVSelection = cms.EDFilter("VertexCountFilter",
    src = cms.InputTag('goodPVs'),
    minNumber = cms.uint32(1),
    maxNumber = cms.uint32(99999),
    
)
process.seqVertexSelection = cms.Sequence(process.goodPVs*process.oneGoodPVSelection)



##
## Path
##
process.path = cms.Path(
    process.mySeqALCARECOTkAlMuonIsolated*
    process.seqVertexSelection
)



##
## Define event selection from path
##
EventSelection = cms.PSet(
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('path')
    )
)



##
## configure output module
##
process.out = cms.OutputModule("PoolOutputModule",
    ## Parameters directly for PoolOutputModule
    #fileName = cms.untracked.string(os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test.root'),
    fileName = cms.untracked.string('alcarecoMuonIsolated.root'),
    # Maximum size per file before a new one is created
    #maxSize = cms.untracked.int32(500000),
    dropMetaData = cms.untracked.string("DROPPED"),
    #dataset = cms.untracked.PSet(
    #    filterName = cms.untracked.string('TkAlMuonIsolated'),
    #    dataTier = cms.untracked.string('ALCARECO'),
    #),
    
    ## Parameters for inherited OutputModule
    SelectEvents = EventSelection.SelectEvents,
    outputCommands = cms.untracked.vstring(
        'drop *',
	'keep *_ALCARECOTkAlMuonIsolated_*_*', 
        'keep L1AcceptBunchCrossings_*_*_*',
        'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*',
        'keep *_TriggerResults_*_*',
    ),
)



##
## Outpath
##
process.outpath = cms.EndPath(process.out)




