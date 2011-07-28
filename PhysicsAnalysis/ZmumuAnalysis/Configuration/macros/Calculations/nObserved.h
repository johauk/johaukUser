#include "ZmumuAnalysis/Configuration/macros/Tools/FullAnalysis.h"



#include "ZmumuAnalysis/Configuration/macros/Tools/eventCount.h"

#include <iostream>
#include <cmath>



void FullAnalysis::setNObserved(){
  if(!this->dataSample()){
    std::cout<<"\tMissing input sample\n"
             <<"\t... take dummy nObserved\n";
    nObserved_ = ValueAndError::dummyValues();
    std::cout<<"No. observed events (candidates): "<<this->nObserved().print()<<"\n";
    return;
  }
  const DataSample& data = *this->dataSample();
  
  
  TH1* events(0);
  events = eventCount(data.file(), this->recoSelectionStep());
  if(!events){
    std::cout<<"\tMissing is histogram containing no. of data events\n"
             <<"\t... nObserved calculation stopped\n";
    return;
  }
  const double nEvents(events->GetEntries());
  
  nObserved_.setValue(nEvents);
  nObserved_.setAbsErr2Up(nEvents);
  nObserved_.setAbsErr2Dw(nEvents);
  
  std::cout<<"No. observed events (candidates): "<<this->nObserved().print()<<"\n";

}












