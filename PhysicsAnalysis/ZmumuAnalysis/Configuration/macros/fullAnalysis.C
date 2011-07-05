{


// Only things to modify:
const TString recoStep("Step6"); // Which selection step of reconstruction cut flow
const TString simuStep("StepB2"); // Which selection step of simulation cut flow (generator level)
const TString sideband1Step("StepZVetoHigh6"); // Which sideband to use
//const TString sideband2Step("StepZVetoLow6"); // Optionally, second sideband to use
const TString sideband2Step("");




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


gROOT->ProcessLine(".L Samples/data.C++");
gROOT->ProcessLine(".L Samples/mc.C++");
gROOT->ProcessLine(".L Samples/simulation.C++");

gROOT->ProcessLine(".L Samples/allSampleStruct.C++");



data();
mc();
simulation();



efficiency(recoStep, simuStep);
luminosity();
nObserved(recoStep);
nBackground(recoStep);
nSignal(theNObserved, theNBackground);
crossSection(theNSignal, theEfficiency, theLuminosity);

// For ttbar background estimation
signalSampleCrossSection();
ratioInOut(recoStep, sideband1Step, sideband2Step);
nObservedSideband(sideband1Step, sideband2Step);
nBackgroundSideband(sideband1Step, sideband2Step);
nSignalSidebandMc(sideband1Step, sideband2Step);
crossSectionIterative(theNObserved, theNObservedSideband, theNBackgroundWoTop, theNBackgroundWoTopSideband, theRatioInOut, theNSignalSidebandMc, theEfficiency, theLuminosity, theCrossSection, theSignalSampleCrossSection);
//crossSectionIterative(theNObserved, theNObservedSideband, theNBackgroundWoTop, theNBackgroundWoTopSideband, theRatioInOut, theNSignalSidebandMc, theEfficiency, theLuminosity, theSignalSampleCrossSection, theSignalSampleCrossSection);
//crossSectionIterative(theNObserved, theNObservedSideband, theNBackgroundWoTop, theNBackgroundWoTopSideband, theRatioInOut, theNSignalSidebandMc, theEfficiency, theLuminosity, 0., theSignalSampleCrossSection);


}
