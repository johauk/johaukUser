{


gROOT->ProcessLine(".L Calculations/efficiency.C++");
gROOT->ProcessLine(".L Calculations/luminosity.C++");
gROOT->ProcessLine(".L Calculations/nObserved.C++");
gROOT->ProcessLine(".L Calculations/nBackground.C++");
gROOT->ProcessLine(".L Calculations/nSignal.C++");
gROOT->ProcessLine(".L Calculations/crossSection.C++");


gROOT->ProcessLine(".L Samples/data.C++");
gROOT->ProcessLine(".L Samples/mc.C++");
gROOT->ProcessLine(".L Samples/simulation.C++");

gROOT->ProcessLine(".L Samples/allSampleStruct.C++");



data();
mc();
simulation();



efficiency("Step1a", "Step0");
luminosity();
nObserved("Step1a");
nBackground("Step1a");
nSignal(theNObserved, theNBackground);
crossSection(theNSignal, theEfficiency, theLuminosity);


}
