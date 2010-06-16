#ifndef ApeEstimator_ApeEstimator_TrackerDetectorStruct_h
#define ApeEstimator_ApeEstimator_TrackerDetectorStruct_h


//#include "TH1.h"

struct TrackerDetectorStruct{
  
  TrackerDetectorStruct(): TrkSize(0),
                           HitsSize(0), HitsValid(0), HitsInvalid(0), Hits2D(0),
			   HitsGood(0), LayersMissed(0),
			   Charge(0), Chi2(0), Ndof(0), NorChi2(0),
			   Eta(0), Theta(0), Phi(0), D0Beamspot(0), Dz(0),
			   P(0), Pt(0), MeanAngle(0),
			   HitsGoodVsHitsValid(0), MeanAngleVsHits(0),
			   PHitsGoodVsHitsValid(0), PMeanAngleVsHits(0){}
  
  TH1 *TrkSize,
      *HitsSize, *HitsValid, *HitsInvalid, *Hits2D,
      *HitsGood, *LayersMissed,
      *Charge, *Chi2, *Ndof, *NorChi2,
      *Eta, *Theta, *Phi, *D0Beamspot, *Dz,
      *P, *Pt, *MeanAngle;
  
  TH2 *HitsGoodVsHitsValid, *MeanAngleVsHits;
  
  TProfile *PHitsGoodVsHitsValid, *PMeanAngleVsHits;
  
};

#endif
