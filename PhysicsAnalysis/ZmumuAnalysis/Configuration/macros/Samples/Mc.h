#include "ZmumuAnalysis/Configuration/macros/Calculations/FullAnalysis.h"


void FullAnalysis::setMcSamples(){
  
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
  
  // Define signal sample
  McSample* zmumuB(0);
  zmumuB = new McSample("zmumuB", 36277961, colorZmumuB);
  zmumuB->crossSection_.setValue(3048.);
  zmumuB->crossSection_.setAbsErrUp(132.);
  zmumuB->crossSection_.setAbsErrDw(132.);
  //zmumuB->setFilterEfficiency(1.);
  if(zmumuB->file())signalSample_ = zmumuB;
  else{
    signalSample_ = 0;
    delete zmumuB;
  }
  
  // Define all background samples
  McSample* zmumuUdsc(0);
  zmumuUdsc = new McSample("zmumuUdsc", 36277961, colorZmumuUdsc);
  zmumuUdsc->crossSection_.setValue(3048.);
  zmumuUdsc->crossSection_.setAbsErrUp(132.);
  zmumuUdsc->crossSection_.setAbsErrDw(132.);
  //zmumuUdsc->setFilterEfficiency(1.);
  if(zmumuUdsc->file())v_backgroundSample_.push_back(zmumuUdsc);
  else delete zmumuUdsc;
  
  McSample* zz(0);
  zz = new McSample("zz", 0, colorZz);
  zz->crossSection_.setValue(7.4);
  zz->crossSection_.setAbsErrUp(0.19);
  zz->crossSection_.setAbsErrDw(0.19);
  //zz->setFilterEfficiency(1.);
  if(zz->file())v_backgroundSample_.push_back(zz);
  else delete zz;
  
  McSample* wz(0);
  wz = new McSample("wz", 0, colorWz);
  wz->crossSection_.setValue(0.61);
  wz->crossSection_.setAbsErrUp(0.02);
  wz->crossSection_.setAbsErrDw(0.02);
  //wz->setFilterEfficiency(1.);
  if(wz->file())v_backgroundSample_.push_back(wz);
  else delete wz;
  
  McSample* ww(0);
  ww = new McSample("ww", 0, colorWw);
  ww->crossSection_.setValue(4.51);
  ww->crossSection_.setAbsErrUp(0.16);
  ww->crossSection_.setAbsErrDw(0.16);
  //ww->setFilterEfficiency(1.);
  if(ww->file())v_backgroundSample_.push_back(ww);
  else delete ww;
  
  McSample* ztautau(0);
  ztautau = new McSample("ztautau", 0, colorZtautau);
  ztautau->crossSection_.setValue(3048.);
  ztautau->crossSection_.setAbsErrUp(132.);
  ztautau->crossSection_.setAbsErrDw(132.);
  //ztautau->setFilterEfficiency(1.);
  if(ztautau->file())v_backgroundSample_.push_back(ztautau);
  else delete ztautau;
  
  McSample* wmunu(0);
  wmunu = new McSample("wmunu", 0, colorWmunu);
  wmunu->crossSection_.setValue(10438.);
  wmunu->crossSection_.setAbsErrUp(519.);
  wmunu->crossSection_.setAbsErrDw(519.);
  //wmunu->setFilterEfficiency(1.);
  if(wmunu->file())v_backgroundSample_.push_back(wmunu);
  else delete wmunu;
  
  McSample* wtaunu(0);
  wtaunu = new McSample("wtaunu", 0, colorWtaunu);
  wtaunu->crossSection_.setValue(10438.);
  wtaunu->crossSection_.setAbsErrUp(519.);
  wtaunu->crossSection_.setAbsErrDw(519.);
  //wtaunu->setFilterEfficiency(1.);
  if(wtaunu->file())v_backgroundSample_.push_back(wtaunu);
  else delete wtaunu;
  
  McSample* singletopTw(0);
  singletopTw = new McSample("singletopTw", 0, colorSingletopTw);
  singletopTw->crossSection_.setValue(10.6);
  singletopTw->crossSection_.setAbsErrUp(0.8);
  singletopTw->crossSection_.setAbsErrDw(0.8);
  //singletopTw->setFilterEfficiency(1.);
  if(singletopTw->file())v_backgroundSample_.push_back(singletopTw);
  else delete singletopTw;
  
  McSample* singletopT(0);
  singletopT = new McSample("singletopT", 0, colorSingletopT);
  singletopT->crossSection_.setValue(64.6);
  singletopT->crossSection_.setAbsErrUp(3.4);
  singletopT->crossSection_.setAbsErrDw(3.2);
  //singletopT->setFilterEfficiency(1.);
  if(singletopT->file())v_backgroundSample_.push_back(singletopT);
  else delete singletopT;
  
  McSample* singletopS(0);
  singletopS = new McSample("singletopS", 0, colorSingletopS);
  singletopS->crossSection_.setValue(4.21);
  singletopS->crossSection_.setAbsErrUp(0.19);
  singletopS->crossSection_.setAbsErrDw(0.18);
  //singletopS->setFilterEfficiency(1.);
  if(singletopS->file())v_backgroundSample_.push_back(singletopS);
  else delete singletopS;
  
  McSample* ttbar(0);
  ttbar = new McSample("ttbar", 3581947, colorTtbar);
  ttbar->crossSection_.setValue(157.5);
  ttbar->crossSection_.setAbsErrUp(23.2);
  ttbar->crossSection_.setAbsErrDw(24.4);
  //ttbar->setFilterEfficiency(1.);
  if(ttbar->file())v_backgroundSample_.push_back(ttbar);
  else delete ttbar;
  
  McSample* qcd(0);
  qcd = new McSample("qcd", 0, colorQcd);  // real values: crossSection*1000, filterEfficiency/1000
  qcd->crossSection_.setValue(296600.);
  qcd->crossSection_.setAbsErrUp(296600.*0.5);
  qcd->crossSection_.setAbsErrDw(296600.*0.5);
  qcd->setFilterEfficiency(0.2864);
  if(qcd->file())v_backgroundSample_.push_back(qcd);
  else delete qcd;
  
  //McSample* (0);
  // = new McSample("", , color);
  //->crossSection_.setValue();
  //->crossSection_.setAbsErrUp();
  //->crossSection_.setAbsErrDw();
  //->setFilterEfficiency();
  //if(->file())v_backgroundSample_.push_back();
  //else delete ;
}
















