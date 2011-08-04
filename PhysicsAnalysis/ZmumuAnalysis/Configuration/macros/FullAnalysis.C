{
gROOT->ProcessLine(".L Tools/printLine.C++");
gROOT->ProcessLine(".L Tools/eventCount.C++");
gROOT->ProcessLine(".L Tools/signalAndSidebandCombined.C++");

gROOT->ProcessLine(".L Tools/ValueAndError.C++");
gROOT->ProcessLine(".L Samples/DefaultSample.C++");
gROOT->ProcessLine(".L Samples/Sample.C++");
gROOT->ProcessLine(".L Tools/FullAnalysis.C++");


FullAnalysis fullAnalysis1;

fullAnalysis1.setRecoSelectionStep("Step5");
fullAnalysis1.setSimuSelectionStep("StepB2");

fullAnalysis1.defaultAnalysis();

fullAnalysis1.ttbarFromSideband(FullAnalysis::upper);


}


