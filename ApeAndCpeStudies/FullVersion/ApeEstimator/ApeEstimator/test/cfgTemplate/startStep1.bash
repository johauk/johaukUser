#!/bin/bash

## Do this from directory test/cfgTemplate/workingArea/

declare -i counter=1

for file in $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/batch/workingArea/*.bash;

do

  bsub -J job${counter} -q cmscaf1nd -R "rusage[pool=3000]" bash $file
  
  counter=$counter+1
  
done

