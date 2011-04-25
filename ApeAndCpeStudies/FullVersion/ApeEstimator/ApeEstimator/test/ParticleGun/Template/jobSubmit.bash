#!/bin/bash

# input files to submit to batch queue
#INPUTBASE="simulation_particleGunPion_seed"
#INPUTBASE="simulation_particleGunAntiPion_seed"
INPUTBASE="simulation_particleGunMuon_seed"
#INPUTBASE="simulation_particleGunAntiMuon_seed"
INPUTSUFFIX="_cfg.py"

# initial seed
declare -i seedBase=0
# increment counter
declare -i counter=501

export PYTHONHOME=/afs/cern.ch/cms/sw/slc5_ia32_gcc434/external/python/2.6.4-cms



while [ $counter -le 1000 ]
do
  
  theFilename="${INPUTBASE}${counter}${INPUTSUFFIX}"
  
  #echo $theFilename
  bsub -J file${counter} -q 2nd cmsRun /afs/cern.ch/user/h/hauk/cms/CMSSW_3_6_1_patch4/src/ApeEstimator/ApeEstimator/test/ParticleGun/Template/$theFilename
  
  counter=$counter+1

done
