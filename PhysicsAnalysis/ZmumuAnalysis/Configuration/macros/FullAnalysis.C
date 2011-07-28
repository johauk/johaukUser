{
gROOT->ProcessLine(".L Tools/printLine.C++");
gROOT->ProcessLine(".L Tools/eventCount.C++");
gROOT->ProcessLine(".L Tools/signalAndSidebandCombined.C++");

gROOT->ProcessLine(".L Tools/ValueAndError.C++");
gROOT->ProcessLine(".L Samples/DefaultSample.C++");
gROOT->ProcessLine(".L Samples/Sample.C++");
gROOT->ProcessLine(".L Tools/FullAnalysis.C++");


FullAnalysis fullAnalysis;

fullAnalysis.setRecoSelectionStep("Step5");
fullAnalysis.setSimuSelectionStep("StepB2");

fullAnalysis.defaultAnalysis();

fullAnalysis.ttbarFromSideband(FullAnalysis::upper);


}


