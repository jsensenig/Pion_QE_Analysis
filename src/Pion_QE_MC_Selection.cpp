//
// Created by Jon Sensenig on 12/3/20.
//

#include "Pion_QE_MC_Selection.h"
#include "Types.hpp"
#include <iostream>

Pion_QE_MC_Selection::Pion_QE_MC_Selection()
{
  Config();
}

Pion_QE_MC_Selection::~Pion_QE_MC_Selection()
{
  // Write all histograms to file
  _hists.WriteHistos( _outfile );
}

//----------------------------------------------------------------
void Pion_QE_MC_Selection::ReadData( std::unique_ptr<Reader> & rdr ) {

  // Initialize variables
  _pionqe = _true_pionqe = _piontruth = _pionreco = 0;
  bool true_qe, reco_qe;

  // Loop over events
  while ( rdr->Next() ) {

    std::cout << "Event " << *rdr->event << " Run " << *rdr->run << " ********************************" << std::endl;
    int em_cnt = 0;
    int track_cnt = 0;
    true_qe = reco_qe = false;

    // Process the true pi+ QE events
    if ( sel.IsTruthPionQE( rdr ) ) {
      ProcessTrueQe( rdr );
      _true_pionqe += 1;
      true_qe = true;
    }

    // Plots for all beam particles

    int prim_pdg = *rdr->true_beam_PDG;
    // Histogram the start P for each true beam particle
    _hists.th2_hists["hPdgStartP"] -> Fill( utils::pdg::pdg2string(prim_pdg).c_str(), *rdr->true_beam_startP, 1 );
    // Histogram the end P for each true beam particle
    _hists.th2_hists["hPdgEndP"] -> Fill( utils::pdg::pdg2string(prim_pdg).c_str(), *rdr->true_beam_endP, 1 );
    // Check how far downstream the particles make it
    _hists.th2_hists["hPdgEndZ"] -> Fill( utils::pdg::pdg2string(prim_pdg).c_str(), *rdr->true_beam_endZ, 1 );

    for ( int i = 0; i < rdr->reco_daughter_PFP_trackScore.GetSize(); i++ ) {
      int pdg = rdr->reco_daughter_PFP_true_byHits_PDG.At(i); std::cout<<"Reco Daughter "<<pdg<<std::endl;
      double tscore = rdr->reco_daughter_PFP_trackScore.At(i);
      double escore = rdr->reco_daughter_PFP_emScore.At(i);
      _hists.th1_hists["RecoDghtrTrackScore"]->Fill( tscore );
      _hists.th1_hists["RecoDghtrEMScore"]->Fill( escore );
      _hists.th1_hists["RecoDghtrMiScore"]->Fill( rdr->reco_daughter_PFP_michelScore.At(i) );
      _hists.th2_hists["hPdgTrackScore"]->Fill(utils::pdg::pdg2string(pdg).c_str(), tscore, 1);
      _hists.th2_hists["hPdgEMScore"]->Fill(utils::pdg::pdg2string(pdg).c_str(), escore, 1);
      if ( sel.EMScoreCut( escore ) ) em_cnt++;
      if ( sel.TrackScoreCut( tscore ) ) track_cnt += 1;
    }

    // Check the TOF for beam particles
    _hists.th2_hists["hPdgBeamTof"] -> Fill( utils::pdg::pdg2string(prim_pdg).c_str(), rdr->beam_inst_TOF.At(0), 1 );

    for ( auto &dE : rdr->true_beam_elastic_deltaE ) _hists.th1_hists["h_omega_550"] -> Fill( dE );

    //---- Only events with pion mother below this selection -----
    for ( auto & score : rdr->reco_daughter_PFP_trackScore)

    std::cout << "EM count = " << em_cnt << " Track count = " << track_cnt << std::endl;
    // Only want nucleons or mesons in final state.
    // To be QE must be at least pi+ and 1 nucleon i.e. 2 tracks so conditions are
    // * < 2 counts of EM activity from CNN score
    // * > 0 count of Tracks from CNN score
    // * TOF cut to select pion this is beam energy dependent assuming 1GeV here
    bool select_evt = em_cnt < 2 && track_cnt > 0 && sel.PiTofCut(rdr->beam_inst_TOF.At(0))
                   && *rdr->reco_beam_type == 13;

    // Print event debug info if true and reco selection don't match
    if( true_qe != select_evt ) PrintEventDebug( rdr );

    if ( !select_evt ) {
      _hists.th2_hists["hTrueRecoPiQeConfusion"] -> Fill( reco_qe, true_qe );
      continue;
    }

    std::cout << "Beam End (x,y,z) = (" << *rdr->reco_beam_endX << ","
              << *rdr->reco_beam_endY << "," <<*rdr->reco_beam_endZ << ")" << std::endl;

    // Reached the end of selection should be a pi QE event
    std::cout << "\033[35m Selected reco pi QE event! \033[0m" << std::endl;
    reco_qe = true;
    _hists.th1_hists["hRecoPiQE"] -> Fill(1);
    _hists.th2_hists["hTrueRecoPiQeConfusion"] -> Fill( reco_qe, true_qe );
    // Daughter scattering angles wrt z-axis. Polar (theta) and azimuthal (phi)
    for ( int d = 0; d < rdr->reco_daughter_allTrack_Theta.GetSize(); d++ ) {
      _hists.th1_hists["hPiQeTheta"]->Fill( rdr->reco_daughter_allTrack_Theta.At( d ));
      _hists.th1_hists["hPiQePhi"]->Fill( rdr->reco_daughter_allTrack_Phi.At( d ));
    }

    // Check the XY position from beam instrumentation and TPC
    _hists.th2_hists["hRecoBeamInstXY"] -> Fill( *rdr->beam_inst_X, *rdr->beam_inst_Y );
    _hists.th2_hists["hRecoBeamTpcXY"] -> Fill( *rdr->reco_beam_startX, *rdr->reco_beam_startY );

    _pionqe += 1;

  }

  std::cout << "True Pi QE: " << _true_pionqe << " Reco Pi QE: " << _pionqe << " Truth 1 pion: "
            << _piontruth << " Reco 1 pion: " << _pionreco << std::endl;

}

// Extract info from true pi+ QE events
// -----------------------------------------------
void Pion_QE_MC_Selection::ProcessTrueQe( std::unique_ptr<Reader> & rdr ) {

  // Print the process tag the true beam particle undergoes
  // Since we're selecting only true QE events expect pi+ inelastic tag
  for ( auto &p  : rdr->true_beam_processes ) std::cout << "\033[35m Beam process " << p << "\033[0m" <<std::endl;

  // Keep tally of events
  _hists.th1_hists["hTruePiQE"] -> Fill(1);

  // Starting P in TPC for
  _hists.th1_hists["htruePiQeStartP"] -> Fill( *rdr->true_beam_startP );

  // The last P before the QE scatter, this should be the end of this particle and subsequent particles are daughters
  _hists.th1_hists["htruePiQeEndP"] -> Fill( *rdr->true_beam_endP );

  // Check how far the particle travels in Z
  _hists.th1_hists["hTruePiQeEndZ"] -> Fill( *rdr->true_beam_endZ );

}

void Pion_QE_MC_Selection::PrintEventDebug( std::unique_ptr<Reader> & rdr ) const {

  // Print truth info
  std::cout << "-------- Debug Event " << *rdr->event << " --------" << std::endl;
  std::cout << "\033[35m Truth Info \033[0m" << std::endl;
  std::cout << "Beam particle " << *rdr->true_beam_PDG << std::endl;

  for ( auto &p  : rdr->true_beam_processes ) std::cout << "Beam process " << p <<std::endl;
  for ( auto &d_pdg  : rdr->true_beam_daughter_PDG ) std::cout << "Daughter " << d_pdg <<std::endl;

  // Print reco info
  std::cout << "\033[35m Reco Info \033[0m" <<std::endl;
  for ( auto &d_pdg  : rdr->reco_daughter_PFP_true_byHits_PDG ) std::cout << "Daughter PDG by hits " << d_pdg <<std::endl;
  for ( auto & parent : rdr->reco_daughter_PFP_true_byHits_parPDG ) std::cout << "Parent PDG by hits " << parent <<std::endl;

}

// -----------------------------------------------
void Pion_QE_MC_Selection::CalculateELoss( std::unique_ptr<Reader> & rdr, int daughter ) {

  //Vector_t p(rdr->primary_truth_Momentum.At(0), rdr->primary_truth_Momentum.At(1), rdr->primary_truth_Momentum.At(2));
  //Vector_t p_prime(rdr->daughter_truth_MomentumX.At(daughter),
  //                 rdr->daughter_truth_MomentumY.At(daughter),
  //                 rdr->daughter_truth_MomentumZ.At(daughter));

  double omega = 0.;//rdr->primaryKineticEnergy.At(c_plane_) - rdr->daughterKineticEnergyP0.At(daughter);
  //double q = std::sqrt( (-q_vec.Mag2() * 1.e3) + omega ); // sqrt( Q2 + q0 )
  double q = 0.0; //(p - p_prime).R() * 1.e3; // Convert GeV -> Mev

  if ( q < 350. ) _hists.th1_hists["h_omega_350"] -> Fill( omega );
  else if ( q >= 350. && q < 550 ) _hists.th1_hists["h_omega_350_550"] -> Fill( omega );
  else if ( q >= 550. ) _hists.th1_hists["h_omega_550"] -> Fill( omega );

}

// -----------------------------------------------
void Pion_QE_MC_Selection::CalculateELoss( const Position4_t & k, const Position4_t& kp ) {

  std::cout << "k: Px " << k.Px() << " Py " << k.Py() << " Pz " << k.Pz() << " E " << k.E() << std::endl;
  std::cout << "kp: Px " << kp.Px() << " Py " << kp.Py() << " Pz " << kp.Pz() << " E " << kp.E() << std::endl;
  Position4_t q_vec = k - kp;
  // Convert all GeV -> Mev
  double omega = q_vec.E() * 1.e3;
  double q = q_vec.Vect().R() * 1.e3;

  if ( q < 350. ) _hists.th1_hists["h_omega_350"] -> Fill( omega );
  else if ( q >= 350. && q < 550 ) _hists.th1_hists["h_omega_350_550"] -> Fill( omega );
  else if ( q >= 550. ) _hists.th1_hists["h_omega_550"] -> Fill( omega );

}

void Pion_QE_MC_Selection::Config() {

  json conf = utils::LoadConfig( _config_file );
  if ( conf == nullptr ) return;

  _outfile = conf.at("out_file").get<std::string>();
  std::cout << "Output file: " << _outfile << std::endl;

  // Create the histograms
  _hists.ConfigureHistos( _config_file );

}

