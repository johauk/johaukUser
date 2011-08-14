#!/bin/bash

DIRBASE="$CMSSW_BASE/src/ApeEstimator/ApeEstimator"



mkdir $DIRBASE/hists/
mkdir $DIRBASE/hists/workingArea/
mkdir $DIRBASE/test/batch/workingArea/
mkdir $DIRBASE/test/cfgTemplateMc/workingArea/
mkdir $DIRBASE/test/cfgTemplateData/workingArea/
mkdir $DIRBASE/test/cfgTemplateParticleGun/workingArea/



cp $DIRBASE/test/cfgTemplate/createStep2.bash $DIRBASE/test/cfgTemplateMc/createStep2.bash
cp $DIRBASE/test/cfgTemplate/startStep1.bash $DIRBASE/test/cfgTemplateMc/startStep1.bash
cp $DIRBASE/test/cfgTemplate/startStep2.bash $DIRBASE/test/cfgTemplateMc/startStep2.bash


cp $DIRBASE/test/cfgTemplate/createStep2.bash $DIRBASE/test/cfgTemplateData/createStep2.bash
cp $DIRBASE/test/cfgTemplate/startStep1.bash $DIRBASE/test/cfgTemplateData/startStep1.bash
cp $DIRBASE/test/cfgTemplate/startStep2.bash $DIRBASE/test/cfgTemplateData/startStep2.bash


cp $DIRBASE/test/cfgTemplate/createStep2.bash $DIRBASE/test/cfgTemplateParticleGun/createStep2.bash
cp $DIRBASE/test/cfgTemplate/startStep1.bash $DIRBASE/test/cfgTemplateParticleGun/startStep1.bash
cp $DIRBASE/test/cfgTemplate/startStep2.bash $DIRBASE/test/cfgTemplateParticleGun/startStep2.bash







