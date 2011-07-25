#include "ZmumuAnalysis/Configuration/macros/Calculations/FullAnalysis.h"



void FullAnalysis::setSimulationSample(){
  SimulationSample* sample(0);
  sample = new SimulationSample("genParticle", 36277961);
  
  if(sample->file()){
    simulationSample_ = sample;
  }
  else{
    simulationSample_ = 0;
    delete sample;
  }
}







