//
// Created by Jon Sensenig on 12/3/20.
//

#ifndef PION_QE_PION_QE_MC_SELECTION_H
#define PION_QE_PION_QE_MC_SELECTION_H

#include "TFile.h"
#include "Histograms.h"
#include "Selections.h"
#include "Reader.h"


class Pion_QE_MC_Selection {

public:

  void ReadData(TFile *file);
  void ProcessPrimary( Reader & rdr );
  void ProcessPrimaryTruthDaughter( Reader & rdr );
  void ProcessRecoDaughter( Reader & rdr );
  void CalculateELoss( const TLorentzVector& k, const TLorentzVector& kp );
  void Config();

private:

  //Histogram class
  Histograms _hists;
  //Selection class
  Selections _sel;

  size_t _pionqe = 0;
  size_t _piontruth = 0;
  size_t _pionreco = 0;

  const std::string _config_file = "../config/Pion_QE_MC_Selection.json";
  TString _outfile;

};


#endif //PION_QE_PION_QE_MC_SELECTION_H
