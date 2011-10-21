#!/bin/bash


cd $CMSSW_BASE/src
eval `scram runtime -sh`
cd -


cmsStageIn _THE_INPUTBASE__THE_NUMBER_.root reco.root


cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/cfgTemplate/apeEstimator_cfg.py_THE_COMMANDS_






