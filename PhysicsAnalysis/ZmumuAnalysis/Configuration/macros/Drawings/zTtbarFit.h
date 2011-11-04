#include "ZmumuAnalysis/Configuration/macros/Tools/FullAnalysis.h"


#include "ZmumuAnalysis/Configuration/macros/Tools/signalAndSidebandCombined.h"
#include "ZmumuAnalysis/Configuration/macros/Tools/histTools.h"


#include "TString.h"
#include "TH1.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TLegend.h"

#include <iostream>



void FullAnalysis::zTtbarFit(const bool zmumuInOne){
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
  
  TH1* dimuonMassZmumuC(0);
  TH1* dimuonMassZmumuUds(0);
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
    else if(background.datasetName()=="zmumuC"){
      dimuonMassZmumuC = Tools::signalAndSidebandCombined(background.file(), this->recoSelectionStep(), pluginBase, pluginFolder, histName);
      if(!zmumuInOne)dimuonMassZmumuC->SetFillColor(background.color()->GetNumber());
    }
    else if(background.datasetName()=="zmumuUds"){
      dimuonMassZmumuUds = Tools::signalAndSidebandCombined(background.file(), this->recoSelectionStep(), pluginBase, pluginFolder, histName);
      if(!zmumuInOne)dimuonMassZmumuUds->SetFillColor(background.color()->GetNumber());
    }
    else if(background.datasetName()=="zmumuUdsc"){
      dimuonMassZmumuUdsc = Tools::signalAndSidebandCombined(background.file(), this->recoSelectionStep(), pluginBase, pluginFolder, histName);
      if(!zmumuInOne)dimuonMassZmumuUdsc->SetFillColor(background.color()->GetNumber());
    }
  }
  
  if(zmumuInOne){
    if(dimuonMassZmumuC && dimuonMassZmumuUds){
      dimuonMassZmumuB->Add(dimuonMassZmumuC);
      dimuonMassZmumuB->Add(dimuonMassZmumuUds);
    }
    else if(dimuonMassZmumuUdsc){
      dimuonMassZmumuB->Add(dimuonMassZmumuUdsc);
    }
    else{
      std::cout<<"Zmumu background sample missing\n"
             <<"\t... stop plotting fit of ttbar and zmumu\n";
      return;
    }
  }
  dimuonMassZmumuB->SetFillColor(zmumuB.color()->GetNumber());
  
  double overallScaleFactorZmumu = this->zmumuFraction()*this->nObserved().value()/this->nZmumuInMc();
  double overallScaleFactorTtbar = this->ttbarFraction().value()*this->nObserved().value()/this->nTtbarInMc();
  dimuonMassZmumuB->Scale(overallScaleFactorZmumu);
  if(dimuonMassZmumuC)dimuonMassZmumuC->Scale(overallScaleFactorZmumu);
  if(dimuonMassZmumuUds)dimuonMassZmumuUds->Scale(overallScaleFactorZmumu);
  if(dimuonMassZmumuUdsc)dimuonMassZmumuUdsc->Scale(overallScaleFactorZmumu);
  dimuonMassTtbar->Scale(overallScaleFactorTtbar);
  
  
  
  // Set plotting parameters and make final plot
  double maxScaleFactor = overallScaleFactorZmumu>overallScaleFactorTtbar ? overallScaleFactorZmumu : overallScaleFactorTtbar;
  
  {
  TH1* dimuonMassZmumuB_rebin = (TH1*)dimuonMassZmumuB->Clone("dimuonMassZmumuB_rebin");
  TH1* dimuonMassZmumuC_rebin(0);
  TH1* dimuonMassZmumuUds_rebin(0);
  TH1* dimuonMassZmumuUdsc_rebin(0);
  if(dimuonMassZmumuC)dimuonMassZmumuC_rebin = (TH1*)dimuonMassZmumuC->Clone("dimuonMassZmumuC_rebin");
  if(dimuonMassZmumuUds)dimuonMassZmumuUds_rebin = (TH1*)dimuonMassZmumuUds->Clone("dimuonMassZmumuUds_rebin");
  if(dimuonMassZmumuUdsc)dimuonMassZmumuUdsc_rebin = (TH1*)dimuonMassZmumuUdsc->Clone("dimuonMassZmumuUdsc_rebin");
  TH1* dimuonMassTtbar_rebin = (TH1*)dimuonMassTtbar->Clone("dimuonMassTtbar_rebin");
  TH1* dimuonMassData_rebin = (TH1*)dimuonMassData->Clone("dimuonMassData_rebin");
  
  dimuonMassZmumuB_rebin->Rebin(10);
  if(dimuonMassZmumuC_rebin)dimuonMassZmumuC_rebin->Rebin(10);
  if(dimuonMassZmumuUds_rebin)dimuonMassZmumuUds_rebin->Rebin(10);
  if(dimuonMassZmumuUdsc_rebin)dimuonMassZmumuUdsc_rebin->Rebin(10);
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
  if(!zmumuInOne){
    if(dimuonMassZmumuC_rebin){
      mcStack->Add(dimuonMassZmumuC_rebin);
      yMinTemp = mcStack->GetMinimum();
      if(yMin>yMinTemp)yMin=yMinTemp;
    }
    if(dimuonMassZmumuUds_rebin){
      mcStack->Add(dimuonMassZmumuUds_rebin);
      yMinTemp = mcStack->GetMinimum();
      if(yMin>yMinTemp)yMin=yMinTemp;
    }
    if(dimuonMassZmumuUdsc_rebin){
      mcStack->Add(dimuonMassZmumuUdsc_rebin);
      yMinTemp = mcStack->GetMinimum();
      if(yMin>yMinTemp)yMin=yMinTemp;
    }
  }
  yMax = mcStack->GetMaximum();
  
  yMinTemp = dimuonMassData_rebin->GetMinimum();
  yMaxTemp = dimuonMassData_rebin->GetMaximum();
  if(yMin>yMinTemp)yMin=yMinTemp;
  if(yMax<yMaxTemp)yMax=yMaxTemp;
  
  StackTools::setTitles(mcStack, dimuonMassZmumuB);
  TCanvas* canvas = new TCanvas("plot", "plot", 800, 800);
  mcStack->Draw();
  // Does not work for y, but works for x !?
  //if(yMax>yMin)mcStack->GetYaxis()->SetRangeUser(0., 1.1*yMax);
  mcStack->SetMaximum(1.1*yMax);
  mcStack->SetMinimum(0.);
  mcStack->GetXaxis()->SetRangeUser(60., 400.);
  
  canvas->Clear();
  mcStack->Draw();
  dimuonMassData_rebin->Draw("same,e1");
  
  TLegend* legend(0);
  if(zmumuInOne)legend = new TLegend(0.75,0.75,0.99,0.85);
  else legend = new TLegend(0.75,0.65,0.99,0.85);
  legend->Clear();
  legend->SetFillColor(0);
  legend->SetFillStyle(4000);
  //legend->AddEntry(dimuonMassData, "data", "le");
  legend->AddEntry(dimuonMassData, "data", "p");
  if(zmumuInOne){
    legend->AddEntry(dimuonMassZmumuB, "Z #rightarrow #mu#mu", "f");
  }
  else{
    legend->AddEntry(dimuonMassZmumuB, "Z+b", "f");
    if(dimuonMassZmumuC)legend->AddEntry(dimuonMassZmumuC, "Z+c", "f");
    if(dimuonMassZmumuUds)legend->AddEntry(dimuonMassZmumuUds, "Z+l", "f");
    if(dimuonMassZmumuUdsc)legend->AddEntry(dimuonMassZmumuUdsc, "Z+c/l", "f");
  }
  legend->AddEntry(dimuonMassTtbar, "t#bar{t}", "f");
  legend->Draw("same");
  
  canvas->Modified();
  canvas->Update();
  
  TString outputDirectory("plots/");
  TString plotName(outputDirectory + this->inputFolder() + "_zTtbarFit" + this->recoSelectionStep());
  
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
  TH1* dimuonMassZmumuC_zoom(0);
  TH1* dimuonMassZmumuUds_zoom(0);
  TH1* dimuonMassZmumuUdsc_zoom(0);
  if(dimuonMassZmumuC)dimuonMassZmumuC_zoom = (TH1*)dimuonMassZmumuC->Clone("dimuonMassZmumuC_zoom");
  if(dimuonMassZmumuUds)dimuonMassZmumuUds_zoom = (TH1*)dimuonMassZmumuUds->Clone("dimuonMassZmumuUds_zoom");
  if(dimuonMassZmumuUdsc)dimuonMassZmumuUdsc_zoom = (TH1*)dimuonMassZmumuUdsc->Clone("dimuonMassZmumuUdsc_zoom");
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
  if(!zmumuInOne){
    if(dimuonMassZmumuC_zoom){
      mcStack->Add(dimuonMassZmumuC_zoom);
      yMinTemp = mcStack->GetMinimum();
      if(yMin>yMinTemp)yMin=yMinTemp;
    }
    if(dimuonMassZmumuUds_zoom){
      mcStack->Add(dimuonMassZmumuUds_zoom);
      yMinTemp = mcStack->GetMinimum();
      if(yMin>yMinTemp)yMin=yMinTemp;
    }
    if(dimuonMassZmumuUdsc_zoom){
      mcStack->Add(dimuonMassZmumuUdsc_zoom);
      yMinTemp = mcStack->GetMinimum();
      if(yMin>yMinTemp)yMin=yMinTemp;
    }
  }
  yMax = mcStack->GetMaximum();
  
  yMinTemp = dimuonMassData_zoom->GetMinimum();
  yMaxTemp = dimuonMassData_zoom->GetMaximum();
  if(yMin>yMinTemp)yMin=yMinTemp;
  if(yMax<yMaxTemp)yMax=yMaxTemp;
  
  StackTools::setTitles(mcStack, dimuonMassZmumuB);
  TCanvas* canvas = new TCanvas("plot", "plot", 800, 800);
  mcStack->Draw();
  // Does not work for y, but works for x !?
  //if(yMax>yMin)mcStack->GetYaxis()->SetRangeUser(0., 1.1*yMax);
  mcStack->SetMaximum(1.1*yMax);
  mcStack->SetMinimum(0.);
  mcStack->GetXaxis()->SetRangeUser(60., 200.);
  
  canvas->Clear();
  mcStack->Draw();
  dimuonMassData_zoom->Draw("same,e1");
  
  TLegend* legend(0);
  if(zmumuInOne)legend = new TLegend(0.75,0.75,0.99,0.85);
  else legend = new TLegend(0.75,0.65,0.99,0.85);
  legend->Clear();
  legend->SetFillColor(0);
  legend->SetFillStyle(4000);
  //legend->AddEntry(dimuonMassData, "data", "le");
  legend->AddEntry(dimuonMassData, "data", "p");
  if(zmumuInOne){
    legend->AddEntry(dimuonMassZmumuB, "Z #rightarrow #mu#mu", "f");
  }
  else{
    legend->AddEntry(dimuonMassZmumuB, "Z+b", "f");
    if(dimuonMassZmumuC)legend->AddEntry(dimuonMassZmumuC, "Z+c", "f");
    if(dimuonMassZmumuUds)legend->AddEntry(dimuonMassZmumuUds, "Z+l", "f");
    if(dimuonMassZmumuUdsc)legend->AddEntry(dimuonMassZmumuUdsc, "Z+c/l", "f");
  }
  legend->AddEntry(dimuonMassTtbar, "t#bar{t}", "f");
  legend->Draw("same");
  
  canvas->Modified();
  canvas->Update();
  
  TString outputDirectory("plots/");
  TString plotName(outputDirectory + this->inputFolder() + "_zTtbarFit" + this->recoSelectionStep());
  
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







