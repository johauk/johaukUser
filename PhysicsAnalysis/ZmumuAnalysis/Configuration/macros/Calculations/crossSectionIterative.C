#include <iostream>
#include <cmath>

#include "ZmumuAnalysis/Configuration/macros/Samples/defaultSampleStruct.C"

#include "ZmumuAnalysis/Configuration/macros/Samples/allSampleStruct.C"



double theNBackgroundOnlyTopIterative(-1.);
double theCrossSectionIterative(-1.);



void crossSectionIterative(const double nObservedIn, const double nObservedOut,
                           const double nBackgroundWoTopIn, const double nBackgroundWoTopOut,
                           const double ratioInOut, const double nSignalOutMc,
			   const double efficiency, const double luminosity,
			   const double crossSectionStart, const double signalSampleCrossSection){
  
  double nTopIn(-999.);
  // Starting value for iterations
  double crossSectionEstimate(crossSectionStart);
  
  unsigned int nIter(0);
  double epsilon(999.);
  while(std::fabs(epsilon)>0.001){
    const double scaleFactor(crossSectionEstimate/signalSampleCrossSection);
    const double nSignalOut(nSignalOutMc*scaleFactor);
    const double nTopOut(nObservedOut - nBackgroundWoTopOut - nSignalOut);
    nTopIn = ratioInOut*nTopOut;
    
    const double nBackgroundIn(nBackgroundWoTopIn + nTopIn);
    const double nSignalIn(nObservedIn - nBackgroundIn);
    const double crossSection(nSignalIn/(efficiency*luminosity));
    
    epsilon = crossSection - crossSectionEstimate;
    crossSectionEstimate = crossSection;
    ++nIter;
    std::cout<<"Iteration, top background, cross section: "
             <<nIter<<" , "<<nTopIn<<" , "<<crossSectionEstimate<<"\n";
  }
  
  
/*  
  const McStruct& zmumuB = *allSampleStruct.signalStruct;
  const std::string datasetName(zmumuB.datasetName_);
  const double nEvents(zmumuB.nEvents_);
  const double filterEfficiency(zmumuB.filterEfficiency_);
  const TColor* color(zmumuB.color_);
  const double crossSectionStart2(zmumuB.crossSection_*scaleFactor);
  
  
  McStruct* newSignal(0);
  if(!newSignal)newSignal = new McStruct("zmumuB", nEvents, crossSectionStart2, filterEfficiency, color);
*/  
  
  
  theNBackgroundOnlyTopIterative = nTopIn;
  theCrossSectionIterative = crossSectionEstimate;
  
  std::cout<<"Number of iterations: "<<nIter<<"\n";
  std::cout<<"Iterative top background: "<<theNBackgroundOnlyTopIterative<<"\n";
  std::cout<<"Iterative cross section: "<<theCrossSectionIterative<<"\n";
}
















