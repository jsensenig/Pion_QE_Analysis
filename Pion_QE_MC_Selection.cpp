//
// Created by Jon Sensenig on 12/3/20.
//

#include "Pion_QE_MC_Selection.h"
// std library includes
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
    _hists.th1_hists["h_total_len"] -> Fill( *rdr.primary_truth_TotalLength );

    int np, nn;
    if ( *rdr.primary_truth_Pdg == utils::pdg::kPdgPiP ) { // primary pions
      _hists.th1_hists["h_prim_pida_pi"] -> Fill( rdr.primaryPID_PIDA.At(0) ); // plane 0 = collection
      _hists.th1_hists["h_total_len_pion"] -> Fill ( *rdr.primary_truth_TotalLength );
      np = _sel.Count<int>(rdr.primary_truthdaughter_Pdg, utils::pdg::kPdgProton );
      nn = _sel.Count<int>(rdr.primary_truthdaughter_Pdg, utils::pdg::kPdgNeutron );
      _hists.th2_hists["h_neutron_proton_pion"] -> Fill( np, nn );
      _hists.th1_hists["h_prim_ke_pion"] -> Fill( rdr.primaryKineticEnergy.At(0) );
    }
    else if ( *rdr.primary_truth_Pdg == utils::pdg::kPdgProton ) { // primary protons
      _hists.th1_hists["h_total_len_proton"] -> Fill ( *rdr.primary_truth_TotalLength );
      _hists.th1_hists["h_prim_pida_proton"] -> Fill( rdr.primaryPID_PIDA.At(0) ); // plane 0 = collection
    }
    else if ( *rdr.primary_truth_Pdg == utils::pdg::kPdgNeutron ){ // primary neutrons
      _hists.th1_hists["h_prim_pida_neutron"] -> Fill( rdr.primaryPID_PIDA.At(0) ); // plane 0 = collection
    }
    else if ( *rdr.primary_truth_Pdg == utils::pdg::kPdgPositron ) { // primary positron
      _hists.th1_hists["h_total_len_positron"] -> Fill ( *rdr.primary_truth_TotalLength );
      _hists.th1_hists["h_prim_pida_positron"] -> Fill( rdr.primaryPID_PIDA.At(0) ); // plane 0 = collection
    }
    else if ( *rdr.primary_truth_Pdg == utils::pdg::kPdgMuon ) {
      _hists.th1_hists["h_prim_pida_muon"] -> Fill( rdr.primaryPID_PIDA.At(0) ); // plane 0 = collection
    }
    else {

    }

    // Count nucleon truth daughters
    np = _sel.Count<int>(rdr.primary_truthdaughter_Pdg, utils::pdg::kPdgProton );
    nn = _sel.Count<int>(rdr.primary_truthdaughter_Pdg, utils::pdg::kPdgNeutron );

    _hists.th2_hists["h_neutron_proton_all"] -> Fill( np, nn );

    if ( ptruth_pdg != utils::pdg::kPdgPiP ) continue;  // Only pion mother below this

    // Get the primary end direction
    TVector3 prim_enddir( rdr.primaryEndDirection.At(0),rdr.primaryEndDirection.At(1), rdr.primaryEndDirection.At(2) );

    // Loop over truth daughters
    np = 0; nn = 0;
    for ( int i = 0; i < ( *rdr.primary_truth_NDAUGTHERS ); i++ ) {

//      TVector3 daughter_startdir( rdr.daughterStartDirectionX.At(i), rdr.daughterStartDirectionY.At(i), rdr.daughterStartDirectionZ.At(i) );
      TVector3 daughter_startdir( rdr.daughterEndDirectionX.At(i), rdr.daughterEndDirectionY.At(i), rdr.daughterEndDirectionZ.At(i) );

      _hists.th1_hists["h_daughter_pida_all_p0"] -> Fill( rdr.daughterPID_PIDAP0.At(i) ); // plane 0 = collection
      _hists.th1_hists["h_daughter_pida_all_p1"] -> Fill( rdr.daughterPID_PIDAP1.At(i) ); // plane 1 = collection
      _hists.th1_hists["h_daughter_pida_all_p2"] -> Fill( rdr.daughterPID_PIDAP2.At(i) ); // plane 2 = collection

      if ( rdr.primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgPiP ) { // daughter pions
        _hists.th1_hists["h_daughter_pida_pi"] -> Fill( rdr.daughterPID_PIDAP0.At(i) ); // plane 0 = collection
        _hists.th1_hists["h_truth_fspion_theta"] -> Fill( utils::ThetaAngle( prim_enddir, daughter_startdir ) );
        _hists.th1_hists["h_truth_fspion_phi"] -> Fill( utils::PhiAngle( prim_enddir, daughter_startdir ) );
      }
      else if ( rdr.primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgProton ) { // daughter proton
        np += 1;
        _hists.th1_hists["h_daughter_pida_proton"] -> Fill( rdr.daughterPID_PIDAP0.At(i) ); // plane 0 = collection
        _hists.th1_hists["h_truth_fsproton_theta"] -> Fill( utils::ThetaAngle( prim_enddir, daughter_startdir ) );
        _hists.th1_hists["h_truth_fsproton_phi"] -> Fill( utils::PhiAngle( prim_enddir, daughter_startdir ) );
      }
      else if ( rdr.primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgNeutron ) { // daughter neutron
        nn += 1;
        _hists.th1_hists["h_daughter_pida_neutron"] -> Fill( rdr.daughterPID_PIDAP0.At(i) ); // plane 0 = collection
        _hists.th1_hists["h_truth_fsneutron_theta"] -> Fill( utils::ThetaAngle( prim_enddir, daughter_startdir ) );
        _hists.th1_hists["h_truth_fsneutron_phi"] -> Fill( utils::PhiAngle( prim_enddir, daughter_startdir ) );
      }
      else if ( rdr.primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgPositron ) { // // daughter positron
        _hists.th1_hists["h_daughter_pida_positron"] -> Fill( rdr.daughterPID_PIDAP0.At(i) ); // plane 0 = collection
      }
      else if ( rdr.primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgMuon ) { // daughter muon
        _hists.th1_hists["h_daughter_pida_muon"] -> Fill( rdr.daughterPID_PIDAP0.At(i) ); // plane 0 = collection
      }

    }

    // Only pion QE events after this selection
    if ( !_sel.IsTruthPionQE( rdr ) ) continue;

    _hists.th1_hists["h_prim_ke_pionqe"] -> Fill( rdr.primaryKineticEnergy.At(0) );
    _hists.th1_hists["h_nproton"] -> Fill( np );
    _hists.th1_hists["h_nneutron"] -> Fill( nn );
    _hists.th1_hists["h_total_len_pionqe"] -> Fill( *rdr.primary_truth_TotalLength );

    _hists.th2_hists["h_neutron_proton_pionqe"] -> Fill( np, nn );

  }

  _hists.WriteHistos( _outfile );

}

void Pion_QE_MC_Selection::Config() {

  json conf = utils::LoadConfig( _config_file );
  if ( conf == 0 ) return;

  _outfile = conf.at("out_file").get<std::string>();
  std::cout << "Output file: " << _outfile << std::endl;

}

