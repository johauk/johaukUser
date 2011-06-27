#include "defaultSampleStruct.h"

#include <iostream>
#include <fstream>

#include "TH1.h"



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
    dynamicWeight_ = this->setDynamicWeight(file, nEvents);
  }
  else{
    std::cout<<"\nThe file \""<<datasetName<<"\" could not be found!\n"
             <<"\t... corresponding sample will not be used\n\n";
  }
  return file;
}



double defaultStruct::setDynamicWeight(TFile* file, const unsigned int nEvents){
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




