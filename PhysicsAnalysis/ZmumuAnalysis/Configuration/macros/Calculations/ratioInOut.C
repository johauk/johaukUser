#include "ZmumuAnalysis/Configuration/macros/Tools/eventCount.h"

#include "ZmumuAnalysis/Configuration/macros/Samples/allSampleStruct.C"

#include <iostream>



double theRatioInOut(-1.);

void ratioInOut(TString pluginSuffixIn = "", TString pluginSuffixOut1 = "", TString pluginSuffixOut2 = ""){
  const std::vector<McStruct*> v_background = allSampleStruct.v_backgroundStruct;
  
  double ttbarRatioInOut(-1.);
  std::vector<McStruct*>::const_iterator i_background;
  for(i_background = v_background.begin(); i_background != v_background.end(); ++i_background){
    const McStruct& background = **i_background;

    TH1* eventsIn(0);
    eventsIn = eventCount(background.file_, pluginSuffixIn);
    if(!eventsIn){
      std::cout<<"\tMissing is histogram containing no. of MC events for \"In\": "<<background.datasetName_<<"\n"
               <<"\t... ratioInOut calculation stopped\n";
      return;
    }
    const double nEventsIn(eventsIn->GetEntries());
    
    TH1* eventsOut1(0);
    eventsOut1 = eventCount(background.file_, pluginSuffixOut1);
    if(!eventsOut1){
      std::cout<<"\tMissing is histogram containing no. of MC events for \"Out1\": "<<background.datasetName_<<"\n"
               <<"\t... ratioInOut calculation stopped\n";
      return;
    }
    const double nEventsOut1(eventsOut1->GetEntries());
    
    TH1* eventsOut2(0);
    if(pluginSuffixOut2 != ""){
      eventsOut2 = eventCount(background.file_, pluginSuffixOut2);
      if(!eventsOut2){
        std::cout<<"\tMissing is histogram containing no. of MC events for \"Out2\": "<<background.datasetName_<<"\n"
                 <<"\t... ratioInOut calculation stopped\n";
        return;
      }
    }
    const double nEventsOut2(eventsOut2 ? eventsOut2->GetEntries() : 0.);
    const double nEventsOut(nEventsOut1 + nEventsOut2);
    
    const double ratioInOut(!isnan(nEventsIn/nEventsOut) && !isinf(nEventsIn/nEventsOut) ? nEventsIn/nEventsOut : -1.);
    
    std::cout<<"Used no. of events (In, Out1, Out2) for \""<<background.datasetName_<<"\": "
             <<nEventsIn<<" , "<<nEventsOut1<<" , "<<nEventsOut2<<"\n";
    std::cout<<"Ratio In/Out for \""<<background.datasetName_<<"\": "
             <<ratioInOut<<"\n";
    
    if(background.datasetName_=="ttbar")ttbarRatioInOut = ratioInOut;
  }
  
  {
    const McStruct& zmumuB = *allSampleStruct.signalStruct;
    TH1* eventsIn(0);
    eventsIn = eventCount(zmumuB.file_, pluginSuffixIn);
    if(!eventsIn){
      std::cout<<"\tMissing is histogram containing no. of MC events for \"In\": "<<zmumuB.datasetName_<<"\n"
               <<"\t... ratioInOut calculation stopped\n";
      return;
    }
    const double nEventsIn(eventsIn->GetEntries());
    
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
    
    const double ratioInOut(!isnan(nEventsIn/nEventsOut) && !isinf(nEventsIn/nEventsOut) ? nEventsIn/nEventsOut : -1.);
    
    std::cout<<"Used no. of events (In, Out1, Out2) for \""<<zmumuB.datasetName_<<"\": "
             <<nEventsIn<<" , "<<nEventsOut1<<" , "<<nEventsOut2<<"\n";
    std::cout<<"Ratio In/Out for \""<<zmumuB.datasetName_<<"\": "
             <<ratioInOut<<"\n";
  }
  
  
  theRatioInOut = ttbarRatioInOut;
  
  
  std::cout<<"Ratio of ttbar for background estimation: "<<theRatioInOut<<"\n";
}




