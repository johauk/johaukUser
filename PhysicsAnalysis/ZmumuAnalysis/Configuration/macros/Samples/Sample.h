#ifndef Sample_h
#define Sample_h


#include "DefaultSample.h"
#include "ZmumuAnalysis/Configuration/macros/Tools/ValueAndError.h"

#include "TColor.h"
#include "TFile.h"




// For real data
class DataSample : public DefaultSample {
  public:
    
    DataSample(const std::string dataset, const unsigned int nEvents, const std::string& inputFolder)
    {this->openInputFile(dataset, this->defaultPath(inputFolder), nEvents);}
    
    ~DataSample(){}
    
    ValueAndError effectiveLuminosity()const;
    
  private:
    
    // Full path of dataset
    static const std::string defaultPath(const std::string& inputFolder){
      if(inputFolder=="")return cmsswBase() + "/src/ZmumuAnalysis/Configuration/hists/data/";
      else return cmsswBase() + "/src/ZmumuAnalysis/Configuration/analysis/data/" + inputFolder + "/data/";
    }
    
    // Luminosity corresponding to the maximum number of events in [pb-1]
    ValueAndError luminosity()const{return luminosity_;}
    ValueAndError luminosity_;
};




// For simulated samples on reco level
class McSample : public DefaultSample {
  public:
    
    McSample(const std::string dataset, const unsigned int nEvents, TColor* col, const std::string& inputFolder):
      filterEfficiency_(1.), color_(col)
      {this->openInputFile(dataset, this->defaultPath(inputFolder), nEvents);}
    
    ~McSample(){if(this->color())this->color()->Delete();}
    
    ValueAndErrorStatSystLumi effectiveWeight(const ValueAndError&)const;
    TColor* color()const{return color_;}
    
  private:
    
    void setFilterEfficiency(const double filterEff){filterEfficiency_ = filterEff;}
    
    ValueAndError correspondingLuminosity()const;
    ValueAndErrorStatSystLumi weight(const ValueAndError&)const;
    
    // Full path of dataset
    static const std::string defaultPath(const std::string& inputFolder){
      if(inputFolder=="")return cmsswBase() + "/src/ZmumuAnalysis/Configuration/hists/mc/";
      else return cmsswBase() + "/src/ZmumuAnalysis/Configuration/analysis/data/" + inputFolder + "/mc/";
    }
    
    // Assign cross section for normalisation to data lumi
    ValueAndError crossSection()const{return crossSection_;}
    ValueAndError crossSection_;
    
    // If given cross section does not correspond exactly to the process, since a filter on generator level is applied
    double filterEfficiency()const{return filterEfficiency_;}
    double filterEfficiency_;
    
    // Set the colour used for the the sample in the plots
    TColor* color_;
};




// For generator level studies
struct SimulationSample : public DefaultSample {
  public:
    
    SimulationSample(const std::string dataset, const unsigned int nEvents)
    {this->openInputFile(dataset, this->defaultPath(), nEvents);}
    
    ~SimulationSample(){}
    
  private:
    
    // Full path of dataset
    static const std::string defaultPath(){return cmsswBase() + "/src/ZmumuAnalysis/Configuration/hists/simulation/";}
};



#endif



