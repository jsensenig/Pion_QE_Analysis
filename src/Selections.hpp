//
// Created by Jon Sensenig on 12/4/20.
//

#ifndef PION_QE_SELECTIONS_HPP
#define PION_QE_SELECTIONS_HPP

#include "Reader.hpp"
#include "Utilities.hpp"


class Selections {

public:

  Selections();
  virtual ~Selections();

  bool DaughterCut( int p, int n ) const ;

  bool PIDACut( double pida ) const ;

  bool EMScoreCut( double score ) const;

  bool TrackScoreCut( double score ) const;

  bool PiTofCut( double tof ) const;

  static bool IsTruthPi2Pi( std::unique_ptr<Reader> & rdr );

  static int PrimaryChi2PID( std::unique_ptr<Reader> & rdr );

  static std::vector<int> DaughterChi2PID( std::unique_ptr<Reader> & rdr );

  // --------------------------------------
  inline bool IsTruthPionQE( std::unique_ptr<Reader> & rdr ) const {
    return ( *rdr->true_beam_PDG == utils::pdg::kPdgPiP ) &&
           ( *rdr->true_daughter_nPiPlus == 1 ) &&
           ( *rdr->true_daughter_nNeutron > 0 || *rdr->true_daughter_nProton > 0 );
  }


  void Config();

protected:

  int upper_PIDACut;
  int lower_PIDACut;

  int proton_daughter_count;
  int neutron_daughter_count;

  double upper_em_score;
  double lower_em_score;

  double upper_track_score;
  double lower_track_score;

  double upper_pi_tof_cut;
  double lower_pi_tof_cut;

private:

  const std::string _config_file = "../config/Selections.json";

};


#endif //PION_QE_SELECTIONS_HPP
