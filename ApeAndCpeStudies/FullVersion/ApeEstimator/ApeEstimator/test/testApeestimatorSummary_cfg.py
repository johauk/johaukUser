import os

import FWCore.ParameterSet.Config as cms


process = cms.Process("Demo")



##
## Message Logger
##
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories.append('CalculateAPE')
#process.MessageLogger.categories.append('ApeEstimatorSummary')
process.MessageLogger.cerr.INFO.limit = 0
process.MessageLogger.cerr.default.limit = 0
process.MessageLogger.cerr.CalculateAPE = cms.untracked.PSet(limit = cms.untracked.int32(-1))
#process.MessageLogger.cerr.ApeEstimatorSummary = cms.untracked.PSet(limit = cms.untracked.int32(-1))

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
from ApeEstimator.ApeEstimator.ApeEstimatorSummary_cff import *
#SAMPLE="particleGun"
SAMPLE="ideal"
#SAMPLE="data"
process.ApeEstimatorSummary1 = ApeEstimatorSummaryBaseline.clone(
    InputFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test_' + SAMPLE + '.root',
    ResultsFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test_' + SAMPLE + '_resultsFile1.root',
    BaselineFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test_' + SAMPLE + '_baselineApe.root',
)
process.ApeEstimatorSummary2 = ApeEstimatorSummaryIter.clone(
    apeWeight = "entries",
    correctionScaling = 0.6,
    smoothIteration = False,
    InputFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test_' + SAMPLE + '.root',
    ResultsFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test_' + SAMPLE + '_resultsFile2.root',
    BaselineFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test_' + SAMPLE + '_baselineApe.root',
    IterationFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test_' + SAMPLE + '_iterationApe2.root',
    ApeOutputFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test_' + SAMPLE + '_apeOutput2.txt',
)
process.ApeEstimatorSummary3 = ApeEstimatorSummaryIter.clone(
    apeWeight = "entries",
    correctionScaling = 0.6,
    smoothIteration = True,
    smoothFraction = 0.5,
    InputFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test_' + SAMPLE + '.root',
    ResultsFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test_' + SAMPLE + '_resultsFile3.root',
    BaselineFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test_' + SAMPLE + '_baselineApe.root',
    IterationFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test_' + SAMPLE + '_iterationApe3.root',
    ApeOutputFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test_' + SAMPLE + '_apeOutput3.txt',
)



process.p = cms.Path(
    #process.ApeEstimatorSummary1*
    process.ApeEstimatorSummary2*
    process.ApeEstimatorSummary3
)



