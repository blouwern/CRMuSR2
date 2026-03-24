#include "CRMuSR2/Detector/Description/Target.h++"
#include "CRMuSR2/Detector/Description/GeometryReference.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace CRMuSR2::Detector::Description {

using namespace Mustard::LiteralUnit::Length;

Target::Target()
    : DescriptionBase{"Target"},
      fSTLFilePath{"PDRTarget.stl"},
      fTargetElevation{35_cm} {
  const auto& geometryReference{Description::GeometryReference::Instance()};
    const auto& geometryDir{geometryReference.ParsedSTLFileDirPath().generic_string()};
    fSTLFilePath = geometryDir + "/" + fSTLFilePath;
}

auto Target::ImportAllValue(const YAML::Node& node) -> void {
    ImportValue(node, fSTLFilePath, "STLFilePath");
    ImportValue(node, fTargetElevation, "TargetElevation");
}

auto Target::ExportAllValue(YAML::Node& node) const -> void {
    ExportValue(node, fSTLFilePath, "STLFilePath");
    ExportValue(node, fTargetElevation, "TargetElevation");
}

} // namespace CRMuSR2::Detector::Description
