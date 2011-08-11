## Submit Jobs
# First copy fullCutflow_cfg.py in the directory, then start jobs

# Testing

#nafJobSplitter.pl -c "sample=mumu1 metCut=True secondBtag=" -d test -q 1 -m 100 2 fullCutflow_cfg.py
#nafJobSplitter.pl -c sample=test,metCut=True,secondBtag= -d test -m 100 2 fullCutflow_cfg.py


Systematics="_SYSTEMATICS_"
MetCut="_METCUT_"

###===============================================================================================###

FirstBtag="HeM"
SecondBtag=""

Sample="mumu1"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="mumu2"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py

Sample="elel1"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="elel2"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py

Sample="qcd"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="singletopS"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="singletopT"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="singletopTw"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="wmunu"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="wtaunu"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="ww"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="wz"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="zz"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="ztautau"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="ttbar"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="zmumuB"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="zmumuUdsc"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py

echo
echo
echo

Sample="mumu1"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="mumu2"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}

Sample="elel1"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="elel2"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}

Sample="qcd"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="singletopS"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="singletopT"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="singletopTw"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="wmunu"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="wtaunu"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="ww"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="wz"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="zz"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="ztautau"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="ttbar"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="zmumuB"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="zmumuUdsc"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}

echo
echo
echo



###===============================================================================================###

FirstBtag="HpT"
SecondBtag="HeM"

Sample="mumu1"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="mumu2"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py

Sample="elel1"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="elel2"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py

Sample="qcd"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="singletopS"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="singletopT"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="singletopTw"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="wmunu"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="wtaunu"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="ww"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="wz"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="zz"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="ztautau"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="ttbar"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="zmumuB"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="zmumuUdsc"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py

echo
echo
echo

Sample="mumu1"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="mumu2"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}

Sample="elel1"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="elel2"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}

Sample="qcd"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="singletopS"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="singletopT"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="singletopTw"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="wmunu"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="wtaunu"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="ww"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="wz"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="zz"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="ztautau"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="ttbar"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="zmumuB"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="zmumuUdsc"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}

echo
echo
echo



###===============================================================================================###

FirstBtag="HeMExcl"
SecondBtag=""

Sample="mumu1"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="mumu2"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py

Sample="elel1"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="elel2"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py

Sample="qcd"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="singletopS"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="singletopT"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="singletopTw"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="wmunu"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="wtaunu"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="ww"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="wz"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="zz"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="ztautau"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="ttbar"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="zmumuB"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="zmumuUdsc"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py

echo
echo
echo

Sample="mumu1"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="mumu2"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}

Sample="elel1"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="elel2"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}

Sample="qcd"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="singletopS"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="singletopT"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="singletopTw"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="wmunu"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="wtaunu"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="ww"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="wz"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="zz"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="ztautau"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="ttbar"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="zmumuB"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="zmumuUdsc"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}

echo
echo
echo



###===============================================================================================###

FirstBtag="HpTExcl"
SecondBtag=""

Sample="mumu1"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="mumu2"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py

Sample="elel1"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="elel2"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py

Sample="qcd"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="singletopS"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="singletopT"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="singletopTw"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="wmunu"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="wtaunu"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="ww"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="wz"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="zz"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="ztautau"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="ttbar"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="zmumuB"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py
Sample="zmumuUdsc"
echo nafJobSplitter.pl -c \"sample=${Sample} metCut=${MetCut} firstBtag=${FirstBtag} secondBtag=${SecondBtag} systematics=${Systematics}\" -d ${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics} 10 fullCutflow_cfg.py

echo
echo
echo

Sample="mumu1"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="mumu2"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}

Sample="elel1"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="elel2"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}

Sample="qcd"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="singletopS"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="singletopT"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="singletopTw"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="wmunu"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="wtaunu"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="ww"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="wz"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="zz"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="ztautau"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="ttbar"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="zmumuB"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}
Sample="zmumuUdsc"
echo nafJobSplitter.pl check naf_fullCutflow_cfg_${Sample}_${MetCut}_${FirstBtag}_${SecondBtag}_${Systematics}

echo
echo
echo



