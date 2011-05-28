#!/bin/bash
cd $CMSSW_BASE/src
eval `scram runtime -sh`
cd -
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/SkimProducer/skimProducer_data_cfg.py
