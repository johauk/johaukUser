#!/bin/bash


DIRBASE="$CMSSW_BASE/src/ZmumuAnalysis/Configuration"


#hadd $DIRBASE/hists/simulation/generatorTopZmumu.root $DIRBASE/analysis/simulation/naf_generatorTopZmumu_cfg/*.root
#sumTriggerReports2.pl $DIRBASE/analysis/simulation/naf_generatorTopZmumu_cfg/out*.txt > $DIRBASE/hists/simulation/generatorTopZmumu.txt


#hadd $DIRBASE/hists/simulation/generatorTopZmumu_powheg.root $DIRBASE/analysis/simulation/naf_generatorTopZmumu_powheg_cfg/*.root
#sumTriggerReports2.pl $DIRBASE/analysis/simulation/naf_generatorTopZmumu_powheg_cfg/out*.txt > $DIRBASE/hists/simulation/generatorTopZmumu_powheg.txt




hadd $DIRBASE/hists/simulation/genParticle.root $DIRBASE/analysis/simulation/naf_genParticle_cfg/*.root
sumTriggerReports2.pl $DIRBASE/analysis/simulation/naf_genParticle_cfg/out*.txt > $DIRBASE/hists/simulation/genParticle.txt
