import os

import FWCore.ParameterSet.Config as cms




##
## Setup command line options
##
import FWCore.ParameterSet.VarParsing as VarParsing
import sys
options = VarParsing.VarParsing ('standard')
options.register('sample', 'data', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "Input sample")
options.register('fileNumber', 1, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "Input file number")
options.register('iterNumber', 0, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int, "Iteration number")
options.register('lastIter', False, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.bool, "Last iteration")
options.register('alignRcd','design', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "AlignmentRcd")



# get and parse the command line arguments
if( hasattr(sys, "argv") ):
    for args in sys.argv :
        arg = args.split(',')
        for val in arg:
            val = val.split('=')
            if(len(val)==2):
                setattr(options,val[0], val[1])

print "Input sample: ", options.sample
print "Input file number", options.fileNumber
print "Iteration number: ", options.iterNumber
print "Last iteration: ", options.lastIter
print "AlignmentRcd: ", options.alignRcd



##
## Process definition
##
process = cms.Process("ApeEstimator")



##
## Message Logger
##
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.categories.append('SectorBuilder')
process.MessageLogger.categories.append('ResidualErrorBinning')
process.MessageLogger.categories.append('HitSelector')
process.MessageLogger.categories.append('CalculateAPE')
process.MessageLogger.categories.append('ApeEstimator')
#process.MessageLogger.categories.append('TrackRefitter')
process.MessageLogger.categories.append('AlignmentTrackSelector')
process.MessageLogger.cerr.INFO.limit = 0
process.MessageLogger.cerr.default.limit = -1
process.MessageLogger.cerr.SectorBuilder = cms.untracked.PSet(limit = cms.untracked.int32(-1))
process.MessageLogger.cerr.HitSelector = cms.untracked.PSet(limit = cms.untracked.int32(-1))
process.MessageLogger.cerr.CalculateAPE = cms.untracked.PSet(limit = cms.untracked.int32(-1))
process.MessageLogger.cerr.ApeEstimator = cms.untracked.PSet(limit = cms.untracked.int32(-1))
process.MessageLogger.cerr.AlignmentTrackSelector = cms.untracked.PSet(limit = cms.untracked.int32(-1))

#process.MessageLogger.cout = cms.untracked.PSet(INFO = cms.untracked.PSet(
#    reportEvery = cms.untracked.int32(100),  # every 100th only
#    limit = cms.untracked.int32(10),         # or limit to 10 printouts...
#))
process.MessageLogger.cerr.FwkReport.reportEvery = 1000 ## really show only every 1000th



##
## Process options
##
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
)



##
## Input sample definition
##
isData = False
isQcd = isWlnu = isZmumu = isZtautau = False
isMc = False
isParticleGunMuon = isParticleGunPion = False
isParticleGun = False
if options.sample == 'data':
    isData = True
elif options.sample == 'qcd':
    isQcd = True
    isMc = True
elif options.sample == 'wlnu':
    isWlnu = True
    isMc = True
elif options.sample == 'zmumu':
    isZmumu = True
    isMc = True
elif options.sample == 'ztautau':
    isZtautau = True
    isMc = True
elif options.sample == 'ParticleGunMuon':
    isParticleGunMuon = True
    isParticleGun = True
elif options.sample == 'ParticleGunPion':
    isParticleGunPion = True
    isParticleGun = True
else:
    print 'ERROR --- incorrect data sammple: ', options.sample
    exit(8888)



##
## Input Files
##
readFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",
    fileNames = readFiles
)
readFiles.extend( [
    'file:reco.root',
] )



##
## Number of Events (should be after input file)
##
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
if isQcd:
  if options.fileNumber==1: process.maxEvents.input = 87763    # 854181 events
  elif options.fileNumber==2: process.maxEvents.input = 87763  # 851413 events
  elif options.fileNumber==3: process.maxEvents.input = 87763  # 206553 events
elif isWlnu:
  if options.fileNumber==1: process.maxEvents.input = 56348    # 894904 events
  elif options.fileNumber==2: process.maxEvents.input = 56348  # 892738 events
  elif options.fileNumber==3: process.maxEvents.input = 56348  # 895703 events
  elif options.fileNumber==4: process.maxEvents.input = 56348  # 365205 events
elif isZmumu:
  if options.fileNumber==1: process.maxEvents.input = 12043    # 619625 events
  elif options.fileNumber==2: process.maxEvents.input = 12043  # 618007 events
  elif options.fileNumber==3: process.maxEvents.input = 12043  # 209738	events
elif isZtautau:
  if options.fileNumber==1: process.maxEvents.input = 414      # 143721 events



##
## Check run and event numbers for Dublicates --- only for real data
##
#process.source.duplicateCheckMode = cms.untracked.string("noDuplicateCheck")
#process.source.duplicateCheckMode = cms.untracked.string("checkEachFile")
process.source.duplicateCheckMode = cms.untracked.string("checkEachRealDataFile")
#process.source.duplicateCheckMode = cms.untracked.string("checkAllFilesOpened")   # default value



##
## Whole Refitter Sequence
##
process.load("ApeEstimator.ApeEstimator.TrackRefitter_38T_cff")
if isParticleGun:
    process.GlobalTag.globaltag = 'DESIGN311_V2::All'
elif isMc:
    #process.GlobalTag.globaltag = 'DESIGN311_V2::All'
    #process.GlobalTag.globaltag = 'START311_V2::All'
    process.GlobalTag.globaltag = 'MC_311_V2::All'
elif isData:
    process.GlobalTag.globaltag = 'FT_R_311_V4A::All'
## --- Further information (Monte Carlo and Data) ---
#process.TTRHBuilderGeometricAndTemplate.StripCPE = 'StripCPEfromTrackAngle'
#process.TTRHBuilderGeometricAndTemplate.PixelCPE = 'PixelCPEGeneric'
#process.HighPuritySelector.src = 'generalTracks'
process.HighPuritySelector.src = 'MuSkim'



##
## Alignment and APE
##
import CalibTracker.Configuration.Common.PoolDBESSource_cfi
## Choose Alignment (w/o touching APE)
if options.alignRcd=='design':
  process.myTrackerAlignment = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(
    connect = 'frontier://FrontierProd/CMS_COND_31X_FROM21X',
    toGet = cms.VPSet(
      cms.PSet(
        record = cms.string('TrackerAlignmentRcd'),
        tag = cms.string('TrackerIdealGeometry210_mc'),
      )
    )
  )
  process.es_prefer_trackerAlignment = cms.ESPrefer("PoolDBESSource","myTrackerAlignment")
elif options.alignRcd == 'data':
  pass
elif options.alignRcd == 'misalTob20':
  process.myTrackerAlignment = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(
    connect = 'sqlite_file:/afs/cern.ch/user/h/hauk/scratch0/apeStudies/misalignments/AlignmentsTob20.db',
    toGet = cms.VPSet(
      cms.PSet(
        record = cms.string('TrackerAlignmentRcd'),
        tag = cms.string('TrackerScenario'),
      )
    )
  )
  process.es_prefer_trackerAlignment = cms.ESPrefer("PoolDBESSource","myTrackerAlignment")
elif options.alignRcd == '':
  pass
else:
  print 'ERROR --- incorrect alignment: ', options.alignRcd
  exit(8888)

## APE
if options.iterNumber==0:
    process.myTrackerAlignmentErr = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(
      connect = 'frontier://FrontierProd/CMS_COND_31X_FROM21X',
      toGet = [
        cms.PSet(
          record = cms.string('TrackerAlignmentErrorRcd'),
          tag = cms.string('TrackerIdealGeometryErrors210_mc'),
        )
      ],
    )
    process.es_prefer_trackerAlignmentErr = cms.ESPrefer("PoolDBESSource","myTrackerAlignmentErr")
else:
    process.myTrackerAlignmentErr = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(
      connect = 'sqlite_file:/afs/cern.ch/user/h/hauk/scratch0/apeStudies/apeObjects/apeIter'+str(options.iterNumber-1)+'.db',
      toGet = [
        cms.PSet(
          record = cms.string('TrackerAlignmentErrorRcd'),
          tag = cms.string('AlignmentErrors'),
        )
      ],
    )
    process.es_prefer_trackerAlignmentErr = cms.ESPrefer("PoolDBESSource","myTrackerAlignmentErr")



##
## Beamspot (Use correct Beamspot for simulated Vertex smearing of ParticleGun)
##
if isParticleGun:
    process.load("ApeEstimator.ApeEstimator.BeamspotForParticleGun_cff")



##
## ApeEstimator
##
from ApeEstimator.ApeEstimator.ApeEstimator_cff import *
process.ApeEstimator1 = ApeEstimator.clone(
    tjTkAssociationMapTag = "TrackRefitterHighPurityForApeEstimator",
    analyzerMode = False,
)

process.ApeEstimator2 = ApeAnalyzer.clone()
process.ApeEstimator3 = process.ApeEstimator2.clone(
    zoomHists = False,
)

process.ApeEstimatorSequence = cms.Sequence(process.ApeEstimator1)
if options.iterNumber==0:
  process.ApeEstimatorSequence *= process.ApeEstimator2
  process.ApeEstimatorSequence *= process.ApeEstimator3
elif options.lastIter == True:
  process.ApeEstimatorSequence *= process.ApeEstimator2



##
## Output File Configuration
##
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/workingArea/'+options.sample+str(options.fileNumber)+'.root'),
    closeFileFast = cms.untracked.bool(True)
)



##
## Path
##
process.p = cms.Path(
    #process.TriggerSelectionSequence*
    process.RefitterHighPuritySequence*
    process.ApeEstimatorSequence
)



