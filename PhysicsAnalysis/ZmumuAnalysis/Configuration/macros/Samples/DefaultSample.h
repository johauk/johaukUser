#ifndef DefaultSample_h
#define DefaultSample_h

#include "ZmumuAnalysis/Configuration/macros/Tools/ValueAndError.h"

#include "TColor.h"
#include "TFile.h"



class DefaultSample{
  public:
    
    DefaultSample():dynamicWeight_(-1.),nEventFullSample_(0), file_(0){};
    ~DefaultSample(){if(this->file())this->file()->Close();};
    
    TFile* file()const{return file_;}
    
  protected:
    
    static const std::string cmsswBase(){return getenv("CMSSW_BASE");}
    
    void openInputFile(const std::string&, const std::string&, const unsigned int);
    double dynamicWeight()const{return dynamicWeight_;}
    // The unweighted number of processed events
    ValueAndError nEvent()const{return nEvent_;}
    // The reweighted number of processed events (pile-up reweighting, b-tag-efficiency reweighting)
    ValueAndError nEventReweight()const{return nEventReweight_;}
    
  private:
    void setDynamicWeightAndNEvent(TFile*, const unsigned int);
    double dynamicWeight_;
    
    // Maximum number of events
    // If less are processed in data, luminosity is scaled down automatically,
    // If less are processed in MC/simulation, weight is scaled down automatically
    void setNEvent(const double, const double, const double);
    double nEventFullSample_;
    ValueAndError nEvent_;
    ValueAndError nEventReweight_;
    
    // Root file name only
    std::string datasetName()const{return datasetName_;}
    void setDatasetName(const std::string& name){datasetName_ = name;}
    std::string datasetName_;
    
    // The root file
    TFile* file_;
};








#endif



