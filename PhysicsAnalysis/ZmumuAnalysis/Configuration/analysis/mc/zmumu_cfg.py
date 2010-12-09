import os

import FWCore.ParameterSet.Config as cms

process = cms.Process("FullCutflow")

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
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.Run2010A_Sep17ReReco_v2_Oct22_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.Run2010B_PromptReco_v2_Oct29_145000_147120_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.Run2010B_PromptReco_v2_Oct29_147120_148864_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.inclusiveMu15_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.singleTopS_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.singleTopTW_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.singleTopT_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.ttbar_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.wmunu_spring10_cff")
process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.zmumu_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.ztautau_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.ww_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.wz_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.zz_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.testSample_cff")



## needed for access to trigger menu
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
# data
#process.GlobalTag.globaltag = cms.string('GR_R_38X_V13::All')
# mc
process.GlobalTag.globaltag = cms.string('START38_V12::All')



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
#process.triggerFilter1 = process.TriggerFilterMu9.clone()
process.triggerFilter1 = process.TriggerFilterMu9_11_15.clone()



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



## muon analizer
process.load("ZmumuAnalysis.Analyzer.MuonAnalyzer_cfi")
process.MuonAnalyzer1 = process.MuonAnalyzer.clone(
    muonSource = 'looseMuons',
)
process.MuonAnalyzer2 = process.MuonAnalyzer1.clone(
)
process.MuonAnalyzer3 = process.MuonAnalyzer1.clone(
)
process.MuonAnalyzer4 = process.MuonAnalyzer1.clone(
)
process.MuonAnalyzer5 = process.MuonAnalyzer1.clone(
)
process.MuonAnalyzer6 = process.MuonAnalyzer1.clone(
)
process.MuonAnalyzer9 = process.MuonAnalyzer1.clone(
)

process.MuonSCAnalyzer6 = process.MuonAnalyzer6.clone(
)
process.MuonSCAnalyzer9 = process.MuonAnalyzer9.clone(
)



## di-muon analyzer
process.load("ZmumuAnalysis.Analyzer.DiMuonAnalyzer_cfi")
process.DiMuonAnalyzer3 = process.DiMuonAnalyzer.clone(
    diMuonSource = "goodDimuons",
)
process.DiMuonAnalyzer4 = process.DiMuonAnalyzer.clone(
    diMuonSource = "isolatedDimuons",
)
#process.DiMuonAnalyzer5 = process.DiMuonAnalyzer.clone(
#    diMuonSource = "atLeast1HltDimuons",
#)
process.DiMuonAnalyzer6 = process.DiMuonAnalyzer.clone(
    diMuonSource = "finalDimuons",
)
process.DiMuonAnalyzer9 = process.DiMuonAnalyzer.clone(
    diMuonSource = "finalDimuons",
)

process.DiMuonSCAnalyzer3 = process.DiMuonAnalyzer3.clone(
    diMuonSource = "goodDimuonsSC",
)
process.DiMuonSCAnalyzer4 = process.DiMuonAnalyzer4.clone(
    diMuonSource = "isolatedDimuonsSC",
)
#process.DiMuonSCAnalyzer5 = process.DiMuonAnalyzer5.clone(
#    diMuonSource = "atLeast1HltDimuonsSC",
#)
process.DiMuonSCAnalyzer6 = process.DiMuonAnalyzer6.clone(
    diMuonSource = "finalDimuonsSC",
)
process.DiMuonSCAnalyzer9 = process.DiMuonAnalyzer9.clone(
    diMuonSource = "finalDimuonsSC",
)



## jet analyzer
process.load("ZmumuAnalysis.Analyzer.JetAnalyzer_cfi")
process.JetAnalyzer7 = process.JetAnalyzer.clone(
    jetSource = 'finalJets',
)
process.JetAnalyzer8 = process.JetAnalyzer.clone(
    jetSource = 'bTcheJets',
)
process.JetAnalyzer9 = process.JetAnalyzer.clone(
    jetSource = 'bTcheJets',
)

process.JetSCAnalyzer7 = process.JetAnalyzer.clone()
process.JetSCAnalyzer8 = process.JetAnalyzer.clone()
process.JetSCAnalyzer9 = process.JetAnalyzer.clone()





#******************************************************************************************
#   Analysis Path
#******************************************************************************************



process.oppositeChargeAnalysis = cms.Path(
    process.TriggerAnalyzer1
    *process.triggerFilter1
    
    *process.buildMuonCollections
    *process.MuonAnalyzer1
    *process.muonSelection
    *process.MuonAnalyzer2
    
    *process.buildDimuonCollections
    *process.DiMuonAnalyzer3
    *process.DiMuonAnalyzer4
#    *process.DiMuonAnalyzer5
    *process.dimuonSelection
    *process.MuonAnalyzer6
    *process.DiMuonAnalyzer6
    
    *process.buildJetCollections
    *process.JetAnalyzer7
    *process.JetAnalyzer8
    *process.jetSelection
    *process.MuonAnalyzer9
    *process.DiMuonAnalyzer9
    *process.JetAnalyzer9
)



process.sameChargeAnalysis = cms.Path(
    process.triggerFilter1
    
    *process.buildMuonCollections
    *process.muonSelection
    
    *process.buildDimuonSCCollections
    *process.DiMuonSCAnalyzer3
    *process.DiMuonSCAnalyzer4
#    *process.DiMuonSCAnalyzer5
    *process.dimuonSCSelection
    *process.MuonSCAnalyzer6
    *process.DiMuonSCAnalyzer6
    
    *process.buildJetCollections
    *process.JetSCAnalyzer7
    *process.JetSCAnalyzer8
    *process.jetSelection
    *process.MuonSCAnalyzer9
    *process.DiMuonSCAnalyzer9
    *process.JetSCAnalyzer9
)



