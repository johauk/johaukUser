#include "ZmumuAnalysis/Configuration/macros/Calculations/FullAnalysis.h"


#include <iostream>



void FullAnalysis::setNSignal(){
  nSignal_.setValue(this->nObserved().value() - this->nBackground().value());
  nSignal_.setAbsErr2StatUp(this->nObserved().absErr2Up());
  nSignal_.setAbsErr2StatDw(this->nObserved().absErr2Dw());
  nSignal_.setAbsErr2SystUp(this->nBackground().absErr2Dw());
  nSignal_.setAbsErr2SystDw(this->nBackground().absErr2Up());
  
  std::cout<<"No. signal events: "<<this->nSignal().print()<<"\n";
}
















