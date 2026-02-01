#include "CRMuSR2/Detector/Description/PDRSiPM.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace CRMuSR2::Detector::Description {

using namespace Mustard::LiteralUnit::Length;

PDRSiPM::PDRSiPM() :
    DescriptionBase{"PDRSiPM"},
    // fSTLFilePath{},
    fPDRSiPMWidth{0.64_cm},
    fPDRSiPMSensorWidth{0.6_cm},
    fPDRSiPMSensorThickness{0.032_cm},
    fPDRSiPMResinThickness{0.01_cm},
    fPDRSiPMCouplerThickness{0.01_cm} {}

auto PDRSiPM::ImportAllValue(const YAML::Node& node) -> void {
    // ImportValue(node, fSTLFilePath, "STLFilePath");
    ImportValue(node, fPDRSiPMWidth, "PDRSiPMBaseWidth");
    ImportValue(node, fPDRSiPMSensorWidth, "PDRSiPMSensorWidth");
    ImportValue(node, fPDRSiPMSensorThickness, "PDRSiPMSensorThickness");
    ImportValue(node, fPDRSiPMResinThickness, "PDRSiPMResinThickness");
    ImportValue(node, fPDRSiPMCouplerThickness, "PDRSiPMCouplerThickness");
}

auto PDRSiPM::ExportAllValue(YAML::Node& node) const -> void {
    // ExportValue(node, fSTLFilePath, "STLFilePath");
    ExportValue(node, fPDRSiPMWidth, "PDRSiPMBaseWidth");
    ExportValue(node, fPDRSiPMSensorWidth, "PDRSiPMSensorWidth");
    ExportValue(node, fPDRSiPMSensorThickness, "PDRSiPMSensorThickness");
    ExportValue(node, fPDRSiPMResinThickness, "PDRSiPMResinThickness");
    ExportValue(node, fPDRSiPMCouplerThickness, "PDRSiPMCouplerThickness");
}

} // namespace CRMuSR2::Detector::Description
