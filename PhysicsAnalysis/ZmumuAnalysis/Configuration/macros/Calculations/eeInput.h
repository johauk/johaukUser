#include "ZmumuAnalysis/Configuration/macros/Tools/FullAnalysis.h"


#include <iostream>
#include <cmath>



// The calculation works either with two split files for C and UDS components of the Zmumu, or with one file containing all components UDSC


void FullAnalysis::eeInput(const std::string& jobSetup){
  std::cout<<"\tTake all important input values for ee analysis from lookup tables\n";
  std::cout<<"\tJob setup: "<<jobSetup<<"\n";
  
  double nObs(-999.);
  double nObsSideband(-999.);
  if(jobSetup=="HE"){
    nBackgroundOther_ = ValueAndError::dummyValues(0.,0.,0.);
    nBackgroundOtherSideband_ = ValueAndError::dummyValues(0.,0.,0.);
    nZmumuInMc_ = 21301.;
    nZmumuOutMc_ = 362.0;
    nTtbarInMc_ = 4663.;
    nTtbarOutMc_ = 4219.3;
    nObs = 4026.;
    nObsSideband = 486.;
  }
  else if(jobSetup=="HP"){
    nBackgroundOther_ = ValueAndError::dummyValues(0.,0.,0.);
    nBackgroundOtherSideband_ = ValueAndError::dummyValues(0.,0.,0.);
    nZmumuInMc_ = 9776.;
    nZmumuOutMc_ = 143.89;
    nTtbarInMc_ = 3525.;
    nTtbarOutMc_ = 3204.9;
    nObs = 1991.;
    nObsSideband = 347.;
  }
  else{
    std::cout<<"\tInvalid job setup: "<<jobSetup<<"\n"
             <<"Take dummy values for ee input";
    nBackgroundOther_ = ValueAndError::dummyValues(0.,0.,0.);
    nBackgroundOtherSideband_ = ValueAndError::dummyValues(0.,0.,0.);
    nZmumuInMc_ = 0.;
    nZmumuOutMc_ = 0.;
    nTtbarInMc_ = 0.;
    nTtbarOutMc_ = 0.;
    nObs = 0.;
    nObsSideband = 0.;
    return;
  }
  
  nOtherIn_ = ValueAndError::dummyValues(0.,0.,0.);
  nOtherOut_ = ValueAndError::dummyValues(0.,0.,0.);
  
  nObserved_.setValue(nObs);
  nObserved_.setAbsErrUp(std::sqrt(nObs));
  nObserved_.setAbsErrDw(std::sqrt(nObs));
  nObservedSideband_.setValue(nObsSideband);
  nObservedSideband_.setAbsErrUp(std::sqrt(nObsSideband));
  nObservedSideband_.setAbsErrDw(std::sqrt(nObsSideband));
  
  std::cout<<"\n";
  std::cout<<"Number of events (In, Out) for ttbar: "<<this->nTtbarInMc()<<" , "<<this->nTtbarOutMc()<<"\n";
  std::cout<<"Number of events (In, Out) for zmumu: "<<this->nZmumuInMc()<<" , "<<this->nZmumuOutMc()<<"\n";
  std::cout<<"Number of events (In, Out) for other: "<<this->nOtherIn().value()<<" , "<<this->nOtherOut().value()<<"\n";
  std::cout<<"\n";
  std::cout<<"No. observed events (candidates): "<<this->nObserved().print()<<"\n";
  std::cout<<"No. observed events (candidates) in sidebands: "<<this->nObservedSideband().print()<<"\n";
}





