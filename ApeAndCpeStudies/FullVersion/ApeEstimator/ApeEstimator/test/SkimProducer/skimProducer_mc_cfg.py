import os

import FWCore.ParameterSet.Config as cms


process = cms.Process("ApeSkim")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories.append('')
#process.MessageLogger.categories.append('TrackRefitter')
process.MessageLogger.categories.append('AlignmentTrackSelector')
process.MessageLogger.cerr.INFO = cms.untracked.VPSet(
    default = cms.untracked.PSet( limit = cms.untracked.int32(0)  ),
)
#process.MessageLogger.cout = cms.untracked.PSet(INFO = cms.untracked.PSet(
    #reportEvery = cms.untracked.int32(100)  # every 100th only
    #limit = cms.untracked.int32(10)        # or limit to 10 printouts...
#))
process.MessageLogger.cerr.FwkReport.reportEvery = 1000 ## really show only every 1000th



##
## Handle huge number of Files
##
process.options = cms.untracked.PSet(
    #wantSummary = cms.untracked.bool(True),
    Rethrow = cms.untracked.vstring("ProductNotFound") # make this exception fatal
    #, fileMode  =  cms.untracked.string('FULLMERGE') # any file order (default): caches all lumi/run products (memory!)
    #, fileMode  =  cms.untracked.string('MERGE') # needs files sorted in run and within run in lumi sections (hard to achieve)
    #, fileMode  =  cms.untracked.string('FULLLUMIMERGE') # needs files sorted in run, caches lumi
    , fileMode  =  cms.untracked.string('NOMERGE') #  no ordering needed, but calls endRun/beginRun etc. at file boundaries
)




process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )



##
## Input Files (CRAFT '09)
##
## --- Monte Carlo ---
#process.load("ApeEstimator.ApeEstimator.samples.CRAFT_mc_31X_cff")
## --- First Reprocessing ---
#process.load("ApeEstimator.ApeEstimator.samples.run109011_109624_FirstRepro_cff")
##
## Input Files (Collisions '10, MinBias 7 TeV)
##
## --- Monte Carlo ---
process.load("ApeEstimator.ApeEstimator.samples.MinBias_mc_356_cff")
## --- Run 132440-132478, First Reprocessing --- (beamspot corrected)
#process.load("ApeEstimator.ApeEstimator.samples.MinBias_run132440_132478_R_356_cff")
## --- Run 133029-133158, Processing ---
#process.load("ApeEstimator.ApeEstimator.samples.MinBias_run133029_133158_P_356_cff")







##
## Trigger Selection
##
process.load("ApeEstimator.ApeEstimator.TriggerSelection_cff")




## FILTER for high purity tracks
import Alignment.CommonAlignmentProducer.AlignmentTrackSelector_cfi
process.MinBiasSkim = Alignment.CommonAlignmentProducer.AlignmentTrackSelector_cfi.AlignmentTrackSelector.clone(
    applyBasicCuts = True,
    filter = True,
    src = 'ALCARECOTkAlMinBias',
    ptMin = 5.,
    pMin = 9.,
    etaMin = -999.,
    etaMax = 999.,
    d0Min = -2.,
    d0Max = 2.,
    dzMin = -15.,
    dzMax = 15.,
    nHitMin = 12,
    nHitMin2D = 2,
    trackQualities = ["highPurity"],
)






process.p = cms.Path(
    #process.TriggerSelectionSequence*
    process.TriggerSelectionSequenceForMC*
    process.MinBiasSkim
)





## define event selection
process.EventSelection = cms.PSet(
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('p')
    )
)




## configure output module
process.out = cms.OutputModule("PoolOutputModule",
    process.EventSelection,
    outputCommands = cms.untracked.vstring('keep *'),
    dropMetaDataForDroppedData = cms.untracked.bool(True),                                     
    fileName = cms.untracked.string('rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356.root')
)
process.load("ApeEstimator.ApeEstimator.PrivateSkim_EventContent_cff")
process.out.outputCommands.extend(process.ApeSkimEventContent.outputCommands)



process.outpath = cms.EndPath(process.out)



