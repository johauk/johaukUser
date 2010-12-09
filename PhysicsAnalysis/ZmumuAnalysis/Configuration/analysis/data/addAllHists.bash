#!/bin/bash


DIRBASE="$CMSSW_BASE/src/ZmumuAnalysis/Configuration"


hadd $DIRBASE/hists/data/Run2010A_Sep17ReReco.root $DIRBASE/analysis/data/naf_Run2010A_Sep17ReReco_cfg/*.root
hadd $DIRBASE/hists/data/Run2010B_PromptReco_1.root $DIRBASE/analysis/data/naf_Run2010B_PromptReco_1_cfg/*.root
hadd $DIRBASE/hists/data/Run2010B_PromptReco_2.root $DIRBASE/analysis/data/naf_Run2010B_PromptReco_2_cfg/*.root

hadd $DIRBASE/hists/data/allData.root $DIRBASE/hists/data/*.root




hadd $DIRBASE/hists/mc/inclusiveMu15.root $DIRBASE/analysis/mc/naf_inclusiveMu15_cfg/*.root
hadd $DIRBASE/hists/mc/singleTopS.root $DIRBASE/analysis/mc/naf_singleTopS_cfg/*.root
hadd $DIRBASE/hists/mc/singleTopTW.root $DIRBASE/analysis/mc/naf_singleTopTW_cfg/*.root
hadd $DIRBASE/hists/mc/singleTopT.root $DIRBASE/analysis/mc/naf_singleTopT_cfg/*.root
hadd $DIRBASE/hists/mc/ttbar.root $DIRBASE/analysis/mc/naf_ttbar_cfg/*.root
hadd $DIRBASE/hists/mc/wmunu.root $DIRBASE/analysis/mc/naf_wmunu_cfg/*.root
hadd $DIRBASE/hists/mc/ww.root $DIRBASE/analysis/mc/naf_ww_cfg/*.root
hadd $DIRBASE/hists/mc/wz.root $DIRBASE/analysis/mc/naf_wz_cfg/*.root
hadd $DIRBASE/hists/mc/zmumu.root $DIRBASE/analysis/mc/naf_zmumu_cfg/*.root
hadd $DIRBASE/hists/mc/ztautau.root $DIRBASE/analysis/mc/naf_ztautau_cfg/*.root
hadd $DIRBASE/hists/mc/zz.root $DIRBASE/analysis/mc/naf_zz_cfg/*.root





