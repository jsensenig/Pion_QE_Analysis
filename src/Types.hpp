//
// Created by Jon Sensenig on 1/4/21.
//

#ifndef PION_QE_TYPES_HPP
#define PION_QE_TYPES_HPP

#include "Math/GenVector/Cartesian3D.h"
#include "Math/GenVector/PositionVector3D.h"
#include "Math/GenVector/DisplacementVector3D.h"
#include "Math/GenVector/PxPyPzE4D.h"
#include "Math/GenVector/LorentzVector.h"


// Use the GenVector class as replacements for the TVector3 and TLorenzVector.
// They are less memory and CPU intensive than their counterparts.

// Describe a 3D point which is invariant to rotations
using Point_t = ROOT::Math::PositionVector3D<ROOT::Math::Cartesian3D<double>>;

// Describe a 3D displacement which is invariant to translations
using Vector_t = ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>>;

// Describe 4D momentum and energy, a Lorentz Vector
using Position4_t = ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double>>;

#endif //PION_QE_TYPES_HPP
