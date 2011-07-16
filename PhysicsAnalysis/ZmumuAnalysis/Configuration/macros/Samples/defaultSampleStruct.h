#ifndef DefaultSampleStruct_h
#define DefaultSampleStruct_h


#include "TColor.h"
#include "TFile.h"



struct defaultStruct{
  
  defaultStruct():dynamicWeight_(-1.){}
  
  TFile* openInputFile(const std::string&, const std::string&, const unsigned int);
  double setDynamicWeight(TFile*, const unsigned int);
  
  static const std::string cmsswBase(){return getenv("CMSSW_BASE");}
  
  double dynamicWeight_;
};





// For real data
struct DataStruct : defaultStruct {
  
  DataStruct(const std::string datasetName, const unsigned int nEvents, const double lumi, const double lumiErrUp, const double lumiErrDw):
  datasetName_(datasetName), nEvents_(nEvents),
  lumi_(lumi), lumiErrUp_(lumiErrUp), lumiErrDw_(lumiErrDw),
  file_(this->openInputFile(datasetName_, this->defaultPath() + datasetName_ + ".root", nEvents_))
  {}
  
  ~DataStruct(){}//file_->Close();}
  
  // Full path of dataset
  static const std::string defaultPath(){return cmsswBase() + "/src/ZmumuAnalysis/Configuration/hists/data/";}
  // Root file name only
  const std::string datasetName_;
  // Maximum number of events
  // If less are processed, luminosity is scaled down automatically, and warning is given
  const unsigned int nEvents_;
  // Luminosity corresponding to the maximum number of events in [pb-1]
  const double lumi_;
  const double lumiErrUp_;
  const double lumiErrDw_;
  
  // The root file
  TFile* file_;
};





// For simulated samples on reco level
struct McStruct : defaultStruct {
  
  McStruct(const std::string datasetName, const unsigned int nEvents, const double crossSection, const double crossSectionErrUp, const double crossSectionErrDw, const double filterEfficiency, TColor* color):
    datasetName_(datasetName), nEvents_(nEvents),
    crossSection_(crossSection), crossSectionErrUp_(crossSectionErrUp), crossSectionErrDw_(crossSectionErrDw),
    filterEfficiency_(filterEfficiency), color_(color),
    file_(this->openInputFile(datasetName_, this->defaultPath() + datasetName_ + ".root", nEvents_))
    {}
  
  ~McStruct(){}//color_->Delete(); file_->Close();}
  
  // Full path of dataset
  static const std::string defaultPath(){return cmsswBase() + "/src/ZmumuAnalysis/Configuration/hists/mc/";}
  // Root file name only
  const std::string datasetName_;
  // Maximum number of events
  // If less are processed, weight is scaled down automatically, and warning is given
  const unsigned int nEvents_;
  // Assign cross section for normalisation to data lumi
  const double crossSection_;
  const double crossSectionErrUp_;
  const double crossSectionErrDw_;
  // If given cross section does not correspond exactly to the process, since a filter on generator level is applied
  const double filterEfficiency_;
  // Set the colour used for the the sample in the plots
  TColor* color_;
  
  // The root file
  TFile* file_;
};





// For generator level studies
struct SimulationStruct : defaultStruct {
  
  SimulationStruct(const std::string datasetName, const unsigned int nEvents):
  datasetName_(datasetName), nEvents_(nEvents),
  file_(this->openInputFile(datasetName_, this->defaultPath() + datasetName_ + ".root", nEvents_))
  {}
  
  ~SimulationStruct(){}//file_->Close();}
  
  // Full path of dataset
  static const std::string defaultPath(){return cmsswBase() + "/src/ZmumuAnalysis/Configuration/hists/simulation/";}
  // Root file name only
  const std::string datasetName_;
  // Maximum number of events
  // If less are processed, warning is given
  const unsigned int nEvents_;
  
  // The root file
  TFile* file_;
};



#endif



