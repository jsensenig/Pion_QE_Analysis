//
// Created by Jon Sensenig on 12/3/20.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "TString.h"

namespace utils {

  namespace pdg {

    const int kPdgPositron = -11;
    const int kPdgElectron = 11;
    const int kPdgMuon = 13;
    const int kPdgAntiMuon = -13;
    const int kPdgPiP = 211; // pi+
    const int kPdgPiM = -211; // pi-
    const int kPdgPi0 = 111; // pi0
    const int kPdgKP = 321; // K+
    const int kPdgKM = -321; // K-
    const int kPdgK0 = 311; // K0
    const int kPdgProton = 2212; //
    const int kPdgAntiProton = -2212; //
    const int kPdgNeutron = 2112; //
    const int kPdgAntiNeutron = -2112; //

  }


//@brief Utility to load a list of files to process from a file.
//
//----------------------------------------------------------------
  static std::vector<TString> LoadFileList( const std::string &file_list ) {

    std::vector<TString> file_vec;
    std::string line;

    std::ifstream file;
    file.open(file_list);

    if (file.is_open()) {
      while (getline(file, line)) {
        std::cout << "Loading file: " << line << std::endl;
        file_vec.emplace_back(line);
      }
      file.close();
    } else std::cout << "Unable to open file" << std::endl;

    return file_vec;

  }

}