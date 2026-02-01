#pragma once

#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Data/Value.h++"

#include <cstdint>

namespace CRMuSR2::Data::internal {

/// @brief Shared between many digit models
using DigiModelHeader = Mustard::Data::TupleModel<
    Mustard::Data::Value<std::int32_t, "EvtID", "Event ID">,
    Mustard::Data::Value<std::int32_t, "DigiID", "Digit ID">,
    Mustard::Data::Value<std::int32_t, "wt", "Digit weight">>;

} // namespace CRMuSR2::Data::internal
