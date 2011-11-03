#include "ZmumuAnalysis/Configuration/macros/Tools/FullAnalysis.h"


#include <iostream>



void FullAnalysis::correctRatioInOutZmumu(){
  const double relErrSystUp(0.1);
  const double relErrSystDw(0.1);
  
  ratioInOutZmumuCorrected_.setValue(this->ratioInOutZmumu().value());
  ratioInOutZmumuCorrected_.setRelErrStatUp(this->ratioInOutZmumu().relErrUp());
  ratioInOutZmumuCorrected_.setRelErrStatDw(this->ratioInOutZmumu().relErrDw());
  ratioInOutZmumuCorrected_.setRelErrSystUp(relErrSystUp);
  ratioInOutZmumuCorrected_.setRelErrSystDw(relErrSystDw);
  
  std::cout<<"Ratio In/Out for Zmumu: "<<this->ratioInOutZmumuCorrected().print()<<"\n";
}





