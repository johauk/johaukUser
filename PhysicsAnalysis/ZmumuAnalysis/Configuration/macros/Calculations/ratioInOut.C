#include "ZmumuAnalysis/Configuration/macros/Tools/eventCount.h"

#include "ZmumuAnalysis/Configuration/macros/Samples/allSampleStruct.C"

#include <iostream>
#include <cmath>



double theNInMcTtbar(-1.);
double theNInMcZmumu(-1.);
double theNInMcOther(-1.);
double theNOutMcTtbar(-1.);
double theNOutMcZmumu(-1.);
double theNOutMcOther(-1.);

double theRatioInOutTtbar(-1.);
double theRatioInOutRelErr2UpTtbar(-1.);
double theRatioInOutRelErr2DwTtbar(-1.);
double theRatioInOutZmumu(-1.);
double theRatioInOutRelErr2UpZmumu(-1.);
double theRatioInOutRelErr2DwZmumu(-1.);



// Old version, leave for compatibility
double theRatioInOut(-1.);

void ratioInOut(TString pluginSuffixIn = "", TString pluginSuffixOut1 = "", TString pluginSuffixOut2 = ""){
  const std::vector<McStruct*> v_background = allSampleStruct.v_backgroundStruct_;
  
  double nInTtbar(0.);
  double nInZmumu(0.);
  double nInOther(0.);
  double nOutTtbar(0.);
  double nOutZmumu(0.);
  double nOutOther(0.);
  
  double ttbarRatioInOut(-1.);
  std::vector<McStruct*>::const_iterator i_background;
  for(i_background = v_background.begin(); i_background != v_background.end(); ++i_background){
    const McStruct& background = **i_background;

    TH1* eventsIn(0);
    eventsIn = eventCount(background.file_, pluginSuffixIn);
    if(!eventsIn){
      std::cout<<"\tMissing is histogram containing no. of MC events for \"In\": "<<background.datasetName_<<"\n"
               <<"\t... ratioInOut calculation stopped\n";
      return;
    }
    const double nEventsIn(eventsIn->GetEntries());
    
    TH1* eventsOut1(0);
    eventsOut1 = eventCount(background.file_, pluginSuffixOut1);
    if(!eventsOut1){
      std::cout<<"\tMissing is histogram containing no. of MC events for \"Out1\": "<<background.datasetName_<<"\n"
               <<"\t... ratioInOut calculation stopped\n";
      return;
    }
    const double nEventsOut1(eventsOut1->GetEntries());
    
    TH1* eventsOut2(0);
    if(pluginSuffixOut2 != ""){
      eventsOut2 = eventCount(background.file_, pluginSuffixOut2);
      if(!eventsOut2){
        std::cout<<"\tMissing is histogram containing no. of MC events for \"Out2\": "<<background.datasetName_<<"\n"
                 <<"\t... ratioInOut calculation stopped\n";
        return;
      }
    }
    const double nEventsOut2(eventsOut2 ? eventsOut2->GetEntries() : 0.);
    const double nEventsOut(nEventsOut1 + nEventsOut2);
    
    const double ratioInOut(!isnan(nEventsIn/nEventsOut) && !isinf(nEventsIn/nEventsOut) ? nEventsIn/nEventsOut : -1.);
    
    std::cout<<"Used no. of events (In, Out1, Out2) for \""<<background.datasetName_<<"\": "
             <<nEventsIn<<" , "<<nEventsOut1<<" , "<<nEventsOut2<<"\n";
    std::cout<<"Ratio In/Out for \""<<background.datasetName_<<"\": "
             <<ratioInOut<<"\n";
    
    if(background.datasetName_=="ttbar"){
      nInTtbar = nEventsIn;
      nOutTtbar = nEventsOut;
      ttbarRatioInOut = ratioInOut;
    }
    else if(background.datasetName_=="zmumuUdsc"){
      nInZmumu = nEventsIn;
      nOutZmumu = nEventsOut;
    }
    else{
      nInOther = nEventsIn;
      nOutOther = nEventsOut;
    }
  }
  
  {
    const McStruct& zmumuB = *allSampleStruct.signalStruct_;
    TH1* eventsIn(0);
    eventsIn = eventCount(zmumuB.file_, pluginSuffixIn);
    if(!eventsIn){
      std::cout<<"\tMissing is histogram containing no. of MC events for \"In\": "<<zmumuB.datasetName_<<"\n"
               <<"\t... ratioInOut calculation stopped\n";
      return;
    }
    const double nEventsIn(eventsIn->GetEntries());
    
    TH1* eventsOut1(0);
    eventsOut1 = eventCount(zmumuB.file_, pluginSuffixOut1);
    if(!eventsOut1){
      std::cout<<"\tMissing is histogram containing no. of MC events for \"Out1\": "<<zmumuB.datasetName_<<"\n"
               <<"\t... ratioInOut calculation stopped\n";
      return;
    }
    const double nEventsOut1(eventsOut1->GetEntries());
    
    TH1* eventsOut2(0);
    if(pluginSuffixOut2 != ""){
      eventsOut2 = eventCount(zmumuB.file_, pluginSuffixOut2);
      if(!eventsOut2){
        std::cout<<"\tMissing is histogram containing no. of MC events for \"Out2\": "<<zmumuB.datasetName_<<"\n"
                 <<"\t... ratioInOut calculation stopped\n";
        return;
      }
    }
    const double nEventsOut2(eventsOut2 ? eventsOut2->GetEntries() : 0.);
    const double nEventsOut(nEventsOut1 + nEventsOut2);
    
    const double ratioInOut(!isnan(nEventsIn/nEventsOut) && !isinf(nEventsIn/nEventsOut) ? nEventsIn/nEventsOut : -1.);
    
    std::cout<<"Used no. of events (In, Out1, Out2) for \""<<zmumuB.datasetName_<<"\": "
             <<nEventsIn<<" , "<<nEventsOut1<<" , "<<nEventsOut2<<"\n";
    std::cout<<"Ratio In/Out for \""<<zmumuB.datasetName_<<"\": "
             <<ratioInOut<<"\n";
  
    nInZmumu += nEventsIn;
    nOutZmumu += nEventsOut;
  }
  
  
  theRatioInOut = ttbarRatioInOut;
  std::cout<<"Ratio of ttbar for background estimation: "<<theRatioInOut<<"\n";
  
  theNInMcTtbar = nInTtbar;
  theNInMcZmumu = nInZmumu;
  theNInMcOther = nInOther;
  theNOutMcTtbar = nOutTtbar;
  theNOutMcZmumu = nOutZmumu;
  theNOutMcOther = nOutOther;
  
  const double nInRelErr2Ttbar(1./nInTtbar);
  const double nOutRelErr2Ttbar(1./nOutTtbar);
  const double nInRelErr2Zmumu(1./nInZmumu);
  const double nOutRelErr2Zmumu(1./nOutZmumu);
  
  theRatioInOutTtbar = nInTtbar/nOutTtbar;
  theRatioInOutRelErr2UpTtbar = nInRelErr2Ttbar + nOutRelErr2Ttbar;
  theRatioInOutRelErr2DwTtbar = nInRelErr2Ttbar + nOutRelErr2Ttbar;
  
  theRatioInOutZmumu = nInZmumu/nOutZmumu;
  theRatioInOutRelErr2UpZmumu = nInRelErr2Zmumu + nOutRelErr2Zmumu;
  theRatioInOutRelErr2DwZmumu = nInRelErr2Zmumu + nOutRelErr2Zmumu;
  
  std::cout<<"\n";
  std::cout<<"Number of events (In, Out) for ttbar: "<<theNInMcTtbar<<" , "<<theNOutMcTtbar<<"\n";
  std::cout<<"Number of events (In, Out) for zmumu: "<<theNInMcZmumu<<" , "<<theNOutMcZmumu<<"\n";
  std::cout<<"Number of events (In, Out) for other: "<<theNInMcOther<<" , "<<theNOutMcOther<<"\n";
  
  const double ratioInOutAbsErrUpTtbar = theRatioInOutTtbar*std::sqrt(theRatioInOutRelErr2UpTtbar);
  const double ratioInOutAbsErrDwTtbar = theRatioInOutTtbar*std::sqrt(theRatioInOutRelErr2DwTtbar);
  const double ratioInOutAbsErrUpZmumu = theRatioInOutZmumu*std::sqrt(theRatioInOutRelErr2UpZmumu);
  const double ratioInOutAbsErrDwZmumu = theRatioInOutZmumu*std::sqrt(theRatioInOutRelErr2DwZmumu);
  
  std::cout<<"Ratio In/Out for ttbar: "<<theRatioInOutTtbar<<" + "<<ratioInOutAbsErrUpTtbar<<" - "<<ratioInOutAbsErrDwTtbar<<"\n";
  std::cout<<"Ratio In/Out for zmumu: "<<theRatioInOutZmumu<<" + "<<ratioInOutAbsErrUpZmumu<<" - "<<ratioInOutAbsErrDwZmumu<<"\n";
}




