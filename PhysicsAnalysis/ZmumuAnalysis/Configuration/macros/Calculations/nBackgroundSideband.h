#include "ZmumuAnalysis/Configuration/macros/Tools/FullAnalysis.h"


#include "ZmumuAnalysis/Configuration/macros/Tools/eventCount.h"

#include <iostream>



void FullAnalysis::setNBackgroundSideband(const Sideband& sideband){
  if(this->backgroundSamples().size()==0){
    std::cout<<"\tNo input sample\n"
             <<"\t... take dummy nBackgroundSideband\n";
    nBackgroundZmumuSideband_ = ValueAndError::dummyValues();
    nBackgroundTtbarSideband_ = ValueAndError::dummyValues();
    nBackgroundOtherSideband_ = ValueAndError::dummyValues();
    nBackgroundSideband_ = ValueAndError::dummyValues();
    std::cout<<"Efficiency: "<<this->nBackgroundSideband().print()<<"\n";
    return;
  }
  const std::vector<McSample*>& v_background = this->backgroundSamples();
  
  
  std::vector<ValueAndError> v_nBkgOtherSideband;
  std::vector<McSample*>::const_iterator i_background;
  for(i_background = v_background.begin(); i_background != v_background.end(); ++i_background){
    const McSample& background = **i_background;
    
    
    TH1* eventsOut1(0);
    if(sideband==upper || sideband==both){
      TString pluginSuffix(this->recoSelectionStep());
      pluginSuffix.Insert(4,"ZVetoHigh");
      eventsOut1 = Tools::eventCount(background.file(), pluginSuffix);
      if(!eventsOut1){
        std::cout<<"\tMissing is histogram containing no. of MC events for \"Out1\": "<<background.datasetName()<<"\n"
                 <<"\t... ratioInOut calculation stopped\n";
        return;
      }
    }
    const double nEventsOut1(eventsOut1 ? eventsOut1->GetEntries() : 0.);
    TH1* eventsOut2(0);
    if(sideband==lower || sideband==both){
      TString pluginSuffix(this->recoSelectionStep());
      pluginSuffix.Insert(4,"ZVetoLow");
      eventsOut2 = Tools::eventCount(background.file(), pluginSuffix);
      if(!eventsOut2){
        std::cout<<"\tMissing is histogram containing no. of MC events for \"Out2\": "<<background.datasetName()<<"\n"
                 <<"\t... ratioInOut calculation stopped\n";
        return;
      }
    }
    const double nEventsOut2(eventsOut2 ? eventsOut2->GetEntries() : 0.);
    const double nEventsOut(nEventsOut1 + nEventsOut2);
    
    ValueAndError nSelectedEvent;
    nSelectedEvent.setValue(nEventsOut);
    nSelectedEvent.setAbsErr2Up(nEventsOut);
    nSelectedEvent.setAbsErr2Dw(nEventsOut);
    
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
      nBackgroundZmumuSideband_.setValue(nSelectedEventWeighted.value());
      nBackgroundZmumuSideband_.setRelErr2Up(nSelectedEventWeighted.relErr2Up());
      nBackgroundZmumuSideband_.setRelErr2Dw(nSelectedEventWeighted.relErr2Dw());
    }
    else if(background.datasetName()=="ttbar"){
      nBackgroundTtbarSideband_.setValue(nSelectedEventWeighted.value());
      nBackgroundTtbarSideband_.setRelErr2Up(nSelectedEventWeighted.relErr2Up());
      nBackgroundTtbarSideband_.setRelErr2Dw(nSelectedEventWeighted.relErr2Dw());
    }
    else{
      ValueAndError nBkgOther;
      nBkgOther.setValue(nSelectedEventWeighted.value());
      nBkgOther.setRelErr2Up(nSelectedEventWeighted.relErr2Up());
      nBkgOther.setRelErr2Dw(nSelectedEventWeighted.relErr2Dw());
      v_nBkgOtherSideband.push_back(nBkgOther);
    }
  }
  
  std::vector<ValueAndError>::const_iterator i_nBkgOther;
  double nBkgOtherValue(0.);
  double nBkgAbsErr2Up(0.);
  double nBkgAbsErr2Dw(0.);
  for(i_nBkgOther = v_nBkgOtherSideband.begin(); i_nBkgOther != v_nBkgOtherSideband.end(); ++i_nBkgOther){
    nBkgOtherValue += i_nBkgOther->value();
    nBkgAbsErr2Up += i_nBkgOther->absErr2Up();
    nBkgAbsErr2Dw += i_nBkgOther->absErr2Dw();
  }
  nBackgroundOtherSideband_.setValue(nBkgOtherValue);
  nBackgroundOtherSideband_.setAbsErr2Up(nBkgAbsErr2Up);
  nBackgroundOtherSideband_.setAbsErr2Dw(nBkgAbsErr2Dw);
  
  nBackgroundSideband_.setValue(this->nBackgroundZmumuSideband().value() + this->nBackgroundTtbarSideband().value() + this->nBackgroundOtherSideband().value());
  nBackgroundSideband_.setAbsErr2Up(this->nBackgroundZmumuSideband().absErr2Up() + this->nBackgroundTtbarSideband().absErr2Up() + this->nBackgroundOtherSideband().absErr2Up());
  nBackgroundSideband_.setAbsErr2Dw(this->nBackgroundZmumuSideband().absErr2Dw() + this->nBackgroundTtbarSideband().absErr2Dw() + this->nBackgroundOtherSideband().absErr2Dw());
  
  
  std::cout<<"No. of expected background events (all): "
           <<this->nBackgroundSideband().print()<<"\n";
  std::cout<<"No. of expected background events (only zmumu): "
           <<this->nBackgroundZmumuSideband().print()<<"\n";
  std::cout<<"No. of expected background events (only ttbar): "
           <<this->nBackgroundTtbarSideband().print()<<"\n";
  std::cout<<"No. of expected background events (only other): "
           <<this->nBackgroundOtherSideband().print()<<"\n";
  
  
}






