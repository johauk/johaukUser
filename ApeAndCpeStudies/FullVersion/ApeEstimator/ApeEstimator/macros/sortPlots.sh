#!/bin/bash



dirbase="$CMSSW_BASE/src/ApeEstimator/ApeEstimator/hists/workingArea"


for folder in ${dirbase}/*;
do
  plots="${folder}/plots"
  
  if [ -d "$plots" ]; then
    rm ${plots}/*.eps
    
    mkdir ${plots}/Result/
    mkdir ${plots}/Sector/
    mkdir ${plots}/Track/
    
    mv ${plots}/ape_*.* ${plots}/Result/.
    mv ${plots}/correction_*.* ${plots}/Result/.
    mv ${plots}/result_*.* ${plots}/Result/.
    
    mv ${plots}/h_NorRes*.* ${plots}/Sector/.
    mv ${plots}/h_entries*.* ${plots}/Sector/.
    mv ${plots}/h_residualWidth*.* ${plots}/Sector/.
    mv ${plots}/h_rms*.* ${plots}/Sector/.
    
    mv ${plots}/h_charge.* ${plots}/Track/.
    mv ${plots}/h_d0Beamspot.* ${plots}/Track/.
    mv ${plots}/h_d0BeamspotErr.* ${plots}/Track/.
    mv ${plots}/h_d0BeamspotSig.* ${plots}/Track/.
    mv ${plots}/h_eta.* ${plots}/Track/.
    mv ${plots}/h_norChi2.* ${plots}/Track/.
    mv ${plots}/h_p.* ${plots}/Track/.
    mv ${plots}/h_phi.* ${plots}/Track/.
    mv ${plots}/h_pt.* ${plots}/Track/.
    mv ${plots}/h_theta.* ${plots}/Track/.
    mv ${plots}/h_trackSizeGood.* ${plots}/Track/.
  fi

done


