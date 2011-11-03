#include "ZmumuAnalysis/Configuration/macros/Tools/FullAnalysis.h"


#include <iostream>
#include <cmath>




// Use results from top analysis in emu channel to correct ratioInOutTtbar

void FullAnalysis::correctRatioInOutTtbar(){
  const double mcValueSignal(0.00755);
  
  const double mcValueSideband(0.00114);
  
  ValueAndErrorStatSyst dataValueSignal;
  dataValueSignal.setValue(0.00755);
  dataValueSignal.setRelErrStatUp(0.036);
  dataValueSignal.setRelErrStatDw(0.036);
  dataValueSignal.setRelErrSystUp(0.047);
  dataValueSignal.setRelErrSystDw(0.047);
  
  ValueAndErrorStatSyst dataValueSideband;
  dataValueSideband.setValue(0.00109);
  dataValueSideband.setRelErrStatUp(0.043);
  dataValueSideband.setRelErrStatDw(0.043);
  dataValueSideband.setRelErrSystUp(0.060);
  dataValueSideband.setRelErrSystDw(0.060);
  
  const double mcRatioInOut((mcValueSignal*60.)/(mcValueSideband*280.));
  
  ValueAndErrorStatSyst dataRatioInOut;
  dataRatioInOut.setValue((dataValueSignal.value()*60.)/(dataValueSideband.value()*280.));
  dataRatioInOut.setRelErr2StatUp(dataValueSignal.relErr2StatUp() + dataValueSideband.relErr2StatDw());
  dataRatioInOut.setRelErr2StatDw(dataValueSignal.relErr2StatDw() + dataValueSideband.relErr2StatUp());
  dataRatioInOut.setRelErr2SystUp(dataValueSignal.relErr2SystUp() + dataValueSideband.relErr2SystDw());
  dataRatioInOut.setRelErr2SystDw(dataValueSignal.relErr2SystDw() + dataValueSideband.relErr2SystUp());
  
  ValueAndErrorStatSyst correctionDataMc;
  correctionDataMc.setValue(dataRatioInOut.value()/mcRatioInOut);
  correctionDataMc.setRelErrStatUp(dataRatioInOut.relErrStatUp());
  correctionDataMc.setRelErrStatDw(dataRatioInOut.relErrStatDw());
  correctionDataMc.setRelErrSystUp(dataRatioInOut.relErrSystUp());
  correctionDataMc.setRelErrSystDw(dataRatioInOut.relErrSystDw());
  
  ratioInOutTtbarCorrected_.setValue(this->ratioInOutTtbar().value()*correctionDataMc.value());
  ratioInOutTtbarCorrected_.setRelErrStatUp(this->ratioInOutTtbar().relErrUp());
  ratioInOutTtbarCorrected_.setRelErrStatDw(this->ratioInOutTtbar().relErrDw());
  ratioInOutTtbarCorrected_.setRelErrSystUp(correctionDataMc.relErrUp());
  ratioInOutTtbarCorrected_.setRelErrSystDw(correctionDataMc.relErrDw());
  
  std::cout<<"Normalised differential cross section from MC (In): "<<mcValueSignal<<"\n";
  std::cout<<"Normalised differential cross section from MC (Out): "<<mcValueSideband<<"\n";
  std::cout<<"Normalised differential cross section from data (In): "<<dataValueSignal.print()<<"\n";
  std::cout<<"Normalised differential cross section from data (Out): "<<dataValueSideband.print()<<"\n";
  
  std::cout<<"\n";
  std::cout<<"Ratio In/Out for ttbar in MC: "<<mcRatioInOut<<"\n";
  std::cout<<"Ratio In/Out for ttbar in data: "<<dataRatioInOut.print()<<"\n";
  
  std::cout<<"\n";
  std::cout<<"Correction factor for ratio In/Out: "<<correctionDataMc.print()<<"\n";
  
  std::cout<<"\n";
  std::cout<<"Ratio In/Out for ttbar: "<<this->ratioInOutTtbarCorrected().print()<<"\n";
}





