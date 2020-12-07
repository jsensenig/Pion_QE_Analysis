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

  explicit Reader( TFile * file );
  virtual ~Reader();

  bool Next();

  // TTree readers
  TTreeReader beamtrack_reader = { "pdAnalysisTree/BeamTrack", infile };
  TTreeReader recobeamtevt_reader  = { "pdAnalysisTree/ReconstructedBeamEvents", infile };
  TTreeReader recodaughters_reader = { "pdAnalysisTree/ReconstructedDaughters", infile };

  // Beam Track tree
  TTreeReaderValue<int> run = {beamtrack_reader, "run"};
  TTreeReaderValue<int> subrun = {beamtrack_reader, "subrun"};
  TTreeReaderValue<int> event = {beamtrack_reader, "event"};
  TTreeReaderValue<int> beamNTracks = {beamtrack_reader, "beamNTracks"};
  TTreeReaderValue<int> beamtrigger = {beamtrack_reader, "beamtrigger"};
  TTreeReaderValue<double> tof = {beamtrack_reader, "tof"};
  TTreeReaderValue<double> tof_expElec = {beamtrack_reader, "tof_expElec"};
  TTreeReaderValue<double> tof_expMuon = {beamtrack_reader, "tof_expMuon"};
  TTreeReaderValue<double> tof_expPion = {beamtrack_reader, "tof_expPion"};
  TTreeReaderValue<double> tof_expKaon = {beamtrack_reader, "tof_expKaon"};
  TTreeReaderValue<double> tof_expProt = {beamtrack_reader, "tof_expProt"};
  TTreeReaderValue<double> tof_expDeut = {beamtrack_reader, "tof_expDeut"};
  TTreeReaderArray<int> cerenkovStatus = {beamtrack_reader, "cerenkovStatus"};
  TTreeReaderArray<double> cerenkovTime = {beamtrack_reader, "cerenkovTime"};
  TTreeReaderArray<double> cerenkovPressure = {beamtrack_reader, "cerenkovPressure"};
  TTreeReaderValue<double> beamtrackMomentum = {beamtrack_reader, "beamtrackMomentum"};
  TTreeReaderValue<double> beamtrackEnergy = {beamtrack_reader, "beamtrackEnergy"};
  TTreeReaderArray<double> beamtrackPos = {beamtrack_reader, "beamtrackPos"};
  TTreeReaderArray<double> beamtrackDir = {beamtrack_reader, "beamtrackDir"};
  TTreeReaderValue<int> BIAndTimingMatched = {beamtrack_reader, "BIAndTimingMatched"};
  TTreeReaderValue<int> beamtrack_truth_Origin = {beamtrack_reader, "beamtrack_truth_Origin"};
  TTreeReaderValue<int> beamtrackPdg = {beamtrack_reader, "beamtrackPdg"};
  TTreeReaderValue<int> beamtrackID = {beamtrack_reader, "beamtrackID"};
  TTreeReaderArray<double> beamtrack_truth_EndPos = {beamtrack_reader, "beamtrack_truth_EndPos"};
  TTreeReaderArray<double> beamtrack_truth_Momentum = {beamtrack_reader, "beamtrack_truth_Momentum"};
  TTreeReaderValue<double> beamtrack_truth_KinEnergy = {beamtrack_reader, "beamtrack_truth_KinEnergy"};
  TTreeReaderValue<double> beamtrack_truth_Pt = {beamtrack_reader, "beamtrack_truth_Pt"};
  TTreeReaderValue<double> beamtrack_truth_Mass = {beamtrack_reader, "beamtrack_truth_Mass"};
  TTreeReaderValue<double> beamtrack_truth_Theta = {beamtrack_reader, "beamtrack_truth_Theta"};
  TTreeReaderValue<double> beamtrack_truth_Phi = {beamtrack_reader, "beamtrack_truth_Phi"};
  TTreeReaderValue<double> beamtrack_truth_TotalLength = {beamtrack_reader, "beamtrack_truth_TotalLength"};
  TTreeReaderValue<int> beamtrack_truth_Process = {beamtrack_reader, "beamtrack_truth_Process"};
  TTreeReaderValue<int> beamtrack_truth_EndProcess = {beamtrack_reader, "beamtrack_truth_EndProcess"};
  TTreeReaderValue<int> beamtrack_truth_Pdg = {beamtrack_reader, "beamtrack_truth_Pdg"};
  TTreeReaderValue<int> beamtrack_truth_NDAUGTHERS = {beamtrack_reader, "beamtrack_truth_NDAUGTHERS"};
  TTreeReaderValue<int> beamtrack_truth_NDECAYDAUGTHERS = {beamtrack_reader, "beamtrack_truth_NDECAYDAUGTHERS"};
  TTreeReaderArray<double> beamtrack_truth_Pos_InTPCActive = {beamtrack_reader, "beamtrack_truth_Pos_InTPCActive"};
  TTreeReaderArray<double> beamtrack_truth_Momentum_InTPCActive = {beamtrack_reader, "beamtrack_truth_Momentum_InTPCActive"};
  TTreeReaderValue<double> beamtrack_truth_P_InTPCActive = {beamtrack_reader, "beamtrack_truth_P_InTPCActive"};
  TTreeReaderValue<double> beamtrack_truth_Pt_InTPCActive = {beamtrack_reader, "beamtrack_truth_Pt_InTPCActive"};
  TTreeReaderValue<double> beamtrack_truth_Theta_InTPCActive = {beamtrack_reader, "beamtrack_truth_Theta_InTPCActive"};
  TTreeReaderValue<double> beamtrack_truth_Phi_InTPCActive = {beamtrack_reader, "beamtrack_truth_Phi_InTPCActive"};
  TTreeReaderValue<double> beamtrack_truth_TotalLength_InTPCActive = {beamtrack_reader, "beamtrack_truth_TotalLength_InTPCActive"};
  TTreeReaderValue<double> beamtrack_truth_KinEnergy_InTPCActive = {beamtrack_reader, "beamtrack_truth_KinEnergy_InTPCActive"};
  TTreeReaderArray<int> beamtrack_truthdaughter_TrackId = {beamtrack_reader, "beamtrack_truthdaughter_TrackId"};
  TTreeReaderArray<int> beamtrack_truthdaughter_Pdg = {beamtrack_reader, "beamtrack_truthdaughter_Pdg"};
  TTreeReaderArray<int> beamtrack_truthdaughter_Mother = {beamtrack_reader, "beamtrack_truthdaughter_Mother"};
  TTreeReaderArray<double> beamtrack_truthdaughter_P = {beamtrack_reader, "beamtrack_truthdaughter_P"};
  TTreeReaderArray<double> beamtrack_truthdaughter_Pt = {beamtrack_reader, "beamtrack_truthdaughter_Pt"};
  TTreeReaderArray<double> beamtrack_truthdaughter_Mass = {beamtrack_reader, "beamtrack_truthdaughter_Mass"};
  TTreeReaderArray<double> beamtrack_truthdaughter_Theta = {beamtrack_reader, "beamtrack_truthdaughter_Theta"};
  TTreeReaderArray<double> beamtrack_truthdaughter_Phi = {beamtrack_reader, "beamtrack_truthdaughter_Phi"};
  TTreeReaderArray<double> beamtrack_truthdaughter_TotalLength = {beamtrack_reader, "beamtrack_truthdaughter_TotalLength"};
  TTreeReaderArray<int> beamtrack_truthdaughter_Process = {beamtrack_reader, "beamtrack_truthdaughter_Process"};
  TTreeReaderArray<int> beamtrack_truthdaughter_EndProcess = {beamtrack_reader, "beamtrack_truthdaughter_EndProcess"};
  TTreeReaderArray<int> beamtrack_truthdecaydaughter_TrackId = {beamtrack_reader, "beamtrack_truthdecaydaughter_TrackId"};
  TTreeReaderArray<int> beamtrack_truthdecaydaughter_Pdg = {beamtrack_reader, "beamtrack_truthdecaydaughter_Pdg"};
  TTreeReaderArray<int> beamtrack_truthdecaydaughter_Mother = {beamtrack_reader, "beamtrack_truthdecaydaughter_Mother"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_P = {beamtrack_reader, "beamtrack_truthdecaydaughter_P"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_Pt = {beamtrack_reader, "beamtrack_truthdecaydaughter_Pt"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_Mass = {beamtrack_reader, "beamtrack_truthdecaydaughter_Mass"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_Theta = {beamtrack_reader, "beamtrack_truthdecaydaughter_Theta"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_Phi = {beamtrack_reader, "beamtrack_truthdecaydaughter_Phi"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_TotalLength = {beamtrack_reader, "beamtrack_truthdecaydaughter_TotalLength"};
  TTreeReaderArray<int> beamtrack_truthdecaydaughter_Process = {beamtrack_reader, "beamtrack_truthdecaydaughter_Process"};
  TTreeReaderArray<int> beamtrack_truthdecaydaughter_EndProcess = {beamtrack_reader, "beamtrack_truthdecaydaughter_EndProcess"};

  // Reco & truth beam events including daughters
  TTreeReaderValue<double> timestamp = {recobeamtevt_reader, "timestamp"};
  TTreeReaderArray<int> Nactivefembs = {recobeamtevt_reader, "Nactivefembs"};
  TTreeReaderValue<int> NpfParticles = {recobeamtevt_reader, "NpfParticles"};
  TTreeReaderValue<double> primaryEarliestHitPeakTim = {recobeamtevt_reader, "primaryEarliestHitPeakTim"};
  TTreeReaderArray<double> primaryVertex = {recobeamtevt_reader, "primaryVertex"};
  TTreeReaderValue<int> primaryIstrack = {recobeamtevt_reader, "primaryIstrack"};
  TTreeReaderValue<int> primaryIsshower = {recobeamtevt_reader, "primaryIsshower"};
  TTreeReaderValue<double> primaryBDTScore = {recobeamtevt_reader, "primaryBDTScore"};
  TTreeReaderValue<int> primaryNHits = {recobeamtevt_reader, "primaryNHits"};
  TTreeReaderValue<double> primaryTheta = {recobeamtevt_reader, "primaryTheta"};
  TTreeReaderValue<double> primaryPhi = {recobeamtevt_reader, "primaryPhi"};
  TTreeReaderValue<double> primaryLength = {recobeamtevt_reader, "primaryLength"};
  TTreeReaderValue<double> primaryMomentum = {recobeamtevt_reader, "primaryMomentum"};
  TTreeReaderValue<double> primaryEndMomentum = {recobeamtevt_reader, "primaryEndMomentum"};
  TTreeReaderArray<double> primaryEndPosition = {recobeamtevt_reader, "primaryEndPosition"};
  TTreeReaderArray<double> primaryStartPosition = {recobeamtevt_reader, "primaryStartPosition"};
  TTreeReaderArray<double> primaryEndDirection = {recobeamtevt_reader, "primaryEndDirection"};
  TTreeReaderArray<double> primaryStartDirection = {recobeamtevt_reader, "primaryStartDirection"};
  TTreeReaderValue<double> primaryOpeningAngle = {recobeamtevt_reader, "primaryOpeningAngle"};
  TTreeReaderValue<int> primaryID = {recobeamtevt_reader, "primaryID"};
  TTreeReaderValue<int> primaryShowerBestPlane = {recobeamtevt_reader, "primaryShowerBestPlane"};
  TTreeReaderArray<int> primaryShowerEnergy = {recobeamtevt_reader, "primaryShowerEnergy"};
  TTreeReaderArray<int> primaryShowerMIPEnergy = {recobeamtevt_reader, "primaryShowerMIPEnergy"};
  TTreeReaderArray<int> primaryShowerdEdx = {recobeamtevt_reader, "primaryShowerdEdx"};
  TTreeReaderValue<double> primaryMomentumByRangeProton = {recobeamtevt_reader, "primaryMomentumByRangeProton"};
  TTreeReaderValue<double> primaryMomentumByRangeMuon = {recobeamtevt_reader, "primaryMomentumByRangeMuon"};
  TTreeReaderArray<double> primaryKineticEnergy = {recobeamtevt_reader, "primaryKineticEnergy"};
  TTreeReaderArray<double> primaryRange = {recobeamtevt_reader, "primaryRange"};
  TTreeReaderArray<double> primaryTrkPitchC = {recobeamtevt_reader, "primaryTrkPitchC"};
  TTreeReaderValue<double> primaryT0 = {recobeamtevt_reader, "primaryT0"};
  TTreeReaderArray<int> primaryPID_Pdg = {recobeamtevt_reader, "primaryPID_Pdg"};
  TTreeReaderArray<int> primaryPID_Ndf = {recobeamtevt_reader, "primaryPID_Ndf"};
  TTreeReaderArray<double> primaryPID_MinChi2 = {recobeamtevt_reader, "primaryPID_MinChi2"};
  TTreeReaderArray<double> primaryPID_DeltaChi2 = {recobeamtevt_reader, "primaryPID_DeltaChi2"};
  TTreeReaderArray<double> primaryPID_Chi2Proton = {recobeamtevt_reader, "primaryPID_Chi2Proton"};
  TTreeReaderArray<double> primaryPID_Chi2Kaon = {recobeamtevt_reader, "primaryPID_Chi2Kaon"};
  TTreeReaderArray<double> primaryPID_Chi2Pion = {recobeamtevt_reader, "primaryPID_Chi2Pion"};
  TTreeReaderArray<double> primaryPID_Chi2Muon = {recobeamtevt_reader, "primaryPID_Chi2Muon"};
  TTreeReaderArray<double> primaryPID_MissingE = {recobeamtevt_reader, "primaryPID_MissingE"};
  TTreeReaderArray<double> primaryPID_MissingEavg = {recobeamtevt_reader, "primaryPID_MissingEavg"};
  TTreeReaderArray<double> primaryPID_PIDA = {recobeamtevt_reader, "primaryPID_PIDA"};
  TTreeReaderValue<int> primary_truth_Origin = {recobeamtevt_reader, "primary_truth_Origin"};
  TTreeReaderValue<int> primary_truth_TrackId = {recobeamtevt_reader, "primary_truth_TrackId"};
  TTreeReaderValue<int> primary_truth_Pdg = {recobeamtevt_reader, "primary_truth_Pdg"};
  TTreeReaderValue<int> primary_truth_Mother = {recobeamtevt_reader, "primary_truth_Mother"};
  TTreeReaderArray<double> primary_truth_StartPosition = {recobeamtevt_reader, "primary_truth_StartPosition"};
  TTreeReaderArray<double> primary_truth_EndPosition = {recobeamtevt_reader, "primary_truth_EndPosition"};
  TTreeReaderArray<double> primary_truth_Momentum = {recobeamtevt_reader, "primary_truth_Momentum"};
  TTreeReaderArray<double> primary_truth_EndMomentum = {recobeamtevt_reader, "primary_truth_EndMomentum"};
  TTreeReaderValue<double> primary_truth_P = {recobeamtevt_reader, "primary_truth_P"};
  TTreeReaderValue<double> primary_truth_Pt = {recobeamtevt_reader, "primary_truth_Pt"};
  TTreeReaderValue<double> primary_truth_Mass = {recobeamtevt_reader, "primary_truth_Mass"};
  TTreeReaderValue<double> primary_truth_Theta = {recobeamtevt_reader, "primary_truth_Theta"};
  TTreeReaderValue<double> primary_truth_Phi = {recobeamtevt_reader, "primary_truth_Phi"};
  TTreeReaderValue<double> primary_truth_TotalLength = {recobeamtevt_reader, "primary_truth_TotalLength"};
  TTreeReaderValue<int> primary_truth_Process = {recobeamtevt_reader, "primary_truth_Process"};
  TTreeReaderValue<int> primary_truth_EndProcess = {recobeamtevt_reader, "primary_truth_EndProcess"};
  TTreeReaderValue<int> primary_truth_Isbeammatched = {recobeamtevt_reader, "primary_truth_Isbeammatched"};
  TTreeReaderValue<double> primary_truth_EkinAtVertex_notcorrected = {recobeamtevt_reader, "primary_truth_EkinAtVertex_notcorrected"};
  TTreeReaderValue<double> primary_truth_EkinAtVertex = {recobeamtevt_reader, "primary_truth_EkinAtVertex"};
  TTreeReaderArray<double> primary_truth_Pos_InTPCActive = {recobeamtevt_reader, "primary_truth_Pos_InTPCActive"};
  TTreeReaderArray<double> primary_truth_Momentum_InTPCActive = {recobeamtevt_reader, "primary_truth_Momentum_InTPCActive"};
  TTreeReaderValue<double> primary_truth_P_InTPCActive = {recobeamtevt_reader, "primary_truth_P_InTPCActive"};
  TTreeReaderValue<double> primary_truth_Pt_InTPCActive = {recobeamtevt_reader, "primary_truth_Pt_InTPCActive"};
  TTreeReaderValue<double> primary_truth_Theta_InTPCActive = {recobeamtevt_reader, "primary_truth_Theta_InTPCActive"};
  TTreeReaderValue<double> primary_truth_Phi_InTPCActive = {recobeamtevt_reader, "primary_truth_Phi_InTPCActive"};
  TTreeReaderValue<double> primary_truth_TotalLength_InTPCActive = {recobeamtevt_reader, "primary_truth_TotalLength_InTPCActive"};
  TTreeReaderValue<double> primary_truth_KinEnergy_InTPCActive = {recobeamtevt_reader, "primary_truth_KinEnergy_InTPCActive"};
  TTreeReaderValue<int> primary_truth_NDAUGTHERS = {recobeamtevt_reader, "primary_truth_NDAUGTHERS"};
  TTreeReaderValue<int> primary_truth_NDECAYDAUGTHERS = {recobeamtevt_reader, "primary_truth_NDECAYDAUGTHERS"};
  TTreeReaderArray<int> primary_truthdaughter_TrackId = {recobeamtevt_reader, "primary_truthdaughter_TrackId"};
  TTreeReaderArray<int> primary_truthdaughter_Pdg = {recobeamtevt_reader, "primary_truthdaughter_Pdg"};
  TTreeReaderArray<int> primary_truthdaughter_Mother = {recobeamtevt_reader, "primary_truthdaughter_Mother"};
  TTreeReaderArray<double> primary_truthdaughter_P = {recobeamtevt_reader, "primary_truthdaughter_P"};
  TTreeReaderArray<double> primary_truthdaughter_Pt = {recobeamtevt_reader, "primary_truthdaughter_Pt"};
  TTreeReaderArray<double> primary_truthdaughter_Mass = {recobeamtevt_reader, "primary_truthdaughter_Mass"};
  TTreeReaderArray<double> primary_truthdaughter_Theta = {recobeamtevt_reader, "primary_truthdaughter_Theta"};
  TTreeReaderArray<double> primary_truthdaughter_Phi = {recobeamtevt_reader, "primary_truthdaughter_Phi"};
  TTreeReaderArray<double> primary_truthdaughter_TotalLength = {recobeamtevt_reader, "primary_truthdaughter_TotalLength"};
  TTreeReaderArray<int> primary_truthdaughter_Process = {recobeamtevt_reader, "primary_truthdaughter_Process"};
  TTreeReaderArray<int> primary_truthdaughter_EndProcess = {recobeamtevt_reader, "primary_truthdaughter_EndProcess"};
  TTreeReaderArray<int> primary_truthdecaydaughter_TrackId = {recobeamtevt_reader, "primary_truthdecaydaughter_TrackId"};
  TTreeReaderArray<int> primary_truthdecaydaughter_Pdg = {recobeamtevt_reader, "primary_truthdecaydaughter_Pdg"};
  TTreeReaderArray<int> primary_truthdecaydaughter_Mother = {recobeamtevt_reader, "primary_truthdecaydaughter_Mother"};
  TTreeReaderArray<double> primary_truthdecaydaughter_P = {recobeamtevt_reader, "primary_truthdecaydaughter_P"};
  TTreeReaderArray<double> primary_truthdecaydaughter_Pt = {recobeamtevt_reader, "primary_truthdecaydaughter_Pt"};
  TTreeReaderArray<double> primary_truthdecaydaughter_Mass = {recobeamtevt_reader, "primary_truthdecaydaughter_Mass"};
  TTreeReaderArray<double> primary_truthdecaydaughter_Theta = {recobeamtevt_reader, "primary_truthdecaydaughter_Theta"};
  TTreeReaderArray<double> primary_truthdecaydaughter_Phi = {recobeamtevt_reader, "primary_truthdecaydaughter_Phi"};
  TTreeReaderArray<double> primary_truthdecaydaughter_TotalLength = {recobeamtevt_reader, "primary_truthdecaydaughter_TotalLength"};
  TTreeReaderArray<int> primary_truthdecaydaughter_Process = {recobeamtevt_reader, "primary_truthdecaydaughter_Process"};
  TTreeReaderArray<int> primary_truthdecaydaughter_EndProcess = {recobeamtevt_reader, "primary_truthdecaydaughter_EndProcess"};

  // Reco & associated truth daughters (these are all arrays of length NMAXDAUGHTER = 15)
  TTreeReaderArray<double> daughterPID_PIDA   = {recodaughters_reader, "daughterPID_PIDA"};
  TTreeReaderValue<int> NDAUGHTERS = {recodaughters_reader, "NDAUGHTERS"};
  TTreeReaderArray<double> daughterVertex = {recodaughters_reader, "daughterVertex"};
  TTreeReaderArray<int> daughterIstrack = {recodaughters_reader, "daughterIstrack"};
  TTreeReaderArray<int> daughterIsshower = {recodaughters_reader, "daughterIsshower"};
  TTreeReaderArray<int> daughterNHits = {recodaughters_reader, "daughterNHits"};
  TTreeReaderArray<double> daughterTheta = {recodaughters_reader, "daughterTheta"};
  TTreeReaderArray<double> daughterPhi = {recodaughters_reader, "daughterPhi"};
  TTreeReaderArray<double> daughterLength = {recodaughters_reader, "daughterLength"};
  TTreeReaderArray<double> daughterMomentum = {recodaughters_reader, "daughterMomentum"};
  TTreeReaderArray<double> daughterEndMomentum = {recodaughters_reader, "daughterEndMomentum"};
  TTreeReaderArray<double> daughterOpeningAngle = {recodaughters_reader, "daughterOpeningAngle"};
  TTreeReaderArray<int> daughterShowerBestPlane = {recodaughters_reader, "daughterShowerBestPlane"};
  TTreeReaderArray<double> daughterMomentumByRangeProton = {recodaughters_reader, "daughterMomentumByRangeProton"};
  TTreeReaderArray<double> daughterMomentumByRangeMuon = {recodaughters_reader, "daughterMomentumByRangeMuon"};
  TTreeReaderArray<int> daughterID = {recodaughters_reader, "daughterID"};
  TTreeReaderArray<double> daughterT0 = {recodaughters_reader, "daughterT0"};
  TTreeReaderArray<int> daughter_truth_TrackId = {recodaughters_reader, "daughter_truth_TrackId"};
  TTreeReaderArray<int> daughter_truth_Pdg = {recodaughters_reader, "daughter_truth_Pdg"};
  TTreeReaderArray<int> daughter_truth_Mother = {recodaughters_reader, "daughter_truth_Mother"};
  TTreeReaderArray<double> daughter_truth_P = {recodaughters_reader, "daughter_truth_P"};
  TTreeReaderArray<double> daughter_truth_Pt = {recodaughters_reader, "daughter_truth_Pt"};
  TTreeReaderArray<double> daughter_truth_Mass = {recodaughters_reader, "daughter_truth_Mass"};
  TTreeReaderArray<double> daughter_truth_Theta = {recodaughters_reader, "daughter_truth_Theta"};
  TTreeReaderArray<double> daughter_truth_Phi = {recodaughters_reader, "daughter_truth_Phi"};
  TTreeReaderArray<double> daughter_truth_TotalLength = {recodaughters_reader, "daughter_truth_TotalLength"};
  TTreeReaderArray<int> daughter_truth_Process = {recodaughters_reader, "daughter_truth_Process"};
  TTreeReaderArray<int> daughter_truth_EndProcess = {recodaughters_reader, "daughter_truth_EndProcess"};


private:

  TFile * infile;

};


#endif //PION_QE_READER_H
