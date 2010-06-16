import FWCore.ParameterSet.Config as cms

readFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",
    inputCommands = cms.untracked.vstring('keep *', 'drop *_MEtoEDMConverter_*_*'),
    fileNames = readFiles
)
readFiles.extend( [



# 19204401 events in ALCARECO, left 160346 events (1.14 tracks/event) in Skim

'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356001.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356002.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356003.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356004.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356005.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356006.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356007.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356008.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356009.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356010.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356011.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356012.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356013.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356014.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356015.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356016.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356017.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356018.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356019.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356020.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356021.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356022.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356023.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356024.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356025.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356026.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356027.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356028.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356029.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356030.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356031.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356032.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356033.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356034.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356035.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356036.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356037.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356038.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356039.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356040.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356041.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356042.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356043.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356044.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356045.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356046.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356047.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356048.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356049.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356050.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356051.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356052.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356053.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356054.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356055.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356056.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356057.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356058.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356059.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356060.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356061.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356062.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356063.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356064.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356065.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356066.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356067.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356068.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356069.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356070.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356071.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356072.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356073.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356074.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356075.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356076.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356077.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356078.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356079.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356080.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356081.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356082.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356083.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356084.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356085.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356086.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356087.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356088.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356089.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356090.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356091.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356092.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356093.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356094.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356095.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356096.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356097.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356098.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356099.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356100.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356101.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/mc/MinBias_START3X_V26_S09_356102.root',




] );

