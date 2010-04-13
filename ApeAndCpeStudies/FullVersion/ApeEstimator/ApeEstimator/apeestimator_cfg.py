import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories.append('SectorBuilder')
process.MessageLogger.categories.append('ResidualErrorBinning')
process.MessageLogger.categories.append('HitSelector')
process.MessageLogger.categories.append('CalculateAPE')
process.MessageLogger.categories.append('')
#process.MessageLogger.categories.append('TrackRefitter')
process.MessageLogger.categories.append('AlignmentTrackSelector')
process.MessageLogger.cerr.INFO = cms.untracked.VPSet(
    default = cms.untracked.PSet( limit = cms.untracked.int32(0)  ),
    SectorBuilder = cms.untracked.PSet( limit = cms.untracked.int32(-1) ),
    HitSelector = cms.untracked.PSet( limit = cms.untracked.int32(-1) ),
    CalculateAPE = cms.untracked.PSet( limit = cms.untracked.int32(-1) ),
    AlignmentTrackSelector = cms.untracked.PSet( limit = cms.untracked.int32(-1) )
)
#process.MessageLogger.cout = cms.untracked.PSet(INFO = cms.untracked.PSet(
    #reportEvery = cms.untracked.int32(100)  # every 100th only
    #limit = cms.untracked.int32(10)        # or limit to 10 printouts...
#))
process.MessageLogger.cerr.FwkReport.reportEvery = 1000 ## really show only every 1000th



##
## Handle huge number of Files
##
process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring("ProductNotFound") # make this exception fatal
#    , fileMode  =  cms.untracked.string('FULLMERGE') # any file order (default): caches all lumi/run products (memory!)
#    , fileMode  =  cms.untracked.string('MERGE') # needs files sorted in run and within run in lumi sections (hard to achieve)
#    , fileMode  =  cms.untracked.string('FULLLUMIMERGE') # needs files sorted in run, caches lumi
    , fileMode  =  cms.untracked.string('NOMERGE') # 
)




process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10001) )



##
## Input Files (CRAFT '09)
##
## --- Monte Carlo ---
#process.load("ApeEstimator.ApeEstimator.CRAFT_mc_31X_cff")
## --- First Reprocessing ---
process.load("ApeEstimator.ApeEstimator.run109011_109624_FirstRepro_cff")



##
## Whole Refitter Sequence
##
process.load("ApeEstimator.ApeEstimator.TrackRefitter_38T_cff")
## --- Monte Carlo ---
#process.GlobalTag.globaltag = 'DESIGN_3X_V8B::All'    # peak mode
#process.GlobalTag.globaltag = 'MC_3XY_V9B::All'    # same, but bad channels are masked
#process.GlobalTag.globaltag = 'DESIGN_3X_V26::All'
## --- First Reprocessing ---
#process.GlobalTag.globaltag = 'CRAFT09_R_V4::All'
process.GlobalTag.globaltag = 'CRAFT09_R_V9::All'
## --- Further information (Monte Carlo and Data) ---
#process.StripCPEgeometricESProducer.APVpeakmode = False
process.TTRHBuilderGeometricAndTemplate.StripCPE = 'StripCPEfromTrackAngle'
#process.TTRHBuilderGeometricAndTemplate.PixelCPE = 'PixelCPEGeneric'
#process.TrackRefitterForApeEstimator.src = 'ALCARECOTkAlCosmicsCTF0T'



## Choose Alignment (w/o touching APE)
#import CalibTracker.Configuration.Common.PoolDBESSource_cfi
#process.myTrackerAlignment = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(
#    connect = 'frontier://FrontierProd/CMS_COND_31X_FROM21X', # or your sqlite file
#    toGet = cms.VPSet(
#      cms.PSet(
#        record = cms.string('TrackerAlignmentRcd'),
#        tag = cms.string('TrackerIdealGeometry210_mc') # 'TrackerAlignment_2009_v2_offline'
#      )
#    )
#)
#process.es_prefer_trackerAlignment = cms.ESPrefer("PoolDBESSource","myTrackerAlignment")



## ApeEstimator
from ApeEstimator.ApeEstimator.apeestimator_cff import *
process.ApeEstimatorCosmics1 = ApeEstimatorCosmics
process.ApeEstimatorCosmics1.maxTracksPerEvent = 0
process.ApeEstimatorCosmics1.applyTrackCuts = False
process.ApeEstimatorCosmics1.zoomHists = False
process.ApeEstimatorCosmics1.Sectors = TIBTOB
process.ApeEstimatorCosmics1.HitSelector.width = []
process.ApeEstimatorCosmics1.HitSelector.edgeStrips = []
process.ApeEstimatorCosmics1.HitSelector.sOverN = []
process.ApeEstimatorCosmics1.HitSelector.phiSensX = []
process.ApeEstimatorCosmics1.HitSelector.phiSensY = []
process.ApeEstimatorCosmics1.apeScaling = 0.5
process.ApeEstimatorCosmics1.ApeOutputFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/apeOutput.txt'



## Output File Configuration
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test.root'),
    closeFileFast = cms.untracked.bool(True)
)



process.p = cms.Path(process.RefitterSequence
		     *process.ApeEstimatorCosmics1
)



