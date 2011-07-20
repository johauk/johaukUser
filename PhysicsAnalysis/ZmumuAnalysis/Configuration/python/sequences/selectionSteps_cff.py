import FWCore.ParameterSet.Config as cms



#******************************************************************************************
#   Filter & Producer Modules
#******************************************************************************************

## Filter for correct decay process
#from ZmumuAnalysis.Configuration.filters.GeneratorZmumuFilter_cff import GeneratorZmumuDiMuFilter, GeneratorZmumuDiTauFilter
#from ZmumuAnalysis.Configuration.filters.GeneratorBclFilter_cff import buildSignalBCollections, signalBSelection

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
EventCounterStep2 = EventCounter.clone()
EventCounterStep3a = EventCounter.clone()
EventCounterStep3b = EventCounter.clone()
EventCounterStep3c = EventCounter.clone()
EventCounterStep3d = EventCounter.clone()
EventCounterStep3e = EventCounter.clone()
EventCounterStep3f = EventCounter.clone()
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
EventCounterStepZVetoLow3f = EventCounter.clone()
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
EventCounterStepZVetoHigh3f = EventCounter.clone()
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
VertexAnalyzerStep3f = VertexAnalyzer.clone(vertexSource = 'finalPVs',)
VertexAnalyzerStep3 = VertexAnalyzer.clone(vertexSource = 'bestPV',)

VertexAnalyzerStepZVetoLow3f = VertexAnalyzerStep3f.clone(vertexSource = 'finalPVsZVetoLow',)
VertexAnalyzerStepZVetoHigh3f = VertexAnalyzerStep3f.clone(vertexSource = 'finalPVsZVetoHigh',)



## muon analizer
from ZmumuAnalysis.Analyzer.MuonAnalyzer_cfi import *
MuonAnalyzerStep2b = MuonAnalyzer.clone(muonSource = 'tightMuons',)
MuonAnalyzerStep2 = MuonAnalyzer.clone(muonSource = 'tightMuons',)
MuonAnalyzerStep3 = MuonAnalyzer.clone(muonSource = 'tightMuons',)
MuonAnalyzerStep4 = MuonAnalyzer.clone(muonSource = 'tightMuons',)
MuonAnalyzerStep5 = MuonAnalyzer.clone(muonSource = 'tightMuons',)
MuonAnalyzerStep6 = MuonAnalyzer.clone(muonSource = 'tightMuons',)
MuonAnalyzerStep7a = MuonAnalyzer.clone(muonSource = 'tightMuons',)
MuonAnalyzerStep7b = MuonAnalyzer.clone(muonSource = 'tightMuons',)
MuonAnalyzerStep7c = MuonAnalyzer.clone(muonSource = 'tightMuons',)
MuonAnalyzerStep7 = MuonAnalyzer.clone(muonSource = 'tightMuons',)

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



## di-muon analyzer
from ZmumuAnalysis.Analyzer.DimuonAnalyzer_cfi import *
DimuonAnalyzerStep3d = DimuonAnalyzer.clone(dimuonSource = "goodDimuons",)
DimuonAnalyzerStep3e = DimuonAnalyzer.clone(dimuonSource = "isolatedDimuons",)
DimuonAnalyzerStep3f = DimuonAnalyzer.clone(dimuonSource = "finalDimuons",)
DimuonAnalyzerStep3 = DimuonAnalyzer.clone(dimuonSource = "bestDimuon",)
DimuonAnalyzerStep4 = DimuonAnalyzer.clone(dimuonSource = "finalDimuons",)
DimuonAnalyzerStep5 = DimuonAnalyzer.clone(dimuonSource = "finalDimuons",)
DimuonAnalyzerStep6 = DimuonAnalyzer.clone(dimuonSource = "finalDimuons",)
DimuonAnalyzerStep7a = DimuonAnalyzer.clone(dimuonSource = "finalDimuons",)
DimuonAnalyzerStep7b = DimuonAnalyzer.clone(dimuonSource = "finalDimuons",)
DimuonAnalyzerStep7c = DimuonAnalyzer.clone(dimuonSource = "finalDimuons",)
DimuonAnalyzerStep7 = DimuonAnalyzer.clone(dimuonSource = "finalDimuons",)

DimuonAnalyzerStepZVetoLow3f = DimuonAnalyzerStep3f.clone(dimuonSource = "finalDimuonsZVetoLow",)
DimuonAnalyzerStepZVetoLow4 = DimuonAnalyzerStep4.clone(dimuonSource = "finalDimuonsZVetoLow",)
DimuonAnalyzerStepZVetoLow5 = DimuonAnalyzerStep5.clone(dimuonSource = "finalDimuonsZVetoLow",)
DimuonAnalyzerStepZVetoLow6 = DimuonAnalyzerStep6.clone(dimuonSource = "finalDimuonsZVetoLow",)
DimuonAnalyzerStepZVetoLow7a = DimuonAnalyzerStep7a.clone(dimuonSource = "finalDimuonsZVetoLow",)
DimuonAnalyzerStepZVetoLow7b = DimuonAnalyzerStep7b.clone(dimuonSource = "finalDimuonsZVetoLow",)
DimuonAnalyzerStepZVetoLow7c = DimuonAnalyzerStep7c.clone(dimuonSource = "finalDimuonsZVetoLow",)
DimuonAnalyzerStepZVetoLow7 = DimuonAnalyzerStep7.clone(dimuonSource = "finalDimuonsZVetoLow",)
DimuonAnalyzerStepZVetoHigh3f = DimuonAnalyzerStep3f.clone(dimuonSource = "finalDimuonsZVetoHigh",)
DimuonAnalyzerStepZVetoHigh4 = DimuonAnalyzerStep4.clone(dimuonSource = "finalDimuonsZVetoHigh",)
DimuonAnalyzerStepZVetoHigh5 = DimuonAnalyzerStep5.clone(dimuonSource = "finalDimuonsZVetoHigh",)
DimuonAnalyzerStepZVetoHigh6 = DimuonAnalyzerStep6.clone(dimuonSource = "finalDimuonsZVetoHigh",)
DimuonAnalyzerStepZVetoHigh7a = DimuonAnalyzerStep7a.clone(dimuonSource = "finalDimuonsZVetoHigh",)
DimuonAnalyzerStepZVetoHigh7b = DimuonAnalyzerStep7b.clone(dimuonSource = "finalDimuonsZVetoHigh",)
DimuonAnalyzerStepZVetoHigh7c = DimuonAnalyzerStep7c.clone(dimuonSource = "finalDimuonsZVetoHigh",)
DimuonAnalyzerStepZVetoHigh7 = DimuonAnalyzerStep7.clone(dimuonSource = "finalDimuonsZVetoHigh",)

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




## jet analyzer
from ZmumuAnalysis.Analyzer.JetAnalyzer_cfi import *
JetAnalyzerStep4a = JetAnalyzer.clone(jetSource = 'selectedPatJetsAK5PF',)
JetAnalyzerStep4b = JetAnalyzer.clone(jetSource = 'cleanJets',)
JetAnalyzerStep4c = JetAnalyzer.clone(jetSource = 'goodIdJets',)
JetAnalyzerStep4d = JetAnalyzer.clone(jetSource = 'goodJets',)
JetAnalyzerStep4 = JetAnalyzer.clone(jetSource = 'finalJets',)
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

JetAnalyzerStepZVetoLow4d = JetAnalyzerStep4d.clone(jetSource = 'goodJetsZVetoLow',)
JetAnalyzerStepZVetoLow4 = JetAnalyzerStep4.clone(jetSource = 'finalJetsZVetoLow',)
JetAnalyzerStepZVetoLow5J = JetAnalyzerStep5J.clone(jetSource = 'finalJetsZVetoLow',)
JetAnalyzerStepZVetoLow5Bhe = JetAnalyzerStep5Bhe.clone(jetSource = 'bSsvHeMJetsZVetoLow',)
JetAnalyzerStepZVetoLow5Bhp = JetAnalyzerStep5Bhp.clone(jetSource = 'bSsvHpTJetsZVetoLow',)
JetAnalyzerStepZVetoLow6J = JetAnalyzerStep6J.clone(jetSource = 'finalJetsZVetoLow',)
JetAnalyzerStepZVetoLow6Bhe = JetAnalyzerStep6Bhe.clone(jetSource = 'bSsvHeMJetsZVetoLow',)
JetAnalyzerStepZVetoLow6Bhp = JetAnalyzerStep6Bhp.clone(jetSource = 'bSsvHpTJetsZVetoLow',)
JetAnalyzerStepZVetoLow7aJ = JetAnalyzerStep7aJ.clone(jetSource = 'finalJetsZVetoLow',)
JetAnalyzerStepZVetoLow7aBhe = JetAnalyzerStep7aBhe.clone(jetSource = 'bSsvHeMJetsZVetoLow',)
JetAnalyzerStepZVetoLow7aBhp = JetAnalyzerStep7aBhp.clone(jetSource = 'bSsvHpTJetsZVetoLow',)
JetAnalyzerStepZVetoLow7bJ = JetAnalyzerStep7bJ.clone(jetSource = 'finalJetsZVetoLow',)
JetAnalyzerStepZVetoLow7bBhe = JetAnalyzerStep7bBhe.clone(jetSource = 'bSsvHeMJetsZVetoLow',)
JetAnalyzerStepZVetoLow7bBhp = JetAnalyzerStep7bBhp.clone(jetSource = 'bSsvHpTJetsZVetoLow',)
JetAnalyzerStepZVetoLow7cJ = JetAnalyzerStep7cJ.clone(jetSource = 'finalJetsZVetoLow',)
JetAnalyzerStepZVetoLow7cBhe = JetAnalyzerStep7cBhe.clone(jetSource = 'bSsvHeMJetsZVetoLow',)
JetAnalyzerStepZVetoLow7cBhp = JetAnalyzerStep7cBhp.clone(jetSource = 'bSsvHpTJetsZVetoLow',)
JetAnalyzerStepZVetoLow7J = JetAnalyzerStep7J.clone(jetSource = 'finalJetsZVetoLow',)
JetAnalyzerStepZVetoLow7Bhe = JetAnalyzerStep7Bhe.clone(jetSource = 'bSsvHeMJetsZVetoLow',)
JetAnalyzerStepZVetoLow7Bhp = JetAnalyzerStep7Bhp.clone(jetSource = 'bSsvHpTJetsZVetoLow',)
JetAnalyzerStepZVetoHigh4d = JetAnalyzerStep4d.clone(jetSource = 'goodJetsZVetoHigh',)
JetAnalyzerStepZVetoHigh4 = JetAnalyzerStep4.clone(jetSource = 'finalJetsZVetoHigh',)
JetAnalyzerStepZVetoHigh5J = JetAnalyzerStep5J.clone(jetSource = 'finalJetsZVetoHigh',)
JetAnalyzerStepZVetoHigh5Bhe = JetAnalyzerStep5Bhe.clone(jetSource = 'bSsvHeMJetsZVetoHigh',)
JetAnalyzerStepZVetoHigh5Bhp = JetAnalyzerStep5Bhp.clone(jetSource = 'bSsvHpTJetsZVetoHigh',)
JetAnalyzerStepZVetoHigh6J = JetAnalyzerStep6J.clone(jetSource = 'finalJetsZVetoHigh',)
JetAnalyzerStepZVetoHigh6Bhe = JetAnalyzerStep6Bhe.clone(jetSource = 'bSsvHeMJetsZVetoHigh',)
JetAnalyzerStepZVetoHigh6Bhp = JetAnalyzerStep6Bhp.clone(jetSource = 'bSsvHpTJetsZVetoHigh',)
JetAnalyzerStepZVetoHigh7aJ = JetAnalyzerStep7aJ.clone(jetSource = 'finalJetsZVetoHigh',)
JetAnalyzerStepZVetoHigh7aBhe = JetAnalyzerStep7aBhe.clone(jetSource = 'bSsvHeMJetsZVetoHigh',)
JetAnalyzerStepZVetoHigh7aBhp = JetAnalyzerStep7aBhp.clone(jetSource = 'bSsvHpTJetsZVetoHigh',)
JetAnalyzerStepZVetoHigh7bJ = JetAnalyzerStep7bJ.clone(jetSource = 'finalJetsZVetoHigh',)
JetAnalyzerStepZVetoHigh7bBhe = JetAnalyzerStep7bBhe.clone(jetSource = 'bSsvHeMJetsZVetoHigh',)
JetAnalyzerStepZVetoHigh7bBhp = JetAnalyzerStep7bBhp.clone(jetSource = 'bSsvHpTJetsZVetoHigh',)
JetAnalyzerStepZVetoHigh7cJ = JetAnalyzerStep7cJ.clone(jetSource = 'finalJetsZVetoHigh',)
JetAnalyzerStepZVetoHigh7cBhe = JetAnalyzerStep7cBhe.clone(jetSource = 'bSsvHeMJetsZVetoHigh',)
JetAnalyzerStepZVetoHigh7cBhp = JetAnalyzerStep7cBhp.clone(jetSource = 'bSsvHpTJetsZVetoHigh',)
JetAnalyzerStepZVetoHigh7J = JetAnalyzerStep7J.clone(jetSource = 'finalJetsZVetoHigh',)
JetAnalyzerStepZVetoHigh7Bhe = JetAnalyzerStep7Bhe.clone(jetSource = 'bSsvHeMJetsZVetoHigh',)
JetAnalyzerStepZVetoHigh7Bhp = JetAnalyzerStep7Bhp.clone(jetSource = 'bSsvHpTJetsZVetoHigh',)

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





#******************************************************************************************
#   Utils Modules
#******************************************************************************************

from ZmumuAnalysis.Utils.RunEventListing_cff import *
RunEventListingStep3 = RunEventListingCreateTreeOnly.clone()
RunEventListingStep5 = RunEventListingCreateTreeOnly.clone()
RunEventListingStep6 = RunEventListingCreateTreeOnly.clone()
RunEventListingStep7 = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoLow3 = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoLow5 = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoLow6 = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoLow7 = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoHigh3 = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoHigh5 = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoHigh6 = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoHigh7 = RunEventListingCreateTreeOnly.clone()

RunEventListingStepNoMet7 = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoLowNoMet7 = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoHighNoMet7 = RunEventListingCreateTreeOnly.clone()






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
    EventCounterStep2c
)
step2d = cms.Sequence(
    EventCounterStep2d
)
step2e = cms.Sequence(
    EventCounterStep2e
)
step2f = cms.Sequence(
    EventCounterStep2f
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
    DimuonAnalyzerStep3d
)
step3e = cms.Sequence(
    EventCounterStep3e+
    DimuonAnalyzerStep3e
)
step3f = cms.Sequence(
    EventCounterStep3f+
    VertexAnalyzerStep3f+
    DimuonAnalyzerStep3f
)
step3 = cms.Sequence(
    EventCounterStep3+
    VertexAnalyzerStep3+
    MuonAnalyzerStep3+
    DimuonAnalyzerStep3+
    RunEventListingStep3
)

step4a = cms.Sequence(
    EventCounterStep4a+
    JetAnalyzerStep4a
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
    JetAnalyzerStep4
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
    MetAnalyzerStep7a
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
    MetAnalyzerStep7+
    RunEventListingStep7
)



## Define steps and corresponding analyzers for analysis excluding the Z mass window (lower sideband)
stepZVetoLow3f = cms.Sequence(
    EventCounterStepZVetoLow3f+
    VertexAnalyzerStepZVetoLow3f+
    DimuonAnalyzerStepZVetoLow3f
)
stepZVetoLow3 = cms.Sequence(
    EventCounterStepZVetoLow3+
    #VertexAnalyzerStepZVetoLow3+
    MuonAnalyzerStepZVetoLow3+
    #DimuonAnalyzerStepZVetoLow3+
    RunEventListingStepZVetoLow3
)

stepZVetoLow4a = cms.Sequence(
    EventCounterStepZVetoLow4a
)
stepZVetoLow4b = cms.Sequence(
    EventCounterStepZVetoLow4b
)
stepZVetoLow4c = cms.Sequence(
    EventCounterStepZVetoLow4c
)
stepZVetoLow4d = cms.Sequence(
    EventCounterStepZVetoLow4d+
    JetAnalyzerStepZVetoLow4d
)
stepZVetoLow4 = cms.Sequence(
    EventCounterStepZVetoLow4+
    MuonAnalyzerStepZVetoLow4+
    DimuonAnalyzerStepZVetoLow4+
    JetAnalyzerStepZVetoLow4
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
    MetAnalyzerStepZVetoLow7a
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
    MetAnalyzerStepZVetoLow7+
    RunEventListingStepZVetoLow7
)



## Define steps and corresponding analyzers for analysis excluding the Z mass window (upper sideband)
stepZVetoHigh3f = cms.Sequence(
    EventCounterStepZVetoHigh3f+
    VertexAnalyzerStepZVetoHigh3f+
    DimuonAnalyzerStepZVetoHigh3f
)
stepZVetoHigh3 = cms.Sequence(
    EventCounterStepZVetoHigh3+
    #VertexAnalyzerStepZVetoHigh3+
    MuonAnalyzerStepZVetoHigh3+
    #DimuonAnalyzerStepZVetoHigh3+
    RunEventListingStepZVetoHigh3
)

stepZVetoHigh4a = cms.Sequence(
    EventCounterStepZVetoHigh4a
)
stepZVetoHigh4b = cms.Sequence(
    EventCounterStepZVetoHigh4b
)
stepZVetoHigh4c = cms.Sequence(
    EventCounterStepZVetoHigh4c
)
stepZVetoHigh4d = cms.Sequence(
    EventCounterStepZVetoHigh4d+
    JetAnalyzerStepZVetoHigh4d
)
stepZVetoHigh4 = cms.Sequence(
    EventCounterStepZVetoHigh4+
    MuonAnalyzerStepZVetoHigh4+
    DimuonAnalyzerStepZVetoHigh4+
    JetAnalyzerStepZVetoHigh4
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
    MetAnalyzerStepZVetoHigh7a
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
    MetAnalyzerStepZVetoHigh7+
    RunEventListingStepZVetoHigh7
)



## Define steps and corresponding analyzers for analysis excluding cut on MET (signal region, lower and upper sideband)
stepNoMet7a = cms.Sequence(
    EventCounterStepNoMet7a+
    MuonAnalyzerStepNoMet7a+
    DimuonAnalyzerStepNoMet7a+
    JetAnalyzerStepNoMet7aJ+
    JetAnalyzerStepNoMet7aBhe+
    JetAnalyzerStepNoMet7aBhp+
    MetAnalyzerStepNoMet7a
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
    MetAnalyzerStepNoMet7+
    RunEventListingStepNoMet7
)

stepZVetoLowNoMet7a = cms.Sequence(
    EventCounterStepZVetoLowNoMet7a+
    MuonAnalyzerStepZVetoLowNoMet7a+
    DimuonAnalyzerStepZVetoLowNoMet7a+
    JetAnalyzerStepZVetoLowNoMet7aJ+
    JetAnalyzerStepZVetoLowNoMet7aBhe+
    JetAnalyzerStepZVetoLowNoMet7aBhp+
    MetAnalyzerStepZVetoLowNoMet7a
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
    MetAnalyzerStepZVetoLowNoMet7+
    RunEventListingStepZVetoLowNoMet7
)

stepZVetoHighNoMet7a = cms.Sequence(
    EventCounterStepZVetoHighNoMet7a+
    MuonAnalyzerStepZVetoHighNoMet7a+
    DimuonAnalyzerStepZVetoHighNoMet7a+
    JetAnalyzerStepZVetoHighNoMet7aJ+
    JetAnalyzerStepZVetoHighNoMet7aBhe+
    JetAnalyzerStepZVetoHighNoMet7aBhp+
    MetAnalyzerStepZVetoHighNoMet7a
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
    MetAnalyzerStepZVetoHighNoMet7+
    RunEventListingStepZVetoHighNoMet7
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
    oneCleanJetSelection*
    oneGoodIdJetSelection*
    oneGoodJetSelection*
    oneFinalJetSelection*
    oneBSsvHeMJetSelection*
    buildMetCollections
)

zVetoLowNoMetDefaultSteps = noMetDefaultSteps.copy()
zVetoLowNoMetDefaultSteps.replace(finalDimuonSelection,finalDimuonZVetoLowSelection)
zVetoLowNoMetDefaultSteps.replace(oneGoodJetSelection,oneGoodJetZVetoLowSelection)
zVetoLowNoMetDefaultSteps.replace(oneFinalJetSelection,oneFinalJetZVetoLowSelection)
zVetoLowNoMetDefaultSteps.replace(oneBSsvHeMJetSelection,oneBSsvHeMJetZVetoLowSelection);

zVetoHighNoMetDefaultSteps = noMetDefaultSteps.copy()
zVetoHighNoMetDefaultSteps.replace(finalDimuonSelection,finalDimuonZVetoHighSelection)
zVetoHighNoMetDefaultSteps.replace(oneGoodJetSelection,oneGoodJetZVetoHighSelection)
zVetoHighNoMetDefaultSteps.replace(oneFinalJetSelection,oneFinalJetZVetoHighSelection)
zVetoHighNoMetDefaultSteps.replace(oneBSsvHeMJetSelection,oneBSsvHeMJetZVetoHighSelection);






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
    oneTightMuonSelection*
    step2c*
    oneIsolatedMuonSelection*
    step2d*
    tightMuonSelection*
    step2e*
    isolatedMuonSelection*
    step2f*
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
    finalDimuonSelection*
    step3f*
    step3*
    
    buildJetCollections*
    step4a*
    oneCleanJetSelection*
    step4b*
    oneGoodIdJetSelection*
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



ZVetoLowOppositeChargeAnalysisSeq = cms.Sequence(
    zVetoDefaultSteps*
    
    finalDimuonZVetoLowSelection*
    stepZVetoLow3f*
    stepZVetoLow3*
    
    buildJetCollections*
    stepZVetoLow4a*
    oneCleanJetSelection*
    stepZVetoLow4b*
    oneGoodIdJetSelection*
    stepZVetoLow4c*
    oneGoodJetZVetoLowSelection*
    stepZVetoLow4d*
    oneFinalJetZVetoLowSelection*
    stepZVetoLow4*
    
    oneBSsvHeMJetZVetoLowSelection*
    stepZVetoLow5*
    
    buildMetCollections*
    stepZVetoLow6a*
    goodMetSelection*
    stepZVetoLow6*
    
    oneBSsvHpTJetZVetoLowSelection*
    stepZVetoLow7a*
    twoFinalJetZVetoLowSelection*
    stepZVetoLow7b*
    twoBSsvHeMJetZVetoLowSelection*
    stepZVetoLow7c*
    twoBSsvHpTJetZVetoLowSelection*
    stepZVetoLow7
    
)



ZVetoHighOppositeChargeAnalysisSeq = cms.Sequence(
    zVetoDefaultSteps*
    
    finalDimuonZVetoHighSelection*
    stepZVetoHigh3f*
    stepZVetoHigh3*
    
    buildJetCollections*
    stepZVetoHigh4a*
    oneCleanJetSelection*
    stepZVetoHigh4b*
    oneGoodIdJetSelection*
    stepZVetoHigh4c*
    oneGoodJetZVetoHighSelection*
    stepZVetoHigh4d*
    oneFinalJetZVetoHighSelection*
    stepZVetoHigh4*
    
    oneBSsvHeMJetZVetoHighSelection*
    stepZVetoHigh5*
    
    buildMetCollections*
    stepZVetoHigh6a*
    goodMetSelection*
    stepZVetoHigh6*
    
    
    oneBSsvHpTJetZVetoHighSelection*
    stepZVetoHigh7a*
    twoFinalJetZVetoHighSelection*
    stepZVetoHigh7b*
    twoBSsvHeMJetZVetoHighSelection*
    stepZVetoHigh7c*
    twoBSsvHpTJetZVetoHighSelection*
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



ZVetoLowNoMetOppositeChargeAnalysisSeq = cms.Sequence(
    zVetoLowNoMetDefaultSteps*
    
    # Do not apply MET Selection
    #goodMetSelection*
    #stepZVetoLowNoMet6*
    
    oneBSsvHpTJetZVetoLowSelection*
    stepZVetoLowNoMet7a*
    twoFinalJetZVetoLowSelection*
    stepZVetoLowNoMet7b*
    twoBSsvHeMJetZVetoLowSelection*
    stepZVetoLowNoMet7c*
    twoBSsvHpTJetZVetoLowSelection*
    stepZVetoLowNoMet7
    
)



ZVetoHighNoMetOppositeChargeAnalysisSeq = cms.Sequence(
    zVetoHighNoMetDefaultSteps*
    
    # Do not apply MET Selection
    #goodMetSelection
    #stepZVetoHighNoMet6*
    
    oneBSsvHpTJetZVetoHighSelection*
    stepZVetoHighNoMet7a*
    twoFinalJetZVetoHighSelection*
    stepZVetoHighNoMet7b*
    twoBSsvHeMJetZVetoHighSelection*
    stepZVetoHighNoMet7c*
    twoBSsvHpTJetZVetoHighSelection*
    stepZVetoHighNoMet7
    
)










