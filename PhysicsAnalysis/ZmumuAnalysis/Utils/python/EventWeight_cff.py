import FWCore.ParameterSet.Config as cms


from ZmumuAnalysis.Utils.EventWeightPU_cfi import *
from ZmumuAnalysis.Utils.EventWeight_cfi import *




EventWeight.eventWeightSources = [
    cms.InputTag('EventWeightPU','eventWeightPU3BX'),
]



makeEventWeights = cms.Sequence(
    EventWeightPU*
    EventWeight
)
