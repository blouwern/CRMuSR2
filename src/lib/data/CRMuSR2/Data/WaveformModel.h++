#pragma once

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Data/Value.h++"

#include <vector>

namespace CRMuSR2::Data {

/// @brief Waveform model
/// @note Shared between many digit models. Lossless up to 24-bit ADC and TDC
using WaveformModel = Mustard::Data::TupleModel<
    Mustard::Data::Value<double, "tF0", "[ns] Frame begin time">,
    Mustard::Data::Value<float, "dtF", "[ns] Sampling interval">,
    Mustard::Data::Value<std::vector<float>, "amp", "[a.u.] Waveform samples">>;
using Waveform = Mustard::Data::Tuple<WaveformModel>;

} // namespace CRMuSR2::Data
