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

    _hists.th1_hists["h_beam_e"] -> Fill(*rdr.beamtrackEnergy);
    _hists.th1_hists["h_total_len"] -> Fill( *rdr.primary_truth_TotalLength );
    _hists.th1_hists["h_prim_pida_all"] -> Fill( rdr.primaryPID_PIDA.At(0) ); // plane 0 = collection

    int np, nn;
    if ( *rdr.primary_truth_Pdg == utils::pdg::kPdgPiP ) { // primary pions
      _hists.th1_hists["h_prim_pida_pi"] -> Fill( rdr.primaryPID_PIDA.At(0) ); // plane 0 = collection
      _hists.th1_hists["h_total_len_pion"] -> Fill ( *rdr.primary_truth_TotalLength );
      np = _sel.Count<int>(rdr.primary_truthdaughter_Pdg, utils::pdg::kPdgProton );
      nn = _sel.Count<int>(rdr.primary_truthdaughter_Pdg, utils::pdg::kPdgNeutron );
      _hists.th2_hists["h_neutron_proton_pion"] -> Fill( np, nn ); 
    }
    if ( *rdr.primary_truth_Pdg == utils::pdg::kPdgProton ) { // primary protons
      _hists.th1_hists["h_total_len_proton"] -> Fill ( *rdr.primary_truth_TotalLength );
    }
    if ( *rdr.primary_truth_Pdg == utils::pdg::kPdgPositron ) { // primary positron
      _hists.th1_hists["h_total_len_positron"] -> Fill ( *rdr.primary_truth_TotalLength );
    }

    // Loop over truth daughters
    np = _sel.Count<int>(rdr.primary_truthdaughter_Pdg, utils::pdg::kPdgProton );
    nn = _sel.Count<int>(rdr.primary_truthdaughter_Pdg, utils::pdg::kPdgNeutron );

    _hists.th2_hists["h_neutron_proton_all"] -> Fill( np, nn );

    // Only pion QE events after this selection
    if ( !_sel.IsTruthPionQE( rdr ) ) continue;

    // Loop over truth daughters
    np = 0; nn = 0;
    for ( int i = 0; i < ( *rdr.primary_truth_NDAUGTHERS ); i++ ) {
      if( rdr.primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgProton )  np += 1;
      if( rdr.primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgNeutron ) nn += 1;
    }

    _hists.th1_hists["h_prim_ke"] -> Fill( *rdr.primary_truth_KinEnergy_InTPCActive );
    _hists.th1_hists["h_nproton"] -> Fill( np );
    _hists.th1_hists["h_nneutron"] -> Fill( nn );
    _hists.th1_hists["h_total_len_pionqe"] -> Fill( *rdr.primary_truth_TotalLength );

    _hists.th2_hists["h_neutron_proton"] -> Fill( np, nn );

  }

  _hists.WriteHistos( _outfile );

}

void Pion_QE_MC_Selection::Config() {

  json conf = utils::LoadConfig( _config_file );
  if ( conf == 0 ) return;

  _outfile = conf.at("out_file").get<std::string>();
  std::cout << "Output file: " << _outfile << std::endl;

}

