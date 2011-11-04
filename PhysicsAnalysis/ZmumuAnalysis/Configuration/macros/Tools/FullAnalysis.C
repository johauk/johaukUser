// .L ../Tools/ValueAndError.C++
// .L ../Samples/DefaultSample.C++
// .L ../Samples/Sample.C++
// .L FullAnalysis.C++


#include "FullAnalysis.h"

// Defintion of samples to use
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
#include "ZmumuAnalysis/Configuration/macros/Calculations/correctRatioInOutTtbar.h"
#include "ZmumuAnalysis/Configuration/macros/Calculations/correctRatioInOutZmumu.h"
#include "ZmumuAnalysis/Configuration/macros/Calculations/nObservedSideband.h"
#include "ZmumuAnalysis/Configuration/macros/Calculations/nBackgroundSideband.h"
#include "ZmumuAnalysis/Configuration/macros/Calculations/ttbarFraction.h"
#include "ZmumuAnalysis/Configuration/macros/Drawings/zTtbarFit.h"

// For printout of tables in LaTeX format
#include "ZmumuAnalysis/Configuration/macros/Drawings/fillTable.h"

// Further helpers
#include "ZmumuAnalysis/Configuration/macros/Tools/printLine.h"



FullAnalysis::FullAnalysis(PrintoutCollector& printoutCollector, const std::string& inputFolderName):
inputFolder_(inputFolderName),
dataSample_(0), signalSample_(0), simulationSample_(0),
printoutCollector_(printoutCollector)
{
  Tools::printLine("Job configuration");
  std::cout<<"Files are taken from folder: "<<inputFolder_<<"\n";
  Tools::printLine("Data sample");
  this->setDataSample();
  Tools::printLine("MC samples");
  this->setMcSamples();
  Tools::printLine("Simulated signal sample");
  this->setSimulationSample();
}



FullAnalysis::~FullAnalysis(){
  // Works without error, but TColors of signal and background samples are still defined...
  if(dataSample_)delete dataSample_;
  if(signalSample_)delete signalSample_;
  if(simulationSample_)delete simulationSample_;
  for(std::vector<McSample*>::iterator i_background = v_backgroundSample_.begin(); i_background != v_backgroundSample_.end(); ++i_background){
    if(*i_background) (**i_background).~McSample();
    //if(*i_background)delete *i_background;
  }
}



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
  Tools::printLine("Correction for ttbar Ratio In/Out");
  this->correctRatioInOutTtbar();
  Tools::printLine("Correction for Zmumu Ratio In/Out");
  this->correctRatioInOutZmumu();
  Tools::printLine("No. of observed events (sidebands)");
  this->setNObservedSideband(sideband);
  Tools::printLine("No. of background events (sidebands)");
  this->setNBackgroundSideband(sideband);
  
  //nBackgroundOther_.setValue(nObserved().value()*0.03);
  //nBackgroundOtherSideband_.setValue(nObservedSideband().value()*0.03);
  
  
  Tools::printLine("ttbar and zmumu yields");
  this->setTtbarFraction();
  Tools::printLine("Plot fitted dimuon distribution");
  //this->zTtbarFit();
  this->zTtbarFit(false);
  
  this->fillTable();
  this->fillSystematicTable();
}













