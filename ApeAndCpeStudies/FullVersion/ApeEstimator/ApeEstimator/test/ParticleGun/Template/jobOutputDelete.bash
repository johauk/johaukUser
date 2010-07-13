#!/bin/bash

# input files to submit to batch queue
INPUTBASE="raw"
INPUTSUFFIX=".root"

# initial seed
declare -i seedBase=0
# increment counter
declare -i counter=1


while [ $counter -le 1000 ]
do
  
  theFilename="${INPUTBASE}${counter}${INPUTSUFFIX}"
  
  rfrm /castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/$theFilename
  
  counter=$counter+1

done
