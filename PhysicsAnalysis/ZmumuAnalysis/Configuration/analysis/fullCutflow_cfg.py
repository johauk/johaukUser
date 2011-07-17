import os

import FWCore.ParameterSet.Config as cms


##
## Process definition
##
process = cms.Process("FullCutflow")



##
## Message logger
##
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000



##
## Specify whether is MC or data, and which conrete type
##
# Data samples
counter = 0
isData1 = False
isData2 = False
isData3 = False  # Recently only two different input files, do not set this line to true
# MC samples
isQcd = False
isSingletopS = False
isSingletopT = False
isSingletopTw = False
isTtbar = False
isWmunu = False
isWtaunu = False
isZmumu = False
isZmumuB = False
isZmumuUdsc = False
isZtautau = False
isWw = False
isWz = False
isZz = False
isTest = True

## Just list here all data and MC samples
isData = False
isMC = False
# Data
if(isData1): counter += 1; isData = True
if(isData2): counter += 1; isData = True
if(isData3): counter += 1; isData = True
# MC
if(isQcd): counter += 1; isMC = True
if(isSingletopS): counter += 1; isMC = True
if(isSingletopT): counter += 1; isMC = True
if(isSingletopTw): counter += 1; isMC = True
if(isTtbar): counter += 1; isMC = True
if(isWmunu): counter += 1; isMC = True
if(isWtaunu): counter += 1; isMC = True
if(isZmumu): counter += 1; isMC = True
if(isZmumuB): counter += 1; isMC = True
if(isZmumuUdsc): counter += 1; isMC = True
if(isZtautau): counter += 1; isMC = True
if(isWw): counter += 1; isMC = True
if(isWz): counter += 1; isMC = True
if(isZz): counter += 1; isMC = True
if(isTest): counter += 1; isMC = True

#print counter
if(not counter == 1): print "Error, wrong configuration of samples"; raise KeyError("ERROR")
    


##
## Sources
##
# Data
if(isData1):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSummer11.Run2011A_May10ReReco_v1_423_July10_160404_163869_cff")
elif(isData2):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSummer11.Run2011A_PromtReco_v4_423_July10_163870_167784_cff")
elif(isData3):
    process.load("")
# MC
elif(isQcd):
    process.load("")
elif(isSingletopS):
    process.load("")
elif(isSingletopT):
    process.load("")
elif(isSingletopTw):
    process.load("")
elif(isTtbar):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSummer11.Summer11_TTJets_Z2_madgraph_423_July10_cff")
elif(isWmunu):
    process.load("")
elif(isWtaunu):
    process.load("")
elif(isZmumu):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSummer11.Summer11_DYJetsToLL_Z2_madgraph_423_July10_cff")
elif(isZmumuB):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSummer11.Summer11_DYJetsToLL_Z2_madgraph_423_July10_cff")
elif(isZmumuUdsc):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSummer11.Summer11_DYJetsToLL_Z2_madgraph_423_July10_cff")
elif(isZtautau):
    process.load("")
elif(isWw):
    process.load("")
elif(isWz):
    process.load("")
elif(isZz):
    process.load("")
elif(isTest):
    process.load("ZmumuAnalysis.Configuration.samples.testSample_cff")
else: print "Error, wrong configuration of samples"; raise KeyError("ERROR")



##
## Direct use of JSON file for event preselection
##
#import PhysicsTools.PythonAnalysis.LumiList as LumiList
#import FWCore.ParameterSet.Types as CfgTypes
#myLumis = LumiList.LumiList(filename = os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/crab/json/syncExercise/Cert_166512_syncExercise_1_JSON.txt').getCMSSWString().split(',')
#myLumis = LumiList.LumiList(filename = os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/crab/json/syncExercise/Cert_166841_syncExercise_2_JSON.txt').getCMSSWString().split(',')
#process.source.lumisToProcess = CfgTypes.untracked(CfgTypes.VLuminosityBlockRange())
#process.source.lumisToProcess.extend(myLumis) 



##
## define maximal number of events to loop over
##
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1001)
)
if(not isTest): process.maxEvents.input = -1



##
## configure process options
##
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
)



##
## needed for access to trigger menu
##
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
if(isData): process.GlobalTag.globaltag = 'GR_R_42_V14::All'
elif(isMC): process.GlobalTag.globaltag = 'START42_V12::All'
else: print "Error, wrong configuration of samples"; raise KeyError("ERROR")



##
## register TFileService
##
fileBase = os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/'
fileName = ''
# Data
if(isData1): fileName = 'data/run2011A_May7PromptReco_1.root'
elif(isData2): fileName = 'data/run2011A_May7PromptReco_2.root'
elif(isData3): fileName = 'data/run2011A_May7to13PromptReco.root'
# MC
elif(isQcd): fileName = 'mc/qcd.root'
elif(isSingletopS): fileName = 'mc/singletopS.root'
elif(isSingletopT): fileName = 'mc/singletopT.root'
elif(isSingletopTw): fileName = 'mc/singletopTw.root'
elif(isTtbar): fileName = 'mc/ttbar.root'
elif(isWmunu): fileName = 'mc/wmunu.root'
elif(isWtaunu): fileName = 'mc/wtaunu.root'
elif(isZmumu): fileName = 'mc/zmumu.root'
elif(isZmumuB): fileName = 'mc/zmumuB.root'
elif(isZmumuUdsc): fileName = 'mc/zmumuUdsc.root'
elif(isZtautau): fileName = 'mc/ztautau.root'
elif(isWw): fileName = 'mc/ww.root'
elif(isWz): fileName = 'mc/wz.root'
elif(isZz): fileName = 'mc/zz.root'
elif(isTest): fileName = 'fullSelection.root'
else: print "Error, wrong configuration of samples"; raise KeyError("ERROR")
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(fileBase + fileName),
    closeFileFast = cms.untracked.bool(True)
)




#******************************************************************************************
#   Filter & Producer Modules
#******************************************************************************************

## Filter for correct decay process
process.load("ZmumuAnalysis.Configuration.filters.GeneratorZmumuFilter_cff")
process.load("ZmumuAnalysis.Configuration.filters.GeneratorBclFilter_cff")



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
process.EventCounterStep0 = process.EventCounter.clone()
process.EventCounterStep1a = process.EventCounter.clone()
process.EventCounterStep1b = process.EventCounter.clone()
process.EventCounterStep1 = process.EventCounter.clone()
process.EventCounterStep2a = process.EventCounter.clone()
process.EventCounterStep2b = process.EventCounter.clone()
process.EventCounterStep2c = process.EventCounter.clone()
process.EventCounterStep2d = process.EventCounter.clone()
process.EventCounterStep2e = process.EventCounter.clone()
process.EventCounterStep2f = process.EventCounter.clone()
process.EventCounterStep2 = process.EventCounter.clone()
process.EventCounterStep3a = process.EventCounter.clone()
process.EventCounterStep3b = process.EventCounter.clone()
process.EventCounterStep3c = process.EventCounter.clone()
process.EventCounterStep3d = process.EventCounter.clone()
process.EventCounterStep3e = process.EventCounter.clone()
process.EventCounterStep3f = process.EventCounter.clone()
process.EventCounterStep3 = process.EventCounter.clone()
process.EventCounterStep4a = process.EventCounter.clone()
process.EventCounterStep4b = process.EventCounter.clone()
process.EventCounterStep4c = process.EventCounter.clone()
process.EventCounterStep4d = process.EventCounter.clone()
process.EventCounterStep4 = process.EventCounter.clone()
process.EventCounterStep5 = process.EventCounter.clone()
process.EventCounterStep6a = process.EventCounter.clone()
process.EventCounterStep6 = process.EventCounter.clone()
process.EventCounterStep7a = process.EventCounter.clone()
process.EventCounterStep7b = process.EventCounter.clone()
process.EventCounterStep7c = process.EventCounter.clone()
process.EventCounterStep7 = process.EventCounter.clone()
process.EventCounterStepZVetoLow3f = process.EventCounter.clone()
process.EventCounterStepZVetoLow3 = process.EventCounter.clone()
process.EventCounterStepZVetoLow4a = process.EventCounter.clone()
process.EventCounterStepZVetoLow4b = process.EventCounter.clone()
process.EventCounterStepZVetoLow4c = process.EventCounter.clone()
process.EventCounterStepZVetoLow4d = process.EventCounter.clone()
process.EventCounterStepZVetoLow4 = process.EventCounter.clone()
process.EventCounterStepZVetoLow5 = process.EventCounter.clone()
process.EventCounterStepZVetoLow6a = process.EventCounter.clone()
process.EventCounterStepZVetoLow6 = process.EventCounter.clone()
process.EventCounterStepZVetoLow7a = process.EventCounter.clone()
process.EventCounterStepZVetoLow7b = process.EventCounter.clone()
process.EventCounterStepZVetoLow7c = process.EventCounter.clone()
process.EventCounterStepZVetoLow7 = process.EventCounter.clone()
process.EventCounterStepZVetoHigh3f = process.EventCounter.clone()
process.EventCounterStepZVetoHigh3 = process.EventCounter.clone()
process.EventCounterStepZVetoHigh4a = process.EventCounter.clone()
process.EventCounterStepZVetoHigh4b = process.EventCounter.clone()
process.EventCounterStepZVetoHigh4c = process.EventCounter.clone()
process.EventCounterStepZVetoHigh4d = process.EventCounter.clone()
process.EventCounterStepZVetoHigh4 = process.EventCounter.clone()
process.EventCounterStepZVetoHigh5 = process.EventCounter.clone()
process.EventCounterStepZVetoHigh6a = process.EventCounter.clone()
process.EventCounterStepZVetoHigh6 = process.EventCounter.clone()
process.EventCounterStepZVetoHigh7a = process.EventCounter.clone()
process.EventCounterStepZVetoHigh7b = process.EventCounter.clone()
process.EventCounterStepZVetoHigh7c = process.EventCounter.clone()
process.EventCounterStepZVetoHigh7 = process.EventCounter.clone()

process.EventCounterStepNoMet7a = process.EventCounter.clone()
process.EventCounterStepNoMet7b = process.EventCounter.clone()
process.EventCounterStepNoMet7c = process.EventCounter.clone()
process.EventCounterStepNoMet7 = process.EventCounter.clone()
process.EventCounterStepZVetoLowNoMet7a = process.EventCounter.clone()
process.EventCounterStepZVetoLowNoMet7b = process.EventCounter.clone()
process.EventCounterStepZVetoLowNoMet7c = process.EventCounter.clone()
process.EventCounterStepZVetoLowNoMet7 = process.EventCounter.clone()
process.EventCounterStepZVetoHighNoMet7a = process.EventCounter.clone()
process.EventCounterStepZVetoHighNoMet7b = process.EventCounter.clone()
process.EventCounterStepZVetoHighNoMet7c = process.EventCounter.clone()
process.EventCounterStepZVetoHighNoMet7 = process.EventCounter.clone()



## trigger analyzer
process.load("ZmumuAnalysis.Analyzer.TriggerAnalyzer_cfi")
process.TriggerAnalyzerStep1a =  process.TriggerAnalyzer.clone(
    #triggerResults = cms.InputTag('TriggerResults','','HLT'),
    #triggerResults = cms.InputTag('TriggerResults','','REDIGI38X'),
)



## vertex analyzer
process.load("ZmumuAnalysis.Analyzer.VertexAnalyzer_cfi")
process.VertexAnalyzerStep1b = process.VertexAnalyzer.clone()#vertexSource = 'offlinePrimaryVertices',)
process.VertexAnalyzerStep1 = process.VertexAnalyzer.clone(vertexSource = 'goodPVs',)
process.VertexAnalyzerStep3f = process.VertexAnalyzer.clone(vertexSource = 'finalPVs',)
process.VertexAnalyzerStep3 = process.VertexAnalyzer.clone(vertexSource = 'bestPV',)

process.VertexAnalyzerStepZVetoLow3f = process.VertexAnalyzerStep3f.clone(vertexSource = 'finalPVsZVetoLow',)
process.VertexAnalyzerStepZVetoHigh3f = process.VertexAnalyzerStep3f.clone(vertexSource = 'finalPVsZVetoHigh',)



## muon analizer
process.load("ZmumuAnalysis.Analyzer.MuonAnalyzer_cfi")
process.MuonAnalyzerStep2b = process.MuonAnalyzer.clone(muonSource = 'tightMuons',)
process.MuonAnalyzerStep2 = process.MuonAnalyzer.clone(muonSource = 'tightMuons',)
process.MuonAnalyzerStep3 = process.MuonAnalyzer.clone(muonSource = 'tightMuons',)
process.MuonAnalyzerStep4 = process.MuonAnalyzer.clone(muonSource = 'tightMuons',)
process.MuonAnalyzerStep5 = process.MuonAnalyzer.clone(muonSource = 'tightMuons',)
process.MuonAnalyzerStep6 = process.MuonAnalyzer.clone(muonSource = 'tightMuons',)
process.MuonAnalyzerStep7a = process.MuonAnalyzer.clone(muonSource = 'tightMuons',)
process.MuonAnalyzerStep7b = process.MuonAnalyzer.clone(muonSource = 'tightMuons',)
process.MuonAnalyzerStep7c = process.MuonAnalyzer.clone(muonSource = 'tightMuons',)
process.MuonAnalyzerStep7 = process.MuonAnalyzer.clone(muonSource = 'tightMuons',)

process.MuonAnalyzerStepZVetoLow3 = process.MuonAnalyzerStep3.clone()
process.MuonAnalyzerStepZVetoLow4 = process.MuonAnalyzerStep4.clone()
process.MuonAnalyzerStepZVetoLow5 = process.MuonAnalyzerStep5.clone()
process.MuonAnalyzerStepZVetoLow6 = process.MuonAnalyzerStep6.clone()
process.MuonAnalyzerStepZVetoLow7a = process.MuonAnalyzerStep7a.clone()
process.MuonAnalyzerStepZVetoLow7b = process.MuonAnalyzerStep7b.clone()
process.MuonAnalyzerStepZVetoLow7c = process.MuonAnalyzerStep7c.clone()
process.MuonAnalyzerStepZVetoLow7 = process.MuonAnalyzerStep7.clone()
process.MuonAnalyzerStepZVetoHigh3 = process.MuonAnalyzerStep3.clone()
process.MuonAnalyzerStepZVetoHigh4 = process.MuonAnalyzerStep4.clone()
process.MuonAnalyzerStepZVetoHigh5 = process.MuonAnalyzerStep5.clone()
process.MuonAnalyzerStepZVetoHigh6 = process.MuonAnalyzerStep6.clone()
process.MuonAnalyzerStepZVetoHigh7a = process.MuonAnalyzerStep7a.clone()
process.MuonAnalyzerStepZVetoHigh7b = process.MuonAnalyzerStep7b.clone()
process.MuonAnalyzerStepZVetoHigh7c = process.MuonAnalyzerStep7c.clone()
process.MuonAnalyzerStepZVetoHigh7 = process.MuonAnalyzerStep7.clone()

process.MuonAnalyzerStepNoMet7a = process.MuonAnalyzerStep7a.clone()
process.MuonAnalyzerStepNoMet7b = process.MuonAnalyzerStep7b.clone()
process.MuonAnalyzerStepNoMet7c = process.MuonAnalyzerStep7c.clone()
process.MuonAnalyzerStepNoMet7 = process.MuonAnalyzerStep7.clone()
process.MuonAnalyzerStepZVetoLowNoMet7a = process.MuonAnalyzerStep7a.clone()
process.MuonAnalyzerStepZVetoLowNoMet7b = process.MuonAnalyzerStep7b.clone()
process.MuonAnalyzerStepZVetoLowNoMet7c = process.MuonAnalyzerStep7c.clone()
process.MuonAnalyzerStepZVetoLowNoMet7 = process.MuonAnalyzerStep7.clone()
process.MuonAnalyzerStepZVetoHighNoMet7a = process.MuonAnalyzerStep7a.clone()
process.MuonAnalyzerStepZVetoHighNoMet7b = process.MuonAnalyzerStep7b.clone()
process.MuonAnalyzerStepZVetoHighNoMet7c = process.MuonAnalyzerStep7c.clone()
process.MuonAnalyzerStepZVetoHighNoMet7 = process.MuonAnalyzerStep7.clone()



## di-muon analyzer
process.load("ZmumuAnalysis.Analyzer.DiMuonAnalyzer_cfi")
process.DiMuonAnalyzerStep3d = process.DiMuonAnalyzer.clone(diMuonSource = "goodDimuons",)
process.DiMuonAnalyzerStep3e = process.DiMuonAnalyzer.clone(diMuonSource = "isolatedDimuons",)
process.DiMuonAnalyzerStep3f = process.DiMuonAnalyzer.clone(diMuonSource = "finalDimuons",)
process.DiMuonAnalyzerStep3 = process.DiMuonAnalyzer.clone(diMuonSource = "bestDimuon",)
process.DiMuonAnalyzerStep4 = process.DiMuonAnalyzer.clone(diMuonSource = "finalDimuons",)
process.DiMuonAnalyzerStep5 = process.DiMuonAnalyzer.clone(diMuonSource = "finalDimuons",)
process.DiMuonAnalyzerStep6 = process.DiMuonAnalyzer.clone(diMuonSource = "finalDimuons",)
process.DiMuonAnalyzerStep7a = process.DiMuonAnalyzer.clone(diMuonSource = "finalDimuons",)
process.DiMuonAnalyzerStep7b = process.DiMuonAnalyzer.clone(diMuonSource = "finalDimuons",)
process.DiMuonAnalyzerStep7c = process.DiMuonAnalyzer.clone(diMuonSource = "finalDimuons",)
process.DiMuonAnalyzerStep7 = process.DiMuonAnalyzer.clone(diMuonSource = "finalDimuons",)

process.DiMuonAnalyzerStepZVetoLow3f = process.DiMuonAnalyzerStep3f.clone(diMuonSource = "finalDimuonsZVetoLow",)
process.DiMuonAnalyzerStepZVetoLow4 = process.DiMuonAnalyzerStep4.clone(diMuonSource = "finalDimuonsZVetoLow",)
process.DiMuonAnalyzerStepZVetoLow5 = process.DiMuonAnalyzerStep5.clone(diMuonSource = "finalDimuonsZVetoLow",)
process.DiMuonAnalyzerStepZVetoLow6 = process.DiMuonAnalyzerStep6.clone(diMuonSource = "finalDimuonsZVetoLow",)
process.DiMuonAnalyzerStepZVetoLow7a = process.DiMuonAnalyzerStep7a.clone(diMuonSource = "finalDimuonsZVetoLow",)
process.DiMuonAnalyzerStepZVetoLow7b = process.DiMuonAnalyzerStep7b.clone(diMuonSource = "finalDimuonsZVetoLow",)
process.DiMuonAnalyzerStepZVetoLow7c = process.DiMuonAnalyzerStep7c.clone(diMuonSource = "finalDimuonsZVetoLow",)
process.DiMuonAnalyzerStepZVetoLow7 = process.DiMuonAnalyzerStep7.clone(diMuonSource = "finalDimuonsZVetoLow",)
process.DiMuonAnalyzerStepZVetoHigh3f = process.DiMuonAnalyzerStep3f.clone(diMuonSource = "finalDimuonsZVetoHigh",)
process.DiMuonAnalyzerStepZVetoHigh4 = process.DiMuonAnalyzerStep4.clone(diMuonSource = "finalDimuonsZVetoHigh",)
process.DiMuonAnalyzerStepZVetoHigh5 = process.DiMuonAnalyzerStep5.clone(diMuonSource = "finalDimuonsZVetoHigh",)
process.DiMuonAnalyzerStepZVetoHigh6 = process.DiMuonAnalyzerStep6.clone(diMuonSource = "finalDimuonsZVetoHigh",)
process.DiMuonAnalyzerStepZVetoHigh7a = process.DiMuonAnalyzerStep7a.clone(diMuonSource = "finalDimuonsZVetoHigh",)
process.DiMuonAnalyzerStepZVetoHigh7b = process.DiMuonAnalyzerStep7b.clone(diMuonSource = "finalDimuonsZVetoHigh",)
process.DiMuonAnalyzerStepZVetoHigh7c = process.DiMuonAnalyzerStep7c.clone(diMuonSource = "finalDimuonsZVetoHigh",)
process.DiMuonAnalyzerStepZVetoHigh7 = process.DiMuonAnalyzerStep7.clone(diMuonSource = "finalDimuonsZVetoHigh",)

process.DiMuonAnalyzerStepNoMet7a = process.DiMuonAnalyzerStep7a.clone()
process.DiMuonAnalyzerStepNoMet7b = process.DiMuonAnalyzerStep7b.clone()
process.DiMuonAnalyzerStepNoMet7c = process.DiMuonAnalyzerStep7c.clone()
process.DiMuonAnalyzerStepNoMet7 = process.DiMuonAnalyzerStep7.clone()
process.DiMuonAnalyzerStepZVetoLowNoMet7a = process.DiMuonAnalyzerStepZVetoLow7a.clone()
process.DiMuonAnalyzerStepZVetoLowNoMet7b = process.DiMuonAnalyzerStepZVetoLow7b.clone()
process.DiMuonAnalyzerStepZVetoLowNoMet7c = process.DiMuonAnalyzerStepZVetoLow7c.clone()
process.DiMuonAnalyzerStepZVetoLowNoMet7 = process.DiMuonAnalyzerStepZVetoLow7.clone()
process.DiMuonAnalyzerStepZVetoHighNoMet7a = process.DiMuonAnalyzerStepZVetoHigh7a.clone()
process.DiMuonAnalyzerStepZVetoHighNoMet7b = process.DiMuonAnalyzerStepZVetoHigh7b.clone()
process.DiMuonAnalyzerStepZVetoHighNoMet7c = process.DiMuonAnalyzerStepZVetoHigh7c.clone()
process.DiMuonAnalyzerStepZVetoHighNoMet7 = process.DiMuonAnalyzerStepZVetoHigh7.clone()




## jet analyzer
process.load("ZmumuAnalysis.Analyzer.JetAnalyzer_cfi")
process.JetAnalyzerStep4a = process.JetAnalyzer.clone(jetSource = 'selectedPatJetsAK5PF',)
process.JetAnalyzerStep4b = process.JetAnalyzer.clone(jetSource = 'cleanPatJets',)
process.JetAnalyzerStep4c = process.JetAnalyzer.clone(jetSource = 'goodIdJets',)
process.JetAnalyzerStep4d = process.JetAnalyzer.clone(jetSource = 'goodJets',)
process.JetAnalyzerStep4 = process.JetAnalyzer.clone(jetSource = 'finalJets',)
process.JetAnalyzerStep5J = process.JetAnalyzer.clone(jetSource = 'finalJets',)
process.JetAnalyzerStep5Bhe = process.JetAnalyzer.clone(jetSource = 'bSsvHeMJets',)
process.JetAnalyzerStep5Bhp = process.JetAnalyzer.clone(jetSource = 'bSsvHpTJets',)
process.JetAnalyzerStep6J = process.JetAnalyzer.clone(jetSource = 'finalJets',)
process.JetAnalyzerStep6Bhe = process.JetAnalyzer.clone(jetSource = 'bSsvHeMJets',)
process.JetAnalyzerStep6Bhp = process.JetAnalyzer.clone(jetSource = 'bSsvHpTJets',)
process.JetAnalyzerStep7aJ = process.JetAnalyzer.clone(jetSource = 'finalJets',)
process.JetAnalyzerStep7aBhe = process.JetAnalyzer.clone(jetSource = 'bSsvHeMJets',)
process.JetAnalyzerStep7aBhp = process.JetAnalyzer.clone(jetSource = 'bSsvHpTJets',)
process.JetAnalyzerStep7bJ = process.JetAnalyzer.clone(jetSource = 'finalJets',)
process.JetAnalyzerStep7bBhe = process.JetAnalyzer.clone(jetSource = 'bSsvHeMJets',)
process.JetAnalyzerStep7bBhp = process.JetAnalyzer.clone(jetSource = 'bSsvHpTJets',)
process.JetAnalyzerStep7cJ = process.JetAnalyzer.clone(jetSource = 'finalJets',)
process.JetAnalyzerStep7cBhe = process.JetAnalyzer.clone(jetSource = 'bSsvHeMJets',)
process.JetAnalyzerStep7cBhp = process.JetAnalyzer.clone(jetSource = 'bSsvHpTJets',)
process.JetAnalyzerStep7J = process.JetAnalyzer.clone(jetSource = 'finalJets',)
process.JetAnalyzerStep7Bhe = process.JetAnalyzer.clone(jetSource = 'bSsvHeMJets',)
process.JetAnalyzerStep7Bhp = process.JetAnalyzer.clone(jetSource = 'bSsvHpTJets',)

process.JetAnalyzerStepZVetoLow4d = process.JetAnalyzerStep4d.clone(jetSource = 'goodJetsZVetoLow',)
process.JetAnalyzerStepZVetoLow4 = process.JetAnalyzerStep4.clone(jetSource = 'finalJetsZVetoLow',)
process.JetAnalyzerStepZVetoLow5J = process.JetAnalyzerStep5J.clone(jetSource = 'finalJetsZVetoLow',)
process.JetAnalyzerStepZVetoLow5Bhe = process.JetAnalyzerStep5Bhe.clone(jetSource = 'bSsvHeMJetsZVetoLow',)
process.JetAnalyzerStepZVetoLow5Bhp = process.JetAnalyzerStep5Bhp.clone(jetSource = 'bSsvHpTJetsZVetoLow',)
process.JetAnalyzerStepZVetoLow6J = process.JetAnalyzerStep6J.clone(jetSource = 'finalJetsZVetoLow',)
process.JetAnalyzerStepZVetoLow6Bhe = process.JetAnalyzerStep6Bhe.clone(jetSource = 'bSsvHeMJetsZVetoLow',)
process.JetAnalyzerStepZVetoLow6Bhp = process.JetAnalyzerStep6Bhp.clone(jetSource = 'bSsvHpTJetsZVetoLow',)
process.JetAnalyzerStepZVetoLow7aJ = process.JetAnalyzerStep7aJ.clone(jetSource = 'finalJetsZVetoLow',)
process.JetAnalyzerStepZVetoLow7aBhe = process.JetAnalyzerStep7aBhe.clone(jetSource = 'bSsvHeMJetsZVetoLow',)
process.JetAnalyzerStepZVetoLow7aBhp = process.JetAnalyzerStep7aBhp.clone(jetSource = 'bSsvHpTJetsZVetoLow',)
process.JetAnalyzerStepZVetoLow7bJ = process.JetAnalyzerStep7bJ.clone(jetSource = 'finalJetsZVetoLow',)
process.JetAnalyzerStepZVetoLow7bBhe = process.JetAnalyzerStep7bBhe.clone(jetSource = 'bSsvHeMJetsZVetoLow',)
process.JetAnalyzerStepZVetoLow7bBhp = process.JetAnalyzerStep7bBhp.clone(jetSource = 'bSsvHpTJetsZVetoLow',)
process.JetAnalyzerStepZVetoLow7cJ = process.JetAnalyzerStep7cJ.clone(jetSource = 'finalJetsZVetoLow',)
process.JetAnalyzerStepZVetoLow7cBhe = process.JetAnalyzerStep7cBhe.clone(jetSource = 'bSsvHeMJetsZVetoLow',)
process.JetAnalyzerStepZVetoLow7cBhp = process.JetAnalyzerStep7cBhp.clone(jetSource = 'bSsvHpTJetsZVetoLow',)
process.JetAnalyzerStepZVetoLow7J = process.JetAnalyzerStep7J.clone(jetSource = 'finalJetsZVetoLow',)
process.JetAnalyzerStepZVetoLow7Bhe = process.JetAnalyzerStep7Bhe.clone(jetSource = 'bSsvHeMJetsZVetoLow',)
process.JetAnalyzerStepZVetoLow7Bhp = process.JetAnalyzerStep7Bhp.clone(jetSource = 'bSsvHpTJetsZVetoLow',)
process.JetAnalyzerStepZVetoHigh4d = process.JetAnalyzerStep4d.clone(jetSource = 'goodJetsZVetoHigh',)
process.JetAnalyzerStepZVetoHigh4 = process.JetAnalyzerStep4.clone(jetSource = 'finalJetsZVetoHigh',)
process.JetAnalyzerStepZVetoHigh5J = process.JetAnalyzerStep5J.clone(jetSource = 'finalJetsZVetoHigh',)
process.JetAnalyzerStepZVetoHigh5Bhe = process.JetAnalyzerStep5Bhe.clone(jetSource = 'bSsvHeMJetsZVetoHigh',)
process.JetAnalyzerStepZVetoHigh5Bhp = process.JetAnalyzerStep5Bhp.clone(jetSource = 'bSsvHpTJetsZVetoHigh',)
process.JetAnalyzerStepZVetoHigh6J = process.JetAnalyzerStep6J.clone(jetSource = 'finalJetsZVetoHigh',)
process.JetAnalyzerStepZVetoHigh6Bhe = process.JetAnalyzerStep6Bhe.clone(jetSource = 'bSsvHeMJetsZVetoHigh',)
process.JetAnalyzerStepZVetoHigh6Bhp = process.JetAnalyzerStep6Bhp.clone(jetSource = 'bSsvHpTJetsZVetoHigh',)
process.JetAnalyzerStepZVetoHigh7aJ = process.JetAnalyzerStep7aJ.clone(jetSource = 'finalJetsZVetoHigh',)
process.JetAnalyzerStepZVetoHigh7aBhe = process.JetAnalyzerStep7aBhe.clone(jetSource = 'bSsvHeMJetsZVetoHigh',)
process.JetAnalyzerStepZVetoHigh7aBhp = process.JetAnalyzerStep7aBhp.clone(jetSource = 'bSsvHpTJetsZVetoHigh',)
process.JetAnalyzerStepZVetoHigh7bJ = process.JetAnalyzerStep7bJ.clone(jetSource = 'finalJetsZVetoHigh',)
process.JetAnalyzerStepZVetoHigh7bBhe = process.JetAnalyzerStep7bBhe.clone(jetSource = 'bSsvHeMJetsZVetoHigh',)
process.JetAnalyzerStepZVetoHigh7bBhp = process.JetAnalyzerStep7bBhp.clone(jetSource = 'bSsvHpTJetsZVetoHigh',)
process.JetAnalyzerStepZVetoHigh7cJ = process.JetAnalyzerStep7cJ.clone(jetSource = 'finalJetsZVetoHigh',)
process.JetAnalyzerStepZVetoHigh7cBhe = process.JetAnalyzerStep7cBhe.clone(jetSource = 'bSsvHeMJetsZVetoHigh',)
process.JetAnalyzerStepZVetoHigh7cBhp = process.JetAnalyzerStep7cBhp.clone(jetSource = 'bSsvHpTJetsZVetoHigh',)
process.JetAnalyzerStepZVetoHigh7J = process.JetAnalyzerStep7J.clone(jetSource = 'finalJetsZVetoHigh',)
process.JetAnalyzerStepZVetoHigh7Bhe = process.JetAnalyzerStep7Bhe.clone(jetSource = 'bSsvHeMJetsZVetoHigh',)
process.JetAnalyzerStepZVetoHigh7Bhp = process.JetAnalyzerStep7Bhp.clone(jetSource = 'bSsvHpTJetsZVetoHigh',)

process.JetAnalyzerStepNoMet7aJ = process.JetAnalyzerStep7aJ.clone()
process.JetAnalyzerStepNoMet7aBhe = process.JetAnalyzerStep7aBhe.clone()
process.JetAnalyzerStepNoMet7aBhp = process.JetAnalyzerStep7aBhp.clone()
process.JetAnalyzerStepNoMet7bJ = process.JetAnalyzerStep7bJ.clone()
process.JetAnalyzerStepNoMet7bBhe = process.JetAnalyzerStep7bBhe.clone()
process.JetAnalyzerStepNoMet7bBhp = process.JetAnalyzerStep7bBhp.clone()
process.JetAnalyzerStepNoMet7cJ = process.JetAnalyzerStep7cJ.clone()
process.JetAnalyzerStepNoMet7cBhe = process.JetAnalyzerStep7cBhe.clone()
process.JetAnalyzerStepNoMet7cBhp = process.JetAnalyzerStep7cBhp.clone()
process.JetAnalyzerStepNoMet7J = process.JetAnalyzerStep7J.clone()
process.JetAnalyzerStepNoMet7Bhe = process.JetAnalyzerStep7Bhe.clone()
process.JetAnalyzerStepNoMet7Bhp = process.JetAnalyzerStep7Bhp.clone()

process.JetAnalyzerStepZVetoLowNoMet7aJ = process.JetAnalyzerStepZVetoLow7aJ.clone()
process.JetAnalyzerStepZVetoLowNoMet7aBhe = process.JetAnalyzerStepZVetoLow7aBhe.clone()
process.JetAnalyzerStepZVetoLowNoMet7aBhp = process.JetAnalyzerStepZVetoLow7aBhp.clone()
process.JetAnalyzerStepZVetoLowNoMet7bJ = process.JetAnalyzerStepZVetoLow7bJ.clone()
process.JetAnalyzerStepZVetoLowNoMet7bBhe = process.JetAnalyzerStepZVetoLow7bBhe.clone()
process.JetAnalyzerStepZVetoLowNoMet7bBhp = process.JetAnalyzerStepZVetoLow7bBhp.clone()
process.JetAnalyzerStepZVetoLowNoMet7cJ = process.JetAnalyzerStepZVetoLow7cJ.clone()
process.JetAnalyzerStepZVetoLowNoMet7cBhe = process.JetAnalyzerStepZVetoLow7cBhe.clone()
process.JetAnalyzerStepZVetoLowNoMet7cBhp = process.JetAnalyzerStepZVetoLow7cBhp.clone()
process.JetAnalyzerStepZVetoLowNoMet7J = process.JetAnalyzerStepZVetoLow7J.clone()
process.JetAnalyzerStepZVetoLowNoMet7Bhe = process.JetAnalyzerStepZVetoLow7Bhe.clone()
process.JetAnalyzerStepZVetoLowNoMet7Bhp = process.JetAnalyzerStepZVetoLow7Bhp.clone()

process.JetAnalyzerStepZVetoHighNoMet7aJ = process.JetAnalyzerStepZVetoHigh7aJ.clone()
process.JetAnalyzerStepZVetoHighNoMet7aBhe = process.JetAnalyzerStepZVetoHigh7aBhe.clone()
process.JetAnalyzerStepZVetoHighNoMet7aBhp = process.JetAnalyzerStepZVetoHigh7aBhp.clone()
process.JetAnalyzerStepZVetoHighNoMet7bJ = process.JetAnalyzerStepZVetoHigh7bJ.clone()
process.JetAnalyzerStepZVetoHighNoMet7bBhe = process.JetAnalyzerStepZVetoHigh7bBhe.clone()
process.JetAnalyzerStepZVetoHighNoMet7bBhp = process.JetAnalyzerStepZVetoHigh7bBhp.clone()
process.JetAnalyzerStepZVetoHighNoMet7cJ = process.JetAnalyzerStepZVetoHigh7cJ.clone()
process.JetAnalyzerStepZVetoHighNoMet7cBhe = process.JetAnalyzerStepZVetoHigh7cBhe.clone()
process.JetAnalyzerStepZVetoHighNoMet7cBhp = process.JetAnalyzerStepZVetoHigh7cBhp.clone()
process.JetAnalyzerStepZVetoHighNoMet7J = process.JetAnalyzerStepZVetoHigh7J.clone()
process.JetAnalyzerStepZVetoHighNoMet7Bhe = process.JetAnalyzerStepZVetoHigh7Bhe.clone()
process.JetAnalyzerStepZVetoHighNoMet7Bhp = process.JetAnalyzerStepZVetoHigh7Bhp.clone()



## missing et analyzer
process.load("ZmumuAnalysis.Analyzer.MetAnalyzer_cfi")
process.MetAnalyzerStep6a = process.MetAnalyzer.clone(metSource = 'patMETsPF',)
process.MetAnalyzerStep7a = process.MetAnalyzer.clone(metSource = 'patMETsPF',)
process.MetAnalyzerStep7b = process.MetAnalyzer.clone(metSource = 'patMETsPF',)
process.MetAnalyzerStep7c = process.MetAnalyzer.clone(metSource = 'patMETsPF',)
process.MetAnalyzerStep7 = process.MetAnalyzer.clone(metSource = 'patMETsPF',)

process.MetAnalyzerStepZVetoLow6a = process.MetAnalyzerStep6a.clone()
process.MetAnalyzerStepZVetoLow7a = process.MetAnalyzerStep7a.clone()
process.MetAnalyzerStepZVetoLow7b = process.MetAnalyzerStep7b.clone()
process.MetAnalyzerStepZVetoLow7c = process.MetAnalyzerStep7c.clone()
process.MetAnalyzerStepZVetoLow7 = process.MetAnalyzerStep7.clone()
process.MetAnalyzerStepZVetoHigh6a = process.MetAnalyzerStep6a.clone()
process.MetAnalyzerStepZVetoHigh7a = process.MetAnalyzerStep7a.clone()
process.MetAnalyzerStepZVetoHigh7b = process.MetAnalyzerStep7b.clone()
process.MetAnalyzerStepZVetoHigh7c = process.MetAnalyzerStep7c.clone()
process.MetAnalyzerStepZVetoHigh7 = process.MetAnalyzerStep7.clone()

process.MetAnalyzerStepNoMet7a = process.MetAnalyzerStep7a.clone()
process.MetAnalyzerStepNoMet7b = process.MetAnalyzerStep7b.clone()
process.MetAnalyzerStepNoMet7c = process.MetAnalyzerStep7c.clone()
process.MetAnalyzerStepNoMet7 = process.MetAnalyzerStep7.clone()
process.MetAnalyzerStepZVetoLowNoMet7a = process.MetAnalyzerStepZVetoLow7a.clone()
process.MetAnalyzerStepZVetoLowNoMet7b = process.MetAnalyzerStepZVetoLow7b.clone()
process.MetAnalyzerStepZVetoLowNoMet7c = process.MetAnalyzerStepZVetoLow7c.clone()
process.MetAnalyzerStepZVetoLowNoMet7 = process.MetAnalyzerStepZVetoLow7.clone()
process.MetAnalyzerStepZVetoHighNoMet7a = process.MetAnalyzerStepZVetoHigh7a.clone()
process.MetAnalyzerStepZVetoHighNoMet7b = process.MetAnalyzerStepZVetoHigh7b.clone()
process.MetAnalyzerStepZVetoHighNoMet7c = process.MetAnalyzerStepZVetoHigh7c.clone()
process.MetAnalyzerStepZVetoHighNoMet7 = process.MetAnalyzerStepZVetoHigh7.clone()





#******************************************************************************************
#   Utils Modules
#******************************************************************************************

process.load("ZmumuAnalysis.Utils.RunEventListing_cff")
process.RunEventListingStep3 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListingStep5 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListingStep6 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListingStep7 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListingStepZVetoLow3 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListingStepZVetoLow5 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListingStepZVetoLow6 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListingStepZVetoLow7 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListingStepZVetoHigh3 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListingStepZVetoHigh5 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListingStepZVetoHigh6 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListingStepZVetoHigh7 = process.RunEventListingCreateTreeOnly.clone()

process.RunEventListingStepNoMet7 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListingStepZVetoLowNoMet7 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListingStepZVetoHighNoMet7 = process.RunEventListingCreateTreeOnly.clone()



#******************************************************************************************
#   Analysis Path
#******************************************************************************************


# Additional statements for use with trigger REDIGI

if(isData): TRIG_RESULT = "HLT"
elif(isMC): TRIG_RESULT = "HLT"
else: print "Error, wrong configuration of samples"; raise KeyError("ERROR")

# Does this work for all files? - No, al least not for TriggerFilter
#TRIG_RESULT = "PAT"

process.TriggerAnalyzerStep1a.triggerResults = cms.InputTag('TriggerResults','',TRIG_RESULT)
process.TriggerFilter.TriggerResultsTag = cms.InputTag('TriggerResults','',TRIG_RESULT)
process.patTrigger.processName = TRIG_RESULT
process.patTrigger.triggerResults = cms.InputTag("TriggerResults::" + TRIG_RESULT)
process.patTrigger.triggerEvent = cms.InputTag("hltTriggerSummaryAOD::" + TRIG_RESULT)



#******************************************************************************************
#   Sequences
#******************************************************************************************

## Apply generator filters here
process.seqGeneratorFilter = cms.Sequence()
if(isZmumu):
    process.seqGeneratorFilter *= process.GeneratorZmumuDiMuFilter
if(isZmumuB or isZmumuUdsc):
    process.seqGeneratorFilter *= process.GeneratorZmumuDiMuFilter
    process.seqGeneratorFilter *= process.buildSignalBCollections
if(isZmumuB):
    process.seqGeneratorFilter *= process.signalBSelection
if(isZmumuUdsc):
    process.seqGeneratorFilter *= ~process.signalBSelection
if(isZtautau):
    process.seqGeneratorFilter *= process.GeneratorZmumuDiTauFilter



## Define steps and corresponding analyzers for default analysis
process.step0 = cms.Sequence(
    process.EventCounterStep0
)

process.step1a = cms.Sequence(
    process.EventCounterStep1a+
    process.TriggerAnalyzerStep1a
)
process.step1b = cms.Sequence(
    process.EventCounterStep1b+
    process.VertexAnalyzerStep1b
)
process.step1 = cms.Sequence(
    process.EventCounterStep1+
    process.VertexAnalyzerStep1
)

process.step2a = cms.Sequence(
    process.EventCounterStep2a
)
process.step2b = cms.Sequence(
    process.EventCounterStep2b+
    process.MuonAnalyzerStep2b
)
process.step2c = cms.Sequence(
    process.EventCounterStep2c
)
process.step2d = cms.Sequence(
    process.EventCounterStep2d
)
process.step2e = cms.Sequence(
    process.EventCounterStep2e
)
process.step2f = cms.Sequence(
    process.EventCounterStep2f
)
process.step2 = cms.Sequence(
    process.EventCounterStep2+
    process.MuonAnalyzerStep2
)

process.step3a = cms.Sequence(
    process.EventCounterStep3a
)
process.step3b = cms.Sequence(
    process.EventCounterStep3b
)
process.step3c = cms.Sequence(
    process.EventCounterStep3c
)
process.step3d = cms.Sequence(
    process.EventCounterStep3d+
    process.DiMuonAnalyzerStep3d
)
process.step3e = cms.Sequence(
    process.EventCounterStep3e+
    process.DiMuonAnalyzerStep3e
)
process.step3f = cms.Sequence(
    process.EventCounterStep3f+
    process.VertexAnalyzerStep3f+
    process.DiMuonAnalyzerStep3f
)
process.step3 = cms.Sequence(
    process.EventCounterStep3+
    process.VertexAnalyzerStep3+
    process.MuonAnalyzerStep3+
    process.DiMuonAnalyzerStep3+
    process.RunEventListingStep3
)

process.step4a = cms.Sequence(
    process.EventCounterStep4a+
    process.JetAnalyzerStep4a
)
process.step4b = cms.Sequence(
    process.EventCounterStep4b+
    process.JetAnalyzerStep4b
)
process.step4c = cms.Sequence(
    process.EventCounterStep4c+
    process.JetAnalyzerStep4c
)
process.step4d = cms.Sequence(
    process.EventCounterStep4d+
    process.JetAnalyzerStep4d
)
process.step4 = cms.Sequence(
    process.EventCounterStep4+
    process.MuonAnalyzerStep4+
    process.DiMuonAnalyzerStep4+
    process.JetAnalyzerStep4
)

process.step5 = cms.Sequence(
    process.EventCounterStep5+
    process.MuonAnalyzerStep5+
    process.DiMuonAnalyzerStep5+
    process.JetAnalyzerStep5J+
    process.JetAnalyzerStep5Bhe+
    process.JetAnalyzerStep5Bhp+
    process.RunEventListingStep5
)

process.step6a = cms.Sequence(
    process.EventCounterStep6a+
    process.MetAnalyzerStep6a
)
process.step6 = cms.Sequence(
    process.EventCounterStep6+
    process.MuonAnalyzerStep6+
    process.DiMuonAnalyzerStep6+
    process.JetAnalyzerStep6J+
    process.JetAnalyzerStep6Bhe+
    process.JetAnalyzerStep6Bhp+
    process.RunEventListingStep6
)

process.step7a = cms.Sequence(
    process.EventCounterStep7a+
    process.MuonAnalyzerStep7a+
    process.DiMuonAnalyzerStep7a+
    process.JetAnalyzerStep7aJ+
    process.JetAnalyzerStep7aBhe+
    process.JetAnalyzerStep7aBhp+
    process.MetAnalyzerStep7a
)
process.step7b = cms.Sequence(
    process.EventCounterStep7b+
    process.MuonAnalyzerStep7b+
    process.DiMuonAnalyzerStep7b+
    process.JetAnalyzerStep7bJ+
    process.JetAnalyzerStep7bBhe+
    process.JetAnalyzerStep7bBhp+
    process.MetAnalyzerStep7b
)
process.step7c = cms.Sequence(
    process.EventCounterStep7c+
    process.MuonAnalyzerStep7c+
    process.DiMuonAnalyzerStep7c+
    process.JetAnalyzerStep7cJ+
    process.JetAnalyzerStep7cBhe+
    process.JetAnalyzerStep7cBhp+
    process.MetAnalyzerStep7c
)
process.step7 = cms.Sequence(
    process.EventCounterStep7+
    process.MuonAnalyzerStep7+
    process.DiMuonAnalyzerStep7+
    process.JetAnalyzerStep7J+
    process.JetAnalyzerStep7Bhe+
    process.JetAnalyzerStep7Bhp+
    process.MetAnalyzerStep7+
    process.RunEventListingStep7
)



## Define steps and corresponding analyzers for analysis excluding the Z mass window (lower sideband)
process.stepZVetoLow0 = cms.Sequence()
process.stepZVetoLow1a = cms.Sequence()
process.stepZVetoLow1b = cms.Sequence()
process.stepZVetoLow1 = cms.Sequence()
process.stepZVetoLow2a = cms.Sequence()
process.stepZVetoLow2b = cms.Sequence()
process.stepZVetoLow2c = cms.Sequence()
process.stepZVetoLow2d = cms.Sequence()
process.stepZVetoLow2e = cms.Sequence()
process.stepZVetoLow2f = cms.Sequence()
process.stepZVetoLow2 = cms.Sequence()
process.stepZVetoLow3a = cms.Sequence()
process.stepZVetoLow3b = cms.Sequence()
process.stepZVetoLow3c = cms.Sequence()
process.stepZVetoLow3d = cms.Sequence()
process.stepZVetoLow3e = cms.Sequence()

process.stepZVetoLow3f = cms.Sequence(
    process.EventCounterStepZVetoLow3f+
    process.VertexAnalyzerStepZVetoLow3f+
    process.DiMuonAnalyzerStepZVetoLow3f
)
process.stepZVetoLow3 = cms.Sequence(
    process.EventCounterStepZVetoLow3+
    #process.VertexAnalyzerStepZVetoLow3+
    process.MuonAnalyzerStepZVetoLow3+
    #process.DiMuonAnalyzerStepZVetoLow3+
    process.RunEventListingStepZVetoLow3
)

process.stepZVetoLow4a = cms.Sequence(
    process.EventCounterStepZVetoLow4a
)
process.stepZVetoLow4b = cms.Sequence(
    process.EventCounterStepZVetoLow4b
)
process.stepZVetoLow4c = cms.Sequence(
    process.EventCounterStepZVetoLow4c
)
process.stepZVetoLow4d = cms.Sequence(
    process.EventCounterStepZVetoLow4d+
    process.JetAnalyzerStepZVetoLow4d
)
process.stepZVetoLow4 = cms.Sequence(
    process.EventCounterStepZVetoLow4+
    process.MuonAnalyzerStepZVetoLow4+
    process.DiMuonAnalyzerStepZVetoLow4+
    process.JetAnalyzerStepZVetoLow4
)

process.stepZVetoLow5 = cms.Sequence(
    process.EventCounterStepZVetoLow5+
    process.MuonAnalyzerStepZVetoLow5+
    process.DiMuonAnalyzerStepZVetoLow5+
    process.JetAnalyzerStepZVetoLow5J+
    process.JetAnalyzerStepZVetoLow5Bhe+
    process.JetAnalyzerStepZVetoLow5Bhp+
    process.RunEventListingStepZVetoLow5
)

process.stepZVetoLow6a = cms.Sequence(
    process.EventCounterStepZVetoLow6a+
    process.MetAnalyzerStepZVetoLow6a
)
process.stepZVetoLow6 = cms.Sequence(
    process.EventCounterStepZVetoLow6+
    process.MuonAnalyzerStepZVetoLow6+
    process.DiMuonAnalyzerStepZVetoLow6+
    process.JetAnalyzerStepZVetoLow6J+
    process.JetAnalyzerStepZVetoLow6Bhe+
    process.JetAnalyzerStepZVetoLow6Bhp+
    process.RunEventListingStepZVetoLow6
)

process.stepZVetoLow7a = cms.Sequence(
    process.EventCounterStepZVetoLow7a+
    process.MuonAnalyzerStepZVetoLow7a+
    process.DiMuonAnalyzerStepZVetoLow7a+
    process.JetAnalyzerStepZVetoLow7aJ+
    process.JetAnalyzerStepZVetoLow7aBhe+
    process.JetAnalyzerStepZVetoLow7aBhp+
    process.MetAnalyzerStepZVetoLow7a
)
process.stepZVetoLow7b = cms.Sequence(
    process.EventCounterStepZVetoLow7b+
    process.MuonAnalyzerStepZVetoLow7b+
    process.DiMuonAnalyzerStepZVetoLow7b+
    process.JetAnalyzerStepZVetoLow7bJ+
    process.JetAnalyzerStepZVetoLow7bBhe+
    process.JetAnalyzerStepZVetoLow7bBhp+
    process.MetAnalyzerStepZVetoLow7b
)
process.stepZVetoLow7c = cms.Sequence(
    process.EventCounterStepZVetoLow7c+
    process.MuonAnalyzerStepZVetoLow7c+
    process.DiMuonAnalyzerStepZVetoLow7c+
    process.JetAnalyzerStepZVetoLow7cJ+
    process.JetAnalyzerStepZVetoLow7cBhe+
    process.JetAnalyzerStepZVetoLow7cBhp+
    process.MetAnalyzerStepZVetoLow7c
)
process.stepZVetoLow7 = cms.Sequence(
    process.EventCounterStepZVetoLow7+
    process.MuonAnalyzerStepZVetoLow7+
    process.DiMuonAnalyzerStepZVetoLow7+
    process.JetAnalyzerStepZVetoLow7J+
    process.JetAnalyzerStepZVetoLow7Bhe+
    process.JetAnalyzerStepZVetoLow7Bhp+
    process.MetAnalyzerStepZVetoLow7+
    process.RunEventListingStepZVetoLow7
)



## Define steps and corresponding analyzers for analysis excluding the Z mass window (upper sideband)
process.stepZVetoHigh0 = cms.Sequence()
process.stepZVetoHigh1a = cms.Sequence()
process.stepZVetoHigh1b = cms.Sequence()
process.stepZVetoHigh1 = cms.Sequence()
process.stepZVetoHigh2a = cms.Sequence()
process.stepZVetoHigh2b = cms.Sequence()
process.stepZVetoHigh2c = cms.Sequence()
process.stepZVetoHigh2d = cms.Sequence()
process.stepZVetoHigh2e = cms.Sequence()
process.stepZVetoHigh2f = cms.Sequence()
process.stepZVetoHigh2 = cms.Sequence()
process.stepZVetoHigh3a = cms.Sequence()
process.stepZVetoHigh3b = cms.Sequence()
process.stepZVetoHigh3c = cms.Sequence()
process.stepZVetoHigh3d = cms.Sequence()
process.stepZVetoHigh3e = cms.Sequence()

process.stepZVetoHigh3f = cms.Sequence(
    process.EventCounterStepZVetoHigh3f+
    process.VertexAnalyzerStepZVetoHigh3f+
    process.DiMuonAnalyzerStepZVetoHigh3f
)
process.stepZVetoHigh3 = cms.Sequence(
    process.EventCounterStepZVetoHigh3+
    #process.VertexAnalyzerStepZVetoHigh3+
    process.MuonAnalyzerStepZVetoHigh3+
    #process.DiMuonAnalyzerStepZVetoHigh3+
    process.RunEventListingStepZVetoHigh3
)

process.stepZVetoHigh4a = cms.Sequence(
    process.EventCounterStepZVetoHigh4a
)
process.stepZVetoHigh4b = cms.Sequence(
    process.EventCounterStepZVetoHigh4b
)
process.stepZVetoHigh4c = cms.Sequence(
    process.EventCounterStepZVetoHigh4c
)
process.stepZVetoHigh4d = cms.Sequence(
    process.EventCounterStepZVetoHigh4d+
    process.JetAnalyzerStepZVetoHigh4d
)
process.stepZVetoHigh4 = cms.Sequence(
    process.EventCounterStepZVetoHigh4+
    process.MuonAnalyzerStepZVetoHigh4+
    process.DiMuonAnalyzerStepZVetoHigh4+
    process.JetAnalyzerStepZVetoHigh4
)

process.stepZVetoHigh5 = cms.Sequence(
    process.EventCounterStepZVetoHigh5+
    process.MuonAnalyzerStepZVetoHigh5+
    process.DiMuonAnalyzerStepZVetoHigh5+
    process.JetAnalyzerStepZVetoHigh5J+
    process.JetAnalyzerStepZVetoHigh5Bhe+
    process.JetAnalyzerStepZVetoHigh5Bhp+
    process.RunEventListingStepZVetoHigh5
)

process.stepZVetoHigh6a = cms.Sequence(
    process.EventCounterStepZVetoHigh6a+
    process.MetAnalyzerStepZVetoHigh6a
)
process.stepZVetoHigh6 = cms.Sequence(
    process.EventCounterStepZVetoHigh6+
    process.MuonAnalyzerStepZVetoHigh6+
    process.DiMuonAnalyzerStepZVetoHigh6+
    process.JetAnalyzerStepZVetoHigh6J+
    process.JetAnalyzerStepZVetoHigh6Bhe+
    process.JetAnalyzerStepZVetoHigh6Bhp+
    process.RunEventListingStepZVetoHigh6
)

process.stepZVetoHigh7a = cms.Sequence(
    process.EventCounterStepZVetoHigh7a+
    process.MuonAnalyzerStepZVetoHigh7a+
    process.DiMuonAnalyzerStepZVetoHigh7a+
    process.JetAnalyzerStepZVetoHigh7aJ+
    process.JetAnalyzerStepZVetoHigh7aBhe+
    process.JetAnalyzerStepZVetoHigh7aBhp+
    process.MetAnalyzerStepZVetoHigh7a
)
process.stepZVetoHigh7b = cms.Sequence(
    process.EventCounterStepZVetoHigh7b+
    process.MuonAnalyzerStepZVetoHigh7b+
    process.DiMuonAnalyzerStepZVetoHigh7b+
    process.JetAnalyzerStepZVetoHigh7bJ+
    process.JetAnalyzerStepZVetoHigh7bBhe+
    process.JetAnalyzerStepZVetoHigh7bBhp+
    process.MetAnalyzerStepZVetoHigh7b
)
process.stepZVetoHigh7c = cms.Sequence(
    process.EventCounterStepZVetoHigh7c+
    process.MuonAnalyzerStepZVetoHigh7c+
    process.DiMuonAnalyzerStepZVetoHigh7c+
    process.JetAnalyzerStepZVetoHigh7cJ+
    process.JetAnalyzerStepZVetoHigh7cBhe+
    process.JetAnalyzerStepZVetoHigh7cBhp+
    process.MetAnalyzerStepZVetoHigh7c
)
process.stepZVetoHigh7 = cms.Sequence(
    process.EventCounterStepZVetoHigh7+
    process.MuonAnalyzerStepZVetoHigh7+
    process.DiMuonAnalyzerStepZVetoHigh7+
    process.JetAnalyzerStepZVetoHigh7J+
    process.JetAnalyzerStepZVetoHigh7Bhe+
    process.JetAnalyzerStepZVetoHigh7Bhp+
    process.MetAnalyzerStepZVetoHigh7+
    process.RunEventListingStepZVetoHigh7
)



## Define steps and corresponding analyzers for analysis excluding cut on MET (signal region, lower and upper sideband)
process.stepNoMet7a = cms.Sequence(
    process.EventCounterStepNoMet7a+
    process.MuonAnalyzerStepNoMet7a+
    process.DiMuonAnalyzerStepNoMet7a+
    process.JetAnalyzerStepNoMet7aJ+
    process.JetAnalyzerStepNoMet7aBhe+
    process.JetAnalyzerStepNoMet7aBhp+
    process.MetAnalyzerStepNoMet7a
)
process.stepNoMet7b = cms.Sequence(
    process.EventCounterStepNoMet7b+
    process.MuonAnalyzerStepNoMet7b+
    process.DiMuonAnalyzerStepNoMet7b+
    process.JetAnalyzerStepNoMet7bJ+
    process.JetAnalyzerStepNoMet7bBhe+
    process.JetAnalyzerStepNoMet7bBhp+
    process.MetAnalyzerStepNoMet7b
)
process.stepNoMet7c = cms.Sequence(
    process.EventCounterStepNoMet7c+
    process.MuonAnalyzerStepNoMet7c+
    process.DiMuonAnalyzerStepNoMet7c+
    process.JetAnalyzerStepNoMet7cJ+
    process.JetAnalyzerStepNoMet7cBhe+
    process.JetAnalyzerStepNoMet7cBhp+
    process.MetAnalyzerStepNoMet7c
)
process.stepNoMet7 = cms.Sequence(
    process.EventCounterStepNoMet7+
    process.MuonAnalyzerStepNoMet7+
    process.DiMuonAnalyzerStepNoMet7+
    process.JetAnalyzerStepNoMet7J+
    process.JetAnalyzerStepNoMet7Bhe+
    process.JetAnalyzerStepNoMet7Bhp+
    process.MetAnalyzerStepNoMet7+
    process.RunEventListingStepNoMet7
)

process.stepZVetoLowNoMet7a = cms.Sequence(
    process.EventCounterStepZVetoLowNoMet7a+
    process.MuonAnalyzerStepZVetoLowNoMet7a+
    process.DiMuonAnalyzerStepZVetoLowNoMet7a+
    process.JetAnalyzerStepZVetoLowNoMet7aJ+
    process.JetAnalyzerStepZVetoLowNoMet7aBhe+
    process.JetAnalyzerStepZVetoLowNoMet7aBhp+
    process.MetAnalyzerStepZVetoLowNoMet7a
)
process.stepZVetoLowNoMet7b = cms.Sequence(
    process.EventCounterStepZVetoLowNoMet7b+
    process.MuonAnalyzerStepZVetoLowNoMet7b+
    process.DiMuonAnalyzerStepZVetoLowNoMet7b+
    process.JetAnalyzerStepZVetoLowNoMet7bJ+
    process.JetAnalyzerStepZVetoLowNoMet7bBhe+
    process.JetAnalyzerStepZVetoLowNoMet7bBhp+
    process.MetAnalyzerStepZVetoLowNoMet7b
)
process.stepZVetoLowNoMet7c = cms.Sequence(
    process.EventCounterStepZVetoLowNoMet7c+
    process.MuonAnalyzerStepZVetoLowNoMet7c+
    process.DiMuonAnalyzerStepZVetoLowNoMet7c+
    process.JetAnalyzerStepZVetoLowNoMet7cJ+
    process.JetAnalyzerStepZVetoLowNoMet7cBhe+
    process.JetAnalyzerStepZVetoLowNoMet7cBhp+
    process.MetAnalyzerStepZVetoLowNoMet7c
)
process.stepZVetoLowNoMet7 = cms.Sequence(
    process.EventCounterStepZVetoLowNoMet7+
    process.MuonAnalyzerStepZVetoLowNoMet7+
    process.DiMuonAnalyzerStepZVetoLowNoMet7+
    process.JetAnalyzerStepZVetoLowNoMet7J+
    process.JetAnalyzerStepZVetoLowNoMet7Bhe+
    process.JetAnalyzerStepZVetoLowNoMet7Bhp+
    process.MetAnalyzerStepZVetoLowNoMet7+
    process.RunEventListingStepZVetoLowNoMet7
)

process.stepZVetoHighNoMet7a = cms.Sequence(
    process.EventCounterStepZVetoHighNoMet7a+
    process.MuonAnalyzerStepZVetoHighNoMet7a+
    process.DiMuonAnalyzerStepZVetoHighNoMet7a+
    process.JetAnalyzerStepZVetoHighNoMet7aJ+
    process.JetAnalyzerStepZVetoHighNoMet7aBhe+
    process.JetAnalyzerStepZVetoHighNoMet7aBhp+
    process.MetAnalyzerStepZVetoHighNoMet7a
)
process.stepZVetoHighNoMet7b = cms.Sequence(
    process.EventCounterStepZVetoHighNoMet7b+
    process.MuonAnalyzerStepZVetoHighNoMet7b+
    process.DiMuonAnalyzerStepZVetoHighNoMet7b+
    process.JetAnalyzerStepZVetoHighNoMet7bJ+
    process.JetAnalyzerStepZVetoHighNoMet7bBhe+
    process.JetAnalyzerStepZVetoHighNoMet7bBhp+
    process.MetAnalyzerStepZVetoHighNoMet7b
)
process.stepZVetoHighNoMet7c = cms.Sequence(
    process.EventCounterStepZVetoHighNoMet7c+
    process.MuonAnalyzerStepZVetoHighNoMet7c+
    process.DiMuonAnalyzerStepZVetoHighNoMet7c+
    process.JetAnalyzerStepZVetoHighNoMet7cJ+
    process.JetAnalyzerStepZVetoHighNoMet7cBhe+
    process.JetAnalyzerStepZVetoHighNoMet7cBhp+
    process.MetAnalyzerStepZVetoHighNoMet7c
)
process.stepZVetoHighNoMet7 = cms.Sequence(
    process.EventCounterStepZVetoHighNoMet7+
    process.MuonAnalyzerStepZVetoHighNoMet7+
    process.DiMuonAnalyzerStepZVetoHighNoMet7+
    process.JetAnalyzerStepZVetoHighNoMet7J+
    process.JetAnalyzerStepZVetoHighNoMet7Bhe+
    process.JetAnalyzerStepZVetoHighNoMet7Bhp+
    process.MetAnalyzerStepZVetoHighNoMet7+
    process.RunEventListingStepZVetoHighNoMet7
)





#******************************************************************************************
#   Analysis Path
#******************************************************************************************



process.oppositeChargeAnalysis = cms.Path(
    process.step0*
    
    
    process.seqGeneratorFilter*
    process.step1a*
    
    process.TriggerFilter*
    process.buildVertexCollections*
    process.step1b*
    
    process.oneGoodPVSelection*
    process.step1*
    
    
    process.buildMuonCollections*
    process.step2a*
    
    process.oneInitialMuonSelection*
    process.step2b*
    
    process.oneLooseMuonSelection*
    process.step2c*
    
    process.oneTightMuonSelection*
    process.step2d*
    
    process.looseMuonSelection*
    process.step2e*
    
    process.tightMuonSelection*
    process.step2f*
    
    process.tightHltMuonSelection*
    process.step2*
    
    
    process.buildDimuonCollections*
    process.step3a*
    
    process.selectedDimuonSelection*
    process.step3b*
    
    process.cleanDimuonSelection*
    process.step3c*
    
    process.goodDimuonSelection*
    process.step3d*
    
    process.isolatedDimuonSelection*
    process.step3e*
    
    process.finalDimuonSelection*
    process.step3f*
    process.step3*
    
    
    process.buildJetCollections*
    process.step4a*
    
    process.oneCleanPatJetSelection*
    process.step4b*
    
    process.oneGoodIdJetSelection*
    process.step4c*
    
    process.oneGoodJetSelection*
    process.step4d*
    
    process.oneFinalJetSelection*
    process.step4*
    
    
    process.oneBSsvHeMJetSelection*
    process.step5*
    
    
    process.buildMetCollections*
    process.step6a*
    
    process.goodMetSelection*
    process.step6*
    
    
    process.oneBSsvHpTJetSelection*
    process.step7a*
    
    process.twoFinalJetSelection*
    process.step7b*
    
    process.twoBSsvHeMJetSelection*
    process.step7c*
    
    process.twoBSsvHpTJetSelection*
    process.step7
    
)




process.ZVetoLowOppositeChargeAnalysis = cms.Path(
    process.stepZVetoLow0*
    
    
    process.seqGeneratorFilter*
    process.stepZVetoLow1a*
    
    process.TriggerFilter*
    process.buildVertexCollections*
    process.stepZVetoLow1b*
    
    process.oneGoodPVSelection*
    process.stepZVetoLow1*
    
    
    process.buildMuonCollections*
    process.stepZVetoLow2a*
    
    process.oneInitialMuonSelection*
    process.stepZVetoLow2b*
    
    process.oneLooseMuonSelection*
    process.stepZVetoLow2c*
    
    process.oneTightMuonSelection*
    process.stepZVetoLow2d*
    
    process.looseMuonSelection*
    process.stepZVetoLow2e*
    
    process.tightMuonSelection*
    process.stepZVetoLow2f*
    
    process.tightHltMuonSelection*
    process.stepZVetoLow2*
    
    
    process.buildDimuonZVetoLowCollections*
    process.stepZVetoLow3a*
    
    process.selectedDimuonSelection*
    process.stepZVetoLow3b*
    
    process.cleanDimuonSelection*
    process.stepZVetoLow3c*
    
    process.goodDimuonSelection*
    process.stepZVetoLow3d*
    
    process.isolatedDimuonSelection*
    process.stepZVetoLow3e*
    
    process.finalDimuonZVetoLowSelection*
    process.stepZVetoLow3f*
    process.stepZVetoLow3*
    
    
    process.buildJetZVetoLowCollections*
    process.stepZVetoLow4a*
    
    process.oneCleanPatJetSelection*
    process.stepZVetoLow4b*
    
    process.oneGoodIdJetSelection*
    process.stepZVetoLow4c*
    
    process.oneGoodJetZVetoLowSelection*
    process.stepZVetoLow4d*
    
    process.oneFinalJetZVetoLowSelection*
    process.stepZVetoLow4*
    
    
    process.oneBSsvHeMJetZVetoLowSelection*
    process.stepZVetoLow5*
    
    
    process.buildMetCollections*
    process.stepZVetoLow6a*
    
    process.goodMetSelection*
    process.stepZVetoLow6*
    
    
    process.oneBSsvHpTJetZVetoLowSelection*
    process.stepZVetoLow7a*
    
    process.twoFinalJetZVetoLowSelection*
    process.stepZVetoLow7b*
    
    process.twoBSsvHeMJetZVetoLowSelection*
    process.stepZVetoLow7c*
    
    process.twoBSsvHpTJetZVetoLowSelection*
    process.stepZVetoLow7
    
)



process.ZVetoHighOppositeChargeAnalysis = cms.Path(
    process.stepZVetoHigh0*
    
    
    process.seqGeneratorFilter*
    process.stepZVetoHigh1a*
    
    process.TriggerFilter*
    process.buildVertexCollections*
    process.stepZVetoHigh1b*
    
    process.oneGoodPVSelection*
    process.stepZVetoHigh1*
    
    
    process.buildMuonCollections*
    process.stepZVetoHigh2a*
    
    process.oneInitialMuonSelection*
    process.stepZVetoHigh2b*
    
    process.oneLooseMuonSelection*
    process.stepZVetoHigh2c*
    
    process.oneTightMuonSelection*
    process.stepZVetoHigh2d*
    
    process.looseMuonSelection*
    process.stepZVetoHigh2e*
    
    process.tightMuonSelection*
    process.stepZVetoHigh2f*
    
    process.tightHltMuonSelection*
    process.stepZVetoHigh2*
    
    
    process.buildDimuonZVetoHighCollections*
    process.stepZVetoHigh3a*
    
    process.selectedDimuonSelection*
    process.stepZVetoHigh3b*
    
    process.cleanDimuonSelection*
    process.stepZVetoHigh3c*
    
    process.goodDimuonSelection*
    process.stepZVetoHigh3d*
    
    process.isolatedDimuonSelection*
    process.stepZVetoHigh3e*
    
    process.finalDimuonZVetoHighSelection*
    process.stepZVetoHigh3f*
    process.stepZVetoHigh3*
    
    
    process.buildJetZVetoHighCollections*
    process.stepZVetoHigh4a*
    
    process.oneCleanPatJetSelection*
    process.stepZVetoHigh4b*
    
    process.oneGoodIdJetSelection*
    process.stepZVetoHigh4c*
    
    process.oneGoodJetZVetoHighSelection*
    process.stepZVetoHigh4d*
    
    process.oneFinalJetZVetoHighSelection*
    process.stepZVetoHigh4*
    
    
    process.oneBSsvHeMJetZVetoHighSelection*
    process.stepZVetoHigh5*
    
    
    process.buildMetCollections*
    process.stepZVetoHigh6a*
    
    process.goodMetSelection*
    process.stepZVetoHigh6*
    
    
    process.oneBSsvHpTJetZVetoHighSelection*
    process.stepZVetoHigh7a*
    
    process.twoFinalJetZVetoHighSelection*
    process.stepZVetoHigh7b*
    
    process.twoBSsvHeMJetZVetoHighSelection*
    process.stepZVetoHigh7c*
    
    process.twoBSsvHpTJetZVetoHighSelection*
    process.stepZVetoHigh7
    
)



process.noMetOppositeChargeAnalysis = cms.Path(
    #process.stepNoMet0*
    
    
    process.seqGeneratorFilter*
    #process.stepNoMet1a*
    
    process.TriggerFilter*
    process.buildVertexCollections*
    #process.stepNoMet1b*
    
    process.oneGoodPVSelection*
    #process.stepNoMet1*
    
    
    process.buildMuonCollections*
    #process.stepNoMet2a*
    
    process.oneInitialMuonSelection*
    #process.stepNoMet2b*
    
    process.oneLooseMuonSelection*
    #process.stepNoMet2c*
    
    process.oneTightMuonSelection*
    #process.stepNoMet2d*
    
    process.looseMuonSelection*
    #process.stepNoMet2e*
    
    process.tightMuonSelection*
    #process.stepNoMet2f*
    
    process.tightHltMuonSelection*
    #process.stepNoMet2*
    
    
    process.buildDimuonCollections*
    #process.stepNoMet3a*
    
    process.selectedDimuonSelection*
    #process.stepNoMet3b*
    
    process.cleanDimuonSelection*
    #process.stepNoMet3c*
    
    process.goodDimuonSelection*
    #process.stepNoMet3d*
    
    process.isolatedDimuonSelection*
    #process.stepNoMet3e*
    
    process.finalDimuonSelection*
    #process.stepNoMet3f*
    #process.stepNoMet3*
    
    
    process.buildJetCollections*
    #process.stepNoMet4a*
    
    process.oneCleanPatJetSelection*
    #process.stepNoMet4b*
    
    process.oneGoodIdJetSelection*
    #process.stepNoMet4c*
    
    process.oneGoodJetSelection*
    #process.stepNoMet4d*
    
    process.oneFinalJetSelection*
    #process.stepNoMet4*
    
    
    process.oneBSsvHeMJetSelection*
    #process.stepNoMet5*
    
    
    # Do not apply MET Selection
    process.buildMetCollections*
    #process.stepNoMet6a*
    
    #process.goodMetSelection*
    #process.stepNoMet6*
    
    
    process.oneBSsvHpTJetSelection*
    process.stepNoMet7a*
    
    process.twoFinalJetSelection*
    process.stepNoMet7b*
    
    process.twoBSsvHeMJetSelection*
    process.stepNoMet7c*
    
    process.twoBSsvHpTJetSelection*
    process.stepNoMet7
    
)




process.ZVetoLowNoMetOppositeChargeAnalysis = cms.Path(
    #process.stepZVetoLowNoMet0*
    
    
    process.seqGeneratorFilter*
    #process.stepZVetoLowNoMet1a*
    
    process.TriggerFilter*
    process.buildVertexCollections*
    #process.stepZVetoLowNoMet1b*
    
    process.oneGoodPVSelection*
    #process.stepZVetoLowNoMet1*
    
    
    process.buildMuonCollections*
    #process.stepZVetoLowNoMet2a*
    
    process.oneInitialMuonSelection*
    #process.stepZVetoLowNoMet2b*
    
    process.oneLooseMuonSelection*
    #process.stepZVetoLowNoMet2c*
    
    process.oneTightMuonSelection*
    #process.stepZVetoLowNoMet2d*
    
    process.looseMuonSelection*
    #process.stepZVetoLowNoMet2e*
    
    process.tightMuonSelection*
    #process.stepZVetoLowNoMet2f*
    
    process.tightHltMuonSelection*
    #process.stepZVetoLowNoMet2*
    
    
    process.buildDimuonZVetoLowCollections*
    #process.stepZVetoLowNoMet3a*
    
    process.selectedDimuonSelection*
    #process.stepZVetoLowNoMet3b*
    
    process.cleanDimuonSelection*
    #process.stepZVetoLowNoMet3c*
    
    process.goodDimuonSelection*
    #process.stepZVetoLowNoMet3d*
    
    process.isolatedDimuonSelection*
    #process.stepZVetoLowNoMet3e*
    
    process.finalDimuonZVetoLowSelection*
    #process.stepZVetoLowNoMet3f*
    #process.stepZVetoLowNoMet3*
    
    
    process.buildJetZVetoLowCollections*
    #process.stepZVetoLowNoMet4a*
    
    process.oneCleanPatJetSelection*
    #process.stepZVetoLowNoMet4b*
    
    process.oneGoodIdJetSelection*
    #process.stepZVetoLowNoMet4c*
    
    process.oneGoodJetZVetoLowSelection*
    #process.stepZVetoLowNoMet4d*
    
    process.oneFinalJetZVetoLowSelection*
    #process.stepZVetoLowNoMet4*
    
    
    process.oneBSsvHeMJetZVetoLowSelection*
    #process.stepZVetoLowNoMet5*
    
    
    # Do not apply MET Selection
    process.buildMetCollections*
    #process.stepZVetoLowNoMet6a*
    
    #process.goodMetSelection*
    #process.stepZVetoLowNoMet6*
    
    
    process.oneBSsvHpTJetZVetoLowSelection*
    process.stepZVetoLowNoMet7a*
    
    process.twoFinalJetZVetoLowSelection*
    process.stepZVetoLowNoMet7b*
    
    process.twoBSsvHeMJetZVetoLowSelection*
    process.stepZVetoLowNoMet7c*
    
    process.twoBSsvHpTJetZVetoLowSelection*
    process.stepZVetoLowNoMet7
    
)



process.ZVetoHighNoMetOppositeChargeAnalysis = cms.Path(
    #process.stepZVetoHighNoMet0*
    
    
    process.seqGeneratorFilter*
    #process.stepZVetoHighNoMet1a*
    
    process.TriggerFilter*
    process.buildVertexCollections*
    #process.stepZVetoHighNoMet1b*
    
    process.oneGoodPVSelection*
    #process.stepZVetoHighNoMet1*
    
    
    process.buildMuonCollections*
    #process.stepZVetoHighNoMet2a*
    
    process.oneInitialMuonSelection*
    #process.stepZVetoHighNoMet2b*
    
    process.oneLooseMuonSelection*
    #process.stepZVetoHighNoMet2c*
    
    process.oneTightMuonSelection*
    #process.stepZVetoHighNoMet2d*
    
    process.looseMuonSelection*
    #process.stepZVetoHighNoMet2e*
    
    process.tightMuonSelection*
    #process.stepZVetoHighNoMet2f*
    
    process.tightHltMuonSelection*
    #process.stepZVetoHighNoMet2*
    
    
    process.buildDimuonZVetoHighCollections*
    #process.stepZVetoHighNoMet3a*
    
    process.selectedDimuonSelection*
    #process.stepZVetoHighNoMet3b*
    
    process.cleanDimuonSelection*
    #process.stepZVetoHighNoMet3c*
    
    process.goodDimuonSelection*
    #process.stepZVetoHighNoMet3d*
    
    process.isolatedDimuonSelection*
    #process.stepZVetoHighNoMet3e*
    
    process.finalDimuonZVetoHighSelection*
    #process.stepZVetoHighNoMet3f*
    #process.stepZVetoHighNoMet3*
    
    
    process.buildJetZVetoHighCollections*
    #process.stepZVetoHighNoMet4a*
    
    process.oneCleanPatJetSelection*
    #process.stepZVetoHighNoMet4b*
    
    process.oneGoodIdJetSelection*
    #process.stepZVetoHighNoMet4c*
    
    process.oneGoodJetZVetoHighSelection*
    #process.stepZVetoHighNoMet4d*
    
    process.oneFinalJetZVetoHighSelection*
    #process.stepZVetoHighNoMet4*
    
    
    process.oneBSsvHeMJetZVetoHighSelection*
    #process.stepZVetoHighNoMet5*
    
    
    # Do not apply MET Selection
    process.buildMetCollections*
    #process.stepZVetoHighNoMet6a*
    
    #process.goodMetSelection
    #process.stepZVetoHighNoMet6*
    
    
    process.oneBSsvHpTJetZVetoHighSelection*
    process.stepZVetoHighNoMet7a*
    
    process.twoFinalJetZVetoHighSelection*
    process.stepZVetoHighNoMet7b*
    
    process.twoBSsvHeMJetZVetoHighSelection*
    process.stepZVetoHighNoMet7c*
    
    process.twoBSsvHpTJetZVetoHighSelection*
    process.stepZVetoHighNoMet7
    
)










