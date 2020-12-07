//
// Created by Jon Sensenig on 12/3/20.
//

#include "Pion_QE_MC_Selection.h"
#include "Selections.h"
#include "Histograms.h"
#include "Reader.h"
#include "Utilities.h"
// std library includes
#include <iostream>


//----------------------------------------------------------------
void Pion_QE_MC_Selection::ReadData(TFile *file) {

  std::cout << "Loading up reader" << std::endl;

  // ROOT event reader
  Reader reader(file);

  // Selection class
  Selections sel;

  //Histogram class
  Histograms hists;
  // Create the histograms
  hists.ConfigureHistos();

  // Loop over trees
  while ( reader.Next() ) {

    hists.h_beam_e -> Fill( *reader.beamtrackEnergy);

    if ( !sel.IsTruthPionQE( reader ) ) continue;

    // Loop over truth daughters
    int np = 0; int nn = 0;
    for ( int i = 0; i < ( *reader.primary_truth_NDAUGTHERS ); i++ ) {
      if( reader.primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgProton )  np += 1;
      if( reader.primary_truthdaughter_Pdg.At(i) == utils::pdg::kPdgNeutron ) nn += 1;
    }

    hists.h_prim_ke -> Fill( *reader.primary_truth_KinEnergy_InTPCActive );
    hists.h_nproton -> Fill( np );
    hists.h_nneutron -> Fill( nn );
    hists.h_n_np -> Fill( np, nn );
    hists.h_total_len-> Fill( *reader.primary_truth_TotalLength );

  }

  TString outfile = "output.root";
  hists.WriteHistos( outfile );

}

