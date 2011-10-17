#include "ZmumuAnalysis/Configuration/macros/Tools/FullAnalysis.h"


#include "ZmumuAnalysis/Configuration/macros/Tools/eventCount.h"

#include <iostream>
#include <cmath>



// The calculation works either with two split files for C and UDS components of the Zmumu, or with one file containing all components UDSC


void FullAnalysis::setRatioInOut(const Sideband& sideband){
  if(!this->signalSample() || this->backgroundSamples().size()==0){
    std::cout<<"\tNo input sample\n"
             <<"\t... take dummy ratioInOut\n";
    ratioInOutZmumu_ = ValueAndErrorStatSyst::dummyValues();
    ratioInOutTtbar_ = ValueAndErrorStatSyst::dummyValues();
    std::cout<<"Ratio In/Out for zmumu: "<<this->ratioInOutZmumu().print()<<"\n";
    std::cout<<"Ratio In/Out for ttbar: "<<this->ratioInOutTtbar().print()<<"\n";
    return;
  }
  const McSample& zmumuB = *this->signalSample();
  const std::vector<McSample*>& v_background = this->backgroundSamples();
  
  double nInTtbar(0.);
  double nInZmumuC(0.);
  double nInZmumuUds(0.);
  double nInZmumuUdsc(0.);
  double nInOther(0.);
  double nOutTtbar(0.);
  double nOutZmumuC(0.);
  double nOutZmumuUds(0.);
  double nOutZmumuUdsc(0.);
  double nOutOther(0.);
  std::vector<McSample*>::const_iterator i_background;
  for(i_background = v_background.begin(); i_background != v_background.end(); ++i_background){
    const McSample& background = **i_background;
    
    TH1* eventsIn(0);
    eventsIn = Tools::eventCount(background.file(), this->recoSelectionStep());
    if(!eventsIn){
      std::cout<<"\tMissing is histogram containing no. of MC events for \"In\": "<<background.datasetName()<<"\n"
               <<"\t... ratioInOut calculation stopped\n";
      return;
    }
    const double nEventsIn(eventsIn->GetEntries());
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
    std::cout<<"Used no. of events (In, Out, [Out1, Out2]) for \""<<background.datasetName()<<"\": "
             <<nEventsIn<<" , "<<nEventsOut<<" , ["<<nEventsOut1<<" , "<<nEventsOut2<<"]\n";
    
    const double ratioInOut(!isnan(nEventsIn/nEventsOut) && !isinf(nEventsIn/nEventsOut) ? nEventsIn/nEventsOut : -1.);
    std::cout<<"Ratio In/Out for \""<<background.datasetName()<<"\": "
             <<ratioInOut<<"\n";
    
    if(background.datasetName()=="ttbar"){
      nInTtbar = nEventsIn;
      nOutTtbar = nEventsOut;
    }
    else if(background.datasetName()=="zmumuC"){
      nInZmumuC = nEventsIn;
      nOutZmumuC = nEventsOut;
    }
    else if(background.datasetName()=="zmumuUds"){
      nInZmumuUds = nEventsIn;
      nOutZmumuUds = nEventsOut;
    }
    else if(background.datasetName()=="zmumuUdsc"){
      nInZmumuUdsc = nEventsIn;
      nOutZmumuUdsc = nEventsOut;
    }
    else{
      nInOther = nEventsIn;
      nOutOther = nEventsOut;
    }
  }
  
  double nInZmumuB(0.);
  double nOutZmumuB(0.);
  {
    TH1* eventsIn(0);
    eventsIn = Tools::eventCount(zmumuB.file(), this->recoSelectionStep());
    if(!eventsIn){
      std::cout<<"\tMissing is histogram containing no. of MC events for \"In\": "<<zmumuB.datasetName()<<"\n"
               <<"\t... ratioInOut calculation stopped\n";
      return;
    }
    const double nEventsIn(eventsIn->GetEntries());
    TH1* eventsOut1(0);
    if(sideband==upper || sideband==both){
      TString pluginSuffix(this->recoSelectionStep());
      pluginSuffix.Insert(4,"ZVetoHigh");
      eventsOut1 = Tools::eventCount(zmumuB.file(), pluginSuffix);
      if(!eventsOut1){
        std::cout<<"\tMissing is histogram containing no. of MC events for \"Out1\": "<<zmumuB.datasetName()<<"\n"
                 <<"\t... ratioInOut calculation stopped\n";
        return;
      }
    }
    const double nEventsOut1(eventsOut1 ? eventsOut1->GetEntries() : 0.);
    TH1* eventsOut2(0);
    if(sideband==lower || sideband==both){
      TString pluginSuffix(this->recoSelectionStep());
      pluginSuffix.Insert(4,"ZVetoLow");
      eventsOut2 = Tools::eventCount(zmumuB.file(), pluginSuffix);
      if(!eventsOut2){
        std::cout<<"\tMissing is histogram containing no. of MC events for \"Out2\": "<<zmumuB.datasetName()<<"\n"
                 <<"\t... ratioInOut calculation stopped\n";
        return;
      }
    }
    const double nEventsOut2(eventsOut2 ? eventsOut2->GetEntries() : 0.);
    const double nEventsOut(nEventsOut1 + nEventsOut2);
    std::cout<<"Used no. of events (In, Out, [Out1, Out2]) for \""<<zmumuB.datasetName()<<"\": "
             <<nEventsIn<<" , "<<nEventsOut<<" , ["<<nEventsOut1<<" , "<<nEventsOut2<<"]\n";
    
    const double ratioInOut(!isnan(nEventsIn/nEventsOut) && !isinf(nEventsIn/nEventsOut) ? nEventsIn/nEventsOut : -1.);
    std::cout<<"Ratio In/Out for \""<<zmumuB.datasetName()<<"\": "
             <<ratioInOut<<"\n";
    
    nInZmumuB = nEventsIn;
    nOutZmumuB = nEventsOut;
  }
  
  nOtherIn_.setValue(nInOther);
  nOtherIn_.setAbsErr2Up(nInOther);
  nOtherIn_.setAbsErr2Dw(nInOther);
  nOtherOut_.setValue(nOutOther);
  nOtherOut_.setAbsErr2Up(nOutOther);
  nOtherOut_.setAbsErr2Dw(nOutOther);
  
  nTtbarInMc_ = nInTtbar;
  if(nInTtbar!=0 && nOutTtbar!=0){
    ratioInOutTtbar_.setValue(nInTtbar/nOutTtbar);
    ratioInOutTtbar_.setRelErr2StatUp(1./nInTtbar + 1./nOutTtbar);
    ratioInOutTtbar_.setRelErr2StatDw(1./nInTtbar + 1./nOutTtbar);
  }
  else{
    ratioInOutTtbar_ = ValueAndErrorStatSyst::dummyValues();
  }
  
  const double nInZmumu(nInZmumuB + nInZmumuC + nInZmumuUds + nInZmumuUdsc);
  nZmumuInMc_ = nInZmumu;
  const double nOutZmumu(nOutZmumuB + nOutZmumuC + nOutZmumuUds + nOutZmumuUdsc);
  if(nInZmumu!=0 && nOutZmumu!=0){
    ratioInOutZmumu_.setValue(nInZmumu/nOutZmumu);
    ratioInOutZmumu_.setRelErr2StatUp(1./nInZmumu + 1./nOutZmumu);
    ratioInOutZmumu_.setRelErr2StatDw(1./nInZmumu + 1./nOutZmumu);
  }
  else{
    ratioInOutZmumu_ = ValueAndErrorStatSyst::dummyValues();
  }
  
  std::cout<<"\n";
  std::cout<<"Number of events (In, Out) for ttbar: "<<this->nTtbarInMc()<<" , "<<nOutTtbar<<"\n";
  std::cout<<"Number of events (In, Out) for zmumu: "<<this->nZmumuInMc()<<" , "<<nOutZmumu<<"\n";
  std::cout<<"Number of events (In, Out) for other: "<<this->nOtherIn().value()<<" , "<<this->nOtherOut().value()<<"\n";
  
  std::cout<<"Ratio In/Out for ttbar: "<<this->ratioInOutTtbar().print()<<"\n";
  std::cout<<"Ratio In/Out for zmumu: "<<this->ratioInOutZmumu().print()<<"\n";
}





