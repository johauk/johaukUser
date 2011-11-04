#ifndef PrintoutCollector_h
#define PrintoutCollector_h


#include <vector>
#include <map>


class PrintoutCollector{
  public:
    
    PrintoutCollector();
    ~PrintoutCollector();
    
    void printTable();
    void printSystematicTable();
    void hline();
    
    
  private:
    
    // For default analysis
    std::vector<std::string> v_nObservedInOut_;
    std::vector<std::string> v_nSimulationInOut_;
    std::vector<std::string> v_ratioInOut_;
    std::vector<std::string> v_ttbarFraction_;
    std::vector<std::string> v_ttbarFractionErrContribution_;
    
    // For systematic studies
    std::map<std::string, std::vector<std::string> > m_pileup_ratioInOutTtbar_;
    std::map<std::string, std::vector<std::string> > m_pileup_ratioInOutZmumu_;
    std::map<std::string, std::vector<std::string> > m_pileup_ttbarFraction_;
    
    
};


#endif


