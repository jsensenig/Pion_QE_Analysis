//
// Created by Jon Sensenig on 12/4/20.
//

#include "Selections.hpp"
#include "Utilities.hpp"

#include <algorithm>


Selections::Selections()
{ Config(); }

Selections::~Selections()
{ ; }


// Select the PIDA range cut
//----------------------------------------------------------------
bool Selections::PIDACut( double pida ) const {

  return pida > lower_PIDACut && pida < upper_PIDACut;

}

// Select the neutron, proton cut. QE scattering has n and/or p > 0
//----------------------------------------------------------------
bool Selections::DaughterCut( int p, int n ) const {

  return n > neutron_daughter_count && p > proton_daughter_count;

}

// Select truth level pion QE events i.e. pi+ --> pi+ + N (N > 0 nucleons)
//----------------------------------------------------------------
bool Selections::IsTruthPionQE( std::unique_ptr<Reader> & rdr ) const {

  return *rdr->true_beam_PDG == utils::pdg::kPdgPiP &&
         ( *rdr->true_daughter_nNeutron > 0 || *rdr->true_daughter_nProton > 0 );

};

// True if there is an 1 pion in initial and final state, otherwise false
// --------------------------------------------------
bool Selections::IsTruthPi2Pi( std::unique_ptr<Reader> & rdr ) {

  if ( *rdr -> true_beam_PDG !=  utils::pdg::kPdgPiP ) return false;

  return utils::Count<int>( rdr -> true_beam_daughter_PDG , utils::pdg::kPdgPiP ) == 1;

}

int Selections::PrimaryChi2PID( std::unique_ptr<Reader> & rdr ) {

  std::map<int, double> chi2_map;
  double min = 0.0; //rdr->primaryPID_MinChi2.At(0);

  //chi2_map[utils::pdg::kPdgKP]     = abs( rdr->primaryPID_Chi2Kaon.At(0) - min );
  //chi2_map[utils::pdg::kPdgMuon]   = abs( rdr->primaryPID_Chi2Muon.At(0) - min );
  chi2_map[utils::pdg::kPdgProton] = abs( *rdr->reco_beam_allTrack_Chi2_proton - min );
  //chi2_map[utils::pdg::kPdgPiP]    = abs( rdr->primaryPID_Chi2Pion.At(0) - min );

  auto pdg = std::min_element( chi2_map.begin(), chi2_map.end(),
                                [](const auto& l, const auto& r) { return l.second < r.second; } );

  if ( pdg != chi2_map.end() ) return (*pdg).first;
  else return 0;

}

std::vector<int> Selections::DaughterChi2PID( std::unique_ptr<Reader> & rdr ) {

  std::map<int, double> chi2_map;
  std::vector<int> daughter_pdg;

  for ( int d = 0; d < rdr->reco_daughter_allTrack_Chi2_proton.GetSize(); d++ ) { // loop over daughters

    double min = 0.0; //rdr->daughterPID_MinChi2P0.At(d);

    //chi2_map[utils::pdg::kPdgKP]     = abs( rdr->daughterPID_Chi2KaonP0.At(d) - min );
    //chi2_map[utils::pdg::kPdgMuon]   = abs( rdr->daughterPID_Chi2MuonP0.At(d) - min );
    chi2_map[utils::pdg::kPdgProton] = abs( rdr->reco_daughter_allTrack_Chi2_proton.At(d) - min );
    //chi2_map[utils::pdg::kPdgPiP]    = abs( rdr->daughterPID_Chi2PionP0.At(d) - min );

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