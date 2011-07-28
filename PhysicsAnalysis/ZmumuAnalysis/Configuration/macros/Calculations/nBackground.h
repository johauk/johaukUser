#include "ZmumuAnalysis/Configuration/macros/Tools/FullAnalysis.h"


#include "ZmumuAnalysis/Configuration/macros/Tools/eventCount.h"

#include <iostream>



void FullAnalysis::setNBackground(){
  if(this->backgroundSamples().size()==0){
    std::cout<<"\tNo input sample\n"
             <<"\t... take dummy nBackground\n";
    nBackgroundZmumu_ = ValueAndError::dummyValues();
    nBackgroundTtbar_ = ValueAndError::dummyValues();
    nBackgroundOther_ = ValueAndError::dummyValues();
    nBackground_ = ValueAndError::dummyValues();
    std::cout<<"Efficiency: "<<this->nBackground().print()<<"\n";
    return;
  }
  const std::vector<McSample*>& v_background = this->backgroundSamples();
  
  
  std::vector<ValueAndError> v_nBkgOther;
  std::vector<McSample*>::const_iterator i_background;
  for(i_background = v_background.begin(); i_background != v_background.end(); ++i_background){
    const McSample& background = **i_background;
    
    TH1* events(0);
    events = eventCount(background.file(), this->recoSelectionStep());
    if(!events){
      std::cout<<"\tMissing is histogram containing no. of MC events for: "<<background.datasetName_<<"\n"
               <<"\t... nObserved calculation stopped\n";
      return;
    }
    const double nEvents(events->GetEntries());
    // Do not use this weighting, use implicit one
    //const double nEffectiveEvents(nEvents/background.dynamicWeight());
    
    ValueAndError nSelectedEvent;
    nSelectedEvent.setValue(nEvents);
    nSelectedEvent.setAbsErr2Up(nEvents);
    nSelectedEvent.setAbsErr2Dw(nEvents);
    
    ValueAndErrorStatSystLumi effectiveWeight = background.effectiveWeight(this->luminosity());
    
    ValueAndErrorStatSystLumi nSelectedEventWeighted;
    nSelectedEventWeighted.setValue(nSelectedEvent.value()*effectiveWeight.value());
    nSelectedEventWeighted.setRelErr2StatUp(nSelectedEvent.relErr2Up());
    nSelectedEventWeighted.setRelErr2StatDw(nSelectedEvent.relErr2Dw());
    nSelectedEventWeighted.setRelErr2SystUp(effectiveWeight.relErr2SystUp());
    nSelectedEventWeighted.setRelErr2SystDw(effectiveWeight.relErr2SystDw());
    nSelectedEventWeighted.setRelErr2LumiUp(effectiveWeight.relErr2LumiUp());
    nSelectedEventWeighted.setRelErr2LumiDw(effectiveWeight.relErr2LumiDw());
    
    std::cout<<"No. events (unweighted) for \""<<background.datasetName()<<"\": "
             <<nSelectedEvent.print()<<"\n";
    std::cout<<"No. events (weighted) for \""<<background.datasetName()<<"\": "
             <<nSelectedEventWeighted.print()<<"\n";
    
    if(background.datasetName()=="zmumuUdsc"){
      nBackgroundZmumu_.setValue(nSelectedEventWeighted.value());
      nBackgroundZmumu_.setRelErr2Up(nSelectedEventWeighted.relErr2Up());
      nBackgroundZmumu_.setRelErr2Dw(nSelectedEventWeighted.relErr2Dw());
    }
    else if(background.datasetName()=="ttbar"){
      nBackgroundTtbar_.setValue(nSelectedEventWeighted.value());
      nBackgroundTtbar_.setRelErr2Up(nSelectedEventWeighted.relErr2Up());
      nBackgroundTtbar_.setRelErr2Dw(nSelectedEventWeighted.relErr2Dw());
    }
    else{
      ValueAndError nBkgOther;
      nBkgOther.setValue(nSelectedEventWeighted.value());
      nBkgOther.setRelErr2Up(nSelectedEventWeighted.relErr2Up());
      nBkgOther.setRelErr2Dw(nSelectedEventWeighted.relErr2Dw());
      v_nBkgOther.push_back(nBkgOther);
    }
  }
  
  std::vector<ValueAndError>::const_iterator i_nBkgOther;
  double nBkgOtherValue(0.);
  double nBkgAbsErr2Up(0.);
  double nBkgAbsErr2Dw(0.);
  for(i_nBkgOther = v_nBkgOther.begin(); i_nBkgOther != v_nBkgOther.end(); ++i_nBkgOther){
    nBkgOtherValue += i_nBkgOther->value();
    nBkgAbsErr2Up += i_nBkgOther->absErr2Up();
    nBkgAbsErr2Dw += i_nBkgOther->absErr2Dw();
  }
  nBackgroundOther_.setValue(nBkgOtherValue);
  nBackgroundOther_.setAbsErr2Up(nBkgAbsErr2Up);
  nBackgroundOther_.setAbsErr2Dw(nBkgAbsErr2Dw);
  
  nBackground_.setValue(this->nBackgroundZmumu().value() + this->nBackgroundTtbar().value() + this->nBackgroundOther().value());
  nBackground_.setAbsErr2Up(this->nBackgroundZmumu().absErr2Up() + this->nBackgroundTtbar().absErr2Up() + this->nBackgroundOther().absErr2Up());
  nBackground_.setAbsErr2Dw(this->nBackgroundZmumu().absErr2Dw() + this->nBackgroundTtbar().absErr2Dw() + this->nBackgroundOther().absErr2Dw());
  
  
  std::cout<<"No. of expected background events (all): "
           <<this->nBackground().print()<<"\n";
  std::cout<<"No. of expected background events (only zmumu): "
           <<this->nBackgroundZmumu().print()<<"\n";
  std::cout<<"No. of expected background events (only ttbar): "
           <<this->nBackgroundTtbar().print()<<"\n";
  std::cout<<"No. of expected background events (only other): "
           <<this->nBackgroundOther().print()<<"\n";
  
}













