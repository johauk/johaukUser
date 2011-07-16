#!/bin/bash


DIRBASE="$CMSSW_BASE/src/ZmumuAnalysis/Configuration"






## Data


hadd $DIRBASE/hists/data/run2011A_May10ReRecoV1_160404_163869.root $DIRBASE/analysis/data/naf_run2011A_May10ReRecoV1_160404_163869_cfg/*.root
hadd $DIRBASE/hists/data/run2011A_PromptRecoV4_163870_167784.root $DIRBASE/analysis/data/naf_run2011A_PromptRecoV4_163870_167784_cfg/*.root

hadd $DIRBASE/hists/data/allData.root $DIRBASE/hists/data/*.root



sumTriggerReports2.pl $DIRBASE/analysis/data/naf_run2011A_May10ReRecoV1_160404_163869_cfg/out*.txt > $DIRBASE/hists/data/run2011A_May10ReRecoV1_160404_163869.txt
sumTriggerReports2.pl $DIRBASE/analysis/data/naf_run2011A_PromptRecoV4_163870_167784_cfg/out*.txt > $DIRBASE/hists/data/run2011A_PromptRecoV4_163870_167784.txt

sumTriggerReports2.pl $DIRBASE/hists/data/run2011*PromptReco*.txt > $DIRBASE/hists/data/allData.txt





## MC


hadd $DIRBASE/hists/mc/qcd.root $DIRBASE/analysis/mc/naf_qcd_cfg/*.root
hadd $DIRBASE/hists/mc/singletopS.root $DIRBASE/analysis/mc/naf_singletopS_cfg/*.root
hadd $DIRBASE/hists/mc/singletopT.root $DIRBASE/analysis/mc/naf_singletopT_cfg/*.root
hadd $DIRBASE/hists/mc/singletopTw.root $DIRBASE/analysis/mc/naf_singletopTw_cfg/*.root
hadd $DIRBASE/hists/mc/wmunu.root $DIRBASE/analysis/mc/naf_wmunu_cfg/*.root
hadd $DIRBASE/hists/mc/wtaunu.root $DIRBASE/analysis/mc/naf_wtaunu_cfg/*.root
hadd $DIRBASE/hists/mc/ww.root $DIRBASE/analysis/mc/naf_ww_cfg/*.root
hadd $DIRBASE/hists/mc/wz.root $DIRBASE/analysis/mc/naf_wz_cfg/*.root
hadd $DIRBASE/hists/mc/ztautau.root $DIRBASE/analysis/mc/naf_ztautau_cfg/*.root
hadd $DIRBASE/hists/mc/zz.root $DIRBASE/analysis/mc/naf_zz_cfg/*.root
#hadd $DIRBASE/hists/mc/zmumu.root $DIRBASE/analysis/mc/naf_zmumu_cfg/*.root
hadd $DIRBASE/hists/mc/ttbar.root $DIRBASE/analysis/mc/naf_ttbar_cfg/*.root
hadd $DIRBASE/hists/mc/zmumuB.root $DIRBASE/analysis/mc/naf_zmumuB_cfg/*.root
hadd $DIRBASE/hists/mc/zmumuUdsc.root $DIRBASE/analysis/mc/naf_zmumuUdsc_cfg/*.root



sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_qcd_cfg/out*.txt > $DIRBASE/hists/mc/qcd.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_singletopS_cfg/out*.txt > $DIRBASE/hists/mc/singletopS.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_singletopT_cfg/out*.txt > $DIRBASE/hists/mc/singletopT.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_singletopTw_cfg/out*.txt > $DIRBASE/hists/mc/singletopTw.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_wmunu_cfg/out*.txt > $DIRBASE/hists/mc/wmunu.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_wtaunu_cfg/out*.txt > $DIRBASE/hists/mc/wtaunu.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_ww_cfg/out*.txt > $DIRBASE/hists/mc/ww.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_wz_cfg/out*.txt > $DIRBASE/hists/mc/wz.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_ztautau_cfg/out*.txt > $DIRBASE/hists/mc/ztautau.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_zz_cfg/out*.txt > $DIRBASE/hists/mc/zz.txt
#sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_zmumu_cfg/out*.txt > $DIRBASE/hists/mc/zmumu.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_ttbar_cfg/out*.txt > $DIRBASE/hists/mc/ttbar.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_zmumuB_cfg/out*.txt > $DIRBASE/hists/mc/zmumuB.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_zmumuUdsc_cfg/out*.txt > $DIRBASE/hists/mc/zmumuUdsc.txt








