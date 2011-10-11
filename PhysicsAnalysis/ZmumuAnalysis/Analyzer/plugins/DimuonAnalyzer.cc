// -*- C++ -*-
//
// Package:    DimuonAnalyzer
// Class:      DimuonAnalyzer
// 
/**\class DimuonAnalyzer DimuonAnalyzer.cc ZmumuAnalysis/Analyzer/plugins/DimuonAnalyzer.cc

 Description: Plotter for combined di-muon distributions

 Implementation:
     Based on reconstructed PAT objects
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Thu May 20 15:47:12 CEST 2010
// $Id: DimuonAnalyzer.cc,v 1.4 2011/09/30 09:39:34 hauk Exp $
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
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "DataFormats/Candidate/interface/CandidateFwd.h"


#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"

#include "FWCore/Utilities/interface/EDMException.h"

#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "ZmumuAnalysis/Utils/interface/eventWeight.h"

#include "TH1.h"
//
// class declaration
//

class DimuonAnalyzer : public edm::EDAnalyzer {
   public:
      explicit DimuonAnalyzer(const edm::ParameterSet&);
      ~DimuonAnalyzer();
      

   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      

      // ----------member data ---------------------------
      
      const edm::ParameterSet parameterSet_;
      
      /// Number of dimuons
      TH1* NDimuon;
      
      /// Properties of the two muons
      TH1F *EtaLow, *EtaHigh, *PtLow, *PtHigh,
           *IsoLow, *IsoHigh;
      
      /// Differences of the two muons
      TH1F *DeltaEta, *DeltaPhi, *DeltaR,
	   *DeltaVz;
      
      /// Properties of reconstructed di-muon particle
      TH1F *DiMass, *DiPt,
	   *DiPhi, *DiY;
      
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
DimuonAnalyzer::DimuonAnalyzer(const edm::ParameterSet& iConfig):
parameterSet_(iConfig),
NDimuon(0),
EtaLow(0), EtaHigh(0), PtLow(0), PtHigh(0),
IsoLow(0), IsoHigh(0),
DeltaEta(0), DeltaPhi(0), DeltaR(0),
DeltaVz(0),
DiMass(0), DiPt(0),
DiPhi(0), DiY(0)
{
}


DimuonAnalyzer::~DimuonAnalyzer()
{
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
DimuonAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // Get event weight
  const  edm::InputTag eventWeightSource(parameterSet_.getParameter<edm::InputTag>("eventWeightSource"));
  const double eventWeight = Weights::eventWeight(iEvent, eventWeightSource);
  
  // get handle on di-muon collection
  const edm::InputTag dimuonSource(parameterSet_.getParameter<edm::InputTag>("dimuonSource"));
  edm::Handle<reco::CandidateView> dimuons;
  iEvent.getByLabel(dimuonSource, dimuons);
  
  // Event properties
  unsigned int nDimuon(999);
  nDimuon = dimuons->size();
  NDimuon->Fill(nDimuon, eventWeight);
  
  // Dimuon properties
  reco::CandidateView::const_iterator i_cand;
  for(i_cand = dimuons->begin(); i_cand != dimuons->end(); ++i_cand){
    const reco::Candidate& dimuon = *i_cand;
    
    const reco::Candidate* daughter1 = dimuon.daughter(0);
    const reco::Candidate* daughter2 = dimuon.daughter(1);
    
    const pat::MuonCollection::const_reference mu1 = dynamic_cast<const pat::Muon&>(*daughter1->masterClone());
    const pat::MuonCollection::const_reference mu2 = dynamic_cast<const pat::Muon&>(*daughter2->masterClone());
    
    // eta and pt
    const double etaLow = std::fabs(mu1.eta())<std::fabs(mu2.eta()) ? mu1.eta() : mu2.eta();
    const double etaHigh = std::fabs(mu1.eta())>std::fabs(mu2.eta()) ? mu1.eta() : mu2.eta();
    const double ptLow = mu1.pt()<mu2.pt() ? mu1.pt() : mu2.pt();
    const double ptHigh = mu1.pt()>mu2.pt() ? mu1.pt() : mu2.pt();
    
    const double iso1 = (mu1.trackIso() + mu1.caloIso())/mu1.pt();
    const double iso2 = (mu2.trackIso() + mu2.caloIso())/mu2.pt();
    const double isoLow = iso1<iso2 ? iso1 : iso2;
    const double isoHigh = iso1>iso2 ? iso1 : iso2;
    
    // eta, phi difference
    const double deltaEta = mu2.eta() - mu1.eta();
    const double deltaPhi = reco::deltaPhi(mu2.phi(),mu1.phi());
    const double deltaR = reco::deltaR(mu1, mu2);
    
    const double deltaVz = mu2.vz() - mu1.vz();
    
    // dimuon invariant mass, pt and rapidity
    //const reco::Candidate::LorentzVector dimuVec = mu1.p4() + mu2.p4();
    const double diMass = dimuon.mass();
    const double diPt = dimuon.pt();
    const double diPhi = dimuon.phi();
    const double diY = dimuon.y();
    
    EtaLow->Fill(etaLow, eventWeight);
    EtaHigh->Fill(etaHigh, eventWeight);
    PtLow->Fill(ptLow, eventWeight);
    PtHigh->Fill(ptHigh, eventWeight);
    IsoLow->Fill(isoLow, eventWeight);
    IsoHigh->Fill(isoHigh, eventWeight);
    DeltaEta->Fill(deltaEta, eventWeight);
    DeltaPhi->Fill(deltaPhi*180./M_PI, eventWeight);
    DeltaR->Fill(deltaR, eventWeight);
    DeltaVz->Fill(deltaVz, eventWeight);
    DiMass->Fill(diMass, eventWeight);
    DiPt->Fill(diPt, eventWeight);
    DiPhi->Fill(diPhi*180./M_PI, eventWeight);
    DiY->Fill(diY, eventWeight);
    
  }
}



// ------------ method called once each job just before starting event loop  ------------
void 
DimuonAnalyzer::beginJob()
{
  edm::Service<TFileService> fileService;
  
  TFileDirectory dirEvent = fileService->mkdir("EventProperties");
  NDimuon = dirEvent.make<TH1F>("h_nDimuon","# dimuons;# dimuons; # events",20,0,20);
  
  TFileDirectory dirDimuon = fileService->mkdir("DimuonProperties");
  EtaLow = dirDimuon.make<TH1F>("h_etaLow","muon with lower absolute value of #eta;#eta;# muons",120,-3,3);
  EtaHigh = dirDimuon.make<TH1F>("h_etaHigh","muon w/ higher absolute value of #eta;#eta;# muons",120,-3,3);
  PtLow = dirDimuon.make<TH1F>("h_ptLow","muon w/ lower p_{t};p_{t}  [GeV];# muons",100,0,200);
  PtHigh = dirDimuon.make<TH1F>("h_ptHigh","muon w/ higher p_{t};p_{t}  [GeV];# muons",100,0,200);
  IsoLow = dirDimuon.make<TH1F>("h_isoLow","muon w/ better isolation I_{comb}^{rel};I_{comb}^{rel};# muons",100,0,0.15);
  IsoHigh = dirDimuon.make<TH1F>("h_isoHigh","muon w/ worse isolation I_{comb}^{rel};I_{comb}^{rel};# muons",100,0,0.15);
  DeltaEta = dirDimuon.make<TH1F>("h_deltaEta","#Delta#eta;#Delta#eta;# muon pairs",100,-5,5);
  DeltaPhi = dirDimuon.make<TH1F>("h_deltaPhi","#Delta#phi;#Delta#phi  [ ^{o}];# muon pairs",100,-200,200);
  DeltaR =  dirDimuon.make<TH1F>("h_deltaR","#Delta R;#Delta R;# muon pairs",100,0,10);
  DeltaVz = dirDimuon.make<TH1F>("h_deltaVz","#Delta v_{z};#Delta v_{z};# muon pairs",100,-1.,1.);
  DiMass = dirDimuon.make<TH1F>("h_diMass","dimuon invariant mass;M_{#mu#mu} [GeV];# muon pairs",200,0.,400.);
  DiPt = dirDimuon.make<TH1F>("h_diPt","dimuon p_{t};p_{t}  [GeV];# muon pairs",100,0,200);
  DiPhi = dirDimuon.make<TH1F>("h_phi","Azimuth angle #phi;#phi;# jets",90,-180,180);
  DiY = dirDimuon.make<TH1F>("h_diY","dimuon rapidity y;y;# muon pairs",120,-3,3);
}



// ------------ method called once each job just after ending the event loop  ------------
void 
DimuonAnalyzer::endJob() {
}



//define this as a plug-in
DEFINE_FWK_MODULE(DimuonAnalyzer);
