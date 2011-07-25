#include "ZmumuAnalysis/Configuration/macros/Calculations/FullAnalysis.h"



void FullAnalysis::setDataSample(){
  DataSample* sample(0);
  sample = new DataSample("allData", 24492880);
  sample->luminosity_.setValue(1092.);
  sample->luminosity_.setRelErrUp(0.06);
  sample->luminosity_.setRelErrDw(0.06);
  
  if(sample->file()){
    dataSample_ = sample;
  }
  else{
    dataSample_ = 0;
    delete sample;
  }
}


