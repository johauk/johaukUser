#ifndef EventCount_h
#define EventCount_h


#include "TH1.h"
#include "TFile.h"
#include "TString.h"



namespace Tools{
  TH1* eventCount(TFile* file, const TString& pluginSuffix);
  double nEvent(const TH1*);
  double nEventReweight(const TH1*);
};




#endif
