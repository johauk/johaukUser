#include "ZmumuAnalysis/Configuration/macros/Tools/eventCount.h"

#include "ZmumuAnalysis/Configuration/macros/Samples/allSampleStruct.C"

#include <iostream>



double theEfficiency(-1.);


void efficiency(TString pluginSuffixReco = "", TString pluginSuffixSimu = ""){
  const McStruct& zmumuB = *allSampleStruct.signalStruct;
  const SimulationStruct& simulation = *allSampleStruct.simulationStruct;
  
  // First: get the number of reconstructed signal events
  TH1* eventsReco(0);
  eventsReco = eventCount(zmumuB.file_, pluginSuffixReco);
  if(!eventsReco){
    std::cout<<"\tMissing is histogram containing no. of reconstructed signal events\n"
             <<"\t... efficiency calculation stopped\n";
    return;
  }
  const double nEventsReco(eventsReco->GetEntries());
  const double nEffectiveEventsReco(nEventsReco/zmumuB.dynamicWeight_);
  
  
  // Second: get the number of simulated signal events
  TH1* eventsSimu(0);
  eventsSimu = eventCount(simulation.file_, pluginSuffixSimu);
  if(!eventsSimu){
    std::cout<<"\tMissing is histogram containing no. of simulated signal events\n"
             <<"\t... efficiency calculation stopped\n";
    return;
  }
  double nEventsSimu(eventsSimu->GetEntries());
  const double nEffectiveEventsSimu(nEventsSimu/simulation.dynamicWeight_);
  
  
  // Finally: calculate efficiency
  theEfficiency = nEffectiveEventsReco/nEffectiveEventsSimu;
  
  std::cout<<"Effective no. of reconstructed signal events: "<<nEffectiveEventsReco<<"\n";
  std::cout<<"Effective no. of simulated signal events: "<<nEffectiveEventsSimu<<"\n";
  std::cout<<"Efficiency: "<<theEfficiency<<"\n";
}











