#pragma once

#include "Mustard/Detector/Description/DescriptionBase.h++"

#include <string>

namespace CRMuSR2::Detector::Description {

class PDRSupport final : public Mustard::Detector::Description::DescriptionBase<PDRSupport> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    PDRSupport();
    ~PDRSupport() override = default;

public:
    auto STLFilePath() const -> const auto& { return fSTLFilePath; }
    auto PDRSupportThickness() const -> auto { return fPDRSupportThickness; }
    auto PDRSupportOuterWidth() const -> auto { return fPDRSupportOuterWidth; }
    auto PDRSupportBaseWidth() const -> auto { return fPDRSupportBaseWidth; }
    auto PDRSupportHeight() const -> auto { return fPDRSupportHeight; }
    auto PDRInnerPlatformHeight() const -> auto { return fPDRInnerPlatformHeight; }
    auto PDRSupportSpacing() const -> auto { return fPDRSupportSpacing; }

    auto STLFilePath(std::string val) -> void { fSTLFilePath = std::move(val); }
    auto PDRSupportThickness(double val) -> void { fPDRSupportThickness = val; }
    auto PDRSupportOuterWidth(double val) -> void { fPDRSupportOuterWidth = val; }
    auto PDRSupportBaseWidth(double val) -> void { fPDRSupportBaseWidth = val; }
    auto PDRSupportHeight(double val) -> void { fPDRSupportHeight = val; }
    auto PDRInnerPlatformHeight(double val) -> void { fPDRInnerPlatformHeight = val; }
    auto PDRSupportSpacing(double val) -> void { fPDRSupportSpacing = val; }


private:
    auto ImportAllValue(const YAML::Node& node) -> void override;
    auto ExportAllValue(YAML::Node& node) const -> void override;

private:
    std::string fSTLFilePath;
    double fPDRSupportThickness;
    double fPDRSupportOuterWidth;
    double fPDRSupportBaseWidth;
    double fPDRSupportHeight;
    double fPDRInnerPlatformHeight;
    double fPDRSupportSpacing;
};

} // namespace CRMuSR2::Detector::Description
