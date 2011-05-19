import os

import FWCore.ParameterSet.Config as cms

process = cms.Process("GenParticleOccurenceCutflow")



## add message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1



## sources
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYToMuMu_M10To20_pythia_F10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYToMuMu_M20_pythia_F10_cff")
# To use for Zmumu (MadGraph)
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYJetsToLL_M50_madgraph_F10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYToTauTau_M10To20_pythia_F10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYToTauTau_M20_pythia_F10_cff")
# To use for Zmumu (Powheg)
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYToMuMu_M_20_CT10_TuneZ2_7TeV_powheg_pythia_Fall10_START38_V12_PAT_v2_cff")
# To use for Ztautau
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYJetsToLL_M50_D6T_madgraph_F10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.WZTo3LNu_pythia_F10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.ZZToAnything_pythia_F10_cff")
process.load("ZmumuAnalysis.Configuration.samples.testSample_cff")



## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5)
)



## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
)



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

## Event Counter
process.load("ZmumuAnalysis.Analyzer.EventCounter_cfi")
process.EventCounter0 = process.EventCounter.clone()



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



process.goodB = cms.EDFilter("GenParticleSelector",
    filter = cms.bool(True),
    src = cms.InputTag("genParticles"),
    cut = cms.string('abs(pdgId)=5 & (status=2 || status=3) & pt>10.'),
)


process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.printTree = cms.EDAnalyzer("ParticleTreeDrawer",
    src = cms.InputTag("genParticles"),
    #printP4 = cms.untracked.bool(True),
    #printPtEtaPhi = cms.untracked.bool(True),
    #printVertex = cms.untracked.bool(True),
    printStatus = cms.untracked.bool(True),
    #printIndex = cms.untracked.bool(True),
    #status = cms.untracked.vint32(1,2,3),
    status = cms.untracked.vint32(3),
)

process.printDecay = cms.EDAnalyzer("ParticleDecayDrawer",
    src = cms.InputTag("genParticles"),
    status = cms.untracked.vint32(3),
    #maxEventsToPrint = cms.untracked.int32(3),
    #printP4 = cms.untracked.bool(True),
    #printPtEtaPhi = cms.untracked.bool(True),
    #printVertex = cms.untracked.bool(True),
)




#******************************************************************************************
#   Analysis Paths
#******************************************************************************************



process.UdsFlavourSelection = cms.Path(
    process.EventCounter0*
    process.printTree*
    #process.printDecay*
    process.goodB*
    process.GeneratorZmumuUdsFilter1*
    #process.goodB*
    process.GenParticleOccurenceFilter1*
    process.GenParticleOccurenceAnalyzerUds1*
    process.GeneratorZmumuAnalyzerUds1
)



process.CFlavourSelection = cms.Path(
    process.goodB*
    process.GeneratorZmumuCFilter1*
    #process.goodB*
    process.GenParticleOccurenceFilter1*
    process.GenParticleOccurenceAnalyzerC1*
    process.GeneratorZmumuAnalyzerC1
)



process.BFlavourSelection = cms.Path(
    process.goodB*
    process.GeneratorZmumuBFilter1*
    #process.goodB*
    process.GenParticleOccurenceFilter1*
    process.GenParticleOccurenceAnalyzerB1*
    process.GeneratorZmumuAnalyzerB1
)


