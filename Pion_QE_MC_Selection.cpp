//
// Created by Jon Sensenig on 12/3/20.
//

#include "Pion_QE_MC_Selection.h"
#include <iostream>


//----------------------------------------------------------------
void Pion_QE_MC_Selection::ReadData(TFile *file) {

  std::cout << "Loading up reader" << std::endl;
  Config();

  // ROOT event reader
  Reader rdr(file);

  // Create the histograms
  _hists.ConfigureHistos();

  // Loop over trees
  while ( rdr.Next() ) {

    _hists.th1_hists["h_prim_ke_all"] -> Fill( rdr.primaryKineticEnergy.At(0) );

    int ptruth_pdg = *rdr.primary_truth_Pdg;


     if ( ptruth_pdg == utils::pdg::kPdgMuon || ptruth_pdg == utils::pdg::kPdgPositron ||
          ptruth_pdg == utils::pdg::kPdgProton || ptruth_pdg == utils::pdg::kPdgPiP ) {
       _hists.th1_hists["h_prim_pida_all"] -> Fill( rdr.primaryPID_PIDA.At(0) ); // plane 0 = collection
     }

    _hists.th1_hists["h_beam_e"] -> Fill(*rdr.beamtrackEnergy);
    _hists.th1_hists["h_prim_len_all"] -> Fill( *rdr.primaryLength );

    // Create histograms of primary reco and associated truth and daughter truth particles
    ProcessPrimary( rdr );

    // Create histograms of primary truth daughter particles
    ProcessPrimaryTruthDaughter( rdr );

    // Create histograms of daughter reco and associated truth particles
    ProcessRecoDaughter( rdr );

    if ( ptruth_pdg != utils::pdg::kPdgPiP ) continue;  // Only events with pion mother below this

    // Calculate the energy loss for all pion -> pion scattering
    if ( Selections::IsTruthPi2Pi( rdr ) ) {
      int pi = utils::FindIndex( rdr.primary_truthdaughter_Pdg, utils::pdg::kPdgPiP );

      TLorentzVector primary_pi_mom( rdr.primary_truth_Momentum.At( 0 ), rdr.primary_truth_Momentum.At( 1 ),
                                     rdr.primary_truth_Momentum.At( 2 ), rdr.primary_truth_Momentum.At( 3 ));
      TLorentzVector truthdaughter_pi_mom( rdr.primary_truthdaughter_MomentumX.At( pi ), rdr.primary_truthdaughter_MomentumY.At( pi ),
                                           rdr.primary_truthdaughter_MomentumZ.At( pi ), rdr.primary_truthdaughter_MomentumE.At( pi ));
      CalculateELoss( primary_pi_mom, truthdaughter_pi_mom );
    }

    // Only pion QE events after this selection
    if ( !Selections::IsTruthPionQE( rdr ) ) continue;
    _pionqe += 1;

    _hists.th1_hists["h_prim_ke_pionqe"] -> Fill( rdr.primaryKineticEnergy.At(0) );
    _hists.th1_hists["h_nproton"] -> Fill( utils::Count<int>( rdr.primary_truthdaughter_Pdg, utils::pdg::kPdgProton ) );
    _hists.th1_hists["h_nneutron"] -> Fill( utils::Count<int>( rdr.primary_truthdaughter_Pdg, utils::pdg::kPdgNeutron ) );
    _hists.th1_hists["h_len_pionqe"] -> Fill( *rdr.primaryLength );

  }

  _hists.WriteHistos( _outfile );

  std::cout << "Pion QE 1 pion: " <<  _pionqe << " Truth 1 pion: " << _piontruth << " Reco 1 pion: " << _pionreco << std::endl;

}

// ---------------------------------------------------
void Pion_QE_MC_Selection::ProcessPrimary( Reader &rdr ) {

  // Get primary particle chi2 PID
  int chi2_pdg = Selections::PrimaryChi2PID( rdr );
  // Count nucleon truth daughters
  int np = utils::Count<int>(rdr.primary_truthdaughter_Pdg, utils::pdg::kPdgProton );
  int nn = utils::Count<int>(rdr.primary_truthdaughter_Pdg, utils::pdg::kPdgNeutron );

  if ( *rdr.primary_truth_Pdg == utils::pdg::kPdgPiP ) { // primary pions
    _hists.th1_hists["h_prim_pida_pi"] -> Fill( rdr.primaryPID_PIDA.At(0) ); // plane 0 = collection
    _hists.th1_hists["h_len_pion"] -> Fill ( *rdr.primaryLength );
    np = utils::Count<int>(rdr.primary_truthdaughter_Pdg, utils::pdg::kPdgProton );
    nn = utils::Count<int>(rdr.primary_truthdaughter_Pdg, utils::pdg::kPdgNeutron );
    _hists.th2_hists["h_neutron_proton_pion"] -> Fill( np, nn );
    _hists.th1_hists["h_prim_ke_pion"] -> Fill( rdr.primaryKineticEnergy.At(0) );
    _hists.th2_hists["h_prim_truth_chi2"] -> Fill( utils::pdg::pdg2string(chi2_pdg).c_str(), utils::pdg::pdg2string(211).c_str(),1);
  }
  else if ( *rdr.primary_truth_Pdg == utils::pdg::kPdgProton ) { // primary protons
    _hists.th1_hists["h_len_proton"] -> Fill ( *rdr.primaryLength );
    _hists.th1_hists["h_prim_pida_proton"] -> Fill( rdr.primaryPID_PIDA.At(0) ); // plane 0 = collection
    _hists.th2_hists["h_prim_truth_chi2"] -> Fill( utils::pdg::pdg2string(chi2_pdg).c_str(), utils::pdg::pdg2string(2212).c_str(),1);
  }
  else if ( *rdr.primary_truth_Pdg == utils::pdg::kPdgNeutron ){ // primary neutrons
    _hists.th1_hists["h_prim_pida_neutron"] -> Fill( rdr.primaryPID_PIDA.At(0) ); // plane 0 = collection
  }
  else if ( *rdr.primary_truth_Pdg == utils::pdg::kPdgPositron ) { // primary positron
    _hists.th1_hists["h_len_positron"] -> Fill ( *rdr.primaryLength );
    _hists.th1_hists["h_prim_pida_positron"] -> Fill( rdr.primaryPID_PIDA.At(0) ); // plane 0 = collection
  }
  else if ( *rdr.primary_truth_Pdg == utils::pdg::kPdgMuon ) {
    _hists.th1_hists["h_prim_pida_muon"] -> Fill( rdr.primaryPID_PIDA.At(0) ); // plane 0 = collection
    _hists.th2_hists["h_prim_truth_chi2"] -> Fill( utils::pdg::pdg2string(chi2_pdg).c_str(), utils::pdg::pdg2string(13).c_str(),1);

  }
  else if ( *rdr.primary_truth_Pdg == utils::pdg::kPdgKP ) {
    _hists.th2_hists["h_prim_truth_chi2"] -> Fill( utils::pdg::pdg2string(chi2_pdg).c_str(), utils::pdg::pdg2string(321).c_str(),1);
  }
  else {

  }

  _hists.th2_hists["h_neutron_proton_all"] -> Fill( np, nn );

}

// ------------------------------------------
void Pion_QE_MC_Selection::ProcessPrimaryTruthDaughter(Reader &rdr) {

  // Get the primary particle end direction
  TVector3 prim_enddir( rdr.primaryEndDirection.At(0),rdr.primaryEndDirection.At(1), rdr.primaryEndDirection.At(2) );

  // Get the daughter chi2 pid
  std::vector<int> daughter_pdg = Selections::DaughterChi2PID( rdr );

  // Loop over daughter reco and associated truth particles
  int np = 0, nn = 0, pi = 0;
  for ( int i = 0; i < ( *rdr.primary_truth_NDAUGTHERS ); i++ ) {

    TVector3 daughter_startdir( rdr.daughterStartDirectionX.At(i), rdr.daughterStartDirectionY.At(i), rdr.daughterStartDirectionZ.At(i) );

    _hists.th1_hists["h_daughter_pida_all_p0"] -> Fill( rdr.daughterPID_PIDAP0.At(i) ); // plane 0 = collection
    _hists.th1_hists["h_daughter_pida_all_p1"] -> Fill( rdr.daughterPID_PIDAP1.At(i) ); // plane 1 = collection
    _hists.th1_hists["h_daughter_pida_all_p2"] -> Fill( rdr.daughterPID_PIDAP2.At(i) ); // plane 2 = collection

    if ( rdr.primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgPiP ) { // daughter pions
      _hists.th1_hists["h_daughter_pida_pi"] -> Fill( rdr.daughterPID_PIDAP0.At(i) ); // plane 0 = collection
      _hists.th1_hists["h_truth_fspion_theta"] -> Fill( utils::ThetaAngle( prim_enddir, daughter_startdir ) );
      _hists.th1_hists["h_truth_fspion_phi"] -> Fill( utils::PhiAngle( prim_enddir, daughter_startdir ) );
      _hists.th1_hists["h_len_daughter_pion"] -> Fill ( rdr.daughter_truth_TotalLength.At(i) );
      if (!daughter_pdg.empty()) _hists.th2_hists["h_daughter_truth_chi2"] -> Fill( utils::pdg::pdg2string(daughter_pdg.at(0)).c_str(), utils::pdg::pdg2string(211).c_str(),1);
      pi += 1;
    }
    else if ( rdr.primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgProton ) { // daughter proton
      np += 1;
      _hists.th1_hists["h_daughter_pida_proton"] -> Fill( rdr.daughterPID_PIDAP0.At(i) ); // plane 0 = collection
      _hists.th1_hists["h_truth_fsproton_theta"] -> Fill( utils::ThetaAngle( prim_enddir, daughter_startdir ) );
      _hists.th1_hists["h_truth_fsproton_phi"] -> Fill( utils::PhiAngle( prim_enddir, daughter_startdir ) );
      _hists.th1_hists["h_len_daughter_proton"] -> Fill ( rdr.daughter_truth_TotalLength.At(i) );
      if (!daughter_pdg.empty()) _hists.th2_hists["h_daughter_truth_chi2"] -> Fill( utils::pdg::pdg2string(daughter_pdg.at(0)).c_str(), utils::pdg::pdg2string(2212).c_str(),1);
    }
    else if ( rdr.primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgNeutron ) { // daughter neutron
      nn += 1;
      _hists.th1_hists["h_daughter_pida_neutron"] -> Fill( rdr.daughterPID_PIDAP0.At(i) ); // plane 0 = collection
      _hists.th1_hists["h_truth_fsneutron_theta"] -> Fill( utils::ThetaAngle( prim_enddir, daughter_startdir ) );
      _hists.th1_hists["h_truth_fsneutron_phi"] -> Fill( utils::PhiAngle( prim_enddir, daughter_startdir ) );
      _hists.th1_hists["h_len_daughter_neutron"] -> Fill ( rdr.daughter_truth_TotalLength.At(i) );
    }
    else if ( rdr.primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgPositron ) { // daughter positron
      _hists.th1_hists["h_daughter_pida_positron"] -> Fill( rdr.daughterPID_PIDAP0.At(i) ); // plane 0 = collection
    }
    else if ( rdr.primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgMuon ) { // daughter muon
      _hists.th1_hists["h_daughter_pida_muon"] -> Fill( rdr.daughterPID_PIDAP0.At(i) ); // plane 0 = collection
      _hists.th1_hists["h_len_daughter_muon"] -> Fill ( rdr.daughter_truth_TotalLength.At(i) );
      if (!daughter_pdg.empty()) _hists.th2_hists["h_daughter_truth_chi2"] -> Fill( utils::pdg::pdg2string(daughter_pdg.at(0)).c_str(), utils::pdg::pdg2string(13).c_str(),1);
    }
    else if ( rdr.primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgKP ) {
      _hists.th1_hists["h_len_daughter_kaon"] -> Fill ( rdr.daughter_truth_TotalLength.At(i) );
      if (!daughter_pdg.empty()) _hists.th2_hists["h_daughter_truth_chi2"] -> Fill( utils::pdg::pdg2string(daughter_pdg.at(0)).c_str(), utils::pdg::pdg2string(321).c_str(),1);
    }

  }

  if ( pi == 1 ) { // check if there is 1 daughter pion
    int p = utils::Count<int>( rdr.primary_truthdaughter_Pdg, utils::pdg::kPdgProton );
    int n = utils::Count<int>( rdr.primary_truthdaughter_Pdg, utils::pdg::kPdgNeutron );
    _hists.th2_hists["h_neutron_proton_pionqe"] -> Fill( p, n );
    _piontruth += 1;
  }

}

// ----------------------------------------------
void Pion_QE_MC_Selection::ProcessRecoDaughter(Reader &rdr) {

  int reco_pi_cnt = utils::Count<int>( rdr.daughter_truth_Pdg, utils::pdg::kPdgPiP );

  if ( reco_pi_cnt == 1 ) { // check if there is 1 daughter pion
    int p = utils::Count<int>( rdr.primary_truthdaughter_Pdg, utils::pdg::kPdgProton );
    int n = utils::Count<int>( rdr.primary_truthdaughter_Pdg, utils::pdg::kPdgNeutron );
    _hists.th2_hists["h_neutron_proton_reco_nucleon"] -> Fill( p, n );
    _pionreco += 1;
  }

}

// -----------------------------------------------
void Pion_QE_MC_Selection::CalculateELoss( const TLorentzVector& k, const TLorentzVector& kp ) {

  TLorentzVector q_vec = k - kp;
  // Convert all GeV -> Mev
  double omega = q_vec.E() * 1.e3;
  double q = std::sqrt( (-q_vec.Mag2() * 1.e3) + omega ); // sqrt( Q2 + q0 )

  if ( q < 350. ) _hists.th1_hists["h_omega_350"] -> Fill( omega );
  else if ( q >= 350. && q < 550 ) _hists.th1_hists["h_omega_350_550"] -> Fill( omega );
  else if ( q >= 550. ) _hists.th1_hists["h_omega_550"] -> Fill( omega );

}

void Pion_QE_MC_Selection::Config() {

  json conf = utils::LoadConfig( _config_file );
  if ( conf == 0 ) return;

  _outfile = conf.at("out_file").get<std::string>();
  std::cout << "Output file: " << _outfile << std::endl;

}

