#!/bin/bash

DIRBASE="$CMSSW_BASE/src/ApeEstimator/ApeEstimator"



mkdir $DIRBASE/hists/
mkdir $DIRBASE/hists/workingArea/
mkdir $DIRBASE/test/batch/workingArea/
mkdir $DIRBASE/test/cfgTemplate/workingArea/
mkdir $DIRBASE/test/cfgTemplateMc/workingArea/
mkdir $DIRBASE/test/cfgTemplateData/workingArea/



cp $DIRBASE/test/cfgTemplate/batchSubmitTemplate.bash $DIRBASE/test/cfgTemplateMc/batchSubmitTemplate.bash
cp $DIRBASE/test/cfgTemplate/createStep2Baseline.bash $DIRBASE/test/cfgTemplateMc/createStep2Baseline.bash
cp $DIRBASE/test/cfgTemplate/startStep1.bash $DIRBASE/test/cfgTemplateMc/startStep1.bash
cp $DIRBASE/test/cfgTemplate/startStep2.bash $DIRBASE/test/cfgTemplateMc/startStep2.bash
cp $DIRBASE/test/cfgTemplate/summaryBaseline_cfg.py $DIRBASE/test/cfgTemplateMc/summaryBaseline_cfg.py


cp $DIRBASE/test/cfgTemplate/apeLocalSettingTemplate_cfg.py $DIRBASE/test/cfgTemplateData/apeLocalSettingTemplate_cfg.py
cp $DIRBASE/test/cfgTemplate/batchSubmitTemplate.bash $DIRBASE/test/cfgTemplateData/batchSubmitTemplate.bash
cp $DIRBASE/test/cfgTemplate/createStep2IterN.bash $DIRBASE/test/cfgTemplateData/createStep2IterN.bash
cp $DIRBASE/test/cfgTemplate/startStep1.bash $DIRBASE/test/cfgTemplateData/startStep1.bash
cp $DIRBASE/test/cfgTemplate/startStep2.bash $DIRBASE/test/cfgTemplateData/startStep2.bash
cp $DIRBASE/test/cfgTemplate/summaryTemplate_cfg.py $DIRBASE/test/cfgTemplateData/summaryTemplate_cfg.py









