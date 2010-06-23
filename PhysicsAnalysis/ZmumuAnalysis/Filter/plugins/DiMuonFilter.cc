// -*- C++ -*-
//
// Package:    DiMuonFilter
// Class:      DiMuonFilter
// 
/**\class DiMuonFilter DiMuonFilter.cc ZmumuAnalysis/Filter/plugins/DiMuonFilter.cc

 Description: Filter for combined di-muon properties

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Thu Jun 10 17:47:40 CEST 2010
// $Id: DiMuonFilter.cc,v 1.1 2010/06/22 16:02:44 hauk Exp $
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

#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "DataFormats/Candidate/interface/LeafCandidate.h"

#include "FWCore/Utilities/interface/EDMException.h"

//
// class declaration
//

class DiMuonFilter : public edm::EDFilter {
   public:
      explicit DiMuonFilter(const edm::ParameterSet&);
      ~DiMuonFilter();

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      const void checkFilter(const std::string&, const std::vector<double>& v_interval)const;
      const bool filterInterval(const double variable, const std::vector<double>& v_interval)const;
      
      // ----------member data ---------------------------
      
      const edm::ParameterSet parameterSet_;
      const bool allowSameCharge_;
      const bool allowOppositeCharge_;
      const std::vector<double> v_deltaEtaIntervals_;
      const std::vector<double> v_deltaPhiIntervals_;
      const std::vector<double> v_massIntervals_;
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
DiMuonFilter::DiMuonFilter(const edm::ParameterSet& iConfig):
parameterSet_(iConfig),
allowSameCharge_(parameterSet_.getParameter<bool>("allowSameCharge")),
allowOppositeCharge_(parameterSet_.getParameter<bool>("allowOppositeCharge")),
v_deltaEtaIntervals_(parameterSet_.getParameter<std::vector<double> >("deltaEtaIntervals")),
v_deltaPhiIntervals_(parameterSet_.getParameter<std::vector<double> >("deltaPhiIntervals")),
v_massIntervals_(parameterSet_.getParameter<std::vector<double> >("massIntervals")),
v_ptIntervals_(parameterSet_.getParameter<std::vector<double> >("ptIntervals"))
{
}


DiMuonFilter::~DiMuonFilter()
{
}


//
// member functions
//


const void
DiMuonFilter::checkFilter(const std::string& name, const std::vector<double>& v_interval)const{
  // No selection, so intervals are fine
  if(v_interval.size()==0){
    edm::LogInfo("DiMuonFilter")<<"No selection for "<<name;
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
        edm::LogInfo("DiMuonFilter")<<"Selected "<<name<<" interval no. "<<i_Entry/2<<": ["<<intervalBegin<<", "<<*i_interval<<"]";
      }
    }
  }
  
  return;
}



const bool
DiMuonFilter::filterInterval(const double variable, const std::vector<double>& v_interval)const{
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
DiMuonFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // get handle on muon collection
  const edm::InputTag muonSource(parameterSet_.getParameter<edm::InputTag>("muonSource"));
  edm::Handle<pat::MuonCollection> muons;
  iEvent.getByLabel(muonSource, muons);
  
  // reject if less than 2 muons
  if(muons->size()<2)return false;
  
  // get leading muons (in pt, since done on pat-tuples)
  const pat::MuonCollection::const_reference mu1 = muons->at(0);
  const pat::MuonCollection::const_reference mu2 = muons->at(1);

  // same or opposite charge?
  bool isSameCharge = false;
  if(mu1.charge()*mu2.charge()>0.) isSameCharge = true;
  if(!allowSameCharge_ && isSameCharge)return false;
  if(!allowOppositeCharge_ && !isSameCharge)return false;
  

  // eta difference
  double deltaEta = mu2.eta() - mu1.eta();
  if(!this->filterInterval(deltaEta, v_deltaEtaIntervals_))return false;
  
  // phi difference
  double deltaPhi = reco::deltaPhi(mu2.phi(),mu1.phi());
  if(!this->filterInterval(deltaPhi, v_deltaPhiIntervals_))return false;
  
  // create combined di-muon particle
  const reco::LeafCandidate::LorentzVector diMuVec = mu1.p4() + mu2.p4();
  
  // invariant mass
  const double diMuMass = diMuVec.M();
  if(!this->filterInterval(diMuMass, v_massIntervals_))return false;
  
  // pt
  const double diMuPt = diMuVec.pt();
  if(!this->filterInterval(diMuPt, v_ptIntervals_))return false;
  
  return true;
}

// ------------ method called once each job just before starting event loop  ------------
void 
DiMuonFilter::beginJob()
{
  // check charge filter settings
  if(!allowSameCharge_ && !allowOppositeCharge_){
    edm::LogError("Error in cfg file")<<"Both charge combinations are rejected, throw exception:";
    throw edm::Exception( edm::errors::Configuration,
                          "Both charge combinations are rejected in cfg file !!!\n" );
  }
  if(allowSameCharge_)edm::LogInfo("DiMuonFilter")<<"Muons with same charge are allowed";
  if(allowOppositeCharge_)edm::LogInfo("DiMuonFilter")<<"Muons with opposite charge are allowed";
  
  // check validity of all filter intervals taken from cfg
  this->checkFilter("deltaEta", v_deltaEtaIntervals_);
  this->checkFilter("deltaPhi", v_deltaPhiIntervals_);
  this->checkFilter("mass", v_massIntervals_);
  this->checkFilter("pt", v_ptIntervals_);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DiMuonFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(DiMuonFilter);
