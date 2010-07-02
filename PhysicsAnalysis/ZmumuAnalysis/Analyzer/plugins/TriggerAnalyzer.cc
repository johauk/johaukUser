// -*- C++ -*-
//
// Package:    TriggerAnalyzer
// Class:      TriggerAnalyzer
// 
/**\class TriggerAnalyzer TriggerAnalyzer.cc ZmumuAnalysis/Analyzer/plugins/TriggerAnalyzer.cc

 Description: Plotter for trigger rates

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Tue Jun  8 11:21:18 CEST 2010
// $Id: TriggerAnalyzer.cc,v 1.1 2010/06/22 15:46:28 hauk Exp $
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

#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"

#include "FWCore/Utilities/interface/EDMException.h"

#include "TH1.h"
#include "TH2.h"

//
// class declaration
//

class TriggerAnalyzer : public edm::EDAnalyzer {
   public:
      explicit TriggerAnalyzer(const edm::ParameterSet&);
      ~TriggerAnalyzer();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      const double binomialError(const double&, const double&)const;
      
      // ----------member data ---------------------------
      
      const edm::ParameterSet parameterSet_;
      
      const std::vector<std::string> hltPaths_;
      
      unsigned int n_events_;
      
      /// Shows which selected triggers have fired
      TH1 *TrigsFired;
      
      /// Shows if event fired at least one of selected triggers
      TH1 *TrigSelPassed;
      
      /// Shows correlations between selected triggers
      TH1 *Correlations;
      
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
TriggerAnalyzer::TriggerAnalyzer(const edm::ParameterSet& iConfig):
parameterSet_(iConfig), hltPaths_(parameterSet_.getParameter<std::vector<std::string> >("hltPaths")),
n_events_(0)
{
}


TriggerAnalyzer::~TriggerAnalyzer()
{
}


//
// member functions
//

const double
TriggerAnalyzer::binomialError(const double& numerator, const double& denominator)const
{      
  if(numerator>denominator) return 999999.;
  
  double error;
  error=sqrt((1-numerator/denominator)*numerator/denominator/denominator);
     
  return error;
}



// ------------ method called to for each event  ------------
void
TriggerAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // get handle on collections
  const edm::InputTag triggerResults(parameterSet_.getParameter<edm::InputTag>("triggerResults"));
  edm::Handle<edm::TriggerResults> trigResults; 
  iEvent.getByLabel(triggerResults, trigResults); 
  if(trigResults.failedToGet()){
    edm::LogError("Problematic Product")<<"Failed to get trigger results, check InputTag in cfg file"
                                        <<"\n...skip event in Analyzer";
    return;
  }
  
  bool trigFired(false);
  const unsigned int nTrig(trigResults->size());
  const unsigned int nTrigPath(hltPaths_.size());
  const edm::TriggerNames trigNames = iEvent.triggerNames(*trigResults);
  for(size_t iTrig=0; iTrig<nTrig; ++iTrig){
    //std::cout<<"Trigger name: "<<trigNames.triggerName(iTrig)<<"\n";
    if(!trigResults.product()->accept(iTrig))continue;
    for(size_t iTrigPath=0; iTrigPath<nTrigPath; ++iTrigPath){
      if(trigNames.triggerName(iTrig)!=hltPaths_[iTrigPath])continue;
      trigFired = true;
      TrigsFired->Fill(iTrigPath);
      
      for(size_t iTrig2=0; iTrig2<nTrig; ++iTrig2){
        if(!trigResults.product()->accept(iTrig2))continue;
	for(size_t iTrigPath2=0; iTrigPath2<iTrigPath; ++iTrigPath2){
	  if(trigNames.triggerName(iTrig2)!=hltPaths_[iTrigPath2])continue;
	  Correlations->Fill(iTrigPath,iTrigPath2);
	  break;
	}
      }
      
      break;
    }
  }
  
  TrigSelPassed->Fill(trigFired);
  
  ++n_events_;
}


// ------------ method called once each job just before starting event loop  ------------
void 
TriggerAnalyzer::beginJob(){
  edm::Service<TFileService> fileService;
  if(!fileService){
    throw edm::Exception( edm::errors::Configuration,
                          "TFileService is not registered in cfg file" );
  }
  
  const unsigned int nTrigPath(hltPaths_.size());
  
  TFileDirectory dirTrig = fileService->mkdir("TriggerProperties");
  
  TrigsFired = dirTrig.make<TH1F>("h_trigsFired","Trigger efficiencies;Trigger Path;#epsilon",nTrigPath,0,nTrigPath);
  for(size_t iTrigPath=0; iTrigPath<nTrigPath; ++iTrigPath){  
    TrigsFired->GetXaxis()->SetBinLabel(iTrigPath+1, hltPaths_[iTrigPath].c_str());
  }
  
  TrigSelPassed = dirTrig.make<TH1F>("h_trigSelPassed","Total efficiency;Trigger status;#epsilon_{tot}",2,0,2);
  TrigSelPassed->GetXaxis()->SetBinLabel(1, "failed");
  TrigSelPassed->GetXaxis()->SetBinLabel(2, "passed");
  
  Correlations = dirTrig.make<TH2F>("h2_correlations","Trigger correlations;Trigger path;Trigger path",nTrigPath,0,nTrigPath,nTrigPath,0,nTrigPath);
  for(size_t iTrigPath=0; iTrigPath<nTrigPath; ++iTrigPath){  
    Correlations->GetXaxis()->SetBinLabel(iTrigPath+1, hltPaths_[iTrigPath].c_str());
    Correlations->GetYaxis()->SetBinLabel(iTrigPath+1, hltPaths_[iTrigPath].c_str());
  }
  
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TriggerAnalyzer::endJob(){
  // Normalise hists to no. of events
  const double n_events(static_cast<double>(n_events_));
  // cannot use size_t, since would be comparison between signed and unsigned expression
  for(int i_Trig = 1; i_Trig <= TrigsFired->GetNbinsX(); ++i_Trig){
    TrigsFired->SetBinContent(i_Trig,TrigsFired->GetBinContent(i_Trig)/n_events);
    TrigsFired->SetBinError(i_Trig,this->binomialError(TrigsFired->GetBinContent(i_Trig)*n_events, n_events));
  }
  
  for(int i_Trig = 1; i_Trig <= TrigSelPassed->GetNbinsX(); ++i_Trig){
    TrigSelPassed->SetBinContent(i_Trig,TrigSelPassed->GetBinContent(i_Trig)/n_events);
    TrigSelPassed->SetBinError(i_Trig,this->binomialError(TrigSelPassed->GetBinContent(i_Trig)*n_events, n_events));
  }
}

//define this as a plug-in
DEFINE_FWK_MODULE(TriggerAnalyzer);
