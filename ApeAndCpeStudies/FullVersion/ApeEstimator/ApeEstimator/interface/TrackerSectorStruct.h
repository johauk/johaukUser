#ifndef ApeEstimator_ApeEstimator_TrackerSectorStruct_h
#define ApeEstimator_ApeEstimator_TrackerSectorStruct_h


//#include "vector"
#include "TH1.h"
#include "TH2.h"
//#include "TProfile.h"

struct TrackerSectorStruct{
  
  TrackerSectorStruct(): IsModuleUsable(0),
                         Width(0), MaxStrip(0), Charge(0), MaxCharge(0), MaxIndex(0), ChargeLR(0),
			 BaryStrip(0), SOverN(0),
			 ResX(0), NorResX(0), XHit(0), XTrk(0),
			 SigmaXHit(0), SigmaXTrk(0), SigmaX(0), SigmaX2(0),
			 PhiSens(0), PhiSensX(0), PhiSensY(0),
			 NorResXVsWidth(0), NorResXVsMaxStrip(0), NorResXVsCharge(0), NorResXVsMaxCharge(0), NorResXVsMaxIndex(0), NorResXVsChargeLR(0),
                         NorResXVsBaryStrip(0), NorResXVsSOverN(0),
			 NorResXVsP(0), NorResXVsMeanAngle(0), NorResXVsHitsValid(0), NorResXVsHitsGood(0),
			 NorResXVsHitsInvalid(0), NorResXVsLayersMissed(0), NorResXVsNorChi2(0),
			 NorResXVsPhiSens(0), NorResXVsPhiSensX(0), NorResXVsPhiSensY(0),
			 SigmaXHitVsWidth(0), SigmaXHitVsMaxStrip(0), SigmaXHitVsCharge(0), SigmaXHitVsMaxCharge(0), SigmaXHitVsMaxIndex(0), SigmaXHitVsChargeLR(0),
                         SigmaXHitVsBaryStrip(0), SigmaXHitVsSOverN(0),
			 SigmaXTrkVsP(0), SigmaXTrkVsInvP(0), SigmaXTrkVsMeanAngle(0), SigmaXTrkVsHitsValid(0),
			 SigmaXTrkVsHitsGood(0), SigmaXTrkVsHitsInvalid(0), SigmaXTrkVsLayersMissed(0), SigmaXVsNorChi2(0),
			 SigmaXHitVsPhiSens(0), SigmaXHitVsPhiSensX(0), SigmaXHitVsPhiSensY(0),
			 SigmaXTrkVsPhiSens(0), SigmaXTrkVsPhiSensX(0), SigmaXTrkVsPhiSensY(0),
			 SigmaXVsPhiSens(0), SigmaXVsPhiSensX(0), SigmaXVsPhiSensY(0),
			 NorResXVsSigmaXHit(0), NorResXVsSigmaXTrk(0), NorResXVsSigmaX(0),
			 WidthVsPhiSensX(0),
			 PNorResXVsWidth(0), PNorResXVsMaxStrip(0), PNorResXVsCharge(0), PNorResXVsMaxCharge(0), PNorResXVsMaxIndex(0), PNorResXVsChargeLR(0),
                         PNorResXVsBaryStrip(0), PNorResXVsSOverN(0),
			 PNorResXVsP(0), PNorResXVsMeanAngle(0), PNorResXVsHitsValid(0), PNorResXVsHitsGood(0),
			 PNorResXVsHitsInvalid(0), PNorResXVsLayersMissed(0), PNorResXVsNorChi2(0),
			 PNorResXVsPhiSens(0), PNorResXVsPhiSensX(0), PNorResXVsPhiSensY(0),
			 PSigmaXHitVsWidth(0), PSigmaXHitVsMaxStrip(0), PSigmaXHitVsCharge(0), PSigmaXHitVsMaxCharge(0), PSigmaXHitVsMaxIndex(0), PSigmaXHitVsChargeLR(0),
                         PSigmaXHitVsBaryStrip(0), PSigmaXHitVsSOverN(0),
			 PSigmaXTrkVsP(0), PSigmaXTrkVsInvP(0), PSigmaXTrkVsMeanAngle(0), PSigmaXTrkVsHitsValid(0),
			 PSigmaXTrkVsHitsGood(0), PSigmaXTrkVsHitsInvalid(0), PSigmaXTrkVsLayersMissed(0), PSigmaXVsNorChi2(0),
			 PSigmaXHitVsPhiSens(0), PSigmaXHitVsPhiSensX(0), PSigmaXHitVsPhiSensY(0),
			 PSigmaXTrkVsPhiSens(0), PSigmaXTrkVsPhiSensX(0), PSigmaXTrkVsPhiSensY(0),
			 PSigmaXVsPhiSens(0), PSigmaXVsPhiSensX(0), PSigmaXVsPhiSensY(0),
			 PNorResXVsSigmaXHit(0), PNorResXVsSigmaXTrk(0), PNorResXVsSigmaX(0),
			 PWidthVsPhiSensX(0){}
  
  
  std::vector<unsigned int> vRawId;
  
  TH1 *IsModuleUsable,
      *Width, *MaxStrip, *Charge, *MaxCharge, *MaxIndex, *ChargeLR,
      *BaryStrip, *SOverN,
      *ResX, *NorResX, *XHit, *XTrk,
      *SigmaXHit, *SigmaXTrk, *SigmaX, *SigmaX2,
      *PhiSens, *PhiSensX, *PhiSensY;
  TH2 *NorResXVsWidth, *NorResXVsMaxStrip, *NorResXVsCharge, *NorResXVsMaxCharge, *NorResXVsMaxIndex, *NorResXVsChargeLR,
      *NorResXVsBaryStrip, *NorResXVsSOverN,
      *NorResXVsP, *NorResXVsMeanAngle, *NorResXVsHitsValid, *NorResXVsHitsGood,
      *NorResXVsHitsInvalid, *NorResXVsLayersMissed, *NorResXVsNorChi2,
      *NorResXVsPhiSens, *NorResXVsPhiSensX, *NorResXVsPhiSensY,
      *SigmaXHitVsWidth, *SigmaXHitVsMaxStrip, *SigmaXHitVsCharge, *SigmaXHitVsMaxCharge, *SigmaXHitVsMaxIndex, *SigmaXHitVsChargeLR,
      *SigmaXHitVsBaryStrip, *SigmaXHitVsSOverN,
      *SigmaXTrkVsP, *SigmaXTrkVsInvP, *SigmaXTrkVsMeanAngle, *SigmaXTrkVsHitsValid,
      *SigmaXTrkVsHitsGood, *SigmaXTrkVsHitsInvalid, *SigmaXTrkVsLayersMissed, *SigmaXVsNorChi2,
      *SigmaXHitVsPhiSens, *SigmaXHitVsPhiSensX, *SigmaXHitVsPhiSensY,
      *SigmaXTrkVsPhiSens, *SigmaXTrkVsPhiSensX, *SigmaXTrkVsPhiSensY,
      *SigmaXVsPhiSens, *SigmaXVsPhiSensX, *SigmaXVsPhiSensY,
      *NorResXVsSigmaXHit, *NorResXVsSigmaXTrk, *NorResXVsSigmaX,
      *WidthVsPhiSensX;
  TProfile *PNorResXVsWidth, *PNorResXVsMaxStrip, *PNorResXVsCharge, *PNorResXVsMaxCharge, *PNorResXVsMaxIndex, *PNorResXVsChargeLR,
           *PNorResXVsBaryStrip, *PNorResXVsSOverN,
           *PNorResXVsP, *PNorResXVsMeanAngle, *PNorResXVsHitsValid, *PNorResXVsHitsGood,
           *PNorResXVsHitsInvalid, *PNorResXVsLayersMissed, *PNorResXVsNorChi2,
	   *PNorResXVsPhiSens, *PNorResXVsPhiSensX, *PNorResXVsPhiSensY,
	   *PSigmaXHitVsWidth, *PSigmaXHitVsMaxStrip, *PSigmaXHitVsCharge, *PSigmaXHitVsMaxCharge, *PSigmaXHitVsMaxIndex, *PSigmaXHitVsChargeLR,
           *PSigmaXHitVsBaryStrip, *PSigmaXHitVsSOverN,
	   *PSigmaXTrkVsP, *PSigmaXTrkVsInvP, *PSigmaXTrkVsMeanAngle, *PSigmaXTrkVsHitsValid,
           *PSigmaXTrkVsHitsGood, *PSigmaXTrkVsHitsInvalid, *PSigmaXTrkVsLayersMissed, *PSigmaXVsNorChi2,
	   *PSigmaXHitVsPhiSens, *PSigmaXHitVsPhiSensX, *PSigmaXHitVsPhiSensY,
           *PSigmaXTrkVsPhiSens, *PSigmaXTrkVsPhiSensX, *PSigmaXTrkVsPhiSensY,
	   *PSigmaXVsPhiSens, *PSigmaXVsPhiSensX, *PSigmaXVsPhiSensY,
	   *PNorResXVsSigmaXHit, *PNorResXVsSigmaXTrk, *PNorResXVsSigmaX,
	   *PWidthVsPhiSensX;
  
  std::map<std::string,std::vector<TH1*> > mSigmaX;
  
  
  //for every bin in sigmaX the needful histos to calculate the APE
  std::map<unsigned int, std::map<std::string,TH1*> > mBinnedHists;
  
  
  //for presenting results
  TH1 *Entries, *MeanX, *RmsX, *FitMeanX, *ResidualWidthX, *ApeX;
  
};

#endif
