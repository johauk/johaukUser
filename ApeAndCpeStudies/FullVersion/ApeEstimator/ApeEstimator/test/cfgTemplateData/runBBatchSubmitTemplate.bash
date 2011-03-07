#!/bin/bash

export PYTHONHOME=/afs/cern.ch/cms/sw/slc5_ia32_gcc434/external/python/2.6.4-cms

export STAGE_SVCCLASS=cmscafuser


#rfcp /castor/cern.ch/cms/store/caf/user/hauk/data/Mu/Run2010A_Dec22ReReco/apeSkim_THE_NUMBER_.root reco.root
rfcp /castor/cern.ch/cms/store/caf/user/hauk/data/Mu/Run2010B_Dec22ReReco/apeSkim_THE_NUMBER_.root reco.root


cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/batch/workingArea/_THE_NAME___THE_NUMBER__cfg.py
