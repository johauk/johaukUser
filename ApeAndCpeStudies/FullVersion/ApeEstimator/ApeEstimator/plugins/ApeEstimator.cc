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
// $Id: ApeEstimator.cc,v 1.9 2011/06/15 17:15:21 hauk Exp $
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
#include "DataFormats/TrackReco/interface/HitPattern.h"
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
#include "Geometry/CommonDetUnit/interface/GeomDetType.h"
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
      typedef std::pair<float,float> XAndY;
      typedef std::pair<XAndY,XAndY> PositionAndError2;
      
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
      PositionAndError2 positionAndError2(const LocalPoint&, const LocalError&, const uint32_t&)const;
      
      void hitSelection();
      void setHitSelectionMap(const std::string&);
      void setHitSelectionMapUInt(const std::string&);
      bool hitSelected(const TrackStruct::HitParameterStruct&)const;
      
      void fillHistsForAnalyzerMode(const TrackStruct&);
      void fillHistsForApeCalculation(const TrackStruct&);
      
      void calculateAPE();
      
      // ----------member data ---------------------------
      const edm::ParameterSet parameterSet_;
      std::map<unsigned int, TrackerSectorStruct> m_tkSector_;
      TrackerDetectorStruct tkDetector_;
      
      std::map<unsigned int, std::pair<double,double> > m_resErrBins_;
      
      std::map<unsigned int, ReducedTrackerTreeVariables> m_tkTreeVar_;
      
      std::map<std::string,std::vector<double> > m_hitSelection_;
      std::map<std::string,std::vector<unsigned int> > m_hitSelectionUInt_;
      
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
  std::vector<edm::ParameterSet> v_sectorDef(parameterSet_.getParameter<std::vector<edm::ParameterSet> >("Sectors"));
  edm::LogInfo("SectorBuilder")<<"There are "<<v_sectorDef.size()<<" Sectors definded";
  std::vector<edm::ParameterSet>::const_iterator i_parSet;
  for(i_parSet = v_sectorDef.begin(); i_parSet != v_sectorDef.end();++i_parSet, ++sectorCounter){
    const edm::ParameterSet& parSet = *i_parSet;
    std::vector<unsigned int> v_rawId(parSet.getParameter<std::vector<unsigned int> >("rawId")),
                              v_subdetId(parSet.getParameter<std::vector<unsigned int> >("subdetId")),
			      v_layer(parSet.getParameter<std::vector<unsigned int> >("layer")),
			      v_side(parSet.getParameter<std::vector<unsigned int> >("side")),
			      v_half(parSet.getParameter<std::vector<unsigned int> >("half")),
			      v_rod(parSet.getParameter<std::vector<unsigned int> >("rod")),
			      v_ring(parSet.getParameter<std::vector<unsigned int> >("ring")),
			      v_petal(parSet.getParameter<std::vector<unsigned int> >("petal")),
                              v_blade(parSet.getParameter<std::vector<unsigned int> >("blade")),
			      v_panel(parSet.getParameter<std::vector<unsigned int> >("panel")),
			      v_outerInner(parSet.getParameter<std::vector<unsigned int> >("outerInner")),
			      v_module(parSet.getParameter<std::vector<unsigned int> >("module")),
			      v_rodAl(parSet.getParameter<std::vector<unsigned int> >("rodAl")),
			      v_bladeAl(parSet.getParameter<std::vector<unsigned int> >("bladeAl")),
			      v_nStrips(parSet.getParameter<std::vector<unsigned int> >("nStrips")),
			      v_isDoubleSide(parSet.getParameter<std::vector<unsigned int> >("isDoubleSide")),
			      v_isRPhi(parSet.getParameter<std::vector<unsigned int> >("isRPhi"));
    std::vector<int> v_uDirection(parSet.getParameter<std::vector<int> >("uDirection")),
                     v_vDirection(parSet.getParameter<std::vector<int> >("vDirection")),
		     v_wDirection(parSet.getParameter<std::vector<int> >("wDirection"));
    std::vector<double> v_posR(parSet.getParameter<std::vector<double> >("posR")),
                        v_posPhi(parSet.getParameter<std::vector<double> >("posPhi")),
			v_posEta(parSet.getParameter<std::vector<double> >("posEta")),
			v_posX(parSet.getParameter<std::vector<double> >("posX")),
			v_posY(parSet.getParameter<std::vector<double> >("posY")),
			v_posZ(parSet.getParameter<std::vector<double> >("posZ"));
    
    if(!this->checkIntervalsForSectors(sectorCounter,v_posR) || !this->checkIntervalsForSectors(sectorCounter,v_posPhi) ||
       !this->checkIntervalsForSectors(sectorCounter,v_posEta) || !this->checkIntervalsForSectors(sectorCounter,v_posX) ||
       !this->checkIntervalsForSectors(sectorCounter,v_posY)   || !this->checkIntervalsForSectors(sectorCounter,v_posZ))continue;
    
    
    TrackerSectorStruct tkSector;
    ReducedTrackerTreeVariables tkTreeVar;
    
    //Loop over all Modules
    for(Int_t module = 0; module < nModules; ++module){
      tkTree->GetEntry(module);
      
      if(sectorCounter==1){
        tkTreeVar.subdetId = subdetId;
        tkTreeVar.nStrips = nStrips;
	tkTreeVar.uDirection = uDirection;
        tkTreeVar.vDirection = vDirection;
        tkTreeVar.wDirection = wDirection;
	m_tkTreeVar_[rawId] = tkTreeVar;
      }
      
      if(!this->checkModuleIds(rawId,v_rawId))continue;
      if(!this->checkModuleIds(subdetId,v_subdetId))continue;
      if(!this->checkModuleIds(layer,v_layer))continue;
      if(!this->checkModuleIds(side,v_side))continue;
      if(!this->checkModuleIds(half,v_half))continue;
      if(!this->checkModuleIds(rod,v_rod))continue;
      if(!this->checkModuleIds(ring,v_ring))continue;
      if(!this->checkModuleIds(petal,v_petal))continue;
      if(!this->checkModuleIds(blade,v_blade))continue;
      if(!this->checkModuleIds(panel,v_panel))continue;
      if(!this->checkModuleIds(outerInner,v_outerInner))continue;
      if(!this->checkModuleIds(module,v_module))continue;
      if(!this->checkModuleIds(rodAl,v_rodAl))continue;
      if(!this->checkModuleIds(bladeAl,v_bladeAl))continue;
      if(!this->checkModuleIds(nStrips,v_nStrips))continue;
      if(!this->checkModuleBools(isDoubleSide,v_isDoubleSide))continue;
      if(!this->checkModuleBools(isRPhi,v_isRPhi))continue;
      if(!this->checkModuleDirections(uDirection,v_uDirection))continue;
      if(!this->checkModuleDirections(vDirection,v_vDirection))continue;
      if(!this->checkModuleDirections(wDirection,v_wDirection))continue;
      if(!this->checkModulePositions(posR,v_posR))continue;
      if(!this->checkModulePositions(posPhi,v_posPhi))continue;
      if(!this->checkModulePositions(posEta,v_posEta))continue;
      if(!this->checkModulePositions(posX,v_posX))continue;
      if(!this->checkModulePositions(posY,v_posY))continue;
      if(!this->checkModulePositions(posZ,v_posZ))continue;
      
      tkSector.v_rawId.push_back(rawId);
      bool moduleSelected(false);
      for(std::vector<unsigned int>::const_iterator i_rawId = allSectors.v_rawId.begin();
          i_rawId != allSectors.v_rawId.end(); ++i_rawId){
        if(rawId == *i_rawId)moduleSelected = true;
      }
      if(!moduleSelected)allSectors.v_rawId.push_back(rawId);
    }
    m_tkSector_[sectorCounter] = tkSector;
    edm::LogInfo("SectorBuilder")<<"There are "<<tkSector.v_rawId.size()<<" Modules in Sector "<<sectorCounter;
  }
  this->statistics(allSectors, nModules);
  return;
}



// -----------------------------------------------------------------------------------------------------------


bool
ApeEstimator::checkIntervalsForSectors(const unsigned int sectorCounter, const std::vector<double>& v_id)const{
  if(v_id.size()==0)return true;
  if(v_id.size()%2==1){
    edm::LogError("SectorBuilder")<<"Incorrect Sector Definition: Position Vectors need even number of arguments (Intervals)"
                                     <<"\n... sector selection is not applied, sector "<<sectorCounter<<" is not built";
    return false;
  }
  int entry(1); double intervalBegin(999.);
  for(std::vector<double>::const_iterator i_id = v_id.begin(); i_id != v_id.end(); ++i_id, ++entry){
    if(entry%2==1)intervalBegin = *i_id;
    if(entry%2==0 && intervalBegin>*i_id){
      edm::LogError("SectorBuilder")<<"Incorrect Sector Definition (Position Vector Intervals): \t"
                                    <<intervalBegin<<" is bigger than "<<*i_id<<" but is expected to be smaller"
                                    <<"\n... sector selection is not applied, sector "<<sectorCounter<<" is not built";
      return false;
    }
  }
  return true;
}

bool
ApeEstimator::checkModuleIds(const unsigned int id, const std::vector<unsigned int>& v_id)const{
  if(v_id.size()==0)return true;
  for(std::vector<unsigned int>::const_iterator i_id = v_id.begin(); i_id != v_id.end(); ++i_id){
    if(id==*i_id)return true;
  }
  return false;
}

bool
ApeEstimator::checkModuleBools(const bool id, const std::vector<unsigned int>& v_id)const{
  if(v_id.size()==0)return true;
  for(std::vector<unsigned int>::const_iterator i_id = v_id.begin(); i_id != v_id.end(); ++i_id){
    if(1==*i_id && id)return true;
    if(2==*i_id && !id)return true;
  }
  return false;
}

bool
ApeEstimator::checkModuleDirections(const int id, const std::vector<int>& v_id)const{
  if(v_id.size()==0)return true;
  for(std::vector<int>::const_iterator i_id = v_id.begin(); i_id != v_id.end(); ++i_id){
    if(id==*i_id)return true;
  }
  return false;
}

bool
ApeEstimator::checkModulePositions(const float id, const std::vector<double>& v_id)const{
  if(v_id.size()==0)return true;
  int entry(1); double intervalBegin(999.);
  for(std::vector<double>::const_iterator i_id = v_id.begin(); i_id != v_id.end(); ++i_id, ++entry){
    if(entry%2==1)intervalBegin = *i_id;
    if(entry%2==0 && id>=intervalBegin && id<*i_id)return true;
  }
  return false;
}

void
ApeEstimator::statistics(const TrackerSectorStruct& allSectors, const Int_t nModules)const{
  bool commonModules(false);
  for(std::map<unsigned int,TrackerSectorStruct>::const_iterator i_sector = m_tkSector_.begin(); i_sector != m_tkSector_.end(); ++i_sector){
    std::map<unsigned int,TrackerSectorStruct>::const_iterator i_sector2(i_sector);
    for(++i_sector2; i_sector2 != m_tkSector_.end(); ++i_sector2){
      unsigned int nCommonModules(0);
      for(std::vector<unsigned int>::const_iterator i_module = (*i_sector).second.v_rawId.begin(); i_module != (*i_sector).second.v_rawId.end(); ++i_module){
        for(std::vector<unsigned int>::const_iterator i_module2 = (*i_sector2).second.v_rawId.begin(); i_module2 != (*i_sector2).second.v_rawId.end(); ++i_module2){
          if(*i_module2 == *i_module)++nCommonModules;
        }
      }
      if(nCommonModules==0)
        ;//edm::LogInfo("SectorBuilder")<<"Sector "<<(*i_sector).first<<" and Sector "<<(*i_sector2).first<< " have ZERO Modules in common";
      else{
        edm::LogError("SectorBuilder")<<"Sector "<<(*i_sector).first<<" and Sector "<<(*i_sector2).first<< " have "<<nCommonModules<<" Modules in common";
        commonModules = true;
      }
    }
  }
  if(static_cast<int>(allSectors.v_rawId.size())==nModules)
    edm::LogInfo("SectorBuilder")<<"ALL Tracker Modules are contained in the Sectors";
  else
    edm::LogWarning("SectorBuilder")<<"There are "<<allSectors.v_rawId.size()<<" Modules in all Sectors"
                               <<" out of "<<nModules<<" Tracker Modules";
  if(!commonModules)
    edm::LogInfo("SectorBuilder")<<"There are ZERO modules associated to different sectors, no ambiguities exist";
  else
  edm::LogError("SectorBuilder")<<"There are modules associated to different sectors, APE value cannot be assigned reasonably";
}


// -----------------------------------------------------------------------------------------------------------


void
ApeEstimator::residualErrorBinning(){
   std::vector<double> v_residualErrorBinning(parameterSet_.getParameter<std::vector<double> >("residualErrorBinning"));
   if(v_residualErrorBinning.size()==1){
     edm::LogError("ResidualErrorBinning")<<"Incorrect selection of Residual Error Bins (used for APE calculation): \t"
                                          <<"Only one argument passed, so no interval is specified"
					  <<"\n... delete whole bin selection";    //m_resErrBins_ remains empty
     return;
   }
   double xMin(0.), xMax(0.);
   unsigned int binCounter(0);
   for(std::vector<double>::const_iterator i_binning = v_residualErrorBinning.begin(); i_binning != v_residualErrorBinning.end(); ++i_binning, ++binCounter){
     if(binCounter == 0){xMin = *i_binning;continue;}
     xMax = *i_binning;
     if(xMax<=xMin){
       edm::LogError("ResidualErrorBinning")<<"Incorrect selection of Residual Error Bins (used for APE calculation): \t"
                                            <<xMin<<" is bigger than "<<xMax<<" but is expected to be smaller"
					    <<"\n... delete whole bin selection";
       m_resErrBins_.clear();
       return;
     }
     m_resErrBins_[binCounter].first = xMin;
     m_resErrBins_[binCounter].second = xMax;
     xMin = xMax;
   }
   edm::LogInfo("ResidualErrorBinning")<<m_resErrBins_.size()<<" Intervals of residual errors used for separate APE calculation sucessfully set";
}



// -----------------------------------------------------------------------------------------------------------



void
ApeEstimator::bookSectorHistsForAnalyzerMode(){
  
  std::vector<unsigned int> v_errHists(parameterSet_.getParameter<std::vector<unsigned int> >("vErrHists"));
  for(std::vector<unsigned int>::iterator i_errHists = v_errHists.begin(); i_errHists != v_errHists.end(); ++i_errHists){
    for(std::vector<unsigned int>::iterator i_errHists2 = i_errHists; i_errHists2 != v_errHists.end();){
      ++i_errHists2;
      if(*i_errHists==*i_errHists2){
        edm::LogError("BookSectorHists")<<"Value of vErrHists in config exists twice: "<<*i_errHists<<"\n... delete one of both";
        v_errHists.erase(i_errHists2);
      }
    }
  }
  
  for(std::map<unsigned int,TrackerSectorStruct>::iterator i_sector = m_tkSector_.begin(); i_sector != m_tkSector_.end(); ++i_sector){
    
    bool zoomHists(parameterSet_.getParameter<bool>("zoomHists"));
    
    double widthMax = zoomHists ? 20. : 200.;
    double chargeMax = zoomHists ? 1000. : 10000.;
    double sOverNMax = zoomHists? 200. : 2000.;
    
    double resXAbsMax = zoomHists ? 0.5 : 5.;
    double norResXAbsMax = zoomHists ? 10. : 50.;
    double probXMin = zoomHists ? -0.01 :  -0.1;
    double probXMax = zoomHists ? 0.11 :  1.1;
    double sigmaXMin = zoomHists ? 0. : -0.05;
    double sigmaXMax = zoomHists ? 0.02 : 1.;
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
    
    std::stringstream sector; sector << "Sector_" << (*i_sector).first;
    TFileDirectory secDir = fileService->mkdir(sector.str().c_str());
    
    if((*i_sector).second.v_rawId.size()==0){
      TH1F* noModule(0);
      noModule = secDir.make<TH1F>("NoModuleInSector","",1,0,1);
      continue;
    }
    
    
    // Cluster Parameters
    (*i_sector).second.setCorrHistParams(&secDir,norResXAbsMax,sigmaXHitMax,sigmaXMax);
    (*i_sector).second.m_correlationHists["Width"] = (*i_sector).second.bookCorrHists("Width","cluster width","w_{cl}","[# strips]",200,20,0.,widthMax,"nph");
    (*i_sector).second.m_correlationHists["Charge"] = (*i_sector).second.bookCorrHists("Charge","cluster charge","c_{cl}","[APV counts]",100,50,0.,chargeMax,"nph");
    (*i_sector).second.m_correlationHists["MaxStrip"] = (*i_sector).second.bookCorrHists("MaxStrip","strip with max. charge","n_{cl,max}","[# strips]",800,800,-10.,790.,"npht");
    (*i_sector).second.m_correlationHists["MaxCharge"] = (*i_sector).second.bookCorrHists("MaxCharge","charge of strip with max. charge","c_{cl,max}","[APV counts]",300,75,-10.,290.,"nph");
    (*i_sector).second.m_correlationHists["MaxIndex"] = (*i_sector).second.bookCorrHists("MaxIndex","cluster-index of strip with max. charge","i_{cl,max}","[# strips]",10,10,0.,10.,"nph");
    (*i_sector).second.m_correlationHists["ChargeOnEdges"] = (*i_sector).second.bookCorrHists("ChargeOnEdges","fraction of charge on edge strips","(c_{st,L}+c_{st,R})/c_{cl}","",60,60,-0.1,1.1,"nph");
    (*i_sector).second.m_correlationHists["ChargeAsymmetry"] = (*i_sector).second.bookCorrHists("ChargeAsymmetry","asymmetry of charge on edge strips","(c_{st,L}-c_{st,R})/c_{cl}","",110,55,-1.1,1.1,"nph");
    (*i_sector).second.m_correlationHists["ChargeLRplus"] = (*i_sector).second.bookCorrHists("ChargeLRplus","fraction of charge not on maxStrip","(c_{cl,L}+c_{cl,R})/c_{cl}","",60,60,-0.1,1.1,"nph");
    (*i_sector).second.m_correlationHists["ChargeLRminus"] = (*i_sector).second.bookCorrHists("ChargeLRminus","asymmetry of charge L and R of maxStrip","(c_{cl,L}-c_{cl,R})/c_{cl}","",110,55,-1.1,1.1,"nph");
    (*i_sector).second.m_correlationHists["BaryStrip"] = (*i_sector).second.bookCorrHists("BaryStrip","barycenter of cluster charge","b_{cl}","[# strips]",800,100,-10.,790.,"nph");
    (*i_sector).second.m_correlationHists["SOverN"] = (*i_sector).second.bookCorrHists("SOverN","signal over noise","s/N","",100,50,0,sOverNMax,"nph");
    (*i_sector).second.m_correlationHists["WidthProj"] = (*i_sector).second.bookCorrHists("WidthProj","projected width","w_{p}","[# strips]",200,20,0.,widthMax,"nph");
    (*i_sector).second.m_correlationHists["WidthDiff"] = (*i_sector).second.bookCorrHists("WidthDiff","width difference","w_{p} - w_{cl}","[# strips]",200,20,-widthMax/2.,widthMax/2.,"nph");
    
    (*i_sector).second.WidthVsWidthProjected = secDir.make<TH2F>("h2_widthVsWidthProj","w_{cl} vs. w_{p};w_{p}  [# strips];w_{cl}  [# strips]",static_cast<int>(widthMax),0,widthMax,static_cast<int>(widthMax),0,widthMax);
    (*i_sector).second.PWidthVsWidthProjected = secDir.make<TProfile>("p_widthVsWidthProj","w_{cl} vs. w_{p};w_{p}  [# strips];w_{cl}  [# strips]",static_cast<int>(widthMax),0,widthMax);
    
    (*i_sector).second.WidthDiffVsMaxStrip = secDir.make<TH2F>("h2_widthDiffVsMaxStrip","(w_{p} - w_{cl}) vs. n_{cl,max};n_{cl,max};w_{p} - w_{cl}  [# strips]",800,-10.,790.,static_cast<int>(widthMax),-widthMax/2.,widthMax/2.);
    (*i_sector).second.PWidthDiffVsMaxStrip = secDir.make<TProfile>("p_widthDiffVsMaxStrip","(w_{p} - w_{cl}) vs. n_{cl,max};n_{cl,max};w_{p} - w_{cl}  [# strips]",800,-10.,790.);
    
    (*i_sector).second.WidthDiffVsSigmaXHit = secDir.make<TH2F>("h2_widthDiffVsSigmaXHit","(w_{p} - w_{cl}) vs. #sigma_{x,hit};#sigma_{x,hit}  [cm];w_{p} - w_{cl}  [# strips]",100,0.,sigmaXMax,100,-10.,10.);
    (*i_sector).second.PWidthDiffVsSigmaXHit = secDir.make<TProfile>("p_widthDiffVsSigmaXHit","(w_{p} - w_{cl}) vs. #sigma_{x,hit};#sigma_{x,hit}  [cm];w_{p} - w_{cl}  [# strips]",100,0.,sigmaXMax);
    
    
    // Hit Parameters
    (*i_sector).second.m_correlationHists["SigmaXHit"] = (*i_sector).second.bookCorrHists("SigmaXHit","hit error","#sigma_{x,hit}","[cm]",105,20,sigmaXMin,sigmaXMax,"np");
    (*i_sector).second.m_correlationHists["SigmaXTrk"] = (*i_sector).second.bookCorrHists("SigmaXTrk","track error","#sigma_{x,track}","[cm]",105,20,sigmaXMin,sigmaXMax,"np");
    (*i_sector).second.m_correlationHists["SigmaX"]    = (*i_sector).second.bookCorrHists("SigmaX","residual error","#sigma_{x}","[cm]",105,20,sigmaXMin,sigmaXMax,"np");
    (*i_sector).second.m_correlationHists["PhiSens"]   = (*i_sector).second.bookCorrHists("PhiSens","track angle on sensor","#phi_{module}","[ ^{o}]",94,47,-2,92,"nphtr");
    (*i_sector).second.m_correlationHists["PhiSensX"]  = (*i_sector).second.bookCorrHists("PhiSensX","track angle on sensor","#phi_{x,module}","[ ^{o}]",184,92,-92,92,"nphtr");
    (*i_sector).second.m_correlationHists["PhiSensY"]  = (*i_sector).second.bookCorrHists("PhiSensY","track angle on sensor","#phi_{y,module}","[ ^{o}]",184,92,-92,92,"nphtr");
    
    (*i_sector).second.XHit    = secDir.make<TH1F>("h_XHit"," hit measurement x_{hit};x_{hit}  [cm];# hits",100,-20,20);
    (*i_sector).second.XTrk    = secDir.make<TH1F>("h_XTrk","track prediction x_{track};x_{track}  [cm];# hits",100,-20,20);
    (*i_sector).second.SigmaX2 = secDir.make<TH1F>("h_SigmaX2","squared residual error #sigma_{x}^{2};#sigma_{x}^{2}  [cm^{2}];# hits",105,sigmaXMin,sigmaX2Max); //no mistake !
    (*i_sector).second.ResX    = secDir.make<TH1F>("h_ResX","residual r_{x};(x_{track}-x_{hit})'  [cm];# hits",100,-resXAbsMax,resXAbsMax);
    (*i_sector).second.NorResX = secDir.make<TH1F>("h_NorResX","normalized residual r_{x}/#sigma_{x};(x_{track}-x_{hit})'/#sigma_{x};# hits",100,-norResXAbsMax,norResXAbsMax);
    (*i_sector).second.ProbX   = secDir.make<TH1F>("h_ProbX","residual probability;prob(r_{x}^{2}/#sigma_{x}^{2},1);# hits",60,probXMin,probXMax);
    
    (*i_sector).second.WidthVsPhiSensX = secDir.make<TH2F>("h2_widthVsPhiSensX","w_{cl} vs. #phi_{x,module};#phi_{x,module}  [ ^{o}];w_{cl}  [# strips]",92,-92,92,static_cast<int>(widthMax),0,widthMax);
    (*i_sector).second.PWidthVsPhiSensX = secDir.make<TProfile>("p_widthVsPhiSensX","w_{cl} vs. #phi_{x,module};#phi_{x,module}  [ ^{o}];w_{cl}  [# strips]",92,-92,92);
    
    
    // Track Parameters
    (*i_sector).second.m_correlationHists["HitsValid"] = (*i_sector).second.bookCorrHists("HitsValid","# hits","[valid]",50,0,50,"npt");
    (*i_sector).second.m_correlationHists["HitsInvalid"] = (*i_sector).second.bookCorrHists("HitsInvalid","# hits","[invalid]",20,0,20,"npt");
    (*i_sector).second.m_correlationHists["Hits2D"] = (*i_sector).second.bookCorrHists("Hits2D","# hits","[2D]",20,0,20,"npth");
    (*i_sector).second.m_correlationHists["LayersMissed"] = (*i_sector).second.bookCorrHists("LayersMissed","# layers","[missed]",10,0,10,"npt");
    (*i_sector).second.m_correlationHists["HitsPixel"] = (*i_sector).second.bookCorrHists("HitsPixel","# hits","[pixel]",10,0,10,"npt");
    (*i_sector).second.m_correlationHists["HitsStrip"] = (*i_sector).second.bookCorrHists("HitsStrip","# hits","[strip]",40,0,40,"npt");
    (*i_sector).second.m_correlationHists["HitsGood"] = (*i_sector).second.bookCorrHists("HitsGood","# hits","[good]",50,0,50,"npt");
    (*i_sector).second.m_correlationHists["NorChi2"] = (*i_sector).second.bookCorrHists("NorChi2","#chi^{2}/ndof","",50,0,norChi2Max,"npr");
    (*i_sector).second.m_correlationHists["Theta"] = (*i_sector).second.bookCorrHists("Theta","#theta","[ ^{o}]",40,-10,190,"npt");
    (*i_sector).second.m_correlationHists["Phi"] = (*i_sector).second.bookCorrHists("Phi","#phi","[ ^{o}]",76,-190,190,"npt");
    (*i_sector).second.m_correlationHists["D0Beamspot"] = (*i_sector).second.bookCorrHists("D0Beamspot","d_{0, BS}","[cm]",40,-d0Max,d0Max,"npt");
    (*i_sector).second.m_correlationHists["Dz"] = (*i_sector).second.bookCorrHists("Dz","d_{z}","[cm]",40,-dzMax,dzMax,"npt");
    (*i_sector).second.m_correlationHists["Pt"] = (*i_sector).second.bookCorrHists("Pt","p_{t}","[GeV]",50,0,pMax,"npt");
    (*i_sector).second.m_correlationHists["P"] = (*i_sector).second.bookCorrHists("P","|p|","[GeV]",50,0,pMax,"npt");
    (*i_sector).second.m_correlationHists["InvP"] = (*i_sector).second.bookCorrHists("InvP","1/|p|","[GeV^{-1}]",25,0,invPMax,"t");
    (*i_sector).second.m_correlationHists["MeanAngle"] = (*i_sector).second.bookCorrHists("MeanAngle","<#phi_{module}>","[ ^{o}]",25,-5,95,"npt");
    //(*i_sector).second.m_correlationHists[""] = (*i_sector).second.bookCorrHists("","","",,,,"nphtr");
    
    
    
    
    
    for(std::vector<unsigned int>::iterator i_errHists = v_errHists.begin(); i_errHists != v_errHists.end(); ++i_errHists){
      double xMin(0.01*(*i_errHists-1)), xMax(0.01*(*i_errHists));
      std::stringstream sigmaXHit, sigmaXTrk, sigmaX;
      sigmaXHit << "h_sigmaXHit_" << *i_errHists;
      sigmaXTrk << "h_sigmaXTrk_" << *i_errHists;
      sigmaX    << "h_sigmaX_"    << *i_errHists;
      (*i_sector).second.m_sigmaX["sigmaXHit"].push_back(secDir.make<TH1F>(sigmaXHit.str().c_str(),"hit error #sigma_{x,hit};#sigma_{x,hit}  [cm];# hits",100,xMin,xMax));
      (*i_sector).second.m_sigmaX["sigmaXTrk"].push_back(secDir.make<TH1F>(sigmaXTrk.str().c_str(),"track error #sigma_{x,track};#sigma_{x,track}  [cm];# hits",100,xMin,xMax));
      (*i_sector).second.m_sigmaX["sigmaX"   ].push_back(secDir.make<TH1F>(sigmaX.str().c_str(),"residual error #sigma_{x};#sigma_{x}  [cm];# hits",100,xMin,xMax));
    }
    
  }
}



void
ApeEstimator::bookSectorHistsForApeCalculation(){
  
  std::vector<unsigned int> v_errHists(parameterSet_.getParameter<std::vector<unsigned int> >("vErrHists"));
  for(std::vector<unsigned int>::iterator i_errHists = v_errHists.begin(); i_errHists != v_errHists.end(); ++i_errHists){
    for(std::vector<unsigned int>::iterator i_errHists2 = i_errHists; i_errHists2 != v_errHists.end();){
      ++i_errHists2;
      if(*i_errHists==*i_errHists2){
        edm::LogError("BookSectorHists")<<"Value of vErrHists in config exists twice: "<<*i_errHists<<"\n... delete one of both";
        v_errHists.erase(i_errHists2);
      }
    }
  }
  
  for(std::map<unsigned int,TrackerSectorStruct>::iterator i_sector = m_tkSector_.begin(); i_sector != m_tkSector_.end(); ++i_sector){
    
    edm::Service<TFileService> fileService;
    if(!fileService){
      throw edm::Exception( edm::errors::Configuration,
                            "TFileService is not registered in cfg file" );
    }
    
    std::stringstream sector; sector << "Sector_" << (*i_sector).first;
    TFileDirectory secDir = fileService->mkdir(sector.str().c_str());
    
    if((*i_sector).second.v_rawId.size()==0){
      TH1F* noModule(0);
      noModule = secDir.make<TH1F>("NoModuleInSector","",1,0,1);
      continue;
    }
    
    
    if(m_resErrBins_.size()==0){m_resErrBins_[1].first = 0.;m_resErrBins_[1].second = 0.01;} // default if no selection taken into account: calculate APE with one bin with residual error 0-100um
    for(std::map<unsigned int,std::pair<double,double> >::const_iterator i_errBins = m_resErrBins_.begin();
         i_errBins != m_resErrBins_.end(); ++i_errBins){
      std::stringstream interval; interval << "Interval_" << (*i_errBins).first;
      TFileDirectory intDir = secDir.mkdir(interval.str().c_str());
      (*i_sector).second.m_binnedHists[(*i_errBins).first]["sigmaX"]  = intDir.make<TH1F>("h_sigmaX","residual error #sigma_{x};#sigma_{x}  [cm];# hits",100,0.,0.01);
      (*i_sector).second.m_binnedHists[(*i_errBins).first]["norResX"] = intDir.make<TH1F>("h_norResX","normalized residual r_{x}/#sigma_{x};(x_{track}-x_{hit})'/#sigma_{x};# hits",100,-10,10);
    }
    
    
    TFileDirectory resDir = secDir.mkdir("Results");
    
    // TTree containing rawIds of all modules in sector
    unsigned int rawId(0);
    (*i_sector).second.RawId = resDir.make<TTree>("rawIdTree","Tree containing rawIds of all modules in sector");
    (*i_sector).second.RawId->Branch("RawId", &rawId, "RawId/i");
    for(std::vector<unsigned int>::const_iterator i_rawId=(*i_sector).second.v_rawId.begin(); i_rawId!=(*i_sector).second.v_rawId.end(); ++i_rawId){
      rawId = (*i_rawId);
      (*i_sector).second.RawId->Fill();
    }
    
    //Result plots (one hist per sector containing one bin per interval)
    std::vector<double> v_binX(parameterSet_.getParameter<std::vector<double> >("residualErrorBinning"));
    (*i_sector).second.Entries         = resDir.make<TH1F>("h_entries","# hits used;#sigma_{x}  [cm];# hits",v_binX.size()-1,&(v_binX[0]));
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
  tkDetector_.HitsSize     = trkDir.make<TH1F>("h_hitsSize","# hits;# hits;# tracks",51,-1,50);
  tkDetector_.HitsValid    = trkDir.make<TH1F>("h_hitsValid","# hits  [valid];# hits  [valid];# tracks",51,-1,50);
  tkDetector_.HitsInvalid  = trkDir.make<TH1F>("h_hitsInvalid","# hits  [invalid];# hits  [invalid];# tracks",21,-1,20);
  tkDetector_.Hits2D       = trkDir.make<TH1F>("h_hits2D","# hits  [2D];# hits  [2D];# tracks",21,-1,20);
  tkDetector_.LayersMissed = trkDir.make<TH1F>("h_layersMissed","# layers  [missed];# layers  [missed];# tracks",11,-1,10);
  tkDetector_.HitsPixel    = trkDir.make<TH1F>("h_hitsPixel","# hits  [pixel];# hits  [pixel];# tracks",11,-1,10);
  tkDetector_.HitsStrip    = trkDir.make<TH1F>("h_hitsStrip","# hits  [strip];# hits  [strip];# tracks",41,-1,40);
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
  
  const reco::HitPattern& hitPattern(track.hitPattern());
  
  TrackStruct::TrackParameterStruct trkParams;
  
  trkParams.hitsSize     = track.recHitsSize();
  trkParams.hitsValid    = track.found(); // invalid is every hit from every single module that expects a hit
  //trkParams.hitsValid    = trkParams.hitsSize-trkParams.hitsLost;  // incorrect: unequal to .found(), because not every invalid hit is a lost one
  trkParams.hitsInvalid  = trkParams.hitsSize-trkParams.hitsValid;
  trkParams.layersMissed = track.lost();  // lost hit means, that a crossed layer doesn't contain a hit (can be more than one invalid hit)
  trkParams.hitsPixel    = hitPattern.numberOfValidPixelHits();
  trkParams.hitsStrip    = hitPattern.numberOfValidStripHits();
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
  
  const std::vector<TrajectoryMeasurement>& v_meas = traj.measurements();
     
  int count2D(0); float meanPhiSensToNorm(0.F);
  std::vector<TrajectoryMeasurement>::const_iterator i_meas;
  for(i_meas = v_meas.begin(); i_meas != v_meas.end(); ++i_meas){     
    const TrajectoryMeasurement& meas = *i_meas;
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
    if(trkParams.hitsStrip<11 || trkParams.hits2D<2 || trkParams.hitsPixel<2 || //trkParams.hitsInvalid>2 ||
       trkParams.hitsStrip>18 || trkParams.hitsPixel>5 ||
       trkParams.norChi2>5 ||
       trkParams.pt<15. || trkParams.pt>100. || 
       std::fabs(trkParams.d0Beamspot)>0.1 || std::fabs(trkParams.dz)>10.)trackCut_ = true;
    //if(trkParams.hitsValid<12 || trkParams.hits2D<2 || trkParams.hitsPixel<1 || //trkParams.hitsInvalid>2 ||
    //   trkParams.pt<15. || trkParams.p>100. || 
    //   std::fabs(trkParams.d0Beamspot)>0.1 || std::fabs(trkParams.dz)>10.)trackCut_ = true;
    //if(trkParams.hitsValid<12 || trkParams.hits2D<2 || trkParams.hitsPixel<1 || //trkParams.hitsInvalid>2 ||
    //   trkParams.pt<10. || trkParams.p<20. || trkParams.p>250. || 
    //   std::fabs(trkParams.d0Beamspot)>0.1 || std::fabs(trkParams.dz)>10.)trackCut_ = true;
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
ApeEstimator::fillHitVariables(const TrajectoryMeasurement& i_meas, const edm::EventSetup& iSetup){
  
  TrackStruct::HitParameterStruct hitParams;
  
  static TrajectoryStateCombiner tsoscomb;
  
  const TrajectoryMeasurement& meas = i_meas;
  const TransientTrackingRecHit& hit = *meas.recHit();
  const TrackingRecHit& recHit = *hit.hit();
  TrajectoryStateOnSurface tsos = tsoscomb(meas.forwardPredictedState(),meas.backwardPredictedState());
  
  DetId detId(hit.geographicalId());
  DetId::Detector detector = detId.det(); if(detector != DetId::Tracker){hitParams.hitState = TrackStruct::notInTracker; return hitParams;}
  uint32_t rawId(detId.rawId());
  
  for(std::map<unsigned int,TrackerSectorStruct>::const_iterator i_sector = m_tkSector_.begin(); i_sector != m_tkSector_.end(); ++i_sector){
    for(std::vector<unsigned int>::const_iterator i_rawId = (*i_sector).second.v_rawId.begin();
        i_rawId != (*i_sector).second.v_rawId.end(); ++i_rawId){
      if(rawId==*i_rawId){hitParams.v_sector.push_back((*i_sector).first); break;}
    }
  }
  
  //Moved to the end of the method (lose speed for more information contained)
  //if(0==hitParams.v_sector.size()){hitParams.hitState = TrackStruct::notAssignedToSectors; return hitParams;}
  
  
//  const align::LocalVector mom(tsos.localDirection());
//  int uDirectionMomentum(0), vDirectionMomentum(0), wDirectionMomentum(0);
//  uDirectionMomentum = static_cast<float>(m_tkTreeVar_[rawId].uDirection)*mom.x() > 0. ? 1 : -1; // > 0. -> momentum pointing in x' direction ( +phi)
//  vDirectionMomentum = static_cast<float>(m_tkTreeVar_[rawId].vDirection)*mom.y() > 0. ? 1 : -1; // > 0. -> momentum pointing in y' direction (Barrel: +z, Forward: +r)
//  wDirectionMomentum = static_cast<float>(m_tkTreeVar_[rawId].wDirection)*mom.z() > 0. ? 1 : -1; // > 0. -> momentum pointing in z' direction (Barrel: +r, Forward: +z)
//  //std::cout<<"\n\tMomentum:\t"<<mom.x()<<" "<<mom.y()<<" "<<mom.z()<<" "<<mom.phi()<<" "<<mom.theta();
//  //std::cout<<"\n\tOrientation:\t"<<m_tkTreeVar_[rawId].uDirection<<" "<<m_tkTreeVar_[rawId].vDirection<<" "<<m_tkTreeVar_[rawId].wDirection;
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
  float phiSensX = std::atan(std::fabs(mom.x()/mom.z()))*static_cast<float>(m_tkTreeVar_[rawId].vDirection);  // check for orientation of E- and B- Field (thoughts for barrel)
  float phiSensY = std::atan(std::fabs(mom.y()/mom.z()))*static_cast<float>(m_tkTreeVar_[rawId].vDirection);
  hitParams.phiSens  = std::atan(std::fabs(std::sqrt(mom.x()*mom.x()+mom.y()*mom.y())/mom.z()));
  hitParams.phiSensX = (xMomentum==zMomentum ? phiSensX : -phiSensX );
  hitParams.phiSensY = (yMomentum==zMomentum ? phiSensY : -phiSensY );
  
  
  if(!hit.isValid()){hitParams.hitState = TrackStruct::invalid; return hitParams;}
  
  
  // Get local positions and errors of hit and track
  LocalPoint lPHit = hit.localPosition(), lPTrk = tsos.localPosition();
  
  // use APE also for the hit error, while APE is automatically included in tsos error
  AlgebraicROOTObject<2>::SymMatrix mat = asSMatrix<2>(hit.parametersError());
  LocalError errHitApe = LocalError( mat(0,0),mat(0,1),mat(1,1) ),
             errHitWoApe = hit.localPositionError(),
	     errTrk = tsos.localError().positionError();
  
  if(errHitWoApe.xx()<0. || errHitWoApe.yy()<0. || errHitApe.xx()<0. || errHitApe.yy()<0. || errTrk.xx()<0. || errTrk.yy()<0.){
    hitParams.hitState = TrackStruct::negativeError;
    ++counter1;
    edm::LogError("Negative error Value")<<"@SUB=ApeEstimator::fillHitVariables"
                                         <<"One of the squared error methods gives negative result"
                                         <<"\n\tSubdetector\terrHitWoApe.xx()\terrHitWoApe.yy()\terrHitAPE.xx()\terrHitAPE.yy()\terrTrk.xx()\terrTrk.yy()"
                                         <<"\n\t"<<m_tkTreeVar_[rawId].subdetId<<"\t\t"<<errHitWoApe.xx()<<"\t"<<errHitWoApe.yy()
					 <<"\t"<<errHitApe.xx()<<"\t"<<errHitApe.yy()<<"\t"<<errTrk.xx()<<"\t"<<errTrk.yy();
    return hitParams;
  }
  
  
  // Calculate all positions, errors and residuals in primed coordinate system
  align::LocalVector res = lPTrk - lPHit;
  
  float xHit(999.F), xTrk(999.F);
  float yHit(999.F), yTrk(999.F);
  
  float errXHit(999.F), errXHitWoApe(999.F), errXTrk(999.F);
  float errYHit(999.F), errYHitWoApe(999.F), errYTrk(999.F);
  float errX(999.F), errXWoApe(999.F);
  float errY(999.F), errYWoApe(999.F);
  float resX(999.F), resY(999.F), norResX(999.F), norResY(999.F);
  
  if(m_tkTreeVar_[rawId].subdetId==PixelSubdetector::PixelBarrel || m_tkTreeVar_[rawId].subdetId==PixelSubdetector::PixelEndcap ||
     m_tkTreeVar_[rawId].subdetId==StripSubdetector::TIB || m_tkTreeVar_[rawId].subdetId==StripSubdetector::TOB){
    
    xHit = lPHit.x();
    xTrk = lPTrk.x();
    
    yHit = lPHit.y();
    yTrk = lPTrk.y();
    
    const float errXHit2(errHitApe.xx()), errXHitWoApe2(errHitWoApe.xx()), errXTrk2(errTrk.xx());
    const float errYHit2(errHitApe.yy()), errYHitWoApe2(errHitWoApe.yy()), errYTrk2(errTrk.yy());
    
    errXHit = std::sqrt(errXHit2);
    errXHitWoApe = std::sqrt(errXHitWoApe2);
    errXTrk = std::sqrt(errXTrk2);
    
    errYHit = std::sqrt(errYHit2);
    errYHitWoApe = std::sqrt(errYHitWoApe2);
    errYTrk = std::sqrt(errYTrk2);
    
    errX = std::sqrt(errXHit2 + errXTrk2);
    errXWoApe = std::sqrt(errXHitWoApe2 + errXTrk2);
    
    errY = std::sqrt(errYHit2 + errYTrk2);
    errYWoApe = std::sqrt(errYHitWoApe2 + errYTrk2);
    
    resX = res.x();
    resY = res.y();
    norResX = resX/errX;
    norResY = resY/errY;
  }
  else if(m_tkTreeVar_[rawId].subdetId==StripSubdetector::TID || m_tkTreeVar_[rawId].subdetId==StripSubdetector::TEC){
    // Local x in radial coordinates (global orientation not yet taken into account)
    // Local y not radial
    
    if(!hit.detUnit()){hitParams.hitState = TrackStruct::invalid; return hitParams;} // is it a single physical module?
    const GeomDetUnit& detUnit = *hit.detUnit();
    
    if(!dynamic_cast<const RadialStripTopology*>(&detUnit.type().topology())){hitParams.hitState = TrackStruct::invalid; return hitParams;}
    const RadialStripTopology& topol = dynamic_cast<const RadialStripTopology&>(detUnit.type().topology());
    
    MeasurementPoint measPosHit = topol.measurementPosition(lPHit);
    MeasurementPoint measPosTrk = topol.measurementPosition(lPTrk);
      
    MeasurementError measErrHitApe = topol.measurementError(lPHit,errHitApe);
    MeasurementError measErrHitWoApe = topol.measurementError(lPHit,errHitWoApe);
    MeasurementError measErrTrk = topol.measurementError(lPTrk,errTrk);
    
    if(measErrHitWoApe.uu()<0. || measErrHitWoApe.vv()<0. || measErrHitApe.uu()<0. || measErrHitApe.vv()<0. || measErrTrk.uu()<0. || measErrTrk.vv()<0.){
      ++counter1;
      
      const SiStripRecHit2D& stripHit = dynamic_cast<const SiStripRecHit2D&>(recHit);
      const SiStripCluster& stripCluster = *stripHit.cluster();
      SiStripClusterInfo clusterInfo = SiStripClusterInfo(stripCluster, iSetup);
      hitParams.width = clusterInfo.width();
      
      edm::LogError("Negative error Value")<<"@SUB=ApeEstimator::fillHitVariables"
                                           <<"One of the squared error methods gives negative result"
                                           <<"\n\tmeasErrHitWoApe.uu()\tmeasErrHitWoApe.vv()\tmeasErrHitApe.uu()\tmeasErrHitApe.vv()\tmeasErrTrk.uu()\tmeasErrTrk.vv()"
	                                   <<"\n\t"<<measErrHitWoApe.uu()<<"\t"<<measErrHitWoApe.vv()<<"\t"<<measErrHitApe.uu()<<"\t"<<measErrHitApe.vv()<<"\t"<<measErrTrk.uu()<<"\t"<<measErrTrk.vv()
					   <<"\n\nOriginalValues:\n"
					   <<lPHit.x()<<" "<<lPHit.y()<<"\n"
					   <<lPTrk.x()<<" "<<lPTrk.y()<<"\n"
					   <<errHitWoApe.xx()<<" "<<errHitWoApe.yy()<<"\n"
					   <<errHitApe.xx()<<" "<<errHitApe.yy()<<"\n"
					   <<"Subdet: "<<m_tkTreeVar_[rawId].subdetId<<" , Width: "<<hitParams.width;
      hitParams.hitState = TrackStruct::negativeError;
      return hitParams;
    }
    //else edm::LogError("No Negative error Value")<<"@SUB=ApeEstimator::fillHitVariables"
    //                                             <<"None of the squared error methods gives negative result !!!!!";
    
    
    
    const float r_0 = topol.originToIntersection();
    const float phiHit = topol.stripAngle(measPosHit.x());
    const float phiTrk = topol.stripAngle(measPosTrk.x());
    const float stripLengthHit = topol.localStripLength(lPHit);
    const float stripLengthTrk = topol.localStripLength(lPTrk);
    
    xHit = phiHit*r_0;
    xTrk = phiTrk*r_0;
    
    // Cartesian y
    yHit = lPHit.y();
    yTrk = lPTrk.y();
    // Trapezoidal y (symmetric around 0; length along strip)
    yHit = measPosHit.y()*stripLengthHit;
    yTrk = measPosTrk.y()*stripLengthTrk;
    // Radial y (not symmetric around 0; radial distance with minimum at middle strip at lower edge [0, yMax])
    const float l_0 = r_0 - topol.detHeight()/2;
    const float cosPhiHit(std::cos(phiHit)), sinPhiHit(std::sin(phiHit));
    const float cosPhiTrk(std::cos(phiTrk)), sinPhiTrk(std::sin(phiTrk));
    yHit = measPosHit.y()*stripLengthHit - 0.5*stripLengthHit + l_0*(1./cosPhiHit - 1.);
    yTrk = measPosTrk.y()*stripLengthTrk - 0.5*stripLengthTrk + l_0*(1./cosPhiTrk - 1.);
    
    
    const float angularWidth2(topol.angularWidth()*topol.angularWidth());
    const float stripLengthHit2(stripLengthHit*stripLengthHit);
    const float stripLengthTrk2(stripLengthTrk*stripLengthTrk);
    const float errPhiHit2(angularWidth2*measErrHitApe.uu()), errPhiHitWoApe2(angularWidth2*measErrHitWoApe.uu()), errPhiTrk2(angularWidth2*measErrTrk.uu());
    const float errXHit2(errPhiHit2*r_0*r_0), errXHitWoApe2(errPhiHitWoApe2*r_0*r_0), errXTrk2(errPhiTrk2*r_0*r_0);
    // Cartesian y
    //const float errYHit2(errHitApe.yy()), errYHitWoApe2(errHitWoApe.yy()), errYTrk2(errTrk.yy());
    // Trapezoidal y (symmetric around 0, length along strip)
    //const float errYHit2(measErrHitApe.vv()*stripLengthHit2), errYHitWoApe2(measErrHitWoApe.vv()*stripLengthHit2), errYTrk2(measErrTrk.vv()*stripLengthTrk2);
    // Radial y (not symmetric around 0, real radial distance from intersection point)
    const float cosPhiHit4(std::pow(cosPhiHit,4)), sinPhiHit2(sinPhiHit*sinPhiHit);
    const float cosPhiTrk4(std::pow(cosPhiTrk,4)), sinPhiTrk2(sinPhiTrk*sinPhiTrk);
    const float helpSummandHit = l_0*l_0*(sinPhiHit2/cosPhiHit4*errPhiHit2);
    const float helpSummandHitWoApe = l_0*l_0*(sinPhiHit2/cosPhiHit4*errPhiHitWoApe2);
    const float helpSummandTrk = l_0*l_0*(sinPhiTrk2/cosPhiTrk4*errPhiTrk2);
    const float errYHit2(measErrHitApe.vv()*stripLengthHit2+helpSummandHit), errYHitWoApe2(measErrHitWoApe.vv()*stripLengthHit2+helpSummandHitWoApe), errYTrk2(measErrTrk.vv()*stripLengthTrk2+helpSummandTrk);
    
    
    
    errXHit = std::sqrt(errXHit2);
    errXHitWoApe = std::sqrt(errXHitWoApe2);
    errXTrk = std::sqrt(errXTrk2);
    
    errYHit = std::sqrt(errYHit2);
    errYHitWoApe = std::sqrt(errYHitWoApe2);
    errYTrk = std::sqrt(errYTrk2);
    
    errX = std::sqrt(errXHit2 + errXTrk2);
    errXWoApe = std::sqrt(errXHitWoApe2 + errXTrk2);
    
    errY = std::sqrt(errYHit2 + errYTrk2);
    errYWoApe = std::sqrt(errYHitWoApe2 + errYTrk2);
    
    resX = xTrk - xHit;
    resY = yTrk - yHit;
    
    norResX = resX/errX;
    norResY = resY/errY;
  }
  
  
  // Take global orientation into account for residuals (sign is not important for errors)
  float resXprime(999.F), resYprime(999.F), norResXprime(999.F), norResYprime(999.F);
  if(m_tkTreeVar_[rawId].uDirection == 1){resXprime = resX; norResXprime = norResX;}
  else if(m_tkTreeVar_[rawId].uDirection == -1){resXprime = -resX; norResXprime = -norResX;}
  else {edm::LogError("FillHitVariables")<<"Incorrect value of uDirection, which gives global module orientation"; hitParams.hitState = TrackStruct::invalid; return hitParams;}
  if(m_tkTreeVar_[rawId].vDirection == 1){resYprime = resY; norResYprime = norResY;}
  else if(m_tkTreeVar_[rawId].vDirection == -1){resYprime = -resY; norResYprime = -norResY;}
  else {edm::LogError("FillHitVariables")<<"Incorrect value of vDirection, which gives global module orientation"; hitParams.hitState = TrackStruct::invalid; return hitParams;}
  
  hitParams.xHit = xHit;
  hitParams.xTrk = xTrk;
  
  hitParams.errXHit = errXHit;
  hitParams.errXHitWoApe = errXHitWoApe;
  hitParams.errXTrk = errXTrk;
  
  hitParams.errX2 = errX*errX;
  hitParams.errX = errX;
  hitParams.errXWoApe = errXWoApe;

  hitParams.resX    = resXprime;
  hitParams.norResX = norResXprime;
  
  float norResX2(norResXprime*norResXprime);
  hitParams.probX   = TMath::Prob(norResX2,1);
  
  
  
  // Cluster parameters
  
  if(m_tkTreeVar_[rawId].subdetId==PixelSubdetector::PixelBarrel || m_tkTreeVar_[rawId].subdetId==PixelSubdetector::PixelEndcap){
    //const SiPixelRecHit& pixelHit = dynamic_cast<const SiPixelRecHit&>(recHit);
    //const SiPixelCluster& pixelCluster = *pixelHit.cluster();
  }
  else if(m_tkTreeVar_[rawId].subdetId==StripSubdetector::TIB || m_tkTreeVar_[rawId].subdetId==StripSubdetector::TOB ||
          m_tkTreeVar_[rawId].subdetId==StripSubdetector::TID || m_tkTreeVar_[rawId].subdetId==StripSubdetector::TEC){
    if(!(dynamic_cast<const SiStripRecHit2D*>(&recHit) || dynamic_cast<const SiStripRecHit1D*>(&recHit))){
      edm::LogError("FillHitVariables")<<"RecHit in Strip is 'Matched' or 'Projected', but here all should be monohits per module";
      hitParams.hitState = TrackStruct::invalid; return hitParams;
    }
    const SiStripCluster* clusterPtr(0);
    if(m_tkTreeVar_[rawId].subdetId==StripSubdetector::TIB || m_tkTreeVar_[rawId].subdetId==StripSubdetector::TOB){
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
    else if(m_tkTreeVar_[rawId].subdetId==StripSubdetector::TID || m_tkTreeVar_[rawId].subdetId==StripSubdetector::TEC){
       const SiStripRecHit2D& stripHit = dynamic_cast<const SiStripRecHit2D&>(recHit);
       clusterPtr = &(*stripHit.cluster());
    }
    if(!clusterPtr){
      edm::LogError("FillHitVariables")<<"Pointer to cluster not valid!!! This should never happen...";
      hitParams.hitState = TrackStruct::invalid; return hitParams;
    }
    const SiStripCluster& stripCluster(*clusterPtr);
    const SiStripClusterInfo clusterInfo = SiStripClusterInfo(stripCluster, iSetup);
    //const std::vector<uint8_t>& stripCharges = clusterInfo.stripCharges();
    const std::vector<uint8_t>::const_iterator stripChargeL(clusterInfo.stripCharges().begin());
    const std::vector<uint8_t>::const_iterator stripChargeR(--(clusterInfo.stripCharges().end()));
    const std::pair<uint16_t, uint16_t> stripChargeLR = std::make_pair(*stripChargeL,*stripChargeR);
    
    hitParams.isModuleUsable   = clusterInfo.IsModuleUsable();
    hitParams.width            = clusterInfo.width();
    hitParams.maxStrip         = clusterInfo.maxStrip() +1;
    hitParams.maxStripInv      = m_tkTreeVar_[rawId].nStrips - hitParams.maxStrip +1;
    hitParams.charge           = clusterInfo.charge();
    hitParams.maxCharge        = clusterInfo.maxCharge();
    hitParams.maxIndex         = clusterInfo.maxIndex();
    hitParams.chargeOnEdges    = static_cast<float>(stripChargeLR.first + stripChargeLR.second)/static_cast<float>(hitParams.charge);
    hitParams.chargeAsymmetry  = static_cast<float>(stripChargeLR.first - stripChargeLR.second)/static_cast<float>(stripChargeLR.first + stripChargeLR.second);
    hitParams.chargeLRplus     = static_cast<float>(clusterInfo.chargeLR().first + clusterInfo.chargeLR().second)/static_cast<float>(hitParams.charge);
    hitParams.chargeLRminus    = static_cast<float>(clusterInfo.chargeLR().first - clusterInfo.chargeLR().second)/static_cast<float>(hitParams.charge);
    hitParams.baryStrip        = clusterInfo.baryStrip() +1.;
    hitParams.sOverN           = clusterInfo.signalOverNoise();
    
    // Calculate projection length corrected by drift
    if(!hit.detUnit()){hitParams.hitState = TrackStruct::invalid; return hitParams;} // is it a single physical module?
    const GeomDetUnit& detUnit = *hit.detUnit();
    if(!dynamic_cast<const StripTopology*>(&detUnit.type().topology())){hitParams.hitState = TrackStruct::invalid; return hitParams;}
    
    
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
    
    
    
    const StripTopology& topol = dynamic_cast<const StripTopology&>(detUnit.type().topology());
    LocalVector momentumDir(tsos.localDirection());
    LocalPoint momentumPos(tsos.localPosition());
    LocalVector scaledMomentumDir(momentumDir);
    if(momentumDir.z() > 0.)scaledMomentumDir *= std::fabs(thickness/momentumDir.z());
    else if(momentumDir.z() < 0.)scaledMomentumDir *= -std::fabs(thickness/momentumDir.z());
    else scaledMomentumDir *= maxLength/momentumDir.mag();
    
    float projEdge1 = topol.measurementPosition(momentumPos - 0.5*scaledMomentumDir).x();
    //std::cout<<"Edge 1: "<<projEdge1<<"\n";
    if(projEdge1 < 0.)projEdge1 = 0.;
    else if(projEdge1 > m_tkTreeVar_[rawId].nStrips)projEdge1 = m_tkTreeVar_[rawId].nStrips;
    float projEdge2 = topol.measurementPosition(momentumPos + 0.5*scaledMomentumDir).x();
    //std::cout<<"Edge 2: "<<projEdge2<<"\n";
    if(projEdge2 < 0.)projEdge1 = 0.;
    else if(projEdge2 > m_tkTreeVar_[rawId].nStrips)projEdge1 = m_tkTreeVar_[rawId].nStrips;
    
    
    float coveredStrips = std::fabs(projEdge2 - projEdge1);
    //std::cout<<"Covered strips: "<<coveredStrips<<"\nWidth: "<<hitParams.width<<"\n";
    
    hitParams.projWidth = coveredStrips;
    
    
    
    
  }
  else{
    edm::LogError("FillHitVariables")<<"Incorrect subdetector ID, hit not associated to tracker";
    hitParams.hitState = TrackStruct::notInTracker; return hitParams;
  }
  
  
  if(!hitParams.isModuleUsable){hitParams.hitState = TrackStruct::invalid; return hitParams;}
  
  if(0==hitParams.v_sector.size()){hitParams.hitState = TrackStruct::notAssignedToSectors; return hitParams;}
  
  return hitParams;
  
}



ApeEstimator::PositionAndError2
ApeEstimator::positionAndError2(const LocalPoint& lP, const LocalError& lE, const uint32_t& rawId)const{
  PositionAndError2 pE2;
  return pE2;
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
  this->setHitSelectionMap("chargeLRplus");
  this->setHitSelectionMap("chargeLRminus");
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
  for(std::map<std::string, std::vector<double> >::iterator i_hitSelection = m_hitSelection_.begin(); i_hitSelection != m_hitSelection_.end(); ++i_hitSelection){
    if(0 < (*i_hitSelection).second.size()){
      //emptyMap = false;
      int entry(1); double intervalBegin(999.);
      for(std::vector<double>::iterator i_hitInterval = (*i_hitSelection).second.begin(); i_hitInterval != (*i_hitSelection).second.end(); ++entry){
        if(entry%2==1){intervalBegin = *i_hitInterval; ++i_hitInterval;}
	else{
	  if(intervalBegin > *i_hitInterval){
	    edm::LogError("HitSelector")<<"INVALID Interval selected for  "<<(*i_hitSelection).first<<":\t"<<intervalBegin<<" > "<<(*i_hitInterval)
	                                <<"\n ... delete Selection for "<<(*i_hitSelection).first;
	    (*i_hitSelection).second.clear(); i_hitInterval = (*i_hitSelection).second.begin(); //emptyMap = true; i_hitSelection = m_hitSelection_.begin();
	  }else{
	    edm::LogInfo("HitSelector")<<"Interval selected for  "<<(*i_hitSelection).first<<":\t"<<intervalBegin<<", "<<(*i_hitInterval);
            ++i_hitInterval;
	  }
	}
      }
      if(0 < (*i_hitSelection).second.size())emptyMap = false;
    }
  }
  
  
  bool emptyMapUInt(true);
  for(std::map<std::string, std::vector<unsigned int> >::iterator i_hitSelection = m_hitSelectionUInt_.begin(); i_hitSelection != m_hitSelectionUInt_.end(); ++i_hitSelection){
    if(0 < (*i_hitSelection).second.size()){
      //emptyMap = false;
      int entry(1); unsigned int intervalBegin(999);
      for(std::vector<unsigned int>::iterator i_hitInterval = (*i_hitSelection).second.begin(); i_hitInterval != (*i_hitSelection).second.end(); ++entry){
        if(entry%2==1){intervalBegin = *i_hitInterval; ++i_hitInterval;}
	else{
	  if(intervalBegin > *i_hitInterval){
	    edm::LogError("HitSelector")<<"INVALID Interval selected for  "<<(*i_hitSelection).first<<":\t"<<intervalBegin<<" > "<<(*i_hitInterval)
	                                <<"\n ... delete Selection for "<<(*i_hitSelection).first;
	    (*i_hitSelection).second.clear(); i_hitInterval = (*i_hitSelection).second.begin(); //emptyMap = true; i_hitSelection = m_hitSelection_.begin();
	  }else{
	    edm::LogInfo("HitSelector")<<"Interval selected for  "<<(*i_hitSelection).first<<":\t"<<intervalBegin<<", "<<(*i_hitInterval);
            ++i_hitInterval;
	  }
	}
      }
      if(0 < (*i_hitSelection).second.size())emptyMapUInt = false;
    }
  }
  
  if(emptyMap && emptyMapUInt){
    m_hitSelection_.clear();
    m_hitSelectionUInt_.clear();
    edm::LogInfo("HitSelector")<<"NO hit cuts applied";
  }
  return;
}



void
ApeEstimator::setHitSelectionMap(const std::string& cutVariable){
  edm::ParameterSet parSet(parameterSet_.getParameter<edm::ParameterSet>("HitSelector"));
  std::vector<double> v_cutVariable(parSet.getParameter<std::vector<double> >(cutVariable));
  if(v_cutVariable.size()%2==1){
    edm::LogError("HitSelector")<<"Invalid Hit Selection for "<<cutVariable<<": need even number of arguments (intervals)"
                                <<"\n ... delete Selection for "<<cutVariable;
    v_cutVariable.clear();
    m_hitSelection_[cutVariable] = v_cutVariable;
    return;
  }
  m_hitSelection_[cutVariable] = v_cutVariable;
  return;
}


void
ApeEstimator::setHitSelectionMapUInt(const std::string& cutVariable){
  edm::ParameterSet parSet(parameterSet_.getParameter<edm::ParameterSet>("HitSelector"));
  std::vector<unsigned int> v_cutVariable(parSet.getParameter<std::vector<unsigned int> >(cutVariable));
  if(v_cutVariable.size()%2==1){
    edm::LogError("HitSelector")<<"Invalid Hit Selection for "<<cutVariable<<": need even number of arguments (intervals)"
                                <<"\n ... delete Selection for "<<cutVariable;
    v_cutVariable.clear();
    m_hitSelectionUInt_[cutVariable] = v_cutVariable;
    return;
  }
  m_hitSelectionUInt_[cutVariable] = v_cutVariable;
  return;
}



bool
ApeEstimator::hitSelected(const TrackStruct::HitParameterStruct& hitParams)const{
  //if(hitParams.hitState == TrackStruct::notInTracker || hitParams.hitState == TrackStruct::notAssignedToSectors)return false;
  if(hitParams.hitState == TrackStruct::notInTracker)return false;
  if(hitParams.hitState == TrackStruct::invalid || hitParams.hitState == TrackStruct::negativeError)return false;
  if(0==m_hitSelection_.size())return true;
  for(std::map<std::string, std::vector<double> >::const_iterator i_hitSelection = m_hitSelection_.begin(); i_hitSelection != m_hitSelection_.end(); ++i_hitSelection){
    if(0==(*i_hitSelection).second.size())continue;
    float variable(999.F);
    
    if     ((*i_hitSelection).first == "widthProj")       variable = hitParams.projWidth;
    else if((*i_hitSelection).first == "widthDiff")       variable = hitParams.projWidth-static_cast<float>(hitParams.width);
    else if((*i_hitSelection).first == "charge")          variable = hitParams.charge;
    else if((*i_hitSelection).first == "maxCharge")       variable = hitParams.maxCharge;
    else if((*i_hitSelection).first == "chargeOnEdges")   variable = hitParams.chargeOnEdges;
    else if((*i_hitSelection).first == "chargeAsymmetry") variable = hitParams.chargeAsymmetry;
    else if((*i_hitSelection).first == "chargeLRplus")    variable = hitParams.chargeLRplus;
    else if((*i_hitSelection).first == "chargeLRminus")   variable = hitParams.chargeLRminus;
    else if((*i_hitSelection).first == "sOverN")          variable = hitParams.sOverN;
    
    else if((*i_hitSelection).first == "resX")            variable = hitParams.resX;
    else if((*i_hitSelection).first == "norResX")         variable = hitParams.norResX;
    else if((*i_hitSelection).first == "probX")           variable = hitParams.probX;
    else if((*i_hitSelection).first == "errXHit")         variable = hitParams.errXHit;
    else if((*i_hitSelection).first == "errXTrk")         variable = hitParams.errXTrk;
    else if((*i_hitSelection).first == "errX")            variable = hitParams.errX;
    else if((*i_hitSelection).first == "errX2")           variable = hitParams.errX2;
    else if((*i_hitSelection).first == "phiSens")         variable = hitParams.phiSens;
    else if((*i_hitSelection).first == "phiSensX")        variable = hitParams.phiSensX;
    else if((*i_hitSelection).first == "phiSensY")        variable = hitParams.phiSensY;
    
    int entry(1); double intervalBegin(999.);
    bool isSelected(false);
    for(std::vector<double>::const_iterator i_hitInterval = (*i_hitSelection).second.begin(); i_hitInterval != (*i_hitSelection).second.end(); ++i_hitInterval, ++entry){
      if(entry%2==1)intervalBegin = *i_hitInterval;
      else if(variable>=intervalBegin && variable<*i_hitInterval)isSelected = true;
    }
    if(!isSelected)return false;
  }
  
  for(std::map<std::string, std::vector<unsigned int> >::const_iterator i_hitSelection = m_hitSelectionUInt_.begin(); i_hitSelection != m_hitSelectionUInt_.end(); ++i_hitSelection){
    if(0==(*i_hitSelection).second.size())continue;
    unsigned int variable(999), variable2(999);
    
    if     ((*i_hitSelection).first == "width")      variable = hitParams.width;
    else if((*i_hitSelection).first == "edgeStrips"){variable = hitParams.maxStrip; variable2 = hitParams.maxStripInv;}
    else if((*i_hitSelection).first == "maxIndex")   variable = hitParams.maxIndex;
    
    int entry(1); unsigned int intervalBegin(999);
    bool isSelected(false);
    for(std::vector<unsigned int>::const_iterator i_hitInterval = (*i_hitSelection).second.begin(); i_hitInterval != (*i_hitSelection).second.end(); ++i_hitInterval, ++entry){
      if(entry%2==1)intervalBegin = *i_hitInterval;
      else if(variable>=intervalBegin && variable<=*i_hitInterval){
        if(variable2==999 || (variable2>=intervalBegin && variable2<=*i_hitInterval))isSelected = true;
      }
    }
    if(!isSelected)return false;
  }
  
  return true;
}



// -----------------------------------------------------------------------------------------------------------


void
ApeEstimator::fillHistsForAnalyzerMode(const TrackStruct& trackStruct){
  
  unsigned int goodHitsPerTrack(trackStruct.v_hitParams.size());
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
  tkDetector_.HitsPixel   ->Fill(trackStruct.trkParams.hitsPixel);
  tkDetector_.HitsStrip   ->Fill(trackStruct.trkParams.hitsStrip);
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
  
  for(std::vector<TrackStruct::HitParameterStruct>::const_iterator i_hit = trackStruct.v_hitParams.begin();
      i_hit != trackStruct.v_hitParams.end(); ++i_hit){
    //Put here from earlier method
    if(i_hit->hitState == TrackStruct::notAssignedToSectors)continue;
    
    for(std::map<unsigned int,TrackerSectorStruct>::iterator i_sector = m_tkSector_.begin(); i_sector != m_tkSector_.end(); ++i_sector){
      
      bool moduleInSector(false);
      for(std::vector<unsigned int>::const_iterator i_hitSector = (*i_hit).v_sector.begin(); i_hitSector != (*i_hit).v_sector.end(); ++i_hitSector){
	if((*i_sector).first == *i_hitSector){moduleInSector = true; break;}
      }
      if(!moduleInSector)continue;
      
      
      // Cluster Parameters
      (*i_sector).second.m_correlationHists["Width"].fillCorrHists(*i_hit,(*i_hit).width);
      (*i_sector).second.m_correlationHists["Charge"].fillCorrHists(*i_hit,(*i_hit).charge);
      (*i_sector).second.m_correlationHists["MaxStrip"].fillCorrHists(*i_hit,(*i_hit).maxStrip);
      (*i_sector).second.m_correlationHists["MaxCharge"].fillCorrHists(*i_hit,(*i_hit).maxCharge);
      (*i_sector).second.m_correlationHists["MaxIndex"].fillCorrHists(*i_hit,(*i_hit).maxIndex);
      (*i_sector).second.m_correlationHists["ChargeOnEdges"].fillCorrHists(*i_hit,(*i_hit).chargeOnEdges);
      (*i_sector).second.m_correlationHists["ChargeAsymmetry"].fillCorrHists(*i_hit,(*i_hit).chargeAsymmetry);
      (*i_sector).second.m_correlationHists["ChargeLRplus"].fillCorrHists(*i_hit,(*i_hit).chargeLRplus);
      (*i_sector).second.m_correlationHists["ChargeLRminus"].fillCorrHists(*i_hit,(*i_hit).chargeLRminus);
      (*i_sector).second.m_correlationHists["BaryStrip"].fillCorrHists(*i_hit,(*i_hit).baryStrip);
      (*i_sector).second.m_correlationHists["SOverN"].fillCorrHists(*i_hit,(*i_hit).sOverN);
      (*i_sector).second.m_correlationHists["WidthProj"].fillCorrHists(*i_hit,(*i_hit).projWidth);
      (*i_sector).second.m_correlationHists["WidthDiff"].fillCorrHists(*i_hit,(*i_hit).projWidth-static_cast<float>((*i_hit).width));
      
      (*i_sector).second.WidthVsWidthProjected->Fill((*i_hit).projWidth,(*i_hit).width);
      (*i_sector).second.PWidthVsWidthProjected->Fill((*i_hit).projWidth,(*i_hit).width);
      
      (*i_sector).second.WidthDiffVsMaxStrip->Fill((*i_hit).maxStrip,(*i_hit).projWidth-static_cast<float>((*i_hit).width));
      (*i_sector).second.PWidthDiffVsMaxStrip->Fill((*i_hit).maxStrip,(*i_hit).projWidth-static_cast<float>((*i_hit).width));
      
      (*i_sector).second.WidthDiffVsSigmaXHit->Fill((*i_hit).errXHit,(*i_hit).projWidth-static_cast<float>((*i_hit).width));
      (*i_sector).second.PWidthDiffVsSigmaXHit->Fill((*i_hit).errXHit,(*i_hit).projWidth-static_cast<float>((*i_hit).width));
      
      
      // Hit Parameters
      (*i_sector).second.m_correlationHists["SigmaXHit"].fillCorrHists(*i_hit,(*i_hit).errXHit);
      (*i_sector).second.m_correlationHists["SigmaXTrk"].fillCorrHists(*i_hit,(*i_hit).errXTrk);
      (*i_sector).second.m_correlationHists["SigmaX"].fillCorrHists(*i_hit,(*i_hit).errX);
      
      (*i_sector).second.m_correlationHists["PhiSens"].fillCorrHists(*i_hit,(*i_hit).phiSens*180./M_PI);
      (*i_sector).second.m_correlationHists["PhiSensX"].fillCorrHists(*i_hit,(*i_hit).phiSensX*180./M_PI);
      (*i_sector).second.m_correlationHists["PhiSensY"].fillCorrHists(*i_hit,(*i_hit).phiSensY*180./M_PI);
      
      (*i_sector).second.XHit   ->Fill((*i_hit).xHit);
      (*i_sector).second.XTrk   ->Fill((*i_hit).xTrk);
      (*i_sector).second.SigmaX2->Fill((*i_hit).errX2);
      
      (*i_sector).second.ResX   ->Fill((*i_hit).resX);
      (*i_sector).second.NorResX->Fill((*i_hit).norResX);
      
      (*i_sector).second.ProbX->Fill((*i_hit).probX);
      
      (*i_sector).second.WidthVsPhiSensX->Fill((*i_hit).phiSensX*180./M_PI,(*i_hit).width);
      (*i_sector).second.PWidthVsPhiSensX->Fill((*i_hit).phiSensX*180./M_PI,(*i_hit).width);
      
      
      // Track Parameters
      (*i_sector).second.m_correlationHists["HitsValid"].fillCorrHists(*i_hit,trackStruct.trkParams.hitsValid);
      (*i_sector).second.m_correlationHists["HitsGood"].fillCorrHists(*i_hit,goodHitsPerTrack);
      (*i_sector).second.m_correlationHists["HitsInvalid"].fillCorrHists(*i_hit,trackStruct.trkParams.hitsInvalid);
      (*i_sector).second.m_correlationHists["Hits2D"].fillCorrHists(*i_hit,trackStruct.trkParams.hits2D);
      (*i_sector).second.m_correlationHists["LayersMissed"].fillCorrHists(*i_hit,trackStruct.trkParams.layersMissed);
      (*i_sector).second.m_correlationHists["HitsPixel"].fillCorrHists(*i_hit,trackStruct.trkParams.hitsPixel);
      (*i_sector).second.m_correlationHists["HitsStrip"].fillCorrHists(*i_hit,trackStruct.trkParams.hitsStrip);
      (*i_sector).second.m_correlationHists["NorChi2"].fillCorrHists(*i_hit,trackStruct.trkParams.norChi2);
      (*i_sector).second.m_correlationHists["Theta"].fillCorrHists(*i_hit,trackStruct.trkParams.theta*180./M_PI);
      (*i_sector).second.m_correlationHists["Phi"].fillCorrHists(*i_hit,trackStruct.trkParams.phi*180./M_PI);
      (*i_sector).second.m_correlationHists["D0Beamspot"].fillCorrHists(*i_hit,trackStruct.trkParams.d0Beamspot);
      (*i_sector).second.m_correlationHists["Dz"].fillCorrHists(*i_hit,trackStruct.trkParams.dz);
      (*i_sector).second.m_correlationHists["Pt"].fillCorrHists(*i_hit,trackStruct.trkParams.pt);
      (*i_sector).second.m_correlationHists["P"].fillCorrHists(*i_hit,trackStruct.trkParams.p);
      (*i_sector).second.m_correlationHists["InvP"].fillCorrHists(*i_hit,1./trackStruct.trkParams.p);
      (*i_sector).second.m_correlationHists["MeanAngle"].fillCorrHists(*i_hit,trackStruct.trkParams.meanPhiSensToNorm*180./M_PI);
      
      //(*i_sector).second.m_correlationHists[""].fillCorrHists(*i_hit,(*i_hit).);
      
      
      
      // Special Histograms
      for(std::map<std::string,std::vector<TH1*> >::iterator i_sigmaX = (*i_sector).second.m_sigmaX.begin(); i_sigmaX != (*i_sector).second.m_sigmaX.end(); ++i_sigmaX){
        for(std::vector<TH1*>::iterator iHist = (*i_sigmaX).second.begin(); iHist != (*i_sigmaX).second.end(); ++iHist){
	  if     ((*i_sigmaX).first=="sigmaXHit")(*iHist)->Fill((*i_hit).errXHit);
	  else if((*i_sigmaX).first=="sigmaXTrk")(*iHist)->Fill((*i_hit).errXTrk);
	  else if((*i_sigmaX).first=="sigmaX")   (*iHist)->Fill((*i_hit).errX);
	}
      }
      
    }
  }
}



void
ApeEstimator::fillHistsForApeCalculation(const TrackStruct& trackStruct){
  
  unsigned int goodHitsPerTrack(trackStruct.v_hitParams.size());
  
  if(parameterSet_.getParameter<bool>("applyTrackCuts")){
    // which tracks to take? need min. nr. of selected hits?
    if(goodHitsPerTrack < minGoodHitsPerTrack_)return;
  }
  
  
  for(std::vector<TrackStruct::HitParameterStruct>::const_iterator i_hit = trackStruct.v_hitParams.begin();
      i_hit != trackStruct.v_hitParams.end(); ++i_hit){
    //Put here from earlier method
    if(i_hit->hitState == TrackStruct::notAssignedToSectors)continue;
    
    for(std::map<unsigned int,TrackerSectorStruct>::iterator i_sector = m_tkSector_.begin(); i_sector != m_tkSector_.end(); ++i_sector){
      
      bool moduleInSector(false);
      for(std::vector<unsigned int>::const_iterator i_hitSector = (*i_hit).v_sector.begin(); i_hitSector != (*i_hit).v_sector.end(); ++i_hitSector){
	if((*i_sector).first == *i_hitSector){moduleInSector = true; break;}
      }
      if(!moduleInSector)continue;
      
      
      
      
      
      
      if(!calculateApe_)continue;
      
      for(std::map<unsigned int,std::pair<double,double> >::const_iterator i_errBins = m_resErrBins_.begin();
          i_errBins != m_resErrBins_.end(); ++i_errBins){
	// Separate the bins for residual resolution w/o APE, to be consistent within iterations where APE will change (have same hit always in same bin)
	// So also fill this value in the histogram sigmaX
	// But of course use the normalized residual regarding the APE to have its influence in its width
	if((*i_hit).errXWoApe < (*i_errBins).second.first || (*i_hit).errXWoApe >= (*i_errBins).second.second){
	  continue;
	}
	(*i_sector).second.m_binnedHists[(*i_errBins).first]["sigmaX"] ->Fill((*i_hit).errXWoApe);
	(*i_sector).second.m_binnedHists[(*i_errBins).first]["norResX"]->Fill((*i_hit).norResX);
	break;
      }
      
    }
  }
}




// -----------------------------------------------------------------------------------------------------------



void
ApeEstimator::calculateAPE(){
   // Loop over sectors for calculating APE
   for(std::map<unsigned int,TrackerSectorStruct>::iterator i_sector = m_tkSector_.begin(); i_sector != m_tkSector_.end(); ++i_sector){
     
     
     // Loop over residual error bins to calculate APE for every bin
     for(std::map<unsigned int, std::map<std::string,TH1*> >::const_iterator i_errBins = (*i_sector).second.m_binnedHists.begin();
         i_errBins != (*i_sector).second.m_binnedHists.end(); ++i_errBins){
       std::map<std::string,TH1*> mHists = (*i_errBins).second;
       
       // Fitting Parameters
       double integral = mHists["norResX"]->Integral();
       
       (*i_sector).second.Entries->SetBinContent((*i_errBins).first, integral);
     }
   }
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
   
   TrajTrackAssociationCollection::const_iterator i_trajTrack;
   for(i_trajTrack = m_TrajTracksMap->begin();i_trajTrack != m_TrajTracksMap->end();++i_trajTrack){
     trajTracks.push_back(ConstTrajTrackPair(&(*(*i_trajTrack).key), &(*(*i_trajTrack).val)));
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
     
     const std::vector<TrajectoryMeasurement> v_meas = (*traj).measurements();
     
     //Loop over Hits
     for(std::vector<TrajectoryMeasurement>::const_iterator i_meas = v_meas.begin(); i_meas != v_meas.end(); ++i_meas){
       TrackStruct::HitParameterStruct hitParams = this->fillHitVariables(*i_meas, iSetup);
       if(this->hitSelected(hitParams))trackStruct.v_hitParams.push_back(hitParams);
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
