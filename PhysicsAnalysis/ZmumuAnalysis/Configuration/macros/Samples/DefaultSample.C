#include "DefaultSample.h"

#include <iostream>
#include <fstream>

#include "TH1.h"



void DefaultSample::openInputFile(const std::string& dataset, const std::string& defaultPath, const unsigned int nEvtFullSample){
  this->setDatasetName(dataset);
  
  const std::string& fullName = defaultPath + datasetName_ + ".root";
  
  TFile* inputFile(0);
  ifstream inputFileStream;
  inputFileStream.open(fullName.c_str());
  if(inputFileStream.is_open()){
    inputFileStream.close();
    inputFile = TFile::Open(fullName.c_str());
  }
  if(inputFile){
    std::cout<<"\nOpened file \""<<datasetName_<<"\" sucessfully\n";
    this->setDynamicWeightAndNEvent(inputFile, nEvtFullSample);
  }
  else{
    std::cout<<"\nThe file \""<<datasetName_<<"\" could not be found!\n"
             <<"\t... corresponding sample will not be used\n\n";
  }
  file_ =  inputFile;
}



void DefaultSample::setDynamicWeightAndNEvent(TFile* inputFile, const unsigned int nEvtFullSample){
  TH1* EventCount(0);
  inputFile->GetObject("EventCounterStep0/h_eventCount;1", EventCount);
  
  if(EventCount){
    const unsigned int eventCount(EventCount->GetEntries());
    this->setNEvent(nEvtFullSample, eventCount);
    if(eventCount==nEvtFullSample){
      std::cout<<"\tFull sample processed, dynamic weighting will not be applied\n";
      dynamicWeight_ = 1.;
    }
    else if(eventCount>nEvtFullSample){
      std::cout<<"\tMore events than maximum allowed are processed: "<<eventCount<<" vs. "<<nEvtFullSample<<"\n"
               <<"\t... corresponding sample will not be used\n\n";
      dynamicWeight_ = -1.;
    }
    else{
      std::cout<<"\tNot the full sample processed: "<<eventCount<<" vs. "<<nEvtFullSample<<"\n"
               <<"\t... dynamic weighting will be applied\n";
      dynamicWeight_ = static_cast<double>(eventCount)/static_cast<double>(nEvtFullSample);
    }
  }
  else{
    std::cout<<"\tHistogram containing number of processed events \"EventCounterStep0/h_eventCount;1\" not found!\n"
             <<"\t... corresponding sample will not be used\n\n";
    dynamicWeight_ = -1.;
  }
}




void DefaultSample::setNEvent(const double nEvtFullSample, const double eventCount){
  nEventFullSample_ = nEvtFullSample;
  
  nEvent_.setValue(eventCount);
  nEvent_.setAbsErr2Up(eventCount);
  nEvent_.setAbsErr2Dw(eventCount);
}










