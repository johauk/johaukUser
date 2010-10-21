import FWCore.ParameterSet.Config as cms

JetAnalyzer = cms.EDAnalyzer('JetAnalyzer',
    # jet collection
    jetSource = cms.InputTag("selectedPatJets"),
)
