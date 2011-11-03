#include "ZmumuAnalysis/Configuration/macros/Tools/FullAnalysis.h"

#include <iostream>

#include "ZmumuAnalysis/Configuration/macros/Tools/printLine.h"



void FullAnalysis::printTable(){
  std::vector<std::string>::const_iterator i_print;
  
  Tools::printLine("Table for nObserved");
  for(i_print = v_nObservedInOut_.begin(); i_print != v_nObservedInOut_.end(); ++i_print){
    std::cout<<*i_print;
  }
  
  Tools::printLine("Table for nSimulation");
  for(i_print = v_nSimulationInOut_.begin(); i_print != v_nSimulationInOut_.end(); ++i_print){
    std::cout<<*i_print;
  }
  
  Tools::printLine("Table for ratioInOut");
  for(i_print = v_ratioInOut_.begin(); i_print != v_ratioInOut_.end(); ++i_print){
    std::cout<<*i_print;
  }
  
  Tools::printLine("Table for ttbarFraction");
  for(i_print = v_ttbarFraction_.begin(); i_print != v_ttbarFraction_.end(); ++i_print){
    std::cout<<*i_print;
  }
}







