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
// $Id$
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
      
      // ----------member data ---------------------------
      
      const edm::ParameterSet parameterSet_;
      
      const std::vector<double> v_diMuDeltaEtaIntervals_;
      const std::vector<double> v_diMuDeltaPhiIntervals_;
      const std::vector<double> v_diMuMassIntervals_;
      const std::vector<double> v_diMuPtIntervals_;
      
      const std::vector<double> v_etaIntervals_;
      const std::vector<double> v_ptIntervals_;
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
v_diMuDeltaEtaIntervals_(parameterSet_.getParameter<std::vector<double> >("diMuDeltaEtaIntervals")),
v_diMuDeltaPhiIntervals_(parameterSet_.getParameter<std::vector<double> >("diMuDeltaPhiIntervals")),
v_diMuMassIntervals_(parameterSet_.getParameter<std::vector<double> >("diMuMassIntervals")),
v_diMuPtIntervals_(parameterSet_.getParameter<std::vector<double> >("diMuPtIntervals")),
v_etaIntervals_(parameterSet_.getParameter<std::vector<double> >("etaIntervals")),
v_ptIntervals_(parameterSet_.getParameter<std::vector<double> >("ptIntervals"))
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
    edm::LogInfo("GeneratorZmumuFilter")<<"No selection for "<<name;
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



// ------------ method called on each new Event  ------------
bool
GeneratorZmumuFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  const edm::InputTag inputTag(parameterSet_.getParameter<edm::InputTag>("src"));
  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(inputTag, genParticles);
  
  // Take care: when analysing events with more than one Z, not all have to be Z->mumu
  bool zmumuFilter(false);
  
  bool diMuDeltaEtaFilter(false);
  bool diMuDeltaPhiFilter(false);
  bool diMuPtFilter(false);
  bool diMuMassFilter(false);
  
  bool etaFilter(false);
  bool ptFilter(false);
  
  for(reco::GenParticleCollection::const_iterator iGenPart = genParticles->begin(); iGenPart != genParticles->end(); ++iGenPart){
    bool isZmumu(false);
    double etaMinus(-999.), etaPlus(-999.);
    double phiMinus(-999.), phiPlus(-999.);
    double ptMinus(-999.), ptPlus(-999.);
    double etaZ(-999.), ptZ(-999.);
    reco::Candidate::LorentzVector lorVecMinus, lorVecPlus;
    if(iGenPart->pdgId()!=23 || iGenPart->status()!=3) continue;
    
    etaZ = iGenPart->eta();
    ptZ = iGenPart->pt();
    
    for(size_t iDaughter = 0; iDaughter < iGenPart->numberOfDaughters(); ++iDaughter){
      const reco::GenParticle* daughter(dynamic_cast<const reco::GenParticle*>(iGenPart->daughter(iDaughter)));
      // select mu-
      if(daughter->pdgId()==13){
        lorVecMinus = daughter->p4();
        etaMinus = daughter->eta();
	phiMinus = daughter->phi();
        ptMinus = daughter->pt();
        isZmumu = true;
      }
      // select mu+
      else if(daughter->pdgId()==-13){
        lorVecPlus = daughter->p4();
        etaPlus = daughter->eta();
	phiPlus = daughter->phi();
        ptPlus = daughter->pt();
      }
    }
    if(!isZmumu)continue;
    else zmumuFilter = true;
    
    const reco::Candidate::LorentzVector diMuVec = lorVecMinus + lorVecPlus;
    const double diMuMass = diMuVec.M();
    const double diMuPt = diMuVec.pt();
    //const double etaLow = std::fabs(etaMinus)<std::fabs(etaPlus) ? etaMinus : etaPlus;
    //const double etaHigh = std::fabs(etaMinus)>std::fabs(etaPlus) ? etaMinus : etaPlus;
    //const double ptLow = ptMinus<ptPlus ? ptMinus : ptPlus;
    //const double ptHigh = ptMinus>ptPlus ? ptMinus : ptPlus;
    const double diMuDeltaEta = etaPlus - etaMinus;
    const double diMuDeltaPhi = reco::deltaPhi(phiPlus,phiMinus);
    
    if(this->filterInterval(diMuDeltaEta, v_diMuDeltaEtaIntervals_))diMuDeltaEtaFilter = true;
    if(this->filterInterval(diMuDeltaPhi, v_diMuDeltaPhiIntervals_))diMuDeltaPhiFilter = true;
    if(this->filterInterval(diMuMass, v_diMuMassIntervals_))diMuPtFilter = true;
    if(this->filterInterval(diMuPt, v_diMuPtIntervals_))diMuMassFilter = true;
    
    if(this->filterInterval(etaMinus, v_etaIntervals_) && this->filterInterval(etaPlus, v_etaIntervals_))etaFilter = true;
    if(this->filterInterval(ptMinus, v_ptIntervals_) && this->filterInterval(ptPlus, v_ptIntervals_))ptFilter = true;
  }
  // Is at least one Z->mumu present?
  if(!zmumuFilter)return false;
  // Does it fulfil all other requirements?
  if(!diMuDeltaEtaFilter || !diMuDeltaPhiFilter ||
     !diMuPtFilter || !diMuMassFilter ||
     !etaFilter || !ptFilter)return false;
  
  // All filters fulfilled...
  return true;
}



// ------------ method called once each job just before starting event loop  ------------
void 
GeneratorZmumuFilter::beginJob()
{
  // check validity of all filter intervals taken from cfg
  this->checkFilter("diMuDeltaEta", v_diMuDeltaEtaIntervals_);
  this->checkFilter("diMuDeltaPhi", v_diMuDeltaPhiIntervals_);
  this->checkFilter("diMuMass", v_diMuMassIntervals_);
  this->checkFilter("diMuPt", v_diMuPtIntervals_);
  this->checkFilter("muEta", v_etaIntervals_);
  this->checkFilter("muPt", v_ptIntervals_);
}



// ------------ method called once each job just after ending the event loop  ------------
void 
GeneratorZmumuFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(GeneratorZmumuFilter);
