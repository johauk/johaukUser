// -*- C++ -*-
//
// Package:    EventAnalyzer
// Class:      EventAnalyzer
// 
/**\class EventAnalyzer EventAnalyzer.cc ZmumuAnalysis/Analyzer/plugins/EventAnalyzer.cc

 Description: Plotter for event properties, which are not especially related to muons or jets

 Implementation:
     Based on reconstructed PAT objects
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Thu Jun  3 17:42:24 CEST 2010
// $Id$
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
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"

#include "FWCore/Utilities/interface/EDMException.h"


#include "TH1.h"
//
// class declaration
//

class EventAnalyzer : public edm::EDAnalyzer {
   public:
      explicit EventAnalyzer(const edm::ParameterSet&);
      ~EventAnalyzer();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      
      const edm::ParameterSet parameterSet_;
      
      /// no. of selected muons in event
      TH1 *MuonSize;
      
      /// no. of selected jets in event
      TH1 *JetSize;
      
      /// missing Et
      TH1 *MissingEt;
      
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
EventAnalyzer::EventAnalyzer(const edm::ParameterSet& iConfig):
parameterSet_(iConfig)
{
}


EventAnalyzer::~EventAnalyzer()
{
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
EventAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // get handle on collections
  const edm::InputTag muonSource(parameterSet_.getParameter<edm::InputTag>("muonSource"));
  edm::Handle<pat::MuonCollection> muons; 
  iEvent.getByLabel(muonSource, muons);
  
  const edm::InputTag jetSource(parameterSet_.getParameter<edm::InputTag>("jetSource"));
  edm::Handle<pat::JetCollection> jets; 
  iEvent.getByLabel(jetSource, jets);
  
  const edm::InputTag metSource(parameterSet_.getParameter<edm::InputTag>("metSource"));
  edm::Handle<pat::METCollection> mets; 
  iEvent.getByLabel(metSource, mets);
  if(mets->size()!=1){
    edm::LogError("Problematic Product")<<"MET collection has not exactly one entry, but: "<<mets->size()
                                        <<"\n...skipping event";
  }
  
  // get weight when indicated, else weight is 1.
  double weight(1.);
  if(parameterSet_.getParameter<bool>("useEventWeight")){
    edm::Handle<double> weightHandle;
    iEvent.getByLabel("eventWeight",weightHandle);
    weight = *weightHandle;
  }
  
  MuonSize->Fill(muons->size(), weight);
  JetSize->Fill(jets->size(), weight);
  //float met = (mets->begin())->corSumEt();  // do not understand, what this is...
  float met = (mets->begin())->et();
  MissingEt->Fill(met, weight);

}


// ------------ method called once each job just before starting event loop  ------------
void 
EventAnalyzer::beginJob()
{
  edm::Service<TFileService> fileService;
  if(!fileService){
    throw edm::Exception( edm::errors::Configuration,
                          "TFileService is not registered in cfg file" );
  }
  
  TFileDirectory dirEvt = fileService->mkdir("EventProperties");
  MuonSize = dirEvt.make<TH1F>("h_muonSize","# selected muons;# muons;# events",10,0,10);
  JetSize = dirEvt.make<TH1F>("h_jetSize","# selected jets;# jets;# events",20,0,20);
  MissingEt =  dirEvt.make<TH1F>("h_missingEt","missing E_{t};E_{t,miss}  [GeV];# events",20,0,200);
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
EventAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(EventAnalyzer);