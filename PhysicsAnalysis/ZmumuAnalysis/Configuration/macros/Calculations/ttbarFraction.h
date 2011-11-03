#include "ZmumuAnalysis/Configuration/macros/Tools/FullAnalysis.h"


#include <iostream>
#include <cmath>



//
// FIXME: For now treat errors symmetrically !!!!!
//

void FullAnalysis::setTtbarFraction(){
  
  // Helper substitutes to shorten the equations
  const double nIn(this->nObserved().value() - this->nBackgroundOther().value());
  const double nOut(this->nObservedSideband().value() - this->nBackgroundOtherSideband().value());
  const double bracket(this->ratioInOutZmumuCorrected().value()*nOut - nIn);
  const double factor(this->ratioInOutTtbarCorrected().value()/(this->ratioInOutZmumuCorrected().value()-this->ratioInOutTtbarCorrected().value()));
  const double diffRatio2(std::pow(this->ratioInOutZmumuCorrected().value() - this->ratioInOutTtbarCorrected().value(),2));
  
  // Central values (absolute contributions)
  const double nTtbarIn = factor*bracket;
  const double nZmumuIn = this->nObserved().value() - this->nBackgroundOther().value() - nTtbarIn;
  const double nTtbarOut = nTtbarIn/this->ratioInOutTtbarCorrected().value();
  const double nZmumuOut = nZmumuIn/this->ratioInOutZmumuCorrected().value();
  std::cout<<"ttbar in, ttbar out, zmumu in, zmumu out (absolute values): "
           <<nTtbarIn<<" , "<<nTtbarOut<<" , "<<nZmumuIn<<" , "<<nZmumuOut<<"\n";
  
  // Relative contributions
  const double nTtbarInRel = nTtbarIn/this->nObserved().value();
  const double nZmumuInRel = nZmumuIn/this->nObserved().value();
  const double nTtbarOutRel = nTtbarOut/this->nObservedSideband().value();
  const double nZmumuOutRel = nZmumuOut/this->nObservedSideband().value();
  std::cout<<"ttbar in, ttbar out, zmumu in, zmumu out (relative values in %): "
           <<nTtbarInRel*100<<" , "<<nTtbarOutRel*100<<" , "<<nZmumuInRel*100<<" , "<<nZmumuOutRel*100<<"\n";
  
  // Derivatives for nTtbarIn, needed for error propagation
  const double dNObservedIn = -factor;
  const double dNOtherIn = factor;
  const double dNObservedOut = factor*this->ratioInOutZmumuCorrected().value();
  const double dNOtherOut = -factor*this->ratioInOutZmumuCorrected().value();
  const double dRatioInOutTtbar = (this->ratioInOutZmumuCorrected().value()/diffRatio2)*bracket;
  const double dRatioInOutZmumu = -(this->ratioInOutTtbarCorrected().value()/diffRatio2)*(this->ratioInOutTtbarCorrected().value()*nOut - nIn);
  
  // Helper substitutes for individual contributions to absolute error ^2 of nInTtbar
  const double absErr2ContNObservedIn = std::pow(dNObservedIn,2)*this->nObserved().absErr2Up();
  const double absErr2ContNOtherIn = std::pow(dNOtherIn,2)*this->nBackgroundOther().absErr2Up();
  const double absErr2ContNObservedOut = std::pow(dNObservedOut,2)*this->nObservedSideband().absErr2Up();
  const double absErr2ContNOtherOut = std::pow(dNOtherOut,2)*this->nBackgroundOtherSideband().absErr2Up();
  const double absErr2StatContRatioInOutTtbar = std::pow(dRatioInOutTtbar,2)*this->ratioInOutTtbarCorrected().absErr2StatUp();
  const double absErr2StatContRatioInOutZmumu = std::pow(dRatioInOutZmumu,2)*this->ratioInOutZmumuCorrected().absErr2StatUp();
  const double absErr2SystContRatioInOutTtbar = std::pow(dRatioInOutTtbar,2)*this->ratioInOutTtbarCorrected().absErr2SystUp();
  const double absErr2SystContRatioInOutZmumu = std::pow(dRatioInOutZmumu,2)*this->ratioInOutZmumuCorrected().absErr2SystUp();
  
  std::cout<<"\n";
  std::cout<<"Error contributions to ttbar fraction with central value in %: "<<nTtbarInRel*100<<"\n";
  std::cout<<"NObservedIn stat. (absolute in %, relative in %): "<<100*std::sqrt(absErr2ContNObservedIn)/this->nObserved().value()<<" , "<<100*std::sqrt(absErr2ContNObservedIn)/nTtbarIn<<"\n";
  std::cout<<"NOtherIn (absolute in %, relative in %): "<<100*std::sqrt(absErr2ContNOtherIn)/this->nObserved().value()<<" , "<<100*std::sqrt(absErr2ContNOtherIn)/nTtbarIn<<"\n";
  std::cout<<"NObservedOut stat. (absolute in %, relative in %): "<<100*std::sqrt(absErr2ContNObservedOut)/this->nObserved().value()<<" , "<<100*std::sqrt(absErr2ContNObservedOut)/nTtbarIn<<"\n";
  std::cout<<"NOtherOut (absolute in %, relative in %): "<<100*std::sqrt(absErr2ContNOtherOut)/this->nObserved().value()<<" , "<<100*std::sqrt(absErr2ContNOtherOut)/nTtbarIn<<"\n";
  std::cout<<"RatioInOutTtbar stat. (absolute in %, relative in %): "<<100*std::sqrt(absErr2StatContRatioInOutTtbar)/this->nObserved().value()<<" , "<<100*std::sqrt(absErr2StatContRatioInOutTtbar)/nTtbarIn<<"\n";
  std::cout<<"RatioInOutZmumu stat. (absolute in %, relative in %): "<<100*std::sqrt(absErr2StatContRatioInOutZmumu)/this->nObserved().value()<<" , "<<100*std::sqrt(absErr2StatContRatioInOutZmumu)/nTtbarIn<<"\n";
  std::cout<<"RatioInOutTtbar syst. (absolute in %, relative in %): "<<100*std::sqrt(absErr2SystContRatioInOutTtbar)/this->nObserved().value()<<" , "<<100*std::sqrt(absErr2SystContRatioInOutTtbar)/nTtbarIn<<"\n";
  std::cout<<"RatioInOutZmumu syst. (absolute in %, relative in %): "<<100*std::sqrt(absErr2SystContRatioInOutZmumu)/this->nObserved().value()<<" , "<<100*std::sqrt(absErr2SystContRatioInOutZmumu)/nTtbarIn<<"\n";
  
  // Corresponding error for nInTtbar
  // Where to assign error of NOther, stat or syst?
  const double nTtbarInAbsErr2Stat = absErr2ContNObservedIn + absErr2ContNOtherIn + absErr2ContNObservedOut + absErr2ContNOtherOut + absErr2StatContRatioInOutTtbar + absErr2StatContRatioInOutZmumu;
  const double nTtbarInAbsErr2Syst = absErr2SystContRatioInOutTtbar + absErr2SystContRatioInOutZmumu;
  
  ValueAndErrorStatSyst ttbarEstimate;
  ttbarEstimate.setValue(nTtbarIn);
  ttbarEstimate.setAbsErr2StatUp(nTtbarInAbsErr2Stat);
  ttbarEstimate.setAbsErr2StatDw(nTtbarInAbsErr2Stat);
  ttbarEstimate.setAbsErr2SystUp(nTtbarInAbsErr2Syst);
  ttbarEstimate.setAbsErr2SystDw(nTtbarInAbsErr2Syst);
  
  std::cout<<"\n";
  std::cout<<"Estimated ttbar contribution (absolute values): "<<ttbarEstimate.print()<<"\n";
  
  // Final results
  zmumuFraction_ = nZmumuInRel;
  ttbarFraction_.setValue(ttbarEstimate.value()/this->nObserved().value());
  ttbarFraction_.setRelErr2StatUp(ttbarEstimate.relErr2StatUp());
  ttbarFraction_.setRelErr2StatDw(ttbarEstimate.relErr2StatDw());
  ttbarFraction_.setRelErr2SystUp(ttbarEstimate.relErr2SystUp());
  ttbarFraction_.setRelErr2SystDw(ttbarEstimate.relErr2SystDw());
  std::cout<<"Estimated ttbar contribution (relative values in %): "<<this->ttbarFraction().print(100.)<<"\n";
}






