#include "CRMuSR2/Detector/Description/GeometryReference.h++"

namespace CRMuSR2::Detector::Description {

GeometryReference::GeometryReference()
    : DescriptionBase{"GeometryReference"},
      fSTLFileDirPath{"${CRMuSR2_GEOMETRY_PATH}"} {}

auto GeometryReference::ImportAllValue(const YAML::Node &node) -> void {
  ImportValue(node, fSTLFileDirPath, "STLFileDirPath");
}

auto GeometryReference::ExportAllValue(YAML::Node &node) const -> void {
  ExportValue(node, fSTLFileDirPath, "STLFileDirPath");
}

} // namespace CRMuSR2::Detector::Description
