#include <TPaveStats.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>
#include <TFitResult.h>
#include <TF1.h>
#include <TSpectrum.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TH1F.h"
#include "TF1.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TSystemFile.h"
#include "TGraph.h"
#include "TAxis.h"

void StatisticComparison() {

  

  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);


  TString filename_eL250 = "../ReTraining250/merged_bb_eL_pR.root";
  TFile *file_eL250 = new TFile(filename_eL250);
  TTree *ntp_eL250=(TTree*)file_eL250->Get("ntp");
  TBranch *jete_eL250=(TBranch*)ntp_eL250->GetBranch("jete");   
  TH1F * jete_eL250_H = new TH1F("jete_eL250_H","jete_eL250_H",100,0,500);
  ntp_eL250->Project("jete_eL250_H", "jete");

  TString filename_eR250 = "../ReTraining250/merged_bb_eR_pL.root";
  TFile *file_eR250 = new TFile(filename_eR250);
  TTree *ntp_eR250=(TTree*)file_eR250->Get("ntp");
  TBranch *jete_eR250=(TBranch*)ntp_eR250->GetBranch("jete");
  TH1F * jete_eR250_H = new TH1F("jete_eR250_H","jete_eR250_H",100,0,500);
  ntp_eR250->Project("jete_eR250_H", "jete");

  TString filename_eL500 = "MakeNTuples_vtx_2f250/eL_pR_b_quark_Kisr_50_merged.root ";
  TFile *file_eL500 = new TFile(filename_eL500);
  TTree *ntp_eL500=(TTree*)file_eL500->Get("ntp");
  TBranch *jete_eL500=(TBranch*)ntp_eL500->GetBranch("jete");
  TH1F * jete_eL500_H = new TH1F("jete_eL500_H","jete_eL500_H",100,0,500);
  ntp_eL500->Project("jete_eL500_H", "jete");

  TString filename_eR500 = "MakeNTuples_vtx_2f250/eR_pL_b_quark_Kisr_50_merged.root ";
  TFile *file_eR500 = new TFile(filename_eR500);
  TTree *ntp_eR500=(TTree*)file_eR500->Get("ntp");
  TBranch *jete_eR500=(TBranch*)ntp_eR500->GetBranch("jete");
  TH1F * jete_eR500_H = new TH1F("jete_eR500_H","jete_eR500_H",100,0,500);
  ntp_eR500->Project("jete_eR500_H", "jete");

  TCanvas* comparison = new TCanvas("comparison","comparison",800,800);
  comparison->cd(1);
  comparison->SetGrid();
  
  jete_eL250_H->SetTitle("b-quark events from MakeNtuples;Energy (GeV);Events");
  //  jete_eL250_H->GetXaxis()->SetTitle("Energy (GeV)");
  //jete_eL250_H->GetYaxis()->SetTitle("Events");
  jete_eL250_H->SetLineColor(4);
  jete_eL250_H->SetLineWidth(3);
  jete_eL250_H->SetLineStyle(1);
  jete_eL250_H->Draw("histo");  
  jete_eR250_H->SetLineColor(2);
  jete_eR250_H->SetLineWidth(3);
  jete_eR250_H->SetLineStyle(1);
  jete_eR250_H->Draw("histosame");  
  jete_eL500_H->SetLineColor(65);
  jete_eL500_H->SetLineWidth(3);
  jete_eL500_H->SetLineStyle(1);
  jete_eL500_H->Draw("histosame"); 
  jete_eR500_H->SetLineColor(95);
  jete_eR500_H->SetLineWidth(3);
  jete_eR500_H->SetLineStyle(1);
  jete_eR500_H->Draw("histosame");
    
  TLegend *leg_b = new TLegend(0.4,0.25,0.6,0.45);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(jete_eL250_H,"e^{-}_{L}e^{+}_{R} (250 GeV)","lp");
  leg_b->AddEntry(jete_eR250_H,"e^{-}_{R}e^{+}_{L} (250 GeV)","lp");
  leg_b->AddEntry(jete_eL500_H,"e^{-}_{L}e^{+}_{R} (500 GeV)","lp");
  leg_b->AddEntry(jete_eR500_H,"e^{-}_{R}e^{+}_{L} (500 GeV)","lp");
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

}
