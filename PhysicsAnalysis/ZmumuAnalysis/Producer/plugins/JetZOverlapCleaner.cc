// -*- C++ -*-
//
// Package:    JetZOverlapCleaner
// Class:      JetZOverlapCleaner
// 
/**\class JetZOverlapCleaner JetZOverlapCleaner.cc ZmumuAnalysis/Producer/plugins/JetZOverlapCleaner.cc

 Description: Checks for overlaps between all jets and both muons from the Z

 Implementation:
     Based on PAT objects
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Thu May  5 15:11:28 CEST 2011
// $Id: JetZOverlapCleaner.cc,v 1.1 2011/05/05 14:49:39 hauk Exp $
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

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"

#include "DataFormats/Math/interface/deltaR.h"


//
// class declaration
//

class JetZOverlapCleaner : public edm::EDProducer {
   public:
      explicit JetZOverlapCleaner(const edm::ParameterSet&);
      ~JetZOverlapCleaner();

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
JetZOverlapCleaner::JetZOverlapCleaner(const edm::ParameterSet& iConfig):
parameterSet_(iConfig)
{
  // Register the pat::Jet Collection for production
  produces<std::vector<pat::Jet> >();
  // Can also be associated with a label
  //produces<std::vector<pat::Jet> >("noZOverlap");
}


JetZOverlapCleaner::~JetZOverlapCleaner()
{
}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
JetZOverlapCleaner::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // Get handle on input jet collection
  const edm::InputTag jetSource(parameterSet_.getParameter<edm::InputTag>("jetSource"));
  edm::Handle<pat::JetCollection> jets;
  iEvent.getByLabel(jetSource, jets);
  
  // Prepare collection for the output via auto_ptr
  std::auto_ptr<pat::JetCollection> output(new pat::JetCollection(*jets));
  
  // Get handle on di-muon collection
  const edm::InputTag dimuonSource(parameterSet_.getParameter<edm::InputTag>("dimuonSource"));
  edm::Handle<reco::CandidateView> diMuons;
  iEvent.getByLabel(dimuonSource, diMuons);
  
  // Loop over dimuons and jets to check for geometrical overlap in deltaR
  const double deltaRMin(parameterSet_.getParameter<double>("deltaRMin"));
  pat::JetCollection::const_iterator i_jet;
  for(i_jet = jets->begin(); i_jet != jets->end(); ++i_jet){
    bool hasNoOverlap(true);
    reco::CandidateView::const_iterator i_cand;
    for(i_cand = diMuons->begin(); i_cand != diMuons->end(); ++i_cand){
      const reco::Candidate& diMuon = *i_cand;
      
      const reco::Candidate* daughter1 = diMuon.daughter(0);
      const reco::Candidate* daughter2 = diMuon.daughter(1);

      const double deltaR_1(reco::deltaR(*i_jet, *daughter1));
      const double deltaR_2(reco::deltaR(*i_jet, *daughter2));
      //std::cout<<"\n\t\tDeltaR of both muons "<<deltaR_1<<" , "<<deltaR_2<<"\n";
      if(deltaR_1<deltaRMin || deltaR_2<deltaRMin){
        hasNoOverlap = false;
	break;
      }
    }
    if(!hasNoOverlap)output->pop_back();
  }
  iEvent.put(output);
}

// ------------ method called once each job just before starting event loop  ------------
void 
JetZOverlapCleaner::beginJob(){
}

// ------------ method called once each job just after ending the event loop  ------------
void 
JetZOverlapCleaner::endJob(){
}

//define this as a plug-in
DEFINE_FWK_MODULE(JetZOverlapCleaner);
