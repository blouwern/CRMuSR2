#pragma once

#include "CRMuSR2/Simulation/Hit/PDRSimHit.h++"

#include "G4VSensitiveDetector.hh"

#include "muc/ptrvec"

#include <memory>
#include <unordered_map>
#include <vector>

namespace CRMuSR2::inline Simulation::inline SD {

class PDRPMSD;

class PDRSD : public G4VSensitiveDetector {
public:
    PDRSD(const G4String& sdName, const PDRPMSD* PDRPMSD = {});

    virtual auto Initialize(G4HCofThisEvent* hitsCollection) -> void override;
    virtual auto ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool override;
    virtual auto EndOfEvent(G4HCofThisEvent*) -> void override;

protected:
    const PDRPMSD* const fPDRPMSD;

    double fEnergyDepositionThreshold;

    std::unordered_map<int, std::vector<std::unique_ptr<PDRSimHit>>> fSplitHit;
    PDRSimHitCollection* fHitsCollection;
};

} // namespace CRMuSR2::inline Simulation::inline SD
