#include "Sample.h"

#include <iostream>
#include <fstream>

#include "TH1.h"




ValueAndError DataSample::effectiveLuminosity()const{
  ValueAndError lumi;
  lumi.setValue(this->luminosity().value()*this->dynamicWeight());
  lumi.setRelErr2Up(this->luminosity().relErr2Up());
  lumi.setRelErr2Dw(this->luminosity().relErr2Dw());
  return lumi;
}





ValueAndError McSample::correspondingLuminosity()const{
  ValueAndError correspondingLumi;
  
  ValueAndError effectiveCrossSection;
  effectiveCrossSection.setValue(this->crossSection().value()*this->filterEfficiency());
  effectiveCrossSection.setRelErr2Up(this->crossSection().relErr2Up());
  effectiveCrossSection.setRelErr2Dw(this->crossSection().relErr2Dw());
  
  correspondingLumi.setValue(this->nEvent().value()/effectiveCrossSection.value());
  correspondingLumi.setRelErr2Up(effectiveCrossSection.relErr2Dw());
  correspondingLumi.setRelErr2Dw(effectiveCrossSection.relErr2Up());
  
  return correspondingLumi;
}



// The weight if full sample is reprocessed
ValueAndErrorStatSystLumi McSample::weight(const ValueAndError& effectiveLuminosity)const{
  ValueAndErrorStatSystLumi wght;
  
  ValueAndError correspondingLumi = this->correspondingLuminosity();
  wght.setValue(effectiveLuminosity.value()/correspondingLumi.value());
  wght.setRelErr2StatUp(0.);
  wght.setRelErr2StatDw(0.);
  wght.setRelErr2SystUp(correspondingLumi.relErr2Dw());
  wght.setRelErr2SystDw(correspondingLumi.relErr2Up());
  wght.setRelErr2LumiUp(effectiveLuminosity.relErr2Up());
  wght.setRelErr2LumiDw(effectiveLuminosity.relErr2Dw());
  
  return wght;
}



// The weight including dynamic weighting if only subsample is reprocessed
ValueAndErrorStatSystLumi McSample::effectiveWeight(const ValueAndError& effectiveLuminosity)const{
  
  //ValueAndError effWeight;
  // NO, dynamic weight is already included in effectiveLuminosity and correspondingLuminosity
  //ValueAndError wght = this->weight(effectiveLuminosity);
  //effWeight.setValue(wght.value()/this->dynamicWeight());
  //effWeight.setRelErr2Up(wght.relErr2Up());
  //effWeight.setRelErr2Dw(wght.relErr2Dw());
  //return effWeight;
  
  return weight(effectiveLuminosity);
}






