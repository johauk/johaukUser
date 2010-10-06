import os

import FWCore.ParameterSet.Config as cms

process = cms.Process("GeneratorZmumuCutflow")



## add message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000



## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)



## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
)



## sources
process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.zmumu_spring10_cff")



## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/mc/generatorZmumu.root'),
    closeFileFast = cms.untracked.bool(True)
)



#******************************************************************************************
#   Filter & Producer Modules
#******************************************************************************************

## filter for Zmumu plus mass range
process.load("ZmumuAnalysis.Configuration.filters.GeneratorZmumuFilter_cff")
process.GeneratorZmumuDiMuMassFilter1 = process.GeneratorZmumuDiMuMassFilter.clone()
process.GeneratorZmumuEtaFilter1 = process.GeneratorZmumuEtaFilter.clone()
process.GeneratorZmumuPtFilter1 = process.GeneratorZmumuPtFilter.clone()



#******************************************************************************************
#   Analyzer Modules
#******************************************************************************************

## generator level muon and di-muon analyzer
process.load("ZmumuAnalysis.Analyzer.GeneratorZmumuAnalyzer_cfi")
process.GeneratorZmumuAnalyzer1 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzer2 =  process.GeneratorZmumuAnalyzer1.clone()
process.GeneratorZmumuAnalyzer3 =  process.GeneratorZmumuAnalyzer2.clone()
process.GeneratorZmumuAnalyzer4 =  process.GeneratorZmumuAnalyzer3.clone()





#******************************************************************************************
#   Analysis Path
#******************************************************************************************



process.p = cms.Path(
    process.GeneratorZmumuAnalyzer1
    *process.GeneratorZmumuDiMuMassFilter1
    *process.GeneratorZmumuAnalyzer2
    *process.GeneratorZmumuEtaFilter1
    *process.GeneratorZmumuAnalyzer3
    *process.GeneratorZmumuPtFilter1
    *process.GeneratorZmumuAnalyzer4
)
