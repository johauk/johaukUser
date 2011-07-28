#include "ZmumuAnalysis/Configuration/macros/Tools/FullAnalysis.h"


#include "ZmumuAnalysis/Configuration/macros/Tools/eventCount.h"

#include <iostream>



void FullAnalysis::setEfficiency(){
  if(!this->signalSample() || !this->simulationSample()){
    std::cout<<"\tMissing input sample\n"
             <<"\t... take dummy efficiency\n";
    //efficiency_ = this->dummyEfficiency();
    efficiency_ = ValueAndErrorStatSyst::dummyValues();
    std::cout<<"Efficiency: "<<this->efficiency().print()<<"\n";
    return;
  }
  const McSample& zmumuB = *this->signalSample();
  const SimulationSample& simulation = *this->simulationSample();
  
  
  // First: get the number of reconstructed signal events
  TH1* eventsReco(0);
  eventsReco = eventCount(zmumuB.file(), this->recoSelectionStep());
  if(!eventsReco){
    std::cout<<"\tMissing is histogram containing no. of reconstructed signal events\n"
             <<"\t... efficiency calculation stopped\n";
    return;
  }
  const double nEventsReco(eventsReco->GetEntries());
  //const double nEffectiveEventsReco(nEventsReco/zmumuB.dynamicWeight());
  
  
  // Second: get the number of simulated signal events
  TH1* eventsSimu(0);
  eventsSimu = eventCount(simulation.file(), this->simuSelectionStep());
  if(!eventsSimu){
    std::cout<<"\tMissing is histogram containing no. of simulated signal events\n"
             <<"\t... efficiency calculation stopped\n";
    return;
  }
  double nEventsSimu(eventsSimu->GetEntries());
  const double nEffectiveEventsSimu(nEventsSimu/simulation.dynamicWeight()*zmumuB.dynamicWeight());
  
  
  // Finally: calculate efficiency
  ValueAndError nSelectedEvent;
  nSelectedEvent.setValue(nEventsReco);
  nSelectedEvent.setRelErr2Up((nEffectiveEventsSimu - nEventsReco)/(nEffectiveEventsSimu*nEventsReco));
  nSelectedEvent.setRelErr2Dw((nEffectiveEventsSimu - nEventsReco)/(nEffectiveEventsSimu*nEventsReco));
  
  efficiency_.setValue(nSelectedEvent.value()/nEffectiveEventsSimu);
  efficiency_.setRelErr2StatUp(nSelectedEvent.relErr2Up());
  efficiency_.setRelErr2StatDw(nSelectedEvent.relErr2Dw());
  
  std::cout<<"No. of simulated signal events: "<<nEventsSimu<<"\n";
  std::cout<<"Effective no. of simulated signal events: "<<nEffectiveEventsSimu<<"\n";
  std::cout<<"No. of reconstructed signal events: "<<nSelectedEvent.print()<<"\n";
  std::cout<<"Efficiency: "<<this->efficiency().print()<<"\n";
  
}










