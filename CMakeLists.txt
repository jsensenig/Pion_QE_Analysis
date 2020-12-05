cmake_minimum_required(VERSION 3.15)
project(Pion_QE)

set(CMAKE_CXX_STANDARD 17)

find_package(ROOT 6.22 CONFIG REQUIRED)

include_directories(.)

add_executable(pion_qe_mc_selection
        CMakeLists.txt
        Pion_QE_Analysis.cpp
        Pion_QE_Analysis.h
        Pion_QE_MC_Selection.cpp
        Pion_QE_MC_Selection.h Utilities.h Reader.cpp Reader.h Selections.cpp Selections.h Histograms.cpp Histograms.h)

target_link_libraries(pion_qe_mc_selection PUBLIC ROOT::Physics ROOT::Core ROOT::Hist ROOT::ROOTVecOps ROOT::Tree ROOT::TreePlayer)