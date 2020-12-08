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

  // Hold all the histograms in these maps
  std::map< std::string, std::unique_ptr<TH1> > th1_hists;
  std::map< std::string, std::unique_ptr<TH2> > th2_hists;

protected:

  bool OpenFile( TString & out_file );

private:

  std::unique_ptr<TFile> ofile;

  const std::string _config_file = "../config/Histograms.json";
  json _conf;

};


#endif //PION_QE_HISTOGRAMS_H
