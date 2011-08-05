import FWCore.ParameterSet.Config as cms



##
## Define Process by hand, or use Template
##
process = cms.Process("PAT")
# import skeleton process
#from PhysicsTools.PatAlgos.patTemplate_cfg import *



##
## Metadata
##
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.1 $'),
    annotation = cms.untracked.string('PAT tuple for Z+b analysis'),
    name = cms.untracked.string('$Source: /cvs/CMSSW/UserCode/JohannesHauk/PhysicsAnalysis/ZmumuAnalysis/Configuration/analysis/patTupleProducer_mc_cfg.py,v $'),
)



##
## Process Options
##
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
)



##
## Message Logger
##
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 10000



##
## Input Files
##
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
process.source = cms.Source("PoolSource",
    fileNames = readFiles,
    secondaryFileNames = secFiles,
)
readFiles.extend([
    '/store/mc/Summer11/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola/AODSIM/PU_S4_START42_V11-v1/0000/FED85C0E-A89C-E011-A90D-E0CB4E19F9B7.root',
])



##
## JSON Event Pre-Selection
##
#import PhysicsTools.PythonAnalysis.LumiList as LumiList
#import FWCore.ParameterSet.Types as CfgTypes
#myLumis = LumiList.LumiList(filename = 'Cert_160404-161216_7TeV_PromptReco_Collisions11_JSON.txt').getCMSSWString().split(',')
#process.source.lumisToProcess = CfgTypes.untracked(CfgTypes.VLuminosityBlockRange())
#process.source.lumisToProcess.extend(myLumis) 



##
## Number of Events
##
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1001) )



##
## Geomety and Conditions
##
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = 'GR_R_42_V19::All'
process.GlobalTag.globaltag = 'START42_V13::All'
#process.GlobalTag.globaltag = 'MC_42_V13::All'



##
## Beam Scrap Filter
##
process.beamScrapFilter = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False),
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.2),
)



##
## HBHE Noise Filter
##
process.load('CommonTools.RecoAlgos.HBHENoiseFilter_cfi')



##
## Primary Vertex Filter
##
process.goodPVs = cms.EDFilter("VertexSelector",
    src = cms.InputTag('offlinePrimaryVertices'),
    cut = cms.string('ndof>4 &'
                     'abs(z)<24 &'
	             '!isFake &'
	             'position.Rho<2'
    ),
)
process.oneGoodPVSelection = cms.EDFilter("VertexCountFilter",
    src = cms.InputTag('goodPVs'),
    minNumber = cms.uint32(1),
    maxNumber = cms.uint32(99999),
)
process.goodVertexSequence = cms.Sequence(process.goodPVs*process.oneGoodPVSelection)



##
## Output Module (needs to be defined before removeCleaning(process))
##
# Do not deselect events during PAT tuple production
EventSelection = cms.PSet(
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring()
    )
)
process.out = cms.OutputModule("PoolOutputModule",
    SelectEvents = EventSelection.SelectEvents,
    outputCommands = cms.untracked.vstring('drop *'),
    dropMetaData = cms.untracked.string("DROPPED"),
    fileName = cms.untracked.string('patTuple.root')
)



##
## Remove unneeded GenParticles from Collection (for MC)
##
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.genParticles = cms.EDProducer("GenParticlePruner",
    #see https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideGenParticlePruner
    src = cms.InputTag("genParticles"),
    select = cms.vstring(
        "drop  *  ",
        "++keep++ pdgId = {Z0}",
        "++keep++ pdgId = {W+}",   "++keep++ pdgId = {W-}",
        "++keep++ pdgId = {t}",    "++keep++ pdgId = {tbar}",
        "++keep++ pdgId = {b}",    "++keep++ pdgId = {bbar}",
        "++keep++ pdgId = {c}",    "++keep++ pdgId = {cbar}",
        # "drop pdgId = {Z0} & status = 2"
        "++keep++ pdgId = {e+}",   "++keep++ pdgId = {e-}",
        "++keep++ pdgId = {mu+}",  "++keep++ pdgId = {mu-}",
        "++keep++ pdgId = {tau+}", "++keep++ pdgId = {tau-}",
    ),
)



##
## PAT Configuration
##
process.load("PhysicsTools.PatAlgos.patSequences_cff")
from PhysicsTools.PatAlgos.tools.coreTools import *

# remove cleaning as it is not used
removeCleaning(process)

# switch off MC matching for data
#removeMCMatching(process, ['All'])

# Taus are currently broken in 4.1.x
#removeSpecificPATObjects( process, ['Taus'] )
#process.patDefaultSequence.remove( process.patTaus )


## Leptons

# Calculate d0 wrt the beam spot
process.patMuons.usePV = False
process.patElectrons.usePV = False

# Electron ID
process.load("RecoLocalCalo/EcalRecAlgos/EcalSeverityLevelESProducer_cfi")
process.load("ElectroWeakAnalysis.WENu.simpleEleIdSequence_cff")
process.patElectrons.addElectronID = cms.bool(True)
process.patElectrons.electronIDSources = cms.PSet(
    simpleEleId95relIso= cms.InputTag("simpleEleId95relIso"),
    simpleEleId90relIso= cms.InputTag("simpleEleId90relIso"),
    simpleEleId85relIso= cms.InputTag("simpleEleId85relIso"),
    #simpleEleId80relIso = cms.InputTag("simpleEleId80relIso"),
    #simpleEleId70relIso = cms.InputTag("simpleEleId70relIso"),
    #simpleEleId60relIso = cms.InputTag("simpleEleId60relIso"),
    simpleEleId95cIso   = cms.InputTag("simpleEleId95cIso"),
    simpleEleId90cIso   = cms.InputTag("simpleEleId90cIso"),
    simpleEleId85cIso   = cms.InputTag("simpleEleId85cIso"),
    #simpleEleId80cIso   = cms.InputTag("simpleEleId80cIso"),
    #simpleEleId70cIso   = cms.InputTag("simpleEleId70cIso"),
    #simpleEleId60cIso   = cms.InputTag("simpleEleId60cIso"),
)
process.patElectronIDs = cms.Sequence(process.simpleEleIdSequence)
process.makePatElectrons = cms.Sequence(process.patElectronIsolation*process.electronMatch*process.patElectrons)  # For MC
#process.makePatElectrons = cms.Sequence(process.patElectronIsolation*process.patElectrons)  # For data

# Embed Tracks
process.patMuons.embedTrack = True
process.patElectrons.embedTrack = True


## Jets

# Produce genjets without nu's (for MC only)
process.load("RecoJets.Configuration.GenJetParticles_cff")
process.genParticlesForJets.ignoreParticleIDs = cms.vuint32(
    1000022, 2000012, 2000014,
    2000016, 1000039, 5000039,
    4000012, 9900012, 9900014,
    9900016, 39, 12, 14, 16,
)
process.load("RecoJets.JetProducers.ak5GenJets_cfi")
process.ak5GenJetsNoNuBSM  =  process.ak5GenJets
process.pgenjets = cms.Sequence(
    process.genParticlesForJets*
    process.ak5GenJetsNoNuBSM
)

# Add PF Jets to the event content
from PhysicsTools.PatAlgos.tools.jetTools import *
# Like VHF Group
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')
process.load('RecoJets.Configuration.RecoPFJets_cff')
# Turn-on the FastJet density calculation
process.kt6PFJets.doRhoFastjet = True
# Turn-on the FastJet jet area calculation for your favorite algorithm
process.ak5PFJets.doAreaFastjet = True
# Jet energy corrections to use:
inputJetCorrLabel = ('AK5PF',['L1FastJet', 'L2Relative', 'L3Absolute'])  # For MC
#inputJetCorrLabel = ('AK5PF',['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual'])  # For data
#switchJetCollection(process,cms.InputTag('ak5PFJets'),
#    doJTA = True,
#    doBTagging = True,
#    jetCorrLabel = inputJetCorrLabel,
#    doType1MET = False,
#    genJetCollection=cms.InputTag("ak5GenJetsNoNuBSM"),  # For MC
#    #genJetCollection=cms.InputTag(""),  # For data
#    doJetID = True,
#    jetIdLabel = "ak5",
#)
# Prefer adding the collection instead of switching (else name remains patJets, but these are patJetsAK5PF)
addJetCollection(process, cms.InputTag('ak5PFJets'), 'AK5','PF',
    doJTA = True,
    doBTagging = True,
    jetCorrLabel = inputJetCorrLabel,
    doType1MET = False,
    doL1Cleaning = False,
    doL1Counters = False,
    genJetCollection = cms.InputTag("ak5GenJetsNoNuBSM"),  # For MC
    #genJetCollection = cms.InputTag(""),  # For data
    doJetID = True,
)
process.patJets.addTagInfos = cms.bool(True)
process.patJetsAK5PF.addTagInfos = cms.bool(True)
# With FastJet correction need to be true
#process.patJetCorrFactors.useRho = True
process.patJetCorrFactorsAK5PF.useRho = True


## MET

# Add PF MET and JPT MET to the event content
from PhysicsTools.PatAlgos.tools.metTools import *
addPfMET(process,'PF')
addTcMET(process,'JPT')


## Further Embeddings

# Embedding of jet constituents into the jets
process.patJets.embedCaloTowers = False
#process.patJetsAK5JPT.embedCaloTowers = False
process.patJetsAK5PF.embedPFCandidates = False

# Embed IsoDeposits
process.patMuons.isoDeposits = cms.PSet(
     tracker = cms.InputTag("muIsoDepositTk"),
     ecal    = cms.InputTag("muIsoDepositCalByAssociatorTowers","ecal"),
     hcal    = cms.InputTag("muIsoDepositCalByAssociatorTowers","hcal"),
     user    = cms.VInputTag(
       cms.InputTag("muIsoDepositCalByAssociatorTowers","ho"),
       cms.InputTag("muIsoDepositJets")
     ),
)

# Embedding of resolutions into the patObjects
process.load("TopQuarkAnalysis.TopObjectResolutions.stringResolutions_etEtaPhi_cff")
process.patJets.addResolutions = True
process.patJets.resolutions = cms.PSet(
    default = cms.string("udscResolution"),
    bjets = cms.string("bjetResolution"),
)
process.patJetsAK5PF.addResolutions = True
process.patJetsAK5PF.resolutions = cms.PSet(
    default = cms.string("udscResolutionPF"),
    bjets = cms.string("bjetResolutionPF"),
)
process.patElectrons.addResolutions = True
process.patElectrons.resolutions = cms.PSet( default = cms.string("elecResolution") )
process.patMuons.addResolutions = True
process.patMuons.resolutions = cms.PSet( default = cms.string("muonResolution") )
process.patMETs.addResolutions = True
process.patMETs.resolutions = cms.PSet( default = cms.string("metResolution") )
process.patMETsPF.addResolutions = True
process.patMETsPF.resolutions = cms.PSet( default = cms.string("metResolutionPF") )



##
## Sequences and Path
##

# Compute weight from trigger prescale
#process.patDefaultSequence *= process.WeightFromTrigger
#process.out.outputCommands += ['keep *_WeightFromTrigger_*_*',]

process.path = cms.Path(
    #process.beamScrapFilter*
    #process.HBHENoiseFilter*
    #process.goodVertexSequence*
    
    process.pgenjets*
    process.kt6PFJets*
    process.ak5PFJets*
    process.patElectronIDs*
    process.patDefaultSequence
    *process.genParticles
)



##
## Products to be kept (define this at the very end, because stupid PAT tools will screw it up (e.g. removeCleaning(process)))
##
from PhysicsTools.PatAlgos.patEventContent_cff import *
process.out.outputCommands += patExtraAodEventContent
process.out.outputCommands += patEventContentNoCleaning
process.out.outputCommands += [
    'drop *_towerMaker_*_*',
    'keep *_TriggerResults_*_*',
    'keep *_hltTriggerSummaryAOD_*_*',
    'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*',
    'keep *_ak5JetID_*_*',
    'keep *_gsf*_*_*',
    'keep *DcsStatus*_*_*_*',
    'keep *_addPileupInfo_*_*',
]
# In addition for MC
process.out.outputCommands += [
    'drop recoGenParticles_genParticles__HLT',
    'drop CaloTowersSorted_towerMaker__RECO', 
    #'drop recoTracks_generalTracks__RECO',
    #'drop patTaus_selectedPatTaus__PAT',
    #'drop patJets_selectedPatJetsAK5JPT__PAT',
    'drop patJets_selectedPatJets__PAT',
    #'drop triggerTriggerEvent_hltTriggerSummaryAOD__HLT',
    #'drop patPhotons_selectedPatPhotons__PAT',
    #'drop recoGenJets_selectedPatJetsAK5JPT_genJets_PAT',
    'drop recoGenJets_selectedPatJets_genJets_PAT',
    'drop patMETs_patMETs__PAT',
    'drop patMETs_patMETsJPT__PAT',
    #'drop recoPFCandidates_selectedPatJetsAK5JPT_pfCandidates_PAT',
    'drop recoPFCandidates_selectedPatJets_pfCandidates_PAT',
    #'drop CaloTowers_selectedPatJetsAK5JPT_caloTowers_PAT',
    'drop CaloTowers_selectedPatJets_caloTowers_PAT',
    #'drop GenEventInfoProduct_generator__HLT',
    #'drop recoBaseTagInfosOwned_selectedPatJetsAK5JPT_tagInfos_PAT',
    'drop recoBaseTagInfosOwned_selectedPatJets_tagInfos_PAT',
]



##
## Endpath
##
process.outpath = cms.EndPath(process.out)










