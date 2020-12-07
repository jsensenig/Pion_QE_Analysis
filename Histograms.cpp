//
// Created by Jon Sensenig on 12/5/20.
//

#include "Histograms.h"
#include "Utilities.h"


Histograms::Histograms()
{ Config(); }

Histograms::~Histograms()
{ ; }

void Histograms::ConfigureHistos() {

  // 1D histograms
  h_beam_e = th1_hists["h_beam_e"] = std::make_unique<TH1D>("h_beam_e", ";E;Count", 80, 0., 2.0 );
  h_beam_e_cut = th1_hists["h_beam_e_cut"] = std::make_unique<TH1D>("h_beam_e_cut", ";E;Count", 80, 0., 2.0 );
  h_prim_ke = th1_hists["h_prim_ke"] = std::make_unique<TH1D>("h_prim_ke", ";KE;Count", 120, 0., 3. );
  h_nproton = th1_hists["h_nproton"] = std::make_unique<TH1I>("h_nproton", ";protons;Count", 15, 0, 15 );
  h_nneutron = th1_hists["h_nneutron"] = std::make_unique<TH1I>("h_nneutron", ";neutron;Count", 15, 0, 15 );
  h_total_len = th1_hists["h_total_len"] = std::make_unique<TH1D>("h_total_len", ";Total Length [cm];Count", 100, 0., 500. );
  h_total_len_pionqe = th1_hists["h_total_len_pionqe"] = std::make_unique<TH1D>("h_total_len_pionqe", ";Total Length [cm];Count", 100, 0., 500. );
  h_prim_pida_pi = th1_hists["h_prim_pida_pi"] = std::make_unique<TH1D>("h_prim_pida_pi", ";PIDA;Count", 10, 0., 10.);
  h_prim_pida_all = th1_hists["h_prim_pida_all"] = std::make_unique<TH1D>("h_prim_pida_all", ";PIDA;Count", 40, 0., 40.);

  // 2D histograms
  h_n_np = th2_hists["h_n_p"] = std::make_unique<TH2I>("h_n_np", ";proton;neutron", 10, 0, 10, 10, 0, 10 );

}

void Histograms::WriteHistos( TString & out_file ) {

  if ( ! OpenFile( out_file ) ) return;

  for ( auto & h : th1_hists ) {
    h.second -> Write();
  }

  for ( auto & h : th2_hists ) {
    h.second -> Write();
  }

  ofile -> Close();

}

bool Histograms::OpenFile( TString & out_file ) {

  ofile = std::make_unique<TFile>(out_file,"recreate");

  if ( !ofile -> IsOpen() ) {
    std::cout << " Failed to open output file " << out_file << std::endl;
    return false;
  }
  return true;
}

void Histograms::Config() {

  json conf = utils::LoadConfig( _config_file );
  if ( conf == 0 ) return;



}