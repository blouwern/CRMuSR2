#pragma once

#include "CRMuSR2/Data/WaveformModel.h++"
#include "CRMuSR2/Data/internal/DigiModelHeader.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Data/Value.h++"

#include "muc/array"

#include <cstdint>

namespace CRMuSR2::Data {

/// @brief Simulated photosensor hit model
/// @note Only for simulation data
using SimPhotosensorHitModel = Mustard::Data::TupleModel<
    Mustard::Data::Value<std::int32_t, "EvtID", "Event ID">,
    Mustard::Data::Value<std::int32_t, "ChID", "Channel ID">,
    Mustard::Data::Value<double, "t", "[ns] Hit time">,
    Mustard::Data::Value<muc::array2f, "x", "[mm] Relative hit position">,
    Mustard::Data::Value<muc::array3f, "k", "[1/mm] Photon wave vector">>;
using SimPhotosensorHit = Mustard::Data::Tuple<SimPhotosensorHitModel>;

/// @brief Photosensor digit model
/// @note For real and simulation data
using PhotosensorDigiModel = Mustard::Data::TupleModel<
    internal::DigiModelHeader,
    Mustard::Data::Value<std::int32_t, "ChID", "Channel ID">,
    Mustard::Data::Value<float, "Npe", "Number of photoelectrons">,
    Mustard::Data::Value<double, "t", "[ns] Signal time">,
    WaveformModel>;
using PhotosensorDigi = Mustard::Data::Tuple<PhotosensorDigiModel>;

} // namespace CRMuSR2::Data
