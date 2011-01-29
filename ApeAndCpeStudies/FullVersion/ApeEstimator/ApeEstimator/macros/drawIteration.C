#include <iostream>
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



void drawIteration(unsigned int iLow = 0, unsigned int iHigh = 99999){
  
  // Set up style
  gROOT->SetStyle("Plain");
  gROOT->ForceStyle();
  double width = 600.;
  gStyle->SetCanvasDefW(width);
  gStyle->SetCanvasDefH(width);
  gStyle->SetTitleX(0.2);
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
  
  
  const TString* inpath = new TString("$CMSSW_BASE/src/ApeEstimator/ApeEstimator/hists/workingArea/iter11/");
  const TString* outpath = new TString(inpath->Copy().Append("plots/"));
  const TString* fileName = new TString(inpath->Copy().Append("allData_iterationApe.root"));
  
  delete inpath;
  
  std::stringstream sectorInterval;
  sectorInterval << iLow << "_" << iHigh;
  
  
  TFile* file(0);
  file = new TFile(*fileName, "READ");
  if(!file)std::cout<<"\n\tInput file not found, please check file name: "<<*fileName<<"\n";
  delete fileName;
  
  TTree* tree1(0);
  file->GetObject("iterTree", tree1);
  if(!tree1)std::cout<<"\n\tTTree with iteration values of APE not found in file!\n";
  
  
  unsigned int nSector(0);
  std::vector<TBranch*> v_branch;
  bool sectorBool(true);
  for(unsigned int iSector(1); sectorBool; ++iSector){
    std::stringstream sectorName, fullSectorName;
    sectorName << "Ape_Sector_" << iSector;
    TBranch* branch(0);
    branch = tree1->GetBranch(sectorName.str().c_str());
    //std::cout<<"\n\tHere we are: "<<sectorName.str().c_str()<<" "<<branch<<"\n";
    if(branch)v_branch.push_back(branch);
    else{
      sectorBool = false;
      nSector = iSector-1;
      std::cout<<"\n\tNumber of sectors for APE calculation contained in TTree: "<<nSector<<"\n";
    }
  }
  
  
  std::map<unsigned int, std::vector<double> > m_sectorValue;
  
  for(size_t iIter = 0; iIter < tree1->GetEntries(); ++iIter){
    unsigned int iSector(1);
    for(std::vector<TBranch*>::const_iterator i_branch = v_branch.begin(); i_branch != v_branch.end(); ++i_branch, ++iSector){
      double value(-999.);
      (*i_branch)->SetAddress(&value);
      (*i_branch)->GetEntry(iIter);
      m_sectorValue[iSector].push_back(value); 
    }
  }
  
  
  double minimumApe(999.), maximumApe(-999.);
  double maxAbsCorrection(-999.);
  
  std::vector<TGraph*> v_graphApe;
  std::vector<TGraph*> v_graphCorrection;
  
  for(std::map<unsigned int, std::vector<double> >::const_iterator i_sectorValue = m_sectorValue.begin(); i_sectorValue != m_sectorValue.end(); ++i_sectorValue){
    if((*i_sectorValue).first >= iLow && (*i_sectorValue).first<= iHigh){
      std::cout<<"\tFor Sector "<<(*i_sectorValue).first<<" final APE value is "<<std::sqrt(*(--((*i_sectorValue).second.end())))<<"\n";
      TGraph* graphApe(0);
      TGraph* graphCorrection(0);
      graphApe = new TGraph(tree1->GetEntries());
      graphCorrection = new TGraph(tree1->GetEntries());
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
	//std::cout<<"\n\tLets see: "<<iValue<<" "<<valueApe<<"\n";
	graphApe->SetPoint(iValue,static_cast<double>(iValue),valueApe);
	
	const double correction(valueApe - lastCorrection);
	//const double correction(correction2>0 ? std::sqrt(correction2) : -std::sqrt(-correction2));
	if(std::fabs(correction)>maxAbsCorrection)maxAbsCorrection = correction;
	graphCorrection->SetPoint(iValue,static_cast<double>(iValue),correction);
	// For next iteration subtract value of this one
	lastCorrection = valueApe;
      }
      if(unregardedSector)continue;
      v_graphApe.push_back(graphApe);
      v_graphCorrection.push_back(graphCorrection);
    }
  }
  
  
  TCanvas* canvas(0);
  canvas = new TCanvas("canvas");
  bool firstGraph(true);
  for(std::vector<TGraph*>::const_iterator i_graph = v_graphApe.begin(); i_graph != v_graphApe.end(); ++i_graph){
    TGraph* graph(*i_graph);
    graph->SetTitle("Absolute correction");
    graph->GetXaxis()->SetTitle("iteration");
    graph->GetYaxis()->SetTitle("#sigma_{APE,x}");
    if(firstGraph){
      graph->Draw("AL*");
      
      firstGraph = false;
    }
    else{
      graph->Draw("sameL*");
    }
    //graph->SetMinimum(-0.0001);
    graph->SetMinimum(minimumApe-0.0001);
    graph->SetMaximum(maximumApe*1.1);
  }
  
  canvas->Print(outpath->Copy().Append("ape").Append(sectorInterval.str()).Append(".eps"));
  canvas->Print(outpath->Copy().Append("ape").Append(sectorInterval.str()).Append(".png"));
  
  for(std::vector<TGraph*>::const_iterator i_graph = v_graphApe.begin(); i_graph != v_graphApe.end(); ++i_graph){
    (*i_graph)->Delete();
  }
  canvas->Close();
  
  
  
  
  firstGraph = true;
  canvas = new TCanvas("canvas");
  for(std::vector<TGraph*>::const_iterator i_graph = v_graphCorrection.begin(); i_graph != v_graphCorrection.end(); ++i_graph){
    TGraph* graph(*i_graph);
    graph->SetTitle("Relative correction");
    graph->GetXaxis()->SetTitle("iteration");
    graph->GetYaxis()->SetTitle("#Delta#sigma_{APE,x}");
    if(firstGraph){
      graph->Draw("AL*");
      
      firstGraph = false;
    }
    else{
      graph->Draw("sameL*");
    }
    graph->SetMinimum(-maxAbsCorrection*1.1);
    graph->SetMaximum(maxAbsCorrection*1.1);
  }
  canvas->Print(outpath->Copy().Append("correction").Append(sectorInterval.str()).Append(".eps"));
  canvas->Print(outpath->Copy().Append("correction").Append(sectorInterval.str()).Append(".png"));
  
  for(std::vector<TGraph*>::const_iterator i_graph = v_graphCorrection.begin(); i_graph != v_graphCorrection.end(); ++i_graph){
    (*i_graph)->Delete();
  }
  canvas->Close();
  
  
  delete outpath;
  tree1->Delete();
  file->Close();
}
