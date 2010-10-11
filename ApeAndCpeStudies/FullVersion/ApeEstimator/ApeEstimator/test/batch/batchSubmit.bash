#!/bin/bash

export PYTHONHOME=/afs/cern.ch/cms/sw/slc5_ia32_gcc434/external/python/2.6.4-cms

#pwd
#ls

# cmsStageIn does not work here...
#cmsStageIn /store/caf/user/hauk/mc/ParticleGunPion/RECO/reco1.root reco1.root
rfcp /castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RECO/reco1.root reco.root

#ls

cmsRun /afs/cern.ch/user/h/hauk/cms/CMSSW_3_6_1_patch4/src/ApeEstimator/ApeEstimator/test/testApeestimator_particleGun_cfg.py
