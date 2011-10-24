#include "DrawIteration.h"


#include <iostream>
#include <iomanip>
#include <sstream>

#include <cmath>

#include "TTree.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TH1F.h"

#include "TROOT.h"
#include "TStyle.h"
#include "TGaxis.h"





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
  this->printFinalValues(iSectorLow, iSectorHigh);
  
  // Clean up
  this->clear();
}



void DrawIteration::drawResult(){
  // Set up style
  //this->setStyle();
  
  // Extract values stored in tree and put them into member data maps
  this->getSectorValues();
  
  // Collect sectors to be shown in same plot in correct order
  this->arrangeHists();
  
  // Final plots
  this->drawFinals("x");
  this->drawFinals("y");
  
  // Clean up
  this->clear();
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
    std::cout<<"Wrong parameter for drawCorrections(...)\n";
  }
  
  if(v_graphApe->size()==0 || v_graphCorrection->size()==0)return;
  
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
  v_graphApe->clear();
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
  v_graphCorrection->clear();
  canvas->Close();
}



void DrawIteration::printFinalValues(unsigned int iSectorLow, unsigned int iSectorHigh){
  for(std::map<unsigned int, std::string*>::const_iterator i_sectorValue = m_sectorName_.begin(); i_sectorValue != m_sectorName_.end(); ++i_sectorValue){
    const unsigned int iSector(i_sectorValue->first);
    if(iSector>=iSectorLow && iSector<=iSectorHigh){
      const std::string* name(i_sectorValue->second);
      const double apeX = std::sqrt(*(--(m_sectorValueX_[iSector].end())));
      double apeY(-9.);
      if(m_sectorValueY_.count(iSector)!=0)apeY = std::sqrt(*(--(m_sectorValueY_[iSector].end())));
      
      std::cout<<"Sector no., APE x, APE y, name:\t"<<iSector<<"\t, "<<std::fixed<<std::setprecision(5)<<apeX<<" , "<<apeY<<" , "<<*name<<"\n";
    }
  }
}



void DrawIteration::clear(){
  m_sectorName_.clear();
  m_sectorValueX_.clear();
  m_sectorValueY_.clear();
  
  v_graphApeX_.clear();
  v_graphCorrectionX_.clear();
  v_graphApeY_.clear();
  v_graphCorrectionY_.clear();
  
  v_resultHist_.clear();
}



void DrawIteration::arrangeHists(){
  v_resultHist_.push_back(this->pixelHist());
  //v_resultHist_.push_back(this->barrelHist());
  v_resultHist_.push_back(this->tibHist());
  v_resultHist_.push_back(this->tobHist());
  //v_resultHist_.push_back(this->endcapHist());
  v_resultHist_.push_back(this->tidHist());
  v_resultHist_.push_back(this->tecHist());
}



std::vector<std::string> DrawIteration::pixelHist(){
  std::vector<std::string> v_name;
  
  v_name.push_back("BpixLayer1Out");
  v_name.push_back("BpixLayer1In");
  v_name.push_back("BpixLayer2Out");
  v_name.push_back("BpixLayer2In");
  v_name.push_back("BpixLayer3Out");
  v_name.push_back("BpixLayer3In");
  
  v_name.push_back("FpixMinusLayer1");
  v_name.push_back("FpixMinusLayer2");
  v_name.push_back("FpixPlusLayer1");
  v_name.push_back("FpixPlusLayer2");
  
  return v_name;
}



std::vector<std::string> DrawIteration::barrelHist(){
  std::vector<std::string> v_name;
  
  v_name.push_back("TibLayer1RphiOut");
  v_name.push_back("TibLayer1RphiIn");
  v_name.push_back("TibLayer1StereoOut");
  v_name.push_back("TibLayer1StereoIn");
  v_name.push_back("TibLayer2RphiOut");
  v_name.push_back("TibLayer2RphiIn");
  v_name.push_back("TibLayer2StereoOut");
  v_name.push_back("TibLayer2StereoIn");
  v_name.push_back("TibLayer3Out");
  v_name.push_back("TibLayer3In");
  v_name.push_back("TibLayer4Out");
  v_name.push_back("TibLayer4In");
  
  v_name.push_back("TobLayer1StereoOut");
  v_name.push_back("TobLayer1RphiIn");
  v_name.push_back("TobLayer2RphiOut");
  v_name.push_back("TobLayer2StereoIn");
  v_name.push_back("TobLayer3Out");
  v_name.push_back("TobLayer3In");
  v_name.push_back("TobLayer4Out");
  v_name.push_back("TobLayer4In");
  v_name.push_back("TobLayer5Out");
  v_name.push_back("TobLayer5In");
  v_name.push_back("TobLayer6Out");
  v_name.push_back("TobLayer6In");
  
  return v_name;
}



std::vector<std::string> DrawIteration::tibHist(){
  std::vector<std::string> v_name;
  
  v_name.push_back("TibLayer1RphiOut");
  v_name.push_back("TibLayer1RphiIn");
  v_name.push_back("TibLayer1StereoOut");
  v_name.push_back("TibLayer1StereoIn");
  v_name.push_back("TibLayer2RphiOut");
  v_name.push_back("TibLayer2RphiIn");
  v_name.push_back("TibLayer2StereoOut");
  v_name.push_back("TibLayer2StereoIn");
  v_name.push_back("TibLayer3Out");
  v_name.push_back("TibLayer3In");
  v_name.push_back("TibLayer4Out");
  v_name.push_back("TibLayer4In");
  
  return v_name;
}



std::vector<std::string> DrawIteration::tobHist(){
  std::vector<std::string> v_name;
  
  v_name.push_back("TobLayer1StereoOut");
  v_name.push_back("TobLayer1RphiIn");
  v_name.push_back("TobLayer2RphiOut");
  v_name.push_back("TobLayer2StereoIn");
  v_name.push_back("TobLayer3Out");
  v_name.push_back("TobLayer3In");
  v_name.push_back("TobLayer4Out");
  v_name.push_back("TobLayer4In");
  v_name.push_back("TobLayer5Out");
  v_name.push_back("TobLayer5In");
  v_name.push_back("TobLayer6Out");
  v_name.push_back("TobLayer6In");
  
  return v_name;
}



std::vector<std::string> DrawIteration::endcapHist(){
  std::vector<std::string> v_name;
  
  v_name.push_back("TidMinusRing1Rphi");
  v_name.push_back("TidMinusRing1Stereo");
  v_name.push_back("TidMinusRing2Rphi");
  v_name.push_back("TidMinusRing2Stereo");
  v_name.push_back("TidMinusRing3");
  
  v_name.push_back("TidPlusRing1Rphi");
  v_name.push_back("TidPlusRing1Stereo");
  v_name.push_back("TidPlusRing2Rphi");
  v_name.push_back("TidPlusRing2Stereo");
  v_name.push_back("TidPlusRing3");
  
  v_name.push_back("TecMinusRing1Rphi");
  v_name.push_back("TecMinusRing1Stereo");
  v_name.push_back("TecMinusRing2Rphi");
  v_name.push_back("TecMinusRing2Stereo");
  v_name.push_back("TecMinusRing3");
  v_name.push_back("TecMinusRing4");
  v_name.push_back("TecMinusRing5Rphi");
  v_name.push_back("TecMinusRing5Stereo");
  v_name.push_back("TecMinusRing6");
  v_name.push_back("TecMinusRing7");
  
  v_name.push_back("TecPlusRing1Rphi");
  v_name.push_back("TecPlusRing1Stereo");
  v_name.push_back("TecPlusRing2Rphi");
  v_name.push_back("TecPlusRing2Stereo");
  v_name.push_back("TecPlusRing3");
  v_name.push_back("TecPlusRing4");
  v_name.push_back("TecPlusRing5Rphi");
  v_name.push_back("TecPlusRing5Stereo");
  v_name.push_back("TecPlusRing6");
  v_name.push_back("TecPlusRing7");
  
  return v_name;
}



std::vector<std::string> DrawIteration::tidHist(){
  std::vector<std::string> v_name;
  
  v_name.push_back("TidMinusRing1Rphi");
  v_name.push_back("TidMinusRing1Stereo");
  v_name.push_back("TidMinusRing2Rphi");
  v_name.push_back("TidMinusRing2Stereo");
  v_name.push_back("TidMinusRing3");
  
  v_name.push_back("TidPlusRing1Rphi");
  v_name.push_back("TidPlusRing1Stereo");
  v_name.push_back("TidPlusRing2Rphi");
  v_name.push_back("TidPlusRing2Stereo");
  v_name.push_back("TidPlusRing3");
  
  return v_name;
}



std::vector<std::string> DrawIteration::tecHist(){
  std::vector<std::string> v_name;
  
  v_name.push_back("TecMinusRing1Rphi");
  v_name.push_back("TecMinusRing1Stereo");
  v_name.push_back("TecMinusRing2Rphi");
  v_name.push_back("TecMinusRing2Stereo");
  v_name.push_back("TecMinusRing3");
  v_name.push_back("TecMinusRing4");
  v_name.push_back("TecMinusRing5Rphi");
  v_name.push_back("TecMinusRing5Stereo");
  v_name.push_back("TecMinusRing6");
  v_name.push_back("TecMinusRing7");
  
  v_name.push_back("TecPlusRing1Rphi");
  v_name.push_back("TecPlusRing1Stereo");
  v_name.push_back("TecPlusRing2Rphi");
  v_name.push_back("TecPlusRing2Stereo");
  v_name.push_back("TecPlusRing3");
  v_name.push_back("TecPlusRing4");
  v_name.push_back("TecPlusRing5Rphi");
  v_name.push_back("TecPlusRing5Stereo");
  v_name.push_back("TecPlusRing6");
  v_name.push_back("TecPlusRing7");
  
  return v_name;
}



TString DrawIteration::associateLabel(const std::string& sectorName){
  const TString name(sectorName.c_str());
  TString nameHelp("");
  
  TString subdet, subdetLabel;
  if(name.BeginsWith("Bpix")){subdet="Bpix"; subdetLabel="BPIX";}
  else if(name.BeginsWith("Fpix")){subdet="Fpix"; subdetLabel="FPIX";}
  else if(name.BeginsWith("Tib")){subdet="Tib"; subdetLabel="TIB";}
  else if(name.BeginsWith("Tid")){subdet="Tid"; subdetLabel="TID";}
  else if(name.BeginsWith("Tob")){subdet="Tob"; subdetLabel="TOB";}
  else if(name.BeginsWith("Tec")){subdet="Tec"; subdetLabel="TEC";}
  else return "ERROR: no label found";
  nameHelp += subdet;
  
  TString side, sideLabel;
  if(name.BeginsWith(nameHelp+"Minus")){side="Minus"; sideLabel="m";}
  else if(name.BeginsWith(nameHelp+"Plus")){side="Plus"; sideLabel="p";}
  else {side=""; sideLabel="";}
  nameHelp += side;
  
  TString layer, layerLabel;
  if(name.BeginsWith(nameHelp+"Layer")){layer="Layer"; layerLabel=" L";}
  else if(name.BeginsWith(nameHelp+"Ring")){layer="Ring"; layerLabel=" R";}
  else return "ERROR: no label found";
  nameHelp += layer;
  
  TString layerNo, layerNoLabel;
  for(unsigned int iLayer=1; iLayer<=7; ++iLayer){
    std::stringstream ss_layer;
    ss_layer<<iLayer;
    if(name.BeginsWith(nameHelp+ss_layer.str())){;
      layerNo=ss_layer.str(); layerNoLabel=ss_layer.str();
      break;
    }
  }
  nameHelp += layerNo;
  
  TString sublayer, sublayerLabel;
  if(name.BeginsWith(nameHelp+"Rphi")){sublayer="Rphi"; sublayerLabel="R";}
  else if(name.BeginsWith(nameHelp+"Stereo")){sublayer="Stereo"; sublayerLabel="S";}
  else {sublayer=""; sublayerLabel="";}
  nameHelp += sublayer;
  
  TString orientation, orientationLabel;
  if(name.BeginsWith(nameHelp+"Out")){orientation="Out"; orientationLabel="o";}
  else if(name.BeginsWith(nameHelp+"In")){orientation="In"; orientationLabel="i";}
  else {orientation=""; orientationLabel="";}
  nameHelp += orientation;
  
  const TString label(subdetLabel+sideLabel+layerLabel+layerNoLabel+sublayerLabel+orientationLabel);
  return label;
}



unsigned int DrawIteration::sectorNumber(const std::string& name){
  unsigned int sectorNo(0);
  std::map<unsigned int, std::string*>::const_iterator i_sector;
  for(i_sector=m_sectorName_.begin(); i_sector!=m_sectorName_.end(); ++i_sector){
    if(*(i_sector->second)==name){
      sectorNo=i_sector->first;
      break;
    }
  }
  return sectorNo;
}



void DrawIteration::drawFinals(const std::string& xOrY){
  std::map<unsigned int, std::vector<double> >* m_sectorValue(0);
  if(xOrY=="x"){
    m_sectorValue = &m_sectorValueX_;
  }
  else if(xOrY=="y"){
    m_sectorValue = &m_sectorValueY_;
  }
  else{
    std::cout<<"Wrong parameter for drawFinals(...)\n";
  }
  
  unsigned int iHist(1);
  std::vector<std::vector<std::string> >::const_iterator i_resultHist;
  for(i_resultHist=v_resultHist_.begin(); i_resultHist!=v_resultHist_.end(); ++i_resultHist, ++iHist){
    //std::cout<<"New histogram\n";
    TCanvas* canvas(0);
    canvas = new TCanvas("canvas");
    TH1* hist(0);
    const TString title("Results;;#sigma_{APE,"+xOrY+"}  [#mum]");
    hist = new TH1F("hist",title,i_resultHist->size(),0,i_resultHist->size());
    
    unsigned int iBin(1);
    bool hasEntry(false);
    std::vector<std::string>::const_iterator i_name;
    for(i_name=i_resultHist->begin(); i_name!=i_resultHist->end(); ++i_name, ++iBin){
      const TString& label = this->associateLabel(*i_name);
      const unsigned int iSector = this->sectorNumber(*i_name);
      double ape(-9.);
      if(m_sectorValue->count(iSector)!=0){
        ape = 10000.*std::sqrt(*(--((*m_sectorValue)[iSector].end())));
	hasEntry = true;
      }
      hist->SetBinContent(iBin, ape);
      hist->SetBinError(iBin, 0.0000001);
      hist->GetXaxis()->SetBinLabel(iBin, label);
      hist->SetAxisRange(0.,30.,"Y");
    }
    
    if(hasEntry){
      //gStyle->SetErrorX(0.5);
      hist->Draw("e0");
      std::stringstream ss_hist;
      ss_hist<<"_"<<iHist;
      canvas->Print(outpath_->Copy().Append("result_").Append(xOrY).Append(ss_hist.str()).Append(".eps"));
      canvas->Print(outpath_->Copy().Append("result_").Append(xOrY).Append(ss_hist.str()).Append(".png"));
    }
    
    hist->Delete();
    canvas->Close();
  }
  
}













