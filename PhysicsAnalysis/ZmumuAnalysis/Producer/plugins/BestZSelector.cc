// -*- C++ -*-
//
// Package:    BestZSelector
// Class:      BestZSelector
// 
/**\class BestZSelector BestZSelector.cc ZmumuAnalysis/Producer/plugins/BestZSelector.cc

 Description: Selects from all dimuons the best one, depending on criterion

 Implementation:
     Based on RECO objects
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Fri May 13 21:04:25 CEST 2011
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

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"

#include "DataFormats/Common/interface/CloneTrait.h"

#include "FWCore/Utilities/interface/EDMException.h"

//
// class declaration
//

class BestZSelector : public edm::EDProducer {
   public:
      explicit BestZSelector(const edm::ParameterSet&);
      ~BestZSelector();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void endRun(edm::Run&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      
      bool isBetterByZMass(const reco::Candidate& dimuon, const reco::Candidate&)const;
      
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
BestZSelector::BestZSelector(const edm::ParameterSet& iConfig):
parameterSet_(iConfig)
{
  produces<reco::CandidateCollection>();
}


BestZSelector::~BestZSelector()
{
}


//
// member functions
//


bool
BestZSelector::isBetterByZMass(const reco::Candidate& newDimuon, const reco::Candidate& oldDimuon)const{
  const double nominalZMass(91.1876);
  const double newDifference(newDimuon.mass() - nominalZMass);
  const double oldDifference(oldDimuon.mass() - nominalZMass);
  if(std::abs(newDifference) < std::abs(oldDifference))return true;
  else return false;
}



// ------------ method called to produce the data  ------------
void
BestZSelector::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // Get handle on di-muon collection
  const edm::InputTag dimuonSource(parameterSet_.getParameter<edm::InputTag>("dimuonSource"));
  edm::Handle<reco::CandidateView> dimuons;
  iEvent.getByLabel(dimuonSource, dimuons);
  std::auto_ptr<reco::CandidateCollection> outputDimuon(new reco::CandidateCollection);
  
  //std::cout<<"\n\tNew Event "<<dimuons->size()<<"\n";
  const std::string criterion(parameterSet_.getParameter<std::string>("criterion"));
  const reco::Candidate* bestZ(0);
  reco::CandidateView::const_iterator i_cand;
  for(i_cand = dimuons->begin(); i_cand != dimuons->end(); ++i_cand){
    const reco::Candidate& dimuon = *i_cand;
    
    //std::cout<<"\tMass "<<dimuon.mass()<<"\n";
    if(!bestZ){
      bestZ = &dimuon;
      continue;
    }
    bool isBetterZ(false);
    if(criterion=="zMass"){
      isBetterZ = this->isBetterByZMass(dimuon, *bestZ);
    }
    else throw edm::Exception( edm::errors::Configuration,   
                             "Invalid criterion name: \""+criterion+ 
                             "\"\nCandidates are \"zMass\"\n");
    
    if(isBetterZ)bestZ = &dimuon;
    
  }
  if(bestZ){
    outputDimuon->push_back(edm::clonehelper::CloneTrait<reco::CandidateView>::type::clone(*bestZ));
    //std::cout<<"\tSelected Mass "<<outputDimuon->begin()->mass()<<"\n";
  }
  //std::cout<<"\tAt End "<<outputDimuon->size()<<"\n";
  
  iEvent.put(outputDimuon);
}

// ------------ method called once each job just before starting event loop  ------------
void 
BestZSelector::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
BestZSelector::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
BestZSelector::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
BestZSelector::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
BestZSelector::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
BestZSelector::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
BestZSelector::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(BestZSelector);
