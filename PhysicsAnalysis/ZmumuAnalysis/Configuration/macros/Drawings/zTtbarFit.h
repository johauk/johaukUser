// .L zTtbarFit.C++
// .L ../Samples/allSampleStruct.C++
// .L ../Samples/data.C++
// data(allSampleStruct);
// .L ../Samples/mc.C++
//  mc(allSampleStruct);
// zTtbarFit("Step5");
#include "ZmumuAnalysis/Configuration/macros/Calculations/FullAnalysis.h"


#include "ZmumuAnalysis/Configuration/macros/Tools/signalAndSidebandCombined.h"

#include "TString.h"
#include "TH1.h"
#include "TCanvas.h"
#include "THStack.h"

#include <iostream>



void FullAnalysis::zTtbarFit(){
  if(!this->dataSample() || !this->signalSample() || this->backgroundSamples().size()==0){
    std::cout<<"\tInput sample missing\n"
             <<"\t... stop plotting fit of ttbar and zmumu\n";
    return;
  }
  const DataSample& data = *this->dataSample();
  const McSample& zmumuB = *this->signalSample();
  const std::vector<McSample*>& v_background = this->backgroundSamples();
  
  //Specify plugin name
  const TString pluginBase("DimuonAnalyzer");
  
  const TString pluginFolder("DimuonProperties");
  
  // Give name of input histogram
  const TString histName("h_diMass");
  
  TH1* dimuonMassData(0);
  dimuonMassData = signalAndSidebandCombined(data.file(), this->recoSelectionStep(), pluginBase, pluginFolder, histName);
  
  TH1* dimuonMassZmumuB(0);
  dimuonMassZmumuB = signalAndSidebandCombined(zmumuB.file(), this->recoSelectionStep(), pluginBase, pluginFolder, histName);
  
  TH1* dimuonMassZmumuUdsc(0);
  TH1* dimuonMassTtbar(0);
  //TH1* dimuonMassOther(0);
  const McSample* ttbar(0);
  std::vector<McSample*>::const_iterator i_background;
  for(i_background = v_background.begin(); i_background != v_background.end(); ++i_background){
    const McSample& background = **i_background;
    if(background.datasetName()=="ttbar"){
      dimuonMassTtbar = signalAndSidebandCombined(background.file(), this->recoSelectionStep(), pluginBase, pluginFolder, histName);
      dimuonMassTtbar->SetFillColor(background.color()->GetNumber());
      ttbar = &background;
    }
    else if(background.datasetName()=="zmumuUdsc"){
      dimuonMassZmumuUdsc = signalAndSidebandCombined(background.file(), this->recoSelectionStep(), pluginBase, pluginFolder, histName);
      //dimuonMassZmumuUdsc->SetFillColor(background.color()->GetNumber());
    }
  }
  
  dimuonMassZmumuB->Add(dimuonMassZmumuUdsc);
  dimuonMassZmumuB->SetFillColor(zmumuB.color()->GetNumber());
  
  double overallScaleFactorZmumu = this->zmumuFraction()*this->nObserved().value()/this->nZmumuInMc();
  double overallScaleFactorTtbar = this->ttbarFraction().value()*this->nObserved().value()/this->nTtbarInMc();
  dimuonMassZmumuB->Scale(overallScaleFactorZmumu);
  dimuonMassTtbar->Scale(overallScaleFactorTtbar);
  
  
  // Set plotting parameters and make final plot
  double maxScaleFactor = overallScaleFactorZmumu>overallScaleFactorTtbar ? overallScaleFactorZmumu : overallScaleFactorTtbar;

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
  TString plotName(outputDirectory + "zTtbarFit" + this->recoSelectionStep());
  
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
  
  
  // Just for information: scaleFactor relative to the one taken from data luminosity scaling
  ValueAndErrorStatSystLumi weightZmumu = zmumuB.effectiveWeight(this->luminosity());
  ValueAndErrorStatSystLumi weightTtbar = ttbar->effectiveWeight(this->luminosity());
  double scaleFactorZmumuLumi = overallScaleFactorZmumu/weightZmumu.value();
  double scaleFactorTtbarLumi = overallScaleFactorTtbar/weightTtbar.value();
  std::cout<<"Scale factor for zmumu: "<<scaleFactorZmumuLumi<<"\n";
  std::cout<<"Scale factor for ttbar: "<<scaleFactorTtbarLumi<<"\n";
}







/*

void zTtbarFit(const TString pluginSuffix = "", const double ttbarFractionIn =0., const double zmumuFractionIn =0., const double nObservedIn=0., const double nInTtbar=0., const double nInZmumu=0.){
  
  
  
  
  
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


*/



