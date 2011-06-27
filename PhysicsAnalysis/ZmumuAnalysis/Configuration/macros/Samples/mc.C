#include "defaultSampleStruct.C"
#include "allSampleStruct.C"

#include "ZmumuAnalysis/Configuration/macros/Tools/printLine.h"


//void mc(){
  PrintLine printLine;

  const TColor* colorZmumuB = new TColor(1001, 0.00, 1.00, 0.00, "zmumuB");
  const TColor* colorZmumuUdsc = new TColor(1002, 0.00, 0.50, 0.00, "zmumuUdsc");
  const TColor* colorZz = new TColor(1003, 1.00, 1.00, 0.00, "zz");
  const TColor* colorWz = new TColor(1004, 0.00, 0.00, 1.00, "wz");
  const TColor* colorWw = new TColor(1005, 0.00, 0.50, 1.00, "ww");
  const TColor* colorZtautau = new TColor(1006, 0.00, 1.00, 1.00, "ztautau");
  const TColor* colorWmunu = new TColor(1007, 0.50, 0.00, 0.50, "wmunu");
  const TColor* colorWtaunu = new TColor(1008, 1.00, 0.00, 1.00, "wtaunu");
  const TColor* colorSingletopTw = new TColor(1009, 0.50, 0.00, 1.00, "singletopTw");
  const TColor* colorSingletopT = new TColor(1010, 0.30, 0.00, 1.00, "singletopT");
  const TColor* colorSingletopS = new TColor(1011, 0.40, 0.00, 1.00, "singletopS");
  const TColor* colorTtbar = new TColor(1012, 1.00, 0.00, 0.00, "ttbar");
  const TColor* colorQcd = new TColor(1013, 0.00, 0.00, 0.50, "qcd");
  
  McStruct zmumuB("zmumuB.root", 2329439, 3048., 1., colorZmumuB);
  McStruct zmumuUdsc("zmumuUdsc.root", 2329439, 3048., 1., colorZmumuUdsc);
  McStruct zz("zz.root", 2108608, 7.4, 1., colorZz);
  McStruct wz("wz.root", 110000, 0.61, 1., colorWz);
  McStruct ww("ww.root", 110000, 4.51, 1., colorWw);
  McStruct ztautau("ztautau.root", 2329439, 3048., 1., colorZtautau);
  McStruct wmunu("wmunu.root", 5038640, 10438., 1., colorWmunu);
  McStruct wtaunu("wtaunu.root", 4773750, 10438., 1., colorWtaunu);
  McStruct singletopTw("singletopTw.root", 489417, 10.6, 1., colorSingletopTw);
  McStruct singletopT("singletopT.root", 484060, 64.6, 1., colorSingletopT);
  McStruct singletopS("singletopS.root", 494967, 4.21, 1., colorSingletopS);
  McStruct ttbar("ttbar.root", 1286491, 157.5, 1., colorTtbar);
  McStruct qcd("qcd.root", 29434562, 296600., 0.2864, colorQcd);  // real values: crossSection*1000, filterEfficiency/1000
  
  
void mc(){
  allSampleStruct.signalStruct = &zmumuB;
  
  allSampleStruct.v_backgroundStruct.push_back(&zmumuUdsc);
  allSampleStruct.v_backgroundStruct.push_back(&zz);
  allSampleStruct.v_backgroundStruct.push_back(&wz);
  allSampleStruct.v_backgroundStruct.push_back(&ww);
  allSampleStruct.v_backgroundStruct.push_back(&ztautau);
  allSampleStruct.v_backgroundStruct.push_back(&wmunu);
  allSampleStruct.v_backgroundStruct.push_back(&wtaunu);
  allSampleStruct.v_backgroundStruct.push_back(&singletopTw);
  allSampleStruct.v_backgroundStruct.push_back(&singletopT);
  allSampleStruct.v_backgroundStruct.push_back(&singletopS);
  allSampleStruct.v_backgroundStruct.push_back(&ttbar);
  allSampleStruct.v_backgroundStruct.push_back(&qcd);
}















