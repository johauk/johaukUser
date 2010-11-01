// -*- C++ -*-
//
// Package:    GenParticleOccurenceFilter
// Class:      GenParticleOccurenceFilter
// 
/**\class GenParticleOccurenceFilter GenParticleOccurenceFilter.cc ZmumuAnalysis/Filter/plugins/GenParticleOccurenceFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Thu Oct 28 16:26:15 CEST 2010
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

#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
//
// class declaration
//

class GenParticleOccurenceFilter : public edm::EDFilter {
   public:
      explicit GenParticleOccurenceFilter(const edm::ParameterSet&);
      ~GenParticleOccurenceFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      
      const edm::ParameterSet parameterSet_;
      
      const std::vector<int> v_particleOccurence_;
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
GenParticleOccurenceFilter::GenParticleOccurenceFilter(const edm::ParameterSet& iConfig):
parameterSet_(iConfig),
v_particleOccurence_(parameterSet_.getParameter<std::vector<int> >("particleOccurence"))
{
}


GenParticleOccurenceFilter::~GenParticleOccurenceFilter()
{
}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
GenParticleOccurenceFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  const edm::InputTag inputTag(parameterSet_.getParameter<edm::InputTag>("src"));
  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(inputTag, genParticles);
  
  bool particleOccurenceFilter(false);
  //unsigned int nParticleOccurence(0);   // not needed if at least one is required
  if(v_particleOccurence_.size()==0)particleOccurenceFilter = true;
  
  
  for(reco::GenParticleCollection::const_iterator i_genPart = genParticles->begin(); i_genPart != genParticles->end(); ++i_genPart){
    for(std::vector<int>::const_iterator i_particleOccurence=v_particleOccurence_.begin(); i_particleOccurence!=v_particleOccurence_.end(); ++i_particleOccurence){
      if(std::fabs(i_genPart->pdgId())==*i_particleOccurence){
	//++nParticleOccurence;
	particleOccurenceFilter = true;
	break;
      }
    }
    // no further information needed if at least one is required and found
    if(particleOccurenceFilter)break;
  }
  // Does required particle occur in full list of all generated particles?
  if(!particleOccurenceFilter)return false;
  
  // All filters fulfilled...
  return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
GenParticleOccurenceFilter::beginJob()
{
  if(v_particleOccurence_.size()==0){
    edm::LogError("Error in cfg file")<<"No particle defined in GenParticleOccurenceFilter, so does not filter at all";
  }
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GenParticleOccurenceFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(GenParticleOccurenceFilter);
