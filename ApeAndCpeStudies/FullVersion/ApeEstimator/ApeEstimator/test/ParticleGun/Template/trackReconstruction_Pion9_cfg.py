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
    version = cms.untracked.string('$Revision: 1.2 $'),
    annotation = cms.untracked.string('step2 nevts:100'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)



# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw801.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw802.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw803.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw804.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw805.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw806.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw807.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw808.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw809.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw810.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw811.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw812.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw813.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw814.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw815.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw816.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw817.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw818.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw819.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw820.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw821.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw822.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw823.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw824.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw825.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw826.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw827.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw828.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw829.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw830.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw831.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw832.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw833.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw834.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw835.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw836.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw837.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw838.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw839.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw840.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw841.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw842.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw843.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw844.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw845.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw846.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw847.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw848.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw849.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw850.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw851.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw852.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw853.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw854.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw855.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw856.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw857.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw858.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw859.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw860.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw861.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw862.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw863.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw864.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw865.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw866.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw867.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw868.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw869.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw870.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw871.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw872.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw873.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw874.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw875.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw876.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw877.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw878.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw879.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw880.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw881.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw882.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw883.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw884.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw885.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw886.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw887.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw888.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw889.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw890.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw891.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw892.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw893.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw894.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw895.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw896.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw897.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw898.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw899.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw900.root",
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
    fileName = cms.untracked.string('rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RECO/reco9.root'),
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
process.GlobalTag.globaltag = 'DESIGN_39_V7::All'
#process.GlobalTag.globaltag = 'MC_39Y_V7::All'
#process.GlobalTag.globaltag = 'START39_V8::All'
# Use correct Beamspot for simulated Vertex smearing of ParticleGun
process.load("ApeEstimator.ApeEstimator.BeamspotForParticleGun_cff")



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
