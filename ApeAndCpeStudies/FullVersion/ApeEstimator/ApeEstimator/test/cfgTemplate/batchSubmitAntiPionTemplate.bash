#!/bin/bash

export PYTHONHOME=/afs/cern.ch/cms/sw/slc5_ia32_gcc434/external/python/2.6.4-cms


rfcp /castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunAntiPion/RECO/reco_THE_NUMBER_.root reco.root


cmsRun /afs/cern.ch/user/h/hauk/cms/CMSSW_3_6_1_patch4/src/ApeEstimator/ApeEstimator/test/cfgTemplate/workingArea/antiPion__THE_NUMBER__cfg.py
