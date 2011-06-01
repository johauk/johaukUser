#!/bin/bash
cd $CMSSW_BASE/src
#cd ~/cms/CMSSW_4_1_6/src
eval `scram runtime -sh`
cd -
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/SkimProducer/skimProducer_DYToMuMu_cfg.py
#cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/SkimProducer/skimProducer_DYToMuMu2_cfg.py
