#!/bin/zsh
#
#(make sure the right shell will be used)
#$ -S /bin/zsh
#
#(the cpu time for this job)
#$ -l h_cpu=48:00:00
#
#(the maximum memory usage of this job)
#$ -l h_vmem=2000M
#
#(stderr and stdout are merged together to stdout)
#$ -j y
#
#$ -cwd
#$ -V
#(send mail on job's end and abort)
#$ -m ae

# change to scratch directory (local, not lustre in this example)
#cd $TMPDIR
# copy raw data to scratch directory (here from the afs)
# DO NOT USE afscp UNTIL FURTHER NOTICE afscp /afs/naf.desy.de/group/vo/rawdata/bigfile bigfile
#cp /afs/naf.desy.de/group/vo/rawdata/bigfile bigfile
# write calculated output also to scratch first
#/path/to/executable/which/works/on/bigfile -in bigfile -out output
# copy the output back into afs
# DO NOT USE afscp UNTIL FURTHER NOTICE afscp output /afs/naf.desy.de/group/vo/output/
#cp output /afs/naf.desy.de/group/vo/output/


#cd $WORKAREA
#ini cmssw
#cmsenv
cmsRun /afs/naf.desy.de/user/j/johauk/cms/CMSSW_3_6_1_patch4/src/ZmumuAnalysis/Configuration/analysis/data/ichepAnalysis_PromptReco_cfg.py
