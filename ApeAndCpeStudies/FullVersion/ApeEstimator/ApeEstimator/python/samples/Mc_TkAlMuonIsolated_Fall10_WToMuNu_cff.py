import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)


readFiles.extend( [
       '/store/mc/Fall10/WToMuNu_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/7A7B8D23-6CD9-DF11-BB33-0024E8768D4E.root',
       '/store/mc/Fall10/WToMuNu_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/5A8A7566-EDD9-DF11-ADA0-001D0967DFFD.root',
       '/store/mc/Fall10/WToMuNu_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0000/F0C74BD1-1AD9-DF11-91C4-001D0967C464.root',
       '/store/mc/Fall10/WToMuNu_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0000/EE00CC9B-07D9-DF11-95EA-001D0967DB11.root',
       '/store/mc/Fall10/WToMuNu_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0000/D85B0203-FDD8-DF11-81FF-0024E87699C0.root',
       '/store/mc/Fall10/WToMuNu_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0000/A235FD3E-FFD8-DF11-BE00-00151796C44C.root',
       '/store/mc/Fall10/WToMuNu_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0000/84DD1AFA-F6D8-DF11-818A-001D0967D5D0.root',
       '/store/mc/Fall10/WToMuNu_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0000/7243E8BB-22D9-DF11-BE2C-0024E876A821.root',
       '/store/mc/Fall10/WToMuNu_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0000/4E21F2A4-F8D8-DF11-8EF7-00266CF25708.root',
       '/store/mc/Fall10/WToMuNu_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0000/4A92071B-00D9-DF11-A2B7-001D097177FA.root',
       '/store/mc/Fall10/WToMuNu_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0000/389777DA-28D9-DF11-9E39-001D096B0F80.root',
       '/store/mc/Fall10/WToMuNu_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0000/3633AA39-02D9-DF11-A67E-0024E876A889.root',
       '/store/mc/Fall10/WToMuNu_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0000/360C75BA-28D9-DF11-AF92-0024E8768265.root',
       '/store/mc/Fall10/WToMuNu_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0000/2E1C6B41-1CD9-DF11-A94A-0024E86E8D4C.root',
       '/store/mc/Fall10/WToMuNu_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0000/2C5D18FD-F6D8-DF11-BF4D-001D0967DBE8.root',
       '/store/mc/Fall10/WToMuNu_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0000/2C239DB6-0BD9-DF11-BE28-0015178C67C0.root',
       '/store/mc/Fall10/WToMuNu_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0000/2091E1E6-11D9-DF11-AEDB-00A0D1EE8F34.root',
       '/store/mc/Fall10/WToMuNu_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0000/00A618D1-1ED9-DF11-ACB1-0015178C4890.root',

] )
