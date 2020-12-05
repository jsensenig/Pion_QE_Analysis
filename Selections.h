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

protected:

};


#endif //PION_QE_SELECTIONS_H
