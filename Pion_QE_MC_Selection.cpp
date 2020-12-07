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

  // ROOT event reader
  Reader rdr(file);

  // Create the histograms
  _hists.ConfigureHistos();

  // Loop over trees
  while ( rdr.Next() ) {

    _hists.h_beam_e -> Fill( *rdr.beamtrackEnergy);

    if ( !Selections::IsTruthPionQE( rdr ) ) continue;

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
    _hists.h_total_len-> Fill( *rdr.primary_truth_TotalLength );

  }

  TString outfile = "output.root";
  _hists.WriteHistos( outfile );

}

