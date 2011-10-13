#!/bin/bash


if [ ! $# == 1 ]; then
  echo "Usage: $0 jobSetup"
  exit 1
fi

jobSetup="$1"


mkdir $jobSetup
mkdir $jobSetup/data
mkdir $jobSetup/mc


cp naf_fullCutflow_cfg_mumu1_${jobSetup}/mumu_run2011A_May10ReRecoV1_160404_163869.* $jobSetup/data/.
cp naf_fullCutflow_cfg_mumu2_${jobSetup}/mumu_run2011A_PromptRecoV4_163870_167784.* $jobSetup/data/.

cp naf_fullCutflow_cfg_ttbar_${jobSetup}/ttbar.* $jobSetup/mc/.
cp naf_fullCutflow_cfg_zmumuB_${jobSetup}/zmumuB.* $jobSetup/mc/.
cp naf_fullCutflow_cfg_zmumuC_${jobSetup}/zmumuC.* $jobSetup/mc/.
cp naf_fullCutflow_cfg_zmumuUds_${jobSetup}/zmumuUds.* $jobSetup/mc/.



hadd $jobSetup/data/allData.root $jobSetup/data/*.root

sumTriggerReports2.pl $jobSetup/data/*.txt > $jobSetup/data/allData.txt



