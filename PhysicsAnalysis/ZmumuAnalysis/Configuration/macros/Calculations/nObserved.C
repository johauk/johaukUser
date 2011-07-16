#include "ZmumuAnalysis/Configuration/macros/Tools/eventCount.h"

#include "ZmumuAnalysis/Configuration/macros/Samples/allSampleStruct.C"

#include <iostream>
#include <cmath>



double theNObserved(-1.);

double theNObservedRelErr2Up(-1.);
double theNObservedRelErr2Dw(-1.);


void nObserved(TString pluginSuffix = ""){
  const DataStruct& data = *allSampleStruct.dataStruct_;
  
  TH1* events(0);
  events = eventCount(data.file_, pluginSuffix);
  
  if(!events){
    std::cout<<"\tMissing is histogram containing no. of data events\n"
             <<"\t... nObserved calculation stopped\n";
    return;
  }
  const double nEvents(events->GetEntries());
  
  theNObserved = nEvents;
  theNObservedRelErr2Up = 1./theNObserved;
  theNObservedRelErr2Dw = 1./theNObserved;
  
  const double nObservedAbsErrUp = theNObserved*std::sqrt(theNObservedRelErr2Up);
  const double nObservedAbsErrDw = theNObserved*std::sqrt(theNObservedRelErr2Dw);
  
  std::cout<<"No. observed events (candidates): "<<theNObserved<<" + "<<nObservedAbsErrUp<<" - "<<nObservedAbsErrDw<<"\n";
}
















