// -*- C++ -*-
//
// Package:    RunEventListing
// Class:      RunEventListing
// 
/**\class RunEventListing RunEventListing.cc ZmumuAnalysis/Utils/plugins/RunEventListing.cc

 Description: Class to print list of processed event (and run) numbers

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Sat May 14 21:44:38 CEST 2011
// $Id: RunEventListing.cc,v 1.1 2011/05/14 21:33:42 hauk Exp $
//
//


// system include files
#include <memory>
#include <fstream>
#include <sstream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"

#include "TTree.h"

//
// class declaration
//

class RunEventListing : public edm::EDAnalyzer {
   public:
      explicit RunEventListing(const edm::ParameterSet&);
      ~RunEventListing();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      
      void createOutputTextFile(std::ofstream& outputTextFile)const;
      void createOutputRootFile(TTree*&, unsigned int&, unsigned int&, unsigned int&)const;
      // ----------member data ---------------------------
      
      const edm::ParameterSet parameterSet_;
      
      typedef std::vector<unsigned int> Events;
      typedef std::map<unsigned int, Events> LumiEvents;
      typedef std::map<unsigned int, LumiEvents> RunLumiEvents;
      
      RunLumiEvents runLumiEvents_;
      
      unsigned int nEvent_;
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
RunEventListing::RunEventListing(const edm::ParameterSet& iConfig):
parameterSet_(iConfig), nEvent_(0)
{
}


RunEventListing::~RunEventListing()
{
}


//
// member functions
//

// ------------ method called for each event  ------------
void
RunEventListing::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  const unsigned int run(iEvent.id().run());
  const unsigned int lumiBlock(iEvent.id().luminosityBlock());
  const unsigned int event(iEvent.id().event());
  
  runLumiEvents_[run][lumiBlock].push_back(event);
  
  ++nEvent_;
}


// ------------ method called once each job just before starting event loop  ------------
void 
RunEventListing::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
RunEventListing::endJob() 
{
  // Check which output modes are chosen
  const bool printToCommandLine(parameterSet_.getParameter<bool>("printToCommandLine"));
  const bool printToFile(parameterSet_.getParameter<bool>("printToFile"));
  const bool createTree(parameterSet_.getParameter<bool>("createTree"));
  if(!printToCommandLine && !printToFile && !createTree){
    edm::LogError("RunEventListing")<<"No output method is specified in RunEventListing ...\n"
                                    <<"Stop Plugin";
    return;
  }
  
  unsigned int run(0), lumiBlock(0), event(0);
  
  // Create text output file, if asked for in config
  std::ofstream outputTextFile;
  if(printToFile)this->createOutputTextFile(outputTextFile);
  
  // Create TTree output, if asked for in config
  TTree* eventTree(0);
  if(createTree)this->createOutputRootFile(eventTree, run, lumiBlock, event);
  
  std::cout<<"Number of selected events: "<<nEvent_<<"\n";
  RunLumiEvents::iterator i_run;
  for(i_run = runLumiEvents_.begin(); i_run != runLumiEvents_.end(); ++i_run){
    run = i_run->first;
    LumiEvents& lumiEvents(i_run->second);
    LumiEvents::iterator i_lumi;
    for(i_lumi = lumiEvents.begin(); i_lumi != lumiEvents.end(); ++i_lumi){
      lumiBlock = i_lumi->first;
      Events& events(i_lumi->second);
      std::sort(events.begin(), events.end());
      Events::iterator i_event;
      for(i_event = events.begin(); i_event != events.end(); ++i_event){
	event = *i_event;
	std::stringstream ssOutput;
	ssOutput<<"'"<<run<<":"<<lumiBlock<<":"<<event<<"',"<<"\n";
	if(printToCommandLine)std::cout<<ssOutput.str();
	if(outputTextFile.is_open())outputTextFile<<ssOutput.str();
	if(eventTree)eventTree->Fill();
      }
    }
  }
  
  
  if(outputTextFile.is_open())outputTextFile.close();
  if(eventTree)eventTree->Print();
}



void
RunEventListing::createOutputTextFile(std::ofstream& outputTextFile)const{
  const std::string outputTextFileName(parameterSet_.getParameter<std::string>("outputTextFile"));
  outputTextFile.open(outputTextFileName.c_str());
  if(outputTextFile.is_open()){
    edm::LogInfo("RunEventListing")<<"Output text file sucessfully opened";
    outputTextFile<<"import FWCore.ParameterSet.Config as cms\n\n";
    outputTextFile<<"source.eventsToProcess = cms.untracked.VEventRange()\n\n";
    outputTextFile<<"# These are "<<nEvent_<<" selected events\n";
    outputTextFile<<"eventsToProcess.extend( [\n";
  }
  else{
    edm::LogError("RunEventListing")<<"Output text file could not be opened !!!\n"
                                    <<"Check name: "<<outputTextFileName.c_str();
  }
}



void
RunEventListing::createOutputRootFile(TTree*& eventTree, unsigned int& run, unsigned int& lumiBlock, unsigned int& event)const{
  edm::Service<TFileService> fileService;
  if(!fileService){
    edm::LogError("RunEventListing")<<"No TFileService in config file, but required ...\n"
                                    <<"TTree is not created";
  }
  else{
    TFileDirectory dirTree = fileService->mkdir("EventTree");
    eventTree = dirTree.make<TTree>("eventTree","Tree containing event numbers");
  }
  //eventTree = new TTree("eventTree","Tree containing event numbers");
  
  if(eventTree){
    eventTree->Branch("Run", &run, "Run/i");
    eventTree->Branch("LumiBlock", &lumiBlock, "LumiBlock/i");
    eventTree->Branch("Event", &event, "Event/i");
  }
}




// ------------ method called when starting to processes a run  ------------
void 
RunEventListing::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
RunEventListing::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
RunEventListing::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
RunEventListing::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
RunEventListing::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(RunEventListing);
