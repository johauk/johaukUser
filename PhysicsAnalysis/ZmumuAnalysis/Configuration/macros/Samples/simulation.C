#include "defaultSampleStruct.C"
#include "allSampleStruct.h"



SimulationStruct simulationStruct("genParticle", 36277961);


void simulation(AllSampleStruct& allSample){ 
  if(simulationStruct.file_)allSample.simulationStruct_ = &simulationStruct;
}






