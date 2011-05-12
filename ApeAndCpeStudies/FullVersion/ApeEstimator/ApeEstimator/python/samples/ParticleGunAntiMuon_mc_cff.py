import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",
    inputCommands = cms.untracked.vstring('keep *', 'drop *_MEtoEDMConverter_*_*'),
    fileNames = readFiles
)
readFiles.extend( [



'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiMuon/RECO/reco1.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiMuon/RECO/reco2.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiMuon/RECO/reco3.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiMuon/RECO/reco4.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiMuon/RECO/reco5.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiMuon/RECO/reco6.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiMuon/RECO/reco7.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiMuon/RECO/reco8.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiMuon/RECO/reco9.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiMuon/RECO/reco10.root',


] );

