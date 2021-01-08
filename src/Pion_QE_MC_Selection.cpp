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
    ProcessPrimary( rdr );

    // Create histograms of primary truth daughter particles
    ProcessPrimaryTruthDaughter( rdr );

    // Create histograms of daughter reco and associated truth particles
    ProcessRecoDaughter( rdr );

    if ( rdr->primaryPID_PIDA.At(0) != -999 ) {
      _hists.th1_hists["h_prim_pida_all"] -> Fill( rdr->primaryPID_PIDA.At(0) ); // plane 0 = collection
    }

    //_hists.th2_hists["h_prim_chi2_pida_all"] -> Fill( rdr->primaryPID_MinChi2.At(0), rdr->primaryPID_PIDA.At(0), 1 );
    _hists.th2_hists["h_prim_chi2_pida_all"] -> Fill( utils::pdg::pdg2string(rdr->primaryPID_Pdg.At(0)).c_str(), rdr->primaryPID_PIDA.At(0), 1 );

    _hists.th1_hists["h_prim_ke_all"] -> Fill( rdr->primaryKineticEnergy.At(0) );
    _hists.th1_hists["h_beam_e"] -> Fill(*rdr->beamtrackEnergy);
    _hists.th1_hists["h_prim_len_all"] -> Fill( *rdr->primaryLength );

    //---- Only events with pion mother below this selection -----
    if ( *rdr->primary_truth_Pdg != utils::pdg::kPdgPiP ) continue;

    // Calculate the pion energy loss for all pion -> pion + X scattering where X >= 0 particles
    if ( Selections::IsTruthPi2Pi( rdr ) ) {
      int pi = utils::FindIndex<int>( rdr->primary_truthdaughter_Pdg, utils::pdg::kPdgPiP );
      std::cout << "Pion idx " << pi << std::endl;
      //CalculateELoss( rdr, pi );
      Position4_t primary_pi_mom( rdr->primary_truth_Momentum.At( 0 ), rdr->primary_truth_Momentum.At( 1 ),
                                     rdr->primary_truth_Momentum.At( 2 ), rdr->primary_truth_Momentum.At( 3 ));
      Position4_t truthdaughter_pi_mom( rdr->primary_truthdaughter_MomentumX.At( pi ), rdr->primary_truthdaughter_MomentumY.At( pi ),
                                           rdr->primary_truthdaughter_MomentumZ.At( pi ), rdr->primary_truthdaughter_MomentumE.At( pi ));
      CalculateELoss( primary_pi_mom, truthdaughter_pi_mom );
    }

    //---- Only pion QE events after this selection ----
    if ( !Selections::IsTruthPionQE( rdr ) ) continue;


    _hists.th1_hists["h_prim_ke_pionqe"] -> Fill( rdr->primaryKineticEnergy.At(0) );
    _hists.th1_hists["h_nproton"] -> Fill( utils::Count<int>( rdr->primary_truthdaughter_Pdg, utils::pdg::kPdgProton ) );
    _hists.th1_hists["h_nneutron"] -> Fill( utils::Count<int>( rdr->primary_truthdaughter_Pdg, utils::pdg::kPdgNeutron ) );
    _hists.th1_hists["h_len_pionqe"] -> Fill( *rdr->primaryLength );
    _pionqe += 1;

  }

  std::cout << "Pion QE 1 pion: " <<  _pionqe << " Truth 1 pion: " << _piontruth << " Reco 1 pion: " << _pionreco << std::endl;

}

// ---------------------------------------------------
void Pion_QE_MC_Selection::ProcessPrimary( std::unique_ptr<Reader> & rdr ) {

  // Get primary particle chi2 PID
  int chi2_pdg = rdr->primaryPID_Pdg.At(0); // Min chi2 pdg from collection plane

  // Count nucleon truth daughters
  int np = utils::Count<int>(rdr->primary_truthdaughter_Pdg, utils::pdg::kPdgProton );
  int nn = utils::Count<int>(rdr->primary_truthdaughter_Pdg, utils::pdg::kPdgNeutron );

  if ( *rdr->primary_truth_Pdg == utils::pdg::kPdgPiP ) { // primary pions
    _hists.th1_hists["h_prim_pida_pi"] -> Fill( rdr->primaryPID_PIDA.At(0) ); // plane 0 = collection
    _hists.th1_hists["h_len_pion"] -> Fill ( *rdr->primaryLength );
    np = utils::Count<int>(rdr->primary_truthdaughter_Pdg, utils::pdg::kPdgProton );
    nn = utils::Count<int>(rdr->primary_truthdaughter_Pdg, utils::pdg::kPdgNeutron );
    _hists.th2_hists["h_neutron_proton_pion"] -> Fill( np, nn );
    _hists.th1_hists["h_prim_ke_pion"] -> Fill( rdr->primaryKineticEnergy.At(0) );
    _hists.th1_hists["h_prim_ke_pion_truth"] -> Fill ( utils::CalculateKE( rdr->primary_truth_Momentum.At(0), *rdr->primary_truth_Mass )*1.e3 );
    _hists.th2_hists["h_prim_truth_chi2"] -> Fill( utils::pdg::pdg2string(chi2_pdg).c_str(), utils::pdg::pdg2string(211).c_str(),1);
  }
  else if ( *rdr->primary_truth_Pdg == utils::pdg::kPdgProton ) { // primary protons
    _hists.th1_hists["h_len_proton"] -> Fill ( *rdr->primaryLength );
    _hists.th1_hists["h_prim_pida_proton"] -> Fill( rdr->primaryPID_PIDA.At(0) ); // plane 0 = collection
    _hists.th2_hists["h_prim_truth_chi2"] -> Fill( utils::pdg::pdg2string(chi2_pdg).c_str(), utils::pdg::pdg2string(2212).c_str(),1);
  }
  else if ( *rdr->primary_truth_Pdg == utils::pdg::kPdgNeutron ){ // primary neutrons
    _hists.th1_hists["h_prim_pida_neutron"] -> Fill( rdr->primaryPID_PIDA.At(0) ); // plane 0 = collection
  }
  else if ( *rdr->primary_truth_Pdg == utils::pdg::kPdgPositron ) { // primary positron
    _hists.th1_hists["h_len_positron"] -> Fill ( *rdr->primaryLength );
    _hists.th1_hists["h_prim_pida_positron"] -> Fill( rdr->primaryPID_PIDA.At(0) ); // plane 0 = collection
  }
  else if ( *rdr->primary_truth_Pdg == utils::pdg::kPdgMuon ) {
    _hists.th1_hists["h_prim_pida_muon"] -> Fill( rdr->primaryPID_PIDA.At(0) ); // plane 0 = collection
    _hists.th2_hists["h_prim_truth_chi2"] -> Fill( utils::pdg::pdg2string(chi2_pdg).c_str(), utils::pdg::pdg2string(13).c_str(),1);

  }
  else if ( *rdr->primary_truth_Pdg == utils::pdg::kPdgKP ) {
    _hists.th2_hists["h_prim_truth_chi2"] -> Fill( utils::pdg::pdg2string(chi2_pdg).c_str(), utils::pdg::pdg2string(321).c_str(),1);
  }
  else {

  }

  _hists.th2_hists["h_neutron_proton_all"] -> Fill( np, nn );

}

// ------------------------------------------
void Pion_QE_MC_Selection::ProcessPrimaryTruthDaughter( std::unique_ptr<Reader> & rdr ) {

  // Get the primary particle end direction
  Vector_t prim_enddir( rdr->primaryEndDirection.At(0),rdr->primaryEndDirection.At(1), rdr->primaryEndDirection.At(2) );
  Vector_t prim_enddir_test( rdr->primaryEndDirection.At(0),rdr->primaryEndDirection.At(1), rdr->primaryEndDirection.At(2) );

  // Get the daughter chi2 pid
  std::vector<int> daughter_pdg = Selections::DaughterChi2PID( rdr );
  //rdr->daughterPID_PdgP0;

  // Loop over daughter reco and associated truth particles
  int np = 0, nn = 0, pi = 0;
  for ( int i = 0; i < ( *rdr->primary_truth_NDAUGTHERS ); i++ ) {

    Vector_t daughter_startdir( rdr->daughterStartDirectionX.At(i), rdr->daughterStartDirectionY.At(i), rdr->daughterStartDirectionZ.At(i) );

    _hists.th1_hists["h_daughter_pida_all_p0"] -> Fill( rdr->daughterPID_PIDAP0.At(i) ); // plane 0 = collection
    _hists.th1_hists["h_daughter_pida_all_p1"] -> Fill( rdr->daughterPID_PIDAP1.At(i) ); // plane 1 = collection
    _hists.th1_hists["h_daughter_pida_all_p2"] -> Fill( rdr->daughterPID_PIDAP2.At(i) ); // plane 2 = collection

    if ( rdr->primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgPiP ) { // daughter pions
      _hists.th1_hists["h_daughter_pida_pi"] -> Fill( rdr->daughterPID_PIDAP0.At(i) ); // plane 0 = collection
      _hists.th1_hists["h_truth_fspion_theta"] -> Fill( utils::ThetaAngle( prim_enddir, daughter_startdir ) );
      _hists.th1_hists["h_truth_fspion_phi"] -> Fill( utils::PhiAngle( prim_enddir, daughter_startdir ) );
      _hists.th1_hists["h_len_daughter_pion"] -> Fill ( rdr->daughter_truth_TotalLength.At(i) );
      _hists.th2_hists["h_daughter_truth_chi2"] -> Fill( utils::pdg::pdg2string(rdr->daughterPID_PdgP0.At(i)).c_str(), utils::pdg::pdg2string(211).c_str(),1) ;
      pi += 1;
    }
    else if ( rdr->primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgProton ) { // daughter proton
      np += 1;
      _hists.th1_hists["h_daughter_pida_proton"] -> Fill( rdr->daughterPID_PIDAP0.At(i) ); // plane 0 = collection
      _hists.th1_hists["h_truth_fsproton_theta"] -> Fill( utils::ThetaAngle( prim_enddir, daughter_startdir ) );
      _hists.th1_hists["h_truth_fsproton_phi"] -> Fill( utils::PhiAngle( prim_enddir, daughter_startdir ) );
      _hists.th1_hists["h_len_daughter_proton"] -> Fill ( rdr->daughter_truth_TotalLength.At(i) );
      _hists.th2_hists["h_daughter_truth_chi2"] -> Fill( utils::pdg::pdg2string(rdr->daughterPID_PdgP0.At(i)).c_str(), utils::pdg::pdg2string(2212).c_str(),1) ;
    }
    else if ( rdr->primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgNeutron ) { // daughter neutron
      nn += 1;
      _hists.th1_hists["h_daughter_pida_neutron"] -> Fill( rdr->daughterPID_PIDAP0.At(i) ); // plane 0 = collection
      _hists.th1_hists["h_truth_fsneutron_theta"] -> Fill( utils::ThetaAngle( prim_enddir, daughter_startdir ) );
      _hists.th1_hists["h_truth_fsneutron_phi"] -> Fill( utils::PhiAngle( prim_enddir, daughter_startdir ) );
      _hists.th1_hists["h_len_daughter_neutron"] -> Fill ( rdr->daughter_truth_TotalLength.At(i) );
    }
    else if ( rdr->primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgPositron ) { // daughter positron
      _hists.th1_hists["h_daughter_pida_positron"] -> Fill( rdr->daughterPID_PIDAP0.At(i) ); // plane 0 = collection
    }
    else if ( rdr->primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgMuon ) { // daughter muon
      _hists.th1_hists["h_daughter_pida_muon"] -> Fill( rdr->daughterPID_PIDAP0.At(i) ); // plane 0 = collection
      _hists.th1_hists["h_len_daughter_muon"] -> Fill ( rdr->daughter_truth_TotalLength.At(i) );
      _hists.th2_hists["h_daughter_truth_chi2"] -> Fill( utils::pdg::pdg2string(rdr->daughterPID_PdgP0.At(i)).c_str(), utils::pdg::pdg2string(13).c_str(),1) ;
    }
    else if ( rdr->primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgKP ) {
      _hists.th1_hists["h_len_daughter_kaon"] -> Fill ( rdr->daughter_truth_TotalLength.At(i) );
      _hists.th2_hists["h_daughter_truth_chi2"] -> Fill( utils::pdg::pdg2string(rdr->daughterPID_PdgP0.At(i)).c_str(), utils::pdg::pdg2string(321).c_str(),1) ;
    }

  }

  if ( pi == 1 ) { // check if there is 1 daughter pion
    int p = utils::Count<int>( rdr->primary_truthdaughter_Pdg, utils::pdg::kPdgProton );
    int n = utils::Count<int>( rdr->primary_truthdaughter_Pdg, utils::pdg::kPdgNeutron );
    _hists.th2_hists["h_neutron_proton_pi_pi"] -> Fill( p, n );
    _piontruth += 1;
    std::cout << "Primary Evt = " << *rdr->event << std::endl;
  }

}

// ----------------------------------------------
void Pion_QE_MC_Selection::ProcessRecoDaughter( std::unique_ptr<Reader> & rdr ) {

  int reco_pi_cnt = utils::Count<int>( rdr->primary_truthdaughter_Pdg, utils::pdg::kPdgPiP );
  int reco_pi_idx = utils::FindIndex<int>( rdr->primary_truthdaughter_Pdg, utils::pdg::kPdgPiP );
  int tpion = utils::Count<int>( rdr->primary_truthdaughter_Pdg, utils::pdg::kPdgPiP );

  if ( reco_pi_cnt == 1 ) { // check if there is 1 daughter pion
    std::cout << "Evt = " << *rdr->event << " Reco truth = " << reco_pi_cnt << " Primary truth = " << tpion << std::endl;
    int p = utils::Count<int>( rdr->primary_truthdaughter_Pdg, utils::pdg::kPdgProton );
    int n = utils::Count<int>( rdr->primary_truthdaughter_Pdg, utils::pdg::kPdgNeutron );
    _hists.th2_hists["h_neutron_proton_reco_nucleon"] -> Fill( p, n );

    Vector_t mom(rdr->primary_truthdaughter_MomentumX.At(reco_pi_idx), rdr->primary_truthdaughter_MomentumY.At(reco_pi_idx), rdr->primary_truthdaughter_MomentumZ.At(reco_pi_idx));
    _hists.th2_hists["h_pdaughter_mom_multiplicity"] -> Fill( (p+n), utils::CalculateKE(mom, rdr->primary_truthdaughter_Mass.At(reco_pi_idx)) );
    _pionreco += 1;
  }

}

// -----------------------------------------------
void Pion_QE_MC_Selection::CalculateELoss( std::unique_ptr<Reader> & rdr, int daughter ) {

  Vector_t p(rdr->primary_truth_Momentum.At(0), rdr->primary_truth_Momentum.At(1), rdr->primary_truth_Momentum.At(2));
  Vector_t p_prime(rdr->daughter_truth_MomentumX.At(daughter), rdr->daughter_truth_MomentumY.At(daughter), rdr->daughter_truth_MomentumZ.At(daughter));

  double omega = rdr->primaryKineticEnergy.At(0) - rdr->daughterKineticEnergyP0.At(daughter);
  //double q = std::sqrt( (-q_vec.Mag2() * 1.e3) + omega ); // sqrt( Q2 + q0 )
  double q = (p - p_prime).R() * 1.e3; // Convert GeV -> Mev

  if ( q < 350. ) _hists.th1_hists["h_omega_350"] -> Fill( omega );
  else if ( q >= 350. && q < 550 ) _hists.th1_hists["h_omega_350_550"] -> Fill( omega );
  else if ( q >= 550. ) _hists.th1_hists["h_omega_550"] -> Fill( omega );

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

