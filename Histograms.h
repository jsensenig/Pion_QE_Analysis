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
#include "Utilities.h"


class Histograms {

public:

  Histograms();
  virtual ~Histograms();

  void Config();
  void ConfigureHistos();
  void WriteHistos( TString & out_file );

  // ----------------
  // Declare the histograms we want
  std::shared_ptr<TH1> h_beam_e;
  std::shared_ptr<TH1> h_beam_e_cut;
  std::shared_ptr<TH1> h_prim_ke;
  std::shared_ptr<TH1> h_nproton;
  std::shared_ptr<TH1> h_nneutron;
  std::shared_ptr<TH1> h_total_len_pionqe;
  std::shared_ptr<TH1> h_total_len;
  std::shared_ptr<TH1> h_prim_pida_pi;
  std::shared_ptr<TH1> h_prim_pida_all;

  std::shared_ptr<TH2> h_n_np;

  std::map< std::string, std::shared_ptr<TH1> > th1_hists;
  std::map< std::string, std::unique_ptr<TH1> > th1_test;
  std::map< std::string , std::shared_ptr<TH2> > th2_hists;

protected:

  bool OpenFile( TString & out_file );

private:

  std::unique_ptr<TFile> ofile;

  const std::string _config_file = "../config/Histograms.json";
  json _conf;

};


#endif //PION_QE_HISTOGRAMS_H
