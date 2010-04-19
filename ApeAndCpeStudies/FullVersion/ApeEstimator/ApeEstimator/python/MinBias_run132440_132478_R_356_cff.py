import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",
    inputCommands = cms.untracked.vstring('keep *', 'drop *_MEtoEDMConverter_*_*'),
    fileNames = readFiles
)
readFiles.extend( [



'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/Commissioning10/MinimumBias/ALCARECO/Apr1ReReco_StreamTkAlMinBias-v2/0131/440640F4-5C3E-DF11-8DD8-003048678B30.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/Commissioning10/MinimumBias/ALCARECO/Apr1ReReco_StreamTkAlMinBias-v2/0131/94E1553A-5D3E-DF11-947D-00261894382D.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/Commissioning10/MinimumBias/ALCARECO/Apr1ReReco_StreamTkAlMinBias-v2/0139/28C253D3-923E-DF11-AC46-001A92810AD2.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/Commissioning10/MinimumBias/ALCARECO/Apr1ReReco_StreamTkAlMinBias-v2/0139/2C157C30-933E-DF11-9941-0018F3D096D8.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/Commissioning10/MinimumBias/ALCARECO/Apr1ReReco_StreamTkAlMinBias-v2/0139/3A0DA6E7-923E-DF11-880D-00304867BED8.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/Commissioning10/MinimumBias/ALCARECO/Apr1ReReco_StreamTkAlMinBias-v2/0139/A6291310-933E-DF11-AC2D-001A92971BDA.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/Commissioning10/MinimumBias/ALCARECO/Apr1ReReco_StreamTkAlMinBias-v2/0139/C074CC28-933E-DF11-A532-001A92971B16.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/Commissioning10/MinimumBias/ALCARECO/Apr1ReReco_StreamTkAlMinBias-v2/0139/CCFBF4E5-923E-DF11-A16D-001A92971B04.root',




] );

