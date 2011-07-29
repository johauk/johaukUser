#include <iostream>
#include <iomanip>
#include <sstream>

#include <vector>
#include <map>

#include <cmath>

#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"

#include "TROOT.h"
#include "TStyle.h"
#include "TGaxis.h"



class DrawIteration{
  public:
    DrawIteration(unsigned int =0);
    ~DrawIteration();
    
    void drawIteration(unsigned int =0, unsigned int =99999);
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
    
    const TString* outpath_;
    TFile* file_;
    
    std::map<unsigned int, std::string*> m_sectorName_;
    std::map<unsigned int, std::vector<double> > m_sectorValueX_;
    std::map<unsigned int, std::vector<double> > m_sectorValueY_;
    
    std::vector<TGraph*> v_graphApeX_;
    std::vector<TGraph*> v_graphCorrectionX_;
    std::vector<TGraph*> v_graphApeY_;
    std::vector<TGraph*> v_graphCorrectionY_;
    
};



DrawIteration::DrawIteration(unsigned int iterationNumber):
outpath_(0), file_(0)
{
  std::stringstream ss_inpath;
  ss_inpath<<"$CMSSW_BASE/src/ApeEstimator/ApeEstimator/hists/workingArea/iter"<<iterationNumber<<"/";
  const TString* inpath = new TString(ss_inpath.str().c_str());
  outpath_ = new TString(inpath->Copy().Append("plots/"));
  const TString* fileName = new TString(inpath->Copy().Append("allData_iterationApe.root"));
  delete inpath;
  
  std::cout<<"Outpath: "<<*outpath_<<"\n";
  std::cout<<"File name: "<<*fileName<<"\n";
  
  file_ = new TFile(*fileName, "READ");
  if(!file_){
    // Not needed: root gives error by default when file is not found
    std::cout<<"\n\tInput file not found, please check file name: "<<*fileName<<"\n";
  }
  delete fileName;
  
}



DrawIteration::~DrawIteration(){
  if(file_)file_->Close();
  if(outpath_)delete outpath_;
}



void DrawIteration::drawIteration(unsigned int iSectorLow, unsigned int iSectorHigh){
  // Set up style
  this->setStyle();
  
  // Extract values stored in tree and put them into member data maps
  this->getSectorValues();
  
  
  // Now create the final graphs, and get their extreme values
  ExtremeValues extremeValuesX(this->getGraphs("x", iSectorLow, iSectorHigh));
  ExtremeValues extremeValuesY(this->getGraphs("y", iSectorLow, iSectorHigh));
  
  // Draw them
  std::stringstream ss_sectorInterval;
  ss_sectorInterval<< "_" << iSectorLow << "_" << iSectorHigh;
  this->drawCorrections("x", extremeValuesX, ss_sectorInterval.str());
  this->drawCorrections("y", extremeValuesY, ss_sectorInterval.str());
  
  // Finally, print out final values
  for(std::map<unsigned int, std::string*>::const_iterator i_sectorValue = m_sectorName_.begin(); i_sectorValue != m_sectorName_.end(); ++i_sectorValue){
    const unsigned int iSector(i_sectorValue->first);
    if(iSector>=iSectorLow && iSector<=iSectorHigh){
      const std::string* name(i_sectorValue->second);
      const double apeX = std::sqrt(*(--(m_sectorValueX_[iSector].end())));
      double apeY(-99.);
      if(m_sectorValueX_.count(iSector)!=0)apeY = std::sqrt(*(--(m_sectorValueY_[iSector].end())));
      
      std::cout<<"Sector no., APE x, APE y, name:\t"<<iSector<<"\t, "<<std::fixed<<std::setprecision(5)<<apeX<<" , "<<apeY<<" , "<<*name<<"\n";
  
    }
  }
  
}



void DrawIteration::setStyle(){
  gROOT->SetStyle("Plain");
  gROOT->ForceStyle();
  double width = 600.;
  gStyle->SetCanvasDefW(width);
  gStyle->SetCanvasDefH(width);
  gStyle->SetTitleX(0.25);
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetPadRightMargin(0.08);
  gStyle->SetPadTopMargin(0.08);
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetHistLineWidth(2);
  //gStyle->SetTitleOffset(1.2,"X");
  gStyle->SetTitleOffset(1.1,"Y");
  gStyle->SetTitleXSize(0.05);
  gStyle->SetTitleYSize(0.05);
  gStyle->SetTitleSize(0.05,"XY");
  //gStyle->SetLabelSize(0.05,"XY");
  TGaxis::SetMaxDigits(3);
}



void DrawIteration::getSectorValues(){
  // Trees containing the iterative APE values and the sector names
  TTree* nameTree(0);
  file_->GetObject("nameTree", nameTree);
  if(!nameTree)std::cout<<"\n\tTTree with names of sectors not found in file!\n";
  TTree* treeX(0);
  file_->GetObject("iterTreeX", treeX);
  if(!treeX)std::cout<<"\n\tTTree with iteration x values of APE not found in file!\n";
  TTree* treeY(0);
  file_->GetObject("iterTreeY", treeY);
  if(!treeY)std::cout<<"\n\tTTree with iteration y values of APE not found in file!\n";
  
  unsigned int nSector(0);
  std::map<unsigned int, TBranch*> m_branchName;
  std::map<unsigned int, TBranch*> m_branchX;
  std::map<unsigned int, TBranch*> m_branchY;
  bool sectorBool(true);
  for(unsigned int iSector(1); sectorBool; ++iSector){
    std::stringstream sectorName, fullSectorName;
    sectorName << "Ape_Sector_" << iSector;
    TBranch* branchName(0);
    branchName = nameTree->GetBranch(sectorName.str().c_str());
    TBranch* branchX(0);
    branchX = treeX->GetBranch(sectorName.str().c_str());
    TBranch* branchY(0);
    branchY = treeY->GetBranch(sectorName.str().c_str());
    //std::cout<<"\n\tHere we are: "<<sectorName.str().c_str()<<" "<<branchX<<"\n";
    
    if(branchName)m_branchName[iSector] = branchName;
    else{
      sectorBool = false;
      nSector = iSector-1;
      std::cout<<"\n\tNumber of sectors for APE calculation contained in TTree: "<<nSector<<"\n";
    }
    if(branchX)m_branchX[iSector] = branchX;
    if(branchY)m_branchY[iSector] = branchY;
  }
  
  for(std::map<unsigned int, TBranch*>::const_iterator i_branch = m_branchName.begin(); i_branch != m_branchName.end(); ++i_branch){
    std::string* value(0);
    i_branch->second->SetAddress(&value);
    i_branch->second->GetEntry(0);
    m_sectorName_[i_branch->first] = value; 
  }
  const unsigned int nIter(treeX->GetEntries());
  for(unsigned int iIter = 0; iIter < nIter; ++iIter){
    for(std::map<unsigned int, TBranch*>::const_iterator i_branch = m_branchX.begin(); i_branch != m_branchX.end(); ++i_branch){
      double value(-999.);
      (i_branch->second)->SetAddress(&value);
      (i_branch->second)->GetEntry(iIter);
      m_sectorValueX_[i_branch->first].push_back(value); 
    }
    for(std::map<unsigned int, TBranch*>::const_iterator i_branch = m_branchY.begin(); i_branch != m_branchY.end(); ++i_branch){
      double value(-999.);
      (i_branch->second)->SetAddress(&value);
      (i_branch->second)->GetEntry(iIter);
      m_sectorValueY_[i_branch->first].push_back(value); 
    }
  }
  
  nameTree->Delete();
  treeX->Delete();
  treeY->Delete();
}



DrawIteration::ExtremeValues DrawIteration::getGraphs(const std::string xOrY, unsigned int iSectorLow, unsigned int iSectorHigh){
  double minimumApe(999.), maximumApe(-999.);
  double maxAbsCorrection(-999.);
  
  std::map<unsigned int, std::vector<double> >* m_sectorValue(0);
  std::vector<TGraph*>* v_graphApe(0);
  std::vector<TGraph*>* v_graphCorrection(0);
  
  if(xOrY=="x"){
    m_sectorValue = &m_sectorValueX_;
    v_graphApe = &v_graphApeX_;
    v_graphCorrection = &v_graphCorrectionX_;
  }
  else if(xOrY=="y"){
    m_sectorValue = &m_sectorValueY_;
    v_graphApe = &v_graphApeY_;
    v_graphCorrection = &v_graphCorrectionY_;
  }
  else{
    std::cout<<"Wrong parameter for getGraphs(...)\n";
  }
  
  for(std::map<unsigned int, std::vector<double> >::const_iterator i_sectorValue = m_sectorValue->begin(); i_sectorValue != m_sectorValue->end(); ++i_sectorValue){
    if((*i_sectorValue).first >= iSectorLow && (*i_sectorValue).first<= iSectorHigh){
      TGraph* graphApe(0);
      TGraph* graphCorrection(0);
      graphApe = new TGraph(m_sectorValueX_[1].size());
      graphCorrection = new TGraph(m_sectorValueX_[1].size());
      double lastCorrection(0.);
      bool unregardedSector(false);
      int iValue(0);
      for(std::vector<double>::const_iterator i_value = (*i_sectorValue).second.begin(); i_value != (*i_sectorValue).second.end(); ++i_value, ++iValue){
        const double valueApe(std::sqrt(*i_value));
	// Prevent method for non-analyzed sectors with default value sqrt(99.)
	if(valueApe>9.){
	  unregardedSector = true;
	  break;
	}
	if(valueApe<minimumApe)minimumApe = valueApe;
	if(valueApe>maximumApe)maximumApe = valueApe;
	graphApe->SetPoint(iValue,static_cast<double>(iValue),valueApe);
	
	const double correction(valueApe - lastCorrection);
	//const double correction(correction2>0 ? std::sqrt(correction2) : -std::sqrt(-correction2));
	if(std::fabs(correction)>maxAbsCorrection)maxAbsCorrection = correction;
	graphCorrection->SetPoint(iValue,static_cast<double>(iValue),correction);
	// For next iteration subtract value of this one
	lastCorrection = valueApe;
      }
      if(unregardedSector)continue;
      (*v_graphApe).push_back(graphApe);
      (*v_graphCorrection).push_back(graphCorrection);
    }
  }
  
  return ExtremeValues(minimumApe, maximumApe, maxAbsCorrection);
}



void DrawIteration::drawCorrections(const std::string& xOrY, const ExtremeValues& extremeValues, const std::string& sectorInterval){
  
  std::vector<TGraph*>* v_graphApe(0);
  std::vector<TGraph*>* v_graphCorrection(0);
  if(xOrY=="x"){
    v_graphApe = &v_graphApeX_;
    v_graphCorrection = &v_graphCorrectionX_;
  }
  else if(xOrY=="y"){
    v_graphApe = &v_graphApeY_;
    v_graphCorrection = &v_graphCorrectionY_;
  }
  else{
    std::cout<<"Wrong parameter for getGraphs(...)\n";
  }
  
  TCanvas* canvas(0);
  canvas = new TCanvas("canvas");
  bool firstGraph(true);
  for(std::vector<TGraph*>::const_iterator i_graph = v_graphApe->begin(); i_graph != v_graphApe->end(); ++i_graph){
    const TString yAxisTitle("#sigma_{APE," + xOrY + "}  [cm]");
    TGraph* graph(*i_graph);
    graph->SetTitle("Absolute correction");
    graph->GetXaxis()->SetTitle("iteration");
    graph->GetYaxis()->SetTitle(yAxisTitle);
    if(firstGraph){
      graph->Draw("AL*");
      
      firstGraph = false;
    }
    else{
      graph->Draw("sameL*");
    }
    //graph->SetMinimum(-0.0001);
    graph->SetMinimum(extremeValues.minimumApe-0.0001);
    graph->SetMaximum(extremeValues.maximumApe*1.1);
  }
  
  canvas->Print(outpath_->Copy().Append("ape_").Append(xOrY).Append(sectorInterval).Append(".eps"));
  canvas->Print(outpath_->Copy().Append("ape_").Append(xOrY).Append(sectorInterval).Append(".png"));
  
  for(std::vector<TGraph*>::const_iterator i_graph = v_graphApe->begin(); i_graph != v_graphApe->end(); ++i_graph){
    (*i_graph)->Delete();
  }
  canvas->Close();
  
  firstGraph = true;
  canvas = new TCanvas("canvas");
  for(std::vector<TGraph*>::const_iterator i_graph = v_graphCorrection->begin(); i_graph != v_graphCorrection->end(); ++i_graph){
    const TString yAxisTitle("#Delta#sigma_{APE," + xOrY + "}  [cm]");
    TGraph* graph(*i_graph);
    graph->SetTitle("Relative correction");
    graph->GetXaxis()->SetTitle("iteration");
    graph->GetYaxis()->SetTitle(yAxisTitle);
    if(firstGraph){
      graph->Draw("AL*");
      
      firstGraph = false;
    }
    else{
      graph->Draw("sameL*");
    }
    graph->SetMinimum(-extremeValues.maxAbsCorrection*1.1);
    graph->SetMaximum(extremeValues.maxAbsCorrection*1.1);
  }
  canvas->Print(outpath_->Copy().Append("correction_").Append(xOrY).Append(sectorInterval).Append(".eps"));
  canvas->Print(outpath_->Copy().Append("correction_").Append(xOrY).Append(sectorInterval).Append(".png"));
  
  for(std::vector<TGraph*>::const_iterator i_graph = v_graphCorrection->begin(); i_graph != v_graphCorrection->end(); ++i_graph){
    (*i_graph)->Delete();
  }
  canvas->Close();
}







