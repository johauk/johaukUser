// -*- C++ -*-
//
// Package:    EventWeight
// Class:      EventWeight
// 
/**\class EventWeight EventWeight.cc ZmumuAnalysis/Utils/plugins/EventWeight.cc

 Description: Calculates the event weight 

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Fri Jul 29 00:12:31 CEST 2011
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

//
// class declaration
//

class EventWeight : public edm::EDProducer {
   public:
      explicit EventWeight(const edm::ParameterSet&);
      ~EventWeight();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void endRun(edm::Run&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

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
EventWeight::EventWeight(const edm::ParameterSet& iConfig):
parameterSet_(iConfig)
{
  produces<double>();
}


EventWeight::~EventWeight(){}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
EventWeight::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  double finalWeight(1.);
  
  std::vector<edm::InputTag> eventWeightSources(parameterSet_.getParameter<std::vector<edm::InputTag> >("eventWeightSources"));
  
  std::vector<edm::InputTag>::const_iterator i_eventWeight;
  for(i_eventWeight = eventWeightSources.begin();i_eventWeight != eventWeightSources.end(); ++i_eventWeight){
    edm::Handle<double> weight;
    iEvent.getByLabel(*i_eventWeight, weight);
    
    if(weight.isValid()){
      finalWeight *= *weight;
    }
    else{
      edm::LogInfo("EventWeight")<<"Weight not found: "<<*i_eventWeight;
    }
  }
  
  std::auto_ptr<double> result(new double);
  *result = finalWeight;
  iEvent.put(result);
}

// ------------ method called once each job just before starting event loop  ------------
void 
EventWeight::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
EventWeight::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
EventWeight::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
EventWeight::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
EventWeight::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
EventWeight::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
EventWeight::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(EventWeight);
