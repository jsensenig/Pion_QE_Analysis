//
// Created by Jon Sensenig on 12/3/20.
//
#include "Pion_QE_Analysis.h"
#include "Pion_QE_MC_Selection.h"
#include "Utilities.h"

#include <iostream>
#include <string>
#include <vector>

// ROOT incudes
#include "TFile.h"
#include "TString.h"


//----------------------------------------------------------------
void ProcessFiles() {

  Pion_QE_MC_Selection Sel;

//  std::string f_list = "../files.txt";
  std::vector<TString> file_list = utils::LoadFileList( files );

  if ( file_list.empty() ) return;

  for ( auto & f : file_list ) {

    TFile *proc_file = TFile::Open( f );

    if( !proc_file -> IsOpen() ) {

      std::cout << "File " << f << " not open!" << std::endl;
      continue;

    }

    Sel.ReadData(proc_file);

  }

}

void Config() {

  json conf = utils::LoadConfig( config_file );
  if ( conf == 0 ) return;

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