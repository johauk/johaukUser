#ifndef DrawIteration_h
#define DrawIteration_h



#include <vector>
#include <map>

#include "TString.h"
#include "TFile.h"
#include "TGraph.h"



class DrawIteration{
  public:
    DrawIteration(unsigned int =0);
    ~DrawIteration();
    
    void drawIteration(unsigned int =0, unsigned int =99999);
    void drawResult();
  private:
    struct ExtremeValues{
      ExtremeValues(const double minApe, const double maxApe, const double maxAbsCorr):
      minimumApe(minApe), maximumApe(maxApe), maxAbsCorrection(maxAbsCorr){}
      const double minimumApe;
      const double maximumApe;
      const double maxAbsCorrection;
    };
    
    void setStyle();
    void getSectorValues();
    ExtremeValues getGraphs(const std::string, unsigned int, unsigned int);
    void drawCorrections(const std::string&, const ExtremeValues&, const std::string&);
    void printFinalValues(unsigned int, unsigned int);
    void clear();
    
    void arrangeHists();
    std::vector<std::string> pixelHist();
    std::vector<std::string> barrelHist();
    std::vector<std::string> tibHist();
    std::vector<std::string> tobHist();
    std::vector<std::string> endcapHist();
    std::vector<std::string> tidHist();
    std::vector<std::string> tecHist();
    TString associateLabel(const std::string&);
    unsigned int sectorNumber(const std::string&);
    void drawFinals(const std::string&);
    
    const TString* outpath_;
    TFile* file_;
    
    std::map<unsigned int, std::string*> m_sectorName_;
    std::map<unsigned int, std::vector<double> > m_sectorValueX_;
    std::map<unsigned int, std::vector<double> > m_sectorValueY_;
    
    std::vector<TGraph*> v_graphApeX_;
    std::vector<TGraph*> v_graphCorrectionX_;
    std::vector<TGraph*> v_graphApeY_;
    std::vector<TGraph*> v_graphCorrectionY_;
    
    std::vector<std::vector<std::string> > v_resultHist_;
};





#endif




