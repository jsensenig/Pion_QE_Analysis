//
// Created by Jon Sensenig on 12/3/20.
//
#include "Pion_QE_Analysis.hpp"
#include "Pion_QE_MC_Selection.h"
#include "Reader.hpp"

// ROOT includes
#include "TFile.h"
#include "TString.h"

#include <iostream>
#include <string>
#include <vector>


//----------------------------------------------------------------
void ProcessFiles() {

  // Declare desired selections here and pass TTreeReader to it below
  Pion_QE_MC_Selection Sel;

  std::vector<TString> file_list = utils::LoadFileList( files );

  if ( file_list.empty() ) return;

  for ( auto & f : file_list ) {

    TFile *proc_file = TFile::Open( f );

    if( !proc_file -> IsOpen() ) {

      std::cout << "File " << f << " not open!" << std::endl;
      continue;

    }

    auto reader = std::make_unique<Reader>( proc_file );

    // Reset the tree back to the 0th entry before each algorithm
    reader->RestartTrees();
    Sel.ReadData( reader );

  }

}

void Config() {

  json conf = utils::LoadConfig( config_file );
  if ( conf == 0x0 ) return;

  files = conf.at("file_list").get<std::string>();
  std::cout << "File list " << files << std::endl;

}

//----------------------------------------------------------------
int main() {

  std::cout << "It's running!!" << std::endl;
  Config();
  ProcessFiles();
  return 0;
}