#ifndef DrawPlot_h
#define DrawPlot_h



#include <vector>


#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"



class DrawPlot{
  public:
    DrawPlot(const unsigned int =0, const bool =true);
    ~DrawPlot();
    
    void setLegendEntry(const TString&, const TString&);
    void setLegendCoordinate(const double, const double, const double, const double);
    void drawPlot(const TString&, const TString&);
    
  private:
    void printHist(const TString&, const TString&)const;
    double maximumY(std::vector<TH1*>&)const;
    double minimumY(std::vector<TH1*>&)const;
    void setRangeUser(std::vector<TH1*>&, const double minY, const double maxY)const;
    void setLineWidth(std::vector<TH1*>&, const unsigned int)const;
    void draw(std::vector<TH1*>& v_hist)const;
    void cleanup(std::vector<TH1*>& v_hist)const;
    
    
    
    const TString* outpath_;
    // File with distributions for result iteration
    TFile* file_;
    // File with distributions for design geometry
    TFile* designFile_;
    // Only used when baseline should be drawn in residualWidth plot
    TTree* baselineTreeX_;
    TTree* baselineTreeY_;
    double* delta0_;
    
    // For setting legend in plots
    TString legendEntry_;
    TString designLegendEntry_;
    double legendXmin_;
    double legendYmin_;
    double legendXmax_;
    double legendYmax_;
};





#endif



