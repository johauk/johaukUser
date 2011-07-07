#ifndef AllSampleStruct_h
#define AllSampleStruct_h

#include <vector>

#include "defaultSampleStruct.h"


struct AllSampleStruct{
  AllSampleStruct():dataStruct_(0), signalStruct_(0), simulationStruct_(0){}
  
  ~AllSampleStruct(){
    /*
    //delete dataStruct_;
    //delete signalStruct_;
    //delete simulationStruct_;
    
    dataStruct_ = 0;
    signalStruct_ = 0;
    simulationStruct_ = 0;
    
    std::vector<McStruct*>::iterator i_background;
    for(i_background = v_backgroundStruct_.begin(); i_background != v_backgroundStruct_.end(); ++i_background){
      //delete *i_background;
      *i_background = 0;
    }
    
    v_backgroundStruct_.clear();
    */
  }
  
  DataStruct* dataStruct_;
  McStruct* signalStruct_;
  std::vector<McStruct*> v_backgroundStruct_;
  SimulationStruct* simulationStruct_;
};





#endif




