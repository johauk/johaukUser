#!/bin/bash

## input template file to configure  --- Use full overview again
TEMPLATEFILE1="antiPionTemplateFullOverview_cfg.py"
## composition of output file name for configured files
OUTPUTBASE1="workingArea/antiPion_"
OUTPUTSUFFIX="_cfg.py"



## number of events
declare -i maxevent=-1



## give number of iteration --- This is the only thing to change...
declare -i nIter=11






## alignment connect string and tag of record (use escape characters for /)
#alignmentRcdConnect="frontier:\/\/FrontierProd\/CMS_COND_31X_FROM21X"
alignmentRcdConnect="sqlite_file:\/afs\/cern.ch\/user\/h\/hauk\/scratch0\/apeStudies\/misalignments\/AlignmentsTob20.db"
#alignmentRcd="TrackerIdealGeometry210_mc"
alignmentRcd="TrackerScenario"

## APE connect string and tag of record (use escape characters for /)
#alignmentErrorRcdConnect="frontier:\/\/FrontierProd\/CMS_COND_31X_FROM21X"
nIter=$nIter-1
alignmentErrorRcdConnect="sqlite_file:\/afs\/cern.ch\/user\/h\/hauk\/scratch0\/apeStudies\/apeObjects\/apeIter${nIter}.db"
#alignmentErrorRcd="TrackerIdealGeometryErrors210_mc"
alignmentErrorRcd="AlignmentErrors"






helpFile1="help1.txt"
cat $TEMPLATEFILE1 |sed "s/_THE_MAXEVENT_/${maxevent}/g" > $helpFile1
helpFile2="help2.txt"
cat $helpFile1 |sed "s/_THE_ALIGNMENT_RCD_CONNECT_/${alignmentRcdConnect}/g" > $helpFile2
helpFile3="help3.txt"
cat $helpFile2 |sed "s/_THE_ALIGNMENT_RCD_/${alignmentRcd}/g" > $helpFile3
helpFile4="help4.txt"
cat $helpFile3 |sed "s/_THE_ALIGNMENT_ERROR_RCD_CONNECT_/${alignmentErrorRcdConnect}/g" > $helpFile4
helpFile5="help5.txt"
cat $helpFile4 |sed "s/_THE_ALIGNMENT_ERROR_RCD_/${alignmentErrorRcd}/g" > $helpFile5




## Same for batch file
BATCH_TEMPLATEFILE1="batchSubmitAntiPionTemplate.bash"
BATCH_OUTPUTBASE1="../batch/workingArea/batchSubmitAntiPion"
BATCH_OUTPUTSUFFIX=".bash"








## increment counter
declare -i counter=1

# number of files to create (maximum value of counter!!!)
while [ $counter -le 10 ]
do

  theFilename="${OUTPUTBASE1}${counter}${OUTPUTSUFFIX}"
  #cat $TEMPLATEFILE |sed "s/_THE_MAXEVENT_/${maxevent}/g" > $helpFile1
  cat $helpFile5 |sed "s/_THE_NUMBER_/${counter}/g" > $theFilename
  
  
  theBatchFilename="${BATCH_OUTPUTBASE1}${counter}${BATCH_OUTPUTSUFFIX}"
  cat $BATCH_TEMPLATEFILE1 |sed "s/_THE_NUMBER_/${counter}/g" > $theBatchFilename
  
  
  counter=$counter+1

done

rm $helpFile1
rm $helpFile2
rm $helpFile3
rm $helpFile4
rm $helpFile5



####################################################################

## Now the same for pions

## input template file to configure
TEMPLATEFILE2="pionTemplateFullOverview_cfg.py"
## composition of output file name for configured files
OUTPUTBASE2="workingArea/pion_"






helpFile1="help1.txt"
cat $TEMPLATEFILE2 |sed "s/_THE_MAXEVENT_/${maxevent}/g" > $helpFile1
helpFile2="help2.txt"
cat $helpFile1 |sed "s/_THE_ALIGNMENT_RCD_CONNECT_/${alignmentRcdConnect}/g" > $helpFile2
helpFile3="help3.txt"
cat $helpFile2 |sed "s/_THE_ALIGNMENT_RCD_/${alignmentRcd}/g" > $helpFile3
helpFile4="help4.txt"
cat $helpFile3 |sed "s/_THE_ALIGNMENT_ERROR_RCD_CONNECT_/${alignmentErrorRcdConnect}/g" > $helpFile4
helpFile5="help5.txt"
cat $helpFile4 |sed "s/_THE_ALIGNMENT_ERROR_RCD_/${alignmentErrorRcd}/g" > $helpFile5




## Same for batch file
BATCH_TEMPLATEFILE2="batchSubmitPionTemplate.bash"
BATCH_OUTPUTBASE2="../batch/workingArea/batchSubmitPion"






# increment counter
declare -i counter2=1

# number of files to create (maximum value of counter!!!)
while [ $counter2 -le 10 ]
do

  theFilename="${OUTPUTBASE2}${counter2}${OUTPUTSUFFIX}"
  cat $helpFile5 |sed "s/_THE_NUMBER_/${counter2}/g" > $theFilename
  
  
  theBatchFilename="${BATCH_OUTPUTBASE2}${counter2}${BATCH_OUTPUTSUFFIX}"
  cat $BATCH_TEMPLATEFILE2 |sed "s/_THE_NUMBER_/${counter2}/g" > $theBatchFilename
  
  
  counter2=$counter2+1

done

rm $helpFile1
rm $helpFile2
rm $helpFile3
rm $helpFile4
rm $helpFile5

