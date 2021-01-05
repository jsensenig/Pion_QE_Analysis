//
// Created by Jon Sensenig on 12/4/20.
//

#include "Reader.hpp"


Reader::Reader( TFile * file ) :
 infile( file )
 { }

Reader::~Reader()
{ }

bool Reader::Next() {

  return beamtrack_reader.Next() && recobeamtevt_reader.Next() && recodaughters_reader.Next();

}

void Reader::RestartTrees() {

  config_reader.Restart();
  beamtrack_reader.Restart();
  recobeamtevt_reader.Restart();
  recodaughters_reader.Restart();

}