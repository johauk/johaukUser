import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

from ApeEstimator.ApeEstimator.samples.GoodRunList_cff import LumisToProcess
source.lumisToProcess = LumisToProcess

readFiles.extend( [
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/FED2561B-0C83-E011-8D51-0017A4771014.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/FEB4BF7A-0C83-E011-9058-001CC47A52B6.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/FE5C1A46-0C83-E011-9284-001E0B471C92.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/FE413A41-0C83-E011-899A-00237DA13F9E.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/FAD24337-0C83-E011-8300-001E0B477F20.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/FA3B6395-0C83-E011-A12C-001CC4C11074.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/F6DD0D93-0C83-E011-B769-00237DA16C5E.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/F6927378-0C83-E011-B4D7-001E0B5FA5A8.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/F638DAE9-0B83-E011-A6BE-00237DA15C5E.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/F4812E3F-0C83-E011-B54A-0025B3E0216C.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/F2F719C7-EA7B-E011-B411-78E7D1E4B6E8.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/F2593035-0C83-E011-B3D9-00237DA16C5E.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/F252131D-0C83-E011-9AD1-0017A4770000.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/F2426A19-2789-E011-8136-0022640D5E2E.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/F0F7997F-0C83-E011-80EE-1CC1DE1D16D4.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/F0D9A8E9-0B83-E011-B38A-001E0B477F20.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/F0C6B648-0C83-E011-896E-1CC1DE1CE56C.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/F06AD3E9-2689-E011-98C0-0017A4770830.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/F0301738-0C83-E011-A7CD-1CC1DE1D16D4.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/EA50DDF3-0B83-E011-9A75-001E0B487192.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/E8CF9487-0C83-E011-994F-00237DA13F9E.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/E681F2F2-0B83-E011-BC4B-00237DA1CDBE.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/E64E0185-0C83-E011-B9E3-001E0B487192.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/E44712A5-0C83-E011-8FF4-001E0B5FC422.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/E427CD53-2689-E011-9A65-0017A4770830.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/E2D16819-2789-E011-A3EA-1CC1DE1CED22.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/E25B6F8B-0C83-E011-A619-001E0B48E92A.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/E0B6B3F3-0B83-E011-9837-001E0B48D108.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/D89B47F1-0B83-E011-B207-0017A4770400.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/D881E5E5-0B83-E011-8136-001E0B482944.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/D6A5BF0E-2789-E011-A300-001E0B48D9A4.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/D4A19C76-0C83-E011-A3F9-0017A4771014.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/D068A636-0C83-E011-9BBD-001E0B479CF4.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/D0254044-0C83-E011-AE8A-00237DA16C42.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/CEDD0C85-0C83-E011-AAC3-001E0B482944.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/CCD33937-0C83-E011-85EB-00237DA12CEC.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/CCC765EF-0B83-E011-8397-0022649C40A8.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/CCB2A7A3-0C83-E011-9744-00237DA1AC2A.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/CCB05B88-0C83-E011-8332-001CC4164B40.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/CC84EC91-0C83-E011-9B91-00237DA1CDBE.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/CC25E419-2789-E011-98C6-001E0B5F27BC.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/C6818E44-0C83-E011-B01F-00237DA1AC2A.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/C0993FA4-0C83-E011-A2E7-001E0B5FA4D8.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/C04ADF49-0C83-E011-8A60-00237DA12CEC.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/BEA7AEA1-0C83-E011-99A0-00237DA1A548.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/BA67CD8F-0C83-E011-9DDC-001E0B482944.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/B89FF883-0C83-E011-8E64-0025B3E0216C.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/B695701D-0C83-E011-BA7A-00237DA1A66C.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/B6549831-0C83-E011-AA4A-0017A4770434.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/B4AAA5A2-0C83-E011-915F-00237DA12CBE.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/B480329A-0C83-E011-A27C-001E0B5FA5A8.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/B45DC7F6-0B83-E011-A878-00237DA12CBE.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/B429804E-0C83-E011-977C-001E0B5FA4D8.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/B2D7EB81-0C83-E011-98EA-00237DA12CEC.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/B2040041-0C83-E011-AF88-00237DA1ED1C.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/B08AAA80-0C83-E011-A049-00237DA16C5E.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/AEE78BEA-0B83-E011-B215-001E0B479CF4.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/AEC9CCF4-0B83-E011-9FDB-001E0B5F3148.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/AE8FA190-0C83-E011-9B7D-0017A477101C.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/ACA1E1F0-0B83-E011-B227-0017A477101C.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/AABEACE7-0B83-E011-9D6E-0017A4770434.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/A8FA9947-0C83-E011-A7A6-001E0B477F20.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/A87E123C-0C83-E011-BA66-001E0B482944.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/A6680250-0C83-E011-9D8D-0017A4770428.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/A4056419-2789-E011-8B7E-001E0B48F0EE.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/A4017735-0C83-E011-B82C-001CC47A52B6.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/A2D6152D-0C83-E011-A3BA-00237D9F2120.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/A27B57A5-0C83-E011-8CB4-1CC1DE1CE128.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/9A78A288-0C83-E011-94D3-001E0B479CF4.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/9A11CB3A-0C83-E011-9284-001CC4164B40.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/967E803A-0C83-E011-BCE0-00237DA15C5E.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/966B7B93-0C83-E011-886B-0017A4770818.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/94C1C0A4-0C83-E011-A0F4-0017A4770428.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/94964550-0C83-E011-8DA5-00237DA1DDFC.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/9288812C-8E7B-E011-A1AF-1CC1DE1CDF2A.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/9281BD03-0C83-E011-B4CE-1CC1DE1D036C.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/903FF244-0C83-E011-9225-001E0B482944.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/900C9381-0C83-E011-87EA-00237DA15C5E.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/8E470020-5B7C-E011-84E6-1CC1DE1CDCAE.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/8CF215FA-0B83-E011-A65F-0017A4770428.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/8C66CFF4-0B83-E011-9FCA-0017A4770C18.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/8C08EE4C-0C83-E011-B099-0017A4770400.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/8A2B12F4-0B83-E011-A136-0025B3E01FC2.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/88B841F3-0B83-E011-9732-00237DA13F9E.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/887F5119-2789-E011-AF9E-1CC1DE052068.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/8435B4E9-0B83-E011-92C5-001CC4164B40.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/828A3CF5-0B83-E011-85CB-001E0B5FA4D8.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/7E4826A1-0C83-E011-AFD4-00237DA13C2E.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/7E276F29-0C83-E011-9791-001E0B5FA5A8.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/788D4444-0C83-E011-BC45-00237DA16C5E.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/787B98E4-0B83-E011-B7A1-00237DA16C5E.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/783635E7-0B83-E011-A21C-00237DA12CEC.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/76CE7254-0C83-E011-A790-0017A4770C18.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/7622058C-0C83-E011-8BBC-1CC1DE1CDD20.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/76088AF4-0B83-E011-B2DC-001E0B5FA5A8.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/74233D00-0C83-E011-B5C7-001E0B471C92.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/7206B286-0C83-E011-BFCE-0022649C40A8.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/7017AE19-2789-E011-B47E-1CC1DE1CE128.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/6EA1A939-0C83-E011-9ECC-00237DA13C2E.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/6E1E729E-0C83-E011-A58C-001E0B477F20.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/6AC1D43D-0C83-E011-B4D7-001E0B487192.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/68572C84-0C83-E011-A8EE-0017A4770434.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/660C4798-0C83-E011-B180-00237DA1DDFC.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/5EABF03E-0C83-E011-8958-0017A477101C.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/5EA59A95-0C83-E011-9D90-001E0B471C92.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/5EA365A9-0C83-E011-817F-001F296A527C.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/5E9A9DF8-0B83-E011-8613-001B78E2A8C8.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/58B2AA33-0C83-E011-B9CB-00237DA15C5E.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/54776940-0C83-E011-8D6A-0025B3E01FC2.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/50687C4A-0C83-E011-B44D-001E0B49808A.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/505EEB4E-0C83-E011-9111-001E0B5FA5A8.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/4EAAD691-0C83-E011-A09B-00237DA1AC2A.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/4AEE7A4B-607D-E011-B28D-0017A4770824.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/4691D3ED-0B83-E011-A5BA-001CC47A52B6.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/3CB61D92-0C83-E011-BCDF-00237DA12CEC.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/3A0DC87E-0C83-E011-A2C4-00237D9F2120.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/38DFCEF3-0B83-E011-B980-00237DA12CEC.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/383CDF8F-0C83-E011-A48E-00237DA16C42.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/32DD8AA3-0C83-E011-8AA6-001B78E2A8C8.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/32992246-0C83-E011-ABF8-001CC4C11074.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/32946C9C-0C83-E011-9713-1CC1DE1D036C.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/2E3D9187-0C83-E011-A1E3-0025B3E01FC2.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/2C5F8F26-C37D-E011-970F-0022649C40A8.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/2A6EEB82-0C83-E011-81EC-00237DA13C2E.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/2802FA46-0C83-E011-BE9F-00237DA1CDBE.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/26F261FB-0B83-E011-A422-0017A477042C.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/22C0CA95-0C83-E011-8D13-1CC1DE1CE56C.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/20F5813D-0C83-E011-AC27-0022649C40A8.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/20CD850E-2789-E011-A467-001E0B5F5898.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/1E6BB24D-0C83-E011-B999-00237DA12CBE.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/1A77A2E2-0B83-E011-B4B3-00237DA15C5E.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/162A8D11-0C83-E011-AEC6-002481A7329C.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/1057420F-2789-E011-9486-001E0B5F3148.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/0EF2EF43-0C83-E011-BAD3-001E0B5FA4D8.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/0E5803F3-0B83-E011-A863-00237DA16C42.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/0C156350-0C83-E011-A9BC-1CC1DE1D036C.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/0AD2E7FC-0B83-E011-872E-0017A4771038.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/0A61C5A3-0C83-E011-A935-002481A8A782.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/0A0F1894-0C83-E011-A019-00237DA1ED1C.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/08C2A951-0C83-E011-8FA5-00237DA1A548.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/06A2FB8F-0C83-E011-96A1-00237DA15C5E.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/065F5E48-0C83-E011-9C99-1CC1DE1CDD20.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/064061E2-0B83-E011-8F0B-1CC1DE1CE56C.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/02BBA585-0C83-E011-80B3-001E0B477F20.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/02B39E19-2789-E011-8867-0017A4770034.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/00E5FEFA-0B83-E011-8381-00237DA15C00.root',
       '/store/data/Run2011A/SingleMu/ALCARECO/TkAlMuonIsolated-May10ReReco-v1/0000/00B0E5F3-0B83-E011-936B-00237DA1AC2A.root' ] );


secFiles.extend( [
               ] )

