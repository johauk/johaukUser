#include "ZmumuAnalysis/Configuration/macros/Tools/FullAnalysis.h"



#include <iostream>
#include <iomanip>
#include <sstream>



void FullAnalysis::fillTable(){
  const std::string selectionStep(this->recoSelectionStep());
  std::stringstream printout;
  std::stringstream parameter1;
  std::stringstream parameter2;
  
  printout<<std::left<<std::setw(10)<<selectionStep<<" & "
          <<std::setw(10)<<this->nObserved().value()<<" & "
	  <<std::setw(10)<<this->nObservedSideband().value()<<" \\\\\n";
  v_nObservedInOut_.push_back(printout.str());
  printout.str("");
  printout.clear();
  
  
  printout<<std::left<<std::setw(10)<<selectionStep<<" & "
          <<std::fixed<<std::setprecision(1)
	  <<std::setw(10)<<this->nTtbarInMc()<<" & "
	  <<std::setw(10)<<this->nTtbarOutMc()<<" & "
	  <<std::setw(10)<<this->nZmumuInMc()<<" & "
	  <<std::setw(10)<<this->nZmumuOutMc()<<" & "
	  <<this->nBackgroundOther().value()<<" & "
	  <<this->nBackgroundOtherSideband().value()<<" \\\\\n";
  v_nSimulationInOut_.push_back(printout.str());
  printout.str("");
  printout.clear();
  
  
  parameter1<<std::fixed<<std::setprecision(3)
            <<"$"<<this->ratioInOutTtbar().value()<<"\\pm"<<this->ratioInOutTtbar().absErrUp()<<"$";
  parameter2<<std::fixed<<std::setprecision(2)
            <<"$"<<this->ratioInOutZmumu().value()<<"\\pm"<<this->ratioInOutZmumu().absErrUp()<<"$";
  printout<<std::left<<std::setw(10)<<selectionStep<<" & "
	  <<std::setw(20)<<parameter1.str()<<" & "
	  <<std::setw(20)<<parameter2.str()<<" \\\\\n";
  v_ratioInOut_.push_back(printout.str());
  printout.str("");
  printout.clear();
  parameter1.str("");
  parameter1.clear();
  parameter2.str("");
  parameter2.clear();
  
  
  parameter1<<std::fixed<<std::setprecision(1)
            <<"$"<<this->ttbarEstimate().value()<<"\\pm"<<this->ttbarEstimate().absErrUp()<<"$";
  parameter2<<std::fixed<<std::setprecision(2)
            <<"$"<<100.*this->ttbarFraction().value()<<"\\pm"<<100.*this->ttbarFraction().absErrUp()<<"$";
  printout<<std::left<<std::setw(10)<<selectionStep<<" & "
	  <<std::fixed<<std::setprecision(1)
	  <<std::setw(20)<<parameter1.str()<<" & "
	  <<std::setw(10)<<this->ttbarEstimateSideband()<<" & "
	  <<std::setw(20)<<parameter2.str()<<" & "
	  <<std::setw(10)<<100.*this->ttbarFractionSideband()<<" & "
	  <<std::setw(10)<<100.*this->zmumuFraction()<<" & "
	  <<std::setw(10)<<100.*this->zmumuFractionSideband()<<" \\\\\n";
  v_ttbarFraction_.push_back(printout.str());
  printout.str("");
  printout.clear();
  parameter1.str("");
  parameter1.clear();
  parameter2.str("");
  parameter2.clear();
}







