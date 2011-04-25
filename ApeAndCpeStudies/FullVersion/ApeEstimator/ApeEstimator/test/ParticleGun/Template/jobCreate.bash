#!/bin/bash

# input template file to configure
#TEMPLATEFILE="simulation_particleGunPion_jobTemplate_cfg.py"
#TEMPLATEFILE="simulation_particleGunAntiPion_jobTemplate_cfg.py"
TEMPLATEFILE="simulation_particleGunMuon_jobTemplate_cfg.py"
#TEMPLATEFILE="simulation_particleGunAntiMuon_jobTemplate_cfg.py"
# composition of output file name for configured files
#OUTPUTBASE="simulation_particleGunPion_seed"
#OUTPUTBASE="simulation_particleGunAntiPion_seed"
OUTPUTBASE="simulation_particleGunMuon_seed"
#OUTPUTBASE="simulation_particleGunAntiMuon_seed"
OUTPUTSUFFIX="_cfg.py"

# initial seed
declare -i seedBase=0
# increment counter
declare -i counter=1

# number of files to create (maximum value of counter!!!)
while [ $counter -le 1000 ]
do

  theSeed=$((${seedBase}+${counter}))
  theFilename="${OUTPUTBASE}${counter}${OUTPUTSUFFIX}"
  # replace the string _THE_SEED_ in files
  cat $TEMPLATEFILE |sed "s/_THE_SEED_/$theSeed/g" > $theFilename

  counter=$counter+1

done
