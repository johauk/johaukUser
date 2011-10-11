samples = [
    ['mumu1', 10],
    ['mumu2', 30],
    #['elel1', 10],
    #['elel2', 30],
    ['ttbar', 20],
    ['zmumuB', 40],
    ['zmumuC', 40],
    ['zmumuUds', 40],
    #['zmumuUdsc', 40],
    ]


metcuts = [
  'False',
  #'True',
  ]


btags = [
  ['HeM', ''],
  ['HpT', 'HeM'],
  #['HeMExcl', ''],
  #['HpTExcl', ''],
  ]


systematics = [
  'default',
  'pileup14',
  'pileup57',
  'pileup8plus',
  #'sideband140',
  #'sideband160',
  #'sideband200',
  ]




output =open("info.txt","w")


for systematic in systematics:
  for metcut in metcuts:
    for btag in btags:
      for sample in samples:
        output.write("nafJobSplitter.pl -c \"sample="+sample[0]+" metCut="+metcut+" firstBtag="+btag[0]+" secondBtag="+btag[1]+" systematics="+systematic+"\" -d "+sample[0]+"_"+metcut+"_"+btag[0]+"_"+btag[1]+"_"+systematic+" "+str(sample[1])+" fullCutflow_cfg.py\n")
      output.write("\n")
    output.write("\n")
  output.write("\n")


output.write("\n\n\n=============================================================================================================================================\n\n\n\n")


for systematic in systematics:
  for metcut in metcuts:
    for btag in btags:
      for sample in samples:
        output.write("nafJobSplitter.pl check naf_fullCutflow_cfg_"+sample[0]+"_"+metcut+"_"+btag[0]+"_"+btag[1]+"_"+systematic+"\n")
      output.write("\n")
    output.write("\n")
  output.write("\n")

output.close()




