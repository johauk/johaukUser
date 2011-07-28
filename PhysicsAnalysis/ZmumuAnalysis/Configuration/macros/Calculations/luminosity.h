#include "ZmumuAnalysis/Configuration/macros/Tools/FullAnalysis.h"


#include <iostream>



void FullAnalysis::setLuminosity(){
  if(!this->dataSample()){
    std::cout<<"\tMissing input sample\n"
             <<"\t... take dummy luminosity\n";
    luminosity_ = ValueAndError::dummyValues();
    std::cout<<"Luminosity: "<<this->luminosity().print()<<"\n";
    return;
  }

  const DataSample& data = *this->dataSample();
  luminosity_ = data.effectiveLuminosity();
  
  std::cout<<"Luminosity as assigned to data: "<<data.luminosity().print()<<"\n";
  std::cout<<"Effective luminosity: "<<this->luminosity().print()<<"\n";
}









