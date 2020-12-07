//
// Created by Jon Sensenig on 12/3/20.
//

#include "Pion_QE_MC_Selection.h"
#include "Utilities.h"
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

    _hists.h_beam_e -> Fill( *rdr.beamtrackEnergy);
    _hists.h_total_len -> Fill( *rdr.primary_truth_TotalLength );
    _hists.h_prim_pida_all -> Fill( rdr.primaryPID_PIDA.At(0) ); // plane 0 = collection

    if ( *rdr.primary_truth_Pdg == utils::pdg::kPdgPiP ) { // only select pions
      _hists.h_prim_pida_pi -> Fill( rdr.primaryPID_PIDA.At(0) ); // plane 0 = collection
    }

    // Only pion QE events after this selection
    if ( !_sel.IsTruthPionQE( rdr ) ) continue;

    // Loop over truth daughters
    int np = 0; int nn = 0;
    for ( int i = 0; i < ( *rdr.primary_truth_NDAUGTHERS ); i++ ) {
      if( rdr.primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgProton )  np += 1;
      if( rdr.primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgNeutron ) nn += 1;
    }

    _hists.h_prim_ke -> Fill( *rdr.primary_truth_KinEnergy_InTPCActive );
    _hists.h_nproton -> Fill( np );
    _hists.h_nneutron -> Fill( nn );
    _hists.h_n_np -> Fill( np, nn );
    _hists.h_total_len_pionqe -> Fill( *rdr.primary_truth_TotalLength );

  }

  _hists.WriteHistos( _outfile );

}

void Pion_QE_MC_Selection::Config() {

  json conf = utils::LoadConfig( _config_file );
  if ( conf == 0 ) return;

  _outfile = conf.at("out_file").get<std::string>();
  std::cout << "Output file: " << _outfile << std::endl;

}

