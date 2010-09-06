// -*- C++ -*-
//
// Package:    GeneratorZmumuAnalyzer
// Class:      GeneratorZmumuAnalyzer
// 
/**\class GeneratorZmumuAnalyzer GeneratorZmumuAnalyzer.cc ZmumuAnalysis/Analyzer/plugins/GeneratorZmumuAnalyzer.cc

 Description: Plotter for generated Z->mumu properties

 Implementation:
     Based on reco::GenParticle objects
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Fri Feb 26 16:48:04 CET 2010
// $Id: GeneratorZmumuAnalyzer.cc,v 1.2 2010/08/20 11:51:09 hauk Exp $
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

#include "DataFormats/Candidate/interface/CandidateFwd.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"
#include "TH1.h"

//
// class declaration
//

class GeneratorZmumuAnalyzer : public edm::EDAnalyzer {
   public:
      explicit GeneratorZmumuAnalyzer(const edm::ParameterSet&);
      ~GeneratorZmumuAnalyzer();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
      const edm::ParameterSet parSet_;
      
      TH1 *EtaLow, *EtaHigh, *PtLow, *PtHigh,
          *EtaZ, *PtZ,
	  *MassZ;
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
GeneratorZmumuAnalyzer::GeneratorZmumuAnalyzer(const edm::ParameterSet& iConfig):
parSet_(iConfig),
EtaLow(0), EtaHigh(0), PtLow(0), PtHigh(0),
EtaZ(0), PtZ(0),
MassZ(0)
{
}


GeneratorZmumuAnalyzer::~GeneratorZmumuAnalyzer()
{
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
GeneratorZmumuAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  
   const edm::InputTag inputTag(parSet_.getParameter<edm::InputTag>("src"));
  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(inputTag, genParticles);
  
//  std::cout<<"\tSize: "<<genParticles->size()<<"\n";
  
  for(reco::GenParticleCollection::const_iterator iGenPart = genParticles->begin(); iGenPart != genParticles->end(); ++iGenPart) {
    bool isZmumu(false);
    double etaMinus(-999.), ptMinus(-999.);
    double etaPlus(-999.), ptPlus(-999.);
    double etaZ(-999.), ptZ(-999.);
    reco::Candidate::LorentzVector lorVecMinus, lorVecPlus;
    // select Z0 gauge bosons
    // take care about status: decaying Z0 (status=3) has 3 daughters, third is Z0 itself as decayed Z0 (status=2)
    // Question: is the status numbering convention only valid for Pythia
    if(iGenPart->pdgId()!=23 || iGenPart->status()!=3) continue;
//    std::cout<<"\tGot ya - no. of daughters: "<<iGenPart->numberOfDaughters()<<"   - status: "<<iGenPart->status()<<"\n";
    etaZ = iGenPart->eta();
    ptZ = iGenPart->pt();
    for(size_t iDaughter = 0; iDaughter < iGenPart->numberOfDaughters(); ++iDaughter){
      const reco::GenParticle* daughter(dynamic_cast<const reco::GenParticle*>(iGenPart->daughter(iDaughter)));
//      std::cout<<"\tDaughter no. "<<iDaughter<<" has ID "<<daughter->pdgId()<<" and Status "<<daughter->status()<<"\n";
      // select mu-
      if(daughter->pdgId()==13){
        lorVecMinus = daughter->p4();
        etaMinus = daughter->eta();
        ptMinus = daughter->pt();
//        std::cout<<"Four vector(Px,Py,Pz,E):\t"<<lorVecMinus.Px()<<"\t"<<lorVecMinus.Py()<<"\t"<<lorVecMinus.Pz()<<"\t"<<lorVecMinus.E()<<"\n";
//        std::cout<<"Eta, Phi, Pt:\t"<<etaMinus<<"\t"<<(daughter->phi())*180./M_PI<<"\t"<<ptMinus<<"\n";
        isZmumu = true;
      }
      // select mu+
      else if(daughter->pdgId()==-13){
        lorVecPlus = daughter->p4();
        etaPlus = daughter->eta();
        ptPlus = daughter->pt();
//        std::cout<<"Four vector(Px,Py,Pz,E):\t"<<lorVecPlus.Px()<<"\t"<<lorVecPlus.Py()<<"\t"<<lorVecPlus.Pz()<<"\t"<<lorVecPlus.E()<<"\n";
//        std::cout<<"Eta, Phi, Pt:\t"<<etaPlus<<"\t"<<(daughter->phi())*180./M_PI<<"\t"<<ptPlus<<"\n";
      }
    }
    
    if(!isZmumu)continue;
    reco::Candidate::LorentzVector diMuVec = lorVecMinus + lorVecPlus;
    double diMuMass = diMuVec.M();
    const double etaLow = std::fabs(etaMinus)<std::fabs(etaPlus) ? etaMinus : etaPlus;
    const double etaHigh = std::fabs(etaMinus)>std::fabs(etaPlus) ? etaMinus : etaPlus;
    const double ptLow = ptMinus<ptPlus ? ptMinus : ptPlus;
    const double ptHigh = ptMinus>ptPlus ? ptMinus : ptPlus;
    
    EtaLow->Fill(etaLow);
    EtaHigh->Fill(etaHigh);
    PtLow->Fill(ptLow);
    PtHigh->Fill(ptHigh);
    EtaZ->Fill(etaZ);
    PtZ->Fill(ptZ);
    MassZ->Fill(diMuMass);
  }
}


// ------------ method called once each job just before starting event loop  ------------
void 
GeneratorZmumuAnalyzer::beginJob(){
  edm::Service<TFileService> fileService;
  TFileDirectory dirSingle = fileService->mkdir("SingleMu");
  EtaLow = dirSingle.make<TH1F>("h_etaLow","muon with lower absolute value of #eta;#eta;# muons",200,-10,10);
  EtaHigh = dirSingle.make<TH1F>("h_etaHigh","muon w/ higher absolute value of #eta;#eta;# muons",200,-10,10);
  PtLow = dirSingle.make<TH1F>("h_ptLow","muon w/ lower p_{t};p_{t}  [GeV];# muons",200,0,200);
  PtHigh = dirSingle.make<TH1F>("h_ptHigh","muon w/ higher p_{t};p_{t}  [GeV];# muons",200,0,200);
  
  TFileDirectory dirZ = fileService->mkdir("GeneratedZ");
  EtaZ = dirZ.make<TH1F>("h_etaZ","#eta of generated Z;#eta;# Z",200,-10,10);
  PtZ = dirZ.make<TH1F>("h_ptZ","p_{t} of generated Z;p_{t}  [GeV];# Z",200,0,200);
  MassZ = dirZ.make<TH1F>("h_massZ","invariant mass of muon pair;m_{#mu#mu} [GeV];# muon pairs",200,0,200);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GeneratorZmumuAnalyzer::endJob(){
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(GeneratorZmumuAnalyzer);
