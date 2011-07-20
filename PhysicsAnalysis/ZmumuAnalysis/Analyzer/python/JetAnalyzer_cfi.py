import FWCore.ParameterSet.Config as cms

JetAnalyzer = cms.EDAnalyzer('JetAnalyzer',
    # jet collection
    jetSource = cms.InputTag("selectedPatJets"),
    
    # which histograms to book
    # possibilities are "major", "basic"
    whichHists = cms.string("major"),
)
