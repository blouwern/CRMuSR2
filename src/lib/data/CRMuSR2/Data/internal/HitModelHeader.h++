#pragma once

#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Data/Value.h++"

#include <cstdint>

namespace CRMuSR2::Data::internal {

/// @brief Shared between many hit models
using HitModelHeader = Mustard::Data::TupleModel<
    Mustard::Data::Value<std::int32_t, "EvtID", "Event ID">,
    Mustard::Data::Value<std::int32_t, "HitID", "Hit ID">,
    Mustard::Data::Value<std::int32_t, "wt", "Hit weight">>;

} // namespace CRMuSR2::Data::internal
