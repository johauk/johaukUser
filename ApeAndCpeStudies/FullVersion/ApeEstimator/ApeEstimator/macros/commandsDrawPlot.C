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
drawPlot1.setLegendEntry("data","MCideal");
drawPlot1.setLegendCoordinate(0.41, 0.27, 0.71, 0.42);
gStyle->SetOptStat(111110);
drawPlot1.drawPlot("ApeEstimatorSummary","h_correctionX1");
drawPlot1.drawPlot("ApeEstimatorSummary","h_correctionX2");
drawPlot1.drawPlot("ApeEstimatorSummary","h_correctionY1");
drawPlot1.drawPlot("ApeEstimatorSummary","h_correctionY2");
drawPlot1.drawPlot("ApeEstimatorSummary","h_fitMeanX1");
drawPlot1.drawPlot("ApeEstimatorSummary","h_fitMeanX2");
drawPlot1.drawPlot("ApeEstimatorSummary","h_fitMeanY1");
drawPlot1.drawPlot("ApeEstimatorSummary","h_fitMeanY2");
drawPlot1.drawPlot("ApeEstimatorSummary","meanX");
drawPlot1.drawPlot("ApeEstimatorSummary","meanY");
drawPlot1.setLegendCoordinate(0.69, 0.22, 0.99, 0.37);
drawPlot1.drawPlot("ApeEstimatorSummary","h_residualWidthX1");
drawPlot1.drawPlot("ApeEstimatorSummary","h_residualWidthX2");
drawPlot1.drawPlot("ApeEstimatorSummary","h_residualWidthY1");
drawPlot1.drawPlot("ApeEstimatorSummary","h_residualWidthY2");
drawPlot1.drawPlot("ApeEstimatorSummary","h_rmsX");
drawPlot1.drawPlot("ApeEstimatorSummary","h_rmsY");




DrawPlot drawPlot2(0, false);
drawPlot2.setLegendEntry("data","MCideal");
//drawPlot2.setLegendCoordinate(0.41, 0.27, 0.71, 0.42);
drawPlot2.setLegendCoordinate(0.69, 0.22, 0.99, 0.37);
gStyle->SetOptStat(111100);
drawPlot2.drawPlot("ApeEstimator1","h_entriesX");
drawPlot2.drawPlot("ApeEstimator1","h_entriesY");
gStyle->SetOptStat(111110);
drawPlot2.drawPlot("ApeEstimator2","h_NorResX");
drawPlot2.drawPlot("ApeEstimator2","h_NorResY");





//gROOT->ProcessLine(".q");


}
