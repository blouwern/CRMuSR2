#pragma once

#include "Mustard/Detector/Definition/DefinitionBase.h++"

namespace CRMuSR2::Detector::Definition {

class PDR final : public Mustard::Detector::Definition::DefinitionBase {
private:
    auto Construct(bool checkOverlaps) -> void override;
    auto DefineMateiral() -> void;
private:
    G4Material* fAir;
    G4Material* fSteel;
    G4Material* fPlasticScintillator;
    G4Material* fEpoxy;
    G4Material* fSiliconeGrease;
    G4Material* fSi;

};

} // namespace CRMuSR2::Detector::Definition