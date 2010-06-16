import FWCore.ParameterSet.Config as cms



##### ----------- ReReco should have most recent beamspot, so do not use this version, but correct globalTag
## Use corrected beamspot
#import CalibTracker.Configuration.Common.PoolDBESSource_cfi
#myBeamspot = CalibTracker.Configuration.Common.PoolDBESSource_cfi.poolDBESSource.clone(
#    connect = cms.string('frontier://PromptProd/CMS_COND_31X_BEAMSPOT'),
#    toGet = cms.VPSet(
#      cms.PSet(
#        record = cms.string('BeamSpotObjectsRcd'),
#        tag = cms.string('BeamSpotObjects_2009_v7_offline')
#      )
#    )
#)
#es_prefer_corrBeamspot = cms.ESPrefer("PoolDBESSource","myBeamspot")










readFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",
    inputCommands = cms.untracked.vstring('keep *', 'drop *_MEtoEDMConverter_*_*'),
    fileNames = readFiles
)
readFiles.extend( [



# 35724717 events in ALCARECO, left 476304 events (1.14 tracks/event) in Skim



'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3001.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3002.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3003.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3004.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3005.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3006.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3007.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3008.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3009.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3010.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3011.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3012.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3013.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3014.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3015.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3016.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3017.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3018.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3019.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3020.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3021.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3022.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3023.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3024.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3025.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3026.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3027.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3028.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3029.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3030.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3031.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3032.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3033.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3034.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3035.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3036.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3037.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3038.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3039.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3040.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3041.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3042.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3043.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3044.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3045.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3046.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3047.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3048.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3049.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3050.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3051.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3052.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3053.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3054.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3055.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3056.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3057.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3058.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3059.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3060.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3061.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3062.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3063.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3064.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3065.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3066.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3067.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3068.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3069.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3070.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3071.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3072.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3073.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3074.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3075.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3076.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3077.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3078.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3079.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3080.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3081.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3082.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3083.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3084.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3085.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3086.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3087.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3088.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3089.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3090.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3091.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3092.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3093.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3094.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3095.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3096.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3097.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3098.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3099.root',

'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3100.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3101.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3102.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3103.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3104.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3105.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3106.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3107.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3108.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3109.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3110.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3111.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3112.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3113.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3114.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3115.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3116.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3117.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3118.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3119.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3120.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3121.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3122.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3123.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3124.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3125.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3126.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3127.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3128.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3129.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3130.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3131.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3132.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3133.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3134.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3135.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3136.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3137.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3138.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3139.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3140.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3141.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3142.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3143.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3144.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3145.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3146.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3147.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3148.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3149.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3150.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3151.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3152.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3153.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3154.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3155.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3156.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3157.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3158.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3159.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3160.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3161.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3162.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3163.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3164.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3165.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3166.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3167.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3168.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3169.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3170.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3171.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3172.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3173.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3174.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3175.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3176.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3177.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3178.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3179.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3180.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3181.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3182.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3183.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3184.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3185.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3186.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3187.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3188.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3189.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3190.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3191.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3192.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3193.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3194.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3195.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3196.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3197.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3198.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3199.root',

'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3200.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3201.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3202.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3203.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3204.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3205.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3206.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3207.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3208.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3209.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3210.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3211.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3212.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3213.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3214.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3215.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3216.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3217.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3218.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3219.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3220.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3221.root',
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/caf/user/hauk/data/MinBias/May6thReReco/MinBias_run132440_134987_RMay06_358p3222.root',



















] );

