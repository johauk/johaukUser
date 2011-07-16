#include <iostream>
#include <cmath>



double theNInTtbar(-1.);
double theNInZmumu(-1.);
double theNOutTtbar(-1.);
double theNOutZmumu(-1.);

double theNInTtbarRel(-1.);
double theNInZmumuRel(-1.);
double theNOutTtbarRel(-1.);
double theNOutZmumuRel(-1.);

double theNInRelErr2UpTtbar(-1.);
double theNInRelErr2DwTtbar(-1.);

double theNInRelErr2UpTtbarRel(-1.);
double theNInRelErr2DwTtbarRel(-1.);

/*
double theNOutRelErr2UpTtbar(-1.);
double theNOutRelErr2DwTtbar(-1.);

double theNInRelErr2UpZmumu(-1.);
double theNInRelErr2DwZmumu(-1.);
double theNOutRelErr2UpZmumu(-1.);
double theNOutRelErr2DwZmumu(-1.);
*/

// FIXME: For now treat errors symmetrically (already in input)
void nInOut(const double nObservedIn, const double nObservedOut,
            const double nObservedInRelErr2, const double nObservedOutRelErr2,
            const double ratioInOutTtbar, const double ratioInOutZmumu,
            const double ratioInOutRelErr2Ttbar, const double ratioInOutRelErr2Zmumu,
            const double nInOther, const double nOutOther,
	    const double nInRelErr2Other, const double nOutRelErr2Other){
  
  
  // Helper substitutes to shorten the equations
  const double nIn(nObservedIn - nInOther);
  const double nOut(nObservedOut - nOutOther);
  const double bracket(ratioInOutZmumu*nOut - nIn);
  const double factor(ratioInOutTtbar/(ratioInOutZmumu-ratioInOutTtbar));
  const double diffRatio2(std::pow(ratioInOutZmumu - ratioInOutTtbar,2));
  
  // Central values
  const double nInTtbar = factor*bracket;
  //double nInTtbar = ratioInOutTtbar/(ratioInOutZmumu-ratioInOutTtbar)*(ratioInOutZmumu*(nObservedOut-nOutOther) - nObservedIn - nInOther);
  const double nInZmumu = nObservedIn - nInOther - nInTtbar;
  const double nOutTtbar = nInTtbar/ratioInOutTtbar;
  const double nOutZmumu = nInZmumu/ratioInOutZmumu;
  
  
  theNInTtbar = nInTtbar;
  theNInZmumu = nInZmumu;
  theNOutTtbar = nOutTtbar;
  theNOutZmumu = nOutZmumu;
  
  std::cout<<"ttbar in, ttbar out, zmumu in, zmumu out (absolute values): "
           <<theNInTtbar<<" , "<<theNOutTtbar<<" , "<<theNInZmumu<<" , "<<theNOutZmumu<<"\n";
  
  
  // Derivatives for nInTtbar, needed for error propagation
  const double dNObservedIn = -factor;
  const double dNInOther = factor;
  const double dNObservedOut = factor*ratioInOutZmumu;
  const double dNOutOther = -factor*ratioInOutZmumu;
  const double dRatioInOutTtbar = (ratioInOutZmumu/diffRatio2)*bracket;
  const double dRatioInOutZmumu = -(ratioInOutTtbar/diffRatio2)*(ratioInOutTtbar*nOut - nIn);
  
  // Helper substitutes for individual contributions to absolute error ^2 of nInTtbar
  const double absErr2ContNObservedIn = std::pow(dNObservedIn,2)*nObservedInRelErr2*std::pow(nObservedIn,2);
  const double absErr2ContNInOther = std::pow(dNInOther,2)*nInRelErr2Other*std::pow(nInOther,2);
  const double absErr2ContNObservedOut = std::pow(dNObservedOut,2)*nObservedOutRelErr2*std::pow(nObservedOut,2);
  const double absErr2ContNOutOther = std::pow(dNOutOther,2)*nOutRelErr2Other*std::pow(nOutOther,2);
  const double absErr2ContRatioInOutTtbar = std::pow(dRatioInOutTtbar,2)*ratioInOutRelErr2Ttbar*std::pow(ratioInOutTtbar,2);
  const double absErr2ContRatioInOutZmumu = std::pow(dRatioInOutZmumu,2)*ratioInOutRelErr2Zmumu*std::pow(ratioInOutZmumu,2);
  
  // Corresponding error for nInTtbar
  const double nInAbsErr2Ttbar = absErr2ContNObservedIn + absErr2ContNInOther + absErr2ContNObservedOut + absErr2ContNOutOther + absErr2ContRatioInOutTtbar + absErr2ContRatioInOutZmumu;
  const double nInRelErr2Ttbar = nInAbsErr2Ttbar/std::pow(nInTtbar,2);
  
  theNInRelErr2UpTtbar = nInRelErr2Ttbar;
  theNInRelErr2DwTtbar = nInRelErr2Ttbar;
  
  const double nInAbsErrTtbar(std::sqrt(theNInRelErr2UpTtbar)*theNInTtbar);
  
  std::cout<<"ttbar in and statistical error (absolute values): "<<theNInTtbar<<" +- "<<nInAbsErrTtbar<<"\n";
  
  // Relative contributions
  theNInTtbarRel = theNInTtbar/nObservedIn;
  theNInZmumuRel = theNInZmumu/nObservedIn;
  theNOutTtbarRel = theNOutTtbar/nObservedOut;
  theNOutZmumuRel = theNOutZmumu/nObservedOut;
  
  std::cout<<"ttbar in, ttbar out, zmumu in, zmumu out (relative values): "
           <<theNInTtbarRel<<" , "<<theNOutTtbarRel<<" , "<<theNInZmumuRel<<" , "<<theNOutZmumuRel<<"\n";
  
  // Does the realtive error need additional error propagation??? At present, I don't think so
  theNInRelErr2UpTtbarRel = theNInRelErr2UpTtbar/std::pow(nObservedIn,2);
  theNInRelErr2DwTtbarRel = theNInRelErr2DwTtbar/std::pow(nObservedIn,2);
  
  const double nInAbsErrTtbarRel(std::sqrt(theNInRelErr2UpTtbarRel)*theNInTtbar);
  
  std::cout<<"ttbar in and statistical error (relative values): "<<theNInTtbarRel<<" +- "<<nInAbsErrTtbarRel<<"\n";
}
