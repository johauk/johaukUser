#include "ZmumuAnalysis/Configuration/macros/Tools/FullAnalysis.h"



#include "ZmumuAnalysis/Configuration/macros/Tools/eventCount.h"

#include <iostream>
#include <cmath>



void FullAnalysis::setNObservedSideband(const Sideband& sideband){
  if(!this->dataSample()){
    std::cout<<"\tMissing input sample\n"
             <<"\t... take dummy nObservedSideband\n";
    nObservedSideband_ = ValueAndError::dummyValues();
    std::cout<<"No. observed events (candidates): "<<this->nObservedSideband().print()<<"\n";
    return;
  }
  const DataSample& data = *this->dataSample();
  
  
  TH1* eventsOut1(0);
  if(sideband==upper || sideband==both){
    TString pluginSuffix(this->recoSelectionStep());
    pluginSuffix.Insert(4,"ZVetoHigh");
    eventsOut1 = eventCount(data.file(), pluginSuffix);
    if(!eventsOut1){
      std::cout<<"\tMissing is histogram containing no. of data events in sideband \"Out1\"\n"
               <<"\t... nObserved calculation stopped\n";
      return;
    }
  }
  const double nEventsOut1(eventsOut1 ? eventsOut1->GetEntries() : 0.);
  TH1* eventsOut2(0);
  if(sideband==lower || sideband==both){
    TString pluginSuffix(this->recoSelectionStep());
    pluginSuffix.Insert(4,"ZVetoLow");
    eventsOut2 = eventCount(data.file(), pluginSuffix);
    if(!eventsOut2){
      std::cout<<"\tMissing is histogram containing no. of data events in sideband \"Out2\"\n"
               <<"\t... ratioInOut calculation stopped\n";
      return;
    }
  }
  const double nEventsOut2(eventsOut2 ? eventsOut2->GetEntries() : 0.);
  const double nEventsOut(nEventsOut1 + nEventsOut2);
  nObservedSideband_.setValue(nEventsOut);
  nObservedSideband_.setAbsErr2Up(nEventsOut);
  nObservedSideband_.setAbsErr2Dw(nEventsOut);
  
  std::cout<<"No. observed events (candidates) in sidebands (Out1, Out2, Both): "
           <<nEventsOut1<<" , "<<nEventsOut2<<" , "<<this->nObservedSideband().value()<<"\n";
  std::cout<<"No. observed events (candidates) in sidebands: "<<this->nObservedSideband().print()<<"\n";

}










/*
void nObservedSideband(TString pluginSuffixOut1 = "", TString pluginSuffixOut2 = ""){
  
  
  std::cout<<"No. observed events (candidates) in sidebands (Out1, Out2, Both): "
           <<nEventsOut1<<" , "<<nEventsOut2<<" , "<<theNObservedSideband<<"\n";
  
  theNObservedSidebandRelErr2Up = 1./theNObservedSideband;
  theNObservedSidebandRelErr2Dw = 1./theNObservedSideband;
  
  const double nObservedAbsErrUp = theNObservedSideband*std::sqrt(theNObservedSidebandRelErr2Up);
  const double nObservedAbsErrDw = theNObservedSideband*std::sqrt(theNObservedSidebandRelErr2Dw);
  
  std::cout<<"No. observed events (candidates) in sidebands: "<<theNObservedSideband<<" + "<<nObservedAbsErrUp<<" - "<<nObservedAbsErrDw<<"\n";
}

*/














