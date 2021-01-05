//
// Created by Jon Sensenig on 12/4/20.
//

#ifndef PION_QE_SELECTIONS_HPP
#define PION_QE_SELECTIONS_HPP

#include "Reader.hpp"


class Selections {

public:

  Selections();
  virtual ~Selections();

  bool PIDACut( double pida ) const;

  bool DaughterCut( int p, int n ) const;

  static bool IsTruthPionQE( std::unique_ptr<Reader> & rdr );

  static bool IsTruthPi2Pi( std::unique_ptr<Reader> & rdr );

  static int PrimaryChi2PID( std::unique_ptr<Reader> & rdr );

  static std::vector<int> DaughterChi2PID( std::unique_ptr<Reader> & rdr );

  void Config();

protected:

  int upper_PIDACut;
  int lower_PIDACut;

  int proton_daughter_count;
  int neutron_daughter_count;

private:

  const std::string _config_file = "../config/Selections.json";

};


#endif //PION_QE_SELECTIONS_HPP
