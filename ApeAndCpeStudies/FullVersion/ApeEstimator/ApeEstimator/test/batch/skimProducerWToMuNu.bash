#!/bin/bash
cd $CMSSW_BASE/src
#cd ~/cms/CMSSW_4_1_6/src
eval `scram runtime -sh`
cd -
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/SkimProducer/skimProducer_WToMuNu_cfg.py
#cmsRun /afs/cern.ch/user/h/hauk/cms/CMSSW_4_1_6/src/ApeEstimator/ApeEstimator/test/SkimProducer/skimProducer_WToMuNu_cfg.py
