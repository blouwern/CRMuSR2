#pragma once

#include "SimCRMu/Detector/DetectorConstruction.h++"

#include "Mustard/Geant4X/Interface/DetectorMessenger.h++"

namespace CRMuSR2::SimCRMu::inline Messenger {

class DetectorMessenger final : public Mustard::Geant4X::DetectorMessenger<DetectorMessenger,
                                                                           DetectorConstruction,
                                                                           "SimCRMu"> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    DetectorMessenger() = default;
    ~DetectorMessenger() = default;
};

} // namespace CRMuSR2::SimCRMu::inline Messenger
