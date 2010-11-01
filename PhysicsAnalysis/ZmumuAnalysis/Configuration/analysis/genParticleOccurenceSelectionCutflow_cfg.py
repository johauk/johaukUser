import os

import FWCore.ParameterSet.Config as cms

process = cms.Process("GenParticleOccurenceCutflow")



## add message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000



## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100000)
)



## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
)



## sources
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.inclusiveMu15_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.singleTopS_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.singleTopTW_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.singleTopT_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.ttbar_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.wmunu_spring10_cff")
process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.zmumu_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.ztautau_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.testSample_cff")



## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/genParticleOccurenceSelection.root'),
    closeFileFast = cms.untracked.bool(True)
)



#******************************************************************************************
#   Filter & Producer Modules
#******************************************************************************************

## filter for occurence of b-quarks
process.load("ZmumuAnalysis.Filter.GenParticleOccurenceFilter_cfi")
process.GenParticleOccurenceFilter1 = process.GenParticleOccurenceFilter.clone()


## filter for Zmumu plus mass range
process.load("ZmumuAnalysis.Configuration.filters.GeneratorZmumuFilter_cff")
process.GeneratorZmumuUdsFilter1 = process.GeneratorZmumuUdsFilter.clone()
process.GeneratorZmumuCFilter1 = process.GeneratorZmumuCFilter.clone()
process.GeneratorZmumuBFilter1 = process.GeneratorZmumuBFilter.clone()
process.GeneratorZmumuDiMuMassFilter1 = process.GeneratorZmumuDiMuMassFilter.clone()
process.GeneratorZmumuEtaFilter1 = process.GeneratorZmumuEtaFilter.clone()
process.GeneratorZmumuPtFilter1 = process.GeneratorZmumuPtFilter.clone()



#******************************************************************************************
#   Analyzer Modules
#******************************************************************************************

## generator level b-quark occurence analyzer
process.load("ZmumuAnalysis.Analyzer.GenParticleOccurenceAnalyzer_cfi")
process.GenParticleOccurenceAnalyzerUds1 = process.GenParticleOccurenceAnalyzer.clone()
process.GenParticleOccurenceAnalyzerC1 = process.GenParticleOccurenceAnalyzer.clone()
process.GenParticleOccurenceAnalyzerB1 = process.GenParticleOccurenceAnalyzer.clone()

## generator level muon and di-muon analyzer
process.load("ZmumuAnalysis.Analyzer.GeneratorZmumuAnalyzer_cfi")
process.GeneratorZmumuAnalyzer0 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerUds1 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerUds2 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerUds3 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerUds4 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerC1 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerC2 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerC3 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerC4 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerB1 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerB2 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerB3 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerB4 =  process.GeneratorZmumuAnalyzer.clone()



#******************************************************************************************
#   Analysis Paths
#******************************************************************************************



process.UdsFlavourSelection = cms.Path(
    process.GeneratorZmumuUdsFilter1
    *process.GenParticleOccurenceFilter1
    *process.GenParticleOccurenceAnalyzerUds1
    *process.GeneratorZmumuAnalyzerUds1
)



process.CFlavourSelection = cms.Path(
    process.GeneratorZmumuCFilter1
    *process.GenParticleOccurenceFilter1
    *process.GenParticleOccurenceAnalyzerC1
    *process.GeneratorZmumuAnalyzerC1
)



process.BFlavourSelection = cms.Path(
    process.GeneratorZmumuBFilter1
    *process.GenParticleOccurenceFilter1
    *process.GenParticleOccurenceAnalyzerB1
    *process.GeneratorZmumuAnalyzerB1
)


