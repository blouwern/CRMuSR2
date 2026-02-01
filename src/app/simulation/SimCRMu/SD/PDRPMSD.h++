#pragma once

#include "CRMuSR2/Simulation/SD/PDRPMSD.h++"

namespace CRMuSR2::SimCRMu::inline SD {

class PDRPMSD final : public Simulation::PDRPMSD {
public:
    using Simulation::PDRPMSD::PDRPMSD;

    auto EndOfEvent(G4HCofThisEvent* hc) -> void override;
};

} // namespace CRMuSR2::SimCRMu::inline SD
