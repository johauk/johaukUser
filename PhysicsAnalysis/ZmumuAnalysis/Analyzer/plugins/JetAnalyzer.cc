// -*- C++ -*-
//
// Package:    JetAnalyzer
// Class:      JetAnalyzer
// 
/**\class JetAnalyzer JetAnalyzer.cc ZmumuAnalysis/Analyzer/plugins/JetAnalyzer.cc

 Description: Plotter for jet distributions

 Implementation:
     Based on reconstructed PAT objects
     Caveat: Some methods work only for ParticleFlow Jets, so corresponding plots are not filled when using others
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Wed Oct 20 16:37:05 CEST 2010
// $Id: JetAnalyzer.cc,v 1.7 2011/08/04 11:42:07 hauk Exp $
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
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"

#include "ZmumuAnalysis/Utils/interface/eventWeight.h"

#include "TH1.h"
//
// class declaration
//

class JetAnalyzer : public edm::EDAnalyzer {
   public:
      explicit JetAnalyzer(const edm::ParameterSet&);
      ~JetAnalyzer();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      

      const edm::ParameterSet parameterSet_;
      
      enum WhichHists{major, basic, veryBasic};
      WhichHists whichHists_;
      
      TH1* NJet;
      
      TH1* Phi;
      TH1* Eta;
      TH1* Pt;
      TH1* NConstituent;
      TH1* BDiscriminatorSsvHe;
      TH1* BDiscriminatorSsvHp;
      
      TH1* ChargedMultiplicity;
      TH1* ChargedHadronEnergyFraction;
      TH1* NeutralHadronEnergyFraction;
      TH1* ChargedEmEnergyFraction;
      TH1* NeutralEmEnergyFraction;
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
JetAnalyzer::JetAnalyzer(const edm::ParameterSet& iConfig):
parameterSet_(iConfig),
NJet(0),
Phi(0), Eta(0), Pt(0),
NConstituent(0),
BDiscriminatorSsvHe(0), BDiscriminatorSsvHp(0),
ChargedMultiplicity(0),
ChargedHadronEnergyFraction(0), NeutralHadronEnergyFraction(0), ChargedEmEnergyFraction(0), NeutralEmEnergyFraction(0)
{
  const std::string whichHists(parameterSet_.getParameter<std::string>("whichHists"));
  if(whichHists=="major")whichHists_ = major;
  else if(whichHists=="basic")whichHists_ = basic;
  else throw edm::Exception( edm::errors::Configuration,   
                             "Invalid parameter for whichHists: \""+whichHists+ 
                             "\"\nCandidates are \"major\", \"basic\"\n");
}


JetAnalyzer::~JetAnalyzer()
{
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
JetAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // Get event weight
  const  edm::InputTag eventWeightSource(parameterSet_.getParameter<edm::InputTag>("eventWeightSource"));
  const double eventWeight = Weights::eventWeight(iEvent, eventWeightSource);
  
  const edm::InputTag jetSource(parameterSet_.getParameter<edm::InputTag>("jetSource"));
  edm::Handle<pat::JetCollection> jets;
  iEvent.getByLabel(jetSource, jets);
  
  // Event properties
  unsigned int nJet(999);
  nJet = jets->size();
  NJet->Fill(nJet, eventWeight);
  
  // Jet properties
  //std::cout<<"\n\t\tNEXT EVENT\n";
  pat::JetCollection::const_iterator i_jet;
  for(i_jet = jets->begin(); i_jet != jets->end(); ++i_jet){
    
    // Check the names of the JEC levels
    //const std::vector<std::string> availableJecLevels(i_jet->availableJECLevels());
    //std::vector<std::string>::const_iterator i_Jec;
    //for(i_Jec = availableJecLevels.begin(); i_Jec != availableJecLevels.end(); ++i_Jec){
    //  std::cout<<"\tLabels of JEC levels "<<*i_Jec<<"\n";
    //}
    
    const double phi = i_jet->phi();
    const double eta = i_jet->eta();
    const double pt = i_jet->pt();
    Phi->Fill(phi*180./M_PI, eventWeight);
    Eta->Fill(eta, eventWeight);
    Pt->Fill(pt, eventWeight);
    
    // b-tag jet properties
    const float bDiscriminatorSsvHe = i_jet->bDiscriminator("simpleSecondaryVertexHighEffBJetTags");
    const float bDiscriminatorSsvHp = i_jet->bDiscriminator("simpleSecondaryVertexHighPurBJetTags");
    BDiscriminatorSsvHe->Fill(bDiscriminatorSsvHe, eventWeight);
    BDiscriminatorSsvHp->Fill(bDiscriminatorSsvHp, eventWeight);
    
    if(whichHists_!=major){
      const int nConstituent = i_jet->nConstituents();
      NConstituent->Fill(nConstituent, eventWeight);
      
      // jet-algorithm specific properties
      if(i_jet->isPFJet() || i_jet->isJPTJet()){
        const int chargedMultiplicity = i_jet->chargedMultiplicity();
        const float chargedHadronEnergyFraction = i_jet->chargedHadronEnergyFraction();
        const float neutralHadronEnergyFraction = i_jet->neutralHadronEnergyFraction();
        const float chargedEmEnergyFraction = i_jet->chargedEmEnergyFraction();
        const float neutralEmEnergyFraction = i_jet->neutralEmEnergyFraction();
        
        ChargedMultiplicity->Fill(chargedMultiplicity, eventWeight);
        ChargedHadronEnergyFraction->Fill(chargedHadronEnergyFraction, eventWeight);
        NeutralHadronEnergyFraction->Fill(neutralHadronEnergyFraction, eventWeight);
        ChargedEmEnergyFraction->Fill(chargedEmEnergyFraction, eventWeight);
        NeutralEmEnergyFraction->Fill(neutralEmEnergyFraction, eventWeight);
      }
    }
  }
}


// ------------ method called once each job just before starting event loop  ------------
void 
JetAnalyzer::beginJob()
{
  int nJetMax(7);
  
  if(whichHists_==basic){
    nJetMax = 20;
  }
  
  edm::Service<TFileService> fileService;
  
  TFileDirectory dirEvent = fileService->mkdir("EventProperties");
  NJet = dirEvent.make<TH1F>("h_nJet","# jets;# jets; # events",nJetMax,0,nJetMax);
  
  TFileDirectory dirJet = fileService->mkdir("JetProperties");
  if(whichHists_==basic){
    NConstituent = dirJet.make<TH1F>("h_nConstituent","# constituents;# constituents;# jets",40,0,40);
    
    ChargedMultiplicity = dirJet.make<TH1F>("h_chargedMult","Charged multiplicity;# tracks;# jets",20,0,20);
    ChargedHadronEnergyFraction = dirJet.make<TH1F>("h_chargedHadFrac","Charged hadron energy fraction f_{h}^{#pm};f_{h}^{#pm};# jets",110,-0.05,1.05);
    NeutralHadronEnergyFraction = dirJet.make<TH1F>("h_neutralHadFrac","Neutral hadron energy fraction f_{h}^{0};f_{h}^{0};# jets",110,-0.05,1.05);
    ChargedEmEnergyFraction = dirJet.make<TH1F>("h_chargedEmFrac","Charged elmagn. energy fraction f_{em}^{#pm};f_{em}^{#pm};# jets",110,-0.05,1.05);
    NeutralEmEnergyFraction = dirJet.make<TH1F>("h_neutralEmFrac","Neutral elmagn. energy fraction f_{em}^{0};f_{em}^{0};# jets",110,-0.05,1.05);
  }
  
  BDiscriminatorSsvHe = dirJet.make<TH1F>("h_bDiscriminatorSsvHe","b discriminator simpleSecondaryVertexHighEff d;d;# jets",80,-1,14);
  BDiscriminatorSsvHp = dirJet.make<TH1F>("h_bDiscriminatorSsvHp","b discriminator simpleSecondaryVertexHighPur d;d;# jets",60,-1,14);
  
  Phi = dirJet.make<TH1F>("h_phi","Azimuth angle #phi;#phi;# jets",90,-180,180);
  Eta = dirJet.make<TH1F>("h_eta","pseudorapidity #eta;#eta;# jets",60,-3,3);
  Pt = dirJet.make<TH1F>("h_pt","transverse momentum p_{t};p_{t};# jets",100,0,200);
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
JetAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(JetAnalyzer);
