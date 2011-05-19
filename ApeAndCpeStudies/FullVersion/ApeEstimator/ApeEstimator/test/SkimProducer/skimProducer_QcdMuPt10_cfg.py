import os

import FWCore.ParameterSet.Config as cms



process = cms.Process("ApeSkim")



##
## Message Logger
##
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories.append('AlignmentTrackSelector')
#process.MessageLogger.categories.append('')
process.MessageLogger.cerr.INFO.limit = 0
process.MessageLogger.cerr.default.limit = 0
process.MessageLogger.cerr.AlignmentTrackSelector = cms.untracked.PSet(limit = cms.untracked.int32(-1))

#process.MessageLogger.cout = cms.untracked.PSet(INFO = cms.untracked.PSet(
#    reportEvery = cms.untracked.int32(100),  # every 100th only
#    limit = cms.untracked.int32(10),         # or limit to 10 printouts...
#))
process.MessageLogger.cerr.FwkReport.reportEvery = 1000 ## really show only every 1000th



##
## Handle huge number of Files
##
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
)



##
## Input Files (Collisions '10, 7 TeV)
##
## --- Particle Gun ---
#process.load("ApeEstimator.ApeEstimator.samples.ParticleGunPion_mc_cff")
#process.load("ApeEstimator.ApeEstimator.samples.ParticleGunAntiPion_mc_cff")
#process.load("ApeEstimator.ApeEstimator.samples.ParticleGunBothPion_mc_cff")
## --- Monte Carlo ---
#process.load("ApeEstimator.ApeEstimator.samples.Mc_TkAlMuonIsolated_Fall10_WToMuNu_cff")
process.load("ApeEstimator.ApeEstimator.samples.Mc_TkAlMuonIsolated_Fall10_QcdMuPt10_cff")
## --- Run XXX-YYY, End of Year Reprocessing ---
#process.load("ApeEstimator.ApeEstimator.samples.Data_TkAlMinBias_Run2010A_Dec22ReReco_cff")
#process.load("ApeEstimator.ApeEstimator.samples.Data_TkAlMinBias_Run2010B_Dec22ReReco_cff")
#process.load("ApeEstimator.ApeEstimator.samples.Data_TkAlMuonIsolated_Run2010A_Dec22ReReco_cff")
#process.load("ApeEstimator.ApeEstimator.samples.Data_TkAlMuonIsolated_Run2010B_Dec22ReReco_cff")



##
## Number of Events (should be after input file)
##
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )



##
## Check run and event numbers only for real data
##
#process.source.duplicateCheckMode = cms.untracked.string("noDuplicateCheck")
#process.source.duplicateCheckMode = cms.untracked.string("checkEachFile")
#process.source.duplicateCheckMode = cms.untracked.string("checkEachRealDataFile")
#process.source.duplicateCheckMode = cms.untracked.string("checkAllFilesOpened")   # default value



##
## Trigger Selection
##
process.load("ApeEstimator.ApeEstimator.TriggerSelection_cff")



##
## ALCARECOTkAlMuonIsolated selection
##
process.load("Alignment.CommonAlignmentProducer.ALCARECOTkAlMuonIsolated_cff")
process.seqALCARECOTkAlMuonIsolated.remove(process.ALCARECOTkAlMuonIsolatedHLT)
process.seqALCARECOTkAlMuonIsolated.remove(process.ALCARECOTkAlMuonIsolatedDCSFilter)



##
## FILTER for high purity tracks
##
import ApeEstimator.ApeEstimator.AlignmentTrackSelector_cff
process.MinBiasSkim = ApeEstimator.ApeEstimator.AlignmentTrackSelector_cff.MinBiasSkimSelector
process.MuSkim = ApeEstimator.ApeEstimator.AlignmentTrackSelector_cff.MuSkimSelector



##
## Path
##
process.path = cms.Path(
    #process.TriggerSelectionSequence*
    #process.TriggerHltMu9Sequence*
    #process.seqALCARECOTkAlMuonIsolated*
    #process.MinBiasSkim
    process.MuSkim
)



##
## Define event selection from path
##
EventSelection = cms.PSet(
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('path')
    )
)



##
## configure output module
##
process.out = cms.OutputModule("PoolOutputModule",
    ## Parameters directly for PoolOutputModule
    fileName = cms.untracked.string('rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/Qcd/apeSkim.root'),
    #fileName = cms.untracked.string(os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/test.root'),
    #fileName = cms.untracked.string('test.root'),
    #logicalFileName = cms.untracked.string(''),
    #catalog = cms.untracked.string(''),
    # Maximus size per file before a new one is created
    maxSize = cms.untracked.int32(2000000),
    #compressionLevel = cms.untracked.int32(0),
    #basketSize = cms.untracked.int32(0),
    #splitLevel = cms.untracked.int32(0),
    #sortBaskets = cms.untracked.string(''),
    #treeMaxVirtualSize =  cms.untracked.int32(0),
    #fastCloning = cms.untracked.bool(False),
    #overrideInputFileSplitLevels = cms.untracked.bool(True),
    dropMetaData = cms.untracked.string("DROPPED"),
    #dataset = cms.untracked.PSet(
    #    filterName = cms.untracked.string('TkAlMuonIsolated'),
    #    dataTier = cms.untracked.string('ALCARECO'),
    #),
    # Not yet implemented
    #eventAutoFlushCompressedSize = cms.untracked.int32(5*1024*1024),
    
    ## Parameters for inherited OutputModule
    SelectEvents = EventSelection.SelectEvents,
    outputCommands = cms.untracked.vstring(
        'drop *',
    ),
)
process.load("ApeEstimator.ApeEstimator.PrivateSkim_EventContent_cff")
process.out.outputCommands.extend(process.ApeSkimEventContent.outputCommands)



##
## Outpath
##
process.outpath = cms.EndPath(process.out)




