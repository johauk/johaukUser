#ifndef FullAnalysis_h
#define FullAnalysis_h


#include <vector>

#include "ZmumuAnalysis/Configuration/macros/Samples/Sample.h"
#include "ZmumuAnalysis/Configuration/macros/Tools/ValueAndError.h"
#include "ZmumuAnalysis/Configuration/macros/Tools/PrintoutCollector.h"

#include "TString.h"



class FullAnalysis{
  public:
    
    FullAnalysis(PrintoutCollector&, const std::string& ="");
    ~FullAnalysis();
    
    void setRecoSelectionStep(TString step){recoSelectionStep_ = step;}
    void setSimuSelectionStep(TString step){simuSelectionStep_ = step;}
    
    void defaultAnalysis();
    
    enum Sideband{upper, lower, both};
    void ttbarFromSideband(const Sideband& =upper);
    void eeAnalysisTtbarFromSideband(const std::string&);
    
    
    
  private:
    
    const std::string inputFolder()const{return inputFolder_;}
    const std::string inputFolder_;
    
    
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
    
    
    
    ValueAndError nOtherIn()const{return nOtherIn_;}
    ValueAndError nOtherOut()const{return nOtherOut_;}
    double nZmumuInMc()const{return nZmumuInMc_;}
    double nTtbarInMc()const{return nTtbarInMc_;}
    double nZmumuOutMc()const{return nZmumuOutMc_;}
    double nTtbarOutMc()const{return nTtbarOutMc_;}
    void nInOutMc(const Sideband&);
    ValueAndError nOtherIn_;
    ValueAndError nOtherOut_;
    double nZmumuInMc_;
    double nTtbarInMc_;
    double nZmumuOutMc_;
    double nTtbarOutMc_;
    
    
    
    ValueAndError ratioInOutZmumu()const{return ratioInOutZmumu_;}
    ValueAndError ratioInOutTtbar()const{return ratioInOutTtbar_;}
    void setRatioInOut();
    ValueAndError ratioInOutZmumu_;
    ValueAndError ratioInOutTtbar_;
    
    
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
    
    
    ValueAndErrorStatSyst ttbarEstimate()const{return ttbarEstimate_;}
    ValueAndErrorStatSyst ttbarFraction()const{return ttbarFraction_;}
    double zmumuFraction()const{return zmumuFraction_;}
    double ttbarEstimateSideband()const{return ttbarEstimateSideband_;}
    double ttbarFractionSideband()const{return ttbarFractionSideband_;}
    double zmumuFractionSideband()const{return zmumuFractionSideband_;}
    double ttbarFractionRelErrFromNObs()const{return ttbarFractionRelErrFromNObs_;}
    double ttbarFractionRelErrFromNObsSideband()const{return ttbarFractionRelErrFromNObsSideband_;}
    double ttbarFractionRelErrFromRatioTtbarStat()const{return ttbarFractionRelErrFromRatioTtbarStat_;}
    double ttbarFractionRelErrFromRatioZmumuStat()const{return ttbarFractionRelErrFromRatioZmumuStat_;}
    double ttbarFractionRelErrFromRatioTtbarSyst()const{return ttbarFractionRelErrFromRatioTtbarSyst_;}
    double ttbarFractionRelErrFromRatioZmumuSyst()const{return ttbarFractionRelErrFromRatioZmumuSyst_;}
    void setTtbarFraction();
    ValueAndErrorStatSyst ttbarEstimate_;
    ValueAndErrorStatSyst ttbarFraction_;
    double zmumuFraction_;
    double ttbarEstimateSideband_;
    double ttbarFractionSideband_;
    double zmumuFractionSideband_;
    double ttbarFractionRelErrFromNObs_;
    double ttbarFractionRelErrFromNObsSideband_;
    double ttbarFractionRelErrFromRatioTtbarStat_;
    double ttbarFractionRelErrFromRatioZmumuStat_;
    double ttbarFractionRelErrFromRatioTtbarSyst_;
    double ttbarFractionRelErrFromRatioZmumuSyst_;
    
    
    void zTtbarFit(const bool =true);
    
    
    void fillTable();
    void fillSystematicTable();
    std::string assignLabel()const;
    PrintoutCollector& printoutCollector_;
    
    
    void eeInput(const std::string&);
    
};









#endif


