import os

import FWCore.ParameterSet.Config as cms



process = cms.Process("ParticleGun")



##
## Message Logger
##
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories.append('SectorBuilder')
process.MessageLogger.categories.append('ResidualErrorBinning')
process.MessageLogger.categories.append('HitSelector')
process.MessageLogger.categories.append('CalculateAPE')
process.MessageLogger.categories.append('ApeEstimator')
#process.MessageLogger.categories.append('TrackRefitter')
process.MessageLogger.categories.append('AlignmentTrackSelector')
process.MessageLogger.cerr.INFO.limit = 0
process.MessageLogger.cerr.default.limit = 0
process.MessageLogger.cerr.SectorBuilder = cms.untracked.PSet(limit = cms.untracked.int32(-1))
process.MessageLogger.cerr.HitSelector = cms.untracked.PSet(limit = cms.untracked.int32(-1))
process.MessageLogger.cerr.CalculateAPE = cms.untracked.PSet(limit = cms.untracked.int32(-1))
process.MessageLogger.cerr.ApeEstimator = cms.untracked.PSet(limit = cms.untracked.int32(-1))
process.MessageLogger.cerr.AlignmentTrackSelector = cms.untracked.PSet(limit = cms.untracked.int32(-1))

#process.MessageLogger.cout = cms.untracked.PSet(INFO = cms.untracked.PSet(
#    reportEvery = cms.untracked.int32(100),  # every 100th only
#    limit = cms.untracked.int32(10),         # or limit to 10 printouts...
#))
process.MessageLogger.cerr.FwkReport.reportEvery = 1000 ## really show only every 1000th



##
## Handle huge number of Files
##
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
)



##
## Input Files (Collisions '10, 7 TeV)
##
## --- Particle Gun ---
#process.load("ApeEstimator.ApeEstimator.samples.ParticleGunPion_mc_cff")
#process.load("ApeEstimator.ApeEstimator.samples.ParticleGunAntiPion_mc_cff")
#process.load("ApeEstimator.ApeEstimator.samples.ParticleGunBothPion_mc_cff")
#process.load("ApeEstimator.ApeEstimator.samples.ParticleGunMuon_mc_cff")
#process.load("ApeEstimator.ApeEstimator.samples.ParticleGunAntiMuon_mc_cff")
#process.load("ApeEstimator.ApeEstimator.samples.ParticleGunBothMuon_mc_cff")
## --- Monte Carlo ---
process.load("ApeEstimator.ApeEstimator.samples.Mc_TkAlMuonIsolated_Fall10_DYToMuMu_ApeSkim_cff")
#process.load("ApeEstimator.ApeEstimator.samples.Mc_TkAlMuonIsolated_Fall10_WToMuNu_ApeSkim_cff")
#process.load("ApeEstimator.ApeEstimator.samples.Mc_TkAlMuonIsolated_Fall10_WToMuNu_cff")
#process.load("ApeEstimator.ApeEstimator.samples.Mc_TkAlMuonIsolated_Fall10_QcdMuPt10_ApeSkim_cff")
#process.load("ApeEstimator.ApeEstimator.samples.Mc_TkAlMuonIsolated_Fall10_QcdMuPt10_cff")
## --- Run XXX-YYY, End of Year Reprocessing ---
#process.load("ApeEstimator.ApeEstimator.samples.Data_TkAlMinBias_Run2010A_Dec22ReReco_cff")
#process.load("ApeEstimator.ApeEstimator.samples.Data_TkAlMinBias_Run2010B_Dec22ReReco_cff")
#process.load("ApeEstimator.ApeEstimator.samples.Data_TkAlMuonIsolated_Run2010A_Dec22ReReco_cff")
#process.load("ApeEstimator.ApeEstimator.samples.Data_TkAlMuonIsolated_Run2010B_Dec22ReReco_cff")



##
## Number of Events (should be after input file)
##
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1001) )



##
## Check run and event numbers for Dublicates --- only for real data
##
#process.source.duplicateCheckMode = cms.untracked.string("noDuplicateCheck")
#process.source.duplicateCheckMode = cms.untracked.string("checkEachFile")
process.source.duplicateCheckMode = cms.untracked.string("checkEachRealDataFile")
#process.source.duplicateCheckMode = cms.untracked.string("checkAllFilesOpened")   # default value



##
## Whole Refitter Sequence
##
process.load("ApeEstimator.ApeEstimator.TrackRefitter_38T_cff")
## --- Monte Carlo for Particle Gun ---
#process.GlobalTag.globaltag = 'DESIGN311_V2::All'
process.GlobalTag.globaltag = 'MC_311_V2::All'
#process.GlobalTag.globaltag = 'START311_V2::All'
## --- Run XXX-YYY, End of Jear Reprocessing ---
#process.GlobalTag.globaltag = 'FT_R_311_V4A::All'

## --- Further information (Monte Carlo and Data) ---
process.TTRHBuilderGeometricAndTemplate.StripCPE = 'StripCPEfromTrackAngle'
#process.TTRHBuilderGeometricAndTemplate.PixelCPE = 'PixelCPEGeneric'
#process.HighPuritySelector.src = 'generalTracks'
#process.HighPuritySelector.src = 'ALCARECOTkAlMuonIsolated'
process.HighPuritySelector.src = 'MuSkim'
#process.HighPuritySelector.src = 'ALCARECOTkAlMinBias'
#process.HighPuritySelector.src = 'MinBiasSkim'



##
## Alignment and APE
##
import CalibTracker.Configuration.Common.PoolDBESSource_cfi
## Choose Alignment (w/o touching APE)
process.myTrackerAlignment = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(
    connect = 'frontier://FrontierProd/CMS_COND_31X_FROM21X', # or your sqlite file
    toGet = [
      cms.PSet(
        record = cms.string('TrackerAlignmentRcd'),
        tag = cms.string('TrackerIdealGeometry210_mc') # 'TrackerAlignment_2009_v2_offline'
      )
    ],
)
process.es_prefer_trackerAlignment = cms.ESPrefer("PoolDBESSource","myTrackerAlignment")
#process.myTrackerAlignment = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(
#    connect = 'sqlite_file:/afs/cern.ch/user/h/hauk/scratch0/apeStudies/misalignments/AlignmentsTob20.db',
#    toGet = [
#      cms.PSet(
#        record = cms.string('TrackerAlignmentRcd'),
#        tag = cms.string('TrackerScenario')
#      )
#    ],
#)
#process.es_prefer_trackerAlignment = cms.ESPrefer("PoolDBESSource","myTrackerAlignment")

## APE (set to zero)
process.myTrackerAlignmentErr = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(
    connect = 'frontier://FrontierProd/CMS_COND_31X_FROM21X',
    toGet = [
      cms.PSet(
        record = cms.string('TrackerAlignmentErrorRcd'),
        tag = cms.string('TrackerIdealGeometryErrors210_mc')
      )
    ],
)
process.es_prefer_trackerAlignmentErr = cms.ESPrefer("PoolDBESSource","myTrackerAlignmentErr")
### APE (as estimated with ApeEstimator)
#process.myTrackerAlignmentErr = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(
#    connect = 'sqlite_file:/afs/cern.ch/user/h/hauk/scratch0/apeStudies/apeObjects/apeIter0.db',
#    toGet = [
#      cms.PSet(
#        record = cms.string('TrackerAlignmentErrorRcd'),
#        tag = cms.string('AlignmentErrors')
#      )
#    ],
#)
#process.es_prefer_trackerAlignmentErr = cms.ESPrefer("PoolDBESSource","myTrackerAlignmentErr")



##
## Trigger Selection
##
process.load("ApeEstimator.ApeEstimator.TriggerSelection_cff")



##
## Beamspot (Use correct Beamspot for simulated Vertex smearing of ParticleGun)
##
#process.load("ApeEstimator.ApeEstimator.BeamspotForParticleGun_cff")



##
## ApeEstimator
##
from ApeEstimator.ApeEstimator.ApeEstimator_cff import *
process.ApeEstimator1 = ApeEstimator.clone(
    tjTkAssociationMapTag = "TrackRefitterHighPurityForApeEstimator",
    maxTracksPerEvent = 0,
    applyTrackCuts = False,
    Sectors = SubdetSectors,
    #Sectors = TIBTOBLayerAndOrientationSeparation,
    analyzerMode = False,
)
process.ApeEstimator1.HitSelector.width = []
process.ApeEstimator1.HitSelector.maxIndex = []
process.ApeEstimator1.HitSelector.widthProj = []
process.ApeEstimator1.HitSelector.widthDiff = []
process.ApeEstimator1.HitSelector.edgeStrips = []
process.ApeEstimator1.HitSelector.sOverN = []
process.ApeEstimator1.HitSelector.probX = []
process.ApeEstimator1.HitSelector.phiSensX = []
process.ApeEstimator1.HitSelector.phiSensY = []

process.ApeEstimator2 = process.ApeEstimator1.clone(
    analyzerMode = True,
    calculateApe = False,
)

process.ApeEstimator3 = process.ApeEstimator2.clone(
    zoomHists = False,
)



##
## Output File Configuration
##
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test_ideal.root'),
    closeFileFast = cms.untracked.bool(True)
)



##
## Path
##
process.p = cms.Path(
    #process.TriggerSelectionSequence*
    process.RefitterHighPuritySequence
    *(process.ApeEstimator1
     +process.ApeEstimator2
     +process.ApeEstimator3
    )
)



