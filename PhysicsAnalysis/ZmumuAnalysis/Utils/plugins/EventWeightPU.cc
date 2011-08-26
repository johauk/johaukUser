// -*- C++ -*-
//
// Package:    EventWeightPU
// Class:      EventWeightPU
// 
/**\class EventWeightPU EventWeightPU.cc ZmumuAnalysis/Utils/plugins/EventWeightPU.cc

 Description: Calculate event weight for MC samples due to pileup reweighting data/MC

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Johannes Hauk,,,DESY
//         Created:  Thu Jul 28 23:18:21 CEST 2011
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ParameterSet/interface/FileInPath.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "DataFormats/Common/interface/View.h"

//
// class declaration
//

class EventWeightPU : public edm::EDProducer {
   public:
      explicit EventWeightPU(const edm::ParameterSet&);
      ~EventWeightPU();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void endRun(edm::Run&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

      // ----------member data ---------------------------
      
      edm::FileInPath inTag_MCSampleFile;
      std::string inTag_MCSampleHistoName;
      edm::FileInPath inTag_DataFile;
      std::string inTag_DataHistoName;

      edm::InputTag inTag_PUSource;

      float inTag_PUSysShiftUp;
      float inTag_PUSysShiftDown;

      edm::LumiReWeighting LumiWeights_;

      reweight::PoissonMeanShifter PUShiftUp_;
      reweight::PoissonMeanShifter PUShiftDown_;

      double wght_;
      double wght_Up_;
      double wght_Down_;
      double wght3BX_;
      double wght3BX_Up_;
      double wght3BX_Down_;
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
EventWeightPU::EventWeightPU(const edm::ParameterSet& iConfig):
  inTag_MCSampleFile(iConfig.getParameter<edm::FileInPath>("MCSampleFile") ),
  inTag_MCSampleHistoName(iConfig.getParameter<std::string>("MCSampleHistoName") ),
  inTag_DataFile(iConfig.getParameter<edm::FileInPath>("DataFile") ),
  inTag_DataHistoName(iConfig.getParameter<std::string>("DataHistoName") ),
  inTag_PUSource(iConfig.getParameter<edm::InputTag>("PUSource") ),
  inTag_PUSysShiftUp(iConfig.getParameter<double>("PUSysShiftUp") ),
  inTag_PUSysShiftDown(iConfig.getParameter<double>("PUSysShiftDown") )

{
  LumiWeights_ = edm::LumiReWeighting(inTag_MCSampleFile.fullPath(),inTag_DataFile.fullPath(),inTag_MCSampleHistoName,inTag_DataHistoName);
  
  PUShiftUp_   = reweight::PoissonMeanShifter(inTag_PUSysShiftUp);
  PUShiftDown_ = reweight::PoissonMeanShifter(inTag_PUSysShiftDown);

  produces<double>("eventWeightPU");
  produces<double>("eventWeightPUUp");
  produces<double>("eventWeightPUDown");
  produces<double>("eventWeightPU3BX");  
  produces<double>("eventWeightPU3BXUp");
  produces<double>("eventWeightPU3BXDown");
}


EventWeightPU::~EventWeightPU()
{
}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
EventWeightPU::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  std::auto_ptr<double> eventWeightPU(new double); 
  std::auto_ptr<double> eventWeightPU_Up(new double); 
  std::auto_ptr<double> eventWeightPU_Down(new double); 
  std::auto_ptr<double> eventWeightPU3BX(new double);
  std::auto_ptr<double> eventWeightPU3BX_Up(new double);
  std::auto_ptr<double> eventWeightPU3BX_Down(new double);
  
  edm::Handle<edm::View<PileupSummaryInfo> > pPUInfo;
  iEvent.getByLabel(inTag_PUSource, pPUInfo);

  edm::View<PileupSummaryInfo>::const_iterator iterPU;

  // default values to allow for tracing errors
  
  wght_ = -1;
  *eventWeightPU = wght_;

  wght3BX_ = -1;
  *eventWeightPU3BX = wght3BX_;   

  float sum_nvtx = 0;
  
  for(iterPU = pPUInfo->begin(); iterPU != pPUInfo->end(); ++iterPU)  // vector size is 3
  { 
    sum_nvtx += iterPU->getPU_NumInteractions();

    if (iterPU->getBunchCrossing()==0) // -1: previous BX, 0: current BX,  1: next BX
    {
      int nvtx = iterPU->getPU_NumInteractions();

      wght_      = LumiWeights_.weight(nvtx);
      wght_Up_   = wght_ * PUShiftUp_.ShiftWeight(nvtx);
      wght_Down_ = wght_ * PUShiftDown_.ShiftWeight(nvtx);
    }
  }

  wght3BX_      = LumiWeights_.weight3BX(sum_nvtx/3.0);
  wght3BX_Up_   = wght3BX_ * PUShiftUp_.ShiftWeight(float(sum_nvtx/3.0));
  wght3BX_Down_ = wght3BX_ * PUShiftDown_.ShiftWeight(float(sum_nvtx/3.0));

  (*eventWeightPU)         = wght_;
  (*eventWeightPU_Up)      = wght_Up_;
  (*eventWeightPU_Down)    = wght_Down_;
  (*eventWeightPU3BX)      = wght3BX_;
  (*eventWeightPU3BX_Up)   = wght3BX_Up_;
  (*eventWeightPU3BX_Down) = wght3BX_Down_;
  
  iEvent.put(eventWeightPU,"eventWeightPU");
  iEvent.put(eventWeightPU_Up,"eventWeightPUUp");
  iEvent.put(eventWeightPU_Down,"eventWeightPUDown");
  iEvent.put(eventWeightPU3BX,"eventWeightPU3BX");
  iEvent.put(eventWeightPU3BX_Up,"eventWeightPU3BXUp");
  iEvent.put(eventWeightPU3BX_Down,"eventWeightPU3BXDown");
  
  //std::cout<<"EventWeightPU: "<<*eventWeightPU<<"\n";
  //std::cout<<"EventWeightPU3BX: "<<*eventWeightPU3BX<<"\n";
}

// ------------ method called once each job just before starting event loop  ------------
void 
EventWeightPU::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
EventWeightPU::endJob() {
}

// ------------ method called when starting to processes a run  ------------
void 
EventWeightPU::beginRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
EventWeightPU::endRun(edm::Run&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
EventWeightPU::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
EventWeightPU::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
EventWeightPU::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(EventWeightPU);
