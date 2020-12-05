//
// Created by Jon Sensenig on 12/4/20.
//

#include "Reader.h"


Reader::Reader()
{ ; }

Reader::~Reader()
{ ; }

bool Reader::Next() {

  return
  beamtrack_reader     -> Next() &&
  recobeamtevt_reader  -> Next() &&
  recodaughters_reader -> Next();

}

int Reader::ConfigureReader(TFile *file) {

  beamtrack_reader     = new TTreeReader( "pdAnalysisTree/BeamTrack", file );
  recobeamtevt_reader  = new TTreeReader( "pdAnalysisTree/ReconstructedBeamEvents", file );
  recodaughters_reader = new TTreeReader( "pdAnalysisTree/ReconstructedDaughters", file );

  return ! ( beamtrack_reader && recobeamtevt_reader && recodaughters_reader );

}

int Reader::ConfigureLeaves() {

  // Beam Track tree
  beamtrackMomentum = new TTreeReaderValue<double>(*beamtrack_reader, "beamtrackMomentum");
  beamtrackDir      = new TTreeReaderArray<double>(*beamtrack_reader, "beamtrackDir");
  beamtrackEnergy   = new TTreeReaderValue<double>(*beamtrack_reader, "beamtrackEnergy");
  beamtrack_truth_Pdg = new TTreeReaderValue<int>(*beamtrack_reader, "beamtrack_truth_Pdg");

  // Reco & truth beam events including daughters
  primaryOpeningAngle = new TTreeReaderValue<double>(*recobeamtevt_reader, "primaryOpeningAngle");
  primaryIsshower = new TTreeReaderValue<int>(*recobeamtevt_reader, "primaryIsshower");
  primary_truth_KinEnergy_InTPCActive = new TTreeReaderValue<double>(*recobeamtevt_reader, "primary_truth_KinEnergy_InTPCActive");
  primaryPID_PIDA   = new TTreeReaderArray<double>(*recobeamtevt_reader, "primaryPID_PIDA");
  primary_truth_Pdg = new TTreeReaderValue<int>(*recobeamtevt_reader, "primary_truth_Pdg");
  primary_truthdaughter_Pdg = new TTreeReaderArray<int>(*recobeamtevt_reader, "primary_truthdaughter_Pdg");
  primary_truth_ndaughters  = new TTreeReaderValue<int>(*recobeamtevt_reader, "primary_truth_NDAUGTHERS");

  // Reco & associated truth daughters (these are all arrays of length NMAXDAUGHTER = 15)
  ndaughters = new TTreeReaderValue<int>(*recodaughters_reader, "NDAUGHTERS");
  daughter_truth_Pdg = new TTreeReaderArray<int>(*recodaughters_reader, "daughter_truth_Pdg");
  daughterPID_PIDA   = new TTreeReaderArray<double>(*recodaughters_reader, "daughterPID_PIDA");

  return 0;
}