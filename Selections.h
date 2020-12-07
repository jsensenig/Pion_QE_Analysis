//
// Created by Jon Sensenig on 12/4/20.
//

#ifndef PION_QE_SELECTIONS_H
#define PION_QE_SELECTIONS_H

#include "Reader.h"


class Selections {

public:

  Selections();
  virtual ~Selections();

  bool PIDACut( double pida );

  bool DaughterCut( int p, int n );

  bool IsTruthPionQE( Reader & rdr );

  void Config();

  // Function to count TTree arrays
//----------------------------------------------------------------
  template<typename T>
  int Count( TTreeReaderArray<T> & arr, T a ) {

    return std::count(arr.begin(), arr.end(), a );

  }

protected:

  int upper_PIDACut;
  int lower_PIDACut;

  int proton_daughter_count;
  int neutron_daughter_count;

private:

  const std::string _config_file = "../config/Selections.json";

};


#endif //PION_QE_SELECTIONS_H
