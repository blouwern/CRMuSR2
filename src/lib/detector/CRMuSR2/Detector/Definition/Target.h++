#pragma once

#include "Mustard/Detector/Definition/DefinitionBase.h++"

namespace CRMuSR2::Detector::Definition {

class Target final : public Mustard::Detector::Definition::DefinitionBase {
private:
    auto Construct(bool checkOverlaps) -> void override;
};

} // namespace CRMuSR2::Detector::Definition
