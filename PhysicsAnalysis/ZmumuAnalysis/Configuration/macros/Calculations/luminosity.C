//#include "ZmumuAnalysis/Configuration/macros/Samples/data.C"
//#include "ZmumuAnalysis/Configuration/macros/Samples/mc.C"
//#include "ZmumuAnalysis/Configuration/macros/Samples/simulation.C"


#include "ZmumuAnalysis/Configuration/macros/Samples/allSampleStruct.C"


#include <iostream>



double theLuminosity(-1.);



void luminosity(){
  const DataStruct& data = *allSampleStruct.dataStruct_;
  
  const double luminosity(data.lumi_);
  const double effectiveLuminosity(luminosity*data.dynamicWeight_);
  
  theLuminosity = effectiveLuminosity;
  
  std::cout<<"Luminosity as assigned to data: "<<luminosity<<"\n";
  
  std::cout<<"Luminosity: "<<theLuminosity<<"\n";
}








