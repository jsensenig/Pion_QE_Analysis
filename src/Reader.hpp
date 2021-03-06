//
// Created by Jon Sensenig on 12/4/20.
//

#ifndef PION_QE_READER_HPP
#define PION_QE_READER_HPP

#include "datatypes/vector_vector.h"

#include "TFile.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"


class Reader {

public:

  explicit Reader( TFile * file );
  virtual ~Reader();

  bool Next();
  void RestartTrees();

  // TTree readers
  TTreeReader config_reader = { "pdAnalysisTree/Config", infile };
  TTreeReader beamtrack_reader = { "pdAnalysisTree/BeamTrack", infile };
  TTreeReader recobeamtevt_reader  = { "pdAnalysisTree/ReconstructedBeamEvents", infile };
  TTreeReader recodaughters_reader = { "pdAnalysisTree/ReconstructedDaughters", infile };

  // Config tree
  TTreeReaderValue<int> NAPAs = {config_reader, "NAPAs"};
  TTreeReaderValue<int> NChansPerAPA = {config_reader, "NChansPerAPA"};
  TTreeReaderValue<int> NCryostats = {config_reader, "NCryostats"};
  TTreeReaderValue<int> NTPCs = {config_reader, "NTPCs"};
  TTreeReaderValue<int> NChannels = {config_reader, "NChannels"};
  TTreeReaderValue<int> NPlanes = {config_reader, "NPlanes"};
  TTreeReaderArray<double> ActiveTPCBoundsX = {config_reader, "ActiveTPCBoundsX"};
  TTreeReaderArray<double> ActiveTPCBoundsY = {config_reader, "ActiveTPCBoundsY"};
  TTreeReaderArray<double > ActiveTPCBoundsZ = {config_reader, "ActiveTPCBoundsZ"};

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
  TTreeReaderValue<double> beamtrackPosX = {beamtrack_reader, "beamtrackPosX"};
  TTreeReaderValue<double> beamtrackPosY = {beamtrack_reader, "beamtrackPosY"};
  TTreeReaderValue<double> beamtrackPosZ = {beamtrack_reader, "beamtrackPosZ"};
  TTreeReaderValue<double> beamtrackPosT = {beamtrack_reader, "beamtrackPosT"};
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
  TTreeReaderArray<double> beamtrack_truthdaughter_StartPositionX = {beamtrack_reader, "beamtrack_truthdaughter_StartPositionX"};
  TTreeReaderArray<double> beamtrack_truthdaughter_StartPositionY = {beamtrack_reader, "beamtrack_truthdaughter_StartPositionY"};
  TTreeReaderArray<double> beamtrack_truthdaughter_StartPositionZ = {beamtrack_reader, "beamtrack_truthdaughter_StartPositionZ"};
  TTreeReaderArray<double> beamtrack_truthdaughter_StartPositionT = {beamtrack_reader, "beamtrack_truthdaughter_StartPositionT"};
  TTreeReaderArray<double> beamtrack_truthdaughter_EndPositionX = {beamtrack_reader, "beamtrack_truthdaughter_EndPositionX"};
  TTreeReaderArray<double> beamtrack_truthdaughter_EndPositionY = {beamtrack_reader, "beamtrack_truthdaughter_EndPositionY"};
  TTreeReaderArray<double> beamtrack_truthdaughter_EndPositionZ = {beamtrack_reader, "beamtrack_truthdaughter_EndPositionZ"};
  TTreeReaderArray<double> beamtrack_truthdaughter_EndPositionT = {beamtrack_reader, "beamtrack_truthdaughter_EndPositionT"};
  TTreeReaderArray<double> beamtrack_truthdaughter_P = {beamtrack_reader, "beamtrack_truthdaughter_P"};
  TTreeReaderArray<double> beamtrack_truthdaughter_MomentumX = {beamtrack_reader, "beamtrack_truthdaughter_MomentumX"};
  TTreeReaderArray<double> beamtrack_truthdaughter_MomentumY = {beamtrack_reader, "beamtrack_truthdaughter_MomentumY"};
  TTreeReaderArray<double> beamtrack_truthdaughter_MomentumZ = {beamtrack_reader, "beamtrack_truthdaughter_MomentumZ"};
  TTreeReaderArray<double> beamtrack_truthdaughter_MomentumE = {beamtrack_reader, "beamtrack_truthdaughter_MomentumE"};
  TTreeReaderArray<double> beamtrack_truthdaughter_EndMomentumX = {beamtrack_reader, "beamtrack_truthdaughter_EndMomentumX"};
  TTreeReaderArray<double> beamtrack_truthdaughter_EndMomentumY = {beamtrack_reader, "beamtrack_truthdaughter_EndMomentumY"};
  TTreeReaderArray<double> beamtrack_truthdaughter_EndMomentumZ = {beamtrack_reader, "beamtrack_truthdaughter_EndMomentumZ"};
  TTreeReaderArray<double> beamtrack_truthdaughter_EndMomentumE = {beamtrack_reader, "beamtrack_truthdaughter_EndMomentumE"};
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
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_StartPositionX = {beamtrack_reader, "beamtrack_truthdecaydaughter_StartPositionX"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_StartPositionY = {beamtrack_reader, "beamtrack_truthdecaydaughter_StartPositionY"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_StartPositionZ = {beamtrack_reader, "beamtrack_truthdecaydaughter_StartPositionZ"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_StartPositionT = {beamtrack_reader, "beamtrack_truthdecaydaughter_StartPositionT"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_EndPositionX = {beamtrack_reader, "beamtrack_truthdecaydaughter_EndPositionX"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_EndPositionY = {beamtrack_reader, "beamtrack_truthdecaydaughter_EndPositionY"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_EndPositionZ = {beamtrack_reader, "beamtrack_truthdecaydaughter_EndPositionZ"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_EndPositionT = {beamtrack_reader, "beamtrack_truthdecaydaughter_EndPositionT"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_P = {beamtrack_reader, "beamtrack_truthdecaydaughter_P"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_MomentumX = {beamtrack_reader, "beamtrack_truthdecaydaughter_MomentumX"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_MomentumY = {beamtrack_reader, "beamtrack_truthdecaydaughter_MomentumY"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_MomentumZ = {beamtrack_reader, "beamtrack_truthdecaydaughter_MomentumZ"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_MomentumE = {beamtrack_reader, "beamtrack_truthdecaydaughter_MomentumE"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_EndMomentumX = {beamtrack_reader, "beamtrack_truthdecaydaughter_EndMomentumX"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_EndMomentumY = {beamtrack_reader, "beamtrack_truthdecaydaughter_EndMomentumY"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_EndMomentumZ = {beamtrack_reader, "beamtrack_truthdecaydaughter_EndMomentumZ"};
  TTreeReaderArray<double> beamtrack_truthdecaydaughter_EndMomentumE = {beamtrack_reader, "beamtrack_truthdecaydaughter_EndMomentumE"};
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
  TTreeReaderArray<double> primary_truthdaughter_StartPositionX = {recobeamtevt_reader, "primary_truthdaughter_StartPositionX"};
  TTreeReaderArray<double> primary_truthdaughter_StartPositionY = {recobeamtevt_reader, "primary_truthdaughter_StartPositionY"};
  TTreeReaderArray<double> primary_truthdaughter_StartPositionZ = {recobeamtevt_reader, "primary_truthdaughter_StartPositionZ"};
  TTreeReaderArray<double> primary_truthdaughter_StartPositionT = {recobeamtevt_reader, "primary_truthdaughter_StartPositionT"};
  TTreeReaderArray<double> primary_truthdaughter_EndPositionX = {recobeamtevt_reader, "primary_truthdaughter_EndPositionX"};
  TTreeReaderArray<double> primary_truthdaughter_EndPositionY = {recobeamtevt_reader, "primary_truthdaughter_EndPositionY"};
  TTreeReaderArray<double> primary_truthdaughter_EndPositionZ = {recobeamtevt_reader, "primary_truthdaughter_EndPositionZ"};
  TTreeReaderArray<double> primary_truthdaughter_EndPositionT = {recobeamtevt_reader, "primary_truthdaughter_EndPositionT"};
  TTreeReaderArray<double> primary_truthdaughter_P = {recobeamtevt_reader, "primary_truthdaughter_P"};
  TTreeReaderArray<double> primary_truthdaughter_MomentumX = {recobeamtevt_reader, "primary_truthdaughter_MomentumX"};
  TTreeReaderArray<double> primary_truthdaughter_MomentumY = {recobeamtevt_reader, "primary_truthdaughter_MomentumY"};
  TTreeReaderArray<double> primary_truthdaughter_MomentumZ = {recobeamtevt_reader, "primary_truthdaughter_MomentumZ"};
  TTreeReaderArray<double> primary_truthdaughter_MomentumE = {recobeamtevt_reader, "primary_truthdaughter_MomentumE"};
  TTreeReaderArray<double> primary_truthdaughter_EndMomentumX = {recobeamtevt_reader, "primary_truthdaughter_EndMomentumX"};
  TTreeReaderArray<double> primary_truthdaughter_EndMomentumY = {recobeamtevt_reader, "primary_truthdaughter_EndMomentumY"};
  TTreeReaderArray<double> primary_truthdaughter_EndMomentumZ = {recobeamtevt_reader, "primary_truthdaughter_EndMomentumZ"};
  TTreeReaderArray<double> primary_truthdaughter_EndMomentumE = {recobeamtevt_reader, "primary_truthdaughter_EndMomentumE"};
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
  TTreeReaderArray<double> primary_truthdecaydaughter_StartPositionX = {recobeamtevt_reader, "primary_truthdecaydaughter_StartPositionX"};
  TTreeReaderArray<double> primary_truthdecaydaughter_StartPositionY = {recobeamtevt_reader, "primary_truthdecaydaughter_StartPositionY"};
  TTreeReaderArray<double> primary_truthdecaydaughter_StartPositionZ = {recobeamtevt_reader, "primary_truthdecaydaughter_StartPositionZ"};
  TTreeReaderArray<double> primary_truthdecaydaughter_StartPositionT = {recobeamtevt_reader, "primary_truthdecaydaughter_StartPositionT"};
  TTreeReaderArray<double> primary_truthdecaydaughter_EndPositionX = {recobeamtevt_reader, "primary_truthdecaydaughter_EndPositionX"};
  TTreeReaderArray<double> primary_truthdecaydaughter_EndPositionY = {recobeamtevt_reader, "primary_truthdecaydaughter_EndPositionY"};
  TTreeReaderArray<double> primary_truthdecaydaughter_EndPositionZ = {recobeamtevt_reader, "primary_truthdecaydaughter_EndPositionZ"};
  TTreeReaderArray<double> primary_truthdecaydaughter_EndPositionT = {recobeamtevt_reader, "primary_truthdecaydaughter_EndPositionT"};
  TTreeReaderArray<double> primary_truthdecaydaughter_P = {recobeamtevt_reader, "primary_truthdecaydaughter_P"};
  TTreeReaderArray<double> primary_truthdecaydaughter_MomentumX = {recobeamtevt_reader, "primary_truthdecaydaughter_MomentumX"};
  TTreeReaderArray<double> primary_truthdecaydaughter_MomentumY = {recobeamtevt_reader, "primary_truthdecaydaughter_MomentumY"};
  TTreeReaderArray<double> primary_truthdecaydaughter_MomentumZ = {recobeamtevt_reader, "primary_truthdecaydaughter_MomentumZ"};
  TTreeReaderArray<double> primary_truthdecaydaughter_MomentumE = {recobeamtevt_reader, "primary_truthdecaydaughter_MomentumE"};
  TTreeReaderArray<double> primary_truthdecaydaughter_EndMomentumX = {recobeamtevt_reader, "primary_truthdecaydaughter_EndMomentumX"};
  TTreeReaderArray<double> primary_truthdecaydaughter_EndMomentumY = {recobeamtevt_reader, "primary_truthdecaydaughter_EndMomentumY"};
  TTreeReaderArray<double> primary_truthdecaydaughter_EndMomentumZ = {recobeamtevt_reader, "primary_truthdecaydaughter_EndMomentumZ"};
  TTreeReaderArray<double> primary_truthdecaydaughter_EndMomentumE = {recobeamtevt_reader, "primary_truthdecaydaughter_EndMomentumE"};
  TTreeReaderArray<double> primary_truthdecaydaughter_Pt = {recobeamtevt_reader, "primary_truthdecaydaughter_Pt"};
  TTreeReaderArray<double> primary_truthdecaydaughter_Mass = {recobeamtevt_reader, "primary_truthdecaydaughter_Mass"};
  TTreeReaderArray<double> primary_truthdecaydaughter_Theta = {recobeamtevt_reader, "primary_truthdecaydaughter_Theta"};
  TTreeReaderArray<double> primary_truthdecaydaughter_Phi = {recobeamtevt_reader, "primary_truthdecaydaughter_Phi"};
  TTreeReaderArray<double> primary_truthdecaydaughter_TotalLength = {recobeamtevt_reader, "primary_truthdecaydaughter_TotalLength"};
  TTreeReaderArray<int> primary_truthdecaydaughter_Process = {recobeamtevt_reader, "primary_truthdecaydaughter_Process"};
  TTreeReaderArray<int> primary_truthdecaydaughter_EndProcess = {recobeamtevt_reader, "primary_truthdecaydaughter_EndProcess"};

  // Reco & associated truth daughters (these are all arrays of length NMAXDAUGHTER = 15)
  TTreeReaderValue<int> NDAUGHTERS = {recodaughters_reader, "NDAUGHTERS"};
  TTreeReaderValue<double> daughterVertexX = {recodaughters_reader, "daughterVertexX"};
  TTreeReaderValue<double> daughterVertexY = {recodaughters_reader, "daughterVertexY"};
  TTreeReaderValue<double> daughterVertexZ = {recodaughters_reader, "daughterVertexZ"};
  TTreeReaderArray<int> daughterIstrack = {recodaughters_reader, "daughterIstrack"};
  TTreeReaderArray<int> daughterIsshower = {recodaughters_reader, "daughterIsshower"};
  TTreeReaderArray<int> daughterNHits = {recodaughters_reader, "daughterNHits"};
  TTreeReaderArray<double> daughterTheta = {recodaughters_reader, "daughterTheta"};
  TTreeReaderArray<double> daughterPhi = {recodaughters_reader, "daughterPhi"};
  TTreeReaderArray<double> daughterLength = {recodaughters_reader, "daughterLength"};
  TTreeReaderArray<double> daughterMomentum = {recodaughters_reader, "daughterMomentum"};
  TTreeReaderArray<double> daughterEndMomentum = {recodaughters_reader, "daughterEndMomentum"};
  TTreeReaderArray<double> daughterEndPositionX = {recodaughters_reader, "daughterEndPositionX"};
  TTreeReaderArray<double> daughterEndPositionY = {recodaughters_reader, "daughterEndPositionY"};
  TTreeReaderArray<double> daughterEndPositionZ = {recodaughters_reader, "daughterEndPositionZ"};
  TTreeReaderArray<double> daughterStartPositionX = {recodaughters_reader, "daughterStartPositionX"};
  TTreeReaderArray<double> daughterStartPositionY = {recodaughters_reader, "daughterStartPositionY"};
  TTreeReaderArray<double> daughterStartPositionZ = {recodaughters_reader, "daughterStartPositionZ"};
  TTreeReaderArray<double> daughterStartDirectionX = {recodaughters_reader, "daughterStartDirectionX"};
  TTreeReaderArray<double> daughterStartDirectionY = {recodaughters_reader, "daughterStartDirectionY"};
  TTreeReaderArray<double> daughterStartDirectionZ = {recodaughters_reader, "daughterStartDirectionZ"};
  TTreeReaderArray<double> daughterEndDirectionX = {recodaughters_reader, "daughterEndDirectionX"};
  TTreeReaderArray<double> daughterEndDirectionY = {recodaughters_reader, "daughterEndDirectionY"};
  TTreeReaderArray<double> daughterEndDirectionZ = {recodaughters_reader, "daughterEndDirectionZ"};
  TTreeReaderArray<double> daughterOpeningAngle = {recodaughters_reader, "daughterOpeningAngle"};
  TTreeReaderArray<int> daughterShowerBestPlane = {recodaughters_reader, "daughterShowerBestPlane"};
  TTreeReaderArray<double> daughterShowerEnergyP0 = {recodaughters_reader, "daughterShowerEnergyP0"};
  TTreeReaderArray<double> daughterShowerEnergyP1 = {recodaughters_reader, "daughterShowerEnergyP1"};
  TTreeReaderArray<double> daughterShowerEnergyP2 = {recodaughters_reader, "daughterShowerEnergyP2"};
  TTreeReaderArray<double> daughterShowerMIPEnergyP0 = {recodaughters_reader, "daughterShowerMIPEnergyP0"};
  TTreeReaderArray<double> daughterShowerMIPEnergyP1 = {recodaughters_reader, "daughterShowerMIPEnergyP1"};
  TTreeReaderArray<double> daughterShowerMIPEnergyP2 = {recodaughters_reader, "daughterShowerMIPEnergyP2"};
  TTreeReaderArray<double> daughterShowerdEdxP0 = {recodaughters_reader, "daughterShowerdEdxP0"};
  TTreeReaderArray<double> daughterShowerdEdxP1 = {recodaughters_reader, "daughterShowerdEdxP1"};
  TTreeReaderArray<double> daughterShowerdEdxP2 = {recodaughters_reader, "daughterShowerdEdxP2"};
  TTreeReaderArray<double> daughterMomentumByRangeProton = {recodaughters_reader, "daughterMomentumByRangeProton"};
  TTreeReaderArray<double> daughterMomentumByRangeMuon = {recodaughters_reader, "daughterMomentumByRangeMuon"};
  TTreeReaderArray<double> daughterKineticEnergyP0 = {recodaughters_reader, "daughterKineticEnergyP0"};
  TTreeReaderArray<double> daughterKineticEnergyP1 = {recodaughters_reader, "daughterKineticEnergyP1"};
  TTreeReaderArray<double> daughterKineticEnergyP2 = {recodaughters_reader, "daughterKineticEnergyP2"};
  TTreeReaderArray<double> daughterRangeP0 = {recodaughters_reader, "daughterRangeP0"};
  TTreeReaderArray<double> daughterRangeP1 = {recodaughters_reader, "daughterRangeP1"};
  TTreeReaderArray<double> daughterRangeP2 = {recodaughters_reader, "daughterRangeP2"};
  TTreeReaderArray<double> daughterTrkPitchCP0 = {recodaughters_reader, "daughterTrkPitchCP0"};
  TTreeReaderArray<double> daughterTrkPitchCP1 = {recodaughters_reader, "daughterTrkPitchCP1"};
  TTreeReaderArray<double> daughterTrkPitchCP2 = {recodaughters_reader, "daughterTrkPitchCP2"};
  TTreeReaderArray<int> daughterID = {recodaughters_reader, "daughterID"};
  TTreeReaderArray<double> daughterT0 = {recodaughters_reader, "daughterT0"};
  TTreeReaderArray<int> daughterPID_PdgP0 = {recodaughters_reader, "daughterPID_PdgP0"};
  TTreeReaderArray<int> daughterPID_PdgP1 = {recodaughters_reader, "daughterPID_PdgP1"};
  TTreeReaderArray<int> daughterPID_PdgP2 = {recodaughters_reader, "daughterPID_PdgP2"};
  TTreeReaderArray<int> daughterPID_NdfP0 = {recodaughters_reader, "daughterPID_NdfP0"};
  TTreeReaderArray<int> daughterPID_NdfP1 = {recodaughters_reader, "daughterPID_NdfP1"};
  TTreeReaderArray<int> daughterPID_NdfP2 = {recodaughters_reader, "daughterPID_NdfP2"};
  TTreeReaderArray<double> daughterPID_MinChi2P0 = {recodaughters_reader, "daughterPID_MinChi2P0"};
  TTreeReaderArray<double> daughterPID_MinChi2P1 = {recodaughters_reader, "daughterPID_MinChi2P1"};
  TTreeReaderArray<double> daughterPID_MinChi2P2 = {recodaughters_reader, "daughterPID_MinChi2P2"};
  TTreeReaderArray<double> daughterPID_DeltaChi2P0 = {recodaughters_reader, "daughterPID_DeltaChi2P0"};
  TTreeReaderArray<double> daughterPID_DeltaChi2P1 = {recodaughters_reader, "daughterPID_DeltaChi2P1"};
  TTreeReaderArray<double> daughterPID_DeltaChi2P2 = {recodaughters_reader, "daughterPID_DeltaChi2P2"};
  TTreeReaderArray<double> daughterPID_Chi2ProtonP0 = {recodaughters_reader, "daughterPID_Chi2ProtonP0"};
  TTreeReaderArray<double> daughterPID_Chi2ProtonP1 = {recodaughters_reader, "daughterPID_Chi2ProtonP1"};
  TTreeReaderArray<double> daughterPID_Chi2ProtonP2 = {recodaughters_reader, "daughterPID_Chi2ProtonP2"};
  TTreeReaderArray<double> daughterPID_Chi2KaonP0 = {recodaughters_reader, "daughterPID_Chi2KaonP0"};
  TTreeReaderArray<double> daughterPID_Chi2KaonP1 = {recodaughters_reader, "daughterPID_Chi2KaonP1"};
  TTreeReaderArray<double> daughterPID_Chi2KaonP2 = {recodaughters_reader, "daughterPID_Chi2KaonP2"};
  TTreeReaderArray<double> daughterPID_Chi2PionP0 = {recodaughters_reader, "daughterPID_Chi2PionP0"};
  TTreeReaderArray<double> daughterPID_Chi2PionP1 = {recodaughters_reader, "daughterPID_Chi2PionP1"};
  TTreeReaderArray<double> daughterPID_Chi2PionP2 = {recodaughters_reader, "daughterPID_Chi2PionP2"};
  TTreeReaderArray<double> daughterPID_Chi2MuonP0 = {recodaughters_reader, "daughterPID_Chi2MuonP0"};
  TTreeReaderArray<double> daughterPID_Chi2MuonP1 = {recodaughters_reader, "daughterPID_Chi2MuonP1"};
  TTreeReaderArray<double> daughterPID_Chi2MuonP2 = {recodaughters_reader, "daughterPID_Chi2MuonP2"};
  TTreeReaderArray<double> daughterPID_MissingEP0 = {recodaughters_reader, "daughterPID_MissingEP0"};
  TTreeReaderArray<double> daughterPID_MissingEP1 = {recodaughters_reader, "daughterPID_MissingEP1"};
  TTreeReaderArray<double> daughterPID_MissingEP2 = {recodaughters_reader, "daughterPID_MissingEP2"};
  TTreeReaderArray<double> daughterPID_MissingEavgP0 = {recodaughters_reader, "daughterPID_MissingEavgP0"};
  TTreeReaderArray<double> daughterPID_MissingEavgP1 = {recodaughters_reader, "daughterPID_MissingEavgP1"};
  TTreeReaderArray<double> daughterPID_MissingEavgP2 = {recodaughters_reader, "daughterPID_MissingEavgP2"};
  TTreeReaderArray<double> daughterPID_PIDAP0 = {recodaughters_reader, "daughterPID_PIDAP0"};
  TTreeReaderArray<double> daughterPID_PIDAP1 = {recodaughters_reader, "daughterPID_PIDAP1"};
  TTreeReaderArray<double> daughterPID_PIDAP2 = {recodaughters_reader, "daughterPID_PIDAP2"};
  TTreeReaderArray<int> daughter_truth_TrackId = {recodaughters_reader, "daughter_truth_TrackId"};
  TTreeReaderArray<int> daughter_truth_Pdg = {recodaughters_reader, "daughter_truth_Pdg"};
  TTreeReaderArray<int> daughter_truth_Mother = {recodaughters_reader, "daughter_truth_Mother"};
  TTreeReaderArray<double> daughter_truth_StartPositionX = {recodaughters_reader, "daughter_truth_StartPositionX"};
  TTreeReaderArray<double> daughter_truth_StartPositionY = {recodaughters_reader, "daughter_truth_StartPositionY"};
  TTreeReaderArray<double> daughter_truth_StartPositionZ = {recodaughters_reader, "daughter_truth_StartPositionZ"};
  TTreeReaderArray<double> daughter_truth_StartPositionT = {recodaughters_reader, "daughter_truth_StartPositionT"};
  TTreeReaderArray<double> daughter_truth_EndPositionX = {recodaughters_reader, "daughter_truth_EndPositionX"};
  TTreeReaderArray<double> daughter_truth_EndPositionY = {recodaughters_reader, "daughter_truth_EndPositionY"};
  TTreeReaderArray<double> daughter_truth_EndPositionZ = {recodaughters_reader, "daughter_truth_EndPositionZ"};
  TTreeReaderArray<double> daughter_truth_EndPositionT = {recodaughters_reader, "daughter_truth_EndPositionT"};
  TTreeReaderArray<double> daughter_truth_MomentumX = {recodaughters_reader, "daughter_truth_MomentumX"};
  TTreeReaderArray<double> daughter_truth_MomentumY = {recodaughters_reader, "daughter_truth_MomentumY"};
  TTreeReaderArray<double> daughter_truth_MomentumZ = {recodaughters_reader, "daughter_truth_MomentumZ"};
  TTreeReaderArray<double> daughter_truth_MomentumE = {recodaughters_reader, "daughter_truth_MomentumE"};
  TTreeReaderArray<double> daughter_truth_EndMomentumX = {recodaughters_reader, "daughter_truth_EndMomentumX"};
  TTreeReaderArray<double> daughter_truth_EndMomentumY = {recodaughters_reader, "daughter_truth_EndMomentumY"};
  TTreeReaderArray<double> daughter_truth_EndMomentumZ = {recodaughters_reader, "daughter_truth_EndMomentumZ"};
  TTreeReaderArray<double> daughter_truth_EndMomentumE = {recodaughters_reader, "daughter_truth_EndMomentumE"};
  TTreeReaderArray<double> daughter_truth_P = {recodaughters_reader, "daughter_truth_P"};
  TTreeReaderArray<double> daughter_truth_Pt = {recodaughters_reader, "daughter_truth_Pt"};
  TTreeReaderArray<double> daughter_truth_Mass = {recodaughters_reader, "daughter_truth_Mass"};
  TTreeReaderArray<double> daughter_truth_Theta = {recodaughters_reader, "daughter_truth_Theta"};
  TTreeReaderArray<double> daughter_truth_Phi = {recodaughters_reader, "daughter_truth_Phi"};
  TTreeReaderArray<double> daughter_truth_TotalLength = {recodaughters_reader, "daughter_truth_TotalLength"};
  TTreeReaderArray<int> daughter_truth_Process = {recodaughters_reader, "daughter_truth_Process"};


private:

  TFile * infile;

};


#endif //PION_QE_READER_HPP
