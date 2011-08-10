// .L zTtbarFit.C++
// .L ../Samples/allSampleStruct.C++
// .L ../Samples/data.C++
// data(allSampleStruct);
// .L ../Samples/mc.C++
//  mc(allSampleStruct);
// zTtbarFit("Step5");
#include "ZmumuAnalysis/Configuration/macros/Tools/FullAnalysis.h"


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
  dimuonMassData = Tools::signalAndSidebandCombined(data.file(), this->recoSelectionStep(), pluginBase, pluginFolder, histName);
  
  TH1* dimuonMassZmumuB(0);
  dimuonMassZmumuB = Tools::signalAndSidebandCombined(zmumuB.file(), this->recoSelectionStep(), pluginBase, pluginFolder, histName);
  
  TH1* dimuonMassZmumuUdsc(0);
  TH1* dimuonMassTtbar(0);
  //TH1* dimuonMassOther(0);
  const McSample* ttbar(0);
  std::vector<McSample*>::const_iterator i_background;
  for(i_background = v_background.begin(); i_background != v_background.end(); ++i_background){
    const McSample& background = **i_background;
    if(background.datasetName()=="ttbar"){
      dimuonMassTtbar = Tools::signalAndSidebandCombined(background.file(), this->recoSelectionStep(), pluginBase, pluginFolder, histName);
      dimuonMassTtbar->SetFillColor(background.color()->GetNumber());
      ttbar = &background;
    }
    else if(background.datasetName()=="zmumuUdsc"){
      dimuonMassZmumuUdsc = Tools::signalAndSidebandCombined(background.file(), this->recoSelectionStep(), pluginBase, pluginFolder, histName);
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
  
  {
  TH1* dimuonMassZmumuB_rebin = (TH1*)dimuonMassZmumuB->Clone("dimuonMassZmumuB_rebin");
  TH1* dimuonMassTtbar_rebin = (TH1*)dimuonMassTtbar->Clone("dimuonMassTtbar_rebin");
  TH1* dimuonMassData_rebin = (TH1*)dimuonMassData->Clone("dimuonMassData_rebin");
  
  dimuonMassZmumuB_rebin->Rebin(10);
  dimuonMassTtbar_rebin->Rebin(10);
  dimuonMassData_rebin->Rebin(10);
  
  double yMin(0.), yMax(0.);
  double yMinTemp(0.), yMaxTemp(0.);
  THStack* mcStack = new THStack("stack","stack");
  mcStack->Add(dimuonMassTtbar_rebin);
  yMin = mcStack->GetMinimum();
  mcStack->Add(dimuonMassZmumuB_rebin);
  yMinTemp = mcStack->GetMinimum();
  if(yMin>yMinTemp)yMin=yMinTemp;
  yMax = mcStack->GetMaximum();
  
  yMinTemp = dimuonMassData_rebin->GetMinimum();
  yMaxTemp = dimuonMassData_rebin->GetMaximum();
  if(yMin>yMinTemp)yMin=yMinTemp;
  if(yMax<yMaxTemp)yMax=yMaxTemp;
  
  TCanvas* canvas = new TCanvas("plot", "plot", 800, 800);
  mcStack->Draw();
  // Does not work for y, but works for x !?
  //if(yMax>yMin)mcStack->GetYaxis()->SetRangeUser(0., 1.1*yMax);
  mcStack->SetMaximum(1.1*yMax);
  mcStack->SetMinimum(0.);
  //mcStack->GetXaxis()->SetRangeUser(60., 200.);
  
  canvas->Clear();
  mcStack->Draw();
  dimuonMassData_rebin->Draw("same,e1");
  
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
  }
  
  
  {
  TH1* dimuonMassZmumuB_zoom = (TH1*)dimuonMassZmumuB->Clone("dimuonMassZmumuB_zoom");
  TH1* dimuonMassTtbar_zoom = (TH1*)dimuonMassTtbar->Clone("dimuonMassTtbar_zoom");
  TH1* dimuonMassData_zoom = (TH1*)dimuonMassData->Clone("dimuonMassData_zoom");
  
  double yMin(0.), yMax(0.);
  double yMinTemp(0.), yMaxTemp(0.);
  THStack* mcStack = new THStack("stack","stack");
  mcStack->Add(dimuonMassTtbar_zoom);
  yMin = mcStack->GetMinimum();
  mcStack->Add(dimuonMassZmumuB_zoom);
  yMinTemp = mcStack->GetMinimum();
  if(yMin>yMinTemp)yMin=yMinTemp;
  yMax = mcStack->GetMaximum();
  
  yMinTemp = dimuonMassData_zoom->GetMinimum();
  yMaxTemp = dimuonMassData_zoom->GetMaximum();
  if(yMin>yMinTemp)yMin=yMinTemp;
  if(yMax<yMaxTemp)yMax=yMaxTemp;
  
  TCanvas* canvas = new TCanvas("plot", "plot", 800, 800);
  mcStack->Draw();
  // Does not work for y, but works for x !?
  //if(yMax>yMin)mcStack->GetYaxis()->SetRangeUser(0., 1.1*yMax);
  mcStack->SetMaximum(1.1*yMax);
  mcStack->SetMinimum(0.);
  mcStack->GetXaxis()->SetRangeUser(40., 200.);
  
  canvas->Clear();
  mcStack->Draw();
  dimuonMassData_zoom->Draw("same,e1");
  
  canvas->Modified();
  canvas->Update();
  
  TString outputDirectory("plots/");
  TString plotName(outputDirectory + "zTtbarFit" + this->recoSelectionStep());
  
  plotName += "_zoom";
  
  canvas->Print(plotName + ".eps");
  canvas->Print(plotName + ".png");
  
  //double yMinHist(yMin<maxScaleFactor ? 0.5*maxScaleFactor : 0.5*yMin);
  double yMinHist(0.5);
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
  
  
  // FIXME: delete stacks and histos...
  
  
  // Just for information: scaleFactor relative to the one taken from data luminosity scaling
  ValueAndErrorStatSystLumi weightZmumu = zmumuB.effectiveWeight(this->luminosity());
  ValueAndErrorStatSystLumi weightTtbar = ttbar->effectiveWeight(this->luminosity());
  double scaleFactorZmumuLumi = overallScaleFactorZmumu/weightZmumu.value();
  double scaleFactorTtbarLumi = overallScaleFactorTtbar/weightTtbar.value();
  std::cout<<"Scale factor for zmumu: "<<scaleFactorZmumuLumi<<"\n";
  std::cout<<"Scale factor for ttbar: "<<scaleFactorTtbarLumi<<"\n";
}







