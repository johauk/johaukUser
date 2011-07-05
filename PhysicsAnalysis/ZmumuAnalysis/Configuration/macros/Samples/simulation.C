#include "defaultSampleStruct.C"
#include "allSampleStruct.C"



SimulationStruct simulationStruct("genParticle", 2329439);


void simulation(){ 
  allSampleStruct.simulationStruct = &simulationStruct;
}






