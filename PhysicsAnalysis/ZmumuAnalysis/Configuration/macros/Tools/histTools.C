#include "histTools.h"


#include "TString.h"
#include "TCanvas.h"


#include <iostream>


void StackTools::setTitles(THStack* stack, TH1* hist){
  TString title = hist->GetTitle();
  TString xTitle = hist->GetXaxis()->GetTitle();
  TString yTitle = hist->GetYaxis()->GetTitle();
  //std::cout<<"Titles: "<<title<<" "<<xTitle<<" "<<yTitle<<"\n";
  
  // Workaround needed to set axis titles for THStack: only possible after command Draw()
  TCanvas* tmpCanvas = new TCanvas("tmpCanvas");
  stack->Draw();
  stack->SetTitle(title);
  stack->GetXaxis()->SetTitle(xTitle);
  stack->GetYaxis()->SetTitle(yTitle);
  delete tmpCanvas;
}
