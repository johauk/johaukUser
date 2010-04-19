import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",
    inputCommands = cms.untracked.vstring('keep *', 'drop *_MEtoEDMConverter_*_*'),
    fileNames = readFiles
)
readFiles.extend( [



'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/user/emiglior/ALCARECO/mc7TeV/Spring10/TkAlMinBias_2_1.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/user/emiglior/ALCARECO/mc7TeV/Spring10/TkAlMinBias_4_2.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/user/emiglior/ALCARECO/mc7TeV/Spring10/TkAlMinBias_5_1.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/user/emiglior/ALCARECO/mc7TeV/Spring10/TkAlMinBias_6_1.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/user/emiglior/ALCARECO/mc7TeV/Spring10/TkAlMinBias_7_1.root',


] );

