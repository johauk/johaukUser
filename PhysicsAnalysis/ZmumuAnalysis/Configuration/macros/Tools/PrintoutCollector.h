#ifndef PrintoutCollector_h
#define PrintoutCollector_h


#include <vector>


class PrintoutCollector{
  public:
    
    PrintoutCollector();
    ~PrintoutCollector();
    
    void printTable();
    void hline();
    
    
  private:
    
    std::vector<std::string> v_nObservedInOut_;
    std::vector<std::string> v_nSimulationInOut_;
    std::vector<std::string> v_ratioInOut_;
    std::vector<std::string> v_ttbarFraction_;
    std::vector<std::string> v_ttbarFractionErrContribution_;
    
};


#endif


