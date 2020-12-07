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
  TTreeReaderValue<Int_t> run = {beamtrack_reader, "run"};
  TTreeReaderValue<Int_t> subrun = {beamtrack_reader, "subrun"};
  TTreeReaderValue<Int_t> event = {beamtrack_reader, "event"};
  TTreeReaderValue<Int_t> beamNTracks = {beamtrack_reader, "beamNTracks"};
  TTreeReaderValue<Int_t> beamtrigger = {beamtrack_reader, "beamtrigger"};
  TTreeReaderValue<Double_t> tof = {beamtrack_reader, "tof"};
  TTreeReaderValue<Double_t> tof_expElec = {beamtrack_reader, "tof_expElec"};
  TTreeReaderValue<Double_t> tof_expMuon = {beamtrack_reader, "tof_expMuon"};
  TTreeReaderValue<Double_t> tof_expPion = {beamtrack_reader, "tof_expPion"};
  TTreeReaderValue<Double_t> tof_expKaon = {beamtrack_reader, "tof_expKaon"};
  TTreeReaderValue<Double_t> tof_expProt = {beamtrack_reader, "tof_expProt"};
  TTreeReaderValue<Double_t> tof_expDeut = {beamtrack_reader, "tof_expDeut"};
  TTreeReaderArray<Int_t> cerenkovStatus = {beamtrack_reader, "cerenkovStatus"};
  TTreeReaderArray<Double_t> cerenkovTime = {beamtrack_reader, "cerenkovTime"};
  TTreeReaderArray<Double_t> cerenkovPressure = {beamtrack_reader, "cerenkovPressure"};
  TTreeReaderValue<Double_t> beamtrackMomentum = {beamtrack_reader, "beamtrackMomentum"};
  TTreeReaderValue<Double_t> beamtrackEnergy = {beamtrack_reader, "beamtrackEnergy"};
  TTreeReaderArray<Double_t> beamtrackPos = {beamtrack_reader, "beamtrackPos"};
  TTreeReaderArray<Double_t> beamtrackDir = {beamtrack_reader, "beamtrackDir"};
  TTreeReaderValue<Int_t> BIAndTimingMatched = {beamtrack_reader, "BIAndTimingMatched"};
  TTreeReaderValue<Int_t> beamtrack_truth_Origin = {beamtrack_reader, "beamtrack_truth_Origin"};
  TTreeReaderValue<Int_t> beamtrackPdg = {beamtrack_reader, "beamtrackPdg"};
  TTreeReaderValue<Int_t> beamtrackID = {beamtrack_reader, "beamtrackID"};
  TTreeReaderArray<Double_t> beamtrack_truth_EndPos = {beamtrack_reader, "beamtrack_truth_EndPos"};
  TTreeReaderArray<Double_t> beamtrack_truth_Momentum = {beamtrack_reader, "beamtrack_truth_Momentum"};
  TTreeReaderValue<Double_t> beamtrack_truth_KinEnergy = {beamtrack_reader, "beamtrack_truth_KinEnergy"};
  TTreeReaderValue<Double_t> beamtrack_truth_Pt = {beamtrack_reader, "beamtrack_truth_Pt"};
  TTreeReaderValue<Double_t> beamtrack_truth_Mass = {beamtrack_reader, "beamtrack_truth_Mass"};
  TTreeReaderValue<Double_t> beamtrack_truth_Theta = {beamtrack_reader, "beamtrack_truth_Theta"};
  TTreeReaderValue<Double_t> beamtrack_truth_Phi = {beamtrack_reader, "beamtrack_truth_Phi"};
  TTreeReaderValue<Double_t> beamtrack_truth_TotalLength = {beamtrack_reader, "beamtrack_truth_TotalLength"};
  TTreeReaderValue<Int_t> beamtrack_truth_Process = {beamtrack_reader, "beamtrack_truth_Process"};
  TTreeReaderValue<Int_t> beamtrack_truth_EndProcess = {beamtrack_reader, "beamtrack_truth_EndProcess"};
  TTreeReaderValue<Int_t> beamtrack_truth_Pdg = {beamtrack_reader, "beamtrack_truth_Pdg"};
  TTreeReaderValue<Int_t> beamtrack_truth_NDAUGTHERS = {beamtrack_reader, "beamtrack_truth_NDAUGTHERS"};
  TTreeReaderValue<Int_t> beamtrack_truth_NDECAYDAUGTHERS = {beamtrack_reader, "beamtrack_truth_NDECAYDAUGTHERS"};
  TTreeReaderArray<Double_t> beamtrack_truth_Pos_InTPCActive = {beamtrack_reader, "beamtrack_truth_Pos_InTPCActive"};
  TTreeReaderArray<Double_t> beamtrack_truth_Momentum_InTPCActive = {beamtrack_reader, "beamtrack_truth_Momentum_InTPCActive"};
  TTreeReaderValue<Double_t> beamtrack_truth_P_InTPCActive = {beamtrack_reader, "beamtrack_truth_P_InTPCActive"};
  TTreeReaderValue<Double_t> beamtrack_truth_Pt_InTPCActive = {beamtrack_reader, "beamtrack_truth_Pt_InTPCActive"};
  TTreeReaderValue<Double_t> beamtrack_truth_Theta_InTPCActive = {beamtrack_reader, "beamtrack_truth_Theta_InTPCActive"};
  TTreeReaderValue<Double_t> beamtrack_truth_Phi_InTPCActive = {beamtrack_reader, "beamtrack_truth_Phi_InTPCActive"};
  TTreeReaderValue<Double_t> beamtrack_truth_TotalLength_InTPCActive = {beamtrack_reader, "beamtrack_truth_TotalLength_InTPCActive"};
  TTreeReaderValue<Double_t> beamtrack_truth_KinEnergy_InTPCActive = {beamtrack_reader, "beamtrack_truth_KinEnergy_InTPCActive"};
  TTreeReaderArray<Int_t> beamtrack_truthdaughter_TrackId = {beamtrack_reader, "beamtrack_truthdaughter_TrackId"};
  TTreeReaderArray<Int_t> beamtrack_truthdaughter_Pdg = {beamtrack_reader, "beamtrack_truthdaughter_Pdg"};
  TTreeReaderArray<Int_t> beamtrack_truthdaughter_Mother = {beamtrack_reader, "beamtrack_truthdaughter_Mother"};
  TTreeReaderArray<Double_t> beamtrack_truthdaughter_P = {beamtrack_reader, "beamtrack_truthdaughter_P"};
  TTreeReaderArray<Double_t> beamtrack_truthdaughter_Pt = {beamtrack_reader, "beamtrack_truthdaughter_Pt"};
  TTreeReaderArray<Double_t> beamtrack_truthdaughter_Mass = {beamtrack_reader, "beamtrack_truthdaughter_Mass"};
  TTreeReaderArray<Double_t> beamtrack_truthdaughter_Theta = {beamtrack_reader, "beamtrack_truthdaughter_Theta"};
  TTreeReaderArray<Double_t> beamtrack_truthdaughter_Phi = {beamtrack_reader, "beamtrack_truthdaughter_Phi"};
  TTreeReaderArray<Double_t> beamtrack_truthdaughter_TotalLength = {beamtrack_reader, "beamtrack_truthdaughter_TotalLength"};
  TTreeReaderArray<Int_t> beamtrack_truthdaughter_Process = {beamtrack_reader, "beamtrack_truthdaughter_Process"};
  TTreeReaderArray<Int_t> beamtrack_truthdaughter_EndProcess = {beamtrack_reader, "beamtrack_truthdaughter_EndProcess"};
  TTreeReaderArray<Int_t> beamtrack_truthdecaydaughter_TrackId = {beamtrack_reader, "beamtrack_truthdecaydaughter_TrackId"};
  TTreeReaderArray<Int_t> beamtrack_truthdecaydaughter_Pdg = {beamtrack_reader, "beamtrack_truthdecaydaughter_Pdg"};
  TTreeReaderArray<Int_t> beamtrack_truthdecaydaughter_Mother = {beamtrack_reader, "beamtrack_truthdecaydaughter_Mother"};
  TTreeReaderArray<Double_t> beamtrack_truthdecaydaughter_P = {beamtrack_reader, "beamtrack_truthdecaydaughter_P"};
  TTreeReaderArray<Double_t> beamtrack_truthdecaydaughter_Pt = {beamtrack_reader, "beamtrack_truthdecaydaughter_Pt"};
  TTreeReaderArray<Double_t> beamtrack_truthdecaydaughter_Mass = {beamtrack_reader, "beamtrack_truthdecaydaughter_Mass"};
  TTreeReaderArray<Double_t> beamtrack_truthdecaydaughter_Theta = {beamtrack_reader, "beamtrack_truthdecaydaughter_Theta"};
  TTreeReaderArray<Double_t> beamtrack_truthdecaydaughter_Phi = {beamtrack_reader, "beamtrack_truthdecaydaughter_Phi"};
  TTreeReaderArray<Double_t> beamtrack_truthdecaydaughter_TotalLength = {beamtrack_reader, "beamtrack_truthdecaydaughter_TotalLength"};
  TTreeReaderArray<Int_t> beamtrack_truthdecaydaughter_Process = {beamtrack_reader, "beamtrack_truthdecaydaughter_Process"};
  TTreeReaderArray<Int_t> beamtrack_truthdecaydaughter_EndProcess = {beamtrack_reader, "beamtrack_truthdecaydaughter_EndProcess"};

  // Reco & truth beam events including daughters
  TTreeReaderValue<Double_t> timestamp = {recobeamtevt_reader, "timestamp"};
  TTreeReaderArray<Int_t> Nactivefembs = {recobeamtevt_reader, "Nactivefembs"};
  TTreeReaderValue<Int_t> NpfParticles = {recobeamtevt_reader, "NpfParticles"};
  TTreeReaderValue<Double_t> primaryEarliestHitPeakTim = {recobeamtevt_reader, "primaryEarliestHitPeakTim"};
  TTreeReaderArray<Double_t> primaryVertex = {recobeamtevt_reader, "primaryVertex"};
  TTreeReaderValue<Int_t> primaryIstrack = {recobeamtevt_reader, "primaryIstrack"};
  TTreeReaderValue<Int_t> primaryIsshower = {recobeamtevt_reader, "primaryIsshower"};
  TTreeReaderValue<Double_t> primaryBDTScore = {recobeamtevt_reader, "primaryBDTScore"};
  TTreeReaderValue<Int_t> primaryNHits = {recobeamtevt_reader, "primaryNHits"};
  TTreeReaderValue<Double_t> primaryTheta = {recobeamtevt_reader, "primaryTheta"};
  TTreeReaderValue<Double_t> primaryPhi = {recobeamtevt_reader, "primaryPhi"};
  TTreeReaderValue<Double_t> primaryLength = {recobeamtevt_reader, "primaryLength"};
  TTreeReaderValue<Double_t> primaryMomentum = {recobeamtevt_reader, "primaryMomentum"};
  TTreeReaderValue<Double_t> primaryEndMomentum = {recobeamtevt_reader, "primaryEndMomentum"};
  TTreeReaderArray<Double_t> primaryEndPosition = {recobeamtevt_reader, "primaryEndPosition"};
  TTreeReaderArray<Double_t> primaryStartPosition = {recobeamtevt_reader, "primaryStartPosition"};
  TTreeReaderArray<Double_t> primaryEndDirection = {recobeamtevt_reader, "primaryEndDirection"};
  TTreeReaderArray<Double_t> primaryStartDirection = {recobeamtevt_reader, "primaryStartDirection"};
  TTreeReaderValue<Double_t> primaryOpeningAngle = {recobeamtevt_reader, "primaryOpeningAngle"};
  TTreeReaderValue<Int_t> primaryID = {recobeamtevt_reader, "primaryID"};
  TTreeReaderValue<Int_t> primaryShowerBestPlane = {recobeamtevt_reader, "primaryShowerBestPlane"};
  TTreeReaderArray<Int_t> primaryShowerEnergy = {recobeamtevt_reader, "primaryShowerEnergy"};
  TTreeReaderArray<Int_t> primaryShowerMIPEnergy = {recobeamtevt_reader, "primaryShowerMIPEnergy"};
  TTreeReaderArray<Int_t> primaryShowerdEdx = {recobeamtevt_reader, "primaryShowerdEdx"};
  TTreeReaderValue<Double_t> primaryMomentumByRangeProton = {recobeamtevt_reader, "primaryMomentumByRangeProton"};
  TTreeReaderValue<Double_t> primaryMomentumByRangeMuon = {recobeamtevt_reader, "primaryMomentumByRangeMuon"};
  TTreeReaderArray<Double_t> primaryKineticEnergy = {recobeamtevt_reader, "primaryKineticEnergy"};
  TTreeReaderArray<Double_t> primaryRange = {recobeamtevt_reader, "primaryRange"};
  TTreeReaderArray<Double_t> primaryTrkPitchC = {recobeamtevt_reader, "primaryTrkPitchC"};
  TTreeReaderValue<Double_t> primaryT0 = {recobeamtevt_reader, "primaryT0"};
  TTreeReaderArray<Int_t> primaryPID_Pdg = {recobeamtevt_reader, "primaryPID_Pdg"};
  TTreeReaderArray<Int_t> primaryPID_Ndf = {recobeamtevt_reader, "primaryPID_Ndf"};
  TTreeReaderArray<Double_t> primaryPID_MinChi2 = {recobeamtevt_reader, "primaryPID_MinChi2"};
  TTreeReaderArray<Double_t> primaryPID_DeltaChi2 = {recobeamtevt_reader, "primaryPID_DeltaChi2"};
  TTreeReaderArray<Double_t> primaryPID_Chi2Proton = {recobeamtevt_reader, "primaryPID_Chi2Proton"};
  TTreeReaderArray<Double_t> primaryPID_Chi2Kaon = {recobeamtevt_reader, "primaryPID_Chi2Kaon"};
  TTreeReaderArray<Double_t> primaryPID_Chi2Pion = {recobeamtevt_reader, "primaryPID_Chi2Pion"};
  TTreeReaderArray<Double_t> primaryPID_Chi2Muon = {recobeamtevt_reader, "primaryPID_Chi2Muon"};
  TTreeReaderArray<Double_t> primaryPID_MissingE = {recobeamtevt_reader, "primaryPID_MissingE"};
  TTreeReaderArray<Double_t> primaryPID_MissingEavg = {recobeamtevt_reader, "primaryPID_MissingEavg"};
  TTreeReaderArray<Double_t> primaryPID_PIDA = {recobeamtevt_reader, "primaryPID_PIDA"};
  TTreeReaderValue<Int_t> primary_truth_Origin = {recobeamtevt_reader, "primary_truth_Origin"};
  TTreeReaderValue<Int_t> primary_truth_TrackId = {recobeamtevt_reader, "primary_truth_TrackId"};
  TTreeReaderValue<Int_t> primary_truth_Pdg = {recobeamtevt_reader, "primary_truth_Pdg"};
  TTreeReaderValue<Int_t> primary_truth_Mother = {recobeamtevt_reader, "primary_truth_Mother"};
  TTreeReaderArray<Double_t> primary_truth_StartPosition = {recobeamtevt_reader, "primary_truth_StartPosition"};
  TTreeReaderArray<Double_t> primary_truth_EndPosition = {recobeamtevt_reader, "primary_truth_EndPosition"};
  TTreeReaderArray<Double_t> primary_truth_Momentum = {recobeamtevt_reader, "primary_truth_Momentum"};
  TTreeReaderArray<Double_t> primary_truth_EndMomentum = {recobeamtevt_reader, "primary_truth_EndMomentum"};
  TTreeReaderValue<Double_t> primary_truth_P = {recobeamtevt_reader, "primary_truth_P"};
  TTreeReaderValue<Double_t> primary_truth_Pt = {recobeamtevt_reader, "primary_truth_Pt"};
  TTreeReaderValue<Double_t> primary_truth_Mass = {recobeamtevt_reader, "primary_truth_Mass"};
  TTreeReaderValue<Double_t> primary_truth_Theta = {recobeamtevt_reader, "primary_truth_Theta"};
  TTreeReaderValue<Double_t> primary_truth_Phi = {recobeamtevt_reader, "primary_truth_Phi"};
  TTreeReaderValue<Double_t> primary_truth_TotalLength = {recobeamtevt_reader, "primary_truth_TotalLength"};
  TTreeReaderValue<Int_t> primary_truth_Process = {recobeamtevt_reader, "primary_truth_Process"};
  TTreeReaderValue<Int_t> primary_truth_EndProcess = {recobeamtevt_reader, "primary_truth_EndProcess"};
  TTreeReaderValue<Int_t> primary_truth_Isbeammatched = {recobeamtevt_reader, "primary_truth_Isbeammatched"};
  TTreeReaderValue<Double_t> primary_truth_EkinAtVertex_notcorrected = {recobeamtevt_reader, "primary_truth_EkinAtVertex_notcorrected"};
  TTreeReaderValue<Double_t> primary_truth_EkinAtVertex = {recobeamtevt_reader, "primary_truth_EkinAtVertex"};
  TTreeReaderArray<Double_t> primary_truth_Pos_InTPCActive = {recobeamtevt_reader, "primary_truth_Pos_InTPCActive"};
  TTreeReaderArray<Double_t> primary_truth_Momentum_InTPCActive = {recobeamtevt_reader, "primary_truth_Momentum_InTPCActive"};
  TTreeReaderValue<Double_t> primary_truth_P_InTPCActive = {recobeamtevt_reader, "primary_truth_P_InTPCActive"};
  TTreeReaderValue<Double_t> primary_truth_Pt_InTPCActive = {recobeamtevt_reader, "primary_truth_Pt_InTPCActive"};
  TTreeReaderValue<Double_t> primary_truth_Theta_InTPCActive = {recobeamtevt_reader, "primary_truth_Theta_InTPCActive"};
  TTreeReaderValue<Double_t> primary_truth_Phi_InTPCActive = {recobeamtevt_reader, "primary_truth_Phi_InTPCActive"};
  TTreeReaderValue<Double_t> primary_truth_TotalLength_InTPCActive = {recobeamtevt_reader, "primary_truth_TotalLength_InTPCActive"};
  TTreeReaderValue<Double_t> primary_truth_KinEnergy_InTPCActive = {recobeamtevt_reader, "primary_truth_KinEnergy_InTPCActive"};
  TTreeReaderValue<Int_t> primary_truth_NDAUGTHERS = {recobeamtevt_reader, "primary_truth_NDAUGTHERS"};
  TTreeReaderValue<Int_t> primary_truth_NDECAYDAUGTHERS = {recobeamtevt_reader, "primary_truth_NDECAYDAUGTHERS"};
  TTreeReaderArray<Int_t> primary_truthdaughter_TrackId = {recobeamtevt_reader, "primary_truthdaughter_TrackId"};
  TTreeReaderArray<Int_t> primary_truthdaughter_Pdg = {recobeamtevt_reader, "primary_truthdaughter_Pdg"};
  TTreeReaderArray<Int_t> primary_truthdaughter_Mother = {recobeamtevt_reader, "primary_truthdaughter_Mother"};
  TTreeReaderArray<Double_t> primary_truthdaughter_P = {recobeamtevt_reader, "primary_truthdaughter_P"};
  TTreeReaderArray<Double_t> primary_truthdaughter_Pt = {recobeamtevt_reader, "primary_truthdaughter_Pt"};
  TTreeReaderArray<Double_t> primary_truthdaughter_Mass = {recobeamtevt_reader, "primary_truthdaughter_Mass"};
  TTreeReaderArray<Double_t> primary_truthdaughter_Theta = {recobeamtevt_reader, "primary_truthdaughter_Theta"};
  TTreeReaderArray<Double_t> primary_truthdaughter_Phi = {recobeamtevt_reader, "primary_truthdaughter_Phi"};
  TTreeReaderArray<Double_t> primary_truthdaughter_TotalLength = {recobeamtevt_reader, "primary_truthdaughter_TotalLength"};
  TTreeReaderArray<Int_t> primary_truthdaughter_Process = {recobeamtevt_reader, "primary_truthdaughter_Process"};
  TTreeReaderArray<Int_t> primary_truthdaughter_EndProcess = {recobeamtevt_reader, "primary_truthdaughter_EndProcess"};
  TTreeReaderArray<Int_t> primary_truthdecaydaughter_TrackId = {recobeamtevt_reader, "primary_truthdecaydaughter_TrackId"};
  TTreeReaderArray<Int_t> primary_truthdecaydaughter_Pdg = {recobeamtevt_reader, "primary_truthdecaydaughter_Pdg"};
  TTreeReaderArray<Int_t> primary_truthdecaydaughter_Mother = {recobeamtevt_reader, "primary_truthdecaydaughter_Mother"};
  TTreeReaderArray<Double_t> primary_truthdecaydaughter_P = {recobeamtevt_reader, "primary_truthdecaydaughter_P"};
  TTreeReaderArray<Double_t> primary_truthdecaydaughter_Pt = {recobeamtevt_reader, "primary_truthdecaydaughter_Pt"};
  TTreeReaderArray<Double_t> primary_truthdecaydaughter_Mass = {recobeamtevt_reader, "primary_truthdecaydaughter_Mass"};
  TTreeReaderArray<Double_t> primary_truthdecaydaughter_Theta = {recobeamtevt_reader, "primary_truthdecaydaughter_Theta"};
  TTreeReaderArray<Double_t> primary_truthdecaydaughter_Phi = {recobeamtevt_reader, "primary_truthdecaydaughter_Phi"};
  TTreeReaderArray<Double_t> primary_truthdecaydaughter_TotalLength = {recobeamtevt_reader, "primary_truthdecaydaughter_TotalLength"};
  TTreeReaderArray<Int_t> primary_truthdecaydaughter_Process = {recobeamtevt_reader, "primary_truthdecaydaughter_Process"};
  TTreeReaderArray<Int_t> primary_truthdecaydaughter_EndProcess = {recobeamtevt_reader, "primary_truthdecaydaughter_EndProcess"};

  // Reco & associated truth daughters (these are all arrays of length NMAXDAUGHTER = 15)
  TTreeReaderArray<double> daughterPID_PIDA   = {recodaughters_reader, "daughterPID_PIDA"};
  TTreeReaderValue<Int_t> NDAUGHTERS = {recodaughters_reader, "NDAUGHTERS"};
  TTreeReaderArray<Double_t> daughterVertex = {recodaughters_reader, "daughterVertex"};
  TTreeReaderArray<Int_t> daughterIstrack = {recodaughters_reader, "daughterIstrack"};
  TTreeReaderArray<Int_t> daughterIsshower = {recodaughters_reader, "daughterIsshower"};
  TTreeReaderArray<Int_t> daughterNHits = {recodaughters_reader, "daughterNHits"};
  TTreeReaderArray<Double_t> daughterTheta = {recodaughters_reader, "daughterTheta"};
  TTreeReaderArray<Double_t> daughterPhi = {recodaughters_reader, "daughterPhi"};
  TTreeReaderArray<Double_t> daughterLength = {recodaughters_reader, "daughterLength"};
  TTreeReaderArray<Double_t> daughterMomentum = {recodaughters_reader, "daughterMomentum"};
  TTreeReaderArray<Double_t> daughterEndMomentum = {recodaughters_reader, "daughterEndMomentum"};
  TTreeReaderArray<Double_t> daughterOpeningAngle = {recodaughters_reader, "daughterOpeningAngle"};
  TTreeReaderArray<Int_t> daughterShowerBestPlane = {recodaughters_reader, "daughterShowerBestPlane"};
  TTreeReaderArray<Double_t> daughterMomentumByRangeProton = {recodaughters_reader, "daughterMomentumByRangeProton"};
  TTreeReaderArray<Double_t> daughterMomentumByRangeMuon = {recodaughters_reader, "daughterMomentumByRangeMuon"};
  TTreeReaderArray<Int_t> daughterID = {recodaughters_reader, "daughterID"};
  TTreeReaderArray<Double_t> daughterT0 = {recodaughters_reader, "daughterT0"};
  TTreeReaderArray<Int_t> daughter_truth_TrackId = {recodaughters_reader, "daughter_truth_TrackId"};
  TTreeReaderArray<Int_t> daughter_truth_Pdg = {recodaughters_reader, "daughter_truth_Pdg"};
  TTreeReaderArray<Int_t> daughter_truth_Mother = {recodaughters_reader, "daughter_truth_Mother"};
  TTreeReaderArray<Double_t> daughter_truth_P = {recodaughters_reader, "daughter_truth_P"};
  TTreeReaderArray<Double_t> daughter_truth_Pt = {recodaughters_reader, "daughter_truth_Pt"};
  TTreeReaderArray<Double_t> daughter_truth_Mass = {recodaughters_reader, "daughter_truth_Mass"};
  TTreeReaderArray<Double_t> daughter_truth_Theta = {recodaughters_reader, "daughter_truth_Theta"};
  TTreeReaderArray<Double_t> daughter_truth_Phi = {recodaughters_reader, "daughter_truth_Phi"};
  TTreeReaderArray<Double_t> daughter_truth_TotalLength = {recodaughters_reader, "daughter_truth_TotalLength"};
  TTreeReaderArray<Int_t> daughter_truth_Process = {recodaughters_reader, "daughter_truth_Process"};
  TTreeReaderArray<Int_t> daughter_truth_EndProcess = {recodaughters_reader, "daughter_truth_EndProcess"};


private:

  TFile * infile;

};


#endif //PION_QE_READER_H
