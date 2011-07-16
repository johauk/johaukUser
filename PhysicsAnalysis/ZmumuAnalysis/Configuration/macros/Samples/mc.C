#include "defaultSampleStruct.C"
#include "allSampleStruct.h"



TColor* colorZmumuB = new TColor(1001, 0.00, 1.00, 0.00, "zmumuB");
TColor* colorZmumuUdsc = new TColor(1002, 0.00, 0.50, 0.00, "zmumuUdsc");
TColor* colorZz = new TColor(1003, 1.00, 1.00, 0.00, "zz");
TColor* colorWz = new TColor(1004, 0.00, 0.00, 1.00, "wz");
TColor* colorWw = new TColor(1005, 0.00, 0.50, 1.00, "ww");
TColor* colorZtautau = new TColor(1006, 0.00, 1.00, 1.00, "ztautau");
TColor* colorWmunu = new TColor(1007, 0.50, 0.00, 0.50, "wmunu");
TColor* colorWtaunu = new TColor(1008, 1.00, 0.00, 1.00, "wtaunu");
TColor* colorSingletopTw = new TColor(1009, 0.50, 0.00, 1.00, "singletopTw");
TColor* colorSingletopT = new TColor(1010, 0.30, 0.00, 1.00, "singletopT");
TColor* colorSingletopS = new TColor(1011, 0.40, 0.00, 1.00, "singletopS");
TColor* colorTtbar = new TColor(1012, 1.00, 0.00, 0.00, "ttbar");
TColor* colorQcd = new TColor(1013, 0.00, 0.00, 0.50, "qcd");

McStruct zmumuB("zmumuB", 36277961, 3048., 132., 132., 1., colorZmumuB);
McStruct zmumuUdsc("zmumuUdsc", 36277961, 3048., 132., 132., 1., colorZmumuUdsc);
McStruct zz("zz", 0, 7.4, 0.19, 0.19, 1., colorZz);
McStruct wz("wz", 0, 0.61, 0.02, 0.02, 1., colorWz);
McStruct ww("ww", 0, 4.51, 0.16, 0.16, 1., colorWw);
McStruct ztautau("ztautau", 0, 3048., 132., 132., 1., colorZtautau);
McStruct wmunu("wmunu", 0, 10438., 519., 519., 1., colorWmunu);
McStruct wtaunu("wtaunu", 0, 10438., 519., 519., 1., colorWtaunu);
McStruct singletopTw("singletopTw", 0, 10.6, 0.8, 0.8, 1., colorSingletopTw);
McStruct singletopT("singletopT", 0, 64.6, 3.4, 3.2, 1., colorSingletopT);
McStruct singletopS("singletopS", 0, 4.21, 0.19, 0.18, 1., colorSingletopS);
McStruct ttbar("ttbar", 3581947, 157.5, 23.2, 24.4, 1., colorTtbar);
McStruct qcd("qcd", 0, 296600., 296600.*0.5, 296600.*0.5, 0.2864, colorQcd);  // real values: crossSection*1000, filterEfficiency/1000


void mc(AllSampleStruct& allSample){
  if(zmumuB.file_)allSample.signalStruct_ = &zmumuB;
  
  if(zmumuUdsc.file_)allSample.v_backgroundStruct_.push_back(&zmumuUdsc);
  if(zz.file_)allSample.v_backgroundStruct_.push_back(&zz);
  if(wz.file_)allSample.v_backgroundStruct_.push_back(&wz);
  if(zz.file_)allSample.v_backgroundStruct_.push_back(&ww);
  if(ztautau.file_)allSample.v_backgroundStruct_.push_back(&ztautau);
  if(wmunu.file_)allSample.v_backgroundStruct_.push_back(&wmunu);
  if(wtaunu.file_)allSample.v_backgroundStruct_.push_back(&wtaunu);
  if(singletopTw.file_)allSample.v_backgroundStruct_.push_back(&singletopTw);
  if(singletopT.file_)allSample.v_backgroundStruct_.push_back(&singletopT);
  if(singletopS.file_)allSample.v_backgroundStruct_.push_back(&singletopS);
  if(ttbar.file_)allSample.v_backgroundStruct_.push_back(&ttbar);
  if(qcd.file_)allSample.v_backgroundStruct_.push_back(&qcd);
  
  std::cout<<"\tNumber of background samples: "<<allSample.v_backgroundStruct_.size()<<"\n";
}















