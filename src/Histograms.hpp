//
// Created by Jon Sensenig on 12/5/20.
//

#ifndef PION_QE_HISTOGRAMS_HPP
#define PION_QE_HISTOGRAMS_HPP

#include <map>
#include <iostream>
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "Utilities.hpp"


class Histograms {

public:

  Histograms();
  virtual ~Histograms();

  void ConfigureHistos( std::string config_file );
  void WriteHistos( TString & out_file );

  // Hold all the histograms in these maps
  std::map< std::string, std::unique_ptr<TH1> > th1_hists;
  std::map< std::string, std::unique_ptr<TH2> > th2_hists;

protected:

  bool OpenFile( TString & out_file );

private:

  std::unique_ptr<TFile> ofile;

};


#endif //PION_QE_HISTOGRAMS_HPP
