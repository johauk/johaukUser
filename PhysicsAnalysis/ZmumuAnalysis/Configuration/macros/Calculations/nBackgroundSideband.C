#include "ZmumuAnalysis/Configuration/macros/Tools/eventCount.h"

#include "ZmumuAnalysis/Configuration/macros/Samples/allSampleStruct.C"



double theNBackgroundWoTopSideband(-1.);



void nBackgroundSideband(TString pluginSuffixOut1 = "", TString pluginSuffixOut2 = ""){
  const DataStruct& data = *allSampleStruct.dataStruct;
  const double luminosity(data.lumi_);
  const double effectiveLuminosity(luminosity*data.dynamicWeight_);
  
  const std::vector<McStruct*> v_background = allSampleStruct.v_backgroundStruct;
  
  double nBackgroundSideband(0.);
  std::vector<McStruct*>::const_iterator i_background;
  for(i_background = v_background.begin(); i_background != v_background.end(); ++i_background){
    const McStruct& background = **i_background;
    
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
    const double nEffectiveEventsOut(nEventsOut/background.dynamicWeight_);
    
    const double nEventsSample(background.nEvents_);
    const double effectiveCrossSection(background.crossSection_*background.filterEfficiency_);
    const double correspondingLuminosity(nEventsSample/effectiveCrossSection);
    const double weight(effectiveLuminosity/correspondingLuminosity);
    
    //const double nWeightedEventsOut(nEventsOut*weight);
    const double nEffectiveWeightedEventsOut(nEffectiveEventsOut*weight);
    
    //std::cout<<"No. events (unweighted, weighted) for \""<<background.datasetName_<<"\": "
    //         <<nEventsOut<<" , "<<nWeightedEventsOut<<"\n";
    std::cout<<"No. effective events (unweighted, weighted) for \""<<background.datasetName_<<"\": "
             <<nEffectiveEventsOut<<" , "<<nEffectiveWeightedEventsOut<<"\n";
    
    if(background.datasetName_!="ttbar")nBackgroundSideband += nEffectiveWeightedEventsOut;
  }
  theNBackgroundWoTopSideband = nBackgroundSideband;
  
  std::cout<<"No. of expected background events in sidebands w/o ttbar and signal: "<<theNBackgroundWoTopSideband<<"\n";
}













