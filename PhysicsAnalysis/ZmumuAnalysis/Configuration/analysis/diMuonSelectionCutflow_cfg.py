import os

import FWCore.ParameterSet.Config as cms

process = cms.Process("FullCutflow")

## add message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.suppressWarning = cms.untracked.vstring("decaySubset") 



## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1001)
)



## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
    #SkipEvent = cms.untracked.vstring('ProductNotFound'),
    #Rethrow = cms.untracked.vstring("ProductNotFound"), # make this exception fatal (now default?)
)



## sources
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.Zmumu_Pat_cff")
process.load("ZmumuAnalysis.Configuration.samples.testSample_cff")



## needed for access to trigger menu
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = cms.string('START36_V9::All')
#process.load("Configuration.StandardSequences.Geometry_cff")
#process.load("Configuration.StandardSequences.MagneticField_cff")



## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/diMuonSelection.root'),
    closeFileFast = cms.untracked.bool(True)
)

#******************************************************************************************
#   Modules
#******************************************************************************************

## add event weight information
#process.load("TopAnalysis.TopUtils.EventWeightPlain_cfi") 

## analyze and filter trigger
process.load("ZmumuAnalysis.Analyzer.TriggerAnalyzer_cfi")
process.TriggerAnalyzer1 =  process.TriggerAnalyzer.clone()
process.load("ZmumuAnalysis.Filter.TriggerFilter_cfi")
process.TriggerFilter1 =  process.TriggerFilter.clone()

## filter for muon quality, kinematics HLT object matching
process.load("ZmumuAnalysis.Configuration.sequences.muonSelection_cff")

## event analyzer
process.load("ZmumuAnalysis.Analyzer.EventAnalyzer_cfi")
process.EventAnalyzer1 = process.EventAnalyzer.clone(
    muonSource = 'looseMuons',
)
process.EventAnalyzer2 = process.EventAnalyzer1.clone(
    muonSource = 'tightHltMuons',
)
process.EventAnalyzer1a = process.EventAnalyzer1.clone(
    diMuonSource = 'overlapExcludedLooseTightHltGlobalDimuons',
    analyzeDiMuons = True,
)
process.EventAnalyzer2a = process.EventAnalyzer2.clone(
    diMuonSource = 'overlapExcludedLooseTightHltGlobalDimuons',
    analyzeDiMuons = True,
)


## add dimuon collections and filter for dimuon properties (including muon isolation)
process.load("ZmumuAnalysis.Configuration.sequences.diMuonSelection_cff")
#process.looseTightHltGlobalDimuons.decay = 'tightHltMuons@+ tightMuons@-'



#process.load("ElectroWeakAnalysis.Skimming.zMuMuSubskimOutputModule_cfi")
#process.load("ElectroWeakAnalysis.Skimming.zMuMu_SubskimPathsWithMCTruth_cff")
#from ElectroWeakAnalysis.ZMuMu.ZMuMuCategoriesSequences_cff import *
#process.load("ElectroWeakAnalysis.ZMuMu.ZMuMuCategoriesVtxed_cff")

#process.load("ElectroWeakAnalysis.Skimming.dimuonsHLTFilter_cfi")
#process.load("ElectroWeakAnalysis.Skimming.patCandidatesForZMuMuSubskim_cff")
#process.dimuonsHLTFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","REDIGI36X")
#process.patTrigger.processName = "REDIGI36X"
#process.patTriggerEvent.processName = "REDIGI36X"
#process.patTrigger.triggerResults = cms.InputTag( "TriggerResults::REDIGI36X" )
#process.patTrigger.triggerEvent = cms.InputTag( "hltTriggerSummaryAOD::REDIGI36X" )



#******************************************************************************************
#   Analysis Path
#******************************************************************************************

process.load("PhysicsTools.PatAlgos.patSequences_cff")
process.out = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('keep *'),
)
process.outpath = cms.EndPath(process.out)
from PhysicsTools.PatAlgos.tools.trigTools import switchOnTrigger
switchOnTrigger(process)
del process.out
del process.outpath


process.p = cms.Path(
    process.TriggerAnalyzer1
    *process.TriggerFilter1
    *process.buildCollections
    *process.EventAnalyzer1
    *process.EventAnalyzer2
    *process.muonSelection
    
    *process.buildDimuonCollections
    *process.EventAnalyzer1a
    *process.EventAnalyzer2a    
    *process.dimuonSelection
)
