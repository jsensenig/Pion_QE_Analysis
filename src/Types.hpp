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

using Point_t = ROOT::Math::PositionVector3D<ROOT::Math::Cartesian3D<double>>;
using Vector_t = ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>>;
using Position4_t = ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double>>;

#endif //PION_QE_TYPES_HPP
