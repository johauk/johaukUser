import os

import FWCore.ParameterSet.Config as cms

process = cms.Process("GenParticleOccurenceCutflow")



## add message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000



## sources
# To use for Zmumu (MadGraph)
process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_DYJetsToLL_M50_madgraph_F10_cff")
# To use for Zmumu (Powheg)
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYToMuMu_M_20_CT10_TuneZ2_7TeV_powheg_pythia_Fall10_START38_V12_PAT_v2_cff")
#process.load("ZmumuAnalysis.Configuration.samples.testSample_cff")



## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)



## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
)



## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/genParticleSelection.root'),
    closeFileFast = cms.untracked.bool(True)
)



#******************************************************************************************
#   Filter & Producer Modules
#******************************************************************************************

## filter for occurence of b-quarks
process.load("ZmumuAnalysis.Configuration.filters.GeneratorBclFilter_cff")



## filter for Zmumu plus mass range
process.load("ZmumuAnalysis.Configuration.filters.GeneratorZmumuFilter_cff")



#******************************************************************************************
#   Analyzer Modules
#******************************************************************************************

## Event Counter
process.load("ZmumuAnalysis.Analyzer.EventCounter_cfi")
process.EventCounter0 = process.EventCounter.clone()



## generator level b-quark occurence analyzer
process.load("ZmumuAnalysis.Analyzer.GenParticleAnalyzer_cfi")
process.GenParticleAnalyzerB2 = process.GenParticleAnalyzer.clone(src = 'selectedBs',)
process.GenParticleAnalyzerB3 = process.GenParticleAnalyzer.clone(src = 'goodBs',)
process.GenParticleAnalyzerB4a = process.GenParticleAnalyzer.clone(src = 'visibleGeometricBs',)
process.GenParticleAnalyzerB4 = process.GenParticleAnalyzer.clone(src = 'visibleKinematicBs',)
process.GenParticleAnalyzerB6 = process.GenParticleAnalyzer.clone(src = 'visibleKinematicBs',)



## generator level muon and di-muon analyzer
process.load("ZmumuAnalysis.Analyzer.GeneratorZmumuAnalyzer_cfi")
process.GeneratorZmumuAnalyzer1a =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzer1 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerB2 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerB3 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerB4 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerB5 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerB6 =  process.GeneratorZmumuAnalyzer.clone()

process.GeneratorZmumuAnalyzerUdsc2 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerUdsc3 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerUdsc4 =  process.GeneratorZmumuAnalyzer.clone()
process.GeneratorZmumuAnalyzerUdsc6 =  process.GeneratorZmumuAnalyzer.clone()



#******************************************************************************************
#   Sequences
#******************************************************************************************



process.step0 = cms.Sequence(
    process.EventCounter0
)
process.step1a = cms.Sequence(
    process.GeneratorZmumuAnalyzer1a
)
process.step1 = cms.Sequence(
    process.GeneratorZmumuAnalyzer1
)
process.step2 = cms.Sequence(
    process.GeneratorZmumuAnalyzerB2+
    process.GenParticleAnalyzerB2
)
process.step3a = cms.Sequence(
)
process.step3 = cms.Sequence(
    process.GeneratorZmumuAnalyzerB3+
    process.GenParticleAnalyzerB3
)
process.step4a = cms.Sequence(
    process.GenParticleAnalyzerB4a
)
process.step4 = cms.Sequence(
    process.GeneratorZmumuAnalyzerB4+
    process.GenParticleAnalyzerB4
)
process.step5 = cms.Sequence(
    process.GeneratorZmumuAnalyzerB5
)
process.step6 = cms.Sequence(
    process.GeneratorZmumuAnalyzerB6+
    process.GenParticleAnalyzerB6
)



process.udscStep2 = cms.Sequence(
    process.GeneratorZmumuAnalyzerUdsc2
)
process.udscStep3a = cms.Sequence(
)
process.udscStep3 = cms.Sequence(
    process.GeneratorZmumuAnalyzerUdsc3
)
process.udscStep4a = cms.Sequence(
)
process.udscStep4 = cms.Sequence(
    process.GeneratorZmumuAnalyzerUdsc4
)
process.udscStep6 = cms.Sequence(
    process.GeneratorZmumuAnalyzerUdsc6
)




#******************************************************************************************
#   Analysis Paths
#******************************************************************************************



process.bSelection = cms.Path(
    process.step0*
    
    process.GeneratorZmumuDiMuFilter*
    process.step1a*
    process.GeneratorZmumuZMassFilter*
    process.step1*
    
    process.buildBCollections*
    process.oneSelectedBSelection*
    process.step2*
    
    process.oneCleanBSelection*
    process.step3a*
    process.oneGoodBSelection*
    process.step3*
    
    
    process.oneVisibleGeometricBSelection*
    process.step4a*
    process.oneVisibleKinematicBSelection*
    process.step4*
    
    process.twoSelectedBSelection*
    process.twoCleanBSelection*
    process.twoGoodBSelection*
    process.step5*
    
    process.twoVisibleGeometricBSelection*
    process.twoVisibleKinematicBSelection*
    process.step6
)



process.udscSelection = cms.Path(
    
    process.GeneratorZmumuFilter*
    process.GeneratorZmumuZMassFilter*
    
    process.buildBCollections*
    
    ~process.twoVisibleKinematicBSelection*
    process.udscStep6*
    ## Makes no sense to require more than one module here
    #~process.twoVisibleGeometricBSelection*
    #~process.twoGoodBSelection*
    # These are valid already when one exists!!! ->Do never use
    #~process.twoCleanBSelection*
    #~process.twoSelectedBSelection*
    
    ~process.oneVisibleKinematicBSelection*
    process.udscStep4*
    
    ~process.oneVisibleGeometricBSelection*
    process.udscStep4a*
    
    ~process.oneGoodBSelection*
    process.udscStep3*
    
    ~process.oneCleanBSelection*
    process.udscStep3a*
    
    ~process.oneSelectedBSelection*
    process.udscStep2
)







