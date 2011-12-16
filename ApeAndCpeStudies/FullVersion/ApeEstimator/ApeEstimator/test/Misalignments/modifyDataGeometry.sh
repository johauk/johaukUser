#!/bin/sh

# Modify data geometry
# Recently used is data of stream Prompt_v4, which contains runs 165071-172619, corresponding to IOVs E,F,G,H,I,P1,P2



cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=5 iov=E
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=5 iov=F
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=5 iov=G
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=5 iov=H
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=5 iov=I
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=5 iov=P1
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=5 iov=P2



cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=10 iov=E
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=10 iov=F
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=10 iov=G
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=10 iov=H
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=10 iov=I
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=10 iov=P1
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=10 iov=P2



cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=15 iov=E
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=15 iov=F
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=15 iov=G
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=15 iov=H
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=15 iov=I
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=15 iov=P1
cmsRun $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/alignment_forGeomComp_cfg.py spread=15 iov=P2


rm alignment.log
rm my_treeFile*.root

mkdir $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/output/

#mv my_treeFile*.root $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/output/.
mv pixelTobMisaligned*.db $CMSSW_BASE/src/ApeEstimator/ApeEstimator/test/Misalignments/output/.
