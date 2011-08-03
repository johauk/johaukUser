{


gROOT->ProcessLine(".L DrawIteration.C+");

DrawIteration a1(7);
//a1.drawIteration();
a1.drawIteration(1,6);
a1.drawIteration(7,14);
a1.drawIteration(15,26);
a1.drawIteration(27,38);
a1.drawIteration(39,48);
a1.drawIteration(49,68);



//gROOT->ProcessLine(".q");


}
