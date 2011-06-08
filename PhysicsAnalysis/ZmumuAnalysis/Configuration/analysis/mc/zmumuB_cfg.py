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
isSingleTopS = False
isSingleTopT = False
isSingleTopTw = False
isTtbar = False
isWmunu = False
isWtaunu = False
isZmumu = False
isZmumuB = True
isZmumuUdsc = False
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
if(isSingleTopS): counter += 1; isMC = True
if(isSingleTopT): counter += 1; isMC = True
if(isSingleTopTw): counter += 1; isMC = True
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
elif(isSingleTopS):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_TToBLNu_TuneZ2_s_channel_7TeV_madgraph_cff")
elif(isSingleTopT):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_TToBLNu_TuneZ2_t_channel_7TeV_madgraph_cff")
elif(isSingleTopTw):
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
elif(isSingleTopS): fileName = 'mc/singleTopS.root'
elif(isSingleTopT): fileName = 'mc/singleTopT.root'
elif(isSingleTopTw): fileName = 'mc/singleTopTw.root'
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



## trigger analyzer
process.load("ZmumuAnalysis.Analyzer.TriggerAnalyzer_cfi")
process.TriggerAnalyzerStep1a =  process.TriggerAnalyzer.clone(
    #triggerResults = cms.InputTag('TriggerResults','','HLT'),
    #triggerResults = cms.InputTag('TriggerResults','','REDIGI38X'),
)



## vertex analyzer
process.load("ZmumuAnalysis.Analyzer.VertexAnalyzer_cfi")
process.VertexAnalyzerStep1b = process.VertexAnalyzer.clone(
    #vertexSource = 'offlinePrimaryVertices',
)
process.VertexAnalyzerStep1 = process.VertexAnalyzer.clone(
    vertexSource = 'goodPVs',
)
process.VertexAnalyzerStep3f = process.VertexAnalyzer.clone(
    vertexSource = 'finalPVs',
)
process.VertexAnalyzerStep3 = process.VertexAnalyzer.clone(
    vertexSource = 'bestPV',
)

process.VertexAnalyzerStepZVeto3f = process.VertexAnalyzerStep3f.clone(
    vertexSource = 'finalPVsZVeto',
)



## muon analizer
process.load("ZmumuAnalysis.Analyzer.MuonAnalyzer_cfi")
process.MuonAnalyzerStep2b = process.MuonAnalyzer.clone(
    muonSource = 'tightMuons',
)
process.MuonAnalyzerStep2 = process.MuonAnalyzer.clone(
    muonSource = 'tightMuons',
)
process.MuonAnalyzerStep3 = process.MuonAnalyzer.clone(
    muonSource = 'tightMuons',
)
process.MuonAnalyzerStep5 = process.MuonAnalyzer.clone(
    muonSource = 'tightMuons',
)
process.MuonAnalyzerStep6 = process.MuonAnalyzer.clone(
    muonSource = 'tightMuons',
)

process.MuonAnalyzerStepZVeto3 = process.MuonAnalyzerStep3.clone()
process.MuonAnalyzerStepZVeto5 = process.MuonAnalyzerStep5.clone()
process.MuonAnalyzerStepZVeto6 = process.MuonAnalyzerStep6.clone()

process.MuonAnalyzerStepSC3 = process.MuonAnalyzerStep3.clone(
)
process.MuonAnalyzerStepSC5 = process.MuonAnalyzerStep5.clone(
)



## di-muon analyzer
process.load("ZmumuAnalysis.Analyzer.DiMuonAnalyzer_cfi")
process.DiMuonAnalyzerStep3d = process.DiMuonAnalyzer.clone(
    diMuonSource = "goodDimuons",
)
process.DiMuonAnalyzerStep3e = process.DiMuonAnalyzer.clone(
    diMuonSource = "isolatedDimuons",
)
process.DiMuonAnalyzerStep3f = process.DiMuonAnalyzer.clone(
    diMuonSource = "finalDimuons",
)
process.DiMuonAnalyzerStep3 = process.DiMuonAnalyzer.clone(
    diMuonSource = "bestDimuon",
)
process.DiMuonAnalyzerStep5 = process.DiMuonAnalyzer.clone(
    diMuonSource = "finalDimuons",
)
process.DiMuonAnalyzerStep6 = process.DiMuonAnalyzer.clone(
    diMuonSource = "finalDimuons",
)

process.DiMuonAnalyzerStepZVeto3f = process.DiMuonAnalyzerStep3f.clone(
    diMuonSource = "finalDimuonsZVeto",
)
process.DiMuonAnalyzerStepZVeto5 = process.DiMuonAnalyzerStep5.clone(
    diMuonSource = "finalDimuonsZVeto",
)
process.DiMuonAnalyzerStepZVeto6 = process.DiMuonAnalyzerStep6.clone(
    diMuonSource = "finalDimuonsZVeto",
)

process.DiMuonAnalyzerStepSC3d = process.DiMuonAnalyzerStep3d.clone(
    diMuonSource = "goodDimuonsSC",
)
process.DiMuonAnalyzerStepSC3e = process.DiMuonAnalyzerStep3e.clone(
    diMuonSource = "isolatedDimuonsSC",
)
process.DiMuonAnalyzerStepSC3f = process.DiMuonAnalyzerStep3f.clone(
    diMuonSource = "finalDimuonsSC",
)
process.DiMuonAnalyzerStepSC5 = process.DiMuonAnalyzerStep5.clone(
    diMuonSource = "finalDimuonsSC",
)



## jet analyzer
process.load("ZmumuAnalysis.Analyzer.JetAnalyzer_cfi")
process.JetAnalyzerStep4a = process.JetAnalyzer.clone(
    jetSource = 'selectedPatJetsAK5PF',
)
process.JetAnalyzerStep4b = process.JetAnalyzer.clone(
    jetSource = 'cleanPatJets',
)
process.JetAnalyzerStep4c = process.JetAnalyzer.clone(
    jetSource = 'cleanJets',
)
process.JetAnalyzerStep4d = process.JetAnalyzer.clone(
    jetSource = 'goodJets',
)
process.JetAnalyzerStep4 = process.JetAnalyzer.clone(
    jetSource = 'finalJets',
)
process.JetAnalyzerStep5 = process.JetAnalyzer.clone(
    jetSource = 'bSsvHeMJets',
)
process.JetAnalyzerStep6 = process.JetAnalyzer.clone(
    jetSource = 'bSsvHeMJets',
)

process.JetAnalyzerStepZVeto4d = process.JetAnalyzerStep4d.clone()
process.JetAnalyzerStepZVeto4 = process.JetAnalyzerStep4.clone()
process.JetAnalyzerStepZVeto5 = process.JetAnalyzerStep5.clone()
process.JetAnalyzerStepZVeto6 = process.JetAnalyzerStep6.clone()



## missing et analyzer
process.load("ZmumuAnalysis.Analyzer.MetAnalyzer_cfi")
process.MetAnalyzerStep6a = process.MetAnalyzer.clone(
    metSource = 'patMETsPF',
)

process.MetAnalyzerStepZVeto6a = process.MetAnalyzerStep6a.clone()

process.MetAnalyzerStepSC6a = process.MetAnalyzerStep6a.clone()




#******************************************************************************************
#   Utils Modules
#******************************************************************************************

process.load("ZmumuAnalysis.Utils.RunEventListing_cff")
process.RunEventListingStep3 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListingStep5 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListingStep6 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListingStep7 = process.RunEventListingCreateTreeOnly.clone()

process.RunEventListingStepZVeto3 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListingStepZVeto5 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListingStepZVeto6 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListingStepZVeto7 = process.RunEventListingCreateTreeOnly.clone()



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
    process.EventCounterStep1a*
    process.TriggerAnalyzerStep1a
)
process.step1b = cms.Sequence(
    process.VertexAnalyzerStep1b
)
process.step1 = cms.Sequence(
    process.VertexAnalyzerStep1
)

process.step2a = cms.Sequence(
)
process.step2b = cms.Sequence(
    process.MuonAnalyzerStep2b
)
process.step2c = cms.Sequence(
)
process.step2d = cms.Sequence(
)
process.step2e = cms.Sequence(
)
process.step2f = cms.Sequence(
)
process.step2 = cms.Sequence(
    process.MuonAnalyzerStep2
)

process.step3a = cms.Sequence(
)
process.step3b = cms.Sequence(
)
process.step3c = cms.Sequence(
)
process.step3d = cms.Sequence(
    process.DiMuonAnalyzerStep3d
)
process.step3e = cms.Sequence(
    process.DiMuonAnalyzerStep3e
)
process.step3f = cms.Sequence(
    process.VertexAnalyzerStep3f*
    process.DiMuonAnalyzerStep3f
)
process.step3 = cms.Sequence(
    process.VertexAnalyzerStep3*
    process.MuonAnalyzerStep3*
    process.DiMuonAnalyzerStep3*
    process.RunEventListingStep3
)

process.step4a = cms.Sequence(
    process.JetAnalyzerStep4a
)
process.step4b = cms.Sequence(
    process.JetAnalyzerStep4b
)
process.step4c = cms.Sequence(
    process.JetAnalyzerStep4c
)
process.step4d = cms.Sequence(
    process.JetAnalyzerStep4d
)
process.step4 = cms.Sequence(
    process.JetAnalyzerStep4
)

process.step5 = cms.Sequence(
    process.MuonAnalyzerStep5*
    process.DiMuonAnalyzerStep5*
    process.JetAnalyzerStep5*
    process.RunEventListingStep5
)

process.step6a = cms.Sequence(
    process.MetAnalyzerStep6a
)
process.step6 = cms.Sequence(
    process.MuonAnalyzerStep6*
    process.DiMuonAnalyzerStep6*
    process.JetAnalyzerStep6*
    process.RunEventListingStep6
)


process.step7a = cms.Sequence(
)
process.step7b = cms.Sequence(
)
process.step7c = cms.Sequence(
)
process.step7 = cms.Sequence(
    process.RunEventListingStep7
)



## Define steps and corresponding analyzers for analysis excluding the Z mass window
process.stepZVeto0 = cms.Sequence(
)

process.stepZVeto1a = cms.Sequence(
)
process.stepZVeto1b = cms.Sequence(
)
process.stepZVeto1 = cms.Sequence(
)

process.stepZVeto2a = cms.Sequence(
)
process.stepZVeto2b = cms.Sequence(
)
process.stepZVeto2c = cms.Sequence(
)
process.stepZVeto2d = cms.Sequence(
)
process.stepZVeto2e = cms.Sequence(
)
process.stepZVeto2f = cms.Sequence(
)
process.stepZVeto2 = cms.Sequence(
)

process.stepZVeto3a = cms.Sequence(
)
process.stepZVeto3b = cms.Sequence(
)
process.stepZVeto3c = cms.Sequence(
)
process.stepZVeto3d = cms.Sequence(
)
process.stepZVeto3e = cms.Sequence(
)
process.stepZVeto3f = cms.Sequence(
    process.VertexAnalyzerStepZVeto3f*
    process.DiMuonAnalyzerStepZVeto3f
)
process.stepZVeto3 = cms.Sequence(
    #process.VertexAnalyzerStepZVeto3*
    process.MuonAnalyzerStepZVeto3*
    #process.DiMuonAnalyzerStepZVeto3*
    process.RunEventListingStepZVeto3
)

process.stepZVeto4a = cms.Sequence(
)
process.stepZVeto4b = cms.Sequence(
)
process.stepZVeto4c = cms.Sequence(
)
process.stepZVeto4d = cms.Sequence(
    process.JetAnalyzerStepZVeto4d
)
process.stepZVeto4 = cms.Sequence(
    process.JetAnalyzerStepZVeto4
)

process.stepZVeto5 = cms.Sequence(
    process.MuonAnalyzerStepZVeto5*
    process.DiMuonAnalyzerStepZVeto5*
    process.JetAnalyzerStepZVeto5*
    process.RunEventListingStepZVeto5
)

process.stepZVeto6a = cms.Sequence(
    process.MetAnalyzerStepZVeto6a
)
process.stepZVeto6 = cms.Sequence(
    process.MuonAnalyzerStepZVeto6*
    process.DiMuonAnalyzerStepZVeto6*
    process.JetAnalyzerStepZVeto6*
    process.RunEventListingStepZVeto6
)


process.stepZVeto7a = cms.Sequence(
)
process.stepZVeto7b = cms.Sequence(
)
process.stepZVeto7c = cms.Sequence(
)
process.stepZVeto7 = cms.Sequence(
    process.RunEventListingStepZVeto7
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




process.zVetoOppositeChargeAnalysis = cms.Path(
    process.stepZVeto0
    
    
    *process.seqGeneratorFilter
    *process.stepZVeto1a
    
    *process.TriggerFilter
    *process.buildVertexCollections
    *process.stepZVeto1b
    
    *process.oneGoodPVSelection
    *process.stepZVeto1
    
    
    *process.buildMuonCollections
    *process.stepZVeto2a
    
    *process.oneInitialMuonSelection
    *process.stepZVeto2b
    
    *process.oneLooseMuonSelection
    *process.stepZVeto2c
    
    *process.oneTightMuonSelection
    *process.stepZVeto2d
    
    *process.looseMuonSelection
    *process.stepZVeto2e
    
    *process.tightMuonSelection
    *process.stepZVeto2f
    
    *process.tightHltMuonSelection
    *process.stepZVeto2
    
    
    *process.buildDimuonZVetoCollections
    *process.stepZVeto3a
    
    *process.selectedDimuonSelection
    *process.stepZVeto3b
    
    *process.cleanDimuonSelection
    *process.stepZVeto3c
    
    *process.goodDimuonSelection
    *process.stepZVeto3d
    
    *process.isolatedDimuonSelection
    *process.stepZVeto3e
    
    *process.finalDimuonZVetoSelection
    *process.stepZVeto3f
    *process.stepZVeto3
    
    
    *process.buildJetCollections
    *process.stepZVeto4a
    
    *process.oneCleanPatJetSelection
    *process.stepZVeto4b
    
    *process.oneCleanJetSelection
    *process.stepZVeto4c
    
    *process.oneGoodJetSelection
    *process.stepZVeto4d
    
    *process.oneFinalJetSelection
    *process.stepZVeto4
    
    
    *process.oneBSsvHeMJetSelection
    *process.stepZVeto5
    
    
    *process.buildMetCollections
    *process.stepZVeto6a
    
    *process.goodMetSelection
    *process.stepZVeto6
    
    
    *process.oneBSsvHpTJetSelection
    *process.stepZVeto7a
    
    *process.twoFinalJetSelection
    *process.stepZVeto7b
    
    *process.twoBSsvHeMJetSelection
    *process.stepZVeto7c
    
    *process.twoBSsvHpTJetSelection
    *process.stepZVeto7
    
)




