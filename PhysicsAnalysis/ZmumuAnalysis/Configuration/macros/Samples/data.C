#include "defaultSampleStruct.C"
#include "allSampleStruct.h"



DataStruct dataStruct("allData", 1842615, 191.);


void data(AllSampleStruct& allSample){
  allSample.dataStruct_ = &dataStruct;
}
