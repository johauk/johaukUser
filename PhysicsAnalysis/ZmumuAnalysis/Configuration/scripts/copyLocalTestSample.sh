#!/bin/sh


# Needs to execute before: >  voms-proxy-init




#srmcp -2 -streams_num=1 "srm://dcache-se-cms.desy.de:8443//pnfs/desy.de/cms/tier2/store/user/dammann/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Fall10-PAT-v2/43e23e1dee19d970b0c8344e9053309f/mcpat_1_1_eXu.root" "file:////scratch/hh/current/cms/user/hauk/data/testPatTuple/mcpat_1_1_eXu_madgraph_D6T.root"

#srmcp -2 -streams_num=1 "srm://dcache-se-cms.desy.de:8443//pnfs/desy.de/cms/tier2/store/user/wbehrenh/ZbbToLL_M-40_PtB1-15_TuneZ2_7TeV-madgraph-pythia6/Fall10_PAT/43e23e1dee19d970b0c8344e9053309f/mcpat_1_3_bfP.root" "file:////scratch/hh/current/cms/user/hauk/data/testPatTuple/mcpat_1_3_bfP_madgraph_Z2.root"



# Change from srm to dc tools, needs: >  ini dctools


#srmcp -2 -streams_num=1 "srm://dcache-se-cms.desy.de:8443//pnfs/desy.de/cms/tier2/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_12_1_wii.root" "file:////scratch/hh/current/cms/user/hauk/data/testPatTupleData/datapat_12_1_wii_Run2011A_PromptReco_v1.root"
#dcls /pnfs/desy.de/cms/tier2/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/
#dcget /pnfs/desy.de/cms/tier2/store/user/blutz/DoubleMu/Run2011A_PromtReco_v1_413p2_mumu_PAT_May7_160404_163757/59e0dd4866f9c31fab6116dc9c2518db/datapat_12_1_wii.root /scratch/hh/current/cms/user/hauk/data/testPatTupleData/datapat_12_1_wii_Run2011A_PromptReco_v1.root

dcget /pnfs/desy.de/cms/tier2/store/user/wbehrenh/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola/Spring11-PAT/6e6559812e09b52af172f27db20ae337/mc2pat_1_1_ntG.root /scratch/hh/current/cms/user/hauk/data/testPatTuple/mc2pat_1_1_ntG_Spring11_madgraph_D6T.root







