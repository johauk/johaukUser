import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",
    inputCommands = cms.untracked.vstring('keep *', 'drop *_MEtoEDMConverter_*_*'),
    fileNames = readFiles
)
readFiles.extend( [



#'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356.root',
'file:/afs/naf.desy.de/user/j/johauk/cms/testing/CMSSW_3_5_6/src/ApeEstimator/ApeEstimator/test/ParticleGun/reco.root',



] );

