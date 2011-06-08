// root -l
// .L JetPlots.C++
// JetPlots()        // empty to define pluginName and plotName completely by hand
// JetPlots("bla")   // name to define pluginName and plotName via an appended suffix "bla"


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
const TString* outpath = new TString("$CMSSW_BASE/src/ZmumuAnalysis/Configuration/macros/plots/Jet_");
const TString* outform = new TString(".png");
//const TString* outform = new TString(".eps");
// number of files used
const size_t nFiles = 12;

// Integrated lumi of taken data for normalising MC in pb-1
const Double_t dataLumi(191.0);


void JetPlots(TString pluginSuffix = ""){
  
  
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
  a_file[9]=new TFile(inpath->Copy().Append("mc/singleTopTw.root"));
  a_file[10]=new TFile(inpath->Copy().Append("mc/ttbar.root"));
  a_file[11]=new TFile(inpath->Copy().Append("mc/qcd.root"));
  
  //Specify plugin name
  TString* pluginName(0);
  pluginName = new TString("JetAnalyzer");
  
  TString* pluginFolder(0);
  pluginFolder = new TString("");
  
  
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
  
  THStack* stack1(0);
  
  TString* histName1(0);
  
  TString* plotName1(0);
  
  //++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++
  
  
  // Next few lines are only one to change for histo (except for individual style changes)
  
  // Give name of input histogram
  histName1 = new TString("EventProperties/h_nJet");
  // Give base name of output plot
  plotName1 = new TString("nJet");
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
  histName1 = new TString("JetProperties/h_bDiscriminatorSvhe");
  // Give base name of output plot
  plotName1 = new TString("bDiscriminatorSvhe");
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
  histName1 = new TString("JetProperties/h_bDiscriminatorTche");
  // Give base name of output plot
  plotName1 = new TString("bDiscriminatorTche");
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
  histName1 = new TString("JetProperties/h_chargedEmFrac");
  // Give base name of output plot
  plotName1 = new TString("chargedEmFrac");
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
  histName1 = new TString("JetProperties/h_chargedHadFrac");
  // Give base name of output plot
  plotName1 = new TString("chargedHadFrac");
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
  histName1 = new TString("JetProperties/h_chargedMult");
  // Give base name of output plot
  plotName1 = new TString("chargedMult");
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
  histName1 = new TString("JetProperties/h_eta");
  // Give base name of output plot
  plotName1 = new TString("eta");
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
  histName1 = new TString("JetProperties/h_nConstituent");
  // Give base name of output plot
  plotName1 = new TString("nConstituent");
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
  histName1 = new TString("JetProperties/h_neutralEmFrac");
  // Give base name of output plot
  plotName1 = new TString("neutralEmFrac");
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
  histName1 = new TString("JetProperties/h_neutralHadFrac");
  // Give base name of output plot
  plotName1 = new TString("neutralHadFrac");
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
  histName1 = new TString("JetProperties/h_pt");
  // Give base name of output plot
  plotName1 = new TString("pt");
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
