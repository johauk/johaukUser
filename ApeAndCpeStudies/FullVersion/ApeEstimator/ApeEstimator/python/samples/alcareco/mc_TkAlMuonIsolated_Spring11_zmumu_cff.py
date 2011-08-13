import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_9_1_hZq.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_8_1_oSZ.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_82_1_tLO.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_81_1_YQS.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_80_1_Jdn.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_7_1_Qj1.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_79_1_L73.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_78_1_KWM.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_77_1_Xa5.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_76_1_BAA.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_75_1_opB.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_74_1_C7c.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_73_1_Xgm.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_72_1_fFO.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_71_1_8jK.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_70_1_E0e.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_6_1_uSM.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_69_1_fut.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_68_1_Bcf.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_67_1_xkw.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_66_1_LuV.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_65_1_JJN.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_64_1_SDX.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_63_1_KNI.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_62_1_pFd.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_61_1_uRg.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_60_1_RAE.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_5_1_DwZ.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_59_1_NPM.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_58_1_eMB.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_57_1_tGM.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_56_1_fNO.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_55_1_JZ3.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_54_1_g5R.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_53_1_cze.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_52_1_vv5.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_51_1_LiV.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_50_1_Abk.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_4_1_By6.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_49_1_AcM.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_48_1_3jv.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_47_1_o3q.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_46_1_HFE.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_45_1_Gpn.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_44_1_xhj.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_43_1_5GN.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_42_1_XbF.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_41_1_FQL.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_40_1_hjU.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_3_1_KFh.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_39_1_DCI.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_38_1_X3N.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_37_1_eT2.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_36_1_KGk.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_35_1_MfS.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_34_1_ksI.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_33_1_aKG.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_32_1_1XM.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_31_1_iiO.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_30_1_nfk.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_2_1_L0h.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_29_1_0q7.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_28_1_xyt.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_27_1_LLW.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_26_1_wnd.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_25_1_fNt.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_24_1_5tW.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_23_1_Giy.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_22_1_v7w.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_21_1_CHR.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_20_1_y9e.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_1_1_vSs.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_19_1_AG1.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_18_1_OHP.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_17_1_8Pq.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_16_1_bE8.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_15_1_11e.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_14_1_hlf.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_13_1_DZa.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_12_1_H5Y.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_11_1_pbk.root',
       '/store/user/hauk/DYToMuMu_M-20_TuneZ2_7TeV-pythia6/Spring11_DYToMuMu_M-20_pythia_414_ALCARECO_Aug08/4a427658f85cab9062396082a9d2b12e/alcarecoMuonIsolated_10_1_dhi.root' ] );


secFiles.extend( [
               ] )
