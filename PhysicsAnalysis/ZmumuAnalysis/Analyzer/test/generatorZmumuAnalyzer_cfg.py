import os

import FWCore.ParameterSet.Config as cms


process = cms.Process("ZmumuGeneratorAnalyzer")



## Message logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000 ## really show only every 1000th



process.options = cms.untracked.PSet(
    #wantSummary = cms.untracked.bool(True),
    Rethrow = cms.untracked.vstring("ProductNotFound"), # make this exception fatal
    # fileMode  =  cms.untracked.string('FULLMERGE'), # any file order (default): caches all lumi/run products (memory!)
    # fileMode  =  cms.untracked.string('MERGE'), # needs files sorted in run and within run in lumi sections (hard to achieve)
    # fileMode  =  cms.untracked.string('FULLLUMIMERGE'), # needs files sorted in run, caches lumi
     fileMode  =  cms.untracked.string('NOMERGE'), #  no ordering needed, but calls endRun/beginRun etc. at file boundaries
)



process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1001) )



## Input Source
process.load("ZmumuAnalysis.Configuration.samples.testSample_cff")



## Analyzer under test
process.load("ZmumuAnalysis.Analyzer.GeneratorZmumuAnalyzer_cfi")
process.GeneratorZmumuAnalyzer1 = process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzer2 = process.GeneratorZmumuAnalyzer1.clone(
    massZMin = 70.,
    massZMax = 110.,
)
process.GeneratorZmumuAnalyzer3 = process.GeneratorZmumuAnalyzer2.clone(
    massZMin = 80.,
    massZMax = 100.,
)
process.GeneratorZmumuAnalyzer4 = process.GeneratorZmumuAnalyzer3.clone(
    absEtaMuMax = 2.5,
)



## Output File Configuration
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Analyzer/hists/test_generatorZmumuAnalyzer.root'),
    #fileName = cms.string('genTest.root'),
    closeFileFast = cms.untracked.bool(True)
)



## Path
process.p = cms.Path(
    process.GeneratorZmumuAnalyzer1
    +process.GeneratorZmumuAnalyzer2
    +process.GeneratorZmumuAnalyzer3
    +process.GeneratorZmumuAnalyzer4
)