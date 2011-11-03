#include "ZmumuAnalysis/Configuration/macros/Tools/FullAnalysis.h"



void FullAnalysis::setDataSample(const std::string& inputFolder){
  DataSample* sample(0);
  sample = new DataSample("allData", 24492880, inputFolder);
  sample->luminosity_.setValue(1143.);
  sample->luminosity_.setRelErrUp(0.045);
  sample->luminosity_.setRelErrDw(0.045);
  
  if(sample->file()){
    dataSample_ = sample;
  }
  else{
    dataSample_ = 0;
    delete sample;
  }
}


