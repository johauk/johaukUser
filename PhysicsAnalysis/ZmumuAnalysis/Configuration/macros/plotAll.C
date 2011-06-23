{



gROOT->ProcessLine(".L MuonPlots.C++");

MuonPlots("Step2b");
MuonPlots("Step2");
MuonPlots("Step3");
MuonPlots("Step5");
MuonPlots("Step6");


MuonPlots("StepZVeto3");
MuonPlots("StepZVeto5");
MuonPlots("StepZVeto6");




gROOT->ProcessLine(".L DimuonPlots.C++");

DimuonPlots("Step3d");
DimuonPlots("Step3e");
DimuonPlots("Step3f");
DimuonPlots("Step3");
DimuonPlots("Step5");
DimuonPlots("Step6");


DimuonPlots("StepZVeto3f");
DimuonPlots("StepZVeto5");
DimuonPlots("StepZVeto6");






gROOT->ProcessLine(".L JetPlots.C++");

JetPlots("Step4a");
JetPlots("Step4b");
JetPlots("Step4c");
JetPlots("Step4d");
JetPlots("Step4");
JetPlots("Step5");
JetPlots("Step6");


JetPlots("StepZVeto4d");
JetPlots("StepZVeto4");
JetPlots("StepZVeto5");
JetPlots("StepZVeto6");






gROOT->ProcessLine(".L MetPlots.C++");

MetPlots("Step6a");


MetPlots("StepZVeto6a");





gROOT->ProcessLine(".q");




}
