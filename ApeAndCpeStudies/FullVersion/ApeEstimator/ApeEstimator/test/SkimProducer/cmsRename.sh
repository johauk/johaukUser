#!/bin/sh

if [ ! $# == 1 ]; then
  echo "Usage: $0 sample"
  exit 1
fi


sample="$1"

directory=""
if [[ "$sample" == data1 ]] ; then directory="/store/caf/user/hauk/data/DoubleMu/Run2011A_May10ReReco/"
elif [[ "$sample" == data2 ]] ; then directory="/store/caf/user/hauk/data/DoubleMu/Run2011A_PromptV4/"
elif [[ "$sample" == qcd ]] ; then directory="/store/caf/user/hauk/mc/Summer11/qcd/"
elif [[ "$sample" == wlnu ]] ; then directory="/store/caf/user/hauk/mc/Summer11/wlnu/"
elif [[ "$sample" == zmumu10 ]] ; then directory="/store/caf/user/hauk/mc/Summer11/zmumu10/"
elif [[ "$sample" == zmumu20 ]] ; then directory="/store/caf/user/hauk/mc/Summer11/zmumu20/"
else
  echo "Invalid dataset: $sample"
  exit 2
fi

filebase="${directory}apeSkim"

filesuffix=".root"

tempFile="/tmp/hauk/temp.root"
if [ -f $tempFile ] ; then mv $tempFile ${tempFile}.old; fi

## increment counter
declare -i counter=1

inputFilename="${filebase}${filesuffix}"
outputFilename="${filebase}${counter}${filesuffix}"

cmsStageIn $inputFilename $tempFile
if [ ! -f $tempFile ] ; then echo "Last file reached: 0"; exit 0; fi
cmsStageOut $tempFile $outputFilename
if [ $? -eq 0 ] ; then
  cmsRm ${filebase}${filesuffix}
fi
rm $tempFile


while [ $counter -le 9 ]
do
  declare -i counterIncrement=${counter}+1
  
  inputFilename="${filebase}00${counter}${filesuffix}"
  outputFilename="${filebase}${counterIncrement}${filesuffix}"
  
  cmsStageIn $inputFilename $tempFile
  if [ ! -f $tempFile ] ; then echo "Last file reached: ${counter}"; exit 0; fi
  cmsStageOut $tempFile $outputFilename
  if [ $? -eq 0 ] ; then
    cmsRm $inputFilename
  fi
  rm $tempFile
  
  counter=$counter+1
done


## increment counter after first 10 files
declare -i counterTen=10

while [ $counterTen -le 99 ]
do
  declare -i counterTenIncrement=${counterTen}+1
  
  inputFilename="${filebase}0${counterTen}${filesuffix}"
  outputFilename="${filebase}${counterTenIncrement}${filesuffix}"
  
  cmsStageIn $inputFilename $tempFile
  if [ ! -f $tempFile ] ; then echo "Last file reached: ${counterTen}"; exit 0; fi
  cmsStageOut $tempFile $outputFilename
  if [ $? -eq 0 ] ; then
    cmsRm $inputFilename
  fi
  rm $tempFile
  
  counterTen=$counterTen+1
done






