import FWCore.ParameterSet.Config as cms


SimulationEventContent = cms.PSet(
    outputCommands = cms.untracked.vstring(
        #'drop  recoGenJets_*_*_RAW',
	#'drop  recoGenMETs_*_*_RAW',
	#'drop  recoGenParticles_*_*_RAW',
	#'drop  Sim*_g4SimHits_*_RAW',
	#'drop  P*Hits_g4SimHits_*_RAW',
	#'keep  PSimHits_g4SimHits_TrackerHits*_RAW',
	#'drop  *_simMuon*Digis_*_RAW',
	#'drop  CrossingFramePlaybackInfoExtended_mix__RAW',
	#'drop  GenEventInfoProduct_generator__RAW',
	#'drop  edm*_*_*_RAW',
	#'drop  RandomEngineStates_randomEngineStateProducer__RAW',
	#'drop  ints_genParticles__RAW',
	
	'drop  *_*_*_RAW',
	'keep  PSimHits_g4SimHits_TrackerHits*_RAW',
	'keep  FEDRawDataCollection_rawDataCollector__RAW',
    ),
    splitLevel = cms.untracked.int32(0),
)



ReconstructionEventContent = cms.PSet(
    outputCommands = cms.untracked.vstring(
	'drop *_*_*_RAW',
	'drop *_*_*_RECO',
	'keep *_generalTracks_*_RECO',
	'drop Trajectory*_generalTracks_*_RECO',
	'keep Si*ClusteredmNewDetSetVector_*_*_RECO',
    ),
    splitLevel = cms.untracked.int32(0),
)



ApeSkimEventContent = cms.PSet(
    outputCommands = cms.untracked.vstring(
	'drop *_*_*_RECO',
        'keep L1*_*_*_RECO',
	'drop *_L1T1*_*_*',
	'drop *_MEtoEDMConverter_*_*',
    ),
)
