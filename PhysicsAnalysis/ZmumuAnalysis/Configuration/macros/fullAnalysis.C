fullAnalysis(TString recoStep = "Step5", TString simuStep = "StepB2", TString sideband1Step = "StepZVetoHigh5", TString sideband2Step = ""){
//fullAnalysis(){

/*
// Only things to modify:
const TString recoStep("Step6"); // Which selection step of reconstruction cut flow
const TString simuStep("StepB2"); // Which selection step of simulation cut flow (generator level)
const TString sideband1Step("StepZVetoHigh6"); // Which sideband to use
//const TString sideband2Step("StepZVetoLow6"); // Optionally, second sideband to use
const TString sideband2Step("");
*/



gROOT->ProcessLine(".L Tools/printLine.C++");

gROOT->ProcessLine(".L Calculations/efficiency.C++");
gROOT->ProcessLine(".L Calculations/luminosity.C++");
gROOT->ProcessLine(".L Calculations/nObserved.C++");
gROOT->ProcessLine(".L Calculations/nBackground.C++");
gROOT->ProcessLine(".L Calculations/nSignal.C++");
gROOT->ProcessLine(".L Calculations/crossSection.C++");
gROOT->ProcessLine(".L Calculations/signalSampleCrossSection.C++");
gROOT->ProcessLine(".L Calculations/ratioInOut.C++");
gROOT->ProcessLine(".L Calculations/nObservedSideband.C++");
gROOT->ProcessLine(".L Calculations/nBackgroundSideband.C++");
gROOT->ProcessLine(".L Calculations/nSignalSidebandMc.C++");
gROOT->ProcessLine(".L Calculations/crossSectionIterative.C++");
//gROOT->ProcessLine(".L Calculations/nInOutIterative.C++");
gROOT->ProcessLine(".L Calculations/nInOut.C++");

gROOT->ProcessLine(".L Drawings/zTtbarFit.C++");

gROOT->ProcessLine(".L Samples/allSampleStruct.C++");


printLine("Data sample");
gROOT->ProcessLine(".L Samples/data.C++");
data(allSampleStruct);
printLine("MC samples");
gROOT->ProcessLine(".L Samples/mc.C++");
mc(allSampleStruct);
printLine("Simulated signal sample");
gROOT->ProcessLine(".L Samples/simulation.C++");
simulation(allSampleStruct);



printLine("Efficiency from MC");
efficiency(recoStep, simuStep);
//efficiencyDummy(recoStep, simuStep);
printLine("Luminosity");
luminosity();
printLine("No. of observed events");
nObserved(recoStep);
printLine("No. of background events");
nBackground(recoStep);
printLine("No. of signal events");
nSignal(theNObserved, theNBackground);
printLine("Cross section");
crossSection(theNSignal, theEfficiency, theLuminosity);

// For ttbar background estimation
printLine("Cross section from MC");
signalSampleCrossSection();
printLine("Ratio In/Out");
ratioInOut(recoStep, sideband1Step, sideband2Step);
printLine("No. of observed events (sidebands)");
nObservedSideband(sideband1Step, sideband2Step);
printLine("No. of background events (sidebands)");
nBackgroundSideband(sideband1Step, sideband2Step);
printLine("No. of signal events (sidebands)");
nSignalSidebandMc(sideband1Step, sideband2Step);

printLine("ttbar and zmumu yields direct");
nInOut(theNObserved, theNObservedSideband, theNObservedRelErr2Up, theNObservedSidebandRelErr2Up, theRatioInOutTtbar, theRatioInOutZmumu, theRatioInOutRelErr2UpTtbar, theRatioInOutRelErr2UpZmumu, theNInMcOther, theNOutMcOther, 0., 0.);

printLine("Plot fitted dimuon distribution");
zTtbarFit(recoStep, theNInTtbarRel, theNInZmumuRel, theNObserved, theNInMcTtbar, theNInMcZmumu);

}
