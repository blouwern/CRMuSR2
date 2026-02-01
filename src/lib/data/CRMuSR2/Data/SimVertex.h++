#pragma once

#include "Mustard/Data/Tuple.h++"
#include "Mustard/Data/TupleModel.h++"
#include "Mustard/Data/Value.h++"

#include "muc/array"

namespace CRMuSR2::Data {

using SimPrimaryVertex = Mustard::Data::TupleModel<
    Mustard::Data::Value<int, "EvtID", "MC Event ID">,
    Mustard::Data::Value<int, "PDGID", "PDG ID">,
    Mustard::Data::Value<double, "t0", "Primary time">,
    Mustard::Data::Value<muc::array3f, "x0", "Primary position">,
    Mustard::Data::Value<float, "Ek0", "Primary kinetic energy">,
    Mustard::Data::Value<muc::array3f, "p0", "Primary momentum">>;

using SimDecayVertex = Mustard::Data::TupleModel<
    Mustard::Data::Value<int, "EvtID", "Event ID">,
    Mustard::Data::Value<int, "PDGID", "Parent PDG ID">,
    Mustard::Data::Value<std::vector<int>, "SecPDGID", "PDG ID of decay products">,
    Mustard::Data::Value<double, "t", "Decay time">,
    Mustard::Data::Value<muc::array3f, "x", "Decay position">,
    Mustard::Data::Value<int, "TrkID", "Parent MC Track ID">,
    Mustard::Data::Value<float, "Ek", "Parent kinetic energy at decay">,
    Mustard::Data::Value<muc::array3f, "p", "Parent momentum at decay">>;

} // namespace CRMuSR2::Data
