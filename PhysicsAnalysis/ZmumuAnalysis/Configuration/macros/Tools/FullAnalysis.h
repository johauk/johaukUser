#ifndef FullAnalysis_h
#define FullAnalysis_h


#include <vector>

#include "ZmumuAnalysis/Configuration/macros/Samples/Sample.h"
#include "ZmumuAnalysis/Configuration/macros/Tools/ValueAndError.h"

#include "TString.h"



class FullAnalysis{
  public:
    
    FullAnalysis();
    ~FullAnalysis();
    
    void setRecoSelectionStep(TString step){recoSelectionStep_ = step;}
    void setSimuSelectionStep(TString step){simuSelectionStep_ = step;}
    
    void defaultAnalysis();
    
    enum Sideband{upper, lower, both};
    void ttbarFromSideband(const Sideband& =upper);
    
    void printTable();
    
    
  private:
    
    DataSample* dataSample()const{return dataSample_;}
    McSample* signalSample()const{return signalSample_;}
    std::vector<McSample*> backgroundSamples()const{return v_backgroundSample_;}
    SimulationSample* simulationSample()const{return simulationSample_;}
    
    void setDataSample();
    void setMcSamples();
    void setSimulationSample();
    
    DataSample* dataSample_;
    McSample* signalSample_;
    std::vector<McSample*> v_backgroundSample_;
    SimulationSample* simulationSample_;
    
    
    ValueAndErrorStatSyst efficiency()const{return efficiency_;}
    void setEfficiency();
    ValueAndErrorStatSyst efficiency_;
    
    
    ValueAndError luminosity()const{return luminosity_;}
    void setLuminosity();
    ValueAndError luminosity_;
    
    
    ValueAndError nObserved()const{return nObserved_;}
    void setNObserved();
    ValueAndError nObserved_;
    
    
    ValueAndError nBackground()const{return nBackground_;}
    ValueAndError nBackgroundZmumu()const{return nBackgroundZmumu_;}
    ValueAndError nBackgroundTtbar()const{return nBackgroundTtbar_;}
    ValueAndError nBackgroundOther()const{return nBackgroundOther_;}
    void setNBackground();
    ValueAndError nBackground_;
    ValueAndError nBackgroundZmumu_;
    ValueAndError nBackgroundTtbar_;
    ValueAndError nBackgroundOther_;
    
    
    ValueAndErrorStatSyst nSignal()const{return nSignal_;}
    void setNSignal();
    ValueAndErrorStatSyst nSignal_;
    
    
    ValueAndErrorStatSystLumi crossSection()const{return crossSection_;}
    void setCrossSection();
    ValueAndErrorStatSystLumi crossSection_;
    
    
    ValueAndErrorStatSyst crossSectionFromMc()const{return crossSectionFromMc_;}
    void setCrossSectionFromMc();
    ValueAndErrorStatSyst crossSectionFromMc_;
    
    
    TString recoSelectionStep()const{return recoSelectionStep_;}
    TString simuSelectionStep()const{return simuSelectionStep_;}
    
    TString recoSelectionStep_;
    TString simuSelectionStep_;
    
    
    
    
    ValueAndError ratioInOutZmumu()const{return ratioInOutZmumu_;}
    ValueAndError ratioInOutTtbar()const{return ratioInOutTtbar_;}
    ValueAndError nOtherIn()const{return nOtherIn_;}
    ValueAndError nOtherOut()const{return nOtherOut_;}
    double nZmumuInMc()const{return nZmumuInMc_;}
    double nTtbarInMc()const{return nTtbarInMc_;}
    double nZmumuOutMc()const{return nZmumuOutMc_;}
    double nTtbarOutMc()const{return nTtbarOutMc_;}
    void setRatioInOut(const Sideband&);
    ValueAndError ratioInOutZmumu_;
    ValueAndError ratioInOutTtbar_;
    ValueAndError nOtherIn_;
    ValueAndError nOtherOut_;
    double nZmumuInMc_;
    double nTtbarInMc_;
    double nZmumuOutMc_;
    double nTtbarOutMc_;
    
    
    ValueAndErrorStatSyst ratioInOutTtbarCorrected()const{return ratioInOutTtbarCorrected_;}
    void correctRatioInOutTtbar();
    ValueAndErrorStatSyst ratioInOutTtbarCorrected_;
    
    
    ValueAndErrorStatSyst ratioInOutZmumuCorrected()const{return ratioInOutZmumuCorrected_;}
    void correctRatioInOutZmumu();
    ValueAndErrorStatSyst ratioInOutZmumuCorrected_;
    
    
    ValueAndError nObservedSideband()const{return nObservedSideband_;}
    void setNObservedSideband(const Sideband&);
    ValueAndError nObservedSideband_;
    
    
    ValueAndError nBackgroundSideband()const{return nBackgroundSideband_;}
    ValueAndError nBackgroundZmumuSideband()const{return nBackgroundZmumuSideband_;}
    ValueAndError nBackgroundTtbarSideband()const{return nBackgroundTtbarSideband_;}
    ValueAndError nBackgroundOtherSideband()const{return nBackgroundOtherSideband_;}
    void setNBackgroundSideband(const Sideband&);
    ValueAndError nBackgroundSideband_;
    ValueAndError nBackgroundZmumuSideband_;
    ValueAndError nBackgroundTtbarSideband_;
    ValueAndError nBackgroundOtherSideband_;
    
    
    //ValueAndErrorStatSyst nSignalSideband()const{return nSignalSideband_;}
    //void setNSignal(const Sideband&);
    //ValueAndErrorStatSyst nSignalSideband_;
    
    
    ValueAndErrorStatSyst ttbarFraction()const{return ttbarFraction_;}
    double zmumuFraction()const{return zmumuFraction_;}
    void setTtbarFraction();
    ValueAndErrorStatSyst ttbarFraction_;
    double zmumuFraction_;
    
    
    void zTtbarFit(const bool =true);
    
    
    
    void fillTable();
    std::vector<std::string> v_nObservedInOut_;
    std::vector<std::string> v_nSimulationInOut_;
    std::vector<std::string> v_ratioInOut_;
    std::vector<std::string> v_ttbarFraction_;
    
};









#endif


