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






process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1001) )



##
## Input Files (CRAFT '09)
##
## --- Monte Carlo ---
## --- First Reprocessing ---
process.load("ApeEstimator.ApeEstimator.run109011_109624_FirstRepro_cff")

##
## Whole Refitter Sequence
##
#process.load("ApeEstimator.ApeEstimator.TrackRefitterCTF_38T_MonteCarlo_cff")
process.load("ApeEstimator.ApeEstimator.TrackRefitterCTF_38T_ReProcessing_cff")



#from ApeEstimator.ApeEstimator.apeestimator_cfi import *
#from ApeEstimator.ApeEstimator.SectorBuilder_cff import *
#process.ApeEstimator1 = ApeEstimator.clone(
#  maxTracksPerEvent = cms.uint32(2),
#  #applyTrackCuts = False,
#  minGoodHitsPerTrack = cms.uint32(1),
#  residualErrorBinning = cms.vdouble(0.0005,0.0010,0.0015,0.0020,0.0025,0.0030,0.0035,0.0040,0.0050,0.0070,0.0100), # 5-100um
#  #zoomHists = False,
#  vErrHists = cms.vuint32(1,2,3,4,5),
#  #Sectors = SubdetSectors
#  #Sectors = TIBTOBQuarters
#  Sectors = TIBTOBQuarters2DSeparation
#)
#process.ApeEstimator1.HitSelector.errXHit = cms.vdouble(0.,0.0060)  # 60um, to exclude very large clusters
#process.ApeEstimator1.HitSelector.phiSens = cms.vdouble(-0.1,1.0472)  # [0,60] degree




## ApeEstimator
from ApeEstimator.ApeEstimator.apeestimator_cff import *
process.ApeEstimatorCosmics1 = ApeEstimatorCosmics




## Output File Configuration
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('/afs/cern.ch/user/h/hauk/cms/CMSSW_3_3_1/src/ApeEstimator/ApeEstimator/hists/test.root'),
    closeFileFast = cms.untracked.bool(True)
)



process.p = cms.Path(process.RefitterSequence
                     #*process.ApeEstimator1
		     *process.ApeEstimatorCosmics1
)



