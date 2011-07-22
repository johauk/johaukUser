#ifndef SignalAndSidebandCombined_h
#define SignalAndSidebandCombined_h


#include "TString.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TFile.h"

#include <iostream>




TH1* signalAndSidebandCombined(TFile* file, const TString& pluginSuffix, const TString& pluginBase, const TString& subFolder, const TString& histName){
  TString pluginSuffixOut1 = pluginSuffix;
  pluginSuffixOut1.Insert(4,"ZVetoHigh");
  TString pluginSuffixOut2 = pluginSuffix;
  pluginSuffixOut2.Insert(4,"ZVetoLow");
  
  TString *pluginNameIn(0), *pluginNameOut1(0), *pluginNameOut2(0);
  pluginNameIn = new TString(pluginBase.Copy().Append(pluginSuffix));
  pluginNameOut1 = new TString(pluginBase.Copy().Append(pluginSuffixOut1));
  pluginNameOut2 = new TString(pluginBase.Copy().Append(pluginSuffixOut2));
  
  if(!pluginNameIn->IsNull())pluginNameIn->Append("/");
  if(!pluginNameOut1->IsNull())pluginNameOut1->Append("/");
  if(!pluginNameOut2->IsNull())pluginNameOut2->Append("/");
  
  TString* pluginFolder(0);
  pluginFolder = new TString(subFolder);
  if(!pluginFolder->IsNull())pluginFolder->Append("/");
  
  TString* fullNameIn = new TString(pluginNameIn->Copy().Append(*pluginFolder).Append(histName));
  TString* fullNameOut1 = new TString(pluginNameOut1->Copy().Append(*pluginFolder).Append(histName));
  TString* fullNameOut2 = new TString(pluginNameOut2->Copy().Append(*pluginFolder).Append(histName));
  
  //std::cout<<"Full name: "<<*fullNameIn<<"\n";
  //std::cout<<"Full name out1: "<<*fullNameOut1<<"\n";
  //std::cout<<"Full name out2: "<<*fullNameOut2<<"\n";
  
  TH1* dimuonMassData(0);
  TH1* dimuonMassDataOut1(0);
  TH1* dimuonMassDataOut2(0);
  
  file->GetObject(*fullNameIn + ";1", dimuonMassData);
  if(!dimuonMassData)std::cout<<"Histogram \""<<*fullNameIn<<"\" not found!\n";
  file->GetObject(*fullNameOut1 + ";1", dimuonMassDataOut1);
  if(!dimuonMassDataOut1)std::cout<<"Histogram \""<<*fullNameOut1<<"\" not found!\n";
  file->GetObject(*fullNameOut2 + ";1", dimuonMassDataOut2);
  if(!dimuonMassDataOut2)std::cout<<"Histogram \""<<*fullNameOut2<<"\" not found!\n";
  
  dimuonMassData->Add(dimuonMassDataOut1);
  dimuonMassData->Add(dimuonMassDataOut2);
  
  return dimuonMassData;
}






#endif
