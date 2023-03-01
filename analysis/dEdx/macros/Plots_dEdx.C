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

void Labels(TString pol, TString tracks, TString cut, TString cat, TString quark){
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

  TString quark_string;
  if(quark=="light")quark_string="uds-jets";
  else if(quark=="c")quark_string="c-jets";
  else if(quark=="b")quark_string="b-jets";

  TString mom_string;
  if(cut=="0")mom_string="";
  else mom_string="p_{track} > "+cut+" GeV";

  TString cat_string;
  if(cat=="catA")cat_string="Cat. A";
  else if(cat=="catB")cat_string="Cat. B";
  else if(cat=="catC")cat_string="Cat. C";
  else if(cat=="catD")cat_string="Cat. D";
  else cat_string="All categories";
  QQBARLabel2(0.3,0.82, track_string+" tracks in "+quark_string,kGray+4);
  QQBARLabel2(0.3,0.78, cat_string,kGray+4);
  QQBARLabel2(0.5,0.965, "Work in progress",kRed+2);
  QQBARLabel2(0.075,0.025, "K_{#gamma} < 50 GeV, |cos#theta| < 0.95",kGray+2);
  QQBARLabel2(0.075,0.075,mom_string,kGray+2); //mom_string
}

void EffPurity_default(TString filename, TString filename2, TString secondary, TString cat, TString cut, TString quark){
 
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  //*-------------  
  //TString filename = "../output/250GeV_IO_false_quark4_eL_pR.root";
  TFile *f = new TFile(filename);

  TH1F*  p_kaon = (TH1F*)f->Get("p_kaon");
  
  TH1F*  prob_pi_kaon = (TH1F*)f->Get("pi_prob_kaon_method2");
  TH1F*  prob_pi_pion = (TH1F*)f->Get("pi_prob_pion_method2");
  TH1F*  prob_pi_proton = (TH1F*)f->Get("pi_prob_proton_method2");
  TH1F*  prob_pi_muon = (TH1F*)f->Get("pi_prob_muon_method2");
  TH1F*  prob_pi_electron = (TH1F*)f->Get("pi_prob_electron_method2");
  float nkaons=p_kaon->GetEntries();
  
  float x[10000], eff[10000], pur[10000];
  int n=0;
  for(int i=1;i<100; i++) {
    float n_kaons=  prob_pi_kaon->Integral(0,i);
    float n_pions=  prob_pi_pion->Integral(0,i);
    float n_protons=  prob_pi_proton->Integral(0,i);
    float n_muons=  prob_pi_muon->Integral(0,i);
    float n_electrons=  prob_pi_electron->Integral(0,i);
    cout<<n_kaons<<endl;

    x[i-1]=i*1.0/100.;
    //    eff[i-1]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;
    eff[i-1]=100.*(n_kaons)/nkaons;
    pur[i-1]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n++;
  }
 
  TGraph* efficiency = new TGraph(n,x,eff);
  TGraph* purity = new TGraph(n,x,pur);
  TGraph* efficiency_purity = new TGraph(n,eff,pur);

  //*-------------                                                                                                                                                                                         
  //TString filename2 = "../output/250GeV_IO_false_quark4_eR_pL.root";
  TFile *f2 = new TFile(filename2);
  TH1F*  p_kaon2 = (TH1F*)f2->Get("p_kaon");
  TH1F*  prob_pi_kaon2 = (TH1F*)f2->Get("pi_prob_kaon_method2");
  TH1F*  prob_pi_pion2 = (TH1F*)f2->Get("pi_prob_pion_method2");
  TH1F*  prob_pi_proton2 = (TH1F*)f2->Get("pi_prob_proton_method2");
  TH1F*  prob_pi_muon2 = (TH1F*)f2->Get("pi_prob_muon_method2");
  TH1F*  prob_pi_electron2 = (TH1F*)f2->Get("pi_prob_electron_method2");
  float nkaons2=p_kaon2->GetEntries();

  float x2[10000], eff2[10000], pur2[10000];
  int n2=0;
  for(int i=1;i<100; i++) {
    float n_kaons=  prob_pi_kaon2->Integral(0,i);
    float n_pions=  prob_pi_pion2->Integral(0,i);
    float n_protons=  prob_pi_proton2->Integral(0,i);
    float n_muons=  prob_pi_muon2->Integral(0,i);
    float n_electrons=  prob_pi_electron2->Integral(0,i);
    //cout<<n_kaons<<endl;

    x2[i-1]=i*1.0/100.;
    eff2[i-1]=100.*(n_kaons)/nkaons2;
    pur2[i-1]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n2++;
  }

  TGraph* efficiency2 = new TGraph(n2,x2,eff2);
  TGraph* purity2 = new TGraph(n2,x2,pur2);
  TGraph* efficiency_purity2 = new TGraph(n2,eff2,pur2);

  //cquark=true;
  TCanvas* c_def = new TCanvas("c_def","c_def",800,800);
  c_def->cd(1);
  c_def->SetGrid();
  efficiency->GetXaxis()->SetTitle("Prob-#pi < x");
  efficiency->GetYaxis()->SetTitle("[%]");
  efficiency->GetYaxis()->SetTitleOffset(1.25);
  efficiency->GetXaxis()->SetTitleOffset(1.);
  efficiency->GetYaxis()->SetRangeUser(0,100);

  efficiency->SetLineColor(4);
  efficiency->SetLineWidth(3);
  efficiency->SetLineStyle(2);
  efficiency->Draw("alp");
  
  purity->SetLineColor(kGreen+1);
  purity->SetLineWidth(1);
  purity->SetLineStyle(1);
  purity->Draw("lp");

  
  Labels("",secondary,cat,cut,quark);

  TLegend *leg0 = new TLegend(0.6,0.8,0.8,0.9);
  leg0->SetTextSize(0.035);
  leg0->SetTextFont(42);
  leg0->AddEntry(efficiency,"Efficiency","lp");
  leg0->AddEntry(purity,"Purity","lp");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

  TCanvas* c_def2 = new TCanvas("c_def2","c_def2",800,800);
  c_def2->cd(1);
  c_def2->SetGrid();
  efficiency_purity->GetXaxis()->SetTitle("Efficiency [%]");
  efficiency_purity->GetYaxis()->SetTitle("Purity [%]");
  efficiency_purity->GetYaxis()->SetTitleOffset(1.25);
  efficiency_purity->GetXaxis()->SetTitleOffset(1.);
  efficiency_purity->GetYaxis()->SetRangeUser(0,100);

  efficiency_purity->SetLineColor(4);
  efficiency_purity->SetLineWidth(3);
  efficiency_purity->SetLineStyle(2);
  efficiency_purity->Draw("alp");

  efficiency_purity2->SetLineColor(2);
  efficiency_purity2->SetLineWidth(3);
  efficiency_purity2->SetLineStyle(1);
  efficiency_purity2->Draw("lp");


  Labels("",secondary,cat,cut,quark);

  QQBARLabel2(0.3,0.2, "Method dEdxPID",kBlack);

  TLegend *leg1 = new TLegend(0.6,0.8,0.8,0.9);
  leg1->SetTextSize(0.035);
  leg1->SetTextFont(42);
  leg1->AddEntry(efficiency_purity,"Left Polarisation","lp");
  leg1->AddEntry(efficiency_purity2,"Right Polarisation","lp");
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();
   

}


void EffPurity_dedxdist(TString filename, TString filename2, TString secondary, TString cat, TString cut, TString quark){

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  
  //TString filename = "../output/250GeV_IO_false_quark4_eL_pR.root";
  TFile *f = new TFile(filename);
  TH1F*  p_kaon = (TH1F*)f->Get("p_kaon");
  TH1F*  kdEdxdist_kaon = (TH1F*)f->Get("kdEdx_dist_kaon");
  TH1F*  kdEdxdist_pion = (TH1F*)f->Get("kdEdx_dist_pion");
  TH1F*  kdEdxdist_proton = (TH1F*)f->Get("kdEdx_dist_proton");
  TH1F*  kdEdxdist_muon = (TH1F*)f->Get("kdEdx_dist_muon");
  TH1F*  kdEdxdist_electron = (TH1F*)f->Get("kdEdx_dist_electron");
  float nkaons=p_kaon->GetEntries();
  
  float x[10000], eff[10000], pur[10000];
  int n=0;
  for(int i=16;i<25; i++) {
    float n_kaons=  kdEdxdist_kaon->Integral(16,i);
    float n_pions=  kdEdxdist_pion->Integral(16,i);
    float n_protons=  kdEdxdist_proton->Integral(16,i);
    float n_muons=  kdEdxdist_muon->Integral(16,i);
    float n_electrons=  kdEdxdist_electron->Integral(16,i);
    x[i-16]=i;
    //    eff[i-16]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;
    eff[i-16]=100.*(n_kaons)/nkaons;                    
    pur[i-16]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n++;
  }
 
  TGraph* efficiency = new TGraph(n,x,eff);
  TGraph* purity = new TGraph(n,x,pur);
  TGraph* efficiency_purity = new TGraph(n,eff,pur);

  //----------
  //TString filename2 = "../output/250GeV_IO_false_quark4_eR_pL.root";
  TFile *f2 = new TFile(filename2);
  TH1F*  p_kaon2 = (TH1F*)f2->Get("p_kaon");
  TH1F*  kdEdxdist_kaon2 = (TH1F*)f2->Get("kdEdx_dist_kaon");
  TH1F*  kdEdxdist_pion2 = (TH1F*)f2->Get("kdEdx_dist_pion");
  TH1F*  kdEdxdist_proton2 = (TH1F*)f2->Get("kdEdx_dist_proton");
  TH1F*  kdEdxdist_muon2 = (TH1F*)f2->Get("kdEdx_dist_muon");
  TH1F*  kdEdxdist_electron2 = (TH1F*)f2->Get("kdEdx_dist_electron");
  float nkaons2=p_kaon2->GetEntries();

  float x2[10000], eff2[10000], pur2[10000];
  int n2=0;
  for(int i=16;i<25; i++) {
    float n_kaons=  kdEdxdist_kaon2->Integral(16,i);
    float n_pions=  kdEdxdist_pion2->Integral(16,i);
    float n_protons=  kdEdxdist_proton2->Integral(16,i);
    float n_muons=  kdEdxdist_muon2->Integral(16,i);
    float n_electrons=  kdEdxdist_electron2->Integral(16,i);
    x2[i-16]=i;
    //    eff[i-16]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;                     
    eff2[i-16]=100.*(n_kaons)/nkaons2;
    pur2[i-16]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n2++;
  }

  TGraph* efficiency2 = new TGraph(n2,x2,eff2);
  TGraph* purity2 = new TGraph(n2,x2,pur2);
  TGraph* efficiency_purity2 = new TGraph(n2,eff2,pur2);

  TCanvas* c_dist = new TCanvas("c_dist","c_dist",800,800);
  c_dist->cd(1);
  c_dist->SetGrid();
  efficiency->GetXaxis()->SetTitle("i");
  efficiency->GetYaxis()->SetTitle("[%]");
  efficiency->GetYaxis()->SetTitleOffset(1.25);
  efficiency->GetXaxis()->SetTitleOffset(1.);
  efficiency->GetYaxis()->SetRangeUser(0,100);

  efficiency->SetLineColor(4);
  efficiency->SetLineWidth(3);
  efficiency->SetLineStyle(2);
  efficiency->Draw("alp");
  
  purity->SetLineColor(kGreen+1);
  purity->SetLineWidth(1);
  purity->SetLineStyle(1);
  purity->Draw("lp");

  
  Labels("",secondary,cat,cut,quark);
  
  TLegend *leg0 = new TLegend(0.2,0.2,0.5,0.4);
  leg0->SetTextSize(0.035);
  leg0->SetTextFont(42);
  leg0->AddEntry(efficiency,"Efficiency","lp");
  leg0->AddEntry(purity,"Purity","lp");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

  TCanvas* c_dist2 = new TCanvas("c_dist2","c_dist2",800,800);
  c_dist2->cd(1);
  c_dist2->SetGrid();
  efficiency_purity->GetXaxis()->SetTitle("Efficiency [%]");
  efficiency_purity->GetYaxis()->SetTitle("Purity [%]");
  efficiency_purity->GetYaxis()->SetTitleOffset(1.25);
  efficiency_purity->GetXaxis()->SetTitleOffset(1.);
  efficiency_purity->GetYaxis()->SetRangeUser(0,100);

  efficiency_purity->SetLineColor(4);
  efficiency_purity->SetLineWidth(3);
  efficiency_purity->SetLineStyle(2);
  efficiency_purity->Draw("alp");

  efficiency_purity2->SetLineColor(2);
  efficiency_purity2->SetLineWidth(3);
  efficiency_purity2->SetLineStyle(1);
  efficiency_purity2->Draw("lp");

  Labels("",secondary,cat,cut,quark);

  QQBARLabel2(0.3,0.2, "Method dEdx-distance",kBlack);
  TLegend *leg1 = new TLegend(0.2,0.8,0.5,0.9);
  leg1->SetTextSize(0.035);
  leg1->SetTextFont(42);
  leg1->AddEntry(efficiency_purity,"Left Polarisation","lp");
  leg1->AddEntry(efficiency_purity2,"Right Polarisation","lp");
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();
   

}


void EffPurity_dedxdist3(TString filename, TString filename2, TString secondary, TString cat, TString cut, TString quark){

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  
  //TString filename = "../output/250GeV_IO_false_quark4_eL_pR.root";
  TFile *f = new TFile(filename);
  TH2F*  kdEdxdist_kaon = (TH2F*)f->Get("p_kdEdx_dist_kaon");
  TH2F*  kdEdxdist_pion = (TH2F*)f->Get("p_kdEdx_dist_pion");
  TH2F*  kdEdxdist_proton = (TH2F*)f->Get("p_kdEdx_dist_proton");
  TH2F*  kdEdxdist_muon = (TH2F*)f->Get("p_kdEdx_dist_muon");
  TH2F*  kdEdxdist_electron = (TH2F*)f->Get("p_kdEdx_dist_electron");
  
  float x[100], eff[100], pur[100];
  int n=0;
  //  option 1, 80eff, 92 pur = 16,21
  //  option 1, 87eff, 87 pur = 16,23

  for(int i=2;i<60; i++) {
    float n_kaons=  kdEdxdist_kaon->Integral(i, i,16,22);
    float n_pions=  kdEdxdist_pion->Integral(i, i,16,22);
    float n_protons=  kdEdxdist_proton->Integral(i, i,16,22);
    float n_muons=  kdEdxdist_muon->Integral(i, i,16,22);
    float n_electrons=  kdEdxdist_electron->Integral(i, i,16,22);
    float nkaons=  kdEdxdist_kaon->Integral(i, i,0,1000);
    x[i-2]=i-1.5;
    //    eff[i-16]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;
    eff[i-2]=100.*(n_kaons)/nkaons;                    
    pur[i-2]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n++;
  }
 
  TGraph* efficiency = new TGraph(n,x,eff);
  TGraph* purity = new TGraph(n,x,pur);
  TGraph* efficiency_purity = new TGraph(n,eff,pur);
  
  //----------
  //TString filename2 = "../output/250GeV_IO_false_quark4_eR_pL.root";
  TFile *f2 = new TFile(filename2);
  TH2F*  kdEdxdist_kaon2 = (TH2F*)f2->Get("p_kdEdx_dist_kaon");
  TH2F*  kdEdxdist_pion2 = (TH2F*)f2->Get("p_kdEdx_dist_pion");
  TH2F*  kdEdxdist_proton2 = (TH2F*)f2->Get("p_kdEdx_dist_proton");
  TH2F*  kdEdxdist_muon2 = (TH2F*)f2->Get("p_kdEdx_dist_muon");
  TH2F*  kdEdxdist_electron2 = (TH2F*)f2->Get("p_kdEdx_dist_electron");
  
  float x2[100], eff2[100], pur2[100];
  int n2=0;
  //  option 1, 80eff, 92 pur = 16,21
  //  option 1, 87eff, 87 pur = 16,23

  for(int i=2;i<60; i++) {
    float n_kaons=  kdEdxdist_kaon2->Integral(i, i,16,23);
    float n_pions=  kdEdxdist_pion2->Integral(i, i,16,23);
    float n_protons=  kdEdxdist_proton2->Integral(i, i,16,23);
    float n_muons=  kdEdxdist_muon2->Integral(i, i,16,23);
    float n_electrons=  kdEdxdist_electron2->Integral(i, i,16,23);
    float nkaons=  kdEdxdist_kaon2->Integral(i, i,0,1000);
    x2[i-2]=i-1.5;
    //    eff[i-16]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;
    eff2[i-2]=100.*(n_kaons)/nkaons;                    
    pur2[i-2]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n2++;
  }
 

  TGraph* efficiency2 = new TGraph(n2,x2,eff2);
  TGraph* purity2 = new TGraph(n2,x2,pur2);
  TGraph* efficiency_purity2 = new TGraph(n2,eff2,pur2);
  
  TCanvas* c_dist3 = new TCanvas("c_dist3","c_dist3",800,800);
  c_dist3->cd(1);
  c_dist3->SetGrid();
  efficiency->GetXaxis()->SetTitle(" momentum [GeV]");
  efficiency->GetYaxis()->SetTitle("[%]");
  efficiency->GetYaxis()->SetTitleOffset(1.25);
  efficiency->GetXaxis()->SetTitleOffset(1.);
  efficiency->GetYaxis()->SetRangeUser(0,100);

  efficiency->SetLineColor(4);
  efficiency->SetLineWidth(3);
  efficiency->SetLineStyle(2);
  efficiency->Draw("alp");
  
  purity->SetLineColor(kGreen+1);
  purity->SetLineWidth(1);
  purity->SetLineStyle(1);
  purity->Draw("lp");
  
  Labels("eL",secondary,cut,cat,quark);
  
  TLegend *leg0 = new TLegend(0.2,0.3,0.5,0.4);
  leg0->SetTextSize(0.035);
  leg0->SetTextFont(42);
  leg0->AddEntry(efficiency,"Efficiency","lp");
  leg0->AddEntry(purity,"Purity","lp");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

 TCanvas* c_dist32 = new TCanvas("c_dist32","c_dist32",800,800);
  c_dist32->cd(1);
  c_dist32->SetGrid();
  efficiency2->GetXaxis()->SetTitle(" momentum [GeV]");
  efficiency2->GetYaxis()->SetTitle("[%]");
  efficiency2->GetYaxis()->SetTitleOffset(1.25);
  efficiency2->GetXaxis()->SetTitleOffset(1.);
  efficiency2->GetYaxis()->SetRangeUser(0,100);

  efficiency2->SetLineColor(4);
  efficiency2->SetLineWidth(3);
  efficiency2->SetLineStyle(2);
  efficiency2->Draw("alp");
  
  purity2->SetLineColor(kGreen+1);
  purity2->SetLineWidth(1);
  purity2->SetLineStyle(1);
  purity2->Draw("lp");

  Labels("eR",secondary,cut,cat,quark);
  
  TLegend *leg2 = new TLegend(0.2,0.3,0.5,0.4);
  leg2->SetTextSize(0.035);
  leg2->SetTextFont(42);
  leg2->AddEntry(efficiency,"Efficiency","lp");
  leg2->AddEntry(purity,"Purity","lp");
  leg2->SetFillColor(0);
  leg2->SetLineColor(0);
  leg2->SetShadowColor(0);
  leg2->Draw();
 


}



void EffPurity_dedxdist4(TString filename, TString filename2, TString secondary, TString cat, TString cut, TString quark){

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  //TString filename = "../output/250GeV_IO_false_quark4_eL_pR.root";

  TFile *f = new TFile(filename);
  TH2F*  kdEdxdist_kaon = (TH2F*)f->Get("costheta_kdEdx_dist_kaon");
  TH2F*  kdEdxdist_pion = (TH2F*)f->Get("costheta_kdEdx_dist_pion");
  TH2F*  kdEdxdist_proton = (TH2F*)f->Get("costheta_kdEdx_dist_proton");
  TH2F*  kdEdxdist_muon = (TH2F*)f->Get("costheta_kdEdx_dist_muon");
  TH2F*  kdEdxdist_electron = (TH2F*)f->Get("costheta_kdEdx_dist_electron");
  
  float x[100], eff[100], pur[100];
  int n=0;
  //  option 1, 80eff, 92 pur = 16,21
  //  option 1, 87eff, 87 pur = 16,23


  for(int i=1;i<21; i++) {
    int ipion=22;
    if(i>16) ipion=22-(i-16);
    float n_kaons=  kdEdxdist_kaon->Integral(i, i,16,ipion);
    float n_pions=  kdEdxdist_pion->Integral(i, i,16,ipion);
    float n_protons=  kdEdxdist_proton->Integral(i, i,16,ipion);
    float n_muons=  kdEdxdist_muon->Integral(i, i,16,ipion);
    float n_electrons=  kdEdxdist_electron->Integral(i, i,16,ipion);
    float nkaons=  kdEdxdist_kaon->Integral(i, i,0,1000);
    if(nkaons==0) nkaons=10000000;
    x[i-1]=i*1./20;
    eff[i-1]=100.*(n_kaons)/nkaons;       
    //  eff2[i-1]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;                    
    pur[i-1]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n++;
  }

 
  TGraph* efficiency = new TGraph(n,x,eff);
  TGraph* purity = new TGraph(n,x,pur);
  TGraph* efficiency_purity = new TGraph(n,eff,pur);
  

  //----------
  //TString filename2 = "../output/250GeV_IO_false_quark4_eR_pL.root";
  TFile *f2 = new TFile(filename2);
  TH2F*  kdEdxdist_kaon2 = (TH2F*)f2->Get("costheta_kdEdx_dist_kaon");
  TH2F*  kdEdxdist_pion2 = (TH2F*)f2->Get("costheta_kdEdx_dist_pion");
  TH2F*  kdEdxdist_proton2 = (TH2F*)f2->Get("costheta_kdEdx_dist_proton");
  TH2F*  kdEdxdist_muon2 = (TH2F*)f2->Get("costheta_kdEdx_dist_muon");
  TH2F*  kdEdxdist_electron2 = (TH2F*)f2->Get("costheta_kdEdx_dist_electron");
  
  float x2[100], eff2[100], pur2[100];
  int n2=0;
  //  option 1, 80eff, 92 pur = 16,21
  //  option 1, 87eff, 87 pur = 16,23

  for(int i=1;i<21; i++) {
    int ipion=22;
    if(i>16) ipion=22-(i-16);
    float n_kaons=  kdEdxdist_kaon2->Integral(i, i,16,ipion);
    float n_pions=  kdEdxdist_pion2->Integral(i, i,16,ipion);
    float n_protons=  kdEdxdist_proton2->Integral(i, i,16,ipion);
    float n_muons=  kdEdxdist_muon2->Integral(i, i,16,ipion);
    float n_electrons=  kdEdxdist_electron2->Integral(i, i,16,ipion);
    float nkaons=  kdEdxdist_kaon2->Integral(i, i,0,1000);
    if(nkaons==0) nkaons=10000000;
    x2[i-1]=i*1./20;
    eff2[i-1]=100.*(n_kaons)/nkaons;       
    //  eff2[i-1]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;                    
    pur2[i-1]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n2++;
  }
 

  TGraph* efficiency2 = new TGraph(n2,x2,eff2);
  TGraph* purity2 = new TGraph(n2,x2,pur2);
  TGraph* efficiency_purity2 = new TGraph(n2,eff2,pur2);
  
  //cquark=true;

  TCanvas* c_dist4 = new TCanvas("c_dist4","c_dist4",800,800);
  c_dist4->cd(1);
  c_dist4->SetGrid();
  efficiency->GetXaxis()->SetTitle("cos #theta");
  efficiency->GetYaxis()->SetTitle("[%]");
  efficiency->GetYaxis()->SetTitleOffset(1.25);
  efficiency->GetXaxis()->SetTitleOffset(1.);
  efficiency->GetYaxis()->SetRangeUser(0,100);

  efficiency->SetLineColor(4);
  efficiency->SetLineWidth(3);
  efficiency->SetLineStyle(2);
  efficiency->Draw("alp");
  
  purity->SetLineColor(kGreen+1);
  purity->SetLineWidth(1);
  purity->SetLineStyle(1);
  purity->Draw("lp");

  Labels("eL",secondary,cut,cat,quark);
  
  TLegend *leg0 = new TLegend(0.2,0.3,0.5,0.4);
  leg0->SetTextSize(0.035);
  leg0->SetTextFont(42);
  leg0->AddEntry(efficiency,"Efficiency","lp");
  leg0->AddEntry(purity,"Purity","lp");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

  //cquark=false;

 TCanvas* c_dist42 = new TCanvas("c_dist42","c_dist42",800,800);
  c_dist42->cd(1);
  c_dist42->SetGrid();
  efficiency2->GetXaxis()->SetTitle("cos #theta");
  efficiency2->GetYaxis()->SetTitle("[%]");
  efficiency2->GetYaxis()->SetTitleOffset(1.25);
  efficiency2->GetXaxis()->SetTitleOffset(1.);
  efficiency2->GetYaxis()->SetRangeUser(0,100);

  efficiency2->SetLineColor(4);
  efficiency2->SetLineWidth(3);
  efficiency2->SetLineStyle(2);
  efficiency2->Draw("alp");
  
  purity2->SetLineColor(kGreen+1);
  purity2->SetLineWidth(1);
  purity2->SetLineStyle(1);
  purity2->Draw("lp");

  Labels("eR",secondary,cut,cat,quark);
  
  TLegend *leg2 = new TLegend(0.2,0.3,0.5,0.4);
  leg2->SetTextSize(0.035);
  leg2->SetTextFont(42);
  leg2->AddEntry(efficiency,"Efficiency","lp");
  leg2->AddEntry(purity,"Purity","lp");
  leg2->SetFillColor(0);
  leg2->SetLineColor(0);
  leg2->SetShadowColor(0);
  leg2->Draw();
}



void EffPurity_dedxdist5(TString filename, TString filename2, TString secondary, TString cat, TString cut, TString quark){
  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  //TString filename = "../output/250GeV_IO_false_quark4_eL_pR.root";

  TFile *f = new TFile(filename);
  TH2F*  kdEdxdist_kaon = (TH2F*)f->Get("p_kdEdx_dist_kaon");
  TH2F*  kdEdxdist_pion = (TH2F*)f->Get("p_kdEdx_dist_pion");
  TH2F*  kdEdxdist_proton = (TH2F*)f->Get("p_kdEdx_dist_proton");
  TH2F*  kdEdxdist_muon = (TH2F*)f->Get("p_kdEdx_dist_muon");
  TH2F*  kdEdxdist_electron = (TH2F*)f->Get("p_kdEdx_dist_electron");
  
  float x[100], eff[100], pur[100];
  int n=0;
  //  option 1, 80eff, 92 pur = 16,21
  //  option 1, 87eff, 87 pur = 16,23


  for(int i=0;i<80; i++) {
    int ipion=22;
    // if(i>16) ipion=22-(i-16);
    float n_kaons=  kdEdxdist_kaon->Integral(i, i,16,ipion);
    float n_pions=  kdEdxdist_pion->Integral(i, i,16,ipion);
    float n_protons=  kdEdxdist_proton->Integral(i, i,16,ipion);
    float n_muons=  kdEdxdist_muon->Integral(i, i,16,ipion);
    float n_electrons=  kdEdxdist_electron->Integral(i, i,16,ipion);
    float nkaons=  kdEdxdist_kaon->Integral(i, i,0,1000);
    if(nkaons==0) nkaons=10000000;
    x[i]=i;
    eff[i]=100.*(n_kaons)/nkaons;       
    //  eff2[i-1]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;                    
    pur[i]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n++;
  }

 
  TGraph* efficiency = new TGraph(n,x,eff);
  TGraph* purity = new TGraph(n,x,pur);
  TGraph* efficiency_purity = new TGraph(n,eff,pur);
  

  //----------
  //TString filename2 = "../output/250GeV_IO_false_quark4_eR_pL.root";
  TFile *f2 = new TFile(filename2);
  TH2F*  kdEdxdist_kaon2 = (TH2F*)f2->Get("p_kdEdx_dist_kaon");
  TH2F*  kdEdxdist_pion2 = (TH2F*)f2->Get("p_kdEdx_dist_pion");
  TH2F*  kdEdxdist_proton2 = (TH2F*)f2->Get("p_kdEdx_dist_proton");
  TH2F*  kdEdxdist_muon2 = (TH2F*)f2->Get("p_kdEdx_dist_muon");
  TH2F*  kdEdxdist_electron2 = (TH2F*)f2->Get("p_kdEdx_dist_electron");
  
  float x2[100], eff2[100], pur2[100];
  int n2=0;
  //  option 1, 80eff, 92 pur = 16,21
  //  option 1, 87eff, 87 pur = 16,23

  for(int i=0;i<80; i++) {
    int ipion=22;
    //  if(i>16) ipion=22-(i-16);
    float n_kaons=  kdEdxdist_kaon2->Integral(i, i,16,ipion);
    float n_pions=  kdEdxdist_pion2->Integral(i, i,16,ipion);
    float n_protons=  kdEdxdist_proton2->Integral(i, i,16,ipion);
    float n_muons=  kdEdxdist_muon2->Integral(i, i,16,ipion);
    float n_electrons=  kdEdxdist_electron2->Integral(i, i,16,ipion);
    float nkaons=  kdEdxdist_kaon2->Integral(i, i,0,1000);
    if(nkaons==0) nkaons=10000000;
    x2[i]=i;//*1./20;
    eff2[i]=100.*(n_kaons)/nkaons;       
    //  eff2[i-1]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;                    
    pur2[i]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n2++;
  }
 

  TGraph* efficiency2 = new TGraph(n2,x2,eff2);
  TGraph* purity2 = new TGraph(n2,x2,pur2);
  TGraph* efficiency_purity2 = new TGraph(n2,eff2,pur2);
  
  //cquark=true;

  TCanvas* c_dist5 = new TCanvas("c_dist5","c_dist5",800,800);
  c_dist5->cd(1);
  c_dist5->SetGrid();
  efficiency->GetXaxis()->SetTitle("p [GeV]");
  efficiency->GetYaxis()->SetTitle("[%]");
  efficiency->GetYaxis()->SetTitleOffset(1.25);
  efficiency->GetXaxis()->SetTitleOffset(1.);
  efficiency->GetYaxis()->SetRangeUser(0,100);

  efficiency->SetLineColor(4);
  efficiency->SetLineWidth(3);
  efficiency->SetLineStyle(2);
  efficiency->Draw("alp");
  
  purity->SetLineColor(kGreen+1);
  purity->SetLineWidth(1);
  purity->SetLineStyle(1);
  purity->Draw("lp");

  Labels("eL",secondary,cut,cat,quark);
  
  TLegend *leg0 = new TLegend(0.2,0.3,0.5,0.4);
  leg0->SetTextSize(0.035);
  leg0->SetTextFont(42);
  leg0->AddEntry(efficiency,"Efficiency","lp");
  leg0->AddEntry(purity,"Purity","lp");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

  //cquark=false;

 TCanvas* c_dist52 = new TCanvas("c_dist52","c_dist52",800,800);
  c_dist52->cd(1);
  c_dist52->SetGrid();
  efficiency2->GetXaxis()->SetTitle("p [GeV]");
  efficiency2->GetYaxis()->SetTitle("[%]");
  efficiency2->GetYaxis()->SetTitleOffset(1.25);
  efficiency2->GetXaxis()->SetTitleOffset(1.);
  efficiency2->GetYaxis()->SetRangeUser(0,100);

  efficiency2->SetLineColor(4);
  efficiency2->SetLineWidth(3);
  efficiency2->SetLineStyle(2);
  efficiency2->Draw("alp");
  
  purity2->SetLineColor(kGreen+1);
  purity2->SetLineWidth(1);
  purity2->SetLineStyle(1);
  purity2->Draw("lp");

  Labels("eR",secondary,cut,cat,quark);
  
  TLegend *leg2 = new TLegend(0.2,0.3,0.5,0.4);
  leg2->SetTextSize(0.035);
  leg2->SetTextFont(42);
  leg2->AddEntry(efficiency,"Efficiency","lp");
  leg2->AddEntry(purity,"Purity","lp");
  leg2->SetFillColor(0);
  leg2->SetLineColor(0);
  leg2->SetShadowColor(0);
  leg2->Draw();
}


void EffPurity_dedxdist2(TString filename, TString filename2, TString secondary, TString cat, TString cut, TString quark){
  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  
  //TString filename = "../output/250GeV_IO_false_quark4_eL_pR.root";
  TFile *f = new TFile(filename);
  TH1F*  p_kaon = (TH1F*)f->Get("p_kaon");
  TH1F*  kdEdxdist_kaon = (TH1F*)f->Get("kdEdx_dist_kaon");
  TH1F*  kdEdxdist_pion = (TH1F*)f->Get("kdEdx_dist_pion");
  TH1F*  kdEdxdist_proton = (TH1F*)f->Get("kdEdx_dist_proton");
  TH1F*  kdEdxdist_muon = (TH1F*)f->Get("kdEdx_dist_muon");
  TH1F*  kdEdxdist_electron = (TH1F*)f->Get("kdEdx_dist_electron");
  float nkaons=p_kaon->GetEntries();
  
  float x[10000], eff[10000], pur[10000];
  int n=0;
  for(int i=16;i<25; i++) {
    float n_kaons=  kdEdxdist_kaon->Integral(16,i);
    float n_pions=  kdEdxdist_pion->Integral(16,i);
    float n_protons=  kdEdxdist_proton->Integral(16,i);
    float n_muons=  kdEdxdist_muon->Integral(16,i);
    float n_electrons=  kdEdxdist_electron->Integral(16,i);
    x[i-16]=16+i;
    //    eff[i-16]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;
    eff[i-16]=100.*(n_kaons)/nkaons;                    
    pur[i-16]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n++;
  }
 
  TGraph* efficiency = new TGraph(n,x,eff);
  TGraph* purity = new TGraph(n,x,pur);
  TGraph* efficiency_purity = new TGraph(n,eff,pur);

  //----------
  //TString filename2 = "../output/250GeV_IO_false_quark4_eR_pL.root";
  TFile *f2 = new TFile(filename2);
  TH1F*  p_kaon2 = (TH1F*)f2->Get("p_kaon");
  TH1F*  kdEdxdist_kaon2 = (TH1F*)f2->Get("kdEdx_dist_kaon");
  TH1F*  kdEdxdist_pion2 = (TH1F*)f2->Get("kdEdx_dist_pion");
  TH1F*  kdEdxdist_proton2 = (TH1F*)f2->Get("kdEdx_dist_proton");
  TH1F*  kdEdxdist_muon2 = (TH1F*)f2->Get("kdEdx_dist_muon");
  TH1F*  kdEdxdist_electron2 = (TH1F*)f2->Get("kdEdx_dist_electron");
  float nkaons2=p_kaon2->GetEntries();

  float x2[10000], eff2[10000], pur2[10000];
  int n2=0;
  for(int i=16;i<25; i++) {
    float n_kaons=  kdEdxdist_kaon2->Integral(16,i);
    float n_pions=  kdEdxdist_pion2->Integral(16,i);
    float n_protons=  kdEdxdist_proton2->Integral(16,i);
    float n_muons=  kdEdxdist_muon2->Integral(16,i);
    float n_electrons=  kdEdxdist_electron2->Integral(16,i);
    x2[i-16]=16+i;
    //    eff[i-16]=100.*(n_kaons+n_pions+n_protons+n_muons+n_electrons)/nkaons;                     
    eff2[i-16]=100.*(n_kaons)/nkaons2;
    pur2[i-16]=100.*n_kaons/(n_kaons+n_pions+n_protons+n_muons+n_electrons);
    n2++;
  }

  TGraph* efficiency2 = new TGraph(n2,x2,eff2);
  TGraph* purity2 = new TGraph(n2,x2,pur2);
  TGraph* efficiency_purity2 = new TGraph(n2,eff2,pur2);

  //cquark=true;
  TCanvas* c_dist2 = new TCanvas("c_dist2","c_dist2",800,800);
  c_dist2->cd(1);
  c_dist2->SetGrid();
  efficiency->GetXaxis()->SetTitle("i");
  efficiency->GetYaxis()->SetTitle("[%]");
  efficiency->GetYaxis()->SetTitleOffset(1.25);
  efficiency->GetXaxis()->SetTitleOffset(1.);
  efficiency->GetYaxis()->SetRangeUser(0,100);

  efficiency->SetLineColor(4);
  efficiency->SetLineWidth(3);
  efficiency->SetLineStyle(2);
  efficiency->Draw("alp");
  
  purity->SetLineColor(kGreen+1);
  purity->SetLineWidth(1);
  purity->SetLineStyle(1);
  purity->Draw("lp");

  Labels("eL",secondary,cut,cat,quark);
  
  TLegend *leg0 = new TLegend(0.6,0.25,0.8,0.35);
  leg0->SetTextSize(0.035);
  leg0->SetTextFont(42);
  leg0->AddEntry(efficiency,"Efficiency","lp");
  leg0->AddEntry(purity,"Purity","lp");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

  TCanvas* c_dist22 = new TCanvas("c_dist22","c_dist22",800,800);
  c_dist22->cd(1);
  c_dist22->SetGrid();
  efficiency_purity->GetXaxis()->SetTitle("Efficiency [%]");
  efficiency_purity->GetYaxis()->SetTitle("Purity [%]");
  efficiency_purity->GetYaxis()->SetTitleOffset(1.25);
  efficiency_purity->GetXaxis()->SetTitleOffset(1.);
  efficiency_purity->GetYaxis()->SetRangeUser(0,100);

  efficiency_purity->SetLineColor(4);
  efficiency_purity->SetLineWidth(3);
  efficiency_purity->SetLineStyle(2);
  efficiency_purity->Draw("alp");

  efficiency_purity2->SetLineColor(2);
  efficiency_purity2->SetLineWidth(3);
  efficiency_purity2->SetLineStyle(1);
  efficiency_purity2->Draw("lp");


  Labels("eR",secondary,cut,cat,quark);
  QQBARLabel2(0.3,0.2, "Method dEdx-distance",kBlack);

  TLegend *leg1 = new TLegend(0.6,0.25,0.8,0.35);
  leg1->SetTextSize(0.035);
  leg1->SetTextFont(42);
  leg1->AddEntry(efficiency_purity,"|p_{track}|> 0 GeV","lp");
  leg1->AddEntry(efficiency_purity2,"|p_{track}|> 2 GeV","lp");
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();
   

}

void Mom(TString filename, TString filename2, TString secondary, TString cat, TString cut, TString quark){
  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  TGaxis::SetMaxDigits(3);
  
  
  //TString filename = "../output/250GeV_IO_false_quark4_eL_pR.root";
  TFile *f = new TFile(filename);

  TH1F*  p_kaon = (TH1F*)f->Get("p_kaon");
  TH1F*  p_pion = (TH1F*)f->Get("p_pion");
  TH1F*  p_proton = (TH1F*)f->Get("p_proton");

  //TString filename2 = "../output/250GeV_IO_false_quark4_eR_pL.root";
  TFile *f2 = new TFile(filename2);

  TH1F*  p_kaon2 = (TH1F*)f2->Get("p_kaon");
  TH1F*  p_pion2 = (TH1F*)f2->Get("p_pion");
  TH1F*  p_proton2 = (TH1F*)f2->Get("p_proton");

  //cquark=true;
  TCanvas* c_mom = new TCanvas("c_mom","c_mom",800,800);
  c_mom->cd(1);
  c_mom->SetGrid();
  p_pion->GetXaxis()->SetTitle("momentum [GeV]");
  p_pion->GetYaxis()->SetTitle("Entries");
  //p_pion->GetYaxis()->SetTitleOffset(1.25);
  //p_pion->GetXaxis()->SetTitleOffset(1.);

  p_pion->SetLineColor(4);
  p_pion->SetLineWidth(3);
  p_pion->SetLineStyle(1);
  p_pion->Draw("histo");

  p_kaon->SetLineColor(2);
  p_kaon->SetLineWidth(3);
  p_kaon->SetLineStyle(1);
  p_kaon->Draw("histosame");

  p_proton->SetLineColor(1);
  p_proton->SetLineWidth(3);
  p_proton->SetLineStyle(1);
  p_proton->Draw("histosame");
  
  Labels("eL",secondary,cut,cat,quark);
  
  TLegend *leg = new TLegend(0.6,0.25,0.8,0.35);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  leg->AddEntry(p_pion,"pions","l");
  leg->AddEntry(p_kaon,"kaons","lp");
  leg->AddEntry(p_proton,"protons","lp");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();


  TCanvas* c_mom2 = new TCanvas("c_mom2","c_mom2",800,800);
  c_mom2->cd(1);
  c_mom2->SetGrid();
  p_pion2->GetXaxis()->SetTitle("momentum [GeV]");
  p_pion2->GetYaxis()->SetTitle("entries");
  //p_pion->GetYaxis()->SetTitleOffset(1.25);                                                                                                                                                              
  //p_pion->GetXaxis()->SetTitleOffset(1.);                                                                                                                                                                

  p_pion2->SetLineColor(4);
  p_pion2->SetLineWidth(3);
  p_pion2->SetLineStyle(1);
  p_pion2->Draw("histo");

  p_kaon2->SetLineColor(2);
  p_kaon2->SetLineWidth(3);
  p_kaon2->SetLineStyle(1);
  p_kaon2->Draw("histosame");

  p_proton2->SetLineColor(1);
  p_proton2->SetLineWidth(3);
  p_proton2->SetLineStyle(1);
  p_proton2->Draw("histosame");

  Labels("eR",secondary,cut,cat,quark);
  
  TLegend *leg2 = new TLegend(0.6,0.25,0.8,0.35);
  leg2->SetTextSize(0.035);
  leg2->SetTextFont(42);
  leg2->AddEntry(p_pion2,"pions","l");
  leg2->AddEntry(p_kaon2,"kaons","lp");
  leg2->AddEntry(p_proton2,"protons","lp");
  leg2->SetFillColor(0);
  leg2->SetLineColor(0);
  leg2->SetShadowColor(0);
  leg2->Draw();


}

void dEdxdist(TString filename, TString filename2, TString secondary, TString cat, TString cut, TString quark){
  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  //  gStyle->SetGridStyle(1);
  TGaxis::SetMaxDigits(3);
  
  //if(cquark_analysis==true) cquark=true;
  //else cquark=false;
  
  //TString filename = "../output/250GeV_IO_false_quark4_eL_pR.root";
  //if(cquark==false) filename = "../results/histos_bquark_secondary_tracks_cat_2f_hadronic_sample_eL_pR_2GeV.root";
  TFile *f = new TFile(filename);

  TH1F*  kdEdx_dist_kaon = (TH1F*)f->Get("kdEdx_dist_kaon");
  TH1F*  kdEdx_dist_pion = (TH1F*)f->Get("kdEdx_dist_pion");
  TH1F*  kdEdx_dist_proton = (TH1F*)f->Get("kdEdx_dist_proton");


  //TString filename2 = "../output/250GeV_IO_false_quark4_eR_pL.root";
  //if(cquark==false) filename2 = "../results/histos_bquark_secondary_tracks_cat_2f_hadronic_sample_eR_pL_2GeV.root";

  TFile *f2 = new TFile(filename2);

  TH1F*  kdEdx_dist_kaon2 = (TH1F*)f2->Get("kdEdx_dist_kaon");
  TH1F*  kdEdx_dist_pion2 = (TH1F*)f2->Get("kdEdx_dist_pion");
  TH1F*  kdEdx_dist_proton2 = (TH1F*)f2->Get("kdEdx_dist_proton");

  TCanvas* c_dist1 = new TCanvas("c_dist1","c_dist1",800,800);
  c_dist1->cd(1);
  c_dist1->SetGrid();
  kdEdx_dist_pion->GetXaxis()->SetTitle("(dEdx-dEdx_{exp-kaon})/#Delta_{dEdx}");
  kdEdx_dist_pion->GetYaxis()->SetTitle("entries");
  //kdEdx_dist_pion->GetYaxis()->SetTitleOffset(1.25);
  //kdEdx_dist_pion->GetXaxis()->SetTitleOffset(1.);

  kdEdx_dist_pion->SetLineColor(4);
  kdEdx_dist_pion->SetLineWidth(3);
  kdEdx_dist_pion->SetLineStyle(1);
  kdEdx_dist_pion->Draw("histo");

  kdEdx_dist_kaon->SetLineColor(2);
  kdEdx_dist_kaon->SetLineWidth(3);
  kdEdx_dist_kaon->SetLineStyle(1);
  kdEdx_dist_kaon->Draw("histosame");

  kdEdx_dist_proton->SetLineColor(1);
  kdEdx_dist_proton->SetLineWidth(3);
  kdEdx_dist_proton->SetLineStyle(1);
  kdEdx_dist_proton->Draw("histosame");
  
  /*
  TF1 *f_k= new TF1("f_k","gaus",-4,4);
  f_k->SetParameter(0,24600);
  f_k->SetParameter(1,0.1226);
  f_k->SetParameter(2,0.6);
  f_k->SetLineColor(2);
  f_k->SetLineWidth(2);
  f_k->SetLineStyle(2);
  f_k->Draw("lsame");
 
 TF1 *f_pi= new TF1("f_pi","gaus",-1,7);
  f_pi->SetParameter(0,55630);
  f_pi->SetParameter(1,3.47);
  f_pi->SetParameter(2,0.6);
  f_pi->SetLineColor(4);
  f_pi->SetLineWidth(2);
  f_pi->SetLineStyle(2);
  f_pi->Draw("lsame");
  */
  
  Labels("eL",secondary,cut,cat,quark);
  
  TLegend *leg = new TLegend(0.3,0.6,0.5,0.75);
  leg->SetTextSize(0.035);
  leg->SetTextFont(42);
  leg->AddEntry(kdEdx_dist_pion,"pions","l");
  leg->AddEntry(kdEdx_dist_kaon,"kaons","lp");
  leg->AddEntry(kdEdx_dist_proton,"protons","lp");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();


  TCanvas* c_dist12 = new TCanvas("c_dist12","c_dist12",800,800);
  c_dist12->cd(1);
  c_dist12->SetGrid();

  kdEdx_dist_pion2->GetXaxis()->SetTitle("(dEdx-dEdx_{exp-kaon})/#Delta_{dEdx}");
  kdEdx_dist_pion2->GetYaxis()->SetTitle("entries");
  //kdEdx_dist_pion->GetYaxis()->SetTitleOffset(1.25);      
  //kdEdx_dist_pion->GetXaxis()->SetTitleOffset(1.);      

  kdEdx_dist_pion2->SetLineColor(4);
  kdEdx_dist_pion2->SetLineWidth(3);
  kdEdx_dist_pion2->SetLineStyle(1);
  kdEdx_dist_pion2->Draw("histo");

  kdEdx_dist_kaon2->SetLineColor(2);
  kdEdx_dist_kaon2->SetLineWidth(3);
  kdEdx_dist_kaon2->SetLineStyle(1);
  kdEdx_dist_kaon2->Draw("histosame");

  kdEdx_dist_proton2->SetLineColor(1);
  kdEdx_dist_proton2->SetLineWidth(3);
  kdEdx_dist_proton2->SetLineStyle(1);
  kdEdx_dist_proton2->Draw("histosame");

  Labels("eR",secondary,cut,cat,quark);

  TLegend *leg2 = new TLegend(0.3,0.6,0.5,0.75);
  leg2->SetTextSize(0.035);
  leg2->SetTextFont(42);
  leg2->AddEntry(kdEdx_dist_pion2,"pions","l");
  leg2->AddEntry(kdEdx_dist_kaon2,"kaons","lp");
  leg2->AddEntry(kdEdx_dist_proton2,"protons","lp");
  leg2->SetFillColor(0);
  leg2->SetLineColor(0);
  leg2->SetShadowColor(0);
  leg2->Draw();


}

void dEdx_p_cos(TString filename, TString filename2, TString secondary, TString cat, TString cut, TString quark){

  SetQQbarStyle();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.3);
  gStyle->SetTitleFontSize(0.4);
  //  gStyle->SetGridStyle(1);                                                                                                                                          
  TGaxis::SetMaxDigits(3);

 
  TFile *f = new TFile(filename);

  TH2F*  dEdx_p_kaon = (TH2F*)f->Get("kaon");
  TH2F*  dEdx_p_pion = (TH2F*)f->Get("pion");
  TH2F*  dEdx_p_proton = (TH2F*)f->Get("proton");

  TH2F*  dEdx_cos_kaon = (TH2F*)f->Get("kaon_cos");
  TH2F*  dEdx_cos_pion = (TH2F*)f->Get("pion_cos");
  TH2F*  dEdx_cos_proton = (TH2F*)f->Get("proton_cos");
  TH2F*  dEdx_cos_electron = (TH2F*)f->Get("electron_cos");
  TH2F*  dEdx_cos_muon = (TH2F*)f->Get("muon_cos");

  TFile *f2 = new TFile(filename2);

  TH2F*  dEdx_p_kaon2 = (TH2F*)f2->Get("kaon");
  TH2F*  dEdx_p_pion2 = (TH2F*)f2->Get("pion");
  TH2F*  dEdx_p_proton2 = (TH2F*)f2->Get("proton");

  TH2F*  dEdx_cos_kaon2 = (TH2F*)f2->Get("kaon_cos");
  TH2F*  dEdx_cos_pion2 = (TH2F*)f2->Get("pion_cos");
  TH2F*  dEdx_cos_proton2 = (TH2F*)f2->Get("proton_cos");
  TH2F*  dEdx_cos_electron2 = (TH2F*)f2->Get("electron_cos");
  TH2F*  dEdx_cos_muon2 = (TH2F*)f2->Get("muon_cos");

  TCanvas* c_dEdx_p = new TCanvas("c_dEdx_p","c_dEdx_p",800,800);
  c_dEdx_p->cd(1);
  c_dEdx_p->SetGrid();
  gPad->SetLogx();
  //kdEdx_dist_pion->GetXaxis()->SetTitle("(dEdx-dEdx_{exp-kaon})/#Delta_{dEdx}");
  //kdEdx_dist_pion->GetYaxis()->SetTitle("entries");
  //kdEdx_dist_pion->GetYaxis()->SetTitleOffset(1.25);                                                                                                                  
  //kdEdx_dist_pion->GetXaxis()->SetTitleOffset(1.);                                                                                                                   
  dEdx_p_pion->GetYaxis()->SetTitleSize(0.03);
  dEdx_p_pion->GetYaxis()->SetTitleOffset(2.5);                                                                                                                 
  dEdx_p_pion->GetXaxis()->SetTitleSize(0.03);
  dEdx_p_pion->GetXaxis()->SetTitleOffset(2.0);
  dEdx_p_pion->SetMarkerColor(4);
  dEdx_p_pion->SetFillColor(4);
  dEdx_p_pion->Draw("histo");
  dEdx_p_kaon->SetMarkerColor(2);
  dEdx_p_kaon->SetFillColor(2);
  dEdx_p_kaon->Draw("histosame");
  dEdx_p_proton->SetMarkerColor(3);
  dEdx_p_proton->SetFillColor(3);
  dEdx_p_proton->Draw("histosame");
  
  Labels("eL",secondary,cut,cat,quark);

  TLegend *leg = new TLegend(0.2,0.7,0.5,0.85);
  leg->SetTextSize(0.03);
  leg->SetTextFont(42);
  leg->AddEntry(dEdx_p_pion,"charged pions","f");
  leg->AddEntry(dEdx_p_kaon,"charged kaons","f");
  leg->AddEntry(dEdx_p_proton,"protons","f");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

  TCanvas* c_dEdx_p2 = new TCanvas("c_dEdx_p2","c_dEdx_p2",800,800);
  c_dEdx_p2->cd(1);
  c_dEdx_p2->SetGrid();
  gPad->SetLogx();
  //kdEdx_dist_pion->GetXaxis()->SetTitle("(dEdx-dEdx_{exp-kaon})/#Delta_{dEdx}");
  //kdEdx_dist_pion->GetYaxis()->SetTitle("entries");
  //kdEdx_dist_pion->GetYaxis()->SetTitleOffset(1.25);
  //kdEdx_dist_pion->GetXaxis()->SetTitleOffset(1.);
  dEdx_p_pion2->GetYaxis()->SetTitleSize(0.03);
  dEdx_p_pion2->GetYaxis()->SetTitleOffset(2.5);
  dEdx_p_pion2->GetXaxis()->SetTitleSize(0.03);
  dEdx_p_pion2->GetXaxis()->SetTitleOffset(2.0);
  dEdx_p_pion2->SetMarkerColor(4);
  dEdx_p_pion2->SetFillColor(4);
  dEdx_p_pion2->Draw("histo");
  dEdx_p_kaon2->SetMarkerColor(2);
  dEdx_p_kaon2->SetFillColor(2);
  dEdx_p_kaon2->Draw("histosame");
  dEdx_p_proton2->SetMarkerColor(3);
  dEdx_p_proton2->SetFillColor(3);
  dEdx_p_proton2->Draw("histosame");

  Labels("eR",secondary,cut,cat,quark);

  TLegend *leg2 = new TLegend(0.2,0.7,0.5,0.85);
  leg2->SetTextSize(0.03);
  leg2->SetTextFont(42);
  leg2->AddEntry(dEdx_p_pion2,"charged pions","f");
  leg2->AddEntry(dEdx_p_kaon2,"charged kaons","f");
  leg2->AddEntry(dEdx_p_proton2,"protons","f");
  leg2->SetFillColor(0);
  leg2->SetLineColor(0);
  leg2->SetShadowColor(0);
  leg2->Draw();

  TCanvas* c_dEdx_cos = new TCanvas("c_dEdx_cos","c_dEdx_cos",800,800);
  c_dEdx_cos->cd(1);
  c_dEdx_cos->SetGrid();
  //gPad->SetLogx();
  dEdx_cos_pion->GetYaxis()->SetTitle("#frac{dE}{dx} [MeV]");
  dEdx_cos_pion->GetXaxis()->SetTitle("|cos#theta|");
  //kdEdx_dist_pion->GetYaxis()->SetTitleOffset(1.25);
  //kdEdx_dist_pion->GetXaxis()->SetTitleOffset(1.);
  dEdx_cos_pion->GetYaxis()->SetTitleSize(0.03);
  dEdx_cos_pion->GetYaxis()->SetTitleOffset(2.5);
  dEdx_cos_pion->GetXaxis()->SetTitleSize(0.03);
  dEdx_cos_pion->GetXaxis()->SetTitleOffset(2.0);
  dEdx_cos_pion->SetFillColor(4);
  dEdx_cos_pion->SetMarkerColor(4);
  dEdx_cos_pion->Draw("histo");
  dEdx_cos_kaon->SetFillColor(2);
  dEdx_cos_kaon->SetMarkerColor(2);
  dEdx_cos_kaon->Draw("histosame");
  dEdx_cos_proton->SetFillColor(3);
  dEdx_cos_proton->SetMarkerColor(3);
  dEdx_cos_proton->Draw("histosame");
  dEdx_cos_electron->SetFillColor(1);
  dEdx_cos_electron->SetMarkerColor(1);
  dEdx_cos_electron->Draw("histosame");
  dEdx_cos_muon->SetFillColor(11);
  dEdx_cos_muon->SetMarkerColor(11);
  dEdx_cos_muon->Draw("histosame");
  
  Labels("eL",secondary,cut,cat,quark);

  TLegend *leg3 = new TLegend(0.2,0.75,0.3,0.9);
  leg3->SetTextSize(0.035);
  leg3->SetTextFont(42);
  leg3->AddEntry(dEdx_cos_pion,"#pi","f");
  leg3->AddEntry(dEdx_cos_kaon,"K","f");
  leg3->AddEntry(dEdx_cos_proton,"p","f");
  leg3->AddEntry(dEdx_cos_electron,"e","f");
  leg3->AddEntry(dEdx_cos_muon,"#mu","f");
  leg3->SetFillColor(0);
  leg3->SetLineColor(0);
  leg3->SetShadowColor(0);
  leg3->Draw();

  TCanvas* c_dEdx_cos2 = new TCanvas("c_dEdx_cos2","c_dEdx_cos2",800,800);
  c_dEdx_cos2->cd(1);
  c_dEdx_cos2->SetGrid();
  //gPad->SetLogx();                                                                                                                                                                                                                       
  dEdx_cos_pion2->GetYaxis()->SetTitle("#frac{dE}{dx} [MeV]");
  dEdx_cos_pion2->GetXaxis()->SetTitle("|cos#theta|");
  //kdEdx_dist_pion->GetYaxis()->SetTitleOffset(1.25);                                                                                                                                                                                     
  //kdEdx_dist_pion->GetXaxis()->SetTitleOffset(1.);                                                                                                                                                                                       
  dEdx_cos_pion2->GetYaxis()->SetTitleSize(0.03);
  dEdx_cos_pion2->GetYaxis()->SetTitleOffset(2.5);
  dEdx_cos_pion2->GetXaxis()->SetTitleSize(0.03);
  dEdx_cos_pion2->GetXaxis()->SetTitleOffset(2.0);
  dEdx_cos_pion2->SetMarkerColor(4);
  dEdx_cos_pion2->SetFillColor(4);
  dEdx_cos_pion2->Draw("histo");
  dEdx_cos_kaon2->SetMarkerColor(2);
  dEdx_cos_kaon2->SetFillColor(2);
  dEdx_cos_kaon2->Draw("histosame");
  dEdx_cos_proton2->SetMarkerColor(3);
  dEdx_cos_proton2->SetFillColor(3);
  dEdx_cos_proton2->Draw("histosame");
  dEdx_cos_electron2->SetMarkerColor(1);
  dEdx_cos_electron2->SetFillColor(1);
  dEdx_cos_electron2->Draw("histosame");
  dEdx_cos_muon2->SetFillColor(11);
  dEdx_cos_muon2->SetMarkerColor(11);
  dEdx_cos_muon2->Draw("histosame");

  Labels("eR",secondary,cut,cat,quark);

  TLegend *leg4 = new TLegend(0.2,0.75,0.3,0.9);
  leg4->SetTextSize(0.035);
  leg4->SetTextFont(42);
  leg4->AddEntry(dEdx_cos_pion2,"#pi","f");
  leg4->AddEntry(dEdx_cos_kaon2,"K","f");
  leg4->AddEntry(dEdx_cos_proton2,"p","f");
  leg4->AddEntry(dEdx_cos_electron2,"e","f");
  leg4->AddEntry(dEdx_cos_muon2,"#mu","f");
  leg4->SetFillColor(0);
  leg4->SetLineColor(0);
  leg4->SetShadowColor(0);
  leg4->Draw();
}

void Plots_dEdx(TString tracks, TString cut, TString cat,TString quark) {
  
  TString filename ="../output/output_500_"+tracks+"_tracks_"+cat+"_500GeV_eL_pR_cut_"+cut+"_"+quark+"quark.root";
  TString filename2 ="../output/output_500_"+tracks+"_tracks_"+cat+"_500GeV_eR_pL_cut_"+cut+"_"+quark+"quark.root";

  Mom(filename,filename2,tracks,cat,cut,quark);
  //EffPurity_default(filename,filename2,tracks,cat,cut,quark);
  //EffPurity_dedxdist(filename,filename2,tracks,cat,cut,quark);
  //EffPurity_dedxdist2(filename,filename2,tracks,cat,cut,quark);
  //EffPurity_dedxdist3(filename,filename2,tracks,cat,cut,quark);
  //EffPurity_dedxdist4(filename,filename2,tracks,cat,cut,quark);
  //EffPurity_dedxdist5(filename,filename2,tracks,cat,cut,quark);
  dEdxdist(filename,filename2,tracks,cat,cut,quark);
  dEdx_p_cos(filename,filename2,tracks,cat,cut,quark);
}
