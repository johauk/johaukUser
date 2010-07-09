import FWCore.ParameterSet.Config as cms

from IOMC.RandomEngine.IOMC_cff import *


RandomNumberGeneratorService.generator.initialSeed = 1                    # default: 123456789
RandomNumberGeneratorService.VtxSmeared.initialSeed = 1                   # default: 98765432
RandomNumberGeneratorService.LHCTransport.initialSeed = 1                 # default: 87654321
RandomNumberGeneratorService.hiSignalLHCTransport.initialSeed = 1         # default: 88776655
RandomNumberGeneratorService.g4SimHits.initialSeed = 1                    # default: 11
RandomNumberGeneratorService.mix.initialSeed = 1                          # default: 12345
RandomNumberGeneratorService.mixData.initialSeed = 1                      # default: 12345
RandomNumberGeneratorService.simSiStripDigis.initialSeed = 1              # default: 1234567
RandomNumberGeneratorService.simSiPixelDigis.initialSeed = 1              # default: 1234567
RandomNumberGeneratorService.simEcalUnsuppressedDigis.initialSeed = 1     # default: 1234567
RandomNumberGeneratorService.simHcalUnsuppressedDigis.initialSeed = 1     # default: 11223344
RandomNumberGeneratorService.simMuonDTDigis.initialSeed = 1               # default: 1234567
RandomNumberGeneratorService.simMuonCSCDigis.initialSeed = 1              # default: 11223344
RandomNumberGeneratorService.simMuonRPCDigis.initialSeed = 1              # default: 1234567
RandomNumberGeneratorService.simCastorDigis.initialSeed = 1               # default: 12345678
RandomNumberGeneratorService.hiSignal.initialSeed = 1                     # default: 123456789
RandomNumberGeneratorService.hiSignalG4SimHits.initialSeed = 1            # default: 11









