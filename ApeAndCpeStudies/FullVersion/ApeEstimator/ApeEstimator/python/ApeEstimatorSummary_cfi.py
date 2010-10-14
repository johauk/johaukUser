import os

import FWCore.ParameterSet.Config as cms


ApeEstimatorSummary = cms.EDAnalyzer('ApeEstimatorSummary',
    
    # Set baseline or calculate APE (for APE calculation)
    setBaseline = cms.bool(False),
    
    # Sigma factor for second gauss fit (+-2.5 sigma1 around mean1 of first fit), (for APE calculation)
    sigmaFactorFit = cms.double(2.5),
    
    # Multiplicative APE correction scaling factor (to prevent overestimation, since estimation is iterative process), (for APE calculation)
    correctionScaling = cms.double(1.),
    
    # File name for input file containing normalized residual distributions per sector per error bin (specified in first step's TFileService)
    InputFile = cms.string(os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/inputFile.root'),
    
    # File name for result histograms of: estimated width of normalized residuals, calculated APE value
    ResultsFile = cms.string(os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/resultsFile.root'),
    
    #File name for root file defining the baseline of normalized residual width per sector for design geometry (for APE calculation)
    BaselineFile = cms.string(os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/baselineApe.root'),
    
    #File name for root file used for iterations where calculated squared APE values are written to (for APE calculation)
    IterationFile = cms.string(os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/iterationApe.root'),
    
    #File name for text file where calculated APE values are written to, used for DBobject creation (for APE calculation)
    ApeOutputFile = cms.string(os.environ['CMSSW_BASE'] + '/src/ApeEstimator/ApeEstimator/hists/apeOutput.txt'),
    
)
