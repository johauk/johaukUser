import os

import FWCore.ParameterSet.Config as cms

process = cms.Process("GeneratorTopZmumuCutflow")



## add message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000



## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
)



## sources
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYToMuMu_M10To20_pythia_F10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYToMuMu_M20_pythia_F10_cff")
# To use for Zmumu (MadGraph)
process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYJetsToLL_M50_madgraph_F10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYToTauTau_M10To20_pythia_F10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYToTauTau_M20_pythia_F10_cff")
# To use for Zmumu (Powheg)
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYToMuMu_M_20_CT10_TuneZ2_7TeV_powheg_pythia_Fall10_START38_V12_PAT_v2_cff")
# To use for Ztautau
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYJetsToLL_M50_D6T_madgraph_F10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.WZTo3LNu_pythia_F10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.ZZToAnything_pythia_F10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.testSample_cff")



## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)



## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/simulation/generatorTopZmumu.root'),
    closeFileFast = cms.untracked.bool(True)
)



#******************************************************************************************
#   Filter & Producer Modules
#******************************************************************************************

## filter for Zmumu plus mass range and muon eta, pt range

process.load("ZmumuAnalysis.Configuration.filters.GeneratorTopZmumuFilter_cff")



#******************************************************************************************
#   Analyzer Modules
#******************************************************************************************

## generator level muon and di-muon analyzer
process.load("ZmumuAnalysis.Analyzer.GeneratorZmumuAnalyzer_cfi")
process.GeneratorZmumuAnalyzer0 = process.GeneratorZmumuAnalyzer.clone(zDecayMode = [],)
process.GeneratorZmumuAnalyzerFinal1 = process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerFinal2 = process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerFinal3 = process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerFinal4 = process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerVisible2 = process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerVisible3 = process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerVisible4 = process.GeneratorZmumuAnalyzer.clone()



#******************************************************************************************
#   Analysis Paths
#******************************************************************************************



#Not needed, since no interest in non-muonic decays of Z
#process.NoSelection = cms.Path(
#    process.GeneratorZmumuAnalyzer0
#)



process.FinalXsectionSelection = cms.Path(
    process.GeneratorZmumuDiMuFilter
    *process.GeneratorZmumuAnalyzerFinal1
    *process.GeneratorZmumuDiMuMassFilterFinal
    *process.GeneratorZmumuAnalyzerFinal2
    *process.GeneratorZmumuEtaFilterVisible
    *process.GeneratorZmumuAnalyzerFinal3
    *process.GeneratorZmumuPtFilterVisible
    *process.GeneratorZmumuAnalyzerFinal4
)



process.VisibleXsectionSelection = cms.Path(
    process.GeneratorZmumuDiMuFilter
    *process.GeneratorZmumuDiMuMassFilterVisible
    *process.GeneratorZmumuAnalyzerVisible2
    *process.GeneratorZmumuEtaFilterVisible
    *process.GeneratorZmumuAnalyzerVisible3
    *process.GeneratorZmumuPtFilterVisible
    *process.GeneratorZmumuAnalyzerVisible4
)





