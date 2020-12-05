//
// Created by Jon Sensenig on 12/4/20.
//

#include "Selections.h"
#include "Utilities.h"


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

  return n > 0 && p > 0;

}

bool Selections::IsTruthPionQE( Reader & rdr ) {

  if ( **rdr.primary_truth_Pdg !=  utils::pdg::kPdgPiP ) return false;
  if ( **rdr.primary_truth_ndaughters < 2 ) return false;

  int pion = 0; int nucleon = 0;

  for ( int p = 0; p < **rdr.primary_truth_ndaughters; p++ ) {

    if ( rdr.primary_truthdaughter_Pdg->At(p) == utils::pdg::kPdgPiP ) pion += 1;
    if ( rdr.primary_truthdaughter_Pdg->At(p) == utils::pdg::kPdgProton ||
         rdr.primary_truthdaughter_Pdg->At(p) == utils::pdg::kPdgNeutron ) nucleon += 1;

  }

  return ( pion == 1 ) && ( nucleon > 0 );

}
