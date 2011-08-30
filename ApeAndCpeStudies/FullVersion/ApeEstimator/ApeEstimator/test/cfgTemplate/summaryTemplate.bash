#!/bin/bash


base="$CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/cfgTemplate"



cmsRun $base/apeEstimatorSummary_cfg.py_THE_COMMANDS_


cmsRun $base/apeLocalSetting_cfg.py_THE_COMMANDS_



if [ $? -eq 0 ] ; then
  echo "APE DB-Object created"
else
  echo "No APE DB-Object created"
fi

if [ -a alignment.log ] ; then
  rm alignment.log
fi




