import os

import FWCore.ParameterSet.Config as cms

process = cms.Process("FullCutflow")

## Message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000



## Sources
# Data
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.Run2010A_Nov04ReReco_cff")
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.Run2010B1_Nov04ReReco_cff")
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.Run2010B2_Nov04ReReco_cff")

# QCD
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.QCD_MuEnrichedPt15_pythia_F10_cff")
# SingleTop
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.TToBLNu_madgraph_F10_cff")
# TTbar
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.TTJets_D6T_madgraph_F10_cff")
# Wmunu
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.WToMuNu_pythia_F10_cff")
# Wtaunu
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.WToTauNu_pythia_F10_cff")
# Zmumu (Drell-Yan low masses) not needed here
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYToMuMu_M10To20_pythia_F10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYToMuMu_M20_pythia_F10_cff")
# To use for Zmumu
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYJetsToLL_M50_madgraph_F10_cff")
# Ztautau (Drell-Yan low masses) not needed here
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYToTauTau_M10To20_pythia_F10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYToTauTau_M20_pythia_F10_cff")
# To use for Ztautau
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.DYJetsToLL_M50_D6T_madgraph_F10_cff")
# WW
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.WWTo2L2Nu_pythia_F10_cff")
# WZ
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.WZTo3LNu_pythia_F10_cff")
# ZZ
#process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.ZZToAnything_pythia_F10_cff")
process.load("ZmumuAnalysis.Configuration.samples.testSample_cff")



## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1001)
)



## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
)



## needed for access to trigger menu
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
# data
process.GlobalTag.globaltag = cms.string('FT_R_311_V4A::All')
# mc
#process.GlobalTag.globaltag = cms.string('START38_V13::All')



## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/fullSelection.root'),
    closeFileFast = cms.untracked.bool(True)
)

#******************************************************************************************
#   Filter & Producer Modules
#******************************************************************************************

## Filter for correct decay process
process.load("ZmumuAnalysis.Configuration.filters.GeneratorZmumuFilter_cff")



## filter trigger
process.load("ZmumuAnalysis.Configuration.filters.TriggerFilter_cff")



## filter for good primary vertices
process.load("ZmumuAnalysis.Configuration.sequences.vertexSelection_cff")



## filter for muon quality, kinematics and HLT object matching
process.load("ZmumuAnalysis.Configuration.sequences.muonSelection_cff")



## add dimuon collections and filter for dimuon properties (including muon isolation)
process.load("ZmumuAnalysis.Configuration.sequences.diMuonSelection_cff")



## clean and filter for jets
process.load("ZmumuAnalysis.Configuration.sequences.jetSelection_cff")



## filter for missing Et
process.load("ZmumuAnalysis.Configuration.sequences.metSelection_cff")




#******************************************************************************************
#   Analyzer Modules
#******************************************************************************************

## Event Counter
process.load("ZmumuAnalysis.Analyzer.EventCounter_cfi")
process.EventCounter0 = process.EventCounter.clone()



## trigger analyzer
process.load("ZmumuAnalysis.Analyzer.TriggerAnalyzer_cfi")
process.TriggerAnalyzer1 =  process.TriggerAnalyzer.clone(
    #triggerResults = cms.InputTag('TriggerResults','','HLT'),
    #triggerResults = cms.InputTag('TriggerResults','','REDIGI38X'),
)



## muon analizer
process.load("ZmumuAnalysis.Analyzer.MuonAnalyzer_cfi")
process.MuonAnalyzer1 = process.MuonAnalyzer.clone(
    muonSource = 'tightMuons',
)
process.MuonAnalyzer2 = process.MuonAnalyzer1.clone(
)
process.MuonAnalyzer6 = process.MuonAnalyzer1.clone(
)
process.MuonAnalyzer9 = process.MuonAnalyzer1.clone(
)
process.MuonAnalyzer10 = process.MuonAnalyzer1.clone(
)

process.MuonAnalyzerSC6 = process.MuonAnalyzer6.clone(
)
process.MuonAnalyzerSC9 = process.MuonAnalyzer9.clone(
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
process.DiMuonAnalyzer10 = process.DiMuonAnalyzer.clone(
    diMuonSource = "finalDimuons",
)

process.DiMuonAnalyzerSC3 = process.DiMuonAnalyzer3.clone(
    diMuonSource = "goodDimuonsSC",
)
process.DiMuonAnalyzerSC4 = process.DiMuonAnalyzer4.clone(
    diMuonSource = "isolatedDimuonsSC",
)
#process.DiMuonAnalyzerSC5 = process.DiMuonAnalyzer5.clone(
#    diMuonSource = "atLeast1HltDimuonsSC",
#)
process.DiMuonAnalyzerSC6 = process.DiMuonAnalyzer6.clone(
    diMuonSource = "finalDimuonsSC",
)
process.DiMuonAnalyzerSC9 = process.DiMuonAnalyzer9.clone(
    diMuonSource = "finalDimuonsSC",
)



## jet analyzer
process.load("ZmumuAnalysis.Analyzer.JetAnalyzer_cfi")
process.JetAnalyzer7 = process.JetAnalyzer.clone(
    jetSource = 'goodJets',
)
process.JetAnalyzer8 = process.JetAnalyzer.clone(
    jetSource = 'finalJets',
)
process.JetAnalyzer9 = process.JetAnalyzer.clone(
    jetSource = 'bSsvHeMJets',
)
process.JetAnalyzer10 = process.JetAnalyzer.clone(
    jetSource = 'bSsvHeMJets',
)

process.JetAnalyzerSC7 = process.JetAnalyzer.clone()
process.JetAnalyzerSC8 = process.JetAnalyzer.clone()
process.JetAnalyzerSC9 = process.JetAnalyzer.clone()


## missing et analyzer
process.load("ZmumuAnalysis.Analyzer.MetAnalyzer_cfi")
process.MetAnalyzer9 = process.MetAnalyzer.clone(
    metSource = 'patMETsPF',
)


process.MetAnalyzerSC9 = process.MetAnalyzer9.clone()




#******************************************************************************************
#   Analysis Path
#******************************************************************************************


# Additional statements for use with trigger REDIGI

TRIG_RESULT = "HLT"
#TRIG_RESULT = "REDIGI38X"

process.TriggerAnalyzer1.triggerResults = cms.InputTag('TriggerResults','',TRIG_RESULT)
process.TriggerFilter.TriggerResultsTag = cms.InputTag('TriggerResults','',TRIG_RESULT)
process.patTrigger.processName = TRIG_RESULT
process.patTrigger.triggerResults = cms.InputTag("TriggerResults::" + TRIG_RESULT)
process.patTrigger.triggerEvent = cms.InputTag("hltTriggerSummaryAOD::" + TRIG_RESULT)



#******************************************************************************************
#   Analysis Path
#******************************************************************************************



process.oppositeChargeAnalysis = cms.Path(
    process.EventCounter0 
    
#    *process.GeneratorZmumuFilter
#    *process.GeneratorZtautauFilter
    
    *process.buildVertexCollections
    *process.vertexSelection
    
    *process.TriggerAnalyzer1
    *process.TriggerFilter
    
    *process.buildMuonCollections
    *process.MuonAnalyzer1
    *process.muonSelection
    *process.MuonAnalyzer2
    
    *process.buildDimuonCollections
    *process.DiMuonAnalyzer3
    *process.DiMuonAnalyzer4
    #*process.DiMuonAnalyzer5
    *process.dimuonSelection
    *process.MuonAnalyzer6
    *process.DiMuonAnalyzer6
    
    *process.buildJetCollections
    *process.JetAnalyzer7
    *process.JetAnalyzer8
    *process.oneJetSelection
    *process.MuonAnalyzer9
    *process.DiMuonAnalyzer9
    *process.JetAnalyzer9
    
    *process.buildMetCollections
    *process.MetAnalyzer9
    *process.metSelection
    *process.MuonAnalyzer10
    *process.DiMuonAnalyzer10
    *process.JetAnalyzer10
    #*process.MetAnalyzer10
    
    
    *process.twoJetSelection
)



#process.sameChargeAnalysis = cms.Path(
#    process.TriggerFilter
#    
#    *process.buildMuonCollections
#    *process.muonSelection
#    
#    *process.buildDimuonSCCollections
#    *process.DiMuonAnalyzerSC3
#    *process.DiMuonAnalyzerSC4
##    *process.DiMuonAnalyzerSC5
#    *process.dimuonSCSelection
#    *process.MuonAnalyzerSC6
#    *process.DiMuonAnalyzerSC6
#    
#    *process.buildJetCollections
#    *process.JetAnalyzerSC7
#    *process.JetAnalyzerSC8
#    *process.jetSelection
#    *process.MuonAnalyzerSC9
#    *process.DiMuonAnalyzerSC9
#    *process.JetAnalyzerSC9
#    
#    *process.buildMetCollections
#    *process.MetAnalyzerSC9
#    *process.metSelection
#    
#)



