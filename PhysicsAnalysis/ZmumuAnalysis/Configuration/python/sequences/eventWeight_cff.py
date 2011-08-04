import FWCore.ParameterSet.Config as cms




# General event weight producer
from ZmumuAnalysis.Utils.EventWeight_cfi import *





buildEventWeights = cms.Sequence(
    EventWeight
)
