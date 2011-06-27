#include "efficiency.h"

#include "ZmumuAnalysis/Configuration/macros/Samples/allSampleStruct.C"



double theNBackground(-1.);



void nBackground(TString pluginSuffix = ""){
  const DataStruct& data = *allSampleStruct.dataStruct;
  const double luminosity(data.lumi_);
  const double effectiveLuminosity(luminosity*data.dynamicWeight_);
  
  const std::vector<McStruct*> v_background = allSampleStruct.v_backgroundStruct;
  
  double nBackground(0.);
  std::vector<McStruct*>::const_iterator i_background;
  for(i_background = v_background.begin(); i_background != v_background.end(); ++i_background){
    const McStruct& background = **i_background;
    
    TH1* events(0);
    events = Efficiency::Events(background.file_, pluginSuffix);
    
    if(!events){
      std::cout<<"\tMissing is histogram containing no. of MC events for: "<<background.datasetName_<<"\n"
               <<"\t... nObserved calculation stopped\n";
      return;
    }
    const double nEvents(events->GetEntries());
    const double nEffectiveEvents(nEvents/background.dynamicWeight_);
    
    
    const double nEventsSample(background.nEvents_);
    const double effectiveCrossSection(background.crossSection_*background.filterEfficiency_);
    const double correspondingLuminosity(nEventsSample/effectiveCrossSection);
    const double weight(effectiveLuminosity/correspondingLuminosity);
    
    const double nWeightedEvents(nEvents*weight);
    const double nEffectiveWeightedEvents(nEffectiveEvents*weight);
    
    std::cout<<"No. events (unweighted, weighted) for \""<<background.datasetName_<<"\": "
             <<nEvents<<" , "<<nWeightedEvents<<"\n";
    std::cout<<"No. effective events (unweighted, weighted) for \""<<background.datasetName_<<"\": "
             <<nEffectiveEvents<<" , "<<nEffectiveWeightedEvents<<"\n";
    
    nBackground += nEffectiveWeightedEvents;
  }
  theNBackground = nBackground;
  
  std::cout<<"No. of expected background events: "<<theNBackground<<"\n";
}













