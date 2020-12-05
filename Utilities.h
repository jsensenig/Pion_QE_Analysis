//
// Created by Jon Sensenig on 12/3/20.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "TString.h"

//@brief Utility to load a list of files to process from a file.
//
//----------------------------------------------------------------
std::vector<TString> LoadFileList( std::string file_list ) {

  std::vector<TString> file_vec;
  std::string line;

  std::ifstream file;
  file.open( file_list );

  if ( file.is_open() )
  {
    while ( getline ( file, line ) )
    {
      std::cout << "Loading file: " << line << std::endl;
      file_vec.push_back(line);
    }
    file.close();
  }
  else std::cout << "Unable to open file" << std::endl;

  return file_vec;

}