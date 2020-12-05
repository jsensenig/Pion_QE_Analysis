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
