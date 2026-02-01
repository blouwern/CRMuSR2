#pragma once

#include "Mustard/Detector/Description/DescriptionBase.h++"

#include <string>

namespace CRMuSR2::Detector::Description {

class PDRModel final : public Mustard::Detector::Description::DescriptionBase<PDRModel> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    PDRModel();
    ~PDRModel() override = default;

// public:
    // auto STLFilePath() const -> const auto& { return fSTLFilePath; }
    // auto PDRModelElevation() const -> auto { return fPDRModelElevation; }

    // auto STLFilePath(std::string val) -> void { fSTLFilePath = std::move(val); }
    // auto PDRModelElevation(double val) -> void { fPDRModelElevation = val; }

private:
    auto ImportAllValue(const YAML::Node& node) -> void override;
    auto ExportAllValue(YAML::Node& node) const -> void override;

private:
    // std::string fSTLFilePath;
    // double fPDRModelElevation;
};

} // namespace CRMuSR2::Detector::Description
