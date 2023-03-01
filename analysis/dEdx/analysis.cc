#include "TROOT.h"
#include "TFile.h"
#include "observable.cc"
#include "TApplication.h"

int analysis(TString file, TString output, TString vertex, bool ignoreoverlay, int cut, int quark, TString cat){

  cout<< " "<<endl;
  cout<< file << endl;
  //  TString folder="/lustre/ific.uv.es/prj/ific/flc/ntuples-2020/2f_hadronic_sample_eL_pR/";
  //file=folder+file;
  cout<<file<<endl;
  observable ss3(file);
  
  ss3.dEdx(-1,TString::Format("%s_cut_%i",output.Data(),cut),vertex,ignoreoverlay,float(cut),quark,cat); 
  //void observable::dEdx(int n_entries=-1, TString process="",bool secondary=false, bool ignoreoverlay=true,float momentum_min=0, int pdg=4)
  //  ss3.dEdx(-1,output,false,ignoreoverlay);
  
  gSystem->Exit(0);

  return 0;
}
