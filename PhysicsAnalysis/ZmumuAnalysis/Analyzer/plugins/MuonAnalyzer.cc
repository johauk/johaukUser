// -*- C++ -*-
//
// Package:    MuonAnalyzer
// Class:      MuonAnalyzer
// 
/**\class MuonAnalyzer MuonAnalyzer.cc ZmumuAnalysis/Analyzer/plugins/MuonAnalyzer.cc

 Description: Plotter for distributions of muon properties

 Implementation:
     Based on reconstructed PAT objects
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Thu Aug 19 17:46:32 CEST 2010
// $Id: MuonAnalyzer.cc,v 1.1 2010/08/20 11:47:04 hauk Exp $
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

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"

#include "FWCore/Utilities/interface/EDMException.h"

#include "TH1.h"
//
// class declaration
//

class MuonAnalyzer : public edm::EDAnalyzer {
   public:
      explicit MuonAnalyzer(const edm::ParameterSet&);
      ~MuonAnalyzer();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      

      const edm::ParameterSet parameterSet_;
      
      TH1* NMuon;
      
      TH1* IsGlobal;
      TH1* IsTracker;
      TH1* NumberOfValidTrackerHits;
      TH1* NumberOfValidPixelHits;
      TH1* NumberOfMatches;
      TH1* NumberOfValidMuonHits;
      TH1* NormalizedChi2;
      TH1* Eta;
      TH1* Pt;
      TH1* D0Beamspot;
      
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
MuonAnalyzer::MuonAnalyzer(const edm::ParameterSet& iConfig):
parameterSet_(iConfig),
NMuon(0),
IsGlobal(0), IsTracker(0),
NumberOfValidTrackerHits(0), NumberOfValidPixelHits(0),
NumberOfMatches(0),
NumberOfValidMuonHits(0),
NormalizedChi2(0),
Eta(0), Pt(0), D0Beamspot(0)
{
}


MuonAnalyzer::~MuonAnalyzer()
{
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
MuonAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // get handle on muon collection
  const edm::InputTag muonSource(parameterSet_.getParameter<edm::InputTag>("muonSource"));
  edm::Handle<pat::MuonCollection> muons;
  iEvent.getByLabel(muonSource, muons);
  
  // Event properties
  unsigned int nMuon(999);
  nMuon = muons->size();
  NMuon->Fill(nMuon);
  
  // Muon properties
  // All values taken from global muon, except for TrackerMuon: numberOfValidTrackerHits, numberOfValidPixelHits
  bool isGlobal(false), isTracker(false);
  unsigned int numberOfValidTrackerHits(999), numberOfValidPixelHits(999);
  unsigned int numberOfMatches(999);
  unsigned int numberOfValidMuonHits(999);
  double normalizedChi2(9999.);
  double eta(-999.), pt(-999.), d0Beamspot(-999.);
  
  pat::MuonCollection::const_iterator i_muon;
  for(i_muon = muons->begin(); i_muon != muons->end(); ++i_muon){
    isGlobal = i_muon->isGlobalMuon();
    isTracker = i_muon->isTrackerMuon();
    if(isTracker){
      numberOfValidTrackerHits = i_muon->track()->hitPattern().numberOfValidTrackerHits();
      numberOfValidPixelHits = i_muon->track()->hitPattern().numberOfValidPixelHits();
    }
    numberOfMatches = i_muon->numberOfMatches();
    if(isGlobal){
      numberOfValidMuonHits = i_muon->globalTrack()->hitPattern().numberOfValidMuonHits();
      normalizedChi2 = i_muon->globalTrack()->normalizedChi2();
    }
    eta = i_muon->eta();
    pt = i_muon->pt();
    d0Beamspot = i_muon->dB();
    
    IsGlobal->Fill(isGlobal);
    IsTracker->Fill(isTracker);
    if(isTracker){
      NumberOfValidTrackerHits->Fill(numberOfValidTrackerHits);
      NumberOfValidPixelHits->Fill(numberOfValidPixelHits);
    }
    NumberOfMatches->Fill(numberOfMatches);
    if(isGlobal){
      NumberOfValidMuonHits->Fill(numberOfValidMuonHits);
      NormalizedChi2->Fill(normalizedChi2);
    }
    Eta->Fill(eta);
    Pt->Fill(pt);
    D0Beamspot->Fill(d0Beamspot);
    
  }
}


// ------------ method called once each job just before starting event loop  ------------
void 
MuonAnalyzer::beginJob()
{
  edm::Service<TFileService> fileService;

  TFileDirectory dirEvent = fileService->mkdir("EventProperties");
  NMuon = dirEvent.make<TH1F>("h_nMuon","# muons;# muons; # events",20,0,20);
  
  TFileDirectory dirMuon = fileService->mkdir("MuonProperties");
  IsGlobal = dirMuon.make<TH1F>("h_isGlobal","global muons;is global;# muons",2,0,2);
  IsTracker = dirMuon.make<TH1F>("h_isTracker","tracker muons;is tracker;# muons",2,0,2);
  NumberOfValidTrackerHits = dirMuon.make<TH1F>("h_nTrackerHits","# hits (tracker fit) [tracker];# hits  [tracker];# muons",40,0,40);
  NumberOfValidPixelHits = dirMuon.make<TH1F>("h_nPixelHits","# hits (tracker fit) [pixel];# hits  [pixel];# muons",10,0,10);
  NumberOfMatches = dirMuon.make<TH1F>("h_nMatches","# matches [muon];#  matches  [muon];# muons",10,0,10);
  NumberOfValidMuonHits = dirMuon.make<TH1F>("h_nMuonHitsGlobal","# hits (global fit) [muon];# hits  [muon];# muons",50,0,50);
  NormalizedChi2 = dirMuon.make<TH1F>("h_chi2","normalized #chi^{2};#chi^{2}/ndof;# muons",50,0,100);
  Eta = dirMuon.make<TH1F>("h_eta","pseudorapidity #eta;#eta;# muons",60,-3,3);
  Pt = dirMuon.make<TH1F>("h_pt","transverse momentum p_{t};p_{t};# muons",100,0,200);
  D0Beamspot = dirMuon.make<TH1F>("h_d0Beamspot","closest approach d_{0} wrt. beamspot;d_{0, BS}  [cm];# muons",100,-1,1);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MuonAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(MuonAnalyzer);
