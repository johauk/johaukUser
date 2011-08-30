#include "DrawPlot.h"


#include <iostream>
#include <sstream>

#include <cmath>

#include "TDirectory.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TBranch.h"
#include "TPaveStats.h"
#include "TLegend.h"





DrawPlot::DrawPlot(const unsigned int iterationNumber, const bool summaryFile):
outpath_(0), file_(0), designFile_(0), baselineTreeX_(0), baselineTreeY_(0), delta0_(0),
legendEntry_("data"),  designLegendEntry_("MCideal"),
legendXmin_(0.41), legendYmin_(0.27), legendXmax_(0.71), legendYmax_(0.42)
{
  std::stringstream ss_inpath;
  ss_inpath<<"$CMSSW_BASE/src/ApeEstimator/ApeEstimator/hists/workingArea/iter"<<iterationNumber<<"/";
  const TString* inpath = new TString(ss_inpath.str().c_str());
  outpath_ = new TString(inpath->Copy().Append("plots/"));
  const TString rootFileName(summaryFile ? "allData_resultsFile.root" : "allData.root");
  const TString* fileName = new TString(inpath->Copy().Append(rootFileName));
  const TString* designFileName = new TString("$CMSSW_BASE/src/ApeEstimator/ApeEstimator/hists/Design/baseline/" + rootFileName);
  const TString* baselineFileName = new TString("$CMSSW_BASE/src/ApeEstimator/ApeEstimator/hists/Design/baseline/allData_baselineApe.root");
  
  std::cout<<"Outpath: "<<*outpath_<<"\n";
  std::cout<<"File name: "<<*fileName<<"\n";
  std::cout<<"Design file name: "<<*designFileName<<"\n";
  std::cout<<"Baseline file name: "<<*baselineFileName<<"\n";
  
  file_ = new TFile(*fileName, "READ");
  designFile_ = new TFile(*designFileName, "READ");
  TFile* baselineFile = new TFile(*baselineFileName, "READ");
  if(!file_ || !designFile_ || !baselineFile){
    // Not needed: root gives error by default when file is not found
    std::cout<<"\n\tInput file not found, please check file name: "<<*fileName<<"\n";
  }
  
  if(baselineFile){
    baselineFile->GetObject("iterTreeX", baselineTreeX_);
    baselineFile->GetObject("iterTreeY", baselineTreeY_);
  }
  
  if(!baselineTreeX_)std::cout<<"Baseline tree for x coordinate not found, cannot draw baselines!\n";
  if(!baselineTreeY_)std::cout<<"Baseline tree for y coordinate not found, cannot draw baselines!\n";
  
  delete inpath;
  delete fileName;
  delete designFileName;
  delete baselineFileName;
}



DrawPlot::~DrawPlot(){
  if(outpath_)delete outpath_;
  if(file_)file_->Close();
  if(designFile_)designFile_->Close();
  if(baselineTreeX_)baselineTreeX_->Delete();
  if(baselineTreeY_)baselineTreeY_->Delete();
}



void
DrawPlot::setLegendEntry(const TString& legendEntry, const TString& designLegendEntry){
  legendEntry_ = legendEntry;
  designLegendEntry_ = designLegendEntry;
}
void
DrawPlot::setLegendCoordinate(const double legendXmin, const double legendYmin, const double legendXmax, const double legendYmax){
  legendXmin_ = legendXmin;
  legendYmin_ = legendYmin;
  legendXmax_ = legendXmax;
  legendYmax_ = legendYmax;
}



void
DrawPlot::drawPlot(const TString& pluginName, const TString& histName){
  TString* plugin = new TString(pluginName.Copy());
  if(!plugin->IsNull())plugin->Append("/");
  for(unsigned int iSector=1; ; ++iSector){
    std::stringstream ss_sectorName, ss_sector;
    ss_sectorName<<"Sector_"<<iSector;
    ss_sector<<*plugin<<ss_sectorName.str()<<"/";
    TDirectory* dir(0);
    //std::cout<<"Sector: "<<ss_sector.str()<<"\n";
    dir = (TDirectory*)file_->TDirectory::GetDirectory(ss_sector.str().c_str());
    if(!dir)break;
    
    TH1* SectorName(0);
    file_->GetObject((ss_sector.str()+"z_name;1").c_str(), SectorName);
    const TString sectorName(SectorName ? SectorName->GetTitle() : ss_sectorName.str().c_str());
    
    
    TTree* baselineTree(0);
    if(histName=="h_residualWidthX1"){baselineTree = baselineTreeX_;}
    else if(histName=="h_residualWidthY1"){baselineTree = baselineTreeY_;}
    if(baselineTree){
      std::stringstream ss_branch;
      ss_branch<<"Ape_Sector_"<<iSector;
      TBranch* branch(0);
      branch = baselineTree->GetBranch(ss_branch.str().c_str());
      if(branch){
	double delta0(999.);
	branch->SetAddress(&delta0);
        branch->GetEntry(0);
        delta0_ = new double(std::sqrt(delta0));
      }
      else delta0_ = 0;
    }
    else delta0_ = 0;
    
    if(histName=="h_entriesX" || histName=="h_entriesY")ss_sector<<"Results/";
    
    ss_sector<<histName;
    const TString fullName(ss_sector.str().c_str());
    this->printHist(fullName, histName.Copy().Append("_").Append(sectorName));
    
    if(delta0_)delete delta0_;
  }
}



void
DrawPlot::drawTrackPlot(const TString& pluginName, const TString& histName){
  TString* plugin = new TString(pluginName.Copy());
  if(!plugin->IsNull())plugin->Append("/");
  std::stringstream ss_sector;
  ss_sector<<*plugin<<"TrackVariables/"<<histName;
  const TString fullName(ss_sector.str().c_str());
  this->printHist(fullName, histName);
}



void
DrawPlot::drawEventPlot(const TString& pluginName, const TString& histName){
  TString* plugin = new TString(pluginName.Copy());
  if(!plugin->IsNull())plugin->Append("/");
  std::stringstream ss_sector;
  ss_sector<<*plugin<<"EventVariables/"<<histName;
  const TString fullName(ss_sector.str().c_str());
  this->printHist(fullName, histName);
}



void
DrawPlot::printHist(const TString& fullName, const TString& sectorName)const{
  TH1* hist(0);
  TH1* designHist(0);
  file_->GetObject(fullName + ";1", hist);
  designFile_->GetObject(fullName + ";1", designHist);
  if(!hist || !designHist){std::cout<<"Histogram not found in file: "<<fullName<<"\n"; return;}
  else std::cout<<"Drawing histogram: "<<fullName<<"\n";
  
  std::vector<TH1*> v_hist;
  v_hist.push_back(designHist);
  v_hist.push_back(hist);
  
  const double maxY(this->maximumY(v_hist));
  //const double minY(this->minimumY(v_hist));
  this->setRangeUser(v_hist, 0., 1.1*maxY);
  
  this->setLineWidth(v_hist, 2);
  hist->SetLineColor(2);
  hist->SetLineStyle(2);
  
  TCanvas* canvas = new TCanvas("canvas");
  canvas->cd();
  
  this->draw(v_hist);
  if(delta0_){
    const double xLow(hist->GetXaxis()->GetXmin());
    const double xUp(hist->GetXaxis()->GetXmax());
    TLine* baseline(0);
    baseline = new TLine(xLow,*delta0_,xUp,*delta0_);
    baseline->SetLineStyle(2);
    baseline->SetLineWidth(2);
    //baseline = new TLine(0.0005,*delta0_,0.01,*delta0_); baseline->Draw("same");
    baseline->DrawLine(xLow,*delta0_,xUp,*delta0_);
    delete baseline;
  }
  canvas->Modified();
  canvas->Update();
  
  //TPaveStats* stats =(TPaveStats*) hist->GetListOfFunctions()->At(1);
  TPaveStats* stats(0);
  stats = (TPaveStats*)hist->GetListOfFunctions()->FindObject("stats");
  if(stats){
    stats->SetY1NDC(0.58);
    stats->SetY2NDC(0.78);
    stats->SetLineColor(2);
    stats->SetTextColor(2);
  }
  canvas->Modified();
  canvas->Update();
  
  TLegend* legend(0);
  legend = new TLegend(legendXmin_, legendYmin_, legendXmax_, legendYmax_);
  legend->SetFillColor(0);
  legend->SetFillStyle(0);
  legend->SetTextSize(0.04);
  legend->SetMargin(0.12);
  legend->SetFillStyle(1001);
  //legend->SetBorderSize(0);
  legend->AddEntry(designHist, designLegendEntry_, "l");
  legend->AddEntry(hist, legendEntry_, "l");
  legend->Draw("same");
  
  canvas->Modified();
  canvas->Update();
  
  const TString plotName(outpath_->Copy().Append(sectorName));
  canvas->Print(plotName + ".eps");
  canvas->Print(plotName + ".png");
  
  if(legend)legend->Delete();
  if(stats)stats->Delete();
  if(canvas)canvas->Close();
  this->cleanup(v_hist);
  if(designHist)designHist->Delete();
  if(hist)hist->Delete();
}


double DrawPlot::maximumY(std::vector<TH1*>& v_hist)const{
  double maxY(-999.);
  for(std::vector<TH1*>::const_iterator i_hist = v_hist.begin();  i_hist != v_hist.end(); ++i_hist){
    const TH1* hist(*i_hist);
    const double histY(hist->GetMaximum());
    if(i_hist==v_hist.begin())maxY = histY;
    else if(maxY<histY)maxY = histY;
  }
  return maxY;
}


double DrawPlot::minimumY(std::vector<TH1*>& v_hist)const{
  double minY(-999.);
  for(std::vector<TH1*>::const_iterator i_hist = v_hist.begin();  i_hist != v_hist.end(); ++i_hist){
    const TH1* hist(*i_hist);
    const double histY(hist->GetMinimum());
    if(i_hist==v_hist.begin())minY = histY;
    else if(minY<histY)minY = histY;
  }
  return minY;
}


void DrawPlot::setRangeUser(std::vector<TH1*>& v_hist, const double minY, const double maxY)const{
  for(std::vector<TH1*>::const_iterator i_hist = v_hist.begin();  i_hist != v_hist.end(); ++i_hist){
    TH1* hist(*i_hist);
    hist->GetYaxis()->SetRangeUser(minY, maxY);
  }
}


void DrawPlot::setLineWidth(std::vector<TH1*>& v_hist, const unsigned int width)const{
  for(std::vector<TH1*>::const_iterator i_hist = v_hist.begin();  i_hist != v_hist.end(); ++i_hist){
    TH1* hist(*i_hist);
    hist->SetLineWidth(width);
  }
}


void DrawPlot::draw(std::vector<TH1*>& v_hist)const{
  for(std::vector<TH1*>::const_iterator i_hist = v_hist.begin();  i_hist != v_hist.end(); ++i_hist){
    TH1* hist(*i_hist);
    if(i_hist==v_hist.begin())hist->Draw();
    else hist->Draw("sameS");
  }
}


void DrawPlot::cleanup(std::vector<TH1*>& v_hist)const{
  for(std::vector<TH1*>::iterator i_hist = v_hist.begin();  i_hist != v_hist.end(); ++i_hist){
    TH1* hist(*i_hist);
    hist = 0;
  }
  v_hist.clear();
}



