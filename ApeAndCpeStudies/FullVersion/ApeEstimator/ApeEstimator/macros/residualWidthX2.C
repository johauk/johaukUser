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
gStyle->SetPadRightMargin(0.12);

gStyle->SetPadTopMargin(0.10);
gStyle->SetPadBottomMargin(0.12);

gStyle->SetTitleOffset(1.2,"Y");
gStyle->SetTitleOffset(1.15,"X");


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


TCanvas* canvas1;

TString* inpath = new TString("$CMSSW_BASE/src/ApeEstimator/ApeEstimator/hists/workingArea/iter0/");

TFile* file1 = TFile::Open("$CMSSW_BASE/src/ApeEstimator/ApeEstimator/hists/workingArea/pGun/iter0/allData_resultsFile.root");
TFile* file2 = TFile::Open(inpath->Copy().Append("allData_resultsFile.root"));

TH1 *hist1, *hist2;

TLegend* legend1;

TString legendEntry1 = "TOBmisal20", legendEntry2 = "data";
Double_t yMax1, yMax2;
Double_t yMin1, yMin2;
TString outputDirectory = "plots/";



//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


TFile* file1Baseline(0);
file1Baseline = TFile::Open("$CMSSW_BASE/src/ApeEstimator/ApeEstimator/hists/Design/baseline/allData_baselineApe.root");
TTree* baselineTree(0);
if(file1Baseline){
  file1Baseline->GetObject("iterTree", baselineTree);
}


double delta0(999.);
TLine* baseline(0);
baseline = new TLine(0.0005,delta0,0.01,delta0);
baseline->SetLineStyle(2);
baseline->SetLineWidth(2);


//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_1/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_1", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tib1outRphi");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");

    legend1->Delete();
    if(stats2)stats2->Delete();
    canvas1->Close();




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_2/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_2", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tib1outStereo");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");

    legend1->Delete();
    if(stats2)stats2->Delete();
    canvas1->Close();




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_3/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_3", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tib1inRphi");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_4/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_4", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tib1inStereo");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_5/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_5", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tib2outRPhi");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_6/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_6", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tib2outStereo");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_7/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_7", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tib2inRphi");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_8/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_8", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tib2inStereo");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_9/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_9", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tib3out");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_10/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_10", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tib3in");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_11/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_11", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tib4out");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_12/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_12", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tib4in");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++

/*
// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_13/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_13", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tob1outRphi");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");

*/


//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_14/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_14", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tob1outStereo");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_15/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_15", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tob1inRphi");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++

/*
// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_16/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_16", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tob1inStereo");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");

*/


//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_17/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_17", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tob2outRphi");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++

/*
// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_18/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_18", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tob2outStereo");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");


*/

//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++

/*
// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_19/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_19", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tob2inRphi");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");


*/

//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_20/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_20", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tob2inStereo");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_21/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_21", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tob3out");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_22/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_22", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tob3in");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_23/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_23", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tob4out");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_24/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_24", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tob4in");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_25/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_25", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tob5out");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_26/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_26", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tob5in");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_27/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_27", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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

  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tob6out");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("Sector_28/h_residualWidthX2");
    file1->GetObject(histName + ";1", hist1);
    file2->GetObject(histName + ";1", hist2);

  //hist1->SetTitle("");
  //hist1->SetXTitle("");
  //hist1->SetYTitle("# Treffer");
  //hist1->GetXaxis()->SetNoExponent();
  hist1->SetLineWidth(2);
  
  yMax1 = hist1->GetMaximum(); yMax2 = hist2->GetMaximum();
  yMin1 = hist1->GetMinimum(); yMin2 = hist2->GetMinimum();
  if(yMax2>yMax1)hist1->GetYaxis()->SetRangeUser(0.,1.1*yMax2);
  hist1->Draw();

  //hist1->SetMarkerColor(4);
  //hist1->SetMarkerStyle(24);
  //hist1->SetMarkerSize(1.5);
  //hist1->SetLineWidth(2);
  //hist1->Draw("P");            //Draw only Markers
  
    if(baselineTree){
      baselineTree->SetBranchAddress("Ape_Sector_28", &delta0); baselineTree->GetEntry(0);
      delta0 = std::sqrt(delta0);
      //baseline = new TLine(0.0005,delta0,0.01,delta0); baseline->Draw("same");
      baseline->DrawLine(0.0005,delta0,0.01,delta0);
    }
  
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
  
  //TPaveStats* stats2 = hist2->GetListOfFunctions()->At(1);
  TPaveStats* stats2 = (TPaveStats*)hist2->GetListOfFunctions()->FindObject("stats");
  if(stats2)stats2->SetY1NDC(0.58);
  if(stats2)stats2->SetY2NDC(0.78);
  if(stats2)stats2->SetLineColor(2);
  if(stats2)stats2->SetTextColor(2);

    canvas1->Modified();
    canvas1->Update();

  legend1 = new TLegend(0.41,0.27,0.71,0.42);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetTextSize(0.04);
  legend1->SetMargin(0.12);
  legend1->SetFillStyle(1001);
  //legend1->SetBorderSize(0);
  legend1->AddEntry(hist1,legendEntry1,"l");
  legend1->AddEntry(hist2,legendEntry2,"l");
  legend1->Draw("same");

    canvas1->Modified();
    canvas1->Update();

  TString plotName(outputDirectory + "residualWidthX2Tob6in");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");







//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


  canvas1->Close();

  hist1->Delete();hist2->Delete();
  
  file1->Close();file2->Close();



}
