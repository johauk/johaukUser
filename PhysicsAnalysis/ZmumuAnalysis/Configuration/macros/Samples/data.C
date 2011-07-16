#include "defaultSampleStruct.C"
#include "allSampleStruct.h"



DataStruct dataStruct("allData", 24492880, 1092., 1092.*0.06, 1092.*0.06);


void data(AllSampleStruct& allSample){
  if(dataStruct.file_)allSample.dataStruct_ = &dataStruct;
}
