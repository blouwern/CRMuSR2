#pragma once

#include "CRMuSR2/Data/internal/HitModelHeader.h++"
#include "CRMuSR2/Data/internal/SimHitTrackTruthModel.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Data/Value.h++"

#include "muc/array"

#include <cstdint>

namespace CRMuSR2::Data {

/// @brief Scintillator hit model
/// @note For real and simulation data
using ScintillatorHitModel = Mustard::Data::TupleModel<
    internal::HitModelHeader,
    Mustard::Data::Value<std::int32_t, "DetID", "Detector ID">,
    Mustard::Data::Value<double, "t", "[ns] Hit time">,
    Mustard::Data::Value<float, "Edep", "[MeV] Energy deposition">,
    Mustard::Data::Value<std::vector<std::int32_t>, "DigiID", "Photosensor digit(ID)s in this scintillator hit">>;
using ScintillatorHit = Mustard::Data::Tuple<ScintillatorHitModel>;

/// @brief Simulated scintillator hit model
/// @note Only for simulation data
/// @extends ScintillatorHitModel
using SimScintillatorHitModel = Mustard::Data::TupleModel<
    ScintillatorHitModel,
    Mustard::Data::Value<muc::array3f, "x", "[mm] Hit position (MC truth)">,
    Mustard::Data::Value<float, "Ek", "[MeV] Hit kinetic energy (MC truth)">,
    Mustard::Data::Value<muc::array3f, "p", "[MeV/c] Hit momentum (MC truth)">,
    internal::SimHitTrackTruthModel>;
using SimScintillatorHit = Mustard::Data::Tuple<SimScintillatorHitModel>;

} // namespace CRMuSR2::Data
