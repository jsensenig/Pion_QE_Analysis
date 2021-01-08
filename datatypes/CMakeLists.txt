cmake_minimum_required(VERSION 3.15)
project(custom_dicts)

set(CMAKE_CXX_STANDARD 11)
# Use the g++ compiler to match ROOT
SET(CMAKE_CXX_COMPILER g++)

find_package(ROOT 6.22 CONFIG REQUIRED)

include_directories(.)

#Generate a ROOT dictionary.
ROOT_GENERATE_DICTIONARY(VecsDict
        vector_vector.h
        LINKDEF LinkDef.h
        MODULE Vecs)

#Create the CustomClasses library with the ROOT dictionary.
add_library(Vecs SHARED
            VecsDict.cxx)

target_link_libraries(Vecs
        PUBLIC ROOT::Core
        ROOT::Tree
        ROOT::TreePlayer
        )
