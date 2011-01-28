#!/bin/bash




cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/cfgTemplate/workingArea/summary_cfg.py


cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/cfgTemplate/workingArea/apeLocalSetting_cfg.py


rm alignment.log



rm $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/cfgTemplate/workingArea/*_cfg.py



