import os

import FWCore.ParameterSet.Config as cms

process = cms.Process("FullCutflow")

## add message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000



## define maximal number of events to loop over
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)



## configure process options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
)



## sources
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.Run2010A_Sep17ReReco_v2_Oct22_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.Run2010B_PromptReco_v2_Oct29_145000_147120_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.Run2010B_PromptReco_v2_Nov05_147120_149442_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.inclusiveMu15_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.singleTopS_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.singleTopTW_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.singleTopT_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.ttbar_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.wmunu_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.zmumu_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.ztautau_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.ww_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.wz_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.zz_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.zjets_madgraph_spring10_cff")
#process.load("ZmumuAnalysis.Configuration.samples.mc.Spring10.samples.dymumu10to20_spring10_cff")
process.load("ZmumuAnalysis.Configuration.samples.testSample_cff")



## needed for access to trigger menu
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
# data
process.GlobalTag.globaltag = cms.string('GR_R_38X_V13::All')
# mc
#process.GlobalTag.globaltag = cms.string('START38_V12::All')





#******************************************************************************************
#   Filter & Producer Modules
#******************************************************************************************

## filter trigger
process.load("ZmumuAnalysis.Configuration.filters.TriggerFilter_cff")
#process.triggerFilter1 = process.TriggerFilterMu9.clone()
#process.triggerFilter1 = process.TriggerFilterMu15.clone()
process.triggerFilter1 = process.TriggerFilterMu9_11_15.clone()



## filter for muon quality, kinematics and HLT object matching
process.load("ZmumuAnalysis.Configuration.sequences.muonSelection_cff")



## add dimuon collections and filter for dimuon properties (including muon isolation)
process.load("ZmumuAnalysis.Configuration.sequences.diMuonSelection_cff")



## clean and filter for jets
process.load("ZmumuAnalysis.Configuration.sequences.jetSelection_cff")




#******************************************************************************************
#   Ntuple producer
#******************************************************************************************


## One can use directly the EDProducer "ZToLLEdmNtupleDumper" with given variables (they are of different type int, float, ...)
process.goodZToMuMuEdmNtuple = cms.EDProducer("ZToLLEdmNtupleDumper",
    zBlocks = cms.VPSet(
      cms.PSet(
        zName = cms.string("zGolden"),
        z = cms.InputTag("selectedDimuons"),
        zGenParticlesMatch = cms.InputTag(""),
        beamSpot = cms.InputTag("offlineBeamSpot"),
        primaryVertices = cms.InputTag("offlinePrimaryVerticesWithBS"), 
        ptThreshold = cms.double("1.5"),
        etEcalThreshold = cms.double("0.2"),
        etHcalThreshold = cms.double("0.5"),
        deltaRVetoTrk = cms.double("0.015"),
        deltaRTrk = cms.double("0.3"),
        deltaREcal = cms.double("0.25"),
        deltaRHcal = cms.double("0.25"),
        alpha = cms.double("0."),
        beta = cms.double("-0.75"),
        relativeIsolation = cms.bool(False),
        hltPath = cms.string("HLT_Mu9"),
      ),
    )
)



## One can use a generic EDProducer CandViewNtpProducer" with self defined variables (they are all of type float!!!)
process.diMuonNtuple = cms.EDProducer("CandViewNtpProducer",
    src = cms.InputTag('selectedDimuons'),
    lazyParser = cms.untracked.bool(True),  # When methods of inherited particles are needed, and not only common Candidate* methods
    #prefix = cms.untracked.string("test"),  # To give all variable's names in ntuples prefix
    #eventInfo = cms.untracked.bool(False),  # If storage of RunNumber, EventNumber, LumiBlock is not wanted
    variables = cms.VPSet(
      cms.PSet(
        tag = cms.untracked.string("mass"),
	quantity = cms.untracked.string("mass"),
      ),
      cms.PSet(
        tag = cms.untracked.string("pt"),
        quantity = cms.untracked.string("pt"),
      ),
      cms.PSet(
        tag = cms.untracked.string("dau0trackIso"),
         quantity = cms.untracked.string("daughter(0).masterClone.trackIso"),
      ),
      cms.PSet(
        tag = cms.untracked.string("dau0IsGlobal"),
         quantity = cms.untracked.string("daughter(0).isGlobalMuon"),
      ),
      #cms.PSet(
      #  tag = cms.untracked.string(""),
      #   quantity = cms.untracked.string(""),
      #),
    )
)




#******************************************************************************************
#   Analysis Path
#******************************************************************************************



process.ntupleProductionPath = cms.Path(
    
    process.buildMuonCollections
    
    *process.buildDimuonCollections
    
    *process.diMuonNtuple
    
    *process.goodZToMuMuEdmNtuple
)


process.ntupleSelectionPath = cms.Path(
    process.triggerFilter1
    
    *process.buildMuonCollections
    *process.muonSelection
    
    *process.buildDimuonCollections
    *process.dimuonSelection
    
    *process.buildJetCollections
    *process.jetSelection
)





#******************************************************************************************
#   Output Module
#******************************************************************************************



process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string(os.environ['CMSSW_BASE'] + '/src/ZmumuAnalysis/Configuration/hists/nTuple_test.root'),
    outputCommands = cms.untracked.vstring(
      "drop *",
      "keep *_*Ntuple_*_*",
    ),
    SelectEvents = cms.untracked.PSet(
      SelectEvents = cms.vstring(
        #"ntupleProductionPath",
	#"ntupleSelectionPath",
      )
    ),
)



process.eventInfo = cms.OutputModule("AsciiOutputModule")




#******************************************************************************************
#   Analysis Endpath
#******************************************************************************************



process.endPath = cms.EndPath(
    #process.eventInfo*
    process.out
)
