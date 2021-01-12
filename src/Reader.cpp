//
// Created by Jon Sensenig on 12/4/20.
//

#include "Reader.hpp"


Reader::Reader( TFile * file ) :
 infile( file )
 { }

Reader::~Reader()
{ }

bool Reader::Next() { return beamana_reader.Next(); }

void Reader::RestartTrees() { beamana_reader.Restart(); }