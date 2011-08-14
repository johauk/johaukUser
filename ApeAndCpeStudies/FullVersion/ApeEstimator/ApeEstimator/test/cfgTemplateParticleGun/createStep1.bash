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
export alignmentRcd
alignmentRcd="design"
#alignmentRcd="misalTob20"
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
## Input file base
cafDir="\/castor\/cern.ch\/cms\/store\/caf\/user\/hauk"
export inputBase


datasetName="ParticleGunMuon"
#datasetName="ParticleGunPion"
inputBase="${cafDir}\/mc\/${datasetName}\/RECO\/reco"
nFiles=10
bash $createStep1 $datasetName $nFiles $iterationNumber $lastIteration $alignmentRcd

datasetName="ParticleGunAntiMuon"
#datasetName="ParticleGunAntiPion"
inputBase="${cafDir}\/mc\/${datasetName}\/RECO\/reco"
nFiles=10
bash $createStep1 $datasetName $nFiles $iterationNumber $lastIteration $alignmentRcd


