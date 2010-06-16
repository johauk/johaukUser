import FWCore.ParameterSet.Config as cms

#maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles )
readFiles.extend( [



'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/9CA7B695-6ABB-DE11-8BAD-001731AF6873.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/CCC20FBE-6BBB-DE11-937A-001731AF66FD.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/F8A02714-6CBB-DE11-BB63-0026189438D3.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0011/6A40C518-A0BA-DE11-A212-001A92971B5E.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0012/90F1E626-A8BA-DE11-A366-0017313F02F2.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/4843B2D3-6BBB-DE11-9187-0018F3D09654.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0012/56A66AAB-A7BA-DE11-B7F6-003048678B92.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/943825A8-6ABB-DE11-95DE-003048678F74.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/029E6A49-6ABB-DE11-8EC2-00261894392B.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/8240E597-6ABB-DE11-AAFF-0026189438FE.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/BCD40F9A-6ABB-DE11-8D0D-002618943922.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/24DB7395-6ABB-DE11-9CD8-0030486791C6.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/AEF2C4B6-6ABB-DE11-8865-002618943963.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/584167C5-6BBB-DE11-B9E8-0018F3D09690.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/EA1D660C-6CBB-DE11-81F0-001A928116C2.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/0094AABE-6BBB-DE11-8B31-002618943800.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0012/B01D72EC-ABBA-DE11-8A30-00261894389E.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/E4DA1ECF-6BBB-DE11-89CB-00304867D838.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/94D30C49-6ABB-DE11-9D8E-0018F3D096C2.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/2C117B26-6CBB-DE11-912C-001A9281174A.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/3653F052-6ABB-DE11-B282-0018F3D09652.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/C24DFE9A-6ABB-DE11-8DB4-001731AF6721.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/96538FAD-6ABB-DE11-ADAE-003048678FA6.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0012/4ECA8719-64BB-DE11-A579-0018F3D096FE.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/62309ECC-6BBB-DE11-8AD4-00261894396A.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0012/6278C92A-A5BA-DE11-8CC7-00248C0BE005.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/BCBED6A2-6ABB-DE11-ACDD-001731AF66B3.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0011/8C11A0A1-85BA-DE11-8EF8-002354EF3BE3.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0012/0AA9E82B-A7BA-DE11-A1CC-00261894387A.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0011/2C6420B4-A0BA-DE11-8F10-001A928116FC.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0012/F8026020-A8BA-DE11-A7B4-001A928116FC.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/160CDBBE-6BBB-DE11-9814-0018F3D09642.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0011/2E16801E-A0BA-DE11-BE4A-001731AF67E3.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0012/70419677-AABA-DE11-B23F-00261894393A.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/4407E064-6ABB-DE11-8A23-0017312B56A7.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/6A708B4D-6ABB-DE11-B554-0026189438BD.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/E0154D61-6ABB-DE11-96EE-0026189438BD.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/FC54AE45-6ABB-DE11-914C-00261894388A.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/A60ACA56-6ABB-DE11-BC42-003048678FEA.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/D81F0264-6ABB-DE11-9ECC-002618943933.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/D2E4FC59-6ABB-DE11-8DED-003048678B8E.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/944D51AD-6ABB-DE11-B70A-001731230C61.root',	
'rfio:///?svcClass=cmscafuser&path=/castor/cern.ch/cms/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0012/7CBC14B1-ACBA-DE11-A35E-001A92810AA4.root'	





#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/9CA7B695-6ABB-DE11-8BAD-001731AF6873.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/CCC20FBE-6BBB-DE11-937A-001731AF66FD.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/F8A02714-6CBB-DE11-BB63-0026189438D3.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0011/6A40C518-A0BA-DE11-A212-001A92971B5E.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0012/90F1E626-A8BA-DE11-A366-0017313F02F2.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/4843B2D3-6BBB-DE11-9187-0018F3D09654.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0012/56A66AAB-A7BA-DE11-B7F6-003048678B92.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/943825A8-6ABB-DE11-95DE-003048678F74.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/029E6A49-6ABB-DE11-8EC2-00261894392B.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/8240E597-6ABB-DE11-AAFF-0026189438FE.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/BCD40F9A-6ABB-DE11-8D0D-002618943922.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/24DB7395-6ABB-DE11-9CD8-0030486791C6.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/AEF2C4B6-6ABB-DE11-8865-002618943963.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/584167C5-6BBB-DE11-B9E8-0018F3D09690.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/EA1D660C-6CBB-DE11-81F0-001A928116C2.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/0094AABE-6BBB-DE11-8B31-002618943800.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0012/B01D72EC-ABBA-DE11-8A30-00261894389E.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/E4DA1ECF-6BBB-DE11-89CB-00304867D838.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/94D30C49-6ABB-DE11-9D8E-0018F3D096C2.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/2C117B26-6CBB-DE11-912C-001A9281174A.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/3653F052-6ABB-DE11-B282-0018F3D09652.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/C24DFE9A-6ABB-DE11-8DB4-001731AF6721.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/96538FAD-6ABB-DE11-ADAE-003048678FA6.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0012/4ECA8719-64BB-DE11-A579-0018F3D096FE.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/62309ECC-6BBB-DE11-8AD4-00261894396A.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0012/6278C92A-A5BA-DE11-8CC7-00248C0BE005.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/BCBED6A2-6ABB-DE11-ACDD-001731AF66B3.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0011/8C11A0A1-85BA-DE11-8EF8-002354EF3BE3.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0012/0AA9E82B-A7BA-DE11-A1CC-00261894387A.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0011/2C6420B4-A0BA-DE11-8F10-001A928116FC.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0012/F8026020-A8BA-DE11-A7B4-001A928116FC.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/160CDBBE-6BBB-DE11-9814-0018F3D09642.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0011/2E16801E-A0BA-DE11-BE4A-001731AF67E3.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0012/70419677-AABA-DE11-B23F-00261894393A.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/4407E064-6ABB-DE11-8A23-0017312B56A7.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/6A708B4D-6ABB-DE11-B554-0026189438BD.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/E0154D61-6ABB-DE11-96EE-0026189438BD.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/FC54AE45-6ABB-DE11-914C-00261894388A.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/A60ACA56-6ABB-DE11-BC42-003048678FEA.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/D81F0264-6ABB-DE11-9ECC-002618943933.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/D2E4FC59-6ABB-DE11-8DED-003048678B8E.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0013/944D51AD-6ABB-DE11-B70A-001731230C61.root',	
#'/store/data/CRAFT09/Cosmics/ALCARECO/StreamTkAlCosmics0T-CRAFT09_R_V4_CosmicsSeq_v1/0012/7CBC14B1-ACBA-DE11-A35E-001A92810AA4.root'	



] );