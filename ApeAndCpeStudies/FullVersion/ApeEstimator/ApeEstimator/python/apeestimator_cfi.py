import FWCore.ParameterSet.Config as cms

import os

#"CMSSW_BASE": os.environ['CMSSW_BASE'],

ApeEstimator = cms.EDAnalyzer('ApeEstimator',
    
    #Input source of Tracks
    tjTkAssociationMapTag = cms.InputTag("TrackRefitter1"),
    
    #Max nr of tracks per event:
    # default = 0, no event selection
    maxTracksPerEvent = cms.uint32(0),
    
    #Perform Track Cuts
    applyTrackCuts = cms.bool(True),
    
    
    HitSelector = cms.PSet(
      
      #Parameters for Cuts on Clusters (independent of track reconstruction, but associated to a track's hit)
      width = cms.vuint32(),        #interval, needs even number of arguments. for int specify one number n as interval (n,n)
      charge = cms.vdouble(),
      chargeLR = cms.vdouble(),
      edgeStrips = cms.vuint32(),   #how many strips on edge to exclude wrt. maxStrip (on both edges)
      maxCharge = cms.vdouble(),
      maxIndex = cms.vuint32(),
      sOverN = cms.vdouble(),
      
      #Parameters for Cuts on Hits (depending on track reconstruction)
      resX = cms.vdouble(),
      norResX = cms.vdouble(),
      errXHit = cms.vdouble(),
      errXTrk = cms.vdouble(),
      errX = cms.vdouble(),
      errX2 = cms.vdouble(),   #squared error of residuals(X)
      phiSens = cms.vdouble(), #trajectory angle on module
      phiSensX = cms.vdouble(),
      phiSensY = cms.vdouble()
    ),
    
    #Define minimum number of selected hits for track selection (choose only tracks with enough good hits)
    minGoodHitsPerTrack = cms.uint32(0),
    
    #Define intervals in residual error for calculation of APE (one estimation per interval)
    residualErrorBinning = cms.vdouble(),
    
    #Vary Histo's ranges for Overview Plots
    zoomHists = cms.bool(True),
    
    #Special Filter for Residual Error Histograms, additional hists binned in 100um (1: 0-100um, 2: 100-200um)
    vErrHists = cms.vuint32(),
    
    #File containing TrackerTree with ideal Geometry
    TrackerTreeFile = cms.string(os.environ['CMSSW_BASE'] + '/src/Alignment/TrackerTreeGenerator/hists/TrackerTree.root'),
    
    #Sectors for same APE
    Sectors = cms.VPSet()
    
)
