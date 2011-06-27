import os

import FWCore.ParameterSet.Config as cms

process = cms.Process("FullCutflow")

## Message logger
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
isData3 = False
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
isZmumuUdsc = True
isZtautau = False
isWw = False
isWz = False
isZz = False
isTest = False

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
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.Run2011A_PromptReco_v1_May7_160404_163757_cff")
elif(isData2):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.Run2011A_PromptReco_v2_May7_160404_163757_cff")
elif(isData3):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.dilepton.Run2011A_v2_May7_to_May13_cff")
# MC
elif(isQcd):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_QCD_MuEnrichedPt15_pythia_F10_cff")
elif(isSingletopS):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_TToBLNu_TuneZ2_s_channel_7TeV_madgraph_cff")
elif(isSingletopT):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_TToBLNu_TuneZ2_t_channel_7TeV_madgraph_cff")
elif(isSingletopTw):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_TToBLNu_madgraph_F10_cff")
elif(isTtbar):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_TTJets_D6T_madgraph_F10_cff")
elif(isWmunu):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_WToMuNu_pythia_F10_cff")
elif(isWtaunu):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_WToTauNu_pythia_F10_cff")
elif(isZmumu):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_DYJetsToLL_M50_madgraph_F10_cff")
elif(isZmumuB):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_DYJetsToLL_M50_madgraph_F10_cff")
elif(isZmumuUdsc):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_DYJetsToLL_M50_madgraph_F10_cff")
elif(isZtautau):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_DYJetsToLL_M50_madgraph_F10_cff")
elif(isWw):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_WWTo2L2Nu_pythia_F10_cff")
elif(isWz):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_WZTo3LNu_pythia_F10_cff")
elif(isZz):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_ZZToAnything_pythia_F10_cff")
elif(isTest):
    process.load("ZmumuAnalysis.Configuration.samples.testSample_cff")
else: print "Error, wrong configuration of samples"; raise KeyError("ERROR")



##
## define maximal number of events to loop over
##
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2001)
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
if(isData): process.GlobalTag.globaltag = 'FT_R_311_V4A::All'
elif(isMC): process.GlobalTag.globaltag = 'START41_V0::All'
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
process.DiMuonAnalyzerStepZVetoLow7a = process.DiMuonAnalyzerStep7.clone(diMuonSource = "finalDimuonsZVetoLow",)
process.DiMuonAnalyzerStepZVetoLow7b = process.DiMuonAnalyzerStep7.clone(diMuonSource = "finalDimuonsZVetoLow",)
process.DiMuonAnalyzerStepZVetoLow7c = process.DiMuonAnalyzerStep7.clone(diMuonSource = "finalDimuonsZVetoLow",)
process.DiMuonAnalyzerStepZVetoLow7 = process.DiMuonAnalyzerStep7.clone(diMuonSource = "finalDimuonsZVetoLow",)
process.DiMuonAnalyzerStepZVetoHigh3f = process.DiMuonAnalyzerStep3f.clone(diMuonSource = "finalDimuonsZVetoHigh",)
process.DiMuonAnalyzerStepZVetoHigh4 = process.DiMuonAnalyzerStep4.clone(diMuonSource = "finalDimuonsZVetoHigh",)
process.DiMuonAnalyzerStepZVetoHigh5 = process.DiMuonAnalyzerStep5.clone(diMuonSource = "finalDimuonsZVetoHigh",)
process.DiMuonAnalyzerStepZVetoHigh6 = process.DiMuonAnalyzerStep6.clone(diMuonSource = "finalDimuonsZVetoHigh",)
process.DiMuonAnalyzerStepZVetoHigh7a = process.DiMuonAnalyzerStep7.clone(diMuonSource = "finalDimuonsZVetoHigh",)
process.DiMuonAnalyzerStepZVetoHigh7b = process.DiMuonAnalyzerStep7.clone(diMuonSource = "finalDimuonsZVetoHigh",)
process.DiMuonAnalyzerStepZVetoHigh7c = process.DiMuonAnalyzerStep7.clone(diMuonSource = "finalDimuonsZVetoHigh",)
process.DiMuonAnalyzerStepZVetoHigh7 = process.DiMuonAnalyzerStep7.clone(diMuonSource = "finalDimuonsZVetoHigh",)



## jet analyzer
process.load("ZmumuAnalysis.Analyzer.JetAnalyzer_cfi")
process.JetAnalyzerStep4a = process.JetAnalyzer.clone(jetSource = 'selectedPatJetsAK5PF',)
process.JetAnalyzerStep4b = process.JetAnalyzer.clone(jetSource = 'cleanPatJets',)
process.JetAnalyzerStep4c = process.JetAnalyzer.clone(jetSource = 'cleanJets',)
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

process.JetAnalyzerStepZVetoLow4d = process.JetAnalyzerStep4d.clone()
process.JetAnalyzerStepZVetoLow4 = process.JetAnalyzerStep4.clone()
process.JetAnalyzerStepZVetoLow5J = process.JetAnalyzerStep5J.clone()
process.JetAnalyzerStepZVetoLow5Bhe = process.JetAnalyzerStep5Bhe.clone()
process.JetAnalyzerStepZVetoLow5Bhp = process.JetAnalyzerStep5Bhp.clone()
process.JetAnalyzerStepZVetoLow6J = process.JetAnalyzerStep6J.clone()
process.JetAnalyzerStepZVetoLow6Bhe = process.JetAnalyzerStep6Bhe.clone()
process.JetAnalyzerStepZVetoLow6Bhp = process.JetAnalyzerStep6Bhp.clone()
process.JetAnalyzerStepZVetoLow7aJ = process.JetAnalyzerStep7aJ.clone()
process.JetAnalyzerStepZVetoLow7aBhe = process.JetAnalyzerStep7aBhe.clone()
process.JetAnalyzerStepZVetoLow7aBhp = process.JetAnalyzerStep7aBhp.clone()
process.JetAnalyzerStepZVetoLow7bJ = process.JetAnalyzerStep7bJ.clone()
process.JetAnalyzerStepZVetoLow7bBhe = process.JetAnalyzerStep7bBhe.clone()
process.JetAnalyzerStepZVetoLow7bBhp = process.JetAnalyzerStep7bBhp.clone()
process.JetAnalyzerStepZVetoLow7cJ = process.JetAnalyzerStep7cJ.clone()
process.JetAnalyzerStepZVetoLow7cBhe = process.JetAnalyzerStep7cBhe.clone()
process.JetAnalyzerStepZVetoLow7cBhp = process.JetAnalyzerStep7cBhp.clone()
process.JetAnalyzerStepZVetoLow7J = process.JetAnalyzerStep7J.clone()
process.JetAnalyzerStepZVetoLow7Bhe = process.JetAnalyzerStep7Bhe.clone()
process.JetAnalyzerStepZVetoLow7Bhp = process.JetAnalyzerStep7Bhp.clone()
process.JetAnalyzerStepZVetoHigh4d = process.JetAnalyzerStep4d.clone()
process.JetAnalyzerStepZVetoHigh4 = process.JetAnalyzerStep4.clone()
process.JetAnalyzerStepZVetoHigh5J = process.JetAnalyzerStep5J.clone()
process.JetAnalyzerStepZVetoHigh5Bhe = process.JetAnalyzerStep5Bhe.clone()
process.JetAnalyzerStepZVetoHigh5Bhp = process.JetAnalyzerStep5Bhp.clone()
process.JetAnalyzerStepZVetoHigh6J = process.JetAnalyzerStep6J.clone()
process.JetAnalyzerStepZVetoHigh6Bhe = process.JetAnalyzerStep6Bhe.clone()
process.JetAnalyzerStepZVetoHigh6Bhp = process.JetAnalyzerStep6Bhp.clone()
process.JetAnalyzerStepZVetoHigh7aJ = process.JetAnalyzerStep7aJ.clone()
process.JetAnalyzerStepZVetoHigh7aBhe = process.JetAnalyzerStep7aBhe.clone()
process.JetAnalyzerStepZVetoHigh7aBhp = process.JetAnalyzerStep7aBhp.clone()
process.JetAnalyzerStepZVetoHigh7bJ = process.JetAnalyzerStep7bJ.clone()
process.JetAnalyzerStepZVetoHigh7bBhe = process.JetAnalyzerStep7bBhe.clone()
process.JetAnalyzerStepZVetoHigh7bBhp = process.JetAnalyzerStep7bBhp.clone()
process.JetAnalyzerStepZVetoHigh7cJ = process.JetAnalyzerStep7cJ.clone()
process.JetAnalyzerStepZVetoHigh7cBhe = process.JetAnalyzerStep7cBhe.clone()
process.JetAnalyzerStepZVetoHigh7cBhp = process.JetAnalyzerStep7cBhp.clone()
process.JetAnalyzerStepZVetoHigh7J = process.JetAnalyzerStep7J.clone()
process.JetAnalyzerStepZVetoHigh7Bhe = process.JetAnalyzerStep7Bhe.clone()
process.JetAnalyzerStepZVetoHigh7Bhp = process.JetAnalyzerStep7Bhp.clone()



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



#******************************************************************************************
#   Analysis Path
#******************************************************************************************


# Additional statements for use with trigger REDIGI

if(isData): TRIG_RESULT = "HLT"
elif(isMC): TRIG_RESULT = "REDIGI311X"
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





#******************************************************************************************
#   Analysis Path
#******************************************************************************************



process.oppositeChargeAnalysis = cms.Path(
    process.step0
    
    
    *process.seqGeneratorFilter
    *process.step1a
    
    *process.TriggerFilter
    *process.buildVertexCollections
    *process.step1b
    
    *process.oneGoodPVSelection
    *process.step1
    
    
    *process.buildMuonCollections
    *process.step2a
    
    *process.oneInitialMuonSelection
    *process.step2b
    
    *process.oneLooseMuonSelection
    *process.step2c
    
    *process.oneTightMuonSelection
    *process.step2d
    
    *process.looseMuonSelection
    *process.step2e
    
    *process.tightMuonSelection
    *process.step2f
    
    *process.tightHltMuonSelection
    *process.step2
    
    
    *process.buildDimuonCollections
    *process.step3a
    
    *process.selectedDimuonSelection
    *process.step3b
    
    *process.cleanDimuonSelection
    *process.step3c
    
    *process.goodDimuonSelection
    *process.step3d
    
    *process.isolatedDimuonSelection
    *process.step3e
    
    *process.finalDimuonSelection
    *process.step3f
    *process.step3
    
    
    *process.buildJetCollections
    *process.step4a
    
    *process.oneCleanPatJetSelection
    *process.step4b
    
    *process.oneCleanJetSelection
    *process.step4c
    
    *process.oneGoodJetSelection
    *process.step4d
    
    *process.oneFinalJetSelection
    *process.step4
    
    
    *process.oneBSsvHeMJetSelection
    *process.step5
    
    
    *process.buildMetCollections
    *process.step6a
    
    *process.goodMetSelection
    *process.step6
    
    
    *process.oneBSsvHpTJetSelection
    *process.step7a
    
    *process.twoFinalJetSelection
    *process.step7b
    
    *process.twoBSsvHeMJetSelection
    *process.step7c
    
    *process.twoBSsvHpTJetSelection
    *process.step7
    
)




process.ZVetoLowOppositeChargeAnalysis = cms.Path(
    process.stepZVetoLow0
    
    
    *process.seqGeneratorFilter
    *process.stepZVetoLow1a
    
    *process.TriggerFilter
    *process.buildVertexCollections
    *process.stepZVetoLow1b
    
    *process.oneGoodPVSelection
    *process.stepZVetoLow1
    
    
    *process.buildMuonCollections
    *process.stepZVetoLow2a
    
    *process.oneInitialMuonSelection
    *process.stepZVetoLow2b
    
    *process.oneLooseMuonSelection
    *process.stepZVetoLow2c
    
    *process.oneTightMuonSelection
    *process.stepZVetoLow2d
    
    *process.looseMuonSelection
    *process.stepZVetoLow2e
    
    *process.tightMuonSelection
    *process.stepZVetoLow2f
    
    *process.tightHltMuonSelection
    *process.stepZVetoLow2
    
    
    *process.buildDimuonZVetoLowCollections
    *process.stepZVetoLow3a
    
    *process.selectedDimuonSelection
    *process.stepZVetoLow3b
    
    *process.cleanDimuonSelection
    *process.stepZVetoLow3c
    
    *process.goodDimuonSelection
    *process.stepZVetoLow3d
    
    *process.isolatedDimuonSelection
    *process.stepZVetoLow3e
    
    *process.finalDimuonZVetoLowSelection
    *process.stepZVetoLow3f
    *process.stepZVetoLow3
    
    
    *process.buildJetCollections
    *process.stepZVetoLow4a
    
    *process.oneCleanPatJetSelection
    *process.stepZVetoLow4b
    
    *process.oneCleanJetSelection
    *process.stepZVetoLow4c
    
    *process.oneGoodJetSelection
    *process.stepZVetoLow4d
    
    *process.oneFinalJetSelection
    *process.stepZVetoLow4
    
    
    *process.oneBSsvHeMJetSelection
    *process.stepZVetoLow5
    
    
    *process.buildMetCollections
    *process.stepZVetoLow6a
    
    *process.goodMetSelection
    *process.stepZVetoLow6
    
    
    *process.oneBSsvHpTJetSelection
    *process.stepZVetoLow7a
    
    *process.twoFinalJetSelection
    *process.stepZVetoLow7b
    
    *process.twoBSsvHeMJetSelection
    *process.stepZVetoLow7c
    
    *process.twoBSsvHpTJetSelection
    *process.stepZVetoLow7
    
)



process.ZVetoHighOppositeChargeAnalysis = cms.Path(
    process.stepZVetoHigh0
    
    
    *process.seqGeneratorFilter
    *process.stepZVetoHigh1a
    
    *process.TriggerFilter
    *process.buildVertexCollections
    *process.stepZVetoHigh1b
    
    *process.oneGoodPVSelection
    *process.stepZVetoHigh1
    
    
    *process.buildMuonCollections
    *process.stepZVetoHigh2a
    
    *process.oneInitialMuonSelection
    *process.stepZVetoHigh2b
    
    *process.oneLooseMuonSelection
    *process.stepZVetoHigh2c
    
    *process.oneTightMuonSelection
    *process.stepZVetoHigh2d
    
    *process.looseMuonSelection
    *process.stepZVetoHigh2e
    
    *process.tightMuonSelection
    *process.stepZVetoHigh2f
    
    *process.tightHltMuonSelection
    *process.stepZVetoHigh2
    
    
    *process.buildDimuonZVetoHighCollections
    *process.stepZVetoHigh3a
    
    *process.selectedDimuonSelection
    *process.stepZVetoHigh3b
    
    *process.cleanDimuonSelection
    *process.stepZVetoHigh3c
    
    *process.goodDimuonSelection
    *process.stepZVetoHigh3d
    
    *process.isolatedDimuonSelection
    *process.stepZVetoHigh3e
    
    *process.finalDimuonZVetoHighSelection
    *process.stepZVetoHigh3f
    *process.stepZVetoHigh3
    
    
    *process.buildJetCollections
    *process.stepZVetoHigh4a
    
    *process.oneCleanPatJetSelection
    *process.stepZVetoHigh4b
    
    *process.oneCleanJetSelection
    *process.stepZVetoHigh4c
    
    *process.oneGoodJetSelection
    *process.stepZVetoHigh4d
    
    *process.oneFinalJetSelection
    *process.stepZVetoHigh4
    
    
    *process.oneBSsvHeMJetSelection
    *process.stepZVetoHigh5
    
    
    *process.buildMetCollections
    *process.stepZVetoHigh6a
    
    *process.goodMetSelection
    *process.stepZVetoHigh6
    
    
    *process.oneBSsvHpTJetSelection
    *process.stepZVetoHigh7a
    
    *process.twoFinalJetSelection
    *process.stepZVetoHigh7b
    
    *process.twoBSsvHeMJetSelection
    *process.stepZVetoHigh7c
    
    *process.twoBSsvHpTJetSelection
    *process.stepZVetoHigh7
    
)










