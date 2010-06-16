import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",
    inputCommands = cms.untracked.vstring('keep *', 'drop *_MEtoEDMConverter_*_*'),
    fileNames = readFiles
)
readFiles.extend( [



'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/mc/Summer09/TkCosmics38T/ALCARECO/STARTUP31X_V3_StreamTkAlCosmics0T-v1/0008/EAC8AD50-FAB4-DE11-8194-00304832293E.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/mc/Summer09/TkCosmics38T/ALCARECO/STARTUP31X_V3_StreamTkAlCosmics0T-v1/0008/C6BD3D77-FFB4-DE11-B46E-0002B3E919CB.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/mc/Summer09/TkCosmics38T/ALCARECO/STARTUP31X_V3_StreamTkAlCosmics0T-v1/0008/BE6AA317-69B4-DE11-BED2-001EC9AA9E96.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/mc/Summer09/TkCosmics38T/ALCARECO/STARTUP31X_V3_StreamTkAlCosmics0T-v1/0008/A4242909-75B4-DE11-9C49-00163691DCC2.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/mc/Summer09/TkCosmics38T/ALCARECO/STARTUP31X_V3_StreamTkAlCosmics0T-v1/0008/123A475B-4FB4-DE11-8765-001E68865229.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/mc/Summer09/TkCosmics38T/ALCARECO/STARTUP31X_V3_StreamTkAlCosmics0T-v1/0008/1010B486-6AB4-DE11-8937-00304867FEAB.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/mc/Summer09/TkCosmics38T/ALCARECO/STARTUP31X_V3_StreamTkAlCosmics0T-v1/0007/DE7893A2-5BB4-DE11-B09F-00163691DC86.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/mc/Summer09/TkCosmics38T/ALCARECO/STARTUP31X_V3_StreamTkAlCosmics0T-v1/0007/B0E11A2E-90B4-DE11-983E-0002B3E92717.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/mc/Summer09/TkCosmics38T/ALCARECO/STARTUP31X_V3_StreamTkAlCosmics0T-v1/0007/A6730957-7DB4-DE11-862B-000102EB84F3.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/mc/Summer09/TkCosmics38T/ALCARECO/STARTUP31X_V3_StreamTkAlCosmics0T-v1/0007/A6176ADA-4FB4-DE11-BF45-001EC9AAA3D7.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/mc/Summer09/TkCosmics38T/ALCARECO/STARTUP31X_V3_StreamTkAlCosmics0T-v1/0007/7C31A75E-30B4-DE11-9382-00304867FD03.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/mc/Summer09/TkCosmics38T/ALCARECO/STARTUP31X_V3_StreamTkAlCosmics0T-v1/0006/FCC79DC6-24B4-DE11-9B60-00163691DA96.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/mc/Summer09/TkCosmics38T/ALCARECO/STARTUP31X_V3_StreamTkAlCosmics0T-v1/0006/DE2C8C72-3EB4-DE11-9B99-000E0C4DE4C2.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/mc/Summer09/TkCosmics38T/ALCARECO/STARTUP31X_V3_StreamTkAlCosmics0T-v1/0006/34449302-30B4-DE11-A8A1-001EC9AAD4F4.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/mc/Summer09/TkCosmics38T/ALCARECO/STARTUP31X_V3_StreamTkAlCosmics0T-v1/0006/20DF2002-44B4-DE11-80AC-00163691DA96.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/mc/Summer09/TkCosmics38T/ALCARECO/STARTUP31X_V3_StreamTkAlCosmics0T-v1/0005/D6012F0D-0CB4-DE11-94BF-00163691DC02.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/mc/Summer09/TkCosmics38T/ALCARECO/STARTUP31X_V3_StreamTkAlCosmics0T-v1/0005/46F7C180-F0B3-DE11-AC43-001EC9AA9AAE.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/mc/Summer09/TkCosmics38T/ALCARECO/STARTUP31X_V3_StreamTkAlCosmics0T-v1/0005/40431B83-17B4-DE11-94B1-0016368E0D00.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/mc/Summer09/TkCosmics38T/ALCARECO/STARTUP31X_V3_StreamTkAlCosmics0T-v1/0005/2CD0DC09-1FB4-DE11-A5CC-00238BBD7594.root' 



] );
