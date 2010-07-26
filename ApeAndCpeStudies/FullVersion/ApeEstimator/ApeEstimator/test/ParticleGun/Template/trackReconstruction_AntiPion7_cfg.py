# Auto generated configuration file
# using: 
# Revision: 1.177 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: step2 -s RAW2DIGI,L1Reco,RECO --datatier GEN-SIM-RECO --eventcontent RECOSIM --geometry DB --conditions auto:mc -n 100 --fileout file:reco.root --filein file:raw.root --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('RECO')



## add message logger
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.categories.append('SiStripQuality')
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.cerr.FwkReport.reportEvery = 1000



## Options
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
    #SkipEvent = cms.untracked.vstring('ProductNotFound'),
    #Rethrow = cms.untracked.vstring("ProductNotFound"), # make this exception fatal (now default?)
)



# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.MixingNoPileUp_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContent_cff')

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.4 $'),
    annotation = cms.untracked.string('step2 nevts:100'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)



# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw601.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw602.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw603.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw604.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw605.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw606.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw607.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw608.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw609.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw610.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw611.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw612.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw613.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw614.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw615.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw616.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw617.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw618.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw619.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw620.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw621.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw622.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw623.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw624.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw625.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw626.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw627.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw628.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw629.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw630.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw631.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw632.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw633.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw634.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw635.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw636.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw637.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw638.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw639.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw640.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw641.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw642.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw643.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw644.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw645.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw646.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw647.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw648.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw649.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw650.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw651.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw652.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw653.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw654.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw655.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw656.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw657.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw658.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw659.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw660.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw661.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw662.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw663.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw664.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw665.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw666.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw667.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw668.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw669.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw670.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw671.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw672.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw673.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw674.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw675.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw676.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw677.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw678.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw679.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw680.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw681.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw682.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw683.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw684.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw685.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw686.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw687.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw688.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw689.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw690.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw691.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw692.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw693.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw694.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw695.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw696.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw697.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw698.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw699.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RAW/raw700.root",
    ),
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    #duplicateCheckMode = cms.untracked.string("checkEachFile"),
    #duplicateCheckMode = cms.untracked.string("checkEachRealDataFile"),
    #duplicateCheckMode = cms.untracked.string("checkAllFilesOpened"),   # default value
)



# Output definition
process.output = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    #overrideInputFileSplitLevels = cms.untracked.bool(True),
    outputCommands = process.RECOSIMEventContent.outputCommands,
    #fileName = cms.untracked.string('file:reco.root'),
    fileName = cms.untracked.string('rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RECO/reco7.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-RECO'),
        filterName = cms.untracked.string('')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('reconstruction_step')
    ),
    dropMetaDataForDroppedData = cms.untracked.bool(True),
)

# Additional output definition
process.load("ApeEstimator.ApeEstimator.PrivateSkim_EventContent_cff")
process.output.outputCommands.extend(process.ReconstructionEventContent.outputCommands)



# Other statements
process.GlobalTag.globaltag = 'DESIGN_36_V10::All'
#process.GlobalTag.globaltag = 'MC_36Y_V10::All'
#process.GlobalTag.globaltag = 'START36_V10::All'

## ALIGNMENT CONSTANTS & APE (set to zero)
import CalibTracker.Configuration.Common.PoolDBESSource_cfi
myTrackerAlignment = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(
    connect = 'frontier://FrontierProd/CMS_COND_31X_FROM21X', # or your sqlite file
    toGet = cms.VPSet(
      cms.PSet(
        record = cms.string('TrackerAlignmentRcd'),
        tag = cms.string('TrackerIdealGeometry210_mc') # your tag
        )
      )
    )
es_prefer_trackerAlignment = cms.ESPrefer("PoolDBESSource","myTrackerAlignment")

## APE (set to zero)
myTrackerAlignmentErr = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(
    connect = cms.string('frontier://FrontierProd/CMS_COND_31X_FROM21X'),
    toGet = cms.VPSet(
      cms.PSet(
        record = cms.string('TrackerAlignmentErrorRcd'),
        tag = cms.string('TrackerIdealGeometryErrors210_mc')
      )
    )
)
es_prefer_trackerAlignmentErr = cms.ESPrefer("PoolDBESSource","myTrackerAlignmentErr")



# Filter used to drop events where not exactly one track is reconstructed (from CommonTools/CandUtils)

process.minOneTrackFilter = cms.EDFilter("TrackCountFilter",
    src = cms.InputTag("generalTracks"),
    minNumber = cms.uint32(1),
    #filter = cms.bool(True),
)
process.minTwoTrackFilter = process.minOneTrackFilter.clone(
  minNumber = 2,
)
process.oneTrackFilter = cms.Sequence(process.minOneTrackFilter + ~process.minTwoTrackFilter)



# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
#process.L1Reco_step = cms.Path(process.L1Reco)
## --- trial: reduce to track reco only ---
#process.reconstruction_step = cms.Path(process.reconstruction)
#process.reconstruction_step = cms.Path(process.trackerlocalreco * (process.offlineBeamSpot + process.recopixelvertexing * process.ckftracks_woBH) * process.logErrorHarvester)
process.reconstruction_step = cms.Path(process.trackerlocalreco * (process.offlineBeamSpot + process.recopixelvertexing * process.ckftracks) * process.oneTrackFilter * process.logErrorHarvester)
process.endjob_step = cms.Path(process.endOfProcess)
process.out_step = cms.EndPath(process.output)

# Schedule definition
#process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.out_step)
process.schedule = cms.Schedule(process.raw2digi_step,process.reconstruction_step,process.endjob_step,process.out_step)
