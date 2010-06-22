// -*- C++ -*-
//
// Package:    DiMuonAnalyzer
// Class:      DiMuonAnalyzer
// 
/**\class DiMuonAnalyzer DiMuonAnalyzer.cc ZmumuAnalysis/Analyzer/plugins/DiMuonAnalyzer.cc

 Description: Plotter for combined di-muon distributions

 Implementation:
     Based on reconstructed PAT objects
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Thu May 20 15:47:12 CEST 2010
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

#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "DataFormats/Candidate/interface/LeafCandidate.h"


#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"

#include "FWCore/Utilities/interface/EDMException.h"

#include "DataFormats/Math/interface/deltaPhi.h"

#include "TH1.h"

//
// class declaration
//

class DiMuonAnalyzer : public edm::EDAnalyzer {
   public:
      explicit DiMuonAnalyzer(const edm::ParameterSet&);
      ~DiMuonAnalyzer();
      
      struct DiMuHists{
        DiMuHists():EtaLow(0), EtaHigh(0), PtLow(0), PtHigh(0),
		    DeltaEta(0), DeltaPhi(0),
		    DiMass(0), DiPt(0){}
	
        /// Properties of the two pt-leading muons
        TH1F *EtaLow, *EtaHigh, *PtLow, *PtHigh;
	
	/// Differences of the two pt-leading muons
        TH1F *DeltaEta, *DeltaPhi;
	
	/// Properties of reconstructed Di-Muon particle
	TH1F *DiMass, *DiPt;
      };


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      void bookHists(DiMuHists&, const TFileDirectory&);
      void fillHists(DiMuHists&, const edm::Handle<pat::MuonCollection>&, const double);

      // ----------member data ---------------------------
      
      
      const edm::ParameterSet parameterSet_;
      
      /// plots for same-charge dimuon mass
      DiMuHists histsSC_;
      
      /// plots for opposite-charge dimuon mass
      DiMuHists histsOC_;
      
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
DiMuonAnalyzer::DiMuonAnalyzer(const edm::ParameterSet& iConfig):
parameterSet_(iConfig)
{
}


DiMuonAnalyzer::~DiMuonAnalyzer()
{
}


//
// member functions
//


void
DiMuonAnalyzer::fillHists(DiMuHists& hists, const edm::Handle<pat::MuonCollection>& muons, const double weight){
  // get leading muons      
  const pat::MuonCollection::const_reference mu1 = muons->at(0);
  const pat::MuonCollection::const_reference mu2 = muons->at(1);
  
  // eta and pt
  const double etaLow = std::fabs(mu1.eta())<std::fabs(mu2.eta()) ? mu1.eta() : mu2.eta();
  const double etaHigh = std::fabs(mu1.eta())>std::fabs(mu2.eta()) ? mu1.eta() : mu2.eta();
  // pat-tuples already ordered in pt
  const double ptHigh = mu1.pt();
  const double ptLow = mu2.pt();
  //const double ptLow = mu1.pt()<mu2.pt() ? mu1.pt() : mu2.pt();
  //const double ptHigh = mu1.pt()>mu2.pt() ? mu1.pt() : mu2.pt();
  
  // eta, phi difference
  double deltaEta = mu2.eta() - mu1.eta();
  double deltaPhi = reco::deltaPhi(mu2.phi(),mu1.phi());
  
  // invariant mass
  const reco::LeafCandidate::LorentzVector diMuVec = mu1.p4() + mu2.p4();
  const double diMuMass = diMuVec.M();
  const double diPt = diMuVec.pt();
  
  hists.EtaLow->Fill(etaLow, weight);
  hists.EtaHigh->Fill(etaHigh, weight);
  hists.PtLow->Fill(ptLow, weight);
  hists.PtHigh->Fill(ptHigh, weight);
  hists.DeltaEta->Fill(deltaEta, weight);
  hists.DeltaPhi->Fill(deltaPhi*180./M_PI, weight);
  hists.DiMass->Fill(diMuMass, weight);
  hists.DiPt->Fill(diPt);
}



// ------------ method called to for each event  ------------
void
DiMuonAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // get handle on muon collection
  const edm::InputTag muonSource(parameterSet_.getParameter<edm::InputTag>("muonSource"));
  edm::Handle<pat::MuonCollection> muons; 
  iEvent.getByLabel(muonSource, muons);
  
  // get weight when indicated, else weight is 1.
  double weight(1.);
  if(parameterSet_.getParameter<bool>("useEventWeight")){
    edm::Handle<double> weightHandle;
    iEvent.getByLabel("eventWeight",weightHandle);
    weight = *weightHandle;
  }
  
  // test if muon collection contains at least two muons resp. exactly two muons
  if(muons->size()<2 || (parameterSet_.getParameter<bool>("exactlyTwoMuons") && muons->size()!=2) )return;
  
  // get leading muons      
  const pat::MuonCollection::const_reference mu1 = muons->at(0);
  const pat::MuonCollection::const_reference mu2 = muons->at(1);
  
  // same or opposite charge?
  bool isSameCharge = false;
  if(mu1.charge()*mu2.charge()>0.) isSameCharge = true;
  
  if(isSameCharge){
    this->fillHists(histsSC_, muons, weight);
  }
  else{
    this->fillHists(histsOC_, muons, weight);
  }
}



void
DiMuonAnalyzer::bookHists(DiMuHists& hists, const TFileDirectory& dir){
  hists.EtaLow = dir.make<TH1F>("h_etaLow","muon with lower absolute value of #eta;#eta;# muons",200,-10,10);
  hists.EtaHigh = dir.make<TH1F>("h_etaHigh","muon w/ higher absolute value of #eta;#eta;# muons",200,-10,10);
  hists.PtLow = dir.make<TH1F>("h_ptLow","muon w/ lower p_{t};p_{t}  [GeV];# muons",200,0,200);
  hists.PtHigh = dir.make<TH1F>("h_ptHigh","muon w/ higher p_{t};p_{t}  [GeV];# muons",200,0,200);
  hists.DeltaEta = dir.make<TH1F>("h_deltaEta","#Delta#eta;#Delta#eta;# muon pairs",100,-5,5);
  hists.DeltaPhi = dir.make<TH1F>("h_deltaPhi","#Delta#phi;#Delta#phi;# muon pairs",200,-200,200);
  hists.DiMass = dir.make<TH1F>("h_diMass","di-muon invariant mass;m_{#mu#mu} [GeV];# muon pairs",100,0.,200.);
  hists.DiPt = dir.make<TH1F>("h_diPt","di-muon p_{t};p_{t}  [GeV];# muon pairs",200,0,200);
}






// ------------ method called once each job just before starting event loop  ------------
void 
DiMuonAnalyzer::beginJob()
{
  edm::Service<TFileService> fileService;
  if(!fileService){
    throw edm::Exception( edm::errors::Configuration,
                          "TFileService is not registered in cfg file" );
  }
  
  TFileDirectory dirSC = fileService->mkdir("SameCharge");
  this->bookHists(histsSC_,dirSC);
  
  TFileDirectory dirOC = fileService->mkdir("OppositeCharge");
  this->bookHists(histsOC_,dirOC);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DiMuonAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(DiMuonAnalyzer);
