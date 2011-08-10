import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_9_1_atc.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_99_1_FHh.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_98_1_s36.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_97_1_Nv0.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_96_1_DEY.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_95_1_6VQ.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_94_1_eHc.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_93_1_hL0.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_91_1_IX3.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_90_1_3Xb.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_8_1_hRH.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_89_1_kWg.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_88_1_JlV.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_87_1_mly.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_86_1_o6Q.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_85_1_Tmk.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_84_1_i7n.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_83_1_lW5.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_82_1_LWl.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_81_1_C1X.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_80_1_uhS.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_7_1_SUc.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_79_1_cy3.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_78_1_JJN.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_77_1_Sq4.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_76_1_rQj.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_75_1_aan.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_74_1_lqg.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_73_1_LVi.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_72_1_1M6.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_71_1_DWW.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_6_1_62l.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_69_1_5hR.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_68_1_2n5.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_67_1_kEU.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_66_1_lV4.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_65_1_Lcm.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_64_1_KQN.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_63_1_suD.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_62_1_Xmf.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_61_1_0Ay.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_60_1_kls.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_5_1_NdO.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_59_1_uYK.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_58_1_mGa.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_57_1_i4L.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_56_1_IPs.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_55_1_AP0.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_54_1_q5x.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_53_1_X2A.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_52_1_MLq.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_51_1_1Au.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_50_1_Ssb.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_4_1_akS.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_49_1_nJY.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_48_1_SlK.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_47_1_iDf.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_46_1_f2y.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_45_1_Y4G.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_44_1_n2w.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_43_1_kOT.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_42_1_pOv.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_41_1_RjQ.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_40_1_yLU.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_3_1_xC6.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_39_1_zVk.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_38_1_fNQ.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_37_1_GdY.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_36_1_pgg.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_35_1_iVR.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_34_1_aym.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_33_1_H65.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_32_1_XzQ.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_31_1_u8C.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_30_1_oxc.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_2_1_W5e.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_29_1_Db6.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_28_1_OQ3.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_27_1_tBi.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_26_1_6tR.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_25_1_wnH.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_24_1_irk.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_23_1_Qgk.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_22_1_ZJ7.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_21_1_NhV.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_20_1_vV3.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_19_1_7ju.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_189_1_wio.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_188_1_6ON.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_187_1_pnJ.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_186_1_4Gm.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_185_1_3dy.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_184_1_iY5.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_183_1_qaj.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_182_1_q5M.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_181_1_Wkd.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_180_1_Q8C.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_179_1_xbN.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_178_1_mrx.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_177_1_02G.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_176_1_oj2.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_175_1_8dw.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_174_1_5xG.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_173_1_0Ui.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_172_1_9SE.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_171_1_q2J.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_170_1_71q.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_16_1_MxY.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_169_1_Hyn.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_168_1_R67.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_167_1_joM.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_166_1_O8D.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_165_1_FQm.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_164_1_N5H.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_163_1_8GU.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_162_1_ZHL.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_161_1_nT6.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_160_1_b2n.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_15_1_Fd0.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_159_1_joh.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_158_1_ByV.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_157_1_gKO.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_156_1_NRF.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_155_1_N5b.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_154_1_FyG.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_153_1_Rg0.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_152_1_X38.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_151_1_lmS.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_150_1_Goo.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_14_1_pqX.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_149_1_kJ8.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_148_1_PEe.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_147_1_ifF.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_146_1_x8c.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_145_1_cns.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_144_1_hQe.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_143_1_o1A.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_142_1_xHU.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_141_1_y7j.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_140_1_nm4.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_13_1_wyP.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_139_1_9LH.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_138_1_3uJ.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_137_1_plp.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_136_1_iRB.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_135_1_X6B.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_134_1_KwZ.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_132_1_Fhb.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_131_1_P3G.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_130_1_5CK.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_12_1_NYI.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_129_1_0mN.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_128_1_YY1.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_127_1_NuX.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_126_1_rxU.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_125_1_RTG.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_124_1_cyk.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_123_1_Jty.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_122_1_9yt.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_121_1_Tbm.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_120_1_2MI.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_11_1_8pN.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_119_1_ULH.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_118_1_kMa.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_117_1_dCd.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_116_1_mxH.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_115_1_B06.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_114_1_ahu.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_113_1_HAl.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_112_1_EBy.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_111_1_6eq.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_110_1_eUA.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_10_1_C4g.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_109_1_sRA.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_108_1_Tgi.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_107_1_s4F.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_106_1_wg6.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_105_1_SW6.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_104_1_0RM.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_103_1_mFV.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_102_1_CpF.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_101_1_z7i.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_425_PAT_Aug05/f7b7b5ec9f6e8dd23fb3ffd521e21ae0/patTuple_100_1_zZj.root' ] );


secFiles.extend( [
               ] )

