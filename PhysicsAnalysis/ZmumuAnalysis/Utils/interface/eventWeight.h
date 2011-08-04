#ifndef EventWeight_h
#define EventWeight_h


#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/InputTag.h"



namespace Weights{
  double eventWeight(const edm::Event& event, const edm::InputTag& source);
}



#endif








