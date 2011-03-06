#!/bin/bash


# input files to submit to batch queue (comment out next line to avoid unwanted deletion)
#INPUTBASE="raw"
INPUTBASE="reco"
INPUTSUFFIX=".root"


# increment counter
declare -i counter=100


while [ $counter -le 823 ]
do
  
  theFilename="${INPUTBASE}${counter}${INPUTSUFFIX}"
  
  #rfrm /castor/cern.ch/cms/store/caf/user/hauk/mc/ParticleGunPion/RAW/$theFilename
  rfrm /castor/cern.ch/cms/store/caf/user/hauk/data/Mu/Run2010A_Dec22ReReco/$theFilename
  
  counter=$counter+1

done
