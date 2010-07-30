// -*- C++ -*-
//
// Package:    TriggerMatchedMuonProducer
// Class:      TriggerMatchedMuonProducer
// 
/**\class TriggerMatchedMuonProducer TriggerMatchedMuonProducer.cc ZmumuAnalysis/Producer/plugins/TriggerMatchedMuonProducer.cc

 Description: Producer for trigger-matched muons

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Thu Jul 29 13:45:53 CEST 2010
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "PhysicsTools/PatUtils/interface/TriggerHelper.h"


//
// class declaration
//

class TriggerMatchedMuonProducer : public edm::EDProducer {
   public:
      explicit TriggerMatchedMuonProducer(const edm::ParameterSet&);
      ~TriggerMatchedMuonProducer();

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      
      const edm::ParameterSet parameterSet_;
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
TriggerMatchedMuonProducer::TriggerMatchedMuonProducer(const edm::ParameterSet& iConfig):
parameterSet_(iConfig)
{
  // produce pat::Muon collection
  produces<std::vector<pat::Muon> >();
}


TriggerMatchedMuonProducer::~TriggerMatchedMuonProducer()
{
}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
TriggerMatchedMuonProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // get handle on muon collection
  const edm::InputTag muonSource(parameterSet_.getParameter<edm::InputTag>("muonSource"));
  edm::Handle<pat::MuonCollection> muons;
  iEvent.getByLabel(muonSource, muons);
  
  // get handle on trigger event
  const edm::InputTag triggerEventSource(parameterSet_.getParameter<edm::InputTag>("triggerEvent"));
  edm::Handle<pat::TriggerEvent> triggerEvent;
  iEvent.getByLabel(triggerEventSource, triggerEvent);
  
  // pat trigger helper to recieve for trigger 
  // matching information
  const pat::helper::TriggerMatchHelper matchHelper;
  
  // prepare vector of output vector
  std::auto_ptr<std::vector<pat::Muon> > matched(new std::vector<pat::Muon>);
  
  // receive the TriggerObjectMatch from the triggerEvent
  const std::string matches(parameterSet_.getParameter<std::string>("matches"));
  const pat::TriggerObjectMatch* triggerMatch( triggerEvent->triggerObjectMatchResult( matches ) );
  
  // loop over candidate references
  for(size_t idx=0; idx<muons->size(); ++idx){ 
    const reco::CandidateBaseRef candBaseRef(edm::Ref<std::vector<pat::Muon> >(muons, idx));
    const pat::TriggerObjectRef trigRefTag(matchHelper.triggerMatchObject(candBaseRef, triggerMatch, iEvent, *triggerEvent));
    if(trigRefTag.isAvailable()){matched->push_back((*muons)[idx]);}
  }
  iEvent.put(matched);
  
}

// ------------ method called once each job just before starting event loop  ------------
void 
TriggerMatchedMuonProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TriggerMatchedMuonProducer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(TriggerMatchedMuonProducer);
