// -*- C++ -*-
//
// Package:    MetAnalyzer
// Class:      MetAnalyzer
// 
/**\class MetAnalyzer MetAnalyzer.cc ZmumuAnalysis/Analyzer/plugins/MetAnalyzer.cc

 Description: Plotter for missing Et distributions

 Implementation:
     Based on reconstructed PAT objects
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Wed Nov 10 11:48:47 CET 2010
// $Id: MetAnalyzer.cc,v 1.1 2010/12/09 16:18:53 hauk Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/MET.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"

#include "FWCore/Utilities/interface/EDMException.h"

#include "ZmumuAnalysis/Utils/interface/eventWeight.h"

#include "TH1.h"
//
// class declaration
//

class MetAnalyzer : public edm::EDAnalyzer {
   public:
      explicit MetAnalyzer(const edm::ParameterSet&);
      ~MetAnalyzer();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      
      const edm::ParameterSet parameterSet_;

      TH1* MissingEt;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
MetAnalyzer::MetAnalyzer(const edm::ParameterSet& iConfig):
parameterSet_(iConfig),
MissingEt(0)
{
}


MetAnalyzer::~MetAnalyzer()
{
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
MetAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // Get event weight
  const  edm::InputTag eventWeightSource(parameterSet_.getParameter<edm::InputTag>("eventWeightSource"));
  const double eventWeight = Weights::eventWeight(iEvent, eventWeightSource);
  
  const edm::InputTag metSource(parameterSet_.getParameter<edm::InputTag>("metSource"));
  edm::Handle<pat::METCollection> mets;
  iEvent.getByLabel(metSource, mets);
  if(mets->size()!=1){
    edm::LogError("Problematic Product")<<"MET collection has not exactly one entry, but: "<<mets->size();
    throw edm::Exception( edm::errors::EventCorruption,
                          "Bad MET collection" );
  }
  
  
  float met = (mets->begin())->et();
  MissingEt->Fill(met, eventWeight);
}


// ------------ method called once each job just before starting event loop  ------------
void 
MetAnalyzer::beginJob()
{
  edm::Service<TFileService> fileService;
  
  TFileDirectory dirMet = fileService->mkdir("MetProperties");
  MissingEt = dirMet.make<TH1F>("h_missingEt","missing E_{t};E_{t,miss}  [GeV];# events",40,0,200);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MetAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(MetAnalyzer);
