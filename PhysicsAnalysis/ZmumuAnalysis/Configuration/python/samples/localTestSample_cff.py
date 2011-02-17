import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles )

readFiles.extend( [


'file:/scratch/hh/current/cms/user/hauk/data/testPatTuple/mcpat_1_1_eXu_madgraph_D6T.root',


] );
