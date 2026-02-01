#pragma once

#include "Mustard/Detector/Description/DescriptionBase.h++"

#include <string>

namespace CRMuSR2::Detector::Description {

class PDRScintillator final : public Mustard::Detector::Description::DescriptionBase<PDRScintillator> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    PDRScintillator();
    ~PDRScintillator() override = default;

public:
    auto STLFilePath() const -> auto { return fSTLFilePath; }
    auto NScintillatorPerLayer() const -> auto { return fNScintillatorPerLayer; }
    auto PDRScintillatorLength() const -> auto { return fPDRScintillatorLength; }
    auto PDRScintillatorThickness() const -> auto { return fPDRScintillatorThickness; }
    auto PDRScintillatorWidth() const -> auto { return fPDRScintillatorWidth; }
    auto PDRScintillatorHeadWidth() const -> auto { return fPDRScintillatorHeadWidth; }
    auto PDRScintillatorHeadHight() const -> auto { return fPDRScintillatorHeadHight; }
    auto PDRScintillatorPackageThickness() const -> auto { return fPDRScintillatorPackageThickness; }
    auto PSScintillationEnergyBin() const -> auto& { return fPSScintillationEnergyBin; }
    auto PSScintillationComponent1() const -> auto& { return fPSScintillationComponent1; }
    auto PSScintillationYield() const -> auto { return fPSScintillationYield; }
    auto PSScintillationTimeConstant1() const -> auto { return fPSScintillationTimeConstant1; }
    auto PSResolutionScale() const -> auto { return fPSResolutionScale; }

    auto STLFilePath(std::string val) -> void { fSTLFilePath = std::move(val); }
    auto NScintillatorPerLayer(int val) -> void { fNScintillatorPerLayer = val; }
    auto PDRScintillatorLength(double val) -> void { fPDRScintillatorLength = val; }
    auto PDRScintillatorThickness(double val) -> void { fPDRScintillatorThickness = val; }
    auto PDRScintillatorWidth(double val) -> void { fPDRScintillatorWidth = val; }
    auto PDRScintillatorHeadWidth(double val) -> void { fPDRScintillatorHeadWidth = val; }
    auto PDRScintillatorHeadHight(double val) -> void { fPDRScintillatorHeadHight = val; }
    auto PDRScintillatorPackageThickness(double val) -> void { fPDRScintillatorPackageThickness = val; }


private:
    auto ImportAllValue(const YAML::Node& node) -> void override;
    auto ExportAllValue(YAML::Node& node) const -> void override;

private:
    std::string fSTLFilePath;
    int fNScintillatorPerLayer;
    double fPDRScintillatorLength;
    double fPDRScintillatorThickness;
    double fPDRScintillatorWidth;
    double fPDRScintillatorHeadWidth;
    double fPDRScintillatorHeadHight;
    double fPDRScintillatorPackageThickness;
    std::vector<double> fPSScintillationEnergyBin;
    std::vector<double> fPSScintillationComponent1;
    double fPSScintillationYield;
    double fPSScintillationTimeConstant1;
    double fPSResolutionScale;

};

} // namespace CRMuSR2::Detector::Description
