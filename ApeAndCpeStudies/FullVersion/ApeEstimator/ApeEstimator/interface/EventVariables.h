#ifndef ApeEstimator_ApeEstimator_EventVariables_h
#define ApeEstimator_ApeEstimator_EventVariables_h


struct TrackStruct{
  
  TrackStruct(){}
  
  enum HitState{notInTracker, notAssignedToSectors, invalid, negativeError, ok};
  
  struct HitParameterStruct{
    
    HitParameterStruct(): hitState(ok),
                 isModuleUsable(true),
		 width(0), charge(0), chargeLR(0), maxStrip(0), maxStripInv(0), maxCharge(0), maxIndex(0),
		 baryStrip(-999.), sOverN(-999.),
		 resX(-999.), norResX(-999.), xHit(-999.), xTrk(-999.),
                 errXHit(-999.), errXTrk(-999.), errX(-999.), errX2(-999.),
                 phiSens(-999.), phiSensX(-999.), phiSensY(-999.){}
    
    HitState hitState;
    std::vector<unsigned int> sectors;
    // cluster parameters
    bool isModuleUsable;
    unsigned int width, charge, chargeLR, maxStrip, maxStripInv, maxCharge, maxIndex;
    float baryStrip, sOverN;
    // trackFit results
    float resX, norResX, xHit, xTrk,
          errXHit, errXTrk, errX, errX2,
          phiSens, phiSensX, phiSensY;
  };
  
  struct TrackParameterStruct{
    
    TrackParameterStruct(): hitsSize(-999), hitsValid(-999), hitsInvalid(-999),
		   hits2D(-999), layersMissed(-999), charge(-999),
		   chi2(-999.), ndof(-999.), norChi2(-999.),
                   eta(-999.), theta(-999.), phi(-999.),
                   p(-999.), pt(-999.), meanPhiSensToNorm(-999.){}
    
    int hitsSize, hitsValid, hitsInvalid,
        hits2D, layersMissed, charge;
    float chi2, ndof, norChi2,
          eta, theta, phi,
	  p, pt, meanPhiSensToNorm;
  };
  
  TrackParameterStruct trkParams;
  std::vector<HitParameterStruct> vHitParams;
};

#endif
