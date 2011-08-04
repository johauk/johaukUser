import FWCore.ParameterSet.Config as cms



#******************************************************************************************
#   Filter & Producer Modules
#******************************************************************************************

## filter trigger
from ZmumuAnalysis.Configuration.filters.TriggerFilter_cff import TriggerFilter

## filter for good primary vertices
from ZmumuAnalysis.Configuration.sequences.vertexSelection_cff import *

## filter for muon quality, kinematics and HLT object matching
from ZmumuAnalysis.Configuration.sequences.muonSelection_cff import *

## add dimuon collections and filter for dimuon properties (including muon isolation)
from ZmumuAnalysis.Configuration.sequences.dimuonSelection_cff import *

## clean and filter for jets
from ZmumuAnalysis.Configuration.sequences.jetSelection_cff import *

## filter for missing Et
from ZmumuAnalysis.Configuration.sequences.metSelection_cff import *





#******************************************************************************************
#   Analyzer Modules
#******************************************************************************************

## Event Counter
from ZmumuAnalysis.Analyzer.EventCounter_cfi import *
EventCounterStep0 = EventCounter.clone()
EventCounterStep1a = EventCounter.clone()
EventCounterStep1b = EventCounter.clone()
EventCounterStep1 = EventCounter.clone()
EventCounterStep2a = EventCounter.clone()
EventCounterStep2b = EventCounter.clone()
EventCounterStep2c = EventCounter.clone()
EventCounterStep2d = EventCounter.clone()
EventCounterStep2e = EventCounter.clone()
EventCounterStep2f = EventCounter.clone()
EventCounterStep2g = EventCounter.clone()
EventCounterStep2 = EventCounter.clone()
EventCounterStep3a = EventCounter.clone()
EventCounterStep3b = EventCounter.clone()
EventCounterStep3c = EventCounter.clone()
EventCounterStep3d = EventCounter.clone()
EventCounterStep3e = EventCounter.clone()
EventCounterStep3 = EventCounter.clone()
EventCounterStep4a = EventCounter.clone()
EventCounterStep4b = EventCounter.clone()
EventCounterStep4c = EventCounter.clone()
EventCounterStep4d = EventCounter.clone()
EventCounterStep4 = EventCounter.clone()
EventCounterStep5 = EventCounter.clone()
EventCounterStep6a = EventCounter.clone()
EventCounterStep6 = EventCounter.clone()
EventCounterStep7a = EventCounter.clone()
EventCounterStep7b = EventCounter.clone()
EventCounterStep7c = EventCounter.clone()
EventCounterStep7 = EventCounter.clone()
EventCounterStepZVetoLow3 = EventCounter.clone()
EventCounterStepZVetoLow4a = EventCounter.clone()
EventCounterStepZVetoLow4b = EventCounter.clone()
EventCounterStepZVetoLow4c = EventCounter.clone()
EventCounterStepZVetoLow4d = EventCounter.clone()
EventCounterStepZVetoLow4 = EventCounter.clone()
EventCounterStepZVetoLow5 = EventCounter.clone()
EventCounterStepZVetoLow6a = EventCounter.clone()
EventCounterStepZVetoLow6 = EventCounter.clone()
EventCounterStepZVetoLow7a = EventCounter.clone()
EventCounterStepZVetoLow7b = EventCounter.clone()
EventCounterStepZVetoLow7c = EventCounter.clone()
EventCounterStepZVetoLow7 = EventCounter.clone()
EventCounterStepZVetoHigh3 = EventCounter.clone()
EventCounterStepZVetoHigh4a = EventCounter.clone()
EventCounterStepZVetoHigh4b = EventCounter.clone()
EventCounterStepZVetoHigh4c = EventCounter.clone()
EventCounterStepZVetoHigh4d = EventCounter.clone()
EventCounterStepZVetoHigh4 = EventCounter.clone()
EventCounterStepZVetoHigh5 = EventCounter.clone()
EventCounterStepZVetoHigh6a = EventCounter.clone()
EventCounterStepZVetoHigh6 = EventCounter.clone()
EventCounterStepZVetoHigh7a = EventCounter.clone()
EventCounterStepZVetoHigh7b = EventCounter.clone()
EventCounterStepZVetoHigh7c = EventCounter.clone()
EventCounterStepZVetoHigh7 = EventCounter.clone()

EventCounterStepNoMet7a = EventCounter.clone()
EventCounterStepNoMet7b = EventCounter.clone()
EventCounterStepNoMet7c = EventCounter.clone()
EventCounterStepNoMet7 = EventCounter.clone()
EventCounterStepZVetoLowNoMet7a = EventCounter.clone()
EventCounterStepZVetoLowNoMet7b = EventCounter.clone()
EventCounterStepZVetoLowNoMet7c = EventCounter.clone()
EventCounterStepZVetoLowNoMet7 = EventCounter.clone()
EventCounterStepZVetoHighNoMet7a = EventCounter.clone()
EventCounterStepZVetoHighNoMet7b = EventCounter.clone()
EventCounterStepZVetoHighNoMet7c = EventCounter.clone()
EventCounterStepZVetoHighNoMet7 = EventCounter.clone()

EventCounterStepOneBSsvHeMJet7a = EventCounter.clone()
EventCounterStepOneBSsvHpTJet7a = EventCounter.clone()
EventCounterStepZVetoLowOneBSsvHeMJet7a = EventCounter.clone()
EventCounterStepZVetoLowOneBSsvHpTJet7a = EventCounter.clone()
EventCounterStepZVetoHighOneBSsvHeMJet7a = EventCounter.clone()
EventCounterStepZVetoHighOneBSsvHpTJet7a = EventCounter.clone()
EventCounterStepNoMetOneBSsvHeMJet7a = EventCounter.clone()
EventCounterStepNoMetOneBSsvHpTJet7a = EventCounter.clone()
EventCounterStepZVetoLowNoMetOneBSsvHeMJet7a = EventCounter.clone()
EventCounterStepZVetoLowNoMetOneBSsvHpTJet7a = EventCounter.clone()
EventCounterStepZVetoHighNoMetOneBSsvHeMJet7a = EventCounter.clone()
EventCounterStepZVetoHighNoMetOneBSsvHpTJet7a = EventCounter.clone()





## trigger analyzer
from ZmumuAnalysis.Analyzer.TriggerAnalyzer_cfi import *
TriggerAnalyzerStep1a =  TriggerAnalyzer.clone(
    #triggerResults = cms.InputTag('TriggerResults','','HLT'),
    #triggerResults = cms.InputTag('TriggerResults','','REDIGI38X'),
)



## vertex analyzer
from ZmumuAnalysis.Analyzer.VertexAnalyzer_cfi import *
VertexAnalyzerStep1b = VertexAnalyzer.clone()#vertexSource = 'offlinePrimaryVertices',)
VertexAnalyzerStep1 = VertexAnalyzer.clone(vertexSource = 'goodPVs',)
VertexAnalyzerStep3d = VertexAnalyzer.clone(vertexSource = 'goodDimuonPVs',)
VertexAnalyzerStep3e = VertexAnalyzer.clone(vertexSource = 'bestPV',)
VertexAnalyzerStep3 = VertexAnalyzer.clone(vertexSource = 'bestPV',)

VertexAnalyzerStepZVetoLow3 = VertexAnalyzerStep3.clone()
VertexAnalyzerStepZVetoHigh3 = VertexAnalyzerStep3.clone()



## muon analizer
from ZmumuAnalysis.Analyzer.MuonAnalyzer_cfi import *
MuonAnalyzerStep2b = MuonAnalyzer.clone(muonSource = 'selectedPatMuons',whichHists = "veryBasic",)
MuonAnalyzerStep2c = MuonAnalyzer.clone(muonSource = 'looseMuons',whichHists = "basic",)
MuonAnalyzerStep2d = MuonAnalyzer.clone(muonSource = 'tightMuons',whichHists = "basic",)
MuonAnalyzerStep2e = MuonAnalyzer.clone(muonSource = 'isolatedMuons',whichHists = "basic",)
MuonAnalyzerStep2 = MuonAnalyzer.clone(muonSource = 'isolatedMuons')
MuonAnalyzerStep3 = MuonAnalyzer.clone(muonSource = 'isolatedMuons',)
MuonAnalyzerStep4 = MuonAnalyzer.clone(muonSource = 'isolatedMuons',)
MuonAnalyzerStep5 = MuonAnalyzer.clone(muonSource = 'isolatedMuons',)
MuonAnalyzerStep6 = MuonAnalyzer.clone(muonSource = 'isolatedMuons',)
MuonAnalyzerStep7a = MuonAnalyzer.clone(muonSource = 'isolatedMuons',)
MuonAnalyzerStep7b = MuonAnalyzer.clone(muonSource = 'isolatedMuons',)
MuonAnalyzerStep7c = MuonAnalyzer.clone(muonSource = 'isolatedMuons',)
MuonAnalyzerStep7 = MuonAnalyzer.clone(muonSource = 'isolatedMuons',)

MuonAnalyzerStepZVetoLow3 = MuonAnalyzerStep3.clone()
MuonAnalyzerStepZVetoLow4 = MuonAnalyzerStep4.clone()
MuonAnalyzerStepZVetoLow5 = MuonAnalyzerStep5.clone()
MuonAnalyzerStepZVetoLow6 = MuonAnalyzerStep6.clone()
MuonAnalyzerStepZVetoLow7a = MuonAnalyzerStep7a.clone()
MuonAnalyzerStepZVetoLow7b = MuonAnalyzerStep7b.clone()
MuonAnalyzerStepZVetoLow7c = MuonAnalyzerStep7c.clone()
MuonAnalyzerStepZVetoLow7 = MuonAnalyzerStep7.clone()
MuonAnalyzerStepZVetoHigh3 = MuonAnalyzerStep3.clone()
MuonAnalyzerStepZVetoHigh4 = MuonAnalyzerStep4.clone()
MuonAnalyzerStepZVetoHigh5 = MuonAnalyzerStep5.clone()
MuonAnalyzerStepZVetoHigh6 = MuonAnalyzerStep6.clone()
MuonAnalyzerStepZVetoHigh7a = MuonAnalyzerStep7a.clone()
MuonAnalyzerStepZVetoHigh7b = MuonAnalyzerStep7b.clone()
MuonAnalyzerStepZVetoHigh7c = MuonAnalyzerStep7c.clone()
MuonAnalyzerStepZVetoHigh7 = MuonAnalyzerStep7.clone()

MuonAnalyzerStepNoMet7a = MuonAnalyzerStep7a.clone()
MuonAnalyzerStepNoMet7b = MuonAnalyzerStep7b.clone()
MuonAnalyzerStepNoMet7c = MuonAnalyzerStep7c.clone()
MuonAnalyzerStepNoMet7 = MuonAnalyzerStep7.clone()
MuonAnalyzerStepZVetoLowNoMet7a = MuonAnalyzerStep7a.clone()
MuonAnalyzerStepZVetoLowNoMet7b = MuonAnalyzerStep7b.clone()
MuonAnalyzerStepZVetoLowNoMet7c = MuonAnalyzerStep7c.clone()
MuonAnalyzerStepZVetoLowNoMet7 = MuonAnalyzerStep7.clone()
MuonAnalyzerStepZVetoHighNoMet7a = MuonAnalyzerStep7a.clone()
MuonAnalyzerStepZVetoHighNoMet7b = MuonAnalyzerStep7b.clone()
MuonAnalyzerStepZVetoHighNoMet7c = MuonAnalyzerStep7c.clone()
MuonAnalyzerStepZVetoHighNoMet7 = MuonAnalyzerStep7.clone()

MuonAnalyzerStepOneBSsvHeMJet7a = MuonAnalyzerStep7a.clone()
MuonAnalyzerStepOneBSsvHpTJet7a = MuonAnalyzerStep7a.clone()
MuonAnalyzerStepZVetoLowOneBSsvHeMJet7a = MuonAnalyzerStep7a.clone()
MuonAnalyzerStepZVetoLowOneBSsvHpTJet7a = MuonAnalyzerStep7a.clone()
MuonAnalyzerStepZVetoHighOneBSsvHeMJet7a = MuonAnalyzerStep7a.clone()
MuonAnalyzerStepZVetoHighOneBSsvHpTJet7a = MuonAnalyzerStep7a.clone()
MuonAnalyzerStepNoMetOneBSsvHeMJet7a = MuonAnalyzerStep7a.clone()
MuonAnalyzerStepNoMetOneBSsvHpTJet7a = MuonAnalyzerStep7a.clone()
MuonAnalyzerStepZVetoLowNoMetOneBSsvHeMJet7a = MuonAnalyzerStep7a.clone()
MuonAnalyzerStepZVetoLowNoMetOneBSsvHpTJet7a = MuonAnalyzerStep7a.clone()
MuonAnalyzerStepZVetoHighNoMetOneBSsvHeMJet7a = MuonAnalyzerStep7a.clone()
MuonAnalyzerStepZVetoHighNoMetOneBSsvHpTJet7a = MuonAnalyzerStep7a.clone()



## di-muon analyzer
from ZmumuAnalysis.Analyzer.DimuonAnalyzer_cfi import *
DimuonAnalyzerStep3d = DimuonAnalyzer.clone(dimuonSource = "goodDimuons",)
DimuonAnalyzerStep3e = DimuonAnalyzer.clone(dimuonSource = "bestDimuon",)
DimuonAnalyzerStep3 = DimuonAnalyzer.clone(dimuonSource = "bestDimuon",)
DimuonAnalyzerStep4 = DimuonAnalyzer.clone(dimuonSource = "bestDimuon",)
DimuonAnalyzerStep5 = DimuonAnalyzer.clone(dimuonSource = "bestDimuon",)
DimuonAnalyzerStep6 = DimuonAnalyzer.clone(dimuonSource = "bestDimuon",)
DimuonAnalyzerStep7a = DimuonAnalyzer.clone(dimuonSource = "bestDimuon",)
DimuonAnalyzerStep7b = DimuonAnalyzer.clone(dimuonSource = "bestDimuon",)
DimuonAnalyzerStep7c = DimuonAnalyzer.clone(dimuonSource = "bestDimuon",)
DimuonAnalyzerStep7 = DimuonAnalyzer.clone(dimuonSource = "bestDimuon",)

DimuonAnalyzerStepZVetoLow3 = DimuonAnalyzerStep3.clone()
DimuonAnalyzerStepZVetoLow4 = DimuonAnalyzerStep4.clone()
DimuonAnalyzerStepZVetoLow5 = DimuonAnalyzerStep5.clone()
DimuonAnalyzerStepZVetoLow6 = DimuonAnalyzerStep6.clone()
DimuonAnalyzerStepZVetoLow7a = DimuonAnalyzerStep7a.clone()
DimuonAnalyzerStepZVetoLow7b = DimuonAnalyzerStep7b.clone()
DimuonAnalyzerStepZVetoLow7c = DimuonAnalyzerStep7c.clone()
DimuonAnalyzerStepZVetoLow7 = DimuonAnalyzerStep7.clone()
DimuonAnalyzerStepZVetoHigh3 = DimuonAnalyzerStep3.clone()
DimuonAnalyzerStepZVetoHigh4 = DimuonAnalyzerStep4.clone()
DimuonAnalyzerStepZVetoHigh5 = DimuonAnalyzerStep5.clone()
DimuonAnalyzerStepZVetoHigh6 = DimuonAnalyzerStep6.clone()
DimuonAnalyzerStepZVetoHigh7a = DimuonAnalyzerStep7a.clone()
DimuonAnalyzerStepZVetoHigh7b = DimuonAnalyzerStep7b.clone()
DimuonAnalyzerStepZVetoHigh7c = DimuonAnalyzerStep7c.clone()
DimuonAnalyzerStepZVetoHigh7 = DimuonAnalyzerStep7.clone()

DimuonAnalyzerStepNoMet7a = DimuonAnalyzerStep7a.clone()
DimuonAnalyzerStepNoMet7b = DimuonAnalyzerStep7b.clone()
DimuonAnalyzerStepNoMet7c = DimuonAnalyzerStep7c.clone()
DimuonAnalyzerStepNoMet7 = DimuonAnalyzerStep7.clone()
DimuonAnalyzerStepZVetoLowNoMet7a = DimuonAnalyzerStepZVetoLow7a.clone()
DimuonAnalyzerStepZVetoLowNoMet7b = DimuonAnalyzerStepZVetoLow7b.clone()
DimuonAnalyzerStepZVetoLowNoMet7c = DimuonAnalyzerStepZVetoLow7c.clone()
DimuonAnalyzerStepZVetoLowNoMet7 = DimuonAnalyzerStepZVetoLow7.clone()
DimuonAnalyzerStepZVetoHighNoMet7a = DimuonAnalyzerStepZVetoHigh7a.clone()
DimuonAnalyzerStepZVetoHighNoMet7b = DimuonAnalyzerStepZVetoHigh7b.clone()
DimuonAnalyzerStepZVetoHighNoMet7c = DimuonAnalyzerStepZVetoHigh7c.clone()
DimuonAnalyzerStepZVetoHighNoMet7 = DimuonAnalyzerStepZVetoHigh7.clone()

DimuonAnalyzerStepOneBSsvHeMJet7a = DimuonAnalyzerStep7a.clone()
DimuonAnalyzerStepOneBSsvHpTJet7a = DimuonAnalyzerStep7a.clone()
DimuonAnalyzerStepZVetoLowOneBSsvHeMJet7a = DimuonAnalyzerStep7a.clone()
DimuonAnalyzerStepZVetoLowOneBSsvHpTJet7a = DimuonAnalyzerStep7a.clone()
DimuonAnalyzerStepZVetoHighOneBSsvHeMJet7a = DimuonAnalyzerStep7a.clone()
DimuonAnalyzerStepZVetoHighOneBSsvHpTJet7a = DimuonAnalyzerStep7a.clone()
DimuonAnalyzerStepNoMetOneBSsvHeMJet7a = DimuonAnalyzerStep7a.clone()
DimuonAnalyzerStepNoMetOneBSsvHpTJet7a = DimuonAnalyzerStep7a.clone()
DimuonAnalyzerStepZVetoLowNoMetOneBSsvHeMJet7a = DimuonAnalyzerStep7a.clone()
DimuonAnalyzerStepZVetoLowNoMetOneBSsvHpTJet7a = DimuonAnalyzerStep7a.clone()
DimuonAnalyzerStepZVetoHighNoMetOneBSsvHeMJet7a = DimuonAnalyzerStep7a.clone()
DimuonAnalyzerStepZVetoHighNoMetOneBSsvHpTJet7a = DimuonAnalyzerStep7a.clone()



## jet analyzer
from ZmumuAnalysis.Analyzer.JetAnalyzer_cfi import *
#JetAnalyzerStep4a = JetAnalyzer.clone(jetSource = 'selectedPatJetsAK5PF',whichHists = "basic",)
JetAnalyzerStep4b = JetAnalyzer.clone(jetSource = 'selectedJets',whichHists = "basic",)
JetAnalyzerStep4c = JetAnalyzer.clone(jetSource = 'cleanJets',whichHists = "basic",)
JetAnalyzerStep4d = JetAnalyzer.clone(jetSource = 'goodJets',)
JetAnalyzerStep4J = JetAnalyzer.clone(jetSource = 'finalJets',whichHists = "basic",)
JetAnalyzerStep4Bhe = JetAnalyzer.clone(jetSource = 'bSsvHeMJets',whichHists = "basic",)
JetAnalyzerStep4Bhp = JetAnalyzer.clone(jetSource = 'bSsvHpTJets',whichHists = "basic",)
JetAnalyzerStep5J = JetAnalyzer.clone(jetSource = 'finalJets',)
JetAnalyzerStep5Bhe = JetAnalyzer.clone(jetSource = 'bSsvHeMJets',)
JetAnalyzerStep5Bhp = JetAnalyzer.clone(jetSource = 'bSsvHpTJets',)
JetAnalyzerStep6J = JetAnalyzer.clone(jetSource = 'finalJets',)
JetAnalyzerStep6Bhe = JetAnalyzer.clone(jetSource = 'bSsvHeMJets',)
JetAnalyzerStep6Bhp = JetAnalyzer.clone(jetSource = 'bSsvHpTJets',)
JetAnalyzerStep7aJ = JetAnalyzer.clone(jetSource = 'finalJets',)
JetAnalyzerStep7aBhe = JetAnalyzer.clone(jetSource = 'bSsvHeMJets',)
JetAnalyzerStep7aBhp = JetAnalyzer.clone(jetSource = 'bSsvHpTJets',)
JetAnalyzerStep7bJ = JetAnalyzer.clone(jetSource = 'finalJets',)
JetAnalyzerStep7bBhe = JetAnalyzer.clone(jetSource = 'bSsvHeMJets',)
JetAnalyzerStep7bBhp = JetAnalyzer.clone(jetSource = 'bSsvHpTJets',)
JetAnalyzerStep7cJ = JetAnalyzer.clone(jetSource = 'finalJets',)
JetAnalyzerStep7cBhe = JetAnalyzer.clone(jetSource = 'bSsvHeMJets',)
JetAnalyzerStep7cBhp = JetAnalyzer.clone(jetSource = 'bSsvHpTJets',)
JetAnalyzerStep7J = JetAnalyzer.clone(jetSource = 'finalJets',)
JetAnalyzerStep7Bhe = JetAnalyzer.clone(jetSource = 'bSsvHeMJets',)
JetAnalyzerStep7Bhp = JetAnalyzer.clone(jetSource = 'bSsvHpTJets',)

JetAnalyzerStepZVetoLow4b = JetAnalyzerStep4b.clone()
JetAnalyzerStepZVetoLow4c = JetAnalyzerStep4c.clone()
JetAnalyzerStepZVetoLow4d = JetAnalyzerStep4d.clone()
JetAnalyzerStepZVetoLow4J = JetAnalyzerStep4J.clone()
JetAnalyzerStepZVetoLow4Bhe = JetAnalyzerStep4Bhe.clone()
JetAnalyzerStepZVetoLow4Bhp = JetAnalyzerStep4Bhp.clone()
JetAnalyzerStepZVetoLow5J = JetAnalyzerStep5J.clone()
JetAnalyzerStepZVetoLow5Bhe = JetAnalyzerStep5Bhe.clone()
JetAnalyzerStepZVetoLow5Bhp = JetAnalyzerStep5Bhp.clone()
JetAnalyzerStepZVetoLow6J = JetAnalyzerStep6J.clone()
JetAnalyzerStepZVetoLow6Bhe = JetAnalyzerStep6Bhe.clone()
JetAnalyzerStepZVetoLow6Bhp = JetAnalyzerStep6Bhp.clone()
JetAnalyzerStepZVetoLow7aJ = JetAnalyzerStep7aJ.clone()
JetAnalyzerStepZVetoLow7aBhe = JetAnalyzerStep7aBhe.clone()
JetAnalyzerStepZVetoLow7aBhp = JetAnalyzerStep7aBhp.clone()
JetAnalyzerStepZVetoLow7bJ = JetAnalyzerStep7bJ.clone()
JetAnalyzerStepZVetoLow7bBhe = JetAnalyzerStep7bBhe.clone()
JetAnalyzerStepZVetoLow7bBhp = JetAnalyzerStep7bBhp.clone()
JetAnalyzerStepZVetoLow7cJ = JetAnalyzerStep7cJ.clone()
JetAnalyzerStepZVetoLow7cBhe = JetAnalyzerStep7cBhe.clone()
JetAnalyzerStepZVetoLow7cBhp = JetAnalyzerStep7cBhp.clone()
JetAnalyzerStepZVetoLow7J = JetAnalyzerStep7J.clone()
JetAnalyzerStepZVetoLow7Bhe = JetAnalyzerStep7Bhe.clone()
JetAnalyzerStepZVetoLow7Bhp = JetAnalyzerStep7Bhp.clone()
JetAnalyzerStepZVetoHigh4b = JetAnalyzerStep4b.clone()
JetAnalyzerStepZVetoHigh4c = JetAnalyzerStep4c.clone()
JetAnalyzerStepZVetoHigh4d = JetAnalyzerStep4d.clone()
JetAnalyzerStepZVetoHigh4J = JetAnalyzerStep4J.clone()
JetAnalyzerStepZVetoHigh4Bhe = JetAnalyzerStep4Bhe.clone()
JetAnalyzerStepZVetoHigh4Bhp = JetAnalyzerStep4Bhp.clone()
JetAnalyzerStepZVetoHigh5J = JetAnalyzerStep5J.clone()
JetAnalyzerStepZVetoHigh5Bhe = JetAnalyzerStep5Bhe.clone()
JetAnalyzerStepZVetoHigh5Bhp = JetAnalyzerStep5Bhp.clone()
JetAnalyzerStepZVetoHigh6J = JetAnalyzerStep6J.clone()
JetAnalyzerStepZVetoHigh6Bhe = JetAnalyzerStep6Bhe.clone()
JetAnalyzerStepZVetoHigh6Bhp = JetAnalyzerStep6Bhp.clone()
JetAnalyzerStepZVetoHigh7aJ = JetAnalyzerStep7aJ.clone()
JetAnalyzerStepZVetoHigh7aBhe = JetAnalyzerStep7aBhe.clone()
JetAnalyzerStepZVetoHigh7aBhp = JetAnalyzerStep7aBhp.clone()
JetAnalyzerStepZVetoHigh7bJ = JetAnalyzerStep7bJ.clone()
JetAnalyzerStepZVetoHigh7bBhe = JetAnalyzerStep7bBhe.clone()
JetAnalyzerStepZVetoHigh7bBhp = JetAnalyzerStep7bBhp.clone()
JetAnalyzerStepZVetoHigh7cJ = JetAnalyzerStep7cJ.clone()
JetAnalyzerStepZVetoHigh7cBhe = JetAnalyzerStep7cBhe.clone()
JetAnalyzerStepZVetoHigh7cBhp = JetAnalyzerStep7cBhp.clone()
JetAnalyzerStepZVetoHigh7J = JetAnalyzerStep7J.clone()
JetAnalyzerStepZVetoHigh7Bhe = JetAnalyzerStep7Bhe.clone()
JetAnalyzerStepZVetoHigh7Bhp = JetAnalyzerStep7Bhp.clone()

JetAnalyzerStepNoMet7aJ = JetAnalyzerStep7aJ.clone()
JetAnalyzerStepNoMet7aBhe = JetAnalyzerStep7aBhe.clone()
JetAnalyzerStepNoMet7aBhp = JetAnalyzerStep7aBhp.clone()
JetAnalyzerStepNoMet7bJ = JetAnalyzerStep7bJ.clone()
JetAnalyzerStepNoMet7bBhe = JetAnalyzerStep7bBhe.clone()
JetAnalyzerStepNoMet7bBhp = JetAnalyzerStep7bBhp.clone()
JetAnalyzerStepNoMet7cJ = JetAnalyzerStep7cJ.clone()
JetAnalyzerStepNoMet7cBhe = JetAnalyzerStep7cBhe.clone()
JetAnalyzerStepNoMet7cBhp = JetAnalyzerStep7cBhp.clone()
JetAnalyzerStepNoMet7J = JetAnalyzerStep7J.clone()
JetAnalyzerStepNoMet7Bhe = JetAnalyzerStep7Bhe.clone()
JetAnalyzerStepNoMet7Bhp = JetAnalyzerStep7Bhp.clone()

JetAnalyzerStepZVetoLowNoMet7aJ = JetAnalyzerStepZVetoLow7aJ.clone()
JetAnalyzerStepZVetoLowNoMet7aBhe = JetAnalyzerStepZVetoLow7aBhe.clone()
JetAnalyzerStepZVetoLowNoMet7aBhp = JetAnalyzerStepZVetoLow7aBhp.clone()
JetAnalyzerStepZVetoLowNoMet7bJ = JetAnalyzerStepZVetoLow7bJ.clone()
JetAnalyzerStepZVetoLowNoMet7bBhe = JetAnalyzerStepZVetoLow7bBhe.clone()
JetAnalyzerStepZVetoLowNoMet7bBhp = JetAnalyzerStepZVetoLow7bBhp.clone()
JetAnalyzerStepZVetoLowNoMet7cJ = JetAnalyzerStepZVetoLow7cJ.clone()
JetAnalyzerStepZVetoLowNoMet7cBhe = JetAnalyzerStepZVetoLow7cBhe.clone()
JetAnalyzerStepZVetoLowNoMet7cBhp = JetAnalyzerStepZVetoLow7cBhp.clone()
JetAnalyzerStepZVetoLowNoMet7J = JetAnalyzerStepZVetoLow7J.clone()
JetAnalyzerStepZVetoLowNoMet7Bhe = JetAnalyzerStepZVetoLow7Bhe.clone()
JetAnalyzerStepZVetoLowNoMet7Bhp = JetAnalyzerStepZVetoLow7Bhp.clone()
JetAnalyzerStepZVetoHighNoMet7aJ = JetAnalyzerStepZVetoHigh7aJ.clone()
JetAnalyzerStepZVetoHighNoMet7aBhe = JetAnalyzerStepZVetoHigh7aBhe.clone()
JetAnalyzerStepZVetoHighNoMet7aBhp = JetAnalyzerStepZVetoHigh7aBhp.clone()
JetAnalyzerStepZVetoHighNoMet7bJ = JetAnalyzerStepZVetoHigh7bJ.clone()
JetAnalyzerStepZVetoHighNoMet7bBhe = JetAnalyzerStepZVetoHigh7bBhe.clone()
JetAnalyzerStepZVetoHighNoMet7bBhp = JetAnalyzerStepZVetoHigh7bBhp.clone()
JetAnalyzerStepZVetoHighNoMet7cJ = JetAnalyzerStepZVetoHigh7cJ.clone()
JetAnalyzerStepZVetoHighNoMet7cBhe = JetAnalyzerStepZVetoHigh7cBhe.clone()
JetAnalyzerStepZVetoHighNoMet7cBhp = JetAnalyzerStepZVetoHigh7cBhp.clone()
JetAnalyzerStepZVetoHighNoMet7J = JetAnalyzerStepZVetoHigh7J.clone()
JetAnalyzerStepZVetoHighNoMet7Bhe = JetAnalyzerStepZVetoHigh7Bhe.clone()
JetAnalyzerStepZVetoHighNoMet7Bhp = JetAnalyzerStepZVetoHigh7Bhp.clone()

JetAnalyzerStepOneBSsvHeMJet7aJ = JetAnalyzerStep7aJ.clone()
JetAnalyzerStepOneBSsvHeMJet7aBhe = JetAnalyzerStep7aBhe.clone()
JetAnalyzerStepOneBSsvHeMJet7aBhp = JetAnalyzerStep7aBhp.clone()
JetAnalyzerStepOneBSsvHpTJet7aJ = JetAnalyzerStep7aJ.clone()
JetAnalyzerStepOneBSsvHpTJet7aBhe = JetAnalyzerStep7aBhe.clone()
JetAnalyzerStepOneBSsvHpTJet7aBhp = JetAnalyzerStep7aBhp.clone()
JetAnalyzerStepZVetoLowOneBSsvHeMJet7aJ = JetAnalyzerStep7aJ.clone()
JetAnalyzerStepZVetoLowOneBSsvHeMJet7aBhe = JetAnalyzerStep7aBhe.clone()
JetAnalyzerStepZVetoLowOneBSsvHeMJet7aBhp = JetAnalyzerStep7aBhp.clone()
JetAnalyzerStepZVetoLowOneBSsvHpTJet7aJ = JetAnalyzerStep7aJ.clone()
JetAnalyzerStepZVetoLowOneBSsvHpTJet7aBhe = JetAnalyzerStep7aBhe.clone()
JetAnalyzerStepZVetoLowOneBSsvHpTJet7aBhp = JetAnalyzerStep7aBhp.clone()
JetAnalyzerStepZVetoHighOneBSsvHeMJet7aJ = JetAnalyzerStep7aJ.clone()
JetAnalyzerStepZVetoHighOneBSsvHeMJet7aBhe = JetAnalyzerStep7aBhe.clone()
JetAnalyzerStepZVetoHighOneBSsvHeMJet7aBhp = JetAnalyzerStep7aBhp.clone()
JetAnalyzerStepZVetoHighOneBSsvHpTJet7aJ = JetAnalyzerStep7aJ.clone()
JetAnalyzerStepZVetoHighOneBSsvHpTJet7aBhe = JetAnalyzerStep7aBhe.clone()
JetAnalyzerStepZVetoHighOneBSsvHpTJet7aBhp = JetAnalyzerStep7aBhp.clone()
JetAnalyzerStepNoMetOneBSsvHeMJet7aJ = JetAnalyzerStep7aJ.clone()
JetAnalyzerStepNoMetOneBSsvHeMJet7aBhe = JetAnalyzerStep7aBhe.clone()
JetAnalyzerStepNoMetOneBSsvHeMJet7aBhp = JetAnalyzerStep7aBhp.clone()
JetAnalyzerStepNoMetOneBSsvHpTJet7aJ = JetAnalyzerStep7aJ.clone()
JetAnalyzerStepNoMetOneBSsvHpTJet7aBhe = JetAnalyzerStep7aBhe.clone()
JetAnalyzerStepNoMetOneBSsvHpTJet7aBhp = JetAnalyzerStep7aBhp.clone()
JetAnalyzerStepZVetoLowNoMetOneBSsvHeMJet7aJ = JetAnalyzerStep7aJ.clone()
JetAnalyzerStepZVetoLowNoMetOneBSsvHeMJet7aBhe = JetAnalyzerStep7aBhe.clone()
JetAnalyzerStepZVetoLowNoMetOneBSsvHeMJet7aBhp = JetAnalyzerStep7aBhp.clone()
JetAnalyzerStepZVetoLowNoMetOneBSsvHpTJet7aJ = JetAnalyzerStep7aJ.clone()
JetAnalyzerStepZVetoLowNoMetOneBSsvHpTJet7aBhe = JetAnalyzerStep7aBhe.clone()
JetAnalyzerStepZVetoLowNoMetOneBSsvHpTJet7aBhp = JetAnalyzerStep7aBhp.clone()
JetAnalyzerStepZVetoHighNoMetOneBSsvHeMJet7aJ = JetAnalyzerStep7aJ.clone()
JetAnalyzerStepZVetoHighNoMetOneBSsvHeMJet7aBhe = JetAnalyzerStep7aBhe.clone()
JetAnalyzerStepZVetoHighNoMetOneBSsvHeMJet7aBhp = JetAnalyzerStep7aBhp.clone()
JetAnalyzerStepZVetoHighNoMetOneBSsvHpTJet7aJ = JetAnalyzerStep7aJ.clone()
JetAnalyzerStepZVetoHighNoMetOneBSsvHpTJet7aBhe = JetAnalyzerStep7aBhe.clone()
JetAnalyzerStepZVetoHighNoMetOneBSsvHpTJet7aBhp = JetAnalyzerStep7aBhp.clone()



## missing et analyzer
from ZmumuAnalysis.Analyzer.MetAnalyzer_cfi import *
MetAnalyzerStep6a = MetAnalyzer.clone(metSource = 'patMETsPF',)
MetAnalyzerStep7a = MetAnalyzer.clone(metSource = 'patMETsPF',)
MetAnalyzerStep7b = MetAnalyzer.clone(metSource = 'patMETsPF',)
MetAnalyzerStep7c = MetAnalyzer.clone(metSource = 'patMETsPF',)
MetAnalyzerStep7 = MetAnalyzer.clone(metSource = 'patMETsPF',)

MetAnalyzerStepZVetoLow6a = MetAnalyzerStep6a.clone()
MetAnalyzerStepZVetoLow7a = MetAnalyzerStep7a.clone()
MetAnalyzerStepZVetoLow7b = MetAnalyzerStep7b.clone()
MetAnalyzerStepZVetoLow7c = MetAnalyzerStep7c.clone()
MetAnalyzerStepZVetoLow7 = MetAnalyzerStep7.clone()
MetAnalyzerStepZVetoHigh6a = MetAnalyzerStep6a.clone()
MetAnalyzerStepZVetoHigh7a = MetAnalyzerStep7a.clone()
MetAnalyzerStepZVetoHigh7b = MetAnalyzerStep7b.clone()
MetAnalyzerStepZVetoHigh7c = MetAnalyzerStep7c.clone()
MetAnalyzerStepZVetoHigh7 = MetAnalyzerStep7.clone()

MetAnalyzerStepNoMet7a = MetAnalyzerStep7a.clone()
MetAnalyzerStepNoMet7b = MetAnalyzerStep7b.clone()
MetAnalyzerStepNoMet7c = MetAnalyzerStep7c.clone()
MetAnalyzerStepNoMet7 = MetAnalyzerStep7.clone()
MetAnalyzerStepZVetoLowNoMet7a = MetAnalyzerStepZVetoLow7a.clone()
MetAnalyzerStepZVetoLowNoMet7b = MetAnalyzerStepZVetoLow7b.clone()
MetAnalyzerStepZVetoLowNoMet7c = MetAnalyzerStepZVetoLow7c.clone()
MetAnalyzerStepZVetoLowNoMet7 = MetAnalyzerStepZVetoLow7.clone()
MetAnalyzerStepZVetoHighNoMet7a = MetAnalyzerStepZVetoHigh7a.clone()
MetAnalyzerStepZVetoHighNoMet7b = MetAnalyzerStepZVetoHigh7b.clone()
MetAnalyzerStepZVetoHighNoMet7c = MetAnalyzerStepZVetoHigh7c.clone()
MetAnalyzerStepZVetoHighNoMet7 = MetAnalyzerStepZVetoHigh7.clone()

MetAnalyzerStepOneBSsvHeMJet7a = MetAnalyzerStep7a.clone()
MetAnalyzerStepOneBSsvHpTJet7a = MetAnalyzerStep7a.clone()
MetAnalyzerStepZVetoLowOneBSsvHeMJet7a = MetAnalyzerStep7a.clone()
MetAnalyzerStepZVetoLowOneBSsvHpTJet7a = MetAnalyzerStep7a.clone()
MetAnalyzerStepZVetoHighOneBSsvHeMJet7a = MetAnalyzerStep7a.clone()
MetAnalyzerStepZVetoHighOneBSsvHpTJet7a = MetAnalyzerStep7a.clone()
MetAnalyzerStepNoMetOneBSsvHeMJet7a = MetAnalyzerStep7a.clone()
MetAnalyzerStepNoMetOneBSsvHpTJet7a = MetAnalyzerStep7a.clone()
MetAnalyzerStepZVetoLowNoMetOneBSsvHeMJet7a = MetAnalyzerStep7a.clone()
MetAnalyzerStepZVetoLowNoMetOneBSsvHpTJet7a = MetAnalyzerStep7a.clone()
MetAnalyzerStepZVetoHighNoMetOneBSsvHeMJet7a = MetAnalyzerStep7a.clone()
MetAnalyzerStepZVetoHighNoMetOneBSsvHpTJet7a = MetAnalyzerStep7a.clone()





#******************************************************************************************
#   Utils Modules
#******************************************************************************************

from ZmumuAnalysis.Utils.RunEventListing_cff import *
RunEventListingStep5 = RunEventListingCreateTreeOnly.clone()
RunEventListingStep6 = RunEventListingCreateTreeOnly.clone()
RunEventListingStep7a = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoLow5 = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoLow6 = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoLow7a = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoHigh5 = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoHigh6 = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoHigh7a = RunEventListingCreateTreeOnly.clone()

RunEventListingStepNoMet7a = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoLowNoMet7a = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoHighNoMet7a = RunEventListingCreateTreeOnly.clone()






#******************************************************************************************
#   Sequences
#******************************************************************************************

## Apply generator filters
seqGeneratorFilter = cms.Sequence()




## Define steps and corresponding analyzers for default analysis
step0 = cms.Sequence(
    EventCounterStep0
)

step1a = cms.Sequence(
    EventCounterStep1a+
    TriggerAnalyzerStep1a
)
step1b = cms.Sequence(
    EventCounterStep1b+
    VertexAnalyzerStep1b
)
step1 = cms.Sequence(
    EventCounterStep1+
    VertexAnalyzerStep1
)

step2a = cms.Sequence(
    EventCounterStep2a
)
step2b = cms.Sequence(
    EventCounterStep2b+
    MuonAnalyzerStep2b
)
step2c = cms.Sequence(
    EventCounterStep2c+
    MuonAnalyzerStep2c
)
step2d = cms.Sequence(
    EventCounterStep2d+
    MuonAnalyzerStep2d
)
step2e = cms.Sequence(
    EventCounterStep2e+
    MuonAnalyzerStep2e
)
step2f = cms.Sequence(
    EventCounterStep2f
)
step2g = cms.Sequence(
    EventCounterStep2g
)
step2 = cms.Sequence(
    EventCounterStep2+
    MuonAnalyzerStep2
)

step3a = cms.Sequence(
    EventCounterStep3a
)
step3b = cms.Sequence(
    EventCounterStep3b
)
step3c = cms.Sequence(
    EventCounterStep3c
)
step3d = cms.Sequence(
    EventCounterStep3d+
    VertexAnalyzerStep3d+
    DimuonAnalyzerStep3d
)
step3e = cms.Sequence(
    EventCounterStep3e+
    VertexAnalyzerStep3e+
    DimuonAnalyzerStep3e
)
step3 = cms.Sequence(
    EventCounterStep3+
    VertexAnalyzerStep3+
    MuonAnalyzerStep3+
    DimuonAnalyzerStep3
)

step4a = cms.Sequence(
    EventCounterStep4a
)
step4b = cms.Sequence(
    EventCounterStep4b+
    JetAnalyzerStep4b
)
step4c = cms.Sequence(
    EventCounterStep4c+
    JetAnalyzerStep4c
)
step4d = cms.Sequence(
    EventCounterStep4d+
    JetAnalyzerStep4d
)
step4 = cms.Sequence(
    EventCounterStep4+
    MuonAnalyzerStep4+
    DimuonAnalyzerStep4+
    JetAnalyzerStep4J+
    JetAnalyzerStep4Bhe+
    JetAnalyzerStep4Bhp
)

step5 = cms.Sequence(
    EventCounterStep5+
    MuonAnalyzerStep5+
    DimuonAnalyzerStep5+
    JetAnalyzerStep5J+
    JetAnalyzerStep5Bhe+
    JetAnalyzerStep5Bhp+
    RunEventListingStep5
)

step6a = cms.Sequence(
    EventCounterStep6a+
    MetAnalyzerStep6a
)
step6 = cms.Sequence(
    EventCounterStep6+
    MuonAnalyzerStep6+
    DimuonAnalyzerStep6+
    JetAnalyzerStep6J+
    JetAnalyzerStep6Bhe+
    JetAnalyzerStep6Bhp+
    RunEventListingStep6
)

step7a = cms.Sequence(
    EventCounterStep7a+
    MuonAnalyzerStep7a+
    DimuonAnalyzerStep7a+
    JetAnalyzerStep7aJ+
    JetAnalyzerStep7aBhe+
    JetAnalyzerStep7aBhp+
    MetAnalyzerStep7a+
    RunEventListingStep7a
)
step7b = cms.Sequence(
    EventCounterStep7b+
    MuonAnalyzerStep7b+
    DimuonAnalyzerStep7b+
    JetAnalyzerStep7bJ+
    JetAnalyzerStep7bBhe+
    JetAnalyzerStep7bBhp+
    MetAnalyzerStep7b
)
step7c = cms.Sequence(
    EventCounterStep7c+
    MuonAnalyzerStep7c+
    DimuonAnalyzerStep7c+
    JetAnalyzerStep7cJ+
    JetAnalyzerStep7cBhe+
    JetAnalyzerStep7cBhp+
    MetAnalyzerStep7c
)
step7 = cms.Sequence(
    EventCounterStep7+
    MuonAnalyzerStep7+
    DimuonAnalyzerStep7+
    JetAnalyzerStep7J+
    JetAnalyzerStep7Bhe+
    JetAnalyzerStep7Bhp+
    MetAnalyzerStep7
)



## Define steps and corresponding analyzers for analysis excluding the Z mass window (lower sideband)
stepZVetoLow3 = cms.Sequence(
    EventCounterStepZVetoLow3+
    VertexAnalyzerStepZVetoLow3+
    MuonAnalyzerStepZVetoLow3+
    DimuonAnalyzerStepZVetoLow3
)

stepZVetoLow4a = cms.Sequence(
    EventCounterStepZVetoLow4a
)
stepZVetoLow4b = cms.Sequence(
    EventCounterStepZVetoLow4b+
    JetAnalyzerStepZVetoLow4b
)
stepZVetoLow4c = cms.Sequence(
    EventCounterStepZVetoLow4c+
    JetAnalyzerStepZVetoLow4c
)
stepZVetoLow4d = cms.Sequence(
    EventCounterStepZVetoLow4d+
    JetAnalyzerStepZVetoLow4d
)
stepZVetoLow4 = cms.Sequence(
    EventCounterStepZVetoLow4+
    MuonAnalyzerStepZVetoLow4+
    DimuonAnalyzerStepZVetoLow4+
    JetAnalyzerStepZVetoLow4J+
    JetAnalyzerStepZVetoLow4Bhe+
    JetAnalyzerStepZVetoLow4Bhp
)

stepZVetoLow5 = cms.Sequence(
    EventCounterStepZVetoLow5+
    MuonAnalyzerStepZVetoLow5+
    DimuonAnalyzerStepZVetoLow5+
    JetAnalyzerStepZVetoLow5J+
    JetAnalyzerStepZVetoLow5Bhe+
    JetAnalyzerStepZVetoLow5Bhp+
    RunEventListingStepZVetoLow5
)

stepZVetoLow6a = cms.Sequence(
    EventCounterStepZVetoLow6a+
    MetAnalyzerStepZVetoLow6a
)
stepZVetoLow6 = cms.Sequence(
    EventCounterStepZVetoLow6+
    MuonAnalyzerStepZVetoLow6+
    DimuonAnalyzerStepZVetoLow6+
    JetAnalyzerStepZVetoLow6J+
    JetAnalyzerStepZVetoLow6Bhe+
    JetAnalyzerStepZVetoLow6Bhp+
    RunEventListingStepZVetoLow6
)

stepZVetoLow7a = cms.Sequence(
    EventCounterStepZVetoLow7a+
    MuonAnalyzerStepZVetoLow7a+
    DimuonAnalyzerStepZVetoLow7a+
    JetAnalyzerStepZVetoLow7aJ+
    JetAnalyzerStepZVetoLow7aBhe+
    JetAnalyzerStepZVetoLow7aBhp+
    MetAnalyzerStepZVetoLow7a+
    RunEventListingStepZVetoLow7a
)
stepZVetoLow7b = cms.Sequence(
    EventCounterStepZVetoLow7b+
    MuonAnalyzerStepZVetoLow7b+
    DimuonAnalyzerStepZVetoLow7b+
    JetAnalyzerStepZVetoLow7bJ+
    JetAnalyzerStepZVetoLow7bBhe+
    JetAnalyzerStepZVetoLow7bBhp+
    MetAnalyzerStepZVetoLow7b
)
stepZVetoLow7c = cms.Sequence(
    EventCounterStepZVetoLow7c+
    MuonAnalyzerStepZVetoLow7c+
    DimuonAnalyzerStepZVetoLow7c+
    JetAnalyzerStepZVetoLow7cJ+
    JetAnalyzerStepZVetoLow7cBhe+
    JetAnalyzerStepZVetoLow7cBhp+
    MetAnalyzerStepZVetoLow7c
)
stepZVetoLow7 = cms.Sequence(
    EventCounterStepZVetoLow7+
    MuonAnalyzerStepZVetoLow7+
    DimuonAnalyzerStepZVetoLow7+
    JetAnalyzerStepZVetoLow7J+
    JetAnalyzerStepZVetoLow7Bhe+
    JetAnalyzerStepZVetoLow7Bhp+
    MetAnalyzerStepZVetoLow7
)



## Define steps and corresponding analyzers for analysis excluding the Z mass window (upper sideband)
stepZVetoHigh3 = cms.Sequence(
    EventCounterStepZVetoHigh3+
    VertexAnalyzerStepZVetoHigh3+
    MuonAnalyzerStepZVetoHigh3+
    DimuonAnalyzerStepZVetoHigh3
)

stepZVetoHigh4a = cms.Sequence(
    EventCounterStepZVetoHigh4a
)
stepZVetoHigh4b = cms.Sequence(
    EventCounterStepZVetoHigh4b+
    JetAnalyzerStepZVetoHigh4b
)
stepZVetoHigh4c = cms.Sequence(
    EventCounterStepZVetoHigh4c+
    JetAnalyzerStepZVetoHigh4c
)
stepZVetoHigh4d = cms.Sequence(
    EventCounterStepZVetoHigh4d+
    JetAnalyzerStepZVetoHigh4d
)
stepZVetoHigh4 = cms.Sequence(
    EventCounterStepZVetoHigh4+
    MuonAnalyzerStepZVetoHigh4+
    DimuonAnalyzerStepZVetoHigh4+
    JetAnalyzerStepZVetoHigh4J+
    JetAnalyzerStepZVetoHigh4Bhe+
    JetAnalyzerStepZVetoHigh4Bhp
)

stepZVetoHigh5 = cms.Sequence(
    EventCounterStepZVetoHigh5+
    MuonAnalyzerStepZVetoHigh5+
    DimuonAnalyzerStepZVetoHigh5+
    JetAnalyzerStepZVetoHigh5J+
    JetAnalyzerStepZVetoHigh5Bhe+
    JetAnalyzerStepZVetoHigh5Bhp+
    RunEventListingStepZVetoHigh5
)

stepZVetoHigh6a = cms.Sequence(
    EventCounterStepZVetoHigh6a+
    MetAnalyzerStepZVetoHigh6a
)
stepZVetoHigh6 = cms.Sequence(
    EventCounterStepZVetoHigh6+
    MuonAnalyzerStepZVetoHigh6+
    DimuonAnalyzerStepZVetoHigh6+
    JetAnalyzerStepZVetoHigh6J+
    JetAnalyzerStepZVetoHigh6Bhe+
    JetAnalyzerStepZVetoHigh6Bhp+
    RunEventListingStepZVetoHigh6
)

stepZVetoHigh7a = cms.Sequence(
    EventCounterStepZVetoHigh7a+
    MuonAnalyzerStepZVetoHigh7a+
    DimuonAnalyzerStepZVetoHigh7a+
    JetAnalyzerStepZVetoHigh7aJ+
    JetAnalyzerStepZVetoHigh7aBhe+
    JetAnalyzerStepZVetoHigh7aBhp+
    MetAnalyzerStepZVetoHigh7a+
    RunEventListingStepZVetoHigh7a
)
stepZVetoHigh7b = cms.Sequence(
    EventCounterStepZVetoHigh7b+
    MuonAnalyzerStepZVetoHigh7b+
    DimuonAnalyzerStepZVetoHigh7b+
    JetAnalyzerStepZVetoHigh7bJ+
    JetAnalyzerStepZVetoHigh7bBhe+
    JetAnalyzerStepZVetoHigh7bBhp+
    MetAnalyzerStepZVetoHigh7b
)
stepZVetoHigh7c = cms.Sequence(
    EventCounterStepZVetoHigh7c+
    MuonAnalyzerStepZVetoHigh7c+
    DimuonAnalyzerStepZVetoHigh7c+
    JetAnalyzerStepZVetoHigh7cJ+
    JetAnalyzerStepZVetoHigh7cBhe+
    JetAnalyzerStepZVetoHigh7cBhp+
    MetAnalyzerStepZVetoHigh7c
)
stepZVetoHigh7 = cms.Sequence(
    EventCounterStepZVetoHigh7+
    MuonAnalyzerStepZVetoHigh7+
    DimuonAnalyzerStepZVetoHigh7+
    JetAnalyzerStepZVetoHigh7J+
    JetAnalyzerStepZVetoHigh7Bhe+
    JetAnalyzerStepZVetoHigh7Bhp+
    MetAnalyzerStepZVetoHigh7
)



## Define steps and corresponding analyzers for analysis excluding cut on MET (signal region, lower and upper sideband)
stepNoMet7a = cms.Sequence(
    EventCounterStepNoMet7a+
    MuonAnalyzerStepNoMet7a+
    DimuonAnalyzerStepNoMet7a+
    JetAnalyzerStepNoMet7aJ+
    JetAnalyzerStepNoMet7aBhe+
    JetAnalyzerStepNoMet7aBhp+
    MetAnalyzerStepNoMet7a+
    RunEventListingStepNoMet7a
)
stepNoMet7b = cms.Sequence(
    EventCounterStepNoMet7b+
    MuonAnalyzerStepNoMet7b+
    DimuonAnalyzerStepNoMet7b+
    JetAnalyzerStepNoMet7bJ+
    JetAnalyzerStepNoMet7bBhe+
    JetAnalyzerStepNoMet7bBhp+
    MetAnalyzerStepNoMet7b
)
stepNoMet7c = cms.Sequence(
    EventCounterStepNoMet7c+
    MuonAnalyzerStepNoMet7c+
    DimuonAnalyzerStepNoMet7c+
    JetAnalyzerStepNoMet7cJ+
    JetAnalyzerStepNoMet7cBhe+
    JetAnalyzerStepNoMet7cBhp+
    MetAnalyzerStepNoMet7c
)
stepNoMet7 = cms.Sequence(
    EventCounterStepNoMet7+
    MuonAnalyzerStepNoMet7+
    DimuonAnalyzerStepNoMet7+
    JetAnalyzerStepNoMet7J+
    JetAnalyzerStepNoMet7Bhe+
    JetAnalyzerStepNoMet7Bhp+
    MetAnalyzerStepNoMet7
)

stepZVetoLowNoMet7a = cms.Sequence(
    EventCounterStepZVetoLowNoMet7a+
    MuonAnalyzerStepZVetoLowNoMet7a+
    DimuonAnalyzerStepZVetoLowNoMet7a+
    JetAnalyzerStepZVetoLowNoMet7aJ+
    JetAnalyzerStepZVetoLowNoMet7aBhe+
    JetAnalyzerStepZVetoLowNoMet7aBhp+
    MetAnalyzerStepZVetoLowNoMet7a+
    RunEventListingStepZVetoLowNoMet7a
)
stepZVetoLowNoMet7b = cms.Sequence(
    EventCounterStepZVetoLowNoMet7b+
    MuonAnalyzerStepZVetoLowNoMet7b+
    DimuonAnalyzerStepZVetoLowNoMet7b+
    JetAnalyzerStepZVetoLowNoMet7bJ+
    JetAnalyzerStepZVetoLowNoMet7bBhe+
    JetAnalyzerStepZVetoLowNoMet7bBhp+
    MetAnalyzerStepZVetoLowNoMet7b
)
stepZVetoLowNoMet7c = cms.Sequence(
    EventCounterStepZVetoLowNoMet7c+
    MuonAnalyzerStepZVetoLowNoMet7c+
    DimuonAnalyzerStepZVetoLowNoMet7c+
    JetAnalyzerStepZVetoLowNoMet7cJ+
    JetAnalyzerStepZVetoLowNoMet7cBhe+
    JetAnalyzerStepZVetoLowNoMet7cBhp+
    MetAnalyzerStepZVetoLowNoMet7c
)
stepZVetoLowNoMet7 = cms.Sequence(
    EventCounterStepZVetoLowNoMet7+
    MuonAnalyzerStepZVetoLowNoMet7+
    DimuonAnalyzerStepZVetoLowNoMet7+
    JetAnalyzerStepZVetoLowNoMet7J+
    JetAnalyzerStepZVetoLowNoMet7Bhe+
    JetAnalyzerStepZVetoLowNoMet7Bhp+
    MetAnalyzerStepZVetoLowNoMet7
)

stepZVetoHighNoMet7a = cms.Sequence(
    EventCounterStepZVetoHighNoMet7a+
    MuonAnalyzerStepZVetoHighNoMet7a+
    DimuonAnalyzerStepZVetoHighNoMet7a+
    JetAnalyzerStepZVetoHighNoMet7aJ+
    JetAnalyzerStepZVetoHighNoMet7aBhe+
    JetAnalyzerStepZVetoHighNoMet7aBhp+
    MetAnalyzerStepZVetoHighNoMet7a+
    RunEventListingStepZVetoHighNoMet7a
)
stepZVetoHighNoMet7b = cms.Sequence(
    EventCounterStepZVetoHighNoMet7b+
    MuonAnalyzerStepZVetoHighNoMet7b+
    DimuonAnalyzerStepZVetoHighNoMet7b+
    JetAnalyzerStepZVetoHighNoMet7bJ+
    JetAnalyzerStepZVetoHighNoMet7bBhe+
    JetAnalyzerStepZVetoHighNoMet7bBhp+
    MetAnalyzerStepZVetoHighNoMet7b
)
stepZVetoHighNoMet7c = cms.Sequence(
    EventCounterStepZVetoHighNoMet7c+
    MuonAnalyzerStepZVetoHighNoMet7c+
    DimuonAnalyzerStepZVetoHighNoMet7c+
    JetAnalyzerStepZVetoHighNoMet7cJ+
    JetAnalyzerStepZVetoHighNoMet7cBhe+
    JetAnalyzerStepZVetoHighNoMet7cBhp+
    MetAnalyzerStepZVetoHighNoMet7c
)
stepZVetoHighNoMet7 = cms.Sequence(
    EventCounterStepZVetoHighNoMet7+
    MuonAnalyzerStepZVetoHighNoMet7+
    DimuonAnalyzerStepZVetoHighNoMet7+
    JetAnalyzerStepZVetoHighNoMet7J+
    JetAnalyzerStepZVetoHighNoMet7Bhe+
    JetAnalyzerStepZVetoHighNoMet7Bhp+
    MetAnalyzerStepZVetoHighNoMet7
)




## Define steps and corresponding analyzers for analysis requiring exactly one b-tag (MET, no MET && signal region, lower and upper sideband)
stepOneBSsvHeMJet7a = cms.Sequence(
    EventCounterStepOneBSsvHeMJet7a*
    MuonAnalyzerStepOneBSsvHeMJet7a*
    DimuonAnalyzerStepOneBSsvHeMJet7a*
    JetAnalyzerStepOneBSsvHeMJet7aJ*
    JetAnalyzerStepOneBSsvHeMJet7aBhe*
    JetAnalyzerStepOneBSsvHeMJet7aBhp*
    MetAnalyzerStepOneBSsvHeMJet7a
)
stepOneBSsvHpTJet7a = cms.Sequence(
    EventCounterStepOneBSsvHpTJet7a*
    MuonAnalyzerStepOneBSsvHpTJet7a*
    DimuonAnalyzerStepOneBSsvHpTJet7a*
    JetAnalyzerStepOneBSsvHpTJet7aJ*
    JetAnalyzerStepOneBSsvHpTJet7aBhe*
    JetAnalyzerStepOneBSsvHpTJet7aBhp*
    MetAnalyzerStepOneBSsvHpTJet7a
)
stepZVetoLowOneBSsvHeMJet7a = cms.Sequence(
    EventCounterStepZVetoLowOneBSsvHeMJet7a*
    MuonAnalyzerStepZVetoLowOneBSsvHeMJet7a*
    DimuonAnalyzerStepZVetoLowOneBSsvHeMJet7a*
    JetAnalyzerStepZVetoLowOneBSsvHeMJet7aJ*
    JetAnalyzerStepZVetoLowOneBSsvHeMJet7aBhe*
    JetAnalyzerStepZVetoLowOneBSsvHeMJet7aBhp*
    MetAnalyzerStepZVetoLowOneBSsvHeMJet7a
)
stepZVetoLowOneBSsvHpTJet7a = cms.Sequence(
    EventCounterStepZVetoLowOneBSsvHpTJet7a*
    MuonAnalyzerStepZVetoLowOneBSsvHpTJet7a*
    DimuonAnalyzerStepZVetoLowOneBSsvHpTJet7a*
    JetAnalyzerStepZVetoLowOneBSsvHpTJet7aJ*
    JetAnalyzerStepZVetoLowOneBSsvHpTJet7aBhe*
    JetAnalyzerStepZVetoLowOneBSsvHpTJet7aBhp*
    MetAnalyzerStepZVetoLowOneBSsvHpTJet7a
)
stepZVetoHighOneBSsvHeMJet7a = cms.Sequence(
    EventCounterStepZVetoHighOneBSsvHeMJet7a*
    MuonAnalyzerStepZVetoHighOneBSsvHeMJet7a*
    DimuonAnalyzerStepZVetoHighOneBSsvHeMJet7a*
    JetAnalyzerStepZVetoHighOneBSsvHeMJet7aJ*
    JetAnalyzerStepZVetoHighOneBSsvHeMJet7aBhe*
    JetAnalyzerStepZVetoHighOneBSsvHeMJet7aBhp*
    MetAnalyzerStepZVetoHighOneBSsvHeMJet7a
)
stepZVetoHighOneBSsvHpTJet7a = cms.Sequence(
    EventCounterStepZVetoHighOneBSsvHpTJet7a*
    MuonAnalyzerStepZVetoHighOneBSsvHpTJet7a*
    DimuonAnalyzerStepZVetoHighOneBSsvHpTJet7a*
    JetAnalyzerStepZVetoHighOneBSsvHpTJet7aJ*
    JetAnalyzerStepZVetoHighOneBSsvHpTJet7aBhe*
    JetAnalyzerStepZVetoHighOneBSsvHpTJet7aBhp*
    MetAnalyzerStepZVetoHighOneBSsvHpTJet7a
)


stepNoMetOneBSsvHeMJet7a = cms.Sequence(
    EventCounterStepNoMetOneBSsvHeMJet7a*
    MuonAnalyzerStepNoMetOneBSsvHeMJet7a*
    DimuonAnalyzerStepNoMetOneBSsvHeMJet7a*
    JetAnalyzerStepNoMetOneBSsvHeMJet7aJ*
    JetAnalyzerStepNoMetOneBSsvHeMJet7aBhe*
    JetAnalyzerStepNoMetOneBSsvHeMJet7aBhp*
    MetAnalyzerStepNoMetOneBSsvHeMJet7a
)
stepNoMetOneBSsvHpTJet7a = cms.Sequence(
    EventCounterStepNoMetOneBSsvHpTJet7a*
    MuonAnalyzerStepNoMetOneBSsvHpTJet7a*
    DimuonAnalyzerStepNoMetOneBSsvHpTJet7a*
    JetAnalyzerStepNoMetOneBSsvHpTJet7aJ*
    JetAnalyzerStepNoMetOneBSsvHpTJet7aBhe*
    JetAnalyzerStepNoMetOneBSsvHpTJet7aBhp*
    MetAnalyzerStepNoMetOneBSsvHpTJet7a
)
stepZVetoLowNoMetOneBSsvHeMJet7a = cms.Sequence(
    EventCounterStepZVetoLowNoMetOneBSsvHeMJet7a*
    MuonAnalyzerStepZVetoLowNoMetOneBSsvHeMJet7a*
    DimuonAnalyzerStepZVetoLowNoMetOneBSsvHeMJet7a*
    JetAnalyzerStepZVetoLowNoMetOneBSsvHeMJet7aJ*
    JetAnalyzerStepZVetoLowNoMetOneBSsvHeMJet7aBhe*
    JetAnalyzerStepZVetoLowNoMetOneBSsvHeMJet7aBhp*
    MetAnalyzerStepZVetoLowNoMetOneBSsvHeMJet7a
)
stepZVetoLowNoMetOneBSsvHpTJet7a = cms.Sequence(
    EventCounterStepZVetoLowNoMetOneBSsvHpTJet7a*
    MuonAnalyzerStepZVetoLowNoMetOneBSsvHpTJet7a*
    DimuonAnalyzerStepZVetoLowNoMetOneBSsvHpTJet7a*
    JetAnalyzerStepZVetoLowNoMetOneBSsvHpTJet7aJ*
    JetAnalyzerStepZVetoLowNoMetOneBSsvHpTJet7aBhe*
    JetAnalyzerStepZVetoLowNoMetOneBSsvHpTJet7aBhp*
    MetAnalyzerStepZVetoLowNoMetOneBSsvHpTJet7a
)
stepZVetoHighNoMetOneBSsvHeMJet7a = cms.Sequence(
    EventCounterStepZVetoHighNoMetOneBSsvHeMJet7a*
    MuonAnalyzerStepZVetoHighNoMetOneBSsvHeMJet7a*
    DimuonAnalyzerStepZVetoHighNoMetOneBSsvHeMJet7a*
    JetAnalyzerStepZVetoHighNoMetOneBSsvHeMJet7aJ*
    JetAnalyzerStepZVetoHighNoMetOneBSsvHeMJet7aBhe*
    JetAnalyzerStepZVetoHighNoMetOneBSsvHeMJet7aBhp*
    MetAnalyzerStepZVetoHighNoMetOneBSsvHeMJet7a
)
stepZVetoHighNoMetOneBSsvHpTJet7a = cms.Sequence(
    EventCounterStepZVetoHighNoMetOneBSsvHpTJet7a*
    MuonAnalyzerStepZVetoHighNoMetOneBSsvHpTJet7a*
    DimuonAnalyzerStepZVetoHighNoMetOneBSsvHpTJet7a*
    JetAnalyzerStepZVetoHighNoMetOneBSsvHpTJet7aJ*
    JetAnalyzerStepZVetoHighNoMetOneBSsvHpTJet7aBhe*
    JetAnalyzerStepZVetoHighNoMetOneBSsvHpTJet7aBhp*
    MetAnalyzerStepZVetoHighNoMetOneBSsvHpTJet7a
)






#******************************************************************************************
#   Analysis Paths
#******************************************************************************************




## Gathering of common sequences

zVetoDefaultSteps = cms.Sequence(
    seqGeneratorFilter*
    TriggerFilter*
    buildVertexCollections*
    oneGoodPVSelection*
    buildMuonCollections*
    oneInitialMuonSelection*
    oneLooseMuonSelection*
    oneTightMuonSelection*
    oneIsolatedMuonSelection*
    tightMuonSelection*
    isolatedMuonSelection*
    isolatedHltMuonSelection*
    buildDimuonCollections*
    selectedDimuonSelection*
    cleanDimuonSelection*
    goodDimuonSelection
)


noMetDefaultSteps = cms.Sequence(
    zVetoDefaultSteps*
    finalDimuonSelection*
    buildJetCollections*
    oneSelectedJetSelection*
    oneCleanJetSelection*
    oneGoodJetSelection*
    oneFinalJetSelection*
    oneBSsvHeMJetSelection*
    buildMetCollections
)

zVetoLowNoMetDefaultSteps = noMetDefaultSteps.copy()
zVetoLowNoMetDefaultSteps.replace(finalDimuonSelection,finalDimuonZVetoLowSelection)

zVetoHighNoMetDefaultSteps = noMetDefaultSteps.copy()
zVetoHighNoMetDefaultSteps.replace(finalDimuonSelection,finalDimuonZVetoHighSelection)





## Analysis Paths

oppositeChargeAnalysisSeq = cms.Sequence(
    step0*
    
    seqGeneratorFilter*
    step1a*
    TriggerFilter*
    buildVertexCollections*
    step1b*
    oneGoodPVSelection*
    step1*
    
    buildMuonCollections*
    step2a*
    oneInitialMuonSelection*
    step2b*
    oneLooseMuonSelection*
    step2c*
    oneTightMuonSelection*
    step2d*
    oneIsolatedMuonSelection*
    step2e*
    tightMuonSelection*
    step2f*
    isolatedMuonSelection*
    step2g*
    isolatedHltMuonSelection*
    step2*
    
    buildDimuonCollections*
    step3a*
    selectedDimuonSelection*
    step3b*
    cleanDimuonSelection*
    step3c*
    goodDimuonSelection*
    step3d*
    step3e*
    finalDimuonSelection*
    step3*
    
    buildJetCollections*
    step4a*
    oneSelectedJetSelection*
    step4b*
    oneCleanJetSelection*
    step4c*
    oneGoodJetSelection*
    step4d*
    oneFinalJetSelection*
    step4*
    
    oneBSsvHeMJetSelection*
    step5*
    
    buildMetCollections*
    step6a*
    goodMetSelection*
    step6*
    
    oneBSsvHpTJetSelection*
    step7a*
    twoFinalJetSelection*
    step7b*
    twoBSsvHeMJetSelection*
    step7c*
    twoBSsvHpTJetSelection*
    step7
    
)



zVetoLowOppositeChargeAnalysisSeq = cms.Sequence(
    zVetoDefaultSteps*
    
    finalDimuonZVetoLowSelection*
    stepZVetoLow3*
    
    buildJetCollections*
    stepZVetoLow4a*
    oneSelectedJetSelection*
    stepZVetoLow4b*
    oneCleanJetSelection*
    stepZVetoLow4c*
    oneGoodJetSelection*
    stepZVetoLow4d*
    oneFinalJetSelection*
    stepZVetoLow4*
    
    oneBSsvHeMJetSelection*
    stepZVetoLow5*
    
    buildMetCollections*
    stepZVetoLow6a*
    goodMetSelection*
    stepZVetoLow6*
    
    oneBSsvHpTJetSelection*
    stepZVetoLow7a*
    twoFinalJetSelection*
    stepZVetoLow7b*
    twoBSsvHeMJetSelection*
    stepZVetoLow7c*
    twoBSsvHpTJetSelection*
    stepZVetoLow7
    
)



zVetoHighOppositeChargeAnalysisSeq = cms.Sequence(
    zVetoDefaultSteps*
    
    finalDimuonZVetoHighSelection*
    stepZVetoHigh3*
    
    buildJetCollections*
    stepZVetoHigh4a*
    oneSelectedJetSelection*
    stepZVetoHigh4b*
    oneCleanJetSelection*
    stepZVetoHigh4c*
    oneGoodJetSelection*
    stepZVetoHigh4d*
    oneFinalJetSelection*
    stepZVetoHigh4*
    
    oneBSsvHeMJetSelection*
    stepZVetoHigh5*
    
    buildMetCollections*
    stepZVetoHigh6a*
    goodMetSelection*
    stepZVetoHigh6*
    
    
    oneBSsvHpTJetSelection*
    stepZVetoHigh7a*
    twoFinalJetSelection*
    stepZVetoHigh7b*
    twoBSsvHeMJetSelection*
    stepZVetoHigh7c*
    twoBSsvHpTJetSelection*
    stepZVetoHigh7
)



noMetOppositeChargeAnalysisSeq = cms.Sequence(
    noMetDefaultSteps*
    
    # Do not apply MET Selection
    #goodMetSelection*
    #stepNoMet6*
    
    oneBSsvHpTJetSelection*
    stepNoMet7a*
    twoFinalJetSelection*
    stepNoMet7b*
    twoBSsvHeMJetSelection*
    stepNoMet7c*
    twoBSsvHpTJetSelection*
    stepNoMet7
    
)



zVetoLowNoMetOppositeChargeAnalysisSeq = cms.Sequence(
    zVetoLowNoMetDefaultSteps*
    
    # Do not apply MET Selection
    #goodMetSelection*
    #stepZVetoLowNoMet6*
    
    oneBSsvHpTJetSelection*
    stepZVetoLowNoMet7a*
    twoFinalJetSelection*
    stepZVetoLowNoMet7b*
    twoBSsvHeMJetSelection*
    stepZVetoLowNoMet7c*
    twoBSsvHpTJetSelection*
    stepZVetoLowNoMet7
    
)



zVetoHighNoMetOppositeChargeAnalysisSeq = cms.Sequence(
    zVetoHighNoMetDefaultSteps*
    
    # Do not apply MET Selection
    #goodMetSelection
    #stepZVetoHighNoMet6*
    
    oneBSsvHpTJetSelection*
    stepZVetoHighNoMet7a*
    twoFinalJetSelection*
    stepZVetoHighNoMet7b*
    twoBSsvHeMJetSelection*
    stepZVetoHighNoMet7c*
    twoBSsvHpTJetSelection*
    stepZVetoHighNoMet7
    
)



oneBSsvHeMJetOppositeChargeAnalysisSeq = cms.Sequence(
    noMetDefaultSteps*
    goodMetSelection*
    ~twoBSsvHeMJetSelection*
    stepOneBSsvHeMJet7a
)

oneBSsvHpTJetOppositeChargeAnalysisSeq = cms.Sequence(
    noMetDefaultSteps*
    goodMetSelection*
    oneBSsvHpTJetSelection*
    ~twoBSsvHpTJetSelection*
    stepOneBSsvHpTJet7a
)

zVetoLowOneBSsvHeMJetOppositeChargeAnalysisSeq = cms.Sequence(
    zVetoLowNoMetDefaultSteps*
    goodMetSelection*
    ~twoBSsvHeMJetSelection*
    stepZVetoLowOneBSsvHeMJet7a
)

zVetoLowOneBSsvHpTJetOppositeChargeAnalysisSeq = cms.Sequence(
    zVetoLowNoMetDefaultSteps*
    goodMetSelection*
    oneBSsvHpTJetSelection*
    ~twoBSsvHpTJetSelection*
    stepZVetoLowOneBSsvHpTJet7a
)

zVetoHighOneBSsvHeMJetOppositeChargeAnalysisSeq = cms.Sequence(
    zVetoHighNoMetDefaultSteps*
    goodMetSelection*
    ~twoBSsvHeMJetSelection*
    stepZVetoHighOneBSsvHeMJet7a
)

zVetoHighOneBSsvHpTJetOppositeChargeAnalysisSeq = cms.Sequence(
    zVetoHighNoMetDefaultSteps*
    goodMetSelection*
    oneBSsvHpTJetSelection*
    ~twoBSsvHpTJetSelection*
    stepZVetoHighOneBSsvHpTJet7a
)



noMetExactlyOneBSsvHeMJetOppositeChargeAnalysisSeq = cms.Sequence(
    noMetDefaultSteps*
    #goodMetSelection*
    ~twoBSsvHeMJetSelection*
    stepNoMetOneBSsvHeMJet7a
)

noMetExactlyOneBSsvHpTJetOppositeChargeAnalysisSeq = cms.Sequence(
    noMetDefaultSteps*
    #goodMetSelection*
    oneBSsvHpTJetSelection*
    ~twoBSsvHpTJetSelection*
    stepNoMetOneBSsvHpTJet7a
)

zVetoLowNoMetExactlyOneBSsvHeMJetOppositeChargeAnalysisSeq = cms.Sequence(
    zVetoLowNoMetDefaultSteps*
    #goodMetSelection*
    ~twoBSsvHeMJetSelection*
    stepZVetoLowNoMetOneBSsvHeMJet7a
)

zVetoLowNoMetExactlyOneBSsvHpTJetOppositeChargeAnalysisSeq = cms.Sequence(
    zVetoLowNoMetDefaultSteps*
    #goodMetSelection*
    oneBSsvHpTJetSelection*
    ~twoBSsvHpTJetSelection*
    stepZVetoLowNoMetOneBSsvHpTJet7a
)

zVetoHighNoMetExactlyOneBSsvHeMJetOppositeChargeAnalysisSeq = cms.Sequence(
    zVetoHighNoMetDefaultSteps*
    #goodMetSelection*
    ~twoBSsvHeMJetSelection*
    stepZVetoHighNoMetOneBSsvHeMJet7a
)

zVetoHighNoMetExactlyOneBSsvHpTJetOppositeChargeAnalysisSeq = cms.Sequence(
    zVetoHighNoMetDefaultSteps*
    #goodMetSelection*
    oneBSsvHpTJetSelection*
    ~twoBSsvHpTJetSelection*
    stepZVetoHighNoMetOneBSsvHpTJet7a
)









