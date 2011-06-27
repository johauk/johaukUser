#include "defaultSampleStruct.C"
#include "allSampleStruct.C"

#include "ZmumuAnalysis/Configuration/macros/Tools/printLine.h"



//void simulation(){
  PrintLine printLine;
  
  SimulationStruct simulationStruct("genParticle", 2329439);
  
  
void simulation(){ 
  allSampleStruct.simulationStruct = &simulationStruct;
}






