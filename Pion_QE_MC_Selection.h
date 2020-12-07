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

private:

  //Histogram class
  Histograms _hists;

};


#endif //PION_QE_PION_QE_MC_SELECTION_H
