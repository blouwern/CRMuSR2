#include "CRMuSR2/Detector/Definition/PDR.h++"
#include "CRMuSR2/Detector/Definition/Target.h++"
#include "CRMuSR2/Detector/Definition/World.h++"

#include "CRMuSR2/Detector/Description/PDRModel.h++"

#include "SimCRMu/Detector/DetectorConstruction.h++"
#include "SimCRMu/Messenger/DetectorMessenger.h++"
#include "SimCRMu/SD/PDRPMSD.h++"
#include "SimCRMu/SD/PDRSD.h++"

#include "Mustard/Detector/Description/DescriptionIO.h++"

#include "G4NistManager.hh"

namespace CRMuSR2::SimCRMu::inline Action {

DetectorConstruction::DetectorConstruction() :
    PassiveSingleton{this},
    G4VUserDetectorConstruction{},
    fCheckOverlap{true},
    fWorld{} {
    DetectorMessenger::EnsureInstantiation();
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
    using namespace CRMuSR2::Detector::Definition;

    fWorld = std::make_unique<World>();
    fWorld->NewDaughter<Target>(fCheckOverlap);
    auto& pdr{fWorld->NewDaughter<PDR>(fCheckOverlap)};
    const auto pdrName{CRMuSR2::Detector::Description::PDRModel::Instance().Name()};
    const auto& pdrPMSD{new SD::PDRPMSD(pdrName + "SiPM")};
    const auto& pdrSD{new SD::PDRSD(pdrName + "Scintillator", pdrPMSD)};

    pdr.RegisterSD("PDRSiPMSensor", pdrPMSD);
    pdr.RegisterSD("PDRScintillator", pdrSD);

    return fWorld->PhysicalVolume();
}

} // namespace CRMuSR2::SimCRMu::inline Action
