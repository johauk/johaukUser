import FWCore.ParameterSet.Config as cms



#******************************************************************************************
#   Filter & Producer Modules
#******************************************************************************************


## Event weight producer
from ZmumuAnalysis.Configuration.sequences.eventWeight_cff import *

## filter trigger
from ZmumuAnalysis.Configuration.filters.TriggerFilter_cff import *

## filter for good primary vertices
from ZmumuAnalysis.Configuration.sequences.vertexSelection_cff import *

## filter for muon quality, kinematics and HLT object matching
from ZmumuAnalysis.Configuration.sequences.muonSelection_cff import *

## add dimuon collections and filter for dimuon properties
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
EventCounterStep3 = EventCounter.clone()
EventCounterStep4a = EventCounter.clone()
EventCounterStep4b = EventCounter.clone()
EventCounterStep4c = EventCounter.clone()
EventCounterStep4 = EventCounter.clone()
EventCounterStep5 = EventCounter.clone()
EventCounterStep6 = EventCounter.clone()
EventCounterStep7a = EventCounter.clone()
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
EventCounterStepZVetoHigh7 = EventCounter.clone()





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
VertexAnalyzerStep3c = VertexAnalyzer.clone(vertexSource = 'goodDimuonPVs',)
VertexAnalyzerStep3d = VertexAnalyzer.clone(vertexSource = 'bestPV',)
VertexAnalyzerStep3 = VertexAnalyzer.clone(vertexSource = 'bestPV',)

VertexAnalyzerStepZVetoLow3 = VertexAnalyzerStep3.clone()
VertexAnalyzerStepZVetoHigh3 = VertexAnalyzerStep3.clone()





## muon analizer
from ZmumuAnalysis.Analyzer.MuonAnalyzer_cfi import *
MuonAnalyzerStep2a = MuonAnalyzer.clone(muonSource = 'selectedPatMuons',whichHists = "veryBasic",)
MuonAnalyzerStep2b = MuonAnalyzer.clone(muonSource = 'looseMuons',whichHists = "basic",)
MuonAnalyzerStep2c = MuonAnalyzer.clone(muonSource = 'tightMuons',whichHists = "basic",)
MuonAnalyzerStep2d = MuonAnalyzer.clone(muonSource = 'isolatedMuons',whichHists = "basic",)
MuonAnalyzerStep2e = MuonAnalyzer.clone(muonSource = 'tightMuons',whichHists = "basic",)
MuonAnalyzerStep2 = MuonAnalyzer.clone(muonSource = 'isolatedMuons')
MuonAnalyzerStep3 = MuonAnalyzer.clone(muonSource = 'isolatedMuons',)
MuonAnalyzerStep4 = MuonAnalyzer.clone(muonSource = 'isolatedMuons',)
MuonAnalyzerStep5 = MuonAnalyzer.clone(muonSource = 'isolatedMuons',)
MuonAnalyzerStep6 = MuonAnalyzer.clone(muonSource = 'isolatedMuons',)
MuonAnalyzerStep7a = MuonAnalyzer.clone(muonSource = 'isolatedMuons',)
MuonAnalyzerStep7 = MuonAnalyzer.clone(muonSource = 'isolatedMuons',)

MuonAnalyzerStepZVetoLow3 = MuonAnalyzerStep3.clone()
MuonAnalyzerStepZVetoLow4 = MuonAnalyzerStep4.clone()
MuonAnalyzerStepZVetoLow5 = MuonAnalyzerStep5.clone()
MuonAnalyzerStepZVetoLow6 = MuonAnalyzerStep6.clone()
MuonAnalyzerStepZVetoLow7a = MuonAnalyzerStep7a.clone()
MuonAnalyzerStepZVetoLow7 = MuonAnalyzerStep7.clone()
MuonAnalyzerStepZVetoHigh3 = MuonAnalyzerStep3.clone()
MuonAnalyzerStepZVetoHigh4 = MuonAnalyzerStep4.clone()
MuonAnalyzerStepZVetoHigh5 = MuonAnalyzerStep5.clone()
MuonAnalyzerStepZVetoHigh6 = MuonAnalyzerStep6.clone()
MuonAnalyzerStepZVetoHigh7a = MuonAnalyzerStep7a.clone()
MuonAnalyzerStepZVetoHigh7 = MuonAnalyzerStep7.clone()





## di-muon analyzer
from ZmumuAnalysis.Analyzer.DimuonAnalyzer_cfi import *
DimuonAnalyzerStep3c = DimuonAnalyzer.clone(dimuonSource = "goodDimuons",)
DimuonAnalyzerStep3d = DimuonAnalyzer.clone(dimuonSource = "bestDimuon",)
DimuonAnalyzerStep3 = DimuonAnalyzer.clone(dimuonSource = "bestDimuon",)
DimuonAnalyzerStep4 = DimuonAnalyzer.clone(dimuonSource = "bestDimuon",)
DimuonAnalyzerStep5 = DimuonAnalyzer.clone(dimuonSource = "bestDimuon",)
DimuonAnalyzerStep6 = DimuonAnalyzer.clone(dimuonSource = "bestDimuon",)
DimuonAnalyzerStep7a = DimuonAnalyzer.clone(dimuonSource = "bestDimuon",)
DimuonAnalyzerStep7 = DimuonAnalyzer.clone(dimuonSource = "bestDimuon",)

DimuonAnalyzerStepZVetoLow3 = DimuonAnalyzerStep3.clone()
DimuonAnalyzerStepZVetoLow4 = DimuonAnalyzerStep4.clone()
DimuonAnalyzerStepZVetoLow5 = DimuonAnalyzerStep5.clone()
DimuonAnalyzerStepZVetoLow6 = DimuonAnalyzerStep6.clone()
DimuonAnalyzerStepZVetoLow7a = DimuonAnalyzerStep7a.clone()
DimuonAnalyzerStepZVetoLow7 = DimuonAnalyzerStep7.clone()
DimuonAnalyzerStepZVetoHigh3 = DimuonAnalyzerStep3.clone()
DimuonAnalyzerStepZVetoHigh4 = DimuonAnalyzerStep4.clone()
DimuonAnalyzerStepZVetoHigh5 = DimuonAnalyzerStep5.clone()
DimuonAnalyzerStepZVetoHigh6 = DimuonAnalyzerStep6.clone()
DimuonAnalyzerStepZVetoHigh7a = DimuonAnalyzerStep7a.clone()
DimuonAnalyzerStepZVetoHigh7 = DimuonAnalyzerStep7.clone()





## jet analyzer
from ZmumuAnalysis.Analyzer.JetAnalyzer_cfi import *
#JetAnalyzerStep3 = JetAnalyzer.clone(jetSource = 'selectedPatJetsAK5PF',whichHists = "basic",)
JetAnalyzerStep4a = JetAnalyzer.clone(jetSource = 'selectedJets',whichHists = "basic",)
JetAnalyzerStep4b = JetAnalyzer.clone(jetSource = 'cleanJets',whichHists = "basic",)
JetAnalyzerStep4c = JetAnalyzer.clone(jetSource = 'goodJets',)
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
JetAnalyzerStep7J = JetAnalyzer.clone(jetSource = 'finalJets',)
JetAnalyzerStep7Bhe = JetAnalyzer.clone(jetSource = 'bSsvHeMJets',)
JetAnalyzerStep7Bhp = JetAnalyzer.clone(jetSource = 'bSsvHpTJets',)

JetAnalyzerStepZVetoLow4a = JetAnalyzerStep4a.clone()
JetAnalyzerStepZVetoLow4b = JetAnalyzerStep4b.clone()
JetAnalyzerStepZVetoLow4c = JetAnalyzerStep4c.clone()
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
JetAnalyzerStepZVetoLow7J = JetAnalyzerStep7J.clone()
JetAnalyzerStepZVetoLow7Bhe = JetAnalyzerStep7Bhe.clone()
JetAnalyzerStepZVetoLow7Bhp = JetAnalyzerStep7Bhp.clone()
JetAnalyzerStepZVetoHigh4a = JetAnalyzerStep4a.clone()
JetAnalyzerStepZVetoHigh4b = JetAnalyzerStep4b.clone()
JetAnalyzerStepZVetoHigh4c = JetAnalyzerStep4c.clone()
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
JetAnalyzerStepZVetoHigh7J = JetAnalyzerStep7J.clone()
JetAnalyzerStepZVetoHigh7Bhe = JetAnalyzerStep7Bhe.clone()
JetAnalyzerStepZVetoHigh7Bhp = JetAnalyzerStep7Bhp.clone()





## missing et analyzer
from ZmumuAnalysis.Analyzer.MetAnalyzer_cfi import *
MetAnalyzerStep4 = MetAnalyzer.clone(metSource = 'patMETsPF',)
MetAnalyzerStep5 = MetAnalyzer.clone(metSource = 'patMETsPF',)
MetAnalyzerStep6 = MetAnalyzer.clone(metSource = 'patMETsPF',)
MetAnalyzerStep7a = MetAnalyzer.clone(metSource = 'patMETsPF',)
MetAnalyzerStep7 = MetAnalyzer.clone(metSource = 'patMETsPF',)

MetAnalyzerStepZVetoLow4 = MetAnalyzerStep4.clone()
MetAnalyzerStepZVetoLow5 = MetAnalyzerStep5.clone()
MetAnalyzerStepZVetoLow6 = MetAnalyzerStep6.clone()
MetAnalyzerStepZVetoLow7a = MetAnalyzerStep7a.clone()
MetAnalyzerStepZVetoLow7 = MetAnalyzerStep7.clone()
MetAnalyzerStepZVetoHigh4 = MetAnalyzerStep4.clone()
MetAnalyzerStepZVetoHigh5 = MetAnalyzerStep5.clone()
MetAnalyzerStepZVetoHigh6 = MetAnalyzerStep6.clone()
MetAnalyzerStepZVetoHigh7a = MetAnalyzerStep7a.clone()
MetAnalyzerStepZVetoHigh7 = MetAnalyzerStep7.clone()





#******************************************************************************************
#   Utils Modules
#******************************************************************************************

from ZmumuAnalysis.Utils.RunEventListing_cff import *
RunEventListingStep5 = RunEventListingCreateTreeOnly.clone()
RunEventListingStep6 = RunEventListingCreateTreeOnly.clone()
RunEventListingStep7a = RunEventListingCreateTreeOnly.clone()
RunEventListingStep7 = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoLow5 = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoLow6 = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoLow7a = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoLow7 = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoHigh5 = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoHigh6 = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoHigh7a = RunEventListingCreateTreeOnly.clone()
RunEventListingStepZVetoHigh7 = RunEventListingCreateTreeOnly.clone()





#******************************************************************************************
#   Sequences
#******************************************************************************************

## Apply generator filters
seqGeneratorFilter = cms.Sequence()



## Which b-tag criteria
oneBtagSelection = cms.Sequence()
twoBtagSelection = cms.Sequence()



## MET selection
metSelection = cms.Sequence()



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
    EventCounterStep2a+
    MuonAnalyzerStep2a
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
    EventCounterStep3c+
    VertexAnalyzerStep3c+
    DimuonAnalyzerStep3c
)
step3d = cms.Sequence(
    EventCounterStep3d+
    VertexAnalyzerStep3d+
    DimuonAnalyzerStep3d
)
step3 = cms.Sequence(
    EventCounterStep3+
    VertexAnalyzerStep3+
    MuonAnalyzerStep3+
    DimuonAnalyzerStep3
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
step4 = cms.Sequence(
    EventCounterStep4+
    MuonAnalyzerStep4+
    DimuonAnalyzerStep4+
    JetAnalyzerStep4J+
    JetAnalyzerStep4Bhe+
    JetAnalyzerStep4Bhp+
    MetAnalyzerStep4
)

step5 = cms.Sequence(
    EventCounterStep5+
    MuonAnalyzerStep5+
    DimuonAnalyzerStep5+
    JetAnalyzerStep5J+
    JetAnalyzerStep5Bhe+
    JetAnalyzerStep5Bhp+
    MetAnalyzerStep5+
    RunEventListingStep5
)

step6 = cms.Sequence(
    EventCounterStep6+
    MuonAnalyzerStep6+
    DimuonAnalyzerStep6+
    JetAnalyzerStep6J+
    JetAnalyzerStep6Bhe+
    JetAnalyzerStep6Bhp+
    MetAnalyzerStep6+
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
stepZVetoLow3 = cms.Sequence(
    EventCounterStepZVetoLow3+
    VertexAnalyzerStepZVetoLow3+
    MuonAnalyzerStepZVetoLow3+
    DimuonAnalyzerStepZVetoLow3
)

stepZVetoLow4a = cms.Sequence(
    EventCounterStepZVetoLow4a+
    JetAnalyzerStepZVetoLow4a
)
stepZVetoLow4b = cms.Sequence(
    EventCounterStepZVetoLow4b+
    JetAnalyzerStepZVetoLow4b
)
stepZVetoLow4c = cms.Sequence(
    EventCounterStepZVetoLow4c+
    JetAnalyzerStepZVetoLow4c
)
stepZVetoLow4 = cms.Sequence(
    EventCounterStepZVetoLow4+
    MuonAnalyzerStepZVetoLow4+
    DimuonAnalyzerStepZVetoLow4+
    JetAnalyzerStepZVetoLow4J+
    JetAnalyzerStepZVetoLow4Bhe+
    JetAnalyzerStepZVetoLow4Bhp+
    MetAnalyzerStepZVetoLow4
)

stepZVetoLow5 = cms.Sequence(
    EventCounterStepZVetoLow5+
    MuonAnalyzerStepZVetoLow5+
    DimuonAnalyzerStepZVetoLow5+
    JetAnalyzerStepZVetoLow5J+
    JetAnalyzerStepZVetoLow5Bhe+
    JetAnalyzerStepZVetoLow5Bhp+
    MetAnalyzerStepZVetoLow5+
    RunEventListingStepZVetoLow5
)

stepZVetoLow6 = cms.Sequence(
    EventCounterStepZVetoLow6+
    MuonAnalyzerStepZVetoLow6+
    DimuonAnalyzerStepZVetoLow6+
    JetAnalyzerStepZVetoLow6J+
    JetAnalyzerStepZVetoLow6Bhe+
    JetAnalyzerStepZVetoLow6Bhp+
    MetAnalyzerStepZVetoLow6+
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
stepZVetoHigh3 = cms.Sequence(
    EventCounterStepZVetoHigh3+
    VertexAnalyzerStepZVetoHigh3+
    MuonAnalyzerStepZVetoHigh3+
    DimuonAnalyzerStepZVetoHigh3
)

stepZVetoHigh4a = cms.Sequence(
    EventCounterStepZVetoHigh4a+
    JetAnalyzerStepZVetoHigh4a
)
stepZVetoHigh4b = cms.Sequence(
    EventCounterStepZVetoHigh4b+
    JetAnalyzerStepZVetoHigh4b
)
stepZVetoHigh4c = cms.Sequence(
    EventCounterStepZVetoHigh4c+
    JetAnalyzerStepZVetoHigh4c
)
stepZVetoHigh4 = cms.Sequence(
    EventCounterStepZVetoHigh4+
    MuonAnalyzerStepZVetoHigh4+
    DimuonAnalyzerStepZVetoHigh4+
    JetAnalyzerStepZVetoHigh4J+
    JetAnalyzerStepZVetoHigh4Bhe+
    JetAnalyzerStepZVetoHigh4Bhp+
    MetAnalyzerStepZVetoHigh4
)

stepZVetoHigh5 = cms.Sequence(
    EventCounterStepZVetoHigh5+
    MuonAnalyzerStepZVetoHigh5+
    DimuonAnalyzerStepZVetoHigh5+
    JetAnalyzerStepZVetoHigh5J+
    JetAnalyzerStepZVetoHigh5Bhe+
    JetAnalyzerStepZVetoHigh5Bhp+
    MetAnalyzerStepZVetoHigh5+
    RunEventListingStepZVetoHigh5
)

stepZVetoHigh6 = cms.Sequence(
    EventCounterStepZVetoHigh6+
    MuonAnalyzerStepZVetoHigh6+
    DimuonAnalyzerStepZVetoHigh6+
    JetAnalyzerStepZVetoHigh6J+
    JetAnalyzerStepZVetoHigh6Bhe+
    JetAnalyzerStepZVetoHigh6Bhp+
    MetAnalyzerStepZVetoHigh6+
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









#******************************************************************************************
#   Analysis Paths
#******************************************************************************************




## Gathering of common sequences

zVetoDefaultSteps = cms.Sequence(
    buildEventWeights*
    seqGeneratorFilter*
    seqTriggerFilter*
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







## Analysis Paths

analysisSeq = cms.Sequence(
    buildEventWeights*
    step0*
    
    seqGeneratorFilter*
    step1a*
    seqTriggerFilter*
    buildVertexCollections*
    step1b*
    oneGoodPVSelection*
    buildMuonCollections*
    step1*
    
    oneInitialMuonSelection*
    step2a*
    oneLooseMuonSelection*
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
    buildDimuonCollections*
    step2*
    
    selectedDimuonSelection*
    step3a*
    cleanDimuonSelection*
    step3b*
    goodDimuonSelection*
    step3c*
    step3d*
    finalDimuonSelection*
    buildJetCollections*
    step3*
    
    oneSelectedJetSelection*
    step4a*
    oneCleanJetSelection*
    step4b*
    oneGoodJetSelection*
    step4c*
    oneFinalJetSelection*
    buildMetCollections*
    step4*
    
    metSelection*
    step5*
    
    oneBtagSelection*
    step6
)

analysisTwoJetSeq = cms.Sequence(
    twoFinalJetSelection*
    step7a*
    twoBtagSelection*
    step7
)




zVetoLowAnalysisSeq = cms.Sequence(
    zVetoDefaultSteps*
    
    finalDimuonZVetoLowSelection*
    buildJetCollections*
    stepZVetoLow3*
    
    oneSelectedJetSelection*
    stepZVetoLow4a*
    oneCleanJetSelection*
    stepZVetoLow4b*
    oneGoodJetSelection*
    stepZVetoLow4c*
    oneFinalJetSelection*
    buildMetCollections*
    stepZVetoLow4*
    
    metSelection*
    stepZVetoLow5*
    
    oneBtagSelection*
    stepZVetoLow6
)

zVetoLowAnalysisTwoJetSeq = cms.Sequence(
    twoFinalJetSelection*
    stepZVetoLow7a*
    twoBtagSelection*
    stepZVetoLow7
)



zVetoHighAnalysisSeq = cms.Sequence(
    zVetoDefaultSteps*
    
    finalDimuonZVetoHighSelection*
    buildJetCollections*
    stepZVetoHigh3*
    
    oneSelectedJetSelection*
    stepZVetoHigh4a*
    oneCleanJetSelection*
    stepZVetoHigh4b*
    oneGoodJetSelection*
    stepZVetoHigh4c*
    oneFinalJetSelection*
    buildMetCollections*
    stepZVetoHigh4*
    
    metSelection*
    stepZVetoHigh5*
    
    oneBtagSelection*
    stepZVetoHigh6
)

zVetoHighAnalysisTwoJetSeq = cms.Sequence(
    twoFinalJetSelection*
    stepZVetoHigh7a*
    twoBtagSelection*
    stepZVetoHigh7
)







