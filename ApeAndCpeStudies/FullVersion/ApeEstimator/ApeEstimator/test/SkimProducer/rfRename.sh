#!/bin/sh

# Directory on Castor
#FILEBASE="/castor/cern.ch/cms/store/caf/user/hauk/data/Mu/Run2010A_Dec22ReReco/apeSkim"
#FILEBASE="/castor/cern.ch/cms/store/caf/user/hauk/data/Mu/Run2010B_Dec22ReReco/apeSkim"
FILEBASE="/castor/cern.ch/cms/store/caf/user/hauk/mc/Zmumu/apeSkim"
#FILEBASE="/castor/cern.ch/cms/store/caf/user/hauk/mc/Wmunu/apeSkim"
#FILEBASE="/castor/cern.ch/cms/store/caf/user/hauk/mc/Qcd/apeSkim"

FILESUFFIX=".root"




## increment counter
declare -i counter=1


theInputFilename="rfio:///?svcClass=cmscafuser&path=${FILEBASE}${FILESUFFIX}"
theOutputFilename="rfio:///?svcClass=cmscafuser&path=${FILEBASE}${counter}${FILESUFFIX}"

rfrename ${theInputFilename} ${theOutputFilename}




# number of files to create (maximum value of counter!!!)
while [ $counter -le 9 ]
do
  
  declare -i counterIncrement=${counter}+1
  
  theInputFilename="rfio:///?svcClass=cmscafuser&path=${FILEBASE}00${counter}${FILESUFFIX}"
  theOutputFilename="rfio:///?svcClass=cmscafuser&path=${FILEBASE}${counterIncrement}${FILESUFFIX}"
  
  rfrename ${theInputFilename} ${theOutputFilename}
  
  counter=$counter+1

done



## increment counter after first 10 files
declare -i counterTen=10


while [ $counterTen -le 17 ]
do
  
  declare -i counterTenIncrement=${counterTen}+1
  
  theInputFilename="rfio:///?svcClass=cmscafuser&path=${FILEBASE}0${counterTen}${FILESUFFIX}"
  theOutputFilename="rfio:///?svcClass=cmscafuser&path=${FILEBASE}${counterTenIncrement}${FILESUFFIX}"
  
  rfrename ${theInputFilename} ${theOutputFilename}
  
  counterTen=$counterTen+1

done






