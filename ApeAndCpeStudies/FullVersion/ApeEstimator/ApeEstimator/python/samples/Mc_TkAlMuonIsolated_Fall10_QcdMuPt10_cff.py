import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)


readFiles.extend( [

        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/FCE96815-DED6-DF11-B575-003048F0E522.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/FC6DC21E-DED6-DF11-8CAD-003048F0E5A4.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/FA1DC8F7-69D7-DF11-A217-003048F0E18A.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/F4E6C2BC-DDD6-DF11-A753-003048F0E83A.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/ECC49A1F-DCD6-DF11-AA77-002481E0E440.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/EAD8EA7A-DDD6-DF11-9A63-003048CF6338.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/E6D1A233-D2D6-DF11-AB1B-003048D43994.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/E40A957A-DFD6-DF11-8A7B-003048F0E83A.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/DEE90214-59D7-DF11-B259-003048CFCBB2.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/D8C63323-DED6-DF11-AA78-003048F0E3B8.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/D45F31CC-D9D6-DF11-AE9F-003048F0E5A4.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/D0CDAA01-DFD6-DF11-929B-003048F0E3B4.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/C01B5609-DAD6-DF11-A79B-003048F02CB2.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/BC662514-59D7-DF11-9E9F-003048F0E55A.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/A6E55CED-DAD6-DF11-8DD4-003048F0E83A.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/98B111CC-D9D6-DF11-A83B-003048F010F4.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/88CD43EF-D2D6-DF11-9BEA-002481E101DA.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/869AA833-D2D6-DF11-84B3-003048D43788.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/84DA921F-DCD6-DF11-ADCD-002481E0E440.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/803AAA08-DAD6-DF11-84B7-003048F0E834.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/801562F2-DAD6-DF11-B022-003048F0E55A.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/78C9C15C-D3D6-DF11-BCB6-003048C69288.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/78BC4616-DED6-DF11-8A1A-002481E94B26.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/60692621-DCD6-DF11-B813-002481E94BFE.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/6061BA72-D1D6-DF11-BAB1-003048C692DE.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/5A21A501-DFD6-DF11-843E-003048F0E188.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/46B12D19-59D7-DF11-A892-003048F0EBBC.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/385164ED-DAD6-DF11-99B9-003048F0E832.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/30F6E833-D2D6-DF11-8D06-002481E107A8.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/30DC6959-DCD6-DF11-AF66-003048F0E186.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/26BDEF08-DAD6-DF11-AB9B-003048F0E834.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/2044F8A6-D0D6-DF11-ADC2-0030487F91DB.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/06A5BC30-D2D6-DF11-8308-003048F0E7FC.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/043A4811-DDD6-DF11-98D2-003048F02CBE.root',
        '/store/mc/Fall10/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6/ALCARECO/START38_V12_TkAlMuonIsolated-v1/0001/02BD93DE-56D7-DF11-8615-003048F0E812.root',

] )
