import os

import FWCore.ParameterSet.Config as cms

process = cms.Process("DiMuonSelectionCutflow")

## add message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.suppressWarning = cms.untracked.vstring("decaySubset") 



## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)



## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
    #SkipEvent = cms.untracked.vstring('ProductNotFound'),
    #Rethrow = cms.untracked.vstring("ProductNotFound"), # make this exception fatal (now default?)
)



## sources
process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.zmumu_spring10_cff")



## needed for access to trigger menu
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
# data
#process.GlobalTag.globaltag = cms.string('GR_R_36X_V12::All')
# mc
process.GlobalTag.globaltag = cms.string('START36_V10::All')



## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/mc/zmumu.root'),
    closeFileFast = cms.untracked.bool(True)
)

#******************************************************************************************
#   Filter & Producer Modules
#******************************************************************************************

## filter trigger
process.load("ZmumuAnalysis.Configuration.filters.TriggerFilter_cff")
process.triggerFilter1 = process.AllLowestUnprescaledTriggerFilter.clone()



## filter for muon quality, kinematics and HLT object matching
process.load("ZmumuAnalysis.Configuration.sequences.muonSelection_cff")



## add dimuon collections and filter for dimuon properties (including muon isolation)
process.load("ZmumuAnalysis.Configuration.sequences.diMuonSelection_cff")
#process.looseTightHltGlobalDimuons.decay = 'tightHltMuons@+ tightMuons@-'



#******************************************************************************************
#   Analyzer Modules
#******************************************************************************************

## trigger analyzer
process.load("ZmumuAnalysis.Analyzer.TriggerAnalyzer_cfi")
process.TriggerAnalyzer1 =  process.TriggerAnalyzer.clone()



## event analyzer
process.load("ZmumuAnalysis.Analyzer.EventAnalyzer_cfi")
process.EventAnalyzer1 = process.EventAnalyzer.clone(
    muonSource = 'looseMuons',
)
process.EventAnalyzer2 = process.EventAnalyzer1.clone(
    analyzeDiMuons = True,
)
process.EventAnalyzer3 = process.EventAnalyzer2.clone(
    diMuonSource = "finalDimuons",
)



## muon analizer
process.load("ZmumuAnalysis.Analyzer.MuonAnalyzer_cfi")
process.MuonAnalyzer1 = process.MuonAnalyzer.clone(
)
process.MuonAnalyzer2 = process.MuonAnalyzer1.clone(
    muonSource = 'looseMuons',
)



## di-muon analyzer
process.load("ZmumuAnalysis.Analyzer.DiMuonAnalyzer_cfi")
process.DiMuonAnalyzer1 = process.DiMuonAnalyzer.clone(
)
process.DiMuonAnalyzer2 = process.DiMuonAnalyzer1.clone(
    diMuonSource = "finalDimuons",
)





#******************************************************************************************
#   Analysis Path
#******************************************************************************************



process.p = cms.Path(
    process.TriggerAnalyzer1
    *process.triggerFilter1
    
    *process.MuonAnalyzer1
    *process.buildMuonCollections
    *process.EventAnalyzer1
    *process.muonSelection
    *process.MuonAnalyzer2
    
    *process.buildDimuonCollections
    *process.EventAnalyzer2
    *process.DiMuonAnalyzer1
    *process.dimuonSelection
    *process.EventAnalyzer3
    *process.DiMuonAnalyzer2
)
