//
// Created by Jon Sensenig on 12/4/20.
//

#include "Selections.h"
#include "Utilities.h"


Selections::Selections()
{ Config(); }

Selections::~Selections()
{ ; }


// Select the PIDA range cut
//----------------------------------------------------------------
bool Selections::PIDACut(double pida) {

  return pida > lower_PIDACut && pida < upper_PIDACut;

}

// Select the neutron, proton cut. QE scattering has n and/or p > 0
//----------------------------------------------------------------
bool Selections::DaughterCut(int p, int n) {

  return n > neutron_daughter_count && p > proton_daughter_count;

}

//// Funtion to count TTree arrays
////----------------------------------------------------------------
//template<typename T>
//int Selections::Count( TTreeReaderArray<T> & arr, T a ) {
//
//  return std::count(arr.begin(), arr.end(), a );
//
//}

bool Selections::IsTruthPionQE( Reader & rdr ) {

  if ( *rdr.primary_truth_Pdg !=  utils::pdg::kPdgPiP ) return false;
  if ( *rdr.primary_truth_NDAUGTHERS < 2 ) return false;

  int pion = 0; int nucleon = 0;

  for ( int p = 0; p < *rdr.primary_truth_NDAUGTHERS; p++ ) {

    if ( rdr.primary_truthdaughter_Pdg.At(p) == utils::pdg::kPdgPiP ) pion += 1;
    else if ( rdr.primary_truthdaughter_Pdg.At(p) == utils::pdg::kPdgProton ||
              rdr.primary_truthdaughter_Pdg.At(p) == utils::pdg::kPdgNeutron ) nucleon += 1;

  }

  return ( pion == 1 ) && ( nucleon > 0 );

}

void Selections::Config() {

  json conf = utils::LoadConfig( _config_file );
  if ( conf == 0 ) return;

  upper_PIDACut = conf.at("PIDACut").at("upper").get<int>();
  lower_PIDACut = conf.at("PIDACut").at("lower").get<int>();

  neutron_daughter_count = conf.at("DaughterCut").at("neutron_count").get<int>();
  proton_daughter_count = conf.at("DaughterCut").at("proton_count").get<int>();

}