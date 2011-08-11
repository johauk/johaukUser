## Submit Jobs
# First copy fullCutflow_cfg.py in the directory, then start jobs

# Testing

#nafJobSplitter.pl -c "sample=mumu1 metCut=True secondBtag=" -d test -q 1 -m 100 2 fullCutflow_cfg.py
#nafJobSplitter.pl -c sample=test,metCut=True,secondBtag= -d test -m 100 2 fullCutflow_cfg.py



###===============================================================================================###

TEMPLATEFILE="createCommandsTemplate.bash"


METCUT="False"
fileFalse="false.txt"
cat $TEMPLATEFILE |sed "s/_METCUT_/${METCUT}/g" > $fileFalse

METCUT="True"
fileTrue="true.txt"
cat $TEMPLATEFILE |sed "s/_METCUT_/${METCUT}/g" > $fileTrue

###===============================================================================================###

SYSTEMATICS="default"

fileFalseSystematics="false_systematics.txt"
cat $fileFalse |sed "s/_SYSTEMATICS_/${SYSTEMATICS}/g" > $fileFalseSystematics
bash $fileFalseSystematics > commands_false_${SYSTEMATICS}.txt
rm $fileFalseSystematics

fileTrueSystematics="true_systematics.txt"
cat $fileTrue |sed "s/_SYSTEMATICS_/${SYSTEMATICS}/g" > $fileTrueSystematics
bash $fileTrueSystematics > commands_true_${SYSTEMATICS}.txt
rm $fileTrueSystematics




###===============================================================================================###

SYSTEMATICS="pileup14"

fileFalseSystematics="false_systematics.txt"
cat $fileFalse |sed "s/_SYSTEMATICS_/${SYSTEMATICS}/g" > $fileFalseSystematics
bash $fileFalseSystematics > commands_false_${SYSTEMATICS}.txt
rm $fileFalseSystematics

fileTrueSystematics="true_systematics.txt"
cat $fileTrue |sed "s/_SYSTEMATICS_/${SYSTEMATICS}/g" > $fileTrueSystematics
bash $fileTrueSystematics > commands_true_${SYSTEMATICS}.txt
rm $fileTrueSystematics


###===============================================================================================###

SYSTEMATICS="pileup57"

fileFalseSystematics="false_systematics.txt"
cat $fileFalse |sed "s/_SYSTEMATICS_/${SYSTEMATICS}/g" > $fileFalseSystematics
bash $fileFalseSystematics > commands_false_${SYSTEMATICS}.txt
rm $fileFalseSystematics

fileTrueSystematics="true_systematics.txt"
cat $fileTrue |sed "s/_SYSTEMATICS_/${SYSTEMATICS}/g" > $fileTrueSystematics
bash $fileTrueSystematics > commands_true_${SYSTEMATICS}.txt
rm $fileTrueSystematics


###===============================================================================================###

SYSTEMATICS="pileup8plus"

fileFalseSystematics="false_systematics.txt"
cat $fileFalse |sed "s/_SYSTEMATICS_/${SYSTEMATICS}/g" > $fileFalseSystematics
bash $fileFalseSystematics > commands_false_${SYSTEMATICS}.txt
rm $fileFalseSystematics

fileTrueSystematics="true_systematics.txt"
cat $fileTrue |sed "s/_SYSTEMATICS_/${SYSTEMATICS}/g" > $fileTrueSystematics
bash $fileTrueSystematics > commands_true_${SYSTEMATICS}.txt
rm $fileTrueSystematics


###===============================================================================================###

SYSTEMATICS="sideband140"

fileFalseSystematics="false_systematics.txt"
cat $fileFalse |sed "s/_SYSTEMATICS_/${SYSTEMATICS}/g" > $fileFalseSystematics
bash $fileFalseSystematics > commands_false_${SYSTEMATICS}.txt
rm $fileFalseSystematics

fileTrueSystematics="true_systematics.txt"
cat $fileTrue |sed "s/_SYSTEMATICS_/${SYSTEMATICS}/g" > $fileTrueSystematics
bash $fileTrueSystematics > commands_true_${SYSTEMATICS}.txt
rm $fileTrueSystematics


###===============================================================================================###

SYSTEMATICS="sideband160"

fileFalseSystematics="false_systematics.txt"
cat $fileFalse |sed "s/_SYSTEMATICS_/${SYSTEMATICS}/g" > $fileFalseSystematics
bash $fileFalseSystematics > commands_false_${SYSTEMATICS}.txt
rm $fileFalseSystematics

fileTrueSystematics="true_systematics.txt"
cat $fileTrue |sed "s/_SYSTEMATICS_/${SYSTEMATICS}/g" > $fileTrueSystematics
bash $fileTrueSystematics > commands_true_${SYSTEMATICS}.txt
rm $fileTrueSystematics


###===============================================================================================###

SYSTEMATICS="sideband200"

fileFalseSystematics="false_systematics.txt"
cat $fileFalse |sed "s/_SYSTEMATICS_/${SYSTEMATICS}/g" > $fileFalseSystematics
bash $fileFalseSystematics > commands_false_${SYSTEMATICS}.txt
rm $fileFalseSystematics

fileTrueSystematics="true_systematics.txt"
cat $fileTrue |sed "s/_SYSTEMATICS_/${SYSTEMATICS}/g" > $fileTrueSystematics
bash $fileTrueSystematics > commands_true_${SYSTEMATICS}.txt
rm $fileTrueSystematics





rm $fileFalse
rm $fileTrue
