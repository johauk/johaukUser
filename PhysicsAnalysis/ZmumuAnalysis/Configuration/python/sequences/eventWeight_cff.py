import FWCore.ParameterSet.Config as cms




# General event weight producer
from ZmumuAnalysis.Utils.EventWeight_cff import *


EventWeight.eventWeightSources = [
    cms.InputTag('EventWeightPU','eventWeightPU'),
]


buildEventWeights = makeEventWeights
