#!/bin/bash

if [ ! $# == 1 ]; then
  echo "Usage: $0 sample"
  exit 1
fi

sample="$1"

cd $CMSSW_BASE/src
eval `scram runtime -sh`
cd -
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/SkimProducer/skimProducer_cfg.py isTest=False sample=$sample











