#!/bin/sh

# Directory on Castor
FILEBASE="/castor/cern.ch/cms/store/caf/user/hauk/data/Mu/Run2010B_Dec22ReReco/apeSkim"

FILESUFFIX=".root"




## increment counter
declare -i counter=1


theInputFilename="rfio:///?svcClass=cmscafuser&path=${FILEBASE}${FILESUFFIX}"
theOutputFilename="rfio:///?svcClass=cmscafuser&path=${FILEBASE}${counter}${FILESUFFIX}"

rfrename ${theInputFilename} ${theOutputFilename}




# number of files to create (maximum value of counter!!!)
while [ $counter -le 7 ]
do
  
  declare -i counterIncrement=${counter}+1
  
  theInputFilename="rfio:///?svcClass=cmscafuser&path=${FILEBASE}00${counter}${FILESUFFIX}"
  theOutputFilename="rfio:///?svcClass=cmscafuser&path=${FILEBASE}${counterIncrement}${FILESUFFIX}"
  
  rfrename ${theInputFilename} ${theOutputFilename}
  
  counter=$counter+1

done
