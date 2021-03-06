#include "eventCount.h"  


#include <iostream>



TH1* Tools::eventCount(TFile* file, const TString& pluginSuffix){
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
  //histName = new TString("h_eventCount");
  histName = new TString("h_eventCountWeighted");  // Do not need to separate, since weighted histogram contains all information: Unweighted number of events is simply given by GetEntries()
  
  TString* fullName(0);
  fullName = new TString(fullPathName->Copy().Append(*histName));
  
  TH1* events(0);
  file->GetObject(*fullName + ";1", events);
  
  if(!events)std::cout<<"Histogram \""<<*fullName<<"\" not found!\n";
  
  return events;
}




double Tools::nEvent(const TH1* eventCount){
  return eventCount->GetEntries();
}



double Tools::nEventReweight(const TH1* eventCount){
  return eventCount->Integral(0, eventCount->GetNbinsX()+1);
}
