#!/bin/bash

if [ ! $# == 1 ]; then
  echo "Usage: $0 sample"
  exit 1
fi

sample="$1"

directory=""

if [[ "$sample" == data1 ]] ; then directory="/store/caf/user/hauk/data/DoubleMu/Run2011A_May10ReReco/"
elif [[ "$sample" == data2 ]] ; then directory="/store/caf/user/hauk/data/DoubleMu/Run2011A_PromptV4/"
elif [[ "$sample" == qcd ]] ; then directory="/store/caf/user/hauk/mc/Summer11/qcd/"
elif [[ "$sample" == wlnu ]] ; then directory="/store/caf/user/hauk/mc/Summer11/wlnu/"
elif [[ "$sample" == zmumu10 ]] ; then directory="/store/caf/user/hauk/mc/Summer11/zmumu10/"
elif [[ "$sample" == zmumu20 ]] ; then directory="/store/caf/user/hauk/mc/Summer11/zmumu20/"
else
  echo "Invalid dataset: $sample"
  exit 2
fi


ls -l

cd $CMSSW_BASE/src
if [[ "$SHELL" == /bin/sh || "$SHELL" == /bin/bash || "$SHELL" == /bin/zsh ]] ; then
  eval `scram runtime -sh`
elif [[ "$SHELL" == /bin/csh || "$SHELL" == /bin/tcsh ]] ; then
  eval `scram runtime -csh`
else
  echo "Unknown shell: $SHELL"
  echo "cannot set CMSSW environment, stop processing"
  exit 5
fi
cd -

cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/SkimProducer/skimProducer_cfg.py isTest=False sample=$sample

ls -l


for file in *.root;
do
  cmsStageOut $file ${directory}${file}
done








