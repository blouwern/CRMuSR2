#pragma once

#include "CRMuSR2/Simulation/Hit/PDRPMSimHit.h++"

#include "G4VSensitiveDetector.hh"

#include "muc/ptrvec"

// #include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

namespace CRMuSR2::inline Simulation::inline SD {

class PDRPMSD : public G4VSensitiveDetector {

public:
    PDRPMSD(const G4String& sdName);

    virtual auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    virtual auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    virtual auto EndOfEvent(G4HCofThisEvent*) -> void override;

    auto NOpticalPhotonHit() const -> std::unordered_map<int, int>;

protected:
    std::unordered_map<int, std::vector<std::unique_ptr<PDRPMSimHit>>> fHit;
    PDRPMSimHitCollection* fHitsCollection;
    
};

} // namespace CRMuSR2::inline Simulation::inline SD
