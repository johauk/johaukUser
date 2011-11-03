#include "ZmumuAnalysis/Configuration/macros/Tools/FullAnalysis.h"



#include <iostream>
#include <iomanip>
#include <sstream>



void FullAnalysis::fillTable(){
  
  const std::string selectionStep(this->assignLabel());
  
  std::stringstream printout;
  std::stringstream parameter1;
  std::stringstream parameter2;
  
  std::stringstream ss_selectionStep;
  ss_selectionStep<<std::left<<std::setw(16)<<selectionStep<<" & ";
  
  printout<<ss_selectionStep.str()
          <<std::setw(8)<<this->nObserved().value()<<" & "
	  <<std::setw(8)<<this->nObservedSideband().value()<<" \\\\\n";
  printoutCollector_.v_nObservedInOut_.push_back(printout.str());
  printout.str("");
  printout.clear();
  
  
  printout<<ss_selectionStep.str()
          <<std::fixed<<std::setprecision(1)
	  <<std::setw(10)<<this->nTtbarInMc()<<" & "
	  <<std::setw(10)<<this->nTtbarOutMc()<<" & "
	  <<std::setw(10)<<this->nZmumuInMc()<<" & "
	  <<std::setw(10)<<this->nZmumuOutMc()<<" & "
	  <<std::setprecision(0)
	  <<this->nBackgroundOther().value()<<" & "
	  <<this->nBackgroundOtherSideband().value()<<" \\\\\n";
  printoutCollector_.v_nSimulationInOut_.push_back(printout.str());
  printout.str("");
  printout.clear();
  
  
  parameter1<<std::fixed<<std::setprecision(3)
            <<"$"<<this->ratioInOutTtbar().value()<<"\\pm"<<this->ratioInOutTtbar().absErrUp()<<"$";
  parameter2<<std::fixed<<std::setprecision(2)
            <<"$"<<this->ratioInOutZmumu().value()<<"\\pm"<<this->ratioInOutZmumu().absErrUp()<<"$";
  printout<<ss_selectionStep.str()
	  <<std::setw(15)<<parameter1.str()<<" & "
	  <<std::setw(15)<<parameter2.str()<<" \\\\\n";
  printoutCollector_.v_ratioInOut_.push_back(printout.str());
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
  printout<<ss_selectionStep.str()
	  <<std::fixed<<std::setprecision(1)
	  <<std::setw(17)<<parameter1.str()<<" & "
	  <<std::setw(6)<<this->ttbarEstimateSideband()<<" & "
	  <<std::setw(17)<<parameter2.str()<<" & "
	  <<std::setw(6)<<100.*this->ttbarFractionSideband()<<" & "
	  <<std::setw(6)<<100.*this->zmumuFraction()<<" & "
	  <<std::setw(6)<<100.*this->zmumuFractionSideband()<<" \\\\\n";
  printoutCollector_.v_ttbarFraction_.push_back(printout.str());
  printout.str("");
  printout.clear();
  parameter1.str("");
  parameter1.clear();
  parameter2.str("");
  parameter2.clear();
}




std::string FullAnalysis::assignLabel()const{
  const std::string& inputFolderName(this->inputFolder());
  const std::string recoStep(this->recoSelectionStep());
  if(inputFolderName=="")return recoStep;
  else if(inputFolderName=="False_HeM__True_default"){
    if(recoStep=="Step3")return "Dimuons";
    else if(recoStep=="Step4")return "1 jet";
    else if(recoStep=="Step5")return "UNDEFINED";
    else if(recoStep=="Step6")return "1 b (HE)";
    else if(recoStep=="Step7a")return "UNDEFINED";
    else if(recoStep=="Step7")return "UNDEFINED";
    else return "--UNKNOWN STEP--";
  }
  else if(inputFolderName=="True_HeM__True_default"){
    if(recoStep=="Step3")return "UNDEFINED";
    else if(recoStep=="Step4")return "UNDEFINED";
    else if(recoStep=="Step5")return "UNDEFINED";
    else if(recoStep=="Step6")return "1 b (HE) \\& MET";
    else if(recoStep=="Step7a")return "UNDEFINED";
    else if(recoStep=="Step7")return "UNDEFINED";
    else return "--UNKNOWN STEP--";
  }
  else if(inputFolderName=="False_HpT_HeM_True_default"){
    if(recoStep=="Step3")return "UNDEFINED";
    else if(recoStep=="Step4")return "UNDEFINED";
    else if(recoStep=="Step5")return "UNDEFINED";
    else if(recoStep=="Step6")return "1 b (HP)";
    else if(recoStep=="Step7a")return "UNDEFINED";
    else if(recoStep=="Step7")return "UNDEFINED";
    else return "--UNKNOWN STEP--";
  }
  else if(inputFolderName=="True_HpT_HeM_True_default"){
    if(recoStep=="Step3")return "UNDEFINED";
    else if(recoStep=="Step4")return "UNDEFINED";
    else if(recoStep=="Step5")return "UNDEFINED";
    else if(recoStep=="Step6")return "1 b (HP) \\& MET";
    else if(recoStep=="Step7a")return "+ 2nd jet";
    else if(recoStep=="Step7")return "+ 2nd b (HE)";
    else return "--UNKNOWN STEP--";
  }
  else return "--UNKNOWN--";
}











