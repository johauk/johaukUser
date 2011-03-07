#!/bin/bash



## identification name of dataset --- This is the only thing to change for different datasets
DATASETNAME1="antiPion"
## input template file to configure
TEMPLATEFILE="cfgTemplateFullOverview_cfg.py"
## composition of output file name for configured files
OUTPUTDIR="../batch/workingArea/"
OUTPUTBASE1="${OUTPUTDIR}${DATASETNAME1}_"
OUTPUTSUFFIX="_cfg.py"



## number of events
declare -i maxevent=-1



## alignment connect string and tag of record (use escape characters for /)
alignmentRcdConnect="frontier:\/\/FrontierProd\/CMS_COND_31X_FROM21X"
#alignmentRcdConnect="sqlite_file:\/afs\/cern.ch\/user\/h\/hauk\/scratch0\/apeStudies\/misalignments\/AlignmentsTob20.db"
alignmentRcd="TrackerIdealGeometry210_mc"
#alignmentRcd="TrackerScenario"

## APE connect string and tag of record (use escape characters for /)
alignmentErrorRcdConnect="frontier:\/\/FrontierProd\/CMS_COND_31X_FROM21X"
#nIter=$nIter-1
#alignmentErrorRcdConnect="sqlite_file:\/afs\/cern.ch\/user\/h\/hauk\/scratch0\/apeStudies\/apeObjects\/apeIter${nIter}.db"
alignmentErrorRcd="TrackerIdealGeometryErrors210_mc"
#alignmentErrorRcd="AlignmentErrors"



helpFile1="help1.txt"
cat $TEMPLATEFILE |sed "s/_THE_MAXEVENT_/${maxevent}/g" > $helpFile1
helpFile2="help2.txt"
cat $helpFile1 |sed "s/_THE_ALIGNMENT_RCD_CONNECT_/${alignmentRcdConnect}/g" > $helpFile2
helpFile3="help3.txt"
cat $helpFile2 |sed "s/_THE_ALIGNMENT_RCD_/${alignmentRcd}/g" > $helpFile3
helpFile4="help4.txt"
cat $helpFile3 |sed "s/_THE_ALIGNMENT_ERROR_RCD_CONNECT_/${alignmentErrorRcdConnect}/g" > $helpFile4
helpFile5="help5.txt"
cat $helpFile4 |sed "s/_THE_ALIGNMENT_ERROR_RCD_/${alignmentErrorRcd}/g" > $helpFile5
helpFile6="help6.txt"
cat $helpFile5 |sed "s/_THE_NAME_/${DATASETNAME1}/g" > $helpFile6





## Same for batch file

BATCH_TEMPLATEFILE1="${DATASETNAME1}BatchSubmitTemplate.bash"
BATCH_OUTPUTBASE1="../batch/workingArea/${DATASETNAME1}BatchSubmit"
BATCH_OUTPUTSUFFIX=".bash"



helpFileB1="helpB1.txt"
cat $BATCH_TEMPLATEFILE1 |sed "s/_THE_NAME_/${DATASETNAME1}/g" > $helpFileB1





## increment counter
declare -i counter1=1

## number of files to create (maximum value of counter!!!)
while [ $counter1 -le 10 ]
do

  theFilename="${OUTPUTBASE1}${counter1}${OUTPUTSUFFIX}"
  cat $helpFile6 |sed "s/_THE_NUMBER_/${counter1}/g" > $theFilename
  
  
  theBatchFilename="${BATCH_OUTPUTBASE1}${counter1}${BATCH_OUTPUTSUFFIX}"
  cat $helpFileB1 |sed "s/_THE_NUMBER_/${counter1}/g" > $theBatchFilename
  
  
  counter1=$counter1+1

done

rm $helpFile1
rm $helpFile2
rm $helpFile3
rm $helpFile4
rm $helpFile5
rm $helpFile6
rm $helpFileB1








####################################################################

## Now the same for pions



## identification name of dataset --- This is the only thing to change for different datasets
DATASETNAME2="pion"
## composition of output file name for configured files
OUTPUTBASE2="${OUTPUTDIR}${DATASETNAME2}_"



helpFile1="help1.txt"
cat $TEMPLATEFILE |sed "s/_THE_MAXEVENT_/${maxevent}/g" > $helpFile1
helpFile2="help2.txt"
cat $helpFile1 |sed "s/_THE_ALIGNMENT_RCD_CONNECT_/${alignmentRcdConnect}/g" > $helpFile2
helpFile3="help3.txt"
cat $helpFile2 |sed "s/_THE_ALIGNMENT_RCD_/${alignmentRcd}/g" > $helpFile3
helpFile4="help4.txt"
cat $helpFile3 |sed "s/_THE_ALIGNMENT_ERROR_RCD_CONNECT_/${alignmentErrorRcdConnect}/g" > $helpFile4
helpFile5="help5.txt"
cat $helpFile4 |sed "s/_THE_ALIGNMENT_ERROR_RCD_/${alignmentErrorRcd}/g" > $helpFile5
helpFile6="help6.txt"
cat $helpFile5 |sed "s/_THE_NAME_/${DATASETNAME2}/g" > $helpFile6





## Same for batch file

BATCH_TEMPLATEFILE2="${DATASETNAME2}BatchSubmitTemplate.bash"
BATCH_OUTPUTBASE2="../batch/workingArea/${DATASETNAME2}BatchSubmit"



helpFileB1="helpB1.txt"
cat $BATCH_TEMPLATEFILE2 |sed "s/_THE_NAME_/${DATASETNAME2}/g" > $helpFileB1





## increment counter
declare -i counter2=1

## number of files to create (maximum value of counter!!!)
while [ $counter2 -le 10 ]
do

  theFilename="${OUTPUTBASE2}${counter2}${OUTPUTSUFFIX}"
  cat $helpFile6 |sed "s/_THE_NUMBER_/${counter2}/g" > $theFilename
  
  
  theBatchFilename="${BATCH_OUTPUTBASE2}${counter2}${BATCH_OUTPUTSUFFIX}"
  cat $helpFileB1 |sed "s/_THE_NUMBER_/${counter2}/g" > $theBatchFilename
  
  
  counter2=$counter2+1

done

rm $helpFile1
rm $helpFile2
rm $helpFile3
rm $helpFile4
rm $helpFile5
rm $helpFile6
rm $helpFileB1


