// -*- C++ -*-
//
// Package:    VertexAnalyzer
// Class:      VertexAnalyzer
// 
/**\class VertexAnalyzer VertexAnalyzer.cc ZmumuAnalysis/Analyzer/plugins/VertexAnalyzer.cc

 Description: Plotter for Vertex quantities

 Implementation:
     Based on reco objects
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Fri May 13 18:24:03 CEST 2011
// $Id: VertexAnalyzer.cc,v 1.1 2011/05/13 20:28:04 hauk Exp $
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

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"

#include "TH1.h"

#include "ZmumuAnalysis/Utils/interface/eventWeight.h"
//
// class declaration
//

class VertexAnalyzer : public edm::EDAnalyzer {
   public:
      explicit VertexAnalyzer(const edm::ParameterSet&);
      ~VertexAnalyzer();

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
      
      TH1* NVertex;
      
      TH1* IsFake;
      TH1* NTracks;
      TH1* Chi2;
      TH1* Ndof;
      TH1* NormalizedChi2;
      TH1* Rho;
      TH1* X;
      TH1* Y;
      TH1* Z;
      TH1* XError;
      TH1* YError;
      TH1* ZError;
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
VertexAnalyzer::VertexAnalyzer(const edm::ParameterSet& iConfig):
parameterSet_(iConfig),
NVertex(0), IsFake(0), NTracks(0), Chi2(0), Ndof(0), NormalizedChi2(0),
Rho(0), X(0), Y(0), Z(0), XError(0), YError(0), ZError(0)
{
}


VertexAnalyzer::~VertexAnalyzer()
{
}


//
// member functions
//

// ------------ method called for each event  ------------
void
VertexAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // Get event weight
  const  edm::InputTag eventWeightSource(parameterSet_.getParameter<edm::InputTag>("eventWeightSource"));
  const double eventWeight = Weights::eventWeight(iEvent, eventWeightSource);
  
  // Get handle on input vertex collection
  const edm::InputTag vertexSource(parameterSet_.getParameter<edm::InputTag>("vertexSource"));
  edm::Handle<reco::VertexCollection> vertices;
  iEvent.getByLabel(vertexSource, vertices);
  
  const unsigned int nVertex(vertices->size());
  NVertex->Fill(nVertex, eventWeight);
  
  reco::VertexCollection::const_iterator i_vertex;
  for(i_vertex=vertices->begin(); i_vertex!=vertices->end(); ++i_vertex){
    const bool isFake(i_vertex->isFake());
    const double nTracks(i_vertex->tracksSize());
    const double chi2(i_vertex->chi2());
    const double ndof(i_vertex->ndof());
    const double normalizedChi2(i_vertex->normalizedChi2());
    const double rho(i_vertex->position().Rho());
    const double x(i_vertex->x());
    const double y(i_vertex->y());
    const double z(i_vertex->z());
    const double xError(i_vertex->xError());
    const double yError(i_vertex->yError());
    const double zError(i_vertex->zError());
    
    IsFake->Fill(isFake, eventWeight);
    NTracks->Fill(nTracks, eventWeight);
    Chi2->Fill(chi2, eventWeight);
    Ndof->Fill(ndof, eventWeight);
    NormalizedChi2->Fill(normalizedChi2, eventWeight);
    Rho->Fill(rho, eventWeight);
    X->Fill(x, eventWeight);
    Y->Fill(y, eventWeight);
    Z->Fill(z, eventWeight);
    XError->Fill(xError, eventWeight);
    YError->Fill(yError, eventWeight);
    ZError->Fill(zError, eventWeight);
  }
}


// ------------ method called once each job just before starting event loop  ------------
void 
VertexAnalyzer::beginJob()
{
  edm::Service<TFileService> fileService;

  TFileDirectory dirEvent = fileService->mkdir("EventProperties");
  NVertex = dirEvent.make<TH1F>("h_nVertex","# vertices;# vertices;# events",20,0,20);
  
  TFileDirectory dirVertex = fileService->mkdir("VertexProperties");
  IsFake = dirVertex.make<TH1F>("h_isFake","isFake;isFake;# vertices",2,0,2);
  NTracks = dirVertex.make<TH1F>("h_nTracks","# associated tracks;# tracks;# vertices",30,0,30);
  Chi2 = dirVertex.make<TH1F>("h_chi2"," #chi^{2};#chi^{2};# vertices",50,0,50);
  Ndof = dirVertex.make<TH1F>("h_ndof","# degrees of freedom;ndof;# vertices",50,0,50);
  NormalizedChi2 = dirVertex.make<TH1F>("h_norChi2","normalized #chi^{2};#chi^{2}/ndof;# vertices",60,0,20);
  Rho = dirVertex.make<TH1F>("h_rho","Transversal distance #rho;#rho  [cm];# vertices",100,0,5);
  X = dirVertex.make<TH1F>("h_x","Position x;x  [cm];# vertices",100,-2,2);
  Y = dirVertex.make<TH1F>("h_y","Position y;y  [cm];# vertices",100,-2,2);
  Z = dirVertex.make<TH1F>("h_z","Longitudinal position z;z  [cm];# vertices",100,-40,40);
  XError = dirVertex.make<TH1F>("h_xError","Position error #sigma_{x};#sigma_{x}  [cm];# vertices",100,0,5);
  YError = dirVertex.make<TH1F>("h_yError","Position error #sigma_{y};#sigma_{y}  [cm];# vertices",100,0,5);
  ZError = dirVertex.make<TH1F>("h_zError","Position error #sigma_{z};#sigma_{z}  [cm];# vertices",100,0,50);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
VertexAnalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
VertexAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
VertexAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
VertexAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
VertexAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
VertexAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(VertexAnalyzer);
