#pragma once

#include "CRMuSR2/Simulation/SD/PDRSD.h++"

namespace CRMuSR2::SimCRMu::inline SD {

class PDRSD final : public Simulation::PDRSD {
public:
    using Simulation::PDRSD::PDRSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} // namespace CRMuSR2::SimCRMu::inline SD
