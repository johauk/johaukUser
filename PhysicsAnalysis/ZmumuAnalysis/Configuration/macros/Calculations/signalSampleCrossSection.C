#include "ZmumuAnalysis/Configuration/macros/Tools/eventCount.h"

#include "ZmumuAnalysis/Configuration/macros/Samples/allSampleStruct.C"

#include <iostream>



double theSignalSampleCrossSection(-1.);

void signalSampleCrossSection(TString pluginSuffix = "Step1a"){
  const McStruct& zmumuB = *allSampleStruct.signalStruct_;
  
  TH1* events(0);
  events = eventCount(zmumuB.file_, pluginSuffix);

  if(!events){
    std::cout<<"\tMissing is histogram containing no. of signal events\n"
             <<"\t... singalSampleCrossSection calculation stopped\n";
    return;
  }
  const double nEvents(events->GetEntries());
  
  const double nEventsAll(zmumuB.nEvents_*zmumuB.dynamicWeight_);
  const double crossSectionAll(zmumuB.crossSection_);
  
  theSignalSampleCrossSection = crossSectionAll*nEvents/nEventsAll;
  
  std::cout<<"Cross section taken from signal sample: "<<theSignalSampleCrossSection<<"\n";
}












