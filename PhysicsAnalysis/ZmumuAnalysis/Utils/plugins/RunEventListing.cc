// -*- C++ -*-
//
// Package:    RunEventListing
// Class:      RunEventListing
// 
/**\class RunEventListing RunEventListing.cc ZmumuAnalysis/Utils/plugins/RunEventListing.cc

 Description: Class to print list of processed event (and run) numbers

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Sat May 14 21:44:38 CEST 2011
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
//
// class declaration
//

class RunEventListing : public edm::EDAnalyzer {
   public:
      explicit RunEventListing(const edm::ParameterSet&);
      ~RunEventListing();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------
      
      typedef std::vector<unsigned int> Events;
      typedef std::map<unsigned int, Events> LumiEvents;
      typedef std::map<unsigned int, LumiEvents> RunLumiEvents;
      
      LumiEvents lumiEvents_;
      RunLumiEvents runLumiEvents_;
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
RunEventListing::RunEventListing(const edm::ParameterSet& iConfig)
{
}


RunEventListing::~RunEventListing()
{
}


//
// member functions
//

// ------------ method called for each event  ------------
void
RunEventListing::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  const unsigned int run(iEvent.id().run());
  const unsigned int lumiBlock(iEvent.id().luminosityBlock());
  const unsigned int event(iEvent.id().event());
  
  runLumiEvents_[run][lumiBlock].push_back(event);
}


// ------------ method called once each job just before starting event loop  ------------
void 
RunEventListing::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RunEventListing::endJob() 
{
  std::cout<<"\n\tLETS SEE ...\n\n";
  RunLumiEvents::iterator i_run;
  for(i_run = runLumiEvents_.begin(); i_run != runLumiEvents_.end(); ++i_run){
    const unsigned int run(i_run->first);
    LumiEvents& lumiEvents(i_run->second);
    LumiEvents::iterator i_lumi;
    for(i_lumi = lumiEvents.begin(); i_lumi != lumiEvents.end(); ++i_lumi){
      const unsigned int lumi(i_lumi->first);
      Events& events(i_lumi->second);
      std::sort(events.begin(), events.end());
      Events::iterator i_event;
      for(i_event = events.begin(); i_event != events.end(); ++i_event){
        const unsigned int event(*i_event);
	std::cout<<run<<":"<<lumi<<":"<<event<<"\n";
      }
    }
  }
  
}


// ------------ method called when starting to processes a run  ------------
void 
RunEventListing::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
RunEventListing::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
RunEventListing::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
RunEventListing::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
RunEventListing::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(RunEventListing);
