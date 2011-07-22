// .L zTtbarFit.C++
// .L ../Samples/allSampleStruct.C++
// .L ../Samples/data.C++
// data(allSampleStruct);
// .L ../Samples/mc.C++
//  mc(allSampleStruct);
// zTtbarFit("Step5");


#include "ZmumuAnalysis/Configuration/macros/Tools/signalAndSidebandCombined.h"
#include "ZmumuAnalysis/Configuration/macros/Samples/allSampleStruct.C"


#include "TString.h"
#include "TH1.h"
#include "TCanvas.h"
#include "THStack.h"

#include <iostream>





void zTtbarFit(const TString pluginSuffix = "", const double ttbarFractionIn =0., const double zmumuFractionIn =0., const double nObservedIn=0., const double nInTtbar=0., const double nInZmumu=0.){
  const DataStruct& data = *allSampleStruct.dataStruct_;
  const McStruct& zmumuB = *allSampleStruct.signalStruct_;
  const std::vector<McStruct*> v_background = allSampleStruct.v_backgroundStruct_;
  
  
  
  
  //Specify plugin name
  const TString pluginBase("DiMuonAnalyzer");
  //const TString pluginBase("DimuonAnalyzer");
  
  const TString pluginFolder("OppositeCharge");
  //const TString pluginFolder("DimuonProperties");
  
  // Give name of input histogram
  const TString histName("h_diMass");
  
  
  
  TH1* dimuonMassData(0);
  dimuonMassData = signalAndSidebandCombined(data.file_, pluginSuffix, pluginBase, pluginFolder, histName);
  
  TH1* dimuonMassZmumuB(0);
  dimuonMassZmumuB = signalAndSidebandCombined(zmumuB.file_, pluginSuffix, pluginBase, pluginFolder, histName);
  
  TH1* dimuonMassZmumuUdsc(0);
  TH1* dimuonMassTtbar(0);
  //TH1* dimuonMassOther(0);
  const McStruct* ttbar(0);
  std::vector<McStruct*>::const_iterator i_background;
  for(i_background = v_background.begin(); i_background != v_background.end(); ++i_background){
    const McStruct& background = **i_background;
    if(background.datasetName_=="ttbar"){
      dimuonMassTtbar = signalAndSidebandCombined(background.file_, pluginSuffix, pluginBase, pluginFolder, histName);
      dimuonMassTtbar->SetFillColor(background.color_->GetNumber());
      ttbar = &background;
    }
    else if(background.datasetName_=="zmumuUdsc"){
      dimuonMassZmumuUdsc = signalAndSidebandCombined(background.file_, pluginSuffix, pluginBase, pluginFolder, histName);
      //dimuonMassZmumuUdsc->SetFillColor(background.color_->GetNumber());
    }
  }
  
  dimuonMassZmumuB->Add(dimuonMassZmumuUdsc);
  dimuonMassZmumuB->SetFillColor(zmumuB.color_->GetNumber());
  
  double luminosity = data.getEffectiveLuminosity();
  double weightZmumu = zmumuB.getEffectiveWeight(luminosity);
  double weightTtbar = ttbar->getEffectiveWeight(luminosity);
  
  double scaleFactorZmumu = zmumuFractionIn*nObservedIn/(nInZmumu*weightZmumu);
  double scaleFactorTtbar = ttbarFractionIn*nObservedIn/(nInTtbar*weightTtbar);
  
  std::cout<<"Scale factor for zmumu: "<<scaleFactorZmumu<<"\n";
  std::cout<<"Scale factor for ttbar: "<<scaleFactorTtbar<<"\n";
  
  dimuonMassZmumuB->Scale(weightZmumu*scaleFactorZmumu);
  dimuonMassTtbar->Scale(weightTtbar*scaleFactorTtbar);
  
  double maxScaleFactor = weightZmumu*scaleFactorZmumu>weightTtbar*scaleFactorTtbar ? weightZmumu*scaleFactorZmumu : weightTtbar*scaleFactorTtbar;
  
  double yMin(0.), yMax(0.);
  double yMinTemp(0.), yMaxTemp(0.);
  THStack* mcStack = new THStack("stack","stack");
  mcStack->Add(dimuonMassTtbar);
  yMin = mcStack->GetMinimum();
  mcStack->Add(dimuonMassZmumuB);
  yMinTemp = mcStack->GetMinimum();
  if(yMin>yMinTemp)yMin=yMinTemp;
  yMax = mcStack->GetMaximum();
  
  yMinTemp = dimuonMassData->GetMinimum();
  yMaxTemp = dimuonMassData->GetMaximum();
  if(yMin>yMinTemp)yMin=yMinTemp;
  if(yMax<yMaxTemp)yMax=yMaxTemp;
  
  TCanvas* canvas = new TCanvas("plot", "plot", 800, 800);
  mcStack->Draw();
  //if(yMax>yMin)mcStack->GetYaxis()->SetRangeUser(0., 1.1*yMax);
  mcStack->SetMaximum(1.1*yMax);
  mcStack->SetMinimum(0.);
  
  canvas->Clear();
  mcStack->Draw();
  dimuonMassData->Draw("same,e1");
  
  canvas->Modified();
  canvas->Update();
  
  TString outputDirectory("plots/");
  TString plotName(outputDirectory + "zTtbarFit" + pluginSuffix);
  
  canvas->Print(plotName + ".eps");
  canvas->Print(plotName + ".png");
  
  double yMinHist(yMin<maxScaleFactor ? 0.5*maxScaleFactor : 0.5*yMin);
  double yMaxHist(pow(yMax,1.1)/pow(yMinHist,0.1));
  //if(yMax>yMin)mcStack->GetYaxis()->SetRangeUser(yMinHist, yMaxHist);
  mcStack->SetMaximum(yMaxHist);
  mcStack->SetMinimum(yMinHist);
  
  //canvas->SetLogy();
  gPad->SetLogy();
  canvas->Modified();
  canvas->Update();
  
  plotName += "_log";
  
  canvas->Print(plotName + ".eps");
  canvas->Print(plotName + ".png");
  canvas->Close();
}


