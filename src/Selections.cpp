//
// Created by Jon Sensenig on 12/4/20.
//

#include "Selections.h"
#include "Utilities.h"
#include <algorithm>


Selections::Selections()
{ Config(); }

Selections::~Selections()
{ ; }


// Select the PIDA range cut
//----------------------------------------------------------------
bool Selections::PIDACut(double pida) const {

  return pida > lower_PIDACut && pida < upper_PIDACut;

}

// Select the neutron, proton cut. QE scattering has n and/or p > 0
//----------------------------------------------------------------
bool Selections::DaughterCut(int p, int n) const {

  return n > neutron_daughter_count && p > proton_daughter_count;

}

bool Selections::IsTruthPionQE( std::unique_ptr<Reader> & rdr ) {

  if ( *rdr->primary_truth_Pdg !=  utils::pdg::kPdgPiP ) return false;
  if ( *rdr->primary_truth_NDAUGTHERS < 2 ) return false;

  int pion = 0, nucleon = 0;

  for ( int p = 0; p < *rdr->primary_truth_NDAUGTHERS; p++ ) {

    if ( rdr->primary_truthdaughter_Pdg.At(p) == utils::pdg::kPdgPiP ) pion += 1;
    else if ( rdr->primary_truthdaughter_Pdg.At(p) == utils::pdg::kPdgProton ||
              rdr->primary_truthdaughter_Pdg.At(p) == utils::pdg::kPdgNeutron ) nucleon += 1;

  }

  return ( pion == 1 ) && ( nucleon > 0 );

}

// True if there is an 1 pion in initial and final state, otherwise false
// --------------------------------------------------
bool Selections::IsTruthPi2Pi( std::unique_ptr<Reader> & rdr ) {

  if ( *rdr->primary_truth_Pdg !=  utils::pdg::kPdgPiP ) return false;

  return utils::Count<int>( rdr->primary_truthdaughter_Pdg , utils::pdg::kPdgPiP ) == 1;

}

int Selections::PrimaryChi2PID( std::unique_ptr<Reader> & rdr ) {

  std::map<int, double> chi2_map;
  double min = rdr->primaryPID_MinChi2.At(0);

  chi2_map[utils::pdg::kPdgKP]     = abs( rdr->primaryPID_Chi2Kaon.At(0) - min );
  chi2_map[utils::pdg::kPdgMuon]   = abs( rdr->primaryPID_Chi2Muon.At(0) - min );
  chi2_map[utils::pdg::kPdgProton] = abs( rdr->primaryPID_Chi2Proton.At(0) - min );
  chi2_map[utils::pdg::kPdgPiP]    = abs( rdr->primaryPID_Chi2Pion.At(0) - min );

  auto pdg = std::min_element( chi2_map.begin(), chi2_map.end(),
                                [](const auto& l, const auto& r) { return l.second < r.second; } );

  if ( pdg != chi2_map.end() ) return (*pdg).first;
  else return 0;

}

std::vector<int> Selections::DaughterChi2PID( std::unique_ptr<Reader> & rdr ) {

  std::map<int, double> chi2_map;
  std::vector<int> daughter_pdg;

  for ( int d = 0; d < *rdr->NDAUGHTERS; d++ ) { // loop over daughters

    double min = rdr->daughterPID_MinChi2P0.At(d);

    chi2_map[utils::pdg::kPdgKP]     = abs( rdr->daughterPID_Chi2KaonP0.At(d) - min );
    chi2_map[utils::pdg::kPdgMuon]   = abs( rdr->daughterPID_Chi2MuonP0.At(d) - min );
    chi2_map[utils::pdg::kPdgProton] = abs( rdr->daughterPID_Chi2ProtonP0.At(d) - min );
    chi2_map[utils::pdg::kPdgPiP]    = abs( rdr->daughterPID_Chi2PionP0.At(d) - min );

    auto pdg = std::min_element( chi2_map.begin(), chi2_map.end(),
                                 []( const auto& l, const auto& r ) { return l.second < r.second; } );

    if ( pdg != chi2_map.end() ) daughter_pdg.emplace_back( ( *pdg ).first );
    else daughter_pdg.emplace_back( 0 );

  }

  return daughter_pdg;

}

void Selections::Config() {

  json conf = utils::LoadConfig( _config_file );
  if ( conf == 0x0 ) return;

  upper_PIDACut = conf.at("PIDACut").at("upper").get<int>();
  lower_PIDACut = conf.at("PIDACut").at("lower").get<int>();

  neutron_daughter_count = conf.at("DaughterCut").at("neutron_count").get<int>();
  proton_daughter_count = conf.at("DaughterCut").at("proton_count").get<int>();

}