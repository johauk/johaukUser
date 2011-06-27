#include "efficiency.h"

#include "ZmumuAnalysis/Configuration/macros/Samples/allSampleStruct.C"

#include <iostream>



double theEfficiency(-1.);


void efficiency(TString pluginSuffixReco = "", TString pluginSuffixSimu = ""){
  const McStruct& zmumuB = *allSampleStruct.signalStruct;
  const SimulationStruct& simulation = *allSampleStruct.simulationStruct;
  
  // First: get the number of reconstructed signal events
  TH1* eventsReco(0);
  eventsReco = Efficiency::Events(zmumuB.file_, pluginSuffixReco);
  if(!eventsReco){
    std::cout<<"\tMissing is histogram containing no. of reconstructed signal events\n"
             <<"\t... efficiency calculation stopped\n";
    return;
  }
  const double nEventsReco(eventsReco->GetEntries());
  const double nEffectiveEventsReco(nEventsReco/zmumuB.dynamicWeight_);
  
  
  // Second: get the number of simulated signal events
  TH1* eventsSimu(0);
  eventsSimu = Efficiency::Events(simulation.file_, pluginSuffixSimu);
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



/*
TH1* Efficiency::Events(TFile* file, const TString& pluginSuffix){
  //Specify plugin name
  TString* pluginName(0);
  pluginName = new TString("EventCounter");
  pluginName->Append(pluginSuffix);
  if(!pluginName->IsNull())pluginName->Append("/");
  
  TString* pluginFolder(0);
  pluginFolder = new TString("");
  if(!pluginFolder->IsNull())pluginFolder->Append("/");
  
  TString* fullPathName(0);
  fullPathName = new TString(pluginName->Copy().Append(*pluginFolder));
  
  // Give name of input histogram
  TString* histName(0);
  histName = new TString("h_eventCount");
  
  TString* fullName(0);
  fullName = new TString(fullPathName->Copy().Append(*histName));
  
  TH1* events(0);
  file->GetObject(*fullName + ";1", events);
  
  if(!events)std::cout<<"Histogram \""<<*fullName<<"\" not found!\n";
  
  return events;
}
*/










