{

gROOT->SetStyle("Plain");
gROOT->ForceStyle();
gStyle->SetOptStat(0);

gStyle->SetPalette(1);      //Spektralpalette, Default: 0 resp. 50
//gStyle->SetNumberContours(20);  // Default: 20

double width = 600.;

gStyle->SetCanvasDefW(width);
gStyle->SetCanvasDefH(width);

gStyle->SetPadLeftMargin(0.12);
gStyle->SetPadRightMargin(0.12);

gStyle->SetPadTopMargin(0.10);
gStyle->SetPadBottomMargin(0.12);

gStyle->SetTitleOffset(1.2,"Y");
gStyle->SetTitleOffset(1.15,"X");


TGaxis::SetMaxDigits(3);


//TH1::StatOverflows(kTRUE);// compute mean etc including overflow!
//gStyle->SetHistMinimumZero(kTRUE); // no zero-suppression on y-axis
//gStyle->SetOptFit(222);              // 1: Fit-PArameter werden angezeigt
//gStyle->SetCanvasDefX(400);     // canvas (default) upper edge in X
//gStyle->SetCanvasDefY(200);     // canvas (default) upper edge in Y

//gStyle->SetHistLineWidth(2);


gStyle->SetTitleX(0.25);        // move upper left corner of title box to specified value
//gStyle->SetTitleY(0.99);        // move upper left corner of title box to specified value



//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++



gStyle->SetTitleXSize(0.05);
gStyle->SetTitleYSize(0.05);
gStyle->SetTitleSize(0.05,"XY");
gStyle->SetLabelSize(0.05,"XY");



//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++





gROOT->ProcessLine(".L DrawPlot.C+");




DrawPlot drawPlot1(0, true);

drawPlot1.setLegendEntry("data (final APE)","data (APE=0)","MCideal");
gStyle->SetOptStat(111110);
drawPlot1.setLegendCoordinate(0.69, 0.20, 0.99, 0.35);
drawPlot1.drawPlot("ApeEstimatorSummary","h_residualWidthX1", false);
drawPlot1.drawPlot("ApeEstimatorSummary","h_residualWidthY1", false);
drawPlot1.drawPlot("ApeEstimatorSummary","h_rmsX", false);
drawPlot1.drawPlot("ApeEstimatorSummary","h_rmsY", false);



DrawPlot drawPlot2(0, false);

drawPlot2.setLegendEntry("data (final APE)","data (APE=0)","MCideal");
drawPlot2.setLegendCoordinate(0.69, 0.20, 0.99, 0.35);
gStyle->SetOptStat(111100);
drawPlot2.drawPlot("ApeEstimator1","h_entriesX", false);
drawPlot2.drawPlot("ApeEstimator1","h_entriesY", false);
gStyle->SetOptStat(111110);
drawPlot2.drawPlot("ApeEstimator1","h_NorResX", false);
drawPlot2.drawPlot("ApeEstimator1","h_NorResY", false);

gStyle->SetOptStat(111110);
drawPlot2.drawTrackPlot("ApeEstimator2","h_eta", false);
drawPlot2.drawTrackPlot("ApeEstimator2","h_theta", false);
drawPlot2.drawTrackPlot("ApeEstimator2","h_phi", false);
drawPlot2.drawTrackPlot("ApeEstimator2","h_norChi2", false);
drawPlot2.drawTrackPlot("ApeEstimator2","h_p", false);
drawPlot2.drawTrackPlot("ApeEstimator2","h_pt", false);
drawPlot2.drawTrackPlot("ApeEstimator2","h_charge", false);
drawPlot2.drawTrackPlot("ApeEstimator2","h_d0Beamspot", false);
drawPlot2.drawTrackPlot("ApeEstimator2","h_d0BeamspotErr", false);
drawPlot2.drawTrackPlot("ApeEstimator2","h_d0BeamspotSig", false);

drawPlot2.drawEventPlot("ApeEstimator2","h_trackSizeGood", false);






DrawPlot drawPlot3(15, true);

drawPlot3.setLegendEntry("data (final APE)","data (APE=0)","MCideal");
drawPlot3.setLegendCoordinate(0.41, 0.27, 0.71, 0.42);
gStyle->SetOptStat(111110);
// drawPlot3.drawPlot("ApeEstimatorSummary","h_correctionX1", false);
// drawPlot3.drawPlot("ApeEstimatorSummary","h_correctionX2", false);
// drawPlot3.drawPlot("ApeEstimatorSummary","h_correctionY1", false);
// drawPlot3.drawPlot("ApeEstimatorSummary","h_correctionY2", false);
// drawPlot3.drawPlot("ApeEstimatorSummary","h_fitMeanX1", false);
// drawPlot3.drawPlot("ApeEstimatorSummary","h_fitMeanX2", false);
// drawPlot3.drawPlot("ApeEstimatorSummary","h_fitMeanY1", false);
// drawPlot3.drawPlot("ApeEstimatorSummary","h_fitMeanY2", false);
// drawPlot3.drawPlot("ApeEstimatorSummary","meanX", false);
// drawPlot3.drawPlot("ApeEstimatorSummary","meanY", false);
drawPlot3.setLegendCoordinate(0.69, 0.20, 0.99, 0.35);
drawPlot3.drawPlot("ApeEstimatorSummary","h_residualWidthX1", false);
drawPlot3.drawPlot("ApeEstimatorSummary","h_residualWidthY1", false);
//drawPlot3.drawPlot("ApeEstimatorSummary","h_residualWidthX2", false);
//drawPlot3.drawPlot("ApeEstimatorSummary","h_residualWidthY2", false);
drawPlot3.drawPlot("ApeEstimatorSummary","h_rmsX", false);
drawPlot3.drawPlot("ApeEstimatorSummary","h_rmsY", false);



DrawPlot drawPlot4(15, false);

drawPlot4.setLegendEntry("data (final APE)","data (APE=0)","MCideal");
drawPlot4.setLegendCoordinate(0.69, 0.20, 0.99, 0.35);
gStyle->SetOptStat(111100);
drawPlot4.drawPlot("ApeEstimator1","h_entriesX", false);
drawPlot4.drawPlot("ApeEstimator1","h_entriesY", false);
gStyle->SetOptStat(111110);
drawPlot4.drawPlot("ApeEstimator1","h_NorResX");
drawPlot4.drawPlot("ApeEstimator1","h_NorResY");

gStyle->SetOptStat(111110);
drawPlot4.drawTrackPlot("ApeEstimator2","h_eta");
drawPlot4.drawTrackPlot("ApeEstimator2","h_theta");
drawPlot4.drawTrackPlot("ApeEstimator2","h_phi");
drawPlot4.drawTrackPlot("ApeEstimator2","h_norChi2");
drawPlot4.drawTrackPlot("ApeEstimator2","h_p");
drawPlot4.drawTrackPlot("ApeEstimator2","h_pt");
drawPlot4.drawTrackPlot("ApeEstimator2","h_charge");
drawPlot4.drawTrackPlot("ApeEstimator2","h_d0Beamspot");
drawPlot4.drawTrackPlot("ApeEstimator2","h_d0BeamspotErr");
drawPlot4.drawTrackPlot("ApeEstimator2","h_d0BeamspotSig");

drawPlot4.drawEventPlot("ApeEstimator2","h_trackSizeGood");



gROOT->ProcessLine(".q");



}






