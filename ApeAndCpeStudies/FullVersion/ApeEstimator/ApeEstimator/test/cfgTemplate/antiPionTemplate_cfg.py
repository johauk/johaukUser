import os

import FWCore.ParameterSet.Config as cms



process = cms.Process("Demo")



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
    #fileMode  =  cms.untracked.string('FULLMERGE'),  # any file order (default): caches all lumi/run products (memory!)
    #fileMode  =  cms.untracked.string('MERGE'),  # needs files sorted in run and within run in lumi sections (hard to achieve)
    #fileMode  =  cms.untracked.string('FULLLUMIMERGE'),  # needs files sorted in run, caches lumi
    #fileMode  =  cms.untracked.string('NOMERGE'),  # no ordering needed, but calls endRun/beginRun etc. at file boundaries
)



##
## Input Files
##
readFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",
    #inputCommands = cms.untracked.vstring('keep *', 'drop *_MEtoEDMConverter_*_*'),
    fileNames = readFiles
)
readFiles.extend( [
    'file:reco.root',
] );



##
## Number of Events (should be after input file)
##
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(_THE_MAXEVENT_) )



##
## Check run and event numbers for Dublicates
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
process.GlobalTag.globaltag = 'DESIGN_39_V7::All'
#process.GlobalTag.globaltag = 'MC_39Y_V7::All'
#process.GlobalTag.globaltag = 'START39_V8::All'
## --- Run XXX-YYY, End of Jear Reprocessing ---
#process.GlobalTag.globaltag = 'FT_R_39X_V4A::All'

## --- Further information (Monte Carlo and Data) ---
process.TTRHBuilderGeometricAndTemplate.StripCPE = 'StripCPEfromTrackAngle'
#process.TTRHBuilderGeometricAndTemplate.PixelCPE = 'PixelCPEGeneric'
#process.HighPuritySelector.src = 'MinBiasSkim'
process.HighPuritySelector.src = 'generalTracks'



##
## Alignment and APE
##
import CalibTracker.Configuration.Common.PoolDBESSource_cfi
## Choose Alignment (w/o touching APE)
process.myTrackerAlignment = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(
    connect = '_THE_ALIGNMENT_RCD_CONNECT_',
    #connect = 'frontier://FrontierProd/CMS_COND_31X_FROM21X',
    toGet = cms.VPSet(
      cms.PSet(
        record = cms.string('TrackerAlignmentRcd'),
	tag = cms.string('_THE_ALIGNMENT_RCD_')
        #tag = cms.string('TrackerIdealGeometry210_mc')
      )
    )
)
process.es_prefer_trackerAlignment = cms.ESPrefer("PoolDBESSource","myTrackerAlignment")

## APE
process.myTrackerAlignmentErr = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(
    connect = '_THE_ALIGNMENT_ERROR_RCD_CONNECT_',
    #connect = 'frontier://FrontierProd/CMS_COND_31X_FROM21X',
    toGet = cms.VPSet(
      cms.PSet(
        record = cms.string('TrackerAlignmentErrorRcd'),
	tag = cms.string('_THE_ALIGNMENT_ERROR_RCD_')
        #tag = cms.string('TrackerIdealGeometryErrors210_mc')
      )
    )
)
process.es_prefer_trackerAlignmentErr = cms.ESPrefer("PoolDBESSource","myTrackerAlignmentErr")



##
## Beamspot (Use correct Beamspot for simulated Vertex smearing of ParticleGun)
##
process.load("ApeEstimator.ApeEstimator.BeamspotForParticleGun_cff")



##
## ApeEstimator
##
from ApeEstimator.ApeEstimator.ApeEstimator_cff import *
process.ApeEstimator1 = ApeEstimator.clone(
    tjTkAssociationMapTag = "TrackRefitterHighPurityForApeEstimator",
    analyzerMode = False,
)

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
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/workingArea/antiPion_THE_NUMBER_.root'),
    closeFileFast = cms.untracked.bool(True)
)



##
## Path
##
process.p = cms.Path(
    #process.TriggerSelectionSequence*       # omit trigger selection for particle gun
    process.RefitterHighPuritySequence
    *process.ApeEstimator1
)



