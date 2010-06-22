// -*- C++ -*-
//
// Package:    TriggerFilter
// Class:      TriggerFilter
// 
/**\class TriggerFilter TriggerFilter.cc ZmumuAnalysis/Filter/plugins/TriggerFilter.cc

 Description: Filter for event triggers as given in config file

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Wed Jun  9 11:28:36 CEST 2010
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"

//
// class declaration
//

class TriggerFilter : public edm::EDFilter {
   public:
      explicit TriggerFilter(const edm::ParameterSet&);
      ~TriggerFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
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
TriggerFilter::TriggerFilter(const edm::ParameterSet& iConfig):
parameterSet_(iConfig)
{
}


TriggerFilter::~TriggerFilter()
{
}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
TriggerFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // get handle on collections
  const edm::InputTag triggerResults(parameterSet_.getParameter<edm::InputTag>("triggerResults"));
  edm::Handle<edm::TriggerResults> trigResults;
  iEvent.getByLabel(triggerResults, trigResults);
  if(trigResults.failedToGet()){
    edm::LogError("Problematic Product")<<"Failed to get trigger results, check InputTag in cfg file"
                                        <<"\n...skip filtering of event";
    return false;
  }
  
  bool trigFired(false);
  const unsigned int nTrig(trigResults->size());
  const edm::TriggerNames trigNames = iEvent.triggerNames(*trigResults);
  const std::vector<std::string> hltPaths(parameterSet_.getParameter<std::vector<std::string> >("hltPaths"));
  const unsigned int nTrigPath(hltPaths.size());
  for(size_t iTrig=0; iTrig<nTrig; ++iTrig){
    //std::cout<<"Trigger name: "<<trigNames.triggerName(iTrig)<<"\n";
    if(!trigResults.product()->accept(iTrig))continue;
    for(size_t iTrigPath=0; iTrigPath<nTrigPath; ++iTrigPath){
      if(trigNames.triggerName(iTrig)!=hltPaths[iTrigPath])continue;
      trigFired = true;
      break;
    }
    if(trigFired)break;
  }
  
  return trigFired;
}

// ------------ method called once each job just before starting event loop  ------------
void 
TriggerFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TriggerFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(TriggerFilter);
