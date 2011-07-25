// .L ../Tools/ValueAndError.C++
// .L ../Samples/DefaultSample.C++
// .L ../Samples/Sample.C++
// .L FullAnalysis.C++


#include "FullAnalysis.h"

#include "ZmumuAnalysis/Configuration/macros/Samples/Data.h"
#include "ZmumuAnalysis/Configuration/macros/Samples/Mc.h"
#include "ZmumuAnalysis/Configuration/macros/Samples/Simulation.h"

// For default analysis
#include "ZmumuAnalysis/Configuration/macros/Calculations/efficiency.h"
#include "ZmumuAnalysis/Configuration/macros/Calculations/luminosity.h"
#include "ZmumuAnalysis/Configuration/macros/Calculations/nObserved.h"
#include "ZmumuAnalysis/Configuration/macros/Calculations/nBackground.h"
#include "ZmumuAnalysis/Configuration/macros/Calculations/nSignal.h"
#include "ZmumuAnalysis/Configuration/macros/Calculations/crossSection.h"
#include "ZmumuAnalysis/Configuration/macros/Calculations/crossSectionFromMc.h"

// For ttbar estimate from sidebands
#include "ZmumuAnalysis/Configuration/macros/Calculations/ratioInOut.h"
#include "ZmumuAnalysis/Configuration/macros/Calculations/nObservedSideband.h"
#include "ZmumuAnalysis/Configuration/macros/Calculations/nBackgroundSideband.h"
//#include "ZmumuAnalysis/Configuration/macros/Calculations/nSignalSideband.h"
#include "ZmumuAnalysis/Configuration/macros/Calculations/ttbarFraction.h"
#include "ZmumuAnalysis/Configuration/macros/Drawings/zTtbarFit.h"

#include "ZmumuAnalysis/Configuration/macros/Tools/printLine.h"



FullAnalysis::FullAnalysis(){
  Tools::printLine("Data sample");
  this->setDataSample();
  Tools::printLine("MC samples");
  this->setMcSamples();
  Tools::printLine("Simulated signal sample");
  this->setSimulationSample();
}



FullAnalysis::~FullAnalysis(){}



void FullAnalysis::defaultAnalysis(){
  Tools::printLine("Efficiency from MC");
  this->setEfficiency();
  Tools::printLine("Luminosity");
  this->setLuminosity();
  Tools::printLine("No. of observed events");
  this->setNObserved();
  Tools::printLine("No. of background events");
  this->setNBackground();
  Tools::printLine("No. of signal events");
  this->setNSignal();
  Tools::printLine("Cross section");
  this->setCrossSection();
  Tools::printLine("Cross section from MC");
  this->setCrossSectionFromMc();
}



void FullAnalysis::ttbarFromSideband(const Sideband& sideband){
  Tools::printLine("Ratio In/Out");
  this->setRatioInOut(sideband);
  Tools::printLine("No. of observed events (sidebands)");
  this->setNObservedSideband(sideband);
  Tools::printLine("No. of background events (sidebands)");
  this->setNBackgroundSideband(sideband);
  //Tools::printLine("No. of signal events (sidebands)");
  //this->setNSignalSideband(sideband);
  Tools::printLine("ttbar and zmumu yields");
  this->setTtbarFraction();
  Tools::printLine("Plot fitted dimuon distribution");
  this->zTtbarFit();
}













