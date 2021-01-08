cmake_minimum_required( VERSION 3.15 )
project( Pion_QE )

set( CMAKE_CXX_STANDARD 17 )

find_package( ROOT 6.22 CONFIG REQUIRED )

include_directories( . )

# Add the custom ROOT data dictionary
add_subdirectory( datatypes )

add_executable( pion_qe_mc_selection
        CMakeLists.txt
        src/Pion_QE_Analysis.cxx
        src/Pion_QE_Analysis.hpp
        src/Pion_QE_MC_Selection.cpp
        src/Pion_QE_MC_Selection.h
        src/Utilities.hpp
        src/Reader.cpp
        src/Reader.hpp
        src/Selections.cpp
        src/Selections.hpp
        src/Histograms.cpp
        src/Histograms.hpp
        src/Types.hpp )

add_library( libVecs SHARED IMPORTED )
set_target_properties( libVecs PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/build/datatypes/libVecs.dylib )

target_link_libraries( pion_qe_mc_selection
         PUBLIC libVecs
                ROOT::Physics
                ROOT::Core
                ROOT::Hist
                ROOT::ROOTVecOps
                ROOT::Tree
                ROOT::TreePlayer )
