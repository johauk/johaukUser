{


gROOT->SetStyle("Plain");
gROOT->ForceStyle();
gStyle->SetOptStat(0);

gStyle->SetPalette(1);      //Spektralpalette, Default: 0 resp. 50
//gStyle->SetNumberContours(20);  // Default: 20


/*
double width = 600.;

gStyle->SetCanvasDefW(width);
gStyle->SetCanvasDefH(width);

gStyle->SetPadLeftMargin(0.12);
gStyle->SetPadRightMargin(0.08);

gStyle->SetPadTopMargin(0.08);
gStyle->SetPadBottomMargin(0.12);

gStyle->SetTitleOffset(1.6,"Y");
gStyle->SetTitleOffset(1.2,"X");


TGaxis::SetMaxDigits(3);


//TH1::StatOverflows(kTRUE);// compute mean etc including overflow!
//gStyle->SetHistMinimumZero(kTRUE); // no zero-suppression on y-axis
//gStyle->SetOptFit(222);              // 1: Fit-PArameter werden angezeigt
//gStyle->SetCanvasDefX(400);     // canvas (default) upper edge in X
//gStyle->SetCanvasDefY(200);     // canvas (default) upper edge in Y

//gStyle->SetHistLineWidth(2);



gStyle->SetTitleX(0.2);         // move upper left corner of title box to specified value
//gStyle->SetTitleY(0.99);        // move upper left corner of title box to specified value



gStyle->SetTitleXSize(0.05);
gStyle->SetTitleYSize(0.05);
gStyle->SetTitleSize(0.05,"XY");
gStyle->SetLabelSize(0.05,"XY");

*/

//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


gROOT->ProcessLine(".L tdrstyle.C");
setTDRStyle();

//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++







gROOT->ProcessLine(".L Tools/printLine.C+");
gROOT->ProcessLine(".L Tools/eventCount.C+");
gROOT->ProcessLine(".L Tools/signalAndSidebandCombined.C+");
gROOT->ProcessLine(".L Tools/histTools.C+");

gROOT->ProcessLine(".L Tools/ValueAndError.C+");
gROOT->ProcessLine(".L Samples/DefaultSample.C+");
gROOT->ProcessLine(".L Samples/Sample.C+");
gROOT->ProcessLine(".L Tools/FullAnalysis.C++");


FullAnalysis fullAnalysis1;

fullAnalysis1.setRecoSelectionStep("Step6");
fullAnalysis1.setSimuSelectionStep("StepB2");

fullAnalysis1.defaultAnalysis();
fullAnalysis1.ttbarFromSideband(FullAnalysis::upper);






//fullAnalysis1.setRecoSelectionStep("Step5");
//fullAnalysis1.defaultAnalysis();
//fullAnalysis1.ttbarFromSideband(FullAnalysis::upper);

// fullAnalysis1.setRecoSelectionStep("Step7a");
// fullAnalysis1.defaultAnalysis();
// fullAnalysis1.ttbarFromSideband(FullAnalysis::upper);
// 
// fullAnalysis1.setRecoSelectionStep("Step7");
// fullAnalysis1.defaultAnalysis();
// fullAnalysis1.ttbarFromSideband(FullAnalysis::upper);




}









