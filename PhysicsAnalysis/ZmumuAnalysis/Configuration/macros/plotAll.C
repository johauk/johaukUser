{



gROOT->ProcessLine(".L MuonPlots.C++");

MuonPlots("Step2b");
MuonPlots("Step2");
MuonPlots("Step3");
MuonPlots("Step5");
MuonPlots("Step6");


MuonPlots("StepZVetoLow3");
MuonPlots("StepZVetoLow5");
MuonPlots("StepZVetoLow6");


MuonPlots("StepZVetoHigh3");
MuonPlots("StepZVetoHigh5");
MuonPlots("StepZVetoHigh6");




gROOT->ProcessLine(".L DimuonPlots.C++");

DimuonPlots("Step3d");
DimuonPlots("Step3e");
DimuonPlots("Step3f");
DimuonPlots("Step3");
DimuonPlots("Step5");
DimuonPlots("Step6");


DimuonPlots("StepZVetoLow3f");
DimuonPlots("StepZVetoLow5");
DimuonPlots("StepZVetoLow6");


DimuonPlots("StepZVetoHigh3f");
DimuonPlots("StepZVetoHigh5");
DimuonPlots("StepZVetoHigh6");




gROOT->ProcessLine(".L JetPlots.C++");

JetPlots("Step4a");
JetPlots("Step4b");
JetPlots("Step4c");
JetPlots("Step4d");
JetPlots("Step4");
JetPlots("Step5");
JetPlots("Step6");


JetPlots("StepZVetoLow4d");
JetPlots("StepZVetoLow4");
JetPlots("StepZVetoLow5");
JetPlots("StepZVetoLow6");


JetPlots("StepZVetoHigh4d");
JetPlots("StepZVetoHigh4");
JetPlots("StepZVetoHigh5");
JetPlots("StepZVetoHigh6");




gROOT->ProcessLine(".L MetPlots.C++");

MetPlots("Step6a");


MetPlots("StepZVetoLow6a");


MetPlots("StepZVetoHigh6a");





gROOT->ProcessLine(".q");




}
