import os

import FWCore.ParameterSet.Config as cms


process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories.append('SectorBuilder')
process.MessageLogger.categories.append('ResidualErrorBinning')
process.MessageLogger.categories.append('HitSelector')
process.MessageLogger.categories.append('CalculateAPE')
process.MessageLogger.categories.append('ApeEstimator')
process.MessageLogger.categories.append('')
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
    #wantSummary = cms.untracked.bool(True),
    Rethrow = cms.untracked.vstring("ProductNotFound") # make this exception fatal
    #, fileMode  =  cms.untracked.string('FULLMERGE') # any file order (default): caches all lumi/run products (memory!)
    #, fileMode  =  cms.untracked.string('MERGE') # needs files sorted in run and within run in lumi sections (hard to achieve)
    #, fileMode  =  cms.untracked.string('FULLLUMIMERGE') # needs files sorted in run, caches lumi
    , fileMode  =  cms.untracked.string('NOMERGE') #  no ordering needed, but calls endRun/beginRun etc. at file boundaries
)



process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1001) )

#process.source.inputCommands = cms.untracked.vstring('keep *', 'drop *_MEtoEDMConverter_*_*') # hack to get rid of the memory consumption problem in 2_2_X and beond




##
## Input Files (CRAFT '09)
##
## --- Monte Carlo ---
#process.load("ApeEstimator.ApeEstimator.samples.CRAFT_mc_31X_cff")
## --- First Reprocessing ---
#process.load("ApeEstimator.ApeEstimator.samples.run109011_109624_FirstRepro_cff")
##
## Input Files (Collisions '10, MinBias 7 TeV)
##
## --- Monte Carlo ---
#process.load("ApeEstimator.ApeEstimator.samples.MinBias_mc_356_cff")
process.load("ApeEstimator.ApeEstimator.samples.MinBias_mc_356_ApeSkim_cff")
## --- Run 132440-132478, First Reprocessing --- (beamspot corrected)
#process.load("ApeEstimator.ApeEstimator.samples.MinBias_run132440_132478_R_356_cff")
## --- Run 133029-133158, Processing ---
#process.load("ApeEstimator.ApeEstimator.samples.MinBias_run133029_133158_P_356_cff")
#process.load("ApeEstimator.ApeEstimator.samples.MinBias_run133029_133158_P_356_ApeSkim_cff")
## --- Run 132440-134987, First Reprocessing ---
#process.load("ApeEstimator.ApeEstimator.samples.MinBias_run132440_134987_RMay06_358p3_cff")
#process.load("ApeEstimator.ApeEstimator.samples.MinBias_run132440_134987_RMay06_358p3_ApeSkim_cff")



##
## Whole Refitter Sequence
##
process.load("ApeEstimator.ApeEstimator.TrackRefitter_38T_cff")
## --- Monte Carlo for CRAFT '09 ---
#process.GlobalTag.globaltag = 'DESIGN_3X_V8B::All'    # peak mode
#process.GlobalTag.globaltag = 'MC_3XY_V9B::All'    # same, but bad channels are masked
#process.GlobalTag.globaltag = 'DESIGN_3X_V26::All'
## --- CRAFT '09, First Reprocessing ---
#process.GlobalTag.globaltag = 'CRAFT09_R_V4::All'
#process.GlobalTag.globaltag = 'CRAFT09_R_V9::All'
## --- Monte Carlo for MinBias 7 TeV ---
process.GlobalTag.globaltag = 'START3X_V26::All'
## --- Run 132440-132478, First Reprocessing --- (beamspot corrected)
#process.GlobalTag.globaltag = 'GR_R_35X_V6::All'
## --- Run 133029-133158, Processing ---
#process.GlobalTag.globaltag = 'GR10_P_V4::All'
## --- Run 132440-134987, First Reprocessing ---
#process.GlobalTag.globaltag = 'GR_R_35X_V8B::All'
## --- Further information (Monte Carlo and Data) ---
#process.OutOfTime.TOBlateBP = 0.071  # do not use in MC
#process.OutOfTime.TIBlateBP=0.036
process.TTRHBuilderGeometricAndTemplate.StripCPE = 'StripCPEfromTrackAngle'
#process.TTRHBuilderGeometricAndTemplate.PixelCPE = 'PixelCPEGeneric'
#process.TrackRefitterForApeEstimator.src = 'ALCARECOTkAlCosmicsCTF0T'
process.TrackRefitterForApeEstimator.src = 'ALCARECOTkAlMinBias'
process.HighPuritySelector.src = 'MinBiasSkim'



## Choose Alignment (w/o touching APE)
import CalibTracker.Configuration.Common.PoolDBESSource_cfi
process.myTrackerAlignment = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(
    connect = 'frontier://FrontierProd/CMS_COND_31X_FROM21X', # or your sqlite file
    toGet = cms.VPSet(
      cms.PSet(
        record = cms.string('TrackerAlignmentRcd'),
        tag = cms.string('TrackerIdealGeometry210_mc') # 'TrackerAlignment_2009_v2_offline'
      )
    )
)
process.es_prefer_trackerAlignment = cms.ESPrefer("PoolDBESSource","myTrackerAlignment")



##
## Trigger Selection
##
process.load("ApeEstimator.ApeEstimator.TriggerSelection_cff")



##
## ApeEstimator
##
from ApeEstimator.ApeEstimator.ApeEstimator_cff import *
process.ApeEstimator1 = ApeEstimator.clone(
    tjTkAssociationMapTag = "TrackRefitterHighPurityForApeEstimator",
    maxTracksPerEvent = 0,
    applyTrackCuts = False,
    #Sectors = SubdetSectors,
    Sectors = TIBTOBLayerAndOrientationSeparation,
    analyzerMode = False,
)
process.ApeEstimator1.HitSelector.width = []
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



## Output File Configuration
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test_ideal.root'),
    closeFileFast = cms.untracked.bool(True)
)



process.p = cms.Path(
    #process.TriggerSelectionSequence*
    process.TriggerSelectionSequenceForMC*
    #process.RefitterSequence
    process.RefitterHighPuritySequence
    *(process.ApeEstimator1 + process.ApeEstimator2 + process.ApeEstimator3)
)



