import os

import FWCore.ParameterSet.Config as cms

process = cms.Process("GeneratorZmumuCutflow")



## add message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000



## sources
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYToMuMu_M10To20_pythia_F10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYToMuMu_M20_pythia_F10_cff")
# To use for Zmumu (MadGraph)
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYJetsToLL_M50_madgraph_F10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYToTauTau_M10To20_pythia_F10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYToTauTau_M20_pythia_F10_cff")
# To use for Zmumu (Powheg)
process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYToMuMu_M_20_CT10_TuneZ2_7TeV_powheg_pythia_Fall10_START38_V12_PAT_v2_cff")
# To use for Ztautau
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYJetsToLL_M50_D6T_madgraph_F10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.WZTo3LNu_pythia_F10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.ZZToAnything_pythia_F10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.testSample_cff")



## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1001)
)



## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
)



## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/generatorZmumuSelection.root'),
    closeFileFast = cms.untracked.bool(True)
)



#******************************************************************************************
#   Filter & Producer Modules
#******************************************************************************************

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

## Event Counter
process.load("ZmumuAnalysis.Analyzer.EventCounter_cfi")
process.EventCounter0 = process.EventCounter.clone()



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



process.NoSelection = cms.Path(
    process.EventCounter0
    *process.GeneratorZmumuAnalyzer0
)



process.UdsFlavourSelection = cms.Path(
    process.GeneratorZmumuUdsFilter1
    *process.GeneratorZmumuAnalyzerUds1
    *process.GeneratorZmumuDiMuMassFilter1
    *process.GeneratorZmumuAnalyzerUds2
    *process.GeneratorZmumuEtaFilter1
    *process.GeneratorZmumuAnalyzerUds3
    *process.GeneratorZmumuPtFilter1
    *process.GeneratorZmumuAnalyzerUds4
)



process.CFlavourSelection = cms.Path(
    process.GeneratorZmumuCFilter1
    *process.GeneratorZmumuAnalyzerC1
    *process.GeneratorZmumuDiMuMassFilter1
    *process.GeneratorZmumuAnalyzerC2
    *process.GeneratorZmumuEtaFilter1
    *process.GeneratorZmumuAnalyzerC3
    *process.GeneratorZmumuPtFilter1
    *process.GeneratorZmumuAnalyzerC4
)



process.BFlavourSelection = cms.Path(
    process.GeneratorZmumuBFilter1
    *process.GeneratorZmumuAnalyzerB1
    *process.GeneratorZmumuDiMuMassFilter1
    *process.GeneratorZmumuAnalyzerB2
    *process.GeneratorZmumuEtaFilter1
    *process.GeneratorZmumuAnalyzerB3
    *process.GeneratorZmumuPtFilter1
    *process.GeneratorZmumuAnalyzerB4
)


