import os

import FWCore.ParameterSet.Config as cms


ApeEstimator = cms.EDAnalyzer('ApeEstimator',
    
    #Input source of Tracks
    tjTkAssociationMapTag = cms.InputTag("TrackRefitterForApeEstimator"),
    
    #Max no. of tracks per event:
    # default = 0, no event selection
    maxTracksPerEvent = cms.uint32(0),
    
    #Perform Track Cuts
    applyTrackCuts = cms.bool(True),
    
    # Selection of useful hits for analysis
    HitSelector = cms.PSet(
      
      #Parameters for Cuts on Clusters (independent of track reconstruction, but associated to a track's hit)
      width = cms.vuint32(),        #interval, needs even number of arguments. for int specify one number n as interval (n,n)
      widthProj = cms.vdouble(),
      widthDiff = cms.vdouble(),
      charge = cms.vdouble(),
      edgeStrips = cms.vuint32(),   #how many strips on edge to exclude wrt. maxStrip (on both edges)
      maxCharge = cms.vdouble(),
      chargeOnEdges = cms.vdouble(),    # fraction of charge on edge strips of cluster
      chargeAsymmetry = cms.vdouble(),     # asymmetry of charge on edge strips of cluster
      maxIndex = cms.vuint32(),
      sOverN = cms.vdouble(),
      
      #Parameters for Cuts on Hits (depending on track reconstruction)
      resX = cms.vdouble(),
      norResX = cms.vdouble(),
      probX = cms.vdouble(),
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
    
    #File containing TrackerTree with ideal Geometry
    TrackerTreeFile = cms.string(os.environ['CMSSW_BASE'] + '/src/Alignment/TrackerTreeGenerator/hists/TrackerTree.root'),
    
    #Sectors defining set of modules for common overview plots resp. APE values
    Sectors = cms.VPSet(),
    
    
    
    #Tool 1: Switch on Analyzer mode with full set of overview plots
    analyzerMode = cms.bool(True),
    
    #Vary Histo's ranges for Overview Plots (for analyzer mode)
    zoomHists = cms.bool(True),
    
    #Special Filter for Residual Error Histograms, additional hists binned in 100um (1: 0-100um, 2: 100-200um), (for analyzer mode)
    vErrHists = cms.vuint32(),
    
    
    
    #Tool 2: Switch on calculation of APE values
    calculateApe = cms.bool(True),
    
     #Define intervals in residual error for calculation of APE (one estimation per interval), (for APE calculation)
    residualErrorBinning = cms.vdouble(),
    
    #Sigma factor for second gauss fit (+-2.5 sigma1 around mean1 of first fit), (for APE calculation)
    sigmaFactorFit = cms.double(2.5),
    
    #Multiplicative APE correction scaling factor (to prevent overestimation, since estimation is iterative process), (for APE calculation)
    correctionScaling = cms.double(1.),
    
    #File name for root file used for iterations where calculated squared APE values are written to (for APE calculation)
    IterationFile = cms.string(os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/iterationApe.root'),
    
    #File name for text file where calculated APE values are written to, used for DBobject creation (for APE calculation)
    ApeOutputFile = cms.string(os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/apeOutput.txt'),
    
)
