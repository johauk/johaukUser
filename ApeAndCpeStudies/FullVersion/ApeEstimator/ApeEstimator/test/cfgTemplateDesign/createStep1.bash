#!/bin/bash



if [ ! $# -ge 1 ]; then
  echo "Usage: $0 iterationNumber"
  echo "Usage: $0 iterationNumber lastIteration"
  exit 1
fi

export iterationNumber="$1"
export lastIteration="False"
if [ $# == 2 ]; then
  lastIteration="$2";
  if [[ ! "$lastIteration" == False ]] && [[ ! "$lastIteration" == True ]] ; then
    echo "Invalid argument for lastIteration: $lastIteration"
    exit 2
  fi
fi

echo "Iteration number: $1"
echo "LastIteration: ${lastIteration}"
echo





## Alignment
export alignmentRcd="design"
#export alignmentRcd="idealAligned"
echo "Alignment Record: $alignmentRcd"
echo



## Script to create submit scripts for specific dataset
createStep1="${CMSSW_BASE}/src/ApeEstimator/ApeEstimator/test/cfgTemplate/writeSubmitScript.sh"

## identification name of dataset
export datasetName
## number of input files
export nFiles
## Input file base
cafDir="\/store\/caf\/user\/hauk"
export inputBase


datasetName="qcd"
inputBase="${cafDir}\/mc\/Summer11\/${datasetName}\/apeSkim"
nFiles=1
bash $createStep1 $datasetName $nFiles $iterationNumber $lastIteration $alignmentRcd $inputBase


datasetName="wlnu"
inputBase="${cafDir}\/mc\/Summer11\/${datasetName}\/apeSkim"
nFiles=15
bash $createStep1 $datasetName $nFiles $iterationNumber $lastIteration $alignmentRcd $inputBase


datasetName="zmumu10"
inputBase="${cafDir}\/mc\/Summer11\/${datasetName}\/apeSkim"
nFiles=1
bash $createStep1 $datasetName $nFiles $iterationNumber $lastIteration $alignmentRcd $inputBase


datasetName="zmumu20"
inputBase="${cafDir}\/mc\/Summer11\/${datasetName}\/apeSkim"
nFiles=21
bash $createStep1 $datasetName $nFiles $iterationNumber $lastIteration $alignmentRcd $inputBase



