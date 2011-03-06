#!/bin/bash




cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/batch/workingArea/summary_cfg.py


cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/batch/workingArea/apeLocalSetting_cfg.py


rm alignment.log



rm $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/batch/workingArea/*_cfg.py

rm $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/batch/workingArea/*.bash

