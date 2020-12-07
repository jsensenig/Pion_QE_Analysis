//
// Created by Jon Sensenig on 12/5/20.
//

#include "Histograms.h"


Histograms::Histograms()
{ Config(); }

Histograms::~Histograms()
{ ; }

void Histograms::ConfigureHistos() {

  json hists_1d = _conf.at("1d_hists");

  for ( auto & h : hists_1d ) {

    auto name = h.at("name").get<std::string>();
    th1_hists[name] = utils::Create1dHist( h );

  }

  json hists_2d = _conf.at("2d_hists");

  for ( auto & h : hists_2d ) {

    auto name = h.at("name").get<std::string>();
    th2_hists[name] = utils::Create2dHist( h );

  }

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

  _conf = utils::LoadConfig( _config_file );
  if ( _conf == 0 ) return;

}