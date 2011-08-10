{
gROOT->ProcessLine(".L Tools/printLine.C+");
gROOT->ProcessLine(".L Tools/eventCount.C+");
gROOT->ProcessLine(".L Tools/signalAndSidebandCombined.C+");

gROOT->ProcessLine(".L Tools/ValueAndError.C+");
gROOT->ProcessLine(".L Samples/DefaultSample.C+");
gROOT->ProcessLine(".L Samples/Sample.C+");
gROOT->ProcessLine(".L Tools/FullAnalysis.C++");


FullAnalysis fullAnalysis1;

fullAnalysis1.setRecoSelectionStep("Step5");
fullAnalysis1.setSimuSelectionStep("StepB2");

fullAnalysis1.defaultAnalysis();
fullAnalysis1.ttbarFromSideband(FullAnalysis::upper);





fullAnalysis1.setRecoSelectionStep("StepNoMet7a");
fullAnalysis1.defaultAnalysis();
fullAnalysis1.ttbarFromSideband(FullAnalysis::upper);

fullAnalysis1.setRecoSelectionStep("Step6");
fullAnalysis1.defaultAnalysis();
fullAnalysis1.ttbarFromSideband(FullAnalysis::upper);

fullAnalysis1.setRecoSelectionStep("Step7a");
fullAnalysis1.defaultAnalysis();
fullAnalysis1.ttbarFromSideband(FullAnalysis::upper);

fullAnalysis1.setRecoSelectionStep("StepNoMetOneBSsvHeMJet7a");
fullAnalysis1.defaultAnalysis();
fullAnalysis1.ttbarFromSideband(FullAnalysis::upper);

fullAnalysis1.setRecoSelectionStep("StepNoMetOneBSsvHpTJet7a");
fullAnalysis1.defaultAnalysis();
fullAnalysis1.ttbarFromSideband(FullAnalysis::upper);

fullAnalysis1.setRecoSelectionStep("StepOneBSsvHeMJet7a");
fullAnalysis1.defaultAnalysis();
fullAnalysis1.ttbarFromSideband(FullAnalysis::upper);

fullAnalysis1.setRecoSelectionStep("StepOneBSsvHpTJet7a");
fullAnalysis1.defaultAnalysis();
fullAnalysis1.ttbarFromSideband(FullAnalysis::upper);




}









