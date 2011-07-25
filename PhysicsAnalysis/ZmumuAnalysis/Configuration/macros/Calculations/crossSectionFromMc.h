#include "ZmumuAnalysis/Configuration/macros/Calculations/FullAnalysis.h"


#include "ZmumuAnalysis/Configuration/macros/Tools/eventCount.h"

#include <iostream>



void FullAnalysis::setCrossSectionFromMc(){
  if(!this->signalSample()){
    std::cout<<"\tMissing input sample\n"
             <<"\t... take dummy cross section from MC\n";
    crossSectionFromMc_ = ValueAndErrorStatSyst::dummyValues();
    std::cout<<"Cross section taken from signal sample: "<<this->crossSectionFromMc().print()<<"\n";
    return;
  }
  const McSample& zmumuB = *this->signalSample();
  
  TH1* events(0);
  events = eventCount(zmumuB.file(), "Step1a");
  if(!events){
    std::cout<<"\tMissing is histogram containing no. of signal events\n"
             <<"\t... crossSectionFromMc calculation stopped\n";
    return;
  }
  const double nEvents(events->GetEntries());
  
  ValueAndError selectionEfficiency;
  selectionEfficiency.setValue(nEvents/zmumuB.nEvent().value());
  selectionEfficiency.setRelErr2Up((zmumuB.nEvent().value()-nEvents)/(zmumuB.nEvent().value()*nEvents));
  selectionEfficiency.setRelErr2Dw((zmumuB.nEvent().value()-nEvents)/(zmumuB.nEvent().value()*nEvents));
  
  crossSectionFromMc_.setValue(selectionEfficiency.value()*zmumuB.crossSection().value());
  crossSectionFromMc_.setRelErr2StatUp(selectionEfficiency.relErr2Up());
  crossSectionFromMc_.setRelErr2StatDw(selectionEfficiency.relErr2Dw());
  crossSectionFromMc_.setRelErr2SystUp(zmumuB.crossSection().relErr2Up());
  crossSectionFromMc_.setRelErr2SystDw(zmumuB.crossSection().relErr2Dw());
  
  
  
  
  std::cout<<"Cross section taken from signal sample: "<<this->crossSectionFromMc().print()<<"\n";
}












