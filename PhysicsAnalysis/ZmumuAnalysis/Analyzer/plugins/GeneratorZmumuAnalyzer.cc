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
// $Id: GeneratorZmumuAnalyzer.cc,v 1.9 2011/01/28 13:33:04 hauk Exp $
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
#include "TH2.h"

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
      
      TH1 *MuEtaLow, *MuEtaHigh, *MuPtLow, *MuPtHigh,
	  *DiMuEta, *DiMuPt, *DiMuMass,
	  *ZEta, *ZY, *ZPt, *ZMass,
	  *DiffY, *DiffPt, *DiffMass,
	  *ZQuarkOrigin;
      TH2 *ZMassVsDiMuMass;
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
MuEtaLow(0), MuEtaHigh(0), MuPtLow(0), MuPtHigh(0),
DiMuEta(0), DiMuPt(0), DiMuMass(0),
ZEta(0), ZY(0), ZPt(0), ZMass(0),
DiffY(0), DiffPt(0), DiffMass(0),
ZQuarkOrigin(0),
ZMassVsDiMuMass(0)
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
  
  
  //std::cout<<"\tNumber of particles in event: "<<genParticles->size()<<"\n";
  for(reco::GenParticleCollection::const_iterator i_genPart = genParticles->begin(); i_genPart != genParticles->end(); ++i_genPart) {
    bool isZmumu(false);
    double etaMinus(-999.), ptMinus(-999.);
    double etaPlus(-999.), ptPlus(-999.);
    double zEta(-999.), zY(-999.), zPt(-999.), zMass(-999.);
    reco::Candidate::LorentzVector lorVecMinus, lorVecPlus;
    //std::cout<<"\tParticle with ID: "<<i_genPart->pdgId()<<" and status "<<i_genPart->status()<<"\n";
    // select Z0 gauge bosons
    // take care about status: decaying Z0 (status=3) has 3 daughters, third is Z0 itself as decayed Z0 (status=2)
    // Question: is the status numbering convention only valid for Pythia?
    if(i_genPart->pdgId()!=23 || i_genPart->status()!=3) continue;
    //std::cout<<"\tNumber of Z daughters: "<<i_genPart->numberOfDaughters()<<"\n";
    if(i_genPart->numberOfDaughters()!=3)edm::LogError("Generator Behaviour")<<"Strange decay of Z, not exactly 3 daughters, but: "<<i_genPart->numberOfDaughters()<<"\n";
    zEta = i_genPart->eta();
    zY = i_genPart->y();
    zPt = i_genPart->pt();
    zMass = i_genPart->mass();
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
    const double diMuEta = diMuVec.eta();
    const double diMuPt = diMuVec.pt();
    double diMuMass = diMuVec.M();
    const double etaLow = std::fabs(etaMinus)<std::fabs(etaPlus) ? etaMinus : etaPlus;
    const double etaHigh = std::fabs(etaMinus)>std::fabs(etaPlus) ? etaMinus : etaPlus;
    const double ptLow = ptMinus<ptPlus ? ptMinus : ptPlus;
    const double ptHigh = ptMinus>ptPlus ? ptMinus : ptPlus;
    
    
    //check flavour of mother quarks qqbar->Z
    //std::cout<<"\tNo. of mothers: "<<i_genPart->numberOfMothers()<<"\n";
    if(i_genPart->numberOfMothers()!=2)edm::LogError("Generator Behaviour")<<"Strange origin of Z, not built from two particles, but "<<i_genPart->numberOfMothers();
    const int motherPdgId1(i_genPart->mother()->pdgId());  // by default first one, so mother(0) is taken
    const int motherPdgId2(i_genPart->mother(1)->pdgId());
    int motherPdgId(motherPdgId1==21 ? std::fabs(motherPdgId2) : std::fabs(motherPdgId1));
    // Usable with Pythia, not correct with MadGraph or Powheg
    //if(motherPdgId1!=-motherPdgId2)edm::LogError("Generator Behaviour")<<"Strange origin of Z, built from "<<i_genPart->mother(0)->pdgId()<<", "<<i_genPart->mother(1)->pdgId();
    // Usable with Powheg, but not with MadGraph
    //if(motherPdgId1!=-motherPdgId2 && motherPdgId1!=21 && motherPdgId2!=21 )edm::LogError("Generator Behaviour")<<"Strange origin of Z, built from "<<i_genPart->mother(0)->pdgId()<<", "<<i_genPart->mother(1)->pdgId();
    // Usable with All
    if(motherPdgId1!=-motherPdgId2 && motherPdgId1!=21 && motherPdgId2!=21 ){
      //edm::LogError("Generator Behaviour")<<"Strange origin of Z, built from "<<i_genPart->mother(0)->pdgId()<<", "<<i_genPart->mother(1)->pdgId();
      motherPdgId = 0;
    }
    
    Flavour flavour(unknown);
    if(motherPdgId == 1)flavour = down;
    else if (motherPdgId == 2)flavour = up;
    else if (motherPdgId == 3)flavour = strange;
    else if (motherPdgId == 4)flavour = charm;
    else if (motherPdgId == 5)flavour = bottom;
    if(motherPdgId >= 1 && motherPdgId <= 5)flavour = Flavour(motherPdgId);
    
    // Not usable with MadGraph
    //if(flavour==unknown)edm::LogError("Generator Behaviour")<<"Strange origin of Z, made of particles of type (PdgId): "<<motherPdgId;
    
    for(size_t iMother = 0; iMother < i_genPart->numberOfMothers(); ++iMother){
      const reco::GenParticle* motherQuark(dynamic_cast<const reco::GenParticle*>(i_genPart->mother(iMother)));
      //std::cout<<"\tMother quark no. "<<iMother<<" has ID "<<motherQuark->pdgId()<<" and Status "<<motherQuark->status()<<"\n";
      //std::cout<<"\tNo. of mothers: "<<motherQuark->numberOfMothers()<<", first has ID: "<<motherQuark->mother()->pdgId()<<", status "<<motherQuark->mother()->status()<<"\n";
      //std::cout<<"\tNo. of daughters: "<<motherQuark->numberOfDaughters()<<", first has ID: "<<motherQuark->daughter(0)->pdgId()<<", status "<<motherQuark->daughter(0)->status()<<"\n";
      //for(size_t iDaughter = 1; iDaughter < motherQuark->numberOfDaughters(); ++iDaughter){
        //std::cout<<"\tDaughter no. "<<iDaughter<<" has ID "<<motherQuark->daughter(iDaughter)->pdgId()<<", status "<<motherQuark->daughter(iDaughter)->status()<<"\n";
      //}
      if(motherQuark->numberOfMothers()!=1)edm::LogError("Generator Behaviour")<<"Strange origin of mother quark, not built from single parton, but "<<motherQuark->numberOfMothers();
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
    
    MuEtaLow->Fill(etaLow);
    MuEtaHigh->Fill(etaHigh);
    MuPtLow->Fill(ptLow);
    MuPtHigh->Fill(ptHigh);
    
    DiMuEta->Fill(diMuEta);
    DiMuPt->Fill(diMuPt);
    DiMuMass->Fill(diMuMass);
    
    ZEta->Fill(zEta);
    ZY->Fill(zY);
    ZPt->Fill(zPt);
    ZMass->Fill(zMass);
    
    ZQuarkOrigin->Fill(flavour-1);
    
    
    DiffY->Fill(zEta-diMuEta);
    DiffPt->Fill(zPt-diMuPt);
    DiffMass->Fill(zMass-diMuMass);
    
    ZMassVsDiMuMass->Fill(diMuMass,zMass);
  }
}


// ------------ method called once each job just before starting event loop  ------------
void 
GeneratorZmumuAnalyzer::beginJob(){
  edm::Service<TFileService> fileService;
  TFileDirectory dirSingleMu = fileService->mkdir("SingleMu");
  MuEtaLow = dirSingleMu.make<TH1F>("h_muEtaLow","muon with lower absolute value of #eta;#eta;# muons",200,-10,10);
  MuEtaHigh = dirSingleMu.make<TH1F>("h_muEtaHigh","muon with higher absolute value of #eta;#eta;# muons",200,-10,10);
  MuPtLow = dirSingleMu.make<TH1F>("h_muPtLow","muon with lower p_{t};p_{t}  [GeV];# muons",200,0,200);
  MuPtHigh = dirSingleMu.make<TH1F>("h_muPtHigh","muon with higher p_{t};p_{t}  [GeV];# muons",200,0,200);
  
  TFileDirectory dirDiMu = fileService->mkdir("DiMu");
  DiMuEta = dirDiMu.make<TH1F>("h_diMuEta","Pseudorapidity of combined muon pair;#eta;# muon pairs",200,-10,10);
  DiMuPt = dirDiMu.make<TH1F>("h_diMuPt","p_{t} of combined muon pair;p_{t}  [GeV];# muon pairs",200,0,200);
  DiMuMass = dirDiMu.make<TH1F>("h_diMuMass","invariant mass of muon pair;m_{#mu#mu}  [GeV];# muon pairs",200,0,200);
  
  TFileDirectory dirZ = fileService->mkdir("GeneratedZ");
  ZEta = dirZ.make<TH1F>("h_zEta","#eta of generated Z;#eta;# Z",200,-10,10);
  ZY = dirZ.make<TH1F>("h_zY","rapidity of generated Z;y;# Z",200,-10,10);
  ZPt = dirZ.make<TH1F>("h_zPt","p_{t} of generated Z;p_{t}  [GeV];# Z",200,0,200);
  ZMass = dirZ.make<TH1F>("h_zMass","invariant mass of Z;m_{Z} [GeV];# Z",200,0,200);
  ZQuarkOrigin = dirZ.make<TH1F>("h_zQuarkOrigin","quark origin of Z;;#Z",6,0,6);
  ZQuarkOrigin->GetXaxis()->SetBinLabel(1,"d");
  ZQuarkOrigin->GetXaxis()->SetBinLabel(2,"u");
  ZQuarkOrigin->GetXaxis()->SetBinLabel(3,"s");
  ZQuarkOrigin->GetXaxis()->SetBinLabel(4,"c");
  ZQuarkOrigin->GetXaxis()->SetBinLabel(5,"b");
  ZQuarkOrigin->GetXaxis()->SetBinLabel(6,"XXX");
  
  TFileDirectory dirDiff = fileService->mkdir("Difference");
  DiffY = dirDiff.make<TH1F>("h_diffEta","Difference of #eta for Z and dimuon;#eta_{Z}-#eta_{#mu#mu};# Z",100,-2,2);
  DiffPt = dirDiff.make<TH1F>("h_diffPt","Difference of p_{t} for Z and dimuon;p_{t,Z}-p_{t,#mu#mu}  [GeV];# Z",100,-50,50);
  DiffMass = dirDiff.make<TH1F>("h_diffMass","Difference of mass for Z and dimuon;m_{Z}-m_{#mu#mu}  [GeV];# Z",100,-50,50);
  
  ZMassVsDiMuMass = dirDiff.make<TH2F>("h2_zMassVsDiMuMass","m_{Z} vs. m_{#mu#mu};m_{#mu#mu} [GeV];m_{Z} [GeV]",100,0,200,100,0,200);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GeneratorZmumuAnalyzer::endJob(){
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(GeneratorZmumuAnalyzer);
