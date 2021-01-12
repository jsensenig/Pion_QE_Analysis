//
// Created by Jon Sensenig on 12/3/20.
//

#include "Pion_QE_MC_Selection.h"
#include "Types.hpp"
#include <iostream>

Pion_QE_MC_Selection::Pion_QE_MC_Selection()
{
  Config();
}

Pion_QE_MC_Selection::~Pion_QE_MC_Selection()
{
  // Write all histograms to file
  _hists.WriteHistos( _outfile );
}

//----------------------------------------------------------------
void Pion_QE_MC_Selection::ReadData( std::unique_ptr<Reader> & rdr ) {


  // Loop over leaves
  while ( rdr->Next() ) {

    // Create histograms of primary reco and associated truth and daughter truth particles
    //ProcessPrimary( rdr );

    // Create histograms of primary truth daughter particles
    //ProcessPrimaryTruthDaughter( rdr );

    // Create histograms of daughter reco and associated truth particles
    //ProcessRecoDaughter( rdr );

    // FIXME add PIDA utility function
    //if ( rdr->primaryPID_PIDA.At(c_plane_) != -999 ) {
    //  _hists.th1_hists["h_prim_pida_all"] -> Fill( rdr->primaryPID_PIDA.At(c_plane_) );
    //}

    //_hists.th2_hists["h_prim_chi2_pida_all"] -> Fill( rdr->primaryPID_MinChi2.At(0), rdr->primaryPID_PIDA.At(0), 1 );
    //_hists.th2_hists["h_prim_chi2_pida_all"] -> Fill( utils::pdg::pdg2string(rdr->primaryPID_Pdg.At(c_plane_)).c_str(), rdr->primaryPID_PIDA.At(c_plane_), 1 );
    for ( auto &p  : rdr->true_beam_processes ) std::cout << "Beam process " << p << std::endl;
    for ( auto &dE : rdr->true_beam_elastic_deltaE ) _hists.th1_hists["h_omega_550"] -> Fill( dE );
    std::cout << "X SP size " << rdr->reco_daughter_spacePts_X->at(0).size() << std::endl;

    //---- Only events with pion mother below this selection -----
    if ( *rdr->true_beam_PDG != utils::pdg::kPdgPiP ) continue;

    // Calculate the pion energy loss for all pion -> pion + X scattering where X >= 0 particles
    if ( *rdr->true_daughter_nPiPlus == 1 ) {//Selections::IsTruthPi2Pi( rdr ) ) {

    }

    //---- Only pion QE events after this selection ----
    if ( !sel.IsTruthPionQE( rdr ) ) continue;

    _pionqe += 1;

  }

  std::cout << "Pion QE 1 pion: " <<  _pionqe << " Truth 1 pion: " << _piontruth << " Reco 1 pion: " << _pionreco << std::endl;

}



// -----------------------------------------------
void Pion_QE_MC_Selection::CalculateELoss( std::unique_ptr<Reader> & rdr, int daughter ) {

  //Vector_t p(rdr->primary_truth_Momentum.At(0), rdr->primary_truth_Momentum.At(1), rdr->primary_truth_Momentum.At(2));
  //Vector_t p_prime(rdr->daughter_truth_MomentumX.At(daughter), rdr->daughter_truth_MomentumY.At(daughter), rdr->daughter_truth_MomentumZ.At(daughter));

  double omega = 0.;//rdr->primaryKineticEnergy.At(c_plane_) - rdr->daughterKineticEnergyP0.At(daughter);
  //double q = std::sqrt( (-q_vec.Mag2() * 1.e3) + omega ); // sqrt( Q2 + q0 )
  double q = 0.0; //(p - p_prime).R() * 1.e3; // Convert GeV -> Mev

  if ( q < 350. ) _hists.th1_hists["h_omega_350"] -> Fill( omega );
  else if ( q >= 350. && q < 550 ) _hists.th1_hists["h_omega_350_550"] -> Fill( omega );
  //else if ( q >= 550. ) _hists.th1_hists["h_omega_550"] -> Fill( omega );

}

// -----------------------------------------------
void Pion_QE_MC_Selection::CalculateELoss( const Position4_t & k, const Position4_t& kp ) {

  std::cout << "k: Px " << k.Px() << " Py " << k.Py() << " Pz " << k.Pz() << " E " << k.E() << std::endl;
  std::cout << "kp: Px " << kp.Px() << " Py " << kp.Py() << " Pz " << kp.Pz() << " E " << kp.E() << std::endl;
  Position4_t q_vec = k - kp;
  // Convert all GeV -> Mev
  double omega = q_vec.E() * 1.e3;
  double q = q_vec.Vect().R() * 1.e3;

  if ( q < 350. ) _hists.th1_hists["h_omega_350"] -> Fill( omega );
  else if ( q >= 350. && q < 550 ) _hists.th1_hists["h_omega_350_550"] -> Fill( omega );
  else if ( q >= 550. ) _hists.th1_hists["h_omega_550"] -> Fill( omega );

}

void Pion_QE_MC_Selection::Config() {

  json conf = utils::LoadConfig( _config_file );
  if ( conf == nullptr ) return;

  _outfile = conf.at("out_file").get<std::string>();
  std::cout << "Output file: " << _outfile << std::endl;

  // Create the histograms
  _hists.ConfigureHistos( _config_file );

}

