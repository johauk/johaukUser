#ifndef AllSampleStruct_h
#define AllSampleStruct_h



#include "defaultSampleStruct.h"


struct AllSampleStruct{
  AllSampleStruct():dataStruct(0), signalStruct(0), simulationStruct(0){}
  
  DataStruct* dataStruct;
  McStruct* signalStruct;
  std::vector<McStruct*> v_backgroundStruct;
  SimulationStruct* simulationStruct;
};





#endif




