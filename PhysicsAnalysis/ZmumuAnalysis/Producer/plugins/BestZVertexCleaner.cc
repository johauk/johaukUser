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
// $Id: BestZVertexCleaner.cc,v 1.2 2011/05/06 16:26:28 hauk Exp $
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
#include "DataFormats/PatCandidates/interface/CompositeCandidate.h"

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
  //if(product_=="dimuon")produces<reco::CandidateCollection>();
  if(product_=="dimuon")produces<std::vector<reco::CompositeCandidate> >();
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
/* This is an event example
   //Read 'ExampleData' from the Event
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);

   //Use the ExampleData to create an ExampleData2 which 
   // is put into the Event
   std::auto_ptr<ExampleData2> pOut(new ExampleData2(*pIn));
   iEvent.put(pOut);
*/

/* this is an EventSetup example
   //Read SetupData from the SetupRecord in the EventSetup
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
*/
  // Get handle on input vertex collection
  const edm::InputTag vertexSource(parameterSet_.getParameter<edm::InputTag>("vertexSource"));
  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByLabel(vertexSource, vertices);
  //std::auto_ptr<reco::VertexCollection> outputVertex(new reco::VertexCollection(*vertices));
  std::auto_ptr<reco::VertexCollection> outputVertex(new reco::VertexCollection);
  //std::auto_ptr<std::vector<reco::Vertex> > outputVertex(new std::vector<reco::Vertex>);
  
  // Get handle on di-muon collection
  const edm::InputTag dimuonSource(parameterSet_.getParameter<edm::InputTag>("dimuonSource"));
  //edm::Handle<reco::CandidateView> diMuons;
  edm::Handle<std::vector<reco::CompositeCandidate> > diMuons;
  //edm::Handle<reco::CandidateCollection> diMuons;
  //edm::Handle<std::vector<reco::Candidate> > diMuons;
  iEvent.getByLabel(dimuonSource, diMuons);
  //std::auto_ptr<reco::CandidateView> outputDimuon(new reco::CandidateView(*diMuons));
  std::auto_ptr<std::vector<reco::CompositeCandidate> > outputDimuon(new std::vector<reco::CompositeCandidate>());
  //std::auto_ptr<reco::CandidateCollection> outputDimuon(new reco::CandidateCollection(*diMuons));
  //std::auto_ptr<std::vector<reco::Candidate> > outputDimuon(new std::vector<reco::Candidate>);
  
  // Loop over Zs and vertices, find best vertex (smallest distance)
  LogDebug("BestZVertexCleaner")<<"New Event "<<diMuons->size()<<" , "<<vertices->size();
  const double deltaZMax(parameterSet_.getParameter<double>("deltaZMax"));
  //reco::CandidateView::const_iterator i_cand;
  std::vector<reco::CompositeCandidate>::const_iterator i_cand;
  std::vector<std::pair<const reco::Candidate*,int> > v_zVertexPair;
  for(i_cand = diMuons->begin(); i_cand != diMuons->end(); ++i_cand){
    bool isGoodZ(false);
    const reco::Candidate& diMuon = *i_cand;
    const reco::CompositeCandidate & z = *i_cand;
    pat::CompositeCandidate dimuon2(z);
    
    const reco::Candidate* daughter1 = diMuon.daughter(0);
    const reco::Candidate* daughter2 = diMuon.daughter(1);
    
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
    const double deltaZ1(daughter1->vz() - bestVertex->z());
    const double deltaZ2(daughter2->vz() - bestVertex->z());
    LogDebug("BestZVertexCleaner")<<"New Z, Best Vertex "<<deltaZ1<<" , "<<deltaZ2;
    if(std::abs(deltaZ1) < deltaZMax && std::abs(deltaZ2) < deltaZMax){
      std::pair<const reco::Candidate*,int> zVertexPair(&*i_cand,iBestVertex);
      v_zVertexPair.push_back(zVertexPair);
      isGoodZ = true;
    }
    if(isGoodZ){
      //outputDimuon->push_back((*diMuons)[0]);
      outputDimuon->push_back(z);
      bool vertexDublicate(false);
      std::vector<std::pair<const reco::Candidate*,int> >::const_iterator i_zVertexPair;
      for(i_zVertexPair=v_zVertexPair.begin(); i_zVertexPair!=(--v_zVertexPair.end());++i_zVertexPair){
        //if(&*bestVertex==&*i_vertex){vertexDublicate = true; break;}
	if(iBestVertex==i_zVertexPair->second){vertexDublicate = true; break;}
      }
      if(!vertexDublicate)outputVertex->push_back((*vertices)[iBestVertex]);
    }
  }
  LogDebug("BestZVertexCleaner")<<"At End "<<outputDimuon->size()<<" , "<<outputVertex->size();
  
//  reco::VertexCollection goodVertices;
//  reco::CandidateCollection goodDimuons;
//  std::vector<std::pair<const reco::Candidate*,const reco::Vertex*> >::const_iterator i_zVertexPair;
//  for(i_zVertexPair=v_zVertexPair.begin(); i_zVertexPair!=v_zVertexPair.end(); ++i_zVertexPair){
//    goodDimuons.push_back(*(i_zVertexPair->first));
//    goodVertices.push_back(*(i_zVertexPair->second));
//  }
  
//  if(product_=="dimuon"){
//    iEvent.put(outputDimuon);
//  }
  //if(product_=="vertex")iEvent.put(outputVertex);
  
  //std::auto_ptr<std::vector<reco::Vertex> > outputVertex(new std::vector<reco::Vertex>);
  //if(product_=="dimuon")iEvent.put(outputDimuon);
  if(product_=="vertex")iEvent.put(outputVertex);
  //iEvent.put(product_=="dimuon" ? outputDimuon : outputVertex);
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
