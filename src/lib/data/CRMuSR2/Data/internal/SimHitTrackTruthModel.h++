#pragma once

#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Data/Value.h++"

#include "muc/array"

#include <cstdint>
#include <string>

namespace CRMuSR2::Data::internal {

/// @brief Shared between many simulated hit models
using SimHitTrackTruthModel = Mustard::Data::TupleModel<
    Mustard::Data::Value<std::int32_t, "TrkID", "MC Track ID">,
    Mustard::Data::Value<std::int32_t, "PDGID", "Particle PDG ID (MC truth)">,
    Mustard::Data::Value<double, "t0", "[ns] Track initial time (MC truth)">,
    Mustard::Data::Value<muc::array3f, "x0", "[mm] Track initial position (MC truth)">,
    Mustard::Data::Value<float, "Ek0", "[MeV] Track initial kinetic energy (MC truth)">,
    Mustard::Data::Value<muc::array3f, "p0", "[MeV/c] Track initial momentum (MC truth)">,
    Mustard::Data::Value<std::string, "CreatProc", "Track creator process (MC truth)">>;

} // namespace CRMuSR2::Data::internal
