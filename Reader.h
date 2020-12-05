//
// Created by Jon Sensenig on 12/4/20.
//

#ifndef PION_QE_READER_H
#define PION_QE_READER_H

#include "TFile.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"

class Reader {

public:
  Reader();
  virtual ~Reader();

  int ConfigureReader( TFile * file );
  int ConfigureLeaves( );
  bool Next();


  TTreeReaderValue<double> * beamtrackMomentum;
  TTreeReaderArray<double> * beamtrackDir;
  TTreeReaderValue<double> * beamtrackEnergy;
  TTreeReaderValue<int> * beamtrack_truth_Pdg;

  // Reco & truth beam events including daughters
  TTreeReaderValue<double> * primaryOpeningAngle;
  TTreeReaderValue<int> * primaryIsshower;
  TTreeReaderValue<double> * primary_truth_KinEnergy_InTPCActive;
  TTreeReaderArray<double> * primaryPID_PIDA;
  TTreeReaderValue<int> * primary_truth_Pdg;
  TTreeReaderArray<int> * primary_truthdaughter_Pdg;
  TTreeReaderValue<int> * primary_truth_ndaughters;

  // Reco & associated truth daughters (these are all arrays of length NMAXDAUGHTER = 15)
  TTreeReaderValue<int> * ndaughters;
  TTreeReaderArray<int> * daughter_truth_Pdg;
  TTreeReaderArray<double> * daughterPID_PIDA;

protected:

  TTreeReader * beamtrack_reader;
  TTreeReader * recobeamtevt_reader;
  TTreeReader * recodaughters_reader;

};


#endif //PION_QE_READER_H
