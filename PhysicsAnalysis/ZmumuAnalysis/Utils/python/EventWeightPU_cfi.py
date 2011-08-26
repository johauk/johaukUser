import FWCore.ParameterSet.Config as cms


EventWeightPU = cms.EDProducer("EventWeightPU",
    PUSource          = cms.InputTag("addPileupInfo"),
    MCSampleFile      = cms.FileInPath("ZmumuAnalysis/Configuration/data/MCpileup.root"),
    MCSampleHistoName = cms.string("pileup"),
    DataFile          = cms.FileInPath("ZmumuAnalysis/Configuration/data/Pileup_2011_EPS_8_jul.root"),
    DataHistoName     = cms.string("pileup"),          
    PUSysShiftUp      = cms.double(0.6),
    PUSysShiftDown    = cms.double(-0.6),
)


