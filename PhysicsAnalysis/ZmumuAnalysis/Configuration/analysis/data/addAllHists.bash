#!/bin/bash


DIRBASE="$CMSSW_BASE/src/ZmumuAnalysis/Configuration"


hadd $DIRBASE/hists/data/run2010A_Nov04ReReco.root $DIRBASE/analysis/data/naf_run2010A_Nov04ReReco_cfg/*.root
hadd $DIRBASE/hists/data/run2010B_Nov04ReReco_1.root $DIRBASE/analysis/data/naf_run2010B_Nov04ReReco_1_cfg/*.root
hadd $DIRBASE/hists/data/run2010B_Nov04ReReco_2.root $DIRBASE/analysis/data/naf_run2010B_Nov04ReReco_2_cfg/*.root

hadd $DIRBASE/hists/data/allData.root $DIRBASE/hists/data/*.root




hadd $DIRBASE/hists/mc/qcd.root $DIRBASE/analysis/mc/naf_qcd_cfg/*.root
hadd $DIRBASE/hists/mc/singleTop.root $DIRBASE/analysis/mc/naf_singleTop_cfg/*.root
hadd $DIRBASE/hists/mc/ttbar.root $DIRBASE/analysis/mc/naf_ttbar_cfg/*.root
hadd $DIRBASE/hists/mc/wmunu.root $DIRBASE/analysis/mc/naf_wmunu_cfg/*.root
hadd $DIRBASE/hists/mc/wtaunu.root $DIRBASE/analysis/mc/naf_wtaunu_cfg/*.root
hadd $DIRBASE/hists/mc/ww.root $DIRBASE/analysis/mc/naf_ww_cfg/*.root
hadd $DIRBASE/hists/mc/wz.root $DIRBASE/analysis/mc/naf_wz_cfg/*.root
hadd $DIRBASE/hists/mc/zmumu.root $DIRBASE/analysis/mc/naf_zmumu_cfg/*.root
hadd $DIRBASE/hists/mc/ztautau.root $DIRBASE/analysis/mc/naf_ztautau_cfg/*.root
hadd $DIRBASE/hists/mc/zz.root $DIRBASE/analysis/mc/naf_zz_cfg/*.root






sumTriggerReports2.pl $DIRBASE/analysis/data/naf_run2010A_Nov04ReReco_cfg/out*.txt > $DIRBASE/hists/data/run2010A_Nov04ReReco.txt
sumTriggerReports2.pl $DIRBASE/analysis/data/naf_run2010B_Nov04ReReco_1_cfg/out*.txt > $DIRBASE/hists/data/run2010B_Nov04ReReco_1.txt
sumTriggerReports2.pl $DIRBASE/analysis/data/naf_run2010B_Nov04ReReco_2_cfg/out*.txt > $DIRBASE/hists/data/run2010B_Nov04ReReco_2.txt

sumTriggerReports2.pl $DIRBASE/hists/data/run2010*_Nov04ReReco*.txt > $DIRBASE/hists/data/allData.txt




sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_qcd_cfg/out*.txt > $DIRBASE/hists/mc/qcd.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_singleTop_cfg/out*.txt > $DIRBASE/hists/mc/singleTop.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_ttbar_cfg/out*.txt > $DIRBASE/hists/mc/ttbar.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_wmunu_cfg/out*.txt > $DIRBASE/hists/mc/wmunu.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_wtaunu_cfg/out*.txt > $DIRBASE/hists/mc/wtaunu.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_ww_cfg/out*.txt > $DIRBASE/hists/mc/ww.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_wz_cfg/out*.txt > $DIRBASE/hists/mc/wz.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_zmumu_cfg/out*.txt > $DIRBASE/hists/mc/zmumu.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_ztautau_cfg/out*.txt > $DIRBASE/hists/mc/ztautau.txt
sumTriggerReports2.pl $DIRBASE/analysis/mc/naf_zz_cfg/out*.txt > $DIRBASE/hists/mc/zz.txt














