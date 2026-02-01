#pragma once

#include "Mustard/Detector/Description/DescriptionBase.h++"

#include <string>

namespace CRMuSR2::Detector::Description {

class Target final : public Mustard::Detector::Description::DescriptionBase<Target> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    Target();
    ~Target() override = default;

public:
    auto STLFilePath() const -> const auto& { return fSTLFilePath; }
    auto TargetElevation() const -> auto { return fTargetElevation; }

    auto STLFilePath(std::string val) -> void { fSTLFilePath = std::move(val); }
    auto TargetElevation(double val) -> void { fTargetElevation = val; }

private:
    auto ImportAllValue(const YAML::Node& node) -> void override;
    auto ExportAllValue(YAML::Node& node) const -> void override;

private:
    std::string fSTLFilePath;
    double fTargetElevation;
};

} // namespace CRMuSR2::Detector::Description
