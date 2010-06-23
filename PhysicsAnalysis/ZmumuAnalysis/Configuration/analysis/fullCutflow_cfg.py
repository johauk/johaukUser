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
#process.source = cms.Source("PoolSource",
#    fileNames = cms.untracked.vstring(
#      '/store/user/dammann/36X/Spring10/Zmumu/PATtuple_v6_35_1.root',
#    )
#    #vorselektierte samples unter /pnfs/desy.de/cms/tier2/store/user/dammann/
#)





### define which collections and correction you want to be used
#muonCollection = cms.InputTag("isolatedMuons")
#jetCollection  = cms.InputTag("tightJets")
#jetCorrection  = cms.string("part")
#correctedMETs  = cms.InputTag("layer1METsAK5")

## register TFileService
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/fullCutflow.root'),
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

### filter for muon and jet kinematics, muon iso and quality				     
process.load("ZmumuAnalysis.Configuration.sequences.muonSelection_cff")

### event analyzer
process.load("ZmumuAnalysis.Analyzer.EventAnalyzer_cfi")
process.EventAnalyzer1 = process.EventAnalyzer.clone(
    muonSource = 'goodIdMuons',
)
process.EventAnalyzer2 = process.EventAnalyzer1.clone(
    muonSource = 'goodZmumuMuons',
)

### filter for dimuon mass				     
#process.load("TopAnalysis.TopFilter.filters.DiMuonMassFilter_cfi")
#process.filterDiMuonMass.muons = muonCollection

### jet analyzer
#from MyAnalysis.JetAnalysis.JetFlavorAnalyzer_cfi import *
#process.analyzeJets0      = analyzeJets.clone()
#process.analyzeJets1      = analyzeJets.clone()
#process.analyzeJets1.jets = jetCollection
#process.analyzeJets2      = analyzeJets.clone()
#process.analyzeJets2.jets = jetCollection
#process.analyzeJets3      = analyzeJets.clone()
#process.analyzeJets3.jets = jetCollection
#process.analyzeJets4      = analyzeJets.clone()
#process.analyzeJets4.jets = jetCollection

### muon analyzer
#from MyAnalysis.MuonAnalysis.MyMuonAnalyzer_cfi import *
#process.analyzeMuons0         = analyzeMuons.clone()
#process.analyzeMuons1         = analyzeMuons.clone()
#process.analyzeMuons1.muons   = muonCollection

## dimuon analyzer
#from TopAnalysis.TopAnalyzer.DimuonAnalyzer_cfi import *
#process.analyzeMuonPair0       = analyzeMuonPair.clone() 
#process.analyzeMuonPair1       = analyzeMuonPair.clone() 
#process.analyzeMuonPair1.muons = muonCollection 

### std sequence to produce the ttGenEvt
#process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttGenEvent_cff")

### std sequence to produce the ttFullLepEvent
#process.load("TopQuarkAnalysis.TopEventProducers.sequences.ttFullLepEvtBuilder_cff")
#process.kinSolutionTtFullLepEventHypothesis.muons              = muonCollection
#process.kinSolutionTtFullLepEventHypothesis.jets               = jetCollection
#process.kinSolutionTtFullLepEventHypothesis.jetCorrectionLevel = jetCorrection
##process.kinSolutionTtFullLepEventHypothesis.mets               = correctedMET
#
#process.ttFullLepHypKinSolution.muons              = muonCollection
#process.ttFullLepHypKinSolution.jets               = jetCollection
#process.ttFullLepHypKinSolution.jetCorrectionLevel = jetCorrection
##process.ttFullLepHypKinSolution.mets               = correctedMET
#
#process.ttFullLepHypGenMatch.muons              = muonCollection
#process.ttFullLepHypGenMatch.jets               = jetCollection
#process.ttFullLepHypGenMatch.jetCorrectionLevel = jetCorrection
##process.ttFullLepHypGenMatch.mets               = correctedMET

### filter reconstructed events
#process.load("TopAnalysis.TopFilter.filters.FullLepHypothesesFilter_cfi")
#process.filterFullLepHypothesis.jets  = jetCollection

### analyze hypotheses
#from TopAnalysis.TopAnalyzer.FullLepHypothesesAnalyzer_cff import *
#process.analyzeKinSolution1 = analyzeKinSolution.clone()
#process.analyzeGenMatch1    = analyzeGenMatch.clone()
#process.analyzeKinSolution2 = analyzeKinSolution.clone()
#process.analyzeGenMatch2    = analyzeGenMatch.clone()

#******************************************************************************************
#   Analysis Path
#******************************************************************************************

process.p = cms.Path(
    process.TriggerAnalyzer1*
    process.TriggerFilter1*
    process.buildCollections*
    process.EventAnalyzer1*
    process.EventAnalyzer2
)


#process.p = cms.Path(process.eventWeight *
#                     process.analyzeTrigger *
#		     process.filterTrigger *      # all muon triggers
#		     process.buildCollections *   # 
		     #process.analyzeMuons0 *     # takes selectedLayer1Muons as input		     
#		     process.analyzeMuonPair0 #*   # takes selectedLayer1Muons as input
		     #process.analyzeJets0 *	  # takes selectedLayer1Jets as input		     
                     #process.analyzeJets1 *
#                     process.fullLeptonicMuonMuonSelection *   # select hard, isolated, good quality muons (>=2) & hard, tight jets (>=2)
		     #process.analyzeMuons1 *		     		     		                          
#                     process.analyzeMuonPair1 #*
		     #process.analyzeJets2 *		     		    
#		     process.filterDiMuonMass *
#		     process.makeGenEvt *
#                     process.makeTtFullLepEvent *		     
         	     #process.analyzeJets3 *
#		     process.analyzeKinSolution1 *
#		     process.analyzeGenMatch1 *
#		     process.filterFullLepHypothesis * #Can be used for invariant mass cuts and b-tag cut 
		     #process.analyzeJets4 *
#		     process.analyzeKinSolution2 *
#		     process.analyzeGenMatch2 
#                    )
