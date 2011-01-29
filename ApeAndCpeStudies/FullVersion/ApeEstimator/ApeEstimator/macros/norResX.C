{



gROOT->SetStyle("Plain");
gROOT->ForceStyle();
gStyle->SetOptStat(111110);

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

TFile* file1 = TFile::Open("$CMSSW_BASE/src/ApeEstimator/ApeEstimator/hists/Design/iter0/bothPion1_10.root");
TFile* file2 = TFile::Open(inpath->Copy().Append("allData.root"));

TH1 *hist1, *hist2;

TLegend* legend1;

TString legendEntry1 = "design", legendEntry2 = "TOBmisal20";
Double_t yMax1, yMax2;
Double_t yMin1, yMin2;
TString outputDirectory = "plots/";



//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++





//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_1/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTib1outRphi");

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
  
  TString histName("ApeEstimator2/Sector_2/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTib1outStereo");

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
  
  TString histName("ApeEstimator2/Sector_3/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTib1inRphi");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_4/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTib1inStereo");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_5/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTib2outRPhi");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_6/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTib2outStereo");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_7/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTib2inRphi");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_8/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTib2inStereo");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_9/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTib3out");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_10/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTib3in");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_11/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTib4out");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_12/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTib4in");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++

/*
// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_13/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTob1outRphi");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");

*/


//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_14/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTob1outStereo");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_15/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTob1inRphi");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++

/*
// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_16/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTob1inStereo");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");

*/


//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_17/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTob2outRphi");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++

/*
// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_18/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTob2outStereo");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");


*/

//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++

/*
// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_19/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTob2inRphi");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");


*/

//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_20/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTob2inStereo");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_21/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTob3out");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_22/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTob3in");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_23/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTob4out");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_24/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTob4in");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_25/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTob5out");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_26/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTob5in");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_27/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTob6out");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");




//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


// 1D-Histo (comparison)

    canvas1 = new TCanvas("canvas1");
    canvas1->cd();
  //canvas1->SetLogy();
  
  TString histName("ApeEstimator2/Sector_28/h_NorResX");
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

  TString plotName(outputDirectory + "NorResXTob6in");

    canvas1->Print(plotName + ".eps");
    canvas1->Print(plotName + ".png");







//++++++++++++++++++++++++++++++++++=====================================+++++++++++++++++++++++++++++++


  canvas1->Close();

  hist1->Delete();hist2->Delete();
  
  file1->Close();file2->Close();



}
