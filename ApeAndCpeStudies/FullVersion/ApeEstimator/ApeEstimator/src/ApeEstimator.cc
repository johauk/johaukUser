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
// $Id: ApeEstimator.cc,v 1.9 2010/07/26 13:18:49 hauk Exp $
//
//


// system include files
#include <memory>
#include <sstream>
#include <fstream>

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
#include "CommonTools/Utils/interface/TFileDirectory.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/CLHEP/interface/AlgebraicObjects.h"
#include "DataFormats/CLHEP/interface/Migration.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/TrackerRecHit2D/interface/SiStripRecHit1D.h"
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

#include "RecoLocalTracker/SiStripClusterizer/interface/SiStripClusterInfo.h"

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
#include "TMath.h"


#include "RecoLocalTracker/SiStripRecHitConverter/interface/StripCPE.h"
#include "Geometry/CommonTopologies/interface/StripTopology.h"

#include "MagneticField/Engine/interface/MagneticField.h"
#include "CondFormats/SiStripObjects/interface/SiStripLorentzAngle.h"
#include "DataFormats/GeometryVector/interface/LocalVector.h"
#include "DataFormats/GeometrySurface/interface/Bounds.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "CondFormats/DataRecord/interface/SiStripLorentzAngleRcd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "FWCore/Utilities/interface/EDMException.h"

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
      
      void bookSectorHistsForAnalyzerMode();
      void bookSectorHistsForApeCalculation();
      void bookTrackHists();
      
      TrackStruct::TrackParameterStruct fillTrackVariables(const reco::Track&, const Trajectory&, const reco::BeamSpot&);
      TrackStruct::HitParameterStruct fillHitVariables(const TrajectoryMeasurement&, const edm::EventSetup&);
      
      void hitSelection();
      void setHitSelectionMap(const std::string&);
      void setHitSelectionMapUInt(const std::string&);
      bool hitSelected(const TrackStruct::HitParameterStruct&)const;
      
      void fillHistsForAnalyzerMode(const TrackStruct&);
      void fillHistsForApeCalculation(const TrackStruct&);
      
      void calculateAPE();
      
      // ----------member data ---------------------------
      edm::ParameterSet parameterSet_;
      std::map<unsigned int, TrackerSectorStruct> mTkSector_;
      TrackerDetectorStruct tkDetector_;
      
      std::map<unsigned int, std::pair<double,double> > mResErrBins_;
      
      std::map<unsigned int, ReducedTrackerTreeVariables> mTkTreeVar_;
      
      std::map<std::string,std::vector<double> > mHitSelection_;
      std::map<std::string,std::vector<unsigned int> > mHitSelectionUInt_;
      
      bool trackCut_;
      
      const unsigned int maxTracksPerEvent_;
      const unsigned int minGoodHitsPerTrack_;
      
      const bool analyzerMode_;
      
      const bool calculateApe_;
      
      unsigned int counter1, counter2, counter3, counter4, counter5, counter6;
      
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
parameterSet_(iConfig), trackCut_(false), maxTracksPerEvent_(parameterSet_.getParameter<unsigned int>("maxTracksPerEvent")),
minGoodHitsPerTrack_(parameterSet_.getParameter<unsigned int>("minGoodHitsPerTrack")),
analyzerMode_(parameterSet_.getParameter<bool>("analyzerMode")),
calculateApe_(parameterSet_.getParameter<bool>("calculateApe"))
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
  
  TFile* tkTreeFile(TFile::Open((parameterSet_.getParameter<std::string>("TrackerTreeFile")).c_str()));
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
  std::vector<edm::ParameterSet> vSectors(parameterSet_.getParameter<std::vector<edm::ParameterSet> >("Sectors"));
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
                                    <<"\n... sector selection is not applied, sector "<<sectorCounter<<" is not built";
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
  bool commonModules(false);
  for(std::map<unsigned int,TrackerSectorStruct>::const_iterator iSec = mTkSector_.begin(); iSec != mTkSector_.end(); ++iSec){
    std::map<unsigned int,TrackerSectorStruct>::const_iterator iSec2(iSec);
    for(++iSec2; iSec2 != mTkSector_.end(); ++iSec2){
      unsigned int nCommonModules(0);
      for(std::vector<unsigned int>::const_iterator iMod = (*iSec).second.vRawId.begin(); iMod != (*iSec).second.vRawId.end(); ++iMod){
        for(std::vector<unsigned int>::const_iterator iMod2 = (*iSec2).second.vRawId.begin(); iMod2 != (*iSec2).second.vRawId.end(); ++iMod2){
          if(*iMod2 == *iMod)++nCommonModules;
        }
      }
      if(nCommonModules==0)
        ;//edm::LogInfo("SectorBuilder")<<"Sector "<<(*iSec).first<<" and Sector "<<(*iSec2).first<< " have ZERO Modules in common";
      else{
        edm::LogError("SectorBuilder")<<"Sector "<<(*iSec).first<<" and Sector "<<(*iSec2).first<< " have "<<nCommonModules<<" Modules in common";
        commonModules = true;
      }
    }
  }
  if(static_cast<int>(allSectors.vRawId.size())==nModules)
    edm::LogInfo("SectorBuilder")<<"ALL Tracker Modules are contained in the Sectors";
  else
    edm::LogWarning("SectorBuilder")<<"There are "<<allSectors.vRawId.size()<<" Modules in all Sectors"
                               <<" out of "<<nModules<<" Tracker Modules";
  if(!commonModules)
    edm::LogInfo("SectorBuilder")<<"There are ZERO modules associated to different sectors, no ambiguities exist";
  else
  edm::LogError("SectorBuilder")<<"There are modules associated to different sectors, APE value cannot be assigned reasonably";
}


// -----------------------------------------------------------------------------------------------------------


void
ApeEstimator::residualErrorBinning(){
   std::vector<double> vResidualErrorBinning(parameterSet_.getParameter<std::vector<double> >("residualErrorBinning"));
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
ApeEstimator::bookSectorHistsForAnalyzerMode(){
  
  std::vector<unsigned int> vErrHists(parameterSet_.getParameter<std::vector<unsigned int> >("vErrHists"));
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
    
    bool zoomHists(parameterSet_.getParameter<bool>("zoomHists"));
    
    double widthMax = zoomHists ? 20. : 200.;
    double chargeMax = zoomHists ? 1000. : 10000.;
    double sOverNMax = zoomHists? 200. : 2000.;
    
    double resXAbsMax = zoomHists ? 0.5 : 5.;
    double norResXAbsMax = zoomHists ? 10. : 50.;
    double probXMin = zoomHists ? -0.01 :  -0.1;
    double probXMax = zoomHists ? 0.11 :  1.1;
    double sigmaXMin = zoomHists ? 0. : -0.05;
    double sigmaXMax = zoomHists ? 0.1 : 1.;
    double sigmaX2Max = sigmaXMax*sigmaXMax;
    double sigmaXHitMax = zoomHists ? 0.02 : 1.;
    
    double norChi2Max = zoomHists ? 20. : 1000.;
    double d0Max = zoomHists ? 0.2 : 40.;  // cosmics: 100.|100.
    double dzMax = zoomHists ? 10. : 100.;  // cosmics: 200.|600.
    double pMax = zoomHists ? 100. : 2000.;
    double invPMax = zoomHists ? 0.05 : 10.;   //begins at 20GeV, 0.1GeV
    
    
    edm::Service<TFileService> fileService;
    if(!fileService){
      throw edm::Exception( edm::errors::Configuration,
                            "TFileService is not registered in cfg file" );
    }
    
    std::stringstream sector; sector << "Sector_" << (*iSec).first;
    TFileDirectory secDir = fileService->mkdir(sector.str().c_str());
    
    
    // Cluster Parameters
    (*iSec).second.setCorrHistParams(&secDir,norResXAbsMax,sigmaXHitMax,sigmaXMax);
    (*iSec).second.mCorrelationHists["Width"] = (*iSec).second.bookCorrHists("Width","cluster width","w_{cl}","[# strips]",200,20,0.,widthMax,"nph");
    (*iSec).second.mCorrelationHists["Charge"] = (*iSec).second.bookCorrHists("Charge","cluster charge","c_{cl}","[APV counts]",100,50,0.,chargeMax,"nph");
    (*iSec).second.mCorrelationHists["MaxStrip"] = (*iSec).second.bookCorrHists("MaxStrip","strip with max. charge","n_{cl,max}","[# strips]",800,800,-10.,790.,"npht");
    (*iSec).second.mCorrelationHists["MaxCharge"] = (*iSec).second.bookCorrHists("MaxCharge","charge of strip with max. charge","c_{cl,max}","[APV counts]",300,75,-10.,290.,"nph");
    (*iSec).second.mCorrelationHists["MaxIndex"] = (*iSec).second.bookCorrHists("MaxIndex","cluster-index of strip with max. charge","i_{cl,max}","[# strips]",10,10,0.,10.,"nph");
    (*iSec).second.mCorrelationHists["ChargeOnEdges"] = (*iSec).second.bookCorrHists("ChargeOnEdges","fraction of charge on edge strips","(c_{cl,L}+c_{cl,R})/c_{cl}","",60,60,-0.1,1.1,"nph");
    (*iSec).second.mCorrelationHists["ChargeAsymmetry"] = (*iSec).second.bookCorrHists("ChargeAsymmetry","asymmetry of charge on edge strips","(c_{cl,L}-c_{cl,R})/c_{cl}","",110,55,-1.1,1.1,"nph");
    (*iSec).second.mCorrelationHists["BaryStrip"] = (*iSec).second.bookCorrHists("BaryStrip","barycenter of cluster charge","b_{cl}","[# strips]",800,100,-10.,790.,"nph");
    (*iSec).second.mCorrelationHists["SOverN"] = (*iSec).second.bookCorrHists("SOverN","signal over noise","s/N","",100,50,0,sOverNMax,"nph");
    (*iSec).second.mCorrelationHists["WidthProj"] = (*iSec).second.bookCorrHists("WidthProj","projected width","w_{p}","[# strips]",200,20,0.,widthMax,"nph");
    (*iSec).second.mCorrelationHists["WidthDiff"] = (*iSec).second.bookCorrHists("WidthDiff","width difference","w_{p} - w_{cl}","[# strips]",200,20,-widthMax/2.,widthMax/2.,"nph");
    
    (*iSec).second.WidthVsWidthProjected = secDir.make<TH2F>("h2_widthVsWidthProj","w_{cl} vs. w_{p};w_{p}  [# strips];w_{cl}  [# strips]",static_cast<int>(widthMax),0,widthMax,static_cast<int>(widthMax),0,widthMax);
    (*iSec).second.PWidthVsWidthProjected = secDir.make<TProfile>("p_widthVsWidthProj","w_{cl} vs. w_{p};w_{p}  [# strips];w_{cl}  [# strips]",static_cast<int>(widthMax),0,widthMax);
    
    (*iSec).second.WidthDiffVsMaxStrip = secDir.make<TH2F>("h2_widthDiffVsMaxStrip","(w_{p} - w_{cl}) vs. n_{cl,max};n_{cl,max};w_{p} - w_{cl}  [# strips]",800,-10.,790.,static_cast<int>(widthMax),-widthMax/2.,widthMax/2.);
    (*iSec).second.PWidthDiffVsMaxStrip = secDir.make<TProfile>("p_widthDiffVsMaxStrip","(w_{p} - w_{cl}) vs. n_{cl,max};n_{cl,max};w_{p} - w_{cl}  [# strips]",800,-10.,790.);
    
    (*iSec).second.WidthDiffVsSigmaXHit = secDir.make<TH2F>("h2_widthDiffVsSigmaXHit","(w_{p} - w_{cl}) vs. #sigma_{x,hit};#sigma_{x,hit}  [cm];w_{p} - w_{cl}  [# strips]",100,0.,sigmaXMax,100,-10.,10.);
    (*iSec).second.PWidthDiffVsSigmaXHit = secDir.make<TProfile>("p_widthDiffVsSigmaXHit","(w_{p} - w_{cl}) vs. #sigma_{x,hit};#sigma_{x,hit}  [cm];w_{p} - w_{cl}  [# strips]",100,0.,sigmaXMax);
    
    
    // Hit Parameters
    (*iSec).second.mCorrelationHists["SigmaXHit"] = (*iSec).second.bookCorrHists("SigmaXHit","hit error","#sigma_{x,hit}","[cm]",105,20,sigmaXMin,sigmaXMax,"np");
    (*iSec).second.mCorrelationHists["SigmaXTrk"] = (*iSec).second.bookCorrHists("SigmaXTrk","track error","#sigma_{x,track}","[cm]",105,20,sigmaXMin,sigmaXMax,"np");
    (*iSec).second.mCorrelationHists["SigmaX"]    = (*iSec).second.bookCorrHists("SigmaX","residual error","#sigma_{x}","[cm]",105,20,sigmaXMin,sigmaXMax,"np");
    (*iSec).second.mCorrelationHists["PhiSens"]   = (*iSec).second.bookCorrHists("PhiSens","track angle on sensor","#phi_{module}","[ ^{o}]",94,47,-2,92,"nphtr");
    (*iSec).second.mCorrelationHists["PhiSensX"]  = (*iSec).second.bookCorrHists("PhiSensX","track angle on sensor","#phi_{x,module}","[ ^{o}]",184,92,-92,92,"nphtr");
    (*iSec).second.mCorrelationHists["PhiSensY"]  = (*iSec).second.bookCorrHists("PhiSensY","track angle on sensor","#phi_{y,module}","[ ^{o}]",184,92,-92,92,"nphtr");
    
    (*iSec).second.XHit    = secDir.make<TH1F>("h_XHit"," hit measurement x_{hit};x_{hit}  [cm];# hits",100,-20,20);
    (*iSec).second.XTrk    = secDir.make<TH1F>("h_XTrk","track prediction x_{track};x_{track}  [cm];# hits",100,-20,20);
    (*iSec).second.SigmaX2 = secDir.make<TH1F>("h_SigmaX2","squared residual error #sigma_{x}^{2};#sigma_{x}^{2}  [cm^{2}];# hits",105,sigmaXMin,sigmaX2Max); //no mistake !
    (*iSec).second.ResX    = secDir.make<TH1F>("h_ResX","residual r_{x};(x_{track}-x_{hit})'  [cm];# hits",100,-resXAbsMax,resXAbsMax);
    (*iSec).second.NorResX = secDir.make<TH1F>("h_NorResX","normalized residual r_{x}/#sigma_{x};(x_{track}-x_{hit})'/#sigma_{x};# hits",100,-norResXAbsMax,norResXAbsMax);
    (*iSec).second.ProbX   = secDir.make<TH1F>("h_ProbX","residual probability;prob(r_{x}^{2}/#sigma_{x}^{2},1);# hits",60,probXMin,probXMax);
    
    (*iSec).second.WidthVsPhiSensX = secDir.make<TH2F>("h2_widthVsPhiSensX","w_{cl} vs. #phi_{x,module};#phi_{x,module}  [ ^{o}];w_{cl}  [# strips]",92,-92,92,static_cast<int>(widthMax),0,widthMax);
    (*iSec).second.PWidthVsPhiSensX = secDir.make<TProfile>("p_widthVsPhiSensX","w_{cl} vs. #phi_{x,module};#phi_{x,module}  [ ^{o}];w_{cl}  [# strips]",92,-92,92);
    
    
    // Track Parameters
    (*iSec).second.mCorrelationHists["HitsValid"] = (*iSec).second.bookCorrHists("HitsValid","# hits","[valid]",50,0,50,"npt");
    (*iSec).second.mCorrelationHists["HitsGood"] = (*iSec).second.bookCorrHists("HitsGood","# hits","[good]",50,0,50,"npt");
    (*iSec).second.mCorrelationHists["HitsInvalid"] = (*iSec).second.bookCorrHists("HitsInvalid","# hits","[invalid]",20,0,20,"npt");
    (*iSec).second.mCorrelationHists["LayersMissed"] = (*iSec).second.bookCorrHists("LayersMissed","# layers","[missed]",10,0,10,"npt");
    (*iSec).second.mCorrelationHists["NorChi2"] = (*iSec).second.bookCorrHists("NorChi2","#chi^{2}/ndof","",50,0,norChi2Max,"npr");
    (*iSec).second.mCorrelationHists["Theta"] = (*iSec).second.bookCorrHists("Theta","#theta","[ ^{o}]",40,-10,190,"npt");
    (*iSec).second.mCorrelationHists["Phi"] = (*iSec).second.bookCorrHists("Phi","#phi","[ ^{o}]",76,-190,190,"npt");
    (*iSec).second.mCorrelationHists["D0Beamspot"] = (*iSec).second.bookCorrHists("D0Beamspot","d_{0, BS}","[cm]",40,-d0Max,d0Max,"npt");
    (*iSec).second.mCorrelationHists["Dz"] = (*iSec).second.bookCorrHists("Dz","d_{z}","[cm]",40,-dzMax,dzMax,"npt");
    (*iSec).second.mCorrelationHists["Pt"] = (*iSec).second.bookCorrHists("Pt","p_{t}","[GeV]",50,0,pMax,"npt");
    (*iSec).second.mCorrelationHists["P"] = (*iSec).second.bookCorrHists("P","|p|","[GeV]",50,0,pMax,"npt");
    (*iSec).second.mCorrelationHists["InvP"] = (*iSec).second.bookCorrHists("InvP","1/|p|","[GeV^{-1}]",25,0,invPMax,"t");
    (*iSec).second.mCorrelationHists["MeanAngle"] = (*iSec).second.bookCorrHists("MeanAngle","<#phi_{module}>","[ ^{o}]",25,-5,95,"npt");
    //(*iSec).second.mCorrelationHists[""] = (*iSec).second.bookCorrHists("","","",,,,"nphtr");
    
    
    
    
    
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
    
  }
}



void
ApeEstimator::bookSectorHistsForApeCalculation(){
  
  std::vector<unsigned int> vErrHists(parameterSet_.getParameter<std::vector<unsigned int> >("vErrHists"));
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
    
    
    edm::Service<TFileService> fileService;
    if(!fileService){
      throw edm::Exception( edm::errors::Configuration,
                            "TFileService is not registered in cfg file" );
    }
    
    std::stringstream sector; sector << "Sector_" << (*iSec).first;
    TFileDirectory secDir = fileService->mkdir(sector.str().c_str());
    
    
    
    if(!calculateApe_)continue;
    
    if(mResErrBins_.size()==0){mResErrBins_[1].first = 0.;mResErrBins_[1].second = 0.01;} // default if no selection taken into account: calculate APE with one bin with residual error 0-100um
    for(std::map<unsigned int,std::pair<double,double> >::const_iterator iErrBins = mResErrBins_.begin();
         iErrBins != mResErrBins_.end(); ++iErrBins){
      std::stringstream interval; interval << "Interval_" << (*iErrBins).first;
      TFileDirectory intDir = secDir.mkdir(interval.str().c_str());
      (*iSec).second.mBinnedHists[(*iErrBins).first]["sigmaX"]  = intDir.make<TH1F>("h_sigmaX","residual error #sigma_{x};#sigma_{x}  [cm];# hits",100,0.,0.01);
      (*iSec).second.mBinnedHists[(*iErrBins).first]["norResX"] = intDir.make<TH1F>("h_norResX","normalized residual r_{x}/#sigma_{x};(x_{track}-x_{hit})'/#sigma_{x};# hits",100,-10,10);
    }
    
    //Result plots (one hist per sector containing one bin per interval)
    std::vector<double> vBinX(parameterSet_.getParameter<std::vector<double> >("residualErrorBinning"));
    TFileDirectory resDir = secDir.mkdir("Results");
    (*iSec).second.Entries         = resDir.make<TH1F>("h_entries","# hits used;#sigma_{x}  [cm];# hits",vBinX.size()-1,&(vBinX[0]));
    (*iSec).second.MeanX           = resDir.make<TH1F>("h_meanX","residual mean <r_{x}/#sigma_{x}>;#sigma_{x}  [cm];<r_{x}/#sigma_{x}>",vBinX.size()-1,&(vBinX[0]));
    (*iSec).second.RmsX            = resDir.make<TH1F>("h_rmsX","residual rms RMS(r_{x}/#sigma_{x});#sigma_{x}  [cm];RMS(r_{x}/#sigma_{x})",vBinX.size()-1,&(vBinX[0]));
    (*iSec).second.FitMeanX1       = resDir.make<TH1F>("h_fitMeanX1","fitted residual mean #mu_{x};#sigma_{x}  [cm];#mu_{x}",vBinX.size()-1,&(vBinX[0]));
    (*iSec).second.ResidualWidthX1 = resDir.make<TH1F>("h_residualWidthX1","residual width #Delta_{x};#sigma_{x}  [cm];#Delta_{x}",vBinX.size()-1,&(vBinX[0]));
    (*iSec).second.CorrectionX1    = resDir.make<TH1F>("h_correctionX1","correction to APE_{x};#sigma_{x}  [cm];#DeltaAPE_{x}",vBinX.size()-1,&(vBinX[0]));
    (*iSec).second.FitMeanX2       = resDir.make<TH1F>("h_fitMeanX2","fitted residual mean #mu_{x};#sigma_{x}  [cm];#mu_{x}",vBinX.size()-1,&(vBinX[0]));
    (*iSec).second.ResidualWidthX2 = resDir.make<TH1F>("h_residualWidthX2","residual width #Delta_{x};#sigma_{x}  [cm];#Delta_{x}",vBinX.size()-1,&(vBinX[0]));
    (*iSec).second.CorrectionX2    = resDir.make<TH1F>("h_correctionX2","correciton to APE_{x};#sigma_{x}  [cm];#DeltaAPE_{x}",vBinX.size()-1,&(vBinX[0]));
  }
}





// -----------------------------------------------------------------------------------------------------------

void
ApeEstimator::bookTrackHists(){
  
  bool zoomHists(parameterSet_.getParameter<bool>("zoomHists"));
  
  int trackSizeBins = zoomHists ? 21 : 201;
  double trackSizeMax = trackSizeBins -1;
  
  double chi2Max = zoomHists ? 200. : 2000.;
  double norChi2Max = zoomHists ? 40. : 1000.;
  double d0max = zoomHists ? 0.2 : 40.;  // cosmics: 100.|100.
  double dzmax = zoomHists ? 10. : 100.;  // cosmics: 200.|600.
  double pMax = zoomHists ? 100. : 2000.;
  
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
  tkDetector_.Eta          = trkDir.make<TH1F>("h_eta","pseudorapidity #eta;#eta;# tracks",100,-5,5);
  tkDetector_.Theta        = trkDir.make<TH1F>("h_theta","polar angle #theta;#theta  [ ^{o}];# tracks",100,-10,190);
  tkDetector_.Phi          = trkDir.make<TH1F>("h_phi","azimuth angle #phi;#phi  [ ^{o}];# tracks",190,-190,190);
  tkDetector_.D0Beamspot   = trkDir.make<TH1F>("h_d0Beamspot","Closest approach d_{0} wrt. beamspot;d_{0, BS}  [cm];# tracks",200,-d0max, d0max);
  tkDetector_.Dz           = trkDir.make<TH1F>("h_dz","Closest approach d_{z};d_{z}  [cm];# tracks",200,-dzmax, dzmax);
  tkDetector_.Pt	   = trkDir.make<TH1F>("h_pt","transverse momentum p_{t};p_{t}  [GeV];# tracks",100,0,pMax);
  tkDetector_.P	           = trkDir.make<TH1F>("h_p","momentum magnitude |p|;|p|  [GeV];# tracks",100,0,pMax);
  tkDetector_.MeanAngle    = trkDir.make<TH1F>("h_meanAngle","mean angle on module <#phi_{module}>;<#phi_{module}>  [ ^{o}];# tracks",100,-5,95);
  tkDetector_.HitsGood     = trkDir.make<TH1F>("h_hitsGood","# hits  [good];# hits  [good];# tracks",51,-1,50);
  
  tkDetector_.MeanAngleVsHits     = trkDir.make<TH2F>("h2_meanAngleVsHits","<#phi_{module}> vs. # hits;# hits;<#phi_{module}>  [ ^{o}]",51,-1,50,50,-5,95);
  tkDetector_.HitsGoodVsHitsValid = trkDir.make<TH2F>("h2_hitsGoodVsHitsValid","# hits  [good] vs. # hits  [valid];# hits  [valid];# hits  [good]",51,-1,50,51,-1,50);
  
  tkDetector_.PMeanAngleVsHits     = trkDir.make<TProfile>("p_meanAngleVsHits","<#phi_{module}> vs. # hits;# hits;<#phi_{module}>  [ ^{o}]",51,-1,50);
  tkDetector_.PHitsGoodVsHitsValid = trkDir.make<TProfile>("p_hitsGoodVsHitsValid","# hits  [good] vs. # hits  [valid];# hits  [valid];# hits  [good]",51,-1,50);
}



// -----------------------------------------------------------------------------------------------------------


TrackStruct::TrackParameterStruct
ApeEstimator::fillTrackVariables(const reco::Track& track, const Trajectory& traj, const reco::BeamSpot& beamSpot){
  
  const math::XYZPoint beamPoint(beamSpot.x0(),beamSpot.y0(), beamSpot.z0());
  //double d0BeamspotSigma = sqrt( Track->d0Error() * Track->d0Error() + 0.5* beamSpot.BeamWidthX()*beamSpot.BeamWidthX() + 0.5* beamSpot.BeamWidthY()*beamSpot.BeamWidthY() );
  
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
  trkParams.d0           = track.d0();
  trkParams.dz           = track.dz();
  trkParams.d0Beamspot   = -1.*track.dxy(beamPoint);
  trkParams.dzBeamspot   = track.dz(beamPoint);
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
  
  if(parameterSet_.getParameter<bool>("applyTrackCuts")){
    trackCut_ = false;
    if(trkParams.hitsValid<12 || trkParams.hits2D<2 || //trkParams.hitsInvalid>2 ||
       trkParams.pt<10. || trkParams.p<20. || trkParams.p>250. || 
       std::fabs(trkParams.d0Beamspot)>0.1 || std::fabs(trkParams.dz)>10.)trackCut_ = true;
    //if(trkParams.hitsValid<12 || trkParams.hits2D<2 || trkParams.pt<2. || trkParams.p<4. || std::fabs(trkParams.d0)>1. || std::fabs(trkParams.dz)>15.)trackCut_ = true;
    //if(trkParams.hitsValid<10 || trkParams.hits2D<2 || trkParams.pt<1. || std::fabs(trkParams.d0)>1. || std::fabs(trkParams.dz)>15.)trackCut_ = true;
    //if(trkParams.hitsValid<8 || trkParams.pt<1. || trkParams.p<4.)trackCut_ = true;
    //if(trkParams.hitsValid<10 || trkParams.hits2D<2 || trkParams.pt<4. || trkParams.p<1. || trkParams.p>500. || trkParams.norChi2>100. || trkParams.phi>0.)trackCut_ = true;
    //if(trkParams.hitsValid<12 || trkParams.hits2D<2 || trkParams.pt<4. || trkParams.p<10. || trkParams.p>500. || trkParams.norChi2>10. || trkParams.phi>0.)trackCut_ = true;
    //if(trkParams.hitsValid<12 || trkParams.hits2D<2 || trkParams.pt<4. || trkParams.p<10. || trkParams.p>500. || trkParams.phi>0.)trackCut_ = true;
    //if(trkParams.hitsValid<12 || trkParams.hits2D<2 || trkParams.p<20. || trkParams.p>500. || trkParams.norChi2>10. || trkParams.phi>0. || trkParams.meanPhiSensToNorm>0.9599)trackCut_ = true;  //55degree
    //if(trkParams.hitsValid<12 || trkParams.hits2D<2 || trkParams.p<4. || trkParams.p>500. || trkParams.norChi2>10. || trkParams.phi>0. || trkParams.meanPhiSensToNorm>0.9599
    //                          || trkParams.pt<4.)trackCut_ = true;  //55degree
    //if(trkParams.hitsValid<15 || trkParams.hits2D<2 || trkParams.p<20. || trkParams.p>500. || trkParams.norChi2>10. || trkParams.phi>0. || trkParams.meanPhiSensToNorm>0.9599
    //                          || trkParams.pt<10.)trackCut_ = true;  //55degree
  }
  else{
    trackCut_ = false;
    // repeat intrinsic ALCARECO hit cuts after track refitting ?
    //if(trkParams.hitsValid<7 || trkParams.hits2D<2)trackCut_ = true;
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
  
  float norResX2(norResXprime*norResXprime);
  hitParams.probX   = TMath::Prob(norResX2,1);
  
  
  
  // Cluster parameters
  
  if(mTkTreeVar_[rawId].subdetId==PixelSubdetector::PixelBarrel || mTkTreeVar_[rawId].subdetId==PixelSubdetector::PixelEndcap){
    //const SiPixelRecHit& pixelHit = dynamic_cast<const SiPixelRecHit&>(recHit);
    //const SiPixelCluster& pixelCluster = *pixelHit.cluster();
  }
  else if(mTkTreeVar_[rawId].subdetId==StripSubdetector::TIB || mTkTreeVar_[rawId].subdetId==StripSubdetector::TOB ||
          mTkTreeVar_[rawId].subdetId==StripSubdetector::TID || mTkTreeVar_[rawId].subdetId==StripSubdetector::TEC){
    if(!(dynamic_cast<const SiStripRecHit2D*>(&recHit) || dynamic_cast<const SiStripRecHit1D*>(&recHit))){
      edm::LogError("FillHitVariables")<<"RecHit in Strip is 'Matched' or 'Projected', but here all should be monohits per module";
      hitParams.hitState = TrackStruct::invalid; return hitParams;
    }
    const SiStripCluster* clusterPtr(0);
    if(mTkTreeVar_[rawId].subdetId==StripSubdetector::TIB || mTkTreeVar_[rawId].subdetId==StripSubdetector::TOB){
      if(dynamic_cast<const SiStripRecHit1D*>(&recHit)){
        const SiStripRecHit1D& stripHit = dynamic_cast<const SiStripRecHit1D&>(recHit);
	clusterPtr = &(*stripHit.cluster());
      }
      else if(dynamic_cast<const SiStripRecHit2D*>(&recHit)){
        edm::LogWarning("FillHitVariables")<<"Data has TIB/TOB hits as SiStripRecHit2D and not 1D. Probably data is processed with CMSSW<34X. Nevertheless everything should work fine";
	const SiStripRecHit2D& stripHit = dynamic_cast<const SiStripRecHit2D&>(recHit);
	clusterPtr = &(*stripHit.cluster());
      }
    }
    else if(mTkTreeVar_[rawId].subdetId==StripSubdetector::TID || mTkTreeVar_[rawId].subdetId==StripSubdetector::TEC){
       const SiStripRecHit2D& stripHit = dynamic_cast<const SiStripRecHit2D&>(recHit);
       clusterPtr = &(*stripHit.cluster());
    }
    if(!clusterPtr){
      edm::LogError("FillHitVariables")<<"Pointer to cluster not valid!!! This should never happen...";
      hitParams.hitState = TrackStruct::invalid; return hitParams;
    }
    const SiStripCluster& stripCluster(*clusterPtr);
    const SiStripClusterInfo clusterInfo = SiStripClusterInfo(stripCluster, iSetup);
    
    hitParams.isModuleUsable   = clusterInfo.IsModuleUsable();
    hitParams.width            = clusterInfo.width();
    hitParams.maxStrip         = clusterInfo.maxStrip() +1;
    hitParams.maxStripInv      = mTkTreeVar_[rawId].nStrips - hitParams.maxStrip +1;
    hitParams.charge           = clusterInfo.charge();
    hitParams.maxCharge        = clusterInfo.maxCharge();
    hitParams.maxIndex         = clusterInfo.maxIndex();
    hitParams.chargeOnEdges    = static_cast<float>(clusterInfo.chargeLR().first + clusterInfo.chargeLR().second)/static_cast<float>(hitParams.charge);
    hitParams.chargeAsymmetry  = static_cast<float>(clusterInfo.chargeLR().first - clusterInfo.chargeLR().second)/static_cast<float>(hitParams.charge);
    hitParams.baryStrip        = clusterInfo.baryStrip() +1.;
    hitParams.sOverN           = clusterInfo.signalOverNoise();
    
    // Calculate projection length corrected by drift
    if(!hit.detUnit()){hitParams.hitState = TrackStruct::invalid; return hitParams;} // is it a single physical module?
    const GeomDetUnit& detUnit = *hit.detUnit();
    if(!dynamic_cast<const StripTopology*>(&detUnit.topology())){hitParams.hitState = TrackStruct::invalid; return hitParams;}
    
    
    edm::ESHandle<MagneticField> magFieldHandle;
    iSetup.get<IdealMagneticFieldRecord>().get(magFieldHandle);
    
    edm::ESHandle<SiStripLorentzAngle> lorentzAngleHandle;
    iSetup.get<SiStripLorentzAngleRcd>().get(lorentzAngleHandle);
    
    
    const StripGeomDetUnit * stripDet = (const StripGeomDetUnit*)(&detUnit);
    const MagneticField * magField(magFieldHandle.product());
    LocalVector bField = (stripDet->surface()).toLocal(magField->inTesla(stripDet->surface().position()));
    const SiStripLorentzAngle * lorentzAngle(lorentzAngleHandle.product());
    float tanLorentzAnglePerTesla = lorentzAngle->getLorentzAngle(stripDet->geographicalId().rawId());
    float dirX = -tanLorentzAnglePerTesla * bField.y();
    float dirY = tanLorentzAnglePerTesla * bField.x();
    float dirZ = 1.; // E field always in z direction
    LocalVector driftDirection(dirX,dirY,dirZ);
    
    
    const Bounds& bounds = stripDet->specificSurface().bounds();
    float maxLength = std::sqrt(std::pow(bounds.length(),2)+std::pow(bounds.width(),2));
    float thickness = bounds.thickness();
    LocalVector drift = driftDirection * thickness;
    
    
    
    const StripTopology& topol = dynamic_cast<const StripTopology&>(detUnit.topology());
    LocalVector momentumDir(tsos.localDirection());
    LocalPoint momentumPos(tsos.localPosition());
    LocalVector scaledMomentumDir(momentumDir);
    if(momentumDir.z() > 0.)scaledMomentumDir *= std::fabs(thickness/momentumDir.z());
    else if(momentumDir.z() < 0.)scaledMomentumDir *= -std::fabs(thickness/momentumDir.z());
    else scaledMomentumDir *= maxLength/momentumDir.mag();
    
    float projEdge1 = topol.measurementPosition(momentumPos - 0.5*scaledMomentumDir).x();
    //std::cout<<"Edge 1: "<<projEdge1<<"\n";
    if(projEdge1 < 0.)projEdge1 = 0.;
    else if(projEdge1 > mTkTreeVar_[rawId].nStrips)projEdge1 = mTkTreeVar_[rawId].nStrips;
    float projEdge2 = topol.measurementPosition(momentumPos + 0.5*scaledMomentumDir).x();
    //std::cout<<"Edge 2: "<<projEdge2<<"\n";
    if(projEdge2 < 0.)projEdge1 = 0.;
    else if(projEdge2 > mTkTreeVar_[rawId].nStrips)projEdge1 = mTkTreeVar_[rawId].nStrips;
    
    
    float coveredStrips = std::fabs(projEdge2 - projEdge1);
    //std::cout<<"Covered strips: "<<coveredStrips<<"\nWidth: "<<hitParams.width<<"\n";
    
    hitParams.projWidth = coveredStrips;
    
    
    
    
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
  this->setHitSelectionMap("widthProj");
  this->setHitSelectionMap("widthDiff");
  this->setHitSelectionMap("charge");
  this->setHitSelectionMapUInt("edgeStrips");
  this->setHitSelectionMap("maxCharge");
  this->setHitSelectionMapUInt("maxIndex");
  this->setHitSelectionMap("chargeOnEdges");
  this->setHitSelectionMap("chargeAsymmetry");
  this->setHitSelectionMap("sOverN");
  
  this->setHitSelectionMap("resX");
  this->setHitSelectionMap("norResX");
  this->setHitSelectionMap("probX");
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
  edm::ParameterSet parSet(parameterSet_.getParameter<edm::ParameterSet>("HitSelector"));
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
  edm::ParameterSet parSet(parameterSet_.getParameter<edm::ParameterSet>("HitSelector"));
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
    
    if     ((*iMap).first == "widthProj")       variable = hitParams.projWidth;
    else if((*iMap).first == "widthDiff")       variable = hitParams.projWidth-static_cast<float>(hitParams.width);
    else if((*iMap).first == "charge")          variable = hitParams.charge;
    else if((*iMap).first == "maxCharge")       variable = hitParams.maxCharge;
    else if((*iMap).first == "chargeOnEdges")   variable = hitParams.chargeOnEdges;
    else if((*iMap).first == "chargeAsymmetry") variable = hitParams.chargeAsymmetry;
    else if((*iMap).first == "sOverN")          variable = hitParams.sOverN;
    
    else if((*iMap).first == "resX")            variable = hitParams.resX;
    else if((*iMap).first == "norResX")         variable = hitParams.norResX;
    else if((*iMap).first == "probX")           variable = hitParams.probX;
    else if((*iMap).first == "errXHit")         variable = hitParams.errXHit;
    else if((*iMap).first == "errXTrk")         variable = hitParams.errXTrk;
    else if((*iMap).first == "errX")            variable = hitParams.errX;
    else if((*iMap).first == "errX2")           variable = hitParams.errX2;
    else if((*iMap).first == "phiSens")         variable = hitParams.phiSens;
    else if((*iMap).first == "phiSensX")        variable = hitParams.phiSensX;
    else if((*iMap).first == "phiSensY")        variable = hitParams.phiSensY;
    
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
ApeEstimator::fillHistsForAnalyzerMode(const TrackStruct& trackStruct){
  
  unsigned int goodHitsPerTrack(trackStruct.vHitParams.size());
  tkDetector_.HitsGood->Fill(goodHitsPerTrack);
  tkDetector_.HitsGoodVsHitsValid->Fill(trackStruct.trkParams.hitsValid,goodHitsPerTrack);
  tkDetector_.PHitsGoodVsHitsValid->Fill(trackStruct.trkParams.hitsValid,goodHitsPerTrack);
  
  if(parameterSet_.getParameter<bool>("applyTrackCuts")){
    // which tracks to take? need min. nr. of selected hits?
    if(goodHitsPerTrack < minGoodHitsPerTrack_)return;
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
  tkDetector_.D0Beamspot  ->Fill(trackStruct.trkParams.d0Beamspot);
  tkDetector_.Dz          ->Fill(trackStruct.trkParams.dz);
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
      
      
      // Cluster Parameters
      (*iSec).second.mCorrelationHists["Width"].fillCorrHists(*iHit,(*iHit).width);
      (*iSec).second.mCorrelationHists["Charge"].fillCorrHists(*iHit,(*iHit).charge);
      (*iSec).second.mCorrelationHists["MaxStrip"].fillCorrHists(*iHit,(*iHit).maxStrip);
      (*iSec).second.mCorrelationHists["MaxCharge"].fillCorrHists(*iHit,(*iHit).maxCharge);
      (*iSec).second.mCorrelationHists["MaxIndex"].fillCorrHists(*iHit,(*iHit).maxIndex);
      (*iSec).second.mCorrelationHists["ChargeOnEdges"].fillCorrHists(*iHit,(*iHit).chargeOnEdges);
      (*iSec).second.mCorrelationHists["ChargeAsymmetry"].fillCorrHists(*iHit,(*iHit).chargeAsymmetry);
      (*iSec).second.mCorrelationHists["BaryStrip"].fillCorrHists(*iHit,(*iHit).baryStrip);
      (*iSec).second.mCorrelationHists["SOverN"].fillCorrHists(*iHit,(*iHit).sOverN);
      (*iSec).second.mCorrelationHists["WidthProj"].fillCorrHists(*iHit,(*iHit).projWidth);
      (*iSec).second.mCorrelationHists["WidthDiff"].fillCorrHists(*iHit,(*iHit).projWidth-static_cast<float>((*iHit).width));
      
      (*iSec).second.WidthVsWidthProjected->Fill((*iHit).projWidth,(*iHit).width);
      (*iSec).second.PWidthVsWidthProjected->Fill((*iHit).projWidth,(*iHit).width);
      
      (*iSec).second.WidthDiffVsMaxStrip->Fill((*iHit).maxStrip,(*iHit).projWidth-static_cast<float>((*iHit).width));
      (*iSec).second.PWidthDiffVsMaxStrip->Fill((*iHit).maxStrip,(*iHit).projWidth-static_cast<float>((*iHit).width));
      
      (*iSec).second.WidthDiffVsSigmaXHit->Fill((*iHit).errXHit,(*iHit).projWidth-static_cast<float>((*iHit).width));
      (*iSec).second.PWidthDiffVsSigmaXHit->Fill((*iHit).errXHit,(*iHit).projWidth-static_cast<float>((*iHit).width));
      
      
      // Hit Parameters
      (*iSec).second.mCorrelationHists["SigmaXHit"].fillCorrHists(*iHit,(*iHit).errXHit);
      (*iSec).second.mCorrelationHists["SigmaXTrk"].fillCorrHists(*iHit,(*iHit).errXTrk);
      (*iSec).second.mCorrelationHists["SigmaX"].fillCorrHists(*iHit,(*iHit).errX);
      
      (*iSec).second.mCorrelationHists["PhiSens"].fillCorrHists(*iHit,(*iHit).phiSens*180./M_PI);
      (*iSec).second.mCorrelationHists["PhiSensX"].fillCorrHists(*iHit,(*iHit).phiSensX*180./M_PI);
      (*iSec).second.mCorrelationHists["PhiSensY"].fillCorrHists(*iHit,(*iHit).phiSensY*180./M_PI);
      
      (*iSec).second.XHit   ->Fill((*iHit).xHit);
      (*iSec).second.XTrk   ->Fill((*iHit).xTrk);
      (*iSec).second.SigmaX2->Fill((*iHit).errX2);
      
      (*iSec).second.ResX   ->Fill((*iHit).resX);
      (*iSec).second.NorResX->Fill((*iHit).norResX);
      
      (*iSec).second.ProbX->Fill((*iHit).probX);
      
      (*iSec).second.WidthVsPhiSensX->Fill((*iHit).phiSensX*180./M_PI,(*iHit).width);
      (*iSec).second.PWidthVsPhiSensX->Fill((*iHit).phiSensX*180./M_PI,(*iHit).width);
      
      
      // Track Parameters
      (*iSec).second.mCorrelationHists["HitsValid"].fillCorrHists(*iHit,trackStruct.trkParams.hitsValid);
      (*iSec).second.mCorrelationHists["HitsGood"].fillCorrHists(*iHit,goodHitsPerTrack);
      (*iSec).second.mCorrelationHists["HitsInvalid"].fillCorrHists(*iHit,trackStruct.trkParams.hitsInvalid);
      (*iSec).second.mCorrelationHists["LayersMissed"].fillCorrHists(*iHit,trackStruct.trkParams.layersMissed);
      (*iSec).second.mCorrelationHists["NorChi2"].fillCorrHists(*iHit,trackStruct.trkParams.norChi2);
      (*iSec).second.mCorrelationHists["Theta"].fillCorrHists(*iHit,trackStruct.trkParams.theta*180./M_PI);
      (*iSec).second.mCorrelationHists["Phi"].fillCorrHists(*iHit,trackStruct.trkParams.phi*180./M_PI);
      (*iSec).second.mCorrelationHists["D0Beamspot"].fillCorrHists(*iHit,trackStruct.trkParams.d0Beamspot);
      (*iSec).second.mCorrelationHists["Dz"].fillCorrHists(*iHit,trackStruct.trkParams.dz);
      (*iSec).second.mCorrelationHists["Pt"].fillCorrHists(*iHit,trackStruct.trkParams.pt);
      (*iSec).second.mCorrelationHists["P"].fillCorrHists(*iHit,trackStruct.trkParams.p);
      (*iSec).second.mCorrelationHists["InvP"].fillCorrHists(*iHit,1./trackStruct.trkParams.p);
      (*iSec).second.mCorrelationHists["MeanAngle"].fillCorrHists(*iHit,trackStruct.trkParams.meanPhiSensToNorm*180./M_PI);
      
      //(*iSec).second.mCorrelationHists[""].fillCorrHists(*iHit,(*iHit).);
      
      
      
      // Special Histograms
      for(std::map<std::string,std::vector<TH1*> >::iterator iMap = (*iSec).second.mSigmaX.begin(); iMap != (*iSec).second.mSigmaX.end(); ++iMap){
        for(std::vector<TH1*>::iterator iHist = (*iMap).second.begin(); iHist != (*iMap).second.end(); ++iHist){
	  if     ((*iMap).first=="sigmaXHit")(*iHist)->Fill((*iHit).errXHit);
	  else if((*iMap).first=="sigmaXTrk")(*iHist)->Fill((*iHit).errXTrk);
	  else if((*iMap).first=="sigmaX")   (*iHist)->Fill((*iHit).errX);
	}
      }
      
    }
  }
}



void
ApeEstimator::fillHistsForApeCalculation(const TrackStruct& trackStruct){
  
  unsigned int goodHitsPerTrack(trackStruct.vHitParams.size());
  
  if(parameterSet_.getParameter<bool>("applyTrackCuts")){
    // which tracks to take? need min. nr. of selected hits?
    if(goodHitsPerTrack < minGoodHitsPerTrack_)return;
  }
  
  
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
      
      
      
      
      
      
      if(!calculateApe_)continue;
      
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
       edm::LogInfo("CalculateAPE")<<"First APE iteration, create iteration file with TTree";
     }
     else{
       iterationTree = new TTree("iterTree","Tree for baseline values of normalized residual width");
       edm::LogInfo("CalculateAPE")<<"Set baseline, create baseline file with TTree";
     }
   }
   else{
     const unsigned int iteration(iterationTree->GetEntries());
     edm::LogWarning("CalculateAPE")<<"NOT the first APE iteration but the "<<iteration+1<<" one, is this wanted or forgot to delete old iteration file with TTree?";
   }
   
   double a_apeSector[16589];
   double a_baselineSector[16589];
   for(size_t i_sector = 1; i_sector <= mTkSector_.size(); ++i_sector){
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
   const double correctionScaling(parameterSet_.getParameter<double>("correctionScaling"));
   const double sigmaFactorFit(parameterSet_.getParameter<double>("sigmaFactorFit"));
   for(std::map<unsigned int,TrackerSectorStruct>::iterator iSec = mTkSector_.begin(); iSec != mTkSector_.end(); ++iSec){
     
     std::vector<std::pair<double,double> > vEntriesAndCorrectionX2PerBin;
     
     // Loop over residual error bins to calculate APE for every bin
     for(std::map<unsigned int, std::map<std::string,TH1*> >::const_iterator iErrBins = (*iSec).second.mBinnedHists.begin();
         iErrBins != (*iSec).second.mBinnedHists.end(); ++iErrBins){
       std::map<std::string,TH1*> mHists = (*iErrBins).second;
       
       double entries = mHists["sigmaX"]->GetEntries();
       double meanSigmaX = mHists["sigmaX"]->GetMean();
       
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
       
       double baselineWidthX2(a_baselineSector[(*iSec).first]*a_baselineSector[(*iSec).first]);
       double correctionX2_1(-0.0010), correctionX2_2(-0.0010);
       correctionX2_1 = meanSigmaX*meanSigmaX*(residualWidth_1*residualWidth_1 -baselineWidthX2);
       correctionX2_2 = meanSigmaX*meanSigmaX*(residualWidth_2*residualWidth_2 -baselineWidthX2);
       
       
       double correctionX_1 = correctionX2_1>=0. ? std::sqrt(correctionX2_1) : -std::sqrt(-correctionX2_1);
       double correctionX_2 = correctionX2_2>=0. ? std::sqrt(correctionX2_2) : -std::sqrt(-correctionX2_2);
       if(isnan(correctionX_1))correctionX_1 = -0.0010;
       if(isnan(correctionX_2))correctionX_2 = -0.0010;
       
       if(entries<1000.){mean     = 0.; rms  = -0.0010;
                         fitMean_1 = 0.; correctionX_1 = residualWidth_1 = -0.0010;
			 fitMean_2 = 0.; correctionX_2 = residualWidth_2 = -0.0010;}
       
       (*iSec).second.Entries       ->SetBinContent((*iErrBins).first,integral);
       (*iSec).second.MeanX         ->SetBinContent((*iErrBins).first,mean);
       (*iSec).second.RmsX          ->SetBinContent((*iErrBins).first,rms);
       
       //std::cout<<"\n\nSector, Bin "<<(*iSec).first<<"\t"<<(*iErrBins).first;
       //std::cout<<"\nEntries, MeanError, ResWidth, APE \t"<<entries<<"\t"<<meanSigmaX<<"\t"<<residualWidth<<"\t"<<ape<<"\n";
       (*iSec).second.FitMeanX1      ->SetBinContent((*iErrBins).first,fitMean_1);
       (*iSec).second.ResidualWidthX1->SetBinContent((*iErrBins).first,residualWidth_1);
       (*iSec).second.CorrectionX1   ->SetBinContent((*iErrBins).first,correctionX_1);
       
       (*iSec).second.FitMeanX2      ->SetBinContent((*iErrBins).first,fitMean_2);
       (*iSec).second.ResidualWidthX2->SetBinContent((*iErrBins).first,residualWidth_2);
       (*iSec).second.CorrectionX2   ->SetBinContent((*iErrBins).first,correctionX_2);
       
       
       // Use result for bin only when entries>1000
       if(entries<1000.)continue;
       // Fill correction^2 for APE calculation, BUT fill residual width for setBaseline mode
       std::pair<double,double> entriesAndCorrectionX2PerBin(entries, setBaseline ? residualWidth_2 : correctionX2_2);
       vEntriesAndCorrectionX2PerBin.push_back(entriesAndCorrectionX2PerBin);
     }
     
     
     // Calculate squared correction for sector (or baselineWidth in setBaseline mode)
     if(vEntriesAndCorrectionX2PerBin.size() == 0){
       edm::LogError("CalculateAPE")<<"NO error interval of sector "<<(*iSec).first<<" has a valid APE calculated,\n...so cannot set APE";
       continue;
     }
     
/*     
     // Question: how to calculate APE from different bins, mean value from all, weighted by entries ???
     double correctionX2(999.);
     unsigned int regardedInterval(1);
     std::vector<std::pair<double,double> >::const_iterator iApeBins;
     for(iApeBins = vEntriesAndCorrectionX2PerBin.begin(); iApeBins != vEntriesAndCorrectionX2PerBin.end(); ++iApeBins){
       if(regardedInterval==1)correctionX2 = (*iApeBins).second;
       else correctionX2 += (*iApeBins).second;
       ++regardedInterval;
     }
     correctionX2 = correctionX2/static_cast<double>(regardedInterval-1);
*/     
     
     
     // Try to calculate mean weighted by entries per bin
     double correctionX2(999.);
     double entriesSum(0.);
     unsigned int regardedInterval(1);
     std::vector<std::pair<double,double> >::const_iterator iApeBins;
     for(iApeBins = vEntriesAndCorrectionX2PerBin.begin(); iApeBins != vEntriesAndCorrectionX2PerBin.end(); ++iApeBins){
       if(regardedInterval==1)correctionX2 = (*iApeBins).second * (*iApeBins).first;
       else correctionX2 += (*iApeBins).second * (*iApeBins).first;
       ++regardedInterval;
       entriesSum += (*iApeBins).first;
     }
     correctionX2 = correctionX2/entriesSum;
     
     
     
     if(!setBaseline){
       // scale APE Correction with value given in cfg
       correctionX2 = correctionX2*correctionScaling*correctionScaling;
     
       // Calculate updated squared APE of current iteration
       double apeX2(999.);
       // old APE value from last iteration
       if(firstIter)apeX2 = 0.;
       else apeX2 = a_apeSector[(*iSec).first];
       // new APE value
       if(apeX2 + correctionX2 < 0.) correctionX2 = -apeX2;
       apeX2 = apeX2 + correctionX2;
       if(apeX2<0.)edm::LogError("CalculateAPE")<<"\n\n\tBad APE, but why???\n\n\n";
       a_apeSector[(*iSec).first] = apeX2;
       
       
       // Set the calculated APE spherical for all modules of the sector
       const double apeX(std::sqrt(apeX2));
       std::vector<unsigned int>::const_iterator iRawId;
       for(iRawId = (*iSec).second.vRawId.begin(); iRawId != (*iSec).second.vRawId.end(); ++iRawId){
         apeOutputFile<<*iRawId<<" "<<std::fixed<<std::setprecision(5)<<apeX<<" "<<apeX<<" "<<apeX<<"\n";
       }
     }
     // In setBaseline mode, just fill estimated mean value of residual width
     else{
       a_apeSector[(*iSec).first] = correctionX2;
     }
     
   }
   if(!setBaseline)apeOutputFile.close();
   
   iterationTree->Fill();
   iterationTree->Write("iterTree", TObject::kOverwrite);  // TObject::kOverwrite needed to not produce another iterTree;2
   iterationFile->Close();
   
   if(baselineFile)baselineFile->Close();
}




// -----------------------------------------------------------------------------------------------------------


bool
ApeEstimator::isHit2D(const TrackingRecHit &hit) const
{
  // we count SiStrip stereo modules as 2D if selected via countStereoHitAs2D_
  // (since they provide theta information)
  // --- NO, here it is always set to true ---
  if (!hit.isValid() ||
      (hit.dimension() < 2 && !dynamic_cast<const SiStripRecHit1D*>(&hit))){
    return false; // real RecHit1D - but SiStripRecHit1D depends on countStereoHitAs2D_
  } else {
    const DetId detId(hit.geographicalId());
    if (detId.det() == DetId::Tracker) {
      if (detId.subdetId() == PixelSubdetector::PixelBarrel || detId.subdetId() == PixelSubdetector::PixelEndcap) {
        return true; // pixel is always 2D
      } else { // should be SiStrip now
	const SiStripDetId stripId(detId);
	if (stripId.stereo()) return true; // stereo modules
        else if (dynamic_cast<const SiStripRecHit1D*>(&hit)
		 || dynamic_cast<const SiStripRecHit2D*>(&hit)) return false; // rphi modules hit
	//the following two are not used any more since ages... 
        else if (dynamic_cast<const SiStripMatchedRecHit2D*>(&hit)) return true; // matched is 2D
        else if (dynamic_cast<const ProjectedSiStripRecHit2D*>(&hit)) {
	  const ProjectedSiStripRecHit2D* pH = static_cast<const ProjectedSiStripRecHit2D*>(&hit);
	  return (this->isHit2D(pH->originalHit())); // depends on original...
	} else {
          edm::LogError("UnkownType") << "@SUB=AlignmentTrackSelector::isHit2D"
                                      << "Tracker hit not in pixel, neither SiStripRecHit[12]D nor "
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
   
   reco::BeamSpot beamSpot;
   edm::Handle<reco::BeamSpot> beamSpotHandle;
   iEvent.getByLabel("offlineBeamSpot", beamSpotHandle);
   
   if (beamSpotHandle.isValid()){
     beamSpot = *beamSpotHandle;
   }
   else
   {
     edm::LogError("ApeEstimator")<<"No beam spot available from EventSetup"
                                  <<"\n...skip event";
     return;
   }
   
   
   //edm::Handle<reco::TrackCollection> tracks;
   edm::InputTag tjTag = parameterSet_.getParameter<edm::InputTag>("tjTkAssociationMapTag");
   edm::Handle<TrajTrackAssociationCollection> m_TrajTracksMap;
   iEvent.getByLabel(tjTag, m_TrajTracksMap);
   
   if(analyzerMode_)tkDetector_.TrkSize->Fill(m_TrajTracksMap->size());
   
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
     trackStruct.trkParams = this->fillTrackVariables(*track, *traj, beamSpot);
     
     if(trackCut_)continue;
     
     const std::vector<TrajectoryMeasurement> meass = (*traj).measurements();
     
     //Loop over Hits
     for(std::vector<TrajectoryMeasurement>::const_iterator iMeass = meass.begin(); iMeass != meass.end(); ++iMeass){
       TrackStruct::HitParameterStruct hitParams = this->fillHitVariables(*iMeass, iSetup);
       if(this->hitSelected(hitParams))trackStruct.vHitParams.push_back(hitParams);
     }
     
     if(analyzerMode_)this->fillHistsForAnalyzerMode(trackStruct);
     if(calculateApe_)this->fillHistsForApeCalculation(trackStruct);
   }
}


// ------------ method called once each job just before starting event loop  ------------
void 
ApeEstimator::beginJob(){
   
   this->hitSelection();
   
   this->sectorBuilder();
   
   this->residualErrorBinning();
   
   if(analyzerMode_)this->bookSectorHistsForAnalyzerMode();
   
   if(calculateApe_)this->bookSectorHistsForApeCalculation();
   
   if(analyzerMode_)this->bookTrackHists();
   
   
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ApeEstimator::endJob() {
   
   if(calculateApe_)this->calculateAPE();
   
   edm::LogInfo("HitSelector")<<"\nThere are "<<counter1<< " negative Errors calculated\n";
}

//define this as a plug-in
DEFINE_FWK_MODULE(ApeEstimator);
