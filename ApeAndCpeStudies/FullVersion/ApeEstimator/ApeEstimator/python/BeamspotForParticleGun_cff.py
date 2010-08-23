import FWCore.ParameterSet.Config as cms


import RecoVertex.BeamSpotProducer.BeamSpotFakeParameters_cfi
BeamspotForParticleGun = RecoVertex.BeamSpotProducer.BeamSpotFakeParameters_cfi.BeamSpotFakeConditions.clone(
    X0 = 0.0322,
    Y0 = 0.,
    Z0 = 0.,
    dxdz = 0.,
    dydz = 0.,
    sigmaZ = 4.2,
    widthX = 0.0105,
    widthY = 0.0105,
    emittanceX = 1.0e-07,
    emittanceY = 1.0e-07,
    betaStar = 1100.,
    errorX0 = 0.0012087,
    errorY0 = 0.00163803,
    errorZ0 = 0.00316228,
    errordxdz = 0.000307662,
    errordydz = 0.000408403,
    errorSigmaZ = 0.251521,
    errorWidth = 0.005,
)
es_prefer_beamspot = cms.ESPrefer("BeamSpotFakeConditions","BeamspotForParticleGun")
