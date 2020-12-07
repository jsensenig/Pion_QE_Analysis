//
// Created by Jon Sensenig on 12/3/20.
//
#include <iostream>
#include <fstream>
#include <vector>

#include "TString.h"
#include "TH1I.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2I.h"
#include "TH2D.h"
#include "TH2F.h"

#include <contrib/json.hpp>

using json = nlohmann::json;

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
  static std::vector<TString> LoadFileList(const std::string &file_list) {

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

  static json LoadConfig( const std::string & file ) {

    std::ifstream injson( file );

    if ( !injson.is_open() ) {

     std::cout << "Failed to open config file " << file << std::endl;
     return nullptr;

   }

    return json::parse(injson);

  }

  static std::unique_ptr<TH1> Create1dHist( json & c ) {

    std::string name = c.at("name").get<std::string>();
    std::string type = c.at("type").get<std::string>();
    std::string axes = c.at("axes").get<std::string>();

    int bins     = c.at("bins").get<int>();
    double u_lim = c.at("u_lim").get<double>();
    double l_lim = c.at("l_lim").get<double>();

    if ( type == "TH1I" )      return std::make_unique<TH1I>(name.c_str(), axes.c_str(), bins, l_lim, u_lim);
    else if ( type == "TH1D" ) return std::make_unique<TH1D>(name.c_str(), axes.c_str(), bins, l_lim, u_lim);
    else if ( type == "TH1F" ) return std::make_unique<TH1F>(name.c_str(), axes.c_str(), bins, l_lim, u_lim);
    else return nullptr;

  }

  static std::unique_ptr<TH2> Create2dHist( json & c ) {

    std::string name = c.at("name").get<std::string>();
    std::string type = c.at("type").get<std::string>();
    std::string axes = c.at("axes").get<std::string>();

    int xbins     = c.at("xbins").get<int>();
    double xu_lim = c.at("xu_lim").get<double>();
    double xl_lim = c.at("xl_lim").get<double>();
    int ybins     = c.at("ybins").get<int>();
    double yu_lim = c.at("yu_lim").get<double>();
    double yl_lim = c.at("yl_lim").get<double>();

    if ( type == "TH2I" )      return std::make_unique<TH2I>(name.c_str(), axes.c_str(), xbins, xl_lim, xu_lim, ybins, yl_lim, yu_lim);
    else if ( type == "TH2D" ) return std::make_unique<TH2D>(name.c_str(), axes.c_str(), xbins, xl_lim, xu_lim, ybins, yl_lim, yu_lim);
    else if ( type == "TH2F" ) return std::make_unique<TH2F>(name.c_str(), axes.c_str(), xbins, xl_lim, xu_lim, ybins, yl_lim, yu_lim);
    else return nullptr;

  }
}