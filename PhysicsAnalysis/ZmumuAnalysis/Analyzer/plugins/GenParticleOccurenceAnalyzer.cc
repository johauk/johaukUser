// -*- C++ -*-
//
// Package:    GenParticleOccurenceAnalyzer
// Class:      GenParticleOccurenceAnalyzer
// 
/**\class GenParticleOccurenceAnalyzer GenParticleOccurenceAnalyzer.cc ZmumuAnalysis/Analyzer/plugins/GenParticleOccurenceAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Thu Oct 28 16:25:59 CEST 2010
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

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"
#include "TH1.h"

//
// class declaration
//

class GenParticleOccurenceAnalyzer : public edm::EDAnalyzer {
   public:
      explicit GenParticleOccurenceAnalyzer(const edm::ParameterSet&);
      ~GenParticleOccurenceAnalyzer();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      const edm::ParameterSet parameterSet_;
      
      TH1 *ParticleOccurence;
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
GenParticleOccurenceAnalyzer::GenParticleOccurenceAnalyzer(const edm::ParameterSet& iConfig):
parameterSet_(iConfig),
ParticleOccurence(0)
{
}


GenParticleOccurenceAnalyzer::~GenParticleOccurenceAnalyzer()
{
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
GenParticleOccurenceAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  const edm::InputTag inputTag(parameterSet_.getParameter<edm::InputTag>("src"));
  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(inputTag, genParticles);
  
  const std::vector<int> v_particleOccurence(parameterSet_.getParameter<std::vector<int> >("particleOccurence"));
  unsigned int nParticleOccurence(0);
  
  for(reco::GenParticleCollection::const_iterator i_genPart = genParticles->begin(); i_genPart != genParticles->end(); ++i_genPart) {
    for(std::vector<int>::const_iterator i_particleOccurence=v_particleOccurence.begin(); i_particleOccurence!=v_particleOccurence.end(); ++i_particleOccurence){
      if(std::fabs(i_genPart->pdgId())==*i_particleOccurence){
        //std::cout<<"\n\tStatus "<<i_genPart->status()<<"\n";
	//std::cout<<"\tDaughters "<<i_genPart->numberOfDaughters()<<" , ID of first is "<<i_genPart->daughter(0)->pdgId();
	//std::cout<<" , and has daughters "<<i_genPart->daughter(0)->numberOfDaughters()<<" , and has mothers "<<i_genPart->daughter(0)->numberOfMothers()<<"\n";
	//std::cout<<"\tMothers "<<i_genPart->numberOfMothers()<<" , ID of first is "<<i_genPart->mother(0)->pdgId()<<"\n";
        ++nParticleOccurence;
	break;
      }
    }
  }
  
  ParticleOccurence->Fill(nParticleOccurence);
}


// ------------ method called once each job just before starting event loop  ------------
void 
GenParticleOccurenceAnalyzer::beginJob()
{
  edm::Service<TFileService> fileService;
  TFileDirectory dirParticle = fileService->mkdir("ParticleOccurence");
  ParticleOccurence = dirParticle.make<TH1F>("h_partOccurence","Occurence of required particles;# particles;# events",20,0,20);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GenParticleOccurenceAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(GenParticleOccurenceAnalyzer);
