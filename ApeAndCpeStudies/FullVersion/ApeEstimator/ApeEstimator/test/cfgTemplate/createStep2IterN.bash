#!/bin/bash


## give number of iteration --- This is the only thing to change...
declare -i nIter=11





#######################################################
## Config for summary step


## input template file to configure
TEMPLATEFILE1="summaryTemplate_cfg.py"
## composition of output file name for configured files
OUTPUTBASE1="workingArea/summary"
OUTPUTSUFFIX="_cfg.py"

theFilename="${OUTPUTBASE1}${OUTPUTSUFFIX}"
cat $TEMPLATEFILE1 |sed "s/_THE_ITERATION_/${nIter}/g" > $theFilename






#######################################################
## Config for creation of APE database object



## input template file to configure
TEMPLATEFILE2="apeLocalSettingTemplate_cfg.py"
## composition of output file name for configured files
OUTPUTBASE2="workingArea/apeLocalSetting"
OUTPUTSUFFIX="_cfg.py"

theFilename="${OUTPUTBASE2}${OUTPUTSUFFIX}"
cat $TEMPLATEFILE2 |sed "s/_THE_ITERATION_/${nIter}/g" > $theFilename







#######################################################
## Add root files from step1 and copy needed iteration file from previous step



ROOTFILEBASE="$CMSSW_BASE/src/ApeEstimator/ApeEstimator/hists/workingArea"


mkdir ${ROOTFILEBASE}/iter${nIter}

## This line does not work for nIter=0, but does not stop the workflow, so does not matter
if [ "$nIter" -ne "0" ]
then
  declare -i nIterDecrement=${nIter}-1
  cp ${ROOTFILEBASE}/iter${nIterDecrement}/allData_iterationApe.root ${ROOTFILEBASE}/iter${nIter}/.
fi


hadd ${ROOTFILEBASE}/iter${nIter}/allData.root ${ROOTFILEBASE}/*.root

rm ${ROOTFILEBASE}/*.root
