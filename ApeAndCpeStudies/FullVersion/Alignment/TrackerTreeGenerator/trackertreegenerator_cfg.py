import FWCore.ParameterSet.Config as cms

import os


process = cms.Process("TrackerTreeGeneration")


# initialize MessageLogger and output report
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('TrackerTreeGenerator')
process.MessageLogger.cerr.INFO.limit = 0
process.MessageLogger.cerr.default.limit = 0
process.MessageLogger.cerr.TrackerTreeGenerator = cms.untracked.PSet(limit = cms.untracked.int32(-1))



#process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )


## INPUT SOURCE
process.source = cms.Source("EmptySource")


## GEOMETRY
process.load("Configuration.StandardSequences.Geometry_cff")


## CONDITIONS
# use always ideal conditions to get no influence from Alignment on absolute Positions, Orientations...
# so it is clear that when choosing special regions in e.g. globalPhi, Modules of the same Rod are contained in the same region
# --- this is now improved, it is always taken from ideal geometry independent of the GlobalTag
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'DESIGN311_V2::All'


## ANALYZER
process.load("Alignment.TrackerTreeGenerator.trackertreegenerator_cfi")


## Output File Configuration
process.TFileService = cms.Service("TFileService",
    fileName = cms.string(os.environ['CMSSW_BASE'] + '/src/Alignment/TrackerTreeGenerator/hists/TrackerTree.root')
)


process.p = cms.Path(process.TrackerTreeGenerator)
