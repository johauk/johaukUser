#include "ZmumuAnalysis/Configuration/macros/Tools/FullAnalysis.h"



void FullAnalysis::setDataSample(){
  DataSample* sample(0);
  sample = new DataSample("allData", 24492880);
  sample->luminosity_.setValue(1143.);
  sample->luminosity_.setRelErrUp(0.04);
  sample->luminosity_.setRelErrDw(0.04);
  
  if(sample->file()){
    dataSample_ = sample;
  }
  else{
    dataSample_ = 0;
    delete sample;
  }
}


