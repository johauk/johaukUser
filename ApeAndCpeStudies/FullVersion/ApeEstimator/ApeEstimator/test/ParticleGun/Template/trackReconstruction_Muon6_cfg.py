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
    version = cms.untracked.string('$Revision: 1.1 $'),
    annotation = cms.untracked.string('step2 nevts:100'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)



# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw501.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw502.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw503.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw504.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw505.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw506.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw507.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw508.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw509.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw510.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw511.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw512.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw513.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw514.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw515.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw516.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw517.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw518.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw519.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw520.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw521.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw522.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw523.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw524.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw525.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw526.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw527.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw528.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw529.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw530.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw531.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw532.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw533.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw534.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw535.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw536.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw537.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw538.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw539.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw540.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw541.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw542.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw543.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw544.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw545.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw546.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw547.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw548.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw549.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw550.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw551.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw552.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw553.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw554.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw555.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw556.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw557.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw558.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw559.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw560.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw561.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw562.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw563.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw564.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw565.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw566.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw567.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw568.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw569.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw570.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw571.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw572.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw573.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw574.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw575.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw576.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw577.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw578.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw579.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw580.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw581.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw582.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw583.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw584.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw585.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw586.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw587.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw588.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw589.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw590.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw591.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw592.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw593.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw594.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw595.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw596.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw597.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw598.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw599.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RAW/raw600.root",
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
    fileName = cms.untracked.string('rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunMuon/RECO/reco6.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-RECO'),
        filterName = cms.untracked.string('')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('reconstruction_step')
    ),
    dropMetaData = cms.untracked.string('DROPPED'),
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