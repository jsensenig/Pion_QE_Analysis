//
// Created by Jon Sensenig on 12/5/20.
//

#include "Histograms.h"



Histograms::Histograms()
{ ; }

Histograms::~Histograms()
{ ; }

void Histograms::ConfigureHistos() {

  h_beam_e = th1_hists["h_beam_e"] = new TH1D("h_beam_e", "E;Count", 80, 0., 2.0 );
  h_beam_e_cut = th1_hists["h_beam_e_cut"] = new TH1D("h_beam_e_cut", "E;Count", 80, 0., 2.0 );
  h_prim_ke = th1_hists["h_prim_ke"] = new TH1D("h_prim_ke", "KE;Count", 120, 0., 3. );
  h_nproton = th1_hists["h_nproton"] = new TH1I("h_nproton", "protons;Count", 15, 0, 15 );
  h_nneutron = th1_hists["h_nneutron"] = new TH1I("h_nneutron", "neutron;Count", 15, 0, 15 );
  h_n_np = th2_hists["h_n_p"] = new TH2I("h_n_np", "proton;neutron", 10, 0, 10, 10, 0, 10 );

}

void Histograms::WriteHistos( TString out_file ) {

  if ( ! OpenFile( out_file ) ) return;

  for ( auto & h : th1_hists ) {
    h.second -> Write();
    delete h.second;
  }

  for ( auto & h : th2_hists ) {
    h.second -> Write();
    delete h.second;
  }

  ofile -> Close();

}

bool Histograms::OpenFile( TString out_file ) {

  ofile = new TFile( out_file, "recreate" );

  if ( !ofile -> IsOpen() ) {
    std::cout << " Failed to open output file " << out_file << std::endl;
    return false;
  }
  return true;
}