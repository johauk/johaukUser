#include <iostream>

#include "TROOT.h"
#include "TFile.h"
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "THStack.h"
#include "TAxis.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TColor.h"
#include "TStyle.h"

// default style for plots

class HistogramTools{

public:
  HistogramTools();
  ~HistogramTools();

  void AddHistArrays(TH1F* hist1[],   TH1F* hist2[], size_t n = defaultNumberOfFiles);
  void ClearPlotFilling(TH1* hist[],  size_t n = defaultNumberOfFiles);
  void Divide(TH1* hist, Double_t divisor);
  void Divide(TH2* hist, Double_t divisor);
//  void DrawHistArray(TH1* hist[], size_t n, Option_t* opt = ""); 
  void FillStack(THStack* stck, TH1F* hist[], size_t n = defaultNumberOfFiles); 
  void GetHistArray(TFile* files[], const TString path, const TString name, TH1F* hist[], size_t n = defaultNumberOfFiles);
  TH1F GetHistSum(TH1F* hist[], size_t n = defaultNumberOfFiles);
  void Normalize(TH1* hist, Double_t norm);  
  void Normalize(TH1* hist[], Double_t norm, size_t n = defaultNumberOfFiles);
  void SetAxisTitle(TH1* hist, Option_t* axis, const char* title, Float_t titlesize, Float_t offset, Float_t labelsize);
  void SetAxisTitle(TH1* hist[], Option_t* axis, const char* title, Float_t titlesize, Float_t offset, Float_t labelsize, size_t n = defaultNumberOfFiles);  
  void SetAxisTitle(THStack* stck, Option_t* axis, const char* title, Float_t titlesize, Float_t offset, Float_t labelsize);   
  void SetDefaultStyle();
  void SetHistBinomialErrors(TH1F* hist, Double_t norm);
  void SetHistBinomialErrors(TH2F* hist, Double_t norm);  
//  void SetMyPalette(const char* mypalette);  
  void SetPlotLine(TH1* hist, Color_t color, Width_t width, Style_t style=1);
  void SetMinimumZero(TH1* hist[], size_t n = defaultNumberOfFiles);
  void SetTitle(TH1* hist[], const char* title, size_t n = defaultNumberOfFiles);
    
  // this methods refer to the currently used files only
  void FillLegend(TLegend* leg, TH1F* hist[], Option_t* opt);
  void SetPlotFilling(TH1F* hist[], size_t n = defaultNumberOfFiles);   
  void SetPlotLines(TH1F* hist[], size_t n = defaultNumberOfFiles);
  void SetWeights(TH1F* hist[], Double_t, size_t n = defaultNumberOfFiles); 
  
  
  TColor* stackColors[12];
  static const size_t defaultNumberOfFiles = 12;
};





HistogramTools::HistogramTools()
{
}



HistogramTools::~HistogramTools()
{
}



void HistogramTools::AddHistArrays(TH1F* hist1[], TH1F* hist2[], size_t n){
  for(size_t i=0; i<n; ++i){
    if(!hist1[i] || !hist2[i]) continue;
    hist1[i]->Add(hist2[i]); 
  }
  return;  
}



void HistogramTools::ClearPlotFilling(TH1* hist[], size_t n)
{
  for(size_t i=0; i<n; ++i){
    if(!hist[i]) continue;
    hist[i]->SetFillColor(0); 
  }
  return;
}



void HistogramTools::Divide(TH1* hist, Double_t divisor)
{
  for(Int_t i=1; i<=hist->GetNbinsX(); ++i){
    //hist->SetBinError(i,hist->GetBinError(i)/divisor);            //use this line wisely! not for linear tranformations of ratios!!!
    hist->SetBinContent(i,hist->GetBinContent(i)/divisor); 
  }
  return;
}



void HistogramTools::Divide(TH2* hist, Double_t divisor)
{
  for(Int_t i=1; i<=hist->GetNbinsX(); ++i){
    for(Int_t j=1; j<=hist->GetNbinsY(); ++j){
      //hist->SetBinError(i,j,hist->GetBinError(i,j)/divisor);      //use this line wisely! not for linear tranformations of ratios!!!
      hist->SetBinContent(i,j,hist->GetBinContent(i,j)/divisor);
    }
  }
  return;
}


/*
void HistogramTools::DrawHistArray(TH1* hist[], size_t n, Option_t* opt)
{
  
  Double_t max=0; 
  Int_t maxHist=0;
   
  for(size_t i=0; i<n; ++i){ 
    if(!hist[i]) continue;  
    if(hist[i]->GetMaximum()>max){
      max = hist[i]->GetMaximum();
      maxHist=i;
    }
  }
  hist[maxHist]->Draw();
  
  for(Int_t j=n-1; j>=0; --j){  //drawing is in reverse order   
    if(!hist[j]) continue; 
    //Option_t* emptyOption("");
    //if(opt==emptyOption){    // gives no warning, but is not tested if works properly
    if(opt==""){     // gives compiler warning
      hist[j]->Draw("same");
    }
    else {
      TString* optstr = new TString("same,");
      *optstr = *optstr->Append(opt);      
      hist[j]->Draw(*optstr);  
    }
  }
  return;  
}
*/


void HistogramTools::FillStack(THStack* stck, TH1F* hist[], size_t n)
{
  for(size_t j=n-1; j!=0; --j){  //filling is in reverse order  
    if(!hist[j]) continue;
    stck->Add(hist[j]);
  }
  return;
}



void HistogramTools::GetHistArray(TFile* files[], const TString path, const TString name, TH1F* hist[], size_t n)
{
  for(size_t i=0; i<n; ++i){
    if(!files[i]) continue;
    files[i]->GetObject(path.Copy().Append(name).Append(";1"), hist[i]); 
  }
  return;
}



TH1F HistogramTools::GetHistSum(TH1F* hist[], size_t n)
{
  TH1F sum = *hist[0];
  for(size_t i=1; i<n; ++i){
    sum.Add(hist[i]);
  }
  return sum;
}



void HistogramTools::Normalize(TH1* hist, Double_t norm)
{
  if(hist->Integral()==0) return;
  hist->Scale(norm/hist->Integral());
  
  return;
}



void HistogramTools::Normalize(TH1* hist[], Double_t norm, size_t n)
{
  for(size_t i=0; i<n; ++i){
    if(!hist[i]) continue;
    Normalize(hist[i],norm); 
  }
  return;
}



void HistogramTools::SetAxisTitle(TH1* hist, Option_t* axis, const char* title, Float_t titlesize, Float_t offset, Float_t labelsize)
{
  TAxis* histAxis = new TAxis();
  
  if(!hist) return;
  
  if(*axis=='x')     histAxis = hist->GetXaxis();
  else if(*axis=='y')histAxis = hist->GetYaxis();
  else if(*axis=='z')histAxis = hist->GetZaxis();
  else std::cout << "WHICH FUCKING AXIS DO YOU MEAN???" << std::endl;  
  
  histAxis->SetTitle(title);
  histAxis->SetTitleSize(titlesize);
  histAxis->SetTitleOffset(offset);
  histAxis->SetLabelSize(labelsize);
  
  // default at the moment:
  histAxis->CenterTitle(kTRUE);

  return;
}



void HistogramTools::SetAxisTitle(TH1* hist[], Option_t* axis, const char* title, Float_t titlesize, Float_t offset, Float_t labelsize, size_t n)
{  
  for(size_t i=0; i<n; ++i){  
    if(!hist[i]) continue;
    SetAxisTitle(hist[i], axis, title, titlesize, offset, labelsize);
    return;
  }
      
  return;
}



void HistogramTools::SetAxisTitle(THStack* stck, Option_t* axis, const char* title, Float_t titlesize, Float_t offset, Float_t labelsize)
{
  if(!stck) return; 
  
  TAxis* stackAxis = new TAxis();
  if(*axis=='x')     stackAxis = stck->GetXaxis();
  else if(*axis=='y')stackAxis = stck->GetYaxis();
  else std::cout << "WHICH FUCKING AXIS DO YOU MEAN?" << std::endl;  
  
  stackAxis->SetTitle(title);  
  stackAxis->SetTitleSize(titlesize); 
  stackAxis->SetTitleOffset(offset); 
  stackAxis->SetLabelSize(labelsize);  

  // default at the moment:
  stackAxis->CenterTitle(kTRUE);

  return;
}



void HistogramTools::SetDefaultStyle()
{
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat("");
  gStyle->SetHistMinimumZero(kTRUE);
  
  TGaxis::SetMaxDigits(3);
      
  // define color palette
  stackColors[1] = new TColor(1001, 0.00, 1.00, 0.00,"sigMM");
  stackColors[2] = new TColor(1002, 0.00, 0.50, 0.00,"bgTM" );
  stackColors[3] = new TColor(1003, 1.00, 1.00, 0.00,"bgTop");
  stackColors[4] = new TColor(1004, 0.00, 0.00, 1.00,"bgZee");
  stackColors[5] = new TColor(1005, 0.00, 0.50, 1.00,"bgZmm");
  stackColors[6] = new TColor(1006, 0.00, 1.00, 1.00,"bgZtt");
  stackColors[7] = new TColor(1007, 0.50, 0.00, 0.50,"bgW"  );
  stackColors[8] = new TColor(1008, 1.00, 0.00, 1.00,"bgWW" );
  stackColors[9] = new TColor(1009, 0.50, 0.00, 1.00,"bgWZ" );
  stackColors[10] = new TColor(1010, 0.00, 0.00, 0.50,"bgZZ" );
  stackColors[11] = new TColor(1011, 1.00, 0.00, 0.00,"bgQCD");
  
  return;    
}



void HistogramTools::SetHistBinomialErrors(TH1F* hist, Double_t norm)
{
  for(Int_t i=1; i<=hist->GetNbinsX(); ++i){
    Double_t numerator = hist->GetBinContent(i);
    Double_t error;
    if(numerator>norm) error = 999999.;
    else error=sqrt((1.-numerator/norm)*numerator/norm/norm);
    hist->SetBinError(i,error);
    
//     cout << "numerator = " << numerator << endl;
//     cout << "norm = " << norm << endl;
//     cout << "Error = " << error << endl << endl;
  }
  return;  
}



void HistogramTools::SetHistBinomialErrors(TH2F* hist, Double_t norm)
{
  for(Int_t i=1; i<=hist->GetNbinsX(); ++i){
    for(Int_t j=1; j<=hist->GetNbinsX(); ++j){  
      Double_t numerator = hist->GetBinContent(i,j);
      Double_t error;
      if(numerator>norm) error = 999999.;
      else error=sqrt((1.-numerator/norm)*numerator/norm/norm);
      hist->SetBinError(i,j,error);
    }
  }
  return;  
}



void HistogramTools::SetPlotLine(TH1* hist, Color_t color, Width_t width, Style_t style)
{
  hist->SetLineColor(color);
  hist->SetLineWidth(width);
  hist->SetLineStyle(style);
  
  return;
}



void HistogramTools::SetMinimumZero(TH1* hist[], size_t n)
{
  for(size_t i=0; i<n; ++i){
    if(!hist[i]) continue;
    hist[i]->SetMinimum(0);
  }
  return;
}

void HistogramTools::SetTitle(TH1* hist[], const char* title, size_t n)
{
  for(size_t i=0; i<n; ++i){
    if(!hist[i]) continue;
    hist[i]->SetTitle(title);
  }
  return;
}





// special methods for currently used files

void HistogramTools::FillLegend(TLegend* leg, TH1F* hist[], Option_t* opt)
{
  leg->Clear();
  leg->SetFillColor(0);  
  
  if(hist[0]  && hist[0]->GetEntries()>0)  leg->AddEntry(hist[0],  "data","le");
  if(hist[1]  && hist[1]->GetEntries()>0)  leg->AddEntry(hist[1],  "Z #rightarrow #mu#mu", opt);
  if(hist[2]  && hist[2]->GetEntries()>0)  leg->AddEntry(hist[2],  "ZZ", opt);
  if(hist[3]  && hist[3]->GetEntries()>0)  leg->AddEntry(hist[3],  "WZ", opt);
  if(hist[4]  && hist[4]->GetEntries()>0)  leg->AddEntry(hist[4],  "WW", opt);
  if(hist[5]  && hist[5]->GetEntries()>0)  leg->AddEntry(hist[5],  "W #rightarrow #mu#nu", opt);
  if(hist[6]  && hist[6]->GetEntries()>0)  leg->AddEntry(hist[6],  "Z #rightarrow #tau#tau", opt);
  if(hist[7]  && hist[7]->GetEntries()>0)  leg->AddEntry(hist[7],  "t (t channel)", opt);
  if(hist[8]  && hist[8]->GetEntries()>0)  leg->AddEntry(hist[8],  "t (tW channel)", opt);
  if(hist[9]  && hist[9]->GetEntries()>0)  leg->AddEntry(hist[9],  "t (s channel)", opt);
  if(hist[10] && hist[10]->GetEntries()>0) leg->AddEntry(hist[10], "t#bar{t}", opt);
  if(hist[11] && hist[11]->GetEntries()>0) leg->AddEntry(hist[11], "QCD", opt);
  
  return;      
}


void HistogramTools::SetPlotFilling(TH1F* hist[], size_t n)
{
  if(hist[0]){
    hist[0]->SetLineWidth( 2);
    hist[0]->SetLineColor(14);
  }
  for(size_t i=1; i<n; ++i){
    if(!hist[i]) continue;
    SetPlotLine(hist[i], 1, 1, 1);
    hist[i]->SetFillColor(1000+i); 
  }
  return;
}


void HistogramTools::SetPlotLines(TH1F* hist[], size_t n)
{
  if(hist[0]){
    hist[0]->SetLineWidth( 2);
    hist[0]->SetLineColor(14);
  }
  for(size_t i=1; i<n; ++i){
    if(!hist[i]) continue;
    SetPlotLine(hist[i], 1000+i, 4, 1); 
  }
  return;
}


void HistogramTools::SetWeights(TH1F* hist[], Double_t dataLumi, size_t n)
{ 
  for(size_t i=1; i<n; ++i){
    // no. of events in MC dataset
    unsigned int nEvents(0);
    // cross section for process in pb
    double crossSection(-999.);
    // filter efficiency if given cross section is not same as for regarded parameter space
    double filterEfficiency(1.);
    
    // eventweights
    switch(i){
      //case  0 : if(hist[i]) hist[i]->Scale(1. ); break;    
      case  1 : nEvents = 2051268; crossSection = 1666.; filterEfficiency = 1.; break;
      case  2 : nEvents = 145000; crossSection = 5.9; filterEfficiency = 1.; break;  
      case  3 : nEvents = 118120; crossSection = 18.2; filterEfficiency = 1.; break;     
      case  4 : nEvents = 122980; crossSection = 43.; filterEfficiency = 1.; break;      
      case  5 : nEvents = 2047693; crossSection = 10438.; filterEfficiency = 1.; break;      
      case  6 : nEvents = 2160000; crossSection = 1666.; filterEfficiency = 1.; break;      
      case  7 : nEvents = 528593; crossSection = 64.6; filterEfficiency = 1.; break;      
      case  8 : nEvents = 466437; crossSection = 10.6; filterEfficiency = 1.; break;       
      case  9 : nEvents = 412055; crossSection = 4.21; filterEfficiency = 1.; break; 
      case 10 : nEvents = 632010; crossSection = 165.; filterEfficiency = 1.; break;       
      case 11 : nEvents = 0; crossSection = 296900.; filterEfficiency = 0.2864; break;  // real values: crossSection*1000, filterEfficiency/1000
      default: continue;      
    }
    if(i>=1 && i<n && hist[i]){
      const double weight(dataLumi * crossSection*filterEfficiency/static_cast<double>(nEvents));
      hist[i]->Scale(weight);
      //std::cout<<"\n\tWeight: "<<weight<<"\n";
    }
  }
}



