#ifndef ApeEstimator_ApeEstimator_EventVariables_h
#define ApeEstimator_ApeEstimator_EventVariables_h


struct TrackStruct{
  
  TrackStruct(){}
  
  enum HitState{notInTracker, notAssignedToSectors, invalid, negativeError, ok};
  
  struct HitParameterStruct{
    
    HitParameterStruct(): hitState(ok),
                 isModuleUsable(true),
		 width(0), charge(0), maxStrip(0), maxStripInv(0), maxCharge(0), maxIndex(0),
		 chargeOnEdges(-999.F), chargeAsymmetry(-999.F), 
		 baryStrip(-999.F), sOverN(-999.F),
		 projWidth(-999.F),
		 resX(-999.F), norResX(-999.F), xHit(-999.F), xTrk(-999.F),
                 errXHit(-999.F), errXTrk(-999.F), errX(-999.F), errX2(-999.F),
		 errXHitWoApe(-999.F), errXWoApe(-999.F),
                 phiSens(-999.F), phiSensX(-999.F), phiSensY(-999.F),
		 probX(-999.F){}
    
    HitState hitState;
    std::vector<unsigned int> v_sector;
    // cluster parameters
    bool isModuleUsable;
    unsigned int width, charge, maxStrip, maxStripInv, maxCharge, maxIndex;
    float chargeOnEdges, chargeAsymmetry,
          chargeLRplus, chargeLRminus;
    float baryStrip, sOverN;
    float projWidth;
    // trackFit results
    float resX, norResX, xHit, xTrk,
          errXHit, errXTrk, errX, errX2,
	  errXHitWoApe, errXWoApe,
          phiSens, phiSensX, phiSensY,
	  probX;
  };
  
  struct TrackParameterStruct{
    
    TrackParameterStruct(): hitsSize(-999), hitsValid(-999), hitsInvalid(-999),
		   hits2D(-999), layersMissed(-999),
		   hitsPixel(-999), hitsStrip(-999),
		   charge(-999),
		   chi2(-999.F), ndof(-999.F), norChi2(-999.F),
                   eta(-999.F), theta(-999.F), phi(-999.F), d0(-999.F), dz(-999.F),
		   d0Beamspot(-999.F), dzBeamspot(-999.F),
                   p(-999.F), pt(-999.F), meanPhiSensToNorm(-999.F){}
    
    int hitsSize, hitsValid, hitsInvalid,
        hits2D, layersMissed,
	hitsPixel, hitsStrip,
	charge;
    float chi2, ndof, norChi2,
          eta, theta, phi, d0, dz,
	  d0Beamspot, dzBeamspot,
	  p, pt, meanPhiSensToNorm;
  };
  
  TrackParameterStruct trkParams;
  std::vector<HitParameterStruct> v_hitParams;
};

#endif
