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
#include "TTreeReader.h"


//----------------------------------------------------------------
void ProcessFiles() {

  Pion_QE_MC_Selection Sel;

  std::string f_list = "../files.txt";
  std::vector<TString> file_list = LoadFileList( f_list );

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

//----------------------------------------------------------------
int main() {

  std::cout << "It's running!!" << std::endl;
  ProcessFiles();
  return 0;
}