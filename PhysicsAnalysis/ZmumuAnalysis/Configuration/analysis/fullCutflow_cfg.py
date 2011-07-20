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
if(isData1): fileName = 'run2011A_May10ReRecoV1_160404_163869.root'  # 'data/run2011A_May10ReRecoV1_160404_163869.root'
elif(isData2): fileName = 'run2011A_PromptRecoV4_163870_167784.root'  # 'data/run2011A_PromptRecoV4_163870_167784.root'
elif(isData3): fileName = ''  # 'data/'
# MC
elif(isQcd): fileName = 'qcd.root'  # 'mc/qcd.root'
elif(isSingletopS): fileName = 'singletopS.root'  # 'mc/singletopS.root'
elif(isSingletopT): fileName = 'singletopT.root'  # 'mc/singletopT.root'
elif(isSingletopTw): fileName = 'singletopTw.root'  # 'mc/singletopTw.root'
elif(isTtbar): fileName = 'ttbar.root'  # 'mc/ttbar.root'
elif(isWmunu): fileName = 'wmunu.root'  # 'mc/wmunu.root'
elif(isWtaunu): fileName = 'wtaunu.root'  # 'mc/wtaunu.root'
elif(isZmumu): fileName = 'zmumu.root'  # 'mc/zmumu.root'
elif(isZmumuB): fileName = 'zmumuB.root'  # 'mc/zmumuB.root'
elif(isZmumuUdsc): fileName = 'zmumuUdsc.root'  # 'mc/zmumuUdsc.root'
elif(isZtautau): fileName = 'ztautau.root'  # 'mc/ztautau.root'
elif(isWw): fileName = 'ww.root'  # 'mc/ww.root'
elif(isWz): fileName = 'wz.root'  # 'mc/wz.root'
elif(isZz): fileName = 'zz.root'  # 'mc/zz.root'
elif(isTest): fileName = 'fullSelection.root'
else: print "Error, wrong configuration of samples"; raise KeyError("ERROR")
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(fileBase + fileName),
    closeFileFast = cms.untracked.bool(True)
)







#******************************************************************************************
#   The selection steps
#******************************************************************************************

process.load("ZmumuAnalysis.Configuration.sequences.selectionSteps_cff")





#******************************************************************************************
#   Trigger setup
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
# Generator Filter Sequences
#******************************************************************************************

## Apply generator filters here
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





#******************************************************************************************
#   Analysis Path
#******************************************************************************************



process.oppositeChargeAnalysis = cms.Path(
    process.oppositeChargeAnalysisSeq
)

process.ZVetoLowOppositeChargeAnalysis = cms.Path(
    process.ZVetoLowOppositeChargeAnalysisSeq
)

process.ZVetoHighOppositeChargeAnalysis = cms.Path(
    process.ZVetoHighOppositeChargeAnalysisSeq
)

process.noMetOppositeChargeAnalysis = cms.Path(
    process.noMetOppositeChargeAnalysisSeq
)

process.ZVetoLowNoMetOppositeChargeAnalysis = cms.Path(
    process.ZVetoLowNoMetOppositeChargeAnalysisSeq
)

process.ZVetoHighNoMetOppositeChargeAnalysis = cms.Path(
    process.ZVetoHighNoMetOppositeChargeAnalysisSeq
)










