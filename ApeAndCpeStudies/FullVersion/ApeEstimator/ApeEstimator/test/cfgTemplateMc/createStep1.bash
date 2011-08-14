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
echo "Alignment Record: $alignmentRcd"
echo



## Script to create submit scripts for specific dataset
createStep1="${CMSSW_BASE}/src/ApeEstimator/ApeEstimator/test/cfgTemplate/writeSubmitScript.sh"

## identification name of dataset
#datasetName="ParticleGunMuon"
#datasetName="ParticleGunPion"
#datasetName="data"
export datasetName
## number of input files
export nFiles

datasetName="qcd"
nFiles=3
bash $createStep1 $datasetName $nFiles $iterationNumber $lastIteration $alignmentRcd

datasetName="wlnu"
nFiles=4
bash $createStep1 $datasetName $nFiles $iterationNumber $lastIteration $alignmentRcd

datasetName="zmumu"
nFiles=3
bash $createStep1 $datasetName $nFiles $iterationNumber $lastIteration $alignmentRcd

datasetName="ztautau"
nFiles=1
bash $createStep1 $datasetName $nFiles $iterationNumber $lastIteration $alignmentRcd



