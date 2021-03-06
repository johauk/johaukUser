// root -l
// .L DimuonPlots.C++
// DimuonPlots()        // empty to define pluginName and plotName completely by hand
// DimuonPlots("bla")   // name to define pluginName and plotName via an appended suffix "bla"


#include "TString.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "THStack.h"
#include "TLegend.h"
#include "TLine.h"
#include "TPostScript.h"
#include "TMath.h"
#include "TPad.h"

#include "HistogramTools.h"

const TString* inpath  = new TString("$CMSSW_BASE/src/ZmumuAnalysis/Configuration/hists/");
const TString* outpath = new TString("$CMSSW_BASE/src/ZmumuAnalysis/Configuration/macros/plots/Dimuon_");
const TString* outform = new TString(".png");
//const TString* outform = new TString(".eps");
// number of files used
const size_t nFiles = 12;

// Integrated lumi of taken data for normalising MC in pb-1
const Double_t dataLumi(191.0);


void DimuonPlots(TString pluginSuffix = ""){
  
  
  // Specify all input files
  TFile* a_file[nFiles];
  for(size_t iFile=0; iFile<nFiles; ++iFile) a_file[iFile]=0;
  a_file[0]=new TFile(inpath->Copy().Append("data/allData.root"));
  //a_file[1]=new TFile(inpath->Copy().Append("mc/zmumu.root"));
  a_file[1]=new TFile(inpath->Copy().Append("mc/zmumuB.root"));
  a_file[2]=new TFile(inpath->Copy().Append("mc/zmumuUdsc.root"));
  a_file[3]=new TFile(inpath->Copy().Append("mc/zz.root"));
  a_file[4]=new TFile(inpath->Copy().Append("mc/wz.root"));
  a_file[5]=new TFile(inpath->Copy().Append("mc/ww.root"));
  a_file[6]=new TFile(inpath->Copy().Append("mc/ztautau.root"));
  a_file[7]=new TFile(inpath->Copy().Append("mc/wmunu.root"));
  a_file[8]=new TFile(inpath->Copy().Append("mc/wtaunu.root"));
  a_file[9]=new TFile(inpath->Copy().Append("mc/singletopTw.root"));
  a_file[10]=new TFile(inpath->Copy().Append("mc/ttbar.root"));
  a_file[11]=new TFile(inpath->Copy().Append("mc/qcd.root"));
  
  //Specify plugin name
  TString* pluginName(0);
  pluginName = new TString("DiMuonAnalyzer");
  
  TString* pluginFolder(0);
  pluginFolder = new TString("OppositeCharge");
  
  
  //++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++
  
  // Do not touch this area
  
  pluginName->Append(pluginSuffix);
  if(!pluginName->IsNull())pluginName->Append("/");
  
  if(!pluginFolder->IsNull())pluginFolder->Append("/");
  
  HistogramTools tools;
  tools.SetDefaultStyle();
  
  TCanvas* canvas1(0);

  TLegend* legend1(0); 
   
  TH1F* a_hist1[nFiles];
  for(size_t iFile=0; iFile<nFiles; ++iFile) a_hist1[iFile]=0;
  TH1F* a_hist2[nFiles];  // For addition of histograms
  for(size_t iFile=0; iFile<nFiles; ++iFile) a_hist2[iFile]=0;
  
  THStack* stack1(0);
  
  TString* histName1(0);
  TString* histName2(0);  // For addition of histograms
  
  TString* plotName1(0);
  
  //++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++
  
  
  // Next few lines are only one to change for histo (except for individual style changes)
  
  // Give name of input histogram
  histName1 = new TString("h_nDimuon");
  // Give base name of output plot
  plotName1 = new TString("nDimuon");
  // Change position & size of legend
  legend1 = new TLegend(0.65,0.55,0.99,0.95); 
  
  
  // Change only style here
  
  canvas1 = new TCanvas("plot", "plot", 800, 800);
  tools.GetHistArray(a_file, pluginName->Copy().Append(*pluginFolder), *histName1, a_hist1);
  tools.SetPlotFilling(a_hist1);
  tools.SetWeights(a_hist1, dataLumi);
  stack1 = new THStack("stack","stack");
  tools.FillStack(stack1, a_hist1);
  // If you want to set maximum by hand, else use function and scale
  // stack1->SetMaximum(30);
  stack1->SetMaximum(tools.GetMaximumValue(stack1, a_hist1[0]) *1.2);
  tools.FillLegend(legend1, a_hist1, "f");
  canvas1->Clear();
  stack1->Draw();
  if(a_hist1[0]){ 
    a_hist1[0]->Draw("same,e1");
  }  
  legend1->Draw("same");
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append(*outform));
  
  gPad->SetLogy(1);
  stack1->SetMinimum(0.01);
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append("_log").Append(*outform));
      
  delete histName1;
  delete plotName1;
  legend1->Delete();
  stack1->Delete();
  for(size_t iFile=0; iFile<nFiles; ++iFile){
    if(a_hist1[iFile])a_hist1[iFile]->Delete();
  }
  canvas1->Close();
  
  
  
  
  //++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++
  
  
  // Next few lines are only one to change for histo (except for individual style changes)
  
  // Give name of input histogram
  histName1 = new TString("h_deltaEta");
  // Give base name of output plot
  plotName1 = new TString("deltaEta");
  // Change position & size of legend
  legend1 = new TLegend(0.65,0.55,0.99,0.95); 
  
  
  // Change only style here
  
  canvas1 = new TCanvas("plot", "plot", 800, 800);
  tools.GetHistArray(a_file, pluginName->Copy().Append(*pluginFolder), *histName1, a_hist1);
  tools.SetPlotFilling(a_hist1);
  tools.SetWeights(a_hist1, dataLumi);
  stack1 = new THStack("stack","stack");
  tools.FillStack(stack1, a_hist1);
  // If you want to set maximum by hand, else use function and scale
  // stack1->SetMaximum(30);
  stack1->SetMaximum(tools.GetMaximumValue(stack1, a_hist1[0]) *1.2);
  tools.FillLegend(legend1, a_hist1, "f");
  canvas1->Clear();
  stack1->Draw();
  if(a_hist1[0]){ 
    a_hist1[0]->Draw("same,e1");
  }  
  legend1->Draw("same");
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append(*outform));
  
  gPad->SetLogy(1);
  stack1->SetMinimum(0.01);
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append("_log").Append(*outform));
      
  delete histName1;
  delete plotName1;
  legend1->Delete();
  stack1->Delete();
  for(size_t iFile=0; iFile<nFiles; ++iFile){
    if(a_hist1[iFile])a_hist1[iFile]->Delete();
  }
  canvas1->Close();
  
  
  
  
  //++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++
  
  
  // Next few lines are only one to change for histo (except for individual style changes)
  
  // Give name of input histogram
  histName1 = new TString("h_deltaPhi");
  // Give base name of output plot
  plotName1 = new TString("deltaPhi");
  // Change position & size of legend
  legend1 = new TLegend(0.65,0.55,0.99,0.95); 
  
  
  // Change only style here
  
  canvas1 = new TCanvas("plot", "plot", 800, 800);
  tools.GetHistArray(a_file, pluginName->Copy().Append(*pluginFolder), *histName1, a_hist1);
  tools.SetPlotFilling(a_hist1);
  tools.SetWeights(a_hist1, dataLumi);
  stack1 = new THStack("stack","stack");
  tools.FillStack(stack1, a_hist1);
  // If you want to set maximum by hand, else use function and scale
  // stack1->SetMaximum(30);
  stack1->SetMaximum(tools.GetMaximumValue(stack1, a_hist1[0]) *1.2);
  tools.FillLegend(legend1, a_hist1, "f");
  canvas1->Clear();
  stack1->Draw();
  if(a_hist1[0]){ 
    a_hist1[0]->Draw("same,e1");
  }  
  legend1->Draw("same");
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append(*outform));
  
  gPad->SetLogy(1);
  stack1->SetMinimum(0.01);
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append("_log").Append(*outform));
      
  delete histName1;
  delete plotName1;
  legend1->Delete();
  stack1->Delete();
  for(size_t iFile=0; iFile<nFiles; ++iFile){
    if(a_hist1[iFile])a_hist1[iFile]->Delete();
  }
  canvas1->Close();
  
  
  
  
  //++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++
  
  
  // Next few lines are only one to change for histo (except for individual style changes)
  
  // Give name of input histogram
  histName1 = new TString("h_diMass");
  // Give base name of output plot
  plotName1 = new TString("diMass");
  // Change position & size of legend
  legend1 = new TLegend(0.65,0.55,0.99,0.95); 
  
  
  // Change only style here
  
  canvas1 = new TCanvas("plot", "plot", 800, 800);
  tools.GetHistArray(a_file, pluginName->Copy().Append(*pluginFolder), *histName1, a_hist1);
  tools.SetPlotFilling(a_hist1);
  tools.SetWeights(a_hist1, dataLumi);
  stack1 = new THStack("stack","stack");
  tools.FillStack(stack1, a_hist1);
  // If you want to set maximum by hand, else use function and scale
  // stack1->SetMaximum(30);
  stack1->SetMaximum(tools.GetMaximumValue(stack1, a_hist1[0]) *1.2);
  tools.FillLegend(legend1, a_hist1, "f");
  canvas1->Clear();
  stack1->Draw();
  if(a_hist1[0]){ 
    a_hist1[0]->Draw("same,e1");
  }  
  legend1->Draw("same");
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append(*outform));
  
  gPad->SetLogy(1);
  stack1->SetMinimum(0.01);
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append("_log").Append(*outform));
      
  delete histName1;
  delete plotName1;
  legend1->Delete();
  stack1->Delete();
  for(size_t iFile=0; iFile<nFiles; ++iFile){
    if(a_hist1[iFile])a_hist1[iFile]->Delete();
  }
  canvas1->Close();
  
  
  
  
  //++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++
  
  
  // Next few lines are only one to change for histo (except for individual style changes)
  
  // Give name of input histogram
  histName1 = new TString("h_diPt");
  // Give base name of output plot
  plotName1 = new TString("diPt");
  // Change position & size of legend
  legend1 = new TLegend(0.65,0.55,0.99,0.95); 
  
  
  // Change only style here
  
  canvas1 = new TCanvas("plot", "plot", 800, 800);
  tools.GetHistArray(a_file, pluginName->Copy().Append(*pluginFolder), *histName1, a_hist1);
  tools.SetPlotFilling(a_hist1);
  tools.SetWeights(a_hist1, dataLumi);
  stack1 = new THStack("stack","stack");
  tools.FillStack(stack1, a_hist1);
  // If you want to set maximum by hand, else use function and scale
  // stack1->SetMaximum(30);
  stack1->SetMaximum(tools.GetMaximumValue(stack1, a_hist1[0]) *1.2);
  tools.FillLegend(legend1, a_hist1, "f");
  canvas1->Clear();
  stack1->Draw();
  if(a_hist1[0]){ 
    a_hist1[0]->Draw("same,e1");
  }  
  legend1->Draw("same");
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append(*outform));
  
  gPad->SetLogy(1);
  stack1->SetMinimum(0.01);
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append("_log").Append(*outform));
      
  delete histName1;
  delete plotName1;
  legend1->Delete();
  stack1->Delete();
  for(size_t iFile=0; iFile<nFiles; ++iFile){
    if(a_hist1[iFile])a_hist1[iFile]->Delete();
  }
  canvas1->Close();
  
  
  
  
  //++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++
  
  
  // Next few lines are only one to change for histo (except for individual style changes)
  
  // Give name of input histogram
  histName1 = new TString("h_diY");
  // Give base name of output plot
  plotName1 = new TString("diY");
  // Change position & size of legend
  legend1 = new TLegend(0.65,0.55,0.99,0.95); 
  
  
  // Change only style here
  
  canvas1 = new TCanvas("plot", "plot", 800, 800);
  tools.GetHistArray(a_file, pluginName->Copy().Append(*pluginFolder), *histName1, a_hist1);
  tools.SetPlotFilling(a_hist1);
  tools.SetWeights(a_hist1, dataLumi);
  stack1 = new THStack("stack","stack");
  tools.FillStack(stack1, a_hist1);
  // If you want to set maximum by hand, else use function and scale
  // stack1->SetMaximum(30);
  stack1->SetMaximum(tools.GetMaximumValue(stack1, a_hist1[0]) *1.2);
  tools.FillLegend(legend1, a_hist1, "f");
  canvas1->Clear();
  stack1->Draw();
  if(a_hist1[0]){ 
    a_hist1[0]->Draw("same,e1");
  }  
  legend1->Draw("same");
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append(*outform));
  
  gPad->SetLogy(1);
  stack1->SetMinimum(0.01);
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append("_log").Append(*outform));
      
  delete histName1;
  delete plotName1;
  legend1->Delete();
  stack1->Delete();
  for(size_t iFile=0; iFile<nFiles; ++iFile){
    if(a_hist1[iFile])a_hist1[iFile]->Delete();
  }
  canvas1->Close();
  
  
  
  //++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++
  
  
  // Next few lines are only one to change for histo (except for individual style changes)
  
  // Give name of input histogram
  histName1 = new TString("h_etaHigh");
  // Give base name of output plot
  plotName1 = new TString("etaHigh");
  // Change position & size of legend
  legend1 = new TLegend(0.65,0.55,0.99,0.95); 
  
  
  // Change only style here
  
  canvas1 = new TCanvas("plot", "plot", 800, 800);
  tools.GetHistArray(a_file, pluginName->Copy().Append(*pluginFolder), *histName1, a_hist1);
  tools.SetPlotFilling(a_hist1);
  tools.SetWeights(a_hist1, dataLumi);
  stack1 = new THStack("stack","stack");
  tools.FillStack(stack1, a_hist1);
  // If you want to set maximum by hand, else use function and scale
  // stack1->SetMaximum(30);
  stack1->SetMaximum(tools.GetMaximumValue(stack1, a_hist1[0]) *1.2);
  tools.FillLegend(legend1, a_hist1, "f");
  canvas1->Clear();
  stack1->Draw();
  if(a_hist1[0]){ 
    a_hist1[0]->Draw("same,e1");
  }  
  legend1->Draw("same");
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append(*outform));
  
  gPad->SetLogy(1);
  stack1->SetMinimum(0.01);
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append("_log").Append(*outform));
      
  delete histName1;
  delete plotName1;
  legend1->Delete();
  stack1->Delete();
  for(size_t iFile=0; iFile<nFiles; ++iFile){
    if(a_hist1[iFile])a_hist1[iFile]->Delete();
  }
  canvas1->Close();
  
  
  
  
  //++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++
  
  
  // Next few lines are only one to change for histo (except for individual style changes)
  
  // Give name of input histogram
  histName1 = new TString("h_etaLow");
  // Give base name of output plot
  plotName1 = new TString("etaLow");
  // Change position & size of legend
  legend1 = new TLegend(0.65,0.55,0.99,0.95); 
  
  
  // Change only style here
  
  canvas1 = new TCanvas("plot", "plot", 800, 800);
  tools.GetHistArray(a_file, pluginName->Copy().Append(*pluginFolder), *histName1, a_hist1);
  tools.SetPlotFilling(a_hist1);
  tools.SetWeights(a_hist1, dataLumi);
  stack1 = new THStack("stack","stack");
  tools.FillStack(stack1, a_hist1);
  // If you want to set maximum by hand, else use function and scale
  // stack1->SetMaximum(30);
  stack1->SetMaximum(tools.GetMaximumValue(stack1, a_hist1[0]) *1.2);
  tools.FillLegend(legend1, a_hist1, "f");
  canvas1->Clear();
  stack1->Draw();
  if(a_hist1[0]){ 
    a_hist1[0]->Draw("same,e1");
  }  
  legend1->Draw("same");
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append(*outform));
  
  gPad->SetLogy(1);
  stack1->SetMinimum(0.01);
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append("_log").Append(*outform));
      
  delete histName1;
  delete plotName1;
  legend1->Delete();
  stack1->Delete();
  for(size_t iFile=0; iFile<nFiles; ++iFile){
    if(a_hist1[iFile])a_hist1[iFile]->Delete();
  }
  canvas1->Close();
  
  
  
  
  //++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++
  
  
  // Next few lines are only one to change for histo (except for individual style changes)
  
  // Give name of input histogram
  histName1 = new TString("h_etaLow");
  // Give name of second input histogram for addition
  histName2 = new TString("h_etaHigh");
  // Give base name of output plot
  plotName1 = new TString("etaBoth");
  // Change position & size of legend
  legend1 = new TLegend(0.65,0.55,0.99,0.95); 
  
  
  // Change only style here
  
  canvas1 = new TCanvas("plot", "plot", 800, 800);
  tools.GetHistArray(a_file, pluginName->Copy().Append(*pluginFolder), *histName1, a_hist1);
  tools.GetHistArray(a_file, pluginName->Copy().Append(*pluginFolder), *histName2, a_hist2);
  tools.AddHistArrays(a_hist1, a_hist2);
  tools.SetPlotFilling(a_hist1);
  tools.SetWeights(a_hist1, dataLumi);
  stack1 = new THStack("stack","stack");
  tools.FillStack(stack1, a_hist1);
  // If you want to set maximum by hand, else use function and scale
  // stack1->SetMaximum(30);
  stack1->SetMaximum(tools.GetMaximumValue(stack1, a_hist1[0]) *1.2);
  tools.FillLegend(legend1, a_hist1, "f");
  canvas1->Clear();
  stack1->SetTitle("pseudorapidity of both muons");
  stack1->Draw();
  if(a_hist1[0]){ 
    a_hist1[0]->Draw("same,e1");
  }  
  legend1->Draw("same");
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append(*outform));
  
  gPad->SetLogy(1);
  stack1->SetMinimum(0.01);
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append("_log").Append(*outform));
      
  delete histName1;
  delete histName2;
  delete plotName1;
  legend1->Delete();
  stack1->Delete();
  for(size_t iFile=0; iFile<nFiles; ++iFile){
    if(a_hist1[iFile])a_hist1[iFile]->Delete();
  }
  for(size_t iFile=0; iFile<nFiles; ++iFile){
    if(a_hist2[iFile])a_hist2[iFile]->Delete();
  }
  canvas1->Close();

  
  
  
  //++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++
  
  
  // Next few lines are only one to change for histo (except for individual style changes)
  
  // Give name of input histogram
  histName1 = new TString("h_ptHigh");
  // Give base name of output plot
  plotName1 = new TString("ptHigh");
  // Change position & size of legend
  legend1 = new TLegend(0.65,0.55,0.99,0.95); 
  
  
  // Change only style here
  
  canvas1 = new TCanvas("plot", "plot", 800, 800);
  tools.GetHistArray(a_file, pluginName->Copy().Append(*pluginFolder), *histName1, a_hist1);
  tools.SetPlotFilling(a_hist1);
  tools.SetWeights(a_hist1, dataLumi);
  stack1 = new THStack("stack","stack");
  tools.FillStack(stack1, a_hist1);
  // If you want to set maximum by hand, else use function and scale
  // stack1->SetMaximum(30);
  stack1->SetMaximum(tools.GetMaximumValue(stack1, a_hist1[0]) *1.2);
  tools.FillLegend(legend1, a_hist1, "f");
  canvas1->Clear();
  stack1->Draw();
  if(a_hist1[0]){ 
    a_hist1[0]->Draw("same,e1");
  }  
  legend1->Draw("same");
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append(*outform));
  
  gPad->SetLogy(1);
  stack1->SetMinimum(0.01);
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append("_log").Append(*outform));
      
  delete histName1;
  delete plotName1;
  legend1->Delete();
  stack1->Delete();
  for(size_t iFile=0; iFile<nFiles; ++iFile){
    if(a_hist1[iFile])a_hist1[iFile]->Delete();
  }
  canvas1->Close();
  
  
  

  //++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++
  
  
  // Next few lines are only one to change for histo (except for individual style changes)
  
  // Give name of input histogram
  histName1 = new TString("h_ptLow");
  // Give base name of output plot
  plotName1 = new TString("ptLow");
  // Change position & size of legend
  legend1 = new TLegend(0.65,0.55,0.99,0.95); 
  
  
  // Change only style here
  
  canvas1 = new TCanvas("plot", "plot", 800, 800);
  tools.GetHistArray(a_file, pluginName->Copy().Append(*pluginFolder), *histName1, a_hist1);
  tools.SetPlotFilling(a_hist1);
  tools.SetWeights(a_hist1, dataLumi);
  stack1 = new THStack("stack","stack");
  tools.FillStack(stack1, a_hist1);
  // If you want to set maximum by hand, else use function and scale
  // stack1->SetMaximum(30);
  stack1->SetMaximum(tools.GetMaximumValue(stack1, a_hist1[0]) *1.2);
  tools.FillLegend(legend1, a_hist1, "f");
  canvas1->Clear();
  stack1->Draw();
  if(a_hist1[0]){ 
    a_hist1[0]->Draw("same,e1");
  }  
  legend1->Draw("same");
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append(*outform));
  
  gPad->SetLogy(1);
  stack1->SetMinimum(0.01);
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append("_log").Append(*outform));
      
  delete histName1;
  delete plotName1;
  legend1->Delete();
  stack1->Delete();
  for(size_t iFile=0; iFile<nFiles; ++iFile){
    if(a_hist1[iFile])a_hist1[iFile]->Delete();
  }
  canvas1->Close();
  
  
  
  
  //++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++
  
  
  // Next few lines are only one to change for histo (except for individual style changes)
  
  // Give name of input histogram
  histName1 = new TString("h_ptLow");
  // Give name of second input histogram for addition
  histName2 = new TString("h_ptHigh");
  // Give base name of output plot
  plotName1 = new TString("ptBoth");
  // Change position & size of legend
  legend1 = new TLegend(0.65,0.55,0.99,0.95); 
  
  
  // Change only style here
  
  canvas1 = new TCanvas("plot", "plot", 800, 800);
  tools.GetHistArray(a_file, pluginName->Copy().Append(*pluginFolder), *histName1, a_hist1);
  tools.GetHistArray(a_file, pluginName->Copy().Append(*pluginFolder), *histName2, a_hist2);
  tools.AddHistArrays(a_hist1, a_hist2);
  tools.SetPlotFilling(a_hist1);
  tools.SetWeights(a_hist1, dataLumi);
  stack1 = new THStack("stack","stack");
  tools.FillStack(stack1, a_hist1);
  // If you want to set maximum by hand, else use function and scale
  // stack1->SetMaximum(30);
  stack1->SetMaximum(tools.GetMaximumValue(stack1, a_hist1[0]) *1.2);
  tools.FillLegend(legend1, a_hist1, "f");
  canvas1->Clear();
  stack1->SetTitle("transverse momentum p_{t} of both muons");
  stack1->Draw();
  if(a_hist1[0]){ 
    a_hist1[0]->Draw("same,e1");
  }  
  legend1->Draw("same");
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append(*outform));
  
  gPad->SetLogy(1);
  stack1->SetMinimum(0.01);
  canvas1->Update();
  canvas1->Print(outpath->Copy().Append(*plotName1).Append(pluginSuffix).Append("_log").Append(*outform));
      
  delete histName1;
  delete histName2;
  delete plotName1;
  legend1->Delete();
  stack1->Delete();
  for(size_t iFile=0; iFile<nFiles; ++iFile){
    if(a_hist1[iFile])a_hist1[iFile]->Delete();
  }
  for(size_t iFile=0; iFile<nFiles; ++iFile){
    if(a_hist2[iFile])a_hist2[iFile]->Delete();
  }
  canvas1->Close();

  
  

  
  
  
  
  //++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++
  
  
  // again, no changes here
  
  delete pluginFolder;
  delete pluginName;
  
  for(size_t iFile=0; iFile<nFiles; ++iFile){
    if(a_file[iFile])a_file[iFile]->Close();
  }
  
  //delete inpath;
  //delete outpath;
  //delete outform;
  
}
