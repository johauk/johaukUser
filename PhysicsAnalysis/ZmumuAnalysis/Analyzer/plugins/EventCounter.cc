// -*- C++ -*-
//
// Package:    EventCounter
// Class:      EventCounter
// 
/**\class EventCounter EventCounter.cc ZmumuAnalysis/EventCounter/src/EventCounter.cc

 Description: Single histogram with number of visited events, used for automated scaling of MC samples to data luminosity

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Thu Apr 28 13:28:10 CEST 2011
// $Id: EventCounter.cc,v 1.1 2011/04/28 12:34:05 hauk Exp $
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

#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"

#include "ZmumuAnalysis/Utils/interface/eventWeight.h"

#include "TH1.h"
//
// class declaration
//

class EventCounter : public edm::EDAnalyzer {
   public:
      explicit EventCounter(const edm::ParameterSet&);
      ~EventCounter();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      
      const edm::ParameterSet parameterSet_;
      
      TH1* EventCount;
      TH1* EventCountWeighted;
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
EventCounter::EventCounter(const edm::ParameterSet& iConfig):
parameterSet_(iConfig), 
EventCount(0), EventCountWeighted(0)
{
}


EventCounter::~EventCounter()
{
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
EventCounter::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // Get event weight
  const  edm::InputTag eventWeightSource(parameterSet_.getParameter<edm::InputTag>("eventWeightSource"));
  const double eventWeight = Weights::eventWeight(iEvent, eventWeightSource);
  
  EventCount->SetBinContent(1, EventCount->GetBinContent(1) + 1.);
  EventCountWeighted->SetBinContent(1, EventCount->GetBinContent(1) + eventWeight);
}


// ------------ method called once each job just before starting event loop  ------------
void 
EventCounter::beginJob(){
  edm::Service<TFileService> fileService;

  //TFileDirectory dirEvt = fileService->mkdir("EventCounts");
  TFileDirectory dirEvt(*fileService);
  
  EventCount = dirEvt.make<TH1F>("h_eventCount","Event counts;;# events",1,0,1);
  EventCountWeighted = dirEvt.make<TH1F>("h_eventCountWeighted","Event counts [weighted];;# events [weighted]",1,0,1);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
EventCounter::endJob(){
}

//define this as a plug-in
DEFINE_FWK_MODULE(EventCounter);
