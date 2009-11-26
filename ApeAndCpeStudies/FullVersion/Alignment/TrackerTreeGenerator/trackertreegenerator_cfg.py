import FWCore.ParameterSet.Config as cms

process = cms.Process("TrackerTreeGeneration")


# initialize MessageLogger and output report
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('TrackerTreeGenerator')
process.MessageLogger.cerr.INFO = cms.untracked.VPSet(
    default = cms.untracked.PSet( limit = cms.untracked.int32(0)  ),
    TrackerTreeGenerator = cms.untracked.PSet( limit = cms.untracked.int32(-1) )
)
#process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )


## INPUT SOURCE
process.source = cms.Source("EmptySource")


## GEOMETRY
process.load("Configuration.StandardSequences.Geometry_cff")


## CONDITIONS
# use always ideal conditions to get no influence from Alignment on absolute Positions, Orientations...
# so it is clear that when choosing special regions in e.g. globalPhi, Modules of the same Rod are contained in the same region
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cfi")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = 'IDEAL_V12::All'
process.GlobalTag.globaltag = 'DESIGN_31X_V8::All'


## ANALYZER
process.load("Alignment.TrackerTreeGenerator.trackertreegenerator_cfi")


## Output File Configuration
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('/afs/cern.ch/user/h/hauk/cms/CMSSW_3_3_1/src/Alignment/TrackerTreeGenerator/hists/TrackerTree.root')
)


process.p = cms.Path(process.TrackerTreeGenerator)
