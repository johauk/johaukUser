// -*- C++ -*-
//
// Package:    ApeEstimator
// Class:      ApeEstimator
// 
/**\class ApeEstimator ApeEstimator.cc ApeEstimator/ApeEstimator/src/ApeEstimator.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Johannes Hauk
//         Created:  Tue Jan  6 15:02:09 CET 2009
// $Id: ApeEstimator.cc,v 1.1 2009/11/26 16:14:13 hauk Exp $
//
//


// system include files
#include <memory>
#include <sstream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/UtilAlgos/interface/TFileDirectory.h"
//#include "CommonTools/Utils/interface/TFileDirectory.h" // not yet in release

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/CLHEP/interface/AlgebraicObjects.h"
#include "DataFormats/CLHEP/interface/Migration.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/TrackerRecHit2D/interface/SiStripRecHit2D.h"
#include "DataFormats/TrackerRecHit2D/interface/SiStripMatchedRecHit2D.h"
#include "DataFormats/TrackerRecHit2D/interface/ProjectedSiStripRecHit2D.h"
#include "DataFormats/TrackerRecHit2D/interface/SiPixelRecHit.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
//#include "DataFormats/GeometrySurface/interface/LocalError.h" // which one of LocalError.h to include ?
#include "DataFormats/GeometryCommonDetAlgo/interface/LocalError.h"
#include "DataFormats/GeometryCommonDetAlgo/interface/MeasurementPoint.h"
#include "DataFormats/GeometryCommonDetAlgo/interface/MeasurementError.h"
#include "DataFormats/SiPixelDetId/interface/PixelSubdetector.h"
#include "DataFormats/SiStripDetId/interface/StripSubdetector.h"
#include "DataFormats/SiStripDetId/interface/SiStripDetId.h"
#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h"
#include "DataFormats/SiStripCluster/interface/SiStripCluster.h"

#include "TrackingTools/PatternTools/interface/Trajectory.h"
#include "TrackingTools/PatternTools/interface/TrajTrackAssociation.h"
#include "TrackingTools/PatternTools/interface/TrajectoryMeasurement.h"
#include "TrackingTools/PatternTools/interface/MeasurementExtractor.h"
#include "TrackingTools/TrackFitters/interface/TrajectoryStateCombiner.h"
#include "TrackingTools/TransientTrackingRecHit/interface/TransientTrackingRecHit.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"

#include "Geometry/CommonDetUnit/interface/GeomDetUnit.h"
#include "Geometry/CommonTopologies/interface/RadialStripTopology.h"
#include "Geometry/TrackerGeometryBuilder/interface/StripGeomDetUnit.h"

#include "CondFormats/Alignment/interface/Definitions.h"

#include "AnalysisDataFormats/SiStripClusterInfo/interface/SiStripClusterInfo.h"
//#include "RecoLocalTracker/SiStripClusterizer/interface/SiStripClusterInfo.h" // not yet in release

#include "ApeEstimator/ApeEstimator/interface/TrackerSectorStruct.h"
#include "ApeEstimator/ApeEstimator/interface/TrackerDetectorStruct.h"
#include "ApeEstimator/ApeEstimator/interface/EventVariables.h"
#include "ApeEstimator/ApeEstimator/interface/ReducedTrackerTreeVariables.h"

#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TFile.h"
#include "TTree.h"
#include "TF1.h"
#include "TString.h"


//
// class decleration
//

class ApeEstimator : public edm::EDAnalyzer {
   public:
      explicit ApeEstimator(const edm::ParameterSet&);
      ~ApeEstimator();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob();
      
      bool isHit2D(const TrackingRecHit&)const;
      
      void sectorBuilder();
      bool checkIntervalsForSectors(const unsigned int sectorCounter, const std::vector<double>&)const;
      bool checkModuleIds(const unsigned int, const std::vector<unsigned int>&)const;
      bool checkModuleBools(const bool, const std::vector<unsigned int>&)const;
      bool checkModuleDirections(const int, const std::vector<int>&)const;
      bool checkModulePositions(const float, const std::vector<double>&)const;
      void statistics(const TrackerSectorStruct&, const Int_t)const;
      
      void residualErrorBinning();
      
      void bookSectorHists();
      void bookTrackHists();
      
      //TrackStruct::TrackParameterStruct fillTrackVariables(const reco::Track&, const Trajectory&)const;  // trackCut_ forbids const
      TrackStruct::TrackParameterStruct fillTrackVariables(const reco::Track&, const Trajectory&);
      TrackStruct::HitParameterStruct fillHitVariables(const TrajectoryMeasurement&, const edm::EventSetup&);
      
      void hitSelection();
      void setHitSelectionMap(const std::string&);
      void setHitSelectionMapUInt(const std::string&);
      bool hitSelected(const TrackStruct::HitParameterStruct&)const;
      
      void fillHists(const TrackStruct&);
      
      void calculateAPE();
      
      // ----------member data ---------------------------
      edm::ParameterSet theParameterSet;
      std::map<unsigned int, TrackerSectorStruct> mTkSector_;
      TrackerDetectorStruct tkDetector_;
      
      std::map<unsigned int, std::pair<double,double> > mResErrBins_;
      
      std::map<unsigned int, ReducedTrackerTreeVariables> mTkTreeVar_;
      
      std::map<std::string,std::vector<double> > mHitSelection_;
      std::map<std::string,std::vector<unsigned int> > mHitSelectionUInt_;
      
      bool trackCut_;
      
      const unsigned int maxTracksPerEvent_;
      const unsigned int minGoodHitsPerTrack_;
      
      unsigned int counter1, counter2, counter3, counter4, counter5, counter6;
      
      TH1* testHist;
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
ApeEstimator::ApeEstimator(const edm::ParameterSet& iConfig):
theParameterSet(iConfig), trackCut_(false), maxTracksPerEvent_(theParameterSet.getParameter<unsigned int>("maxTracksPerEvent")),
minGoodHitsPerTrack_(theParameterSet.getParameter<unsigned int>("minGoodHitsPerTrack"))
{
   counter1 = counter2 = counter3 = counter4 = counter5 = counter6 = 0;
}


ApeEstimator::~ApeEstimator()
{
}


//
// member functions
//

// -----------------------------------------------------------------------------------------------------------

void
ApeEstimator::sectorBuilder(){
  
  TFile* tkTreeFile(TFile::Open((theParameterSet.getParameter<std::string>("TrackerTreeFile")).c_str()));
  if(tkTreeFile){
    edm::LogInfo("SectorBuilder")<<"TrackerTreeFile OK";
  }else{
    edm::LogError("SectorBuilder")<<"TrackerTreeFile not found";
    return;
  }
  TTree* tkTree(0);
  tkTreeFile->GetObject("TrackerTreeGenerator/TrackerTree/TrackerTree",tkTree);
  if(tkTree){
    edm::LogInfo("SectorBuilder")<<"TrackerTree OK";
  }else{
    edm::LogError("SectorBuilder")<<"TrackerTree not found in file";
    return;
  }
  UInt_t rawId(999), subdetId(999), layer(999), side(999), half(999), rod(999), ring(999), petal(999),
         blade(999), panel(999), outerInner(999), module(999), rodAl(999), bladeAl(999), nStrips(999);
  Bool_t isDoubleSide(false), isRPhi(false);
  Int_t uDirection(999), vDirection(999), wDirection(999);
  Float_t posR(999.F), posPhi(999.F), posEta(999.F), posX(999.F), posY(999.F), posZ(999.F); 
  tkTree->SetBranchAddress("RawId", &rawId);
  tkTree->SetBranchAddress("SubdetId", &subdetId);
  tkTree->SetBranchAddress("Layer", &layer);
  tkTree->SetBranchAddress("Side", &side);
  tkTree->SetBranchAddress("Half", &half);
  tkTree->SetBranchAddress("Rod", &rod);
  tkTree->SetBranchAddress("Ring", &ring);
  tkTree->SetBranchAddress("Petal", &petal);
  tkTree->SetBranchAddress("Blade", &blade);
  tkTree->SetBranchAddress("Panel", &panel);
  tkTree->SetBranchAddress("OuterInner", &outerInner);
  tkTree->SetBranchAddress("Module", &module);
  tkTree->SetBranchAddress("RodAl", &rodAl);
  tkTree->SetBranchAddress("BladeAl", &bladeAl);
  tkTree->SetBranchAddress("NStrips", &nStrips);
  tkTree->SetBranchAddress("IsDoubleSide", &isDoubleSide);
  tkTree->SetBranchAddress("IsRPhi", &isRPhi);
  tkTree->SetBranchAddress("UDirection", &uDirection);
  tkTree->SetBranchAddress("VDirection", &vDirection);
  tkTree->SetBranchAddress("WDirection", &wDirection);
  tkTree->SetBranchAddress("PosR", &posR);
  tkTree->SetBranchAddress("PosPhi", &posPhi);
  tkTree->SetBranchAddress("PosEta", &posEta);
  tkTree->SetBranchAddress("PosX", &posX);
  tkTree->SetBranchAddress("PosY", &posY);
  tkTree->SetBranchAddress("PosZ", &posZ);
  
  Int_t nModules(tkTree->GetEntries());
  TrackerSectorStruct allSectors;
  
  //Loop over all Sectors
  unsigned int sectorCounter(1);
  std::vector<edm::ParameterSet> vSectors(theParameterSet.getParameter<std::vector<edm::ParameterSet> >("Sectors"));
  edm::LogInfo("SectorBuilder")<<"There are "<<vSectors.size()<<" Sectors definded";
  std::vector<edm::ParameterSet>::const_iterator iPSet;
  for(iPSet = vSectors.begin(); iPSet != vSectors.end();++iPSet, ++sectorCounter){
    const edm::ParameterSet& parSet = *iPSet;
    std::vector<unsigned int> vRawId(parSet.getParameter<std::vector<unsigned int> >("rawId")),
                              vSubdetId(parSet.getParameter<std::vector<unsigned int> >("subdetId")),
			      vLayer(parSet.getParameter<std::vector<unsigned int> >("layer")),
			      vSide(parSet.getParameter<std::vector<unsigned int> >("side")),
			      vHalf(parSet.getParameter<std::vector<unsigned int> >("half")),
			      vRod(parSet.getParameter<std::vector<unsigned int> >("rod")),
			      vRing(parSet.getParameter<std::vector<unsigned int> >("ring")),
			      vPetal(parSet.getParameter<std::vector<unsigned int> >("petal")),
                              vBlade(parSet.getParameter<std::vector<unsigned int> >("blade")),
			      vPanel(parSet.getParameter<std::vector<unsigned int> >("panel")),
			      vOuterInner(parSet.getParameter<std::vector<unsigned int> >("outerInner")),
			      vModule(parSet.getParameter<std::vector<unsigned int> >("module")),
			      vRodAl(parSet.getParameter<std::vector<unsigned int> >("rodAl")),
			      vBladeAl(parSet.getParameter<std::vector<unsigned int> >("bladeAl")),
			      vNStrips(parSet.getParameter<std::vector<unsigned int> >("nStrips")),
			      vIsDoubleSide(parSet.getParameter<std::vector<unsigned int> >("isDoubleSide")),
			      vIsRPhi(parSet.getParameter<std::vector<unsigned int> >("isRPhi"));
    std::vector<int> vUDirection(parSet.getParameter<std::vector<int> >("uDirection")),
                     vVDirection(parSet.getParameter<std::vector<int> >("vDirection")),
		     vWDirection(parSet.getParameter<std::vector<int> >("wDirection"));
    std::vector<double> vPosR(parSet.getParameter<std::vector<double> >("posR")),
                        vPosPhi(parSet.getParameter<std::vector<double> >("posPhi")),
			vPosEta(parSet.getParameter<std::vector<double> >("posEta")),
			vPosX(parSet.getParameter<std::vector<double> >("posX")),
			vPosY(parSet.getParameter<std::vector<double> >("posY")),
			vPosZ(parSet.getParameter<std::vector<double> >("posZ"));
    //if(vPosR.size()%2 == 1 || vPosPhi.size()%2 == 1 || vPosEta.size()%2 == 1 || 
    //   vPosX.size()%2 == 1 || vPosY.size()%2 == 1 || vPosZ.size()%2 == 1){
    //   edm::LogError("SectorBuilder")<<"Incorrect Sector Definition: Position Vectors need even number of arguments (Intervals)"
    //                                 <<"\n... sector selection is not applied, no sectors are built";
    //   return;
    //}
    if(!this->checkIntervalsForSectors(sectorCounter,vPosR) || !this->checkIntervalsForSectors(sectorCounter,vPosPhi) ||
       !this->checkIntervalsForSectors(sectorCounter,vPosEta) || !this->checkIntervalsForSectors(sectorCounter,vPosX) ||
       !this->checkIntervalsForSectors(sectorCounter,vPosY)   || !this->checkIntervalsForSectors(sectorCounter,vPosZ))continue;
    
    
    
    TrackerSectorStruct tkSector;
    ReducedTrackerTreeVariables tkTreeVar;
    
    //Loop over all Modules
    for(Int_t iMod = 0; iMod < nModules; ++iMod){
      tkTree->GetEntry(iMod);
      
      if(sectorCounter==1){
        tkTreeVar.subdetId = subdetId;
        tkTreeVar.nStrips = nStrips;
	tkTreeVar.uDirection = uDirection;
        tkTreeVar.vDirection = vDirection;
        tkTreeVar.wDirection = wDirection;
	mTkTreeVar_[rawId] = tkTreeVar;
      }
      
      if(!this->checkModuleIds(rawId,vRawId))continue;
      if(!this->checkModuleIds(subdetId,vSubdetId))continue;
      if(!this->checkModuleIds(layer,vLayer))continue;
      if(!this->checkModuleIds(side,vSide))continue;
      if(!this->checkModuleIds(half,vHalf))continue;
      if(!this->checkModuleIds(rod,vRod))continue;
      if(!this->checkModuleIds(ring,vRing))continue;
      if(!this->checkModuleIds(petal,vPetal))continue;
      if(!this->checkModuleIds(blade,vBlade))continue;
      if(!this->checkModuleIds(panel,vPanel))continue;
      if(!this->checkModuleIds(outerInner,vOuterInner))continue;
      if(!this->checkModuleIds(module,vModule))continue;
      if(!this->checkModuleIds(rodAl,vRodAl))continue;
      if(!this->checkModuleIds(bladeAl,vBladeAl))continue;
      if(!this->checkModuleIds(nStrips,vNStrips))continue;
      if(!this->checkModuleBools(isDoubleSide,vIsDoubleSide))continue;
      if(!this->checkModuleBools(isRPhi,vIsRPhi))continue;
      if(!this->checkModuleDirections(uDirection,vUDirection))continue;
      if(!this->checkModuleDirections(vDirection,vVDirection))continue;
      if(!this->checkModuleDirections(wDirection,vWDirection))continue;
      if(!this->checkModulePositions(posR,vPosR))continue;
      if(!this->checkModulePositions(posPhi,vPosPhi))continue;
      if(!this->checkModulePositions(posEta,vPosEta))continue;
      if(!this->checkModulePositions(posX,vPosX))continue;
      if(!this->checkModulePositions(posY,vPosY))continue;
      if(!this->checkModulePositions(posZ,vPosZ))continue;
      
      tkSector.vRawId.push_back(rawId);
      bool moduleSelected(false);
      for(std::vector<unsigned int>::const_iterator iRawId = allSectors.vRawId.begin();
          iRawId != allSectors.vRawId.end(); ++iRawId){
        if(rawId == *iRawId)moduleSelected = true;
      }
      if(!moduleSelected)allSectors.vRawId.push_back(rawId);
    }
    mTkSector_[sectorCounter] = tkSector;
    edm::LogInfo("SectorBuilder")<<"There are "<<tkSector.vRawId.size()<<" Modules in Sector "<<sectorCounter;
  }
  this->statistics(allSectors, nModules);
  return;
}



// -----------------------------------------------------------------------------------------------------------


bool
ApeEstimator::checkIntervalsForSectors(const unsigned int sectorCounter, const std::vector<double>& vId)const{
  if(vId.size()==0)return true;
  if(vId.size()%2==1){
    edm::LogError("SectorBuilder")<<"Incorrect Sector Definition: Position Vectors need even number of arguments (Intervals)"
                                     <<"\n... sector selection is not applied, sector "<<sectorCounter<<" is not built";
    return false;
  }
  int iEntry(1); double intervalBegin(999.);
  for(std::vector<double>::const_iterator iId = vId.begin(); iId != vId.end(); ++iId, ++iEntry){
    if(iEntry%2==1)intervalBegin = *iId;
    if(iEntry%2==0 && intervalBegin>*iId){
      edm::LogError("SectorBuilder")<<"Incorrect Sector Definition (Position Vector Intervals): \t"
                                    <<intervalBegin<<" is bigger than "<<*iId<<" but is expected to be smaller"
                                    <<"\n... sector selection is not applied,  sector "<<sectorCounter<<" is not built";
      return false;
    }
  }
  return true;
}

bool
ApeEstimator::checkModuleIds(const unsigned int id, const std::vector<unsigned int>& vId)const{
  if(vId.size()==0)return true;
  for(std::vector<unsigned int>::const_iterator iId = vId.begin(); iId != vId.end(); ++iId){
    if(id==*iId)return true;
  }
  return false;
}

bool
ApeEstimator::checkModuleBools(const bool id, const std::vector<unsigned int>& vId)const{
  if(vId.size()==0)return true;
  for(std::vector<unsigned int>::const_iterator iId = vId.begin(); iId != vId.end(); ++iId){
    if(1==*iId && id)return true;
    if(2==*iId && !id)return true;
  }
  return false;
}

bool
ApeEstimator::checkModuleDirections(const int id, const std::vector<int>& vId)const{
  if(vId.size()==0)return true;
  for(std::vector<int>::const_iterator iId = vId.begin(); iId != vId.end(); ++iId){
    if(id==*iId)return true;
  }
  return false;
}

bool
ApeEstimator::checkModulePositions(const float id, const std::vector<double>& vId)const{
  if(vId.size()==0)return true;
  int iEntry(1); double intervalBegin(999.);
  for(std::vector<double>::const_iterator iId = vId.begin(); iId != vId.end(); ++iId, ++iEntry){
    if(iEntry%2==1)intervalBegin = *iId;
    if(iEntry%2==0 && id>=intervalBegin && id<*iId)return true;
  }
  return false;
}

void
ApeEstimator::statistics(const TrackerSectorStruct& allSectors, const Int_t nModules)const{
  for(std::map<unsigned int,TrackerSectorStruct>::const_iterator iSec = mTkSector_.begin(); iSec != mTkSector_.end(); ++iSec){
    int nCommonModules(0);
    std::map<unsigned int,TrackerSectorStruct>::const_iterator iSec2(iSec);
    for(++iSec2; iSec2 != mTkSector_.end(); ++iSec2){
      for(std::vector<unsigned int>::const_iterator iMod = (*iSec).second.vRawId.begin(); iMod != (*iSec).second.vRawId.end(); ++iMod){
        for(std::vector<unsigned int>::const_iterator iMod2 = (*iSec2).second.vRawId.begin(); iMod2 != (*iSec2).second.vRawId.end(); ++iMod2){
          if(*iMod2 == *iMod)++nCommonModules;
        }
      }
      if(nCommonModules==0)
      edm::LogInfo("SectorBuilder")<<"Sector "<<(*iSec).first<<" and Sector "<<(*iSec2).first<< " have ZERO Modules in common";
      else
      edm::LogWarning("SectorBuilder")<<"Sector "<<(*iSec).first<<" and Sector "<<(*iSec2).first<< " have "<<nCommonModules<<" Modules in common";
    }
  }
  if(static_cast<int>(allSectors.vRawId.size())==nModules)
  edm::LogInfo("SectorBuilder")<<"ALL Tracker Modules are contained in the Sectors";
  else
  edm::LogWarning("SectorBuilder")<<"There are "<<allSectors.vRawId.size()<<" Modules in all Sectors"
                               <<" out of "<<nModules<<" Tracker Modules";
}


// -----------------------------------------------------------------------------------------------------------


void
ApeEstimator::residualErrorBinning(){
   std::vector<double> vResidualErrorBinning(theParameterSet.getParameter<std::vector<double> >("residualErrorBinning"));
   if(vResidualErrorBinning.size()==1){
     edm::LogError("ResidualErrorBinning")<<"Incorrect selection of Residual Error Bins (used for APE calculation): \t"
                                          <<"Only one argument passed, so no interval is specified"
					  <<"\n... delete whole bin selection";    //mResErrBins_ remains empty
     return;
   }
   double xMin(0.), xMax(0.);
   unsigned int binCounter(0);
   for(std::vector<double>::const_iterator iVec = vResidualErrorBinning.begin(); iVec != vResidualErrorBinning.end(); ++iVec, ++binCounter){
     if(binCounter == 0){xMin = *iVec;continue;}
     xMax = *iVec;
     if(xMax<=xMin){
       edm::LogError("ResidualErrorBinning")<<"Incorrect selection of Residual Error Bins (used for APE calculation): \t"
                                            <<xMin<<" is bigger than "<<xMax<<" but is expected to be smaller"
					    <<"\n... delete whole bin selection";
       mResErrBins_.clear();
       return;
     }
     mResErrBins_[binCounter].first = xMin;
     mResErrBins_[binCounter].second = xMax;
     xMin = xMax;
   }
   edm::LogInfo("ResidualErrorBinning")<<mResErrBins_.size()<<" Intervals of residual errors used for separate APE calculation sucessfully set";
}



// -----------------------------------------------------------------------------------------------------------



void
ApeEstimator::bookSectorHists(){
  
  std::vector<unsigned int> vErrHists(theParameterSet.getParameter<std::vector<unsigned int> >("vErrHists"));
  for(std::vector<unsigned int>::iterator iErrHists = vErrHists.begin(); iErrHists != vErrHists.end(); ++iErrHists){
    for(std::vector<unsigned int>::iterator iErrHists2 = iErrHists; iErrHists2 != vErrHists.end();){
      ++iErrHists2;
      if(*iErrHists==*iErrHists2){
        edm::LogError("BookSectorHists")<<"Value of vErrHists in config exists twice: "<<*iErrHists<<"\n... delete one of both";
        vErrHists.erase(iErrHists2);
      }
    }
  }
  
  for(std::map<unsigned int,TrackerSectorStruct>::iterator iSec = mTkSector_.begin(); iSec != mTkSector_.end(); ++iSec){
    if((*iSec).second.vRawId.size()==0)continue;
    
    bool zoomHists(theParameterSet.getParameter<bool>("zoomHists"));
    
    int widthMax = zoomHists ? 20 : 200;
    double chargeMax = zoomHists ? 1000. : 10000.;
    double sOverNMax = zoomHists? 200. : 2000.;
    
    double resXAbsMax = zoomHists ? 0.5 : 5.;
    double norResXAbsMax = zoomHists ? 10. : 50.;
    double sigmaXMin = zoomHists ? 0. : -0.05;
    double sigmaXMax = zoomHists ? 0.1 : 1.;
    double sigmaX2Max = sigmaXMax*sigmaXMax;
    double sigmaXHitMax = zoomHists ? 0.02 : 1.;
    
    double pMax = zoomHists ? 100. : 5000.;
    double invPMax = zoomHists ? 0.05 : 10.;   //begins at 20GeV, 0.1GeV
    double norChi2Max = zoomHists ? 20. : 1000.;
    
    
    edm::Service<TFileService> fileService;
    
    std::stringstream sector; sector << "Sector_" << (*iSec).first;
    TFileDirectory secDir = fileService->mkdir(sector.str().c_str());
    
    (*iSec).second.IsModuleUsable = secDir.make<TH1F>("h_isModuleUsable","is module usable;;# hits",4,-1,3);
    (*iSec).second.Width          = secDir.make<TH1F>("h_width","cluster width w_{cl};w_{cl}  [# strips];# hits",widthMax,0,widthMax);
    (*iSec).second.Charge         = secDir.make<TH1F>("h_charge","cluster charge c_{cl};c_{cl}  [APV counts];# hits",100,0,chargeMax);
    (*iSec).second.ChargeLR       = secDir.make<TH1F>("h_chargeLR","cluster surround charge c_{cl,LR};c_{cl,LR}  [APV counts];# hits",100,0,chargeMax);
    (*iSec).second.MaxStrip       = secDir.make<TH1F>("h_maxStrip","strip with max. charge n_{cl,max};n_{cl,max}  [# strips];# hits",800,-10,790);
    (*iSec).second.MaxCharge      = secDir.make<TH1F>("h_maxCharge","charge of strip with max. charge c_{cl,max};c_{cl,max}  [APV counts];# hits",100,-10,290);
    (*iSec).second.MaxIndex       = secDir.make<TH1F>("h_maxIndex","cluster-index of strip with max. charge i_{cl,max};i_{cl,max}  [# strips];# hits",10,0,10);
    (*iSec).second.BaryStrip      = secDir.make<TH1F>("h_baryStrip","barycenter of cluster charge b_{cl};b_{cl}  [# strips];# hits",800,-10,790);
    (*iSec).second.SOverN         = secDir.make<TH1F>("h_sOverN","signal over noise s/N;s/N;# hits",100,0,sOverNMax);
    
    (*iSec).second.ResX      = secDir.make<TH1F>("h_resX","residual r_{x};(x_{track}-x_{hit})'  [cm];# hits",100,-resXAbsMax,resXAbsMax);
    (*iSec).second.NorResX   = secDir.make<TH1F>("h_norResX","normalized residual r_{x}/#sigma_{x};(x_{track}-x_{hit})'/#sigma_{x};# hits",100,-norResXAbsMax,norResXAbsMax);
    (*iSec).second.XHit      = secDir.make<TH1F>("h_xHit"," hit measurement x_{hit};x_{hit}  [cm];# hits",100,-20,20);
    (*iSec).second.XTrk      = secDir.make<TH1F>("h_xTrk","track prediction x_{track};x_{track}  [cm];# hits",100,-20,20);
    
    (*iSec).second.SigmaXHit = secDir.make<TH1F>("h_sigmaXHit","hit error #sigma_{x,hit};#sigma_{x,hit}  [cm];# hits",105,sigmaXMin,sigmaXMax);
    (*iSec).second.SigmaXTrk = secDir.make<TH1F>("h_sigmaXTrk","track error #sigma_{x,track};#sigma_{x,track}  [cm];# hits",105,sigmaXMin,sigmaXMax);
    (*iSec).second.SigmaX    = secDir.make<TH1F>("h_sigmaX","residual error #sigma_{x};#sigma_{x}  [cm];# hits",105,sigmaXMin,sigmaXMax);
    (*iSec).second.SigmaX2   = secDir.make<TH1F>("h_sigmaX2","squared residual error #sigma_{x}^{2};#sigma_{x}^{2}  [cm^{2}];# hits",105,sigmaXMin,sigmaX2Max); //no mistake !
    
    (*iSec).second.PhiSens   = secDir.make<TH1F>("h_phiSens" ,"track angle on sensor #phi_{module};#phi_{module}  [ ^{o}];# hits"    ,94,-2,92);
    (*iSec).second.PhiSensX  = secDir.make<TH1F>("h_phiSensX","track angle on sensor #phi_{x,module};#phi_{x,module}  [ ^{o}];# hits",184,-92,92);
    (*iSec).second.PhiSensY  = secDir.make<TH1F>("h_phiSensY","track angle on sensor #phi_{y,module};#phi_{y,module}  [ ^{o}];# hits",184,-92,92);
    
    (*iSec).second.NorResXVsWidth          = secDir.make<TH2F>("h2_norResXVsWidth","r_{x}/#sigma_{x} vs. w_{cl};w_{cl}  [# strips];(x_{track}-x_{hit})'/#sigma_{x}",widthMax,0,widthMax,25,-norResXAbsMax,norResXAbsMax);
    (*iSec).second.NorResXVsCharge         = secDir.make<TH2F>("h2_norResXVsCharge","r_{x}/#sigma_{x} vs. c_{cl};c_{cl}  [APV counts];(x_{track}-x_{hit})'/#sigma_{x}",100,0,chargeMax,25,-norResXAbsMax,norResXAbsMax);
    (*iSec).second.NorResXVsChargeLR       = secDir.make<TH2F>("h2_norResXVsChargeLR","r_{x}/#sigma_{x} vs. c_{cl,LR};c_{cl,LR}  [APV counts];(x_{track}-x_{hit})'/#sigma_{x}",100,0,chargeMax,25,-norResXAbsMax,norResXAbsMax);
    (*iSec).second.NorResXVsMaxStrip       = secDir.make<TH2F>("h2_norResXVsMaxStrip","r_{x}/#sigma_{x} vs. n_{cl,max};n_{cl,max}  [# strips];(x_{track}-x_{hit})'/#sigma_{x}",800,-10,790,25,-norResXAbsMax,norResXAbsMax);
    (*iSec).second.NorResXVsMaxCharge      = secDir.make<TH2F>("h2_norResXVsMaxCharge","r_{x}/#sigma_{x} vs. c_{cl,max};c_{cl,max}  [APV counts];(x_{track}-x_{hit})'/#sigma_{x}",100,-10,290,25,-norResXAbsMax,norResXAbsMax);
    (*iSec).second.NorResXVsMaxIndex       = secDir.make<TH2F>("h2_norResXVsMaxIndex","r_{x}/#sigma_{x} vs. i_{cl,max};i_{cl,max}  [# strips];(x_{track}-x_{hit})'/#sigma_{x}",10,0,10,25,-norResXAbsMax,norResXAbsMax);
    (*iSec).second.NorResXVsBaryStrip      = secDir.make<TH2F>("h2_norResXVsBaryStrip","r_{x}/#sigma_{x} vs. b_{cl};b_{cl}  [# strips];(x_{track}-x_{hit})'/#sigma_{x}",100,-10,790,25,-norResXAbsMax,norResXAbsMax);
    (*iSec).second.NorResXVsSOverN         = secDir.make<TH2F>("h2_norResXVsSOverN","r_{x}/#sigma_{x} vs. s/N;s/N;(x_{track}-x_{hit})'/#sigma_{x}",100,0,sOverNMax,25,-norResXAbsMax,norResXAbsMax);
    
    (*iSec).second.NorResXVsP              = secDir.make<TH2F>("h2_norResXVsP","r_{x}/#sigma_{x} vs. |p|;|p|  [GeV];(x_{track}-x_{hit})'/#sigma_{x}",50,0,pMax,25,-norResXAbsMax,norResXAbsMax);
    (*iSec).second.NorResXVsMeanAngle      = secDir.make<TH2F>("h2_norResXVsMeanAngle","r_{x}/#sigma_{x} vs. <#phi_{module}>;<#phi_{module}>  [ ^{o}];(x_{track}-x_{hit})'/#sigma_{x}",25,-5,95,25,-norResXAbsMax,norResXAbsMax);
    (*iSec).second.NorResXVsHitsValid      = secDir.make<TH2F>("h2_norResXVsHitsValid","r_{x}/#sigma_{x} vs. # hits  [valid];# hits  [valid];(x_{track}-x_{hit})'/#sigma_{x}",50,0,50,25,-norResXAbsMax,norResXAbsMax);
    (*iSec).second.NorResXVsHitsGood       = secDir.make<TH2F>("h2_norResXVsHitsGood","r_{x}/#sigma_{x} vs. # hits  [good];# hits  [good];(x_{track}-x_{hit})'/#sigma_{x}",50,0,50,25,-norResXAbsMax,norResXAbsMax);
    (*iSec).second.NorResXVsHitsInvalid    = secDir.make<TH2F>("h2_norResXVsHitsInvalid","r_{x}/#sigma_{x} vs. # hits  [invalid];# hits  [invalid];(x_{track}-x_{hit})'/#sigma_{x}",20,0,20,25,-norResXAbsMax,norResXAbsMax);
    (*iSec).second.NorResXVsLayersMissed   = secDir.make<TH2F>("h2_norResXVsLayersMissed","r_{x}/#sigma_{x} vs. # layers  [missed];# layers  [missed];(x_{track}-x_{hit})'/#sigma_{x}",10,0,10,25,-norResXAbsMax,norResXAbsMax);
    (*iSec).second.NorResXVsNorChi2        = secDir.make<TH2F>("h2_norResXVsNorChi2","r_{x}/#sigma_{x} vs. #chi^{2}/ndof;#chi^{2}/ndof;(x_{track}-x_{hit})'/#sigma_{x}",50,0,norChi2Max,25,-norResXAbsMax,norResXAbsMax);
    
    (*iSec).second.NorResXVsPhiSens        = secDir.make<TH2F>("h2_norResXVsPhiSens","r_{x}/#sigma_{x} vs. #phi_{module};#phi_{module}  [ ^{o}];(x_{track}-x_{hit})'/#sigma_{x}",47,-2,92,25,-norResXAbsMax,norResXAbsMax);
    (*iSec).second.NorResXVsPhiSensX       = secDir.make<TH2F>("h2_norResXVsPhiSensX","r_{x}/#sigma_{x} vs. #phi_{x,module};#phi_{x,module}  [ ^{o}];(x_{track}-x_{hit})'/#sigma_{x}",92,-92,92,25,-norResXAbsMax,norResXAbsMax);
    (*iSec).second.NorResXVsPhiSensY       = secDir.make<TH2F>("h2_norResXVsPhiSensY","r_{x}/#sigma_{x} vs. #phi_{y,module};#phi_{y,module}  [ ^{o}];(x_{track}-x_{hit})'/#sigma_{x}",92,-92,92,25,-norResXAbsMax,norResXAbsMax);
    
    (*iSec).second.SigmaXHitVsWidth        = secDir.make<TH2F>("h2_sigmaXHitVsWidth","#sigma_{x,hit} vs. w_{cl};w_{cl}  [# strips];#sigma_{x,hit}  [cm]",widthMax,0,widthMax,100,0,sigmaXHitMax);
    (*iSec).second.SigmaXHitVsCharge       = secDir.make<TH2F>("h2_sigmaXHitVsCharge","#sigma_{x,hit} vs. c_{cl};c_{cl}  [APV counts];#sigma_{x,hit}  [cm]",100,0,chargeMax,100,0,sigmaXHitMax);
    (*iSec).second.SigmaXHitVsChargeLR     = secDir.make<TH2F>("h2_sigmaXHitVsChargeLR","#sigma_{x,hit} vs. c_{cl,LR};c_{cl,LR}  [APV counts];#sigma_{x,hit}  [cm]",100,0,chargeMax,100,0,sigmaXHitMax);
    (*iSec).second.SigmaXHitVsMaxStrip     = secDir.make<TH2F>("h2_sigmaXHitVsMaxStrip","#sigma_{x,hit} vs. n_{cl,max};n_{cl,max}  [# strips];#sigma_{x,hit}  [cm]",800,-10,790,100,0,sigmaXHitMax);
    (*iSec).second.SigmaXHitVsMaxCharge    = secDir.make<TH2F>("h2_sigmaXHitVsMaxCharge","#sigma_{x,hit} vs. c_{cl,max};c_{cl,max}  [APV counts];#sigma_{x,hit}  [cm]",100,-10,290,100,0,sigmaXHitMax);
    (*iSec).second.SigmaXHitVsMaxIndex     = secDir.make<TH2F>("h2_sigmaXHitVsMaxIndex","#sigma_{x,hit} vs. i_{cl,max};i_{cl,max}  [# strips];#sigma_{x,hit}  [cm]",10,0,10,100,0,sigmaXHitMax);
    (*iSec).second.SigmaXHitVsBaryStrip    = secDir.make<TH2F>("h2_sigmaXHitVsBaryStrip","#sigma_{x,hit} vs. b_{cl};b_{cl}  [# strips];#sigma_{x,hit}  [cm]",100,-10,790,100,0,sigmaXHitMax);
    (*iSec).second.SigmaXHitVsSOverN       = secDir.make<TH2F>("h2_sigmaXHitVsSOverN","#sigma_{x,hit} vs. s/N;s/N;#sigma_{x,hit}  [cm]",100,0,sOverNMax,100,0,sigmaXHitMax);
    
    (*iSec).second.SigmaXTrkVsP            = secDir.make<TH2F>("h2_sigmaXTrkVsP","#sigma_{x,track} vs. |p|;|p|  [GeV];#sigma_{x,track}  [cm]",50,0,pMax,25,0,1);
    (*iSec).second.SigmaXTrkVsInvP         = secDir.make<TH2F>("h2_sigmaXTrkVsInvP","#sigma_{x,track} vs. 1/|p|;1/|p|  [GeV^{-1}];#sigma_{x,track}  [cm]",25,0,invPMax,25,0,1);
    (*iSec).second.SigmaXTrkVsMeanAngle    = secDir.make<TH2F>("h2_sigmaXTrkVsMeanAngle","#sigma_{x,track} vs. <#phi_{module}>;<#phi_{module}>  [ ^{o}];#sigma_{x,track}  [cm]",25,-5,95,25,0,1);
    (*iSec).second.SigmaXTrkVsHitsValid    = secDir.make<TH2F>("h2_sigmaXTrkVsHitsValid","#sigma_{x,track} vs. # hits  [valid];# hits  [valid];#sigma_{x,track}  [cm]",50,0,50,25,0,1);
    (*iSec).second.SigmaXTrkVsHitsGood     = secDir.make<TH2F>("h2_sigmaXTrkVsHitsGood","#sigma_{x,track} vs. # hits  [good];# hits  [good];#sigma_{x,track}  [cm]",50,0,50,25,0,1);
    (*iSec).second.SigmaXTrkVsHitsInvalid  = secDir.make<TH2F>("h2_sigmaXTrkVsHitsInvalid","#sigma_{x,track} vs. # hits  [invalid];# hits  [invalid];#sigma_{x,track}  [cm]",20,0,20,25,0,1);
    (*iSec).second.SigmaXTrkVsLayersMissed = secDir.make<TH2F>("h2_sigmaXTrkVsLayersMissed","#sigma_{x,track} vs. # layers  [missed];# layers  [missed];#sigma_{x,track}  [cm]",10,0,10,25,0,1);
    (*iSec).second.SigmaXVsNorChi2         = secDir.make<TH2F>("h2_sigmaXVsNorChi2","#sigma_{x} vs. #chi^{2}/ndof;#chi^{2}/ndof;#sigma_{x}  [cm]",50,0,norChi2Max,25,0,1);
    
    (*iSec).second.SigmaXHitVsPhiSens      = secDir.make<TH2F>("h2_sigmaXHitVsPhiSens" ,"#sigma_{x,hit} vs. #phi_{module};#phi_{module}  [ ^{o}];#sigma_{x,hit}  [cm]",47,-2,92,50,0,sigmaXHitMax);
    (*iSec).second.SigmaXHitVsPhiSensX     = secDir.make<TH2F>("h2_sigmaXHitVsPhiSensX","#sigma_{x,hit} vs. #phi_{x,module};#phi_{x,module}  [ ^{o}];#sigma_{x,hit}  [cm]",92,-92,92,50,0,sigmaXHitMax);
    (*iSec).second.SigmaXHitVsPhiSensY     = secDir.make<TH2F>("h2_sigmaXHitVsPhiSensY","#sigma_{x,hit} vs. #phi_{y,module};#phi_{y,module}  [ ^{o}];#sigma_{x,hit}  [cm]",92,-92,92,50,0,sigmaXHitMax);
    (*iSec).second.SigmaXTrkVsPhiSens      = secDir.make<TH2F>("h2_sigmaXTrkVsPhiSens" ,"#sigma_{x,track} vs. #phi_{module};#phi_{module}  [ ^{o}];#sigma_{x,track}  [cm]",47,-2,92,50,0,1);
    (*iSec).second.SigmaXTrkVsPhiSensX     = secDir.make<TH2F>("h2_sigmaXTrkVsPhiSensX","#sigma_{x,track} vs. #phi_{x,module};#phi_{x,module}  [ ^{o}];#sigma_{x,track}  [cm]",92,-92,92,50,0,1);
    (*iSec).second.SigmaXTrkVsPhiSensY     = secDir.make<TH2F>("h2_sigmaXTrkVsPhiSensY","#sigma_{x,track} vs. #phi_{y,module};#phi_{y,module}  [ ^{o}];#sigma_{x,track}  [cm]",92,-92,92,50,0,1);
    (*iSec).second.SigmaXVsPhiSens         = secDir.make<TH2F>("h2_sigmaXVsPhiSens" ,"#sigma_{x} vs. #phi_{module};#phi_{module}  [ ^{o}];#sigma_{x,track}  [cm]",47,-2,92,50,0,1);
    (*iSec).second.SigmaXVsPhiSensX        = secDir.make<TH2F>("h2_sigmaXVsPhiSensX","#sigma_{x} vs. #phi_{x,module};#phi_{x,module}  [ ^{o}];#sigma_{x}  [cm]",92,-92,92,50,0,1);
    (*iSec).second.SigmaXVsPhiSensY        = secDir.make<TH2F>("h2_sigmaXVsPhiSensY","#sigma_{x} vs. #phi_{y,module};#phi_{y,module}  [ ^{o}];#sigma_{x}  [cm]",92,-92,92,50,0,1);
    
    (*iSec).second.NorResXVsSigmaXHit      = secDir.make<TH2F>("h2_norResXVsSigmaXHit","r_{x}/#sigma_{x} vs. #sigma_{x,hit};#sigma_{x,hit}  [cm];(x_{track}-x_{hit})'/#sigma_{x}",20,0,0.01,25,-norResXAbsMax,norResXAbsMax);
    (*iSec).second.NorResXVsSigmaXTrk      = secDir.make<TH2F>("h2_norResXVsSigmaXTrk","r_{x}/#sigma_{x} vs. #sigma_{x,track};#sigma_{x,track}  [cm];(x_{track}-x_{hit})'/#sigma_{x}",20,0,0.01,25,-norResXAbsMax,norResXAbsMax);
    (*iSec).second.NorResXVsSigmaX         = secDir.make<TH2F>("h2_norResXVsSigmaX","r_{x}/#sigma_{x} vs. #sigma_{x};#sigma_{x}  [cm];(x_{track}-x_{hit})'/#sigma_{x}",20,0,0.01,25,-norResXAbsMax,norResXAbsMax);
    
    (*iSec).second.WidthVsPhiSensX         = secDir.make<TH2F>("h2_widthVsPhiSensX","w_{cl} vs. #phi_{x,module};#phi_{x,module}  [ ^{o}];w_{cl}  [# strips]",92,-92,92,widthMax,0,widthMax);
    
    (*iSec).second.PNorResXVsWidth          = secDir.make<TProfile>("p_norResXVsWidth","r_{x}/#sigma_{x} vs. w_{cl};w_{cl}  [# strips];(x_{track}-x_{hit})'/#sigma_{x}",widthMax,0,widthMax,"s");
    (*iSec).second.PNorResXVsCharge         = secDir.make<TProfile>("p_norResXVsCharge","r_{x}/#sigma_{x} vs. c_{cl};c_{cl}  [APV counts];(x_{track}-x_{hit})'/#sigma_{x}",100,0,chargeMax,"s");
    (*iSec).second.PNorResXVsChargeLR       = secDir.make<TProfile>("p_norResXVsChargeLR","r_{x}/#sigma_{x} vs. c_{cl,LR};c_{cl,LR}  [APV counts];(x_{track}-x_{hit})'/#sigma_{x}",100,0,chargeMax,"s");
    (*iSec).second.PNorResXVsMaxStrip       = secDir.make<TProfile>("p_norResXVsMaxStrip","r_{x}/#sigma_{x} vs. n_{cl,max};n_{cl,max}  [# strips];(x_{track}-x_{hit})'/#sigma_{x}",800,-10,790,"s");
    (*iSec).second.PNorResXVsMaxCharge      = secDir.make<TProfile>("p_norResXVsMaxCharge","r_{x}/#sigma_{x} vs. c_{cl,max};c_{cl,max}  [APV counts];(x_{track}-x_{hit})'/#sigma_{x}",100,-10,290,"s");
    (*iSec).second.PNorResXVsMaxIndex       = secDir.make<TProfile>("p_norResXVsMaxIndex","r_{x}/#sigma_{x} vs. i_{cl,max};i_{cl,max}  [# strips];(x_{track}-x_{hit})'/#sigma_{x}",10,0,10,"s");
    (*iSec).second.PNorResXVsBaryStrip      = secDir.make<TProfile>("p_norResXVsBaryStrip","r_{x}/#sigma_{x} vs. b_{cl};b_{cl}  [# strips];(x_{track}-x_{hit})'/#sigma_{x}",100,-10,790,"s");
    (*iSec).second.PNorResXVsSOverN         = secDir.make<TProfile>("p_norResXVsSOverN","r_{x}/#sigma_{x} vs. s/N;s/N;(x_{track}-x_{hit})'/#sigma_{x}",100,0,sOverNMax,"s");
    
    (*iSec).second.PNorResXVsP              = secDir.make<TProfile>("p_norResXVsP","r_{x}/#sigma_{x} vs. |p|;|p|  [GeV];(x_{track}-x_{hit})'/#sigma_{x}",50,0,pMax,"s");
    (*iSec).second.PNorResXVsMeanAngle      = secDir.make<TProfile>("p_norResXVsMeanAngle","r_{x}/#sigma_{x} vs. <#phi_{module}>;<#phi_{module}>  [ ^{o}];(x_{track}-x_{hit})'/#sigma_{x}",25,-5,95,"s");
    (*iSec).second.PNorResXVsHitsValid      = secDir.make<TProfile>("p_norResXVsHitsValid","r_{x}/#sigma_{x} vs. # hits  [valid];# hits  [valid];(x_{track}-x_{hit})'/#sigma_{x}",50,0,50,"s");
    (*iSec).second.PNorResXVsHitsGood       = secDir.make<TProfile>("p_norResXVsHitsGood","r_{x}/#sigma_{x} vs. # hits  [good];# hits  [good];(x_{track}-x_{hit})'/#sigma_{x}",50,0,50,"s");
    (*iSec).second.PNorResXVsHitsInvalid    = secDir.make<TProfile>("p_norResXVsHitsInvalid","r_{x}/#sigma_{x} vs. # hits  [invalid];# hits  [invalid];(x_{track}-x_{hit})'/#sigma_{x}",20,0,20,"s");
    (*iSec).second.PNorResXVsLayersMissed   = secDir.make<TProfile>("p_norResXVsLayersMissed","r_{x}/#sigma_{x} vs. # layers  [missed];# layers  [missed];(x_{track}-x_{hit})'/#sigma_{x}",10,0,10,"s");
    (*iSec).second.PNorResXVsNorChi2        = secDir.make<TProfile>("p_norResXVsNorChi2","r_{x}/#sigma_{x} vs. #chi^{2}/ndof;#chi^{2}/ndof;(x_{track}-x_{hit})'/#sigma_{x}",50,0,norChi2Max,"s");
    
    (*iSec).second.PNorResXVsPhiSens        = secDir.make<TProfile>("p_norResXVsPhiSens","r_{x}/#sigma_{x} vs. #phi_{module};#phi_{module}  [ ^{o}];(x_{track}-x_{hit})'/#sigma_{x}",47,-2,92,"s");
    (*iSec).second.PNorResXVsPhiSensX       = secDir.make<TProfile>("p_norResXVsPhiSensX","r_{x}/#sigma_{x} vs. #phi_{x,module};#phi_{x,module}  [ ^{o}];(x_{track}-x_{hit})'/#sigma_{x}",92,-92,92,"s");
    (*iSec).second.PNorResXVsPhiSensY       = secDir.make<TProfile>("p_norResXVsPhiSensY","r_{x}/#sigma_{x} vs. #phi_{y,module};#phi_{y,module}  [ ^{o}];(x_{track}-x_{hit})'/#sigma_{x}",92,-92,92,"s");
    
    (*iSec).second.PSigmaXHitVsWidth        = secDir.make<TProfile>("p_sigmaXHitVsWidth","#sigma_{x,hit} vs. w_{cl};w_{cl}  [# strips];#sigma_{x,hit}  [cm]",widthMax,0,widthMax);
    (*iSec).second.PSigmaXHitVsCharge       = secDir.make<TProfile>("p_sigmaXHitVsCharge","#sigma_{x,hit} vs. c_{cl};c_{cl}  [APV counts];#sigma_{x,hit}  [cm]",100,0,chargeMax);
    (*iSec).second.PSigmaXHitVsChargeLR     = secDir.make<TProfile>("p_sigmaXHitVsChargeLR","#sigma_{x,hit} vs. c_{cl,LR};c_{cl,LR}  [APV counts];#sigma_{x,hit}  [cm]",100,0,chargeMax);
    (*iSec).second.PSigmaXHitVsMaxStrip     = secDir.make<TProfile>("p_sigmaXHitVsMaxStrip","#sigma_{x,hit} vs. n_{cl,max};n_{cl,max}  [# strips];#sigma_{x,hit}  [cm]",800,-10,790);
    (*iSec).second.PSigmaXHitVsMaxCharge    = secDir.make<TProfile>("p_sigmaXHitVsMaxCharge","#sigma_{x,hit} vs. c_{cl,max};c_{cl,max}  [APV counts];#sigma_{x,hit}  [cm]",100,-10,290);
    (*iSec).second.PSigmaXHitVsMaxIndex     = secDir.make<TProfile>("p_sigmaXHitVsMaxIndex","#sigma_{x,hit} vs. i_{cl,max};i_{cl,max}  [# strips];#sigma_{x,hit}  [cm]",10,0,10);
    (*iSec).second.PSigmaXHitVsBaryStrip    = secDir.make<TProfile>("p_sigmaXHitVsBaryStrip","#sigma_{x,hit} vs. b_{cl};b_{cl}  [# strips];#sigma_{x,hit}  [cm]",100,-10,790);
    (*iSec).second.PSigmaXHitVsSOverN       = secDir.make<TProfile>("p_sigmaXHitVsSOverN","#sigma_{x,hit} vs. s/N;s/N;#sigma_{x,hit}  [cm]",100,0,sOverNMax);
    
    (*iSec).second.PSigmaXTrkVsP            = secDir.make<TProfile>("p_sigmaXTrkVsP","#sigma_{x,track} vs. |p|; |p|  [GeV];#sigma_{x,track}  [cm]",50,0,pMax);
    (*iSec).second.PSigmaXTrkVsInvP         = secDir.make<TProfile>("p_sigmaXTrkVsInvP","#sigma_{x,track} vs. 1/|p|; 1/|p|  [GeV^{-1}];#sigma_{x,track}  [cm]",25,0,invPMax);
    (*iSec).second.PSigmaXTrkVsMeanAngle    = secDir.make<TProfile>("p_sigmaXTrkVsMeanAngle","#sigma_{x,track} vs. <#phi_{module}>;<#phi_{module}>  [ ^{o}];#sigma_{x,track}",25,-5,95);
    (*iSec).second.PSigmaXTrkVsHitsValid    = secDir.make<TProfile>("p_sigmaXTrkVsHitsValid","#sigma_{x,track} vs. # hits;# hits  [valid];#sigma_{x,track}  [cm]",50,0,50);
    (*iSec).second.PSigmaXTrkVsHitsGood     = secDir.make<TProfile>("p_sigmaXTrkVsHitsGood","#sigma_{x,track} vs. # hits  [good];# hits  [good];#sigma_{x,track}  [cm]",50,0,50);
    (*iSec).second.PSigmaXTrkVsHitsInvalid  = secDir.make<TProfile>("p_sigmaXTrkVsHitsInvalid","#sigma_{x,track} vs. # hits  [invalid];# hits  [invalid];#sigma_{x,track}  [cm]",20,0,20);
    (*iSec).second.PSigmaXTrkVsLayersMissed = secDir.make<TProfile>("p_sigmaXTrkVsLayersMissed","#sigma_{x,track} vs. # layers  [missed];# layers  [missed];#sigma_{x,track}  [cm]",10,0,10);
    (*iSec).second.PSigmaXVsNorChi2         = secDir.make<TProfile>("p_sigmaXVsNorChi2","#sigma_{x} vs. #chi^{2}/ndof;#chi^{2}/ndof;#sigma_{x}  [cm]",50,0,norChi2Max);
    
    (*iSec).second.PSigmaXHitVsPhiSens      = secDir.make<TProfile>("p_sigmaXHitVsPhiSens" ,"#sigma_{x,hit} vs. #phi_{module};#phi_{module}  [ ^{o}];#sigma_{x,hit}  [cm]",47,-2,92);
    (*iSec).second.PSigmaXHitVsPhiSensX     = secDir.make<TProfile>("p_sigmaXHitVsPhiSensX","#sigma_{x,hit} vs. #phi_{x,module};#phi_{x,module}  [ ^{o}];#sigma_{x,hit}  [cm]",92,-92,92);
    (*iSec).second.PSigmaXHitVsPhiSensY     = secDir.make<TProfile>("p_sigmaXHitVsPhiSensY","#sigma_{x,hit} vs. #phi_{y,module};#phi_{y,module}  [ ^{o}];#sigma_{x,hit}  [cm]",92,-92,92);
    (*iSec).second.PSigmaXTrkVsPhiSens      = secDir.make<TProfile>("p_sigmaXTrkVsPhiSens" ,"#sigma_{x,track} vs. #phi_{module};#phi_{module}  [ ^{o}];#sigma_{x,track}  [cm]",47,-2,92);
    (*iSec).second.PSigmaXTrkVsPhiSensX     = secDir.make<TProfile>("p_sigmaXTrkVsPhiSensX","#sigma_{x,track} vs. #phi_{x,module};#phi_{x,module}  [ ^{o}];#sigma_{x,track}  [cm]",92,-92,92);
    (*iSec).second.PSigmaXTrkVsPhiSensY     = secDir.make<TProfile>("p_sigmaXTrkVsPhiSensY","#sigma_{x,track} vs. #phi_{y,module};#phi_{y,module}  [ ^{o}];#sigma_{x,track}  [cm]",92,-92,92);
    (*iSec).second.PSigmaXVsPhiSens         = secDir.make<TProfile>("p_sigmaXVsPhiSens" ,"#sigma_{x} vs. #phi_{module};#phi_{module}  [ ^{o}];#sigma_{x}  [cm]",47,-2,92);
    (*iSec).second.PSigmaXVsPhiSensX        = secDir.make<TProfile>("p_sigmaXVsPhiSensX","#sigma_{x} vs. #phi_{x,module};#phi_{x,module}  [ ^{o}];#sigma_{x}  [cm]",92,-92,92);
    (*iSec).second.PSigmaXVsPhiSensY        = secDir.make<TProfile>("p_sigmaXVsPhiSensY","#sigma_{x} vs. #phi_{y,module};#phi_{y,module}  [ ^{o}];#sigma_{x}  [cm]",92,-92,92);
    
    (*iSec).second.PNorResXVsSigmaXHit      = secDir.make<TProfile>("p_norResXVsSigmaXHit","r_{x}/#sigma_{x} vs. #sigma_{x,hit};#sigma_{x,hit}  [cm];(x_{track}-x_{hit})'/#sigma_{x}",20,0,0.01,"s");
    (*iSec).second.PNorResXVsSigmaXTrk      = secDir.make<TProfile>("p_norResXVsSigmaXTrk","r_{x}/#sigma_{x} vs. #sigma_{x,track};#sigma_{x,track}  [cm];(x_{track}-x_{hit})'/#sigma_{x}",20,0,0.01,"s");
    (*iSec).second.PNorResXVsSigmaX         = secDir.make<TProfile>("p_norResXVsSigmaX","r_{x}/#sigma_{x} vs. #sigma_{x};#sigma_{x}  [cm];(x_{track}-x_{hit})'/#sigma_{x}",20,0,0.01,"s");
    
    (*iSec).second.PWidthVsPhiSensX         = secDir.make<TProfile>("p_widthVsPhiSensX","w_{cl} vs. #phi_{x,module};#phi_{x,module}  [ ^{o}];w_{cl}  [# strips]",92,-92,92);
    
    for(std::vector<unsigned int>::iterator iErrHists = vErrHists.begin(); iErrHists != vErrHists.end(); ++iErrHists){
      double xMin(0.01*(*iErrHists-1)), xMax(0.01*(*iErrHists));
      std::stringstream sigmaXHit, sigmaXTrk, sigmaX;
      sigmaXHit << "h_sigmaXHit_" << *iErrHists;
      sigmaXTrk << "h_sigmaXTrk_" << *iErrHists;
      sigmaX    << "h_sigmaX_"    << *iErrHists;
      (*iSec).second.mSigmaX["sigmaXHit"].push_back(secDir.make<TH1F>(sigmaXHit.str().c_str(),"hit error #sigma_{x,hit};#sigma_{x,hit}  [cm];# hits",100,xMin,xMax));
      (*iSec).second.mSigmaX["sigmaXTrk"].push_back(secDir.make<TH1F>(sigmaXTrk.str().c_str(),"track error #sigma_{x,track};#sigma_{x,track}  [cm];# hits",100,xMin,xMax));
      (*iSec).second.mSigmaX["sigmaX"   ].push_back(secDir.make<TH1F>(sigmaX.str().c_str(),"residual error #sigma_{x};#sigma_{x}  [cm];# hits",100,xMin,xMax));
    }
    
    if(mResErrBins_.size()==0){mResErrBins_[1].first = 0.;mResErrBins_[1].second = 0.01;} // default if no selection taken into account: calculate APE with one bin with residual error 0-100um
    for(std::map<unsigned int,std::pair<double,double> >::const_iterator iErrBins = mResErrBins_.begin();
         iErrBins != mResErrBins_.end(); ++iErrBins){
      std::stringstream interval; interval << "Interval_" << (*iErrBins).first;
      TFileDirectory intDir = secDir.mkdir(interval.str().c_str());
      (*iSec).second.mBinnedHists[(*iErrBins).first]["sigmaX"]  = intDir.make<TH1F>("h_sigmaX","residual error #sigma_{x};#sigma_{x}  [cm];# hits",100,0.,0.01);
      (*iSec).second.mBinnedHists[(*iErrBins).first]["norResX"] = intDir.make<TH1F>("h_norResX","normalized residual r_{x}/#sigma_{x};(x_{track}-x_{hit})'/#sigma_{x};# hits",100,-10,10);
    }
    
    //Result plots (one hist per sector containing one bin per interval)
    std::vector<double> vBinX(theParameterSet.getParameter<std::vector<double> >("residualErrorBinning"));
    //int nBinX(mResErrBins_.size()), minBinX(1), maxBinX(nBinX+minBinX);
    TFileDirectory resDir = secDir.mkdir("Results");
    //(*iSec).second.Entries        = resDir.make<TH1F>("h_entries","# hits used;# interval;# hits",nBinX,minBinX,maxBinX);
    //(*iSec).second.MeanX          = resDir.make<TH1F>("h_meanX","residual mean <r_{x}/#sigma_{x}>;# interval;<r_{x}/#sigma_{x}>",nBinX,minBinX,maxBinX);
    //(*iSec).second.RmsX           = resDir.make<TH1F>("h_rmsX","residual rms RMS(r_{x}/#sigma_{x});# interval;RMS(r_{x}/#sigma_{x})",nBinX,minBinX,maxBinX);
    //(*iSec).second.FitMeanX       = resDir.make<TH1F>("h_fitMeanX","fitted residual mean #mu_{x};# interval;#mu_{x}",nBinX,minBinX,maxBinX);
    //(*iSec).second.ResidualWidthX = resDir.make<TH1F>("h_residualWidthX","residual width #Delta_{x};# interval;#Delta_{x}",nBinX,minBinX,maxBinX);
    //(*iSec).second.ApeX           = resDir.make<TH1F>("h_apeX","alignment precision APE_{x};# interval;APE_{x}",nBinX,minBinX,maxBinX);
    (*iSec).second.Entries        = resDir.make<TH1F>("h_entries","# hits used;#sigma_{x}  [cm];# hits",vBinX.size()-1,&(vBinX[0]));
    (*iSec).second.MeanX          = resDir.make<TH1F>("h_meanX","residual mean <r_{x}/#sigma_{x}>;#sigma_{x}  [cm];<r_{x}/#sigma_{x}>",vBinX.size()-1,&(vBinX[0]));
    (*iSec).second.RmsX           = resDir.make<TH1F>("h_rmsX","residual rms RMS(r_{x}/#sigma_{x});#sigma_{x}  [cm];RMS(r_{x}/#sigma_{x})",vBinX.size()-1,&(vBinX[0]));
    (*iSec).second.FitMeanX       = resDir.make<TH1F>("h_fitMeanX","fitted residual mean #mu_{x};#sigma_{x}  [cm];#mu_{x}",vBinX.size()-1,&(vBinX[0]));
    (*iSec).second.ResidualWidthX = resDir.make<TH1F>("h_residualWidthX","residual width #Delta_{x};#sigma_{x}  [cm];#Delta_{x}",vBinX.size()-1,&(vBinX[0]));
    (*iSec).second.ApeX           = resDir.make<TH1F>("h_apeX","alignment precision APE_{x};#sigma_{x}  [cm];APE_{x}",vBinX.size()-1,&(vBinX[0]));
  }
}


// -----------------------------------------------------------------------------------------------------------

void
ApeEstimator::bookTrackHists(){
  
  bool zoomHists(theParameterSet.getParameter<bool>("zoomHists"));
  
  int trackSizeBins = zoomHists ? 21 : 201;
  double trackSizeMax = trackSizeBins -1;
  double chi2Max = zoomHists ? 200. : 2000.;
  double norChi2Max = zoomHists ? 40. : 1000.;
  double pMax = zoomHists ? 100. : 5000.;
  
  edm::Service<TFileService> fileService;
  //TFileDirectory dir1(*fileService);
  TFileDirectory evtDir = fileService->mkdir("EventVariables");
  tkDetector_.TrkSize = evtDir.make<TH1F>("h_trackSize","# tracks;# tracks;# events",trackSizeBins,-1,trackSizeMax);
  TFileDirectory trkDir = fileService->mkdir("TrackVariables");
  tkDetector_.HitsSize     = trkDir.make<TH1F>("h_hitSize","# hits;# hits;# tracks",51,-1,50);
  tkDetector_.HitsValid    = trkDir.make<TH1F>("h_hitValid","# hits  [valid];# hits  [valid];# tracks",51,-1,50);
  tkDetector_.HitsInvalid  = trkDir.make<TH1F>("h_hitInvalid","# hits  [invalid];# hits  [invalid];# tracks",21,-1,20);
  tkDetector_.Hits2D       = trkDir.make<TH1F>("h_hit2D","# hits  [2D];# hits  [2D];# tracks",21,-1,20);
  tkDetector_.LayersMissed = trkDir.make<TH1F>("h_layerMissed","# layers  [missed];# layers  [missed];# tracks",11,-1,10);
  tkDetector_.Charge       = trkDir.make<TH1F>("h_charge","charge q;q  [e];# tracks",5,-2,3);
  tkDetector_.Chi2         = trkDir.make<TH1F>("h_chi2"," #chi^{2};#chi^{2};# tracks",100,0,chi2Max);
  tkDetector_.Ndof         = trkDir.make<TH1F>("h_ndof","# degrees of freedom ndof;ndof;# tracks",101,-1,100);
  tkDetector_.NorChi2      = trkDir.make<TH1F>("h_norChi2","normalized #chi^{2};#chi^{2}/ndof;# tracks",200,0,norChi2Max);
  tkDetector_.Eta          = trkDir.make<TH1F>("h_eta","pseudorapidity #eta;#eta;# tracks",50,-3,3);
  tkDetector_.Theta        = trkDir.make<TH1F>("h_theta","polar angle #theta;#theta  [ ^{o}];# tracks",100,-10,190);
  tkDetector_.Phi          = trkDir.make<TH1F>("h_phi","azimuth angle #phi;#phi  [ ^{o}];# tracks",190,-190,190);
  tkDetector_.P	           = trkDir.make<TH1F>("h_p","momentum magnitude |p|;|p|  [GeV];# tracks",100,0,pMax);
  tkDetector_.Pt	   = trkDir.make<TH1F>("h_pt","transverse momentum p_{t};p_{t}  [GeV];# tracks",100,0,pMax);
  tkDetector_.MeanAngle    = trkDir.make<TH1F>("h_meanAngle","mean angle on module <#phi_{module}>;<#phi_{module}>  [ ^{o}];# tracks",100,-5,95);
  tkDetector_.HitsGood     = trkDir.make<TH1F>("h_hitsGood","# hits  [good];# hits  [good];# tracks",51,-1,50);
  
  tkDetector_.MeanAngleVsHits     = trkDir.make<TH2F>("h2_meanAngleVsHits","<#phi_{module}> vs. # hits;# hits;<#phi_{module}>  [ ^{o}]",51,-1,50,50,-5,95);
  tkDetector_.HitsGoodVsHitsValid = trkDir.make<TH2F>("h2_hitsGoodVsHitsValid","# hits  [good] vs. # hits  [valid];# hits  [valid];# hits  [good]",51,-1,50,51,-1,50);
  
  tkDetector_.PMeanAngleVsHits     = trkDir.make<TProfile>("p_meanAngleVsHits","<#phi_{module}> vs. # hits;# hits;<#phi_{module}>  [ ^{o}]",51,-1,50);
  tkDetector_.PHitsGoodVsHitsValid = trkDir.make<TProfile>("p_hitsGoodVsHitsValid","# hits  [good] vs. # hits  [valid];# hits  [valid];# hits  [good]",51,-1,50);
}



// -----------------------------------------------------------------------------------------------------------


TrackStruct::TrackParameterStruct
//ApeEstimator::fillTrackVariables(const reco::Track& track, const Trajectory& traj)const{  // trackCut_ forbids const
ApeEstimator::fillTrackVariables(const reco::Track& track, const Trajectory& traj){
  
  static TrajectoryStateCombiner tsoscomb;
  
  TrackStruct::TrackParameterStruct trkParams;
  
  trkParams.hitsSize     = track.recHitsSize();
  trkParams.hitsValid    = track.found(); // invalid is every hit from every single module that expects a hit
  //trkParams.hitsValid    = trkParams.hitsSize-trkParams.hitsLost;  // incorrect: unequal to .found(), because not every invalid hit is a lost one
  trkParams.hitsInvalid  = trkParams.hitsSize-trkParams.hitsValid;
  trkParams.layersMissed = track.lost();  // lost hit means, that a crossed layer doesn't contain a hit (can be more than one invalid hit)
  trkParams.charge       = track.charge();
  trkParams.chi2         = track.chi2();
  trkParams.ndof         = track.ndof();
  trkParams.norChi2      = trkParams.chi2/trkParams.ndof;
  trkParams.eta          = track.eta();
  trkParams.theta        = track.theta();
  trkParams.phi          = track.phi();
  trkParams.p            = track.p();
  trkParams.pt           = track.pt();
  
  const std::vector<TrajectoryMeasurement>& meass = traj.measurements();
     
  int count2D(0); float meanPhiSensToNorm(0.F);
  std::vector<TrajectoryMeasurement>::const_iterator im;
  for(im = meass.begin(); im != meass.end(); ++im){     
    const TrajectoryMeasurement& meas = *im;
    const TransientTrackingRecHit& hit = *meas.recHit();
    const TrackingRecHit& recHit = *hit.hit();
    if(this->isHit2D(recHit))++count2D;
    
    TrajectoryStateOnSurface tsos = tsoscomb(meas.forwardPredictedState(),meas.backwardPredictedState());
    const align::LocalVector mom(tsos.localDirection());
    meanPhiSensToNorm += atan(fabs(sqrt(mom.x()*mom.x()+mom.y()*mom.y())/mom.z()));
  }
  meanPhiSensToNorm *= (1./static_cast<float>(trkParams.hitsSize));
  
  trkParams.hits2D            = count2D;
  trkParams.meanPhiSensToNorm = meanPhiSensToNorm;
  
  if(theParameterSet.getParameter<bool>("applyTrackCuts")){
    trackCut_ = false;
    if(trkParams.hitsValid<10 || trkParams.hits2D<2 || trkParams.pt<4. || trkParams.p<1. || trkParams.p>500. || trkParams.norChi2>100. || trkParams.phi>0.)trackCut_ = true;
    //if(trkParams.hitsValid<12 || trkParams.hits2D<2 || trkParams.p<20. || trkParams.p>500. || trkParams.norChi2>10. || trkParams.phi>0. || trkParams.meanPhiSensToNorm>0.9599)trackCut_ = true;  //55degree
    //if(trkParams.hitsValid<12 || trkParams.hits2D<2 || trkParams.p<4. || trkParams.p>500. || trkParams.norChi2>10. || trkParams.phi>0. || trkParams.meanPhiSensToNorm>0.9599
    //                          || trkParams.pt<4.)trackCut_ = true;  //55degree
    //if(trkParams.hitsValid<15 || trkParams.hits2D<2 || trkParams.p<20. || trkParams.p>500. || trkParams.norChi2>10. || trkParams.phi>0. || trkParams.meanPhiSensToNorm>0.9599
    //                          || trkParams.pt<10.)trackCut_ = true;  //55degree
  }
  else{
    //repeat intrinsic ALCARECO cuts after track refitting 
    trackCut_ = false;
    if(trkParams.hitsValid<7)trackCut_ = true;
  }
  
  return trkParams;
}



TrackStruct::HitParameterStruct
ApeEstimator::fillHitVariables(const TrajectoryMeasurement& iMeass, const edm::EventSetup& iSetup){
  
  TrackStruct::HitParameterStruct hitParams;
  
  static TrajectoryStateCombiner tsoscomb;
  
  const TrajectoryMeasurement& meas = iMeass;
  const TransientTrackingRecHit& hit = *meas.recHit();
  const TrackingRecHit& recHit = *hit.hit();
  TrajectoryStateOnSurface tsos = tsoscomb(meas.forwardPredictedState(),meas.backwardPredictedState());
  
  DetId detId(hit.geographicalId());
  DetId::Detector detector = detId.det(); if(detector != DetId::Tracker){hitParams.hitState = TrackStruct::notInTracker; return hitParams;}
  uint32_t rawId(detId.rawId());
  
  for(std::map<unsigned int,TrackerSectorStruct>::const_iterator iSec = mTkSector_.begin(); iSec != mTkSector_.end(); ++iSec){
    for(std::vector<unsigned int>::const_iterator iRawId = (*iSec).second.vRawId.begin();
        iRawId != (*iSec).second.vRawId.end(); ++iRawId){
      if(rawId==*iRawId){hitParams.sectors.push_back((*iSec).first); break;}
    }
  }
  
  //Moved to the end of the method (lose speed for more information contained)
  //if(0==hitParams.sectors.size()){hitParams.hitState = TrackStruct::notAssignedToSectors; return hitParams;}
  
  
//  const align::LocalVector mom(tsos.localDirection());
//  int uDirectionMomentum(0), vDirectionMomentum(0), wDirectionMomentum(0);
//  uDirectionMomentum = static_cast<float>(mTkTreeVar_[rawId].uDirection)*mom.x() > 0. ? 1 : -1; // > 0. -> momentum pointing in x' direction ( +phi)
//  vDirectionMomentum = static_cast<float>(mTkTreeVar_[rawId].vDirection)*mom.y() > 0. ? 1 : -1; // > 0. -> momentum pointing in y' direction (Barrel: +z, Forward: +r)
//  wDirectionMomentum = static_cast<float>(mTkTreeVar_[rawId].wDirection)*mom.z() > 0. ? 1 : -1; // > 0. -> momentum pointing in z' direction (Barrel: +r, Forward: +z)
//  //std::cout<<"\n\tMomentum:\t"<<mom.x()<<" "<<mom.y()<<" "<<mom.z()<<" "<<mom.phi()<<" "<<mom.theta();
//  //std::cout<<"\n\tOrientation:\t"<<mTkTreeVar_[rawId].uDirection<<" "<<mTkTreeVar_[rawId].vDirection<<" "<<mTkTreeVar_[rawId].wDirection;
//  //std::cout<<"\n\tMomDirection:\t"<<uDirectionMomentum<<" "<<vDirectionMomentum<<" "<<wDirectionMomentum<<"\n";
//  hitParams.phiSens  = atan(fabs(sqrt(mom.x()*mom.x()+mom.y()*mom.y())/mom.z()));
//  hitParams.phiSensX = (uDirectionMomentum == wDirectionMomentum ? atan(fabs(mom.x()/mom.z())) : -atan(fabs(mom.x()/mom.z())) );
//  hitParams.phiSensY = (vDirectionMomentum == wDirectionMomentum ? atan(fabs(mom.y()/mom.z())) : -atan(fabs(mom.y()/mom.z())) );
  
  // gives same results
  const align::LocalVector mom(tsos.localDirection());
  int xMomentum(0), yMomentum(0), zMomentum(0);
  xMomentum = mom.x()>0. ? 1 : -1;
  yMomentum = mom.y()>0. ? 1 : -1;
  zMomentum = mom.z()>0. ? 1 : -1;
  float phiSensX = atan(fabs(mom.x()/mom.z()))*static_cast<float>(mTkTreeVar_[rawId].vDirection);  // check for orientation of E- and B- Field (thoughts for barrel)
  float phiSensY = atan(fabs(mom.y()/mom.z()))*static_cast<float>(mTkTreeVar_[rawId].vDirection);
  hitParams.phiSens  = atan(fabs(sqrt(mom.x()*mom.x()+mom.y()*mom.y())/mom.z()));
  hitParams.phiSensX = (xMomentum==zMomentum ? phiSensX : -phiSensX );
  hitParams.phiSensY = (yMomentum==zMomentum ? phiSensY : -phiSensY );
  
  
  
  if(!hit.isValid()){hitParams.hitState = TrackStruct::invalid; return hitParams;}
       
  LocalPoint lPHit = hit.localPosition(), lPTrk = tsos.localPosition();
  hitParams.xHit = lPHit.x();
  hitParams.xTrk = lPTrk.x();
  
  // use APE also for the hit error, while APE is automatically included in tsos error (method taken from Jula)
  AlgebraicROOTObject<2>::SymMatrix mat = asSMatrix<2>(hit.parametersError());
  LocalError errHitAPE = LocalError( mat(0,0),mat(0,1),mat(1,1) ),
             errHit = hit.localPositionError(),
	     errTrk = tsos.localError().positionError();
  
  
  if(errHit.xx()<0. || errHit.yy()<0. || errHitAPE.xx()<0. || errHitAPE.yy()<0. || errTrk.xx()<0. || errTrk.yy()<0.){
    hitParams.hitState = TrackStruct::negativeError;
    ++counter1;
    edm::LogError("Negative error Value")<<"@SUB=ApeEstimator::fillHitVariables"
                                         <<"One of the squared error methods gives negative result"
                                         <<"\n\tSubdetector\terrHit.xx()\terrHit.yy()\terrHitAPE.xx()\terrHitAPE.yy()\terrTrk.xx()\terrTrk.yy()"
                                         <<"\n\t"<<mTkTreeVar_[rawId].subdetId<<"\t\t"<<errHit.xx()<<"\t"<<errHit.yy()
					 <<errHitAPE.xx()<<"\t"<<errHitAPE.yy()<<"\t"<<errTrk.xx()<<"\t"<<errTrk.yy();
    return hitParams;
  }
  
  // errors in cartesian x, also in TID, TEC
  float errX2(999.F), errY2(999.F);
  errX2 = errHitAPE.xx()+errTrk.xx();
  errY2 = errHitAPE.yy()+errTrk.yy();
  hitParams.errXHit = sqrt(errHitAPE.xx());
  hitParams.errXTrk = sqrt(errTrk.xx());
  hitParams.errX2   = errX2;
  hitParams.errX    = sqrt(errX2);
  
  
  align::LocalVector res = lPTrk - lPHit;
  float resX(999.F), resY(999.F), errX(999.F), errY(999.F), norResX(999.F), norResY(999.F);
  
  if(mTkTreeVar_[rawId].subdetId==PixelSubdetector::PixelBarrel || mTkTreeVar_[rawId].subdetId==PixelSubdetector::PixelEndcap ||
     mTkTreeVar_[rawId].subdetId==StripSubdetector::TIB || mTkTreeVar_[rawId].subdetId==StripSubdetector::TOB){
    resX = res.x();
    resY = res.y();
    errX = sqrt(errX2);
    errY = sqrt(errY2);
    norResX = resX/errX;
    norResY = resY/errY;
  }
  else if(mTkTreeVar_[rawId].subdetId==StripSubdetector::TID || mTkTreeVar_[rawId].subdetId==StripSubdetector::TEC){
    
    if(!hit.detUnit()){hitParams.hitState = TrackStruct::invalid; return hitParams;} // is it a single physical module?
    const GeomDetUnit& detUnit = *hit.detUnit();
    
    if(!dynamic_cast<const RadialStripTopology*>(&detUnit.topology())){hitParams.hitState = TrackStruct::invalid; return hitParams;}
    const RadialStripTopology& topol = dynamic_cast<const RadialStripTopology&>(detUnit.topology());
    
    MeasurementPoint measHitPos = topol.measurementPosition(lPHit);
    MeasurementPoint measTrkPos = topol.measurementPosition(lPTrk);
      
    MeasurementError measHitErr = topol.measurementError(lPHit,errHitAPE);
    MeasurementError measTrkErr = topol.measurementError(lPTrk,errTrk);
    
    if(measHitErr.uu()<0. || measHitErr.vv()<0. || measTrkErr.uu()<0. || measTrkErr.vv()<0.){
      ++counter1;
      
      const SiStripRecHit2D& stripHit = dynamic_cast<const SiStripRecHit2D&>(recHit);
      const SiStripCluster& stripCluster = *stripHit.cluster();
      SiStripClusterInfo clusterInfo = SiStripClusterInfo(stripCluster, iSetup);
      hitParams.width          = clusterInfo.width();
      
      edm::LogError("Negative error Value")<<"@SUB=ApeEstimator::fillHitVariables"
                                           <<"One of the squared error methods gives negative result"
                                           <<"\n\tmeasHitErr.uu()\tmeasHitErr.vv()\tmeasTrkErr.uu()\tmeasTrkErr.vv()"
	                                   <<"\n\t"<<measHitErr.uu()<<"\t"<<measHitErr.vv()<<"\t"<<measTrkErr.uu()<<"\t"<<measTrkErr.vv()
					   <<"\n\nOriginalValues: "<<lPHit.x()<<" "<<lPHit.y()<<"\n"<<lPTrk.x()<<" "<<lPTrk.y()<<"\n"<<errHit.xx()<<" "<<errHit.yy()<<"\n"
					   <<errHitAPE.xx()<<" "<<errHitAPE.yy()<<"\n"<<"Subdet: "<<mTkTreeVar_[rawId].subdetId
					   <<"Width: "<<hitParams.width;
      hitParams.hitState = TrackStruct::negativeError;
      return hitParams;
    }
//    else edm::LogError("No Negative error Value")<<"@SUB=ApeEstimator::fillHitVariables"
//                                                 <<"None of the squared error methods gives negative result !!!!!";
    
    float localStripLengthHit = topol.localStripLength(lPHit);
    float localStripLengthTrk = topol.localStripLength(lPTrk);
    float phiHit = topol.stripAngle(measHitPos.x());
    float phiTrk = topol.stripAngle(measTrkPos.x());
    float r_0 = topol.originToIntersection();
    
    resX = (phiTrk-phiHit)*r_0;
    float cosPhiHit(cos(phiHit)), cosPhiTrk(cos(phiTrk)),
          sinPhiHit(sin(phiHit)), sinPhiTrk(sin(phiTrk));
    float l_0 = r_0 - topol.detHeight()/2;
    resY = measTrkPos.y()*localStripLengthTrk - measHitPos.y()*localStripLengthHit + l_0*(1/cosPhiTrk - 1/cosPhiHit);
    
    errX = std::sqrt(measHitErr.uu()+measTrkErr.uu())*topol.angularWidth()*r_0;
    float helpSummand = l_0*l_0*topol.angularWidth()*topol.angularWidth()*(sinPhiHit*sinPhiHit/pow(cosPhiHit,4)*measHitErr.uu()
                                                                         + sinPhiTrk*sinPhiTrk/pow(cosPhiTrk,4)*measTrkErr.uu());
    errY = std::sqrt(measHitErr.vv()*localStripLengthHit*localStripLengthHit
                   + measTrkErr.vv()*localStripLengthTrk*localStripLengthTrk + helpSummand);
    
    norResX = resX/errX;
    norResY = resY/errY;
  }
  
  //now take global orientation into account
  float resXprime(999.F), resYprime(999.F), norResXprime(999.F), norResYprime(999.F);
  if(mTkTreeVar_[rawId].uDirection == 1){resXprime = resX; norResXprime = norResX;}
  else if(mTkTreeVar_[rawId].uDirection == -1){resXprime = -resX; norResXprime = -norResX;}
  else {edm::LogError("FillHitVariables")<<"Incorrect value of uDirection, which gives global module orientation"; hitParams.hitState = TrackStruct::invalid; return hitParams;}
  if(mTkTreeVar_[rawId].vDirection == 1){resYprime = resY; norResYprime = norResY;}
  else if(mTkTreeVar_[rawId].vDirection == -1){resYprime = -resY; norResYprime = -norResY;}
  else {edm::LogError("FillHitVariables")<<"Incorrect value of vDirection, which gives global module orientation"; hitParams.hitState = TrackStruct::invalid; return hitParams;}
  
  hitParams.resX    = resXprime;
  hitParams.norResX = norResXprime;
  
  
  
   if(mTkTreeVar_[rawId].subdetId==PixelSubdetector::PixelBarrel || mTkTreeVar_[rawId].subdetId==PixelSubdetector::PixelEndcap){
     //const SiPixelRecHit& pixelHit = dynamic_cast<const SiPixelRecHit&>(recHit);
     //const SiPixelCluster& pixelCluster = *pixelHit.cluster();
   }
   else if(mTkTreeVar_[rawId].subdetId==StripSubdetector::TIB || mTkTreeVar_[rawId].subdetId==StripSubdetector::TOB ||
           mTkTreeVar_[rawId].subdetId==StripSubdetector::TID || mTkTreeVar_[rawId].subdetId==StripSubdetector::TEC){
     if(!dynamic_cast<const SiStripRecHit2D*>(&recHit)){
       edm::LogError("FillHitVariables")<<"RecHit in Strip is 'Matched' or 'Projected', but here all should be monohits per module";
       hitParams.hitState = TrackStruct::invalid; return hitParams;
     }
     const SiStripRecHit2D& stripHit = dynamic_cast<const SiStripRecHit2D&>(recHit);
     const SiStripCluster& stripCluster = *stripHit.cluster();
     SiStripClusterInfo clusterInfo = SiStripClusterInfo(stripCluster, iSetup);
     
     hitParams.isModuleUsable = clusterInfo.IsModuleUsable();
     hitParams.width          = clusterInfo.width();
     hitParams.maxStrip       = clusterInfo.maxStrip() +1;
     hitParams.maxStripInv    = mTkTreeVar_[rawId].nStrips - hitParams.maxStrip +1;
     hitParams.charge         = clusterInfo.charge();
     hitParams.maxCharge      = clusterInfo.maxCharge();
     hitParams.maxIndex       = clusterInfo.maxIndex();
     hitParams.chargeLR       = clusterInfo.chargeLR().first + clusterInfo.chargeLR().second;
     hitParams.baryStrip      = clusterInfo.baryStrip() +1.;
     hitParams.sOverN         = clusterInfo.signalOverNoise();
   }
   else{
     edm::LogError("FillHitVariables")<<"Incorrect subdetector ID, hit not associated to tracker";
     hitParams.hitState = TrackStruct::notInTracker; return hitParams;
   }
  
  
  if(!hitParams.isModuleUsable){hitParams.hitState = TrackStruct::invalid; return hitParams;}
  
  if(0==hitParams.sectors.size()){hitParams.hitState = TrackStruct::notAssignedToSectors; return hitParams;}
  
  return hitParams;
  
}



// -----------------------------------------------------------------------------------------------------------

void
ApeEstimator::hitSelection(){
  this->setHitSelectionMapUInt("width");
  this->setHitSelectionMap("charge");
  this->setHitSelectionMap("chargeLR");
  this->setHitSelectionMapUInt("edgeStrips");
  this->setHitSelectionMap("maxCharge");
  this->setHitSelectionMapUInt("maxIndex");
  this->setHitSelectionMap("sOverN");
  
  this->setHitSelectionMap("resX");
  this->setHitSelectionMap("norResX");
  this->setHitSelectionMap("errXHit");
  this->setHitSelectionMap("errXTrk");
  this->setHitSelectionMap("errX");
  this->setHitSelectionMap("errX2");
  this->setHitSelectionMap("phiSens");
  this->setHitSelectionMap("phiSensX");
  this->setHitSelectionMap("phiSensY");
  
  edm::LogInfo("HitSelector")<<"applying hit cuts ...";
  bool emptyMap(true);
  for(std::map<std::string, std::vector<double> >::iterator iMap = mHitSelection_.begin(); iMap != mHitSelection_.end(); ++iMap){
    if(0 < (*iMap).second.size()){
      //emptyMap = false;
      int iEntry(1); double intervalBegin(999.);
      for(std::vector<double>::iterator iVec = (*iMap).second.begin(); iVec != (*iMap).second.end(); ++iEntry){
        if(iEntry%2==1){intervalBegin = *iVec; ++iVec;}
	else{
	  if(intervalBegin > *iVec){
	    edm::LogError("HitSelector")<<"INVALID Interval selected for  "<<(*iMap).first<<":\t"<<intervalBegin<<" > "<<(*iVec)
	                                <<"\n ... delete Selection for "<<(*iMap).first;
	    (*iMap).second.clear(); iVec = (*iMap).second.begin(); //emptyMap = true; iMap = mHitSelection_.begin();
	  }else{
	    edm::LogInfo("HitSelector")<<"Interval selected for  "<<(*iMap).first<<":\t"<<intervalBegin<<", "<<(*iVec);
            ++iVec;
	  }
	}
      }
      if(0 < (*iMap).second.size())emptyMap = false;
    }
  }
  
  
  bool emptyMapUInt(true);
  for(std::map<std::string, std::vector<unsigned int> >::iterator iMap = mHitSelectionUInt_.begin(); iMap != mHitSelectionUInt_.end(); ++iMap){
    if(0 < (*iMap).second.size()){
      //emptyMap = false;
      int iEntry(1); unsigned int intervalBegin(999);
      for(std::vector<unsigned int>::iterator iVec = (*iMap).second.begin(); iVec != (*iMap).second.end(); ++iEntry){
        if(iEntry%2==1){intervalBegin = *iVec; ++iVec;}
	else{
	  if(intervalBegin > *iVec){
	    edm::LogError("HitSelector")<<"INVALID Interval selected for  "<<(*iMap).first<<":\t"<<intervalBegin<<" > "<<(*iVec)
	                                <<"\n ... delete Selection for "<<(*iMap).first;
	    (*iMap).second.clear(); iVec = (*iMap).second.begin(); //emptyMap = true; iMap = mHitSelection_.begin();
	  }else{
	    edm::LogInfo("HitSelector")<<"Interval selected for  "<<(*iMap).first<<":\t"<<intervalBegin<<", "<<(*iVec);
            ++iVec;
	  }
	}
      }
      if(0 < (*iMap).second.size())emptyMapUInt = false;
    }
  }
  
  if(emptyMap && emptyMapUInt){
    mHitSelection_.clear();
    mHitSelectionUInt_.clear();
    edm::LogInfo("HitSelector")<<"NO hit cuts applied";
  }
  return;
}



void
ApeEstimator::setHitSelectionMap(const std::string& cutVariable){
  edm::ParameterSet parSet(theParameterSet.getParameter<edm::ParameterSet>("HitSelector"));
  std::vector<double> vCutVariable(parSet.getParameter<std::vector<double> >(cutVariable));
  if(vCutVariable.size()%2==1){
    edm::LogError("HitSelector")<<"Invalid Hit Selection for "<<cutVariable<<": need even number of arguments (intervals)"
                                <<"\n ... delete Selection for "<<cutVariable;
    vCutVariable.clear();
    mHitSelection_[cutVariable] = vCutVariable;
    return;
  }
  mHitSelection_[cutVariable] = vCutVariable;
  return;
}


void
ApeEstimator::setHitSelectionMapUInt(const std::string& cutVariable){
  edm::ParameterSet parSet(theParameterSet.getParameter<edm::ParameterSet>("HitSelector"));
  std::vector<unsigned int> vCutVariable(parSet.getParameter<std::vector<unsigned int> >(cutVariable));
  if(vCutVariable.size()%2==1){
    edm::LogError("HitSelector")<<"Invalid Hit Selection for "<<cutVariable<<": need even number of arguments (intervals)"
                                <<"\n ... delete Selection for "<<cutVariable;
    vCutVariable.clear();
    mHitSelectionUInt_[cutVariable] = vCutVariable;
    return;
  }
  mHitSelectionUInt_[cutVariable] = vCutVariable;
  return;
}



bool
ApeEstimator::hitSelected(const TrackStruct::HitParameterStruct& hitParams)const{
  //if(hitParams.hitState == TrackStruct::notInTracker || hitParams.hitState == TrackStruct::notAssignedToSectors)return false;
  if(hitParams.hitState == TrackStruct::notInTracker)return false;
  if(hitParams.hitState == TrackStruct::invalid || hitParams.hitState == TrackStruct::negativeError)return false;
  if(0==mHitSelection_.size())return true;
  for(std::map<std::string, std::vector<double> >::const_iterator iMap = mHitSelection_.begin(); iMap != mHitSelection_.end(); ++iMap){
    if(0==(*iMap).second.size())continue;
    float variable(999.F);
    
    if     ((*iMap).first == "charge")   variable = hitParams.charge;
    else if((*iMap).first == "chargeLR") variable = hitParams.chargeLR;
    else if((*iMap).first == "maxCharge")variable = hitParams.maxCharge;
    else if((*iMap).first == "sOverN")   variable = hitParams.sOverN;
    
    else if((*iMap).first == "resX")     variable = hitParams.resX;
    else if((*iMap).first == "norResX")  variable = hitParams.norResX;
    else if((*iMap).first == "errXHit")  variable = hitParams.errXHit;
    else if((*iMap).first == "errXTrk")  variable = hitParams.errXTrk;
    else if((*iMap).first == "errX")     variable = hitParams.errX;
    else if((*iMap).first == "errX2")    variable = hitParams.errX2;
    else if((*iMap).first == "phiSens")  variable = hitParams.phiSens;
    else if((*iMap).first == "phiSensX") variable = hitParams.phiSensX;
    else if((*iMap).first == "phiSensY") variable = hitParams.phiSensY;
    
    int iEntry(1); double intervalBegin(999.);
    for(std::vector<double>::const_iterator iVec = (*iMap).second.begin(); iVec != (*iMap).second.end(); ++iVec, ++iEntry){
      if(iEntry%2==1)intervalBegin = *iVec;
      else if(variable < intervalBegin || variable >= *iVec)return false;
    }
  }
  
  for(std::map<std::string, std::vector<unsigned int> >::const_iterator iMap = mHitSelectionUInt_.begin(); iMap != mHitSelectionUInt_.end(); ++iMap){
    if(0==(*iMap).second.size())continue;
    unsigned int variable(999), variable2(999);
    
    if     ((*iMap).first == "width")      variable = hitParams.width;
    else if((*iMap).first == "edgeStrips"){variable = hitParams.maxStrip; variable2 = hitParams.maxStripInv;}
    else if((*iMap).first == "maxIndex")   variable = hitParams.maxIndex;
    
    int iEntry(1); unsigned int intervalBegin(999);
    for(std::vector<unsigned int>::const_iterator iVec = (*iMap).second.begin(); iVec != (*iMap).second.end(); ++iVec, ++iEntry){
      if(iEntry%2==1)intervalBegin = *iVec;
      else if(variable < intervalBegin || variable > *iVec)return false;
      else if(variable2 != 999 && (variable2 < intervalBegin || variable2 > *iVec))return false;
    }
  }
  
  return true;
}



// -----------------------------------------------------------------------------------------------------------


void
ApeEstimator::fillHists(const TrackStruct& trackStruct){
  
  unsigned int goodHitsPerTrack(trackStruct.vHitParams.size());
  tkDetector_.HitsGood->Fill(goodHitsPerTrack);
  tkDetector_.HitsGoodVsHitsValid->Fill(trackStruct.trkParams.hitsValid,goodHitsPerTrack);
  tkDetector_.PHitsGoodVsHitsValid->Fill(trackStruct.trkParams.hitsValid,goodHitsPerTrack);
  
  if(theParameterSet.getParameter<bool>("applyTrackCuts")){
    // which tracks to take? need min. nr. of selected hits?
    if(goodHitsPerTrack < minGoodHitsPerTrack_)return;
    //if(goodHitsPerTrack < 10)return;
  }
  
  tkDetector_.HitsSize    ->Fill(trackStruct.trkParams.hitsSize);
  tkDetector_.HitsValid   ->Fill(trackStruct.trkParams.hitsValid);
  tkDetector_.HitsInvalid ->Fill(trackStruct.trkParams.hitsInvalid);
  tkDetector_.Hits2D      ->Fill(trackStruct.trkParams.hits2D);
  tkDetector_.LayersMissed->Fill(trackStruct.trkParams.layersMissed);
  tkDetector_.Charge      ->Fill(trackStruct.trkParams.charge);
  tkDetector_.Chi2        ->Fill(trackStruct.trkParams.chi2);
  tkDetector_.Ndof        ->Fill(trackStruct.trkParams.ndof);
  tkDetector_.NorChi2     ->Fill(trackStruct.trkParams.norChi2);
  tkDetector_.Eta         ->Fill(trackStruct.trkParams.eta);
  tkDetector_.Theta       ->Fill(trackStruct.trkParams.theta*180./M_PI);
  tkDetector_.Phi         ->Fill(trackStruct.trkParams.phi*180./M_PI);
  tkDetector_.P	          ->Fill(trackStruct.trkParams.p);
  tkDetector_.Pt          ->Fill(trackStruct.trkParams.pt);
  tkDetector_.MeanAngle   ->Fill(trackStruct.trkParams.meanPhiSensToNorm*180./M_PI);
  
  tkDetector_.MeanAngleVsHits->Fill(trackStruct.trkParams.hitsSize,trackStruct.trkParams.meanPhiSensToNorm*180./M_PI);
  
  tkDetector_.PMeanAngleVsHits->Fill(trackStruct.trkParams.hitsSize,trackStruct.trkParams.meanPhiSensToNorm*180./M_PI);
  
  for(std::vector<TrackStruct::HitParameterStruct>::const_iterator iHit = trackStruct.vHitParams.begin();
      iHit != trackStruct.vHitParams.end(); ++iHit){
    //Put here from earlier method
    if(iHit->hitState == TrackStruct::notAssignedToSectors)continue;
    
    for(std::map<unsigned int,TrackerSectorStruct>::iterator iSec = mTkSector_.begin(); iSec != mTkSector_.end(); ++iSec){
      bool moduleInSector(false);
      for(std::vector<unsigned int>::const_iterator iUInt = (*iHit).sectors.begin(); iUInt != (*iHit).sectors.end(); ++iUInt){
	if((*iSec).first == *iUInt){moduleInSector = true; break;}
      }
      if(!moduleInSector)continue;
      
      (*iSec).second.PhiSens  ->Fill((*iHit).phiSens*180./M_PI);
      (*iSec).second.PhiSensX ->Fill((*iHit).phiSensX*180./M_PI);
      (*iSec).second.PhiSensY ->Fill((*iHit).phiSensY*180./M_PI);
      
      //Put to earlier method (hit cuts and default value assignments may clash, def. of goodHitsPerTrack changes signeficantly)
      //if(iHit->hitState == TrackStruct::invalid)continue;
      //if(iHit->hitState == TrackStruct::negativeError)continue;
      
      
      (*iSec).second.IsModuleUsable->Fill((*iHit).isModuleUsable);
      (*iSec).second.Width	   ->Fill((*iHit).width);
      (*iSec).second.Charge	   ->Fill((*iHit).charge);
      (*iSec).second.ChargeLR      ->Fill((*iHit).chargeLR);
      (*iSec).second.MaxStrip      ->Fill((*iHit).maxStrip);
      (*iSec).second.MaxCharge     ->Fill((*iHit).maxCharge);
      (*iSec).second.MaxIndex      ->Fill((*iHit).maxIndex);
      (*iSec).second.BaryStrip     ->Fill((*iHit).baryStrip);
      (*iSec).second.SOverN        ->Fill((*iHit).sOverN);
      
      (*iSec).second.ResX     ->Fill((*iHit).resX);
      (*iSec).second.NorResX  ->Fill((*iHit).norResX);
      (*iSec).second.XHit     ->Fill((*iHit).xHit);
      (*iSec).second.XTrk     ->Fill((*iHit).xTrk);
      
      (*iSec).second.SigmaXHit->Fill((*iHit).errXHit);
      (*iSec).second.SigmaXTrk->Fill((*iHit).errXTrk);
      (*iSec).second.SigmaX   ->Fill((*iHit).errX);
      (*iSec).second.SigmaX2  ->Fill((*iHit).errX2);
      
      (*iSec).second.NorResXVsWidth         ->Fill((*iHit).width,(*iHit).norResX);
      (*iSec).second.NorResXVsCharge        ->Fill((*iHit).charge,(*iHit).norResX);
      (*iSec).second.NorResXVsChargeLR      ->Fill((*iHit).chargeLR,(*iHit).norResX);
      (*iSec).second.NorResXVsMaxStrip      ->Fill((*iHit).maxStrip,(*iHit).norResX);
      (*iSec).second.NorResXVsMaxCharge     ->Fill((*iHit).maxCharge,(*iHit).norResX);
      (*iSec).second.NorResXVsMaxIndex      ->Fill((*iHit).maxIndex,(*iHit).norResX);
      (*iSec).second.NorResXVsBaryStrip     ->Fill((*iHit).baryStrip,(*iHit).norResX);
      (*iSec).second.NorResXVsSOverN        ->Fill((*iHit).sOverN,(*iHit).norResX);
      
      (*iSec).second.NorResXVsP             ->Fill(trackStruct.trkParams.p,(*iHit).norResX);
      (*iSec).second.NorResXVsMeanAngle     ->Fill(trackStruct.trkParams.meanPhiSensToNorm*180./M_PI,(*iHit).norResX);
      (*iSec).second.NorResXVsHitsValid     ->Fill(trackStruct.trkParams.hitsValid,(*iHit).norResX);
      (*iSec).second.NorResXVsHitsGood      ->Fill(goodHitsPerTrack,(*iHit).norResX);
      (*iSec).second.NorResXVsHitsInvalid   ->Fill(trackStruct.trkParams.hitsInvalid,(*iHit).norResX);
      (*iSec).second.NorResXVsLayersMissed  ->Fill(trackStruct.trkParams.layersMissed,(*iHit).norResX);
      (*iSec).second.NorResXVsNorChi2       ->Fill(trackStruct.trkParams.norChi2,(*iHit).norResX);
      
      (*iSec).second.NorResXVsPhiSens       ->Fill((*iHit).phiSens*180./M_PI,(*iHit).norResX);
      (*iSec).second.NorResXVsPhiSensX      ->Fill((*iHit).phiSensX*180./M_PI,(*iHit).norResX);
      (*iSec).second.NorResXVsPhiSensY      ->Fill((*iHit).phiSensY*180./M_PI,(*iHit).norResX);
      
      (*iSec).second.SigmaXHitVsWidth       ->Fill((*iHit).width,(*iHit).errXHit);
      (*iSec).second.SigmaXHitVsCharge      ->Fill((*iHit).charge,(*iHit).errXHit);
      (*iSec).second.SigmaXHitVsChargeLR    ->Fill((*iHit).chargeLR,(*iHit).errXHit);
      (*iSec).second.SigmaXHitVsMaxStrip    ->Fill((*iHit).maxStrip,(*iHit).errXHit);
      (*iSec).second.SigmaXHitVsMaxCharge   ->Fill((*iHit).maxCharge,(*iHit).errXHit);
      (*iSec).second.SigmaXHitVsMaxIndex    ->Fill((*iHit).maxIndex,(*iHit).errXHit);
      (*iSec).second.SigmaXHitVsBaryStrip   ->Fill((*iHit).baryStrip,(*iHit).errXHit);
      (*iSec).second.SigmaXHitVsSOverN      ->Fill((*iHit).sOverN,(*iHit).errXHit);
      
      (*iSec).second.SigmaXTrkVsP           ->Fill(trackStruct.trkParams.p,(*iHit).errXTrk);
      (*iSec).second.SigmaXTrkVsInvP        ->Fill(1./trackStruct.trkParams.p,(*iHit).errXTrk);
      (*iSec).second.SigmaXTrkVsMeanAngle   ->Fill(trackStruct.trkParams.meanPhiSensToNorm*180./M_PI,(*iHit).errXTrk);
      (*iSec).second.SigmaXTrkVsHitsValid   ->Fill(trackStruct.trkParams.hitsValid,(*iHit).errXTrk);
      (*iSec).second.SigmaXTrkVsHitsGood    ->Fill(goodHitsPerTrack,(*iHit).errXTrk);
      (*iSec).second.SigmaXTrkVsHitsInvalid ->Fill(trackStruct.trkParams.hitsInvalid,(*iHit).errXTrk);
      (*iSec).second.SigmaXTrkVsLayersMissed->Fill(trackStruct.trkParams.layersMissed,(*iHit).errXTrk);
      (*iSec).second.SigmaXVsNorChi2        ->Fill(trackStruct.trkParams.norChi2,(*iHit).errX);
      
      (*iSec).second.SigmaXHitVsPhiSens     ->Fill((*iHit).phiSens*180./M_PI,(*iHit).errXHit);
      (*iSec).second.SigmaXHitVsPhiSensX    ->Fill((*iHit).phiSensX*180./M_PI,(*iHit).errXHit);
      (*iSec).second.SigmaXHitVsPhiSensY    ->Fill((*iHit).phiSensY*180./M_PI,(*iHit).errXHit);
      (*iSec).second.SigmaXTrkVsPhiSens     ->Fill((*iHit).phiSens*180./M_PI,(*iHit).errXTrk);
      (*iSec).second.SigmaXTrkVsPhiSensX    ->Fill((*iHit).phiSensX*180./M_PI,(*iHit).errXTrk);
      (*iSec).second.SigmaXTrkVsPhiSensY    ->Fill((*iHit).phiSensY*180./M_PI,(*iHit).errXTrk);
      (*iSec).second.SigmaXVsPhiSens        ->Fill((*iHit).phiSens*180./M_PI,(*iHit).errX);
      (*iSec).second.SigmaXVsPhiSensX       ->Fill((*iHit).phiSensX*180./M_PI,(*iHit).errX);
      (*iSec).second.SigmaXVsPhiSensY       ->Fill((*iHit).phiSensY*180./M_PI,(*iHit).errX);
      
      (*iSec).second.NorResXVsSigmaXHit     ->Fill((*iHit).errXHit,(*iHit).norResX);
      (*iSec).second.NorResXVsSigmaXTrk     ->Fill((*iHit).errXTrk,(*iHit).norResX);
      (*iSec).second.NorResXVsSigmaX        ->Fill((*iHit).errX,(*iHit).norResX);
      
      (*iSec).second.WidthVsPhiSensX        ->Fill((*iHit).phiSensX*180./M_PI,(*iHit).width);
      
      (*iSec).second.PNorResXVsWidth         ->Fill((*iHit).width,(*iHit).norResX);
      (*iSec).second.PNorResXVsCharge        ->Fill((*iHit).charge,(*iHit).norResX);
      (*iSec).second.PNorResXVsChargeLR      ->Fill((*iHit).chargeLR,(*iHit).norResX);
      (*iSec).second.PNorResXVsMaxStrip      ->Fill((*iHit).maxStrip,(*iHit).norResX);
      (*iSec).second.PNorResXVsMaxCharge     ->Fill((*iHit).maxCharge,(*iHit).norResX);
      (*iSec).second.PNorResXVsMaxIndex      ->Fill((*iHit).maxIndex,(*iHit).norResX);
      (*iSec).second.PNorResXVsBaryStrip     ->Fill((*iHit).baryStrip,(*iHit).norResX);
      (*iSec).second.PNorResXVsSOverN        ->Fill((*iHit).sOverN,(*iHit).norResX);
      
      (*iSec).second.PNorResXVsP             ->Fill(trackStruct.trkParams.p,(*iHit).norResX);
      (*iSec).second.PNorResXVsMeanAngle     ->Fill(trackStruct.trkParams.meanPhiSensToNorm*180./M_PI,(*iHit).norResX);
      (*iSec).second.PNorResXVsHitsValid     ->Fill(trackStruct.trkParams.hitsValid,(*iHit).norResX);
      (*iSec).second.PNorResXVsHitsGood      ->Fill(goodHitsPerTrack,(*iHit).norResX);
      (*iSec).second.PNorResXVsHitsInvalid   ->Fill(trackStruct.trkParams.hitsInvalid,(*iHit).norResX);
      (*iSec).second.PNorResXVsLayersMissed  ->Fill(trackStruct.trkParams.layersMissed,(*iHit).norResX);
      (*iSec).second.PNorResXVsNorChi2       ->Fill(trackStruct.trkParams.norChi2,(*iHit).norResX);
      
      (*iSec).second.PNorResXVsPhiSens       ->Fill((*iHit).phiSens*180./M_PI,(*iHit).norResX);
      (*iSec).second.PNorResXVsPhiSensX      ->Fill((*iHit).phiSensX*180./M_PI,(*iHit).norResX);
      (*iSec).second.PNorResXVsPhiSensY      ->Fill((*iHit).phiSensY*180./M_PI,(*iHit).norResX);
      
      (*iSec).second.PSigmaXHitVsWidth       ->Fill((*iHit).width,(*iHit).errXHit);
      (*iSec).second.PSigmaXHitVsCharge      ->Fill((*iHit).charge,(*iHit).errXHit);
      (*iSec).second.PSigmaXHitVsChargeLR    ->Fill((*iHit).chargeLR,(*iHit).errXHit);
      (*iSec).second.PSigmaXHitVsMaxStrip    ->Fill((*iHit).maxStrip,(*iHit).errXHit);
      (*iSec).second.PSigmaXHitVsMaxCharge   ->Fill((*iHit).maxCharge,(*iHit).errXHit);
      (*iSec).second.PSigmaXHitVsMaxIndex    ->Fill((*iHit).maxIndex,(*iHit).errXHit);
      (*iSec).second.PSigmaXHitVsBaryStrip   ->Fill((*iHit).baryStrip,(*iHit).errXHit);
      (*iSec).second.PSigmaXHitVsSOverN      ->Fill((*iHit).sOverN,(*iHit).errXHit);
      
      (*iSec).second.PSigmaXTrkVsP	     ->Fill(trackStruct.trkParams.p,(*iHit).errXTrk);
      (*iSec).second.PSigmaXTrkVsInvP        ->Fill(1./trackStruct.trkParams.p,(*iHit).errXTrk);
      (*iSec).second.PSigmaXTrkVsMeanAngle   ->Fill(trackStruct.trkParams.meanPhiSensToNorm*180./M_PI,(*iHit).errXTrk);
      (*iSec).second.PSigmaXTrkVsHitsValid   ->Fill(trackStruct.trkParams.hitsValid,(*iHit).errXTrk);
      (*iSec).second.PSigmaXTrkVsHitsGood    ->Fill(goodHitsPerTrack,(*iHit).errXTrk);
      (*iSec).second.PSigmaXTrkVsHitsInvalid ->Fill(trackStruct.trkParams.hitsInvalid,(*iHit).errXTrk);
      (*iSec).second.PSigmaXTrkVsLayersMissed->Fill(trackStruct.trkParams.layersMissed,(*iHit).errXTrk);
      (*iSec).second.PSigmaXVsNorChi2        ->Fill(trackStruct.trkParams.norChi2,(*iHit).errX);
      
      (*iSec).second.PSigmaXHitVsPhiSens     ->Fill((*iHit).phiSens*180./M_PI,(*iHit).errXHit);
      (*iSec).second.PSigmaXHitVsPhiSensX    ->Fill((*iHit).phiSensX*180./M_PI,(*iHit).errXHit);
      (*iSec).second.PSigmaXHitVsPhiSensY    ->Fill((*iHit).phiSensY*180./M_PI,(*iHit).errXHit);
      (*iSec).second.PSigmaXTrkVsPhiSens     ->Fill((*iHit).phiSens*180./M_PI,(*iHit).errXTrk);
      (*iSec).second.PSigmaXTrkVsPhiSensX    ->Fill((*iHit).phiSensX*180./M_PI,(*iHit).errXTrk);
      (*iSec).second.PSigmaXTrkVsPhiSensY    ->Fill((*iHit).phiSensY*180./M_PI,(*iHit).errXTrk);
      (*iSec).second.PSigmaXVsPhiSens        ->Fill((*iHit).phiSens*180./M_PI,(*iHit).errX);
      (*iSec).second.PSigmaXVsPhiSensX       ->Fill((*iHit).phiSensX*180./M_PI,(*iHit).errX);
      (*iSec).second.PSigmaXVsPhiSensY       ->Fill((*iHit).phiSensY*180./M_PI,(*iHit).errX);
      
      (*iSec).second.PNorResXVsSigmaXHit     ->Fill((*iHit).errXHit,(*iHit).norResX);
      (*iSec).second.PNorResXVsSigmaXTrk     ->Fill((*iHit).errXTrk,(*iHit).norResX);
      (*iSec).second.PNorResXVsSigmaX        ->Fill((*iHit).errX,(*iHit).norResX);
      
      (*iSec).second.PWidthVsPhiSensX        ->Fill((*iHit).phiSensX*180./M_PI,(*iHit).width);
      
      for(std::map<std::string,std::vector<TH1*> >::iterator iMap = (*iSec).second.mSigmaX.begin(); iMap != (*iSec).second.mSigmaX.end(); ++iMap){
        for(std::vector<TH1*>::iterator iHist = (*iMap).second.begin(); iHist != (*iMap).second.end(); ++iHist){
	  if     ((*iMap).first=="sigmaXHit")(*iHist)->Fill((*iHit).errXHit);
	  else if((*iMap).first=="sigmaXTrk")(*iHist)->Fill((*iHit).errXTrk);
	  else if((*iMap).first=="sigmaX")   (*iHist)->Fill((*iHit).errX);
	}
      }
      
      for(std::map<unsigned int,std::pair<double,double> >::const_iterator iErrBins = mResErrBins_.begin();
          iErrBins != mResErrBins_.end(); ++iErrBins){
	if((*iHit).errX < (*iErrBins).second.first || (*iHit).errX >= (*iErrBins).second.second){
	  continue;
	}
	(*iSec).second.mBinnedHists[(*iErrBins).first]["sigmaX"] ->Fill((*iHit).errX);
	(*iSec).second.mBinnedHists[(*iErrBins).first]["norResX"]->Fill((*iHit).norResX);
      }
      
    }
  }
}


// -----------------------------------------------------------------------------------------------------------



void
ApeEstimator::calculateAPE(){
   for(std::map<unsigned int,TrackerSectorStruct>::iterator iSec = mTkSector_.begin(); iSec != mTkSector_.end(); ++iSec){
     for(std::map<unsigned int, std::map<std::string,TH1*> >::const_iterator iErrBins = (*iSec).second.mBinnedHists.begin();
         iErrBins != (*iSec).second.mBinnedHists.end(); ++iErrBins){
       std::map<std::string,TH1*> mHists = (*iErrBins).second;
       
       
       
       double entries = mHists["sigmaX"]->GetEntries();
       
       if(entries<0.1){  // There are no entries outside histo range (over-, underflow) possible
//         edm::LogWarning("CalculateAPE")<<"\nNo valid entry in histogram \"sigmaX\" in error bin "<<(*iErrBins).first<<" of sector "<<(*iSec).first<<", APE is not calculated\n";
	 //continue;
       }
       
       double meanSigmaX = mHists["sigmaX"]->GetMean();
       
       // Fitting Parameters
       double xMin     = mHists["norResX"]->GetXaxis()->GetXmin(),
              xMax     = mHists["norResX"]->GetXaxis()->GetXmax(),
	      integral = mHists["norResX"]->Integral(),
	      mean     = mHists["norResX"]->GetMean(),
	      rms      = mHists["norResX"]->GetRMS();
       
       //if(integral<0.1){  // There might be all entries outside histo range
       //  edm::LogWarning("CalculateAPE")<<"\nNo valid entry in histogram \"norResX\" in error bin "<<(*iErrBins).first<<" of sector "<<(*iSec).first<<", APE is not calculated\n";
       //  continue;
       //}
       
       
       
//       std::cout<<"Test0a\t"<<entries<<"\t"<<integral<<"\n";
       
       // First Gaus Fit
       TF1 func1("mygaus", "gaus", xMin, xMax);
       func1.SetParameters(integral, mean, rms);
       TString fitOpt("RQ"); //TString fitOpt("IMR"); ("IRLL"); ("IRQ");
       if(mHists["norResX"]->Fit(&func1, fitOpt)){
//         edm::LogWarning("CalculateAPE")<<"Fit1 did not work: "<<mHists["norResX"]->Fit(&func1, fitOpt);
	 continue;
       }
       Int_t fitResult = mHists["norResX"]->Fit(&func1, fitOpt);
//       std::cout<<"FitResult1\t"<<fitResult<<"\n";
       
//       std::cout<<"Test0b\n";
       
       // Second Gaus Fit
       TF1 *newFunc1 = mHists["norResX"]->GetFunction(func1.GetName());
       
       Double_t mean1  = newFunc1->GetParameter(1);
       Double_t sigma1 = newFunc1->GetParameter(2);
       
       TF1 func2("mygaus2","gaus",mean1 - 2.0 * TMath::Abs(sigma1),mean1 + 2.0 * TMath::Abs(sigma1));
       func2.SetParameters(newFunc1->GetParameter(0),newFunc1->GetParameter(1),newFunc1->GetParameter(2));
       if(mHists["norResX"]->Fit(&func2, fitOpt)){
//         edm::LogWarning("CalculateAPE")<<"Fit2 did not work: "<<mHists["norResX"]->Fit(&func2, fitOpt);
	 continue;
       }
       fitResult = mHists["norResX"]->Fit(&func2, fitOpt);
//       std::cout<<"FitResult2\t"<<fitResult<<"\n";
//       std::cout<<"Test1\n";
       
       TF1 *newFunc2 = mHists["norResX"]->GetFunction(func2.GetName());
       mean1  = newFunc2->GetParameter(1);
       sigma1 = newFunc2->GetParameter(2);
       
//       std::cout<<"Test2\n";
       
       double fitMean = mean1;
       double residualWidth = sigma1;
       
       double ape = meanSigmaX*sqrt(residualWidth*residualWidth -1);
       if(isnan(ape))ape = -0.0010;
       
       (*iSec).second.Entries       ->SetBinContent((*iErrBins).first,integral);
       (*iSec).second.MeanX         ->SetBinContent((*iErrBins).first,mean);
       (*iSec).second.RmsX          ->SetBinContent((*iErrBins).first,rms);
       
       if(entries<100.){fitMean = 0; ape = residualWidth = -0.0010;}
       
       //std::cout<<"\n\nSector, Bin "<<(*iSec).first<<"\t"<<(*iErrBins).first;
       //std::cout<<"\nEntries, MeanError, ResWidth, APE \t"<<entries<<"\t"<<meanSigmaX<<"\t"<<residualWidth<<"\t"<<ape<<"\n";
       (*iSec).second.FitMeanX      ->SetBinContent((*iErrBins).first,fitMean);
       (*iSec).second.ResidualWidthX->SetBinContent((*iErrBins).first,residualWidth);
       (*iSec).second.ApeX          ->SetBinContent((*iErrBins).first,ape);
     }
   }
}






// -----------------------------------------------------------------------------------------------------------


bool
ApeEstimator::isHit2D(const TrackingRecHit &hit) const
{
  // we count SiStrip stereo modules as 2D if selected via countStereoHitAs2D_
  // (since they provide theta information)
  if (!hit.isValid() || hit.dimension() < 2) {
    return false; // some (muon...) stuff really has RecHit1D
  } else {
    const DetId detId(hit.geographicalId());
    if (detId.det() == DetId::Tracker) {
      if (detId.subdetId() == PixelSubdetector::PixelBarrel || detId.subdetId() == PixelSubdetector::PixelEndcap) {
        return true; // pixel is always 2D
      } else { // should be SiStrip now
	const SiStripDetId stripId(detId);
	if (stripId.stereo()) return true; // 1D stereo modules ALWAYS as 2D hits
        else if (dynamic_cast<const SiStripRecHit2D*>(&hit)) return false; // normal hit
        else if (dynamic_cast<const SiStripMatchedRecHit2D*>(&hit)) return true; // matched is 2D
        else if (dynamic_cast<const ProjectedSiStripRecHit2D*>(&hit)) {
	  const ProjectedSiStripRecHit2D* pH = static_cast<const ProjectedSiStripRecHit2D*>(&hit);
	  return (true && this->isHit2D(pH->originalHit())); // depends on original...
	} else {
          edm::LogError("UnkownType") << "@SUB=ApeEstimator::isHit2D"
                                      << "Tracker hit not in pixel and neither SiStripRecHit2D nor "
                                      << "SiStripMatchedRecHit2D nor ProjectedSiStripRecHit2D.";
          return false;
        }
      }
    } else { // not tracker??
      edm::LogWarning("DetectorMismatch") << "@SUB=AlignmentTrackSelector::isHit2D"
                                          << "Hit not in tracker with 'official' dimension >=2.";
      return true; // dimension() >= 2 so accept that...
    }
  }
  // never reached...
}



// -----------------------------------------------------------------------------------------------------------

// ------------ method called to for each event  ------------
void
ApeEstimator::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   //using namespace edm;

   //edm::Handle<reco::TrackCollection> tracks;
   
   edm::InputTag tjTag = theParameterSet.getParameter<edm::InputTag>("tjTkAssociationMapTag");
   edm::Handle<TrajTrackAssociationCollection> m_TrajTracksMap;
   iEvent.getByLabel(tjTag, m_TrajTracksMap);
   
   tkDetector_.TrkSize->Fill(m_TrajTracksMap->size());
   if(maxTracksPerEvent_!=0 && m_TrajTracksMap->size()>maxTracksPerEvent_)return;
   
   //Creation of (traj,track)
   typedef std::pair<const Trajectory*, const reco::Track*> ConstTrajTrackPair;
   typedef std::vector<ConstTrajTrackPair> ConstTrajTrackPairCollection;
   ConstTrajTrackPairCollection trajTracks;
   
   TrajTrackAssociationCollection::const_iterator iPair;
   for(iPair = m_TrajTracksMap->begin();iPair != m_TrajTracksMap->end();++iPair){
     trajTracks.push_back(ConstTrajTrackPair(&(*(*iPair).key), &(*(*iPair).val)));
   }
   
   //static TrajectoryStateCombiner tsoscomb;
   
   //Loop over Tracks & Hits
   ConstTrajTrackPairCollection::const_iterator iTrack;
   for(iTrack = trajTracks.begin(); iTrack != trajTracks.end();++iTrack){
     
     const Trajectory *traj = (*iTrack).first;
     const reco::Track *track = (*iTrack).second;
     
     TrackStruct trackStruct;
     trackStruct.trkParams = this->fillTrackVariables(*track, *traj);
     
     if(trackCut_)continue;
     
     const std::vector<TrajectoryMeasurement> meass = (*traj).measurements();
     
     //Loop over Hits
     for(std::vector<TrajectoryMeasurement>::const_iterator iMeass = meass.begin(); iMeass != meass.end(); ++iMeass){
       TrackStruct::HitParameterStruct hitParams = this->fillHitVariables(*iMeass, iSetup);
       if(this->hitSelected(hitParams))trackStruct.vHitParams.push_back(hitParams);
     }
     
     this->fillHists(trackStruct);
   }
}


// ------------ method called once each job just before starting event loop  ------------
void 
ApeEstimator::beginJob(){
   
   this->hitSelection();
   
   this->sectorBuilder();
   
   this->residualErrorBinning();
   
   this->bookSectorHists();
   
   this->bookTrackHists();
   
   
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ApeEstimator::endJob() {
   
   this->calculateAPE();
   
   edm::LogInfo("HitSelector")<<"\nThere are "<<counter1<< " negative Errors calculated\n";
}

//define this as a plug-in
DEFINE_FWK_MODULE(ApeEstimator);
