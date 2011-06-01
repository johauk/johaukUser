import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)


readFiles.extend( [

       'file:/tmp/hauk/Zmumu/apeSkim1.root',
       'file:/tmp/hauk/Zmumu/apeSkim2.root',
       'file:/tmp/hauk/Zmumu/apeSkim3.root',
       'file:/tmp/hauk/Zmumu/apeSkim4.root',
       'file:/tmp/hauk/Zmumu/apeSkim5.root',
       'file:/tmp/hauk/Zmumu/apeSkim6.root',
       'file:/tmp/hauk/Zmumu/apeSkim7.root',
       'file:/tmp/hauk/Zmumu/apeSkim8.root',
       'file:/tmp/hauk/Zmumu/apeSkim9.root',
       'file:/tmp/hauk/Zmumu/apeSkim10.root',
       'file:/tmp/hauk/Zmumu/apeSkim11.root',
       'file:/tmp/hauk/Zmumu/apeSkim12.root',
       'file:/tmp/hauk/Zmumu/apeSkim13.root',
       'file:/tmp/hauk/Zmumu/apeSkim14.root',
       'file:/tmp/hauk/Zmumu/apeSkim15.root',
       'file:/tmp/hauk/Zmumu/apeSkim16.root',
       'file:/tmp/hauk/Zmumu/apeSkim17.root',
       'file:/tmp/hauk/Zmumu/apeSkim18.root',
       'file:/tmp/hauk/Zmumu/apeSkim19.root',
       'file:/tmp/hauk/Zmumu/apeSkim20.root',
       'file:/tmp/hauk/Zmumu/apeSkim21.root',
       'file:/tmp/hauk/Zmumu/apeSkim22.root',

] )
