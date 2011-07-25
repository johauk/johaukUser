#include "ZmumuAnalysis/Configuration/macros/Calculations/FullAnalysis.h"


#include <iostream>
#include <cmath>



//
// FIXME: For now treat errors symmetrically !!!!!
//

void FullAnalysis::setTtbarFraction(){
  
  // Helper substitutes to shorten the equations
  const double nIn(this->nObserved().value() - this->nBackgroundOther().value());
  const double nOut(this->nObservedSideband().value() - this->nBackgroundOtherSideband().value());
  const double bracket(this->ratioInOutZmumu().value()*nOut - nIn);
  const double factor(this->ratioInOutTtbar().value()/(this->ratioInOutZmumu().value()-this->ratioInOutTtbar().value()));
  const double diffRatio2(std::pow(this->ratioInOutZmumu().value() - this->ratioInOutTtbar().value(),2));
  
  // Central values (absolute contributions)
  const double nTtbarIn = factor*bracket;
  const double nZmumuIn = this->nObserved().value() - this->nBackgroundOther().value() - nTtbarIn;
  const double nTtbarOut = nTtbarIn/this->ratioInOutTtbar().value();
  const double nZmumuOut = nZmumuIn/this->ratioInOutZmumu().value();
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
  const double dNObservedOut = factor*this->ratioInOutZmumu().value();
  const double dNOtherOut = -factor*this->ratioInOutZmumu().value();
  const double dRatioInOutTtbar = (this->ratioInOutZmumu().value()/diffRatio2)*bracket;
  const double dRatioInOutZmumu = -(this->ratioInOutTtbar().value()/diffRatio2)*(this->ratioInOutTtbar().value()*nOut - nIn);
  
  // Helper substitutes for individual contributions to absolute error ^2 of nInTtbar
  const double absErr2ContNObservedIn = std::pow(dNObservedIn,2)*this->nObserved().absErr2Up();
  const double absErr2ContNOtherIn = std::pow(dNOtherIn,2)*this->nBackgroundOther().absErr2Up();
  const double absErr2ContNObservedOut = std::pow(dNObservedOut,2)*this->nObservedSideband().absErr2Up();
  const double absErr2ContNOtherOut = std::pow(dNOtherOut,2)*this->nBackgroundOtherSideband().absErr2Up();
  const double absErr2ContRatioInOutTtbar = std::pow(dRatioInOutTtbar,2)*this->ratioInOutTtbar().absErr2Up();
  const double absErr2ContRatioInOutZmumu = std::pow(dRatioInOutZmumu,2)*this->ratioInOutZmumu().absErr2Up();
  
  // Corresponding error for nInTtbar
  const double nTtbarInAbsErr2 = absErr2ContNObservedIn + absErr2ContNOtherIn + absErr2ContNObservedOut + absErr2ContNOtherOut + absErr2ContRatioInOutTtbar + absErr2ContRatioInOutZmumu;
  
  ValueAndError ttbarEstimate;
  ttbarEstimate.setValue(nTtbarIn);
  ttbarEstimate.setAbsErr2Up(nTtbarInAbsErr2);
  ttbarEstimate.setAbsErr2Dw(nTtbarInAbsErr2);
  std::cout<<"\n";
  std::cout<<"Estimated ttbar contribution (absolute values): "<<ttbarEstimate.print()<<"\n";
  
  // Final results
  zmumuFraction_ = nZmumuInRel;
  ttbarFraction_.setValue(ttbarEstimate.value()/this->nObserved().value());
  ttbarFraction_.setRelErr2StatUp(ttbarEstimate.relErr2Up());
  ttbarFraction_.setRelErr2StatDw(ttbarEstimate.relErr2Dw());
  std::cout<<"Estimated ttbar contribution (relative values in %): "<<this->ttbarFraction().print()<<"\n";
}






