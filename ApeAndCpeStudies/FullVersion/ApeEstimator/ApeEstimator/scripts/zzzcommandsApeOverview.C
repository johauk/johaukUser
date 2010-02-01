{



gROOT->SetStyle("Plain");
gROOT->ForceStyle();
gStyle->SetOptStat(111110);

gStyle->SetPalette(1);      //Spektralpalette, Default: 0 resp. 50
//gStyle->SetNumberContours(20);  // Default: 20

//double width = 600.;
//gStyle->SetCanvasDefW(width);
//gStyle->SetCanvasDefH(width);

gStyle->SetPadLeftMargin(0.15);
gStyle->SetPadRightMargin(0.11);

gStyle->SetPadTopMargin(0.125);
gStyle->SetPadBottomMargin(0.135);

gStyle->SetTitleOffset(1.3,"Y");
gStyle->SetTitleOffset(1.15,"X");


TGaxis::SetMaxDigits(3);


//TH1::StatOverflows(kTRUE);// compute mean etc including overflow!
//gStyle->SetHistMinimumZero(kTRUE); // no zero-suppression on y-axis
//gStyle->SetOptFit(222);              // 1: Fit-PArameter werden angezeigt
//gStyle->SetCanvasDefX(400);     // canvas (default) upper edge in X
//gStyle->SetCanvasDefY(200);     // canvas (default) upper edge in Y

//gStyle->SetHistLineWidth(2);


gStyle->SetTitleX(0.26);



//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++



gStyle->SetTitleXSize(0.05);
gStyle->SetTitleYSize(0.05);
gStyle->SetTitleSize(0.05,"XY");
gStyle->SetLabelSize(0.05,"XY");



//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++



gROOT->ProcessLine(".L ApeOverview.C+");
gROOT->ProcessLine("ApeOverview a1(\"../mcZoom.root\");");

gROOT->ProcessLine("a1.onlyZoomedHists()");

gROOT->ProcessLine("a1.setSectorsForOverview(\"1,2,3,4,5,6,7,8\")");
gROOT->ProcessLine("a1.setSectorsForOverview(\"1,3,5,7\")");

gROOT->ProcessLine("a1.getOverview();");
//gROOT->ProcessLine("a1.printOverview();");
gROOT->ProcessLine("a1.printOverview(\"../plots/mcZoom.ps\");");
//gROOT->ProcessLine("a1.printOverview(\"../plots/mcHitSelZoom.ps\",ApeOverview::sector);");
//gROOT->ProcessLine("a1.printOverview(\"apeOverview.ps\",ApeOverview::event);");



gROOT->ProcessLine(".q");



}
