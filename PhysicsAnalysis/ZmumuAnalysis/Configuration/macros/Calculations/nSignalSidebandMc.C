#include "ZmumuAnalysis/Configuration/macros/Tools/eventCount.h"

#include "ZmumuAnalysis/Configuration/macros/Samples/allSampleStruct.C"

#include <iostream>



double theNSignalSidebandMc(-1.);



void nSignalSidebandMc(const TString pluginSuffixOut1 = "", const TString pluginSuffixOut2 = ""){
  const DataStruct& data = *allSampleStruct.dataStruct_;
  const double luminosity(data.lumi_);
  const double effectiveLuminosity(luminosity*data.dynamicWeight_);
  
  const McStruct& zmumuB = *allSampleStruct.signalStruct_;
  
  TH1* eventsOut1(0);
  eventsOut1 = eventCount(zmumuB.file_, pluginSuffixOut1);
  if(!eventsOut1){
    std::cout<<"\tMissing is histogram containing no. of MC events for \"Out1\": "<<zmumuB.datasetName_<<"\n"
  	     <<"\t... ratioInOut calculation stopped\n";
    return;
  }
  const double nEventsOut1(eventsOut1->GetEntries());
  
  TH1* eventsOut2(0);
  if(pluginSuffixOut2 != ""){
    eventsOut2 = eventCount(zmumuB.file_, pluginSuffixOut2);
    if(!eventsOut2){
      std::cout<<"\tMissing is histogram containing no. of MC events for \"Out2\": "<<zmumuB.datasetName_<<"\n"
  	       <<"\t... ratioInOut calculation stopped\n";
      return;
    }
  }
  const double nEventsOut2(eventsOut2 ? eventsOut2->GetEntries() : 0.);
  const double nEventsOut(nEventsOut1 + nEventsOut2);
  const double nEffectiveEventsOut(nEventsOut/zmumuB.dynamicWeight_);
  
  const double nEventsSample(zmumuB.nEvents_);
  const double effectiveCrossSection(zmumuB.crossSection_*zmumuB.filterEfficiency_);
  const double correspondingLuminosity(nEventsSample/effectiveCrossSection);
  const double weight(effectiveLuminosity/correspondingLuminosity);
  
  //const double nWeightedEventsOut(nEventsOut*weight);
  const double nEffectiveWeightedEventsOut(nEffectiveEventsOut*weight);
  
  std::cout<<"No. unweighted sideband events (Out1, Out2, Both) for signal MC: "
  	     <<nEventsOut1<<" , "<<nEventsOut2<<" , "<<nEventsOut<<"\n";
  
  
  
  theNSignalSidebandMc = nEffectiveWeightedEventsOut;
  
  std::cout<<"No. effective weighted MC signal events in sideband: "<<theNSignalSidebandMc<<"\n";
}
















