import FWCore.ParameterSet.Config as cms

JetAnalyzer = cms.EDAnalyzer('JetAnalyzer',
    # Event weight source
    eventWeightSource = cms.InputTag("EventWeight"),
    
    # jet collection
    jetSource = cms.InputTag("selectedPatJets"),
    
    # which histograms to book
    # possibilities are "major", "basic"
    whichHists = cms.string("major"),
)
