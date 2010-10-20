import os

import FWCore.ParameterSet.Config as cms

process = cms.Process("FullCutflow")

## add message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000



## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10001)
)



## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
)



## sources
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.Jun14ReReco_MuonPreselection_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.May27ReReco_MuonPreselection_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.inclusiveMu15_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.singleTopS_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.singleTopTW_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.singleTopT_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.ttbar_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.wmunu_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.zmumu_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.ztautau_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.ww_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.wz_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.zz_spring10_cff")
process.load("ZmumuAnalysis.Configuration.samples.testSample_cff")



## needed for access to trigger menu
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
# data
process.GlobalTag.globaltag = cms.string('GR_R_36X_V12::All')
# mc
#process.GlobalTag.globaltag = cms.string('START36_V10::All')



## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/fullSelection.root'),
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



## clean and filter for jets
process.load("ZmumuAnalysis.Configuration.sequences.jetSelection_cff")




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
process.EventAnalyzer4 = process.EventAnalyzer3.clone(
    jetSource = 'finalJets',
)
process.EventAnalyzer5 = process.EventAnalyzer4.clone(
    jetSource = 'bTcheJets',
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
    
    *process.buildJetCollections
    *process.EventAnalyzer4
    *process.EventAnalyzer5
    *process.jetSelection
)
