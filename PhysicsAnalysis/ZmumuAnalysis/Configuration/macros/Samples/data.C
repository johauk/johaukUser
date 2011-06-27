#include "defaultSampleStruct.C"
#include "allSampleStruct.C"

#include "ZmumuAnalysis/Configuration/macros/Tools/printLine.h"



//void data(){
  PrintLine printLine;
  
  DataStruct dataStruct("allData.root", 1842615, 191.);
  
void data(){
  allSampleStruct.dataStruct = &dataStruct;
}
