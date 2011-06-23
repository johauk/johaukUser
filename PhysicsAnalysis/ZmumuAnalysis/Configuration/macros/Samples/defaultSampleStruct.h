#ifndef DefaultSampleStruct_h
#define DefaultSampleStruct_h

#include <iostream>
#include <fstream>

#include "TColor.h"
#include "TFile.h"
#include "TH1.h"



struct defaultStruct{
  
  defaultStruct():lumiWeight_(-1.){}
  
  TFile* openInputFile(const std::string&, const std::string&, const unsigned int);
  double setLumiWeight(TFile*, const unsigned int);
  
  static const std::string cmsswBase(){return getenv("CMSSW_BASE");}
  
  double lumiWeight_;
};

TFile* defaultStruct::openInputFile(const std::string& datasetName,const std::string& fullName, const unsigned int nEvents){
  TFile* file(0);
  ifstream inputFileStream;
  inputFileStream.open(fullName.c_str());
  if(inputFileStream.is_open()){
    inputFileStream.close();
    file = TFile::Open(fullName.c_str());
  }
  if(file){
    std::cout<<"\nOpened file \""<<datasetName<<"\" sucessfully\n";
    lumiWeight_ = this->setLumiWeight(file, nEvents);
  }
  else{
    std::cout<<"\nThe file \""<<datasetName<<"\" could not be found!\n"
             <<"\t... corresponding sample will not be used\n\n";
  }
  return file;
}

double defaultStruct::setLumiWeight(TFile* file, const unsigned int nEvents){
  TH1* EventCount(0);
  file->GetObject("EventCounterStep0/h_eventCount;1", EventCount);
  
  if(EventCount){
    const unsigned int eventCount(EventCount->GetEntries());
    if(eventCount==nEvents){
      std::cout<<"\tFull sample processed, dynamic weighting will not be applied\n";
      return 1.;
    }
    else if(eventCount>nEvents){
      std::cout<<"\tMore events than maximum allowed are processed: "<<eventCount<<" vs. "<<nEvents<<"\n"
               <<"\t... corresponding sample will not be used\n\n";
      return -1.;
    }
    else{
      std::cout<<"\tNot the full sample processed: "<<eventCount<<" vs. "<<nEvents<<"\n"
               <<"\t... dynamic weighting will be applied\n";
      return static_cast<double>(eventCount)/static_cast<double>(nEvents);
    }
  }
  else{
    std::cout<<"\tHistogram containing number of processed events \"EventCounterStep0/h_eventCount;1\" not found!\n"
             <<"\t... corresponding sample will not be used\n\n";
    return -1.;
  }
}




// For real data
struct DataStruct : defaultStruct {
  
  DataStruct(const std::string datasetName, const unsigned int nEvents, const double lumi):
  datasetName_(datasetName), nEvents_(nEvents), lumi_(lumi),
  file_(this->openInputFile(datasetName_, this->defaultPath() + datasetName_, nEvents_))
  {}
  
  // Full path of dataset
  static const std::string defaultPath(){return cmsswBase() + "/src/ZmumuAnalysis/Configuration/hists/data/";}
  // Root file name only
  const std::string datasetName_;
  // Maximum number of events
  // If less are processed, luminosity is scaled down automatically, and warning is given
  const unsigned int nEvents_;
  // Luminosity corresponding to the maximum number of events in [pb-1]
  const double lumi_;
  
  // The root file
  const TFile* file_;
};





// For simulated samples on reco level
struct McStruct : defaultStruct {
  
  McStruct(const std::string datasetName, const unsigned int nEvents, const double crossSection, const double filterEfficiency, const TColor* color):
    datasetName_(datasetName), nEvents_(nEvents), crossSection_(crossSection), filterEfficiency_(filterEfficiency), color_(color),
    file_(this->openInputFile(datasetName_, this->defaultPath() + datasetName_, nEvents_))
    {}
  
  // Full path of dataset
  static const std::string defaultPath(){return cmsswBase() + "/src/ZmumuAnalysis/Configuration/hists/mc/";}
  // Root file name only
  const std::string datasetName_;
  // Maximum number of events
  // If less are processed, weight is scaled down automatically, and warning is given
  const unsigned int nEvents_;
  // Assign cross section for normalisation to data lumi
  const double crossSection_;
  // If given cross section does not correspond exactly to the process, since a filter on generator level is applied
  const double filterEfficiency_;
  // Set the colour used for the the sample in the plots
  const TColor* color_;
  
  // The root file
  const TFile* file_;
};





// For generator level studies
struct SimulationStruct : defaultStruct {
  
  SimulationStruct(const std::string datasetName, const unsigned int nEvents):
  datasetName_(datasetName), nEvents_(nEvents),
  file_(this->openInputFile(datasetName_, this->defaultPath() + datasetName_, nEvents_))
  {}
  
  // Full path of dataset
  static const std::string defaultPath(){return cmsswBase() + "/src/ZmumuAnalysis/Configuration/hists/simulation/";}
  // Root file name only
  const std::string datasetName_;
  // Maximum number of events
  // If less are processed, warning is given
  const unsigned int nEvents_;
  
  // The root file
  const TFile* file_;
};



#endif



