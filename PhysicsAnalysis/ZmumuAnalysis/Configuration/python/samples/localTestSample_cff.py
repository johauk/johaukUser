import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles )

readFiles.extend( [


#'file:/afs/naf.desy.de/user/j/johauk/cms/CMSSW_4_2_3/src/ZmumuAnalysis/Configuration/analysis/test.root',

#'file:/scratch/hh/current/cms/user/hauk/data/testPatTuple/mc2pat_1_1_ntG_Spring11_madgraph_D6T.root',

#'file:/scratch/hh/current/cms/user/hauk/data/testPatTuple/patTuple_1_1_BQg_Summer11_madgraph_Z2.root',

#'file:/scratch/hh/current/cms/user/hauk/data/testPatTuple/patTuple_data.root',
'file:/scratch/hh/current/cms/user/hauk/data/testPatTuple/patTuple_mc.root',


] );
