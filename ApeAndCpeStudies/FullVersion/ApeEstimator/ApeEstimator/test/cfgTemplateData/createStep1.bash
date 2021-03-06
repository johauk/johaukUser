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
#export alignmentRcd="globalTag"
export alignmentRcd="GR10_v6"
#export alignmentRcd="GR10_v6_plus5"
#export alignmentRcd="GR10_v6_plus10"
#export alignmentRcd="GR10_v6_plus15"
#export alignmentRcd="GR10_v6_plus20"
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


#datasetName="data1"
#inputBase="${cafDir}\/data\/DoubleMu\/Run2011A_May10ReReco\/apeSkim"
#nFiles=3
#bash $createStep1 $datasetName $nFiles $iterationNumber $lastIteration $alignmentRcd $inputBase


datasetName="data2"
inputBase="${cafDir}\/data\/DoubleMu\/Run2011A_PromptV4\/apeSkim"
nFiles=10
bash $createStep1 $datasetName $nFiles $iterationNumber $lastIteration $alignmentRcd $inputBase



