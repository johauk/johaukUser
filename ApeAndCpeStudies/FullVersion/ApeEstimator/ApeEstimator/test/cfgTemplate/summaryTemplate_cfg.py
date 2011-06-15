import os

import FWCore.ParameterSet.Config as cms



process = cms.Process("Demo")



##
## Message Logger
##
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories.append('CalculateAPE')
process.MessageLogger.cerr.INFO.limit = 0
process.MessageLogger.cerr.default.limit = -1
process.MessageLogger.cerr.CalculateAPE = cms.untracked.PSet(limit = cms.untracked.int32(-1))

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
process.ApeEstimatorSummary1 = ApeEstimatorSummaryIter.clone(
    # keep the same for all jobs
    BaselineFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/Design/baseline/allData_baselineApe.root',
    # keep the first one on misaligned geometry for iterations on same geometry (or better use copy of it)
    IterationFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/workingArea/iter_THE_ITERATION_/allData_iterationApe.root',
    # change iteration number for these
    InputFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/workingArea/iter_THE_ITERATION_/allData.root',
    ResultsFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/workingArea/iter_THE_ITERATION_/allData_resultsFile.root',
    ApeOutputFile = os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/workingArea/iter_THE_ITERATION_/allData_apeOutput.txt',
)




process.p = cms.Path(
    process.ApeEstimatorSummary1
)



