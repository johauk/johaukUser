import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles )

readFiles.extend( [


#'file:/scratch/hh/current/cms/user/hauk/data/testPatTuple/mcpat_1_1_eXu_madgraph_D6T.root',
#'file:/scratch/hh/current/cms/user/hauk/data/testPatTuple/mcpat_1_3_bfP_madgraph_Z2.root',

#'file:/scratch/hh/current/cms/user/hauk/data/testPatTupleData/datapat_12_1_wii_Run2011A_PromptReco_v1.root',

'file:/scratch/hh/current/cms/user/hauk/data/testPatTuple/mc2pat_1_1_ntG_Spring11_madgraph_D6T.root',

] );
