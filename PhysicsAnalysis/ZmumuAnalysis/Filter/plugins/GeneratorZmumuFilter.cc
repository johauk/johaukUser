// -*- C++ -*-
//
// Package:    GeneratorZmumuFilter
// Class:      GeneratorZmumuFilter
// 
/**\class GeneratorZmumuFilter GeneratorZmumuFilter.cc ZmumuAnalysis/Filter/plugins/GeneratorZmumuFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Wed Sep  1 15:49:35 CEST 2010
// $Id: GeneratorZmumuFilter.cc,v 1.7 2011/02/16 18:15:14 hauk Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"

#include "DataFormats/Math/interface/deltaPhi.h"

#include "FWCore/Utilities/interface/EDMException.h"
//
// class declaration
//

class GeneratorZmumuFilter : public edm::EDFilter {
   public:
      explicit GeneratorZmumuFilter(const edm::ParameterSet&);
      ~GeneratorZmumuFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      const void checkFilter(const std::string&, const std::vector<double>&)const;
      const bool filterInterval(const double, const std::vector<double>&)const;
      const bool filterQuarkOrigin(const reco::GenParticle& genPart, const std::vector<int>&)const;
      
      enum Flavour{down=1, up=2, strange=3, charm=4, bottom=5, unknown=6};
      
      // ----------member data ---------------------------
      
      const edm::ParameterSet parameterSet_;
      
      const std::vector<double> v_zMassIntervals_;
      
      const std::vector<double> v_diMuDeltaEtaIntervals_;
      const std::vector<double> v_diMuDeltaPhiIntervals_;
      const std::vector<double> v_diMuMassIntervals_;
      const std::vector<double> v_diMuPtIntervals_;
      
      const std::vector<double> v_muEtaLowIntervals_;
      const std::vector<double> v_muEtaHighIntervals_;
      const std::vector<double> v_muPtLowIntervals_;
      const std::vector<double> v_muPtHighIntervals_;
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
GeneratorZmumuFilter::GeneratorZmumuFilter(const edm::ParameterSet& iConfig):
parameterSet_(iConfig),
v_zMassIntervals_(parameterSet_.getParameter<std::vector<double> >("zMassIntervals")),
v_diMuDeltaEtaIntervals_(parameterSet_.getParameter<std::vector<double> >("diMuDeltaEtaIntervals")),
v_diMuDeltaPhiIntervals_(parameterSet_.getParameter<std::vector<double> >("diMuDeltaPhiIntervals")),
v_diMuMassIntervals_(parameterSet_.getParameter<std::vector<double> >("diMuMassIntervals")),
v_diMuPtIntervals_(parameterSet_.getParameter<std::vector<double> >("diMuPtIntervals")),
v_muEtaLowIntervals_(parameterSet_.getParameter<std::vector<double> >("muEtaLowIntervals")),
v_muEtaHighIntervals_(parameterSet_.getParameter<std::vector<double> >("muEtaHighIntervals")),
v_muPtLowIntervals_(parameterSet_.getParameter<std::vector<double> >("muPtLowIntervals")),
v_muPtHighIntervals_(parameterSet_.getParameter<std::vector<double> >("muPtHighIntervals"))
{
}


GeneratorZmumuFilter::~GeneratorZmumuFilter()
{
}


//
// member functions
//
const void
GeneratorZmumuFilter::checkFilter(const std::string& name, const std::vector<double>& v_interval)const{
  // No selection, so intervals are fine
  if(v_interval.size()==0){
    //edm::LogInfo("GeneratorZmumuFilter")<<"No selection for "<<name;
    return;
  }
  
  const std::string message("Incorrect interval definition in cfg file for: " + name + " !!!\n");
  
  // Odd no., of arguments cannot give intervals
  if(v_interval.size()%2==1){
    edm::LogError("Error in cfg file")<<"Odd number of arguments in interval definition of "<<name<<", throw exception:";
    throw edm::Exception( edm::errors::Configuration,
                          message );
  }
  
  // Every odd entry must be followed by one with bigger (or equal) value to define intervals
  int i_Entry(1);
  double intervalBegin(999.);
  for(std::vector<double>::const_iterator i_interval = v_interval.begin(); i_interval != v_interval.end(); ++i_interval, ++i_Entry){
    if(i_Entry%2==1)intervalBegin = *i_interval;
    if(i_Entry%2==0){
      if(intervalBegin>*i_interval){
        edm::LogError("Error in cfg file")<<"Incorrect interval definition of "<<name<<", entry "<<i_Entry-1<<" is smaller than entry "<<i_Entry<<", throw exception:";
        throw edm::Exception( edm::errors::Configuration,
                              message );
      }
      else{
        edm::LogInfo("GeneratorZmumuFilter")<<"Selected "<<name<<" interval no. "<<i_Entry/2<<": ["<<intervalBegin<<", "<<*i_interval<<"]";
      }
    }
  }
}



const bool
GeneratorZmumuFilter::filterInterval(const double variable, const std::vector<double>& v_interval)const{
  if(v_interval.size()==0)return true;
  int i_entry(1);
  double intervalBegin(999.);
  for(std::vector<double>::const_iterator i_interval = v_interval.begin(); i_interval != v_interval.end(); ++i_interval, ++i_entry){
    if(i_entry%2==1)intervalBegin = *i_interval;
    if(i_entry%2==0 && variable>=intervalBegin && variable<=*i_interval)return true;  // keep also interval borders absolutely symmetric 
  }
  return false;
}



const bool
GeneratorZmumuFilter::filterQuarkOrigin(const reco::GenParticle& genPart, const std::vector<int>& v_zQuarkOrigin)const{
  if(v_zQuarkOrigin.size()==0)return true;
  if(genPart.numberOfMothers()!=2)edm::LogError("Generator Behaviour")<<"Strange origin of Z, not built from two particles, but "<<genPart.numberOfMothers();
  const int motherPdgId1(genPart.mother()->pdgId());  // by default first one, so mother(0) is taken
  const int motherPdgId2(genPart.mother(1)->pdgId());
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
  
  for(std::vector<int>::const_iterator i_zQuarkOrigin = v_zQuarkOrigin.begin(); i_zQuarkOrigin != v_zQuarkOrigin.end(); ++i_zQuarkOrigin){
    if(flavour==Flavour(*i_zQuarkOrigin))return true;
  }
  return false;
}


// ------------ method called on each new Event  ------------
bool
GeneratorZmumuFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  const edm::InputTag inputTag(parameterSet_.getParameter<edm::InputTag>("src"));
  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(inputTag, genParticles);
  
  // all variable names are like in Z->mumu case, but act universally on Z->xx
  const std::vector<int> v_zDecayMode(parameterSet_.getParameter<std::vector<int> >("zDecayMode"));
  
  // Take care: when analysing events with more than one Z, not all have to be Z->xx with specified x
  bool zmumuFilter(false);
  
  bool allOtherFilters(false);
  
  const std::vector<int> v_zQuarkOrigin(parameterSet_.getParameter<std::vector<int> >("zQuarkOrigin"));
  
  
  for(reco::GenParticleCollection::const_iterator i_genPart = genParticles->begin(); i_genPart != genParticles->end(); ++i_genPart){
    bool isZmumu(false);
    
    bool quarkOriginFilter(false);
    
    bool zMassFilter(false);
    
    bool diMuDeltaEtaFilter(false);
    bool diMuDeltaPhiFilter(false);
    bool diMuPtFilter(false);
    bool diMuMassFilter(false);
  
    bool muEtaLowFilter(false);
    bool muEtaHighFilter(false);
    bool muPtLowFilter(false);
    bool muPtHighFilter(false);
    
    double etaMinus(-999.), etaPlus(-999.);
    double phiMinus(-999.), phiPlus(-999.);
    double ptMinus(-999.), ptPlus(-999.);
    //double zEta(-999.), zY(-999.), zPt(-999.);
    double zMass(-999.);
    reco::Candidate::LorentzVector lorVecMinus, lorVecPlus;
    if(i_genPart->pdgId()!=23 || i_genPart->status()!=3) continue;
    
    if(i_genPart->numberOfDaughters()!=3)edm::LogError("Generator Behaviour")<<"Strange decay of Z, not exactly 3 daughters, but: "<<i_genPart->numberOfDaughters()<<"\n";

    //zEta = i_genPart->eta();
    //zY = i_genPart->y();
    //zPt = i_genPart->pt();
    zMass = i_genPart->mass();
    
    for(size_t iDaughter = 0; iDaughter < i_genPart->numberOfDaughters(); ++iDaughter){
      const reco::GenParticle* daughter(dynamic_cast<const reco::GenParticle*>(i_genPart->daughter(iDaughter)));
      // select mu-
      for(std::vector<int>::const_iterator i_zDecayMode = v_zDecayMode.begin();i_zDecayMode != v_zDecayMode.end(); ++i_zDecayMode){
        if(daughter->pdgId() == (*i_zDecayMode)){
          lorVecMinus = daughter->p4();
          etaMinus = daughter->eta();
	  phiMinus = daughter->phi();
          ptMinus = daughter->pt();
          isZmumu = true;
        }
        // select mu+
        else if(daughter->pdgId() == -(*i_zDecayMode)){
          lorVecPlus = daughter->p4();
          etaPlus = daughter->eta();
	  phiPlus = daughter->phi();
          ptPlus = daughter->pt();
        }
      }
    }
    if(!isZmumu)continue;
    else zmumuFilter = true;
    
    
    //check flavour of mother quarks qqbar->Z
    quarkOriginFilter = this->filterQuarkOrigin(*i_genPart, v_zQuarkOrigin);
    if(!quarkOriginFilter)continue;
    
    
    const reco::Candidate::LorentzVector diMuVec = lorVecMinus + lorVecPlus;
    const double diMuMass = diMuVec.M();
    const double diMuPt = diMuVec.pt();
    const double diMuDeltaEta = etaPlus - etaMinus;
    const double diMuDeltaPhi = reco::deltaPhi(phiPlus,phiMinus);
    
    const double muEtaLow = std::fabs(etaMinus)<std::fabs(etaPlus) ? etaMinus : etaPlus;
    const double muEtaHigh = std::fabs(etaMinus)>std::fabs(etaPlus) ? etaMinus : etaPlus;
    const double muPtLow = ptMinus<ptPlus ? ptMinus : ptPlus;
    const double muPtHigh = ptMinus>ptPlus ? ptMinus : ptPlus;
    
    if(this->filterInterval(zMass, v_zMassIntervals_))zMassFilter = true;
    
    if(this->filterInterval(diMuDeltaEta, v_diMuDeltaEtaIntervals_))diMuDeltaEtaFilter = true;
    if(this->filterInterval(diMuDeltaPhi, v_diMuDeltaPhiIntervals_))diMuDeltaPhiFilter = true;
    if(this->filterInterval(diMuMass, v_diMuMassIntervals_))diMuMassFilter = true;
    if(this->filterInterval(diMuPt, v_diMuPtIntervals_))diMuPtFilter = true;
    
    if(this->filterInterval(muEtaLow, v_muEtaLowIntervals_))muEtaLowFilter = true;
    if(this->filterInterval(muEtaHigh, v_muEtaHighIntervals_))muEtaHighFilter = true;
    if(this->filterInterval(muPtLow, v_muPtLowIntervals_))muPtLowFilter = true;
    if(this->filterInterval(muPtHigh, v_muPtHighIntervals_))muPtHighFilter = true;
    
    if(!zMassFilter ||
       !diMuDeltaEtaFilter || !diMuDeltaPhiFilter ||
       !diMuMassFilter || !diMuPtFilter ||
       !muEtaLowFilter || !muEtaHighFilter ||
       !muPtLowFilter || !muPtHighFilter)continue;
    
    allOtherFilters = true;
  }
  // Is at least one Z->mumu present?
  if(!zmumuFilter)return false;
  // Does it fulfil all other requirements?
  if(!allOtherFilters)return false;
  
  // All filters fulfilled...
  return true;
}



// ------------ method called once each job just before starting event loop  ------------
void 
GeneratorZmumuFilter::beginJob()
{
  // check validity of all filter intervals taken from cfg
  this->checkFilter("zMass", v_zMassIntervals_);
  this->checkFilter("diMuDeltaEta", v_diMuDeltaEtaIntervals_);
  this->checkFilter("diMuDeltaPhi", v_diMuDeltaPhiIntervals_);
  this->checkFilter("diMuMass", v_diMuMassIntervals_);
  this->checkFilter("diMuPt", v_diMuPtIntervals_);
  this->checkFilter("muEtaLow", v_muEtaLowIntervals_);
  this->checkFilter("muEtaHigh", v_muEtaHighIntervals_);
  this->checkFilter("muPtLow", v_muPtLowIntervals_);
  this->checkFilter("muPtHigh", v_muPtHighIntervals_);
}



// ------------ method called once each job just after ending the event loop  ------------
void 
GeneratorZmumuFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(GeneratorZmumuFilter);
