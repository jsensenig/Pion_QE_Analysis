//
// Created by Jon Sensenig on 12/5/20.
//

#include "Histograms.hpp"


Histograms::Histograms()
{ ; }

Histograms::~Histograms()
{ ; }

bool Histograms::ConfigureHistos( std::string config_file ) {

  json conf = utils::LoadConfig( config_file );

  if ( conf == 0x0 ) return false; // Failed to load config

  json hists_1d = conf.at("1d_hists");

  for ( auto & h : hists_1d ) {

    auto name = h.at("name").get<std::string>();
    th1_hists[name] = utils::Create1dHist( h );

  }

  json hists_2d = conf.at("2d_hists");

  for ( auto & h : hists_2d ) {

    auto name = h.at("name").get<std::string>();
    th2_hists[name] = utils::Create2dHist( h );

  }

  return true;

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
