#include <iostream>



double theNSignal(-1.);



void nSignal(const double nObserved, const double nBackground){
  const double nSignal(nObserved - nBackground);
  
  theNSignal = nSignal;
  
  std::cout<<"No. signal events: "<<theNSignal<<"\n";
}
















