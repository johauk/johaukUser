#!/bin/bash


cd $CMSSW_BASE/src
eval `scram runtime -sh`
cd -


export STAGE_SVCCLASS=cmscafuser


rfcp _THE_INPUTBASE__THE_NUMBER_.root reco.root


cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/batch/workingArea/_THE_NAME___THE_NUMBER__cfg.py
