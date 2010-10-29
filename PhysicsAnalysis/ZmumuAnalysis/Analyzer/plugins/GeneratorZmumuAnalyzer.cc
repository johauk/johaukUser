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
// $Id: GeneratorZmumuAnalyzer.cc,v 1.5 2010/10/21 15:34:09 hauk Exp $
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

#include "FWCore/MessageLogger/interface/MessageLogger.h"

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
      
      enum Flavour{down=1, up=2, strange=3, charm=4, bottom=5, unknown=6};

      // ----------member data ---------------------------
      const edm::ParameterSet parameterSet_;
      
      TH1 *EtaLow, *EtaHigh, *PtLow, *PtHigh,
          *EtaZ, *PtZ,
	  *MassZ,
	  *QuarkOrigin;
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
parameterSet_(iConfig),
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
  
  const edm::InputTag inputTag(parameterSet_.getParameter<edm::InputTag>("src"));
  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(inputTag, genParticles);
  
  // all variable names are like in Z->mumu case, but act universally on Z->xx
  const std::vector<int> v_zDecayMode(parameterSet_.getParameter<std::vector<int> >("zDecayMode"));
  
  for(reco::GenParticleCollection::const_iterator i_genPart = genParticles->begin(); i_genPart != genParticles->end(); ++i_genPart) {
    bool isZmumu(false);
    double etaMinus(-999.), ptMinus(-999.);
    double etaPlus(-999.), ptPlus(-999.);
    double etaZ(-999.), ptZ(-999.);
    reco::Candidate::LorentzVector lorVecMinus, lorVecPlus;
    // select Z0 gauge bosons
    // take care about status: decaying Z0 (status=3) has 3 daughters, third is Z0 itself as decayed Z0 (status=2)
    // Question: is the status numbering convention only valid for Pythia?
    if(i_genPart->pdgId()!=23 || i_genPart->status()!=3) continue;
    //std::cout<<"\tGot ya - no. of daughters: "<<i_genPart->numberOfDaughters()<<"   - status: "<<i_genPart->status()<<"\n";
    etaZ = i_genPart->eta();
    ptZ = i_genPart->pt();
    for(size_t iDaughter = 0; iDaughter < i_genPart->numberOfDaughters(); ++iDaughter){
      const reco::GenParticle* daughter(dynamic_cast<const reco::GenParticle*>(i_genPart->daughter(iDaughter)));
      //std::cout<<"\tDaughter no. "<<iDaughter<<" has ID "<<daughter->pdgId()<<" and Status "<<daughter->status()<<"\n";
      // select mu-
      for(std::vector<int>::const_iterator i_zDecayMode = v_zDecayMode.begin();i_zDecayMode != v_zDecayMode.end(); ++i_zDecayMode){
        if(daughter->pdgId() == (*i_zDecayMode)){
          lorVecMinus = daughter->p4();
          etaMinus = daughter->eta();
          ptMinus = daughter->pt();
          //std::cout<<"Four vector(Px,Py,Pz,E):\t"<<lorVecMinus.Px()<<"\t"<<lorVecMinus.Py()<<"\t"<<lorVecMinus.Pz()<<"\t"<<lorVecMinus.E()<<"\n";
          //std::cout<<"Eta, Phi, Pt:\t"<<etaMinus<<"\t"<<(daughter->phi())*180./M_PI<<"\t"<<ptMinus<<"\n";
          isZmumu = true;
        }
        // select mu+
        else if(daughter->pdgId() == -(*i_zDecayMode)){
          lorVecPlus = daughter->p4();
          etaPlus = daughter->eta();
          ptPlus = daughter->pt();
          //std::cout<<"Four vector(Px,Py,Pz,E):\t"<<lorVecPlus.Px()<<"\t"<<lorVecPlus.Py()<<"\t"<<lorVecPlus.Pz()<<"\t"<<lorVecPlus.E()<<"\n";
          //std::cout<<"Eta, Phi, Pt:\t"<<etaPlus<<"\t"<<(daughter->phi())*180./M_PI<<"\t"<<ptPlus<<"\n";
        }
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
    
    
    //check flavour of mother quarks qqbar->Z
    //std::cout<<"\tNo. of mothers: "<<i_genPart->numberOfMothers()<<"\n";
    if(i_genPart->numberOfMothers()!=2)edm::LogError("Generator Behaviour")<<"Strange origin of Z, not built from two particles, but "<<i_genPart->numberOfMothers();
    if(i_genPart->mother(0)->pdgId() != -i_genPart->mother(1)->pdgId())edm::LogError("Generator Behaviour")<<"Strange origin of Z, built from "<<i_genPart->mother(0)->pdgId()<<", "<<i_genPart->mother(1)->pdgId();
    const int motherPdgId(std::fabs(i_genPart->mother()->pdgId()));  // by default first one, so mother(0) is taken
    Flavour flavour(unknown);
    if(motherPdgId == 1)flavour = down;
    else if (motherPdgId == 2)flavour = up;
    else if (motherPdgId == 3)flavour = strange;
    else if (motherPdgId == 4)flavour = charm;
    else if (motherPdgId == 5)flavour = bottom;
    if(motherPdgId >= 1 && motherPdgId <= 5)flavour = Flavour(motherPdgId);
    if(flavour==unknown)edm::LogError("Generator Behaviour")<<"Strange origin of Z, made of particles of type (PdgId): "<<motherPdgId;
    for(size_t iMother = 0; iMother < i_genPart->numberOfMothers(); ++iMother){
      const reco::GenParticle* motherQuark(dynamic_cast<const reco::GenParticle*>(i_genPart->mother(iMother)));
      //std::cout<<"\tMother quark no. "<<iMother<<" has ID "<<motherQuark->pdgId()<<" and Status "<<motherQuark->status()<<"\n";
      //std::cout<<"\tNo. of mother gluons: "<<motherQuark->numberOfMothers()<<"\n";
      if(motherQuark->numberOfMothers()!=1)edm::LogError("Generator Behaviour")<<"Strange origin of mother quark, not built from single gluon, but "<<motherQuark->numberOfMothers();
      //const reco::GenParticle* gluon(dynamic_cast<const reco::GenParticle*>(motherQuark->mother()));
      //if(gluon->pdgId()!=21){ // && std::fabs(gluon->pdgId())>2){
	//std::cout<<"\tMother gluon (of quark with ID "<<motherQuark->pdgId()<<") has ID "<<gluon->pdgId()<<" and Status "<<gluon->status()<<"\n";
        //std::cout<<"\t\tHas "<<gluon->numberOfDaughters()<<" daughters and "<<gluon->numberOfMothers()<<" mothers, first one with ID "<<gluon->mother()->pdgId()<<"\n";
	//for(size_t iDaughter2 = 0; iDaughter2 < gluon->numberOfDaughters(); ++iDaughter2){
	//  if(gluon->daughter(iDaughter2)->status()!=2){
	//    std::cout<<"\t\tDaughter "<<iDaughter2<<" has ID "<<gluon->daughter(iDaughter2)->pdgId()<<" and Status "<<gluon->daughter(iDaughter2)->status()<<"\n";
	//  }
	//}
      //}
    }
    QuarkOrigin->Fill(flavour-1);
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
  QuarkOrigin = dirZ.make<TH1F>("h_quarkOrigin","quark origin;;#Z",6,0,6);
  QuarkOrigin->GetXaxis()->SetBinLabel(1,"d");
  QuarkOrigin->GetXaxis()->SetBinLabel(2,"u");
  QuarkOrigin->GetXaxis()->SetBinLabel(3,"s");
  QuarkOrigin->GetXaxis()->SetBinLabel(4,"c");
  QuarkOrigin->GetXaxis()->SetBinLabel(5,"b");
  QuarkOrigin->GetXaxis()->SetBinLabel(6,"XXX");
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GeneratorZmumuAnalyzer::endJob(){
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(GeneratorZmumuAnalyzer);
