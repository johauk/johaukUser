{

gROOT->ProcessLine(".L DrawIteration.C+");

DrawIteration a1(14);

//a1.drawIteration();
a1.drawIteration(1,6);
a1.drawIteration(7,10);
a1.drawIteration(11,22);
a1.drawIteration(23,34);
a1.drawIteration(35,44);
a1.drawIteration(45,64);

gROOT->ProcessLine(".L tdrstyle.C");
setTDRStyle();
gStyle->SetErrorX(0.5);

a1.drawResult();


gROOT->ProcessLine(".q");


}
