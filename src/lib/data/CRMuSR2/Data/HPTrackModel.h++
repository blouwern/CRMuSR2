#pragma once

#include "CRMuSR2/Data/HPTrackStateModel.h++"

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Data/Value.h++"

#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>

namespace CRMuSR2::Data {

/// @brief High-momentum track type enumeration
/// @note Corresponding to the "TrkType" field in BasicHPTrackModel
enum struct HPTrackType : std::int8_t {
    Unknown,  // default value or candidate track
    Normal,   // real track from physical event
    Fake,     // fake track
    CosmicRay // cosmic ray track
};

/// @brief Reference point type enumeration for high-momentum tracks
/// @note Corresponding to the "RefPtType" field in BasicHPTrackModel
enum struct HPTrackRefPtType : std::int8_t {
    Unknown,         // default value
    Virtual,         // virtual point
    Vertex,          // vertex
    FirstHit,        // first hit in the track
    LastHit,         // last hit in the track
    IntermediateHit, // intermediate hit in the track
    POCAToBeamAxis,  // point of closest approach to beam axis
    POCAToOrigin     // point of closest approach to origin
};

/// @brief High-momentum (high-p) track model, for tracks in MMS
/// @note For real data and simulation data
/// @extends HPTrackStateModel
using HPTrackModel = Mustard::Data::TupleModel<
    Mustard::Data::Value<std::int32_t, "EvtID", "Event ID">,
    Mustard::Data::Value<std::int32_t, "TrkID", "Track ID">,
    Mustard::Data::Value<float, "wt", "Track weight">,
    Mustard::Data::Value<float, "chi2", "Goodness of fit (chi^{2})">,
    Mustard::Data::Value<float, "ndf", "Number of degrees of freedom in fit">,
    Mustard::Data::Value<std::underlying_type_t<HPTrackType>, "TrkType", "Track type">,
    Mustard::Data::Value<std::underlying_type_t<HPTrackRefPtType>, "RefPtType", "Reference point type">,
    Mustard::Data::Value<std::int32_t, "PDGID", "Particle PDG ID">,
    HPTrackStateModel,
    Mustard::Data::Value<std::vector<std::int32_t>, "CellHitID", "CDC cell hits in this track">,
    Mustard::Data::Value<std::vector<std::int32_t>, "TTCHitID", "TTC hits in this track">>;
using HPTrack = Mustard::Data::Tuple<HPTrackModel>;

/// @brief Simulated high-momentum (high-p) track model, for tracks in MMS
/// @note Only for simulation data
/// @extends HPTrackModel
using SimHPTrackModel = Mustard::Data::TupleModel<
    HPTrackModel,
    Mustard::Data::Value<std::string, "CreatProc", "Track creator process (MC truth)">>;
using SimHPTrack = Mustard::Data::Tuple<SimHPTrackModel>;

} // namespace CRMuSR2::Data
