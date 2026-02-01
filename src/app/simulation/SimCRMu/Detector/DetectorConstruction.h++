#pragma once

#include "CRMuSR2/Detector/Description/PDRScintillator.h++"
#include "CRMuSR2/Detector/Description/PDRSiPM.h++"
#include "CRMuSR2/Detector/Description/PDRSupport.h++"
#include "CRMuSR2/Detector/Description/Target.h++"
#include "CRMuSR2/Detector/Description/World.h++"

#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "G4VUserDetectorConstruction.hh"

#include <memory>
#include <tuple>

namespace Mustard::Detector::Definition {
class DefinitionBase;
} // namespace Mustard::Detector::Definition

namespace CRMuSR2::SimCRMu::inline Action {

class DetectorConstruction final : public Mustard::Env::Memory::PassiveSingleton<DetectorConstruction>,
                                   public G4VUserDetectorConstruction {
public:
    DetectorConstruction();

    auto Construct() -> G4VPhysicalVolume* override;

    auto SetCheckOverlaps(G4bool checkOverlaps) -> void { fCheckOverlap = checkOverlaps; }

public:
    using ProminentDescription = std::tuple<Detector::Description::PDRScintillator,
                                            Detector::Description::PDRSiPM,
                                            Detector::Description::PDRSupport,
                                            Detector::Description::Target,
                                            Detector::Description::World>;

private:
    G4bool fCheckOverlap;

    std::unique_ptr<Mustard::Detector::Definition::DefinitionBase> fWorld;
};

} // namespace CRMuSR2::SimCRMu::inline Action
