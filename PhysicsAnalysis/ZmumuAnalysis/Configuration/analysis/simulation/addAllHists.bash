#!/bin/bash


DIRBASE="$CMSSW_BASE/src/ZmumuAnalysis/Configuration"


hadd $DIRBASE/hists/simulation/generatorTopZmumu.root $DIRBASE/analysis/simulation/naf_generatorTopZmumu_cfg/*.root
sumTriggerReports2.pl $DIRBASE/analysis/simulation/naf_generatorTopZmumu_cfg/out*.txt > $DIRBASE/hists/simulation/generatorTopZmumu.txt


