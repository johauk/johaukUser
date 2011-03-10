import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

from ApeEstimator.ApeEstimator.samples.GoodRunList_cff import LumisToProcess
source.lumisToProcess = LumisToProcess

readFiles.extend( [

'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/Mu/Run2010B_Dec22ReReco/apeSkim1.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/Mu/Run2010B_Dec22ReReco/apeSkim2.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/Mu/Run2010B_Dec22ReReco/apeSkim3.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/Mu/Run2010B_Dec22ReReco/apeSkim4.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/Mu/Run2010B_Dec22ReReco/apeSkim5.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/Mu/Run2010B_Dec22ReReco/apeSkim6.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/Mu/Run2010B_Dec22ReReco/apeSkim7.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/Mu/Run2010B_Dec22ReReco/apeSkim8.root',



] );


secFiles.extend( [
               ] )

