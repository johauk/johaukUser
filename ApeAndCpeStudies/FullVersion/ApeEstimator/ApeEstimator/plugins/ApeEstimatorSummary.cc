// -*- C++ -*-
//
// Package:    ApeEstimatorSummary
// Class:      ApeEstimatorSummary
// 
/**\class ApeEstimatorSummary ApeEstimatorSummary.cc Alignment/ApeEstimatorSummary/src/ApeEstimatorSummary.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Johannes Hauk,6 2-039,+41227673512,
//         Created:  Mon Oct 11 13:44:03 CEST 2010
// $Id: ApeEstimatorSummary.cc,v 1.7 2011/06/05 15:48:03 hauk Exp $
//
//


// system include files
#include <memory>
#include <fstream>
#include <sstream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Utilities/interface/EDMException.h"



#include "ApeEstimator/ApeEstimator/interface/TrackerSectorStruct.h"


#include "TH1.h"
#include "TString.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TTree.h"
#include "TF1.h"
#include "TMath.h"
//
// class declaration
//

class ApeEstimatorSummary : public edm::EDAnalyzer {
   public:
      explicit ApeEstimatorSummary(const edm::ParameterSet&);
      ~ApeEstimatorSummary();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      void openInputFile();
      void getTrackerSectorStructs();
      void bookHists();
      std::vector<double> residualErrorBinning();
      void writeHists();
      
      void calculateApe();
      
      enum ApeWeight{wInvalid, wUnity, wEntries, wEntriesOverSigmaX2};
      
      // ----------member data ---------------------------
      const edm::ParameterSet parameterSet_;
      
      
      TFile* inputFile_;
      
      std::map<unsigned int, TrackerSectorStruct> m_tkSector_;
      
      
      TH1 *MeanX, *RmsX,
          *FitMeanX1, *ResidualWidthX1, *CorrectionX1,
          *FitMeanX2, *ResidualWidthX2, *CorrectionX2;
      
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
ApeEstimatorSummary::ApeEstimatorSummary(const edm::ParameterSet& iConfig):
parameterSet_(iConfig),
inputFile_(0)
{
}


ApeEstimatorSummary::~ApeEstimatorSummary()
{
}


//
// member functions
//

void
ApeEstimatorSummary::openInputFile(){
  const std::string inputFileName(parameterSet_.getParameter<std::string>("InputFile"));
  ifstream inputFileStream;
  // Check if baseline file exists
  inputFileStream.open(inputFileName.c_str());
  if(inputFileStream.is_open()){
    inputFile_ = new TFile(inputFileName.c_str(),"READ");
  }
  if(inputFile_){
    edm::LogInfo("CalculateAPE")<<"Input file from loop over tracks and corresponding hits sucessfully opened";
  }
  else{
    edm::LogError("CalculateAPE")<<"There is NO input file\n"
       <<"...APE calculation stopped. Please check path of input file name in config:\n"
       <<"\t"<<inputFileName;
    throw edm::Exception( edm::errors::Configuration,
                          "Bad input file name");
  }
}



void
ApeEstimatorSummary::getTrackerSectorStructs(){
  // At present first of the plugins registered in TFileService needs to be the one containing the normalized residual histos per sector   per error bin
  TString pluginName(inputFile_->GetListOfKeys()->At(0)->GetName());
  //std::cout<<"\n\tPlugin Name "<<pluginName<<"\n\n";
  
  pluginName += "/";
  TDirectory *sectorDir(0), *intervalDir(0);
  bool sectorBool(true);
  for(unsigned int iSector(1);sectorBool;++iSector){
    std::stringstream sectorName, fullSectorName;
    sectorName << "Sector_" << iSector << "/";
    fullSectorName << pluginName << sectorName.str();
    TString fullName(fullSectorName.str().c_str());
    inputFile_->cd();
    sectorDir = (TDirectory*)inputFile_->TDirectory::GetDirectory(fullName);
    if(sectorDir){
      TrackerSectorStruct tkSector;
      bool intervalBool(true);
      for(unsigned int iInterval(1);intervalBool;++iInterval){
        std::stringstream intervalName, fullIntervalName;
	intervalName << "Interval_" << iInterval <<"/";
	fullIntervalName << fullSectorName.str() << intervalName.str();
	fullName = fullIntervalName.str().c_str();
	//std::cout<<"\n\tInterval name "<<fullName<<"\n";
	intervalDir = (TDirectory*)inputFile_->TDirectory::GetDirectory(fullName);
	if(intervalDir){
	  //inputFile_->GetObject(fullName + "h_sigmaX;1", tkSector.m_binnedHists[iInterval]["sigmaX"]);
	  intervalDir->GetObject("h_sigmaX;1", tkSector.m_binnedHists[iInterval]["sigmaX"]);
	  intervalDir->GetObject("h_norResX;1", tkSector.m_binnedHists[iInterval]["norResX"]);
	  //std::cout<<"\n\tTEST2 Interval"<<iInterval<<" "<<tkSector.m_binnedHists[iInterval]["sigmaX"]<<" "<<tkSector.m_binnedHists[iInterval]["norResX"]<<"\n";
	  //std::cout<<"\n\tSigmaX: "<<tkSector.m_binnedHists[iInterval]["sigmaX"]->GetMean()<<" "<<tkSector.m_binnedHists[iInterval]["sigmaX"]->GetRMS()<<"\n";
	  //std::cout<<"\tNorResX: "<<tkSector.m_binnedHists[iInterval]["norResX"]->GetMean()<<" "<<tkSector.m_binnedHists[iInterval]["norResX"]->GetRMS()<<"\n";
	}
	else{
	  intervalBool = false;
	  if(iSector==1)edm::LogInfo("CalculateAPE")<<"There are "<<iInterval-1<<" intervals per sector defined in input file";
	}
      }
      TDirectory *resultsDir(0);
      std::stringstream fullResultName;
      fullResultName << fullSectorName.str() << "Results/";
      fullName = fullResultName.str().c_str();
      resultsDir = (TDirectory*)inputFile_->TDirectory::GetDirectory(fullName);
      if(resultsDir){
        resultsDir->GetObject("h_entries;1", tkSector.Entries);
	//std::cout<<"\n\tTest Results "<<tkSector.Entries<<"\n";
	//std::cout<<"\n\tEntries "<<tkSector.Entries->GetMean()<<" "<<tkSector.Entries->GetRMS()<<"\n";
	TTree* rawIdTree(0);
	resultsDir->GetObject("rawIdTree", rawIdTree);
	//std::cout<<"\n\tTest RawId "<<rawIdTree<<"\n";
	//std::cout<<"\n\tRawId "<<rawIdTree->GetEntries()<<"\n";
	unsigned int rawId(0);
	rawIdTree->SetBranchAddress("RawId", &rawId);
	for(Int_t entry=0; entry<rawIdTree->GetEntries(); ++entry){
	  rawIdTree->GetEntry(entry);
	  // command "hadd" adds entries in TTree, so rawId are existing as often as number of files are added
	  bool alreadyAdded(false);
	  for(std::vector<unsigned int>::const_iterator i_rawId = tkSector.v_rawId.begin(); i_rawId != tkSector.v_rawId.end(); ++i_rawId){
	    if(rawId==*i_rawId)alreadyAdded = true;
	  }
	  if(alreadyAdded)break;
	  tkSector.v_rawId.push_back(rawId);
	}
      }
      m_tkSector_[iSector] = tkSector;
    }
    else{
      sectorBool = false;
      edm::LogInfo("CalculateAPE")<<"There are "<<iSector-1<<" sectors defined in input file";
    }
  }
}



void
ApeEstimatorSummary::bookHists(){
  const std::vector<double> v_binX(this->residualErrorBinning());
  for(std::map<unsigned int,TrackerSectorStruct>::iterator i_sector=m_tkSector_.begin(); i_sector!=m_tkSector_.end(); ++i_sector){
    (*i_sector).second.MeanX           = new TH1F("h_meanX","residual mean <r_{x}/#sigma_{x}>;#sigma_{x}  [cm];<r_{x}/#sigma_{x}>",v_binX.size()-1,&(v_binX[0]));
    (*i_sector).second.RmsX            = new TH1F("h_rmsX","residual rms RMS(r_{x}/#sigma_{x});#sigma_{x}  [cm];RMS(r_{x}/#sigma_{x})",v_binX.size()-1,&(v_binX[0]));
    (*i_sector).second.FitMeanX1       = new TH1F("h_fitMeanX1","fitted residual mean #mu_{x};#sigma_{x}  [cm];#mu_{x}",v_binX.size()-1,&(v_binX[0]));
    (*i_sector).second.ResidualWidthX1 = new TH1F("h_residualWidthX1","residual width #Delta_{x};#sigma_{x}  [cm];#Delta_{x}",v_binX.size()-1,&(v_binX[0]));
    (*i_sector).second.CorrectionX1    = new TH1F("h_correctionX1","correction to APE_{x};#sigma_{x}  [cm];#DeltaAPE_{x}",v_binX.size()-1,&(v_binX[0]));
    (*i_sector).second.FitMeanX2       = new TH1F("h_fitMeanX2","fitted residual mean #mu_{x};#sigma_{x}  [cm];#mu_{x}",v_binX.size()-1,&(v_binX[0]));
    (*i_sector).second.ResidualWidthX2 = new TH1F("h_residualWidthX2","residual width #Delta_{x};#sigma_{x}  [cm];#Delta_{x}",v_binX.size()-1,&(v_binX[0]));
    (*i_sector).second.CorrectionX2    = new TH1F("h_correctionX2","correction to APE_{x};#sigma_{x}  [cm];#DeltaAPE_{x}",v_binX.size()-1,&(v_binX[0]));
  }
}



std::vector<double>
ApeEstimatorSummary::residualErrorBinning(){
  std::vector<double> v_binX;
  TH1* Entries(m_tkSector_[1].Entries);
  for(int iBin=1; iBin<=Entries->GetNbinsX()+1; ++iBin){
    //std::cout<<"\n\tLower bin edge of bin"<<iBin<<" "<<Entries->GetBinLowEdge(iBin)<<"\n";
    v_binX.push_back(Entries->GetBinLowEdge(iBin));
  }
  return v_binX;
}


void
ApeEstimatorSummary::writeHists(){
  //TDirectory* oldDir = gDirectory;
  TFile* resultsFile = new TFile(parameterSet_.getParameter<std::string>("ResultsFile").c_str(), "RECREATE");
  TDirectory* baseDir = resultsFile->mkdir("ApeEstimatorSummary");
  for(std::map<unsigned int,TrackerSectorStruct>::const_iterator i_sector=m_tkSector_.begin(); i_sector!=m_tkSector_.end(); ++i_sector){
    std::stringstream dirName;
    dirName<<"Sector_" << (*i_sector).first;
    //resultsFile->mkdir(dirName.str().c_str());
    TDirectory* dir = baseDir->mkdir(dirName.str().c_str());
    //resultsFile->cd(dirName.str().c_str());
    dir->cd();
    
    (*i_sector).second.MeanX->Write();
    (*i_sector).second.RmsX->Write();	   
    (*i_sector).second.FitMeanX1->Write();	   
    (*i_sector).second.ResidualWidthX1 ->Write();
    (*i_sector).second.CorrectionX1->Write();   
    (*i_sector).second.FitMeanX2->Write();	   
    (*i_sector).second.ResidualWidthX2->Write();
    (*i_sector).second.CorrectionX2->Write();  
  }
  //resultsFile->Write();
  resultsFile->Close();
  //oldDir->cd();
}



void
ApeEstimatorSummary::calculateApe(){
   // Set baseline or calculate APE value?
   const bool setBaseline(parameterSet_.getParameter<bool>("setBaseline"));
   // Read in baseline file for calculation of APE value (if not setting baseline)
   // Has same format as iterationFile
   const std::string baselineFileName(parameterSet_.getParameter<std::string>("BaselineFile"));
   TFile* baselineFile(0);
   TTree* baselineTree(0);
   if(!setBaseline){
     ifstream baselineFileStream;
     // Check if baseline file exists
     baselineFileStream.open(baselineFileName.c_str());
     if(baselineFileStream.is_open()){
       baselineFile = new TFile(baselineFileName.c_str(),"READ");
     }
     if(baselineFile){
       edm::LogInfo("CalculateAPE")<<"Baseline file for APE values sucessfully opened";
       baselineFile->GetObject("iterTree;1",baselineTree);
     }
     else{
       edm::LogWarning("CalculateAPE")<<"There is NO baseline file for APE values, so normalized residual width =1 for ideal conditions is assumed";
     }
   }
   // Set up root file for iterations on APE value (or for setting baseline in setBaseline mode)
   const std::string iterationFileName(setBaseline ? baselineFileName : parameterSet_.getParameter<std::string>("IterationFile"));
   // For iterations, updates are needed to not overwrite the iterations before
   TFile* iterationFile = new TFile(iterationFileName.c_str(),setBaseline ? "RECREATE" : "UPDATE");
   
   
   // Set up TTree for iterative APE values on first pass (first iteration) or read from file (further iterations)
   TTree* iterationTree(0);
   iterationFile->GetObject("iterTree;1",iterationTree);
   
   bool firstIter(false);
   if(!iterationTree){ // should be always true in setBaseline mode, since file is recreated
     firstIter = true;
     if(!setBaseline){
       iterationTree = new TTree("iterTree","Tree for APE values of all iterations");
       edm::LogInfo("CalculateAPE")<<"First APE iteration (number 0.), create iteration file with TTree";
     }
     else{
       iterationTree = new TTree("iterTree","Tree for baseline values of normalized residual width");
       edm::LogInfo("CalculateAPE")<<"Set baseline, create baseline file with TTree";
     }
   }
   else{
     const unsigned int iteration(iterationTree->GetEntries());
     edm::LogWarning("CalculateAPE")<<"NOT the first APE iteration (number 0.) but the "<<iteration<<". one, is this wanted or forgot to delete old iteration file with TTree?";
   }
   
   double a_apeSector[16589];
   double a_baselineSector[16589];
   for(size_t i_sector = 1; i_sector <= m_tkSector_.size(); ++i_sector){
     a_apeSector[i_sector] = 99.;
     a_baselineSector[i_sector] = -99.;
     std::stringstream ss_sector, ss_sectorSuffixed;
     ss_sector << "Ape_Sector_" << i_sector;
     if(!setBaseline && baselineTree){
       baselineTree->SetBranchAddress(ss_sector.str().c_str(), &a_baselineSector[i_sector]);
       baselineTree->GetEntry(0);
     }
     else{
       // Set default ideal normalized residual width to 1
       a_baselineSector[i_sector] = 1.;
     }
     if(firstIter){ // should be always true in setBaseline mode, since file is recreated  
       ss_sectorSuffixed << ss_sector.str() << "/D";
       iterationTree->Branch(ss_sector.str().c_str(), &a_apeSector[i_sector], ss_sectorSuffixed.str().c_str());
     }
     else{
       iterationTree->SetBranchAddress(ss_sector.str().c_str(), &a_apeSector[i_sector]);
       iterationTree->GetEntry(iterationTree->GetEntries()-1);
     }
   }
   
   
   // Set up text file for writing out APE values per module
   ofstream apeOutputFile;
   if(!setBaseline){
     const std::string apeOutputFileName(parameterSet_.getParameter<std::string>("ApeOutputFile"));
     apeOutputFile.open(apeOutputFileName.c_str());
     if(apeOutputFile.is_open()){
       edm::LogInfo("CalculateAPE")<<"Text file for writing APE values successfully opened";
     }else{
       edm::LogError("CalculateAPE")<<"Text file for writing APE values NOT opened,\n"
                                    <<"...APE calculation stopped. Please check path of text file name in config:\n"
                                    <<"\t"<<apeOutputFileName;
       return;
     }
   }
   
   
   
   
   // Loop over sectors for calculating APE
   const std::string apeWeightName(parameterSet_.getParameter<std::string>("apeWeight"));
   ApeWeight apeWeight(wInvalid);
   if(apeWeightName=="unity") apeWeight = wUnity;
   else if(apeWeightName=="entries")apeWeight = wEntries;
   else if(apeWeightName=="entriesOverSigmaX2")apeWeight = wEntriesOverSigmaX2;
   if(apeWeight==wInvalid){
     edm::LogError("CalculateAPE")<<"Invalid parameter 'apeWeight' in cfg file: \""<<apeWeightName
                                  <<"\"\nimplemented apeWeights are \"unity\", \"entries\", \"entriesOverSigmaX2\""
				  <<"\n...APE calculation stopped.";
     return;
   }
   const double sigmaFactorFit(parameterSet_.getParameter<double>("sigmaFactorFit"));
   const double correctionScaling(parameterSet_.getParameter<double>("correctionScaling"));
   const bool smoothIteration(parameterSet_.getParameter<bool>("smoothIteration"));
   const double smoothFraction(parameterSet_.getParameter<double>("smoothFraction"));
   if(smoothFraction<=0. || smoothFraction>1.){
     edm::LogError("CalculateAPE")<<"Incorrect parameter in cfg file,"
                                  <<"\nsmoothFraction has to be in [0,1], but is "<<smoothFraction
				  <<"\n...APE calculation stopped.";
     return;
   }
   for(std::map<unsigned int,TrackerSectorStruct>::iterator i_sector = m_tkSector_.begin(); i_sector != m_tkSector_.end(); ++i_sector){
     
     typedef std::pair<double,double> ErrorX2AndResidualWidthX2PerBin;
     typedef std::pair<double,ErrorX2AndResidualWidthX2PerBin> WeightAndResultsPerBin;
     std::vector<WeightAndResultsPerBin> v_weightAndResultsPerBin;
     
     
     double baselineWidthX2(a_baselineSector[(*i_sector).first]);
     
     
     // Loop over residual error bins to calculate APE for every bin
     for(std::map<unsigned int, std::map<std::string,TH1*> >::const_iterator i_errBins = (*i_sector).second.m_binnedHists.begin();
         i_errBins != (*i_sector).second.m_binnedHists.end(); ++i_errBins){
       std::map<std::string,TH1*> mHists = (*i_errBins).second;
       
       double entries = mHists["sigmaX"]->GetEntries();
       double meanSigmaX = mHists["sigmaX"]->GetMean();
       //double meanSigmaX = (*i_sector).second.Entries->GetBinCenter((*i_errBins).first);
       //std::cout<<"\n\tMean1 "<<meanSigmaX<<"\n";
       //std::cout<<"\n\tMean2 "<<(*i_sector).second.Entries->GetBinCenter((*i_errBins).first)<<"\n";
       
       // Fitting Parameters
       double xMin     = mHists["norResX"]->GetXaxis()->GetXmin(),
              xMax     = mHists["norResX"]->GetXaxis()->GetXmax(),
	      integral = mHists["norResX"]->Integral(),
	      mean     = mHists["norResX"]->GetMean(),
	      rms      = mHists["norResX"]->GetRMS(),
	      maximum  = mHists["norResX"]->GetBinContent(mHists["norResX"]->GetMaximumBin());
       
       
       // First Gaus Fit
       TF1 func_1("mygaus", "gaus", xMin, xMax);
       func_1.SetParameters(maximum, mean, rms);
       TString fitOpt("ILERQ"); //TString fitOpt("IMR"); ("IRLL"); ("IRQ");
       Int_t fitResult(0);
       if(integral>1000.){
         if(mHists["norResX"]->Fit(&func_1, fitOpt)){
           edm::LogWarning("CalculateAPE")<<"Fit1 did not work: "<<mHists["norResX"]->Fit(&func_1, fitOpt);
           continue;
         }
         fitResult = mHists["norResX"]->Fit(&func_1, fitOpt);
         //std::cout<<"FitResult1\t"<<fitResult<<"\n";
       }
       Double_t mean_1  = func_1.GetParameter(1);
       Double_t sigma_1 = func_1.GetParameter(2);
       
       
       // Second gaus fit
       TF1 func_2("mygaus2","gaus",mean_1 - sigmaFactorFit * TMath::Abs(sigma_1),mean_1 + sigmaFactorFit * TMath::Abs(sigma_1));
       func_2.SetParameters(func_1.GetParameter(0),mean_1,sigma_1);
       if(integral>1000.){
         if(mHists["norResX"]->Fit(&func_2, fitOpt)){
           edm::LogWarning("CalculateAPE")<<"Fit2 did not work: "<<mHists["norResX"]->Fit(&func_2, fitOpt);
	   continue;
         }
         fitResult = mHists["norResX"]->Fit(&func_2, fitOpt);
       }
       Double_t mean_2  = func_2.GetParameter(1);
       Double_t sigma_2 = func_2.GetParameter(2);
       //std::cout<<"\n\tTest "<<integral<<" "<<mean<<" "<<rms<<" "<<mean_1<<" "<<sigma_1<<" "<<mean_2<<" "<<sigma_2<<"\n";
       
       
       // Fill histograms
       double fitMean_1(mean_1), fitMean_2(mean_2);
       double residualWidth_1(sigma_1), residualWidth_2(sigma_2);
       
       //double baselineWidthX2(a_baselineSector[(*i_sector).first]);  // now taken out of this loop, is one value per sector
       double correctionX2_1(-0.0010), correctionX2_2(-0.0010);
       correctionX2_1 = meanSigmaX*meanSigmaX*(residualWidth_1*residualWidth_1 -baselineWidthX2);
       correctionX2_2 = meanSigmaX*meanSigmaX*(residualWidth_2*residualWidth_2 -baselineWidthX2);
       
       
       double correctionX_1 = correctionX2_1>=0. ? std::sqrt(correctionX2_1) : -std::sqrt(-correctionX2_1);
       double correctionX_2 = correctionX2_2>=0. ? std::sqrt(correctionX2_2) : -std::sqrt(-correctionX2_2);
       // Meanwhile, this got very bad default values, or? (negative corrections allowed)
       if(isnan(correctionX_1))correctionX_1 = -0.0010;
       if(isnan(correctionX_2))correctionX_2 = -0.0010;
       
       if(entries<1000.){mean     = 0.; rms  = -0.0010;
                         fitMean_1 = 0.; correctionX_1 = residualWidth_1 = -0.0010;
			 fitMean_2 = 0.; correctionX_2 = residualWidth_2 = -0.0010;}
       
       //(*i_sector).second.Entries       ->SetBinContent((*i_errBins).first,integral);
       (*i_sector).second.MeanX         ->SetBinContent((*i_errBins).first,mean);
       (*i_sector).second.RmsX          ->SetBinContent((*i_errBins).first,rms);
       
       //std::cout<<"\n\nSector, Bin "<<(*i_sector).first<<"\t"<<(*i_errBins).first;
       //std::cout<<"\nEntries, MeanError, ResWidth, APE \t"<<entries<<"\t"<<meanSigmaX<<"\t"<<residualWidth<<"\t"<<ape<<"\n";
       (*i_sector).second.FitMeanX1      ->SetBinContent((*i_errBins).first,fitMean_1);
       (*i_sector).second.ResidualWidthX1->SetBinContent((*i_errBins).first,residualWidth_1);
       (*i_sector).second.CorrectionX1   ->SetBinContent((*i_errBins).first,correctionX_1);
       
       (*i_sector).second.FitMeanX2      ->SetBinContent((*i_errBins).first,fitMean_2);
       (*i_sector).second.ResidualWidthX2->SetBinContent((*i_errBins).first,residualWidth_2);
       (*i_sector).second.CorrectionX2   ->SetBinContent((*i_errBins).first,correctionX_2);
       
       
       // Use result for bin only when entries>1000
       if(entries<1000.)continue;
       
       double weight(0.);
       if(apeWeight==wUnity)weight = 1.;
       else if(apeWeight==wEntries)weight = entries;
       else if(apeWeight==wEntriesOverSigmaX2)weight = entries/(meanSigmaX*meanSigmaX);
       
       const ErrorX2AndResidualWidthX2PerBin errorX2AndResidualWidthX2PerBin(meanSigmaX*meanSigmaX, residualWidth_1*residualWidth_1);
       const WeightAndResultsPerBin weightAndResultsPerBin(weight, errorX2AndResidualWidthX2PerBin);
       v_weightAndResultsPerBin.push_back(weightAndResultsPerBin);
     }
     
     
     // Do the final calculations
     
     if(v_weightAndResultsPerBin.size() == 0){
       edm::LogError("CalculateAPE")<<"NO error interval of sector "<<(*i_sector).first<<" has a valid APE calculated,\n...so cannot set APE";
       continue;
     }
     
     double correctionX2(999.);
     
     // Get sum of all weights
     double weightSum(0.);
     std::vector<WeightAndResultsPerBin>::const_iterator i_apeBin;
     for(i_apeBin=v_weightAndResultsPerBin.begin(); i_apeBin!=v_weightAndResultsPerBin.end(); ++i_apeBin){
       weightSum += i_apeBin->first;
     }
     
     if(!setBaseline){
       // Calculate weighted mean
       bool firstInterval(true);
       for(i_apeBin=v_weightAndResultsPerBin.begin(); i_apeBin!=v_weightAndResultsPerBin.end(); ++i_apeBin){
         if(firstInterval){
	   correctionX2 = i_apeBin->first*i_apeBin->second.first*(i_apeBin->second.second - baselineWidthX2);
	   firstInterval = false;
	 }
	 else{
	   correctionX2 += i_apeBin->first*i_apeBin->second.first*(i_apeBin->second.second - baselineWidthX2);
	 }
       }
       correctionX2 = correctionX2/weightSum;
     }
     else{
       double numerator(0.), denominator(0.);
       for(i_apeBin=v_weightAndResultsPerBin.begin(); i_apeBin!=v_weightAndResultsPerBin.end(); ++i_apeBin){
         numerator += i_apeBin->first*i_apeBin->second.first*i_apeBin->second.second;
	 denominator+= i_apeBin->first*i_apeBin->second.first;
       }
       correctionX2 = numerator/denominator;
     }
     
     
     
     if(!setBaseline){
       // Calculate updated squared APE of current iteration
       double apeX2(999.);
       
       // old APE value from last iteration
       if(firstIter)apeX2 = 0.;
       else apeX2 = a_apeSector[(*i_sector).first];
       const double apeX2old = apeX2;
       
       // scale APE Correction with value given in cfg (not if smoothed iteration is used)
       edm::LogInfo("CalculateAPE")<<"Unscaled correction for sector "<<(*i_sector).first<<" is "<<(correctionX2>0 ? +1 : -1)*std::sqrt(std::fabs(correctionX2));
       if(!smoothIteration || firstIter)correctionX2 = correctionX2*correctionScaling*correctionScaling;

       // new APE value
       // smooth iteration or not?
       if(apeX2 + correctionX2 < 0.) correctionX2 = -apeX2;
       const double apeX2new(apeX2old + correctionX2);
       if(!smoothIteration || firstIter)apeX2 = apeX2new;
       else apeX2 = std::pow(smoothFraction*std::sqrt(apeX2new) + (1-smoothFraction)*std::sqrt(apeX2old), 2);
       if(apeX2<0.)edm::LogError("CalculateAPE")<<"\n\n\tBad APE, but why???\n\n\n";
       a_apeSector[(*i_sector).first] = apeX2;
       
       // Set the calculated APE spherical for all modules of the sector
       const double apeX(std::sqrt(apeX2));
       std::vector<unsigned int>::const_iterator i_rawId;
       for(i_rawId = (*i_sector).second.v_rawId.begin(); i_rawId != (*i_sector).second.v_rawId.end(); ++i_rawId){
         //std::cout<<*i_rawId<<" "<<std::fixed<<std::setprecision(5)<<apeX<<" "<<apeX<<" "<<apeX<<"\n";
	 apeOutputFile<<*i_rawId<<" "<<std::fixed<<std::setprecision(5)<<apeX<<" "<<apeX<<" "<<apeX<<"\n";
       }
     }
     // In setBaseline mode, just fill estimated mean value of residual width
     else{
       a_apeSector[(*i_sector).first] = correctionX2;
     }
     
   }
   if(!setBaseline)apeOutputFile.close();
   
   iterationTree->Fill();
   iterationTree->Write("iterTree", TObject::kOverwrite);  // TObject::kOverwrite needed to not produce another iterTree;2
   iterationFile->Close();
   
   if(baselineFile)baselineFile->Close();
}



// ------------ method called to for each event  ------------
void
ApeEstimatorSummary::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
}


// ------------ method called once each job just before starting event loop  ------------
void 
ApeEstimatorSummary::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ApeEstimatorSummary::endJob() {
  this->openInputFile();
  
  this->getTrackerSectorStructs();
  
  this->bookHists();
  
  this->calculateApe();
  
  this->writeHists();
  
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(ApeEstimatorSummary);
