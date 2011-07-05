#include "defaultSampleStruct.C"
#include "allSampleStruct.C"



DataStruct dataStruct("allData", 1842615, 191.);


void data(){
  allSampleStruct.dataStruct = &dataStruct;
}
