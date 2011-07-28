#ifndef SignalAndSidebandCombined_h
#define SignalAndSidebandCombined_h


#include "TString.h"
#include "TH1.h"
#include "TFile.h"



namespace Tools{
  TH1* signalAndSidebandCombined(TFile* file, const TString& pluginSuffix, const TString& pluginBase, const TString& subFolder, const TString& histName);
};






#endif
