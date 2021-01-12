//
// Created by Jon Sensenig on 12/3/20.
//

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "../contrib/json.hpp"
#include "Reader.hpp"
#include "Types.hpp"

#include "TString.h"
#include "TH1I.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2I.h"
#include "TH2D.h"
#include "TH2F.h"
#include "Math/GenVector/AxisAngle.h"

#include <iostream>
#include <fstream>
#include <vector>

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

    static std::string pdg2string( int p ){

      switch ( p ) {
        case kPdgMuon     : return "Muon";
        case kPdgPiP      : return "Pion";
        case kPdgKP       : return "Kaon";
        case kPdgProton   : return "Proton";
        case kPdgNeutron  : return "Neutron";
        case kPdgPositron : return "Positron";
        case kPdgElectron : return "Electron";
        default           : return "Unknown";
      }

    }

  }




//@brief Utility to load a list of files to process from a file.
//
//----------------------------------------------------------------
  static std::vector<TString> LoadFileList( const std::string &file_list ) {

    std::vector<TString> file_vec;
    std::string line;

    std::ifstream file(file_list);

    if (file.is_open()) {
      while (getline(file, line)) {
        std::cout << "Loading file: " << line << std::endl;
        file_vec.emplace_back(line);
      }
      file.close();
    } else std::cout << "Unable to open file " << file_list << std::endl;

    return file_vec;

  }

  static json LoadConfig( const std::string & file ) {

    std::ifstream injson( file );

    if ( !injson.is_open() ) {

     std::cout << "Failed to open config file " << file << std::endl;
     return nullptr;

   }

    json parsed;
    try {

      parsed = json::parse( injson );

    } catch ( json::exception &ex ) {

      std::cout << " Parse error in file " << file << " " << ex.what() << std::endl;
      return nullptr;

    }

    return parsed;

  }

  static std::unique_ptr<TH1> Create1dHist( json & c ) {

    auto name = c.at("name").get<std::string>();
    auto type = c.at("type").get<std::string>();
    auto axes = c.at("axes").get<std::string>();

    int bins     = c.at("bins").get<int>();
    double u_lim = c.at("u_lim").get<double>();
    double l_lim = c.at("l_lim").get<double>();

    if ( type == "TH1I" )      return std::make_unique<TH1I>(name.c_str(), axes.c_str(), bins, l_lim, u_lim);
    else if ( type == "TH1D" ) return std::make_unique<TH1D>(name.c_str(), axes.c_str(), bins, l_lim, u_lim);
    else if ( type == "TH1F" ) return std::make_unique<TH1F>(name.c_str(), axes.c_str(), bins, l_lim, u_lim);
    else return nullptr;

  }

  static std::unique_ptr<TH2> Create2dHist( json & c ) {

    auto name = c.at("name").get<std::string>();
    auto type = c.at("type").get<std::string>();
    auto axes = c.at("axes").get<std::string>();

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

  static std::map<std::string, double> MakePrimaryPIDMap( std::unique_ptr<Reader> & rdr, int plane=2 ) {

    std::map<std::string, double> pid_map;

    pid_map.emplace( "proton_chi2", *rdr->reco_beam_allTrack_Chi2_proton );
    //pid_map.emplace( "pion_chi2", rdr->primaryPID_Chi2Pion.At(plane) );
    //pid_map.emplace( "muon_chi2", rdr->primaryPID_Chi2Muon.At(plane) );
    //pid_map.emplace( "kaon_chi2", rdr->primaryPID_Chi2Kaon.At(plane) );

    //pid_map.emplace( "proton_chi2", rdr->primaryPID_PIDA.At(plane) );
    pid_map.emplace( "truth_pdg", *rdr->true_beam_PDG );

    return pid_map;

  }

  //------------------------------------------------------------
  // Rotate vector v into dir reference frame then return the theta angle in that frame
  static double ThetaAngle( const Vector_t& dir, Vector_t v ) {

    //v.RotateUz( dir.Unit() ) ;   FIXME
    //ROOT::Math::AxisAngle r(dir, 0);
    //return (r * v).Theta();
    return v.Theta();

  }

  //-------------------------------------------------------------
  // Rotate vector v into dir reference frame then return the phi angle in that frame
  static double PhiAngle( const Vector_t& dir, Vector_t v ) {

    //v.RotateUz( dir.Unit() ) ;  FIXME
    //ROOT::Math::AxisAngle r(dir, 0);
    //return (r * v).Phi();
    return v.Phi();

  }

  //-------------------------------------------------------------
  // Calculate kinetic energy for a given momentum and mass
  static double CalculateKE( const Vector_t & p, const double m ) {

    return sqrt( p.Mag2() + pow(m, 2) ) - m;

  }

  //-------------------------------------------------------------
  // Calculate kinetic energy for a given momentum and mass
  static double CalculateKE( const double p, const double m ) {

    return sqrt( pow(p, 2) + pow(m, 2) ) - m;

  }


  // Template function to count the occurrence of a specified TTree array elements
  //----------------------------------------------------------------
  template<typename T>
  int Count( TTreeReaderArray<T> & arr, T a ) {

    return std::count( arr.begin(), arr.end(), a );

  }

  // Template function to find an element in a TTree array
  //----------------------------------------------------------------
  template<typename T>
  T Find( TTreeReaderArray<T> & arr, T a ) {

    auto it = std::find( arr.begin(), arr.end(), a );

    if ( it != arr.end() ) return *it;
    else return -1;

  }

  // Template function to find and return an element index in a TTree array
  //----------------------------------------------------------------
  template<typename T>
  int FindIndex( TTreeReaderArray<T> & arr, T a ) {

    auto it = std::find( arr.begin(), arr.end(), a );

    if ( it != arr.end() ) return it - arr.begin();
    else return -1;

  }

}

#endif //UTILITIES_HPP