import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_9_1_hgA.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_99_1_gnH.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_98_1_xRK.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_97_1_2Gj.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_96_1_OuH.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_95_1_KRb.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_94_1_TE4.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_93_1_kqd.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_91_1_Zgs.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_90_1_dHq.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_8_1_PMb.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_89_1_Qfu.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_88_1_qnV.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_87_1_AoK.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_86_1_Oyh.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_85_1_UQe.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_84_1_8hR.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_83_1_kke.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_82_1_LW8.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_81_1_1ya.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_80_1_LHU.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_7_1_gKI.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_79_1_APC.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_78_1_Fy7.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_77_1_R8m.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_76_1_pK9.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_75_1_1Bt.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_74_1_7gX.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_73_1_k0C.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_72_1_Kr5.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_71_1_Pp0.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_6_1_AN3.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_69_1_JWh.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_68_1_3mn.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_67_1_uBa.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_66_1_VOi.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_65_1_aMT.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_64_1_hm2.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_63_1_KxO.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_62_1_vIn.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_61_1_V1j.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_60_1_SSL.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_5_1_Cyl.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_59_1_uIx.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_58_1_M7R.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_57_1_TEX.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_56_1_wff.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_55_1_hi8.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_54_1_Vnz.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_53_1_I8F.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_52_1_RRo.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_51_1_q0A.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_50_1_MWD.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_4_1_9SG.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_49_1_q4p.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_48_1_n0Y.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_47_1_K0P.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_46_1_DJj.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_45_1_lTA.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_44_1_4BV.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_43_1_bqq.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_42_1_nAe.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_41_1_i1M.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_40_1_iys.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_3_1_b7Y.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_39_1_zLl.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_38_1_fsl.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_37_1_yFI.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_36_1_6oP.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_35_1_JPM.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_34_1_gtF.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_33_1_UhQ.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_32_1_xCM.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_31_1_9g9.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_30_1_jM6.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_2_1_BLj.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_29_1_f9S.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_28_1_wkr.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_27_1_824.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_26_1_GHv.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_25_1_ykf.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_24_1_5ys.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_23_1_Je0.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_22_1_ucJ.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_21_1_fw9.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_20_1_Sjw.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_19_1_05t.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_189_1_tNS.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_188_1_xWW.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_187_1_fqJ.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_186_1_MCF.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_185_1_Wmu.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_184_1_m7E.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_183_1_F0p.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_182_1_Y9k.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_181_1_yGg.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_180_1_nRs.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_179_1_RX5.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_178_1_LqV.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_177_1_MDf.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_176_1_yZf.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_175_1_W0p.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_174_1_lfX.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_173_1_ox4.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_172_1_ZpO.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_171_1_297.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_170_1_bkC.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_16_1_6gO.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_169_1_O3R.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_168_1_GCY.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_167_1_LvI.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_166_1_d4B.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_165_1_F9G.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_164_1_tDU.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_163_1_avi.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_162_1_EtP.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_161_1_Ojw.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_160_1_vRS.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_15_1_4iP.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_159_1_2Eq.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_158_1_tr6.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_157_1_oal.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_156_1_CKB.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_155_1_tDe.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_154_1_aBv.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_153_1_yHy.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_152_1_ZwP.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_151_1_rNr.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_150_1_fq5.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_14_1_flV.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_149_1_U90.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_148_1_ZYP.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_147_1_7Gs.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_146_1_iyx.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_145_1_790.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_144_1_1cc.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_143_1_eKw.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_142_1_VzH.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_141_1_v2V.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_140_1_pzJ.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_13_1_KH9.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_139_1_S3u.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_138_1_AYF.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_137_1_P2i.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_136_1_cTG.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_135_1_BmX.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_134_1_Aae.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_132_1_J67.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_131_1_Szq.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_130_1_IRK.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_12_1_oM7.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_129_1_MvJ.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_128_1_KqL.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_127_1_yS0.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_126_1_rDN.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_125_1_eew.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_124_1_X1Q.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_123_1_CG9.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_122_1_mTq.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_121_1_Vvc.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_120_1_cup.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_11_1_hGK.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_119_1_dDt.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_118_1_f8f.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_117_1_uVi.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_116_1_zGt.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_115_1_Fgc.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_114_1_ot8.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_113_1_Q7J.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_112_1_yki.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_111_1_RAJ.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_110_1_LWU.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_10_1_tjJ.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_109_1_5TN.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_108_1_mun.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_107_1_oFF.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_106_1_Ate.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_105_1_fZu.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_104_1_oAj.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_103_1_r1u.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_102_1_gq9.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_101_1_4Dw.root',
       '/store/user/hauk/TTJets_TuneZ2_7TeV-madgraph-tauola/Summer11_TTJets_Z2_madgraph_423_PAT_July10/bbcc262b5d85210b5cbc083e60a17a9c/patTuple_100_1_AWg.root' ] );


secFiles.extend( [
               ] )
