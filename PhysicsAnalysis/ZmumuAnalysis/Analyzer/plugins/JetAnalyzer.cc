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
// $Id: JetAnalyzer.cc,v 1.4 2011/05/06 11:27:01 hauk Exp $
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
      
      TH1* NJet;
      
      TH1* Eta;
      TH1* Pt;
      TH1* NConstituent;
      TH1* BDiscriminatorTche;
      TH1* BDiscriminatorSvhe;
      
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
Eta(0), Pt(0),
NConstituent(0),
BDiscriminatorTche(0), BDiscriminatorSvhe(0),
ChargedMultiplicity(0),
ChargedHadronEnergyFraction(0), NeutralHadronEnergyFraction(0), ChargedEmEnergyFraction(0), NeutralEmEnergyFraction(0)
{
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
  const edm::InputTag jetSource(parameterSet_.getParameter<edm::InputTag>("jetSource"));
  edm::Handle<pat::JetCollection> jets;
  iEvent.getByLabel(jetSource, jets);
  
  // Event properties
  unsigned int nJet(999);
  nJet = jets->size();
  NJet->Fill(nJet);
  
  // Jet properties
  double eta(-999.), pt(-999.);
  int nConstituent(-1);
  float bDiscriminatorTche(-999.), bDiscriminatorSvhe(-999.);
  int chargedMultiplicity(-1);
  float chargedHadronEnergyFraction(-999.), neutralHadronEnergyFraction(-999.), chargedEmEnergyFraction(-999.), neutralEmEnergyFraction(-999.);
  
  
  //std::cout<<"\n\t\tNEXT EVENT\n";
  
  pat::JetCollection::const_iterator i_jet;
  for(i_jet = jets->begin(); i_jet != jets->end(); ++i_jet){
    
    // Check the names of the JEC levels
    //const std::vector<std::string> availableJecLevels(i_jet->availableJECLevels());
    //std::vector<std::string>::const_iterator i_Jec;
    //for(i_Jec = availableJecLevels.begin(); i_Jec != availableJecLevels.end(); ++i_Jec){
    //  std::cout<<"\tLabels of JEC levels "<<*i_Jec<<"\n";
    //}
    
    //if(nJet>2)std::cout<<"\n\t\tOverlaps? "<<i_jet->hasOverlaps("muons")<<" , "<<i_jet->hasOverlaps("electrons")<<"\n";
    
    // Common jet properties
    eta = i_jet->eta();
    pt = i_jet->pt();
    nConstituent = i_jet->nConstituents();
    
    Eta->Fill(eta);
    Pt->Fill(pt);
    NConstituent->Fill(nConstituent);
    
    // b-tag jet properties
    //std::cout<<"\tTrackCounting "<<i_jet->bDiscriminator("trackCountingHighEffBJetTags")<<" "<<i_jet->tagInfo("trackCountingHighEffBJetTags")<<"\n";
    //if(i_jet->hasTagInfo("trackCountingHighEffBJetTags")){  // not yet implemented in CMSSW_3_8_4
    //if(i_jet->tagInfo("trackCountingHighEffBJetTags")!=0){  // use this line instead, but gives always zero...
      bDiscriminatorTche = i_jet->bDiscriminator("trackCountingHighEffBJetTags");
      BDiscriminatorTche->Fill(bDiscriminatorTche);
    //}
    //std::cout<<"\tSecondaryVertex "<<i_jet->bDiscriminator("simpleSecondaryVertexHighEffBJetTags")<<" "<<i_jet->tagInfo("simpleSecondaryVertexHighEffBJetTags")<<"\n";
    //if(i_jet->hasTagInfo("simpleSecondaryVertexHighEffBJetTags")){  // not yet implemented in CMSSW_3_8_4
    //if(i_jet->tagInfo("simpleSecondaryVertexHighEffBJetTags")!=0){  // use this line instead, but gives always zero...
      bDiscriminatorSvhe = i_jet->bDiscriminator("simpleSecondaryVertexHighEffBJetTags");
      BDiscriminatorSvhe->Fill(bDiscriminatorSvhe);
    //}
    
    // jet-algorithm specific properties
    if(i_jet->isPFJet() || i_jet->isJPTJet()){
      chargedMultiplicity = i_jet->chargedMultiplicity();
      chargedHadronEnergyFraction = i_jet->chargedHadronEnergyFraction();
      neutralHadronEnergyFraction = i_jet->neutralHadronEnergyFraction();
      chargedEmEnergyFraction = i_jet->chargedEmEnergyFraction();
      neutralEmEnergyFraction = i_jet->neutralEmEnergyFraction();
      
      ChargedMultiplicity->Fill(chargedMultiplicity);
      ChargedHadronEnergyFraction->Fill(chargedHadronEnergyFraction);
      NeutralHadronEnergyFraction->Fill(neutralHadronEnergyFraction);
      ChargedEmEnergyFraction->Fill(chargedEmEnergyFraction);
      NeutralEmEnergyFraction->Fill(neutralEmEnergyFraction);
    }
  }
}


// ------------ method called once each job just before starting event loop  ------------
void 
JetAnalyzer::beginJob()
{
  edm::Service<TFileService> fileService;
  
  TFileDirectory dirEvent = fileService->mkdir("EventProperties");
  NJet = dirEvent.make<TH1F>("h_nJet","# jets;# jets; # events",20,0,20);
  
  TFileDirectory dirJet = fileService->mkdir("JetProperties");
  Eta = dirJet.make<TH1F>("h_eta","pseudorapidity #eta;#eta;# jets",60,-3,3);
  Pt = dirJet.make<TH1F>("h_pt","transverse momentum p_{t};p_{t};# jets",100,0,200);
  NConstituent = dirJet.make<TH1F>("h_nConstituent","# constituents;# constituents;# jets",40,0,40);
  BDiscriminatorTche = dirJet.make<TH1F>("h_bDiscriminatorTche","b discriminator trackCountingHighEff d;d;# jets",80,-10,30);
  BDiscriminatorSvhe = dirJet.make<TH1F>("h_bDiscriminatorSvhe","b discriminator simpleSecondaryVertexHighEff d;d;# jets",60,-1,14);
  
  ChargedMultiplicity = dirJet.make<TH1F>("h_chargedMult","Charged multiplicity;# tracks;# jets",20,0,20);
  ChargedHadronEnergyFraction = dirJet.make<TH1F>("h_chargedHadFrac","Charged hadron energy fraction f_{h}^{#pm};f_{h}^{#pm};# jets",110,-0.05,1.05);
  NeutralHadronEnergyFraction = dirJet.make<TH1F>("h_neutralHadFrac","Neutral hadron energy fraction f_{h}^{0};f_{h}^{0};# jets",110,-0.05,1.05);
  ChargedEmEnergyFraction = dirJet.make<TH1F>("h_chargedEmFrac","Charged elmagn. energy fraction f_{em}^{#pm};f_{em}^{#pm};# jets",110,-0.05,1.05);
  NeutralEmEnergyFraction = dirJet.make<TH1F>("h_neutralEmFrac","Neutral elmagn. energy fraction f_{em}^{0};f_{em}^{0};# jets",110,-0.05,1.05);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
JetAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(JetAnalyzer);
