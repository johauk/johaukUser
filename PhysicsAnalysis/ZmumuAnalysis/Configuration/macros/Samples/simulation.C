#include "defaultSampleStruct.C"
#include "allSampleStruct.h"



SimulationStruct simulationStruct("genParticle", 2329439);


void simulation(AllSampleStruct& allSample){ 
  allSample.simulationStruct_ = &simulationStruct;
}






