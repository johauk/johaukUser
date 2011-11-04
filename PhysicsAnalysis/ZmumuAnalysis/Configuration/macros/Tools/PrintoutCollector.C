#include "PrintoutCollector.h"

#include "ZmumuAnalysis/Configuration/macros/Tools/printLine.h"


#include <iostream>



PrintoutCollector::PrintoutCollector(){}



PrintoutCollector::~PrintoutCollector(){}




void PrintoutCollector::printTable(){
  std::vector<std::string>::const_iterator i_print;

  Tools::printLine("Table for nObserved");
  for(i_print = v_nObservedInOut_.begin(); i_print != v_nObservedInOut_.end(); ++i_print){
    std::cout<<*i_print;
  }
  std::cout<<"\n\n\n";

  Tools::printLine("Table for nSimulation");
  for(i_print = v_nSimulationInOut_.begin(); i_print != v_nSimulationInOut_.end(); ++i_print){
    std::cout<<*i_print;
  }
  std::cout<<"\n\n\n";
  
  Tools::printLine("Table for ratioInOut");
  for(i_print = v_ratioInOut_.begin(); i_print != v_ratioInOut_.end(); ++i_print){
    std::cout<<*i_print;
  }
  std::cout<<"\n\n\n";
  
  Tools::printLine("Table for ttbarFraction");
  for(i_print = v_ttbarFraction_.begin(); i_print != v_ttbarFraction_.end(); ++i_print){
    std::cout<<*i_print;
  }
  std::cout<<"\n\n\n";
  
  Tools::printLine("Table for error contribution to ttbarFraction");
  for(i_print = v_ttbarFractionErrContribution_.begin(); i_print != v_ttbarFractionErrContribution_.end(); ++i_print){
    std::cout<<*i_print;
  }
  std::cout<<"\n\n\n";
}



void PrintoutCollector::hline(){
  v_nObservedInOut_.push_back("\\hline\n");
  v_nSimulationInOut_.push_back("\\hline\n");
  v_ratioInOut_.push_back("\\hline\n");
  v_ttbarFraction_.push_back("\\hline\n");
  v_ttbarFractionErrContribution_.push_back("\\hline\n");
}












