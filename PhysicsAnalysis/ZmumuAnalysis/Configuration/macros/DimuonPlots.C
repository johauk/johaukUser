// root -l
// .L DimuonPlots.C++
// DimuonPlots()

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

const TString* inpath  = new TString("/afs/naf.desy.de/user/j/johauk/cms/CMSSW_3_6_1_patch4/src/ZmumuAnalysis/Configuration/hists/");
const TString* outpath = new TString("/afs/naf.desy.de/user/j/johauk/cms/CMSSW_3_6_1_patch4/src/ZmumuAnalysis/Configuration/macros/plots/Dimuon_");
//const TString* outform = new TString(".png");
const TString* outform = new TString(".eps");
// number of files used
const size_t nFiles = 12;

// Integrated lumi of taken data for normalising MC in pb-1
const Double_t dataLumi(0.2112);


void DimuonPlots(){
  HistogramTools tools;
  tools.SetDefaultStyle();
  
  TFile* files[nFiles];
  files[0]=new TFile(inpath->Copy().Append("data/ichep_all.root"));
  files[1]=new TFile(inpath->Copy().Append("mc/zmumu.root"));
  files[2]=new TFile(inpath->Copy().Append("mc/zz.root"));
  files[3]=new TFile(inpath->Copy().Append("mc/wz.root"));
  files[4]=new TFile(inpath->Copy().Append("mc/ww.root"));
  files[5]=new TFile(inpath->Copy().Append("mc/wmunu.root"));
  files[6]=new TFile(inpath->Copy().Append("mc/ztautau.root"));
  files[7]=new TFile(inpath->Copy().Append("mc/singleTopT.root"));
  files[8]=new TFile(inpath->Copy().Append("mc/singleTopTW.root"));
  files[9]=new TFile(inpath->Copy().Append("mc/singleTopS.root"));
  files[10]=new TFile(inpath->Copy().Append("mc/ttbar.root"));
  files[11]=new TFile(inpath->Copy().Append("mc/inclusiveMu15.root"));
  
  
  // make canvas
  TCanvas* Canvas = new TCanvas("plot", "plot", 800, 800);

  TLegend* legFilled = new TLegend(0.65,0.55,0.99,0.95);  
  
  
  
  // prepare and print histos
  
  gPad->SetLogy(1);
  
  TH1F* diMuMass1[nFiles];
  //tools.GetHistArray(files, "DiMuonAnalyzer2/OppositeCharge/", "h_diMass", diMuMass1, nFiles);
  tools.GetHistArray(files, "DiMuonAnalyzer2/OppositeCharge/", "h_diMass", diMuMass1);
//  for(size_t i=0; i<nFiles; ++i){
//    if(diMuMass1[i]) diMuMass1[i]->Rebin(3);
//    std::cout<<"\nTEST 2b\n";
//  }
  //tools.SetPlotFilling(diMuMass1, nFiles);
  tools.SetPlotFilling(diMuMass1);
  //tools.SetWeights(diMuMass1, dataLumi, nFiles);
  tools.SetWeights(diMuMass1, dataLumi);
  THStack* stack_mass1 = new THStack("s_diMuMass1","Reconstructed Dimuon Mass");
  stack_mass1->SetMaximum(30);
  //tools.FillStack(stack_mass1, diMuMass1, nFiles);
  tools.FillStack(stack_mass1, diMuMass1);
  tools.FillLegend(legFilled, diMuMass1, "f");
  Canvas->Clear();
  stack_mass1->Draw();
  if(diMuMass1[0]){ 
    diMuMass1[0]->Draw("same,e1");
//    tools.SetAxisTitle(diMuMass1[0],"x","M_{top} [GeV]" , 0.04, 1.1, 0.035);
//    tools.SetAxisTitle(diMuMass1[0],"y","N"             , 0.04, 1.3, 0.035);      
  }  
//  tools.SetAxisTitle(stack_mass1,"x","M_{top} [GeV]" , 0.04, 1.1, 0.035);
//  tools.SetAxisTitle(stack_mass1,"y","N"             , 0.04, 1.3, 0.035);  
  legFilled->Draw("same");
  Canvas->Update();
  Canvas->Print(outpath->Copy().Append("diMuMass_1").Append(*outform));
  
  
/*  
  
  
  TH1F* topmass1[nFiles];
  tools.GetHistArray(files, "analyzeKinSolution1/", "kin_TopMass", topmass1, nFiles);
  for(size_t i=0; i<nFiles; ++i){
    if(topmass1[i]) topmass1[i]->Rebin(3);    
  }  
  tools.SetPlotFilling(topmass1, nFiles);
  tools.SetWeights(topmass1, nFiles);  
  THStack* stack_mass1 = new THStack("stack_mass","Reconstructed Top Mass");
  stack_mass1->SetMaximum(20);
  tools.FillStack(stack_mass1, topmass1, nFiles);  
  tools.FillLegend(legFilled, topmass1, "f");
  Canvas->Clear();
  stack_mass1->Draw();
  if(topmass1[0]){ 
    topmass1[0]->Draw("same,e1");
    tools.SetAxisTitle(topmass1[0],"x","M_{top} [GeV]" , 0.04, 1.1, 0.035);
    tools.SetAxisTitle(topmass1[0],"y","N"             , 0.04, 1.3, 0.035);      
  }  
  tools.SetAxisTitle(stack_mass1,"x","M_{top} [GeV]" , 0.04, 1.1, 0.035);
  tools.SetAxisTitle(stack_mass1,"y","N"             , 0.04, 1.3, 0.035);  
  legFilled->Draw("same");
  Canvas->Update();
  Canvas->Print(outpath->Copy().Append("topMass_1").Append(*outform));


  TH1F* topmass2[nFiles];
  tools.GetHistArray(files, "analyzeKinSolution2/", "kin_TopMass", topmass2, nFiles);
  for(size_t i=0; i<nFiles; ++i){
    if(topmass2[i]) topmass2[i]->Rebin(3);    
  }  
  tools.SetPlotFilling(topmass2, nFiles);
  tools.SetWeights(topmass2, nFiles);  
  THStack* stack_mass2 = new THStack("stack_mass","Reconstructed Top Mass");
  stack_mass2->SetMaximum(15);
  tools.FillStack(stack_mass2, topmass2, nFiles);
  tools.FillLegend(legFilled, topmass2, "f");
  Canvas->Clear();
  stack_mass2->Draw();
  tools.SetAxisTitle(stack_mass2,"x","M_{top} [GeV]" , 0.04, 1.1, 0.035);
  tools.SetAxisTitle(stack_mass2,"y","N"             , 0.04, 1.3, 0.035);
  if(topmass2[0]){ 
    topmass2[0]->Draw("same,e1");
    tools.SetAxisTitle(topmass2[0],"x","M_{top} [GeV]" , 0.04, 1.1, 0.035);
    tools.SetAxisTitle(topmass2[0],"y","N"             , 0.04, 1.3, 0.035);      
  } 
  legFilled->Draw("same");
  Canvas->Update();
  Canvas->Print(outpath->Copy().Append("topMass_2").Append(*outform));


  gPad->SetLogy(1);

  TH1F* njets1[nFiles];
  tools.GetHistArray(files, "analyzeJets1/", "N_nJets", njets1, nFiles);
  tools.SetPlotFilling(njets1, nFiles);
  tools.SetWeights(njets1, nFiles);  
  THStack* stack_njets1 = new THStack("stack_njets","N_{Jets} before Selection");
  //stack_njets1->SetMaximum(15000);
  tools.FillStack(stack_njets1, njets1, nFiles);
  tools.FillLegend(legFilled, njets1, "f");
  Canvas->Clear();
  stack_njets1->Draw();
  tools.SetAxisTitle(stack_njets1,"x","N_{Jets}" , 0.04, 1.1, 0.035);
  tools.SetAxisTitle(stack_njets1,"y","N_{evts}" , 0.04, 1.3, 0.035);
  if(njets1[0]){ 
    njets1[0]->Draw("same,e1");
    tools.SetAxisTitle(njets1[0],"x","N_{Jets}" , 0.04, 1.1, 0.035);
    tools.SetAxisTitle(njets1[0],"y","N_{evts}" , 0.04, 1.3, 0.035);   
  } 
  legFilled->Draw("same");
  Canvas->Update();
  Canvas->Print(outpath->Copy().Append("njets_1").Append(*outform));
   
  TH1F* njets2[nFiles];
  tools.GetHistArray(files, "analyzeJets2/", "N_nJets", njets2, nFiles);
  tools.SetPlotFilling(njets2, nFiles);
  tools.SetWeights(njets2, nFiles);  
  THStack* stack_njets2 = new THStack("stack_njets2","N_{Jets} after Muon Selection");
  //stack_njets2->SetMaximum(14000);
  tools.FillStack(stack_njets2, njets2, nFiles);
  tools.FillLegend(legFilled, njets2, "f");  
  Canvas->Clear();
  stack_njets2->Draw(); 
  tools.SetAxisTitle(stack_njets2,"x","N_{Jets}" , 0.04, 1.1, 0.035);
  tools.SetAxisTitle(stack_njets2,"y","N_{evts}" , 0.04, 1.3, 0.035);
  if(njets2[0]){ 
    njets2[0]->Draw("same,e1");
    tools.SetAxisTitle(njets2[0],"x","N_{Jets}" , 0.04, 1.1, 0.035);
    tools.SetAxisTitle(njets2[0],"y","N_{evts}" , 0.04, 1.3, 0.035);   
  } 
  legFilled->Draw("same");
  Canvas->Update();
  Canvas->Print(outpath->Copy().Append("njets_2").Append(*outform));
  
  TH1F* njets3[nFiles];
  tools.GetHistArray(files, "analyzeJets3/", "N_nJets", njets3, nFiles);
  tools.SetPlotFilling(njets3, nFiles);
  tools.SetWeights(njets3, nFiles);  
  THStack* stack_njets3 = new THStack("stack_njets3","N_{Jets} after Z-Veto");
  //stack_njets3->SetMaximum(300);
  tools.FillStack(stack_njets3, njets3, nFiles);
  tools.FillLegend(legFilled, njets3, "f");    
  Canvas->Clear();
  stack_njets3->Draw();
  tools.SetAxisTitle(stack_njets3,"x","N_{Jets}" , 0.04, 1.1, 0.035);
  tools.SetAxisTitle(stack_njets3,"y","N_{evts}" , 0.04, 1.3, 0.035);
  if(njets3[0]){ 
    njets3[0]->Draw("same,e1");
    tools.SetAxisTitle(njets3[0],"x","N_{Jets}" , 0.04, 1.1, 0.035);
    tools.SetAxisTitle(njets3[0],"y","N_{evts}" , 0.04, 1.3, 0.035);   
  } 
  legFilled->Draw("same");
  Canvas->Update();
  Canvas->Print(outpath->Copy().Append("njets_3").Append(*outform));   


  TH1F* njets4[nFiles];
  tools.GetHistArray(files, "analyzeJets4/", "N_nJets", njets4, nFiles);
  tools.SetPlotFilling(njets4, nFiles);
  tools.SetWeights(njets4, nFiles);  
  THStack* stack_njets4 = new THStack("stack_njets4","N_{Jets} after Full Selection with b-tag");
  //stack_njets4->SetMaximum(30);
  tools.FillStack(stack_njets4, njets4, nFiles);
  tools.FillLegend(legFilled, njets4, "f");    
  Canvas->Clear();
  stack_njets4->Draw();
  tools.SetAxisTitle(stack_njets4,"x","N_{Jets}" , 0.04, 1.1, 0.035);
  tools.SetAxisTitle(stack_njets4,"y","N_{evts}" , 0.04, 1.3, 0.035);
  if(njets4[0]){ 
    njets4[0]->Draw("same,e1");
    tools.SetAxisTitle(njets4[0],"x","N_{Jets}" , 0.04, 1.1, 0.035);
    tools.SetAxisTitle(njets4[0],"y","N_{evts}" , 0.04, 1.3, 0.035);   
  } 
  legFilled->Draw("same");
  Canvas->Update();
  Canvas->Print(outpath->Copy().Append("njets_4").Append(*outform));  

  gPad->SetLogx(1);

  TH1F* dilepmass1[nFiles];
  tools.GetHistArray(files, "analyzeMuonPair0/", "dimassRC", dilepmass1, nFiles);
  tools.SetPlotFilling(dilepmass1, nFiles);   
  tools.SetWeights(dilepmass1, nFiles);
  THStack* stack_dilepmass1 = new THStack("stack_dilepmass1","#mu#mu-Mass before muon selection");
  tools.FillStack(stack_dilepmass1, dilepmass1, nFiles);
  tools.FillLegend(legFilled, dilepmass1, "f");    
  Canvas->Clear();
  stack_dilepmass1->Draw();  
  stack_dilepmass1->GetXaxis()->SetMoreLogLabels(kTRUE);
  tools.SetAxisTitle(stack_dilepmass1,"x","M_{#mu#mu} [GeV]" , 0.04, 1.1, 0.035);
  tools.SetAxisTitle(stack_dilepmass1,"y","N"                , 0.04, 1.3, 0.035);  
  if(dilepmass1[0]){ 
    dilepmass1[0]->Draw("same,e1");
    tools.SetAxisTitle(dilepmass1[0],"x","M_{#mu#mu} [GeV]" , 0.04, 1.1, 0.035);
    tools.SetAxisTitle(dilepmass1[0],"y","N"                , 0.04, 1.3, 0.035);   
  } 
  legFilled->Draw("same");
  Canvas->Print(outpath->Copy().Append("dilepMass_1").Append(*outform));

  TLine* line = new TLine();
  line->SetLineWidth(4);
  line->SetLineStyle(1);
  line->SetLineColor(1);

  TH1F* dilepmass2[nFiles];
  tools.GetHistArray(files, "analyzeMuonPair1/", "dimassRC", dilepmass2, nFiles);
  tools.SetPlotFilling(dilepmass2, nFiles);   
  tools.SetWeights(dilepmass2, nFiles);
  THStack* stack_dilepmass2 = new THStack("stack_dilepmass","#mu#mu-Mass after muon selection");
  tools.FillStack(stack_dilepmass2, dilepmass2, nFiles);
  tools.FillLegend(legFilled, dilepmass2, "f");   
  Canvas->Clear();
  stack_dilepmass2->Draw();  
  stack_dilepmass2->GetXaxis()->SetMoreLogLabels(kTRUE);
  tools.SetAxisTitle(stack_dilepmass2,"x","M_{#mu#mu} [GeV]" , 0.04, 1.1, 0.035);
  tools.SetAxisTitle(stack_dilepmass2,"y","N"                , 0.04, 1.3, 0.035);
  line-> DrawLine( 20,0, 20,10000);
  line-> DrawLine( 76,0, 76,10000);
  line-> DrawLine(106,0,106,10000);  
  if(dilepmass2[0]){ 
    dilepmass2[0]->Draw("same,e1");
    tools.SetAxisTitle(dilepmass2[0],"x","M_{#mu#mu} [GeV]" , 0.04, 1.1, 0.035);
    tools.SetAxisTitle(dilepmass2[0],"y","N"                , 0.04, 1.3, 0.035);   
  }  
  legFilled->Draw("same");
  Canvas->Print(outpath->Copy().Append("dilepMass_2").Append(*outform));
  
  
  TH1F* dilepmassWC1[nFiles];
  tools.GetHistArray(files, "analyzeMuonPair0/", "dimassWC", dilepmassWC1, nFiles);
  tools.SetPlotFilling(dilepmassWC1, nFiles);   
  tools.SetWeights(dilepmassWC1, nFiles);
  THStack* stack_dilepmassWC1 = new THStack("stack_dilepmassWC1","wrong charge #mu#mu-Mass before muon selection");
  tools.FillStack(stack_dilepmassWC1, dilepmassWC1, nFiles);   
  Canvas->Clear();
  stack_dilepmassWC1->Draw();  
  stack_dilepmassWC1->GetXaxis()->SetMoreLogLabels(kTRUE);
  tools.SetAxisTitle(stack_dilepmassWC1,"x","M_{#mu#mu} [GeV]" , 0.04, 1.1, 0.035);
  tools.SetAxisTitle(stack_dilepmassWC1,"y","N"                , 0.04, 1.3, 0.035);  
  if(dilepmassWC1[0]){ 
    dilepmassWC1[0]->Draw("same,e1");
    tools.SetAxisTitle(dilepmassWC1[0],"x","M_{#mu#mu} [GeV]" , 0.04, 1.1, 0.035);
    tools.SetAxisTitle(dilepmassWC1[0],"y","N"                , 0.04, 1.3, 0.035);   
  }  
  Canvas->Print(outpath->Copy().Append("dilepMassWC_1").Append(*outform));

  TH1F* dilepmassWC2[nFiles];
  tools.GetHistArray(files, "analyzeMuonPair1/", "dimassWC", dilepmassWC2, nFiles);
  tools.SetPlotFilling(dilepmassWC2, nFiles);   
  tools.SetWeights(dilepmassWC2, nFiles);
  THStack* stack_dilepmassWC2 = new THStack("stack_dilepmass","wrong charge #mu#mu-Mass after muon selection");
  tools.FillStack(stack_dilepmassWC2, dilepmassWC2, nFiles);  
  Canvas->Clear();
  stack_dilepmassWC2->Draw();  
  stack_dilepmassWC2->GetXaxis()->SetMoreLogLabels(kTRUE);
  tools.SetAxisTitle(stack_dilepmassWC2,"x","M_{#mu#mu} [GeV]" , 0.04, 1.1, 0.035);
  tools.SetAxisTitle(stack_dilepmassWC2,"y","N"                , 0.04, 1.3, 0.035);
  line-> DrawLine( 20,0, 20,10000);
  line-> DrawLine( 76,0, 76,10000);
  line-> DrawLine(106,0,106,10000);  
  if(dilepmassWC2[0]){ 
    dilepmassWC2[0]->Draw("same,e1");
    tools.SetAxisTitle(dilepmassWC2[0],"x","M_{#mu#mu} [GeV]" , 0.04, 1.1, 0.035);
    tools.SetAxisTitle(dilepmassWC2[0],"y","N"                , 0.04, 1.3, 0.035);   
  }  
  Canvas->Print(outpath->Copy().Append("dilepMassWC_2").Append(*outform));  
*/  
  
  
  Canvas->Close();  
/*    
  TPostScript ps (TString("TTbarPlots").Append(".ps"), 111);
  TCanvas* CanvasPs = new TCanvas("ttbar", "Jet Multiplicity", 1000, 1200);  
  CanvasPs->Clear(); 
  CanvasPs->Divide(2,2);  
  CanvasPs->cd(1); 
  gPad->SetLogy(1);
  stack_njets1->Draw();
  if(njets1[0]) njets1[0]->Draw("same,e1");   
  CanvasPs->cd(2); 
  gPad->SetLogy(1);  
  stack_njets2->Draw(); 
  if(njets2[0]) njets2[0]->Draw("same,e1");   
  CanvasPs->cd(3); 
  gPad->SetLogy(1);  
  stack_njets3->Draw(); 
  if(njets3[0]) njets3[0]->Draw("same,e1");   
  CanvasPs->cd(4);
  gPad->SetLogy(1);   
  stack_njets4->Draw();
  if(njets4[0]) njets4[0]->Draw("same,e1");  
  CanvasPs->Update();     
  
  CanvasPs->Clear(); 
  CanvasPs->Divide(2,2);  
  CanvasPs->cd(1); 
  gPad->SetLogx(1);
  gPad->SetLogy(1);  
  stack_dilepmass1->Draw();
  if(dilepmass1[0]) dilepmass1[0]->Draw("same,e1");  ; 
  CanvasPs->cd(2); 
  gPad->SetLogx(1); 
  gPad->SetLogy(1);   
  stack_dilepmass2->Draw(); 
  if(dilepmass2[0]) dilepmass2[0]->Draw("same,e1");    
  CanvasPs->cd(3);   
  stack_mass1->Draw(); 
  if(topmass1[0]) topmass1[0]->Draw("same,e1");   
  CanvasPs->cd(4);   
  stack_mass2->Draw();
  if(topmass2[0]) topmass2[0]->Draw("same,e1");  
  CanvasPs->Update();
  
  gPad->SetLogx(1);
      
  CanvasPs->Clear(); 
  CanvasPs->Divide(1,2);     
  CanvasPs->cd(1); 
  stack_dilepmass2->SetMaximum(10);  
  stack_dilepmass2->Draw();   
  CanvasPs->cd(2);     
  stack_dilepmassWC2->Draw();   
  CanvasPs->Update();           
  CanvasPs->Close();
  ps.Close();  
*/
/*  
  // calculate signal to background ratio
  double entries[nFiles] = {0,0,0,0,0,0,0,0,0,0}; //here entries[0] is used for bg sum
  for(size_t i=1; i<nFiles; ++i){
    if(diMuMass1[i]) entries[i] = diMuMass1[i]->Integral();
    if(i>=3) entries[0]+=entries[i];
  }
  cout << "N signal       = "<< entries[1] << endl;
  cout << "N ttbar tau mu = "<< entries[2] << endl;
  cout << "N ttbar bg     = "<< entries[3] << endl;
  cout << "N Z -> ee      = "<< entries[4] << endl;
  cout << "N Z -> mumu    = "<< entries[5] << endl;
  cout << "N Z -> tautau  = "<< entries[6] << endl;  
  cout << "N W + jets     = "<< entries[7] << endl;    
  cout << "N WW           = "<< entries[8] << endl;
  cout << "N WZ           = "<< entries[9] << endl;
  cout << "N ZZ           = "<< entries[10] << endl;
  cout << "N QCD          = "<< entries[11] << endl;
  cout << "signal to background = "<< (entries[1]+entries[2])/entries[0] << endl;
  cout << "significance = " << (entries[1]+entries[2])/TMath::Sqrt(entries[1]+entries[2]+entries[0]) << " sigma" << endl;
  

*/
}
