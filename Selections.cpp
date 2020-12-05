//
// Created by Jon Sensenig on 12/4/20.
//

#include "Selections.h"


Selections::Selections()
{ ; }

Selections::~Selections()
{ ; }


// Select the PIDA range cut
//----------------------------------------------------------------
bool Selections::PIDACut(double pida) {

  if ( pida > 0 && pida < 12 ) return true;

  return false;

}

// Select the neutron, proton cut. QE scattering has n and/or p > 0
//----------------------------------------------------------------
bool Selections::DaughterCut(int p, int n) {

  if ( n > 0 && p > 0 ) return true;
  return false;
}

bool Selections::IsTruthPionQE( Reader & rdr ) {

  if ( **rdr.primary_truth_Pdg != 211 ) return false;
  if ( **rdr.primary_truth_ndaughters < 2 ) return false;

  int pion = 0; int nucleon = 0;

  for ( int p = 0; p < **rdr.primary_truth_ndaughters; p++ ) {

    if ( rdr.primary_truthdaughter_Pdg->At(p) == 211 ) pion += 1;
    if ( rdr.primary_truthdaughter_Pdg->At(p) == 2212 ||
         rdr.primary_truthdaughter_Pdg->At(p) == 2112 ) nucleon += 1;

  }

  return ( pion == 1 ) && ( nucleon > 0 );

}
