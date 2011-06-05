#!/bin/bash








#######################################################
## Config for summary step


cp summaryBaseline_cfg.py ../batch/workingArea/summary_cfg.py








#######################################################
## Create final output directory


ROOTFILEBASE="$CMSSW_BASE/src/ApeEstimator/ApeEstimator/hists/workingArea"

mv ${ROOTFILEBASE}/../Design/baseline ${ROOTFILEBASE}/../Design/baseline_old

mkdir ${ROOTFILEBASE}/../Design
mkdir ${ROOTFILEBASE}/../Design/baseline







#######################################################
## Add root files from step1 and delete them, keep only summed file



hadd ${ROOTFILEBASE}/../Design/baseline/allData.root ${ROOTFILEBASE}/*.root

rm ${ROOTFILEBASE}/*.root





