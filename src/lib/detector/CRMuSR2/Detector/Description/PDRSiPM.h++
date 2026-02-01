#pragma once

#include "Mustard/Detector/Description/DescriptionBase.h++"

#include <string>

namespace CRMuSR2::Detector::Description {

class PDRSiPM final : public Mustard::Detector::Description::DescriptionBase<PDRSiPM> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    PDRSiPM();
    ~PDRSiPM() override = default;

public:
    // auto STLFilePath() const -> auto { return fSTLFilePath; }
    auto PDRSiPMWidth() const -> auto { return fPDRSiPMWidth; }
    auto PDRSiPMSensorWidth() const -> auto { return fPDRSiPMSensorWidth; }
    auto PDRSiPMSensorThickness() const -> auto { return fPDRSiPMSensorThickness; }
    auto PDRSiPMResinThickness() const -> auto { return fPDRSiPMResinThickness; }
    auto PDRSiPMCouplerThickness() const -> auto { return fPDRSiPMCouplerThickness; }

    // auto STLFilePath(std::string val) -> void { fSTLFilePath = std::move(val); }
    auto PDRSiPMWidth(double val) -> void { fPDRSiPMWidth = val; }
    auto PDRSiPMSensorWidth(double val) -> void { fPDRSiPMSensorWidth = val; }
    auto PDRSiPMSensorThickness(double val) -> void { fPDRSiPMSensorThickness = val; }
    auto PDRSiPMResinThickness(double val) -> void { fPDRSiPMResinThickness = val; }
    auto PDRSiPMCouplerThickness(double val) -> void { fPDRSiPMCouplerThickness = val; }

private:
    auto ImportAllValue(const YAML::Node& node) -> void override;
    auto ExportAllValue(YAML::Node& node) const -> void override;

private:
    // std::string fSTLFilePath;
    double fPDRSiPMWidth;
    double fPDRSiPMSensorWidth;
    double fPDRSiPMSensorThickness;
    double fPDRSiPMResinThickness;
    double fPDRSiPMCouplerThickness;
};

} // namespace CRMuSR2::Detector::Description
