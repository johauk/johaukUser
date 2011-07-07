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

McStruct zmumuB("zmumuB", 2329439, 3048., 1., colorZmumuB);
McStruct zmumuUdsc("zmumuUdsc", 2329439, 3048., 1., colorZmumuUdsc);
McStruct zz("zz", 2108608, 7.4, 1., colorZz);
McStruct wz("wz", 110000, 0.61, 1., colorWz);
McStruct ww("ww", 110000, 4.51, 1., colorWw);
McStruct ztautau("ztautau", 2329439, 3048., 1., colorZtautau);
McStruct wmunu("wmunu", 5038640, 10438., 1., colorWmunu);
McStruct wtaunu("wtaunu", 4773750, 10438., 1., colorWtaunu);
McStruct singletopTw("singletopTw", 489417, 10.6, 1., colorSingletopTw);
McStruct singletopT("singletopT", 484060, 64.6, 1., colorSingletopT);
McStruct singletopS("singletopS", 494967, 4.21, 1., colorSingletopS);
McStruct ttbar("ttbar", 1286491, 157.5, 1., colorTtbar);
McStruct qcd("qcd", 29434562, 296600., 0.2864, colorQcd);  // real values: crossSection*1000, filterEfficiency/1000


void mc(AllSampleStruct& allSample){
  allSample.signalStruct_ = &zmumuB;
  
  allSample.v_backgroundStruct_.push_back(&zmumuUdsc);
  allSample.v_backgroundStruct_.push_back(&zz);
  allSample.v_backgroundStruct_.push_back(&wz);
  allSample.v_backgroundStruct_.push_back(&ww);
  allSample.v_backgroundStruct_.push_back(&ztautau);
  allSample.v_backgroundStruct_.push_back(&wmunu);
  allSample.v_backgroundStruct_.push_back(&wtaunu);
  allSample.v_backgroundStruct_.push_back(&singletopTw);
  allSample.v_backgroundStruct_.push_back(&singletopT);
  allSample.v_backgroundStruct_.push_back(&singletopS);
  allSample.v_backgroundStruct_.push_back(&ttbar);
  allSample.v_backgroundStruct_.push_back(&qcd);
  
}















