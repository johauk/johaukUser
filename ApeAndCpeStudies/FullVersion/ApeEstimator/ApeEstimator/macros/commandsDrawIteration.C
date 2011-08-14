{


gROOT->ProcessLine(".L DrawIteration.C+");

DrawIteration a1(2);
//a1.drawIteration();
a1.drawIteration(1,6);
a1.drawIteration(7,10);
a1.drawIteration(11,22);
a1.drawIteration(26,34);
a1.drawIteration(35,44);
a1.drawIteration(45,64);



//gROOT->ProcessLine(".q");


}
