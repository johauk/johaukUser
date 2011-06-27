#ifndef Efficiency_h
#define Efficiency_h


#include "TH1.h"
#include "TFile.h"

#include <iostream>



namespace Efficiency{
  TH1* Events(TFile*, const TString&);
}


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




#endif
