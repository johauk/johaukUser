import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles )

readFiles.extend( [


#'file:/scratch/hh/current/cms/user/hauk/data/testPatTuple/PATtuple_2.root',
'file:/scratch/hh/current/cms/user/hauk/data/testPatTuple/PATtuple_NEW_1_1.root',



] );
