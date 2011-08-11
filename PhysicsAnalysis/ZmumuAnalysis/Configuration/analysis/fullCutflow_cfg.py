import os

import FWCore.ParameterSet.Config as cms



##
## Setup command line options
##
import FWCore.ParameterSet.VarParsing as VarParsing
import sys
options = VarParsing.VarParsing ('standard')
options.register('sample', 'test', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "Input sample")
options.register('metCut', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool, "Apply MET cut")
options.register('firstBtag', 'HeM', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "Requirement for first b-tag")
options.register('secondBtag', 'HeM', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "Requirement for second b-tag")
options.register('systematics', 'default', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "Default analysis or systematic study")

# get and parse the command line arguments
if( hasattr(sys, "argv") ):
    for args in sys.argv :
        arg = args.split(',')
        for val in arg:
            val = val.split('=')
            if(len(val)==2):
                setattr(options,val[0], val[1])

if options.firstBtag=='HeMExcl'  or options.firstBtag=='HpTExcl': options.secondBtag = ''

print "Input sample: ", options.sample
print "Apply MET cut: ", options.metCut
print "1st b-tag: ", options.firstBtag
print "2nd b-tag: ", options.secondBtag
print "Systematic study: ", options.systematics



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
isMumu1 = isMumu2 = isMumu3 = False
isElel1 = isElel2 = isElel3 = False
isQcd = isSingletopS = isSingletopT = isSingletopTw = isTtbar = isWmunu = isWtaunu = isZmumu = isZmumuB = isZmumuUdsc = isZtautau = isWw = isWz = isZz = False
isTest = False
# Data samples
if options.sample == 'mumu1': isMumu1 = True
elif options.sample == 'mumu2': isMumu2 = True
elif options.sample == 'mumu3': isMumu3 = True
elif options.sample == 'elel1': isElel1 = True
elif options.sample == 'elel2': isElel2 = True
elif options.sample == 'elel3': isElel3 = True
# MC samples
elif options.sample == 'qcd': isQcd = True
elif options.sample == 'singletopS': isSingletopS = True
elif options.sample == 'singletopT': isSingletopT = True
elif options.sample == 'singletopTw': isSingletopTw = True
elif options.sample == 'ttbar': isTtbar = True
elif options.sample == 'wmunu': isWmunu = True
elif options.sample == 'wtaunu': isWtaunu = True
elif options.sample == 'zmumu': isZmumu = True
elif options.sample == 'zmumuB': isZmumuB = True
elif options.sample == 'zmumuUdsc': isZmumuUdsc = True
elif options.sample == 'ztautau': isZtautau = True
elif options.sample == 'ww': isWw = True
elif options.sample == 'wz': isWz = True
elif options.sample == 'zz': isZz = True
elif options.sample == 'test': isTest = True

## Just list here all data and MC samples
counter = 0
isMumu = False
isElel = False
isData = False
isMC = False
# Data
if(isMumu1): counter += 1; isMumu = True
if(isMumu2): counter += 1; isMumu = True
if(isMumu3): counter += 1; isMumu = True
if(isElel1): counter += 1; isElel = True
if(isElel2): counter += 1; isElel = True
if(isElel3): counter += 1; isElel = True
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

if(isMumu or isElel): isData = True

#print counter
if(not counter == 1): print "Error, wrong configuration of samples"; raise KeyError("ERROR")





##
## Sources
##
# Data
if(isMumu1):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSummer11.Run2011A_May10ReReco_v1_425_mumu_Aug05_160404_163869_cff")
elif(isMumu2):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSummer11.Run2011A_PromtReco_v4_425_mumu_Aug05_163870_167784_cff")
elif(isMumu3):
    process.load("")
elif(isElel1):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSummer11.Run2011A_May10ReReco_v1_425_ee_Aug05_160404_163869_cff")
elif(isElel2):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSummer11.Run2011A_PromtReco_v4_425_ee_Aug05_163870_167784_cff")
elif(isElel3):
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
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSummer11.Summer11_TTJets_Z2_madgraph_425_Aug05_cff")
elif(isWmunu):
    process.load("")
elif(isWtaunu):
    process.load("")
elif(isZmumu):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSummer11.Summer11_DYJetsToLL_Z2_madgraph_425_Aug08_cff")
elif(isZmumuB):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSummer11.Summer11_DYJetsToLL_Z2_madgraph_425_Aug08_cff")
elif(isZmumuUdsc):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSummer11.Summer11_DYJetsToLL_Z2_madgraph_425_Aug08_cff")
elif(isZtautau):
    process.load("ZmumuAnalysis.Configuration.samples.dataAndSummer11.Summer11_DYJetsToLL_Z2_madgraph_425_Aug08_cff")
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
if(isData): process.GlobalTag.globaltag = 'GR_R_42_V19::All'
elif(isMC): process.GlobalTag.globaltag = 'START42_V13::All'
else: print "Error, wrong configuration of samples"; raise KeyError("ERROR")



##
## register TFileService
##
fileBase = os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/'
fileName = ''
# Data
if(isMumu1): fileName = 'mumu_run2011A_May10ReRecoV1_160404_163869.root'  # 'data/mumu_run2011A_May10ReRecoV1_160404_163869.root'
elif(isMumu2): fileName = 'mumu_run2011A_PromptRecoV4_163870_167784.root'  # 'data/mumu_run2011A_PromptRecoV4_163870_167784.root'
elif(isMumu3): fileName = ''  # 'data/'
elif(isElel1): fileName = 'elel_run2011A_May10ReRecoV1_160404_163869.root'  # 'data/elel_run2011A_May10ReRecoV1_160404_163869.root'
elif(isElel2): fileName = 'elel_run2011A_PromptRecoV4_163870_167784.root'  # 'data/elel_run2011A_PromptRecoV4_163870_167784.root'
elif(isElel3): fileName = ''  # 'data/'
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


# For now remove vertex association
process.cleanDimuonSelection.minNumber = 0
process.goodDimuons.src = 'selectedDimuons'




#******************************************************************************************
#   Trigger setup
#******************************************************************************************


# Additional statements for use with trigger REDIGI

if(isData): TRIG_RESULT = "HLT"
elif(isMC): TRIG_RESULT = "HLT"
else: print "Error, wrong configuration of samples"; raise KeyError("ERROR")

process.TriggerAnalyzerStep1a.triggerResults = cms.InputTag('TriggerResults','',TRIG_RESULT)
process.TriggerFilter.TriggerResultsTag = cms.InputTag('TriggerResults','',TRIG_RESULT)
process.patTrigger.processName = TRIG_RESULT
process.patTrigger.triggerResults = cms.InputTag("TriggerResults::" + TRIG_RESULT)
process.patTrigger.triggerEvent = cms.InputTag("hltTriggerSummaryAOD::" + TRIG_RESULT)


# Remove trigger selection and muon trigger matching for MC
if isMC:
    process.seqTriggerFilter.remove(process.TriggerFilter)
    process.isolatedHltMuonSelection.minNumber = 0
    process.selectedDimuons.cut = ''



#******************************************************************************************
# Generator Filter Sequences
#******************************************************************************************

## Filter for correct decay process
process.load("ZmumuAnalysis.Configuration.filters.GeneratorZmumuFilter_cff")
process.load("ZmumuAnalysis.Configuration.filters.GeneratorBclFilter_cff")


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
# Dynamic changes for command line parameters
#******************************************************************************************

if options.firstBtag=='HeM':
    process.oneBtagSelection *= process.oneBSsvHeMJetSelection
elif options.firstBtag=='HpT':
    process.oneBtagSelection *= process.oneBSsvHpTJetSelection
elif options.firstBtag=='HeMExcl':
    process.oneBtagSelection *= process.oneBSsvHeMJetSelection * ~process.twoBSsvHeMJetSelection
elif options.firstBtag=='HpTExcl':
    process.oneBtagSelection *= process.oneBSsvHpTJetSelection * ~process.twoBSsvHpTJetSelection
else:
    print 'ERROR --- incorrect b-tag type for first b-tag: ', options.firstBtag, '\nuse \'HeM\', \'HpT\', \'HeMExcl\', \'HpTExcl\''
    exit(8888)


if options.secondBtag=='HeM':
    process.twoBtagSelection *= process.twoBSsvHeMJetSelection
elif options.secondBtag=='HpT':
    process.twoBtagSelection *= process.twoBSsvHpTJetSelection
elif options.secondBtag=='':
    pass
else:
    print 'ERROR --- incorrect b-tag type for second b-tag: ', options.secondBtag, '\nuse \'HeM\', \'HpT\', \'\''
    exit(8888)


if options.metCut:
    process.metSelection *= process.goodMetSelection



if options.secondBtag != '':
    process.analysisSeq *= process.analysisTwoJetSeq
    process.zVetoLowAnalysisSeq *= process.zVetoLowAnalysisTwoJetSeq
    process.zVetoHighAnalysisSeq *= process.zVetoHighAnalysisTwoJetSeq



#******************************************************************************************
# Dynamic changes for command line parameters - Systematic studies
#******************************************************************************************

if options.systematics=='default':
    pass
elif options.systematics=='pileup14':
    process.oneGoodPVSelection.minNumber = 1
    process.oneGoodPVSelection.maxNumber = 4
elif options.systematics=='pileup57':
    process.oneGoodPVSelection.minNumber = 5
    process.oneGoodPVSelection.maxNumber = 7
elif options.systematics=='pileup8plus':
    process.oneGoodPVSelection.minNumber = 8
    process.oneGoodPVSelection.maxNumber = 99999
elif options.systematics=='sideband140':
    process.finalDimuonsZVetoHigh.cut = 'mass >= 140.'
elif options.systematics=='sideband160':
    process.finalDimuonsZVetoHigh.cut = 'mass >= 160.'
elif options.systematics=='sideband200':
    process.finalDimuonsZVetoHigh.cut = 'mass >= 120. & mass < 200.'
else:
    print 'ERROR --- systematic study not defined: ', options.systematics,
    exit(8888)



#******************************************************************************************
#   Analysis Path
#******************************************************************************************




process.analysis = cms.Path(
    process.analysisSeq
)

process.zVetoLowAnalysis = cms.Path(
    process.zVetoLowAnalysisSeq
)

process.zVetoHighAnalysis = cms.Path(
    process.zVetoHighAnalysisSeq
)

















