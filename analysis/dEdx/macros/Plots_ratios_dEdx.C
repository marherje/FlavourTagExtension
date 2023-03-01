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
#include "TH1.h"
#include "TF1.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TSystemFile.h"
#include "../../../style/Style.C"
#include "../../../style/Labels.C"

void Labels(TString pol, TString tracks, TString cut, TString cat){
  QQBARLabel(0.86,0.952,"");
  // QQBARLabel2(0.3,0.97, "e^{-}e^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);                                                                              
  if(pol=="eL")
    QQBARLabel2(0.3,0.965, "e_{L}^{-}e_{R}^{+}",kGray+2);//#rightarrow b#bar{b}                                                                                                   
  else{
    if(pol=="eR")
      QQBARLabel2(0.3,0.965, "e_{R}^{-}e_{L}^{+}",kGray+2);
    else
      QQBARLabel2(0.3,0.965, "e^{-}e^{+}",kGray+2);
  }

  TString track_string;
  if(tracks=="primary")track_string="Primary";
  else if(tracks=="secondary")track_string="Secondary";
  else track_string="All";

  TString mom_string;
  if(cut=="0")mom_string="";
  else mom_string="p_{track} > "+cut+" GeV";
  
  TString cat_string;
  if(cat=="catA")cat_string="Cat. A";
  else if(cat=="catB")cat_string="Cat. B";
  else if(cat=="catC")cat_string="Cat. C";
  else if(cat=="catD")cat_string="Cat. D";
  else cat_string="All categories";
  QQBARLabel2(0.3,0.82, track_string+" tracks");
  QQBARLabel2(0.3,0.78, cat_string);
  QQBARLabel2(0.5,0.965, "Work in progress",kRed+2);
  QQBARLabel2(0.075,0.025, "K_{#gamma} < 50 GeV, |cos#theta| < 0.95",kGray+2);
  QQBARLabel2(0.075,0.075, mom_string,kGray+2);
}

void NoCheat_dEdx(TString filename_b, TString filename_b2, TString filename_c, TString filename_c2, TString filename_light, TString filename_light2, TString tracks, TString cut, TString cat){

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);                                                                                                                                                     

  TFile *f_b = new TFile(filename_b);
  TFile *f_c = new TFile(filename_c);
  TFile *f_light = new TFile(filename_light);  
  TFile *f_b2 = new TFile(filename_b2);
  TFile *f_c2 = new TFile(filename_c2);
  TFile *f_light2 = new TFile(filename_light2);
  
  TH1F*  kdEdx_dist_nocheat_b = (TH1F*)f_b->Get("kdEdx_dist_nocheat");
  TH1F*  kdEdx_dist_nocheat_c = (TH1F*)f_c->Get("kdEdx_dist_nocheat");
  TH1F*  kdEdx_dist_nocheat_light = (TH1F*)f_light->Get("kdEdx_dist_nocheat");
  TH1F*  kdEdx_dist_nocheat_b2 = (TH1F*)f_b2->Get("kdEdx_dist_nocheat");
  TH1F*  kdEdx_dist_nocheat_c2 = (TH1F*)f_c2->Get("kdEdx_dist_nocheat");
  TH1F*  kdEdx_dist_nocheat_light2 = (TH1F*)f_light2->Get("kdEdx_dist_nocheat");

  TH1F*  kdEdx_dist_count_b = (TH1F*)f_b->Get("kdEdx_dist_count");
  TH1F*  kdEdx_dist_count_c = (TH1F*)f_c->Get("kdEdx_dist_count");
  TH1F*  kdEdx_dist_count_light = (TH1F*)f_light->Get("kdEdx_dist_count");
  TH1F*  kdEdx_dist_count_b2 = (TH1F*)f_b2->Get("kdEdx_dist_count");
  TH1F*  kdEdx_dist_count_c2 = (TH1F*)f_c2->Get("kdEdx_dist_count");
  TH1F*  kdEdx_dist_count_light2 = (TH1F*)f_light2->Get("kdEdx_dist_count");

  TH1F*  kdEdx_dist_count_b_short = (TH1F*)f_b->Get("kdEdx_dist_count_short");
  TH1F*  kdEdx_dist_count_c_short = (TH1F*)f_c->Get("kdEdx_dist_count_short");
  TH1F*  kdEdx_dist_count_light_short = (TH1F*)f_light->Get("kdEdx_dist_count_short");
  TH1F*  kdEdx_dist_count_b2_short = (TH1F*)f_b2->Get("kdEdx_dist_count_short");
  TH1F*  kdEdx_dist_count_c2_short = (TH1F*)f_c2->Get("kdEdx_dist_count_short");
  TH1F*  kdEdx_dist_count_light2_short = (TH1F*)f_light2->Get("kdEdx_dist_count_short");

  TCanvas* c_dist_nocheat = new TCanvas("c_dist_nocheat","c_dist_nocheat",800,800);
  c_dist_nocheat->cd(1);
  c_dist_nocheat->SetGrid();
  kdEdx_dist_nocheat_b->GetXaxis()->SetTitle("(dEdx-dEdx_{exp-kaon})/#Delta_{dEdx}");
  kdEdx_dist_nocheat_b->GetYaxis()->SetTitle("Entries (pfos)");
  kdEdx_dist_nocheat_b->GetYaxis()->SetTitleOffset(1.25);
  kdEdx_dist_nocheat_b->GetXaxis()->SetTitleOffset(1.);
  //kdEdx_dist_nocheat_b->GetYaxis()->SetRangeUser(0,100);

  float entries_b=kdEdx_dist_nocheat_b->Integral();
  float entries_c=kdEdx_dist_nocheat_c->Integral();
  float entries_light=kdEdx_dist_nocheat_light->Integral();
  //cout<<entries_b<<" "<<entries_c<<" "<<entries_light<<endl;
  kdEdx_dist_nocheat_b->SetLineColor(2);
  kdEdx_dist_nocheat_b->SetLineWidth(3);
  //kdEdx_dist_nocheat_b->SetLineStyle(2);
  kdEdx_dist_nocheat_b->Scale(1/entries_b);
  kdEdx_dist_nocheat_b->Draw("histo");
  kdEdx_dist_nocheat_c->SetLineColor(4);
  kdEdx_dist_nocheat_c->SetLineWidth(3);
  //kdEdx_dist_nocheat_c->SetLineStyle(2);
  kdEdx_dist_nocheat_c->Scale(1/entries_c);
  kdEdx_dist_nocheat_c->Draw("histosame");
  kdEdx_dist_nocheat_light->SetLineColor(3);
  kdEdx_dist_nocheat_light->SetLineWidth(3);
  //kdEdx_dist_nocheat_light->SetLineStyle(2);
  kdEdx_dist_nocheat_light->Scale(1/entries_light);
  kdEdx_dist_nocheat_light->Draw("histosame");

  Labels("eL",tracks,cut,cat);

  TLegend *leg0 = new TLegend(0.2,0.25,0.4,0.35);
  leg0->SetTextSize(0.035);
  leg0->SetTextFont(42);
  leg0->AddEntry(kdEdx_dist_nocheat_b,"b-jets","lp");
  leg0->AddEntry(kdEdx_dist_nocheat_c,"c-jets","lp");
  leg0->AddEntry(kdEdx_dist_nocheat_light,"uds-jets","lp");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

  TCanvas* c_dist_nocheat2 = new TCanvas("c_dist_nocheat2","c_dist_nocheat2",800,800);
  c_dist_nocheat2->cd(1);
  c_dist_nocheat2->SetGrid();
  kdEdx_dist_nocheat_b2->GetXaxis()->SetTitle("(dEdx-dEdx_{exp-kaon})/#Delta_{dEdx}");
  kdEdx_dist_nocheat_b2->GetYaxis()->SetTitle("Entries (pfos)");
  kdEdx_dist_nocheat_b2->GetYaxis()->SetTitleOffset(1.25);
  kdEdx_dist_nocheat_b2->GetXaxis()->SetTitleOffset(1.);
  //kdEdx_dist_nocheat_b2->GetYaxis()->SetRangeUser(0,100);

  float entries_b2=kdEdx_dist_nocheat_b2->Integral();
  float entries_c2=kdEdx_dist_nocheat_c2->Integral();
  float entries_light2=kdEdx_dist_nocheat_light2->Integral();
  kdEdx_dist_nocheat_b2->SetLineColor(2);
  kdEdx_dist_nocheat_b2->SetLineWidth(3);
  //kdEdx_dist_nocheat_b2->SetLineStyle(2);
  kdEdx_dist_nocheat_b2->Scale(1/entries_b2);
  kdEdx_dist_nocheat_b2->Draw("histo");
  kdEdx_dist_nocheat_c2->SetLineColor(4);
  kdEdx_dist_nocheat_c2->SetLineWidth(3);
  //kdEdx_dist_nocheat_c2->SetLineStyle(2);
  kdEdx_dist_nocheat_c2->Scale(1/entries_c2);
  kdEdx_dist_nocheat_c2->Draw("histosame");
  kdEdx_dist_nocheat_light2->SetLineColor(3);
  kdEdx_dist_nocheat_light2->SetLineWidth(3);
  //kdEdx_dist_nocheat_light2->SetLineStyle(2);
  kdEdx_dist_nocheat_light2->Scale(1/entries_light2);
  kdEdx_dist_nocheat_light2->Draw("histosame");

  Labels("eR",tracks,cut,cat);

  TLegend *leg02 = new TLegend(0.2,0.25,0.4,0.35);
  leg02->SetTextSize(0.035);
  leg02->SetTextFont(42);
  leg02->AddEntry(kdEdx_dist_nocheat_b2,"b-jets","lp");
  leg02->AddEntry(kdEdx_dist_nocheat_c2,"c-jets","lp");
  leg02->AddEntry(kdEdx_dist_nocheat_light2,"uds-jets","lp");
  leg02->SetFillColor(0);
  leg02->SetLineColor(0);
  leg02->SetShadowColor(0);
  leg02->Draw();


  //---------
  TCanvas* c_dist_count = new TCanvas("c_dist_count","c_dist_count",800,800);
  c_dist_count->cd(1);
  c_dist_count->SetGrid();
  kdEdx_dist_count_b->GetXaxis()->SetTitle("K_{dEdx} distance");
 //kdEdx_dist_count_b->GetXaxis()->SetTitle("(dEdx-dEdx_{exp-kaon})/#Delta_{dEdx}");
  kdEdx_dist_count_b->GetYaxis()->SetTitle("Entries (pfos)");
  kdEdx_dist_count_b->GetYaxis()->SetTitleOffset(1.25);
  kdEdx_dist_count_b->GetXaxis()->SetTitleOffset(1.);
  kdEdx_dist_count_b->GetXaxis()->SetLabelSize(0);
  //kdEdx_dist_count_b->GetYaxis()->SetRangeUser(0,100);                                                                                                                                                  

  float e_count_b=kdEdx_dist_count_b->Integral();
  float e_count_c=kdEdx_dist_count_c->Integral();
  float e_count_light=kdEdx_dist_count_light->Integral();
  //cout<<entries_b<<" "<<entries_c<<" "<<entries_light<<endl;
  kdEdx_dist_count_b->SetLineColor(2);
  kdEdx_dist_count_b->SetLineWidth(3);
  //kdEdx_dist_count_b->SetLineStyle(2);                                                                                                                                                                  
  kdEdx_dist_count_b->Scale(1/e_count_b);
  kdEdx_dist_count_b->Draw("histo");
  kdEdx_dist_count_c->SetLineColor(4);
  kdEdx_dist_count_c->SetLineWidth(3);
  //kdEdx_dist_count_c->SetLineStyle(2);                                                                                                                                                                  
  kdEdx_dist_count_c->Scale(1/e_count_c);
  kdEdx_dist_count_c->Draw("histosame");
  kdEdx_dist_count_light->SetLineColor(3);
  kdEdx_dist_count_light->SetLineWidth(3);
  //kdEdx_dist_count_light->SetLineStyle(2);                                                                                                                                                              
  kdEdx_dist_count_light->Scale(1/e_count_light);
  kdEdx_dist_count_light->Draw("histosame");

  Labels("eL",tracks,cut,cat);
  TLegend *leg1 = new TLegend(0.3,0.65,0.5,0.75);
  leg1->SetTextSize(0.035);
  leg1->SetTextFont(42);
  leg1->AddEntry(kdEdx_dist_count_b,"b-jets","lp");
  leg1->AddEntry(kdEdx_dist_count_c,"c-jets","lp");
  leg1->AddEntry(kdEdx_dist_count_light,"uds-jets","lp");
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();
  QQBARLabel2(0.26,0.3, "d<-2");
  QQBARLabel2(0.5,0.3, "-2<d<2");
  QQBARLabel2(0.8,0.3, "d>2");

  TCanvas* c_dist_count2 = new TCanvas("c_dist_count2","c_dist_count2",800,800);
  c_dist_count2->cd(1);
  c_dist_count2->SetGrid();
  kdEdx_dist_count_b2->GetXaxis()->SetTitle("K_{dEdx} distance");
//kdEdx_dist_count_b2->GetXaxis()->SetTitle("(dEdx-dEdx_{exp-kaon})/#Delta_{dEdx}");
  kdEdx_dist_count_b2->GetYaxis()->SetTitle("Entries (pfos)");
  kdEdx_dist_count_b2->GetYaxis()->SetTitleOffset(1.25);
  kdEdx_dist_count_b2->GetXaxis()->SetTitleOffset(1.);
  kdEdx_dist_count_b2->GetXaxis()->SetLabelSize(0);
//kdEdx_dist_count_b2->GetYaxis()->SetRangeUser(0,100);                                                                                                                                                    

  float e_count_b2=kdEdx_dist_count_b2->Integral();
  float e_count_c2=kdEdx_dist_count_c2->Integral();
  float e_count_light2=kdEdx_dist_count_light2->Integral();
  kdEdx_dist_count_b2->SetLineColor(2);
  kdEdx_dist_count_b2->SetLineWidth(3);
  //kdEdx_dist_count_b->SetLineStyle(2);                                                                                                                                                                    
  kdEdx_dist_count_b2->Scale(1/e_count_b2);
  kdEdx_dist_count_b2->Draw("histo");
  kdEdx_dist_count_c2->SetLineColor(4);
  kdEdx_dist_count_c2->SetLineWidth(3);
  //kdEdx_dist_count_c2->SetLineStyle(2);                                                                                                                                                                    
  kdEdx_dist_count_c2->Scale(1/e_count_c2);
  kdEdx_dist_count_c2->Draw("histosame");
  kdEdx_dist_count_light2->SetLineColor(3);
  kdEdx_dist_count_light2->SetLineWidth(3);
  //kdEdx_dist_count_light2->SetLineStyle(2);                                                                                                                                                                
  kdEdx_dist_count_light2->Scale(1/e_count_light2);
  kdEdx_dist_count_light2->Draw("histosame");

  Labels("eR",tracks,cut,cat);
  TLegend *leg12 = new TLegend(0.3,0.65,0.5,0.75);
  leg12->SetTextSize(0.035);
  leg12->SetTextFont(42);
  leg12->AddEntry(kdEdx_dist_count_b2,"b-jets","lp");
  leg12->AddEntry(kdEdx_dist_count_c2,"c-jets","lp");
  leg12->AddEntry(kdEdx_dist_count_light2,"uds-jets","lp");
  leg12->SetFillColor(0);
  leg12->SetLineColor(0);
  leg12->SetShadowColor(0);
  leg12->Draw();
  
  QQBARLabel2(0.26,0.3, "d<-2");
  QQBARLabel2(0.5,0.3, "-2<d<2");
  QQBARLabel2(0.8,0.3, "d>2");


  //---------                                                                                                                                                                                                                                
  //---------                                                                                                                                                                                                                                                                                  
  TCanvas* c_dist_count_short = new TCanvas("c_dist_count_short","c_dist_count_short",800,800);
  c_dist_count_short->cd(1);
  c_dist_count_short->SetGrid();
  kdEdx_dist_count_b_short->GetXaxis()->SetTitle("K_{dEdx} distance");
  //kdEdx_dist_count_b_short->GetXaxis()->SetTitle("(dEdx-dEdx_{exp-kaon})/#Delta_{dEdx}");                                                                                                                                                                                                     
  kdEdx_dist_count_b_short->GetYaxis()->SetTitle("Entries (pfos)");
  kdEdx_dist_count_b_short->GetYaxis()->SetTitleOffset(1.25);
  kdEdx_dist_count_b_short->GetXaxis()->SetTitleOffset(1.);
  kdEdx_dist_count_b_short->GetXaxis()->SetLabelSize(0);
  //kdEdx_dist_count_b_short->GetYaxis()->SetRangeUser(0,100);                                                                                                                                                                                                                                       

  float e_count_b_short=kdEdx_dist_count_b_short->Integral();
  float e_count_c_short=kdEdx_dist_count_c_short->Integral();
  float e_count_light_short=kdEdx_dist_count_light_short->Integral();
  //cout<<entries_b<<" "<<entries_c<<" "<<entries_light<<endl;                                                                                                                                                                                                                                 
  kdEdx_dist_count_b_short->SetLineColor(2);
  kdEdx_dist_count_b_short->SetLineWidth(3);
  //kdEdx_dist_count_b_short->SetLineStyle(2);                                                                                                                                                                                                                                                       
  kdEdx_dist_count_b_short->Scale(1/e_count_b);
  kdEdx_dist_count_b_short->Draw("histo");
  kdEdx_dist_count_c_short->SetLineColor(4);
  kdEdx_dist_count_c_short->SetLineWidth(3);
  //kdEdx_dist_count_c_short->SetLineStyle(2);                                                                                                                                                                                                                                                       
  kdEdx_dist_count_c_short->Scale(1/e_count_c);
  kdEdx_dist_count_c_short->Draw("histosame");
  kdEdx_dist_count_light_short->SetLineColor(3);
  kdEdx_dist_count_light_short->SetLineWidth(3);
  //kdEdx_dist_count_light_short->SetLineStyle(2);                                                                                                                                                                                                                                                   
  kdEdx_dist_count_light_short->Scale(1/e_count_light);
  kdEdx_dist_count_light_short->Draw("histosame");

  Labels("eL",tracks,cut,cat);
  TLegend *leg1_short = new TLegend(0.3,0.65,0.5,0.75);
  leg1_short->SetTextSize(0.035);
  leg1_short->SetTextFont(42);
  leg1_short->AddEntry(kdEdx_dist_count_b_short,"b-jets","lp");
  leg1_short->AddEntry(kdEdx_dist_count_c_short,"c-jets","lp");
  leg1_short->AddEntry(kdEdx_dist_count_light_short,"uds-jets","lp");
  leg1_short->SetFillColor(0);
  leg1_short->SetLineColor(0);
  leg1_short->SetShadowColor(0);
  leg1_short->Draw();
  
  QQBARLabel2(0.22,0.3, "|d|>5");
  QQBARLabel2(0.4,0.3, "-5<d<-2");
  QQBARLabel2(0.6,0.3, "-2<d<2");
  QQBARLabel2(0.805,0.3, "2<d<5");

  TCanvas* c_dist_count2_short = new TCanvas("c_dist_count2_short","c_dist_count2_short",800,800);
  c_dist_count2_short->cd(1);
  c_dist_count2_short->SetGrid();
  kdEdx_dist_count_b2_short->GetXaxis()->SetTitle("K_{dEdx} distance");
  //kdEdx_dist_count_b2->GetXaxis()->SetTitle("(dEdx-dEdx_{exp-kaon})/#Delta_{dEdx}");                                                                                                                                                                                                     
  kdEdx_dist_count_b2_short->GetYaxis()->SetTitle("Entries (pfos)");
  kdEdx_dist_count_b2_short->GetYaxis()->SetTitleOffset(1.25);
  kdEdx_dist_count_b2_short->GetXaxis()->SetTitleOffset(1.);
  kdEdx_dist_count_b2_short->GetXaxis()->SetLabelSize(0);
  //kdEdx_dist_count_b2->GetYaxis()->SetRangeUser(0,100);                                                                                                                                                                                                                                        

  float e_count_b2_short=kdEdx_dist_count_b2_short->Integral();
  float e_count_c2_short=kdEdx_dist_count_c2_short->Integral();
  float e_count_light2_short=kdEdx_dist_count_light2_short->Integral();
  kdEdx_dist_count_b2_short->SetLineColor(2);
  kdEdx_dist_count_b2_short->SetLineWidth(3);
  //kdEdx_dist_count_b->SetLineStyle(2);                                                                                                                                                                                                                                                       
  kdEdx_dist_count_b2_short->Scale(1/e_count_b2);
  kdEdx_dist_count_b2_short->Draw("histo");
  kdEdx_dist_count_c2_short->SetLineColor(4);
  kdEdx_dist_count_c2_short->SetLineWidth(3);
  //kdEdx_dist_count_c2->SetLineStyle(2);                                                                                                                                                                                                                                                      
  kdEdx_dist_count_c2_short->Scale(1/e_count_c2);
  kdEdx_dist_count_c2_short->Draw("histosame");
  kdEdx_dist_count_light2_short->SetLineColor(3);
  kdEdx_dist_count_light2_short->SetLineWidth(3);
  //kdEdx_dist_count_light2->SetLineStyle(2);                                                                                                                                                                                                                                                  
  kdEdx_dist_count_light2_short->Scale(1/e_count_light2);
  kdEdx_dist_count_light2_short->Draw("histosame");

  Labels("eR",tracks,cut,cat);
  TLegend *leg12_short = new TLegend(0.3,0.65,0.5,0.75);
  leg12_short->SetTextSize(0.035);
  leg12_short->SetTextFont(42);
  leg12_short->AddEntry(kdEdx_dist_count_b2_short,"b-jets","lp");
  leg12_short->AddEntry(kdEdx_dist_count_c2_short,"c-jets","lp");
  leg12_short->AddEntry(kdEdx_dist_count_light2_short,"uds-jets","lp");
  leg12_short->SetFillColor(0);
  leg12_short->SetLineColor(0);
  leg12_short->SetShadowColor(0);
  leg12_short->Draw();

  QQBARLabel2(0.22,0.3, "|d|>5");
  QQBARLabel2(0.4,0.3, "-5<d<-2");
  QQBARLabel2(0.6,0.3, "-2<d<2");
  QQBARLabel2(0.805,0.3, "2<d<5");
  
}

void Ratios_dEdx(TString filename_b, TString filename_b2, TString filename_c, TString filename_c2, TString filename_light, TString filename_light2, TString tracks, TString cut, TString cat){

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);                                                                                                    
  TFile *f_b = new TFile(filename_b);
  TFile *f_c = new TFile(filename_c);
  TFile *f_light = new TFile(filename_light);
  TH1F*  ratio_pi_k_b = (TH1F*)f_b->Get("kdEdx_dist_ratio_pi_k");
  TH1F*  ratio_pi_k_c = (TH1F*)f_c->Get("kdEdx_dist_ratio_pi_k");
  TH1F*  ratio_pi_k_light = (TH1F*)f_light->Get("kdEdx_dist_ratio_pi_k");
  TH1F*  ratio_pi_p_b = (TH1F*)f_b->Get("kdEdx_dist_ratio_pi_p");
  TH1F*  ratio_pi_p_c = (TH1F*)f_c->Get("kdEdx_dist_ratio_pi_p");
  TH1F*  ratio_pi_p_light = (TH1F*)f_light->Get("kdEdx_dist_ratio_pi_p");
  TH1F*  ratio_k_p_b = (TH1F*)f_b->Get("kdEdx_dist_ratio_k_p");
  TH1F*  ratio_k_p_c = (TH1F*)f_c->Get("kdEdx_dist_ratio_k_p");
  TH1F*  ratio_k_p_light = (TH1F*)f_light->Get("kdEdx_dist_ratio_k_p");
  /*float entries_b = ratio_pi_k_b->GetEntries();                                                                                                            
  float entries_c = ratio_pi_k_c->GetEntries();                                                 
  float entries_light = ratio_pi_k_light->GetEntries();*/
  float entries_pi_k_b = ratio_pi_k_b->Integral();
  float entries_pi_k_c = ratio_pi_k_c->Integral();
  float entries_pi_k_light = ratio_pi_k_light->Integral();
  float entries_pi_p_b = ratio_pi_p_b->Integral();
  float entries_pi_p_c = ratio_pi_p_c->Integral();
  float entries_pi_p_light = ratio_pi_p_light->Integral();
  float entries_k_p_b = ratio_k_p_b->Integral();
  float entries_k_p_c = ratio_k_p_c->Integral();
  float entries_k_p_light = ratio_k_p_light->Integral();
  
  cout<<entries_pi_k_b<<" "<<entries_pi_k_c<<" "<<entries_pi_k_light<<endl;

  TFile *f_b2 = new TFile(filename_b2);
  TFile *f_c2 = new TFile(filename_c2);
  TFile *f_light2 = new TFile(filename_light2);
  TH1F*  ratio_pi_k_b2 = (TH1F*)f_b2->Get("kdEdx_dist_ratio_pi_k");
  TH1F*  ratio_pi_k_c2 = (TH1F*)f_c2->Get("kdEdx_dist_ratio_pi_k");
  TH1F*  ratio_pi_k_light2 = (TH1F*)f_light2->Get("kdEdx_dist_ratio_pi_k");
  TH1F*  ratio_pi_p_b2 = (TH1F*)f_b2->Get("kdEdx_dist_ratio_pi_p");
  TH1F*  ratio_pi_p_c2 = (TH1F*)f_c2->Get("kdEdx_dist_ratio_pi_p");
  TH1F*  ratio_pi_p_light2 = (TH1F*)f_light2->Get("kdEdx_dist_ratio_pi_p");
  TH1F*  ratio_k_p_b2 = (TH1F*)f_b2->Get("kdEdx_dist_ratio_k_p");
  TH1F*  ratio_k_p_c2 = (TH1F*)f_c2->Get("kdEdx_dist_ratio_k_p");
  TH1F*  ratio_k_p_light2 = (TH1F*)f_light2->Get("kdEdx_dist_ratio_k_p");
  /*float entries_b2 = ratio_pi_k_b2->GetEntries();
  float entries_c2 = ratio_pi_k_c2->GetEntries();
  float entries_light2 = ratio_pi_k_light2->GetEntries();*/
  float entries_pi_k_b2 = ratio_pi_k_b2->Integral();
  float entries_pi_k_c2 = ratio_pi_k_c2->Integral();
  float entries_pi_k_light2 = ratio_pi_k_light2->Integral();
  float entries_pi_p_b2 = ratio_pi_p_b2->Integral();
  float entries_pi_p_c2 = ratio_pi_p_c2->Integral();
  float entries_pi_p_light2 = ratio_pi_p_light2->Integral();
  float entries_k_p_b2 = ratio_k_p_b2->Integral();
  float entries_k_p_c2 = ratio_k_p_c2->Integral();
  float entries_k_p_light2 = ratio_k_p_light2->Integral();

  TCanvas* c_ratio_pi_k = new TCanvas("c_ratio_pi_k","c_ratio_pi_k",800,800);
  c_ratio_pi_k->cd(1);
  c_ratio_pi_k->SetGrid();
  ratio_pi_k_b->GetXaxis()->SetTitle("Estimated #pi/K");
  ratio_pi_k_b->GetYaxis()->SetTitle("Entries (jets)");
  ratio_pi_k_b->GetYaxis()->SetTitleOffset(1.25);
  ratio_pi_k_b->GetXaxis()->SetTitleOffset(1.);
  ratio_pi_k_b->SetLineColor(2);
  ratio_pi_k_b->SetLineWidth(3);
  ratio_pi_k_b->Scale(1/entries_pi_k_b);
  ratio_pi_k_b->GetYaxis()->SetRangeUser(0,0.5);
  ratio_pi_k_b->Draw("histo");
  ratio_pi_k_c->SetLineColor(4);
  ratio_pi_k_c->SetLineWidth(3);
  ratio_pi_k_c->Scale(1/entries_pi_k_c);
  ratio_pi_k_c->Draw("histosame");
  ratio_pi_k_light->SetLineColor(3);
  ratio_pi_k_light->SetLineWidth(3);
  ratio_pi_k_light->Scale(1/entries_pi_k_light);
  ratio_pi_k_light->Draw("histosame");
  Labels("eL",tracks,cut,cat);
  TLegend *leg = new TLegend(0.6,0.55,0.8,0.65);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  leg->AddEntry(ratio_pi_k_b,"b-jets","lp");
  leg->AddEntry(ratio_pi_k_c,"c-jets","lp");
  leg->AddEntry(ratio_pi_k_light,"uds-jets","lp");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

  TCanvas* c_ratio_pi_k2 = new TCanvas("c_ratio_pi_k2","c_ratio_pi_k2",800,800);
  c_ratio_pi_k2->cd(1);
  c_ratio_pi_k2->SetGrid();
  ratio_pi_k_b2->GetXaxis()->SetTitle("Estimated #pi/K");
  ratio_pi_k_b2->GetYaxis()->SetTitle("Entries (jets)");
  ratio_pi_k_b2->GetYaxis()->SetTitleOffset(1.25);
  ratio_pi_k_b2->GetXaxis()->SetTitleOffset(1.);
  ratio_pi_k_b2->SetLineColor(2);
  ratio_pi_k_b2->SetLineWidth(3);
  ratio_pi_k_b2->Scale(1/entries_pi_k_b2);
  ratio_pi_k_b2->GetYaxis()->SetRangeUser(0,0.5);
  ratio_pi_k_b2->Draw("histo");
  ratio_pi_k_c2->SetLineColor(4);
  ratio_pi_k_c2->SetLineWidth(3);
  ratio_pi_k_c2->Scale(1/entries_pi_k_c2);
  ratio_pi_k_c2->Draw("histosame");
  ratio_pi_k_light2->SetLineColor(3);
  ratio_pi_k_light2->SetLineWidth(3);
  ratio_pi_k_light2->Scale(1/entries_pi_k_light2);
  ratio_pi_k_light2->Draw("histosame");
  Labels("eR",tracks,cut,cat);
  leg->Draw();

  TCanvas* c_ratio_pi_p = new TCanvas("c_ratio_pi_p","c_ratio_pi_p",800,800);
  c_ratio_pi_p->cd(1);
  c_ratio_pi_p->SetGrid();
  ratio_pi_p_b->GetXaxis()->SetTitle("Estimated #pi/p");
  ratio_pi_p_b->GetYaxis()->SetTitle("Entries (jets)");
  ratio_pi_p_b->GetYaxis()->SetTitleOffset(1.25);
  ratio_pi_p_b->GetXaxis()->SetTitleOffset(1.);
  ratio_pi_p_b->SetLineColor(2);
  ratio_pi_p_b->SetLineWidth(3);
  ratio_pi_p_b->Scale(1/entries_pi_p_b);
  ratio_pi_p_b->GetYaxis()->SetRangeUser(0,0.7);
  ratio_pi_p_b->Draw("histo");
  ratio_pi_p_c->SetLineColor(4);
  ratio_pi_p_c->SetLineWidth(3);
  ratio_pi_p_c->Scale(1/entries_pi_p_c);
  ratio_pi_p_c->Draw("histosame");
  ratio_pi_p_light->SetLineColor(3);
  ratio_pi_p_light->SetLineWidth(3);
  ratio_pi_p_light->Scale(1/entries_pi_p_light);
  ratio_pi_p_light->Draw("histosame");
  Labels("eL",tracks,cut,cat);
  leg->Draw();
  
  TCanvas* c_ratio_pi_p2 = new TCanvas("c_ratio_pi_p2","c_ratio_pi_p2",800,800);
  c_ratio_pi_p2->cd(1);
  c_ratio_pi_p2->SetGrid();
  ratio_pi_p_b2->GetXaxis()->SetTitle("Estimated #pi/p");
  ratio_pi_p_b2->GetYaxis()->SetTitle("Entries (jets)");
  ratio_pi_p_b2->GetYaxis()->SetTitleOffset(1.25);
  ratio_pi_p_b2->GetXaxis()->SetTitleOffset(1.);
  ratio_pi_p_b2->SetLineColor(2);
  ratio_pi_p_b2->SetLineWidth(3);
  ratio_pi_p_b2->Scale(1/entries_pi_p_b2);
  ratio_pi_p_b2->GetYaxis()->SetRangeUser(0,0.7);
  ratio_pi_p_b2->Draw("histo");
  ratio_pi_p_c2->SetLineColor(4);
  ratio_pi_p_c2->SetLineWidth(3);
  ratio_pi_p_c2->Scale(1/entries_pi_p_c2);
  ratio_pi_p_c2->Draw("histosame");
  ratio_pi_p_light2->SetLineColor(3);
  ratio_pi_p_light2->SetLineWidth(3);
  ratio_pi_p_light2->Scale(1/entries_pi_p_light2);
  ratio_pi_p_light2->Draw("histosame");
  Labels("eR",tracks,cut,cat);
  leg->Draw();

  TCanvas* c_ratio_k_p = new TCanvas("c_ratio_k_p","c_ratio_k_p",800,800);
  c_ratio_k_p->cd(1);
  c_ratio_k_p->SetGrid();
  ratio_k_p_b->GetXaxis()->SetTitle("Estimated K/p");
  ratio_k_p_b->GetYaxis()->SetTitle("Entries (jets)");
  ratio_k_p_b->GetYaxis()->SetTitleOffset(1.25);
  ratio_k_p_b->GetXaxis()->SetTitleOffset(1.);
  ratio_k_p_b->SetLineColor(2);
  ratio_k_p_b->SetLineWidth(3);
  ratio_k_p_b->Scale(1/entries_k_p_b);
  ratio_k_p_b->GetYaxis()->SetRangeUser(0,0.7);
  ratio_k_p_b->Draw("histo");
  ratio_k_p_c->SetLineColor(4);
  ratio_k_p_c->SetLineWidth(3);
  ratio_k_p_c->Scale(1/entries_k_p_c);
  ratio_k_p_c->Draw("histosame");
  ratio_k_p_light->SetLineColor(3);
  ratio_k_p_light->SetLineWidth(3);
  ratio_k_p_light->Scale(1/entries_k_p_light);
  ratio_k_p_light->Draw("histosame");
  Labels("eL",tracks,cut,cat);
  leg->Draw();

  TCanvas* c_ratio_k_p2 = new TCanvas("c_ratio_k_p2","c_ratio_k_p2",800,800);
  c_ratio_k_p2->cd(1);
  c_ratio_k_p2->SetGrid();
  ratio_k_p_b2->GetXaxis()->SetTitle("Estimated K/p");
  ratio_k_p_b2->GetYaxis()->SetTitle("Entries (jets)");
  ratio_k_p_b2->GetYaxis()->SetTitleOffset(1.25);
  ratio_k_p_b2->GetXaxis()->SetTitleOffset(1.);
  ratio_k_p_b2->SetLineColor(2);
  ratio_k_p_b2->SetLineWidth(3);
  ratio_k_p_b2->Scale(1/entries_k_p_b2);
  ratio_k_p_b2->GetYaxis()->SetRangeUser(0,0.7);
  ratio_k_p_b2->Draw("histo");
  ratio_k_p_c2->SetLineColor(4);
  ratio_k_p_c2->SetLineWidth(3);
  ratio_k_p_c2->Scale(1/entries_k_p_c2);
  ratio_k_p_c2->Draw("histosame");
  ratio_k_p_light2->SetLineColor(3);
  ratio_k_p_light2->SetLineWidth(3);
  ratio_k_p_light2->Scale(1/entries_k_p_light2);
  ratio_k_p_light2->Draw("histosame");
  Labels("eR",tracks,cut,cat);
  leg->Draw();

}

void Ratios_dEdx_short(TString filename_b, TString filename_b2, TString filename_c, TString filename_c2, TString filename_light, TString filename_light2, TString tracks, TString cut, TString cat){

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  TFile *f_b = new TFile(filename_b);
  TFile *f_c = new TFile(filename_c);
  TFile *f_light = new TFile(filename_light);
  TH1F*  ratio_pi_k_b = (TH1F*)f_b->Get("kdEdx_dist_ratio_pi_k_short");
  TH1F*  ratio_pi_k_c = (TH1F*)f_c->Get("kdEdx_dist_ratio_pi_k_short");
  TH1F*  ratio_pi_k_light = (TH1F*)f_light->Get("kdEdx_dist_ratio_pi_k_short");
  TH1F*  ratio_pi_p_b = (TH1F*)f_b->Get("kdEdx_dist_ratio_pi_p_short");
  TH1F*  ratio_pi_p_c = (TH1F*)f_c->Get("kdEdx_dist_ratio_pi_p_short");
  TH1F*  ratio_pi_p_light = (TH1F*)f_light->Get("kdEdx_dist_ratio_pi_p_short");
  TH1F*  ratio_k_p_b = (TH1F*)f_b->Get("kdEdx_dist_ratio_k_p_short");
  TH1F*  ratio_k_p_c = (TH1F*)f_c->Get("kdEdx_dist_ratio_k_p_short");
  TH1F*  ratio_k_p_light = (TH1F*)f_light->Get("kdEdx_dist_ratio_k_p_short");
  /*float entries_b = ratio_pi_k_b->GetEntries();                      
    float entries_c = ratio_pi_k_c->GetEntries();                                                                                                                                                                                                  float entries_light = ratio_pi_k_light->GetEntries();*/
  float entries_pi_k_b = ratio_pi_k_b->Integral();
  float entries_pi_k_c = ratio_pi_k_c->Integral();
  float entries_pi_k_light = ratio_pi_k_light->Integral();
  float entries_pi_p_b = ratio_pi_p_b->Integral();
  float entries_pi_p_c = ratio_pi_p_c->Integral();
  float entries_pi_p_light = ratio_pi_p_light->Integral();
  float entries_k_p_b = ratio_k_p_b->Integral();
  float entries_k_p_c = ratio_k_p_c->Integral();
  float entries_k_p_light = ratio_k_p_light->Integral();

  //cout<<entries_b<<" "<<entries_c<<" "<<entries_light<<endl;                                                                                                                                                                                   
  TFile *f_b2 = new TFile(filename_b2);
  TFile *f_c2 = new TFile(filename_c2);
  TFile *f_light2 = new TFile(filename_light2);
  TH1F*  ratio_pi_k_b2 = (TH1F*)f_b2->Get("kdEdx_dist_ratio_pi_k_short");
  TH1F*  ratio_pi_k_c2 = (TH1F*)f_c2->Get("kdEdx_dist_ratio_pi_k_short");
  TH1F*  ratio_pi_k_light2 = (TH1F*)f_light2->Get("kdEdx_dist_ratio_pi_k_short");
  TH1F*  ratio_pi_p_b2 = (TH1F*)f_b2->Get("kdEdx_dist_ratio_pi_p_short");
  TH1F*  ratio_pi_p_c2 = (TH1F*)f_c2->Get("kdEdx_dist_ratio_pi_p_short");
  TH1F*  ratio_pi_p_light2 = (TH1F*)f_light2->Get("kdEdx_dist_ratio_pi_p_short");
  TH1F*  ratio_k_p_b2 = (TH1F*)f_b2->Get("kdEdx_dist_ratio_k_p_short");
  TH1F*  ratio_k_p_c2 = (TH1F*)f_c2->Get("kdEdx_dist_ratio_k_p_short");
  TH1F*  ratio_k_p_light2 = (TH1F*)f_light2->Get("kdEdx_dist_ratio_k_p_short");
  /*float entries_b2 = ratio_pi_k_b2->GetEntries();                                                                                                                                                                                                float entries_c2 = ratio_pi_k_c2->GetEntries();                                                                                                                                                                                              float entries_light2 = ratio_pi_k_light2->GetEntries();*/
  float entries_pi_k_b2 = ratio_pi_k_b2->Integral();
  float entries_pi_k_c2 = ratio_pi_k_c2->Integral();
  float entries_pi_k_light2 = ratio_pi_k_light2->Integral();
  float entries_pi_p_b2 = ratio_pi_p_b2->Integral();
  float entries_pi_p_c2 = ratio_pi_p_c2->Integral();
  float entries_pi_p_light2 = ratio_pi_p_light2->Integral();
  float entries_k_p_b2 = ratio_k_p_b2->Integral();
  float entries_k_p_c2 = ratio_k_p_c2->Integral();
  float entries_k_p_light2 = ratio_k_p_light2->Integral();

  TCanvas* c_ratio_pi_k_short = new TCanvas("c_ratio_pi_k_short","c_ratio_pi_k_short",800,800);
  c_ratio_pi_k_short->cd(1);
  c_ratio_pi_k_short->SetGrid();
  ratio_pi_k_b->GetXaxis()->SetTitle("Estimated #pi/K (5#sigma ver.)");
  ratio_pi_k_b->GetYaxis()->SetTitle("Entries (jets)");
  ratio_pi_k_b->GetYaxis()->SetTitleOffset(1.25);
  ratio_pi_k_b->GetXaxis()->SetTitleOffset(1.);
  ratio_pi_k_b->SetLineColor(2);
  ratio_pi_k_b->SetLineWidth(3);
  ratio_pi_k_b->Scale(1/entries_pi_k_b);
  ratio_pi_k_b->GetYaxis()->SetRangeUser(0,0.5);
  ratio_pi_k_b->Draw("histo");
  ratio_pi_k_c->SetLineColor(4);
  ratio_pi_k_c->SetLineWidth(3);
  ratio_pi_k_c->Scale(1/entries_pi_k_c);
  ratio_pi_k_c->Draw("histosame");
  ratio_pi_k_light->SetLineColor(3);
  ratio_pi_k_light->SetLineWidth(3);
  ratio_pi_k_light->Scale(1/entries_pi_k_light);
  ratio_pi_k_light->Draw("histosame");
  Labels("eL",tracks,cut,cat);
  TLegend *leg = new TLegend(0.6,0.55,0.8,0.65);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  leg->AddEntry(ratio_pi_k_b,"b-jets","lp");
  leg->AddEntry(ratio_pi_k_c,"c-jets","lp");
  leg->AddEntry(ratio_pi_k_light,"uds-jets","lp");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

  TCanvas* c_ratio_pi_k2_short = new TCanvas("c_ratio_pi_k2_short","c_ratio_pi_k2_short",800,800);
  c_ratio_pi_k2_short->cd(1);
  c_ratio_pi_k2_short->SetGrid();
  ratio_pi_k_b2->GetXaxis()->SetTitle("Estimated #pi/K (5#sigma ver.)");
  ratio_pi_k_b2->GetYaxis()->SetTitle("Entries (jets)");
  ratio_pi_k_b2->GetYaxis()->SetTitleOffset(1.25);
  ratio_pi_k_b2->GetXaxis()->SetTitleOffset(1.);
  ratio_pi_k_b2->SetLineColor(2);
  ratio_pi_k_b2->SetLineWidth(3);
  ratio_pi_k_b2->Scale(1/entries_pi_k_b2);
  ratio_pi_k_b2->GetYaxis()->SetRangeUser(0,0.5);
  ratio_pi_k_b2->Draw("histo");
  ratio_pi_k_c2->SetLineColor(4);
  ratio_pi_k_c2->SetLineWidth(3);
  ratio_pi_k_c2->Scale(1/entries_pi_k_c2);
  ratio_pi_k_c2->Draw("histosame");
  ratio_pi_k_light2->SetLineColor(3);
  ratio_pi_k_light2->SetLineWidth(3);
  ratio_pi_k_light2->Scale(1/entries_pi_k_light2);
  ratio_pi_k_light2->Draw("histosame");
  Labels("eR",tracks,cut,cat);
  leg->Draw();

  TCanvas* c_ratio_pi_p_short = new TCanvas("c_ratio_pi_p_short","c_ratio_pi_p_short",800,800);
  c_ratio_pi_p_short->cd(1);
  c_ratio_pi_p_short->SetGrid();
  ratio_pi_p_b->GetXaxis()->SetTitle("Estimated #pi/p (5#sigma ver.)");
  ratio_pi_p_b->GetYaxis()->SetTitle("Entries (jets)");
  ratio_pi_p_b->GetYaxis()->SetTitleOffset(1.25);
  ratio_pi_p_b->GetXaxis()->SetTitleOffset(1.);
  ratio_pi_p_b->SetLineColor(2);
  ratio_pi_p_b->SetLineWidth(3);
  ratio_pi_p_b->Scale(1/entries_pi_p_b);
  ratio_pi_p_b->GetYaxis()->SetRangeUser(0,0.7);
  ratio_pi_p_b->Draw("histo");
  ratio_pi_p_c->SetLineColor(4);
  ratio_pi_p_c->SetLineWidth(3);
  ratio_pi_p_c->Scale(1/entries_pi_p_c);
  ratio_pi_p_c->Draw("histosame");
  ratio_pi_p_light->SetLineColor(3);
  ratio_pi_p_light->SetLineWidth(3);
  ratio_pi_p_light->Scale(1/entries_pi_p_light);
  ratio_pi_p_light->Draw("histosame");
  Labels("eL",tracks,cut,cat);
  leg->Draw();

  TCanvas* c_ratio_pi_p2_short = new TCanvas("c_ratio_pi_p2_short","c_ratio_pi_p2_short",800,800);
  c_ratio_pi_p2_short->cd(1);
  c_ratio_pi_p2_short->SetGrid();
  ratio_pi_p_b2->GetXaxis()->SetTitle("Estimated #pi/p (5#sigma ver.)");
  ratio_pi_p_b2->GetYaxis()->SetTitle("Entries (jets)");
  ratio_pi_p_b2->GetYaxis()->SetTitleOffset(1.25);
  ratio_pi_p_b2->GetXaxis()->SetTitleOffset(1.);
  ratio_pi_p_b2->SetLineColor(2);
  ratio_pi_p_b2->SetLineWidth(3);
  ratio_pi_p_b2->Scale(1/entries_pi_p_b2);
  ratio_pi_p_b2->GetYaxis()->SetRangeUser(0,0.7);
  ratio_pi_p_b2->Draw("histo");
  ratio_pi_p_c2->SetLineColor(4);
  ratio_pi_p_c2->SetLineWidth(3);
  ratio_pi_p_c2->Scale(1/entries_pi_p_c2);
  ratio_pi_p_c2->Draw("histosame");
  ratio_pi_p_light2->SetLineColor(3);
  ratio_pi_p_light2->SetLineWidth(3);
  ratio_pi_p_light2->Scale(1/entries_pi_p_light2);
  ratio_pi_p_light2->Draw("histosame");
  Labels("eR",tracks,cut,cat);
  leg->Draw();

  TCanvas* c_ratio_k_p_short = new TCanvas("c_ratio_k_p_short","c_ratio_k_p_short",800,800);
  c_ratio_k_p_short->cd(1);
  c_ratio_k_p_short->SetGrid();
  ratio_k_p_b->GetXaxis()->SetTitle("Estimated K/p (5#sigma ver.)");
  ratio_k_p_b->GetYaxis()->SetTitle("Entries (jets)");
  ratio_k_p_b->GetYaxis()->SetTitleOffset(1.25);
  ratio_k_p_b->GetXaxis()->SetTitleOffset(1.);
  ratio_k_p_b->SetLineColor(2);
  ratio_k_p_b->SetLineWidth(3);
  ratio_k_p_b->Scale(1/entries_k_p_b);
  ratio_k_p_b->GetYaxis()->SetRangeUser(0,0.7);
  ratio_k_p_b->Draw("histo");
  ratio_k_p_c->SetLineColor(4);
  ratio_k_p_c->SetLineWidth(3);
  ratio_k_p_c->Scale(1/entries_k_p_c);
  ratio_k_p_c->Draw("histosame");
  ratio_k_p_light->SetLineColor(3);
  ratio_k_p_light->SetLineWidth(3);
  ratio_k_p_light->Scale(1/entries_k_p_light);
  ratio_k_p_light->Draw("histosame");
  Labels("eL",tracks,cut,cat);
  leg->Draw();

  TCanvas* c_ratio_k_p2_short = new TCanvas("c_ratio_k_p2_short","c_ratio_k_p2_short",800,800);
  c_ratio_k_p2_short->cd(1);
  c_ratio_k_p2_short->SetGrid();
  ratio_k_p_b2->GetXaxis()->SetTitle("Estimated K/p (5#sigma ver.)");
  ratio_k_p_b2->GetYaxis()->SetTitle("Entries (jets)");
  ratio_k_p_b2->GetYaxis()->SetTitleOffset(1.25);
  ratio_k_p_b2->GetXaxis()->SetTitleOffset(1.);
  ratio_k_p_b2->SetLineColor(2);
  ratio_k_p_b2->SetLineWidth(3);
  ratio_k_p_b2->Scale(1/entries_k_p_b2);
  ratio_k_p_b2->GetYaxis()->SetRangeUser(0,0.7);
  ratio_k_p_b2->Draw("histo");
  ratio_k_p_c2->SetLineColor(4);
  ratio_k_p_c2->SetLineWidth(3);
  ratio_k_p_c2->Scale(1/entries_k_p_c2);
  ratio_k_p_c2->Draw("histosame");
  ratio_k_p_light2->SetLineColor(3);
  ratio_k_p_light2->SetLineWidth(3);
  ratio_k_p_light2->Scale(1/entries_k_p_light2);
  ratio_k_p_light2->Draw("histosame");
  Labels("eR",tracks,cut,cat);
  leg->Draw();

}



void Plots_ratios_dEdx(TString tracks, TString cut, TString cat) {
    
  TString filename_b ="../output/output_500_"+tracks+"_tracks_"+cat+"_500GeV_eL_pR_cut_"+cut+"_bquark"+".root";
  TString filename_b2 ="../output/output_500_"+tracks+"_tracks_"+cat+"_500GeV_eR_pL_cut_"+cut+"_bquark"+".root";
  TString filename_c ="../output/output_500_"+tracks+"_tracks_"+cat+"_500GeV_eL_pR_cut_"+cut+"_cquark"+".root";
  TString filename_c2 ="../output/output_500_"+tracks+"_tracks_"+cat+"_500GeV_eR_pL_cut_"+cut+"_cquark"+".root";
  TString filename_light ="../output/output_500_"+tracks+"_tracks_"+cat+"_500GeV_eL_pR_cut_"+cut+"_lightquark"+".root";
  TString filename_light2 ="../output/output_500_"+tracks+"_tracks_"+cat+"_500GeV_eR_pL_cut_"+cut+"_lightquark"+".root";

  NoCheat_dEdx(filename_b,filename_b2,filename_c,filename_c2,filename_light,filename_light2,tracks,cut,cat);
  Ratios_dEdx(filename_b,filename_b2,filename_c,filename_c2,filename_light,filename_light2,tracks,cut,cat);
  Ratios_dEdx_short(filename_b,filename_b2,filename_c,filename_c2,filename_light,filename_light2,tracks,cut,cat);
}
