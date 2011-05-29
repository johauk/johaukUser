// -*- C++ -*-
//
// Package:    GenParticleAnalyzer
// Class:      GenParticleAnalyzer
// 
/**\class GenParticleAnalyzer GenParticleAnalyzer.cc ZmumuAnalysis/GenParticleAnalyzer/src/GenParticleAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Sun May 29 20:16:41 CEST 2011
// $Id: GenParticleAnalyzer.cc,v 1.1 2011/05/29 19:31:28 hauk Exp $
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
#include "TH2.h"

//
// class declaration
//

class GenParticleAnalyzer : public edm::EDAnalyzer {
   public:
      explicit GenParticleAnalyzer(const edm::ParameterSet&);
      ~GenParticleAnalyzer();

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
      
      const edm::ParameterSet parameterSet_;
      
      TH1* NParticle;
      
      TH2* NStatus2VsNStatus3;
      
      TH1* Status;
      TH1* NDaughter;
      TH1* NMother;
      TH1* Eta;
      TH1* Phi;
      TH1* Pt;
      TH1* Charge;
      TH1* Mass;
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
GenParticleAnalyzer::GenParticleAnalyzer(const edm::ParameterSet& iConfig):
parameterSet_(iConfig),
NParticle(0), NStatus2VsNStatus3(0),
Status(0), NDaughter(0), NMother(0), Eta(0), Phi(0), Pt(0), Charge(0), Mass(0)
{
}


GenParticleAnalyzer::~GenParticleAnalyzer()
{
}


//
// member functions
//

// ------------ method called for each event  ------------
void
GenParticleAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  const edm::InputTag inputTag(parameterSet_.getParameter<edm::InputTag>("src"));
  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(inputTag, genParticles);
  
  // Event properties
  const unsigned int nParticle(genParticles->size());
  NParticle->Fill(nParticle);
  unsigned int nStatus2(0), nStatus3(0);
  
  reco::GenParticleCollection::const_iterator i_genPart;
  for(i_genPart = genParticles->begin(); i_genPart != genParticles->end(); ++i_genPart) {
    const int status(i_genPart->status());
    const int numberOfDaughters(i_genPart->numberOfDaughters());
    const int numberOfMothers(i_genPart->numberOfMothers());
    const double eta(i_genPart->eta());
    const double phi(i_genPart->phi());
    const double pt(i_genPart->pt());
    const int charge(i_genPart->charge());
    const double mass(i_genPart->mass());
    
    Status->Fill(status);
    NDaughter->Fill(numberOfDaughters);
    NMother->Fill(numberOfMothers);
    Eta->Fill(eta);
    Phi->Fill(phi*180./M_PI);
    Pt->Fill(pt);
    Charge->Fill(charge);
    Mass->Fill(mass);
    
    if(status==2)++nStatus2;
    if(status==3)++nStatus3;
    
    //std::cout<<"\tCharge, mass: "<<charge<<" , "<<mass<<"\n";
  }
  
  NStatus2VsNStatus3->Fill(nStatus2,nStatus3);
}


// ------------ method called once each job just before starting event loop  ------------
void 
GenParticleAnalyzer::beginJob()
{
  edm::Service<TFileService> fileService;
  TFileDirectory dirEvent = fileService->mkdir("EventProperties");
  NParticle = dirEvent.make<TH1F>("h_nParticle","# particles;# particles;# events",20,0,20);
  NStatus2VsNStatus3 = dirEvent.make<TH2F>("h2_nStatus2VsNStatus3","# particles [status2] vs. [status3];# particles [status2];# particles [status3]",10,0,10,10,0,10);
  
  TFileDirectory dirPart = fileService->mkdir("ParticleProperties");
  Status = dirPart.make<TH1F>("h_status","Generator status;status;# events",10,0,10);
  NDaughter = dirPart.make<TH1F>("h_nDaughter","# daughters;# daughters;# events",10,0,10);
  NMother = dirPart.make<TH1F>("h_nMother","# mothers;# mothers;# events",10,0,10);
  Eta = dirPart.make<TH1F>("h_eta","Pseudorapidity #eta;#eta;# events",200,-10,10);
  Phi = dirPart.make<TH1F>("h_phi","Azimuth angle #phi;#phi;# events",380,-190,190);
  Pt = dirPart.make<TH1F>("h_pt","Transverse momentum p_{t};p_{t}  [GeV];# events",200,0,200);
  Charge = dirPart.make<TH1F>("h_charge","Charge q;q  [e];# events",3,-1,2);
  Mass = dirPart.make<TH1F>("h_mass","Mass m;m  [GeV];# particles",100,0,200);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GenParticleAnalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
GenParticleAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
GenParticleAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
GenParticleAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
GenParticleAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
GenParticleAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(GenParticleAnalyzer);
