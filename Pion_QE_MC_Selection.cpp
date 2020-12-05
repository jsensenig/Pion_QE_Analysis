//
// Created by Jon Sensenig on 12/3/20.
//

#include "Pion_QE_MC_Selection.h"
#include "Selections.h"
#include "Histograms.h"
#include "Reader.h"
// std library includes
#include <iostream>


//----------------------------------------------------------------
void Pion_QE_MC_Selection::ReadData(TFile *file) {

  std::cout << "Loading up reader" << std::endl;

  Reader reader;
  // Read the Root trees into the TTreeReader
  reader.ConfigureReader(file);
  // Set the tree leaves to TTreeValues and TTreeArrays
  reader.ConfigureLeaves();

  // Selection class
  Selections sel;

  //Histogram class
  Histograms hists;
  // Create the histograms
  hists.ConfigureHistos();

  // Loop over trees
  while ( reader.Next() ) {
    
    hists.h_beam_e -> Fill( **reader.beamtrackEnergy);
    if ( **reader.beamtrack_truth_Pdg == 2212 ) { hists.h_beam_e_cut -> Fill(**reader.beamtrackEnergy); }

    // Loop over truth daughters
    bool pi_pi = false; int np = 0; int nn = 0;
    for ( int i = 0; i < (**reader.primary_truth_ndaughters); i++ ) {

      if( **reader.primary_truth_Pdg == 211 && (*reader.primary_truthdaughter_Pdg)[i] == 211 ) { //primary and FS pion
        hists.h_prim_ke -> Fill( **reader.primary_truth_KinEnergy_InTPCActive );
        pi_pi = true;
      }
      if( (*reader.primary_truthdaughter_Pdg)[i] == 2212 ) np += 1;
      if( (*reader.primary_truthdaughter_Pdg)[i] == 2112 ) nn += 1;
    }

    //std::cout << "Pass daughter cut? " << sel.DaughterCut(np, nn) << std::endl;

    if ( pi_pi ){
      hists.h_nproton -> Fill( np );
      hists.h_nneutron -> Fill( nn );
      hists.h_n_np -> Fill( np, nn );
    }

  }

  hists.WriteHistos("output.root");

}

