{

gROOT->ProcessLine(".L DrawIteration.C+");



DrawIteration drawIteration1(14);

//drawIteration1.drawIteration();
drawIteration1.drawIteration(1,6);
drawIteration1.drawIteration(7,10);
drawIteration1.drawIteration(11,22);
drawIteration1.drawIteration(23,34);
drawIteration1.drawIteration(35,44);
drawIteration1.drawIteration(45,64);



DrawIteration drawIteration2(15);

drawIteration2.drawIteration(1,6);
drawIteration2.drawIteration(7,10);
drawIteration2.drawIteration(11,22);
drawIteration2.drawIteration(23,34);
drawIteration2.drawIteration(35,44);
drawIteration2.drawIteration(45,64);



gROOT->ProcessLine(".L tdrstyle.C");
setTDRStyle();
gStyle->SetErrorX(0.5);

drawIteration1.drawResult();

drawIteration2.drawResult();







gROOT->ProcessLine(".q");


}
