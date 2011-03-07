#!/bin/bash

export PYTHONHOME=/afs/cern.ch/cms/sw/slc5_ia32_gcc434/external/python/2.6.4-cms

export STAGE_SVCCLASS=cmscafuser


rfcp _THE_INPUTBASE__THE_NUMBER_.root reco.root


cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/batch/workingArea/_THE_NAME___THE_NUMBER__cfg.py
