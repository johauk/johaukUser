// Macro for plotting a stack of Z->mumu histograms sorted by quark origin flavour
// root -l
// .L GenParticleOccurencePlots.C++
// GenParticleOccurencePlots()        // empty to define pluginName and plotName completely by hand
// GenParticleOccurencePlots("bla")   // name to define pluginName and plotName via an appended suffix "bla"


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
const TString* outpath = new TString("$CMSSW_BASE/src/ZmumuAnalysis/Configuration/macros/plots/Generator_");
const TString* outform = new TString(".png");
//const TString* outform = new TString(".eps");

const size_t nFlavour(3 +1); // start all arrays at [1], to use already present methods


void GenParticleOccurencePlots(TString pluginSuffix = ""){
  
  
  // Specify all input files
  TFile* file;
  //file = new TFile(inpath->Copy().Append("mc/genParticleOccurence.root"));
  file = new TFile(inpath->Copy().Append("genParticleOccurenceSelection.root"));
  
  //Specify plugin name
  TString* pluginName(0);
  pluginName = new TString("GenParticleOccurenceAnalyzer");
  
  TString* a_flavour[nFlavour];
  for(size_t iFlavour=0; iFlavour<nFlavour; ++iFlavour) a_flavour[iFlavour]=0;
  a_flavour[1] = new TString("Uds");
  a_flavour[2] = new TString("C");
  a_flavour[3] = new TString("B");
  
  
  TString* pluginFolder(0);
  pluginFolder = new TString("ParticleOccurence");
  
  
  
  
  //++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++
  
  // Do not touch this area
  
  
  if(!pluginFolder->IsNull())pluginFolder->Append("/");
  
  TString* a_baseString[nFlavour];
  for(size_t iFlavour=0; iFlavour<nFlavour; ++iFlavour) a_baseString[iFlavour]=0;
  
  for(size_t iFlavour=0; iFlavour<nFlavour; ++iFlavour){  // do not use array [0]
    if(!a_flavour[iFlavour])continue;
    const TString flavour(*a_flavour[iFlavour]);
    a_baseString[iFlavour] = new TString(pluginName->Copy().Append(flavour).Append(pluginSuffix).Append("/").Append(*pluginFolder));
  }
  
  
  //++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++
  
  
  
  // Do not touch this area
  
  
  
  HistogramTools tools;
  tools.SetDefaultStyle();
  
  TCanvas* canvas1(0);

  TLegend* legend1(0); 
   
  TH1F* a_hist1[nFlavour];  // do not use array [0]
  for(size_t iFlavour=0; iFlavour<nFlavour; ++iFlavour) a_hist1[iFlavour]=0;
  
  THStack* stack1(0);
  
  TString* histName1(0);
  
  TString* plotName1(0);
  
  //++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++
  
  
  // Next few lines are only one to change for histo (except for individual style changes)
  
  // Give name of input histogram
  histName1 = new TString("h_partOccurence");
  // Give base name of output plot
  plotName1 = new TString("bQuark_mult");
  // Change position & size of legend
  legend1 = new TLegend(0.85,0.75,0.99,0.95); 
  
  
  // Change only style here
  
  canvas1 = new TCanvas("plot", "plot", 800, 800);
  tools.GetHistArraySameFile(file, a_baseString, *histName1, a_hist1);
  tools.SetPlotFilling(a_hist1, nFlavour);
  stack1 = new THStack("stack","stack");
  tools.FillStack(stack1, a_hist1, nFlavour);
  tools.FillLegendGenerator(legend1, a_hist1, "f");
  canvas1->Clear();
  stack1->Draw();
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
  for(size_t iHist=0; iHist<nFlavour; ++iHist){
    if(a_hist1[iHist])a_hist1[iHist]->Delete();
  }
  canvas1->Close();
  
  
  
  //++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++
  
  
  // again, no changes here
  
  
  for(size_t iHist=0; iHist<nFlavour; ++iHist){
    if(a_flavour[iHist])delete a_flavour[iHist];
  }
  
  delete pluginFolder;
  delete pluginName;
  
  file->Close();
  
  //delete inpath;
  //delete outpath;
  //delete outform;
  
}
