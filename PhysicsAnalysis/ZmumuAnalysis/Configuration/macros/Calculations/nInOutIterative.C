#include <iostream>
#include <cmath>



double theNInTtbar(-1.);
double theNInZmumu(-1.);
double theNOutTtbar(-1.);
double theNOutZmumu(-1.);

double theNInRelErr2UpTtbar(-1.);
double theNInRelErr2DwTtbar(-1.);
double theNOutRelErr2UpTtbar(-1.);
double theNOutRelErr2DwTtbar(-1.);

double theNInRelErr2UpZmumu(-1.);
double theNInRelErr2DwZmumu(-1.);
double theNOutRelErr2UpZmumu(-1.);
double theNOutRelErr2DwZmumu(-1.);


// FIXME: For now treat errors symmetrically (already in input)
void nInOutIterative(const double nObservedIn, const double nObservedOut,
                     const double nObservedInRelErr2, const double nObservedOutRelErr2,
                     const double ratioInOutTtbar, const double ratioInOutZmumu,
		     const double ratioInOutRelErr2Ttbar, const double ratioInOutRelErr2Zmumu,
		     const double nInOther, const double nOutOther,
		     const double nOutZmumuStart){
  
  
  double nInTtbarEstimate(-999.);
  double nOutTtbarEstimate(-999.);
  double nInZmumuEstimate(-999.);
  double nOutZmumuEstimate(-999.);
  
  // Start value for iterations
  double nOutZmumu(nOutZmumuStart);
  
  unsigned int nIter(0);
  double epsilon(999.);
  while(std::fabs(epsilon)>0.01){
    const double nOutTtbar(nObservedOut - nOutZmumu - nOutOther);
    const double nInTtbar = ratioInOutTtbar*nOutTtbar;
    const double nInZmumu(nObservedIn - nInTtbar - nInOther);
    nOutZmumu = (1./ratioInOutZmumu)*nInZmumu;
    
    ++nIter;
    std::cout<<"Iteration, ttbar in, ttbar out, zmumu in, zmumu out: "
             <<nIter<<" , "<<nInTtbar<<" , "<<nOutTtbar<<" , "<<nInZmumu<<" , "<<nOutZmumu<<"\n";
    
    epsilon = nInTtbar - nInTtbarEstimate;
    nInTtbarEstimate = nInTtbar;
    nOutTtbarEstimate = nOutTtbar;
    nInZmumuEstimate = nInZmumu;
    nOutZmumuEstimate = nOutZmumu;
  }
  
  theNInTtbar = nInTtbarEstimate;
  theNInZmumu = nOutTtbarEstimate;
  theNOutTtbar = nInZmumuEstimate;
  theNOutZmumu = nOutZmumuEstimate;
  
  theNOutRelErr2UpTtbar = (nObservedOutRelErr2*std::pow(nObservedOut,2)) /std::pow(theNOutTtbar,2);
  theNOutRelErr2DwTtbar = (nObservedOutRelErr2*std::pow(nObservedOut,2)) /std::pow(theNOutTtbar,2);
  
  theNInRelErr2UpTtbar = ratioInOutRelErr2Ttbar*theNOutRelErr2UpTtbar;
  theNInRelErr2DwTtbar = ratioInOutRelErr2Ttbar*theNOutRelErr2DwTtbar;
  
  
  //theNInRelErr2UpZmumu = ;
  //theNInRelErr2DwZmumu = ;
  
  
  
}
