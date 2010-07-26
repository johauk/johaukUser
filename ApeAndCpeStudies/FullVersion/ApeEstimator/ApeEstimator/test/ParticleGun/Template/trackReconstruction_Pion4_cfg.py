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
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw301.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw302.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw303.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw304.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw305.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw306.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw307.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw308.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw309.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw310.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw311.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw312.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw313.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw314.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw315.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw316.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw317.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw318.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw319.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw320.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw321.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw322.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw323.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw324.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw325.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw326.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw327.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw328.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw329.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw330.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw331.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw332.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw333.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw334.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw335.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw336.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw337.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw338.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw339.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw340.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw341.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw342.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw343.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw344.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw345.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw346.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw347.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw348.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw349.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw350.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw351.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw352.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw353.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw354.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw355.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw356.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw357.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw358.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw359.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw360.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw361.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw362.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw363.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw364.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw365.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw366.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw367.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw368.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw369.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw370.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw371.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw372.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw373.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw374.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw375.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw376.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw377.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw378.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw379.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw380.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw381.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw382.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw383.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw384.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw385.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw386.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw387.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw388.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw389.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw390.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw391.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw392.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw393.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw394.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw395.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw396.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw397.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw398.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw399.root",
      "rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/raw400.root",
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
    fileName = cms.untracked.string('rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RECO/reco4.root'),
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
