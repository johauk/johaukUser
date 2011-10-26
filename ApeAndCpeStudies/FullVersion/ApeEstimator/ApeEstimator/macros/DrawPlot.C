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
outpath_(0), file_(0), fileZeroApe_(0), designFile_(0), baselineTreeX_(0), baselineTreeY_(0), delta0_(0),
legendEntry_("data (final APE)"), legendEntryZeroApe_("data (APE=0)"), designLegendEntry_("MCideal"),
legendXmin_(0.41), legendYmin_(0.27), legendXmax_(0.71), legendYmax_(0.42)
{
  std::stringstream ss_inpath, ss_inpathZeroApe;
  ss_inpath<<"$CMSSW_BASE/src/ApeEstimator/ApeEstimator/hists/workingArea/iter";
  ss_inpathZeroApe<<ss_inpath.str()<<"0/";
  ss_inpath<<iterationNumber<<"/";
  
  const TString* inpath = new TString(ss_inpath.str().c_str());
  const TString* inpathZeroApe = new TString(ss_inpathZeroApe.str().c_str());
  outpath_ = new TString(inpath->Copy().Append("plots/"));
  const TString rootFileName(summaryFile ? "allData_resultsFile.root" : "allData.root");
  const TString* fileName = new TString(inpath->Copy().Append(rootFileName));
  const TString* fileNameZeroApe = new TString(inpathZeroApe->Copy().Append(rootFileName));
  const TString* designFileName = new TString("$CMSSW_BASE/src/ApeEstimator/ApeEstimator/hists/Design/baseline/" + rootFileName);
  const TString* baselineFileName = new TString("$CMSSW_BASE/src/ApeEstimator/ApeEstimator/hists/Design/baseline/allData_baselineApe.root");
  
  std::cout<<"\n";
  std::cout<<"Outpath: "<<*outpath_<<"\n";
  std::cout<<"File name (final APE): "<<*fileName<<"\n";
  std::cout<<"File name (zero APE): "<<*fileNameZeroApe<<"\n";
  std::cout<<"Design file name: "<<*designFileName<<"\n";
  std::cout<<"Baseline file name: "<<*baselineFileName<<"\n";
  std::cout<<"\n";
  
  if(iterationNumber!=0)file_ = new TFile(*fileName, "READ");
  fileZeroApe_ = new TFile(*fileNameZeroApe, "READ");
  designFile_ = new TFile(*designFileName, "READ");
  TFile* baselineFile = new TFile(*baselineFileName, "READ");
  
  //if(!file_ || !fileZeroApe_ || !designFile_ || !baselineFile){
    // Not needed: root gives error by default when file is not found
    //std::cout<<"\n\tInput file not found, please check file name: "<<*fileName<<"\n";
  //}
  
  if(baselineFile){
    baselineFile->GetObject("iterTreeX", baselineTreeX_);
    baselineFile->GetObject("iterTreeY", baselineTreeY_);
  }
  
  if(!baselineTreeX_)std::cout<<"Baseline tree for x coordinate not found, cannot draw baselines!\n";
  if(!baselineTreeY_)std::cout<<"Baseline tree for y coordinate not found, cannot draw baselines!\n";
  
  delete inpath;
  delete fileName;
  delete fileNameZeroApe;
  delete designFileName;
  delete baselineFileName;
}



DrawPlot::~DrawPlot(){
  if(outpath_)delete outpath_;
  if(file_)file_->Close();
  if(fileZeroApe_)fileZeroApe_->Close();
  if(designFile_)designFile_->Close();
  if(baselineTreeX_)baselineTreeX_->Delete();
  if(baselineTreeY_)baselineTreeY_->Delete();
}



void
DrawPlot::setLegendEntry(const TString& legendEntry, const TString& legendEntryZeroApe, const TString& designLegendEntry){
  legendEntry_ = legendEntry;
  legendEntryZeroApe_ = legendEntryZeroApe;
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
DrawPlot::drawPlot(const TString& pluginName, const TString& histName, const bool normalise, const bool plotZeroApe){
  TString* plugin = new TString(pluginName.Copy());
  if(!plugin->IsNull())plugin->Append("/");
  for(unsigned int iSector=1; ; ++iSector){
    std::stringstream ss_sectorName, ss_sector;
    ss_sectorName<<"Sector_"<<iSector;
    ss_sector<<*plugin<<ss_sectorName.str()<<"/";
    TDirectory* dir(0);
    //std::cout<<"Sector: "<<ss_sector.str()<<"\n";
    dir = (TDirectory*)designFile_->TDirectory::GetDirectory(ss_sector.str().c_str());
    if(!dir)break;
    
    TH1* SectorName(0);
    designFile_->GetObject((ss_sector.str()+"z_name;1").c_str(), SectorName);
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
    
    if(histName=="h_entriesX" || histName=="h_entriesY" ||
       histName=="h_resX" || histName=="h_resY" ||
       histName=="h_NorResX" || histName=="h_NorResY")ss_sector<<"Results/";
    
    ss_sector<<histName;
    const TString fullName(ss_sector.str().c_str());
    this->printHist(fullName, histName.Copy().Append("_").Append(sectorName), normalise, plotZeroApe);
    
    if(delta0_)delete delta0_;
  }
}



void
DrawPlot::drawTrackPlot(const TString& pluginName, const TString& histName, const bool normalise, const bool plotZeroApe){
  TString* plugin = new TString(pluginName.Copy());
  if(!plugin->IsNull())plugin->Append("/");
  std::stringstream ss_sector;
  ss_sector<<*plugin<<"TrackVariables/"<<histName;
  const TString fullName(ss_sector.str().c_str());
  this->printHist(fullName, histName, normalise, plotZeroApe);
}



void
DrawPlot::drawEventPlot(const TString& pluginName, const TString& histName, const bool normalise, const bool plotZeroApe){
  TString* plugin = new TString(pluginName.Copy());
  if(!plugin->IsNull())plugin->Append("/");
  std::stringstream ss_sector;
  ss_sector<<*plugin<<"EventVariables/"<<histName;
  const TString fullName(ss_sector.str().c_str());
  this->printHist(fullName, histName, normalise, plotZeroApe);
}



void
DrawPlot::printHist(const TString& fullName, const TString& sectorName, const bool normalise, const bool plotZeroApe)const{
  TH1* hist(0);
  TH1* histZeroApe(0);
  TH1* designHist(0);
  if(file_)file_->GetObject(fullName + ";1", hist);
  if(fileZeroApe_)fileZeroApe_->GetObject(fullName + ";1", histZeroApe);
  designFile_->GetObject(fullName + ";1", designHist);
  if(hist && !plotZeroApe)histZeroApe = 0;
  if(!(hist || histZeroApe) || !designHist){std::cout<<"Histogram not found in file: "<<fullName<<"\n"; return;}
  else std::cout<<"Drawing histogram: "<<fullName<<"\n";
  
  std::vector<TH1*> v_hist;
  v_hist.push_back(designHist);
  if(histZeroApe)v_hist.push_back(histZeroApe);
  if(hist)v_hist.push_back(hist);
  
  if(normalise)this->scale(v_hist, 100.);
  
  const double maxY(this->maximumY(v_hist));
  //const double minY(this->minimumY(v_hist));
  this->setRangeUser(v_hist, 0., 1.1*maxY);
  
  this->setLineWidth(v_hist, 2);
  if(histZeroApe)histZeroApe->SetLineColor(2);
  if(histZeroApe)histZeroApe->SetLineStyle(2);
  if(hist)hist->SetLineColor(4);
  if(hist)hist->SetLineStyle(4);
  
  TCanvas* canvas = new TCanvas("canvas");
  canvas->cd();
  
  this->draw(v_hist);
  if(delta0_){
    const double xLow(designHist->GetXaxis()->GetXmin());
    const double xUp(designHist->GetXaxis()->GetXmax());
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
  TPaveStats* statsZeroApe(0);
  if(histZeroApe)statsZeroApe = (TPaveStats*)histZeroApe->GetListOfFunctions()->FindObject("stats");
  if(statsZeroApe){
    statsZeroApe->SetY1NDC(0.58);
    statsZeroApe->SetY2NDC(0.78);
    statsZeroApe->SetLineColor(2);
    statsZeroApe->SetTextColor(2);
  }
  TPaveStats* stats(0);
  if(hist)stats = (TPaveStats*)hist->GetListOfFunctions()->FindObject("stats");
  if(stats){
    stats->SetY1NDC(0.37);
    stats->SetY2NDC(0.57);
    stats->SetLineColor(4);
    stats->SetTextColor(4);
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
  if(histZeroApe)legend->AddEntry(histZeroApe, legendEntryZeroApe_, "l");
  if(hist)legend->AddEntry(hist, legendEntry_, "l");
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
  if(histZeroApe)histZeroApe->Delete();
  if(hist)hist->Delete();
}


void DrawPlot::scale(std::vector<TH1*>& v_hist, const double factor)const{
  for(std::vector<TH1*>::const_iterator i_hist = v_hist.begin();  i_hist != v_hist.end(); ++i_hist){
    TH1* hist(*i_hist);
    const double integral(hist->Integral(0,hist->GetNbinsX()+1));
    if(integral>0.)hist->Scale(factor/integral);
    hist->SetYTitle(TString(hist->GetYaxis()->GetTitle()) + "  (scaled)");
  }
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



