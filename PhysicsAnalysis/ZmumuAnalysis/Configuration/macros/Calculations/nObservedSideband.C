#include "efficiency.h"

#include "ZmumuAnalysis/Configuration/macros/Samples/allSampleStruct.C"

#include <iostream>



double theNObservedSideband(-1.);



void nObservedSideband(TString pluginSuffixOut1 = "", TString pluginSuffixOut2 = ""){
  const DataStruct& data = *allSampleStruct.dataStruct;
  
  TH1* eventsOut1(0);
  eventsOut1 = Efficiency::Events(data.file_, pluginSuffixOut1);
  
  if(!eventsOut1){
    std::cout<<"\tMissing is histogram containing no. of data events in sideband \"Out1\"\n"
             <<"\t... nObserved calculation stopped\n";
    return;
  }
  const double nEventsOut1(eventsOut1->GetEntries());
  
  TH1* eventsOut2(0);
  if(pluginSuffixOut2 != ""){
    eventsOut2 = Efficiency::Events(data.file_, pluginSuffixOut2);
    if(!eventsOut2){
      std::cout<<"\tMissing is histogram containing no. of data events in sideband \"Out2\"\n"
               <<"\t... ratioInOut calculation stopped\n";
      return;
    }
  }
  const double nEventsOut2(eventsOut2 ? eventsOut2->GetEntries() : 0.);
  
  
  theNObservedSideband = nEventsOut1 + nEventsOut2;
  
  
  std::cout<<"No. observed events (candidates) in sidebands (Out1, Out2, Both): "
           <<nEventsOut1<<" , "<<nEventsOut2<<" , "<<theNObservedSideband<<"\n";
}
















