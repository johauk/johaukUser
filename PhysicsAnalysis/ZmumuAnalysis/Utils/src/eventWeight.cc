#include "ZmumuAnalysis/Utils/interface/eventWeight.h"

#include "DataFormats/Common/interface/Handle.h"



double Weights::eventWeight(const edm::Event& event, const edm::InputTag& source){
  if(event.isRealData())return 1.;
  edm::Handle<double> weight;
  if(source.label().empty())return 1.;
  event.getByLabel(source, weight);
  return *weight;
}
