#include "ZmumuAnalysis/Configuration/macros/Tools/FullAnalysis.h"



#include <iostream>



// The calculation works either with two split files for C and UDS components of the Zmumu, or with one file containing all components UDSC


void FullAnalysis::setRatioInOut(){
  const double nInTtbar(this->nTtbarInMc());
  const double nOutTtbar(this->nTtbarOutMc());
  if(nInTtbar>0. && nOutTtbar>0.){
    ratioInOutTtbar_.setValue(nInTtbar/nOutTtbar);
    ratioInOutTtbar_.setRelErr2Up(1./nInTtbar + 1./nOutTtbar);
    ratioInOutTtbar_.setRelErr2Dw(1./nInTtbar + 1./nOutTtbar);
  }
  else{
    ratioInOutTtbar_ = ValueAndError::dummyValues(0.,1.,1.);
  }
  
  const double nInZmumu(this->nZmumuInMc());
  const double nOutZmumu(this->nZmumuOutMc());
  if(nInZmumu>0. && nOutZmumu>0.){
    ratioInOutZmumu_.setValue(nInZmumu/nOutZmumu);
    ratioInOutZmumu_.setRelErr2Up(1./nInZmumu + 1./nOutZmumu);
    ratioInOutZmumu_.setRelErr2Dw(1./nInZmumu + 1./nOutZmumu);
  }
  else{
    ratioInOutZmumu_ = ValueAndError::dummyValues(0.,1.,1.);
  }
  
  std::cout<<"Ratio In/Out for ttbar: "<<this->ratioInOutTtbar().print()<<"\n";
  std::cout<<"Ratio In/Out for zmumu: "<<this->ratioInOutZmumu().print()<<"\n";
}





