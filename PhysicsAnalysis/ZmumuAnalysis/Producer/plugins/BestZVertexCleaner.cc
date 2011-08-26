	// -*- C++ -*-
//
// Package:    BestZVertexCleaner
// Class:      BestZVertexCleaner
// 
/**\class BestZVertexCleaner BestZVertexCleaner.cc ZmumuAnalysis/Producer/plugins/BestVertexCleaner.cc

 Description: Select Vertex with smallest distance to Z, and require maximum allowed distance

 Implementation:
     Based on Pat objects, but Reco vertex
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Thu May  5 18:06:19 CEST 2011
// $Id: BestZVertexCleaner.cc,v 1.5 2011/05/06 20:32:30 hauk Exp $
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

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
//#include "DataFormats/Candidate/interface/CompositeCandidate.h"
//#include "DataFormats/Candidate/interface/CompositeCandidateFwd.h"
//#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"

#include "DataFormats/Common/interface/CloneTrait.h"

#include "FWCore/Utilities/interface/EDMException.h"

//
// class declaration
//

class BestZVertexCleaner : public edm::EDProducer {
   public:
      explicit BestZVertexCleaner(const edm::ParameterSet&);
      ~BestZVertexCleaner();

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      
      const edm::ParameterSet parameterSet_;
      const std::string product_;
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
BestZVertexCleaner::BestZVertexCleaner(const edm::ParameterSet& iConfig):
parameterSet_(iConfig), product_(parameterSet_.getParameter<std::string>("product"))
{
  if(product_=="dimuon")produces<reco::CandidateCollection>();
  //if(product_=="dimuon")produces<std::vector<reco::CompositeCandidate> >();
  else if(product_=="vertex")produces<reco::VertexCollection>();
  //produces<reco::VertexCollection>("bestZVertex");
  else throw edm::Exception( edm::errors::Configuration,   
                             "Invalid product name: \""+product_+ 
                             "\"\nCandidates are \"dimuon\", \"vertex\"\n");
}


BestZVertexCleaner::~BestZVertexCleaner()
{
}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
BestZVertexCleaner::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
  // Get handle on input vertex collection
  const edm::InputTag vertexSource(parameterSet_.getParameter<edm::InputTag>("vertexSource"));
  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByLabel(vertexSource, vertices);
  //std::auto_ptr<reco::VertexCollection> outputVertex(new reco::VertexCollection(*vertices));
  std::auto_ptr<reco::VertexCollection> outputVertex(new reco::VertexCollection);
  
  // Get handle on di-muon collection
  const edm::InputTag dimuonSource(parameterSet_.getParameter<edm::InputTag>("dimuonSource"));
  //edm::Handle<std::vector<reco::CompositeCandidate> > dimuons;
  //iEvent.getByLabel(dimuonSource, dimuons);
  //std::auto_ptr<std::vector<reco::CompositeCandidate> > outputDimuon(new std::vector<reco::CompositeCandidate>());
  edm::Handle<reco::CandidateView> dimuons;
  iEvent.getByLabel(dimuonSource, dimuons);
  std::auto_ptr<reco::CandidateCollection> outputDimuon(new reco::CandidateCollection);
  
  
  // Loop over Zs and vertices, find best vertex (smallest distance)
  LogDebug("BestZVertexCleaner")<<"New Event "<<dimuons->size()<<" , "<<vertices->size();
  const double deltaZMuMuMax(parameterSet_.getParameter<double>("deltaZMuMuMax"));
  const double deltaZZVertexMax(parameterSet_.getParameter<double>("deltaZZVertexMax"));
  //std::vector<reco::CompositeCandidate>::const_iterator i_cand;
  reco::CandidateView::const_iterator i_cand;
  std::vector<std::pair<const reco::Candidate*,int> > v_zVertexPair;
  for(i_cand = dimuons->begin(); i_cand != dimuons->end(); ++i_cand){
    bool isGoodZ(false);
    //const reco::CompositeCandidate & z = *i_cand;
    //pat::CompositeCandidate dimuon2(z);
    const reco::Candidate& dimuon = *i_cand;
    
    const reco::Candidate* daughter1 = dimuon.daughter(0);
    const reco::Candidate* daughter2 = dimuon.daughter(1);
    
    // First: check for distance between muons
    const double deltaZMuMu(daughter1->vz()-daughter2->vz());
    LogDebug("BestZVertexCleaner")<<"New Z, Muon distance "<<deltaZMuMu;
    if(std::abs(deltaZMuMu)>deltaZMuMuMax)continue;
    
    // Second: check for distance between Z and vertex
    const double vzZ = 0.5*(daughter1->vz()+daughter2->vz());
    
    const reco::Vertex* bestVertex(0);
    int iBestVertex(-99);
    reco::VertexCollection::const_iterator i_vertex;
    int nIter(0);
    for(i_vertex=vertices->begin(); i_vertex!=vertices->end();++i_vertex, ++nIter){
      const double deltaZ = vzZ - i_vertex->z();
      if(!bestVertex){bestVertex = &*i_vertex;iBestVertex = nIter;}
      else{
        const double lastDeltaZ = vzZ - bestVertex->z();
	if(std::abs(deltaZ)<std::abs(lastDeltaZ)){bestVertex = &*i_vertex;iBestVertex = nIter;}
      }
    }
    if(!bestVertex)continue;
    const double deltaZ1(daughter1->vz() - bestVertex->z());
    const double deltaZ2(daughter2->vz() - bestVertex->z());
    LogDebug("BestZVertexCleaner")<<"New Z, Best Vertex "<<deltaZ1<<" , "<<deltaZ2;
    if(std::abs(deltaZ1) < deltaZZVertexMax && std::abs(deltaZ2) < deltaZZVertexMax){
      std::pair<const reco::Candidate*,int> zVertexPair(&*i_cand,iBestVertex);
      v_zVertexPair.push_back(zVertexPair);
      isGoodZ = true;
    }
    if(isGoodZ){
      //outputDimuon->push_back(z);
      outputDimuon->push_back(edm::clonehelper::CloneTrait<reco::CandidateView>::type::clone(dimuon));
      bool vertexDublicate(false);
      std::vector<std::pair<const reco::Candidate*,int> >::const_iterator i_zVertexPair;
      for(i_zVertexPair=v_zVertexPair.begin(); i_zVertexPair!=(--v_zVertexPair.end());++i_zVertexPair){
	if(iBestVertex==i_zVertexPair->second){vertexDublicate = true; break;}
      }
      if(!vertexDublicate)outputVertex->push_back((*vertices)[iBestVertex]);
    }
  }
  
  LogDebug("BestZVertexCleaner")<<"At End "<<outputDimuon->size()<<" , "<<outputVertex->size();
  
  
  if(product_=="vertex")iEvent.put(outputVertex);
  else if(product_=="dimuon")iEvent.put(outputDimuon);
}

// ------------ method called once each job just before starting event loop  ------------
void 
BestZVertexCleaner::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
BestZVertexCleaner::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(BestZVertexCleaner);
