// -*- C++ -*-
//
// Package:    JetIdFunctorSelector
// Class:      JetIdFunctorSelector
// 
/**\class JetIdFunctorSelector JetIdFunctorSelector.cc ZmumuAnalysis/Producer/plugins/JetIdFunctorSelector.cc

 Description: Select jets fulfilling a specific set of ID requirements via the JetIDSelectionFunctor

 Implementation:
     Based on PAT objects
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Fri May 13 22:40:48 CEST 2011
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

#include "DataFormats/PatCandidates/interface/Jet.h"

#include "PhysicsTools/SelectorUtils/interface/JetIDSelectionFunctor.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"

#include "FWCore/Utilities/interface/EDMException.h"

//
// class declaration
//

class JetIdFunctorSelector : public edm::EDProducer {
   public:
      explicit JetIdFunctorSelector(const edm::ParameterSet&);
      ~JetIdFunctorSelector();

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
      // given jet type: CALO, JPT or PF
      const std::string type_;
      // version of the selection criteria to be used
      const std::string version_;
      // selection quality to be used
      const std::string quality_;
      
      JetIDSelectionFunctor::Version_t version;
      JetIDSelectionFunctor::Quality_t quality;
  
      PFJetIDSelectionFunctor::Version_t versionPF;
      PFJetIDSelectionFunctor::Quality_t qualityPF;
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
JetIdFunctorSelector::JetIdFunctorSelector(const edm::ParameterSet& iConfig):
parameterSet_(iConfig),
type_(parameterSet_.getParameter<std::string>("jetType")),
version_(parameterSet_.getParameter<std::string>("version")),
quality_(parameterSet_.getParameter<std::string>("quality"))
{
  produces<std::vector<pat::Jet> >();
}


JetIdFunctorSelector::~JetIdFunctorSelector()
{
}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
JetIdFunctorSelector::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // Get handle on input jet collection
  const edm::InputTag jetSource(parameterSet_.getParameter<edm::InputTag>("jetSource"));
  edm::Handle<edm::View<pat::Jet> > jets; 
  iEvent.getByLabel(jetSource, jets);
  std::auto_ptr< std::vector<pat::Jet> > outputJets(new std::vector<pat::Jet>);
  
  
  if(type_=="CALO" || type_=="JPT"){
    // create selection functor
    JetIDSelectionFunctor jetIDFunctor(version,quality);
    pat::strbitset ret = jetIDFunctor.getBitTemplate();
    // loop over inut jets
    for ( edm::View<pat::Jet>::const_iterator jet = jets->begin();jet != jets->end(); ++jet ) {      
      ret.set(false);
      bool passed = jetIDFunctor( *jet, ret );
      // append jets fulfilling selection criteria to output collection
      if(passed) outputJets->push_back(*jet);
    }
  }
  else if(type_=="PF"){
    // create selection functor
    PFJetIDSelectionFunctor jetIDFunctor(versionPF,qualityPF);
    pat::strbitset ret = jetIDFunctor.getBitTemplate();
    // loop over inut jets
    for ( edm::View<pat::Jet>::const_iterator jet = jets->begin();jet != jets->end(); ++jet ) {      
      ret.set(false);
      bool passed = jetIDFunctor( *jet, ret );
      // append jets fulfilling selection criteria to output collection
      if(passed) outputJets->push_back(*jet);
    }
  }
  
  iEvent.put(outputJets);
}

// ------------ method called once each job just before starting event loop  ------------
void 
JetIdFunctorSelector::beginJob()
{
  if(type_=="CALO" || type_=="JPT"){
    if      ( quality_ == "MINIMAL" )   quality = JetIDSelectionFunctor::MINIMAL;
    else if ( quality_ == "LOOSE_AOD" ) quality = JetIDSelectionFunctor::LOOSE_AOD;
    else if ( quality_ == "LOOSE" )     quality = JetIDSelectionFunctor::LOOSE;
    else if ( quality_ == "TIGHT" )     quality = JetIDSelectionFunctor::TIGHT;
    else       
      throw edm::Exception( edm::errors::Configuration, "Expect quality to be one of MINIMAL, LOOSE_AOD, LOOSE,TIGHT\n");

    if      ( version_ == "CRAFT08" ) version = JetIDSelectionFunctor::CRAFT08;
    else if ( version_ == "PURE09"  ) version = JetIDSelectionFunctor::PURE09;  
    else if ( version_ == "DQM09"   ) version = JetIDSelectionFunctor::DQM09;    
    else {
      throw edm::Exception( edm::errors::Configuration, "Expect version to be one of CRAFT08, PURE09, DQM09\n");
    }
  }
  else if(type_=="PF"){
    if      ( quality_ == "LOOSE" )     qualityPF = PFJetIDSelectionFunctor::LOOSE;
    else if ( quality_ == "TIGHT" )     qualityPF = PFJetIDSelectionFunctor::TIGHT;
    else       
      throw edm::Exception( edm::errors::Configuration, "Expect quality to be one of MINIMAL, LOOSE_AOD, LOOSE,TIGHT\n");

    if      ( version_ == "FIRSTDATA" ) versionPF = PFJetIDSelectionFunctor::FIRSTDATA; 
    else {
      throw edm::Exception( edm::errors::Configuration, "Expect version to be FIRSTDATA\n");
    }  
  }
  else throw edm::Exception( edm::errors::Configuration, "Unknown jet type specified\n");
}

// ------------ method called once each job just after ending the event loop  ------------
void 
JetIdFunctorSelector::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
JetIdFunctorSelector::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
JetIdFunctorSelector::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
JetIdFunctorSelector::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
JetIdFunctorSelector::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
JetIdFunctorSelector::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(JetIdFunctorSelector);
