#include "ZmumuAnalysis/Configuration/macros/Tools/FullAnalysis.h"


#include <iostream>



void FullAnalysis::setCrossSection(){
  crossSection_.setValue(this->nSignal().value()/(this->efficiency().value()*this->luminosity().value()));
  crossSection_.setRelErr2StatUp(this->nSignal().relErr2StatUp());
  crossSection_.setRelErr2StatDw(this->nSignal().relErr2StatDw());
  crossSection_.setRelErr2SystUp(this->nSignal().relErr2SystDw() + this->efficiency().relErr2Dw());
  crossSection_.setRelErr2SystDw(this->nSignal().relErr2SystUp() + this->efficiency().relErr2Up());
  crossSection_.setRelErr2LumiUp(this->luminosity().relErr2Dw());
  crossSection_.setRelErr2LumiDw(this->luminosity().relErr2Up());
  
  std::cout<<"Cross section: "<<this->crossSection().print()<<"\n";
}
















