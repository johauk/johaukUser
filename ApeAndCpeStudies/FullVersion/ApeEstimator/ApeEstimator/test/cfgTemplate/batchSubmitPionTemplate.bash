#!/bin/bash

export PYTHONHOME=/afs/cern.ch/cms/sw/slc5_ia32_gcc434/external/python/2.6.4-cms

export STAGE_SVCCLASS=cmscafuser


rfcp /castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RECO/reco_THE_NUMBER_.root reco.root


cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/cfgTemplate/workingArea/pion__THE_NUMBER__cfg.py
