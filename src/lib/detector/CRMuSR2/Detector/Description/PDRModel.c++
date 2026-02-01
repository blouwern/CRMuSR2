#include "CRMuSR2/Detector/Description/PDRModel.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace CRMuSR2::Detector::Description {

using namespace Mustard::LiteralUnit::Length;

PDRModel::PDRModel() :
    DescriptionBase{"PDR"} {}

auto PDRModel::ImportAllValue(const YAML::Node&) -> void {
}

auto PDRModel::ExportAllValue(YAML::Node&) const -> void {
}

} // namespace CRMuSR2::Detector::Description
