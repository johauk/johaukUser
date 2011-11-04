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



void PrintoutCollector::printSystematicTable(){
  std::vector<std::string>::const_iterator i_default;
  std::vector<std::string>::const_iterator i_syst1;
  std::vector<std::string>::const_iterator i_syst2;
  std::vector<std::string>::const_iterator i_syst3;
  
  Tools::printLine("Systematic table (pileup) for ratioTtbar");
  for(i_default=m_pileup_ratioInOutTtbar_["default"].begin(),
      i_syst1=m_pileup_ratioInOutTtbar_["pileup14"].begin(),
      i_syst2=m_pileup_ratioInOutTtbar_["pileup57"].begin(),
      i_syst3=m_pileup_ratioInOutTtbar_["pileup8plus"].begin();
      i_default!=m_pileup_ratioInOutTtbar_["default"].end();
      ++i_default, ++i_syst1, ++i_syst2, ++i_syst3){
    std::cout<<*i_default<<*i_syst1<<*i_syst2<<*i_syst3;
  }
  std::cout<<"\n\n\n";
  
  Tools::printLine("Systematic table (pileup) for ratioZmumu");
  for(i_default=m_pileup_ratioInOutZmumu_["default"].begin(),
      i_syst1=m_pileup_ratioInOutZmumu_["pileup14"].begin(),
      i_syst2=m_pileup_ratioInOutZmumu_["pileup57"].begin(),
      i_syst3=m_pileup_ratioInOutZmumu_["pileup8plus"].begin();
      i_default!=m_pileup_ratioInOutZmumu_["default"].end();
      ++i_default, ++i_syst1, ++i_syst2, ++i_syst3){
    std::cout<<*i_default<<*i_syst1<<*i_syst2<<*i_syst3;
  }
  std::cout<<"\n\n\n";
  
  Tools::printLine("Systematic table (pileup) for ttbarFraction");
  for(i_default=m_pileup_ttbarFraction_["default"].begin(),
      i_syst1=m_pileup_ttbarFraction_["pileup14"].begin(),
      i_syst2=m_pileup_ttbarFraction_["pileup57"].begin(),
      i_syst3=m_pileup_ttbarFraction_["pileup8plus"].begin();
      i_default!=m_pileup_ttbarFraction_["default"].end();
      ++i_default, ++i_syst1, ++i_syst2, ++i_syst3){
    std::cout<<*i_default<<*i_syst1<<*i_syst2<<*i_syst3;
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












