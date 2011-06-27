#include <iostream>



double theCrossSection(-1.);



void crossSection(const double nSignal, const double efficiency, const double luminosity){
  const double crossSection(nSignal/(efficiency*luminosity));
  
  theCrossSection = crossSection;
  
  std::cout<<"Cross section: "<<theCrossSection<<"\n";
}
















