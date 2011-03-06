#!/bin/bash








#######################################################
## Config for summary step


cp summaryBaseline_cfg.py ../batch/workingArea/summary_cfg.py








#######################################################
## Create final output directory


ROOTFILEBASE="$CMSSW_BASE/src/ApeEstimator/ApeEstimator/hists/workingArea"

mkdir ${ROOTFILEBASE}/../Design
mkdir ${ROOTFILEBASE}/../Design/baseline







#######################################################
## Add root files from step1 and delete them, kepp only summed file



hadd ${ROOTFILEBASE}/../Design/baseline/allData.root ${ROOTFILEBASE}/*.root

rm ${ROOTFILEBASE}/*.root





