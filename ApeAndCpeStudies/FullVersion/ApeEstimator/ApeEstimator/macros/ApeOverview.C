// Usage:
// .L ApeOverview.C++
// ApeOverview a1("test.root");
// a1.getOverview()
// a1.printOverview() resp. a1.printOverview("apeOverview.ps",ApeOverview::event)


#include "ApeOverview.h"

#include <sstream>    //for stringstream
#include <iostream>   //for cout

#include "TProfile.h"
#include "TPostScript.h"
#include "TLatex.h"


ApeOverview::ApeOverview(const TString inputFileName):
inputFile_(TFile::Open(inputFileName)), moduleNo_(1), onlyZoomedHists_(false), firstSelectedSector_("")
{
  eventPadCounter_.first = eventPadCounter_.second = trackPadCounter_.first = trackPadCounter_.second = sectorCounter_ = 1;
}

ApeOverview::~ApeOverview(){}



void
ApeOverview::whichModuleInFile(int moduleNo){
  moduleNo_ = moduleNo;
}



void
ApeOverview::onlyZoomedHists(){
  onlyZoomedHists_ = true;
}



void
ApeOverview::setSectorsForOverview(const TString sectors){
  //std::vector<>
  TObjArray* aSector = TString(sectors).Tokenize(",");
  for(Int_t iSec= 0; iSec < aSector->GetEntriesFast(); ++iSec){
    
    TString sector = aSector->At(iSec)->GetName();
    bool validSectorArgument(false);
    for(unsigned int i = 0; i<20000 ; ++i){
      std::stringstream ssSec;
      ssSec << i;
      if(ssSec.str().c_str() == sector){
        vSelectedSector_.push_back(i);
	std::cout<<"\n\tPrint overview for Sector:\t"<<sector<<"\n";
	validSectorArgument = true;
	break;
      }
    }
    if(!validSectorArgument)std::cout<<"\n\tWrong argument in comma separated sector list:\t"<<sector<<"\n";
  }
}



void
ApeOverview::getOverview(){
  //pluginDir_ = "ApeEstimatorCosmics1/";
  //int nKeys = inputFile_->GetNkeys();
  //pluginDir_ = inputFile_->GetListOfKeys()->At(0)->GetName();
  //pluginDir_ += "/";
  if(moduleNo_<1 || moduleNo_>inputFile_->GetNkeys()){
    std::cout<<"Incorrect number given in method whichModuleInFile(...), cannot continue!!!\n";
    return;
  }
  pluginDir_ = inputFile_->GetListOfKeys()->At(moduleNo_-1)->GetName();
  pluginDir_ += "/";
  
  TDirectory* secDir(0);
  bool sectorBool(true);
  for(unsigned int iSec(1);sectorBool;++iSec){
    std::stringstream sectorName, fullDirectoryName;
    sectorName << "Sector_" << iSec << "/";
    fullDirectoryName << pluginDir_ << sectorName.str();
    TString fullName(fullDirectoryName.str().c_str());
    inputFile_->cd();
    secDir = (TDirectory*)inputFile_->TDirectory::GetDirectory(fullName);
    if(secDir){
      mSectorPadCounter_[iSec].first = mSectorPadCounter_[iSec].second = 1;
      mSectorPair_[iSec].first = mSectorPair_[iSec].second = std::vector<TCanvas*>();
    }
    else sectorBool = false;
  }
  
  // first print event and track histos (FIXME: now contains also sector hists -> rename)
  this->eventAndTrackHistos();
}


TString
ApeOverview::setCanvasName()const{
  std::stringstream canvas;
  int canvasCounter(0);
  canvasCounter += eventPair_.first.size() + eventPair_.second.size() + trackPair_.first.size() + trackPair_.second.size();
  for(std::map<unsigned int,CanvasPair>::const_iterator iSec = mSectorPair_.begin(); iSec != mSectorPair_.end(); ++iSec){
    canvasCounter += (*iSec).second.first.size() + (*iSec).second.second.size();
  }
  canvas << "canvas" << canvasCounter;
  return (canvas.str()).c_str();
}


void
ApeOverview::eventAndTrackHistos(){
  TString histName;
  
  histDir_ = "EventVariables/";
  histLevel_ = event;
  std::cout<<"List of event histograms to print:\n";
  
  if(!onlyZoomedHists_){
  this->drawHistToPad("h_trackSize",true);  //logScale only for 1d-hists? Also for Profiles, but not TH2?
  }
  
  histDir_ = "TrackVariables/";
  histLevel_ = track;
  std::cout<<"List of track histograms to print:\n";
  
  if(!onlyZoomedHists_){
  this->drawHistToPad("h_hitSize");
  this->drawHistToPad("h_hitValid");
  this->drawHistToPad("h_hitsGood");
  this->drawHistToPad("h_hit2D");
  this->drawHistToPad("h_hitInvalid");
  this->drawHistToPad("h_layerMissed");
  }
  
  this->drawHistToPad("h_chi2");
  this->drawHistToPad("h_ndof");
  this->drawHistToPad("h_norChi2");
  if(!onlyZoomedHists_){
  this->drawHistToPad("h_eta");
  this->drawHistToPad("h_theta");
  this->drawHistToPad("h_phi");
  }
  this->setNewCanvas(dim1);
  
  this->drawHistToPad("h_pt");
  this->drawHistToPad("h_d0Beamspot");
  this->drawHistToPad("h_dz");
  this->drawHistToPad("h_p");
  if(!onlyZoomedHists_){
  this->drawHistToPad("h_charge",false);
  this->drawHistToPad("h_meanAngle");
  }
  this->setNewCanvas(dim1);
  
  if(!onlyZoomedHists_){
  this->drawHistToPad("h2_hitsGoodVsHitsValid",false);
  this->drawHistToPad("h2_meanAngleVsHits",false);
  }
  
  histLevel_ = sector;
  TDirectory* secDir(0);
  bool sectorBool(true);
  for(unsigned int iSec(1);sectorBool;++iSec){
    std::stringstream sectorName, fullDirectoryName;
    sectorName << "Sector_" << iSec << "/";
    fullDirectoryName << pluginDir_ << sectorName.str();
    TString fullName(fullDirectoryName.str().c_str());
    inputFile_->cd();
    secDir = (TDirectory*)inputFile_->TDirectory::GetDirectory(fullName);
    sectorCounter_ = iSec;
    if(secDir){
      
      bool selectedSector(false);
      std::stringstream ssFirstSelectedSector;
      ssFirstSelectedSector << "Sector_";
      if(vSelectedSector_.size() == 0){
        selectedSector = true;
	ssFirstSelectedSector << "1";
      }
      else{
        ssFirstSelectedSector << *(vSelectedSector_.begin());
      }
      firstSelectedSector_ = ssFirstSelectedSector.str().c_str();
      
      for(std::vector<unsigned int>::const_iterator iSelSec = vSelectedSector_.begin(); iSelSec != vSelectedSector_.end(); ++iSelSec){
        if(iSec==*iSelSec)selectedSector = true;
      }
      if(!selectedSector)continue;
      
      histDir_  = sectorName.str().c_str();
      if(histDir_.BeginsWith(firstSelectedSector_))std::cout<<"List of hit histograms to print (showcase for "<<firstSelectedSector_<<", all other sectors identical):\n";
      
      this->drawHistToPad("sectorTitleSheet");
      
      this->drawHistToPad("h_Width");
      this->drawHistToPad("h_WidthProj");
      this->drawHistToPad("h_WidthDiff");
      if(!onlyZoomedHists_){
      this->drawHistToPad("h_MaxStrip",false);
      this->drawHistToPad("h_MaxIndex");
      this->drawHistToPad("h_BaryStrip",false);
      }
      this->drawHistToPad("h_Charge");
      this->drawHistToPad("h_SOverN");
      if(!onlyZoomedHists_){
      this->drawHistToPad("h_MaxCharge");
      this->drawHistToPad("h_ChargeOnEdges");
      this->drawHistToPad("h_ChargeAsymmetry");
      //this->drawHistToPad("h_IsModuleUsable");  // not filled anymore, hits already deselected
      }
      this->setNewCanvas(dim1);
      
      this->drawHistToPad("h_ResX");
      this->drawHistToPad("h_NorResX");
      this->drawHistToPad("h_ProbX",false);
      this->drawHistToPad("h_SigmaXHit");
      this->drawHistToPad("h_SigmaXTrk");
      this->drawHistToPad("h_SigmaX");
      for(unsigned int iUint = 1;;++iUint){
        std::stringstream sigmaXHit, sigmaXTrk, sigmaX;
        sigmaXHit << "h_sigmaXHit_" << iUint;
        sigmaXTrk << "h_sigmaXTrk_" << iUint;
        sigmaX    << "h_sigmaX_"    << iUint;
	if(this->drawHistToPad(sigmaXHit.str().c_str()) == -1){this->setNewCanvas(dim1); break;}
	this->drawHistToPad(sigmaXTrk.str().c_str());
	this->drawHistToPad(sigmaX.str().c_str());
      }
      if(!onlyZoomedHists_){
      this->drawHistToPad("h_XHit");
      this->drawHistToPad("h_XTrk");
      this->setNewCanvas(dim1);
      this->drawHistToPad("h_PhiSens");
      this->drawHistToPad("h_PhiSensX");
      this->drawHistToPad("h_PhiSensY");
      }
      
      if(!onlyZoomedHists_){
      this->drawHistToPad("h2_sigmaXTrkVsHitsValid",false);
      this->drawHistToPad("h2_sigmaXTrkVsHitsGood",false);
      this->drawHistToPad("h2_sigmaXTrkVsMeanAngle",false);
      this->setNewCanvas(dim2);
      }
      if(!onlyZoomedHists_){
      this->drawHistToPad("h2_sigmaXTrkVsHitsInvalid",false);
      this->drawHistToPad("h2_sigmaXTrkVsLayersMissed",false);
      }
      this->drawHistToPad("h2_sigmaXTrkVsP",false);
      this->setNewCanvas(dim2);
      if(!onlyZoomedHists_){
      this->drawHistToPad("h2_sigmaXTrkVsTheta",false);
      this->drawHistToPad("h2_sigmaXTrkVsPhi",false);
      this->drawHistToPad("h2_sigmaXTrkVsMaxStrip",false);
      this->setNewCanvas(dim2);
      }
      this->drawHistToPad("h2_sigmaXTrkVsD0Beamspot",false);
      this->drawHistToPad("h2_sigmaXTrkVsDz",false);
      this->drawHistToPad("h2_sigmaXTrkVsPt",false);
      this->drawHistToPad("h2_sigmaXTrkVsInvP",false);
      this->drawHistToPad("h2_sigmaXVsNorChi2",false);
      this->setNewCanvas(dim2);
      
      this->drawHistToPad("h2_sigmaXHitVsWidth",false);
      this->drawHistToPad("h2_sigmaXHitVsWidthProj",false);
      this->drawHistToPad("h2_sigmaXHitVsWidthDiff",false);
      if(!onlyZoomedHists_){
      this->drawHistToPad("h2_sigmaXHitVsMaxStrip",false);
      this->drawHistToPad("h2_sigmaXHitVsMaxIndex",false);
      this->drawHistToPad("h2_sigmaXHitVsBaryStrip",false);
      }
      this->drawHistToPad("h2_sigmaXHitVsCharge",false);
      this->drawHistToPad("h2_sigmaXHitVsSOverN",false);
      if(!onlyZoomedHists_){
      this->drawHistToPad("h2_sigmaXHitVsMaxCharge",false);
      this->drawHistToPad("h2_sigmaXHitVsChargeOnEdges",false);
      this->drawHistToPad("h2_sigmaXHitVsChargeAsymmetry",false);
      }
      this->setNewCanvas(dim2);
      
      if(!onlyZoomedHists_){
      this->drawHistToPad("h2_sigmaXHitVsPhiSens",false);
      this->drawHistToPad("h2_sigmaXHitVsPhiSensX",false);
      this->drawHistToPad("h2_sigmaXHitVsPhiSensY",false);
      this->drawHistToPad("h2_sigmaXTrkVsPhiSens",false);
      this->drawHistToPad("h2_sigmaXTrkVsPhiSensX",false);
      this->drawHistToPad("h2_sigmaXTrkVsPhiSensY",false);
      this->drawHistToPad("h2_sigmaXVsPhiSens",false);
      this->drawHistToPad("h2_sigmaXVsPhiSensX",false);
      this->drawHistToPad("h2_sigmaXVsPhiSensY",false);
      }
      
      if(!onlyZoomedHists_){
      this->drawHistToPad("h2_norResXVsHitsValid",false);
      this->drawHistToPad("h2_norResXVsHitsGood",false);
      this->drawHistToPad("h2_norResXVsMeanAngle",false);
      this->drawHistToPad("h2_norResXVsHitsInvalid",false);
      this->drawHistToPad("h2_norResXVsLayersMissed",false);
      }
      this->drawHistToPad("h2_norResXVsP",false);
      if(!onlyZoomedHists_){
      this->setNewCanvas(dim2);
      }
      
      this->drawHistToPad("h2_norResXVsNorChi2",false);
      if(!onlyZoomedHists_){
      this->drawHistToPad("h2_norResXVsTheta",false);
      this->drawHistToPad("h2_norResXVsPhi",false);
      }
      this->setNewCanvas(dim2);
      this->drawHistToPad("h2_norResXVsD0Beamspot",false);
      this->drawHistToPad("h2_norResXVsDz",false);
      this->drawHistToPad("h2_norResXVsPt",false);
      
      this->drawHistToPad("h2_norResXVsWidth",false);
      this->drawHistToPad("h2_norResXVsWidthProj",false);
      this->drawHistToPad("h2_norResXVsWidthDiff",false);
      if(!onlyZoomedHists_){
      this->drawHistToPad("h2_norResXVsMaxStrip",false);
      this->drawHistToPad("h2_norResXVsMaxIndex",false);
      this->drawHistToPad("h2_norResXVsBaryStrip",false);
      }
      this->drawHistToPad("h2_norResXVsCharge",false);
      this->drawHistToPad("h2_norResXVsSOverN",false);
      if(!onlyZoomedHists_){
      this->drawHistToPad("h2_norResXVsMaxCharge",false);
      this->drawHistToPad("h2_norResXVsChargeOnEdges",false);
      this->drawHistToPad("h2_norResXVsChargeAsymmetry",false);
      }
      this->setNewCanvas(dim2);
      
      if(!onlyZoomedHists_){
      this->drawHistToPad("h2_norResXVsPhiSens",false);
      this->drawHistToPad("h2_norResXVsPhiSensX",false);
      this->drawHistToPad("h2_norResXVsPhiSensY",false);
      }
      
      this->drawHistToPad("h2_norResXVsSigmaXHit",false);
      this->drawHistToPad("h2_norResXVsSigmaXTrk",false);
      this->drawHistToPad("h2_norResXVsSigmaX",false);
      this->setNewCanvas(dim2);
      
      
      if(!onlyZoomedHists_){
      this->drawHistToPad("h2_probXVsHitsValid",false);
      this->drawHistToPad("h2_probXVsHitsGood",false);
      this->drawHistToPad("h2_probXVsMeanAngle",false);
      this->drawHistToPad("h2_probXVsHitsInvalid",false);
      this->drawHistToPad("h2_probXVsLayersMissed",false);
      }
      this->drawHistToPad("h2_probXVsP",false);
      if(!onlyZoomedHists_){
      this->setNewCanvas(dim2);
      }
      
      this->drawHistToPad("h2_probXVsNorChi2",false);
      if(!onlyZoomedHists_){
      this->drawHistToPad("h2_probXVsTheta",false);
      this->drawHistToPad("h2_probXVsPhi",false);
      }
      this->setNewCanvas(dim2);
      this->drawHistToPad("h2_probXVsD0Beamspot",false);
      this->drawHistToPad("h2_probXVsDz",false);
      this->drawHistToPad("h2_probXVsPt",false);
      
      this->drawHistToPad("h2_probXVsWidth",false);
      this->drawHistToPad("h2_probXVsWidthProj",false);
      this->drawHistToPad("h2_probXVsWidthDiff",false);
      if(!onlyZoomedHists_){
      this->drawHistToPad("h2_probXVsMaxStrip",false);
      this->drawHistToPad("h2_probXVsMaxIndex",false);
      this->drawHistToPad("h2_probXVsBaryStrip",false);
      }
      this->drawHistToPad("h2_probXVsCharge",false);
      this->drawHistToPad("h2_probXVsSOverN",false);
      if(!onlyZoomedHists_){
      this->drawHistToPad("h2_probXVsMaxCharge",false);
      this->drawHistToPad("h2_probXVsChargeOnEdges",false);
      this->drawHistToPad("h2_probXVsChargeAsymmetry",false);
      }
      this->setNewCanvas(dim2);
      
      if(!onlyZoomedHists_){
      this->drawHistToPad("h2_probXVsPhiSens",false);
      this->drawHistToPad("h2_probXVsPhiSensX",false);
      this->drawHistToPad("h2_probXVsPhiSensY",false);
      }
      
      this->drawHistToPad("h2_probXVsSigmaXHit",false);
      this->drawHistToPad("h2_probXVsSigmaXTrk",false);
      this->drawHistToPad("h2_probXVsSigmaX",false);
      this->setNewCanvas(dim2);
      
      
      this->drawHistToPad("h2_widthVsPhiSensX",false);
      this->drawHistToPad("h2_widthVsWidthProj",false);
      this->drawHistToPad("h2_widthDiffVsMaxStrip",false);
      
      this->setNewCanvas(dim1);
      TDirectory* intDir(0);
      bool intervalBool(true);
      for(unsigned int iBin(1);intervalBool;++iBin){
        std::stringstream intervalName, fullDirectoryName2;
        intervalName << "Interval_" << iBin << "/";
	fullDirectoryName2 << fullDirectoryName.str() << intervalName.str();
        TString fullName2(fullDirectoryName2.str().c_str());
	inputFile_->cd();
        intDir = (TDirectory*)inputFile_->TDirectory::GetDirectory(fullName2);
	if(intDir){
	  histDir_  = (sectorName.str() + intervalName.str()).c_str();
	  if(!onlyZoomedHists_){
	  this->drawHistToPad("h_norResX",false);
	  }
	}
	else intervalBool = false;
      }
      
      if(!onlyZoomedHists_){
      this->setNewCanvas(dim1);
      TDirectory* resDir(0);
      std::string resultName("Results/");
      std::stringstream fullDirectoryName3;
      fullDirectoryName3 << fullDirectoryName.str() << resultName;
      resDir = (TDirectory*)inputFile_->TDirectory::GetDirectory(fullDirectoryName3.str().c_str());
      histDir_  = (sectorName.str() + resultName).c_str();
      this->drawHistToPad("h_meanX",false);
      this->drawHistToPad("h_fitMeanX1",false);
      this->drawHistToPad("h_fitMeanX2",false);
      this->drawHistToPad("h_rmsX",false);
      this->drawHistToPad("h_residualWidthX1",false);
      this->drawHistToPad("h_residualWidthX2",false);
      this->drawHistToPad("h_entries");
      this->drawHistToPad("h_correctionX1",false);
      this->drawHistToPad("h_correctionX2",false);
      }
    }
    else sectorBool = false;
  }
}



int
ApeOverview::drawHistToPad(const TString histName, const bool setLogScale){
  PadCounterPair* padCounter;
  CanvasPair* canvasPair;
  
  if(histLevel_==event){padCounter=&eventPadCounter_; canvasPair=&eventPair_;}
  else if(histLevel_==track){padCounter=&trackPadCounter_; canvasPair=&trackPair_;}
  else if(histLevel_==sector){padCounter=&mSectorPadCounter_[sectorCounter_]; canvasPair=&mSectorPair_[sectorCounter_];}
  else return -1;
  
  //if(histName.BeginsWith("h_", TString::kIgnoreCase)) not case sensitive
  if(histName.BeginsWith("h_")){
    if(padCounter->first >= 7){padCounter->first = 1;}
    if(padCounter->first == 1){
      //new TCanvas
      TCanvas* canvas0 = new TCanvas(this->setCanvasName());
      canvas0->Divide(3,2);
      canvasPair->first.push_back(canvas0);
    }
    (*(--(canvasPair->first.end())))->cd(padCounter->first);
    TH1 *hist1(0);
    inputFile_->GetObject(pluginDir_ + histDir_ + histName + ";1", hist1);
    if(histDir_.BeginsWith(firstSelectedSector_) || histDir_ == "TrackVariables/" || histDir_ == "EventVariables/")std::cout<<"\tDraw 1D Histo\t\t"<<pluginDir_<<histDir_<<histName<<"\n";
    //GetEntries delivers double
    if(hist1){
      if(setLogScale==true && hist1->GetEffectiveEntries()>0.1)(*(--(canvasPair->first.end())))->cd(padCounter->first)->SetLogy();
      //if(setLogScale==true && hist1->Integral()>0.1)(*(--(canvasPair->first.end())))->cd(padCounter->first)->SetLogy();  // gives same result
      hist1->Draw();
    }
    else{if(histDir_.BeginsWith(firstSelectedSector_) || histDir_ == "TrackVariables/" || histDir_ == "EventVariables/")std::cout<<"\t\t\t\t... Histogram does not exist!\n"; if(padCounter->first == 1)canvasPair->first.pop_back(); return -1;}
    ++(padCounter->first);
    return 0;
  }
  
  else if(histName.BeginsWith("h2_")){
    if(padCounter->second >= 4){padCounter->second = 1;}
    if(padCounter->second == 1){
      //new TCanvas
      TCanvas* canvas0 = new TCanvas(this->setCanvasName());
      canvas0->Divide(3,2);
      canvasPair->second.push_back(canvas0);
    }
    (*(--(canvasPair->second.end())))->cd(padCounter->second);
    TH2 *hist2(0);
    inputFile_->GetObject(pluginDir_ + histDir_ + histName + ";1", hist2);
    if(histDir_.BeginsWith(firstSelectedSector_) || histDir_ == "TrackVariables/" || histDir_ == "EventVariables/")std::cout<<"\tDraw 2D Histo\t\t"<<pluginDir_<<histDir_<<histName<<"\n";
    if(hist2){
      if(setLogScale==true && hist2->GetEffectiveEntries()>0.1)(*(--(canvasPair->second.end())))->cd(padCounter->second)->SetLogy();
      hist2->Draw("box");
    }
    else{if(histDir_.BeginsWith(firstSelectedSector_) || histDir_ == "TrackVariables/" || histDir_ == "EventVariables/")std::cout<<"\t\t\t\t... Histogram does not exist!\n"; if(padCounter->second == 1)canvasPair->second.pop_back(); return -1;}
    
    (*(--(canvasPair->second.end())))->cd(padCounter->second+3);
    TString histNameP(histName);
    histNameP.ReplaceAll("h2_","p_");
    TProfile *histP(0);
    inputFile_->GetObject(pluginDir_ + histDir_ + histNameP + ";1", histP);
    if(histDir_.BeginsWith(firstSelectedSector_) || histDir_ == "TrackVariables/" || histDir_ == "EventVariables/")std::cout<<"\tDraw Profile Histo\t"<<pluginDir_<<histDir_<<histNameP<<"\n";
    if(histP){
      if(setLogScale==true && histP->GetEffectiveEntries()>0.1)(*(--(canvasPair->second.end())))->cd(padCounter->second+3)->SetLogy();
      histP->Draw();
    }
    else{if(histDir_.BeginsWith(firstSelectedSector_) || histDir_ == "TrackVariables/" || histDir_ == "EventVariables/")std::cout<<"\t\t\t\t... Histogram does not exist!\n";return -1;}
    ++(padCounter->second);
    return 0;
  }
  else if(histName.BeginsWith("p_")){std::cout<<"\n\tProfile Plot chosen, but set up automatically"<<std::endl; return 1;}
  else if(histName == "sectorTitleSheet"){
    TCanvas* canvas0 = new TCanvas(this->setCanvasName());
      canvas0->cd();
      TLatex *title1 = new TLatex(0.1583,0.925,histDir_);title1->SetNDC();//title1->SetTextSize(0.075);
      title1->Draw();
      canvasPair->first.push_back(canvas0);
      this->setNewCanvas(dim1);
      return 0;
  }
  else{std::cout<<"\n\tIncorrect Initial Letters for histogram !!!"<<std::endl; return -1;}
}


int
ApeOverview::setNewCanvas(const PlotDimension& pDim){
  std::pair<unsigned int, unsigned int>* padCounter;
  if(histLevel_==event){padCounter=&eventPadCounter_;}
  else if(histLevel_==track){padCounter=&trackPadCounter_;}
  else if(histLevel_==sector){padCounter=&mSectorPadCounter_[sectorCounter_];}
  else return -1;
  
  if(pDim==dim1){padCounter->first = 7; return 0;}
  else if(pDim==dim2){padCounter->second = 4; return 0;}
  else return -1;
  return 0;
}



void
ApeOverview::printOverview(const TString& outputFileName, const HistLevel& histLevel)const{
  if(eventPair_.first.size()==0 && eventPair_.second.size()==0 &&
     trackPair_.first.size()==0 && trackPair_.second.size()==0 &&
     mSectorPair_.size()==0)return;
  std::cout<<"\tCreate PostScript File:\t"<<outputFileName<<std::endl;
  TPostScript* ps = new TPostScript(outputFileName,112);
  std::vector<TCanvas*>::const_iterator iCan;
  if(histLevel==event){
    for(iCan = eventPair_.first.begin(); iCan != eventPair_.first.end(); ++iCan){ps->NewPage();(*iCan)->Draw();}
    for(iCan = eventPair_.second.begin(); iCan != eventPair_.second.end(); ++iCan){ps->NewPage();(*iCan)->Draw();}
  }
  if(histLevel==event || histLevel==track){
    for(iCan = trackPair_.first.begin(); iCan != trackPair_.first.end(); ++iCan){ps->NewPage();(*iCan)->Draw();}
    for(iCan = trackPair_.second.begin(); iCan != trackPair_.second.end(); ++iCan){ps->NewPage();(*iCan)->Draw();}
  }
  if(histLevel==event || histLevel==track || histLevel==sector){
    std::map<unsigned int, CanvasPair>::const_iterator iSec;
    for(iSec = mSectorPair_.begin(); iSec != mSectorPair_.end(); ++iSec){
      for(iCan = iSec->second.first.begin(); iCan != iSec->second.first.end(); ++iCan){ps->NewPage();(*iCan)->Draw();}
      for(iCan = iSec->second.second.begin(); iCan != iSec->second.second.end(); ++iCan){ps->NewPage();(*iCan)->Draw();}
    }    
  }
  ps->Close();
}





