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
isData2 = True
isData3 = False
# MC samples
isQcd = False
isSingleTopS = False
isSingleTopTw = False
isSingleTopT = False
isTtbar = False
isWmunu = False
isWtaunu = False
isZmumu = False
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
if(isSingleTopTw): counter += 1; isMC = True
if(isSingleTopT): counter += 1; isMC = True
if(isTtbar): counter += 1; isMC = True
if(isWmunu): counter += 1; isMC = True
if(isWtaunu): counter += 1; isMC = True
if(isZmumu): counter += 1; isMC = True
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
elif(isQcd): # OLD
    process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.QCD_MuEnrichedPt15_pythia_F10_cff")
elif(isSingleTopS):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_TToBLNu_TuneZ2_s_channel_7TeV_madgraph_cff")
elif(isSingleTopTw):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_TToBLNu_TuneZ2_t_channel_7TeV_madgraph_cff")
elif(isSingleTopT):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_TToBLNu_madgraph_F10_cff")
elif(isTtbar):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSpring11.samples.Spring11_TTJets_D6T_madgraph_F10_cff")
elif(isWmunu):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.Spring11_WToMuNu_pythia_F10_cff")
elif(isWtaunu):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndFall10.samples.Spring11_WToTauNu_pythia_F10_cff")
elif(isZmumu):
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
elif(isSingleTopTw): fileName = 'mc/singleTopTw.root'
elif(isSingleTopT): fileName = 'mc/singleTopT.root'
elif(isTtbar): fileName = 'mc/ttbar.root'
elif(isWmunu): fileName = 'mc/wmunu.root'
elif(isWtaunu): fileName = 'mc/wtaunu.root'
elif(isZmumu): fileName = 'mc/zmumu.root'
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



## vertex analyzer
process.load("ZmumuAnalysis.Analyzer.VertexAnalyzer_cfi")
process.VertexAnalyzer1 = process.VertexAnalyzer.clone(
    #vertexSource = 'offlinePrimaryVertices',
)
process.VertexAnalyzer2 = process.VertexAnalyzer.clone(
    vertexSource = 'goodPVs',
)
process.VertexAnalyzer6 = process.VertexAnalyzer.clone(
    vertexSource = 'finalPVs',
)
process.VertexAnalyzer6a = process.VertexAnalyzer.clone(
    vertexSource = 'bestPV',
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
process.DiMuonAnalyzer6a = process.DiMuonAnalyzer.clone(
    diMuonSource = "bestDimuon",
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
process.JetAnalyzer7a = process.JetAnalyzer.clone(
    jetSource = 'selectedPatJetsAK5PF',
)
process.JetAnalyzer7b = process.JetAnalyzer.clone(
    jetSource = 'cleanPatJets',
)
process.JetAnalyzer7c = process.JetAnalyzer.clone(
    jetSource = 'cleanJets',
)
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
#   Utils Modules
#******************************************************************************************

process.load("ZmumuAnalysis.Utils.RunEventListing_cff")
process.RunEventListing6 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListing9 = process.RunEventListingCreateTreeOnly.clone()
process.RunEventListing10 = process.RunEventListingCreateTreeOnly.clone()


#******************************************************************************************
#   Analysis Path
#******************************************************************************************


# Additional statements for use with trigger REDIGI

if(isData): TRIG_RESULT = "HLT"
elif(isMC): TRIG_RESULT = "REDIGI311X"
else: print "Error, wrong configuration of samples"; raise KeyError("ERROR")

# Does this work for all files? - No, al least not for TriggerFilter
#TRIG_RESULT = "PAT"

process.TriggerAnalyzer1.triggerResults = cms.InputTag('TriggerResults','',TRIG_RESULT)
process.TriggerFilter.TriggerResultsTag = cms.InputTag('TriggerResults','',TRIG_RESULT)
process.patTrigger.processName = TRIG_RESULT
process.patTrigger.triggerResults = cms.InputTag("TriggerResults::" + TRIG_RESULT)
process.patTrigger.triggerEvent = cms.InputTag("hltTriggerSummaryAOD::" + TRIG_RESULT)



#******************************************************************************************
#   Sequences
#******************************************************************************************

## Apply generator filters here
process.seqGeneratorFilter = cms.Sequence()
if(isZmumu): process.seqGeneratorFilter *= process.GeneratorZmumuFilter
if(isZtautau): process.seqGeneratorFilter *= process.GeneratorZtautauFilter





#******************************************************************************************
#   Analysis Path
#******************************************************************************************



process.oppositeChargeAnalysis = cms.Path(
    process.EventCounter0
    
    *process.seqGeneratorFilter
    
    *process.buildVertexCollections
    *process.VertexAnalyzer1
    *process.vertexSelection
    *process.VertexAnalyzer2
    
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
    *process.VertexAnalyzer6
    *process.DiMuonAnalyzer6a
    *process.VertexAnalyzer6a
    *process.RunEventListing6
    
    *process.buildJetCollections
    *process.JetAnalyzer7a
    *process.JetAnalyzer7b
    *process.JetAnalyzer7c
    *process.JetAnalyzer7
    *process.JetAnalyzer8
    *process.oneJetSelection
    *process.MuonAnalyzer9
    *process.DiMuonAnalyzer9
    *process.JetAnalyzer9
    *process.RunEventListing9
    
    *process.buildMetCollections
    *process.MetAnalyzer9
    *process.metSelection
    *process.MuonAnalyzer10
    *process.DiMuonAnalyzer10
    *process.JetAnalyzer10
    #*process.MetAnalyzer10
    *process.RunEventListing10
    
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



