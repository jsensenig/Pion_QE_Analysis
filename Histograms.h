//
// Created by Jon Sensenig on 12/5/20.
//

#ifndef PION_QE_HISTOGRAMS_H
#define PION_QE_HISTOGRAMS_H

#include <map>
#include <iostream>
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"


class Histograms {

public:

  Histograms();
  virtual ~Histograms();

  void ConfigureHistos();
  void WriteHistos( TString & out_file );

  // ----------------
  // Declare the histograms we want
  TH1 * h_beam_e;
  TH1 * h_beam_e_cut;
  TH1* h_prim_ke;
  TH1* h_nproton;
  TH1* h_nneutron;
  TH2* h_n_np;

protected:

  bool OpenFile( TString & out_file );

private:

  std::map<std::string, TH1*> th1_hists;
  std::map<std::string , TH2*> th2_hists;

  TFile * ofile;

};


#endif //PION_QE_HISTOGRAMS_H
