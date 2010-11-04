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
// $Id: DiMuonAnalyzer.cc,v 1.4 2010/10/22 12:20:27 hauk Exp $
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

#include "TH1.h"

//
// class declaration
//

class DiMuonAnalyzer : public edm::EDAnalyzer {
   public:
      explicit DiMuonAnalyzer(const edm::ParameterSet&);
      ~DiMuonAnalyzer();
      
      struct DiMuHists{
        DiMuHists():NDimuon(0),
	            EtaLow(0), EtaHigh(0), PtLow(0), PtHigh(0),
		    DeltaEta(0), DeltaPhi(0),
		    DiMass(0), DiPt(0){}
	
	/// Number of dimuons
        TH1* NDimuon;
	
        /// Properties of the two muons
        TH1F *EtaLow, *EtaHigh, *PtLow, *PtHigh;
	
	/// Differences of the two muons
        TH1F *DeltaEta, *DeltaPhi;
	
	/// Properties of reconstructed di-muon particle
	TH1F *DiMass, *DiPt,
	     *DiY;
      };


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      void bookHists(DiMuHists&, const TFileDirectory&);
      void fillHists(DiMuHists&, const reco::Candidate&);

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
DiMuonAnalyzer::bookHists(DiMuHists& hists, const TFileDirectory& dir){
  hists.NDimuon = dir.make<TH1F>("h_nDimuon","# dimuons;# dimuons; # events",20,0,20);
  hists.EtaLow = dir.make<TH1F>("h_etaLow","muon with lower absolute value of #eta;#eta;# muons",200,-4,4);
  hists.EtaHigh = dir.make<TH1F>("h_etaHigh","muon w/ higher absolute value of #eta;#eta;# muons",200,-4,4);
  hists.PtLow = dir.make<TH1F>("h_ptLow","muon w/ lower p_{t};p_{t}  [GeV];# muons",200,0,200);
  hists.PtHigh = dir.make<TH1F>("h_ptHigh","muon w/ higher p_{t};p_{t}  [GeV];# muons",200,0,200);
  hists.DeltaEta = dir.make<TH1F>("h_deltaEta","#Delta#eta;#Delta#eta;# muon pairs",100,-5,5);
  hists.DeltaPhi = dir.make<TH1F>("h_deltaPhi","#Delta#phi;#Delta#phi;# muon pairs",200,-200,200);
  hists.DiMass = dir.make<TH1F>("h_diMass","di-muon invariant mass;m_{#mu#mu} [GeV];# muon pairs",100,0.,200.);
  hists.DiPt = dir.make<TH1F>("h_diPt","di-muon p_{t};p_{t}  [GeV];# muon pairs",200,0,200);
  hists.DiY = dir.make<TH1F>("h_diY","di-muon rapidity y;y;# muon pairs",200,-4,4);
}



void
DiMuonAnalyzer::fillHists(DiMuHists& hists, const reco::Candidate& diMuon){
  const reco::Candidate* daughter1 = diMuon.daughter(0);
  const reco::Candidate* daughter2 = diMuon.daughter(1);
  
  const pat::MuonCollection::const_reference mu1 = dynamic_cast<const pat::Muon&>(*daughter1->masterClone());
  const pat::MuonCollection::const_reference mu2 = dynamic_cast<const pat::Muon&>(*daughter2->masterClone());
  
  // eta and pt
  const double etaLow = std::fabs(mu1.eta())<std::fabs(mu2.eta()) ? mu1.eta() : mu2.eta();
  const double etaHigh = std::fabs(mu1.eta())>std::fabs(mu2.eta()) ? mu1.eta() : mu2.eta();
  const double ptLow = mu1.pt()<mu2.pt() ? mu1.pt() : mu2.pt();
  const double ptHigh = mu1.pt()>mu2.pt() ? mu1.pt() : mu2.pt();
  
  // eta, phi difference
  const double deltaEta = mu2.eta() - mu1.eta();
  const double deltaPhi = reco::deltaPhi(mu2.phi(),mu1.phi());
  
  // dimuon invariant mass, pt and rapidity
  const reco::Candidate::LorentzVector diMuVec = mu1.p4() + mu2.p4();
  const double diMass = diMuon.mass();
  const double diPt = diMuon.pt();
  const double diY = diMuon.y();
  
  hists.EtaLow->Fill(etaLow);
  hists.EtaHigh->Fill(etaHigh);
  hists.PtLow->Fill(ptLow);
  hists.PtHigh->Fill(ptHigh);
  hists.DeltaEta->Fill(deltaEta);
  hists.DeltaPhi->Fill(deltaPhi*180./M_PI);
  hists.DiMass->Fill(diMass);
  hists.DiPt->Fill(diPt);
  hists.DiY->Fill(diY);
}



// ------------ method called to for each event  ------------
void
DiMuonAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // get handle on di-muon collection
  const edm::InputTag diMuonSource(parameterSet_.getParameter<edm::InputTag>("diMuonSource"));
  edm::Handle<reco::CandidateView> diMuons;
  iEvent.getByLabel(diMuonSource, diMuons);
  
  // Event properties
  unsigned int nDimuonOC(0), nDimuonSC(0);
  
  reco::CandidateView::const_iterator i_cand;
  for(i_cand = diMuons->begin(); i_cand != diMuons->end(); ++i_cand){
    const reco::Candidate& diMuon = *i_cand;
    if(diMuon.charge()==0){
      this->fillHists(histsOC_, diMuon);
      ++nDimuonOC;
    }
    else{
      this->fillHists(histsSC_, diMuon);
      ++nDimuonSC;
    }
  }
  histsOC_.NDimuon->Fill(nDimuonOC);
  histsSC_.NDimuon->Fill(nDimuonSC);
}



// ------------ method called once each job just before starting event loop  ------------
void 
DiMuonAnalyzer::beginJob()
{
  edm::Service<TFileService> fileService;
  
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
