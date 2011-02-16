import os

import FWCore.ParameterSet.Config as cms


process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories.append('SectorBuilder')
process.MessageLogger.categories.append('ResidualErrorBinning')
process.MessageLogger.categories.append('HitSelector')
process.MessageLogger.categories.append('CalculateAPE')
process.MessageLogger.categories.append('ApeEstimatorSummary')
#process.MessageLogger.categories.append('TrackRefitter')
process.MessageLogger.categories.append('AlignmentTrackSelector')
process.MessageLogger.cerr.INFO.limit = 0
process.MessageLogger.cerr.default.limit = 0
process.MessageLogger.cerr.SectorBuilder = cms.untracked.PSet(limit = cms.untracked.int32(-1))
process.MessageLogger.cerr.HitSelector = cms.untracked.PSet(limit = cms.untracked.int32(-1))
process.MessageLogger.cerr.CalculateAPE = cms.untracked.PSet(limit = cms.untracked.int32(-1))
process.MessageLogger.cerr.ApeEstimatorSummary = cms.untracked.PSet(limit = cms.untracked.int32(-1))
process.MessageLogger.cerr.AlignmentTrackSelector = cms.untracked.PSet(limit = cms.untracked.int32(-1))

#process.MessageLogger.cout = cms.untracked.PSet(INFO = cms.untracked.PSet(
#    reportEvery = cms.untracked.int32(100),  # every 100th only
#    limit = cms.untracked.int32(10),         # or limit to 10 printouts...
#))
process.MessageLogger.cerr.FwkReport.reportEvery = 1000 ## really show only every 1000th



process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
)



process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )



##
## Input Files
##
process.source = cms.Source("EmptySource")



##
## ApeEstimatorSummary
##
from ApeEstimator.ApeEstimator.ApeEstimatorSummary_cfi import *
process.ApeEstimatorSummary1 = ApeEstimatorSummary.clone(
    #setBaseline = True,
    sigmaFactorFit = 2.5,
    correctionScaling = 1.,
    InputFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test_particleGun.root',
    ResultsFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test_particleGun_resultsFile.root',
    BaselineFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test_particleGun_baselineApe.root',
    IterationFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test_particleGun_iterationApe.root',
    ApeOutputFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test_particleGun_apeOutput.txt',
)




process.p = cms.Path(
    process.ApeEstimatorSummary1
)



