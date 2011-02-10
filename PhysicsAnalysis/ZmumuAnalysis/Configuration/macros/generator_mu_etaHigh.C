{



gROOT->SetStyle("Plain");
gROOT->ForceStyle();
gStyle->SetOptStat(0);

gStyle->SetPalette(1);      //Spektralpalette, Default: 0 resp. 50
//gStyle->SetNumberContours(20);  // Default: 20

double width = 600.;

gStyle->SetCanvasDefW(width);
gStyle->SetCanvasDefH(width);

gStyle->SetPadLeftMargin(0.12);
gStyle->SetPadRightMargin(0.08);

gStyle->SetPadTopMargin(0.08);
gStyle->SetPadBottomMargin(0.12);

gStyle->SetTitleOffset(1.6,"Y");
gStyle->SetTitleOffset(1.2,"X");


TGaxis::SetMaxDigits(3);


//TH1::StatOverflows(kTRUE);// compute mean etc including overflow!
//gStyle->SetHistMinimumZero(kTRUE); // no zero-suppression on y-axis
//gStyle->SetOptFit(222);              // 1: Fit-PArameter werden angezeigt
//gStyle->SetCanvasDefX(400);     // canvas (default) upper edge in X
//gStyle->SetCanvasDefY(200);     // canvas (default) upper edge in Y

//gStyle->SetHistLineWidth(2);



gStyle->SetTitleX(0.2);         // move upper left corner of title box to specified value
//gStyle->SetTitleY(0.99);        // move upper left corner of title box to specified value



//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++



gStyle->SetTitleXSize(0.05);
gStyle->SetTitleYSize(0.05);
gStyle->SetTitleSize(0.05,"XY");
gStyle->SetLabelSize(0.05,"XY");



//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


gROOT->ProcessLine(".L tdrstyle.C");
setTDRStyle();


//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


TCanvas* canvas1;

TFile* file1 = TFile::Open("$CMSSW_BASE/src/ZmumuAnalysis/Configuration/hists/simulation/generatorTopZmumu_powheg.root");
TFile* file2 = TFile::Open("$CMSSW_BASE/src/ZmumuAnalysis/Configuration/hists/simulation/generatorTopZmumu.root");

TH1 *hist1, *hist2;

TLegend* legend1;

TString legendEntry1 = "POWHEG", legendEntry2 = "MADGRAPH";
Double_t yMax1, yMax2;
Double_t yMin1, yMin2;
TString outputDirectory = "$CMSSW_BASE/src/ZmumuAnalysis/Configuration/macros/plots/generatorTop_";



//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


TLine *line1, *line2, *line3, *line4;



//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++




// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("GeneratorZmumuAnalyzerVisible2/SingleMu/h_etaHigh");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  hist1->GetXaxis()->SetRangeUser(-8.5,8.4);
  
  Double_t scaleFactor1(1.);
  Double_t scaleFactor2(1.);
  //Int_t xIntegralLow(hist1->GetXaxis()->FindBin(50.)), xIntegralHigh(hist1->GetNbinsX()+1);
  //if(hist1->Integral(xIntegralLow,xIntegralHigh)>0.)scaleFactor1 = 100./hist1->Integral(xIntegralLow,xIntegralHigh);
  //if(hist2->Integral(xIntegralLow,xIntegralHigh)>0.)scaleFactor2 = 100./hist2->Integral(xIntegralLow,xIntegralHigh);
  if(hist1->Integral()>0.)scaleFactor1 = 100./hist1->GetEntries();
  if(hist2->Integral()>0.)scaleFactor2 = 100./hist2->GetEntries();
  Double_t maxScaleFactor(scaleFactor1>scaleFactor2 ? scaleFactor1 : scaleFactor2);
  hist1->Scale(scaleFactor1);
  hist1->SetYTitle(TString(hist1->GetYaxis()->GetTitle()) + "  (scaled)");
  hist2->Scale(scaleFactor2);
  
  //yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  //yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();   // Avoid bins out of range if range of Xaxis gets reduced (SetRange, SetRangeUser)
  yMax1 = hist1->GetBinContent(hist1->GetMaximumBin()); yMax2 = hist2->GetBinContent(hist1->GetMaximumBin());
  yMin1 = hist1->GetBinContent(hist1->GetMinimumBin()); yMin2 = hist2->GetBinContent(hist1->GetMinimumBin());
  Double_t yMin(yMin1>yMin2 ? yMin2 : yMin1), yMax(yMax1>yMax2 ? yMax1 : yMax2);
  Double_t yMinHist(0.0*yMin), yMaxHist(1.1*yMax);
  if(yMax>yMin)hist1->GetYaxis()->SetRangeUser(yMinHist,yMaxHist);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
  //hist2->SetMarkerColor(2);
  //hist2->SetMarkerStyle(25);
  //hist2->SetMarkerSize(1.5);
  //hist2->Draw("Psame");

  hist2->SetLineColor(2);
  hist2->SetLineStyle(2);
  hist2->SetLineWidth(2);
  hist2->Draw("sameS");

    canvas1->Modified();
    canvas1->Update();

  //TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->At(1);
  //TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  //stats2->SetY1NDC(0.58);
  //stats2->SetY2NDC(0.78);
  //stats2->SetLineColor(2);
  //stats2->SetTextColor(2);
  
  line1 = new TLine(-2.4, yMinHist,-2.4, yMaxHist);line1->SetLineStyle(2);line1->SetLineWidth(2);
  line2 = new TLine(2.4,  yMinHist,2.4,  yMaxHist);line2->SetLineStyle(2);line2->SetLineWidth(2);
  //line3 = new TLine(106.,yMinHist,106.,yMaxHist);line3->SetLineStyle(2);line3->SetLineWidth(2);
  //line4 = new TLine(120.,yMinHist,120.,yMaxHist);line4->SetLineStyle(2);line4->SetLineWidth(2);
  line1->Draw("same"); line2->Draw("same"); //line3->Draw("same"); line4->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.71,0.82,0.91,0.92);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0); // hollow, but with border //legend1->SetFillStyle(1001); solid style, but w/o frame
  legend1->SetBorderSize(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.24);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "mu_etaHigh");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");
    
  yMinHist = (yMin<maxScaleFactor ? 0.5*maxScaleFactor : 0.5*yMin);
  yMaxHist = (pow(yMax,1.1))/(pow(yMinHist,0.1));
  if(yMax>yMin)hist1->SetMinimum(yMinHist);
  if(yMax>yMin)hist1->SetMaximum(yMaxHist);
  
  if(line1)line1->SetY2(yMaxHist); if(line2)line2->SetY2(yMaxHist); if(line3)line3->SetY2(yMaxHist); if(line4)line4->SetY2(yMaxHist);
    
    gPad->SetLogy(1);
    canvas1->Update();
    
    plotName = plotName + "_log";

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");

    legend1->Delete();
    //stats2->Delete();
    canvas1->Close();






//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++



  hist1->Delete();hist2->Delete();
  
  file1->Close();file2->Close();



}
