#include "CRMuSR2/Detector/Description/PDRSupport.h++"

#include "Mustard/Utility/LiteralUnit.h++"

using namespace Mustard::LiteralUnit::Length;

namespace CRMuSR2::Detector::Description {
PDRSupport::PDRSupport() :
    DescriptionBase{"PDRSupport"},
    fSTLFilePath{""},
    fPDRSupportThickness{1_cm},
    fPDRSupportOuterWidth{71.6_cm},
    fPDRSupportBaseWidth{11_cm},
    fPDRSupportHeight{71.6_cm},
    fPDRInnerPlatformHeight{2_cm},
    fPDRSupportSpacing{0.2_cm} {}

auto PDRSupport::ImportAllValue(const YAML::Node& node) -> void {
    ImportValue(node, fSTLFilePath, "STLFilePath");
    ImportValue(node, fPDRSupportThickness, "PDRSupportThickness");
    ImportValue(node, fPDRSupportOuterWidth, "PDRSupportOuterWidth");
    ImportValue(node, fPDRSupportBaseWidth, "PDRSupportBaseWidth");
    ImportValue(node, fPDRSupportSpacing, "PDRSupportSpacing");
}

auto PDRSupport::ExportAllValue(YAML::Node& node) const -> void {
    ExportValue(node, fSTLFilePath, "STLFilePath");
    ExportValue(node, fPDRSupportThickness, "PDRSupportThickness");
    ExportValue(node, fPDRSupportOuterWidth, "PDRSupportOuterWidth");
    ExportValue(node, fPDRSupportBaseWidth, "PDRSupportBaseWidth");
    ExportValue(node, fPDRSupportSpacing, "PDRSupportSpacing");
}

} // namespace CRMuSR2::Detector::Description
